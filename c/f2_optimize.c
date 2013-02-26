// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
// 
// Permission to use, copy, modify and distribute this software and its
// documentation is hereby granted, provided that both the copyright
// notice and this permission notice appear in all copies of the
// software, derivative works or modified versions, and any portions
// thereof, and that both notices appear in supporting documentation.
// 
// BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
// BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
// WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
// 
// Bo Morgan requests users of this software to return to bo@mit.edu any
// improvements or extensions that they make and grant Bo Morgan the
// rights to redistribute these changes.
// 

#include "funk2.h"

//#define F2__OPTIMIZE__DEBUG_PRINTF


// optimize_bytecode

def_primobject_3_slot(optimize_bytecode,
		      optimize_context,
		      sequence,
		      execution_count);

f2ptr f2__optimize_bytecode__new(f2ptr cause, f2ptr optimize_context, f2ptr sequence) {
  f2ptr execution_count = f2integer__new(cause, 0);
  return f2optimize_bytecode__new(cause,
				  optimize_context,
				  sequence,
				  execution_count);
}
def_pcfunk2(optimize_bytecode__new, optimize_context, sequence,
	    "",
	    return f2__optimize_bytecode__new(this_cause, optimize_context, sequence));


f2ptr raw__optimize_bytecode__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_bytecode"),
					       new__symbol(cause, "sequence"), f2__optimize_bytecode__sequence(cause, this),
					       new__symbol(cause, "execution_count"),  f2__optimize_bytecode__execution_count( cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_bytecode__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_bytecode,    this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_bytecode__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_bytecode__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this optimize_bytecode to the given terminal.",
	    return f2__optimize_bytecode__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_bytecode__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_bytecode__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_bytecode.terminal_print_with_frame__funk);}
  return this;
}


// optimize_chunk

def_primobject_2_slot(optimize_chunk,
		      bytecode_sequence,
		      transition);

f2ptr f2__optimize_chunk__new(f2ptr cause, f2ptr bytecode_sequence, f2ptr transition) {
  return f2optimize_chunk__new(cause,
					bytecode_sequence,
					transition);
}
def_pcfunk2(optimize_chunk__new, bytecode_sequence, transition,
	    "",
	    return f2__optimize_chunk__new(this_cause, bytecode_sequence, transition));


// optimize_chunk

void raw__bytecodes__add_to_chunk_sequence_ptypehash(f2ptr cause, f2ptr these, f2ptr chunk_sequence_ptypehash, f2ptr seen_sequence_set) {
  if (these != nil) {
    if (! raw__set__contains(cause, seen_sequence_set, these)) {
      raw__ptypehash__add(cause, chunk_sequence_ptypehash, these, f2__optimize_chunk__new(cause, nil, nil));
      {
	f2ptr iter = these;
	while (iter != nil) {
	  if (! raw__set__contains(cause, seen_sequence_set, iter)) {
	    raw__set__add(cause, seen_sequence_set, iter);
	  }
	  f2ptr next     = f2__cons__cdr(cause, iter);
	  f2ptr bytecode = f2__cons__car(cause, iter);
	  {
	    f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
	    if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk"))) {
	      raw__ptypehash__add(cause, chunk_sequence_ptypehash, next, f2__optimize_chunk__new(cause, nil, nil));
	    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk"))) {
	      raw__ptypehash__add(cause, chunk_sequence_ptypehash, next, f2__optimize_chunk__new(cause, nil, nil));
	    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code"))) {
	      raw__ptypehash__add(cause, chunk_sequence_ptypehash, next, f2__optimize_chunk__new(cause, nil, nil));
	    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump"))) {
	      f2ptr jump_sequence = f2__bytecode__arg0(cause, bytecode);
	      if (! raw__ptypehash__contains(cause, chunk_sequence_ptypehash, jump_sequence)) {
		raw__ptypehash__add(cause, chunk_sequence_ptypehash, jump_sequence, f2__optimize_chunk__new(cause, nil, nil));
		raw__bytecodes__add_to_chunk_sequence_ptypehash(cause, jump_sequence, chunk_sequence_ptypehash, seen_sequence_set);
	      }
	    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump"))) {
	      f2ptr jump_sequence = f2__bytecode__arg0(cause, bytecode);
	      if (! raw__ptypehash__contains(cause, chunk_sequence_ptypehash, jump_sequence)) {
		raw__ptypehash__add(cause, chunk_sequence_ptypehash, jump_sequence, f2__optimize_chunk__new(cause, nil, nil));
		raw__bytecodes__add_to_chunk_sequence_ptypehash(cause, jump_sequence, chunk_sequence_ptypehash, seen_sequence_set);
	      }
	      raw__ptypehash__add(cause, chunk_sequence_ptypehash, next, f2__optimize_chunk__new(cause, nil, nil));
	    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump"))) {
	      f2ptr jump_sequence = f2__bytecode__arg0(cause, bytecode);
	      if (! raw__ptypehash__contains(cause, chunk_sequence_ptypehash, jump_sequence)) {
		raw__ptypehash__add(cause, chunk_sequence_ptypehash, jump_sequence, f2__optimize_chunk__new(cause, nil, nil));
		raw__bytecodes__add_to_chunk_sequence_ptypehash(cause, jump_sequence, chunk_sequence_ptypehash, seen_sequence_set);
	      }
	      raw__ptypehash__add(cause, chunk_sequence_ptypehash, next, f2__optimize_chunk__new(cause, nil, nil));
	    }	  
	  }
	  iter = next;
	}
      }
    }
  }
}

f2ptr raw__optimize_chunk__new_from_bytecodes(f2ptr cause, f2ptr these) {
  f2ptr chunk_sequence_ptypehash = raw__ptypehash__new(cause, 6);
  f2ptr seen_sequence_set        = raw__set__new(cause, 7);
  raw__bytecodes__add_to_chunk_sequence_ptypehash(cause, these, chunk_sequence_ptypehash, seen_sequence_set);
  ptypehash__iteration(cause, chunk_sequence_ptypehash, sequence, chunk,
		       f2ptr new_sequence = nil;
		       f2ptr new_iter     = nil;
		       {
			 f2ptr iter = sequence;
			 while (iter != nil) {
			   f2ptr next     = f2__cons__cdr(cause, iter);
			   f2ptr bytecode = f2__cons__car(cause, iter);
			   {
			     f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
			     if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk"))) {
			       f2ptr transition_type = new__symbol(cause, "jump-funk");
			       f2ptr next_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, next);
			       f2ptr true_chunk      = nil;
			       f2ptr false_chunk     = nil;
			       f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
			       f2__optimize_chunk__transition__set(cause, chunk, transition);
			       break;
			     } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk"))) {
			       f2ptr transition_type = new__symbol(cause, "funk");
			       f2ptr next_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, next);
			       f2ptr true_chunk      = nil;
			       f2ptr false_chunk     = nil;
			       f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
			       f2__optimize_chunk__transition__set(cause, chunk, transition);
			       break;
			     } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code"))) {
			       f2ptr transition_type = new__symbol(cause, "machine_code");
			       f2ptr next_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, next);
			       f2ptr true_chunk      = nil;
			       f2ptr false_chunk     = nil;
			       f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
			       f2__optimize_chunk__transition__set(cause, chunk, transition);
			       break;
			     } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump"))) {
			       f2ptr jump_sequence = f2__bytecode__arg0(cause, bytecode);
			       {
				 f2ptr transition_type = new__symbol(cause, "jump");
				 f2ptr next_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, jump_sequence);
				 f2ptr true_chunk      = nil;
				 f2ptr false_chunk     = nil;
				 f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
				 f2__optimize_chunk__transition__set(cause, chunk, transition);
			       }
			       break;
			     } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump"))) {
			       f2ptr jump_sequence = f2__bytecode__arg0(cause, bytecode);
			       {
				 f2ptr transition_type = new__symbol(cause, "if-jump");
				 f2ptr next_chunk      = nil;
				 f2ptr true_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, jump_sequence);
				 f2ptr false_chunk     = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, next);
				 f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
				 f2__optimize_chunk__transition__set(cause, chunk, transition);
			       }
			       break;
			     } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump"))) {
			       f2ptr jump_sequence = f2__bytecode__arg0(cause, bytecode);
			       {
				 f2ptr transition_type = new__symbol(cause, "else-jump");
				 f2ptr next_chunk      = nil;
				 f2ptr true_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, next);
				 f2ptr false_chunk     = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, jump_sequence);
				 f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
				 f2__optimize_chunk__transition__set(cause, chunk, transition);
			       }
			       break;
			     } else if ((iter != sequence) &&
					raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, iter)) {
			       f2ptr transition_type = new__symbol(cause, "jumped-to");
			       f2ptr next_chunk      = raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, iter);
			       f2ptr true_chunk      = nil;
			       f2ptr false_chunk     = nil;
			       f2ptr transition      = f2__optimize_transition__new(cause, transition_type, next_chunk, true_chunk, false_chunk);
			       f2__optimize_chunk__transition__set(cause, chunk, transition);
			       break;
			     }
			     f2ptr new_cons = raw__cons__new(cause, bytecode, nil);
			     if (new_iter == nil) {
			       new_sequence = new_cons;
			       new_iter     = new_cons;
			     } else {
			       f2__cons__cdr__set(cause, new_iter, new_cons);
			       new_iter = new_cons;
			     }
			   }
			   iter = next;
			 }
		       }
		       if (new_sequence == nil) {
			 new_sequence = f2__compile__nop(cause);
		       }
		       f2__optimize_chunk__bytecode_sequence__set(cause, chunk, new_sequence);
		       );
  return raw__ptypehash__lookup(cause, chunk_sequence_ptypehash, these);
}

f2ptr f2__optimize_chunk__new_from_bytecodes(f2ptr cause, f2ptr these) {
  assert_argument_type(conslist, these);
  return raw__optimize_chunk__new_from_bytecodes(cause, these);
}
def_pcfunk1(optimize_chunk__new_from_bytecodes, these,
	    "Converts the given bytecode sequence into a new optimize_chunk and optimize_transition graph.",
	    return f2__optimize_chunk__new_from_bytecodes(this_cause, these));


void raw__optimize_chunk__as__bytecodes__gather_chunks(f2ptr cause, f2ptr this, f2ptr sequence_chunk_ptypehash) {
  if (! raw__ptypehash__contains(cause, sequence_chunk_ptypehash, this)) {
    {
      f2ptr new_sequence = nil;
      f2ptr new_iter     = nil;
      {
	f2ptr iter = f2__optimize_chunk__bytecode_sequence(cause, this);
	while (iter != nil) {
	  f2ptr bytecode = f2__cons__car(cause, iter);
	  {
	    f2ptr new_cons = raw__cons__new(cause, bytecode, nil);
	    if (new_iter == nil) {
	      new_sequence = new_cons;
	      new_iter     = new_cons;
	    } else {
	      f2__cons__cdr__set(cause, new_iter, new_cons);
	      new_iter = new_cons;
	    }
	  }
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, new_sequence);
    }
    f2ptr transition = f2__optimize_chunk__transition(cause, this);
    if (transition != nil) {
      {
	f2ptr next_chunk = f2__optimize_transition__next_chunk(cause, transition);
	if (next_chunk != nil) {
	  raw__optimize_chunk__as__bytecodes__gather_chunks(cause, next_chunk, sequence_chunk_ptypehash);
	}
      }
      {
	f2ptr true_chunk = f2__optimize_transition__true_chunk(cause, transition);
	if (true_chunk != nil) {
	  raw__optimize_chunk__as__bytecodes__gather_chunks(cause, true_chunk, sequence_chunk_ptypehash);
	}
      }
      {
	f2ptr false_chunk = f2__optimize_transition__false_chunk(cause, transition);
	if (false_chunk != nil) {
	  raw__optimize_chunk__as__bytecodes__gather_chunks(cause, false_chunk, sequence_chunk_ptypehash);
	}
      }
    }
  }
}

void raw__optimize_chunk__as__bytecodes__append_transition(f2ptr cause, f2ptr this, f2ptr sequence_chunk_ptypehash, f2ptr finished_chunk_set) {
  if (! raw__set__contains(cause, finished_chunk_set, this)) {
    raw__set__add(cause, finished_chunk_set, this);
    f2ptr full_bcs   = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, this);
    f2ptr iter_bcs   = full_bcs;
    f2ptr transition = f2__optimize_chunk__transition(cause, this);
    if (transition != nil) {
      f2ptr transition_type = f2__optimize_transition__transition_type(cause, transition);
      if (raw__eq(cause, transition_type, new__symbol(cause, "jump-funk"))) {
	{
	  f2ptr transition_bcs = f2__compile__jump_funk(cause);
	  {f2ptr new_bcs = transition_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	f2ptr next_chunk = f2__optimize_transition__next_chunk(cause, transition);
	{
	  f2ptr next_bcs = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, next_chunk);
	  {f2ptr new_bcs = next_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	raw__optimize_chunk__as__bytecodes__append_transition(cause, next_chunk, sequence_chunk_ptypehash, finished_chunk_set);
      } else if (raw__eq(cause, transition_type, new__symbol(cause, "funk"))) {
	{
	  f2ptr transition_bcs = f2__compile__funk_bc(cause);
	  {f2ptr new_bcs = transition_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	f2ptr next_chunk = f2__optimize_transition__next_chunk(cause, transition);
	{
	  f2ptr next_bcs = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, next_chunk);
	  {f2ptr new_bcs = next_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	raw__optimize_chunk__as__bytecodes__append_transition(cause, next_chunk, sequence_chunk_ptypehash, finished_chunk_set);
      } else if (raw__eq(cause, transition_type, new__symbol(cause, "machine_code"))) {
	error(nil, "raw__optimize_chunk__as__bytecodes__append_transition error: machine_code bytecode not fully implemented.");
      } else if (raw__eq(cause, transition_type, new__symbol(cause, "jump"))) {
	f2ptr next_chunk = f2__optimize_transition__next_chunk(cause, transition);
	f2ptr next_bcs   = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, next_chunk);
	{
	  f2ptr transition_bcs = f2__compile__jump(cause, next_bcs);
	  {f2ptr new_bcs = transition_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	raw__optimize_chunk__as__bytecodes__append_transition(cause, next_chunk, sequence_chunk_ptypehash, finished_chunk_set);
      } else if (raw__eq(cause, transition_type, new__symbol(cause, "if-jump"))) {
	f2ptr true_chunk = f2__optimize_transition__true_chunk(cause, transition);
	f2ptr true_bcs   = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, true_chunk);
	{
	  f2ptr transition_bcs = f2__compile__if_jump(cause, true_bcs);
	  {f2ptr new_bcs = transition_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	f2ptr false_chunk = f2__optimize_transition__false_chunk(cause, transition);
	{
	  f2ptr false_bcs = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, false_chunk);
	  {f2ptr new_bcs = false_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	raw__optimize_chunk__as__bytecodes__append_transition(cause, true_chunk,  sequence_chunk_ptypehash, finished_chunk_set);
	raw__optimize_chunk__as__bytecodes__append_transition(cause, false_chunk, sequence_chunk_ptypehash, finished_chunk_set);
      } else if (raw__eq(cause, transition_type, new__symbol(cause, "else-jump"))) {
	f2ptr false_chunk = f2__optimize_transition__false_chunk(cause, transition);
	f2ptr false_bcs   = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, false_chunk);
	{
	  f2ptr transition_bcs = f2__compile__else_jump(cause, false_bcs);
	  {f2ptr new_bcs = transition_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	f2ptr true_chunk = f2__optimize_transition__true_chunk(cause, transition);
	{
	  f2ptr true_bcs = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, true_chunk);
	  {f2ptr new_bcs = true_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	raw__optimize_chunk__as__bytecodes__append_transition(cause, false_chunk, sequence_chunk_ptypehash, finished_chunk_set);
	raw__optimize_chunk__as__bytecodes__append_transition(cause, true_chunk,  sequence_chunk_ptypehash, finished_chunk_set);
      } else if (raw__eq(cause, transition_type, new__symbol(cause, "jumped-to"))) {
	f2ptr next_chunk = f2__optimize_transition__next_chunk(cause, transition);
	{
	  f2ptr next_bcs = raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, next_chunk);
	  {f2ptr new_bcs = next_bcs;
	    if (iter_bcs == nil) {full_bcs = new_bcs; raw__ptypehash__add(cause, sequence_chunk_ptypehash, this, full_bcs); iter_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}}
	}
	raw__optimize_chunk__as__bytecodes__append_transition(cause, next_chunk, sequence_chunk_ptypehash, finished_chunk_set);
      } else {
	error(nil, "raw__optimize_chunk__as__bytecodes__append_transition error: unknown transition_type.");
      }
    }
  }
}

f2ptr raw__optimize_chunk__as__bytecodes(f2ptr cause, f2ptr this) {
  f2ptr sequence_chunk_ptypehash = raw__ptypehash__new(cause, 6);
  raw__optimize_chunk__as__bytecodes__gather_chunks(cause, this, sequence_chunk_ptypehash);
  f2ptr finished_chunk_set = raw__set__new(cause, 6);
  raw__optimize_chunk__as__bytecodes__append_transition(cause, this, sequence_chunk_ptypehash, finished_chunk_set);
  return raw__ptypehash__lookup(cause, sequence_chunk_ptypehash, this);
}

f2ptr f2__optimize_chunk__as__bytecodes(f2ptr cause, f2ptr this) {
  assert_argument_type(optimize_chunk, this);
  return raw__optimize_chunk__as__bytecodes(cause, this);
}
def_pcfunk1(optimize_chunk__as__bytecodes, this,
	    "Returns a new sequence of bytecodes that represents this optimize_chunk.",
	    return f2__optimize_chunk__as__bytecodes(this_cause, this));


f2ptr raw__optimize_chunk__possible_optimized_funk_bytecodes(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr transition = f2__optimize_chunk__transition(cause, this);
  if (transition != nil) {
    // only try to optimize funks without transitions for now.
    return nil;
  }
  s64   maximum_loop_count = 2; // shouldn't have any loops, actually.
  f2ptr optimize_context   = raw__optimize_context__new(cause, maximum_loop_count);
  // attempt to unroll all loops in simulation
  {
    f2ptr initial_fiber = f2__optimize_context__initial_fiber(cause, optimize_context);
    {
      f2ptr result = raw__optimize_fiber__prepare_to_call_funk(cause, initial_fiber, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    f2ptr possible_too_many_loops_larva = raw__optimize_context__complete_simulation(cause, optimize_context);
    if (raw__larva__is_type(cause, possible_too_many_loops_larva)) {
      if (! raw__optimize_too_many_loops_larva__is_type(cause, possible_too_many_loops_larva)) {
	return possible_too_many_loops_larva;
      }
      // need to extract loops.
      printf("\noptimize warning: loop extraction not yet implemented."); fflush(stdout);
      return nil;
    }
    {
      f2ptr result = raw__optimize_context__compile_new_bytecodes(cause, optimize_context, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  {
    f2ptr optimized_bytecodes = f2__optimize_context__optimized_bytecodes(cause, optimize_context);
    return optimized_bytecodes;
  }
}

f2ptr f2__optimize_chunk__possible_optimized_funk_bytecodes(f2ptr cause, f2ptr this, f2ptr funk) {
  assert_argument_type(optimize_chunk, this);
  return raw__optimize_chunk__possible_optimized_funk_bytecodes(cause, this, funk);
}
def_pcfunk2(optimize_chunk__possible_optimized_funk_bytecodes, this, funk,
	    "Returns optimized bytescodes for this funk or nil if no optimization can be found.",
	    return f2__optimize_chunk__possible_optimized_funk_bytecodes(this_cause, this, funk));


f2ptr raw__optimize_chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_chunk"),
					       new__symbol(cause, "bytecode_sequence"), f2__optimize_chunk__bytecode_sequence(cause, this),
					       new__symbol(cause, "transition"),        f2__optimize_chunk__transition(       cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_chunk,    this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_chunk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_chunk__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this optimize_chunk to the given terminal.",
	    return f2__optimize_chunk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_chunk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_chunk__primobject_type__new(cause);
  {char* slot_name = "as-bytecodes";                      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.as__bytecodes__funk);}
  {char* slot_name = "possible_optimized_funk_bytecodes"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.possible_optimized_funk_bytecodes__funk);}
  {char* slot_name = "terminal_print_with_frame";         f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.terminal_print_with_frame__funk);}
  return this;
}


// optimize_transition

def_primobject_4_slot(optimize_transition,
		      transition_type,
		      next_chunk,
		      true_chunk,
		      false_chunk);

f2ptr f2__optimize_transition__new(f2ptr cause,
				   f2ptr transition_type,
				   f2ptr next_chunk,
				   f2ptr true_chunk,
				   f2ptr false_chunk) {
  return f2optimize_transition__new(cause,
				    transition_type,
				    next_chunk,
				    true_chunk,
				    false_chunk);
}
def_pcfunk4(optimize_transition__new, transition_type, next_chunk, true_chunk, false_chunk,
	    "",
	    return f2__optimize_transition__new(this_cause, transition_type, next_chunk, true_chunk, false_chunk));


f2ptr raw__optimize_transition__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_transition"),
						new__symbol(cause, "transition_type"), f2__optimize_transition__transition_type(cause, this),
						new__symbol(cause, "next_chunk"),      f2__optimize_transition__next_chunk(cause, this),
						new__symbol(cause, "true_chunk"),      f2__optimize_transition__true_chunk(cause, this),
						new__symbol(cause, "false_chunk"),     f2__optimize_transition__false_chunk(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_transition__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_transition,  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_transition__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_transition__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this optimize_transition to the given terminal.",
	    return f2__optimize_transition__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_transition__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_transition__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_transition.terminal_print_with_frame__funk);}
  return this;
}


// optimize_data

def_primobject_4_slot(optimize_data,
		      optimize_context,
		      name,
		      data_type,
		      args);

f2ptr f2__optimize_data__new(f2ptr cause, f2ptr optimize_context, f2ptr name, f2ptr data_type, f2ptr args) {
  return f2optimize_data__new(cause, optimize_context, name, data_type, args);
}
def_pcfunk4(optimize_data__new, optimize_context, name, data_type, args,
	    "",
	    return f2__optimize_data__new(this_cause, optimize_context, name, data_type, args));




f2ptr raw__optimize_data__compile__jump__funk(f2ptr cause, f2ptr this, boolean_t is_last_value_to_compute) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter       = f2__optimize_data__args(cause, this);
    f2ptr funk__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr args__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, funk__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, funk__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put args data value in args register
    if (raw__optimize_data__is_type(cause, args__data)) {
      {
	f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, args__data));
	if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
      }
      {
	f2ptr new_bcs = f2__compile__copy(cause, new__symbol(cause, "value"), new__symbol(cause, "args"));
	if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
      }
    } else {
      if (args__data == nil) {
	{
	  f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "args"), nil);
	  if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
	}
      } else {
	f2ptr args_iter = args__data;
	while (args_iter != nil) {
	  f2ptr arg__data = f2__cons__car(cause, args_iter);
	  {
	    if (raw__optimize_data__is_type(cause, arg__data)) {
	      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, arg__data);
	      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
	    }
	  }
	  args_iter = f2__cons__cdr(cause, args_iter);
	}
	{
	  {
	    f2ptr new_bcs = f2__compile__block_eval_args_begin(cause);
	    if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
	  }
	  {
	    f2ptr args_iter = args__data;
	    while (args_iter != nil) {
	      f2ptr arg__data  = f2__cons__car(cause, args_iter);
	      f2ptr args__next = f2__cons__cdr(cause, args_iter);
	      {
		if (raw__optimize_data__is_type(cause, arg__data)) {
		  iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, arg__data)));
		} else {
		  iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), arg__data));
		}
		if (args__next != nil) {
		  f2ptr new_bcs = f2__compile__block_eval_args_next(cause);
		  if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
		} else {
		  f2ptr new_bcs = f2__compile__block_eval_args_end(cause);
		  if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
		}
	      }
	      args_iter = args__next;
	    }
	  }
	}
      }
    }
    // put funk data value in value register
    if (raw__optimize_data__is_type(cause, funk__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, funk__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), funk__data));
    }
    // tail recursion optimization
    if (is_last_value_to_compute) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_pop(cause));
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__jump_funk(cause));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_push(cause));
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__funk_bc(cause));
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_pop(cause));
    }
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__lookup(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter      = f2__optimize_data__args(cause, this);
    f2ptr type_name = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr var_name  = f2__cons__car(cause, iter);
    {
      f2ptr new_bcs = f2__compile__lookup(cause, type_name, var_name);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__mutate__type_var(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter        = f2__optimize_data__args(cause, this);
    f2ptr type_name   = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr var_name    = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr value__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, value__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, value__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put value data in value register
    if (raw__optimize_data__is_type(cause, value__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, value__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), value__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // mutate
    {
      f2ptr new_bcs = f2__compile__type_var__mutate(cause, type_name, var_name);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__globalize__type_var(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter        = f2__optimize_data__args(cause, this);
    f2ptr type_name   = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr var_name    = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr value__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, value__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, value__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put value data in value register
    if (raw__optimize_data__is_type(cause, value__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, value__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), value__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // globalize
    {
      f2ptr new_bcs = f2__compile__globalize_type_var(cause, type_name, var_name);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__initial__variable(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  f2ptr name     = f2__optimize_data__name(cause, this);
  {
    f2ptr new_bcs = f2__compile__lookup(cause, new__symbol(cause, "variable"), name);
    if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__eq(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__eq(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__not(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter    = f2__optimize_data__args(cause, this);
    f2ptr x__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x data value in value register
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__not(cause, new__symbol(cause, "value"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__and(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__and(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__or(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__or(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__add(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__add(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__negative(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter    = f2__optimize_data__args(cause, this);
    f2ptr x__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x data value in value register
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__negative(cause, new__symbol(cause, "value"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__subtract(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__subtract(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__multiply(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__multiply(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__inverse(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter    = f2__optimize_data__args(cause, this);
    f2ptr x__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x data value in value register
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__inverse(cause, new__symbol(cause, "value"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__divide(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__divide(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__modulo(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__modulo(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__increment(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter    = f2__optimize_data__args(cause, this);
    f2ptr x__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x data value in value register
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__increment(cause, new__symbol(cause, "value"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__decrement(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter    = f2__optimize_data__args(cause, this);
    f2ptr x__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x data value in value register
    if (raw__optimize_data__is_type(cause, x__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__decrement(cause, new__symbol(cause, "value"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__numerically_equals(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__numerically_equals(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__greater_than(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__greater_than(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}

f2ptr raw__optimize_data__compile__less_than(f2ptr cause, f2ptr this) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  {
    f2ptr iter     = f2__optimize_data__args(cause, this);
    f2ptr x0__data = f2__cons__car(cause, iter); iter = f2__cons__cdr(cause, iter);
    f2ptr x1__data = f2__cons__car(cause, iter);
    // make sure data variables are defined.
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    if (raw__optimize_data__is_type(cause, x1__data)) {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, x1__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // put x0 data value in value register
    if (raw__optimize_data__is_type(cause, x0__data)) {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x0__data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), x0__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    // push x0 data value onto stack
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__push(cause, new__symbol(cause, "value")));
    // put x1 data value in value register
    if (raw__optimize_data__is_type(cause, x1__data)) {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__lookup_var(cause, f2__optimize_data__name(cause, x1__data)));
    } else {
      iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__set(cause, new__symbol(cause, "value"), x1__data));
    }
    // pop x0 data value into iter register
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__pop(cause, new__symbol(cause, "iter")));
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__less_than(cause, new__symbol(cause, "value"), new__symbol(cause, "iter"), new__symbol(cause, "value")));
  }
  return full_bcs;
}


f2ptr raw__optimize_data__compile_new_bytecodes_for_value(f2ptr cause, f2ptr this, boolean_t is_last_value_to_compute) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  f2ptr optimize_context   = f2__optimize_data__optimize_context(cause, this);
  f2ptr evaluated_data_set = f2__optimize_context__evaluated_data_set(cause, optimize_context);
  if (! raw__set__contains(cause, evaluated_data_set, this)) {
    raw__set__add(cause, evaluated_data_set, this);
  } else {
    printf("\noptimize_data warning: evaluating data twice."); fflush(stdout);
    printf("\ndata: "); f2__terminal_print(cause, this); fflush(stdout);
  }
  {
    f2ptr data_type = f2__optimize_data__data_type(cause, this);
    if (raw__eq(cause, data_type, new__symbol(cause, "jump-funk"))) {
      f2ptr new_bcs = raw__optimize_data__compile__jump__funk(cause, this, is_last_value_to_compute);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "lookup"))) {
      f2ptr new_bcs = raw__optimize_data__compile__lookup(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "mutate-type_var"))) {
      f2ptr new_bcs = raw__optimize_data__compile__mutate__type_var(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "globalize-type_var"))) {
      f2ptr new_bcs = raw__optimize_data__compile__globalize__type_var(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "initial-variable"))) {
      f2ptr new_bcs = raw__optimize_data__compile__initial__variable(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "eq"))) {
      f2ptr new_bcs = raw__optimize_data__compile__eq(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "not"))) {
      f2ptr new_bcs = raw__optimize_data__compile__not(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "and"))) {
      f2ptr new_bcs = raw__optimize_data__compile__and(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "or"))) {
      f2ptr new_bcs = raw__optimize_data__compile__or(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "add"))) {
      f2ptr new_bcs = raw__optimize_data__compile__add(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "negative"))) {
      f2ptr new_bcs = raw__optimize_data__compile__negative(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "subtract"))) {
      f2ptr new_bcs = raw__optimize_data__compile__subtract(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "multiply"))) {
      f2ptr new_bcs = raw__optimize_data__compile__multiply(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "inverse"))) {
      f2ptr new_bcs = raw__optimize_data__compile__inverse(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "divide"))) {
      f2ptr new_bcs = raw__optimize_data__compile__divide(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "modulo"))) {
      f2ptr new_bcs = raw__optimize_data__compile__modulo(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "increment"))) {
      f2ptr new_bcs = raw__optimize_data__compile__increment(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "decrement"))) {
      f2ptr new_bcs = raw__optimize_data__compile__decrement(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "numerically_equals"))) {
      f2ptr new_bcs = raw__optimize_data__compile__numerically_equals(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "less_than"))) {
      f2ptr new_bcs = raw__optimize_data__compile__less_than(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else if (raw__eq(cause, data_type, new__symbol(cause, "greater_than"))) {
      f2ptr new_bcs = raw__optimize_data__compile__greater_than(cause, this);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    } else {
      printf("\noptimize_data warning: data_type not yet implemented."); fflush(stdout);
      return f2larva__new(cause, 51242, nil);
    }
  }
  return full_bcs;
}


f2ptr raw__optimize_data__compile_new_bytecodes_for_define(f2ptr cause, f2ptr this) {
  f2ptr optimize_context = f2__optimize_data__optimize_context(cause, this);
  f2ptr defined_data_set = f2__optimize_context__defined_data_set(cause, optimize_context);
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  if (! raw__set__contains(cause, defined_data_set, this)) {
    raw__set__add(cause, defined_data_set, this);
    f2ptr data_type = f2__optimize_data__data_type(cause, this);
    if (! raw__eq(cause, data_type, new__symbol(cause, "initial-variable"))) {
      boolean_t is_last_value_to_compute = boolean__false;
      {
	f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_value(cause, this, is_last_value_to_compute);
	if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
      }
      {
	f2ptr new_bcs = f2__compile__define_var(cause, f2__optimize_data__name(cause, this));
	if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
      }
    }
  }
  return full_bcs;
}


f2ptr raw__optimize_data__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list8__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_data"),
					       new__symbol(cause, "name"),      f2__optimize_data__name(     cause, this),
					       new__symbol(cause, "data_type"), f2__optimize_data__data_type(cause, this),
					       new__symbol(cause, "args"),      f2__optimize_data__args(     cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_data__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_data,        this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_data__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_data__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this optimize_data to the given terminal.",
	    return f2__optimize_data__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_data__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_data__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__funk);}
  return this;
}


// optimize_fiber

def_primobject_13_slot(optimize_fiber,
		       optimize_context,
		       parent_branched_fiber,
		       branch_condition_data,
		       true_child_branched_fiber,
		       false_child_branched_fiber,
		       data_side_effects,
		       stack,
		       value,
		       iter,
		       program_counter,
		       args,
		       return_reg,
		       env);

f2ptr f2__optimize_fiber__new(f2ptr cause, f2ptr optimize_context) {
  f2ptr parent_branched_fiber      = nil;
  f2ptr branch_condition_data      = nil;
  f2ptr true_child_branched_fiber  = nil;
  f2ptr false_child_branched_fiber = nil;
  f2ptr data_side_effects          = nil;
  f2ptr stack                      = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-stack"),           new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "stack")));
  f2ptr value                      = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-value"),           new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "value")));
  f2ptr iter                       = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-iter"),            new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "iter")));
  f2ptr program_counter            = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-program_counter"), new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "program_counter")));
  f2ptr args                       = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-args"),            new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "args")));
  f2ptr return_reg                 = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-return_reg"),      new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "return_reg")));
  f2ptr env                        = f2__optimize_data__new(cause, optimize_context, gensym(cause, "register-env"),             new__symbol(cause, "initial-register"), f2list1__new(cause, new__symbol(cause, "env")));
  return f2optimize_fiber__new(cause,
			       optimize_context,
			       parent_branched_fiber,
			       branch_condition_data,
			       true_child_branched_fiber,
			       false_child_branched_fiber,
			       data_side_effects,
			       stack,
			       value,
			       iter,
			       program_counter,
			       args,
			       return_reg,
			       env);
}
def_pcfunk1(optimize_fiber__new, optimize_context,
	    "",
	    return f2__optimize_fiber__new(this_cause, optimize_context));


f2ptr raw__optimize_fiber__new_copy(f2ptr cause, f2ptr this) {
  f2ptr optimize_context           = f2__optimize_fiber__optimize_context(cause, this);
  f2ptr parent_branched_fiber      = this;
  f2ptr branch_condition_data      = nil;
  f2ptr true_child_branched_fiber  = nil;
  f2ptr false_child_branched_fiber = nil;
  f2ptr data_side_effects          = nil;
  f2ptr stack                      = f2__optimize_fiber__stack(          cause, this);
  f2ptr value                      = f2__optimize_fiber__value(          cause, this);
  f2ptr iter                       = f2__optimize_fiber__iter(           cause, this);
  f2ptr program_counter            = f2__optimize_fiber__program_counter(cause, this);
  f2ptr args                       = f2__optimize_fiber__args(           cause, this);
  f2ptr return_reg                 = f2__optimize_fiber__return_reg(     cause, this);
  f2ptr env                        = f2__optimize_fiber__env(            cause, this);
  return f2optimize_fiber__new(cause,
			       optimize_context,
			       parent_branched_fiber,
			       branch_condition_data,
			       true_child_branched_fiber,
			       false_child_branched_fiber,
			       data_side_effects,
			       stack,
			       value,
			       iter,
			       program_counter,
			       args,
			       return_reg,
			       env);
}


void raw__optimize_fiber__add_side_effect(f2ptr cause, f2ptr this, f2ptr side_effect) {
  f2ptr side_effects = f2__optimize_fiber__data_side_effects(cause, this);
  f2__optimize_fiber__data_side_effects__set(cause, this, raw__cons__new(cause, side_effect, side_effects));
}



f2ptr raw__optimize_fiber__prepare_to_call_funk(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr funk__body_bytecodes = f2__funk__body_bytecodes(cause, funk);
  f2ptr funk__env            = f2__funk__env(           cause, funk);
  f2ptr args_reg             = nil;
  f2ptr args_reg_iter        = nil;
  {
    f2ptr funk__args = f2__funk__args(cause, funk);
    {
      f2ptr iter = funk__args;
      while (iter != nil) {
	f2ptr variable_name = f2__cons__car(cause, iter);
	f2ptr next          = f2__cons__cdr(cause, iter);
	if (raw__eq(cause, variable_name, __funk2.globalenv.and_rest__symbol)) {
	  if (next == nil) {
	    return f2larva__new(cause, 523531, nil);
	  }
	  f2ptr variable_name = f2__cons__car(cause, next);
	  f2ptr initial_variable_data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), variable_name, new__symbol(cause, "initial-variable"), nil);
	  if (args_reg == nil) {
	    args_reg = initial_variable_data;
	  } else {
	    f2__cons__cdr__set(cause, args_reg_iter, initial_variable_data);
	  }
	  iter = nil;
	} else {
	  f2ptr initial_variable_data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), variable_name, new__symbol(cause, "initial-variable"), nil);
	  f2ptr new_cons = raw__cons__new(cause, initial_variable_data, nil);
	  if (args_reg == nil) {
	    args_reg      = new_cons;
	    args_reg_iter = new_cons;
	  } else {
	    f2__cons__cdr__set(cause, args_reg_iter, new_cons);
	    args_reg_iter = new_cons;
	  }
	  iter = next;
	}
      }
    }
  }
  f2__optimize_fiber__env__set(            cause, this, funk__env);
  f2__optimize_fiber__args__set(           cause, this, args_reg);
  f2__optimize_fiber__program_counter__set(cause, this, funk__body_bytecodes);
  return nil;
}




// push registers

void raw__optimize_fiber__stack__push_constant       (f2ptr cause, f2ptr this, f2ptr constant) {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, constant, f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_value          (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, f2optimize_fiber__value(          this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_iter           (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, f2optimize_fiber__iter(           this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_program_counter(f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, f2optimize_fiber__program_counter(this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_args           (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, f2optimize_fiber__args(           this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_return_reg     (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, f2optimize_fiber__return_reg(     this, cause), f2optimize_fiber__stack(this, cause)));}
void raw__optimize_fiber__stack__push_env            (f2ptr cause, f2ptr this)                 {f2optimize_fiber__stack__set(this, cause, raw__cons__new(cause, f2optimize_fiber__env(            this, cause), f2optimize_fiber__stack(this, cause)));}

// pop registers

void raw__optimize_fiber__stack__pop_value          (f2ptr cause, f2ptr this) {f2optimize_fiber__value__set(          this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_iter           (f2ptr cause, f2ptr this) {f2optimize_fiber__iter__set(           this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_program_counter(f2ptr cause, f2ptr this) {f2optimize_fiber__program_counter__set(this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_args           (f2ptr cause, f2ptr this) {f2optimize_fiber__args__set(           this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_return_reg     (f2ptr cause, f2ptr this) {f2optimize_fiber__return_reg__set(     this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_env            (f2ptr cause, f2ptr this) {f2optimize_fiber__env__set(            this, cause, f2cons__car(f2optimize_fiber__stack(this, cause), cause)); f2optimize_fiber__stack__set(this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}
void raw__optimize_fiber__stack__pop_nil            (f2ptr cause, f2ptr this) {f2optimize_fiber__stack__set(          this, cause, f2cons__cdr(f2optimize_fiber__stack(this, cause), cause));}



f2ptr raw__optimize_fiber__increment_program_counter(f2ptr cause, f2ptr this) {
  f2ptr next_program_counter = nil;
  {
    f2ptr program_counter = f2__optimize_fiber__program_counter(cause, this);
    if (program_counter == nil) {
      return f2larva__new(cause, 523452, nil);
    }
    if (! raw__cons__is_type(cause, program_counter)) {
      return f2larva__new(cause, 523453, nil);
    }
    next_program_counter = f2__cons__cdr(cause, program_counter);
  }
  f2__optimize_fiber__program_counter__set(cause, this, next_program_counter);
  return nil;
}


// jump-funk

f2ptr raw__optimize_fiber__call_bytecode__jump__funk__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr funk__data = f2__optimize_fiber__value(cause, this);
  f2ptr args__data = f2__optimize_fiber__args( cause, this);
  boolean_t all_data_is_known = boolean__true;
  if (raw__optimize_data__is_type(cause, funk__data) ||
      raw__optimize_data__is_type(cause, args__data)) {
    all_data_is_known = boolean__false;
  }
  if (all_data_is_known) {
    f2ptr iter = args__data;
    while (iter != nil) {
      f2ptr arg__data = f2__cons__car(cause, iter);
      if (raw__optimize_data__is_type(cause, arg__data)) {
	all_data_is_known = boolean__false;
	break;
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  if (all_data_is_known) {
    if (raw__funk__is_type(cause, funk__data)) {
      f2ptr funk_env = f2funk__env(           funk__data, cause);
      f2ptr body_bcs = f2funk__body_bytecodes(funk__data, cause);
      f2__optimize_fiber__env__set(            cause, this, funk_env);
      f2__optimize_fiber__program_counter__set(cause, this, body_bcs);
    } else if (raw__cfunk__is_type(              cause, funk__data) ||
	       raw__core_extension_funk__is_type(cause, funk__data)) {
      {
	f2ptr value = f2__force_funk_apply(cause, f2__this__fiber(cause), funk__data, args__data);
	f2__optimize_fiber__value__set(cause, this, value);
      }
      {
	f2ptr return_reg = f2__optimize_fiber__return_reg(cause, this);
	f2__optimize_fiber__program_counter__set(cause, this, return_reg);
      }
    } else if (raw__metro__is_type(cause, funk__data)) {
      f2ptr metro_env = raw__metro__env(           cause, funk__data);
      f2ptr body_bcs  = raw__metro__body_bytecodes(cause, funk__data);
      f2__optimize_fiber__env__set(            cause, this, metro_env);
      f2__optimize_fiber__program_counter__set(cause, this, body_bcs);
    } else {
      return f2larva__new(cause, 523514, nil);
    }
  } else {
    f2ptr result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "funk_result"), new__symbol(cause, "jump-funk"), f2list2__new(cause, funk__data, args__data));
    raw__optimize_fiber__add_side_effect(cause, this, result__data);
    f2__optimize_fiber__value__set(cause, this, result__data);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__jump__funk(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: jump-funk"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__jump__funk__no_increment_pc(cause, this);
}


// funk

f2ptr raw__optimize_fiber__call_bytecode__funk__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr program_counter = f2__optimize_fiber__program_counter(cause, this);
  f2__optimize_fiber__return_reg__set(cause, this, program_counter);
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__jump__funk__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__funk(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: funk"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__funk__no_increment_pc(cause, this);
}


// array

f2ptr raw__optimize_fiber__call_bytecode__array__no_increment_pc(f2ptr cause, f2ptr this, f2ptr length) {
  if (! raw__integer__is_type(cause, length)) {
    return f2larva__new(cause, 5235, nil);
  }
  f2ptr new_array = raw__array__new(cause, f2integer__i(length, cause));
  f2__optimize_fiber__iter__set(cause, this, new_array);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__array(f2ptr cause, f2ptr this, f2ptr length) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: array"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__array__no_increment_pc(cause, this, length);
}


// cons

f2ptr raw__optimize_fiber__call_bytecode__cons__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr new_cons = raw__cons__new(cause, nil, nil);
  f2__optimize_fiber__iter__set(cause, this, new_cons);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__cons(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: cons"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__cons__no_increment_pc(cause, this);
}


// consp

f2ptr raw__optimize_fiber__call_bytecode__consp__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr result = f2bool__new(raw__cons__is_type(cause, f2__optimize_fiber__value(cause, this)));
  f2__optimize_fiber__value__set(cause, this, result);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__consp(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: consp"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__consp__no_increment_pc(cause, this);
}


// car

f2ptr raw__optimize_fiber__call_bytecode__car__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr fiber__iter = f2__optimize_fiber__iter(cause, this);
  if (! raw__cons__is_type(cause, fiber__iter)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "fiber_iter_is_not_cons_in_bytecode_car"));
    return f2larva__new(cause, 531, f2__bug__new(cause, f2integer__new(cause, 531), bug_frame));
  }
  f2ptr fiber__value = f2cons__car(fiber__iter, cause);
  f2__optimize_fiber__value__set(cause, this, fiber__value);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__car(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: car"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__car__no_increment_pc(cause, this);
}


// cdr

f2ptr raw__optimize_fiber__call_bytecode__cdr__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr fiber__iter  = f2__optimize_fiber__iter(cause, this);
  if (! raw__cons__is_type(cause, fiber__iter)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "fiber_iter_is_not_cons_in_bytecode_cdr"));
    return f2larva__new(cause, 5311, f2__bug__new(cause, f2integer__new(cause, 5311), bug_frame));
  }
  f2ptr fiber__value = f2cons__cdr(fiber__iter, cause);
  f2__optimize_fiber__value__set(cause, this, fiber__value);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__cdr(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: cdr"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__cdr__no_increment_pc(cause, this);
}


// car-set

f2ptr raw__optimize_fiber__call_bytecode__car__set__no_increment_pc(f2ptr cause, f2ptr this) {
  f2__cons__car__set(cause, f2__optimize_fiber__iter(cause, this), f2__optimize_fiber__value(cause, this));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__car__set(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: car-set"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__car__set__no_increment_pc(cause, this);
}


// cdr-set

f2ptr raw__optimize_fiber__call_bytecode__cdr__set__no_increment_pc(f2ptr cause, f2ptr this) {
  f2__cons__cdr__set(cause, f2__optimize_fiber__iter(cause, this), f2__optimize_fiber__value(cause, this));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__cdr__set(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: cdr-set"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__cdr__set__no_increment_pc(cause, this);
}


// array_elt

f2ptr raw__optimize_fiber__call_bytecode__array_elt__no_increment_pc(f2ptr cause, f2ptr this, f2ptr array, f2ptr index) {
  if (! raw__array__is_type(cause, array)) {
    return f2larva__new(cause, 51555, nil);
  }
  if (! raw__integer__is_type(cause, array)) {
    return f2larva__new(cause, 51556, nil);
  }
  f2__optimize_fiber__value__set(cause, this, f2__array__elt(cause, array, index));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__array_elt(f2ptr cause, f2ptr this, f2ptr array, f2ptr index) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: array_elt"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__array_elt__no_increment_pc(cause, this, array, index);
}


// set

f2ptr raw__optimize_fiber__call_bytecode__set__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name, f2ptr exp) {
  if      (raw__eq(cause, register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, exp);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, exp);}
  else {
    return f2larva__new(cause, 5432661, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__set(f2ptr cause, f2ptr this, f2ptr register_name, f2ptr exp) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: set"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__set__no_increment_pc(cause, this, register_name, exp);
}


// swap

f2ptr raw__optimize_fiber__call_bytecode__swap__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name_0, f2ptr register_name_1) {
  f2ptr value_0 = nil;
  f2ptr value_1 = nil;
  if      (raw__eq(cause, register_name_0, new__symbol(cause, "value")))           {value_0 = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "iter")))            {value_0 = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "program_counter"))) {value_0 = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "args")))            {value_0 = f2__optimize_fiber__args(           cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "return_reg")))      {value_0 = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "env")))             {value_0 = f2__optimize_fiber__env(            cause, this);}
  else {
    return f2larva__new(cause, 5432662, nil);
  }
  if      (raw__eq(cause, register_name_1, new__symbol(cause, "value")))           {value_1 = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "iter")))            {value_1 = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "program_counter"))) {value_1 = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "args")))            {value_1 = f2__optimize_fiber__args(           cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "return_reg")))      {value_1 = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "env")))             {value_1 = f2__optimize_fiber__env(            cause, this);}
  else {
    return f2larva__new(cause, 5432663, nil);
  }
  if      (raw__eq(cause, register_name_0, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, value_1);}
  else if (raw__eq(cause, register_name_0, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, value_1);}
  else {
    return f2larva__new(cause, 5432664, nil);
  }
  if      (raw__eq(cause, register_name_1, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, value_0);}
  else if (raw__eq(cause, register_name_1, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, value_0);}
  else {
    return f2larva__new(cause, 5432665, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__swap(f2ptr cause, f2ptr this, f2ptr register_name_0, f2ptr register_name_1) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: swap"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__swap__no_increment_pc(cause, this, register_name_0, register_name_1);
}


// push

f2ptr raw__optimize_fiber__call_bytecode__push__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name) {
  if      (raw__eq(cause, register_name, new__symbol(cause, "value")))           {raw__optimize_fiber__stack__push_value(          cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "iter")))            {raw__optimize_fiber__stack__push_iter(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "program_counter"))) {raw__optimize_fiber__stack__push_program_counter(cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "args")))            {raw__optimize_fiber__stack__push_args(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "return_reg")))      {raw__optimize_fiber__stack__push_return_reg(     cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "env")))             {raw__optimize_fiber__stack__push_env(            cause, this);}
  else {
    return f2larva__new(cause, 5432369, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__push(f2ptr cause, f2ptr this, f2ptr register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: push"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, register_name);
}


// push_constant

f2ptr raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc(f2ptr cause, f2ptr this, f2ptr constant) {
  raw__optimize_fiber__stack__push_constant(cause, this, constant);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__push_constant(f2ptr cause, f2ptr this, f2ptr constant) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: push_constant"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc(cause, this, constant);
}


// pop

f2ptr raw__optimize_fiber__call_bytecode__pop__no_increment_pc(f2ptr cause, f2ptr this, f2ptr register_name) {
  if      (register_name == nil)                                                 {raw__optimize_fiber__stack__pop_nil(            cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "value")))           {raw__optimize_fiber__stack__pop_value(          cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "iter")))            {raw__optimize_fiber__stack__pop_iter(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "program_counter"))) {raw__optimize_fiber__stack__pop_program_counter(cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "args")))            {raw__optimize_fiber__stack__pop_args(           cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "return_reg")))      {raw__optimize_fiber__stack__pop_return_reg(     cause, this);}
  else if (raw__eq(cause, register_name, new__symbol(cause, "env")))             {raw__optimize_fiber__stack__pop_env(            cause, this);}
  else {
    return f2larva__new(cause, 5432369, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__pop(f2ptr cause, f2ptr this, f2ptr register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: pop"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, register_name);
}


// copy

f2ptr raw__optimize_fiber__call_bytecode__copy__no_increment_pc(f2ptr cause, f2ptr this, f2ptr from_register_name, f2ptr to_register_name) {
  f2ptr from_value = nil;
  if      (raw__eq(cause, from_register_name, new__symbol(cause, "value")))           {from_value = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "iter")))            {from_value = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "program_counter"))) {from_value = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "args")))            {from_value = f2__optimize_fiber__args(           cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "return_reg")))      {from_value = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, from_register_name, new__symbol(cause, "env")))             {from_value = f2__optimize_fiber__env(            cause, this);}
  else {
    return f2larva__new(cause, 5433462, nil);
  }
  if      (raw__eq(cause, to_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, from_value);}
  else if (raw__eq(cause, to_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, from_value);}
  else {
    return f2larva__new(cause, 5433564, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__copy(f2ptr cause, f2ptr this, f2ptr from_register_name, f2ptr to_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: copy"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, from_register_name, to_register_name);
}


f2ptr raw__environment__optimize_lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  // lookup special funks that we assume are not locally masked by the local environment.
  if (raw__eq(cause, type_name, new__symbol(cause, "funk_variable"))) {
    /*
    if (raw__eq(cause, var_name,  new__symbol(cause, "conslist")) ||
	raw__eq(cause, var_name,  new__symbol(cause, "funk-new"))) {
      f2ptr funk = f2__environment__lookup_type_var_value(cause, global_environment(), type_name, var_name);
      if (! raw__larva__is_type(cause, funk)) {
	return funk;
      }
    }
    */
  } else if (raw__eq(cause, type_name, new__symbol(cause, "variable"))) {
    if (raw__eq(cause, var_name,  new__symbol(cause, "t"))) {
      return new__symbol(cause, "t");
    }
  }
  boolean_t found_value = boolean__false;
  f2ptr     environment  = this;
  f2ptr     frame_lookup = nil;
  while (! found_value) {
    f2ptr environment__frame = f2__environment__frame(cause, environment);
    if (! raw__frame__is_type(cause, environment__frame)) {
      return f2larva__new(cause, 5423626, nil);
    }
    frame_lookup = raw__frame__lookup_type_var_value(cause, environment__frame, type_name, var_name, new__symbol(cause, "<optimize-lookup-undefined>"));
    if (raw__larva__is_type(cause, frame_lookup)) {
      return frame_lookup;
    }
    if (! raw__eq(cause, frame_lookup, new__symbol(cause, "<optimize-lookup-undefined>"))) {
      found_value = boolean__true;
    } else {
      environment = f2__environment__parent_env(cause, environment);
      if ((environment == nil) ||
	  raw__optimize_data__is_type(cause, environment)) {
	return f2larva__new(cause, 2301, nil);
      }
    }
  }
  if (raw__eq(cause, frame_lookup, new__symbol(cause, "<optimize-lookup-undefined>"))) {
    return f2larva__new(cause, 2302, nil);
  }
  return frame_lookup;
}


// lookup

f2ptr raw__optimize_fiber__call_bytecode__lookup__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  f2ptr env = f2__optimize_fiber__env(cause, this);
  if (! raw__environment__is_type(cause, env)) {
    return f2larva__new(cause, 523542, nil);
  }
  f2ptr value = raw__environment__optimize_lookup_type_var_value(cause, env, type_name, var_name);
  if (raw__larva__is_type(cause, value)) {
    value = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), f2__gensym(cause, f2__stringlist__concat(cause, f2list4__new(cause,
																			  new__string(cause, "lookup-"),
																			  f2__exp__as__string(cause, type_name),
																			  new__string(cause, "-"),
																			  f2__exp__as__string(cause, var_name)))),
				   new__symbol(cause, "lookup"), f2list2__new(cause, type_name, var_name));
  }
  f2__optimize_fiber__value__set(cause, this, value);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__lookup(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: lookup"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__lookup__no_increment_pc(cause, this, type_name, var_name);
}


// define

f2ptr raw__optimize_fiber__call_bytecode__define__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  f2ptr env   = f2__optimize_fiber__env(  cause, this);
  f2ptr value = f2__optimize_fiber__value(cause, this);
  f2__optimize_fiber__value__set(cause, this, f2__environment__define_type_var_value(cause, env, type_name, var_name, value));
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__define(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: define"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__define__no_increment_pc(cause, this, type_name, var_name);
}


f2ptr raw__environment__optimize_mutate_type_var_value(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name, f2ptr value) {
  boolean_t found_value = boolean__false;
  f2ptr     environment  = this;
  f2ptr     frame_lookup = nil;
  while (! found_value) {
    f2ptr environment__frame = f2__environment__frame(cause, environment);
    if (! raw__frame__is_type(cause, environment__frame)) {
      return f2larva__new(cause, 5423626, nil);
    }
    frame_lookup = raw__frame__lookup_type_var_value(cause, environment__frame, type_name, var_name, new__symbol(cause, "<optimize-lookup-undefined>"));
    if (raw__larva__is_type(cause, frame_lookup)) {
      return frame_lookup;
    }
    if (! raw__eq(cause, frame_lookup, new__symbol(cause, "<optimize-lookup-undefined>"))) {
      raw__frame__add_type_var_value(cause, environment__frame, type_name, var_name, value);
      frame_lookup = value;
      found_value = boolean__true;
    } else {
      environment = f2__environment__parent_env(cause, environment);
      if ((environment == nil) ||
	  raw__optimize_data__is_type(cause, environment)) {
	return f2larva__new(cause, 2301, nil);
      }
    }
  }
  if (raw__eq(cause, frame_lookup, new__symbol(cause, "<optimize-lookup-undefined>"))) {
    return f2larva__new(cause, 2302, nil);
  }
  return frame_lookup;
}

// mutate-type_var

f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  f2ptr env = f2__optimize_fiber__env(cause, this);
  if (! raw__environment__is_type(cause, env)) {
    return f2larva__new(cause, 523542, nil);
  }
  f2ptr value__data             = f2__optimize_fiber__value(cause, this);
  f2ptr current_var_value__data = raw__environment__optimize_lookup_type_var_value(cause, env, type_name, var_name);
  if (raw__larva__is_type(cause, current_var_value__data)) {
    f2ptr data_side_effect = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), nil, new__symbol(cause, "mutate-type_var"), f2list3__new(cause, type_name, var_name, value__data));
    raw__optimize_fiber__add_side_effect(cause, this, data_side_effect);
  } else {
    raw__environment__optimize_mutate_type_var_value(cause, env, type_name, var_name, value__data);
  }
  f2__optimize_fiber__value__set(cause, this, nil);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__mutate__type_var(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: mutate-type_var"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__mutate__type_var__no_increment_pc(cause, this, type_name, var_name);
}


// globalize-type_var

f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var__no_increment_pc(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
  f2ptr value__data      = f2__optimize_fiber__value(cause, this);
  f2ptr data_side_effect = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), nil, new__symbol(cause, "globalize-type_var"), f2list3__new(cause, type_name, var_name, value__data));
  raw__optimize_fiber__add_side_effect(cause, this, data_side_effect);
  f2__optimize_fiber__value__set(cause, this, nil);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__globalize__type_var(f2ptr cause, f2ptr this, f2ptr type_name, f2ptr var_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: globalize-type_var"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__globalize__type_var__no_increment_pc(cause, this, type_name, var_name);
}


// jump

f2ptr raw__optimize_fiber__call_bytecode__jump__no_increment_pc(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  f2__optimize_fiber__program_counter__set(cause, this, new_program_counter);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__jump(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: jump"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__jump__no_increment_pc(cause, this, new_program_counter);
}


// if-jump

f2ptr raw__optimize_fiber__call_bytecode__if__jump__no_increment_pc(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  f2ptr optimize_context =  f2__optimize_fiber__optimize_context(cause, this);
  f2ptr value__data      =  f2__optimize_fiber__value(           cause, this);
  if (raw__optimize_data__is_type(cause, value__data)) {
    f2ptr true_branch_fiber  = raw__optimize_fiber__new_copy(cause, this);
    f2ptr false_branch_fiber = raw__optimize_fiber__new_copy(cause, this);
    raw__optimize_context__active_fiber_branched(cause, optimize_context, this);
    raw__optimize_context__add_active_fiber(     cause, optimize_context, true_branch_fiber);
    raw__optimize_context__add_active_fiber(     cause, optimize_context, false_branch_fiber);
    f2__optimize_fiber__branch_condition_data__set(     cause, this, value__data);
    f2__optimize_fiber__true_child_branched_fiber__set( cause, this, true_branch_fiber);
    f2__optimize_fiber__false_child_branched_fiber__set(cause, this, false_branch_fiber);
    // assuming value is true:
    f2__optimize_fiber__program_counter__set(cause, true_branch_fiber, new_program_counter);
    // assuming value is false:
    f2__optimize_fiber__value__set(cause, false_branch_fiber, nil);
    //   do nothing.
  } else {
    // we know the value (it is not a hypothetical data value)
    if (value__data != nil) {
      f2__optimize_fiber__program_counter__set(cause, this, new_program_counter);
    } else {
      // do nothing
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__if__jump(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: if-jump"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__if__jump__no_increment_pc(cause, this, new_program_counter);
}


// else-jump

f2ptr raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
  f2ptr optimize_context          =  f2__optimize_fiber__optimize_context(cause, this);
  f2ptr value__data               =  f2__optimize_fiber__value(           cause, this);
  if (raw__optimize_data__is_type(cause, value__data)) {
    f2ptr true_branch_fiber  = raw__optimize_fiber__new_copy(cause, this);
    f2ptr false_branch_fiber = raw__optimize_fiber__new_copy(cause, this);
    raw__optimize_context__active_fiber_branched(cause, optimize_context, this);
    raw__optimize_context__add_active_fiber(     cause, optimize_context, true_branch_fiber);
    raw__optimize_context__add_active_fiber(     cause, optimize_context, false_branch_fiber);
    f2__optimize_fiber__branch_condition_data__set(     cause, this, value__data);
    f2__optimize_fiber__true_child_branched_fiber__set( cause, this, true_branch_fiber);
    f2__optimize_fiber__false_child_branched_fiber__set(cause, this, false_branch_fiber);
    // assuming value is true:
    //   do nothing.
    // assuming value is false:
    f2__optimize_fiber__value__set(          cause, false_branch_fiber, nil);
    f2__optimize_fiber__program_counter__set(cause, false_branch_fiber, new_program_counter);
  } else {
    // we know the value (it is not a hypothetical data value)
    if (value__data != nil) {
      // do nothing
    } else {
      f2__optimize_fiber__program_counter__set(cause, this, new_program_counter);
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__else__jump(f2ptr cause, f2ptr this, f2ptr new_program_counter) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: else-jump"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc(cause, this, new_program_counter);
}


// nop

f2ptr raw__optimize_fiber__call_bytecode__nop__no_increment_pc(f2ptr cause, f2ptr this) {
  // nothing to do.
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__nop(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: nop"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__nop__no_increment_pc(cause, this);
}


// debug

f2ptr raw__optimize_fiber__call_bytecode__debug__no_increment_pc(f2ptr cause, f2ptr this, f2ptr debug_value) {
  // nothing to do.
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__debug(f2ptr cause, f2ptr this, f2ptr debug_value) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: debug"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__debug__no_increment_pc(cause, this, debug_value);
}


// tracer

f2ptr raw__optimize_fiber__call_bytecode__tracer__no_increment_pc(f2ptr cause, f2ptr this, f2ptr name, f2ptr args) {
  // nothing to do.
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__tracer(f2ptr cause, f2ptr this, f2ptr name, f2ptr args) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: tracer"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__tracer__no_increment_pc(cause, this, name, args);
}


// endfunk

f2ptr raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc(f2ptr cause, f2ptr this, f2ptr funk) {
  // nothing to do.
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__endfunk(f2ptr cause, f2ptr this, f2ptr funk) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: endfunk"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc(cause, this, funk);
}


// compile

f2ptr raw__optimize_fiber__call_bytecode__compile__no_increment_pc(f2ptr cause, f2ptr this, f2ptr protect_environment) {
  printf("\noptimize warning: compile not yet implemented."); fflush(stdout);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__compile(f2ptr cause, f2ptr this, f2ptr protect_environment) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: compile"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__compile__no_increment_pc(cause, this, protect_environment);
}


// yield

f2ptr raw__optimize_fiber__call_bytecode__yield__no_increment_pc(f2ptr cause, f2ptr this) {
  // nothing to do.
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__yield(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: yield"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__yield__no_increment_pc(cause, this);
}


// newenv

f2ptr raw__optimize_fiber__call_bytecode__newenv__no_increment_pc(f2ptr cause, f2ptr this) {
  f2ptr parent_env = f2__optimize_fiber__env(cause, this);
  f2ptr new_env    = f2environment__new(cause,
					f2__frame__new(cause, nil),
					parent_env,
					new__symbol(cause, "push-env"));
  f2__optimize_fiber__env__set(cause, this, new_env);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__newenv(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: newenv"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__newenv__no_increment_pc(cause, this);
}


// machine_code

f2ptr raw__optimize_fiber__call_bytecode__machine_code__no_increment_pc(f2ptr cause, f2ptr this, f2ptr chunk) {
  printf("\noptimize warning: machine_code not yet implemented."); fflush(stdout);
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__machine_code(f2ptr cause, f2ptr this, f2ptr chunk) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: machine_code"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__machine_code__no_increment_pc(cause, this, chunk);
}


// eq

f2ptr raw__optimize_fiber__call_bytecode__eq__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__eq(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "eq_result"), new__symbol(cause, "eq"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__eq(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: eq"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__eq__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// not

f2ptr raw__optimize_fiber__call_bytecode__not__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
  f2ptr x__data = nil;
  if      (raw__eq(cause, x_register_name, new__symbol(cause, "return_reg")))      {x__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "value")))           {x__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "iter")))            {x__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "program_counter"))) {x__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "env")))             {x__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "args")))            {x__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr result__data = nil;
  if (! raw__optimize_data__is_type(cause, x__data)) {
    result__data = f2__not(cause, x__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "not_result"), new__symbol(cause, "not"), f2list1__new(cause, x__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543619, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__not(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: not"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__not__no_increment_pc(cause, this, result_register_name, x_register_name);
}


// and

f2ptr raw__optimize_fiber__call_bytecode__and__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__and(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "and_result"), new__symbol(cause, "and"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__and(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: and"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__and__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// or

f2ptr raw__optimize_fiber__call_bytecode__or__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__or(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "or_result"), new__symbol(cause, "or"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__or(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: or"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__or__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// add

f2ptr raw__optimize_fiber__call_bytecode__add__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__add(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "add_result"), new__symbol(cause, "add"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__add(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: add"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__add__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// negative

f2ptr raw__optimize_fiber__call_bytecode__negative__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
  f2ptr x__data = nil;
  if      (raw__eq(cause, x_register_name, new__symbol(cause, "return_reg")))      {x__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "value")))           {x__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "iter")))            {x__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "program_counter"))) {x__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "env")))             {x__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "args")))            {x__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr result__data = nil;
  if (! raw__optimize_data__is_type(cause, x__data)) {
    result__data = f2__negative(cause, x__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "negative_result"), new__symbol(cause, "negative"), f2list1__new(cause, x__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543619, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__negative(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: negative"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__negative__no_increment_pc(cause, this, result_register_name, x_register_name);
}


// subtract

f2ptr raw__optimize_fiber__call_bytecode__subtract__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__subtract(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "subtract_result"), new__symbol(cause, "subtract"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__subtract(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: subtract"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__subtract__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// multiply

f2ptr raw__optimize_fiber__call_bytecode__multiply__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__multiply(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "multiply_result"), new__symbol(cause, "multiply"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__multiply(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: multiply"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__multiply__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// inverse

f2ptr raw__optimize_fiber__call_bytecode__inverse__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
  f2ptr x__data = nil;
  if      (raw__eq(cause, x_register_name, new__symbol(cause, "return_reg")))      {x__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "value")))           {x__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "iter")))            {x__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "program_counter"))) {x__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "env")))             {x__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "args")))            {x__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr result__data = nil;
  if (! raw__optimize_data__is_type(cause, x__data)) {
    result__data = f2__inverse(cause, x__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "inverse_result"), new__symbol(cause, "inverse"), f2list1__new(cause, x__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543619, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__inverse(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: inverse"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__inverse__no_increment_pc(cause, this, result_register_name, x_register_name);
}


// divide

f2ptr raw__optimize_fiber__call_bytecode__divide__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__divide(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "divide_result"), new__symbol(cause, "divide"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__divide(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: divide"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__divide__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// modulo

f2ptr raw__optimize_fiber__call_bytecode__modulo__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__modulo(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "modulo_result"), new__symbol(cause, "modulo"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__modulo(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: modulo"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__modulo__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// increment

f2ptr raw__optimize_fiber__call_bytecode__increment__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
  f2ptr x__data = nil;
  if      (raw__eq(cause, x_register_name, new__symbol(cause, "return_reg")))      {x__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "value")))           {x__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "iter")))            {x__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "program_counter"))) {x__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "env")))             {x__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "args")))            {x__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr result__data = nil;
  if (! raw__optimize_data__is_type(cause, x__data)) {
    result__data = f2__increment(cause, x__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "increment_result"), new__symbol(cause, "increment"), f2list1__new(cause, x__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543619, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__increment(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: increment"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__increment__no_increment_pc(cause, this, result_register_name, x_register_name);
}


// decrement

f2ptr raw__optimize_fiber__call_bytecode__decrement__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
  f2ptr x__data = nil;
  if      (raw__eq(cause, x_register_name, new__symbol(cause, "return_reg")))      {x__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "value")))           {x__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "iter")))            {x__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "program_counter"))) {x__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "env")))             {x__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x_register_name, new__symbol(cause, "args")))            {x__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr result__data = nil;
  if (! raw__optimize_data__is_type(cause, x__data)) {
    result__data = f2__decrement(cause, x__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "decrement_result"), new__symbol(cause, "decrement"), f2list1__new(cause, x__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543619, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__decrement(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: decrement"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__decrement__no_increment_pc(cause, this, result_register_name, x_register_name);
}


// numerically_equals

f2ptr raw__optimize_fiber__call_bytecode__numerically_equals__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__numerically_equals(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "numerically_equals_result"), new__symbol(cause, "numerically_equals"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__numerically_equals(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: numerically_equals"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__numerically_equals__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// less_than

f2ptr raw__optimize_fiber__call_bytecode__less_than__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__less_than(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "less_than_result"), new__symbol(cause, "less_than"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__less_than(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: less_than"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__less_than__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// greater_than

f2ptr raw__optimize_fiber__call_bytecode__greater_than__no_increment_pc(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
  f2ptr x0__data = nil;
  if      (raw__eq(cause, x0_register_name, new__symbol(cause, "return_reg")))      {x0__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "value")))           {x0__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "iter")))            {x0__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "program_counter"))) {x0__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "env")))             {x0__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x0_register_name, new__symbol(cause, "args")))            {x0__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543616, nil);
  }
  f2ptr x1__data = nil;
  if      (raw__eq(cause, x1_register_name, new__symbol(cause, "return_reg")))      {x1__data = f2__optimize_fiber__return_reg(     cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "value")))           {x1__data = f2__optimize_fiber__value(          cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "iter")))            {x1__data = f2__optimize_fiber__iter(           cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "program_counter"))) {x1__data = f2__optimize_fiber__program_counter(cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "env")))             {x1__data = f2__optimize_fiber__env(            cause, this);}
  else if (raw__eq(cause, x1_register_name, new__symbol(cause, "args")))            {x1__data = f2__optimize_fiber__args(           cause, this);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  f2ptr result__data = nil;
  if ((! raw__optimize_data__is_type(cause, x0__data)) &&
      (! raw__optimize_data__is_type(cause, x1__data))) {
    result__data = f2__greater_than(cause, x0__data, x1__data);
  } else {
    result__data = f2__optimize_data__new(cause, f2__optimize_fiber__optimize_context(cause, this), gensym(cause, "greater_than_result"), new__symbol(cause, "greater_than"), f2list2__new(cause, x0__data, x1__data));
  }
  if      (raw__eq(cause, result_register_name, new__symbol(cause, "return_reg")))      {f2__optimize_fiber__return_reg__set(     cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "value")))           {f2__optimize_fiber__value__set(          cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "iter")))            {f2__optimize_fiber__iter__set(           cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "program_counter"))) {f2__optimize_fiber__program_counter__set(cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "env")))             {f2__optimize_fiber__env__set(            cause, this, result__data);}
  else if (raw__eq(cause, result_register_name, new__symbol(cause, "args")))            {f2__optimize_fiber__args__set(           cause, this, result__data);}
  else {
    return f2larva__new(cause, 543617, nil);
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__greater_than(f2ptr cause, f2ptr this, f2ptr result_register_name, f2ptr x0_register_name, f2ptr x1_register_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: greater_than"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__greater_than__no_increment_pc(cause, this, result_register_name, x0_register_name, x1_register_name);
}


// block_push

f2ptr raw__optimize_fiber__call_bytecode__block_push__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "return_reg"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "env"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push_constant__no_increment_pc(cause, this, __funk2.compile.debug_funk_call__symbol);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_push(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_push"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_push__no_increment_pc(cause, this);
}


// block_enter

f2ptr raw__optimize_fiber__call_bytecode__block_enter__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__block_push__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__newenv__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_enter(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_enter"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_enter__no_increment_pc(cause, this);
}


// block_define_rest_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "iter"), new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__define__no_increment_pc(cause, this, __funk2.primobject__frame.variable__symbol, variable_name);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_define_rest_argument(f2ptr cause, f2ptr this, f2ptr variable_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_define_rest_argument"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_define_rest_argument__no_increment_pc(cause, this, variable_name);
}


// block_define_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "iter"), new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc(cause, this, __funk2.compile.wrong_argument_number__bcs);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__car__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__define__no_increment_pc(cause, this, __funk2.primobject__frame.variable__symbol, variable_name);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__cdr__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "value"), new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_define_argument(f2ptr cause, f2ptr this, f2ptr variable_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_define_argument"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_define_argument__no_increment_pc(cause, this, variable_name);
}


// block_define_last_argument

f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument__no_increment_pc(f2ptr cause, f2ptr this, f2ptr variable_name) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "iter"), new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__else__jump__no_increment_pc(cause, this, __funk2.compile.wrong_argument_number__bcs);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__car__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__define__no_increment_pc(cause, this, __funk2.primobject__frame.variable__symbol, variable_name);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_define_last_argument(f2ptr cause, f2ptr this, f2ptr variable_name) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_define_last_argument"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_define_last_argument__no_increment_pc(cause, this, variable_name);
}


// block_pop

f2ptr raw__optimize_fiber__call_bytecode__block_pop__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, new__symbol(cause, "env"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, new__symbol(cause, "return_reg"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_pop(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_pop"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_pop__no_increment_pc(cause, this);
}


// block_exit_and_pop

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop__no_increment_pc(f2ptr cause, f2ptr this, f2ptr funk) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc(  cause, this, funk);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__block_pop__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(     cause, this, new__symbol(cause, "return_reg"), new__symbol(cause, "program_counter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_pop(f2ptr cause, f2ptr this, f2ptr funk) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_exit_and_pop"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_exit_and_pop__no_increment_pc(cause, this, funk);
}


// block_exit_and_no_pop

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop__no_increment_pc(f2ptr cause, f2ptr this, f2ptr funk) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__endfunk__no_increment_pc(cause, this, funk);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "return_reg"), new__symbol(cause, "program_counter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_exit_and_no_pop(f2ptr cause, f2ptr this, f2ptr funk) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_exit_and_no_pop"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_exit_and_no_pop__no_increment_pc(cause, this, funk);
}


// block_eval_args_begin

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__cons__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "iter"), new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_begin(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_eval_args_begin"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_eval_args_begin__no_increment_pc(cause, this);
}


// block_eval_args_next

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__car__set__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__copy__no_increment_pc(cause, this, new__symbol(cause, "iter"), new__symbol(cause, "value"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__cons__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__swap__no_increment_pc(cause, this, new__symbol(cause, "value"), new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__cdr__set__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__swap__no_increment_pc(cause, this, new__symbol(cause, "value"), new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__push__no_increment_pc(cause, this, new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_next(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_eval_args_next"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_eval_args_next__no_increment_pc(cause, this);
}


// block_eval_args_end

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end__no_increment_pc(f2ptr cause, f2ptr this) {
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, new__symbol(cause, "args"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__pop__no_increment_pc(cause, this, new__symbol(cause, "iter"));
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr result = raw__optimize_fiber__call_bytecode__car__set__no_increment_pc(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return nil;
}

f2ptr raw__optimize_fiber__call_bytecode__block_eval_args_end(f2ptr cause, f2ptr this) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize: block_eval_args_end"); fflush(stdout);
#endif
  {
    f2ptr result = raw__optimize_fiber__increment_program_counter(cause, this);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  return raw__optimize_fiber__call_bytecode__block_eval_args_end__no_increment_pc(cause, this);
}

#define optimize_too_many_loops__larva_type 5123456

f2ptr raw__optimize_too_many_loops_larva__new(f2ptr cause, f2ptr optimize_bytecode) {
  return f2larva__new(cause, optimize_too_many_loops__larva_type, f2__bug__new(cause, f2integer__new(cause, optimize_too_many_loops__larva_type), f2__frame__new(cause, f2list2__new(cause, new__symbol(cause, "optimize_bytecode"), optimize_bytecode))));
}

boolean_t raw__optimize_too_many_loops_larva__is_type(f2ptr cause, f2ptr object) {
  if (! raw__larva__is_type(cause, object)) {
    return boolean__false;
  }
  if (raw__larva__larva_type(cause, object) != optimize_too_many_loops__larva_type) {
    return boolean__false;
  }
  return boolean__true;
}

f2ptr raw__optimize_too_many_loops_larva__optimize_bytecode(f2ptr cause, f2ptr this) {
  f2ptr bug   = raw__larva__bug(cause, this);
  f2ptr frame = f2__bug__frame(cause, bug);
  return f2__frame__lookup_var_value(cause, frame, new__symbol(cause, "optimize_bytecode"), nil);
}


f2ptr raw__optimize_fiber__call_next_bytecode(f2ptr cause, f2ptr this) {
  f2ptr program_counter = f2__optimize_fiber__program_counter(cause, this);
  if (! raw__cons__is_type(cause, program_counter)) {
    return f2larva__new(cause, 512431, nil);
  }
  f2ptr bytecode = f2__cons__car(cause, program_counter);
  {
    f2ptr optimize_context      = f2__optimize_fiber__optimize_context(cause, this);
    f2ptr maximum_loop_count    = f2__optimize_context__maximum_loop_count(cause, optimize_context);
    s64   maximum_loop_count__i = f2integer__i(maximum_loop_count, cause);
    f2ptr optimize_bytecode     = raw__optimize_context__get_optimize_bytecode_for_sequence(cause, optimize_context, program_counter);
    f2ptr execution_count       = f2__optimize_bytecode__execution_count(cause, optimize_bytecode);
    s64   execution_count__i    = f2integer__i(execution_count, cause);
    execution_count__i            ++;
    execution_count             = f2integer__new(cause, execution_count__i);
    f2__optimize_bytecode__execution_count__set(cause, optimize_bytecode, execution_count);
    if (execution_count__i > maximum_loop_count__i) {
      return raw__optimize_too_many_loops_larva__new(cause, optimize_bytecode);
    }
  }
  {
    f2ptr bytecode__command = f2__bytecode__command(cause, bytecode);
    if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump-funk"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__jump__funk(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "funk"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__funk(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array"))) {
      f2ptr length = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__array(cause, this, length);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cons"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__cons(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "consp"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__consp(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__car(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__cdr(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "car-set"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__car__set(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "cdr-set"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__cdr__set(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "array_elt"))) {
      f2ptr array  = f2__bytecode__arg0(cause, bytecode);
      f2ptr index  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__array_elt(cause, this, array, index);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "set"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr exp           = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__set(cause, this, register_name, exp);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "swap"))) {
      f2ptr register_name_0 = f2__bytecode__arg0(cause, bytecode);
      f2ptr register_name_1 = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__swap(cause, this, register_name_0, register_name_1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__push(cause, this, register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "push_constant"))) {
      f2ptr constant = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__push_constant(cause, this, constant);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "pop"))) {
      f2ptr register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__pop(cause, this, register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "copy"))) {
      f2ptr register_name_0 = f2__bytecode__arg0(cause, bytecode);
      f2ptr register_name_1 = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__copy(cause, this, register_name_0, register_name_1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "lookup"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__lookup(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "define"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__define(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "mutate-type_var"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__mutate__type_var(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "globalize-type_var"))) {
      f2ptr type_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr var_name  = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__globalize__type_var(cause, this, type_name, var_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "jump"))) {
      f2ptr new_program_counter = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__jump(cause, this, new_program_counter);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "if-jump"))) {
      f2ptr new_program_counter = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__if__jump(cause, this, new_program_counter);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "else-jump"))) {
      f2ptr new_program_counter = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__else__jump(cause, this, new_program_counter);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "nop"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__nop(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "debug"))) {
      f2ptr debug_value = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__debug(cause, this, debug_value);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "tracer"))) {
      f2ptr name = f2__bytecode__arg0(cause, bytecode);
      f2ptr args = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__tracer(cause, this, name, args);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "endfunk"))) {
      f2ptr funk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__endfunk(cause, this, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "compile"))) {
      f2ptr protect_environment = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__compile(cause, this, protect_environment);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "yield"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__yield(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "newenv"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__newenv(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "machine_code"))) {
      f2ptr chunk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__machine_code(cause, this, chunk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "eq"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__eq(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "not"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__not(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "and"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__and(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "or"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__or(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "add"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__add(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "negative"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__negative(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "subtract"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__subtract(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "multiply"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__multiply(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "inverse"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__inverse(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "divide"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__divide(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "modulo"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__modulo(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "increment"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__increment(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "decrement"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x_register_name      = f2__bytecode__arg1(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__decrement(cause, this, result_register_name, x_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "numerically_equals"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__numerically_equals(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "less_than"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__less_than(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "greater_than"))) {
      f2ptr result_register_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr x0_register_name     = f2__bytecode__arg1(cause, bytecode);
      f2ptr x1_register_name     = f2__bytecode__arg2(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__greater_than(cause, this, result_register_name, x0_register_name, x1_register_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_push"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_push(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_enter"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_enter(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_rest_argument"))) {
      f2ptr variable_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_define_rest_argument(cause, this, variable_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_argument"))) {
      f2ptr variable_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_define_argument(cause, this, variable_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_define_last_argument"))) {
      f2ptr variable_name = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_define_last_argument(cause, this, variable_name);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_pop"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_pop(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_pop"))) {
      f2ptr funk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_exit_and_pop(cause, this, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_exit_and_no_pop"))) {
      f2ptr funk = f2__bytecode__arg0(cause, bytecode);
      f2ptr result = raw__optimize_fiber__call_bytecode__block_exit_and_no_pop(cause, this, funk);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_begin"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_begin(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_next"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_next(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else if (raw__eq(cause, bytecode__command, new__symbol(cause, "block_eval_args_end"))) {
      f2ptr result = raw__optimize_fiber__call_bytecode__block_eval_args_end(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else {
      printf("\nbytecode UNRECOGNIZED: cannot optimize funk."); fflush(stdout);
      return f2larva__new(cause, 5123, nil);
    }
  }
  return nil;
}


f2ptr raw__optimize_fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list26__new(cause,
						new__symbol(cause, "print_object_type"),          new__symbol(cause, "optimize_fiber"),
						new__symbol(cause, "parent_branched_fiber"),      f2__optimize_fiber__parent_branched_fiber(     cause, this),
						new__symbol(cause, "branch_condition_data"),      f2__optimize_fiber__branch_condition_data(     cause, this),
						new__symbol(cause, "true_child_branched_fiber"),  f2__optimize_fiber__true_child_branched_fiber( cause, this),
						new__symbol(cause, "false_child_branched_fiber"), f2__optimize_fiber__false_child_branched_fiber(cause, this),
						new__symbol(cause, "data_side_effects"),          f2__optimize_fiber__data_side_effects(         cause, this),
						new__symbol(cause, "stack"),                      f2__optimize_fiber__stack(                     cause, this),
						new__symbol(cause, "value"),                      f2__optimize_fiber__value(                     cause, this),
						new__symbol(cause, "iter"),                       f2__optimize_fiber__iter(                      cause, this),
						new__symbol(cause, "program_counter"),            f2__optimize_fiber__program_counter(           cause, this),
						new__symbol(cause, "args"),                       f2__optimize_fiber__args(                      cause, this),
						new__symbol(cause, "return_reg"),                 f2__optimize_fiber__return_reg(                cause, this),
						new__symbol(cause, "env"),                        f2__optimize_fiber__env(                       cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_fiber__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_fiber,       this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_fiber__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_fiber__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this optimize_fiber to the given terminal.",
	    return f2__optimize_fiber__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_fiber__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_fiber__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__funk);}
  return this;
}



// optimize_context

def_primobject_9_slot(optimize_context,
		      maximum_loop_count,
		      optimize_bytecode_sequence_hash,
		      initial_fiber,
		      active_fiber_set,
		      branched_fiber_set,
		      finished_fiber_set,
		      evaluated_data_set,
		      defined_data_set,
		      optimized_bytecodes);

f2ptr f2__optimize_context__new(f2ptr cause, f2ptr maximum_loop_count) {
  assert_argument_type(integer, maximum_loop_count);
  f2ptr optimize_bytecode_sequence_hash = f2__ptypehash__new(cause);
  f2ptr initial_fiber          = nil;
  f2ptr active_fiber_set       = f2__set__new(cause, nil);
  f2ptr branched_fiber_set     = f2__set__new(cause, nil);
  f2ptr finished_fiber_set     = f2__set__new(cause, nil);
  f2ptr evaluated_data_set     = f2__set__new(cause, nil);
  f2ptr defined_data_set       = f2__set__new(cause, nil);
  f2ptr optimized_bytecodes    = nil;
  f2ptr this = f2optimize_context__new(cause,
				       maximum_loop_count,
				       optimize_bytecode_sequence_hash,
				       initial_fiber,
				       active_fiber_set,
				       branched_fiber_set,
				       finished_fiber_set,
				       evaluated_data_set,
				       defined_data_set,
				       optimized_bytecodes);
  initial_fiber = f2__optimize_fiber__new(cause, this);
  f2__optimize_context__initial_fiber__set(cause, this, initial_fiber);
  raw__optimize_context__add_active_fiber(cause, this, initial_fiber);
  return this;
}

f2ptr raw__optimize_context__new(f2ptr cause, s64 maximum_loop_count) {
  return f2__optimize_context__new(cause, f2integer__new(cause, maximum_loop_count));
}

def_pcfunk1(optimize_context__new, maximum_loop_count,
	    "",
	    return f2__optimize_context__new(this_cause, maximum_loop_count));


void raw__optimize_context__add_active_fiber(f2ptr cause, f2ptr this, f2ptr active_fiber) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize_context: adding active fiber."); fflush(stdout);
#endif
  f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
  raw__set__add(cause, active_fiber_set, active_fiber);
}

f2ptr raw__optimize_context__active_fiber_finished(f2ptr cause, f2ptr this, f2ptr active_fiber) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize_context: active fiber finished."); fflush(stdout);
#endif
  {
    f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
    if (! raw__set__remove(cause, active_fiber_set, active_fiber)) {
      return f2larva__new(cause, 567264, nil);
    }
  }
  f2ptr finished_fiber = active_fiber;
  {
    f2ptr finished_fiber_set = f2__optimize_context__finished_fiber_set(cause, this);
    raw__set__add(cause, finished_fiber_set, finished_fiber);
  }
  return nil;
}

f2ptr raw__optimize_context__active_fiber_branched(f2ptr cause, f2ptr this, f2ptr active_fiber) {
#ifdef F2__OPTIMIZE__DEBUG_PRINTF
  printf("\noptimize_context: active fiber branched."); fflush(stdout);
#endif
  {
    f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
    if (! raw__set__remove(cause, active_fiber_set, active_fiber)) {
      return f2larva__new(cause, 567264, nil);
    }
  }
  f2ptr branched_fiber = active_fiber;
  {
    f2ptr branched_fiber_set = f2__optimize_context__branched_fiber_set(cause, this);
    raw__set__add(cause, branched_fiber_set, branched_fiber);
  }
  return nil;
}


f2ptr raw__optimize_context__get_optimize_bytecode_for_sequence(f2ptr cause, f2ptr this, f2ptr bytecode_sequence) {
  f2ptr optimize_bytecode_sequence_hash = f2__optimize_context__optimize_bytecode_sequence_hash(cause, this);
  f2ptr optimize_bytecode               = raw__ptypehash__lookup(cause, optimize_bytecode_sequence_hash, bytecode_sequence);
  if (optimize_bytecode == nil) {
    optimize_bytecode = f2__optimize_bytecode__new(cause, this, bytecode_sequence);
    raw__ptypehash__add(cause, optimize_bytecode_sequence_hash, bytecode_sequence, optimize_bytecode);
  }
  return optimize_bytecode;
}


f2ptr raw__optimize_context__execute_one_bytecode(f2ptr cause, f2ptr this) {
  f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
  if (raw__set__is_empty(cause, active_fiber_set)) {
    return f2larva__new(cause, 52464, nil);
  }
  f2ptr active_fiber = raw__set__an_arbitrary_element(cause, active_fiber_set);
  {
    f2ptr result = raw__optimize_fiber__call_next_bytecode(cause, active_fiber);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
  {
    f2ptr program_counter = f2__optimize_fiber__program_counter(cause, active_fiber);
    if (! raw__cons__is_type(cause, program_counter)) {
      f2ptr result = raw__optimize_context__active_fiber_finished(cause, this, active_fiber);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}


f2ptr raw__optimize_context__complete_simulation(f2ptr cause, f2ptr this) {
  f2ptr active_fiber_set = f2__optimize_context__active_fiber_set(cause, this);
  while (! raw__set__is_empty(cause, active_fiber_set)) {
    {
      f2ptr result = raw__optimize_context__execute_one_bytecode(cause, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return nil;
}


f2ptr raw__optimize_context__compile_fiber_branch_or_return_value(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  f2ptr branch_condition_data = f2__optimize_fiber__branch_condition_data(cause, fiber);
  if (branch_condition_data != nil) {
    {
      f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, branch_condition_data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    {
      f2ptr new_bcs = f2__compile__lookup_var(cause, f2__optimize_data__name(cause, branch_condition_data));
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
  } else {
    f2ptr value__data = f2__optimize_fiber__value(cause, fiber);
    if (raw__optimize_data__is_type(cause, value__data)) {
      boolean_t is_last_value_to_compute = boolean__true;
      {
	f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_value(cause, value__data, is_last_value_to_compute);
	if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
      }
    } else {
      f2ptr new_bcs = f2__compile__set(cause, new__symbol(cause, "value"), value__data);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
  }
  return full_bcs;
}

f2ptr raw__optimize_context__compile_fiber_side_effects(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr full_bcs           = nil;
  f2ptr iter_bcs           = nil;
  f2ptr evaluated_data_set = f2__optimize_context__evaluated_data_set(cause, this);
  {
    f2ptr data_side_effects = f2__optimize_fiber__data_side_effects(cause, fiber);
    {
      f2ptr iter = data_side_effects;
      while (iter != nil) {
	f2ptr data = f2__cons__car(cause, iter);
	if (! raw__set__contains(cause, evaluated_data_set, data)) {
	  f2ptr new_bcs = raw__optimize_data__compile_new_bytecodes_for_define(cause, data);
	  if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
  }
  return full_bcs;
}

f2ptr raw__optimize_context__compile_new_bytecodes_for_fiber_and_branches(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr full_bcs = nil;
  f2ptr iter_bcs = nil;
  // Note the need to compute branch_or_return_value before side
  // effects because we only need to explicitely compute side effects if they are not
  // already going to be computed for values later.
  f2ptr fiber_branch_or_return_value_bcs = raw__optimize_context__compile_fiber_branch_or_return_value(cause, this, fiber);
  f2ptr fiber_side_effects_bcs           = raw__optimize_context__compile_fiber_side_effects(          cause, this, fiber);
  {
    f2ptr new_bcs = fiber_side_effects_bcs;
    if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
  }
  {
    f2ptr new_bcs = fiber_branch_or_return_value_bcs;
    if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
  }
  f2ptr branch_condition_data = f2__optimize_fiber__branch_condition_data(cause, fiber);
  if (branch_condition_data != nil) {
    f2ptr true_child_branched_fiber  = f2__optimize_fiber__true_child_branched_fiber( cause, fiber);
    f2ptr false_child_branched_fiber = f2__optimize_fiber__false_child_branched_fiber(cause, fiber);
    f2ptr true_bcs                   = raw__optimize_context__compile_new_bytecodes_for_fiber_and_branches(cause, this, true_child_branched_fiber);
    f2ptr false_bcs                  = raw__optimize_context__compile_new_bytecodes_for_fiber_and_branches(cause, this, false_child_branched_fiber);
    f2ptr end_bcs                    = f2__compile__nop(cause);
    {
      f2ptr new_bcs = f2__compile__else_jump(cause, false_bcs);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    {
      f2ptr new_bcs = true_bcs;
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    {
      f2ptr new_bcs = f2__compile__jump(cause, end_bcs);
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    {
      f2ptr new_bcs = false_bcs;
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
    {
      f2ptr new_bcs = end_bcs;
      if (iter_bcs == nil) {iter_bcs = full_bcs = new_bcs;} else {iter_bcs = raw__list_cdr__set(cause, iter_bcs, new_bcs);}
    }
  }
  return full_bcs;
}

f2ptr raw__bytecodes__remove_nops(f2ptr cause, f2ptr these) {
  f2ptr full_bcs = these;
  f2ptr nop_bcs_next_hash = f2__ptypehash__new(cause);
  // Remove nops while keeping track of their next pointer in a hash.
  {
    f2ptr prev = nil;
    f2ptr iter = full_bcs;
    while (iter != nil) {
      f2ptr bytecode = f2__cons__car(cause, iter);
      f2ptr next     = f2__cons__cdr(cause, iter);
      {
	f2ptr command = f2__bytecode__command(cause, bytecode);
	if (raw__eq(cause, command, __funk2.bytecode.bytecode__nop__symbol)) {
	  raw__ptypehash__add(cause, nop_bcs_next_hash, iter, next);
	  if (prev == nil) {
	    full_bcs = next;
	  } else {
	    f2__cons__cdr__set(cause, prev, next);
	  }
	}
      }
      prev = iter;
      iter = next;
    }
  }
  // Replace all jumps to nop pointers with their respective next pointers.
  {
    f2ptr iter = full_bcs;
    while (iter != nil) {
      f2ptr bytecode = f2__cons__car(cause, iter);
      {
	f2ptr command = f2__bytecode__command(cause, bytecode);
	if (raw__eq(cause, command, __funk2.bytecode.bytecode__jump__symbol)) {
	  f2ptr new_pc = f2__bytecode__arg0(cause, bytecode);
	  if (raw__ptypehash__contains(cause, nop_bcs_next_hash, new_pc)) {
	    f2ptr nop_pc_replacement = raw__ptypehash__lookup(cause, nop_bcs_next_hash, new_pc);
	    f2__bytecode__arg0__set(cause, bytecode, nop_pc_replacement);
	  }
	} else if (raw__eq(cause, command, __funk2.bytecode.bytecode__if_jump__symbol)) {
	  f2ptr new_pc = f2__bytecode__arg0(cause, bytecode);
	  if (raw__ptypehash__contains(cause, nop_bcs_next_hash, new_pc)) {
	    f2ptr nop_pc_replacement = raw__ptypehash__lookup(cause, nop_bcs_next_hash, new_pc);
	    f2__bytecode__arg0__set(cause, bytecode, nop_pc_replacement);
	  }
	} else if (raw__eq(cause, command, __funk2.bytecode.bytecode__else_jump__symbol)) {
	  f2ptr new_pc = f2__bytecode__arg0(cause, bytecode);
	  if (raw__ptypehash__contains(cause, nop_bcs_next_hash, new_pc)) {
	    f2ptr nop_pc_replacement = raw__ptypehash__lookup(cause, nop_bcs_next_hash, new_pc);
	    f2__bytecode__arg0__set(cause, bytecode, nop_pc_replacement);
	  }
	}
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return full_bcs;
}


f2ptr raw__optimize_context__compile_new_bytecodes(f2ptr cause, f2ptr this, f2ptr funk) {
  f2ptr full_bcs = f2__compile__block_enter(cause);
  f2ptr iter_bcs = full_bcs;
  // define arguments from stack
  {
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__copy_args_to_iter(cause));
    f2ptr args = f2__funk__args(cause, funk);
    {
      f2ptr iter = args;
      while (iter != nil) {
	f2ptr arg  = f2__cons__car(cause, iter);
	f2ptr next = f2__cons__cdr(cause, iter);
	if (raw__symbol__eq(cause, arg, __funk2.globalenv.and_rest__symbol)) {
	  iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_define_rest_argument(cause, f2__cons__car(cause, next)));
	  iter = nil;
	} else {
	  if (next) {
	    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_define_argument(cause, arg));
	  } else {
	    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_define_last_argument(cause, arg));
	  }
	  iter = next;
	}
      }
    }
  }
  
  // convert fiber tree to bytecodes
  {
    f2ptr initial_fiber = f2__optimize_context__initial_fiber(cause, this);
    f2ptr fiber_bcs     = raw__optimize_context__compile_new_bytecodes_for_fiber_and_branches(cause, this, initial_fiber);
    if (raw__larva__is_type(cause, fiber_bcs)) {
      return fiber_bcs;
    }
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, fiber_bcs);
  }
  
  // exit block
  boolean_t popped_env_and_return = boolean__false;
  if (! popped_env_and_return) {
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_exit_and_pop(cause, funk));
  } else {
    iter_bcs = raw__list_cdr__set(cause, iter_bcs, f2__compile__block_exit_and_no_pop(cause, funk));
  }
  
  // remove nops that were necessary for constructing branches.
  full_bcs = raw__bytecodes__remove_nops(cause, full_bcs);
  
  f2__optimize_context__optimized_bytecodes__set(cause, this, full_bcs);
  return nil;
}


f2ptr raw__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list18__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "optimize_context"),
						new__symbol(cause, "maximum_loop_count"),  f2__optimize_context__maximum_loop_count( cause, this),
						new__symbol(cause, "initial_fiber"),       f2__optimize_context__initial_fiber(      cause, this),
						new__symbol(cause, "active_fiber_set"),    f2__optimize_context__active_fiber_set(   cause, this),
						new__symbol(cause, "branched_fiber_set"),  f2__optimize_context__branched_fiber_set( cause, this),
						new__symbol(cause, "finished_fiber_set"),  f2__optimize_context__finished_fiber_set( cause, this),
						new__symbol(cause, "evaluated_data_set"),  f2__optimize_context__evaluated_data_set( cause, this),
						new__symbol(cause, "defined_data_set"),    f2__optimize_context__defined_data_set(   cause, this),
						new__symbol(cause, "optimized_bytecodes"), f2__optimize_context__optimized_bytecodes(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__optimize_context__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(optimize_context,     this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__optimize_context__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(optimize_context__terminal_print_with_frame, this, terminal_print_frame,
	    "Prints this optimize_context to the given terminal.",
	    return f2__optimize_context__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2optimize_context__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2optimize_context__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk);}
  return this;
}


f2ptr raw__funk__optimize(f2ptr cause, f2ptr this, s64 maximum_loop_count) {
  f2ptr optimize_context = raw__optimize_context__new(cause, maximum_loop_count);
  // attempt to unroll all loops in simulation
  {
    f2ptr initial_fiber = f2__optimize_context__initial_fiber(cause, optimize_context);
    {
      f2ptr result = raw__optimize_fiber__prepare_to_call_funk(cause, initial_fiber, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    f2ptr possible_too_many_loops_larva = raw__optimize_context__complete_simulation(cause, optimize_context);
    if (raw__larva__is_type(cause, possible_too_many_loops_larva)) {
      if (! raw__optimize_too_many_loops_larva__is_type(cause, possible_too_many_loops_larva)) {
	return possible_too_many_loops_larva;
      }
      // need to extract loops.
      printf("\noptimize warning: loop extraction not yet implemented."); fflush(stdout);
      return optimize_context;
    }
    {
      f2ptr result = raw__optimize_context__compile_new_bytecodes(cause, optimize_context, this);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr optimized_bytecodes = f2__optimize_context__optimized_bytecodes(cause, optimize_context);
      f2__funk__body_bytecodes__set(cause, this, optimized_bytecodes);
    }
    f2__funk__body__set(               cause, this, nil);
    f2__funk__demetropolized_body__set(cause, this, nil);
  }
  return optimize_context;
}

f2ptr f2__funk__optimize(f2ptr cause, f2ptr this, f2ptr maximum_loop_count) {
  assert_argument_type(funk,    this);
  assert_argument_type(integer, maximum_loop_count);
  s64 maximum_loop_count__i = f2integer__i(maximum_loop_count, cause);
  return raw__funk__optimize(cause, this, maximum_loop_count__i);
}






// **

void f2__optimize__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // optimize_bytecode
  
  initialize_primobject_3_slot__defragment__fix_pointers(optimize_bytecode,
							 optimize_context,
							 sequence,
							 execution_count);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_bytecode.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_bytecode__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_bytecode.terminal_print_with_frame__funk);
  
  
  // optimize_chunk
  
  initialize_primobject_2_slot__defragment__fix_pointers(optimize_chunk,
							 bytecode_sequence,
							 transition);
  
  f2__primcfunk__init__defragment__fix_pointers(optimize_chunk__new_from_bytecodes);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.as__bytecodes__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_chunk__as__bytecodes);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.as__bytecodes__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.possible_optimized_funk_bytecodes__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_chunk__possible_optimized_funk_bytecodes);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.possible_optimized_funk_bytecodes__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_chunk__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.terminal_print_with_frame__funk);
  
  
  
  // optimize_transition
  
  initialize_primobject_4_slot__defragment__fix_pointers(optimize_transition,
							 transition_type,
							 next_chunk,
							 true_chunk,
							 false_chunk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_transition.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_transition__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_transition.terminal_print_with_frame__funk);
  
  
  // optimize_data
  
  initialize_primobject_4_slot__defragment__fix_pointers(optimize_data,
							 optimize_context,
							 name,
							 data_type,
							 args);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_data__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__funk);
  
  
  // optimize_fiber
  
  initialize_primobject_13_slot__defragment__fix_pointers(optimize_fiber,
							  optimize_context,
							  parent_branched_fiber,
							  branch_condition_data,
							  true_child_branched_fiber,
							  false_child_branched_fiber,
							  data_side_effects,
							  stack,
							  value,
							  iter,
							  program_counter,
							  args,
							  return_reg,
							  env);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_fiber__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__funk);
  
  
  // optimize_context
  
  initialize_primobject_9_slot__defragment__fix_pointers(optimize_context,
							 maximum_loop_count,
							 optimize_bytecode_sequence_hash,
							 initial_fiber,
							 active_fiber_set,
							 branched_fiber_set,
							 finished_fiber_set,
							 evaluated_data_set,
							 defined_data_set,
							 optimized_bytecodes);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(optimize_context__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk);
}

void f2__optimize__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // optimize_bytecode
  
  initialize_primobject_3_slot(optimize_bytecode,
			       optimize_context,
			       sequence,
			       execution_count);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_bytecode.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_bytecode__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_bytecode.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_chunk
  
  initialize_primobject_2_slot(optimize_chunk,
			       bytecode_sequence,
			       transition);
  
  f2__primcfunk__init__1(optimize_chunk__new_from_bytecodes, these);
  
  {char* symbol_str = "as-bytecodes"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.as__bytecodes__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(optimize_chunk__as__bytecodes, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.as__bytecodes__funk = never_gc(cfunk);}
  {char* symbol_str = "possible_optimized_funk_bytecodes"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.possible_optimized_funk_bytecodes__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_chunk__possible_optimized_funk_bytecodes, this, funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.possible_optimized_funk_bytecodes__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_chunk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_chunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  
  // optimize_transition
  
  initialize_primobject_4_slot(optimize_transition,
			       transition_type,
			       next_chunk,
			       true_chunk,
			       false_chunk);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_transition.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_transition__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_transition.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_data
  
  initialize_primobject_4_slot(optimize_data,
			       optimize_context,
			       name,
			       data_type,
			       args);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_data__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_data.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_fiber
  
  initialize_primobject_13_slot(optimize_fiber,
				optimize_context,
				parent_branched_fiber,
				branch_condition_data,
				true_child_branched_fiber,
				false_child_branched_fiber,
				data_side_effects,
				stack,
				value,
				iter,
				program_counter,
				args,
				return_reg,
				env);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_fiber__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_fiber.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // optimize_context
  
  initialize_primobject_9_slot(optimize_context,
			       maximum_loop_count,
			       optimize_bytecode_sequence_hash,
			       initial_fiber,
			       active_fiber_set,
			       branched_fiber_set,
			       finished_fiber_set,
			       evaluated_data_set,
			       defined_data_set,
			       optimized_bytecodes);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(optimize_context__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_optimize_context.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__optimize__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "optimize", "", &f2__optimize__reinitialize_globalvars, &f2__optimize__defragment__fix_pointers);
  
  f2__optimize__reinitialize_globalvars();
}


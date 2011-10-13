// 
// Copyright (c) 2007-2011 Bo Morgan.
// All rights reserved.
// 
// Author: Bo Morgan
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

#define F2__PTYPE__C__COMPILING

#include "funk2.h"

void print_cmutex_error(int retval) {
  switch (retval) {
  case EINVAL: error(nil, "error unlocking ptype_cmutex: cmutex is not initialized.");              break;
  case EFAULT: error(nil, "error unlocking ptype_cmutex: cmutex is an invalid pointer.");           break;
  case EPERM:  error(nil, "error unlocking ptype_cmutex: the calling thread does not own cmutex."); break;
  default:     error(nil, "error unlocking ptype_cmutex: unknown error.");                         break;
  }
}

void raw__exp__increment_reference_count(f2ptr this) {
  if (this) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this));
    atomic_inc(&(block->reference_count));
  }
}

void debug__contradictory_atomic_dec_and_test() {
  printf("\ncontradictory atomic dec and test.");
  status(  "contradictory atomic dec and test.");
}

boolean_t raw__exp__decrement_reference_count(f2ptr this) {
  boolean_t no_more_references = boolean__false;
  if (this) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this));
    no_more_references      = atomic_dec_and_test(&(block->reference_count));
    //if (no_more_references) {
    //if (atomic_read(&(block->reference_count)) != 0) { // double check...
    //debug__contradictory_atomic_dec_and_test();
    //}
    //}
  }
  return no_more_references;
}

// notify garbage collector of changed references and mutated memory.
void funk2_garbage_collector__know_of_changed_references(funk2_garbage_collector_t* this, f2ptr exp, f2ptr old_value, f2ptr value) {
  if (old_value) {
    boolean_t no_more_references = raw__exp__decrement_reference_count(old_value);
    if (no_more_references) {
      // notify garbage collector to whiten old value if it is not already because it has no references (because of no references it doesn't upset the "no black references white" invariant).
      funk2_garbage_collector__know_of_no_more_references(this, old_value);
    }
  }
  if (value) {
    raw__exp__increment_reference_count(value);
  }
  
  // notify garbage collector to grey this memory if it is black because it has been mutated.
  funk2_garbage_collector__know_of_used_exp_mutation(this, exp);
  
  if (old_value) {
    // protect the old value
    funk2_garbage_collector__know_of_protected_f2ptr(this, old_value);
  }
} 

// used by global initialization for creation (and other) causes

f2ptr initial_cause() {
  return nil;
}

// this.system

f2ptr pfunk2__system__environment(f2ptr cause) {
  return __funk2.memory.global_environment_f2ptr;
}

// memblock

boolean_t raw__cause__is_traced__trace_depth(f2ptr cause, f2ptr this, int trace_depth) {
  if (! this) {
    return nil;
  }
#ifdef F2__PTYPE__TYPE_CHECK
  //if(! raw__cause__is_type(cause, this)) {
  //  status("raw__cause__is_traced !raw__cause__is_type(cause, this)");
  //  f2__print(nil, this); fflush(stdout);
  //  error(nil, "raw__cause__is_traced !raw__cause__is_type(cause, this)");
  //}
#endif
  return f2cause__memory_tracing_on__trace_depth(this, cause, trace_depth);
}

boolean_t raw__cause__is_traced(f2ptr cause, f2ptr this) {
  return raw__cause__is_traced__trace_depth(cause, this, 0);
}

void debug__cause__is_imaginary() {
  //printf("\ndebug__cause__is_imaginary here.");
}

boolean_t raw__cause__is_imaginary__trace_depth(f2ptr cause, f2ptr this, int trace_depth) {
  if (! this) {
    return nil;
  }
#ifdef F2__PTYPE__TYPE_CHECK
  //if(! raw__cause__is_type(cause, this)) {
  //  status("raw__cause__is_imaginary !raw__cause__is_type(cause, this)");
  //  f2__print(nil, this); fflush(stdout);
  //  error(nil, "raw__cause__is_imaginary !raw__cause__is_type(cause, this)");
  //}
#endif
  f2ptr the_cause_for_checking_whether_imaginary_or_not = nil; // avoids infinitely considering whether or not we are imagining by returning the "real" value of our cause's imagination stack... (see South Park, ImaginationLand Episode for elaboration)
  boolean_t return_value = (f2cause__imagination_stack(this, the_cause_for_checking_whether_imaginary_or_not) != nil);
  if (return_value) {
    debug__cause__is_imaginary();
  }
  return return_value;
}

boolean_t raw__cause__is_imaginary(f2ptr cause, f2ptr this) {
  return raw__cause__is_imaginary__trace_depth(cause, this, 0);
}

void ptype_error(f2ptr cause, f2ptr this, f2ptr expected_type) {
  error(nil, "ptype_error.");
}

#define check_wait_politely() funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller))

// ptype

boolean_t raw__ptype__is_type(f2ptr cause, f2ptr thing) {
  if (thing) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__ptype__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__ptype__is_type(cause, thing));}
def_pcfunk1(ptype__is_type, thing,
	    "",
	    return f2__ptype__is_type(this_cause, thing));

f2ptr f2__ptype__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "ptype");}
def_pcfunk1(ptype__type, this,
	    "",
	    return f2__ptype__type(this_cause, this));

ptype_t pfunk2__f2ptype__raw(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  ptype_t retval = __pure__f2ptype__raw(this);
  return retval;
}

f2ptr f2__ptype__raw(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2ptype__raw(x, cause));}
def_pcfunk1(ptype__raw, x,
	    "",
	    return f2__ptype__raw(this_cause, x));

f2ptr pfunk2__f2ptype__cause(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  f2ptr value = __pure__f2ptype__cause(this);
  debug__assert((! value) || raw__cause__is_type(cause, value), nil, "debug error: value is not cause.");
  return value;
}

f2ptr f2__ptype__cause(f2ptr cause, f2ptr x) {
  assert_argument_type(ptype, x);
  return f2ptype__cause(x, cause);
}
def_pcfunk1(ptype__cause, x,
	    "",
	    return f2__ptype__cause(this_cause, x));

f2ptr pfunk2__f2ptype__cause__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  debug__assert((! value) || raw__cause__is_type(cause, value), nil, "debug error: value is not cause.");
  f2ptr old_value = __pure__f2ptype__cause(this);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  __pure__f2ptype__cause(this) = value;
  return nil;
}

f2ptr f2__ptype__cause__set(f2ptr cause, f2ptr x, f2ptr value) {
  assert_argument_type(ptype, x);
  f2ptype__cause__set(x, cause, value);
  return nil;
}
def_pcfunk2(ptype__cause__set, x, value,
	    "",
	    return f2__ptype__cause__set(this_cause, x, value));

f2ptr f2ptype__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, nil);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.is_type__funk);}
  {char* slot_name = "type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.type__funk);}
  {char* slot_name = "raw";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.raw__funk);}
  {char* slot_name = "cause";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.cause__funk);}
  {char* slot_name = "cause";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.cause__set__funk);}
  return this;
}

// integer

f2ptr ptype_integer__new(int pool_index, f2ptr cause, s64 i) {
  f2ptr integer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_integer_block_t));
  ptype_integer_block_t* integer_block = (ptype_integer_block_t*)from_ptr(raw__f2ptr_to_ptr(integer_f2ptr));
  debug__assert(integer_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  integer_block->ptype.block.ptype = ptype_integer;
  integer_block->ptype.cause       = cause;
  integer_block->i                 = i;
  return integer_f2ptr;
}

f2ptr pfunk2__f2integer__new(f2ptr cause, s64 i) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2integer__new(pool_index, cause, i);
  return retval;
}

s64 pfunk2__f2integer__i(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_integer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_integer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  s64 i = __pure__f2integer__i(this);
  return i;
}

boolean_t raw__integer__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_integer);
}
f2ptr f2__integer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__integer__is_type(cause, x));}
def_pcfunk1(integer__is_type, this,
	    "",
	    return f2__integer__is_type(this_cause, this));

f2ptr f2__integer__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "integer");}
def_pcfunk1(integer__type,    this,
	    "",
	    return f2__integer__type(this_cause, this));

def_pcfunk1(integer__new,     this,
	    "",
	    return f2integer__new(this_cause, f2integer__i(this, this_cause)));
def_pcfunk1(integer__i,       this,
	    "",
	    return this);


boolean_t raw__integer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__integer__is_type(cause, that)) {
    return boolean__false;
  }
  return f2integer__i(this, cause) == f2integer__i(that, cause);
}

f2ptr f2__integer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__integer__eq(cause, this, that));
}
def_pcfunk2(integer__eq, this, that,
	    "",
	    return f2__integer__eq(this_cause, this, that));


u64 raw__integer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__i(this, cause);}

f2ptr f2__integer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__integer__eq_hash_value(cause, this));}
def_pcfunk1(integer__eq_hash_value, this,
	    "",
	    return f2__integer__eq_hash_value(this_cause, this));


boolean_t raw__integer__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__integer__eq(cause, this, that);}

f2ptr f2__integer__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(integer, this);
  return f2bool__new(raw__integer__equals(cause, this, that));
}
def_pcfunk2(integer__equals, this, that,
	    "",
	    return f2__integer__equals(this_cause, this, that));


u64 raw__integer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__integer__eq_hash_value(cause, this);
}

f2ptr f2__integer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(integer,   this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__integer__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(integer__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__integer__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__integer__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__integer__eq_hash_value(cause, this);
}

f2ptr f2__integer__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2integer__new(cause, raw__integer__equals_hash_value(cause, this));
}
def_pcfunk1(integer__equals_hash_value, this,
	    "",
	    return f2__integer__equals_hash_value(this_cause, this));


double raw__integer__as__double(f2ptr cause, f2ptr this) {
  return f2integer__i(this, cause);
}

f2ptr f2__integer__as__double(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2double__new(cause, raw__integer__as__double(cause, this));
}
def_pcfunk1(integer__as__double, this,
	    "",
	    return f2__integer__as__double(this_cause, this));


ptr raw__integer__as__pointer(f2ptr cause, f2ptr this) {
  return (ptr)f2integer__i(this, cause);
}

f2ptr f2__integer__as__pointer(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2pointer__new(cause, raw__integer__as__pointer(cause, this));
}
def_pcfunk1(integer__as__pointer, this,
	    "",
	    return f2__integer__as__pointer(this_cause, this));


f2ptr f2__integer__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__multiply_overflows(value, number_value)) {
      return f2integer__new(cause, value * number_value);
    } else {
      return f2__largeinteger__multiplied_by(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__multiplied_by(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_multiply_an_integer_by_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__multiplied_by, this, that,
	    "",
	    return f2__integer__multiplied_by(this_cause, this, that));


f2ptr f2__integer__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2integer__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__divide(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_divide_an_integer_by_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__divided_by, this, that,
	    "",
	    return f2__integer__divided_by(this_cause, this, that));


f2ptr f2__integer__plus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__add_overflows(value, number_value)) {
      return f2integer__new(cause, value + number_value);
    } else {
      return f2__largeinteger__add(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__add(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_add_integer_to_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__plus, this, that,
	    "",
	    return f2__integer__plus(this_cause, this, that));


f2ptr f2__integer__minus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__add_overflows(value, -number_value) && ((number_value == 0) || (-number_value != number_value))) {
      return f2integer__new(cause, value - f2integer__i(number, cause));
    } else {
      return f2__largeinteger__subtract(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__subtract(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_minus_an_integer_with_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__minus, this, that,
	    "",
	    return f2__integer__minus(this_cause, this, that));


f2ptr f2__integer__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__greater_than(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_ask_is_greater_than_with_an_integer_and_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__is_greater_than, this, that,
	    "",
	    return f2__integer__is_greater_than(this_cause, this, that));


f2ptr f2__integer__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__less_than(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_ask_is_less_than_with_an_integer_and_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__is_less_than, this, that,
	    "",
	    return f2__integer__is_less_than(this_cause, this, that));


f2ptr f2__integer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__equals(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_ask_is_numerically_equal_to_with_an_integer_and_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__is_numerically_equal_to, this, that,
	    "",
	    return f2__integer__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__integer__square_root(f2ptr cause, f2ptr this) {
  s64 i = f2integer__i(this, cause);
  if (i < 0) {
    return f2larva__new(cause, 5, nil);
  }
  return f2integer__new(cause, u64__sqrt(i));
}

f2ptr f2__integer__square_root(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return raw__integer__square_root(cause, this);
}
def_pcfunk1(integer__square_root, this,
	    "",
	    return f2__integer__square_root(this_cause, this));


f2ptr raw__integer__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  s64 this__i    = f2integer__i(this, cause);
  s64 that__i    = f2integer__i(that, cause);
  s64 result     = this__i % that__i;
  return f2integer__new(cause, result);
}

f2ptr f2__integer__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(integer, this);
  assert_argument_type(integer, that);
  return raw__integer__modulo(cause, this, that);
}
def_pcfunk2(integer__modulo, this, that,
	    "",
	    return f2__integer__modulo(this_cause, this, that));


f2ptr raw__integer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t integer_string[128];
  u64               integer_string__length = funk2_character_string__snprintf(integer_string, 128, s64__fstr, f2integer__i(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__integer__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, integer_string__length, integer_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__integer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(integer,              this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__integer__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(integer__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__integer__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__integer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.i__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.as__double__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.as__integer__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.as__integer__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.plus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.minus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.square_root__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.new__funk;
    }
  }
  return nil;
}

f2ptr f2integer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.new__funk);}
  {char* slot_name = "i";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.i__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk);}
  {char* slot_name = "as-double";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk);}
  {char* slot_name = "as-pointer";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__funk);}
  {char* slot_name = "multiplied_by";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk);}
  {char* slot_name = "divided_by";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk);}
  {char* slot_name = "plus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.plus__funk);}
  {char* slot_name = "minus";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.minus__funk);}
  {char* slot_name = "is_greater_than";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk);}
  {char* slot_name = "square_root";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk);}
  {char* slot_name = "modulo";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.modulo__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__funk);}
  return this;
}


// double

f2ptr ptype_double__new(int pool_index, f2ptr cause, double d) {
  f2ptr double_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_double_block_t));
  ptype_double_block_t* double_block = (ptype_double_block_t*)from_ptr(raw__f2ptr_to_ptr(double_f2ptr));
  debug__assert(double_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  double_block->ptype.block.ptype = ptype_double;
  double_block->ptype.cause       = cause;
  double_block->d                 = d;
  return double_f2ptr;
}

f2ptr pfunk2__f2double__new(f2ptr cause, double d) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2double__new(pool_index, cause, d);
  return retval;
}

double pfunk2__f2double__d(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_double) {
    ptype_error(cause, this, __funk2.globalenv.ptype_double__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  double d = __pure__f2double__d(this);
  return d;
}

boolean_t raw__double__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_double);
}
f2ptr f2__double__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__double__is_type(cause, x));}
def_pcfunk1(double__is_type, x,   
	    "",
	    return f2__double__is_type(this_cause, x));

f2ptr f2__double__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "double");}
def_pcfunk1(double__type,    this,
	    "",
	    return f2__double__type(this_cause, this));

def_pcfunk1(double__new,     this,
	    "",
	    return f2double__new(this_cause, f2double__d(this, this_cause)));
def_pcfunk1(double__d,       this,
	    "",
	    return f2double__new(this_cause, f2double__d(this, this_cause)));

boolean_t raw__double__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__double__is_type(cause, that)) {
    return boolean__false;
  }
  return f2double__d(this, cause) == f2double__d(that, cause);
}

f2ptr f2__double__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__double__eq(cause, this, that));
}
def_pcfunk2(double__eq, this, that,
	    "",
	    return f2__double__eq(this_cause, this, that));

u64 raw__double__eq_hash_value(f2ptr cause, f2ptr this) {
  union {
    struct {
      double d;
      u64    zero;
    } s;
    u64 u;
  } stack_memory;
  stack_memory.s.d    = f2double__d(this, cause);
  stack_memory.s.zero = 0;
  u64 eq_hash_value = stack_memory.u;
  return eq_hash_value;
}

f2ptr f2__double__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__double__eq_hash_value(cause, this));}
def_pcfunk1(double__eq_hash_value, this,
	    "",
	    return f2__double__eq_hash_value(this_cause, this));

boolean_t raw__double__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__double__eq(cause, this, that);}

f2ptr f2__double__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(double, this);
  return f2bool__new(raw__double__equals(cause, this, that));
}
def_pcfunk2(double__equals, this, that,
	    "",
	    return f2__double__equals(this_cause, this, that));


u64 raw__double__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__double__eq_hash_value(cause, this);
}

f2ptr f2__double__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(double,    this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__double__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(double__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__double__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__double__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__double__eq_hash_value(cause, this);
}

f2ptr f2__double__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return f2integer__new(cause, raw__double__equals_hash_value(cause, this));
}
def_pcfunk1(double__equals_hash_value, this,
	    "",
	    return f2__double__equals_hash_value(this_cause, this));


double raw__double__as__double(f2ptr cause, f2ptr this) {
  return f2double__d(this, cause);
}

f2ptr f2__double__as__double(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return f2double__new(cause, raw__double__as__double(cause, this));
}
def_pcfunk1(double__as__double, this,
	    "",
	    return f2__double__as__double(this_cause, this));


f2ptr f2__double__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value * f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value * raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 1246246, nil);
}
def_pcfunk2(double__multiplied_by, this, that,
	    "",
	    return f2__double__multiplied_by(this_cause, this, that));


f2ptr f2__double__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value / raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 12634, nil);
}
def_pcfunk2(double__divided_by, this, that,
	    "",
	    return f2__double__divided_by(this_cause, this, that));


f2ptr f2__double__plus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value + f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value + raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 23441, nil);
}
def_pcfunk2(double__plus, this, that,
	    "",
	    return f2__double__plus(this_cause, this, that));


f2ptr f2__double__minus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value - f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value - raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 12642, nil);
}
def_pcfunk2(double__minus, this, that,
	    "",
	    return f2__double__minus(this_cause, this, that));


f2ptr f2__double__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value > raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 123525, nil);
}
def_pcfunk2(double__is_greater_than, this, that,
	    "",
	    return f2__double__is_greater_than(this_cause, this, that));


f2ptr f2__double__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value < raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 124624, nil);
}
def_pcfunk2(double__is_less_than, this, that,
	    "",
	    return f2__double__is_less_than(this_cause, this, that));


f2ptr f2__double__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value == raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 124625, nil);
}
def_pcfunk2(double__is_numerically_equal_to, this, that,
	    "",
	    return f2__double__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__double__square_root(f2ptr cause, f2ptr this) {
  double d = f2double__d(this, cause);
  if (d < 0) {
    return f2larva__new(cause, 5, nil);
  }
  return f2double__new(cause, sqrt(d));
}

f2ptr f2__double__square_root(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__square_root(cause, this);
}
def_pcfunk1(double__square_root, this,
	    "",
	    return f2__double__square_root(this_cause, this));


f2ptr raw__double__radian_sine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = sin(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_sine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_sine(cause, this);
}
def_pcfunk1(double__radian_sine, this,
	    "",
	    return f2__double__radian_sine(this_cause, this));


f2ptr raw__double__radian_arcsine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = asin(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_arcsine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_arcsine(cause, this);
}
def_pcfunk1(double__radian_arcsine, this,
	    "",
	    return f2__double__radian_arcsine(this_cause, this));


f2ptr raw__double__radian_cosine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = cos(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_cosine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_cosine(cause, this);
}
def_pcfunk1(double__radian_cosine, this,
	    "",
	    return f2__double__radian_cosine(this_cause, this));


f2ptr raw__double__radian_arccosine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = acos(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_arccosine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_arccosine(cause, this);
}
def_pcfunk1(double__radian_arccosine, this,
	    "",
	    return f2__double__radian_arccosine(this_cause, this));


f2ptr raw__double__radian_tangent(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = tan(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_tangent(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_tangent(cause, this);
}
def_pcfunk1(double__radian_tangent, this,
	    "",
	    return f2__double__radian_tangent(this_cause, this));


f2ptr raw__double__radian_arctangent(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = atan(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_arctangent(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_arctangent(cause, this);
}
def_pcfunk1(double__radian_arctangent, this,
	    "",
	    return f2__double__radian_arctangent(this_cause, this));


f2ptr raw__double__power(f2ptr cause, f2ptr this, f2ptr that) {
  double this__d = f2double__d(this, cause);
  double that__d = f2double__d(that, cause);
  double result  = pow(this__d, that__d);
  return f2double__new(cause, result);
}

f2ptr f2__double__power(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(double, this);
  assert_argument_type(double, that);
  return raw__double__power(cause, this, that);
}
def_pcfunk2(double__power, this, that,
	    "",
	    return f2__double__power(this_cause, this, that));


f2ptr raw__double__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  double this__d    = f2double__d(this, cause);
  double that__d    = f2double__d(that, cause);
  double whole_part = (int)(this__d / that__d);
  double result     = this__d - (that__d * whole_part);
  return f2double__new(cause, result);
}

f2ptr f2__double__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(double, this);
  assert_argument_type(double, that);
  return raw__double__modulo(cause, this, that);
}
def_pcfunk2(double__modulo, this, that,
	    "",
	    return f2__double__modulo(this_cause, this, that));


f2ptr raw__double__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t double_string[128];
  u64               double_string__length = funk2_character_string__snprintf(double_string, 128, "%1.16f", f2double__d(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__double__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, double_string__length, double_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__double__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(double,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__double__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(double__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__double__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__double__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.d__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.d__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.as__double__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.as__double__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.divided_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.plus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.minus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.square_root__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.square_root__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
  }
  return nil;
}

f2ptr f2__double__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.new__funk;
  }
  return nil;
}

f2ptr f2double__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.new__funk);}
  {char* slot_name = "d";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.d__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk);}
  {char* slot_name = "as-double";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.as__double__funk);}
  {char* slot_name = "multiplied_by";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk);}
  {char* slot_name = "divided_by";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk);}
  {char* slot_name = "plus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.plus__funk);}
  {char* slot_name = "minus";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.minus__funk);}
  {char* slot_name = "is_greater_than";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk);}
  {char* slot_name = "square_root";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.square_root__funk);}
  {char* slot_name = "radian_sine";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_sine__funk);}
  {char* slot_name = "radian_arcsine";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__funk);}
  {char* slot_name = "radian_cosine";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__funk);}
  {char* slot_name = "radian_arccosine";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__funk);}
  {char* slot_name = "radian_tangent";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__funk);}
  {char* slot_name = "radian_arctangent";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__funk);}
  {char* slot_name = "power";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.power__funk);}
  {char* slot_name = "modulo";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.modulo__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__funk);}
  return this;
}


// float

f2ptr ptype_float__new(int pool_index, f2ptr cause, float f) {
  f2ptr float_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_float_block_t));
  ptype_float_block_t* float_block = (ptype_float_block_t*)from_ptr(raw__f2ptr_to_ptr(float_f2ptr));
  debug__assert(float_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  float_block->ptype.block.ptype = ptype_float;
  float_block->ptype.cause       = cause;
  float_block->f                 = f;
  return float_f2ptr;
}

f2ptr pfunk2__f2float__new(f2ptr cause, float f) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2float__new(pool_index, cause, f);
  return retval;
}

float pfunk2__f2float__f(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_float) {
    ptype_error(cause, this, __funk2.globalenv.ptype_float__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  float f = __pure__f2float__f(this);
  return f;
}

boolean_t raw__float__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_float);
}
f2ptr f2__float__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__float__is_type(cause, x));}
def_pcfunk1(float__is_type, x,   
	    "",
	    return f2__float__is_type(this_cause, x));

f2ptr f2__float__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "float");}
def_pcfunk1(float__type,    this,
	    "",
	    return f2__float__type(this_cause, this));

def_pcfunk1(float__new,     this,
	    "",
	    return f2float__new(this_cause, f2float__f(this_cause, this)));
def_pcfunk1(float__f,       this,
	    "",
	    return this);

boolean_t raw__float__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2float__f(this, cause) == f2float__f(that, cause);
}

f2ptr f2__float__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__float__eq(cause, this, that));
}
def_pcfunk2(float__eq, this, that,
	    "",
	    return f2__float__eq(this_cause, this, that));

u64 raw__float__eq_hash_value(f2ptr cause, f2ptr this) {
  union {
    u64 u;
    struct {
      float f;
      u64   zero;
    } s;
  } stack_memory;
  stack_memory.s.f    = f2float__f(this, cause);
  stack_memory.s.zero = 0;
  u64 eq_hash_value   = stack_memory.u;
  return eq_hash_value;
}

f2ptr f2__float__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__float__eq_hash_value(cause, this));}
def_pcfunk1(float__eq_hash_value, this,
	    "",
	    return f2__float__eq_hash_value(this_cause, this));

boolean_t raw__float__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__float__is_type(cause, that)) {
    return boolean__false;
  }
  return raw__float__eq(cause, this, that);
}

f2ptr f2__float__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(float, this);
  return f2bool__new(raw__float__equals(cause, this, that));
}
def_pcfunk2(float__equals, this, that,
	    "",
	    return f2__float__equals(this_cause, this, that));


u64 raw__float__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__float__eq_hash_value(cause, this);
}

f2ptr f2__float__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(float,     this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__float__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(float__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__float__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__float__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__float__eq_hash_value(cause, this);
}

f2ptr f2__float__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(float, this);
  return f2integer__new(cause, raw__float__equals_hash_value(cause, this));
}
def_pcfunk1(float__equals_hash_value, this,
	    "",
	    return f2__float__equals_hash_value(this_cause, this));


double raw__float__as__double(f2ptr cause, f2ptr this) {
  return f2float__f(this, cause);
}

f2ptr f2__float__as__double(f2ptr cause, f2ptr this) {
  assert_argument_type(float, this);
  return raw__float__as__double(cause, this);
}
def_pcfunk1(float__as__double, this,
	    "",
	    return f2__float__as__double(this_cause, this));


f2ptr f2__float__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value * f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value * (float)raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 12462, nil);
}
def_pcfunk2(float__multiplied_by, this, that,
	    "",
	    return f2__float__multiplied_by(this_cause, this, that));


f2ptr f2__float__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value / raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 123434, nil);
}
def_pcfunk2(float__divided_by, this, that,
	    "",
	    return f2__float__divided_by(this_cause, this, that));


f2ptr f2__float__plus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value + f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value + (float)raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 123256, nil);
}
def_pcfunk2(float__plus, this, that,
	    "",
	    return f2__float__plus(this_cause, this, that));


f2ptr f2__float__minus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value - f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value - (float)raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 125335, nil);
}
def_pcfunk2(float__minus, this, that,
	    "",
	    return f2__float__minus(this_cause, this, that));


f2ptr f2__float__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value > ((float)raw__largeinteger__as__double(cause, number)));
  }
  return f2larva__new(cause, 123552, nil);
}
def_pcfunk2(float__is_greater_than, this, that,
	    "",
	    return f2__float__is_greater_than(this_cause, this, that));


f2ptr f2__float__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value < ((float)raw__largeinteger__as__double(cause, number)));
  }
  return f2larva__new(cause, 124642, nil);
}
def_pcfunk2(float__is_less_than, this, that,
	    "",
	    return f2__float__is_less_than(this_cause, this, that));


f2ptr f2__float__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value == ((float)raw__largeinteger__as__double(cause, number)));
  }
  return f2larva__new(cause, 124625, nil);
}
def_pcfunk2(float__is_numerically_equal_to, this, that,
	    "",
	    return f2__float__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__float__square_root(f2ptr cause, f2ptr this) {
  float f = f2float__f(this, cause);
  if (f < 0) {
    return f2larva__new(cause, 5, nil);
  }
  return f2float__new(cause, sqrtf(f));
}

f2ptr f2__float__square_root(f2ptr cause, f2ptr this) {
  assert_argument_type(float, this);
  return raw__float__square_root(cause, this);
}
def_pcfunk1(float__square_root, this,
	    "",
	    return f2__float__square_root(this_cause, this));


f2ptr raw__float__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t float_string[128];
  u64               float_string__length = funk2_character_string__snprintf(float_string, 128, "%1.8f", f2float__f(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__float__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, float_string__length, float_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__float__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(float,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__float__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(float__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__float__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__float__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.f__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.f__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.as__double__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.as__double__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.divided_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.plus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.minus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.square_root__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.square_root__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.new__funk;
    }
  }
  return nil;
}

f2ptr f2float__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.new__funk);}
  {char* slot_name = "f";                            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.f__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk);}
  {char* slot_name = "as-double";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.as__double__funk);}
  {char* slot_name = "multiplied_by";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk);}
  {char* slot_name = "divided_by";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk);}
  {char* slot_name = "plus";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.plus__funk);}
  {char* slot_name = "minus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.minus__funk);}
  {char* slot_name = "is_greater_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk);}
  {char* slot_name = "square_root";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.square_root__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__funk);}
  return this;
}



// pointer

f2ptr ptype_pointer__new(int pool_index, f2ptr cause, ptr p) {
  f2ptr pointer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_pointer_block_t));
  ptype_pointer_block_t* pointer_block = (ptype_pointer_block_t*)from_ptr(raw__f2ptr_to_ptr(pointer_f2ptr));
  debug__assert(pointer_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  pointer_block->ptype.block.ptype = ptype_pointer;
  pointer_block->ptype.cause       = cause;
  pointer_block->p                 = p;
  return pointer_f2ptr;
}

f2ptr pfunk2__f2pointer__new(f2ptr cause, ptr p) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2pointer__new(pool_index, cause, p);
  return retval;
}

ptr pfunk2__f2pointer__p(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  ptr p = __pure__f2pointer__p(this);
  return p;
}

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_pointer);
}
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__pointer__is_type(cause, x));}
def_pcfunk1(pointer__is_type, x,   
	    "",
	    return f2__pointer__is_type(this_cause, x));

f2ptr f2__pointer__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "pointer");}
def_pcfunk1(pointer__type,    this,
	    "",
	    return f2__pointer__type(this_cause, this));

def_pcfunk1(pointer__new,     this,
	    "",
	    return f2pointer__new(this_cause, f2pointer__p(this_cause, this)));
def_pcfunk1(pointer__p,       this,
	    "",
	    return this);

boolean_t raw__pointer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2pointer__p(this, cause) == f2pointer__p(that, cause);
}

f2ptr f2__pointer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__pointer__eq(cause, this, that));
}
def_pcfunk2(pointer__eq, this, that,
	    "",
	    return f2__pointer__eq(this_cause, this, that));

u64 raw__pointer__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2pointer__p(this, cause);}

f2ptr f2__pointer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__pointer__eq_hash_value(cause, this));}
def_pcfunk1(pointer__eq_hash_value, this,
	    "",
	    return f2__pointer__eq_hash_value(this_cause, this));

boolean_t raw__pointer__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__pointer__eq( cause, this, that);}

f2ptr f2__pointer__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  return f2bool__new(raw__pointer__equals(cause, this, that));
}
def_pcfunk2(pointer__equals, this, that,
	    "",
	    return f2__pointer__equals(this_cause, this, that));


u64 raw__pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__pointer__eq_hash_value(cause, this);
}

f2ptr f2__pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(pointer,   this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__pointer__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(pointer__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__pointer__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__pointer__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__pointer__eq_hash_value(cause, this);
}

f2ptr f2__pointer__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(pointer, this);
  return f2integer__new(cause, raw__pointer__equals_hash_value(cause, this));
}
def_pcfunk1(pointer__equals_hash_value, this,
	    "",
	    return f2__pointer__equals_hash_value(this_cause, this));


f2ptr f2__pointer__plus(f2ptr cause, f2ptr this, f2ptr integer) {
  assert_argument_type(pointer, this);
  assert_argument_type(integer, integer);
  return f2pointer__new(cause, f2pointer__p(this, cause) + f2integer__i(integer, cause));
}
def_pcfunk2(pointer__plus, this, that,
	    "",
	    return f2__pointer__plus(this_cause, this, that));

f2ptr f2__pointer__minus(f2ptr cause, f2ptr this, f2ptr integer) {
  assert_argument_type(pointer, this);
  assert_argument_type(integer, integer);
  return f2pointer__new(cause, f2pointer__p(this, cause) - f2integer__i(integer, cause));
}
def_pcfunk2(pointer__minus, this, that,
	    "",
	    return f2__pointer__minus(this_cause, this, that));

f2ptr f2__pointer__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  assert_argument_type(pointer, that);
  return f2bool__new(f2pointer__p(this, cause) > f2pointer__p(that, cause));
}
def_pcfunk2(pointer__is_greater_than, this, that,
	    "",
	    return f2__pointer__is_greater_than(this_cause, this, that));

f2ptr f2__pointer__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  assert_argument_type(pointer, that);
  return f2bool__new(f2pointer__p(this, cause) < f2pointer__p(that, cause));
}
def_pcfunk2(pointer__is_less_than, this, that,
	    "",
	    return f2__pointer__is_less_than(this_cause, this, that));

f2ptr f2__pointer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  assert_argument_type(pointer, that);
  return f2bool__new(f2pointer__p(this, cause) == f2pointer__p(that, cause));
}
def_pcfunk2(pointer__is_numerically_equal_to, this, that,
	    "",
	    return f2__pointer__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t pointer_string[128];
  u64               pointer_string__length = funk2_character_string__snprintf(pointer_string, 128, "%c%c" ptr__fstr, (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_hex, cause), f2pointer__p(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__pointer__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, pointer_string__length, pointer_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(pointer,              this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__pointer__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(pointer__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__pointer__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__pointer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk;
    }
  }
  return nil;
}

f2ptr f2pointer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk);}
  {char* slot_name = "p";                            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk);}
  {char* slot_name = "plus";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk);}
  {char* slot_name = "minus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk);}
  {char* slot_name = "is_greater_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__funk);}
  return this;
}



// scheduler_cmutex

f2ptr ptype_scheduler_cmutex__new(int pool_index, f2ptr cause) {
  f2ptr scheduler_cmutex_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_scheduler_cmutex_block_t));
  ptype_scheduler_cmutex_block_t* scheduler_cmutex_block = (ptype_scheduler_cmutex_block_t*)from_ptr(raw__f2ptr_to_ptr(scheduler_cmutex_f2ptr));
  debug__assert(scheduler_cmutex_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  scheduler_cmutex_block->ptype.block.ptype = ptype_scheduler_cmutex;
  scheduler_cmutex_block->ptype.cause       = cause;
  scheduler_cmutex_block->locked_state      = boolean__false;
  funk2_processor_mutex__init(scheduler_cmutex_block->m);
  return scheduler_cmutex_f2ptr;
}

f2ptr pfunk2__f2scheduler_cmutex__new(f2ptr cause) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2scheduler_cmutex__new(pool_index, cause);
  return retval;
}

funk2_processor_mutex_t* ptype_scheduler_cmutex__m(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  funk2_processor_mutex_t* m = __pure__f2scheduler_cmutex__m(this);
  return m;
}

boolean_t pfunk2__f2scheduler_cmutex__is_locked(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_scheduler_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_scheduler_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  //int pool_index = this_processor_thread__pool_index();
  boolean_t is_locked = funk2_processor_mutex__is_locked(ptype_scheduler_cmutex__m(this, cause));
  return is_locked;
}

void pfunk2__f2scheduler_cmutex__lock(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_scheduler_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_scheduler_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_processor_mutex_trylock_result_t trylock_result = funk2_processor_mutex_trylock_result__failure;
  {
    u64 lock_tries = 0;
    while (1) {
      trylock_result = funk2_processor_mutex__trylock(ptype_scheduler_cmutex__m(this, cause));
      if (trylock_result == funk2_processor_mutex_trylock_result__failure) {
	lock_tries ++;
	if (lock_tries > 1000) {
	  raw__spin_sleep_yield();
	} else {
	  raw__fast_spin_sleep_yield();
	}
	// no user process yield, thus is safe for scheduler and cannot be used by user process.
      } else {
	break;
      }
    }
  }
  __pure__f2scheduler_cmutex__locked_state__set(this, boolean__true);
}

void pfunk2__f2scheduler_cmutex__unlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_scheduler_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_scheduler_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  // note that this assumes the scheduler_cmutex is locked.
  __pure__f2scheduler_cmutex__locked_state__set(this, boolean__false);
  funk2_processor_mutex__unlock(ptype_scheduler_cmutex__m(this, cause));
}

int pfunk2__f2scheduler_cmutex__trylock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_scheduler_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_scheduler_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_mutex__trylock(ptype_scheduler_cmutex__m(this, cause));
  if (return_value == 0) {
    __pure__f2scheduler_cmutex__locked_state__set(this, boolean__true);
  }
  return return_value;
}

boolean_t raw__scheduler_cmutex__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_scheduler_cmutex);
}
f2ptr f2__scheduler_cmutex__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__scheduler_cmutex__is_type(cause, x));}
def_pcfunk1(scheduler_cmutex__is_type, x,
	    "",
	    return f2__scheduler_cmutex__is_type(this_cause, x));

f2ptr f2__scheduler_cmutex__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "scheduler_cmutex");}
def_pcfunk1(scheduler_cmutex__type, x,
	    "",
	    return f2__scheduler_cmutex__type(this_cause, x));

f2ptr f2__scheduler_cmutex__new(f2ptr cause) {return f2scheduler_cmutex__new(cause);}
def_pcfunk0(scheduler_cmutex__new,
	    "",
	    return f2__scheduler_cmutex__new(this_cause));


boolean_t raw__scheduler_cmutex__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__scheduler_cmutex__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__scheduler_cmutex__eq(cause, this, that));
}
def_pcfunk2(scheduler_cmutex__eq, this, that,
	    "",
	    return f2__scheduler_cmutex__eq(this_cause, this, that));


u64 raw__scheduler_cmutex__eq_hash_value(f2ptr cause, f2ptr this) {
  return ((u64)this);
}

f2ptr f2__scheduler_cmutex__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__scheduler_cmutex__eq_hash_value(cause, this));}
def_pcfunk1(scheduler_cmutex__eq_hash_value, this,
	    "",
	    return f2__scheduler_cmutex__eq_hash_value(this_cause, this));


boolean_t raw__scheduler_cmutex__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__scheduler_cmutex__eq(cause, this, that);
}

f2ptr f2__scheduler_cmutex__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(scheduler_cmutex, this);
  return f2bool__new(raw__scheduler_cmutex__equals(cause, this, that));
}
def_pcfunk2(scheduler_cmutex__equals, this, that,
	    "",
	    return f2__scheduler_cmutex__equals(this_cause, this, that));


u64 raw__scheduler_cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  funk2_processor_mutex_t* m = __pure__f2scheduler_cmutex__m(this);
  return funk2_processor_mutex__equals_hash_value(m);
}

f2ptr f2__scheduler_cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(scheduler_cmutex, this);
  return f2integer__new(cause, raw__scheduler_cmutex__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(scheduler_cmutex__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__scheduler_cmutex__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__scheduler_cmutex__equals_hash_value(f2ptr cause, f2ptr this) {
  funk2_processor_mutex_t* m = __pure__f2scheduler_cmutex__m(this);
  return funk2_processor_mutex__equals_hash_value(m);
}

f2ptr f2__scheduler_cmutex__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(scheduler_cmutex, this);
  return f2integer__new(cause, raw__scheduler_cmutex__equals_hash_value(cause, this));
}
def_pcfunk1(scheduler_cmutex__equals_hash_value, this,
	    "",
	    return f2__scheduler_cmutex__equals_hash_value(this_cause, this));


f2ptr raw__scheduler_cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t scheduler_cmutex_string[128];
  u64               scheduler_cmutex_string__length;
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__scheduler_cmutex__foreground);
    scheduler_cmutex_string__length = funk2_character_string__snprintf(scheduler_cmutex_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__left_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, scheduler_cmutex_string__length, scheduler_cmutex_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    scheduler_cmutex_string__length = funk2_character_string__snprintf(scheduler_cmutex_string, 128, "scheduler_cmutex");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, scheduler_cmutex_string__length, scheduler_cmutex_string);
  }
  if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
    return nil;
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__scheduler_cmutex__foreground);
    scheduler_cmutex_string__length = funk2_character_string__snprintf(scheduler_cmutex_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__right_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, scheduler_cmutex_string__length, scheduler_cmutex_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__scheduler_cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(scheduler_cmutex,      this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__scheduler_cmutex__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(scheduler_cmutex__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__scheduler_cmutex__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__scheduler_cmutex__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.new__funk;
    }
  }
  return nil;
}

f2ptr f2scheduler_cmutex__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.new__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.terminal_print_with_frame__funk);}
  return this;
}



// cmutex

f2ptr ptype_cmutex__new(int pool_index, f2ptr cause) {
  f2ptr cmutex_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_cmutex_block_t));
  ptype_cmutex_block_t* cmutex_block = (ptype_cmutex_block_t*)from_ptr(raw__f2ptr_to_ptr(cmutex_f2ptr));
  debug__assert(cmutex_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  cmutex_block->ptype.block.ptype = ptype_cmutex;
  cmutex_block->ptype.cause       = cause;
  cmutex_block->locked_state      = boolean__false;
  funk2_processor_mutex__init(cmutex_block->m);
  return cmutex_f2ptr;
}

f2ptr pfunk2__f2cmutex__new(f2ptr cause) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2cmutex__new(pool_index, cause);
  return retval;
}

funk2_processor_mutex_t* ptype_cmutex__m(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  funk2_processor_mutex_t* m = __pure__f2cmutex__m(this);
  return m;
}

boolean_t pfunk2__f2cmutex__is_locked(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  //int pool_index = this_processor_thread__pool_index();
  boolean_t is_locked = funk2_processor_mutex__is_locked(ptype_cmutex__m(this, cause));
  return is_locked;
}

void pfunk2__f2cmutex__lock(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_processor_mutex_trylock_result_t trylock_result = funk2_processor_mutex_trylock_result__failure;
  while (1) {
    trylock_result = funk2_processor_mutex__trylock(ptype_cmutex__m(this, cause));
    if (trylock_result == funk2_processor_mutex_trylock_result__failure) {
      f2__this__fiber__yield(cause);
    } else {
      break;
    }
  }
  __pure__f2cmutex__locked_state__set(this, boolean__true);
}

void pfunk2__f2cmutex__unlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  // note that this assumes the cmutex is locked.
  __pure__f2cmutex__locked_state__set(this, boolean__false);
  funk2_processor_mutex__unlock(ptype_cmutex__m(this, cause));
}

int pfunk2__f2cmutex__trylock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_cmutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_cmutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_mutex__trylock(ptype_cmutex__m(this, cause));
  if (return_value == 0) {
    __pure__f2cmutex__locked_state__set(this, boolean__true);
  }
  return return_value;
}

boolean_t raw__cmutex__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_cmutex);
}
f2ptr f2__cmutex__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__cmutex__is_type(cause, x));}
def_pcfunk1(cmutex__is_type, x,
	    "",
	    return f2__cmutex__is_type(this_cause, x));

f2ptr f2__cmutex__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "cmutex");}
def_pcfunk1(cmutex__type, x,
	    "",
	    return f2__cmutex__type(this_cause, x));

f2ptr f2__cmutex__new(f2ptr cause) {return f2cmutex__new(cause);}
def_pcfunk0(cmutex__new,
	    "",
	    return f2__cmutex__new(this_cause));

boolean_t raw__cmutex__is_locked(f2ptr cause, f2ptr this) {
  return f2cmutex__is_locked(this, cause);
}

f2ptr f2__cmutex__is_locked(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__is_locked(cause, this));
}
def_pcfunk1(cmutex__is_locked, this,
	    "",
	    return f2__cmutex__is_locked(this_cause, this));

void raw__cmutex__lock(f2ptr cause, f2ptr this) {
  f2cmutex__lock(this, cause);
}

f2ptr f2__cmutex__lock(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  raw__cmutex__lock(cause, this);
  return nil;
}

void raw__cmutex__unlock(f2ptr cause, f2ptr this) {
  f2cmutex__unlock(this, cause);
}

f2ptr f2__cmutex__unlock(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  raw__cmutex__unlock(cause, this);
  return nil;
}
def_pcfunk1(cmutex__unlock, this,
	    "",
	    return f2__cmutex__unlock(this_cause, this));

boolean_t raw__cmutex__trylock(f2ptr cause, f2ptr this) {
  return (f2cmutex__trylock(this, cause) != 0) ? boolean__true : boolean__false;
}

f2ptr f2__cmutex__trylock(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__cmutex__trylock(cause, this));
}
def_pcfunk1(cmutex__trylock, this,
	    "",
	    return f2__cmutex__trylock(this_cause, this));

boolean_t raw__cmutex__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__cmutex__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__cmutex__eq(cause, this, that));
}
def_pcfunk2(cmutex__eq, this, that,
	    "",
	    return f2__cmutex__eq(this_cause, this, that));

u64 raw__cmutex__eq_hash_value(f2ptr cause, f2ptr this) {
  return ((u64)this);
}

f2ptr f2__cmutex__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__cmutex__eq_hash_value(cause, this));}
def_pcfunk1(cmutex__eq_hash_value, this,
	    "",
	    return f2__cmutex__eq_hash_value(this_cause, this));

boolean_t raw__cmutex__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__cmutex__eq(cause, this, that);}

f2ptr f2__cmutex__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__equals(cause, this, that));
}
def_pcfunk2(cmutex__equals, this, that,
	    "",
	    return f2__cmutex__equals(this_cause, this, that));


u64 raw__cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  funk2_processor_mutex_t* m = __pure__f2cmutex__m(this);
  return funk2_processor_mutex__equals_hash_value(m);
}

f2ptr f2__cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(cmutex, this);
  return f2integer__new(cause, raw__cmutex__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(cmutex__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__cmutex__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__cmutex__equals_hash_value(f2ptr cause, f2ptr this) {
  funk2_processor_mutex_t* m = __pure__f2cmutex__m(this);
  return funk2_processor_mutex__equals_hash_value(m);
}

f2ptr f2__cmutex__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2integer__new(cause, raw__cmutex__equals_hash_value(cause, this));
}
def_pcfunk1(cmutex__equals_hash_value, this,
	    "",
	    return f2__cmutex__equals_hash_value(this_cause, this));


f2ptr raw__cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t cmutex_string[128];
  u64               cmutex_string__length;
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__cmutex__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__left_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "cmutex ");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "is_locked ");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, f2bool__new(f2cmutex__is_locked(this, cause)), terminal_print_frame);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
    return nil;
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__cmutex__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__right_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cmutex,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cmutex__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cmutex__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__cmutex__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__cmutex__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk;
    }
  }
  return nil;
}

f2ptr f2cmutex__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk);}
  {char* slot_name = "trylock";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk);}
  {char* slot_name = "unlock";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk);}
  {char* slot_name = "is_locked";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__funk);}
  return this;
}



// char

f2ptr ptype_char__new(int pool_index, f2ptr cause, funk2_character_t ch) {
  f2ptr char_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_char_block_t));
  ptype_char_block_t* char_block = (ptype_char_block_t*)from_ptr(raw__f2ptr_to_ptr(char_f2ptr));
  debug__assert(char_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  char_block->ptype.block.ptype = ptype_char;
  char_block->ptype.cause       = cause;
  char_block->ch                = ch;
  return char_f2ptr;
}

f2ptr pfunk2__f2char__new(f2ptr cause, funk2_character_t ch) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2char__new(pool_index, cause, ch);
  return retval;
}

funk2_character_t pfunk2__f2char__ch(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_char) {
    ptype_error(cause, this, __funk2.globalenv.ptype_char__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 ch = __pure__f2char__ch(this);
  return ch;
}

boolean_t raw__char__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_char);
}
f2ptr f2__char__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__char__is_type(cause, x));}
def_pcfunk1(char__is_type, x,
	    "",
	    return f2__char__is_type(this_cause, x));

f2ptr f2__char__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "char");}
def_pcfunk1(char__type, this,
	    "",
	    return f2__char__type(this_cause, this));

def_pcfunk1(char__new, ch,
	    "",
	    return f2char__new(this_cause, f2char__ch(ch, this_cause)));

funk2_character_t raw__char__ch(f2ptr cause, f2ptr this) {
  return f2char__ch(this, cause);
}

f2ptr f2__char__ch(f2ptr cause, f2ptr this) {
  return f2char__new(cause, raw__char__ch(cause, this));
}
def_pcfunk1(char__ch, this,
	    "",
	    return f2__char__ch(this_cause, this));

boolean_t raw__char__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2char__ch(this, cause) == f2char__ch(that, cause);
}

f2ptr f2__char__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__char__eq(cause, this, that));
}
def_pcfunk2(char__eq, this, that,
	    "",
	    return f2__char__eq(this_cause, this, that));

u64 raw__char__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2char__ch(this, cause);}

f2ptr f2__char__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__char__eq_hash_value(cause, this));}
def_pcfunk1(char__eq_hash_value, this,
	    "",
	    return f2__char__eq_hash_value(this_cause, this));

boolean_t raw__char__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__char__eq(cause, this, that);}

f2ptr f2__char__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(char, this);
  return f2bool__new(raw__char__equals(cause, this, that));
}
def_pcfunk2(char__equals, this, that,
	    "",
	    return f2__char__equals(this_cause, this, that));


u64 raw__char__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__char__eq_hash_value(cause, this);
}

f2ptr f2__char__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(char,      this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__char__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(char__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__char__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__char__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__char__eq_hash_value(cause, this);
}

f2ptr f2__char__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(char, this);
  return f2integer__new(cause, raw__char__equals_hash_value(cause, this));
}
def_pcfunk1(char__equals_hash_value, this,
	    "",
	    return f2__char__equals_hash_value(this_cause, this));


f2ptr raw__char__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t char_string[128];
  u64               char_string__length;
  funk2_character_t ch = f2char__ch(this, cause);
  if (ch >= 28) {
    char_string__length = 3;
    char_string[0] = f2char__ch(__funk2.reader.char__escape, cause);
    char_string[1] = f2char__ch(__funk2.reader.char__escape_char, cause);
    char_string[2] = ch;
    char_string[3] = 0;
  } else {
    char_string__length = 2;
    char_string[0] = f2char__ch(__funk2.reader.char__escape, cause);
    char_string[1] = f2char__ch(__funk2.reader.char__escape_hex_char, cause);
    {
      char temp_str[128];
      u64  temp_str__length = snprintf(temp_str, 128, "%X", (uint)ch);
      {
	u64 index;
	for (index = 0; index < temp_str__length; index ++) {
	  char_string[2 + index] = temp_str[index];
	}
      }
      char_string__length += temp_str__length;
    }
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__char__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, char_string__length, char_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__char__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(char,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__char__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(char__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__char__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__char__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.ch__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.new__funk;
    }
  }
  return nil;
}

f2ptr f2char__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.new__funk);}
  {char* slot_name = "ch";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.ch__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__funk);}
  return this;
}


// string

f2ptr ptype_string__new(int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  f2ptr                 string_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_string_block_t) + ((length + 1) * sizeof(funk2_character_t)));
  ptype_string_block_t* string_block = (ptype_string_block_t*)from_ptr(raw__f2ptr_to_ptr(string_f2ptr));
  debug__assert(string_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  string_block->ptype.block.ptype = ptype_string;
  string_block->ptype.cause       = cause;
  string_block->length            = length;
  if (str) {memcpy(string_block->str, str, length * sizeof(funk2_character_t));}
  else     {memset(string_block->str, 0,   length * sizeof(funk2_character_t));}
  string_block->str[length] = 0;
  return string_f2ptr;
}

f2ptr pfunk2__f2string__new(f2ptr cause, u64 length, funk2_character_t* init) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2string__new(pool_index, cause, length, init);
  return retval;
}

u64 pfunk2__f2string__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  length = __pure__f2string__length(this);
  return length;
}

funk2_character_t pfunk2__f2string__elt(f2ptr this, int index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_character_t ch = __pure__f2string__str(this)[index];
  return ch;
}

void pfunk2__f2string__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2string__str(this), __pure__f2string__length(this) * sizeof(funk2_character_t));
}

void raw__string__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str) {
  f2string__str_copy(this, cause, str);
}

u64 pfunk2__f2string__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return (u64)this;
}

boolean_t raw__string__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_string);
}
f2ptr f2__string__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__string__is_type(cause, x));}
f2ptr f2__string__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "string");}

u64   raw__string__length(f2ptr cause, f2ptr this) {return f2string__length(this, cause);}
f2ptr  f2__string__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__string__length(cause, this));}

funk2_character_t raw__string__elt(f2ptr cause, f2ptr this, s64 index) {
  if (index < 0) {
    return f2larva__new(cause, 2, nil);
  }
  u64 length = f2string__length(this, cause);
  if (index >= length) {
    return f2larva__new(cause, 2, nil);
  }
  return f2string__elt(this, index, cause);
}

f2ptr f2__string__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(string, this);
  u64 raw_index = f2integer__i(index, cause);
  return f2char__new(cause, raw__string__elt(cause, this, raw_index));
}


boolean_t raw__string__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__string__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  return f2bool__new(raw__string__eq(cause, this, that));
}
def_pcfunk2(string__eq, this, that,
	    "",
	    return f2__string__eq(this_cause, this, that));


u64 raw__string__eq_hash_value(f2ptr cause, f2ptr this) {
  return f2string__eq_hash_value(this, cause);
}

f2ptr f2__string__eq_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return f2integer__new(cause, raw__string__eq_hash_value(cause, this));
}
def_pcfunk1(string__eq_hash_value, this,
	    "",
	    return f2__string__eq_hash_value(this_cause, this));


f2ptr f2__string__new(f2ptr cause, f2ptr str) {
  assert_argument_type(string, str);
  int str__length = f2string__length(str, cause);
  if (str__length < 0) {
    error(nil, "f2__string__new error: initial string length is less than zero.");
  }
  funk2_character_t* str__data = (funk2_character_t*)alloca(str__length * sizeof(funk2_character_t));
  f2string__str_copy(str, cause, str__data);
  return f2string__new(cause, str__length, str__data);
}

def_pcfunk1(string__is_type, x,
	    "",
	    return f2__string__is_type(this_cause, x));
def_pcfunk1(string__type, x,
	    "",
	    return f2__string__type(this_cause, x));
def_pcfunk1(string__new, str,
	    "",
	    return f2__string__new(this_cause, str));
def_pcfunk1(string__length, this,
	    "",
	    return f2__string__length(this_cause, this));
def_pcfunk2(string__elt, this, index,
	    "",
	    return f2__string__elt(this_cause, this, index));


u64 raw__string__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  f2ptr previous_equals_hash_value = raw__ptypehash__lookup(cause, node_ptypehash, this);
  if (previous_equals_hash_value != nil) {
    u64 previous_equals_hash_value__i = f2integer__i(previous_equals_hash_value, cause);
    return previous_equals_hash_value__i;
  }
  u64                len = f2string__length(this, cause);
  funk2_character_t* str = (funk2_character_t*)from_ptr(f2__malloc(len * sizeof(funk2_character_t)));
  f2string__str_copy(this, cause, str);
  u64 retval = (u64)character_array__hash_value(len, str);
  f2__free(to_ptr(str));
  raw__ptypehash__add(cause, node_ptypehash, this, f2integer__new(cause, retval));
  return retval;
}

f2ptr f2__string__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(string,    this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__string__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(string__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__string__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__string__equals_hash_value(f2ptr cause, f2ptr this) {
  u64 len                = f2string__length(this, cause);
  funk2_character_t* str = (funk2_character_t*)from_ptr(f2__malloc(len * sizeof(funk2_character_t)));
  f2string__str_copy(this, cause, str);
  u64 retval = (u64)character_array__hash_value(len, str);
  f2__free(to_ptr(str));
  return retval;
}

f2ptr f2__string__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return f2integer__new(cause, raw__string__equals_hash_value(cause, this));
}
def_pcfunk1(string__equals_hash_value, this,
	    "",
	    return f2__string__equals_hash_value(this_cause, this));


boolean_t raw__string__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__string__is_type(cause, that)) {
    return boolean__false;
  }
  u64 this_len = f2string__length(this, cause);
  u64 that_len = f2string__length(that, cause);
  if (this_len != that_len) {
    return nil;
  }
  u64                both_len = this_len;
  funk2_character_t* this_str = alloca(both_len * sizeof(funk2_character_t));
  funk2_character_t* that_str = alloca(both_len * sizeof(funk2_character_t));
  f2string__str_copy(this, cause, this_str);
  f2string__str_copy(that, cause, that_str);
  return (memcmp(this_str, that_str, both_len * sizeof(funk2_character_t)) == 0);
}

f2ptr f2__string__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  return f2bool__new(raw__string__equals(cause, this, that));
}
def_pcfunk2(string__equals, this, that,
	    "",
	    return f2__string__equals(this_cause, this, that));


u64 raw__string__utf8_length(f2ptr cause, f2ptr this) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__string__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      utf8_str__index += utf8_code__length;
    }
  }
  f2__free(to_ptr(str));
  return utf8_str__index;
}


void raw__string__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__string__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      u8  utf8_code[6];       funk2_character__utf8_str_copy(str[index], utf8_code);
      {
	u64 utf8_code__index;
	for (utf8_code__index = 0; utf8_code__index < utf8_code__length; utf8_code__index ++) {
	  utf8_str[utf8_str__index] = utf8_code[utf8_code__index]; utf8_str__index ++;
	}
      }
    }
  }
  f2__free(to_ptr(str));
}


f2size_t raw__utf8_char__parse_character(char* utf8_string, funk2_character_t* result) {
  funk2_character_t ch0 = utf8_string[0];
  if ((ch0 & 0x80) == 0) {
    // normal ascii
    if (result != NULL) {
      *result = ch0;
    }
    return 1;
  } else if ((ch0 & 0x40) != 0) {
    if ((ch0 & 0x20) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	if (result != NULL) {
	  *result = ((ch0 & 0x1f) << 6) | (ch1 & 0x3f);
	}
	return 2;
      }
    } else if ((ch0 & 0x10) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  if (result != NULL) {
	    *result = ((ch0 & 0x0f) << 12) | ((ch1 & 0x3f) << 6) | (ch2 & 0x3f);
	  }
	  return 3;
	}
      }
    } else if ((ch0 & 0x08) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  funk2_character_t ch3 = utf8_string[3];
	  if ((ch3 & 0xc0) == 0x80) {
	    if (result != NULL) {
	      *result = ((ch0 & 0x07) << 18) | ((ch1 & 0x3f) << 12) | ((ch2 & 0x3f) << 6) | (ch3 & 0x3f);
	    }
	    return 4;
	  }
	}
      }
    } else if ((ch0 & 0x04) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  funk2_character_t ch3 = utf8_string[3];
	  if ((ch3 & 0xc0) == 0x80) {
	    funk2_character_t ch4 = utf8_string[4];
	    if ((ch4 & 0xc0) == 0x80) {
	      if (result != NULL) {
		*result = ((ch0 & 0x03) << 24) | ((ch1 & 0x3f) << 18) | ((ch2 & 0x3f) << 12) | ((ch3 & 0x3f) << 6) | (ch4 & 0x3f);
	      }
	      return 5;
	    }
	  }
	}
      }
    } else if ((ch0 & 0x02) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  funk2_character_t ch3 = utf8_string[3];
	  if ((ch3 & 0xc0) == 0x80) {
	    funk2_character_t ch4 = utf8_string[4];
	    if ((ch4 & 0xc0) == 0x80) {
	      funk2_character_t ch5 = utf8_string[5];
	      if ((ch5 & 0xc0) == 0x80) {
		if (result != NULL) {
		  *result = ((ch0 & 0x01) << 30) | ((ch1 & 0x3f) << 24) | ((ch2 & 0x3f) << 18) | ((ch3 & 0x3f) << 12) | ((ch4 & 0x3f) << 6) | (ch5 & 0x3f);
		}
		return 6;
	      }
	    }
	  }
	}
      }
    }
  }
  if (result != NULL) {
    *result = (funk2_character_t)'?';
  }
  return 1;
}

f2size_t raw__utf8_char__utf8_length(char* utf8_char) {
  return raw__utf8_char__parse_character(utf8_char, NULL);
}


u64 raw__utf8_string__length(char* utf8_string) {
  u64 length = 0;
  do {
    funk2_character_t ch;
    utf8_string += raw__utf8_char__parse_character(utf8_string, &ch);
    if (ch == 0) {
      return length;
    }
    length ++;
  } while (1);
}

void raw__utf8_string__str_copy(char* utf8_string, funk2_character_t* str) {
  u64 index = 0;
  do {
    funk2_character_t ch;
    utf8_string += raw__utf8_char__parse_character(utf8_string, &ch);
    if (ch == 0) {
      return;
    }
    str[index] = ch;
    index++;
  } while (1);
}


f2ptr raw__string__new_from_utf8(f2ptr cause, char* utf8_string) {
  u64                utf8_string__length = raw__utf8_string__length(utf8_string);
  funk2_character_t* utf8_string__str    = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (utf8_string__length + 1)));
  raw__utf8_string__str_copy(utf8_string, utf8_string__str);
  f2ptr new = f2string__new(cause, utf8_string__length, utf8_string__str);
  f2__free(to_ptr(utf8_string__str));
  return new;
}



f2ptr raw__string__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr              size                  = f2__terminal_print_frame__size(cause, terminal_print_frame);
  u64                size__i               = f2integer__i(size, cause);
  f2ptr              max_size              = f2__terminal_print_frame__max_size(cause, terminal_print_frame);
  u64                max_size__i           = f2integer__i(max_size, cause);
  f2ptr              use_one_line          = f2__terminal_print_frame__use_one_line(cause, terminal_print_frame);
  u64                string__length        = raw__string__length(cause, this);
  funk2_character_t* string__str           = (funk2_character_t*)from_ptr(f2__malloc((string__length + 1)          * sizeof(funk2_character_t))); raw__string__str_copy(cause, this, string__str); string__str[string__length] = 0;
  funk2_character_t* string_string         = (funk2_character_t*)from_ptr(f2__malloc(((string__length << 1) + 128) * sizeof(funk2_character_t)));
  string_string[0]                         = f2char__ch(__funk2.reader.char__string_quote, cause);
  u64                string_string__length = 1;
  {
    u64 size_index = 0;
    u64 index      = 0;
    while ((index < string__length) && (size__i < max_size__i)) {
      for (size_index = 0; (size_index < 8) && (index < string__length); index ++, size_index ++) {
	funk2_character_t ch = string__str[index];
	if (ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_quote, cause);
	  string_string__length ++;
	} else if ((use_one_line != nil) && (ch == (funk2_character_t)'\n')) {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_newline, cause);
	  string_string__length ++;
	} else if (ch == f2char__ch(__funk2.reader.char__escape_char, cause)) {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	} else if (ch == (funk2_character_t)'\r') {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_return, cause);
	  string_string__length ++;
	} else if (ch == (funk2_character_t)'\t') {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_tab, cause);
	  string_string__length ++;
	} else if (ch == (funk2_character_t)'\b') {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_backspace, cause);
	  string_string__length ++;
	} else {
	  string_string[string_string__length] = ch;
	  string_string__length ++;
	}
      }
      size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
    }
    if (index < string__length) {
      string_string[string_string__length] = (funk2_character_t)'.'; string_string__length ++;
      string_string[string_string__length] = (funk2_character_t)'.'; string_string__length ++;
      string_string[string_string__length] = (funk2_character_t)'.'; string_string__length ++;
      f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
    }
  }
  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_quote, cause);
  string_string__length ++;
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__string__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, string_string__length, string_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  f2__free(to_ptr(string__str));
  f2__free(to_ptr(string_string));
  return nil;
}

f2ptr f2__string__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(string,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__string__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(string__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__string__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__string__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.new__funk;
    }
  }
  return nil;
}

f2ptr f2string__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.new__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.length__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.elt__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__funk);}
  return this;
}



// symbol

f2ptr ptype_symbol__new(int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  if (length == 0) {
    return nil;
  }
  return funk2_symbol_hash__lookup_or_create_symbol(&(__funk2.ptypes.symbol_hash), pool_index, cause, length, str);
}

f2ptr pfunk2__f2symbol__new(f2ptr cause, u64 length, funk2_character_t* init) {
  check_wait_politely();
  int   pool_index = this_processor_thread__pool_index();
  f2ptr retval     = __pure__f2symbol__new(pool_index, cause, length, init);
  return retval;
}

u64 pfunk2__f2symbol__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2symbol__length(this);
  return length;
}

u64 pfunk2__f2symbol__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 eq_hash_value = __pure__f2symbol__eq_hash_value(this);
  return eq_hash_value;
}

funk2_character_t pfunk2__f2symbol__elt(f2ptr this, int index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_character_t ch = __pure__f2symbol__str(this)[index];
  return ch;
}

void pfunk2__f2symbol__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2symbol__str(this), __pure__f2symbol__length(this) * sizeof(funk2_character_t));
}

void raw__symbol__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str) {
  f2symbol__str_copy(this, cause, str);
}

boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_symbol);
}
f2ptr f2__symbol__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__symbol__is_type(cause, x));}
f2ptr f2__symbol__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "symbol");}

u64   raw__symbol__length(f2ptr cause, f2ptr this) {return f2symbol__length(this, cause);}
f2ptr  f2__symbol__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__symbol__length(cause, this));}

// this looks like a bug, but doing a big replacement -bo
f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2symbol__elt(x, f2integer__i(y, cause), cause));}

u64   raw__symbol__eq_hash_value(f2ptr cause, f2ptr this) {return f2symbol__eq_hash_value(this, cause);}
f2ptr  f2__symbol__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__symbol__eq_hash_value(cause, this));}
def_pcfunk1(symbol__eq_hash_value, this,
	    "",
	    return f2__symbol__eq_hash_value(this_cause, this));

f2ptr f2__symbol__new(f2ptr cause, f2ptr str) {
  assert_argument_type(string, str);
  int str__length = f2string__length(str, cause);
  if (str__length < 0) {
    error(nil, "f2__symbol__new error: initial string length is less than zero.");
  }
  funk2_character_t* str__data = (funk2_character_t*)alloca(str__length * sizeof(funk2_character_t));
  f2string__str_copy(str, cause, str__data);
  return f2symbol__new(cause, str__length, str__data);
}

boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (raw__symbol__is_type(cause, this)) {
    if (this == that) {
      return boolean__true;
    }
  } else {
    return boolean__false;
  }
  if (! raw__symbol__is_type(cause, that)) {return boolean__false;}
  u64 this__length = f2symbol__length(this, cause);
  u64 that__length = f2symbol__length(that, cause);
  if (this__length != that__length) {
    return boolean__false;
  }
  funk2_character_t* this__str = (funk2_character_t*)alloca((this__length + 1) * sizeof(funk2_character_t));
  funk2_character_t* that__str = (funk2_character_t*)alloca((that__length + 1) * sizeof(funk2_character_t));
  f2symbol__str_copy(this, cause, this__str);
  f2symbol__str_copy(that, cause, that__str);
  if (memcmp(this__str, that__str, this__length * sizeof(funk2_character_t)) != 0) {
    return boolean__false;
  }
  return boolean__true;
}

f2ptr f2__symbol__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__symbol__eq(cause, this, that));
}
def_pcfunk2(symbol__eq, x, y,
	    "",
	    return f2__symbol__eq(this_cause, x, y));


boolean_t raw__symbol__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__symbol__eq(cause, this, that);
}

f2ptr f2__symbol__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(symbol, this);
  return f2bool__new(raw__symbol__equals(cause, this, that));
}
def_pcfunk2(symbol__equals, this, that,
	    "",
	    return f2__symbol__equals(this_cause, this, that));


u64 raw__symbol__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__symbol__eq_hash_value(cause, this);
}

f2ptr f2__symbol__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(symbol,    this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__symbol__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(symbol__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__symbol__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__symbol__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__symbol__eq_hash_value(cause, this);
}

f2ptr f2__symbol__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(symbol, this);
  return f2integer__new(cause, raw__symbol__equals_hash_value(cause, this));
}
def_pcfunk1(symbol__equals_hash_value, this,
	    "",
	    return f2__symbol__equals_hash_value(this_cause, this));


def_pcfunk1(symbol__is_type, x,
	    "",
	    return f2__symbol__is_type(this_cause, x));
def_pcfunk1(symbol__type, x,
	    "",
	    return f2__symbol__type(this_cause, x));
def_pcfunk1(symbol__new, str,
	    "",
	    return f2__symbol__new(this_cause, str));
def_pcfunk1(symbol__length, this,
	    "",
	    return f2__symbol__length(this_cause, this));
def_pcfunk2(symbol__elt, this, index,
	    "",
	    return f2__symbol__elt(this_cause, this, index));


u64 raw__symbol__utf8_length(f2ptr cause, f2ptr this) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__symbol__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__symbol__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      utf8_str__index += utf8_code__length;
    }
  }
  f2__free(to_ptr(str));
  return utf8_str__index;
}


void raw__symbol__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__symbol__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__symbol__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      u8  utf8_code[6];       funk2_character__utf8_str_copy(str[index], utf8_code);
      {
	u64 utf8_code__index;
	for (utf8_code__index = 0; utf8_code__index < utf8_code__length; utf8_code__index ++) {
	  utf8_str[utf8_str__index] = utf8_code[utf8_code__index]; utf8_str__index ++;
	}
      }
    }
  }
  f2__free(to_ptr(str));
}


f2ptr raw__symbol__new_from_utf8(f2ptr cause, char* utf8_string) {
  u64                utf8_string__length = raw__utf8_string__length(utf8_string);
  funk2_character_t* utf8_string__str    = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (utf8_string__length + 1)));
  raw__utf8_string__str_copy(utf8_string, utf8_string__str);
  f2ptr new = f2symbol__new(cause, utf8_string__length, utf8_string__str);
  f2__free(to_ptr(utf8_string__str));
  return new;
}


f2ptr raw__symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  u64                symbol__length     = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str        = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  boolean_t          symbol_needs_quote = boolean__false;
  {
    u64 index;
    for (index = 0; index < symbol__length; index ++) {
      funk2_character_t ch = symbol__str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	symbol_needs_quote = boolean__true;
	break;
      }
    }
  }
  if (symbol_needs_quote) {
    funk2_character_t* symbol_string = (funk2_character_t*)from_ptr(f2__malloc(((symbol__length << 1) + 128) * sizeof(funk2_character_t)));
    symbol_string[0]                 = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    u64 symbol_string__length = 1;
    {
      u64 index;
      for (index = 0; index < symbol__length; index ++) {
	funk2_character_t ch = symbol__str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  symbol_string__length ++;
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
	  symbol_string__length ++;
	} else {
	  symbol_string[symbol_string__length] = ch;
	  symbol_string__length ++;
	}
      }
    }
    symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    symbol_string__length ++;
    if ((symbol__length > 0) && (symbol__str[0] == f2char__ch(__funk2.reader.char__symbol_key, cause))) {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    } else {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
    }
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol_string__length, symbol_string);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
    f2__free(to_ptr(symbol_string));
  } else {
    if ((symbol__length > 0) && (symbol__str[0] == f2char__ch(__funk2.reader.char__symbol_key, cause))) {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    } else {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
    }
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol__length, symbol__str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  f2__free(to_ptr(symbol__str));
  return nil;
}

f2ptr f2__symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(symbol,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__symbol__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(symbol__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__symbol__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr raw__key_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  u64                symbol__length     = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str        = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  boolean_t          symbol_needs_quote = boolean__false;
  {
    u64 index;
    for (index = 0; index < symbol__length; index ++) {
      char ch = symbol__str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	symbol_needs_quote = boolean__true;
	break;
      }
    }
  }
  if (symbol_needs_quote) {
    funk2_character_t* symbol_string = (funk2_character_t*)from_ptr(f2__malloc(((symbol__length << 1) + 128) * sizeof(funk2_character_t)));
    symbol_string[0]                 = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    u64 symbol_string__length = 1;
    {
      u64 index;
      for (index = 0; index < symbol__length; index ++) {
	funk2_character_t ch = symbol__str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  symbol_string__length ++;
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
	  symbol_string__length ++;
	} else {
	  symbol_string[symbol_string__length] = ch;
	  symbol_string__length ++;
	}
      }
    }
    symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    symbol_string__length ++;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol_string__length, symbol_string);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
    f2__free(to_ptr(symbol_string));
  } else {
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol__length, symbol__str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  f2__free(to_ptr(symbol__str));
  return nil;
}


f2ptr raw__type_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  u64                symbol__length     = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str        = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  boolean_t          symbol_needs_quote = boolean__false;
  {
    u64 index;
    for (index = 0; index < symbol__length; index ++) {
      funk2_character_t ch = symbol__str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	symbol_needs_quote = boolean__true;
	break;
      }
    }
  }
  if (symbol_needs_quote) {
    funk2_character_t* symbol_string = (funk2_character_t*)from_ptr(f2__malloc(((symbol__length << 1) + 128) * sizeof(funk2_character_t)));
    symbol_string[0]                 = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    u64 symbol_string__length = 1;
    {
      u64 index;
      for (index = 0; index < symbol__length; index ++) {
	funk2_character_t ch = symbol__str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  symbol_string__length ++;
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
	  symbol_string__length ++;
	} else {
	  symbol_string[symbol_string__length] = ch;
	  symbol_string__length ++;
	}
      }
    }
    symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    symbol_string__length ++;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol_string__length, symbol_string);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
    f2__free(to_ptr(symbol_string));
  } else {
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol__length, symbol__str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  f2__free(to_ptr(symbol__str));
  return nil;
}


f2ptr raw__symbol__as__string(f2ptr cause, f2ptr this) {
  u64                symbol__length = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str    = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  f2ptr              string         = f2string__new(cause, symbol__length, symbol__str);
  f2__free(to_ptr(symbol__str));
  return string;
}

f2ptr f2__symbol__as__string(f2ptr cause, f2ptr this) {
  assert_argument_type(symbol, this);
  return raw__symbol__as__string(cause, this);
}
def_pcfunk1(symbol__as__string, this,
	    "",
	    return f2__symbol__as__string(this_cause, this));


f2ptr f2__symbol__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk;
    }
  }
  return nil;
}

f2ptr f2symbol__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk);}
  {char* slot_name = "length";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk);}
  {char* slot_name = "elt";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__funk);}
  {char* slot_name = "as-string";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.as__string__funk);}
  return this;
}



// chunk

f2ptr ptype_chunk__new(int pool_index, f2ptr cause, u64 length, byte* bytes) {
  u64 data_byte_num = (sizeof(u8) * length);
  f2ptr chunk_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_chunk_block_t) + data_byte_num);
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  chunk_block->ptype.block.ptype = ptype_chunk;
  chunk_block->ptype.cause       = cause;
  chunk_block->length            = length;
  if (bytes) {memcpy(chunk_block->bytes, bytes, data_byte_num);}
  else       {memset(chunk_block->bytes, 0,     data_byte_num);}
  return chunk_f2ptr;
}

f2ptr ptype_chunk__new_copy(int pool_index, f2ptr cause, f2ptr init_chunk) {
  ptype_chunk_block_t* init_chunk_block = (ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(init_chunk)));
  u64 data_byte_num = (sizeof(u8) * init_chunk_block->length);
  f2ptr chunk_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_chunk_block_t));
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  chunk_block->ptype.block.ptype = ptype_chunk;
  chunk_block->ptype.cause       = cause;
  chunk_block->length            = init_chunk_block->length;
  memcpy(chunk_block->bytes, init_chunk_block->bytes, data_byte_num);
  return chunk_f2ptr;
}

u8* ptype_chunk__bytes(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8* bytes = __pure__f2chunk__bytes(this);
  return bytes;
}

f2ptr pfunk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2chunk__new(pool_index, cause, length, bytes);
  return retval;
}

f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2chunk__new_copy(pool_index, cause, init_chunk);
  return retval;
}

u64 pfunk2__f2chunk__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2chunk__length(this);
  return length;
}

void pfunk2__f2chunk__str_copy(f2ptr this, f2ptr cause, u8* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2chunk__bytes(this), __pure__f2chunk__length(this));
}

void raw__chunk__str_copy(f2ptr cause, f2ptr this, u8* str) {
  f2chunk__str_copy(this, cause, str);
}

u64 pfunk2__f2chunk__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return (u64)this;
}

u64 pfunk2__f2chunk__equals_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 len   = __pure__f2chunk__length(this);
  u8* bytes = __pure__f2chunk__bytes(this);
  return (u64)chararray__hash_value(len, bytes);
}

u8 pfunk2__f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8 retval = __pure__f2chunk__bit8__elt(this, index);
  return retval;
}

void  pfunk2__f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value)   {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
  __pure__f2chunk__bit8__elt__set(this, index, value);
}

u16 pfunk2__f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u16 retval = __pure__f2chunk__bit16__elt(this, index);
  return retval;
}

void pfunk2__f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit16__elt__set(this, index, value);
}

u32 pfunk2__f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 retval = __pure__f2chunk__bit32__elt(this, index);
  return retval;
}

void pfunk2__f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit32__elt__set(this, index, value);
}

u64 pfunk2__f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 retval = __pure__f2chunk__bit64__elt(this, index);
  return retval;
}

void pfunk2__f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit64__elt__set(this, index, value);
}

f2ptr pfunk2__f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr fiber, f2ptr env, f2ptr args) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  cfunkptr_t jump = (cfunkptr_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  printf("\nchunk-cfunk_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  return jump(cause, fiber, env, args);
}

int pfunk2__f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr fiber) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  bytecode_jump_t jump = (bytecode_jump_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  //printf("\nchunk-bytecode_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  f2ptr bytecode = nil;
  return jump(fiber, bytecode);
}

f2ptr pfunk2__f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = f2integer__new(cause, send(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  return rv;
}

f2ptr pfunk2__f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = f2integer__new(cause, recv(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  return rv;
}

f2ptr raw__chunk__new(f2ptr cause, u64 length) {
  return f2chunk__new(cause, length, NULL);
}

f2ptr f2__chunk__new(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return f2larva__new(cause, 220101, nil);
  }
  return raw__chunk__new(cause, length__i);
}

boolean_t raw__chunk__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if ((!cause) || (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_chunk);
}
f2ptr f2__chunk__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__chunk__is_type(cause, x));}
f2ptr f2__chunk__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "chunk");}

u64 raw__chunk__length(f2ptr cause, f2ptr this) {
  return f2chunk__length(this, cause);
}

f2ptr f2__chunk__length(f2ptr cause, f2ptr this) {
  assert_argument_type(chunk, this);
  return f2integer__new(cause, raw__chunk__length(cause, this));
}

boolean_t raw__chunk__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__chunk__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(chunk, this);
  return f2bool__new(raw__chunk__eq(cause, this, that));
}
def_pcfunk2(chunk__eq, this, that,
	    "",
	    return f2__chunk__eq(this_cause, this, that));

u64   raw__chunk__eq_hash_value(f2ptr cause, f2ptr this) {return f2chunk__eq_hash_value(this, cause);}
f2ptr  f2__chunk__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__chunk__eq_hash_value(this, cause));}
def_pcfunk1(chunk__eq_hash_value, x,
	    "",
	    return f2__chunk__eq_hash_value(this_cause, x));


boolean_t raw__chunk__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__chunk__eq(cause, this, that);
}

f2ptr f2__chunk__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(chunk, this);
  return f2bool__new(raw__chunk__equals(cause, this, that));
}
def_pcfunk2(chunk__equals, this, that,
	    "",
	    return f2__chunk__equals(this_cause, this, that));


u64 raw__chunk__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  f2ptr previous_hash_value = raw__ptypehash__lookup(cause, node_ptypehash, this);
  if (previous_hash_value != nil) {
    u64 previous_hash_value__i = f2integer__i(previous_hash_value, cause);
    return previous_hash_value__i;
  }
  u64 hash_value__i = f2chunk__equals_hash_value(this, cause);
  raw__ptypehash__add(cause, node_ptypehash, this, f2integer__new(cause, hash_value__i));
  return hash_value__i;
}

f2ptr f2__chunk__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(chunk,     this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__chunk__equals_hash_value__loop_free(this, cause, node_ptypehash));
}
def_pcfunk2(chunk__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__chunk__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__chunk__equals_hash_value(f2ptr cause, f2ptr this) {
  return f2chunk__equals_hash_value(this, cause);
}

f2ptr f2__chunk__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(chunk, this);
  return f2integer__new(cause, raw__chunk__equals_hash_value(this, cause));
}
def_pcfunk1(chunk__equals_hash_value, x,
	    "",
	    return f2__chunk__equals_hash_value(this_cause, x));


def_pcfunk1(chunk__is_type, x,
	    "",
	    return f2__chunk__is_type(this_cause, x));

def_pcfunk1(chunk__type, x,
	    "",
	    return f2__chunk__type(this_cause, x));

def_pcfunk1(chunk__new, length,
	    "",
	    return f2__chunk__new(this_cause, length));

def_pcfunk1(chunk__length, x,
	    "",
	    return f2__chunk__length(this_cause, x));

u8 raw__chunk__bit8__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit8__elt(this, index, cause);
}

f2ptr f2__chunk__bit8__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  return f2pointer__new(cause, raw__chunk__bit8__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit8__elt, this, index,
	    "",
	    return f2__chunk__bit8__elt(this_cause, this, index));


void raw__chunk__bit8__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit8__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit8__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  s64 value__p = f2pointer__p(value, cause);
  if ((value__p < 0) || (value__p >= (((u64)1) << 8))) {
    return f2larva__new(cause, 3, nil);
  }
  raw__chunk__bit8__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit8__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit8__elt__set(this_cause, this, index, value));


u16 raw__chunk__bit16__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit16__elt(this, index, cause);
}

f2ptr f2__chunk__bit16__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  return f2pointer__new(cause, raw__chunk__bit16__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit16__elt, this, index,
	    "",
	    return f2__chunk__bit16__elt(this_cause, this, index));


void raw__chunk__bit16__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit16__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit16__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  s64 value__p = f2pointer__p(value, cause);
  if ((value__p < 0) || (value__p >= (((u64)1) << 16))) {
    return f2larva__new(cause, 3, nil);
  }
  raw__chunk__bit16__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit16__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit16__elt__set(this_cause, this, index, value));

//def_pcfunk2(chunk__bit16__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit16__elt(this, this_cause, f2integer__i(index, this_cause))));
//def_pcfunk3(chunk__bit16__elt__set, this, index, value, f2chunk__bit16__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);


u32 raw__chunk__bit32__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit32__elt(this, index, cause);
}

f2ptr f2__chunk__bit32__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  return f2pointer__new(cause, raw__chunk__bit32__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit32__elt, this, index,
	    "",
	    return f2__chunk__bit32__elt(this_cause, this, index));


void raw__chunk__bit32__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit32__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit32__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  s64 value__p = f2pointer__p(value, cause);
  if ((value__p < 0) || (value__p >= (((u64)1) << 32))) {
    return f2larva__new(cause, 3, nil);
  }
  raw__chunk__bit32__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit32__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit32__elt__set(this_cause, this, index, value));

//def_pcfunk2(chunk__bit32__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit32__elt(this, this_cause, f2integer__i(index, this_cause))));
//def_pcfunk3(chunk__bit32__elt__set, this, index, value, f2chunk__bit32__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);


u64 raw__chunk__bit64__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit64__elt(this, index, cause);
}

f2ptr f2__chunk__bit64__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  return f2pointer__new(cause, raw__chunk__bit64__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit64__elt, this, index,
	    "",
	    return f2__chunk__bit64__elt(this_cause, this, index));


void raw__chunk__bit64__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit64__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit64__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return f2larva__new(cause, 2, nil);
  }
  s64 value__p = f2pointer__p(value, cause);
  // don't need to check range here because 64 bits is the size of our pointer object.
  raw__chunk__bit64__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit64__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit64__elt__set(this_cause, this, index, value));

//def_pcfunk2(chunk__bit64__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit64__elt(this, this_cause, f2integer__i(index, this_cause))));
//def_pcfunk3(chunk__bit64__elt__set, this, index, value, f2chunk__bit64__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);


def_pcfunk4(chunk__cfunk_jump, this, fiber, env, args,
	    "",
	    return f2chunk__cfunk_jump(this, this_cause, fiber, env, args));
def_pcfunk2(chunk__bytecode_jump, this, fiber,
	    "",
	    return f2integer__new(this_cause, f2chunk__bytecode_jump(this, this_cause, fiber)));


f2ptr raw__chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr size                     = f2__terminal_print_frame__size(                    cause, terminal_print_frame);
  u64   size__i                  = f2integer__i(size, cause);
  f2ptr x                        = f2__terminal_print_frame__x(                       cause, terminal_print_frame);
  u64   x__i                     = f2integer__i(x, cause);
  f2ptr max_size                 = f2__terminal_print_frame__max_size(                cause, terminal_print_frame);
  u64   max_size__i              = f2integer__i(max_size, cause);
  f2ptr testing                  = f2__terminal_print_frame__testing(                 cause, terminal_print_frame);
  f2ptr testing_max_x_constraint = f2__terminal_print_frame__testing_max_x_constraint(cause, terminal_print_frame);
  f2ptr use_one_line             = f2__terminal_print_frame__use_one_line(            cause, terminal_print_frame);
  f2ptr indent_distance          = f2__terminal_print_frame__indent_distance(         cause, terminal_print_frame);
  u64   indent_distance__i       = f2integer__i(indent_distance, cause);
  {
    indent_distance__i = x__i + 7;
    indent_distance    = f2integer__new(cause, indent_distance__i);
    f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
  }
  f2ptr max_x                = f2__terminal_print_frame__max_x(cause, terminal_print_frame);
  u64   max_x__i             = f2integer__i(max_x, cause);
  u64   chunk__length        = raw__chunk__length(cause, this);
  u64                chunk_string__max_length = (chunk__length * 5) + max_x__i + 128;
  funk2_character_t* chunk_string             = (funk2_character_t*)from_ptr(f2__malloc(chunk_string__max_length * sizeof(funk2_character_t)));
  u64                chunk_string__length     = 0;
  {
    chunk_string[0]      = f2char__ch(__funk2.reader.char__left_paren, cause);
    chunk_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  {
    chunk_string__length = funk2_character_string__snprintf(chunk_string, chunk_string__max_length, "chunk ");
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  {
    chunk_string__length = 0;
    {
      u64 index;
      for (index = 0; index < chunk__length; index ++) {
	if (size__i < max_size__i) {
	  size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
	  u64 increment_distance = funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, "#x%02x", f2chunk__bit8__elt(this, index, cause));
	  chunk_string__length += increment_distance;
	  x__i                 += increment_distance;
	  if (index < (chunk__length - 1)) {
	    if (max_x__i - x__i <= 5) {
	      chunk_string__length += funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, "\n");
	      x__i                  = indent_distance__i;
	      if ((testing != nil) && (testing_max_x_constraint != nil) && (use_one_line != nil)) {
		f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	      }
	    } else {
	      u64 increment_distance = funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, " ");
	      chunk_string__length += increment_distance;
	      x__i                 += increment_distance;
	    }
	  }
	} else {
	  f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	  u64 increment_distance = funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, "...");
	  chunk_string__length += increment_distance;
	  x__i                 += increment_distance;
	  break;
	}
      }
    }
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__pointer__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  {
    chunk_string[0]      = f2char__ch(__funk2.reader.char__right_paren, cause);
    chunk_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  f2__free(to_ptr(chunk_string));
  return nil;
}

f2ptr f2__chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(chunk,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__chunk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(chunk__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__chunk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__chunk__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk;
    }
  }
  return nil;
}

f2ptr f2chunk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk);}
  {char* slot_name = "new_copy";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.new_copy__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk);}
  {char* slot_name = "bit8-elt";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk);}
  {char* slot_name = "bit8-elt";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk);}
  {char* slot_name = "bit16-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk);}
  {char* slot_name = "bit16-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk);}
  {char* slot_name = "bit32-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk);}
  {char* slot_name = "bit32-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk);}
  {char* slot_name = "bit64-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk);}
  {char* slot_name = "bit64-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk);}
  {char* slot_name = "cfunk_jump";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk);}
  {char* slot_name = "bytecode_jump";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__funk);}
  return this;
}


// simple_array

f2ptr ptype_simple_array__new(int pool_index, f2ptr cause, u64 length, ptr f2ptr_ptr) {
  u64 data_byte_num = (sizeof(f2ptr_t) * length);
  f2ptr simple_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_simple_array_block_t) + data_byte_num);
  ptype_simple_array_block_t* simple_array_block = (ptype_simple_array_block_t*)from_ptr(raw__f2ptr_to_ptr(simple_array_f2ptr));
  debug__assert(simple_array_block, nil, "block is nil.");
  //debug__assert(!cause || valid_funk2_memblock_ptr(f2ptr_to_ptr(cause)), nil, "valid_funk2_memblock_ptr(cause) failed");
  if (cause) {raw__exp__increment_reference_count(cause);}
  simple_array_block->ptype.block.ptype = ptype_simple_array;
  simple_array_block->ptype.cause       = cause;
  simple_array_block->immutable         = 0;
  simple_array_block->length            = length;
  if (f2ptr_ptr) {memcpy(simple_array_block->slot, from_ptr(f2ptr_ptr), data_byte_num);}
  else           {memset(simple_array_block->slot, 0,                   data_byte_num);}
  return simple_array_f2ptr;
}

f2ptr pfunk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2simple_array__new(pool_index, cause, length, f2ptr_ptr);
  return this;
}

f2ptr pfunk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(init_array) != ptype_simple_array) {
    ptype_error(cause, init_array, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return pfunk2__f2simple_array__new(cause, length, to_ptr(((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(init_array))))->slot));
}

u8 pfunk2__f2simple_array__immutable(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  u8 retval = __pure__f2simple_array__immutable(this);
  return retval;
}

void pfunk2__f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  __pure__f2simple_array__immutable__set(this, value);
}

u64 pfunk2__f2simple_array__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2simple_array__length(this);
  return length;
}

f2ptr pfunk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int length = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
    //error(nil, "f2array__elt error: index out of range.");
  }
  f2ptr rv = __pure__f2simple_array__elt(this, index);
  return rv;
}

f2ptr pfunk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  
  //int pool_index = __f2ptr__pool_index(this);
  
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length     = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
    //error(nil, "f2array__elt__set__trace_depth error: index out of range.");
  }
  
  f2ptr old_value = __pure__f2simple_array__elt(this, index);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2simple_array__elt__set(this, index, value);
  return nil;
}

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_simple_array);
}
f2ptr f2__simple_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__simple_array__is_type(cause, x));}
f2ptr f2__simple_array__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "simple_array");}

f2ptr f2__simple_array__new(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return f2larva__new(cause, 222010, nil);
  }
  return f2simple_array__new(cause, length__i, to_ptr(NULL));
}

u64 raw__simple_array__length(f2ptr cause, f2ptr this) {return f2simple_array__length(this, cause);}
f2ptr f2__simple_array__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__simple_array__length(cause, this));}

f2ptr raw__simple_array__elt(f2ptr cause, f2ptr this, u64 index) {return f2simple_array__elt(this, index, cause);}
f2ptr f2__simple_array__elt(f2ptr cause, f2ptr this, f2ptr index) {return raw__simple_array__elt(cause, this, f2integer__i(index, cause));}

f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2simple_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}

boolean_t raw__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__simple_array__eq(cause, this, that));
}
def_pcfunk2(simple_array__eq, this, that,
	    "",
	    return f2__simple_array__eq(this_cause, this, that));

u64   raw__simple_array__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)this;}
f2ptr  f2__simple_array__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__simple_array__eq_hash_value(cause, this));}
def_pcfunk1(simple_array__eq_hash_value, this,
	    "",
	    return f2__simple_array__eq_hash_value(this_cause, this));


boolean_t raw__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__array__equals(cause, this, that);
}

f2ptr f2__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(simple_array, this);
  return f2bool__new(raw__simple_array__equals(cause, this, that));
}
def_pcfunk2(simple_array__equals, this, that,
	    "",
	    return f2__simple_array__equals(this_cause, this, that));


f2ptr raw__simple_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  return raw__array__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__simple_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  assert_argument_type(simple_array, this);
  assert_argument_type(ptypehash,    node_hash);
  return raw__simple_array__equals_hash_value__loop_free(cause, this, node_hash);
}
def_pcfunk2(simple_array__equals_hash_value__loop_free, this, node_hash,
	    "",
	    return f2__simple_array__equals_hash_value__loop_free(this_cause, this, node_hash));


f2ptr raw__simple_array__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__array__equals_hash_value(cause, this);
}


f2ptr f2__simple_array__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(simple_array, this);
  return f2__simple_array__equals_hash_value(cause, this);
}
def_pcfunk1(simple_array__equals_hash_value, this,
	    "",
	    return f2__simple_array__equals_hash_value(this_cause, this));


def_pcfunk1(simple_array__is_type, x,
	    "",
	    return f2__simple_array__is_type(this_cause, x));
def_pcfunk1(simple_array__type, x,
	    "",
	    return f2__simple_array__type(this_cause, x));
def_pcfunk1(simple_array__new, length,
	    "",
	    return f2__simple_array__new(this_cause, length));
def_pcfunk1(simple_array__length, x,
	    "",
	    return f2__simple_array__length(this_cause, x));
def_pcfunk2(simple_array__elt, x, y,
	    "",
	    return f2__simple_array__elt(this_cause, x, y));
def_pcfunk3(simple_array__elt__set, x, y, z,
	    "",
	    return f2__simple_array__elt__set(this_cause, x, y, z));


f2ptr f2__simple_array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(simple_array,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__array__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(simple_array__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__simple_array__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__simple_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk;
    }
  }
  return nil;
}

f2ptr f2simple_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk);}
  {char* slot_name = "new_copy";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.new_copy__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__funk);}
  return this;
}


// traced_array

f2ptr ptype_traced_array__new(int pool_index, f2ptr cause, u64 length, ptr dptr_ptr) {
  f2ptr                       reflective_cause   = nil;
  boolean_t                   tracing_on         = raw__cause__is_traced(reflective_cause, cause);
  u64                         data_byte_num      = (sizeof(funk2_dptr_t) * length);
  f2ptr                       traced_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_traced_array_block_t) + data_byte_num);
  ptype_traced_array_block_t* traced_array_block = (ptype_traced_array_block_t*)from_ptr(raw__f2ptr_to_ptr(traced_array_f2ptr));
  debug__assert(traced_array_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  traced_array_block->ptype.block.ptype = ptype_traced_array;
  traced_array_block->ptype.cause       = cause;
  traced_array_block->length            = length;
  if (dptr_ptr) {memcpy(traced_array_block->dptr_data, from_ptr(dptr_ptr), data_byte_num);}
  else {
    int i;
    funk2_dptr_t* dptr_iter = (funk2_dptr_t*)(traced_array_block->dptr_data);
    for (i = length; i > 0; i --) {
      funk2_dptr__init(dptr_iter, nil, tracing_on, nil, nil, nil, nil);
      dptr_iter  ++;
    }
  }
  return traced_array_f2ptr;
}

f2ptr ptype_traced_array__new_from_f2ptrs(int pool_index, f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  f2ptr                       reflective_cause   = nil;
  boolean_t                   tracing_on         = raw__cause__is_traced(reflective_cause, cause);
  u64                         data_byte_num      = (sizeof(funk2_dptr_t) * length);
  f2ptr                       traced_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_traced_array_block_t) + data_byte_num);
  ptype_traced_array_block_t* traced_array_block = (ptype_traced_array_block_t*)from_ptr(raw__f2ptr_to_ptr(traced_array_f2ptr));
  debug__assert(traced_array_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  traced_array_block->ptype.block.ptype = ptype_traced_array;
  traced_array_block->ptype.cause       = cause;
  traced_array_block->length            = length;
  if (f2ptr_ptr) {
    int i;
    f2ptr*  f2ptr_iter = f2ptr_ptr;
    funk2_dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      funk2_dptr__init(dptr_iter, *f2ptr_iter, tracing_on, nil, nil, nil, nil);
      f2ptr_iter ++;
      dptr_iter  ++;
    }
  } else {
    int i;
    funk2_dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      funk2_dptr__init(dptr_iter, nil, tracing_on, nil, nil, nil, nil);
      dptr_iter  ++;
    }
  }
  return traced_array_f2ptr;
}

f2ptr pfunk2__f2traced_array__new(f2ptr cause, u64 length, ptr dptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2traced_array__new(pool_index, cause, length, dptr_ptr);
  return this;
}

f2ptr pfunk2__f2traced_array__new_from_f2ptrs(f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2traced_array__new_from_f2ptrs(pool_index, cause, length, f2ptr_ptr);
  return this;
}

f2ptr pfunk2__f2traced_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(init_array) != ptype_traced_array) {
    ptype_error(cause, init_array, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return f2traced_array__new(cause, length, to_ptr(((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(init_array))))->dptr_data));
}

u8 pfunk2__f2traced_array__immutable(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  u8 retval = __pure__f2traced_array__immutable(this);
  return retval;
}

void pfunk2__f2traced_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  __pure__f2traced_array__immutable__set(this, value);
}

u64 pfunk2__f2traced_array__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  return length;
}

f2ptr pfunk2__f2traced_array__elt__trace_depth(f2ptr this, u64 index, f2ptr cause, int trace_depth) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2traced_array_elt failed debug assertion: cause is non-null and not a cause.");
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
    //error(nil, "f2traced_array__elt error: index out of range.");
  }
  f2ptr return_value = nil;
  f2ptr this__cause = __pure__f2ptype__cause(this);
  // only apply special memory access effects if we're not looking at our own memory.
  if (cause != this__cause) {
    if (raw__cause__is_imaginary__trace_depth(cause, cause, trace_depth - 1)) {
      // this is an imaginary cause, so we need to retrieve the correct imaginary value, or the default (non-imaginary or "real") value is returned.
      f2ptr the_real_cause_for_really_thinking_imaginarily = nil;
      f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, the_real_cause_for_really_thinking_imaginarily);
      f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
      f2ptr real_value              = __pure__f2traced_array__elt(this, index);
      return_value = f2__imagination_frame__get_value_from_name_stack__trace_depth(the_real_cause_for_really_thinking_imaginarily, imagination_frame, imagination_name_stack, real_value, trace_depth - 1);
    } else {
      return_value = __pure__f2traced_array__elt(this, index);
    }
  } else {
    return_value = __pure__f2traced_array__elt(this, index);
  }
  
  // after reading a value, execute read_funks
  {
    f2ptr read_funks = __pure__f2traced_array__elt__read_funks(this, index);
    if (read_funks) {
      f2ptr funkable_iter = read_funks;
      f2ptr fiber         = f2__this__fiber(cause);
      f2ptr args          = nil;
      while (funkable_iter) {
	f2ptr funkable = f2cons__car(funkable_iter, cause);
	f2__force_funk_apply(cause, fiber, funkable, args);
	funkable_iter = f2cons__cdr(funkable_iter, cause);
      }
    }
  }
  
  // then execute causal interaction read funks
  {
    if (cause) {
      f2ptr this__cause = __pure__f2ptype__cause(this);
      if (cause != this__cause) {
	f2ptr reflective_cause            = nil;
	f2ptr read_other_memory_callbacks = f2__cause__read_other_memory_callbacks(reflective_cause, cause);
	if (read_other_memory_callbacks) {
	  f2ptr fiber = f2__this__fiber(cause);
	  f2ptr iter  = read_other_memory_callbacks;
	  while (iter) {
	    f2ptr callback = f2__cons__car(reflective_cause, iter);
	    f2__force_funk_apply(reflective_cause, fiber, callback, f2list3__new(reflective_cause, cause, this, f2integer__new(cause, index)));
	    iter = f2__cons__cdr(reflective_cause, iter);
	  }
	}
      }
    }
  }
  
  return return_value;
}

f2ptr pfunk2__f2traced_array__elt(f2ptr this, u64 index, f2ptr cause) {
  return pfunk2__f2traced_array__elt__trace_depth(this, index, cause, 1);
}

f2ptr pfunk2__f2traced_array__elt__set__trace_depth(f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2traced_array_elt failed debug assertion: cause is non-null and not a cause.");
  
  //int pool_index = __f2ptr__pool_index(this);
  
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length     = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
    //error(nil, "f2traced_array__elt__set__trace_depth error: index out of range.");
  }
  if (! raw__cause__is_imaginary__trace_depth(cause, cause, trace_depth - 1)) {
    //f2ptr old_elt    = __pure__f2traced_array__elt(this, index);
    f2ptr prev_elts  = __pure__f2traced_array__elt__trace(this, index);
    int   tracing_on = __pure__f2traced_array__elt__tracing_on(this, index);
    
    f2ptr new_tracing_doublelink = nil;
    if (tracing_on && (trace_depth > 0)) {
      new_tracing_doublelink = f2doublelink__new__trace_depth(cause, prev_elts, nil, value, trace_depth - 1);
    }
    
    if (new_tracing_doublelink) {
      if (prev_elts) {
	f2doublelink__next__set__trace_depth(prev_elts, nil, new_tracing_doublelink, trace_depth - 1);
      }
      __pure__f2traced_array__elt__trace__set(this, index, new_tracing_doublelink);
    }
    
    f2ptr old_value = __pure__f2traced_array__elt(this, index);
    
    funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
    
    __pure__f2traced_array__elt__set(this, index, value);
    
  } else {
    // cause has imaginary effects
    // we first find imagination_link with the correct name if it exists or we allocate a new imagination_link with the cause's imagination's name.
    f2ptr the_real_cause_for_really_thinking_imaginarily = nil;
    f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, the_real_cause_for_really_thinking_imaginarily);
    f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
    f2ptr real_value              = __pure__f2traced_array__elt(this, index);
    f2ptr name = f2cons__car(imagination_name_stack, the_real_cause_for_really_thinking_imaginarily);
    f2ptr next = f2cons__cdr(imagination_name_stack, the_real_cause_for_really_thinking_imaginarily);
    f2ptr slot = f2__imagination_frame__get_slot(the_real_cause_for_really_thinking_imaginarily, imagination_frame, name);
    if (! slot) {
      imagination_frame = raw__imagination_frame__new_with_added_slot__trace_depth(the_real_cause_for_really_thinking_imaginarily, imagination_frame, name, next ? real_value : value, trace_depth - 1);
      __pure__f2traced_array__elt__imagination_frame__set(this, index, imagination_frame);
      if (next) {
	slot = f2__imagination_frame__get_slot(the_real_cause_for_really_thinking_imaginarily, imagination_frame, name);
	release__assert(slot != nil, cause, "pfunk2__f2traced_array__elt__set__trace_depth error 1: !(slot != nil)");
      }
    }
    if (next) {
      release__assert(slot != nil, cause, "pfunk2__f2traced_array__elt__set__trace_depth error 2: !(slot != nil)");
      f2__imagination_link__set_value_from_name_stack__trace_depth(the_real_cause_for_really_thinking_imaginarily, slot, next, value, trace_depth - 1);
    }
  }
  
  // after setting value, execute mutate_funks
  {
    f2ptr mutate_funks = __pure__f2traced_array__elt__mutate_funks(this, index);
    if (mutate_funks) {
      f2ptr funkable_iter = mutate_funks;
      f2ptr fiber         = f2__this__fiber(cause);
      f2ptr args          = nil;
      while (funkable_iter) {
	f2ptr funkable = f2cons__car(funkable_iter, cause);
	f2__force_funk_apply(cause, fiber, funkable, args);
	funkable_iter = f2cons__cdr(funkable_iter, cause);
      }
    }
  }
  
  return nil;
}

f2ptr pfunk2__f2traced_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  return pfunk2__f2traced_array__elt__set__trace_depth(this, index, cause, value, 1);
}

f2ptr pfunk2__f2traced_array__elt__tracing_on(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr rv = __pure__f2traced_array__elt__tracing_on(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__tracing_on__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr old_value = __pure__f2traced_array__elt__tracing_on(this, index);
  
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2traced_array__elt__tracing_on__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__trace(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr rv = __pure__f2traced_array__elt__trace(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__trace__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr old_value = __pure__f2traced_array__elt__trace(this, index);
  
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2traced_array__elt__trace__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__imagination_frame(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr rv = __pure__f2traced_array__elt__imagination_frame(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__imagination_frame__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr old_value = __pure__f2traced_array__elt__imagination_frame(this, index);
  
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2traced_array__elt__imagination_frame__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__mutate_funks(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr rv = __pure__f2traced_array__elt__mutate_funks(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__mutate_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr old_value = __pure__f2traced_array__elt__mutate_funks(this, index);
  
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2traced_array__elt__mutate_funks__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__read_funks(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr rv = __pure__f2traced_array__elt__read_funks(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__read_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds, nil);
  }
  f2ptr old_value = __pure__f2traced_array__elt__read_funks(this, index);
  
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  __pure__f2traced_array__elt__read_funks__set(this, index, value);
  return nil;
}


boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_traced_array);
}
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__traced_array__is_type(cause, x));}
f2ptr f2__traced_array__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "traced_array");}

f2ptr f2__traced_array__new(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return f2larva__new(cause, 2201, nil);
  }
  return f2traced_array__new(cause, length__i, to_ptr(NULL));
}

u64   raw__traced_array__length(f2ptr cause, f2ptr this) {return f2traced_array__length(this, cause);}
f2ptr  f2__traced_array__length(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_array, this);
  return f2integer__new(cause, raw__traced_array__length(cause, this));
}

f2ptr raw__traced_array__elt(f2ptr cause, f2ptr this, u64   index) {return f2traced_array__elt(this, index, cause);}
f2ptr  f2__traced_array__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(traced_array, this);
  assert_argument_type(integer,      index);
  return raw__traced_array__elt(cause, this, f2integer__i(index, cause));
}

f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__tracing_on(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__tracing_on__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__trace(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__trace__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__imagination_frame(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__imagination_frame__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__mutate_funks(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__mutate_funks(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__mutate_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__mutate_funks__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__read_funks(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__read_funks(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__read_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__read_funks__set(x, f2integer__i(y, cause), cause, z); return nil;}

def_pcfunk1(traced_array__is_type, x,
	    "",
	    return f2__traced_array__is_type(this_cause, x));
def_pcfunk1(traced_array__type, x,
	    "",
	    return f2__traced_array__type(this_cause, x));
def_pcfunk1(traced_array__new, length,
	    "",
	    return f2__traced_array__new(this_cause, length));
def_pcfunk1(traced_array__length, x,
	    "",
	    return f2__traced_array__length(this_cause, x));
def_pcfunk2(traced_array__elt, x, y,
	    "",
	    return f2__traced_array__elt(this_cause, x, y));
def_pcfunk3(traced_array__elt__set, x, y, z,
	    "",
	    return f2__traced_array__elt__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__tracing_on, x, y,
	    "",
	    return f2__traced_array__elt__tracing_on(this_cause, x, y));
def_pcfunk3(traced_array__elt__tracing_on__set, x, y, z,
	    "",
	    return f2__traced_array__elt__tracing_on__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__trace, x, y,
	    "",
	    return f2__traced_array__elt__trace(this_cause, x, y));
def_pcfunk3(traced_array__elt__trace__set, x, y, z,
	    "",
	    return f2__traced_array__elt__trace__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__imagination_frame, x, y,
	    "",
	    return f2__traced_array__elt__imagination_frame(this_cause, x, y));
def_pcfunk3(traced_array__elt__imagination_frame__set, x, y, z,
	    "",
	    return f2__traced_array__elt__imagination_frame__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__mutate_funks, x, y,
	    "",
	    return f2__traced_array__elt__mutate_funks(this_cause, x, y));
def_pcfunk3(traced_array__elt__mutate_funks__set, x, y, z,
	    "",
	    return f2__traced_array__elt__mutate_funks__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__read_funks, x, y,
	    "",
	    return f2__traced_array__elt__read_funks(this_cause, x, y));
def_pcfunk3(traced_array__elt__read_funks__set, x, y, z,
	    "",
	    return f2__traced_array__elt__read_funks__set(this_cause, x, y, z));

boolean_t raw__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__traced_array__eq(cause, this, that));
}
def_pcfunk2(traced_array__eq, this, that,
	    "",
	    return f2__traced_array__eq(this_cause, this, that));

u64   raw__traced_array__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)this;}
f2ptr  f2__traced_array__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__traced_array__eq_hash_value(cause, this));}
def_pcfunk1(traced_array__eq_hash_value, this,
	    "",
	    return f2__traced_array__eq_hash_value(this_cause, this));


boolean_t raw__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__array__equals(cause, this, that);
}

f2ptr f2__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(traced_array, this);
  return f2bool__new(raw__traced_array__equals(cause, this, that));
}
def_pcfunk2(traced_array__equals, this, that,
	    "",
	    return f2__traced_array__equals(this_cause, this, that));


f2ptr raw__traced_array__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__array__equals_hash_value(cause, this);
}

f2ptr f2__traced_array__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_array, this);
  return raw__traced_array__equals_hash_value(cause, this);
}
def_pcfunk1(traced_array__equals_hash_value, this,
	    "",
	    return f2__traced_array__equals_hash_value(this_cause, this));


f2ptr raw__traced_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  return raw__array__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__traced_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(traced_array, this);
  assert_argument_type(ptypehash,    node_ptypehash);
  return raw__traced_array__equals_hash_value__loop_free(cause, this, node_ptypehash);
}
def_pcfunk2(traced_array__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__traced_array__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


f2ptr f2__traced_array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(traced_array,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__array__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(traced_array__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__traced_array__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__traced_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk;
    }
  }
  return nil;
}

f2ptr f2traced_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk);}
  {char* slot_name = "elt-tracing_on";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk);}
  {char* slot_name = "elt-tracing_on";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk);}
  {char* slot_name = "elt-trace";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk);}
  {char* slot_name = "elt-trace";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk);}
  {char* slot_name = "elt-imagination_frame";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk);}
  {char* slot_name = "elt-imagination_frame";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk);}
  {char* slot_name = "elt-mutate_funks";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk);}
  {char* slot_name = "elt-mutate_funks";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk);}
  {char* slot_name = "elt-read_funks";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk);}
  {char* slot_name = "elt-read_funks";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__funk);}
  return this;
}


// larva

f2ptr ptype_larva__new(int pool_index, f2ptr cause, u32 larva_type, f2ptr bug) {
  f2ptr larva_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_larva_block_t));
  ptype_larva_block_t* larva_block = (ptype_larva_block_t*)from_ptr(raw__f2ptr_to_ptr(larva_f2ptr));
  debug__assert(larva_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  if (bug)   {raw__exp__increment_reference_count(bug);}
  larva_block->ptype.block.ptype = ptype_larva;
  larva_block->ptype.cause       = cause;
  larva_block->larva_type        = larva_type;
  larva_block->bug               = bug;
  return larva_f2ptr;
}

f2ptr pfunk2__f2larva__new(f2ptr cause, u32 larva_type, f2ptr bug) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2larva__new(pool_index, cause, larva_type, bug);
  return retval;
}

u32 pfunk2__f2larva__larva_type(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_larva) {
    ptype_error(cause, this, __funk2.globalenv.ptype_larva__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 type = __pure__f2larva__larva_type(this);
  return type;
}

f2ptr pfunk2__f2larva__bug(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_larva) {
    ptype_error(cause, this, __funk2.globalenv.ptype_larva__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr bug = __pure__f2larva__bug(this);
  return bug;
}

boolean_t raw__larva__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_larva);
}
f2ptr f2__larva__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__larva__is_type(cause, x));}
def_pcfunk1(larva__is_type, x,
	    "",
	    return f2__larva__is_type(this_cause, x));

f2ptr f2__larva__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "larva");}
def_pcfunk1(larva__type, x,
	    "",
	    return f2__larva__type(this_cause, x));

u32 raw__larva__larva_type(f2ptr cause, f2ptr this) {
  return f2larva__larva_type(this, cause);
}

f2ptr f2__larva__larva_type(f2ptr cause, f2ptr this) {
  assert_argument_type(larva, this);
  return f2integer__new(cause, raw__larva__larva_type(cause, this));
}

f2ptr raw__larva__bug(f2ptr cause, f2ptr this) {
  return f2larva__bug(this, cause);
}

f2ptr f2__larva__bug(f2ptr cause, f2ptr this) {
  assert_argument_type(larva, this);
  return raw__larva__bug(cause, this);
}

f2ptr f2__larva__new(f2ptr cause, f2ptr larva_type, f2ptr bug) {
  assert_argument_type(       integer, larva_type);
  assert_argument_type_or_nil(bug,     bug);
  return f2larva__new(cause, f2integer__i(larva_type, cause), bug);
}

def_pcfunk2(larva__new,        larva_type, bug,
	    "",
	    return f2__larva__new(this_cause, larva_type, bug));
def_pcfunk1(larva__larva_type, this,
	    "",
	    return f2__larva__larva_type(this_cause, this));
def_pcfunk1(larva__bug,        this,
	    "",
	    return f2__larva__bug(this_cause, this));

boolean_t raw__larva__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__larva__is_type(cause, that)) {
    return boolean__false;
  }
  return f2larva__larva_type(this, cause) == f2larva__larva_type(that, cause);
}

f2ptr f2__larva__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(larva, this);
  return f2bool__new(raw__larva__eq(cause, this, that));
}
def_pcfunk2(larva__eq, this, that,
	    "",
	    return f2__larva__eq(this_cause, this, that));

u64 raw__larva__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2larva__larva_type(this, cause);}

f2ptr f2__larva__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__larva__eq_hash_value(cause, this));}
def_pcfunk1(larva__eq_hash_value, this,
	    "",
	    return f2__larva__eq_hash_value(this_cause, this));


boolean_t raw__larva__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__larva__eq(cause, this, that);
}

f2ptr f2__larva__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(larva, this);
  return f2bool__new(raw__larva__equals(cause, this, that));
}
def_pcfunk2(larva__equals, this, that,
	    "",
	    return f2__larva__equals(this_cause, this, that));


u64 raw__larva__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__larva__eq_hash_value(cause, this);
}

f2ptr f2__larva__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(larva,     this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__larva__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(larva__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__larva__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__larva__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__larva__eq_hash_value(cause, this);
}

f2ptr f2__larva__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(larva, this);
  return f2integer__new(cause, raw__larva__equals_hash_value(cause, this));
}
def_pcfunk1(larva__equals_hash_value, this,
	    "",
	    return f2__larva__equals_hash_value(this_cause, this));


f2ptr raw__larva__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "larva"),
					       new__symbol(cause, "larva_type"),        f2__larva__larva_type(cause, this),
					       new__symbol(cause, "bug"),               f2__larva__bug(       cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__larva__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(larva,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__larva__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(larva__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__larva__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__larva__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.type__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.eq__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.equals__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.new__funk;
    }
  }
  return nil;
}

f2ptr f2larva__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.new__funk);}
  {char* slot_name = "larva_type";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__funk);}
  return this;
}



// symbol_hash

void funk2_symbol_hash__init(funk2_symbol_hash_t* this) {
  funk2_processor_mutex__init(&(this->cmutex));
  this->array               = (funk2_symbol_hash_node_t**)from_ptr(f2__malloc(sizeof(funk2_symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH));
  memset(this->array, 0, sizeof(funk2_symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH);
  this->total_symbol_num    = 0;
  this->eq_hash_value_bit_mask = SYMBOL_HASH__INITIAL_ARRAY_LENGTH - 1; // assumes SYMBOL_HASH__INITIAL_ARRAY_LENGTH is power of 2
  this->array_length        = SYMBOL_HASH__INITIAL_ARRAY_LENGTH;
}

void funk2_symbol_hash__destroy(funk2_symbol_hash_t* this) {
  {
    funk2_symbol_hash_node_t** array_iter = this->array;
    funk2_symbol_hash_node_t*  node_iter;
    int i;
    for (i = this->array_length; i > 0; i --) {
      node_iter = *array_iter;
      while (node_iter) {
	funk2_symbol_hash_node_t* next = node_iter->next;
	f2__free(to_ptr(node_iter));
	node_iter = next;
      }
      array_iter ++;
    }
  }
  f2__free(to_ptr(this->array));
}

void funk2_symbol_hash__reinit(funk2_symbol_hash_t* this) {
  funk2_symbol_hash__destroy(this);
  funk2_symbol_hash__init(this);
}

void funk2_symbol_hash__add_symbol(funk2_symbol_hash_t* this, f2ptr symbol_f2ptr) {
  ptype_symbol_block_t*     symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(symbol_f2ptr));
  u64                       bin_index    = symbol_block->eq_hash_value & (this->eq_hash_value_bit_mask);
  funk2_symbol_hash_node_t* new_node     = (funk2_symbol_hash_node_t*)from_ptr(f2__malloc(sizeof(funk2_symbol_hash_node_t)));
  new_node->symbol = symbol_f2ptr;
  new_node->next = this->array[bin_index];
  this->array[bin_index] = new_node;
}

f2ptr funk2_symbol_hash__lookup_symbol__thread_unsafe(funk2_symbol_hash_t* this, u64 length, funk2_character_t* str) {
  ptype_symbol_block_t* symbol_block = NULL;
  // search for chararray in hashed symbols
  u64 bin_index = (u64)((u64)character_array__hash_value(length, str) & (u64)(this->eq_hash_value_bit_mask));
  funk2_symbol_hash_node_t* node = (this->array[bin_index]);
  while (node) {
    symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(node->symbol));
    //if we find a symbol that matches chararray, return it.
    debug__assert(symbol_block->ptype.block.used, nil, "funk2_symbol_hash__lookup_symbol error: found unused symbol.");
    if (symbol_block->length == length && (! memcmp(symbol_block->str, str, length * sizeof(funk2_character_t)))) {
      funk2_processor_mutex__unlock(&(this->cmutex));
      return node->symbol;
    }
    node = node->next;
  }
  return nil;
}

f2ptr funk2_symbol_hash__lookup_symbol(funk2_symbol_hash_t* this, u64 length, funk2_character_t* str) {
  funk2_processor_mutex__user_lock(&this->cmutex);
  f2ptr result = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, length, str);
  funk2_processor_mutex__unlock(&(this->cmutex));
  return result;
}

f2ptr funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  f2ptr symbol_f2ptr = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, length, str);
  if (symbol_f2ptr) {
    return symbol_f2ptr;
  }
  
  // otherwise, create a new symbol
  symbol_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_symbol_block_t) + (length * sizeof(funk2_character_t)));
  ptype_symbol_block_t* symbol_block = (ptype_symbol_block_t*)from_ptr(raw__f2ptr_to_ptr(symbol_f2ptr));
  debug__assert(symbol_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  symbol_block->ptype.block.ptype = ptype_symbol;
  symbol_block->ptype.cause       = cause;
  symbol_block->length            = length;
  if (str) {memcpy(symbol_block->str, str, length * sizeof(funk2_character_t));}
  else     {memset(symbol_block->str, 0,   length * sizeof(funk2_character_t));}
  symbol_block->eq_hash_value  = (u64)((u64)character_array__hash_value(length, str));
  
  // and add new symbol to hash table
  funk2_symbol_hash__add_symbol(this, symbol_f2ptr);
  return symbol_f2ptr;
}

f2ptr funk2_symbol_hash__lookup_or_create_symbol(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, funk2_character_t* str) {
  funk2_processor_mutex__user_lock(&this->cmutex);
  f2ptr result = funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(this, pool_index, cause, length, str);
  funk2_processor_mutex__unlock(&(this->cmutex));
  return result;
}

#define gensym__length 11
f2ptr funk2_symbol_hash__generate_new_random_symbol__thread_unsafe(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string) {
  s64 total_gensym_length = initial_string_length + gensym__length;
  funk2_character_t* gensym__name = (funk2_character_t*)from_ptr(f2__malloc((total_gensym_length + 1) * sizeof(funk2_character_t)));
  {
    int index;
    for (index = 0; index < initial_string_length; index ++) {
      gensym__name[index] = initial_string[index];
    }
  }
  gensym__name[initial_string_length + 0] = (funk2_character_t)'-';
  f2ptr symbol_exists;
  do {
    int index;
    for (index = 0; index < gensym__length - 1; index ++) {
      int random_num = random() % (10 + 26);
      if (random_num < 10) {
	gensym__name[initial_string_length + index + 1] = ((funk2_character_t)'0') + random_num;
      } else {
	gensym__name[initial_string_length + index + 1] = ((funk2_character_t)'a') + (random_num - 10);
      }
    }
    symbol_exists = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, total_gensym_length, gensym__name);
  } while (symbol_exists);
  f2ptr new_symbol = funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(this, pool_index, cause, total_gensym_length, gensym__name);
  return new_symbol;
}

f2ptr funk2_symbol_hash__generate_new_random_symbol(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string) {
  funk2_processor_mutex__user_lock(&this->cmutex);
  f2ptr new_symbol = funk2_symbol_hash__generate_new_random_symbol__thread_unsafe(this, pool_index, cause, initial_string_length, initial_string);
  funk2_processor_mutex__unlock(&(this->cmutex));
  return new_symbol;
}

f2ptr raw__gensym(f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string) {
  int pool_index = this_processor_thread__pool_index();
  return funk2_symbol_hash__generate_new_random_symbol(&(__funk2.ptypes.symbol_hash), pool_index, cause, initial_string_length, initial_string);
}

f2ptr f2__gensym(f2ptr cause, f2ptr initial_string) {
  assert_argument_type(string, initial_string);
  s64                initial_string__length = raw__string__length(cause, initial_string);
  funk2_character_t* initial_string__str    = (funk2_character_t*)from_ptr(f2__malloc((initial_string__length + 1) * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, initial_string, initial_string__str);
  initial_string__str[initial_string__length] = 0;
  f2ptr new_symbol = raw__gensym(cause, initial_string__length, initial_string__str);
  f2__free(to_ptr(initial_string__str));
  return new_symbol;
}
def_pcfunk1(gensym, initial_string,
	    "generates a symbol that did not exist previously.",
	    return f2__gensym(this_cause, initial_string));

f2ptr raw__gensym__new_from_utf8(f2ptr cause, char* initial_utf8_string) {
  u64                initial_string__length = raw__utf8_string__length(initial_utf8_string);
  funk2_character_t* initial_string         = (funk2_character_t*)from_ptr(f2__malloc(initial_string__length * sizeof(funk2_character_t)));
  raw__utf8_string__str_copy(initial_utf8_string, initial_string);
  f2ptr new = raw__gensym(cause, initial_string__length, initial_string);
  f2__free(to_ptr(initial_string));
  return new;
}


void funk2_symbol_hash__touch_all_symbols(funk2_symbol_hash_t* this, funk2_garbage_collector_t* garbage_collector) {
  status("funk2_garbage_collector: touch_all_symbols.");
  funk2_symbol_hash_node_t** array_iter = this->array;
  funk2_symbol_hash_node_t*  node_iter;
  int i;
  for (i = this->array_length; i > 0; i --) {
    for (node_iter = array_iter[0]; node_iter; node_iter = node_iter->next) {
      funk2_garbage_collector__touch_f2ptr(garbage_collector, node_iter->symbol);
    }
    array_iter ++;
  }
}

// 2^64 = 18, 446,744,073,709,551,616
//   or = 18  sextillion



// ptypes

void funk2_ptypes__init(funk2_ptypes_t* this) {
  funk2_symbol_hash__init(&(this->symbol_hash));
}

void funk2_ptypes__destroy(funk2_ptypes_t* this) {
  funk2_symbol_hash__destroy(&(this->symbol_hash));
}


// **

void f2__ptypes__initialize__object_slots() {
  f2ptr cause = initial_cause();
  
  // ptype
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__type, this, cfunk); __funk2.globalenv.object_type.ptype.type__funk = never_gc(cfunk);}
  {char* str = "raw"; __funk2.globalenv.object_type.ptype.raw__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__raw, this, cfunk); __funk2.globalenv.object_type.ptype.raw__funk = never_gc(cfunk);}
  {char* str = "cause"; __funk2.globalenv.object_type.ptype.cause__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__cause, this, cfunk); __funk2.globalenv.object_type.ptype.cause__funk = never_gc(cfunk);}
  {char* str = "cause-set"; __funk2.globalenv.object_type.ptype.cause__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptype__cause__set, this, value, cfunk); __funk2.globalenv.object_type.ptype.cause__set__funk = never_gc(cfunk);}
  
  // integer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_integer.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_integer.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.new__funk = never_gc(cfunk);}
  {char* str = "i"; __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__i, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.i__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_integer.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_integer.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__equals_hash_value__loop_free, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "as-double"; __funk2.globalenv.object_type.ptype.ptype_integer.as__double__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__as__double, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk = never_gc(cfunk);}
  {char* str = "as-pointer"; __funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__as__pointer, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__funk = never_gc(cfunk);}
  {char* str = "multiplied_by"; __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__multiplied_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk = never_gc(cfunk);}
  {char* str = "divided_by"; __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__divided_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_integer.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_integer.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "square_root"; __funk2.globalenv.object_type.ptype.ptype_integer.square_root__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__square_root, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk = never_gc(cfunk);}
  {char* str = "modulo"; __funk2.globalenv.object_type.ptype.ptype_integer.modulo__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__modulo, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.modulo__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // double
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_double.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_double.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_double.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.new__funk = never_gc(cfunk);}
  {char* str = "d"; __funk2.globalenv.object_type.ptype.ptype_double.d__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__d, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.d__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_double.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_double.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "as-double"; __funk2.globalenv.object_type.ptype.ptype_double.as__double__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__as__double, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.as__double__funk = never_gc(cfunk);}
  {char* str = "multiplied_by"; __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__multiplied_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk = never_gc(cfunk);}
  {char* str = "divided_by"; __funk2.globalenv.object_type.ptype.ptype_double.divided_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__divided_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_double.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_double.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "square_root"; __funk2.globalenv.object_type.ptype.ptype_double.square_root__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__square_root, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.square_root__funk = never_gc(cfunk);}
  {char* str = "radian_sine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_sine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_sine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_sine__funk = never_gc(cfunk);}
  {char* str = "radian_arcsine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_arcsine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__funk = never_gc(cfunk);}
  {char* str = "radian_cosine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_cosine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__funk = never_gc(cfunk);}
  {char* str = "radian_arccosine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_arccosine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__funk = never_gc(cfunk);}
  {char* str = "radian_tangent"; __funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_tangent, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__funk = never_gc(cfunk);}
  {char* str = "radian_arctangent"; __funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_arctangent, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__funk = never_gc(cfunk);}
  {char* str = "power"; __funk2.globalenv.object_type.ptype.ptype_double.power__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__power, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.power__funk = never_gc(cfunk);}
  {char* str = "modulo"; __funk2.globalenv.object_type.ptype.ptype_double.modulo__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__modulo, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.modulo__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // float
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_float.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_float.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_float.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.new__funk = never_gc(cfunk);}
  {char* str = "f"; __funk2.globalenv.object_type.ptype.ptype_float.f__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__f, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.f__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_float.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_float.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "as-double"; __funk2.globalenv.object_type.ptype.ptype_float.as__double__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__as__double, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.as__double__funk = never_gc(cfunk);}
  {char* str = "multiplied_by"; __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__multiplied_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk = never_gc(cfunk);}
  {char* str = "divided_by"; __funk2.globalenv.object_type.ptype.ptype_float.divided_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__divided_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_float.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_float.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "square_root"; __funk2.globalenv.object_type.ptype.ptype_float.square_root__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__square_root, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.square_root__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // pointer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_pointer.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk = never_gc(cfunk);}
  {char* str = "p"; __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__p, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_pointer.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_pointer.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_pointer.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_pointer.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__terminal_print_with_frame, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // scheduler_cmutex
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler_cmutex__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler_cmutex__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler_cmutex__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.new__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler_cmutex__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler_cmutex__eq_hash_value, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler_cmutex__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler_cmutex__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler_cmutex__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler_cmutex__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_scheduler_cmutex.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // cmutex
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_cmutex.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_cmutex.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk = never_gc(cfunk);}
  {char* str = "unlock"; __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__unlock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk = never_gc(cfunk);}
  {char* str = "trylock"; __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__trylock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk = never_gc(cfunk);}
  {char* str = "is_locked"; __funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__is_locked, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__eq_hash_value, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // char
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_char.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_char.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_char.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.new__funk = never_gc(cfunk);}
  {char* str = "ch"; __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__ch, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.ch__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_char.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_char.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // string
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_string.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_string.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_string.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_string.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.length__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.elt__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_string.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_string.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // symbol
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_symbol.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_symbol.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_symbol.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__funk = never_gc(cfunk);}
  {char* str = "as-string"; __funk2.globalenv.object_type.ptype.ptype_symbol.as__string__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__as__string, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.as__string__funk = never_gc(cfunk);}
  
  // chunk
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_chunk.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__new, length, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_chunk.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_chunk.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "bit8-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit8__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk = never_gc(cfunk);}
  {char* str = "bit8-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit8__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit16-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit16__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk = never_gc(cfunk);}
  {char* str = "bit16-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit16__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit32-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit32__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk = never_gc(cfunk);}
  {char* str = "bit32-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit32__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit64-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit64__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk = never_gc(cfunk);}
  {char* str = "bit64-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit64__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk = never_gc(cfunk);}
  {char* str = "cfunk_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(chunk__cfunk_jump, this, fiber, env, args, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk = never_gc(cfunk);}
  {char* str = "bytecode_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bytecode_jump, this, fiber, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // simple_array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__equals_hash_value__loop_free, this, node_hash, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(simple_array__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__terminal_print_with_frame, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // traced_array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__equals_hash_value__loop_free, this, node_hash, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__tracing_on, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__tracing_on__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk = never_gc(cfunk);}
  {char* str = "elt-trace"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__trace, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk = never_gc(cfunk);}
  {char* str = "elt-trace-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__trace__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__imagination_frame, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__imagination_frame__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__mutate_funks, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__mutate_funks__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__read_funks, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__read_funks__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // larva
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_larva.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.new__funk = never_gc(cfunk);}
  {char* str = "larva_type"; __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__larva_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk = never_gc(cfunk);}
  {char* str = "bug"; __funk2.globalenv.object_type.ptype.ptype_larva.bug__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__bug, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.bug__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_larva.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_larva.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // gensym
  f2__primcfunk__init__0(gensym);
  
}

// initialize ptypes

void f2__ptypes__initialize() {
  funk2_ptypes__init(&(__funk2.ptypes));
}

void f2__ptypes__destroy() {
  funk2_ptypes__destroy(&(__funk2.ptypes));
}


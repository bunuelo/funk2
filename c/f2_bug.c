// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#include "funk2.h"

// bug

def_primobject_2_slot(bug, bug_type, frame);

f2ptr f2__bug__new(f2ptr cause, f2ptr type, f2ptr frame) {return f2bug__new(cause, type, frame);}
def_pcfunk2(bug__new, type, frame,
	    "",
	    return f2__bug__new(this_cause, type, frame));

f2ptr raw__bug__new_from_larva(f2ptr cause, f2ptr larva) {
  u64 larva_type = f2larva__larva_type(larva, cause);
  return f2__bug__new(cause, f2integer__new(cause, larva_type), f2__frame__new(cause, nil));
}

f2ptr f2__bug__new_from_larva(f2ptr cause, f2ptr larva) {
  assert_argument_type(larva, larva);
  return raw__bug__new_from_larva(cause, larva);
}

f2ptr raw__bug__pretty_print(f2ptr cause, f2ptr this) {
  f2ptr print_frame = f2__frame__new(cause, nil);
  f2ptr bug_frame   = f2__bug__frame(cause, this);
  if (bug_frame && raw__frame__is_type(cause, bug_frame)) {
    f2ptr source_expression = f2__frame__lookup_var_value(cause, bug_frame, new__symbol(cause, "source_expression"), nil);
    if (raw__source_expression__is_type(cause, source_expression)) {
      f2ptr filename     = f2source_expression__filename(    source_expression, cause);
      f2ptr first_line   = f2source_expression__first_line(  source_expression, cause);
      f2ptr last_line    = f2source_expression__last_line(   source_expression, cause);
      f2ptr first_column = f2source_expression__first_column(source_expression, cause);
      f2ptr last_column  = f2source_expression__last_column( source_expression, cause);
      printf("bug in ");
      if (raw__string__is_type(cause, filename)) {
	assert_value(f2__ansi__stream__write(cause, __funk2.globalenv.stdout_stream, filename));
      } else {
	printf("<unknown-filename>");
      }
      printf(": lines ");
      if (raw__integer__is_type(cause, first_line)) {
	u64 first_line__i = f2integer__i(first_line, cause);
	printf(u64__fstr, first_line__i);
      } else {
	printf("??");
      }
      printf("--");
      if (raw__integer__is_type(cause, last_line)) {
	u64 last_line__i = f2integer__i(last_line, cause);
	printf(u64__fstr, last_line__i);
      } else {
	printf("??");
      }
      printf("\n");
    }
    frame__var__iteration(cause, bug_frame, slot_name, slot_value,
			  boolean_t value_printable = boolean__true;
			  if (raw__array__is_type(cause, slot_value)) {
			    value_printable = boolean__false;
			  }
			  if (value_printable) {
			    f2__frame__add_var_value(cause, print_frame, slot_name, slot_value);
			  } else {
			    f2__frame__add_var_value(cause, print_frame, slot_name, f2list2__new(cause, f2__object__type(cause, slot_value), new__symbol(cause, "<>")));
			  }
			  );
  }
  f2__print(cause, f2__bug__new(cause, f2__bug__bug_type(cause, this), print_frame));
  
  f2ptr fiber = f2__frame__lookup_var_value(cause, bug_frame, new__symbol(cause, "fiber"), nil);
  if (raw__fiber__is_type(cause, fiber)) {
    printf("\nstack trace:\n");
    f2ptr result = f2__fiber_stack_trace__print(cause, f2__fiber__stack_trace(cause, fiber));
    if (raw__larva__is_type(cause, result)) {
      printf("bug printing stack trace (");
      f2__print(cause, result);
      printf(")\n");
    }
  } else {
    printf("\nraw__bug__pretty_print: couldn't find fiber slot in bug frame.");
  }
  return nil;
}

f2ptr f2__bug__pretty_print(f2ptr cause, f2ptr this) {
  assert_argument_type(bug, this);
  return raw__bug__pretty_print(cause, this);
}
def_pcfunk1(bug__pretty_print, this,
	    "Prints a bug object for human readability, suppressing large objects from printing in their entirety.",
	    return f2__bug__pretty_print(this_cause, this));


f2ptr raw__bug__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "bug"),
					       new__symbol(cause, "bug_type"), f2__bug__bug_type(cause, this),
					       new__symbol(cause, "frame"),    f2__bug__frame(   cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__bug__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(bug,                  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__bug__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(bug__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__bug__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2bug__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2bug__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bug.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__bug__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // bug
  
  initialize_primobject_2_slot__defragment__fix_pointers(bug, bug_type, frame);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_bug.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(bug__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_bug.terminal_print_with_frame__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(bug__pretty_print);
}

void f2__bug__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // bug
  
  initialize_primobject_2_slot(bug, bug_type, frame);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_bug.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bug__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_bug.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(bug__pretty_print, this);
}

void f2__bug__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bug", "", &f2__bug__reinitialize_globalvars, &f2__bug__defragment__fix_pointers);
  
  f2__bug__reinitialize_globalvars();
}


// 
// Copyright (c) 2007-2010 Bo Morgan.
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
def_pcfunk2(bug__new, type, frame, return f2__bug__new(this_cause, type, frame));

f2ptr raw__bug__new_from_larva(f2ptr cause, f2ptr larva) {
  u64 larva_type = f2larva__larva_type(larva, cause);
  return f2__bug__new(cause, f2integer__new(cause, larva_type), f2__frame__new(cause, nil));
}

f2ptr f2__bug__new_from_larva(f2ptr cause, f2ptr larva) {
  if (! raw__larva__is_type(cause, larva)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bug__new_from_larva(cause, larva);
}

f2ptr raw__bug__pretty_print(f2ptr cause, f2ptr this) {
  f2ptr print_frame = f2__frame__new(cause, nil);
  f2ptr bug_frame   = f2__bug__frame(cause, this);
  if (bug_frame && raw__frame__is_type(cause, bug_frame)) {
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
  printf("\nbug: ");
  f2__print(cause, f2__bug__new(cause, f2__bug__bug_type(cause, this), print_frame));
  
  f2ptr fiber = f2__frame__lookup_var_value(cause, bug_frame, new__symbol(cause, "fiber"), nil);
  if (raw__fiber__is_type(cause, fiber)) {
    printf("\nstack trace: ");
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
  if (! raw__bug__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bug__pretty_print(cause, this);
}
def_pcfunk1(bug__pretty_print, this, return f2__bug__pretty_print(this_cause, this));


// **

void f2__bug__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __bug__symbol = new__symbol(cause, "bug");
}


void f2__bug__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "bug", "", &f2__bug__reinitialize_globalvars);
  
  f2__bug__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // bug
  
  initialize_primobject_2_slot(bug, bug_type, frame);
  
  f2__primcfunk__init__1(bug__pretty_print, this, "Prints a bug object for human readability, suppressing large objects from printing in their entirety.");
  
}


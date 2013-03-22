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

f2ptr f2__exp__documentation(f2ptr cause, f2ptr exp) {
  if (raw__cfunk__is_type(cause, exp)) {
    return f2cfunk__documentation(exp, cause);
  } else if (raw__metrocfunk__is_type(cause, exp)) {
    return raw__metrocfunk__documentation(cause, exp);
  } else if (raw__funk__is_type(cause, exp)) {
    return f2funk__documentation(exp, cause);
  } else if (raw__metro__is_type(cause, exp)) {
    return raw__metro__documentation(cause, exp);
  } else {
    return nil;
  }
}

f2ptr f2__environment__apropos(f2ptr cause, f2ptr this, f2ptr find_string) {
  assert_argument_type(environment, this);
  assert_argument_type(string,      find_string);
  
  f2ptr match_frame = f2__frame__new(cause, nil);
  f2ptr frame       = f2environment__frame(this, cause);
  
  frame__iteration(cause, frame, type_slot_name, slot_name, slot_value,
		   boolean_t matches = boolean__false;
		   
		   f2ptr slot_name_string = f2__exp__as__string(cause, slot_name);
		   if (f2__string__contains(cause, slot_name_string, find_string) != nil) {
		     matches = boolean__true;
		   }
		   if (! matches) {
		     f2ptr documentation = f2__exp__documentation(cause, slot_value);
		     if (raw__string__is_type(cause, documentation)) {
		       if (f2__string__contains(cause, documentation, find_string) != nil) {
			 matches = boolean__true;
		       }
		     }
		   }
		   
		   if (matches) {
		     f2__frame__add_type_var_value(cause, match_frame, type_slot_name, slot_name, slot_value);
		   }
		   );
  
  return match_frame;
}

f2ptr f2__apropos(f2ptr cause, f2ptr find_string) {
  return f2__environment__apropos(cause, global_environment(), find_string);
}
def_pcfunk1(apropos, find_string,
	    "",
	    return f2__apropos(this_cause, find_string));



// **

void f2__apropos__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(apropos);
  
}

void f2__apropos__reinitialize_globalvars() {
  f2__primcfunk__init(apropos);
}

void f2__apropos__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "apropos", "", &f2__apropos__reinitialize_globalvars, &f2__apropos__defragment__fix_pointers);
  
  f2__apropos__reinitialize_globalvars();
}


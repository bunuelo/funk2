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


f2ptr f2__larva__invalid_value__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name,
				    f2ptr value_name, f2ptr value) {
  f2ptr value_was_larva = nil;
  if (raw__larva__is_type(cause, value)) {
    value_was_larva = f2bool__new(boolean__true);
    value           = f2__bug__new_from_larva(cause, value);
  }
  return f2larva__new(cause, 7, f2__bug__new(cause, f2integer__new(cause, 7), f2__frame__new(cause, f2list16__new(cause,
														  new__symbol(cause, "bug_type"),           new__symbol(cause, "invalid_value"),
														  new__symbol(cause, "fiber"),              f2__this__try_fiber(cause),
														  new__symbol(cause, "source_filename"),    source_filename,
														  new__symbol(cause, "source_line_number"), source_line_number,
														  new__symbol(cause, "funktion_name"),      funktion_name,
														  new__symbol(cause, "value_name"),         value_name,
														  new__symbol(cause, "value_was_larva"),    value_was_larva,
														  new__symbol(cause, "value"),              value))));
}


f2ptr f2__larva__caught_invalid_value__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name,
					   f2ptr value_name, f2ptr value,
					   f2ptr additional_args) {
  f2ptr value_was_larva = nil;
  if (raw__larva__is_type(cause, value)) {
    value_was_larva = f2bool__new(boolean__true);
    value           = f2__bug__new_from_larva(cause, value);
  }
  f2ptr bug_frame = f2__frame__new(cause, f2list16__new(cause,
							new__symbol(cause, "bug_type"),           new__symbol(cause, "invalid_value"),
							new__symbol(cause, "fiber"),              f2__this__try_fiber(cause),
							new__symbol(cause, "source_filename"),    source_filename,
							new__symbol(cause, "source_line_number"), source_line_number,
							new__symbol(cause, "funktion_name"),      funktion_name,
							new__symbol(cause, "value_name"),         value_name,
							new__symbol(cause, "value_was_larva"),    value_was_larva,
							new__symbol(cause, "value"),              value));
  if (raw__conslist__is_type(cause, additional_args)) {
    f2ptr iter = additional_args;
    while (iter != nil) {
      f2ptr additional_arg_name  = f2__cons__car(cause, iter);
      iter = f2__cons__cdr(cause, iter);
      if (iter != nil) {
	f2ptr additional_arg_value = f2__cons__car(cause, iter);
	if (raw__larva__is_type(cause, additional_arg_value)) {
	  f2ptr additional_arg_value__bug = f2__bug__new_from_larva(cause, additional_arg_value);
	  f2__frame__add_var_value(cause, bug_frame, additional_arg_name, additional_arg_value__bug);
	} else {
	  f2__frame__add_var_value(cause, bug_frame, additional_arg_name, additional_arg_value);
	}
	iter = f2__cons__cdr(cause, iter);
      } else {
	f2__frame__add_var_value(cause, bug_frame, additional_arg_name, new__symbol(cause, "<no-bug-argument-value>"));
      }
    }
  } else {
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug-argument-values"), new__symbol(cause, "<invalid>"));
  }
  return f2larva__new(cause, 8, f2__bug__new(cause, f2integer__new(cause, 8), bug_frame));
}


f2ptr f2__larva__error__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name, f2ptr frame_args) {
  f2ptr bug_frame = f2__frame__new(cause, frame_args);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),           new__symbol(cause, "error"));
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "fiber"),              f2__this__try_fiber(cause));
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_filename"),    source_filename);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line_number"), source_line_number);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funktion_name"),      funktion_name);
  return f2larva__new(cause, 13, f2__bug__new(cause, f2integer__new(cause, 13), bug_frame));
}


f2ptr f2__larva__invalid_argument_type__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name,
					    f2ptr correct_type, f2ptr actual_type, f2ptr argument_name, f2ptr argument_value) {
  f2ptr argument_value_was_larva = nil;
  if (raw__larva__is_type(cause, argument_value)) {
    argument_value_was_larva = f2bool__new(boolean__true);
    argument_value           = f2__bug__new_from_larva(cause, argument_value);
  }
  return f2__larva__error__new(cause, source_filename, source_line_number, funktion_name,
			       f2list14__new(cause,
					     new__symbol(cause, "bug_name"),                 new__symbol(cause, "invalid_argument_type"),
					     new__symbol(cause, "fiber"),                    f2__this__try_fiber(cause),
					     new__symbol(cause, "correct_type"),             correct_type,
					     new__symbol(cause, "actual_type"),              actual_type,
					     new__symbol(cause, "argument_name"),            argument_name,
					     new__symbol(cause, "argument_value_was_larva"), argument_value_was_larva,
					     new__symbol(cause, "argument_value"),           argument_value));
}


// **

void f2__larva__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  
}

void f2__larva__reinitialize_globalvars() {
}

void f2__larva__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "larva", "", &f2__larva__reinitialize_globalvars, &f2__larva__defragment__fix_pointers);
  
  f2__larva__reinitialize_globalvars();
}


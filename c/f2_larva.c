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

#include "funk2.h"


f2ptr f2__larva__invalid_argument_type__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name,
					    f2ptr correct_type, f2ptr actual_type, f2ptr argument_name, f2ptr argument_value) {
  return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list16__new(cause,
														  new__symbol(cause, "bug_type"),           new__symbol(cause, "invalid_argument_type"),
														  new__symbol(cause, "source_filename"),    source_filename,
														  new__symbol(cause, "source_line_number"), source_line_number,
														  new__symbol(cause, "funktion_name"),      funktion_name,
														  new__symbol(cause, "correct_type"),       correct_type,
														  new__symbol(cause, "actual_type"),        actual_type,
														  new__symbol(cause, "argument_name"),      argument_name,
														  new__symbol(cause, "argument_value"),     argument_value))));
}



// **

void f2__larva__reinitialize_globalvars() {
  //f2ptr cause = initial_cause();
  
}


void f2__larva__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "larva", "", &f2__larva__reinitialize_globalvars);
  
  f2__larva__reinitialize_globalvars();
  //f2ptr cause = initial_cause();
  
}


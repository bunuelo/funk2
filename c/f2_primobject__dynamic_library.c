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

// dynamic_library

defprimobject__static_slot(dynamic_library__type,      0);
defprimobject__static_slot(dynamic_library__directory, 1);
defprimobject__static_slot(dynamic_library__name,      2);

f2ptr __dynamic_library__symbol = -1;

f2ptr f2dynamic_library__new__trace_depth(f2ptr cause, f2ptr type, f2ptr directory, f2ptr name, int trace_depth) {
  release__assert(__dynamic_library__symbol != -1, nil, "f2dynamic_library__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __dynamic_library__symbol, 3, nil, trace_depth);
  f2dynamic_library__type__set__trace_depth(     this, cause, type,      trace_depth);
  f2dynamic_library__directory__set__trace_depth(this, cause, directory, trace_depth);
  f2dynamic_library__name__set__trace_depth(     this, cause, name,      trace_depth);
  return this;
}

f2ptr f2dynamic_library__new(f2ptr cause, f2ptr type, f2ptr directory, f2ptr name) {
  return f2dynamic_library__new__trace_depth(cause, type, directory, name, 1);
}

// **

void f2__primobject__dynamic_library__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __dynamic_library__symbol = new__symbol(cause, "dynamic_library");
}

void f2__primobject__dynamic_library__defragment__fix_pointers() {
  // -- reinitialize --
  
  defragment__fix_pointer(__dynamic_library__symbol);
  
  
  // -- initialize --
  
  
}

void f2__primobject__dynamic_library__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__dynamic_library", "", &f2__primobject__dynamic_library__reinitialize_globalvars, &f2__primobject__dynamic_library__defragment__fix_pointers);
  
  f2__primobject__dynamic_library__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __dynamic_library__symbol, nil);
}


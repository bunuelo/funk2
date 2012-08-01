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

// int setenv(const char *name, const char *value, int overwrite);

f2ptr f2__setenv(f2ptr cause, f2ptr name, f2ptr value, f2ptr overwrite) {
  return nil;
}
def_pcfunk3(setenv, name, value, overwrite,
	    "",
	    return f2__setenv(this_cause, name, value, overwrite));


// **

void f2__primfunks__stdlib__defragment__fix_pointers() {
  f2__primcfunk__init__defragment__fix_pointers(setenv);
}

void f2__primfunks__stdlib__reinitialize_globalvars() {
  f2__primcfunk__init(setenv);
}

void f2__primfunks__stdlib__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks-stdlib", "", &f2__primfunks__stdlib__reinitialize_globalvars, &f2__primfunks__stdlib__defragment__fix_pointers);
  
  f2__primfunks__stdlib__reinitialize_globalvars();
}


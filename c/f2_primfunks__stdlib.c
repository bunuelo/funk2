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
  u64 name__utf8_length = f2string__utf8_length(intersperse_string, cause);
  u8* name__utf8_str    = (u8*)from_ptr(f2__malloc((name__utf8_length + 1) * sizeof(u8)));
  raw__string__utf8_str_copy(cause, name, name__utf8_str);
  u64 value__utf8_length = f2string__utf8_length(intersperse_string, cause);
  u8* value__utf8_str    = (u8*)from_ptr(f2__malloc((value__utf8_length + 1) * sizeof(u8)));
  raw__string__utf8_str_copy(cause, value, value__utf8_str);
  int overwrite__i = f2integer__i(overwrite, cause);
  int result = setenv(name__utf8_str, value__utf8_str, overwrite__i);
  f2__free(to_ptr(name__utf8_str));
  f2__free(to_ptr(value__utf8_str));
  return f2integer__new(cause, result);
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


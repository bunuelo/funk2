// 
// Copyright (c) 2007-2009 Bo Morgan.
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

f2ptr f2__stringlist__new_string_from_concatenation(f2ptr cause, f2ptr this) {
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__consp(iter, cause)) {return f2larva__new(cause, 1);}
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__stringp(str, cause)) {return f2larva__new(cause, 1);}
      u64 str_length = f2string__length(str, cause);
      total_length += str_length;
      iter = f2cons__cdr(iter, cause);
    }
  }
  u8* temp_str = (u8*)malloc(total_length + 1);
  u64 index = 0;
  {
    f2ptr iter = this;
    while (iter) {
      f2ptr str = f2cons__car(iter, cause);
      u64 str_length = f2string__length(str, cause);
      f2string__str_copy(str, cause, temp_str + index);
      index += str_length;
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr new_string = f2string__new(cause, total_length, temp_str);
  free(temp_str);
  return new_string;
}
def_pcfunk1(stringlist__concat, this, return f2__stringlist__new_string_from_concatenation(this_cause, this));

f2ptr f2__stringlist__new_string_from_intersperse(f2ptr cause, f2ptr this, f2ptr intersperse_string) {
  if (! raw__stringp(intersperse_string, cause)) {
    return f2larva__new(cause, 1);
  }
  u64 intersperse_string__length = f2string__length(intersperse_string, cause);
  u8* intersperse_string__str    = malloc(intersperse_string__length + 1);
  f2string__str_copy(intersperse_string, cause, intersperse_string__str);
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__consp(iter, cause)) {return f2larva__new(cause, 1);}
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__stringp(str, cause)) {return f2larva__new(cause, 1);}
      u64 str_length = f2string__length(str, cause);
      total_length += str_length;
      iter = f2cons__cdr(iter, cause);
      if (iter) {
	total_length += intersperse_string__length;
      }
    }
  }
  u8* temp_str = (u8*)malloc(total_length + 1);
  u64 index = 0;
  {
    f2ptr iter = this;
    while (iter) {
      f2ptr str = f2cons__car(iter, cause);
      u64 str_length = f2string__length(str, cause);
      f2string__str_copy(str, cause, temp_str + index);
      index += str_length;
      iter = f2cons__cdr(iter, cause);
      if (iter) {
	memcpy(temp_str + index, intersperse_string__str, intersperse_string__length);
	index += intersperse_string__length;
      }
    }
  }
  f2ptr new_string = f2string__new(cause, total_length, temp_str);
  free(temp_str);
  free(intersperse_string__str);
  return new_string;
}
def_pcfunk2(stringlist__intersperse, this, intersperse_string, return f2__stringlist__new_string_from_intersperse(this_cause, this, intersperse_string));


void f2__string__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__string__initialize() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__primobject_frame__reinitialize_globalvars();
  
  f2__primcfunk__init(stringlist__concat);
  f2__primcfunk__init(stringlist__intersperse);
  
  resume_gc();
  try_gc();
}


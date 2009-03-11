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

#define F2__DLFCN__SUPPORTED

bool raw__dlfcn__supported() {
#ifdef F2__DLFCN__SUPPORTED
  return true;
#else
  return false;
#endif
}

f2ptr f2__dlfcn__supported(f2ptr cause) {
  return f2bool__new(raw__dlfcn__supported());
}
def_pcfunk0(dlfcn__supported, return f2__dlfcn__supported(this_cause));

void* raw__dlfcn__dlopen(char* filename, int flag) {
#ifdef F2__DLFCN__SUPPORTED
  return dlopen(filename, flag);
#else
  return NULL;
#endif
}

f2ptr f2__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag) {
  if ((! raw__stringp(filename, cause)) ||
      (! raw__integerp(flag, cause))) {
    return f2larva__new(cause, 1);
  }
  int filename__length = f2string__length(filename, cause);
  u8* raw_filename = (u8*)alloca(filename__length + 1);
  f2string__str_copy(filename, cause, raw_filename);
  raw_filename[filename__length] = 0;
  int raw_flag = f2integer__i(flag, cause);
  return f2pointer__new(cause, to_ptr(raw__dlfcn__dlopen(raw_filename, raw_flag)));
}
def_pcfunk2(dlfcn__dlopen, filename, flag, return f2__dlfcn__dlopen(this_cause, filename, flag));

char* raw__dlfcn__dlerror() {
#ifdef F2__DLFCN__SUPPORTED
  return dlerror();
#else
  return NULL;
#endif
}

f2ptr f2__dlfcn__dlerror(f2ptr cause) {
  char* str = raw__dlfcn__dlerror();
  if (str == NULL) {
    return nil;
  }
  return f2string__new(cause, strlen(str), str);
}
def_pcfunk0(dlfcn__dlerror, return f2__dlfcn__dlerror(this_cause));

void* raw__dlfcn__dlsym(void* handle, char* symbol) {
#ifdef F2__DLFCN__SUPPORTED
  return dlsym(handle, symbol);
#else
  return NULL;
#endif
}

f2ptr f2__dlfcn__dlsym(f2ptr cause, f2ptr handle, f2ptr symbol) {
  if ((! raw__pointerp(handle, cause)) ||
      (! raw__stringp(symbol, cause))) {
    return f2larva__new(cause, 1);
  }
  ptr raw_handle = f2pointer__p(handle, cause);
  int symbol__length = f2string__length(symbol, cause);
  u8* raw_symbol = (u8*)alloca(symbol__length + 1);
  f2string__str_copy(symbol, cause, raw_symbol);
  raw_symbol[symbol__length] = 0;
  ptr result = raw__dlfcn__dlsym(from_ptr(raw_handle), raw_symbol);
  if (result == to_ptr(NULL)) {
    return nil;
  }
  return f2pointer__new(cause, result);
}
def_pcfunk2(dlfcn__dlsym, handle, symbol, return f2__dlfcn__dlsym(this_cause, handle, symbol));

int raw__dlfcn__dlclose(void* handle) {
#ifdef F2__DLFCN__SUPPORTED
  return dlclose(handle);
#else
  return -1;
#endif
}

f2ptr f2__dlfcn__dlclose(f2ptr cause, f2ptr handle) {
  if (! raw__pointerp(handle, cause)) {
    return f2larva__new(cause, 1);
  }
  ptr raw_handle = f2pointer__p(handle, cause);
  return f2integer__new(cause, raw__dlfcn__dlclose(from_ptr(raw_handle)));
}
def_pcfunk1(dlfcn__dlclose, handle, return f2__dlfcn__dlclose(this_cause, handle));

// **

void f2__dlfcn__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_dlfcn_c__cause__new(initial_cause(), nil, nil);
  
}

void f2__dlfcn__initialize() {
  pause_gc();
  f2__dlfcn__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_dlfcn_c__cause__new(initial_cause(), nil, nil);
  
  f2__funktional_primcfunk__init__0(dlfcn__supported);
  f2__primcfunk__init__2(           dlfcn__dlopen, filename, flag);
  f2__primcfunk__init__0(           dlfcn__dlerror);
  f2__primcfunk__init__2(           dlfcn__dlsym, handle, symbol);
  f2__primcfunk__init__1(           dlfcn__dlclose, handle);
  
  resume_gc();
  try_gc();
}


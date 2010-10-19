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

// raw dlfcn function wrappers

boolean_t raw__dlfcn__supported() {
#ifdef F2__DLFCN__SUPPORTED
  return boolean__true;
#else
  return boolean__false;
#endif
}

f2ptr f2__dlfcn__supported(f2ptr cause) {
  return f2bool__new(raw__dlfcn__supported());
}
def_pcfunk0(dlfcn__supported, return f2__dlfcn__supported(this_cause));

ptr raw__dlfcn__dlopen(u8* filename, int flag) {
#ifdef F2__DLFCN__SUPPORTED
  return to_ptr(dlopen((char*)filename, flag));
#else
  return to_ptr(NULL);
#endif
}


f2ptr raw__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag) {
  int filename__length = f2string__length(filename, cause);
  u8* raw_filename     = (u8*)alloca(filename__length + 1);
  f2string__str_copy(filename, cause, raw_filename);
  raw_filename[filename__length] = 0;
  int raw_flag = flag ? f2integer__i(flag, cause) : (RTLD_LAZY | RTLD_GLOBAL);
  ptr result = to_ptr(raw__dlfcn__dlopen(raw_filename, raw_flag));
  if (! result) {
    status("f2__dlfcn__dlopen: failed to load library, \"%s\".", raw_filename);
    char* dlerror_string = raw__dlfcn__dlerror();
    return f2larva__new(cause, 923, f2__bug__new(cause, f2integer__new(cause, 923), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"),      new__symbol(cause, "could_not_open_dlfcn_dynamic_library"),
															new__symbol(cause, "funkname"),      new__symbol(cause, "dlfcn-dlopen"),
															new__symbol(cause, "filename"),      filename,
															new__symbol(cause, "flag"),          flag,
															new__symbol(cause, "dlfcn-dlerror"), new__string(cause, dlerror_string)))));
  }
  status("f2__dlfcn__dlopen: successfully loaded library, \"%s\".", raw_filename);
  return f2pointer__new(cause, result);
}

f2ptr f2__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag) {
  if ((! raw__string__is_type(cause, filename)) ||
      (flag && (! raw__integer__is_type(cause, flag)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__dlfcn__dlopen(cause, filename, flag);
}
def_pcfunk2(dlfcn__dlopen, filename, flag, return f2__dlfcn__dlopen(this_cause, filename, flag));


u8* raw__dlfcn__dlerror() {
#ifdef F2__DLFCN__SUPPORTED
  return (u8*)dlerror();
#else
  return (u8*)NULL;
#endif
}

f2ptr f2__dlfcn__dlerror(f2ptr cause) {
  u8* str = raw__dlfcn__dlerror();
  if (str == NULL) {
    return nil;
  }
  return f2string__new(cause, strlen((char*)str), str);
}
def_pcfunk0(dlfcn__dlerror, return f2__dlfcn__dlerror(this_cause));

ptr raw__dlfcn__dlsym(ptr handle, u8* symbol) {
#ifdef F2__DLFCN__SUPPORTED
  return to_ptr(dlsym(from_ptr(handle), (char*)symbol));
#else
  return to_ptr(NULL);
#endif
}

f2ptr f2__dlfcn__dlsym(f2ptr cause, f2ptr handle, f2ptr symbol) {
  if ((! raw__pointer__is_type(cause, handle)) ||
      (! raw__string__is_type(cause, symbol))) {
    return f2larva__new(cause, 1, nil);
  }
  ptr raw_handle = f2pointer__p(handle, cause);
  int symbol__length = f2string__length(symbol, cause);
  u8* raw_symbol = (u8*)alloca(symbol__length + 1);
  f2string__str_copy(symbol, cause, raw_symbol);
  raw_symbol[symbol__length] = 0;
  ptr result = raw__dlfcn__dlsym(raw_handle, raw_symbol);
  if (result == to_ptr(NULL)) {
    return nil;
  }
  return f2pointer__new(cause, result);
}
def_pcfunk2(dlfcn__dlsym, handle, symbol, return f2__dlfcn__dlsym(this_cause, handle, symbol));


int raw__dlfcn__dlclose(ptr handle) {
#ifdef F2__DLFCN__SUPPORTED
  return dlclose(from_ptr(handle));
#else
  return -1;
#endif
}

f2ptr f2__dlfcn__dlclose(f2ptr cause, f2ptr handle) {
  if (! raw__pointer__is_type(cause, handle)) {
    return f2larva__new(cause, 1, nil);
  }
  ptr raw_handle = f2pointer__p(handle, cause);
  return f2integer__new(cause, raw__dlfcn__dlclose(raw_handle));
}
def_pcfunk1(dlfcn__dlclose, handle, return f2__dlfcn__dlclose(this_cause, handle));

u64 raw__dlfcn__rtld_lazy() {
#ifdef F2__DLFCN__SUPPORTED
  return (u64)RTLD_LAZY;
#else
  return 0;
#endif
}

f2ptr f2__dlfcn__rtld_lazy(f2ptr cause) {
  return f2integer__new(cause, raw__dlfcn__rtld_lazy());
}
def_pcfunk0(dlfcn__rtld_lazy, return f2__dlfcn__rtld_lazy(this_cause));

u64 raw__dlfcn__rtld_now() {
#ifdef F2__DLFCN__SUPPORTED
  return (u64)RTLD_NOW;
#else
  return 0;
#endif
}

f2ptr f2__dlfcn__rtld_now(f2ptr cause) {
  return f2integer__new(cause, raw__dlfcn__rtld_now());
}
def_pcfunk0(dlfcn__rtld_now, return f2__dlfcn__rtld_now(this_cause));

u64 raw__dlfcn__rtld_global() {
#ifdef F2__DLFCN__SUPPORTED
  return (u64)RTLD_GLOBAL;
#else
  return 0;
#endif
}

f2ptr f2__dlfcn__rtld_global(f2ptr cause) {
  return f2integer__new(cause, raw__dlfcn__rtld_global());
}
def_pcfunk0(dlfcn__rtld_global, return f2__dlfcn__rtld_global(this_cause));

u64 raw__dlfcn__rtld_local() {
#if defined(F2__DLFCN__SUPPORTED) && (! defined(F2__CYGWIN))
  return (u64)RTLD_LOCAL;
#else
  return 0;
#endif
}

f2ptr f2__dlfcn__rtld_local(f2ptr cause) {
  return f2integer__new(cause, raw__dlfcn__rtld_local());
}
def_pcfunk0(dlfcn__rtld_local, return f2__dlfcn__rtld_local(this_cause));

u64 raw__dlfcn__rtld_nodelete() {
#if defined(F2__DLFCN__SUPPORTED) && (! defined(F2__CYGWIN))
  return (u64)RTLD_NODELETE;
#else
  return 0;
#endif
}

f2ptr f2__dlfcn__rtld_nodelete(f2ptr cause) {
  return f2integer__new(cause, raw__dlfcn__rtld_nodelete());
}
def_pcfunk0(dlfcn__rtld_nodelete, return f2__dlfcn__rtld_nodelete(this_cause));

u64 raw__dlfcn__rtld_noload() {
#if defined(F2__DLFCN__SUPPORTED) && (! defined(F2__CYGWIN))
  return (u64)RTLD_NOLOAD;
#else
  return 0;
#endif
}

f2ptr f2__dlfcn__rtld_noload(f2ptr cause) {
  return f2integer__new(cause, raw__dlfcn__rtld_noload());
}
def_pcfunk0(dlfcn__rtld_noload, return f2__dlfcn__rtld_noload(this_cause));



// dlfcn_dynamic_library

def_frame_object__global__1_slot(dlfcn_dynamic_library, pointer);

f2ptr f2__dlfcn_dynamic_library__new(f2ptr cause, f2ptr pointer) {
  return f2dlfcn_dynamic_library__new(cause, pointer);
}


f2ptr raw__dlfcn_dynamic_library__new_open(f2ptr cause, f2ptr filename, f2ptr flag) {
  f2ptr dlfcn_pointer = f2__dlfcn__open(cause, filename, flag);
  if (raw__larva__is_type(cause, dlfcn_pointer)) {
    return dlfcn_pointer;
  }
  return f2__dlfcn_dynamic_library__new(cause, dlfcn_pointer);
}

f2ptr f2__dlfcn_dynamic_library__new_open(f2ptr cause, f2ptr filename, f2ptr flag) {
  if ((! raw__string__is_type(cause, filename)) ||
      (flag && (! raw__integer__is_type(cause, flag)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__dlfcn_dynamic_library__new_copy(cause, filename, flag);
}
def_pcfunk2(dlfcn_dynamic_library__new_open, filename, flag, return f2__dlfcn_dynamic_library__new_open(this_cause, filename, flag));


f2ptr raw__dlfcn_dynamic_library__lookup_symbol(f2ptr cause, f2ptr this, f2ptr symbol) {
  f2ptr dlfcn_pointer = f2__dlfcn_dynamic_library__pointer(cause, this);
  return f2__dlfcn__dlsym(cause, dlfcn_pointer, symbol);
}

f2ptr f2__dlfcn_dynamic_library__lookup_symbol(f2ptr cause, f2ptr this, f2ptr symbol) {
  if ((! raw__dlfcn_dynamic_library__is_type(cause, this)) ||
      (! raw__symbol__is_type(cause, symbol))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__dlfcn_dynamic_library__lookup_symbol(cause, this, symbol);
}
def_pcfunk2(dlfcn_dynamic_library__lookup_symbol, this, symbol, return f2__dlfcn_dynamic_library__lookup_symbol(this_cause, this, symbol));


f2ptr raw__dlfcn_dynamic_library__close(f2ptr cause, f2ptr this) {
  f2ptr dlfcn_pointer = f2__dlfcn_dynamic_library__pointer(cause, this);
  return f2__dlfcn__dlclose(cause, dlfcn_pointer);
}

f2ptr f2__dlfcn_dynamic_library__close(f2ptr cause, f2ptr this) {
  if (! raw__dlfcn_dynamic_library__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__dlfcn_dynamic_library__close(cause, this);
}
def_pcfunk1(dlfcn_dynamic_library__close, this, return f2__dlfcn_dynamic_library__close(this_cause, this));


f2ptr f2dlfcn_dynamic_library__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2dlfcn_dynamic_library__primobject_type__new(cause);
  {char* slot_name = "lookup_symbol"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__funk);}
  {char* slot_name = "close";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__funk);}
  return this;
}


// **

void f2__dlfcn__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_dlfcn_c__cause__new(initial_cause(), nil, nil);
  
}

void f2__dlfcn__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "dlfcn", "", &f2__dlfcn__reinitialize_globalvars);
  
  f2__dlfcn__reinitialize_globalvars();
  
  f2__funktional_primcfunk__init__0(dlfcn__supported, "");
  f2__primcfunk__init__2(           dlfcn__dlopen, filename, flag, "");
  f2__primcfunk__init__0(           dlfcn__dlerror, "");
  f2__primcfunk__init__2(           dlfcn__dlsym, handle, symbol, "");
  f2__primcfunk__init__1(           dlfcn__dlclose, handle, "");
  f2__funktional_primcfunk__init__0(dlfcn__rtld_lazy, "");
  f2__funktional_primcfunk__init__0(dlfcn__rtld_now, "");
  f2__funktional_primcfunk__init__0(dlfcn__rtld_global, "");
  f2__funktional_primcfunk__init__0(dlfcn__rtld_local, "");
  f2__funktional_primcfunk__init__0(dlfcn__rtld_nodelete, "");
  f2__funktional_primcfunk__init__0(dlfcn__rtld_noload, "");
  
  
  // dlfcn_dynamic_library
  
  init_frame_object__1_slot(dlfcn_dynamic_library, pointer);
  
  f2__primcfunk__init__2(dlfcn_dynamic_library__new_open, filename, flag, "");
  
  {char* symbol_str = "lookup_symbol"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(dlfcn_dynamic_library__lookup_symbol, this, symbol, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__funk = never_gc(cfunk);}
  
  {char* symbol_str = "close"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(dlfcn_dynamic_library__close, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__funk = never_gc(cfunk);}
  
  
}


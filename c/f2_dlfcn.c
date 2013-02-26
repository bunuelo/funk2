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
def_pcfunk0(dlfcn__supported,
	    "",
	    return f2__dlfcn__supported(this_cause));

ptr raw__dlfcn__dlopen_ex(u8* filename, int flag) {
#ifdef F2__DLFCN__SUPPORTED
  return to_ptr(dlopen((char*)filename, flag));
#else
  return to_ptr(NULL);
#endif
}


f2ptr raw__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag) {
  int filename__utf8_length = raw__string__utf8_length(cause, filename);
  u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
  raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
  filename__utf8_str[filename__utf8_length] = 0;
  int raw_flag = flag ? f2integer__i(flag, cause) : (RTLD_LAZY | RTLD_GLOBAL);
  ptr result = to_ptr(raw__dlfcn__dlopen_ex(filename__utf8_str, raw_flag));
  if (! result) {
    status("f2__dlfcn__dlopen: failed to load library, \"%s\".", filename__utf8_str);
    char* dlerror_string = (char*)raw__dlfcn__dlerror();
    return f2larva__new(cause, 923, f2__bug__new(cause, f2integer__new(cause, 923), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"),      new__symbol(cause, "could_not_open_dlfcn_dynamic_library"),
															new__symbol(cause, "funkname"),      new__symbol(cause, "dlfcn-dlopen"),
															new__symbol(cause, "filename"),      filename,
															new__symbol(cause, "flag"),          flag,
															new__symbol(cause, "dlfcn-dlerror"), new__string(cause, dlerror_string)))));
  }
  status("f2__dlfcn__dlopen: successfully loaded library, \"%s\".", filename__utf8_str);
  f2ptr dynamic_library_pointer = f2pointer__new(cause, result);
  f2__free(to_ptr(filename__utf8_str));
  return dynamic_library_pointer;
}

f2ptr f2__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag) {
  assert_argument_type(       string,  filename);
  assert_argument_type_or_nil(integer, flag);
  return raw__dlfcn__dlopen(cause, filename, flag);
}
def_pcfunk2(dlfcn__dlopen, filename, flag,
	    "",
	    return f2__dlfcn__dlopen(this_cause, filename, flag));


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
  return new__string(cause, (char*)str);
}
def_pcfunk0(dlfcn__dlerror,
	    "",
	    return f2__dlfcn__dlerror(this_cause));

ptr raw__dlfcn__dlsym(ptr handle, u8* symbol) {
#ifdef F2__DLFCN__SUPPORTED
  return to_ptr(dlsym(from_ptr(handle), (char*)symbol));
#else
  return to_ptr(NULL);
#endif
}

f2ptr f2__dlfcn__dlsym(f2ptr cause, f2ptr handle, f2ptr symbol) {
  assert_argument_type(pointer, handle);
  assert_argument_type(symbol,  symbol);
  ptr raw_handle = f2pointer__p(handle, cause);
  u64 symbol__utf8_length = raw__symbol__utf8_length(cause, symbol);
  u8* symbol__utf8_str    = (u8*)alloca(symbol__utf8_length + 1);
  raw__symbol__utf8_str_copy(cause, symbol, symbol__utf8_str);
  symbol__utf8_str[symbol__utf8_length] = 0;
  ptr result = raw__dlfcn__dlsym(raw_handle, symbol__utf8_str);
  if (result == to_ptr(NULL)) {
    return nil;
  }
  return f2pointer__new(cause, result);
}
def_pcfunk2(dlfcn__dlsym, handle, symbol,
	    "",
	    return f2__dlfcn__dlsym(this_cause, handle, symbol));


int raw__dlfcn__dlclose(ptr handle) {
#ifdef F2__DLFCN__SUPPORTED
  return dlclose(from_ptr(handle));
#else
  return -1;
#endif
}

f2ptr f2__dlfcn__dlclose(f2ptr cause, f2ptr handle) {
  assert_argument_type(pointer, handle);
  ptr raw_handle = f2pointer__p(handle, cause);
  return f2integer__new(cause, raw__dlfcn__dlclose(raw_handle));
}
def_pcfunk1(dlfcn__dlclose, handle,
	    "",
	    return f2__dlfcn__dlclose(this_cause, handle));

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
def_pcfunk0(dlfcn__rtld_lazy,
	    "",
	    return f2__dlfcn__rtld_lazy(this_cause));

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
def_pcfunk0(dlfcn__rtld_now,
	    "",
	    return f2__dlfcn__rtld_now(this_cause));

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
def_pcfunk0(dlfcn__rtld_global,
	    "",
	    return f2__dlfcn__rtld_global(this_cause));

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
def_pcfunk0(dlfcn__rtld_local,
	    "",
	    return f2__dlfcn__rtld_local(this_cause));

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
def_pcfunk0(dlfcn__rtld_nodelete,
	    "",
	    return f2__dlfcn__rtld_nodelete(this_cause));

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
def_pcfunk0(dlfcn__rtld_noload,
	    "",
	    return f2__dlfcn__rtld_noload(this_cause));



// dlfcn_dynamic_library

def_frame_object__global__4_slot(dlfcn_dynamic_library, pointer, filename, stat, pointer_symbol_hash);

f2ptr f2__dlfcn_dynamic_library__new(f2ptr cause, f2ptr pointer, f2ptr filename, f2ptr stat) {
  f2ptr pointer_symbol_hash = f2__ptypehash__new(cause);
  return f2dlfcn_dynamic_library__new(cause, pointer, filename, stat, pointer_symbol_hash);
}


f2ptr raw__dlfcn_dynamic_library__new_open(f2ptr cause, f2ptr filename, f2ptr flag, f2ptr search_pathnames) {
  f2ptr stat;
  f2ptr full_filename = nil;
  {
    f2ptr search_pathnames__iter = assert_value(search_pathnames);
    {
      boolean_t keep_searching = (search_pathnames__iter != nil);
      while (keep_searching) {
	f2ptr search_pathname = assert_value(f2__cons__car(cause, search_pathnames__iter));
	full_filename   = assert_value(f2__pathname__concat(cause, search_pathname, filename));
	stat = f2__pathname__stat(cause, full_filename);
	if (raw__larva__is_type(cause, stat)) {
	  search_pathnames__iter = assert_value(f2__cons__cdr(cause, search_pathnames__iter));
	  keep_searching         = (search_pathnames__iter != nil);
	} else {
	  keep_searching = boolean__false;
	}
      }
    }
  }
  if (full_filename == nil) {
    return new__error(f2list8__new(cause,
				   new__symbol(cause, "bug_name"),         new__symbol(cause, "could_not_find_dynamic_library_in_search_path"),
				   new__symbol(cause, "filename"),         filename,
				   new__symbol(cause, "flag"),             flag,
				   new__symbol(cause, "search_pathnames"), search_pathnames));
  }
  f2ptr dlfcn_pointer = assert_value(f2__dlfcn__dlopen(cause, full_filename, flag));
  return f2__dlfcn_dynamic_library__new(cause, dlfcn_pointer, filename, stat);
}

f2ptr f2__dlfcn_dynamic_library__new_open(f2ptr cause, f2ptr filename, f2ptr flag, f2ptr search_pathnames) {
  assert_argument_type(       string, filename);
  assert_argument_type_or_nil(integer, flag);
  return raw__dlfcn_dynamic_library__new_open(cause, filename, flag, search_pathnames);
}
def_pcfunk3(dlfcn_dynamic_library__new_open, filename, flag, search_pathnames,
	    "",
	    return f2__dlfcn_dynamic_library__new_open(this_cause, filename, flag, search_pathnames));


f2ptr raw__dlfcn_dynamic_library__lookup_symbol(f2ptr cause, f2ptr this, f2ptr symbol) {
  f2ptr pointer_symbol_hash = f2__dlfcn_dynamic_library__pointer_symbol_hash(cause, this);
  f2ptr symbol_pointer      = raw__ptypehash__lookup(cause, pointer_symbol_hash, symbol);
  if (symbol_pointer == nil) {
    f2ptr dlfcn_pointer = f2__dlfcn_dynamic_library__pointer(cause, this);
    symbol_pointer      = f2__dlfcn__dlsym(cause, dlfcn_pointer, symbol);
    raw__ptypehash__add(cause, pointer_symbol_hash, symbol, symbol_pointer);
  }
  return symbol_pointer;
}

f2ptr f2__dlfcn_dynamic_library__lookup_symbol(f2ptr cause, f2ptr this, f2ptr symbol) {
  assert_argument_type(dlfcn_dynamic_library, this);
  assert_argument_type(symbol,                symbol);
  return raw__dlfcn_dynamic_library__lookup_symbol(cause, this, symbol);
}
def_pcfunk2(dlfcn_dynamic_library__lookup_symbol, this, symbol,
	    "",
	    return f2__dlfcn_dynamic_library__lookup_symbol(this_cause, this, symbol));


f2ptr raw__dlfcn_dynamic_library__close(f2ptr cause, f2ptr this) {
  f2ptr dlfcn_pointer = f2__dlfcn_dynamic_library__pointer(cause, this);
  return f2__dlfcn__dlclose(cause, dlfcn_pointer);
}

f2ptr f2__dlfcn_dynamic_library__close(f2ptr cause, f2ptr this) {
  assert_argument_type(dlfcn_dynamic_library, this);
  return raw__dlfcn_dynamic_library__close(cause, this);
}
def_pcfunk1(dlfcn_dynamic_library__close, this,
	    "",
	    return f2__dlfcn_dynamic_library__close(this_cause, this));


f2ptr raw__dlfcn_dynamic_library__current_stat(f2ptr cause, f2ptr this, f2ptr search_pathnames) {
  f2ptr filename = assert_value(f2__dlfcn_dynamic_library__filename(cause, this));
  {
    f2ptr iter = search_pathnames;
    while (iter != nil) {
      f2ptr search_pathname = assert_value(f2__cons__car(cause, iter));
      f2ptr full_filename   = f2__pathname__concat(cause, search_pathname, filename);
      f2ptr stat            = f2__pathname__stat(cause, full_filename);
      if (! raw__larva__is_type(cause, stat)) {
	return stat;
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  return nil;
}

f2ptr raw__dlfcn_dynamic_library__changed_on_disk(f2ptr cause, f2ptr this, f2ptr search_pathnames) {
  f2ptr stat         = assert_value( f2__dlfcn_dynamic_library__stat(        cause, this));
  f2ptr current_stat = assert_value(raw__dlfcn_dynamic_library__current_stat(cause, this, search_pathnames));
  if ((! raw__frame__is_type(cause, current_stat)) ||
      (! raw__frame__is_type(cause, stat))) {
    return f2larva__new(cause, 227, nil);
  }
  f2ptr time_of_last_modification         = assert_value(f2__frame__lookup_var_value(cause, stat,         new__symbol(cause, "time_of_last_modification"), nil));
  f2ptr current_time_of_last_modification = assert_value(f2__frame__lookup_var_value(cause, current_stat, new__symbol(cause, "time_of_last_modification"), nil));
  if (assert_value(f2__object__equals(cause, time_of_last_modification, current_time_of_last_modification)) != nil) {
    return f2bool__new(boolean__false);
  }
  return f2bool__new(boolean__true);
}

f2ptr f2__dlfcn_dynamic_library__changed_on_disk(f2ptr cause, f2ptr this, f2ptr search_pathnames) {
  assert_argument_type(dlfcn_dynamic_library, this);
  return raw__dlfcn_dynamic_library__changed_on_disk(cause, this, search_pathnames);
}
def_pcfunk2(dlfcn_dynamic_library__changed_on_disk, this, search_pathnames,
	    "",
	    return f2__dlfcn_dynamic_library__changed_on_disk(this_cause, this, search_pathnames));


f2ptr f2dlfcn_dynamic_library__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2dlfcn_dynamic_library__primobject_type__new(cause);
  {char* slot_name = "lookup_symbol";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__funk);}
  {char* slot_name = "close";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__funk);}
  {char* slot_name = "changed_on_disk"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.changed_on_disk__funk);}
  return this;
}


// dlfcn_dynamic_library_handler

def_frame_object__global__3_slot(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_pointer_hash, dlfcn_dynamic_library_filename_hash, search_pathnames);

f2ptr f2__dlfcn_dynamic_library_handler__new(f2ptr cause, f2ptr search_pathnames) {
  f2ptr dlfcn_dynamic_library_pointer_hash  = f2__ptypehash__new(cause);
  f2ptr dlfcn_dynamic_library_filename_hash = f2__ptypehash__new(cause);
  return f2dlfcn_dynamic_library_handler__new(cause, dlfcn_dynamic_library_pointer_hash, dlfcn_dynamic_library_filename_hash, search_pathnames);
}


void raw__dlfcn_dynamic_library_handler__reinit(f2ptr cause, f2ptr this) {
  f2ptr dlfcn_dynamic_library_pointer_hash  = f2__ptypehash__new(cause);
  f2ptr dlfcn_dynamic_library_filename_hash = f2__ptypehash__new(cause);
  f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_pointer_hash__set( cause, this, dlfcn_dynamic_library_pointer_hash);
  f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_filename_hash__set(cause, this, dlfcn_dynamic_library_filename_hash);
}


f2ptr raw__dlfcn_dynamic_library_handler__dynamic_library(f2ptr cause, f2ptr this, f2ptr filename) {
  f2ptr dlfcn_dynamic_library_filename_hash = assert_value(f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_filename_hash(cause, this));
  f2ptr search_pathnames                    = assert_value(f2__dlfcn_dynamic_library_handler__search_pathnames(                   cause, this));
  f2ptr dynamic_library                     = nil;
  dynamic_library                           = assert_value(f2__ptypehash__lookup(cause, dlfcn_dynamic_library_filename_hash, filename));
  if (dynamic_library == nil) {
    dynamic_library                          = assert_value(f2__dlfcn_dynamic_library__new_open(cause, filename, nil, search_pathnames));
    f2ptr pointer                            = assert_value(f2__dlfcn_dynamic_library__pointer(cause, dynamic_library));
    f2ptr dlfcn_dynamic_library_pointer_hash = assert_value(f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_pointer_hash(cause, this));
    f2ptr already_loaded_dynamic_library     = assert_value(f2__ptypehash__lookup(cause, dlfcn_dynamic_library_pointer_hash, pointer));
    if (already_loaded_dynamic_library == nil) {
      f2__ptypehash__add(cause, dlfcn_dynamic_library_pointer_hash, pointer, dynamic_library);
    } else {
      dynamic_library = already_loaded_dynamic_library;
    }
    f2__ptypehash__add(cause, dlfcn_dynamic_library_filename_hash, filename, dynamic_library);
  }
  return dynamic_library;
}

f2ptr f2__dlfcn_dynamic_library_handler__dynamic_library(f2ptr cause, f2ptr this, f2ptr filename) {
  assert_argument_type(dlfcn_dynamic_library_handler, this);
  assert_argument_type(string,                        filename);
  return raw__dlfcn_dynamic_library_handler__dynamic_library(cause, this, filename);
}
def_pcfunk2(dlfcn_dynamic_library_handler__dynamic_library, this, filename,
	    "",
	    return f2__dlfcn_dynamic_library_handler__dynamic_library(this_cause, this, filename));

f2ptr raw__dlfcn_dynamic_library_handler__unload_dynamic_library(f2ptr cause, f2ptr this, f2ptr filename) {
  f2ptr dynamic_library = assert_value(raw__dlfcn_dynamic_library_handler__dynamic_library(cause, this, filename));
  assert_argument_type(dlfcn_dynamic_library, dynamic_library);
  assert_value(f2__dlfcn_dynamic_library__close(cause, dynamic_library));
  {
    f2ptr dlfcn_dynamic_library_filename_hash = assert_value(f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_filename_hash(cause, this));
    f2ptr keys_to_remove                      = nil;
    ptypehash__iteration(cause, dlfcn_dynamic_library_filename_hash, filename, dlfcn_dynamic_library,
			 assert_value(filename);
			 assert_value(dlfcn_dynamic_library);
			 if (raw__eq(cause, dynamic_library, dlfcn_dynamic_library)) {
			   keys_to_remove = raw__cons__new(cause, filename, keys_to_remove);
			 }
			 );
    {
      f2ptr key_iter = keys_to_remove;
      while (key_iter) {
	f2ptr key = f2cons__car(key_iter, cause);
	raw__ptypehash__remove(cause, dlfcn_dynamic_library_filename_hash, key);
	key_iter = f2cons__cdr(key_iter, cause);
      }
    }
  }
  {
    f2ptr dlfcn_dynamic_library_pointer_hash  = assert_value(f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_pointer_hash(cause, this));
    f2ptr keys_to_remove = nil;
    ptypehash__iteration(cause, dlfcn_dynamic_library_pointer_hash, pointer, dlfcn_dynamic_library,
			 assert_value(pointer);
			 assert_value(dlfcn_dynamic_library);
			 if (raw__eq(cause, dynamic_library, dlfcn_dynamic_library)) {
			   keys_to_remove = raw__cons__new(cause, pointer, keys_to_remove);
			 }
			 );
    {
      f2ptr key_iter = keys_to_remove;
      while (key_iter) {
	f2ptr key = f2cons__car(key_iter, cause);
	raw__ptypehash__remove(cause, dlfcn_dynamic_library_pointer_hash, key);
	key_iter = f2cons__cdr(key_iter, cause);
      }
    }
  }
  return nil;
}

f2ptr f2__dlfcn_dynamic_library_handler__unload_dynamic_library(f2ptr cause, f2ptr this, f2ptr filename) {
  assert_argument_type(dlfcn_dynamic_library_handler, this);
  assert_argument_type(string,                        filename);
  return raw__dlfcn_dynamic_library_handler__unload_dynamic_library(cause, this, filename);
}
def_pcfunk2(dlfcn_dynamic_library_handler__unload_dynamic_library, this, filename,
	    "",
	    return f2__dlfcn_dynamic_library_handler__unload_dynamic_library(this_cause, this, filename));


f2ptr raw__dlfcn_dynamic_library_handler__unload_changed(f2ptr cause, f2ptr this) {
  f2ptr search_pathnames  = f2__dlfcn_dynamic_library_handler__search_pathnames(cause, this);
  f2ptr changed_libraries = nil;
  {
    f2ptr dlfcn_dynamic_library_pointer_hash = assert_value(f2__dlfcn_dynamic_library_handler__dlfcn_dynamic_library_pointer_hash(cause, this));
    ptypehash__value__iteration(cause, dlfcn_dynamic_library_pointer_hash, dynamic_library,
				assert_argument_type(dlfcn_dynamic_library, dynamic_library);
				f2ptr changed_on_disk = assert_value(f2__dlfcn_dynamic_library__changed_on_disk(cause, dynamic_library, search_pathnames));
				if (changed_on_disk != nil) {
				  changed_libraries = raw__cons__new(cause, dynamic_library, changed_libraries);
				}
				);
  }
  {
    f2ptr iter = changed_libraries;
    while (iter) {
      f2ptr dynamic_library = f2cons__car(iter, cause);
      {
	f2ptr filename = assert_value(f2__dlfcn_dynamic_library__filename(cause, dynamic_library));
	assert_value(f2__dlfcn_dynamic_library_handler__unload_dynamic_library(cause, this, filename));
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return nil;
}

f2ptr f2__dlfcn_dynamic_library_handler__unload_changed(f2ptr cause, f2ptr this) {
  assert_argument_type(dlfcn_dynamic_library_handler, this);
  return raw__dlfcn_dynamic_library_handler__unload_changed(cause, this);
}
def_pcfunk1(dlfcn_dynamic_library_handler__unload_changed, this,
	    "",
	    return f2__dlfcn_dynamic_library_handler__unload_changed(this_cause, this));


f2ptr f2dlfcn_dynamic_library_handler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2dlfcn_dynamic_library_handler__primobject_type__new(cause);
  {char* slot_name = "dynamic_library";        f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.dynamic_library__funk);}
  {char* slot_name = "unload_dynamic_library"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_dynamic_library__funk);}
  {char* slot_name = "unload_changed";         f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_changed__funk);}
  return this;
}


// global_dlfcn_dynamic_library_handler

f2ptr f2__global_dlfcn_dynamic_library_handler(f2ptr cause) {
  return assert_value(environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "-dlfcn_dynamic_library_handler-")));
}


// global_dlfcn_dynamic_library

f2ptr f2__global_dlfcn_dynamic_library(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  f2ptr dlfcn_dynamic_library_handler = assert_value(f2__global_dlfcn_dynamic_library_handler(cause));
  assert_argument_type(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_handler);
  return f2__dlfcn_dynamic_library_handler__dynamic_library(cause, dlfcn_dynamic_library_handler, filename);
}
def_pcfunk1(global_dlfcn_dynamic_library, filename,
	    "",
	    return f2__global_dlfcn_dynamic_library(this_cause, filename));


f2ptr f2__global_dlfcn_dynamic_library__lookup_symbol(f2ptr cause, f2ptr filename, f2ptr symbol) {
  f2ptr dlfcn_dynamic_library = f2__global_dlfcn_dynamic_library(cause, filename);
  if (raw__larva__is_type(cause, dlfcn_dynamic_library)) {
    return dlfcn_dynamic_library;
  }
  return f2__dlfcn_dynamic_library__lookup_symbol(cause, dlfcn_dynamic_library, symbol);
}
def_pcfunk2(global_dlfcn_dynamic_library__lookup_symbol, filename, symbol,
	    "",
	    return f2__global_dlfcn_dynamic_library__lookup_symbol(this_cause, filename, symbol));


f2ptr f2__global_dlfcn_dynamic_library__unload_dynamic_library(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  f2ptr dlfcn_dynamic_library_handler = assert_value(f2__global_dlfcn_dynamic_library_handler(cause));
  if (raw__larva__is_type(cause, dlfcn_dynamic_library_handler)) {
    return dlfcn_dynamic_library_handler;
  }
  if (! raw__dlfcn_dynamic_library_handler__is_type(cause, dlfcn_dynamic_library_handler)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__dlfcn_dynamic_library_handler__unload_dynamic_library(cause, dlfcn_dynamic_library_handler, filename);
}
def_pcfunk1(global_dlfcn_dynamic_library__unload_dynamic_library, filename,
	    "",
	    return f2__global_dlfcn_dynamic_library__unload_dynamic_library(this_cause, filename));


f2ptr f2__global_dlfcn_dynamic_library__unload_changed(f2ptr cause) {
  f2ptr dlfcn_dynamic_library_handler = assert_value(f2__global_dlfcn_dynamic_library_handler(cause));
  assert_argument_type(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_handler);
  return f2__dlfcn_dynamic_library_handler__unload_changed(cause, dlfcn_dynamic_library_handler);
}
def_pcfunk0(global_dlfcn_dynamic_library__unload_changed,
	    "If a dynamic library has changed on disk, this function will cause it to be reloaded the next time it is used.",
	    return f2__global_dlfcn_dynamic_library__unload_changed(this_cause));



// **

void f2__dlfcn__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__supported);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__dlopen);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__dlerror);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__dlsym);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__dlclose);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__rtld_lazy);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__rtld_now);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__rtld_global);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__rtld_local);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__rtld_nodelete);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn__rtld_noload);
  
  
  // dlfcn_dynamic_library
  
  init_frame_object__4_slot__defragment__fix_pointers(dlfcn_dynamic_library, pointer, filename, stat, pointer_symbol_hash);
  
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library__new_open);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__symbol);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library__lookup_symbol);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__symbol);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library__close);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.changed_on_disk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library__changed_on_disk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.changed_on_disk__funk);
  
  
  // dlfcn_dynamic_library_handler
  
  init_frame_object__3_slot__defragment__fix_pointers(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_pointer_hash, dlfcn_dynamic_library_filename_hash, search_pathnames);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.dynamic_library__symbol);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library_handler__dynamic_library);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.dynamic_library__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_dynamic_library__symbol);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library_handler__unload_dynamic_library);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_dynamic_library__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_changed__symbol);
  f2__primcfunk__init__defragment__fix_pointers(dlfcn_dynamic_library_handler__unload_changed);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_changed__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(global_dlfcn_dynamic_library);
  f2__primcfunk__init__defragment__fix_pointers(global_dlfcn_dynamic_library__lookup_symbol);
  f2__primcfunk__init__defragment__fix_pointers(global_dlfcn_dynamic_library__unload_dynamic_library);
  f2__primcfunk__init__defragment__fix_pointers(global_dlfcn_dynamic_library__unload_changed);
  
}

void f2__dlfcn__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  f2ptr dynamic_library_handler = f2__global_dlfcn_dynamic_library_handler(cause);
  if ((dynamic_library_handler == nil) || raw__larva__is_type(cause, dynamic_library_handler)) {
    environment__add_var_value(cause, global_environment(), new__symbol(cause, "-dlfcn_dynamic_library_handler-"), f2__dlfcn_dynamic_library_handler__new(cause, nil));
  } else {
    raw__dlfcn_dynamic_library_handler__reinit(cause, dynamic_library_handler);
  }
  
  
  f2__primcfunk__init__0(dlfcn__supported);
  f2__primcfunk__init__2(dlfcn__dlopen, filename, flag);
  f2__primcfunk__init__0(dlfcn__dlerror);
  f2__primcfunk__init__2(dlfcn__dlsym, handle, symbol);
  f2__primcfunk__init__1(dlfcn__dlclose, handle);
  f2__primcfunk__init__0(dlfcn__rtld_lazy);
  f2__primcfunk__init__0(dlfcn__rtld_now);
  f2__primcfunk__init__0(dlfcn__rtld_global);
  f2__primcfunk__init__0(dlfcn__rtld_local);
  f2__primcfunk__init__0(dlfcn__rtld_nodelete);
  f2__primcfunk__init__0(dlfcn__rtld_noload);
  
  
  // dlfcn_dynamic_library
  
  init_frame_object__4_slot(dlfcn_dynamic_library, pointer, filename, stat, pointer_symbol_hash);
  
  f2__primcfunk__init__2(dlfcn_dynamic_library__new_open, filename, flag);
  
  {char* symbol_str = "lookup_symbol"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(dlfcn_dynamic_library__lookup_symbol, this, symbol, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.lookup_symbol__funk = never_gc(cfunk);}
  
  {char* symbol_str = "close"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(dlfcn_dynamic_library__close, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.close__funk = never_gc(cfunk);}
  
  {char* symbol_str = "changed_on_disk"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.changed_on_disk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(dlfcn_dynamic_library__changed_on_disk, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library.changed_on_disk__funk = never_gc(cfunk);}
  
  
  // dlfcn_dynamic_library_handler
  
  init_frame_object__3_slot(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_pointer_hash, dlfcn_dynamic_library_filename_hash, search_pathnames);
  
  {char* symbol_str = "dynamic_library"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.dynamic_library__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(dlfcn_dynamic_library_handler__dynamic_library, this, filename, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.dynamic_library__funk = never_gc(cfunk);}
  
  {char* symbol_str = "unload_dynamic_library"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_dynamic_library__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(dlfcn_dynamic_library_handler__unload_dynamic_library, this, filename, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_dynamic_library__funk = never_gc(cfunk);}
  
  {char* symbol_str = "unload_changed"; __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_changed__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(dlfcn_dynamic_library_handler__unload_changed, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_dlfcn_dynamic_library_handler.unload_changed__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(global_dlfcn_dynamic_library,                         filename);
  f2__primcfunk__init__2(global_dlfcn_dynamic_library__lookup_symbol,          filename, symbol);
  f2__primcfunk__init__1(global_dlfcn_dynamic_library__unload_dynamic_library, filename);
  f2__primcfunk__init__0(global_dlfcn_dynamic_library__unload_changed);
  
  
}

void f2__dlfcn__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "dlfcn", "", &f2__dlfcn__reinitialize_globalvars, &f2__dlfcn__defragment__fix_pointers);
  
  f2__dlfcn__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  environment__add_var_value(cause, global_environment(), new__symbol(cause, "-dlfcn_dynamic_library_handler-"), f2__dlfcn_dynamic_library_handler__new(cause, nil));
}


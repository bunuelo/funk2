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

#ifndef F2__DLFCN__TYPES__H
#define F2__DLFCN__TYPES__H

// dlfcn_dynamic_library

typedef struct funk2_object_type__dlfcn_dynamic_library__slot_s funk2_object_type__dlfcn_dynamic_library__slot_t;
struct funk2_object_type__dlfcn_dynamic_library__slot_s {
  f2ptr lookup_symbol__symbol;
  f2ptr lookup_symbol__funk;
  f2ptr close__symbol;
  f2ptr close__funk;
  f2ptr changed_on_disk__symbol;
  f2ptr changed_on_disk__funk;
};


// dlfcn_dynamic_library_handler

typedef struct funk2_object_type__dlfcn_dynamic_library_handler__slot_s funk2_object_type__dlfcn_dynamic_library_handler__slot_t;
struct funk2_object_type__dlfcn_dynamic_library_handler__slot_s {
  f2ptr dynamic_library__symbol;
  f2ptr dynamic_library__funk;
  f2ptr unload_dynamic_library__symbol;
  f2ptr unload_dynamic_library__funk;
  f2ptr unload_changed__symbol;
  f2ptr unload_changed__funk;
};


#endif // F2__DLFCN__TYPES__H

#ifndef F2__DLFCN__H
#define F2__DLFCN__H

boolean_t raw__dlfcn__supported();
f2ptr      f2__dlfcn__supported(f2ptr cause);
ptr       raw__dlfcn__dlopen_ex(u8* filename, int flag);
f2ptr     raw__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag);
f2ptr      f2__dlfcn__dlopen(f2ptr cause, f2ptr filename, f2ptr flag);
u8*       raw__dlfcn__dlerror();
f2ptr      f2__dlfcn__dlerror(f2ptr cause);
ptr       raw__dlfcn__dlsym(ptr handle, u8* symbol);
f2ptr      f2__dlfcn__dlsym(f2ptr cause, f2ptr handle, f2ptr symbol);
int       raw__dlfcn__dlclose(ptr handle);
f2ptr      f2__dlfcn__dlclose(f2ptr cause, f2ptr handle);
u64       raw__dlfcn__rtld_lazy();
f2ptr      f2__dlfcn__rtld_lazy(f2ptr cause);
u64       raw__dlfcn__rtld_now();
f2ptr      f2__dlfcn__rtld_now(f2ptr cause);
u64       raw__dlfcn__rtld_global();
f2ptr      f2__dlfcn__rtld_global(f2ptr cause);
u64       raw__dlfcn__rtld_local();
f2ptr      f2__dlfcn__rtld_local(f2ptr cause);
u64       raw__dlfcn__rtld_nodelete();
f2ptr      f2__dlfcn__rtld_nodelete(f2ptr cause);
u64       raw__dlfcn__rtld_noload();
f2ptr      f2__dlfcn__rtld_noload(f2ptr cause);


// dlfcn_dynamic_library

f2ptr  f2__dlfcn_dynamic_library__new(            f2ptr cause, f2ptr pointer, f2ptr filename, f2ptr stat);
f2ptr raw__dlfcn_dynamic_library__new_open(       f2ptr cause, f2ptr filename, f2ptr flag, f2ptr search_pathnames);
f2ptr  f2__dlfcn_dynamic_library__new_open(       f2ptr cause, f2ptr filename, f2ptr flag, f2ptr search_pathnames);
f2ptr raw__dlfcn_dynamic_library__lookup_symbol(  f2ptr cause, f2ptr this, f2ptr symbol);
f2ptr  f2__dlfcn_dynamic_library__lookup_symbol(  f2ptr cause, f2ptr this, f2ptr symbol);
f2ptr raw__dlfcn_dynamic_library__close(          f2ptr cause, f2ptr this);
f2ptr  f2__dlfcn_dynamic_library__close(          f2ptr cause, f2ptr this);
f2ptr raw__dlfcn_dynamic_library__changed_on_disk(f2ptr cause, f2ptr this, f2ptr search_pathnames);
f2ptr  f2__dlfcn_dynamic_library__changed_on_disk(f2ptr cause, f2ptr this, f2ptr search_pathnames);

f2ptr f2dlfcn_dynamic_library__primobject_type__new_aux(f2ptr cause);


// dlfcn_dynamic_library_handler

f2ptr  f2__dlfcn_dynamic_library_handler__new(                   f2ptr cause, f2ptr search_pathnames);
f2ptr raw__dlfcn_dynamic_library_handler__dynamic_library(       f2ptr cause, f2ptr this, f2ptr filename);
f2ptr  f2__dlfcn_dynamic_library_handler__dynamic_library(       f2ptr cause, f2ptr this, f2ptr filename);
f2ptr raw__dlfcn_dynamic_library_handler__unload_dynamic_library(f2ptr cause, f2ptr this, f2ptr filename);
f2ptr  f2__dlfcn_dynamic_library_handler__unload_dynamic_library(f2ptr cause, f2ptr this, f2ptr filename);

f2ptr f2dlfcn_dynamic_library_handler__primobject_type__new_aux(f2ptr cause);


// global_dlfcn_dynamic_library_handler

//  init_frame_object__3_slot(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_pointer_hash, dlfcn_dynamic_library_filename_hash, search_pathnames);

declare_primobject_3_slot(dlfcn_dynamic_library_handler, dlfcn_dynamic_library_pointer_hash, dlfcn_dynamic_library_filename_hash, search_pathnames);


f2ptr f2__global_dlfcn_dynamic_library_handler(f2ptr cause);


// global_dlfcn_dynamic_library

//  init_frame_object__4_slot(dlfcn_dynamic_library, pointer, filename, stat, pointer_symbol_hash);

declare_primobject_4_slot(dlfcn_dynamic_library, pointer, filename, stat, pointer_symbol_hash);


f2ptr f2__global_dlfcn_dynamic_library(                        f2ptr cause, f2ptr filename);
f2ptr f2__global_dlfcn_dynamic_library__lookup_symbol(         f2ptr cause, f2ptr filename, f2ptr symbol);
f2ptr f2__global_dlfcn_dynamic_library__unload_dynamic_library(f2ptr cause, f2ptr filename);


// **

void f2__dlfcn__reinitialize_globalvars();
void f2__dlfcn__initialize();

#endif // F2__DLFCN__H



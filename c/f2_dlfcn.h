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

#ifndef F2__DLFCN__H
#define F2__DLFCN__H

boolean_t raw__dlfcn__supported();
f2ptr      f2__dlfcn__supported(f2ptr cause);
ptr       raw__dlfcn__dlopen(u8* filename, int flag);
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

// **

void f2__dlfcn__reinitialize_globalvars();
void f2__dlfcn__initialize();

#endif // F2__DLFCN__H



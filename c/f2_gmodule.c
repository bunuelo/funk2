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

//gboolean g_module_supported();
boolean_t raw__gmodule__supported() {
#ifdef F2__GMODULE__SUPPORTED
  return (g_module_supported() ? boolean__true : boolean__false);
#else
  return boolean__false;
#endif
}

f2ptr f2__gmodule__supported(f2ptr cause) {
  return f2bool__new(raw__gmodule__supported());
}
def_pcfunk0(gmodule__supported,
	    "",
	    return f2__gmodule__supported(this_cause));

//gchar* g_module_build_path(const gchar *directory, const gchar *module_name);
u8* raw__gmodule__build_path(u8* directory, u8* module_name) {
#ifdef F2__GMODULE__SUPPORTED
  return g_module_build_path(directory__str, module_name__str);
#else
  return NULL;
#endif
}

f2ptr f2__gmodule__build_path(f2ptr cause, f2ptr directory, f2ptr module_name) {
  assert_argument_type(string, directory);
  assert_argument_type(string, module_name);
  int directory__utf8_length = raw__string__utf8_length(cause, directory);
  u8* directory__utf8_str    = alloca(directory__utf8_length + 1);
  raw__string__utf8_str_copy(cause, directory, directory__utf8_str);
  directory__utf8_str[directory__utf8_length] = 0;
  int module_name__utf8_length = raw__string__utf8_length(cause, module_name);
  u8* module_name__utf8_str    = alloca(module_name__utf8_length + 1);
  raw__string__utf8_str_copy(cause, module_name, module_name__utf8_str);
  module_name__utf8_str[module_name__utf8_length] = 0;
  u8* new_path_utf8_str = raw__gmodule__build_path(directory__utf8_str, module_name__utf8_str);
  if (new_path_utf8_str == NULL) {
    return nil;
  }
  f2ptr new_path = new__string(cause, (char*)new_path_utf8_str);
  f2__free(to_ptr(new_path_utf8_str));
  return new_path;
}
def_pcfunk2(gmodule__build_path, directory, module_name,
	    "",
	    return f2__gmodule__build_path(this_cause, directory, module_name));

//GModule* g_module_open(const gchar *file_name, GModuleFlags flags);
ptr raw__gmodule__open(u8* filename, u64 flags) {
#ifdef F2__GMODULE__SUPPORTED
  return to_ptr(g_module_open((char*)filename, flags));
#else
  return to_ptr(NULL);
#endif
}

f2ptr f2__gmodule__open(f2ptr cause, f2ptr filename, f2ptr flags) {
  assert_argument_type(       string,  filename);
  assert_argument_type_or_nil(integer, flags);
  int filename__utf8_length = raw__string__utf8_length(cause, filename);
  u8* filename__utf8_str    = (u8*)alloca(filename__utf8_length + 1);
  raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
  u64 raw_flags = flags ? f2integer__i(flags, cause) : 0;
  ptr module_ptr = raw__gmodule__open(filename__utf8_str, raw_flags);
  if (module_ptr == to_ptr(NULL)) {
    return nil;
  }
  return f2pointer__new(cause, module_ptr);
}
def_pcfunk2(gmodule__open, filename, flags,
	    "",
	    return f2__gmodule__open(this_cause, filename, flags));

//gboolean g_module_symbol(GModule *module, const gchar *symbol_name, gpointer *symbol);
ptr raw__gmodule__symbol(ptr module, u8* symbol_name) {
#ifdef F2__GMODULE__SUPPORTED
  gpointer symbol_pointer = NULL;
  boolean_t result = g_module_symbol(from_ptr(module), (char*)symbol_name, &symbol_pointer);
  if (! result) {
    return to_ptr(NULL);
  }
  return to_ptr(symbol_pointer);
#else
  return to_ptr(NULL);
#endif
}

f2ptr f2__gmodule__symbol(f2ptr cause, f2ptr module, f2ptr symbol_name) {
  assert_argument_type(pointer, module);
  assert_argument_type(string,  symbol_name);
  ptr raw_module = f2pointer__p(module, cause);
  int symbol_name__utf8_length = raw__string__utf8_length(cause, symbol_name);
  u8* symbol_name__utf8_str    = (u8*)alloca(symbol_name__utf8_length + 1);
  raw__string__utf8_str_copy(cause, symbol_name, symbol_name__utf8_str);
  symbol_name__utf8_str[symbol_name__utf8_length] = 0;
  ptr symbol_pointer = raw__gmodule__symbol(raw_module, symbol_name__utf8_str);
  if (symbol_pointer == to_ptr(NULL)) {
    return nil;
  }
  return f2pointer__new(cause, symbol_pointer);
}
def_pcfunk2(gmodule__symbol, module, symbol_name,
	    "",
	    return f2__gmodule__symbol(this_cause, module, symbol_name));

//const gchar* g_module_name(GModule *module);
u8* raw__gmodule__name(ptr module) {
#ifdef F2__GMODULE__SUPPORTED
  return g_module_name(from_ptr(module));
#else
  return (u8*)NULL;
#endif  
}

f2ptr f2__gmodule__name(f2ptr cause, f2ptr module) {
  assert_argument_type(pointer, module);
  ptr raw_module = f2pointer__p(module, cause);
  u8* module_name_utf8_str = raw__gmodule__name(raw_module);
  if (module_name_utf8_str == NULL) {
    return nil;
  }
  return new__string(cause, (char*)module_name_utf8_str);
}
def_pcfunk1(gmodule__name, module,
	    "",
	    return f2__gmodule__name(this_cause, module));

//void g_module_make_resident(GModule *module);
void raw__gmodule__make_resident(ptr module) {
#ifdef F2__GMODULE__SUPPORTED
  g_module_make_resident(from_ptr(module));
#else
#endif
}

f2ptr f2__gmodule__make_resident(f2ptr cause, f2ptr module) {
  assert_argument_type(pointer, module);
  ptr raw_module = f2pointer__p(module, cause);
  raw__gmodule__make_resident(raw_module);
  return nil;
}
def_pcfunk1(gmodule__make_resident, module,
	    "",
	    return f2__gmodule__make_resident(this_cause, module));

//gboolean g_module_close(GModule *module);
boolean_t raw__gmodule__close(ptr module) {
#ifdef F2__GMODULE__SUPPORTED
  return (boolean_t)g_module_close(from_ptr(module));
#else
  return boolean__false;
#endif  
}

f2ptr f2__gmodule__close(f2ptr cause, f2ptr module) {
  assert_argument_type(pointer, module);
  ptr raw_module = f2pointer__p(module, cause);
  return f2bool__new(raw__gmodule__close(raw_module));
}
def_pcfunk1(gmodule__close, module,
	    "",
	    return f2__gmodule__close(this_cause, module));

//const gchar* g_module_error();
u8* raw__gmodule__error() {
#ifdef F2__GMODULE__SUPPORTED
  return (u8*)g_module_error();
#else
  return (u8*)NULL;
#endif  
}

f2ptr f2__gmodule__error(f2ptr cause) {
  u8* error_utf8_str = raw__gmodule__error();
  if (error_utf8_str == NULL) {
    return nil;
  }
  return new__string(cause, (char*)error_utf8_str);
}
def_pcfunk0(gmodule__error,
	    "",
	    return f2__gmodule__error(this_cause));


// **

void f2__gmodule__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(gmodule__supported);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__build_path);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__open);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__symbol);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__name);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__make_resident);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__close);
  f2__primcfunk__init__defragment__fix_pointers(gmodule__error);
  
}

void f2__gmodule__reinitialize_globalvars() {
  f2__primcfunk__init__0(gmodule__supported);
  f2__primcfunk__init__2(gmodule__build_path, directory, module_name);
  f2__primcfunk__init__2(gmodule__open, filename, flags);
  f2__primcfunk__init__2(gmodule__symbol, module, symbol_name);
  f2__primcfunk__init__1(gmodule__name, module);
  f2__primcfunk__init__1(gmodule__make_resident, module);
  f2__primcfunk__init__1(gmodule__close, module);
  f2__primcfunk__init__0(gmodule__error);
}

void f2__gmodule__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "gmodule", "", &f2__gmodule__reinitialize_globalvars, &f2__gmodule__defragment__fix_pointers);
  
  f2__gmodule__reinitialize_globalvars();
}


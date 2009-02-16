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

//gboolean g_module_supported();
f2ptr f2__g_module_supported() {
  return f2bool__new(g_module_supported());
}

//gchar* g_module_build_path(const gchar *directory, const gchar *module_name);
f2ptr f2__g_module_build_path(f2ptr cause, f2ptr directory, f2ptr module_name) {
  char* directory__str   = (directory ? (char*)from_ptr(f2__malloc(f2string__length(directory, cause))) : NULL); if (directory__str) {f2string__str_copy(directory, cause, (u8*)directory__str);}
  char* module_name__str = (char*)from_ptr(f2__malloc(f2string__length(module_name, cause))); f2string__str_copy(module_name, cause, (u8*)module_name__str);
  char* new_path_str     = g_module_build_path(directory__str, module_name__str);
  f2ptr new_path = f2string__new(cause, strlen(new_path_str), (u8*)new_path_str);
  f2__free(to_ptr(directory__str));
  f2__free(to_ptr(module_name__str));
  free(new_path_str);
  return new_path;
}

//GModule* g_module_open(const gchar *file_name, GModuleFlags flags);
f2ptr f2__g_module_open(f2ptr cause, f2ptr file_name, f2ptr flags) {
  char* file_name__str = (char*)from_ptr(f2__malloc(f2string__length(file_name, cause))); f2string__str_copy(file_name, cause, (u8*)file_name__str);
  ptr module_ptr = to_ptr(g_module_open(file_name__str, f2integer__i(flags, cause)));
  f2ptr module = (module_ptr ? f2pointer__new(cause, module_ptr) : nil);
  f2__free(to_ptr(file_name__str));
  if (! module) {
    printf("\nf2__g_module_open error: g_module_error() = '%s'", g_module_error()); fflush(stdout);
  }
  return module;
}

//gboolean g_module_symbol(GModule *module, const gchar *symbol_name, gpointer *symbol);
f2ptr f2__g_module_symbol(f2ptr cause, f2ptr module, f2ptr symbol_name) {
  char* symbol_name__str = (char*)from_ptr(f2__malloc(f2string__length(symbol_name, cause))); f2string__str_copy(symbol_name, cause, (u8*)symbol_name__str);
  void* os_symbol_ptr; f2ptr result = nil; if (g_module_symbol(from_ptr(f2pointer__p(module, cause)), symbol_name__str, &os_symbol_ptr)) {result = f2pointer__new(cause, to_ptr(os_symbol_ptr));}
  f2__free(to_ptr(symbol_name__str));
  return result;
}

//const gchar* g_module_name(GModule *module);
f2ptr f2__g_module_name(f2ptr cause, f2ptr module) {
  char* module_name_str = (char*)g_module_name(from_ptr(f2pointer__p(module, cause)));
  return f2string__new(cause, strlen(module_name_str), (u8*)module_name_str);
}

//void g_module_make_resident(GModule *module);
void f2__g_module_make_resident(f2ptr cause, f2ptr module) {
  g_module_make_resident(from_ptr(f2pointer__p(module, cause)));
}

//gboolean g_module_close(GModule *module);
f2ptr f2__g_module_close(f2ptr cause, f2ptr module) {
  return f2bool__new(g_module_close(from_ptr(f2pointer__p(module, cause))));
}

//const gchar* g_module_error();
f2ptr f2__g_module_error(f2ptr cause) {
  char* error_str = (char*)g_module_error();
  return error_str ? f2string__new(cause, strlen(error_str), (u8*)error_str) : nil;
}



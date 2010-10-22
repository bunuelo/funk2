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


// core_extension

def_frame_object__global__3_slot(core_extension, name, filename, initialized);

f2ptr raw__core_extension__new(f2ptr cause, f2ptr name, f2ptr filename) {
  f2ptr initialized = nil;
  return f2core_extension__new(cause, name, filename, initialized);
}

f2ptr f2__core_extension__new(f2ptr cause, f2ptr name, f2ptr filename) {
  if (! raw__string__is_type(cause, filename)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension__new(cause, name, filename);
}
def_pcfunk2(core_extension__new, name, filename, return f2__core_extension__new(this_cause, name, filename));


f2ptr raw__core_extension__initialize(f2ptr cause, f2ptr this) {
  if (f2__core_extension__initialized(cause, this) != nil) {
    return f2larva__new(cause, 124352, nil);
  }
  f2ptr name                 = f2__core_extension__name(    cause, this);
  f2ptr initialize_funk_name = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, name), new__string(cause, "__core_extension_initialize"))));
  f2ptr initialize_funk      = f2__core_extension_funk__new(cause, name, initialize_funk_name);
  f2ptr result = f2__core_extension_funk__apply_without_initializing(cause, initialize_funk, nil);
  if (raw__larva__is_type(cause, result)) {
    return f2larva__new(cause, 3435, f2__bug__new(cause, f2integer__new(cause, 3435), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_initialize_core_extension"),
															 new__symbol(cause, "funkname"), new__symbol(cause, "core_extension-initialize"),
															 new__symbol(cause, "this"),     this,
															 new__symbol(cause, "result"),   result))));
  }
  f2__core_extension__initialized__set(cause, this, f2bool__new(boolean__true));
  return nil;
}

f2ptr f2__core_extension__initialize(f2ptr cause, f2ptr this) {
  if (! raw__core_extension__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension__initialize(cause, this);
}
def_pcfunk1(core_extension__initialize, this, return f2__core_extension__initialize(this_cause, this));


f2ptr raw__core_extension__destroy(f2ptr cause, f2ptr this) {
  if (f2__core_extension__initialized(cause, this) == nil) {
    return f2larva__new(cause, 124351, nil);
  }
  f2ptr name              = f2__core_extension__name(    cause, this);
  f2ptr destroy_funk_name = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, name), new__string(cause, "__core_extension_destroy"))));
  f2ptr destroy_funk      = f2__core_extension_funk__new(cause, name, destroy_funk_name);
  f2ptr result = f2__core_extension_funk__apply(cause, destroy_funk, nil);
  if (raw__larva__is_type(cause, result)) {
    return f2larva__new(cause, 3435, f2__bug__new(cause, f2integer__new(cause, 3435), f2__frame__new(cause, f2list8__new(cause,
															 new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_destroy_core_extension"),
															 new__symbol(cause, "funkname"), new__symbol(cause, "core_extension-destroy"),
															 new__symbol(cause, "this"),     this,
															 new__symbol(cause, "result"),   result))));
  }
  f2__core_extension__initialized__set(cause, this, f2bool__new(boolean__false));
  return nil;
}

f2ptr f2__core_extension__destroy(f2ptr cause, f2ptr this) {
  if (! raw__core_extension__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension__destroy(cause, this);
}
def_pcfunk1(core_extension__destroy, this, return f2__core_extension__destroy(this_cause, this));


f2ptr raw__core_extension__assure_initialized(f2ptr cause, f2ptr this) {
  if (f2__core_extension__initialized(cause, this) != nil) {
    return nil;
  }
  f2ptr result = f2__core_extension__initialize(cause, this);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  return nil;
}

f2ptr f2__core_extension__assure_initialized(f2ptr cause, f2ptr this) {
  if (! raw__core_extension__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension__assure_initialized(cause, this);
}
def_pcfunk1(core_extension__assure_initialized, this, return f2__core_extension__assure_initialized(this_cause, this));


f2ptr f2core_extension__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension__primobject_type__new(cause);
  {char* slot_name = "initialize";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__funk);}
  {char* slot_name = "destroy";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__funk);}
  {char* slot_name = "assure_initialized"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__funk);}
  return this;
}


// core_extension_handler

def_frame_object__global__1_slot(core_extension_handler, core_extension_name_hash);

f2ptr raw__core_extension_handler__new(f2ptr cause) {
  f2ptr core_extension_name_hash = f2__ptypehash__new(cause);
  return f2core_extension_handler__new(cause, core_extension_name_hash);
}

f2ptr f2__core_extension_handler__new(f2ptr cause) {
  return raw__core_extension_handler__new(cause);
}
def_pcfunk0(core_extension_handler__new, return f2__core_extension_handler__new(this_cause));


f2ptr raw__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename) {
  f2ptr core_extension_name_hash = f2__core_extension_handler__core_extension_name_hash(cause, this);
  f2ptr core_extension = f2__core_extension__new(cause, name, filename);
  f2__ptypehash__add(cause, core_extension_name_hash, name, core_extension);
  return nil;
}

f2ptr f2__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename) {
  if (! raw__core_extension_handler__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_handler__add_new_core_extension(cause, this, name, filename);
}
def_pcfunk3(core_extension_handler__add_new_core_extension, this, name, filename, return f2__core_extension_handler__add_new_core_extension(this_cause, this, name, filename));


f2ptr raw__core_extension_handler__lookup_core_extension(f2ptr cause, f2ptr this, f2ptr name) {
  f2ptr core_extension_name_hash = f2__core_extension_handler__core_extension_name_hash(cause, this);
  return f2__ptypehash__lookup(cause, core_extension_name_hash, name);
}

f2ptr f2__core_extension_handler__lookup_core_extension(f2ptr cause, f2ptr this, f2ptr name) {
  if (! raw__core_extension_handler__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_handler__lookup_core_extension(cause, this, name);
}
def_pcfunk2(core_extension_handler__lookup_core_extension, this, name, return f2__core_extension_handler__lookup_core_extension(this_cause, this, name));


f2ptr f2core_extension_handler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension_handler__primobject_type__new(cause);
  {char* slot_name = "add_new_core_extension"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__funk);}
  {char* slot_name = "lookup_core_extension";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__funk);}
  return this;
}


f2ptr f2__global_core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr name, f2ptr filename) {
  f2ptr core_extension_handler = environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"));
  if (raw__larva__is_type(cause, core_extension_handler)) {
    return core_extension_handler;
  }
  if (! raw__core_extension_handler__is_type(cause, core_extension_handler)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__core_extension_handler__add_new_core_extension(cause, core_extension_handler, name, filename);
}
def_pcfunk2(global_core_extension_handler__add_new_core_extension, name, filename, return f2__global_core_extension_handler__add_new_core_extension(this_cause, name, filename));


f2ptr f2__global_core_extension_handler__lookup_core_extension(f2ptr cause, f2ptr name) {
  f2ptr core_extension_handler = environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"));
  if (raw__larva__is_type(cause, core_extension_handler)) {
    return core_extension_handler;
  }
  if (! raw__core_extension_handler__is_type(cause, core_extension_handler)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__core_extension_handler__lookup_core_extension(cause, core_extension_handler, name);
}
def_pcfunk1(global_core_extension_handler__lookup_core_extension, name, return f2__global_core_extension_handler__lookup_core_extension(this_cause, name));


// **

void f2__core_extension__reinitialize_globalvars() {
  //f2ptr cause = initial_cause();
  
  //environment__add_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"), f2__core_extension_handler__new(cause));
}

void f2__core_extension__initialize_module() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "core_extension", "", &f2__core_extension__reinitialize_globalvars);
  
  f2__core_extension__reinitialize_globalvars();
  
  
  // core_extension
  
  init_frame_object__3_slot(core_extension, name, filename, initialized);
  
  f2__primcfunk__init__2(core_extension__new, name, filename, "");
  
  {char* symbol_str = "initialize"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__initialize, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__funk = never_gc(cfunk);}
  
  {char* symbol_str = "destroy"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__destroy, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__funk = never_gc(cfunk);}
  
  {char* symbol_str = "assure_initialized"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__assure_initialized, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__funk = never_gc(cfunk);}
  
  
  // core_extension_handler
  
  init_frame_object__1_slot(core_extension_handler, core_extension_name_hash);
  
  f2__primcfunk__init__0(core_extension_handler__new, "");
  
  {char* symbol_str = "add_new_core_extension"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_handler__add_new_core_extension, name, filename, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__funk = never_gc(cfunk);}
  
  {char* symbol_str = "lookup_core_extension"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_handler__lookup_core_extension, name, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__funk = never_gc(cfunk);}
  
  
  // global_core_extension_handler
  
  f2__primcfunk__init__2(global_core_extension_handler__add_new_core_extension, name, filename, "");
  f2__primcfunk__init__1(global_core_extension_handler__lookup_core_extension,  name,           "");
  
  
  environment__add_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"), f2__core_extension_handler__new(cause));
  
}





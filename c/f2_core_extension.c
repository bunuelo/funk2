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

// core_extension_funk

def_frame_object__global__6_slot(core_extension_funk, filename, name, cname, args_cname, is_funktional_cname, documentation_cname);

f2ptr raw__core_extension_funk__new(f2ptr cause, f2ptr filename, f2ptr name) {
  f2ptr cname               = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list2__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name))));
  f2ptr args_cname          = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name), new__string(cause, "__args"))));
  f2ptr is_funktional_cname = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name), new__string(cause, "__is_funktional"))));
  f2ptr documentation_cname = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name), new__string(cause, "__documentation"))));
  return f2core_extension_funk__new(cause, filename, name, cname, args_cname, is_funktional_cname, documentation_cname);
}

f2ptr f2__core_extension_funk__new(f2ptr cause, f2ptr filename, f2ptr name) {
  if ((! raw__string__is_type(cause, filename)) ||
      (! raw__symbol__is_type(cause, name))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__new(cause, filename, name);
}
def_pcfunk2(core_extension_funk__new, filename, name, return f2__core_extension_funk__new(this_cause, filename, name));




f2ptr raw__core_extension_funk__pointer(f2ptr cause, f2ptr this) {
  f2ptr filename = f2__core_extension_funk__filename(cause, this);
  f2ptr cname    = f2__core_extension_funk__cname(   cause, this);
  return f2__global_dlfcn_dynamic_library__lookup_symbol(cause, filename, cname);
}

f2ptr f2__core_extension_funk__pointer(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__pointer(cause, this);
}
def_pcfunk1(core_extension_funk__pointer, this, return f2__core_extension_funk__pointer(this_cause, this));


f2ptr raw__core_extension_funk__cfunk(f2ptr cause, f2ptr this) {
  f2ptr pointer = f2__core_extension_funk__pointer(cause, this);
  if (raw__larva__is_type(cause, pointer)) {
    return pointer;
  }
  if (! raw__pointer__is_type(cause, pointer)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr name          = f2__core_extension_funk__name(cause, this);
  f2ptr args          = f2__core_extension_funk__args(cause, this);
  f2ptr cfunkptr      = f2pointer__new(cause, raw_executable__to__relative_ptr(f2pointer__p(pointer, cause)));
  f2ptr env           = global_environment();
  f2ptr is_funktional = f2__core_extension_funk__is_funktional(cause, this);
  f2ptr documentation = f2__core_extension_funk__documentation(cause, this);
  return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);
}

f2ptr f2__core_extension_funk__cfunk(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__cfunk(cause, this);
}
def_pcfunk1(core_extension_funk__cfunk, this, return f2__core_extension_funk__cfunk(this_cause, this));


f2ptr raw__core_extension_funk__apply(f2ptr cause, f2ptr this, f2ptr args) {
  f2ptr cfunk = raw__core_extension_funk__cfunk(cause, this);
  if (raw__larva__is_type(cause, cfunk)) {
    return cfunk;
  }
  if (! raw__cfunk__is_type(cause, cfunk)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__cfunk__apply(cause, cfunk, f2__this__fiber(cause), args);
}

f2ptr f2__core_extension_funk__apply(f2ptr cause, f2ptr this, f2ptr args) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__apply(cause, this, args);
}
def_pcfunk2(core_extension_funk__apply, this, args, return f2__core_extension_funk__apply(this_cause, this, args));















f2ptr raw__core_extension_funk__args_pointer(f2ptr cause, f2ptr this) {
  f2ptr filename   = f2__core_extension_funk__filename(cause, this);
  f2ptr args_cname = f2__core_extension_funk__args_cname(   cause, this);
  return f2__global_dlfcn_dynamic_library__lookup_symbol(cause, filename, args_cname);
}

f2ptr f2__core_extension_funk__args_pointer(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__args_pointer(cause, this);
}
def_pcfunk1(core_extension_funk__args_pointer, this, return f2__core_extension_funk__args_pointer(this_cause, this));


f2ptr raw__core_extension_funk__args_cfunk(f2ptr cause, f2ptr this) {
  f2ptr args_pointer = f2__core_extension_funk__args_pointer(cause, this);
  if (raw__larva__is_type(cause, args_pointer)) {
    return args_pointer;
  }
  if (! raw__pointer__is_type(cause, args_pointer)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr name          = f2__core_extension_funk__args_cname(cause, this);
  f2ptr args          = nil;
  f2ptr cfunkptr      = f2pointer__new(cause, raw_executable__to__relative_ptr(f2pointer__p(args_pointer, cause)));
  f2ptr env           = global_environment();
  f2ptr is_funktional = f2bool__new(boolean__true);
  f2ptr documentation = new__string(cause, "This cfunk returns the arguments for its core_extension_funk.");
  return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);
}

f2ptr f2__core_extension_funk__args_cfunk(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__args_cfunk(cause, this);
}
def_pcfunk1(core_extension_funk__args_cfunk, this, return f2__core_extension_funk__args_cfunk(this_cause, this));


f2ptr raw__core_extension_funk__args(f2ptr cause, f2ptr this) {
  f2ptr args_cfunk = raw__core_extension_funk__args_cfunk(cause, this);
  if (raw__larva__is_type(cause, args_cfunk)) {
    return args_cfunk;
  }
  if (! raw__cfunk__is_type(cause, args_cfunk)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__cfunk__apply(cause, args_cfunk, f2__this__fiber(cause), nil);
}

f2ptr f2__core_extension_funk__args(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__args(cause, this);
}
def_pcfunk1(core_extension_funk__args, this, return f2__core_extension_funk__args(this_cause, this));


f2ptr raw__core_extension_funk__is_funktional(f2ptr cause, f2ptr this) {
  return nil;
}

f2ptr f2__core_extension_funk__is_funktional(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__is_funktional(cause, this);
}
def_pcfunk1(core_extension_funk__is_funktional, this, return f2__core_extension_funk__is_funktional(this_cause, this));


f2ptr raw__core_extension_funk__documentation(f2ptr cause, f2ptr this) {
  return new__string(cause, "This core_extension_funk was not documented by its developers.");
}

f2ptr f2__core_extension_funk__documentation(f2ptr cause, f2ptr this) {
  if (! raw__core_extension_funk__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__documentation(cause, this);
}
def_pcfunk1(core_extension_funk__documentation, this, return f2__core_extension_funk__documentation(this_cause, this));



f2ptr raw__core_extension_funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "core_extension_funk"),
						new__symbol(cause, "filename"),          f2__core_extension_funk__filename(     cause, this),
						new__symbol(cause, "name"),              f2__core_extension_funk__name(         cause, this),
						new__symbol(cause, "args"),              f2__core_extension_funk__args(         cause, this),
						new__symbol(cause, "is_funktional"),     f2__core_extension_funk__is_funktional(cause, this),
						new__symbol(cause, "documentation"),     f2__core_extension_funk__documentation(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__core_extension_funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__core_extension_funk__is_type(cause, this)) ||
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__core_extension_funk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(core_extension_funk__terminal_print_with_frame, this, terminal_print_frame, return f2__core_extension_funk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2core_extension_funk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension_funk__primobject_type__new(cause);
  {char* slot_name = "pointer";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__funk);}
  {char* slot_name = "cfunk";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__funk);}
  {char* slot_name = "apply";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__funk);}
  {char* slot_name = "args_pointer";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__funk);}
  {char* slot_name = "args_cfunk";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__funk);}
  {char* slot_name = "args";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__funk);}
  {char* slot_name = "is_funktional";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__funk);}
  {char* slot_name = "documentation";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__funk);}
  return this;
}





// **

void f2__core_extension__reinitialize_globalvars() {
}

void f2__core_extension__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "core_extension", "", &f2__core_extension__reinitialize_globalvars);
  
  f2__core_extension__reinitialize_globalvars();
  
  
  // core_extension_funk
  
  init_frame_object__6_slot(core_extension_funk, filename, name, cname, args_cname, is_funktional_cname, documentation_cname);
  
  f2__primcfunk__init__2(core_extension_funk__new, filename, name, "");
  
  {char* symbol_str = "pointer"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__pointer, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__funk = never_gc(cfunk);}
  
  {char* symbol_str = "cfunk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__cfunk, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__funk = never_gc(cfunk);}
  
  {char* symbol_str = "apply"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_funk__apply, this, args, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_funk__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  {char* symbol_str = "args_pointer"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__args_pointer, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__funk = never_gc(cfunk);}
  
  {char* symbol_str = "args_cfunk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__args_cfunk, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__funk = never_gc(cfunk);}
  
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__args, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_funktional"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__is_funktional, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__funk = never_gc(cfunk);}
  
  {char* symbol_str = "documentation"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__documentation, this, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__funk = never_gc(cfunk);}
  
}


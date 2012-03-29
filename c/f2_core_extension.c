// 
// Copyright (c) 2007-2012 Bo Morgan.
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

def_frame_object__global__4_slot(core_extension, name, filename, initialized_time_stamp_cmutex, initialized_time_stamp);

f2ptr raw__core_extension__new(f2ptr cause, f2ptr name, f2ptr filename) {
  f2ptr initialized_time_stamp_cmutex = f2__cmutex__new(cause);
  f2ptr initialized_time_stamp        = nil;
  return f2core_extension__new(cause, name, filename, initialized_time_stamp_cmutex, initialized_time_stamp);
}

f2ptr f2__core_extension__new(f2ptr cause, f2ptr name, f2ptr filename) {
  assert_argument_type(string, filename);
  return raw__core_extension__new(cause, name, filename);
}
def_pcfunk2(core_extension__new, name, filename,
	    "",
	    return f2__core_extension__new(this_cause, name, filename));


f2ptr raw__core_extension__initialize(f2ptr cause, f2ptr this) {
  f2ptr initialized_time_stamp_cmutex = f2__core_extension__initialized_time_stamp_cmutex(cause, this);
  raw__cmutex__lock(cause, initialized_time_stamp_cmutex);
  if (f2__core_extension__initialized_time_stamp(cause, this) != nil) {
    raw__cmutex__unlock(cause, initialized_time_stamp_cmutex);
    return nil;
  }
  f2ptr name                 = f2__core_extension__name(    cause, this);
  f2ptr initialize_funk_name = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, name), new__string(cause, "__core_extension__initialize"))));
  f2ptr initialize_funk      = f2__core_extension_funk__new(cause, name, initialize_funk_name);
  f2ptr result               = f2__core_extension_funk__apply_without_initializing(cause, initialize_funk, nil);
  if (raw__larva__is_type(cause, result)) {
    raw__cmutex__unlock(cause, initialized_time_stamp_cmutex);
    catch_value(result,
		f2list8__new(cause,
			     new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_initialize_core_extension"),
			     new__symbol(cause, "funkname"), new__symbol(cause, "core_extension-initialize"),
			     new__symbol(cause, "this"),     this,
			     new__symbol(cause, "result"),   result));
    return result;
  }
  f2__core_extension__initialized_time_stamp__set(cause, this, f2__time(cause));
  raw__cmutex__unlock(cause, initialized_time_stamp_cmutex);
  return nil;
}

f2ptr f2__core_extension__initialize(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension, this);
  return raw__core_extension__initialize(cause, this);
}
def_pcfunk1(core_extension__initialize, this,
	    "",
	    return f2__core_extension__initialize(this_cause, this));


f2ptr raw__core_extension__destroy(f2ptr cause, f2ptr this) {
  f2ptr initialized_time_stamp_cmutex = f2__core_extension__initialized_time_stamp_cmutex(cause, this);
  raw__cmutex__lock(cause, initialized_time_stamp_cmutex);
  if (f2__core_extension__initialized_time_stamp(cause, this) == nil) {
    raw__cmutex__unlock(cause, initialized_time_stamp_cmutex);
    return nil;
  }
  f2ptr name              = f2__core_extension__name(    cause, this);
  f2ptr destroy_funk_name = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, name), new__string(cause, "__core_extension__destroy"))));
  f2ptr destroy_funk      = f2__core_extension_funk__new(cause, name, destroy_funk_name);
  f2ptr result            = f2__core_extension_funk__apply(cause, destroy_funk, nil);
  if (raw__larva__is_type(cause, result)) {
    raw__cmutex__unlock(cause, initialized_time_stamp_cmutex);
    catch_value(result,
		f2list8__new(cause,
			     new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_destroy_core_extension"),
			     new__symbol(cause, "funkname"), new__symbol(cause, "core_extension-destroy"),
			     new__symbol(cause, "this"),     this,
			     new__symbol(cause, "result"),   result));
    return result;
  }
  f2__core_extension__initialized_time_stamp__set(cause, this, nil);
  raw__cmutex__unlock(cause, initialized_time_stamp_cmutex);
  return nil;
}

f2ptr f2__core_extension__destroy(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension, this);
  return raw__core_extension__destroy(cause, this);
}
def_pcfunk1(core_extension__destroy, this,
	    "",
	    return f2__core_extension__destroy(this_cause, this));


f2ptr raw__core_extension__assure_initialized(f2ptr cause, f2ptr this) {
  if (f2__core_extension__initialized_time_stamp(cause, this) != nil) {
    return nil;
  }
  assert_value(f2__core_extension__initialize(cause, this));
  return nil;
}

f2ptr f2__core_extension__assure_initialized(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension, this);
  return raw__core_extension__assure_initialized(cause, this);
}
def_pcfunk1(core_extension__assure_initialized, this,
	    "",
	    return f2__core_extension__assure_initialized(this_cause, this));


f2ptr raw__core_extension__assure_destroyed(f2ptr cause, f2ptr this) {
  if (f2__core_extension__initialized_time_stamp(cause, this) == nil) {
    return nil;
  }
  assert_value(f2__core_extension__destroy(cause, this));
  return nil;
}

f2ptr f2__core_extension__assure_destroyed(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension, this);
  return raw__core_extension__assure_destroyed(cause, this);
}
def_pcfunk1(core_extension__assure_destroyed, this,
	    "",
	    return f2__core_extension__assure_destroyed(this_cause, this));


f2ptr raw__core_extension__changed_on_disk(f2ptr cause, f2ptr this) {
  f2ptr dynamic_library_handler = assert_value(f2__global_dlfcn_dynamic_library_handler(cause));
  f2ptr search_pathnames        = assert_value(f2__dlfcn_dynamic_library_handler__search_pathnames(cause, dynamic_library_handler));
  f2ptr filename                = assert_value(f2__core_extension__filename(cause, this));
  f2ptr dynamic_library         = assert_value(f2__global_dlfcn_dynamic_library(cause, filename));
  f2ptr changed_on_disk         = assert_value(f2__dlfcn_dynamic_library__changed_on_disk(cause, dynamic_library, search_pathnames));
  return changed_on_disk;
}

f2ptr f2__core_extension__changed_on_disk(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension, this);
  return raw__core_extension__changed_on_disk(cause, this);
}
def_pcfunk1(core_extension__changed_on_disk, this,
	    "",
	    return f2__core_extension__changed_on_disk(this_cause, this));


f2ptr f2core_extension__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension__primobject_type__new(cause);
  {char* slot_name = "initialize";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__funk);}
  {char* slot_name = "destroy";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__funk);}
  {char* slot_name = "assure_initialized"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__funk);}
  {char* slot_name = "assure_destroyed";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_destroyed__funk);}
  {char* slot_name = "changed_on_disk";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension.changed_on_disk__funk);}
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
def_pcfunk0(core_extension_handler__new,
	    "",
	    return f2__core_extension_handler__new(this_cause));


f2ptr raw__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename) {
  f2ptr core_extension_name_hash = f2__core_extension_handler__core_extension_name_hash(cause, this);
  f2ptr core_extension           = assert_value(f2__core_extension__new(cause, name, filename));
  assert_argument_type(core_extension, core_extension);
  f2__ptypehash__add(cause, core_extension_name_hash, name, core_extension);
  return nil;
}

f2ptr f2__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename) {
  assert_argument_type(core_extension_handler, this);
  assert_argument_type(string,                 filename);
  return raw__core_extension_handler__add_new_core_extension(cause, this, name, filename);
}
def_pcfunk3(core_extension_handler__add_new_core_extension, this, name, filename,
	    "",
	    return f2__core_extension_handler__add_new_core_extension(this_cause, this, name, filename));


f2ptr raw__core_extension_handler__lookup_core_extension(f2ptr cause, f2ptr this, f2ptr name) {
  f2ptr core_extension_name_hash = f2__core_extension_handler__core_extension_name_hash(cause, this);
  return f2__ptypehash__lookup(cause, core_extension_name_hash, name);
}

f2ptr f2__core_extension_handler__lookup_core_extension(f2ptr cause, f2ptr this, f2ptr name) {
  assert_argument_type(core_extension_handler, this);
  return raw__core_extension_handler__lookup_core_extension(cause, this, name);
}
def_pcfunk2(core_extension_handler__lookup_core_extension, this, name,
	    "",
	    return f2__core_extension_handler__lookup_core_extension(this_cause, this, name));


f2ptr raw__core_extension_handler__unload_changed(f2ptr cause, f2ptr this) {
  f2ptr changed_core_extensions = nil;
  {
    f2ptr core_extension_name_hash = assert_value(f2__core_extension_handler__core_extension_name_hash(cause, this));
    assert_argument_type(ptypehash, core_extension_name_hash);
    ptypehash__value__iteration(cause, core_extension_name_hash, core_extension,
				assert_value(core_extension);
				assert_argument_type(core_extension, core_extension);
				f2ptr changed_on_disk = f2__core_extension__changed_on_disk(cause, core_extension);
				if (! raw__larva__is_type(cause, changed_on_disk)) {
				  if (changed_on_disk != nil) {
				    changed_core_extensions = f2cons__new(cause, core_extension, changed_core_extensions);
				  }
				}
				);
  }
  {
    f2ptr iter = changed_core_extensions;
    while (iter) {
      f2ptr core_extension = assert_value(f2__cons__car(cause, iter));
      {
	assert_value(f2__core_extension__assure_destroyed(cause, core_extension));
	f2ptr filename = f2__core_extension__filename(cause, core_extension);
	assert_value(f2__global_dlfcn_dynamic_library__unload_dynamic_library(cause, filename));
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  return nil;
}

f2ptr f2__core_extension_handler__unload_changed(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_handler, this);
  return raw__core_extension_handler__unload_changed(cause, this);
}
def_pcfunk1(core_extension_handler__unload_changed, this,
	    "",
	    return f2__core_extension_handler__unload_changed(this_cause, this));


f2ptr raw__core_extension_handler__reset_to_boot_state(f2ptr cause, f2ptr this) {
  f2ptr core_extension_name_hash = f2__core_extension_handler__core_extension_name_hash(cause, this);
  ptypehash__value__iteration(cause, core_extension_name_hash, core_extension,
			      f2__core_extension__initialized_time_stamp__set(cause, core_extension, nil);
			      );
  return nil;
}

f2ptr f2__core_extension_handler__reset_to_boot_state(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_handler, this);
  return raw__core_extension_handler__reset_to_boot_state(cause, this);
}
def_pcfunk1(core_extension_handler__reset_to_boot_state, this,
	    "",
	    return f2__core_extension_handler__reset_to_boot_state(this_cause, this));



f2ptr f2core_extension_handler__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension_handler__primobject_type__new(cause);
  {char* slot_name = "add_new_core_extension"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__funk);}
  {char* slot_name = "lookup_core_extension";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__funk);}
  {char* slot_name = "unload_changed";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.unload_changed__funk);}
  {char* slot_name = "reset_to_boot_state";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.reset_to_boot_state__funk);}
  return this;
}


f2ptr f2__global_core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr name, f2ptr filename) {
  assert_argument_type(string, filename);
  f2ptr core_extension_handler = environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"));
  if (raw__larva__is_type(cause, core_extension_handler)) {
    return core_extension_handler;
  }
  if (! raw__core_extension_handler__is_type(cause, core_extension_handler)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__core_extension_handler__add_new_core_extension(cause, core_extension_handler, name, filename);
}
def_pcfunk2(global_core_extension_handler__add_new_core_extension, name, filename,
	    "",
	    return f2__global_core_extension_handler__add_new_core_extension(this_cause, name, filename));


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
def_pcfunk1(global_core_extension_handler__lookup_core_extension, name,
	    "",
	    return f2__global_core_extension_handler__lookup_core_extension(this_cause, name));


f2ptr f2__global_core_extension_handler__unload_changed(f2ptr cause) {
  f2ptr core_extension_handler = assert_value(environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-")));
  assert_argument_type(core_extension_handler, core_extension_handler);
  return f2__core_extension_handler__unload_changed(cause, core_extension_handler);
}
def_pcfunk0(global_core_extension_handler__unload_changed,
	    "",
	    return f2__global_core_extension_handler__unload_changed(this_cause));


f2ptr f2__global_core_extension_handler__reset_to_boot_state(f2ptr cause) {
  f2ptr core_extension_handler = environment__lookup_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"));
  if (raw__larva__is_type(cause, core_extension_handler)) {
    return core_extension_handler;
  }
  if (! raw__core_extension_handler__is_type(cause, core_extension_handler)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2__core_extension_handler__reset_to_boot_state(cause, core_extension_handler);
}
def_pcfunk0(global_core_extension_handler__reset_to_boot_state,
	    "",
	    return f2__global_core_extension_handler__reset_to_boot_state(this_cause));


// **

void f2__core_extension__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // core_extension
  
  init_frame_object__4_slot__defragment__fix_pointers(core_extension, name, filename, initialized_time_stamp_cmutex, initialized_time_stamp);
  
  f2__primcfunk__init__defragment__fix_pointers(core_extension__new);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension__initialize);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension__destroy);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension__assure_initialized);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_destroyed__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension__assure_destroyed);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_destroyed__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.changed_on_disk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension__changed_on_disk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension.changed_on_disk__funk);
  
  
  // core_extension_handler
  
  init_frame_object__1_slot__defragment__fix_pointers(core_extension_handler, core_extension_name_hash);
  
  f2__primcfunk__init__defragment__fix_pointers(core_extension_handler__new);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_handler__add_new_core_extension);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_handler__lookup_core_extension);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.unload_changed__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_handler__unload_changed);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.unload_changed__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.reset_to_boot_state__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_handler__reset_to_boot_state);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.reset_to_boot_state__funk);
  
  
  // global_core_extension_handler
  
  f2__primcfunk__init__defragment__fix_pointers(global_core_extension_handler__add_new_core_extension);
  f2__primcfunk__init__defragment__fix_pointers(global_core_extension_handler__lookup_core_extension);
  f2__primcfunk__init__defragment__fix_pointers(global_core_extension_handler__unload_changed);
  f2__primcfunk__init__defragment__fix_pointers(global_core_extension_handler__reset_to_boot_state);
}

void f2__core_extension__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // core_extension
  
  init_frame_object__4_slot(core_extension, name, filename, initialized_time_stamp_cmutex, initialized_time_stamp);
  
  f2__primcfunk__init__2(core_extension__new, name, filename);
  
  {char* symbol_str = "initialize"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__initialize, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.initialize__funk = never_gc(cfunk);}
  
  {char* symbol_str = "destroy"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__destroy, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.destroy__funk = never_gc(cfunk);}
  
  {char* symbol_str = "assure_initialized"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__assure_initialized, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_initialized__funk = never_gc(cfunk);}
  
  {char* symbol_str = "assure_destroyed"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_destroyed__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__assure_destroyed, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.assure_destroyed__funk = never_gc(cfunk);}
  
  {char* symbol_str = "changed_on_disk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension.changed_on_disk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension__changed_on_disk, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension.changed_on_disk__funk = never_gc(cfunk);}
  
  
  // core_extension_handler
  
  init_frame_object__1_slot(core_extension_handler, core_extension_name_hash);
  
  f2__primcfunk__init__0(core_extension_handler__new);
  
  {char* symbol_str = "add_new_core_extension"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_handler__add_new_core_extension, name, filename, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.add_new_core_extension__funk = never_gc(cfunk);}
  
  {char* symbol_str = "lookup_core_extension"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_handler__lookup_core_extension, name, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.lookup_core_extension__funk = never_gc(cfunk);}
  
  {char* symbol_str = "unload_changed"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.unload_changed__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(core_extension_handler__unload_changed, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.unload_changed__funk = never_gc(cfunk);}
  
  {char* symbol_str = "reset_to_boot_state"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.reset_to_boot_state__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(core_extension_handler__reset_to_boot_state, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_handler.reset_to_boot_state__funk = never_gc(cfunk);}
  
  
  // global_core_extension_handler
  
  f2__primcfunk__init__2(global_core_extension_handler__add_new_core_extension, name, filename);
  f2__primcfunk__init__1(global_core_extension_handler__lookup_core_extension,  name);
  f2__primcfunk__init__0(global_core_extension_handler__unload_changed);
  f2__primcfunk__init__0(global_core_extension_handler__reset_to_boot_state);
}

void f2__core_extension__initialize_module() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "core_extension", "", &f2__core_extension__reinitialize_globalvars, &f2__core_extension__defragment__fix_pointers);
  
  f2__core_extension__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  environment__add_var_value(cause, global_environment(), new__symbol(cause, "-core_extension_handler-"), f2__core_extension_handler__new(cause));
}





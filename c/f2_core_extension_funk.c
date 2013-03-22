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

// core_extension_funk

def_frame_object__global__8_slot(core_extension_funk,
				 core_extension_name,
				 name,
				 cname,
				 cfunk__cached,
				 cfunk__cached__time_stamp,
				 args_cname,
				 is_funktional_cname,
				 documentation_cname);

f2ptr raw__core_extension_funk__new(f2ptr cause, f2ptr core_extension_name, f2ptr name) {
  f2ptr cname                     = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list2__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name))));
  f2ptr cfunk__cached             = nil;
  f2ptr cfunk__cached__time_stamp = nil;
  f2ptr args_cname                = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name), new__string(cause, "__args"))));
  f2ptr is_funktional_cname       = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name), new__string(cause, "__is_funktional"))));
  f2ptr documentation_cname       = f2__string__as__symbol(cause, f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "pcfunk__core_extension_funk__"), f2__exp__as__string(cause, name), new__string(cause, "__documentation"))));
  return f2core_extension_funk__new(cause,
				    core_extension_name,
				    name,
				    cname,
				    cfunk__cached,
				    cfunk__cached__time_stamp,
				    args_cname,
				    is_funktional_cname,
				    documentation_cname);
}

f2ptr f2__core_extension_funk__new(f2ptr cause, f2ptr core_extension_name, f2ptr name) {
  assert_argument_type(symbol, core_extension_name);
  assert_argument_type(symbol, name);
  return raw__core_extension_funk__new(cause, core_extension_name, name);
}
def_pcfunk2(core_extension_funk__new, core_extension_name, name,
	    "",
	    return f2__core_extension_funk__new(this_cause, core_extension_name, name));


f2ptr raw__core_extension_funk__filename(f2ptr cause, f2ptr this) {
  f2ptr core_extension_name = f2__core_extension_funk__core_extension_name(cause, this);
  f2ptr core_extension      = f2__global_core_extension_handler__lookup_core_extension(cause, core_extension_name);
  catch_value(core_extension,
	      f2list10__new(cause,
			    new__symbol(cause, "bug_name"),            new__symbol(cause, "could_not_lookup_core_extension"),
			    new__symbol(cause, "funkname"),            new__symbol(cause, "core_extension_funk-filename"),
			    new__symbol(cause, "core_extension"),      core_extension,
			    new__symbol(cause, "core_extension_name"), core_extension_name,
			    new__symbol(cause, "this"),                this));
  assert_argument_type(core_extension, core_extension);
  return f2__core_extension__filename(cause, core_extension);
}

f2ptr f2__core_extension_funk__filename(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__filename(cause, this);
}
def_pcfunk1(core_extension_funk__filename, this,
	    "",
	    return f2__core_extension_funk__filename(this_cause, this));


f2ptr raw__core_extension_funk__pointer(f2ptr cause, f2ptr this) {
  f2ptr filename = f2__core_extension_funk__filename(cause, this);
  catch_value(filename,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "could_not_get_core_extension_funk_filename"),
			   new__symbol(cause, "funkname"), new__symbol(cause, "core_extension_funk-pointer"),
			   new__symbol(cause, "filename"), filename,
			   new__symbol(cause, "this"),     this));
  f2ptr cname = f2__core_extension_funk__cname(cause, this);
  return f2__global_dlfcn_dynamic_library__lookup_symbol(cause, filename, cname);
}

f2ptr f2__core_extension_funk__pointer(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__pointer(cause, this);
}
def_pcfunk1(core_extension_funk__pointer, this,
	    "",
	    return f2__core_extension_funk__pointer(this_cause, this));


f2ptr raw__core_extension_funk__env(f2ptr cause, f2ptr this) {
  return global_environment();
}

f2ptr f2__core_extension_funk__env(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__env(cause, this);
}
def_pcfunk1(core_extension_funk__env, this,
	    "",
	    return f2__core_extension_funk__env(this_cause, this));


f2ptr raw__core_extension_funk__cfunk(f2ptr cause, f2ptr this) {
  f2ptr core_extension_name                    = f2__core_extension_funk__core_extension_name(cause, this);
  f2ptr core_extension                         = f2__global_core_extension_handler__lookup_core_extension(cause, core_extension_name);
  f2ptr core_extension__initialized_time_stamp = f2__core_extension__initialized_time_stamp(cause, core_extension);
  f2ptr cfunk__cached__time_stamp              = f2__core_extension_funk__cfunk__cached__time_stamp(cause, this);
  f2ptr cfunk                                  = nil;
  if ((cfunk__cached__time_stamp != nil) &&
      raw__eq(cause, cfunk__cached__time_stamp, core_extension__initialized_time_stamp)) {
    cfunk = f2__core_extension_funk__cfunk__cached(cause, this);
  } else {
    {
      f2ptr pointer = raw__core_extension_funk__pointer(cause, this);
      catch_value(pointer,
		  f2list8__new(cause,
			       new__symbol(cause, "bug_name"), new__symbol(cause, "could_not_get_core_extension_funk_pointer"),
			       new__symbol(cause, "funkname"), new__symbol(cause, "core_extension_funk-cfunk"),
			       new__symbol(cause, "pointer"),  pointer,
			       new__symbol(cause, "this"),     this));
      assert_argument_type(pointer, pointer);
      
      f2ptr name                       = f2__core_extension_funk__name(cause, this);
      f2ptr args                       = f2__core_extension_funk__args(cause, this);
      f2ptr stack_machine_code_pointer = nil;
      f2ptr cfunkptr                   = f2pointer__new(cause, raw_executable__to__relative_ptr(f2pointer__p(pointer, cause)));
      f2ptr env                        = f2__core_extension_funk__env(cause, this);
      f2ptr is_funktional              = f2__core_extension_funk__is_funktional(cause, this);
      f2ptr documentation              = f2__core_extension_funk__documentation(cause, this);
      cfunk = f2cfunk__new(cause, name, args, stack_machine_code_pointer, cfunkptr, env, is_funktional, documentation);
    }
    f2ptr cfunk__cached       = cfunk;
    cfunk__cached__time_stamp = core_extension__initialized_time_stamp;
    f2__core_extension_funk__cfunk__cached__set(            cause, this, cfunk__cached);
    f2__core_extension_funk__cfunk__cached__time_stamp__set(cause, this, cfunk__cached__time_stamp);
  }
  return cfunk;
}

f2ptr f2__core_extension_funk__cfunk(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__cfunk(cause, this);
}
def_pcfunk1(core_extension_funk__cfunk, this,
	    "",
	    return f2__core_extension_funk__cfunk(this_cause, this));


f2ptr raw__core_extension_funk__apply_without_initializing(f2ptr cause, f2ptr this, f2ptr args) {
  f2ptr cfunk = raw__core_extension_funk__cfunk(cause, this);
  catch_value(cfunk,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "could_not_get_core_extension_funk_cfunk"),
			   new__symbol(cause, "funkname"), new__symbol(cause, "core_extension_funk-apply_without_initializing"),
			   new__symbol(cause, "cfunk"),    cfunk,
			   new__symbol(cause, "this"),     this));
  assert_argument_type(cfunk, cfunk);
  return f2__cfunk__apply(cause, cfunk, f2__this__fiber(cause), args);
}

f2ptr f2__core_extension_funk__apply_without_initializing(f2ptr cause, f2ptr this, f2ptr args) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__apply_without_initializing(cause, this, args);
}
def_pcfunk2(core_extension_funk__apply_without_initializing, this, args,
	    "",
	    return f2__core_extension_funk__apply_without_initializing(this_cause, this, args));


f2ptr raw__core_extension_funk__apply(f2ptr cause, f2ptr this, f2ptr args) {
  f2ptr core_extension_name = f2__core_extension_funk__core_extension_name(cause, this);
  f2ptr core_extension      = f2__global_core_extension_handler__lookup_core_extension(cause, core_extension_name);
  catch_value(core_extension,
	      f2list10__new(cause,
			    new__symbol(cause, "bug_name"),            new__symbol(cause, "could_not_lookup_core_extension"),
			    new__symbol(cause, "funkname"),            new__symbol(cause, "core_extension_funk-apply"),
			    new__symbol(cause, "core_extension_name"), core_extension_name,
			    new__symbol(cause, "core_extension"),      core_extension,
			    new__symbol(cause, "this"),                this));
  f2ptr result = f2__core_extension__assure_initialized(cause, core_extension);
  catch_value(result,
	      f2list12__new(cause,
			    new__symbol(cause, "bug_name"),            new__symbol(cause, "could_not_assure_core_extension_is_initialized"),
			    new__symbol(cause, "funkname"),            new__symbol(cause, "core_extension_funk-apply"),
			    new__symbol(cause, "core_extension_name"), core_extension_name,
			    new__symbol(cause, "core_extension"),      core_extension,
			    new__symbol(cause, "result"),              result,
			    new__symbol(cause, "this"),                this));
  return raw__core_extension_funk__apply_without_initializing(cause, this, args);
}

f2ptr f2__core_extension_funk__apply(f2ptr cause, f2ptr this, f2ptr args) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__apply(cause, this, args);
}
def_pcfunk2(core_extension_funk__apply, this, args,
	    "",
	    return f2__core_extension_funk__apply(this_cause, this, args));


f2ptr raw__core_extension_funk__args_pointer(f2ptr cause, f2ptr this) {
  f2ptr filename = f2__core_extension_funk__filename(cause, this);
  catch_value(filename,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "could_not_get_core_extension_funk_filename"),
			   new__symbol(cause, "funkname"), new__symbol(cause, "core_extension_funk-args_pointer"),
			   new__symbol(cause, "filename"), filename,
			   new__symbol(cause, "this"),     this));
  f2ptr args_cname = f2__core_extension_funk__args_cname(cause, this);
  return f2__global_dlfcn_dynamic_library__lookup_symbol(cause, filename, args_cname);
}

f2ptr f2__core_extension_funk__args_pointer(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__args_pointer(cause, this);
}
def_pcfunk1(core_extension_funk__args_pointer, this,
	    "",
	    return f2__core_extension_funk__args_pointer(this_cause, this));


f2ptr raw__core_extension_funk__args_cfunk(f2ptr cause, f2ptr this) {
  f2ptr args_pointer = f2__core_extension_funk__args_pointer(cause, this);
  catch_value(args_pointer,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"),     new__symbol(cause, "could_not_get_core_extension_funk_pointer"),
			   new__symbol(cause, "funkname"),     new__symbol(cause, "core_extension_funk-args_cfunk"),
			   new__symbol(cause, "args_pointer"), args_pointer,
			   new__symbol(cause, "this"),         this));
  assert_argument_type(pointer, args_pointer);
  
  f2ptr name          = f2__core_extension_funk__args_cname(cause, this);
  f2ptr args          = nil;
  f2ptr cfunkptr      = f2pointer__new(cause, raw_executable__to__relative_ptr(f2pointer__p(args_pointer, cause)));
  f2ptr env           = global_environment();
  f2ptr is_funktional = f2bool__new(boolean__true);
  f2ptr documentation = new__string(cause, "This cfunk returns the arguments for its core_extension_funk.");
  return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);
}

f2ptr f2__core_extension_funk__args_cfunk(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__args_cfunk(cause, this);
}
def_pcfunk1(core_extension_funk__args_cfunk, this,
	    "",
	    return f2__core_extension_funk__args_cfunk(this_cause, this));


f2ptr raw__core_extension_funk__args(f2ptr cause, f2ptr this) {
  f2ptr args_cfunk = raw__core_extension_funk__args_cfunk(cause, this);
  catch_value(args_cfunk,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"),   new__symbol(cause, "could_not_get_core_extension_funk_cfunk"),
			   new__symbol(cause, "funkname"),   new__symbol(cause, "core_extension_funk-args"),
			   new__symbol(cause, "args_cfunk"), args_cfunk,
			   new__symbol(cause, "this"),       this));
  assert_argument_type(cfunk, args_cfunk);
  return f2__cfunk__apply(cause, args_cfunk, f2__this__fiber(cause), nil);
}

f2ptr f2__core_extension_funk__args(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__args(cause, this);
}
def_pcfunk1(core_extension_funk__args, this,
	    "",
	    return f2__core_extension_funk__args(this_cause, this));


f2ptr raw__core_extension_funk__is_funktional_pointer(f2ptr cause, f2ptr this) {
  f2ptr filename   = f2__core_extension_funk__filename(cause, this);
  catch_value(filename,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "could_not_get_core_extension_funk_filename"),
			   new__symbol(cause, "funkname"), new__symbol(cause, "core_extension_funk-is_funktional_pointer"),
			   new__symbol(cause, "filename"), filename,
			   new__symbol(cause, "this"),     this));
  f2ptr is_funktional_cname = f2__core_extension_funk__is_funktional_cname(   cause, this);
  return f2__global_dlfcn_dynamic_library__lookup_symbol(cause, filename, is_funktional_cname);
}

f2ptr f2__core_extension_funk__is_funktional_pointer(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__is_funktional_pointer(cause, this);
}
def_pcfunk1(core_extension_funk__is_funktional_pointer, this,
	    "",
	    return f2__core_extension_funk__is_funktional_pointer(this_cause, this));


f2ptr raw__core_extension_funk__is_funktional_cfunk(f2ptr cause, f2ptr this) {
  f2ptr is_funktional_pointer = f2__core_extension_funk__is_funktional_pointer(cause, this);
  catch_value(is_funktional_pointer,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"),              new__symbol(cause, "could_not_get_core_extension_funk_pointer"),
			   new__symbol(cause, "funkname"),              new__symbol(cause, "core_extension_funk-is_funktional_pointer"),
			   new__symbol(cause, "is_funktional_pointer"), is_funktional_pointer,
			   new__symbol(cause, "this"),                  this));
  assert_argument_type(pointer, is_funktional_pointer);
  
  f2ptr name          = f2__core_extension_funk__is_funktional_cname(cause, this);
  f2ptr args          = nil;
  f2ptr cfunkptr      = f2pointer__new(cause, raw_executable__to__relative_ptr(f2pointer__p(is_funktional_pointer, cause)));
  f2ptr env           = global_environment();
  f2ptr is_funktional = f2bool__new(boolean__true);
  f2ptr documentation = new__string(cause, "This cfunk returns whether its core_extension_funk is funktional.");
  return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);
}

f2ptr f2__core_extension_funk__is_funktional_cfunk(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__is_funktional_cfunk(cause, this);
}
def_pcfunk1(core_extension_funk__is_funktional_cfunk, this,
	    "",
	    return f2__core_extension_funk__is_funktional_cfunk(this_cause, this));


f2ptr raw__core_extension_funk__is_funktional(f2ptr cause, f2ptr this) {
  f2ptr is_funktional_cfunk = raw__core_extension_funk__is_funktional_cfunk(cause, this);
  catch_value(is_funktional_cfunk,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"),            new__symbol(cause, "could_not_get_core_extension_funk_is_funktional_cfunk"),
			   new__symbol(cause, "funkname"),            new__symbol(cause, "core_extension_funk-is_funktional"),
			   new__symbol(cause, "is_funktional_cfunk"), is_funktional_cfunk,
			   new__symbol(cause, "this"),                this));
  assert_argument_type(cfunk, is_funktional_cfunk);
  return f2__cfunk__apply(cause, is_funktional_cfunk, f2__this__fiber(cause), nil);
}

f2ptr f2__core_extension_funk__is_funktional(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__is_funktional(cause, this);
}
def_pcfunk1(core_extension_funk__is_funktional, this,
	    "",
	    return f2__core_extension_funk__is_funktional(this_cause, this));


f2ptr raw__core_extension_funk__documentation_pointer(f2ptr cause, f2ptr this) {
  f2ptr filename   = f2__core_extension_funk__filename(cause, this);
  catch_value(filename,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "could_not_get_core_extension_funk_filename"),
			   new__symbol(cause, "funkname"), new__symbol(cause, "core_extension_funk-documentation_pointer"),
			   new__symbol(cause, "filename"), filename,
			   new__symbol(cause, "this"),     this));
  f2ptr documentation_cname = f2__core_extension_funk__documentation_cname(   cause, this);
  return f2__global_dlfcn_dynamic_library__lookup_symbol(cause, filename, documentation_cname);
}

f2ptr f2__core_extension_funk__documentation_pointer(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__documentation_pointer(cause, this);
}
def_pcfunk1(core_extension_funk__documentation_pointer, this,
	    "",
	    return f2__core_extension_funk__documentation_pointer(this_cause, this));


f2ptr raw__core_extension_funk__documentation_cfunk(f2ptr cause, f2ptr this) {
  f2ptr documentation_pointer = f2__core_extension_funk__documentation_pointer(cause, this);
  catch_value(documentation_pointer,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"),              new__symbol(cause, "could_not_get_core_extension_funk_documentation_pointer"),
			   new__symbol(cause, "funkname"),              new__symbol(cause, "core_extension_funk-documentation_cfunk"),
			   new__symbol(cause, "documentation_pointer"), documentation_pointer,
			   new__symbol(cause, "this"),                  this));
  assert_argument_type(pointer, documentation_pointer);
  
  f2ptr name          = f2__core_extension_funk__documentation_cname(cause, this);
  f2ptr args          = nil;
  f2ptr cfunkptr      = f2pointer__new(cause, raw_executable__to__relative_ptr(f2pointer__p(documentation_pointer, cause)));
  f2ptr env           = global_environment();
  f2ptr is_funktional = f2bool__new(boolean__true);
  f2ptr documentation = new__string(cause, "This cfunk returns the documentation for its core_extension_funk.");
  return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);
}

f2ptr f2__core_extension_funk__documentation_cfunk(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__documentation_cfunk(cause, this);
}
def_pcfunk1(core_extension_funk__documentation_cfunk, this,
	    "",
	    return f2__core_extension_funk__documentation_cfunk(this_cause, this));


f2ptr raw__core_extension_funk__documentation(f2ptr cause, f2ptr this) {
  f2ptr documentation_cfunk = raw__core_extension_funk__documentation_cfunk(cause, this);
  catch_value(documentation_cfunk,
	      f2list8__new(cause,
			   new__symbol(cause, "bug_name"),            new__symbol(cause, "could_not_get_core_extension_funk_documentation_cfunk"),
			   new__symbol(cause, "funkname"),            new__symbol(cause, "core_extension_funk-documentation"),
			   new__symbol(cause, "documentation_cfunk"), documentation_cfunk,
			   new__symbol(cause, "this"),                this));
  assert_argument_type(cfunk, documentation_cfunk);
  return f2__cfunk__apply(cause, documentation_cfunk, f2__this__fiber(cause), nil);
}

f2ptr f2__core_extension_funk__documentation(f2ptr cause, f2ptr this) {
  assert_argument_type(core_extension_funk, this);
  return raw__core_extension_funk__documentation(cause, this);
}
def_pcfunk1(core_extension_funk__documentation, this,
	    "",
	    return f2__core_extension_funk__documentation(this_cause, this));


f2ptr raw__core_extension_funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list12__new(cause,
						new__symbol(cause, "print_object_type"),   new__symbol(cause, "core_extension_funk"),
						new__symbol(cause, "core_extension_name"), f2__core_extension_funk__core_extension_name(cause, this),
						new__symbol(cause, "name"),                f2__core_extension_funk__name(               cause, this),
						new__symbol(cause, "args"),                f2__core_extension_funk__args(               cause, this),
						new__symbol(cause, "is_funktional"),       f2__core_extension_funk__is_funktional(      cause, this),
						new__symbol(cause, "documentation"),       f2__core_extension_funk__documentation(      cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__core_extension_funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(core_extension_funk,  this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__core_extension_funk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(core_extension_funk__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__core_extension_funk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2core_extension_funk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2core_extension_funk__primobject_type__new(cause);
  {char* slot_name = "pointer";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__funk);}
  {char* slot_name = "env";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.env__funk);}
  {char* slot_name = "cfunk";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__funk);}
  {char* slot_name = "apply";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__funk);}
  {char* slot_name = "apply_without_initializing"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply_without_initializing__funk);}
  {char* slot_name = "args_pointer";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__funk);}
  {char* slot_name = "args_cfunk";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__funk);}
  {char* slot_name = "args";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__funk);}
  {char* slot_name = "is_funktional_pointer";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_pointer__funk);}
  {char* slot_name = "is_funktional_cfunk";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_cfunk__funk);}
  {char* slot_name = "is_funktional";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__funk);}
  {char* slot_name = "documentation_pointer";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_pointer__funk);}
  {char* slot_name = "documentation_cfunk";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_cfunk__funk);}
  {char* slot_name = "documentation";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__funk);}
  {char* slot_name = "terminal_print_with_frame";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__funk);}
  return this;
}





// **

void f2__core_extension_funk__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  // core_extension_funk
  
  init_frame_object__6_slot__defragment__fix_pointers(core_extension_funk, core_extension_name, name, cname, args_cname, is_funktional_cname, documentation_cname);
  
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__new);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__pointer);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.env__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__env);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.env__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__cfunk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__apply);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply_without_initializing__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__apply_without_initializing);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply_without_initializing__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__args_pointer);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__args_cfunk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__args);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_pointer__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__is_funktional_pointer);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_pointer__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_cfunk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__is_funktional_cfunk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_cfunk__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__is_funktional);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_pointer__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__documentation_pointer);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_pointer__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_cfunk__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__documentation_cfunk);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_cfunk__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__symbol);
  f2__primcfunk__init__defragment__fix_pointers(core_extension_funk__documentation);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__funk);
}

void f2__core_extension_funk__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // core_extension_funk
  
  init_frame_object__6_slot(core_extension_funk, core_extension_name, name, cname, args_cname, is_funktional_cname, documentation_cname);
  
  f2__primcfunk__init__2(core_extension_funk__new, filename, name);
  
  {char* symbol_str = "pointer"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__pointer, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.pointer__funk = never_gc(cfunk);}
  
  {char* symbol_str = "env"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.env__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__env, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.env__funk = never_gc(cfunk);}
  
  {char* symbol_str = "cfunk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__cfunk, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.cfunk__funk = never_gc(cfunk);}
  
  {char* symbol_str = "apply"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_funk__apply, this, args, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply__funk = never_gc(cfunk);}
  
  {char* symbol_str = "apply_without_initializing"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply_without_initializing__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_funk__apply_without_initializing, this, args, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.apply_without_initializing__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(core_extension_funk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  {char* symbol_str = "args_pointer"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__args_pointer, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_pointer__funk = never_gc(cfunk);}
  
  {char* symbol_str = "args_cfunk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__args_cfunk, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args_cfunk__funk = never_gc(cfunk);}
  
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__args, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.args__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_funktional_pointer"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_pointer__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__is_funktional_pointer, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_pointer__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_funktional_cfunk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_cfunk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__is_funktional_cfunk, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional_cfunk__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_funktional"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__is_funktional, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.is_funktional__funk = never_gc(cfunk);}
  
  {char* symbol_str = "documentation_pointer"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_pointer__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__documentation_pointer, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_pointer__funk = never_gc(cfunk);}
  
  {char* symbol_str = "documentation_cfunk"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_cfunk__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__documentation_cfunk, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation_cfunk__funk = never_gc(cfunk);}
  
  {char* symbol_str = "documentation"; __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(core_extension_funk__documentation, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_core_extension_funk.documentation__funk = never_gc(cfunk);}
}

void f2__core_extension_funk__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "core_extension_funk", "", &f2__core_extension_funk__reinitialize_globalvars, &f2__core_extension_funk__defragment__fix_pointers);
  
  f2__core_extension_funk__reinitialize_globalvars();
}


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

#include "semantic_resource_action_sequence.h"
#include "../event_stream/event_stream.h"


// semantic_resource_action_sequence

f2ptr raw__semantic_resource_action_sequence__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr action_name, f2ptr agent) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_resource_action_sequence"));
  }
  assert_value(raw__semantic_action_event__type_create(cause, this, semantic_realm, action_name, agent));
  assert_value(raw__semantic_event_sequence__type_create(cause, this, semantic_realm, action_name));
  return this;
}

f2ptr raw__semantic_resource_action_sequence__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name, f2ptr agent) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_resource_action_sequence__type_create(cause, this, semantic_realm, action_name, agent));
  return this;
}

f2ptr f2__semantic_resource_action_sequence__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name, f2ptr agent) {
  assert_argument_type(semantic_realm,    semantic_realm);
  assert_argument_type(semantic_resource, agent);
  return raw__semantic_resource_action_sequence__new(cause, semantic_realm, action_name, agent);
}
export_cefunk3(semantic_resource_action_sequence__new, semantic_realm, action_name, agent, 0, "Given a semantic_resource, returns a new semantic_resource_action_sequence object.");


boolean_t raw__semantic_resource_action_sequence__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_resource_action_sequence");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__semantic_resource_action_sequence__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_resource_action_sequence__is_type(cause, thing));
}
export_cefunk1(semantic_resource_action_sequence__is_type, thing, 0, "Returns whether or not thing is of type semantic_resource_action_sequence.");


f2ptr raw__semantic_resource_action_sequence__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_resource_action_sequence__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_resource_action_sequence, this);
  return raw__semantic_resource_action_sequence__type(cause, this);
}
export_cefunk1(semantic_resource_action_sequence__type, thing, 0, "Returns the specific type of object that this semantic_resource_action_sequence is.");


f2ptr raw__semantic_resource_action_sequence__cairo_render_frame(f2ptr cause, f2ptr this) {
  f2ptr render_frame = f2__frame__new(cause, f2list2__new(cause,
							  new__symbol(cause, "cairo_render_type"), f2__object__type(cause, this)));
  {
    f2ptr action_name = raw__semantic_event__action_name(cause, this);
    f2__frame__add_var_value(cause, render_frame, new__symbol(cause, "action_name"), action_name);
  }
  {
    f2ptr agent                  = f2__semantic_action_event__agent(cause, this);
    f2ptr agent__phenomenal_name = f2__semantic_object__phenomenal_name(cause, agent);
    f2__frame__add_var_value(cause, render_frame, new__symbol(cause, "agent"), agent__phenomenal_name);
  }
  return render_frame;
}

f2ptr f2__semantic_resource_action_sequence__cairo_render_frame(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_resource_action_sequence, this);
  return raw__semantic_resource_action_sequence__cairo_render_frame(cause, this);
}
export_cefunk1(semantic_resource_action_sequence__cairo_render_frame, this, 0, "Generates a cairo_render_frame for this event.");


f2ptr f2__semantic_resource_action_sequence_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list2__new(cause,
							    new__symbol(cause, "semantic_action_event"),
							    new__symbol(cause, "semantic_event_sequence")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "new"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "is_type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "type"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "cairo_render_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__cairo_render_frame")));}
  return this;
}





// **

f2ptr f2__semantic_resource_action_sequence__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_resource_action_sequence__core_extension__ping, 0, "");

f2ptr f2__semantic_resource_action_sequence__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_resource_action_sequence, semantic_action_event);
  core_extension__ping(semantic_resource_action_sequence, semantic_event_sequence);
  status("semantic_resource_action_sequence initialized.");
  return nil;
}
export_cefunk0(semantic_resource_action_sequence__core_extension__initialize, 0, "");

f2ptr f2__semantic_resource_action_sequence__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_resource_action_sequence"), f2__semantic_resource_action_sequence_type__new(cause));
  status("semantic_resource_action_sequence types defines.");
  return nil;
}
export_cefunk0(semantic_resource_action_sequence__core_extension__define_types, 0, "");

f2ptr f2__semantic_resource_action_sequence__core_extension__destroy(f2ptr cause) {
  status("semantic_resource_action_sequence destroyed.");
  return nil;
}
export_cefunk0(semantic_resource_action_sequence__core_extension__destroy, 0, "");



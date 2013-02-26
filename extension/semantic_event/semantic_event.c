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

#include "semantic_event.h"


// semantic_event

f2ptr raw__semantic_event__type_create(f2ptr cause, f2ptr this, f2ptr semantic_realm, f2ptr action_name) {
  if (! raw__frame__contains_var(cause, this, new__symbol(cause, "type"))) {
    raw__frame__add_var_value(cause, this, new__symbol(cause, "type"), new__symbol(cause, "semantic_event"));
  }
  assert_value(raw__semantic_temporal_object__type_create(cause, this, semantic_realm));
  // avoids redefining in cases of multiple inheritance.
  if (raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "property"), new__symbol(cause, "action_name")) == nil) {
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "action_name"),         action_name);
    f2ptr start_semantic_time = f2__semantic_time__new(cause, new__symbol(cause, "before"));
    f2ptr end_semantic_time   = f2__semantic_time__new(cause, new__symbol(cause, "after"));
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "absolute_start_time"), start_semantic_time);
    raw__semantic_frame__add(cause, this, new__symbol(cause, "property"), new__symbol(cause, "absolute_end_time"),   end_semantic_time);
  }
  return this;
}

f2ptr raw__semantic_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name) {
  f2ptr this = assert_value(f2__frame__new(cause, nil));
  assert_value(raw__semantic_event__type_create(cause, this, semantic_realm, action_name));
  return this;
}

f2ptr f2__semantic_event__new(f2ptr cause, f2ptr semantic_realm, f2ptr action_name) {
  assert_argument_type(semantic_realm, semantic_realm);
  return raw__semantic_event__new(cause, semantic_realm, action_name);
}
export_cefunk2(semantic_event__new, semantic_realm, action_name, 0, "Returns a new semantic_event object.");


boolean_t raw__semantic_event__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_event");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__larva__is_type(cause, thing_type)) {
    return boolean__false;
  }
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__semantic_event__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_event__is_type(cause, thing));
}
export_cefunk1(semantic_event__is_type, thing, 0, "Returns whether or not thing is of type semantic_event.");


f2ptr raw__semantic_event__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_event__type(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__type(cause, this);
}
export_cefunk1(semantic_event__type, thing, 0, "Returns the specific type of object that this semantic_event is.");


f2ptr raw__semantic_event__action_name(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "action_name"));
}

f2ptr f2__semantic_event__action_name(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__action_name(cause, this);
}
export_cefunk1(semantic_event__action_name, this, 0, "");


f2ptr raw__semantic_event__action_name__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "action_name"), that);
}

f2ptr f2__semantic_event__action_name__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__action_name__set(cause, this, that);
}
export_cefunk2(semantic_event__action_name__set, this, that, 0, "");


f2ptr raw__semantic_event__absolute_start_time(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "absolute_start_time"));
}

f2ptr f2__semantic_event__absolute_start_time(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__absolute_start_time(cause, this);
}
export_cefunk1(semantic_event__absolute_start_time, this, 0, "");


f2ptr raw__semantic_event__absolute_start_time__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "absolute_start_time"), that);
}

f2ptr f2__semantic_event__absolute_start_time__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_event, this);
  assert_argument_type(semantic_time,  that);
  return raw__semantic_event__absolute_start_time__set(cause, this, that);
}
export_cefunk2(semantic_event__absolute_start_time__set, this, that, 0, "");


f2ptr raw__semantic_event__absolute_end_time(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "absolute_end_time"));
}

f2ptr f2__semantic_event__absolute_end_time(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__absolute_end_time(cause, this);
}
export_cefunk1(semantic_event__absolute_end_time, this, 0, "");


f2ptr raw__semantic_event__absolute_end_time__set(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__replace_type_var_value(cause, this, new__symbol(cause, "property"), new__symbol(cause, "absolute_end_time"), that);
}

f2ptr f2__semantic_event__absolute_end_time__set(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_event, this);
  assert_argument_type(semantic_time,  that);
  return raw__semantic_event__absolute_end_time__set(cause, this, that);
}
export_cefunk2(semantic_event__absolute_end_time__set, this, that, 0, "");



f2ptr raw__semantic_event__update_parent_container_start_and_end_times_with_child_start_time(f2ptr cause, f2ptr this, f2ptr child_start_time) {
  f2ptr absolute_start_time = assert_value(raw__semantic_event__absolute_start_time(cause, this));
  f2ptr absolute_end_time   = assert_value(raw__semantic_event__absolute_end_time(  cause, this));
  if (raw__semantic_time__is__before(cause, child_start_time)) {
    raw__semantic_event__absolute_start_time__set(cause, this, f2__semantic_time__new(cause, new__symbol(cause, "before")));
  } else {
    if (raw__semantic_time__is__before(cause, absolute_start_time) ||
	(f2__is_less_than(cause, child_start_time, absolute_start_time) != nil)) {
      raw__semantic_event__absolute_start_time__set(cause, this, child_start_time);
    }
    if (raw__semantic_time__is__after(cause, absolute_end_time) ||
	(f2__is_greater_than(cause, child_start_time, absolute_end_time) != nil)) {
      raw__semantic_event__absolute_end_time__set(cause, this, child_start_time);
    }
  }
  return nil;
}

f2ptr raw__semantic_event__update_parent_container_start_and_end_times_with_child_end_time(f2ptr cause, f2ptr this, f2ptr child_end_time) {
  f2ptr absolute_start_time = assert_value(raw__semantic_event__absolute_start_time(cause, this));
  f2ptr absolute_end_time   = assert_value(raw__semantic_event__absolute_end_time(  cause, this));
  if (raw__semantic_time__is__after(cause, child_end_time)) {
    raw__semantic_event__absolute_end_time__set(cause, this, f2__semantic_time__new(cause, new__symbol(cause, "after")));
  } else {
    if (raw__semantic_time__is__before(cause, absolute_start_time) ||
	(f2__is_less_than(cause, child_end_time, absolute_start_time) != nil)) {
      raw__semantic_event__absolute_start_time__set(cause, this, child_end_time);
    }
    if (raw__semantic_time__is__after(cause, absolute_end_time) ||
	(f2__is_greater_than(cause, child_end_time, absolute_end_time) != nil)) {
      raw__semantic_event__absolute_end_time__set(cause, this, child_end_time);
    }
  }
  return nil;
}

f2ptr raw__semantic_event__update_parent_container_start_and_end_times_with_child_event(f2ptr cause, f2ptr this, f2ptr child_semantic_event) {
  {
    f2ptr child_semantic_event__absolute_start_time = raw__semantic_event__absolute_start_time(cause, child_semantic_event);
    assert_value(raw__semantic_event__update_parent_container_start_and_end_times_with_child_start_time(cause, this, child_semantic_event__absolute_start_time));
  }
  {
    f2ptr child_semantic_event__absolute_end_time = raw__semantic_event__absolute_end_time(cause, child_semantic_event);
    assert_value(raw__semantic_event__update_parent_container_start_and_end_times_with_child_end_time(cause, this, child_semantic_event__absolute_end_time));
  }
  return nil;
}

f2ptr f2__semantic_event__update_parent_container_start_and_end_times_with_child_event(f2ptr cause, f2ptr this, f2ptr child_semantic_event) {
  assert_argument_type(semantic_event, this);
  assert_argument_type(semantic_event, child_semantic_event);
  return raw__semantic_event__update_parent_container_start_and_end_times_with_child_event(cause, this, child_semantic_event);
}
export_cefunk2(semantic_event__update_parent_container_start_and_end_times_with_child_event, this, child_semantic_event, 0, "");


f2ptr raw__semantic_event__update_child_container_start_and_end_times_with_parent_start_time(f2ptr cause, f2ptr this, f2ptr parent_start_time) {
  f2ptr absolute_start_time = assert_value(raw__semantic_event__absolute_start_time(cause, this));
  f2ptr absolute_end_time   = assert_value(raw__semantic_event__absolute_end_time(  cause, this));
  if (raw__semantic_time__is__before(cause, parent_start_time)) {
    raw__semantic_event__absolute_start_time__set(cause, this, f2__semantic_time__new(cause, new__symbol(cause, "before")));
  } else {
    if (raw__semantic_time__is__before(cause, absolute_start_time) ||
	(f2__is_less_than(cause, absolute_start_time, parent_start_time) != nil)) {
      raw__semantic_event__absolute_start_time__set(cause, this, parent_start_time);
    }
    if (raw__semantic_time__is__after(cause, absolute_end_time) ||
	(f2__is_less_than(cause, absolute_end_time, parent_start_time) != nil)) {
      raw__semantic_event__absolute_end_time__set(cause, this, parent_start_time);
    }
  }
  return nil;
}

f2ptr raw__semantic_event__update_child_container_start_and_end_times_with_parent_end_time(f2ptr cause, f2ptr this, f2ptr parent_end_time) {
  f2ptr absolute_start_time = assert_value(raw__semantic_event__absolute_start_time(cause, this));
  f2ptr absolute_end_time   = assert_value(raw__semantic_event__absolute_end_time(  cause, this));
  if (raw__semantic_time__is__after(cause, parent_end_time)) {
    raw__semantic_event__absolute_end_time__set(cause, this, f2__semantic_time__new(cause, new__symbol(cause, "after")));
  } else {
    if (raw__semantic_time__is__before(cause, absolute_start_time) ||
	(f2__is_greater_than(cause, absolute_start_time, parent_end_time) != nil)) {
      raw__semantic_event__absolute_end_time__set(cause, this, parent_end_time);
    }
    if (raw__semantic_time__is__after(cause, absolute_end_time) ||
	(f2__is_greater_than(cause, absolute_end_time, parent_end_time) != nil)) {
      raw__semantic_event__absolute_end_time__set(cause, this, parent_end_time);
    }
  }
  return nil;
}

f2ptr raw__semantic_event__update_child_container_start_and_end_times_with_parent_event(f2ptr cause, f2ptr this, f2ptr parent_semantic_event) {
  {
    f2ptr parent_semantic_event__absolute_start_time = raw__semantic_event__absolute_start_time(cause, parent_semantic_event);
    assert_value(raw__semantic_event__update_child_container_start_and_end_times_with_parent_start_time(cause, this, parent_semantic_event__absolute_start_time));
  }
  {
    f2ptr parent_semantic_event__absolute_end_time = raw__semantic_event__absolute_end_time(cause, parent_semantic_event);
    assert_value(raw__semantic_event__update_child_container_start_and_end_times_with_parent_end_time(cause, this, parent_semantic_event__absolute_end_time));
  }
  return nil;
}

f2ptr f2__semantic_event__update_child_container_start_and_end_times_with_parent_event(f2ptr cause, f2ptr this, f2ptr parent_semantic_event) {
  assert_argument_type(semantic_event, this);
  assert_argument_type(semantic_event, parent_semantic_event);
  return raw__semantic_event__update_child_container_start_and_end_times_with_parent_event(cause, this, parent_semantic_event);
}
export_cefunk2(semantic_event__update_child_container_start_and_end_times_with_parent_event, this, parent_semantic_event, 0, "");



f2ptr raw__semantic_event__transframe__lookup_set(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup_set(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "transframe"));
}

f2ptr f2__semantic_event__transframe__lookup_set(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__transframe__lookup_set(cause, this);
}
export_cefunk1(semantic_event__transframe__lookup_set, this, 0, "");


f2ptr raw__semantic_event__transframe__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "transframe"), that);
}

f2ptr f2__semantic_event__transframe__add(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_event,            this);
  assert_argument_type(semantic_event_transframe, that);
  return raw__semantic_event__transframe__add(cause, this, that);
}
export_cefunk2(semantic_event__transframe__add, this, that, 0, "");


f2ptr raw__semantic_event__transframe__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relation"), new__symbol(cause, "transframe"), that);
}

f2ptr f2__semantic_event__transframe__remove(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_event,            this);
  assert_argument_type(semantic_event_transframe, that);
  return raw__semantic_event__transframe__remove(cause, this, that);
}
export_cefunk2(semantic_event__transframe__remove, this, that, 0, "");


f2ptr raw__semantic_event__cairo_render_frame(f2ptr cause, f2ptr this) {
  f2ptr render_frame = f2__frame__new(cause, f2list2__new(cause,
							  new__symbol(cause, "cairo_render_type"), f2__object__type(cause, this)));
  f2ptr action_name = raw__semantic_event__action_name(cause, this);
  f2__frame__add_var_value(cause, render_frame, new__symbol(cause, "action_name"), action_name);
  return render_frame;
}

f2ptr f2__semantic_event__cairo_render_frame(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_event, this);
  return raw__semantic_event__cairo_render_frame(cause, this);
}
export_cefunk1(semantic_event__cairo_render_frame, this, 0, "Generates a cairo_render_frame for this event.");


f2ptr f2__semantic_event_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_temporal_object")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "new"),                                                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "is_type"),                                                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "type"),                                                         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "action_name"),                                                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__action_name")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "action_name"),                                                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__action_name__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "absolute_start_time"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__absolute_start_time")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "absolute_start_time"),                                          f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__absolute_start_time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "absolute_end_time"),                                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__absolute_end_time")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "set"),                 new__symbol(cause, "absolute_end_time"),                                            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__absolute_end_time__set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "update_parent_container_start_and_end_times_with_child_event"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__update_parent_container_start_and_end_times_with_child_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),             new__symbol(cause, "update_child_container_start_and_end_times_with_parent_event"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__update_child_container_start_and_end_times_with_parent_event")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup_set"), new__symbol(cause, "transframe"),                                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__transframe__lookup_set")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),        new__symbol(cause, "transframe"),                                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__transframe__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"),     new__symbol(cause, "transframe"),                                                   f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__transframe__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),                 new__symbol(cause, "cairo_render_frame"),                                           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__cairo_render_frame")));}
  return this;
}




// **

f2ptr f2__semantic_event__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_event__core_extension__ping, 0, "");

f2ptr f2__semantic_event__core_extension__initialize(f2ptr cause) {
  core_extension__ping(semantic_event, semantic_temporal_object);
  core_extension__ping(semantic_event, semantic_time);
  status("semantic_event initialized.");
  return nil;
}
export_cefunk0(semantic_event__core_extension__initialize, 0, "");

f2ptr f2__semantic_event__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_event"), f2__semantic_event_type__new(cause));
  status("semantic_event define types.");
  return nil;
}
export_cefunk0(semantic_event__core_extension__define_types, 0, "");

f2ptr f2__semantic_event__core_extension__destroy(f2ptr cause) {
  status("semantic_event destroyed.");
  return nil;
}
export_cefunk0(semantic_event__core_extension__destroy, 0, "");



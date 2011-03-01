// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#include "semantic_resource_action_sequence.h"
#include "../event_stream/event_stream.h"


// semantic_resource_action_sequence

f2ptr raw__semantic_resource_action_sequence__new(f2ptr cause, f2ptr semantic_realm, f2ptr resource) {
  f2ptr this = f2__semantic_event_sequence__new(cause, semantic_realm);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),         new__symbol(cause, "semantic_resource_action_sequence"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "type"),         new__symbol(cause, "name"),     new__symbol(cause, "semantic_resource_action_sequence"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "resource"), resource);
  return this;
}

f2ptr f2__semantic_resource_action_sequence__new(f2ptr cause, f2ptr semantic_realm, f2ptr resource) {
  if ((! raw__semantic_realm__is_type(cause, semantic_realm)) ||
      (! raw__semantic_resource__is_type(cause, resource))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource_action_sequence__new(cause, semantic_realm, resource);
}
export_cefunk2(semantic_resource_action_sequence__new, semantic_realm, resource, 0, "Given a semantic_resource, returns a new semantic_resource_action_sequence object.");


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
  if (! raw__semantic_resource_action_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource_action_sequence__type(cause, this);
}
export_cefunk1(semantic_resource_action_sequence__type, thing, 0, "Returns the specific type of object that this semantic_resource_action_sequence is.");


f2ptr raw__semantic_resource_action_sequence__resource__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "resource"));
}

f2ptr f2__semantic_resource_action_sequence__resource__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_resource_action_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource_action_sequence__resource__lookup(cause, this);
}
export_cefunk1(semantic_resource_action_sequence__resource__lookup, this, 0, "");


f2ptr raw__semantic_resource_action_sequence__resource__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "resource"), that);
}

f2ptr f2__semantic_resource_action_sequence__resource__add(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_resource_action_sequence__is_type(cause, this)) ||
      (! raw__semantic_resource__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource_action_sequence__resource__add(cause, this, that);
}
export_cefunk2(semantic_resource_action_sequence__resource__add, this, that, 0, "");


f2ptr raw__semantic_resource_action_sequence__resource__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "resource"), that);
}

f2ptr f2__semantic_resource_action_sequence__resource__remove(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_resource_action_sequence__is_type(cause, this)) ||
      (! raw__semantic_resource__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource_action_sequence__resource__remove(cause, this, that);
}
export_cefunk2(semantic_resource_action_sequence__resource__remove, this, that, 0, "");


f2ptr raw__semantic_resource_action_sequence__cairo_render_frame(f2ptr cause, f2ptr this) {
  printf("\nraw__semantic_resource_action_sequence__cairo_render_frame: I'm here."); fflush(stdout);
  f2ptr render_frame = f2__frame__new(cause, f2list2__new(cause,
							  new__symbol(cause, "cairo_render_type"), f2__object__type(cause, this)));
  {
    f2ptr action_name_set = f2__semantic_event__action_name__lookup(cause, this);
    if (action_name_set != nil) {
      f2__frame__add_var_value(cause, render_frame, new__symbol(cause, "action_name"), f2__set__an_arbitrary_element(cause, action_name_set));
    }
  }
  {
    f2ptr resource_set = f2__semantic_resource_action_sequence__resource__lookup(cause, this);
    if (resource_set != nil) {
      f2ptr resource = f2__set__an_arbitrary_element(cause, resource_set);
      f2ptr resource_name = nil;
      if (raw__semantic_resource__is_type(cause, resource)) {
	f2ptr name_set = f2__semantic_resource__name__lookup(cause, resource);
	if (name_set != nil) {
	  resource_name = f2__set__an_arbitrary_element(cause, name_set);
	} else {
	  resource_name = new__symbol(cause, "resource_name-is-nil");
	}
      } else {
	f2__terminal_print(cause, resource_set);
	resource_name = new__symbol(cause, "resource-is-not-semantic_resource");
      }
      f2__frame__add_var_value(cause, render_frame, new__symbol(cause, "resource"), resource_name);
    } else {
      f2__frame__add_var_value(cause, render_frame, new__symbol(cause, "resource"), new__symbol(cause, "resource_set-is-nil"));
    }
  }
  return render_frame;
}

f2ptr f2__semantic_resource_action_sequence__cairo_render_frame(f2ptr cause, f2ptr this) {
  if (! raw__semantic_resource_action_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_resource_action_sequence__cairo_render_frame(cause, this);
}
export_cefunk1(semantic_resource_action_sequence__cairo_render_frame, this, 0, "Generates a cairo_render_frame for this event.");


f2ptr f2__semantic_resource_action_sequence_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_event_sequence")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "new"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "is_type"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),             new__symbol(cause, "type"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-lookup"), new__symbol(cause, "resource"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__resource__lookup")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "resource"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__resource__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "resource"),           f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__resource__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),             new__symbol(cause, "cairo_render_frame"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_resource_action_sequence"), new__symbol(cause, "semantic_resource_action_sequence__cairo_render_frame")));}
  return this;
}



// **

f2ptr f2__semantic_resource_action_sequence__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_resource_action_sequence__core_extension__ping, 0, "");

f2ptr f2__semantic_resource_action_sequence__core_extension__initialize(f2ptr cause) {
  {
    f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__core_extension__ping")), nil);
    if (raw__larva__is_type(cause, result)) {
      return result;
    }
  }
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



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

#include "semantic_event_sequence.h"
#include "../event_stream/event_stream.h"


// semantic_event_sequence

f2ptr raw__semantic_event_sequence__new(f2ptr cause, f2ptr semantic_realm) {
  f2ptr this = f2__semantic_frame__new(cause, semantic_realm);
  if (raw__larva__is_type(cause, this)) {
    return this;
  }
  raw__frame__add_var_value(cause, this, new__symbol(cause, "type"),         new__symbol(cause, "semantic_event_sequence"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "type"),         new__symbol(cause, "name"), new__symbol(cause, "semantic_event_sequence"));
  raw__semantic_frame__add( cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "first_event"), nil);
  raw__semantic_frame__add( cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "last_event"),  nil);
  return this;
}

f2ptr f2__semantic_event_sequence__new(f2ptr cause, f2ptr semantic_realm) {
  if (! raw__semantic_realm__is_type(cause, semantic_realm)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__new(cause, semantic_realm);
}
export_cefunk1(semantic_event_sequence__new, semantic_realm, 0, "Returns a new semantic_event_sequence object.");


boolean_t raw__semantic_event_sequence__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "semantic_event_sequence");
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

f2ptr f2__semantic_event_sequence__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__semantic_event_sequence__is_type(cause, thing));
}
export_cefunk1(semantic_event_sequence__is_type, thing, 0, "Returns whether or not thing is of type semantic_event_sequence.");


f2ptr raw__semantic_event_sequence__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__semantic_event_sequence__type(f2ptr cause, f2ptr this) {
  if (! raw__semantic_event_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__type(cause, this);
}
export_cefunk1(semantic_event_sequence__type, thing, 0, "Returns the specific type of object that this semantic_event_sequence is.");


f2ptr raw__semantic_event_sequence__relationship__first_event__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "first_event"));
}

f2ptr f2__semantic_event_sequence__relationship__first_event__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_event_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__relationship__first_event__lookup(cause, this);
}
export_cefunk1(semantic_event_sequence__relationship__first_event__lookup, this, 0, "");


f2ptr raw__semantic_event_sequence__relationship__first_event__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "first_event"), that);
}

f2ptr f2__semantic_event_sequence__relationship__first_event__add(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_event_sequence__is_type(cause, this)) ||
      (! raw__semantic_event__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__relationship__first_event__add(cause, this, that);
}
export_cefunk2(semantic_event_sequence__relationship__first_event__add, this, that, 0, "");


f2ptr raw__semantic_event_sequence__relationship__first_event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "first_event"), that);
}

f2ptr f2__semantic_event_sequence__relationship__first_event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_event_sequence__is_type(cause, this)) ||
      (! raw__semantic_event__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__relationship__first_event__remove(cause, this, that);
}
export_cefunk2(semantic_event_sequence__relationship__first_event__remove, this, that, 0, "");


f2ptr raw__semantic_event_sequence__relationship__last_event__lookup(f2ptr cause, f2ptr this) {
  return raw__semantic_frame__lookup(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "last_event"));
}

f2ptr f2__semantic_event_sequence__relationship__last_event__lookup(f2ptr cause, f2ptr this) {
  if (! raw__semantic_event_sequence__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__relationship__last_event__lookup(cause, this);
}
export_cefunk1(semantic_event_sequence__relationship__last_event__lookup, this, 0, "");


f2ptr raw__semantic_event_sequence__relationship__last_event__add(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__add(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "last_event"), that);
}

f2ptr f2__semantic_event_sequence__relationship__last_event__add(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_event_sequence__is_type(cause, this)) ||
      (! raw__semantic_event__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__relationship__last_event__add(cause, this, that);
}
export_cefunk2(semantic_event_sequence__relationship__last_event__add, this, that, 0, "");


f2ptr raw__semantic_event_sequence__relationship__last_event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__semantic_frame__remove(cause, this, new__symbol(cause, "relationship"), new__symbol(cause, "last_event"), that);
}

f2ptr f2__semantic_event_sequence__relationship__last_event__remove(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__semantic_event_sequence__is_type(cause, this)) ||
      (! raw__semantic_event__is_type(cause, that))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__relationship__last_event__remove(cause, this, that);
}
export_cefunk2(semantic_event_sequence__relationship__last_event__remove, this, that, 0, "");


f2ptr raw__semantic_event_sequence__add_to_end(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  f2ptr last_event_set = raw__semantic_event_sequence__relationship__last_event__lookup(cause, this);
  if (raw__larva__is_type(cause, last_event_set)) {
    return last_event_set;
  }
  if (! raw__set__is_type(cause, last_event_set)) {
    return f2larva__new(cause, 31, nil);
  }
  if (raw__set__contains(cause, last_event_set, nil)) {
    raw__semantic_event_sequence__relationship__first_event__remove(cause, this, nil);
    raw__semantic_event_sequence__relationship__first_event__add(   cause, this, semantic_event);
    raw__semantic_event_sequence__relationship__last_event__remove( cause, this, nil);
    raw__semantic_event_sequence__relationship__last_event__add(    cause, this, semantic_event);
  } else {
    {
      f2ptr iter = raw__set__elements(cause, last_event_set);
      while (iter != nil) {
	f2ptr last_event = f2__cons__car(cause, iter);
	{
	  raw__semantic_event_sequence__relationship__last_event__remove(cause, this, last_event);
	  raw__semantic_temporal_object__next__add(cause, last_event, semantic_event);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
    raw__semantic_event_sequence__relationship__last_event__add(cause, this, semantic_event);
  }
  raw__semantic_temporal_object__contains__add(cause, this, semantic_event);
  return nil;
}

f2ptr f2__semantic_event_sequence__add_to_end(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  if ((! raw__semantic_event_sequence__is_type(cause, this)) ||
      (! raw__semantic_event__is_type(cause, semantic_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__add_to_end(cause, this, semantic_event);
}
export_cefunk2(semantic_event_sequence__add_to_end, this, semantic_event, 0, "");


f2ptr raw__semantic_event_sequence__add_to_beginning(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  f2ptr first_event_set = raw__semantic_event_sequence__relationship__first_event__lookup(cause, this);
  if (raw__set__contains(cause, first_event_set, nil)) {
    raw__semantic_event_sequence__relationship__first_event__remove(cause, this, nil);
    raw__semantic_event_sequence__relationship__first_event__add(   cause, this, semantic_event);
    raw__semantic_event_sequence__relationship__last_event__remove( cause, this, nil);
    raw__semantic_event_sequence__relationship__last_event__add(    cause, this, semantic_event);
  } else {
    {
      f2ptr iter = raw__set__elements(cause, first_event_set);
      while (iter != nil) {
	f2ptr first_event = f2__cons__car(cause, iter);
	{
	  raw__semantic_event_sequence__relationship__first_event__remove(cause, this,        first_event);
	  raw__semantic_temporal_object__previous__add(                   cause, first_event, semantic_event);
	}
	iter = f2__cons__cdr(cause, iter);
      }
    }
    raw__semantic_event_sequence__relationship__first_event__add(cause, this, semantic_event);
  }
  raw__semantic_temporal_object__contains__add(cause, this, semantic_event);
  return nil;
}

f2ptr f2__semantic_event_sequence__add_to_beginning(f2ptr cause, f2ptr this, f2ptr semantic_event) {
  if ((! raw__semantic_event_sequence__is_type(cause, this)) ||
      (! raw__semantic_event__is_type(cause, semantic_event))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__semantic_event_sequence__add_to_beginning(cause, this, semantic_event);
}
export_cefunk2(semantic_event_sequence__add_to_beginning, this, semantic_event, 0, "");


f2ptr f2__semantic_event_sequence_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "semantic_event")));
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "new"),                      f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__new")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "is_type"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),             new__symbol(cause, "type"),                     f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__type")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "relationship-first_event"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__relationship__first_event__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "relationship-first_event"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__relationship__first_event__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-add"),    new__symbol(cause, "relationship-last_event"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__relationship__last_event__add")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "semantic-remove"), new__symbol(cause, "relationship-last_event"),  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__relationship__last_event__remove")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "add_to_end"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__add_to_end")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"),         new__symbol(cause, "add_to_beginning"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event_sequence"), new__symbol(cause, "semantic_event_sequence__add_to_beginning")));}
  return this;
}





// **

f2ptr f2__semantic_event_sequence__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_event_sequence__core_extension_ping, 0, "");

f2ptr f2__semantic_event_sequence__core_extension_initialize(f2ptr cause) {
  f2ptr result = f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_event"), new__symbol(cause, "semantic_event__core_extension_ping")), nil);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2__add_type(cause, new__symbol(cause, "semantic_event_sequence"), f2__semantic_event_sequence_type__new(cause));
  status("semantic_event_sequence initialized.");
  return nil;
}
export_cefunk0(semantic_event_sequence__core_extension_initialize, 0, "");

f2ptr f2__semantic_event_sequence__core_extension_destroy(f2ptr cause) {
  status("semantic_event_sequence destroyed.");
  return nil;
}
export_cefunk0(semantic_event_sequence__core_extension_destroy, 0, "");



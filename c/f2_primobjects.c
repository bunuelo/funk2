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

defarray_slot(primobject__primobject_label, 0);
defarray_slot(primobject__type,             1);
defarray_slot(primobject__dynamic_slots,    2);

#define primobject_error(str) f2exception__new(cause, f2string__new(cause, strlen("primobject:error"), (u8*)"primobject:error"), f2string__new(cause, strlen(str), (u8*)str))


// primobject

f2ptr f2primobject__new(f2ptr cause, f2ptr type, f2ptr static_slot_num, f2ptr dynamic_slots) {return f2__primobject__new(cause, type, f2integer__i(static_slot_num, cause), dynamic_slots);}

f2ptr __primobject__symbol = -1;

f2ptr f2__primobject__new__trace_depth(f2ptr cause, f2ptr type, int static_slot_num, f2ptr dynamic_slots, int trace_depth) {
  release__assert(__primobject__symbol != -1, nil, "f2__primobject__new error: used before primobjects initialized.");
  f2ptr this = raw__array__new(cause, primobject__header_size + static_slot_num);
  f2primobject__primobject_label__set__trace_depth(this, cause, __primobject__symbol, trace_depth);
  f2primobject__type__set__trace_depth(            this, cause, type,                 trace_depth);
  f2primobject__dynamic_slots__set__trace_depth(   this, cause, dynamic_slots,        trace_depth);
  return this;
}

f2ptr f2__primobject__new(f2ptr cause, f2ptr type, int static_slot_num, f2ptr dynamic_slots) {
  return f2__primobject__new__trace_depth(cause, type, static_slot_num, dynamic_slots, 1);
}

f2ptr f2__primobject__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__primobject__is_type(cause, thing));}
def_pcfunk1(primobject__is_type, thing, return f2__primobject__is_type(this_cause, thing));

f2ptr f2__primobject__type(f2ptr cause, f2ptr this) {return f2primobject__type(this, cause);}
def_pcfunk1(primobject__type, this, return f2__primobject__type(this_cause, this));

f2ptr f2__primobject__type__set(f2ptr cause, f2ptr this, f2ptr value) {return f2primobject__type__set(this, cause, value);}
def_pcfunk2(primobject__type__set, this, value, return f2__primobject__type__set(this_cause, this, value));

f2ptr f2__primobject__dynamic_slots(f2ptr cause, f2ptr this) {return f2primobject__dynamic_slots(this, cause);}
def_pcfunk1(primobject__dynamic_slots, this, return f2__primobject__dynamic_slots(this_cause, this));

f2ptr f2__primobject__dynamic_slots__set(f2ptr cause, f2ptr this, f2ptr value) {return f2primobject__dynamic_slots__set(this, cause, value);}
def_pcfunk2(primobject__dynamic_slots__set, this, value, return f2__primobject__dynamic_slots__set(this_cause, this, value));

// not thread safe (use appropriately, it would create too much of a slowdown to create a new mutex for every primitive object)
f2ptr f2__primobject__create_new_dynamic_slots_frame(f2ptr cause, f2ptr this) {
  f2ptr dynamic_slots = f2__frame__new(cause);
  f2primobject__dynamic_slots__set(this, cause, dynamic_slots);
  return dynamic_slots;
}

f2ptr f2__primobject__add_dynamic_slot_type_value(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr value) {
  f2ptr dynamic_slots = f2primobject__dynamic_slots(this, cause);
  if (! dynamic_slots) {
    dynamic_slots = f2__primobject__create_new_dynamic_slots_frame(cause, this);
  }
  return f2__frame__add_type_var_value(cause, dynamic_slots, slot_type, slot_name, value);
}
def_pcfunk4(primobject__add_dynamic_slot_type_value, this, slot_type, slot_name, value, return f2__primobject__add_dynamic_slot_type_value(this_cause, this, slot_type, slot_name, value));

f2ptr f2__primobject__dynamic_slot_type_value(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr no_such_slot_value) {
  f2ptr dynamic_slots = f2primobject__dynamic_slots(this, cause);
  if (! dynamic_slots) {
    return no_such_slot_value;
  }
  return f2__frame__lookup_type_var_value(cause, dynamic_slots, slot_type, slot_name, no_such_slot_value);
}
def_pcfunk4(primobject__dynamic_slot_type_value, this, slot_type, slot_name, no_such_slot_value, return f2__primobject__dynamic_slot_type_value(this_cause, this, slot_type, slot_name, no_such_slot_value));

f2ptr f2__primobject__dynamic_slot_type_value__set(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr value, f2ptr no_such_slot_value) {
  f2ptr dynamic_slots = f2primobject__dynamic_slots(this, cause);
  if (! dynamic_slots) {
    return no_such_slot_value;
  }
  return f2__frame__type_var_value__set(cause, dynamic_slots, slot_type, slot_name, value, no_such_slot_value);
}
def_pcfunk5(primobject__dynamic_slot_type_value__set, this, slot_type, slot_name, value, no_such_slot_value, return f2__primobject__dynamic_slot_type_value__set(this_cause, this, slot_type, slot_name, value, no_such_slot_value));

f2ptr f2primobject__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("array"), (u8*)"array"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.type__set__funk);}
  {char* slot_name = "dynamic_slots";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slots__funk);}
  {char* slot_name = "dynamic_slots";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slots__set__funk);}
  {char* slot_name = "add_dynamic_slot_type_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.add_dynamic_slot_type_value__funk);}
  {char* slot_name = "dynamic_slot_type_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__funk);}
  {char* slot_name = "dynamic_slot_type_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__set__funk);}
  return this;
}

// place

defprimobject__static_slot(place__thing, 0);

f2ptr __place__symbol = -1;

f2ptr f2place__new(f2ptr cause, f2ptr p) {
  release__assert(__place__symbol != -1, nil, "f2place__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __place__symbol, 1, nil);
  f2place__thing__set(this, cause, p);
  return this;
}

#ifdef DEBUG
#  define F2__PRIMOBJECT__TYPE_CHECK
#endif // DEBUG

boolean_t raw__place__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__place(x, cause));
}


f2ptr f2__place__new(f2ptr cause, f2ptr x) {return f2place__new(cause, x);}
def_pcfunk1(place__new, x, return f2__place__new(this_cause, x));

f2ptr f2__place__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__place__is_type(cause, x));}
def_pcfunk1(place__is_type, x, return f2__place__is_type(this_cause, x));

f2ptr f2__place__type(f2ptr cause, f2ptr x) {return __place__symbol;}
def_pcfunk1(place__type, x, return f2__place__type(this_cause, x));

f2ptr f2__place__thing(f2ptr cause, f2ptr x) {return f2place__thing(x, cause);}
def_pcfunk1(place__thing, x, return f2__place__thing(this_cause, x));

f2ptr f2__place__thing__set(f2ptr cause, f2ptr x, f2ptr y) {f2place__thing__set(x, cause, y); return nil;}
def_pcfunk2(place__thing__set, x, y, return f2__place__thing__set(this_cause, x, y));

f2ptr f2place__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("primobject"), (u8*)"primobject"), nil));
  {char* slot_name = "is_type"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_place.is_type__funk);}
  {char* slot_name = "type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_place.new__funk);}
  {char* slot_name = "thing";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.primobject_type_place.thing__funk);}
  {char* slot_name = "thing";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.primobject_type_place.thing__set__funk);}
  return this;
}

#define def_primobject_static_slot(name, slot_number, slot_name) \
  defprimobject__static_slot(name##__##slot_name, slot_number); \
   \
  f2ptr f2__##name##__##slot_name(f2ptr cause, f2ptr x) {return f2##name##__##slot_name(x, cause);} \
  def_pcfunk1(name##__##slot_name, x, return f2__##name##__##slot_name(this_cause, x)); \
   \
  f2ptr f2__##name##__##slot_name##__set(f2ptr cause, f2ptr x, f2ptr y) {f2##name##__##slot_name##__set(x, cause, y); return nil;} \
  def_pcfunk2(name##__##slot_name##__set, x, y, return f2__##name##__##slot_name##__set(this_cause, x, y));


#define def_primobject_common(name, new_trace_depth_code, new_f2type_code, add_slots_code) \
  f2ptr __##name##__symbol = -1; \
   \
  new_trace_depth_code; \
   \
  new_f2type_code; \
   \
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr x) { \
    return (raw__primobject__is_type(cause, x) && f2primobject__is__##name(x, cause)); \
  } \
  f2ptr f2__##name##__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__##name##__is_type(cause, x));} \
  def_pcfunk1(name##__is_type, x, return f2__##name##__is_type(this_cause, x)); \
   \
  f2ptr f2__##name##__type(f2ptr cause, f2ptr x) {return __##name##__symbol;} \
  def_pcfunk1(name##__type, x, return f2__##name##__type(this_cause, x)); \
   \
  f2ptr f2##name##__primobject_type__new(f2ptr cause) { \
    f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("primobject"), (u8*)"primobject"), nil)); \
    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), __funk2.globalenv.object_type.primobject.primobject_type_##name.is_type__funk); \
    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    __funk2.globalenv.object_type.primobject.primobject_type_##name.type__funk); \
    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     __funk2.globalenv.object_type.primobject.primobject_type_##name.new__funk); \
    add_slots_code; \
    return this; \
  }

#define def_primobject_add_slot(name, slot_name) \
  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, #slot_name),   __funk2.globalenv.object_type.primobject.primobject_type_##name.slot_name##__funk); \
  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, #slot_name),   __funk2.globalenv.object_type.primobject.primobject_type_##name.slot_name##__set__funk); \

#define def_primobject_1_slot(name, slot_1) \
  def_primobject_static_slot(name, 0, slot_1); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 1, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1) { \
      return f2##name##__new__trace_depth(cause, slot_1, 1); \
    }, \
    def_primobject_add_slot(name, slot_1));

#define def_primobject_2_slot(name, slot_1, slot_2) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 2, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2));

#define def_primobject_3_slot(name, slot_1, slot_2, slot_3) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 3, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3));

#define def_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 4, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4));

#define def_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 5, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5));

#define def_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 6, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6));

#define def_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 7, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7));

#define def_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 8, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8));

#define def_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 9, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9));

#define def_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 10, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10));

#define def_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 11, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11));

#define def_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 12, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12));

#define def_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 13, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13));

#define def_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 14, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13); \
    def_primobject_add_slot(name, slot_14));

#define def_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14); \
  def_primobject_static_slot(name, 14, slot_15); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 15, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth); \
      f2##name##__##slot_15##__set__trace_depth(this, cause, slot_15, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13); \
    def_primobject_add_slot(name, slot_14); \
    def_primobject_add_slot(name, slot_15));

#define def_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14); \
  def_primobject_static_slot(name, 14, slot_15); \
  def_primobject_static_slot(name, 15, slot_16); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 16, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth); \
      f2##name##__##slot_15##__set__trace_depth(this, cause, slot_15, trace_depth); \
      f2##name##__##slot_16##__set__trace_depth(this, cause, slot_16, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13); \
    def_primobject_add_slot(name, slot_14); \
    def_primobject_add_slot(name, slot_15); \
    def_primobject_add_slot(name, slot_16));

#define def_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14); \
  def_primobject_static_slot(name, 14, slot_15); \
  def_primobject_static_slot(name, 15, slot_16); \
  def_primobject_static_slot(name, 16, slot_17); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 17, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth); \
      f2##name##__##slot_15##__set__trace_depth(this, cause, slot_15, trace_depth); \
      f2##name##__##slot_16##__set__trace_depth(this, cause, slot_16, trace_depth); \
      f2##name##__##slot_17##__set__trace_depth(this, cause, slot_17, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13); \
    def_primobject_add_slot(name, slot_14); \
    def_primobject_add_slot(name, slot_15); \
    def_primobject_add_slot(name, slot_16); \
    def_primobject_add_slot(name, slot_17));

#define def_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14); \
  def_primobject_static_slot(name, 14, slot_15); \
  def_primobject_static_slot(name, 15, slot_16); \
  def_primobject_static_slot(name, 16, slot_17); \
  def_primobject_static_slot(name, 17, slot_18); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 18, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth); \
      f2##name##__##slot_15##__set__trace_depth(this, cause, slot_15, trace_depth); \
      f2##name##__##slot_16##__set__trace_depth(this, cause, slot_16, trace_depth); \
      f2##name##__##slot_17##__set__trace_depth(this, cause, slot_17, trace_depth); \
      f2##name##__##slot_18##__set__trace_depth(this, cause, slot_18, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13); \
    def_primobject_add_slot(name, slot_14); \
    def_primobject_add_slot(name, slot_15); \
    def_primobject_add_slot(name, slot_16); \
    def_primobject_add_slot(name, slot_17); \
    def_primobject_add_slot(name, slot_18));

#define def_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_primobject_static_slot(name, 0, slot_1); \
  def_primobject_static_slot(name, 1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14); \
  def_primobject_static_slot(name, 14, slot_15); \
  def_primobject_static_slot(name, 15, slot_16); \
  def_primobject_static_slot(name, 16, slot_17); \
  def_primobject_static_slot(name, 17, slot_18); \
  def_primobject_static_slot(name, 18, slot_19); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 19, nil, trace_depth); \
      f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth); \
      f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth); \
      f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth); \
      f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth); \
      f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth); \
      f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth); \
      f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth); \
      f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth); \
      f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth); \
      f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth); \
      f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth); \
      f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth); \
      f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth); \
      f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth); \
      f2##name##__##slot_15##__set__trace_depth(this, cause, slot_15, trace_depth); \
      f2##name##__##slot_16##__set__trace_depth(this, cause, slot_16, trace_depth); \
      f2##name##__##slot_17##__set__trace_depth(this, cause, slot_17, trace_depth); \
      f2##name##__##slot_18##__set__trace_depth(this, cause, slot_18, trace_depth); \
      f2##name##__##slot_18##__set__trace_depth(this, cause, slot_19, trace_depth); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, 1); \
    }, \
    def_primobject_add_slot(name, slot_1); \
    def_primobject_add_slot(name, slot_2); \
    def_primobject_add_slot(name, slot_3); \
    def_primobject_add_slot(name, slot_4); \
    def_primobject_add_slot(name, slot_5); \
    def_primobject_add_slot(name, slot_6); \
    def_primobject_add_slot(name, slot_7); \
    def_primobject_add_slot(name, slot_8); \
    def_primobject_add_slot(name, slot_9); \
    def_primobject_add_slot(name, slot_10); \
    def_primobject_add_slot(name, slot_11); \
    def_primobject_add_slot(name, slot_12); \
    def_primobject_add_slot(name, slot_13); \
    def_primobject_add_slot(name, slot_14); \
    def_primobject_add_slot(name, slot_15); \
    def_primobject_add_slot(name, slot_16); \
    def_primobject_add_slot(name, slot_17); \
    def_primobject_add_slot(name, slot_18); \
    def_primobject_add_slot(name, slot_19));


// compound_object

def_primobject_3_slot(compound_object, compound_object_type, frame, part_frame);

f2ptr f2__compound_object__new(f2ptr cause, f2ptr compound_object_type) {
  return f2compound_object__new(cause, compound_object_type, f2__frame__new(cause), f2__frame__new(cause));
}
def_pcfunk1(compound_object__new, compound_object_type, return f2__compound_object__new(this_cause, compound_object_type));



// cons

def_primobject_2_slot(cons, car, cdr);

f2ptr f2__cons__new(f2ptr cause, f2ptr x, f2ptr y) {return f2cons__new(cause, x, y);}
def_pcfunk2(cons__new, x, y, return f2__cons__new(this_cause, x, y));



// doublelink

def_primobject_3_slot(doublelink, prev, next, value);

f2ptr f2__doublelink__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {return f2doublelink__new(cause, x, y, z);}
def_pcfunk3(doublelink__new, x, y, z, return f2__doublelink__new(this_cause, x, y, z));


// imagination_link

def_primobject_5_slot(imagination_link, next, name, value, trace, imagination_frame);

f2ptr f2__imagination_link__new(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame) {return f2imagination_link__new(cause, next, name, value, trace, imagination_frame);}
def_pcfunk5(imagination_link__new, next, name, value, trace, imagination_frame, return f2__imagination_link__new(this_cause, next, name, value, trace, imagination_frame));

f2ptr raw__imagination_frame__new_with_added_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth) {
  f2ptr trace             = nil;
  f2ptr imagination_frame = nil;
  return f2imagination_link__new__trace_depth(cause, this, name, value, trace, imagination_frame, trace_depth - 1);
}

void raw__imagination_link__add_new_imagination_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth) {
  f2ptr imagination_frame     = f2imagination_link__imagination_frame(this, cause);
  f2ptr new_imagination_frame = raw__imagination_frame__new_with_added_slot__trace_depth(cause, imagination_frame, name, value, trace_depth - 1);
  f2imagination_link__imagination_frame__set__trace_depth(this, cause, new_imagination_frame, trace_depth - 1);
}

f2ptr f2__imagination_frame__get_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, int trace_depth) {
  f2ptr slot_iter = this;
  while (slot_iter) {
    f2ptr slot_name = f2imagination_link__name__trace_depth(slot_iter, cause, trace_depth);
    if (raw__symbol__eq(cause, name, slot_name)) {
      return slot_iter;
    }
    slot_iter = f2imagination_link__next__trace_depth(slot_iter, cause, trace_depth);
  }
  return nil;
}

f2ptr f2__imagination_frame__get_slot(f2ptr cause, f2ptr this, f2ptr name) {
  return f2__imagination_frame__get_slot__trace_depth(cause, this, name, 1);
}

f2ptr f2__imagination_link__get_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, int trace_depth) {
  f2ptr imagination_frame = f2imagination_link__imagination_frame__trace_depth(this, cause, trace_depth);
  return f2__imagination_frame__get_slot__trace_depth(cause, imagination_frame, name, trace_depth);
}

f2ptr f2__imagination_link__get_slot(f2ptr cause, f2ptr this, f2ptr name) {
  return f2__imagination_link__get_slot__trace_depth(cause, this, name, 1);
}

f2ptr f2__imagination_link__get_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value, u64 trace_depth) {
  f2ptr imagination_link_iter = this;
  f2ptr name_iter             = name_stack;
  while (name_iter) {
    f2ptr name = f2cons__car__trace_depth(name_iter, cause, trace_depth);
    f2ptr slot = f2__imagination_link__get_slot__trace_depth(cause, imagination_link_iter, name, trace_depth);
    if (! slot) {
      return doesnt_exist_value;
    }
    imagination_link_iter = slot;
    name_iter = f2cons__cdr(name_iter, cause);
  }
  return f2imagination_link__value__trace_depth(imagination_link_iter, cause, trace_depth);
}

f2ptr f2__imagination_link__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value) {
  return f2__imagination_link__get_value_from_name_stack__trace_depth(cause, this, name_stack, doesnt_exist_value, 1);
}

f2ptr f2__imagination_frame__get_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value, int trace_depth) {
  if (name_stack) {
    f2ptr name = f2cons__car(name_stack, cause);
    f2ptr slot = f2__imagination_frame__get_slot__trace_depth(cause, this, name, trace_depth);
    if (! slot) {
      return doesnt_exist_value;
    }
    return f2__imagination_link__get_value_from_name_stack__trace_depth(cause, slot, f2cons__cdr(name_stack, cause), doesnt_exist_value, trace_depth);
  }
  return doesnt_exist_value;
}

f2ptr f2__imagination_frame__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value) {
  return f2__imagination_frame__get_value_from_name_stack__trace_depth(cause, this, name_stack, doesnt_exist_value, 1);
}

void f2__imagination_link__set_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr value, int trace_depth) {
  f2ptr imagination_link_iter = this;
  f2ptr name_iter             = name_stack;
  while (name_iter) {
    f2ptr name = f2cons__car(name_iter, cause);
    f2ptr next = f2cons__cdr(name_iter, cause);
    f2ptr slot = f2__imagination_link__get_slot(cause, imagination_link_iter, name);
    if (! slot) {
      raw__imagination_link__add_new_imagination_slot__trace_depth(cause, imagination_link_iter, name, next ? f2imagination_link__value(imagination_link_iter, cause) : value, trace_depth - 1);
      slot = f2__imagination_link__get_slot(cause, imagination_link_iter, name);
      release__assert(slot != nil, cause, "f2__imagination_link__set_value_from_name_stack: !(slot != nil)");
    }
    imagination_link_iter = slot;
    name_iter = next;
  }
}


// cfunk

def_primobject_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation);

f2ptr f2__cfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(cfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__cfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));



// metrocfunk

def_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);

f2ptr f2__metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2metrocfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(metrocfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__metrocfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));



// funk

def_primobject_9_slot(funk, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);

f2ptr f2__funk__new(f2ptr cause) {
  return f2funk__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(funk__new, return f2__funk__new(this_cause));


// metro

def_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);

f2ptr f2__metro__new(f2ptr cause) {
  return f2metro__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(metro__new, return f2__metro__new(this_cause));


// exception

def_primobject_2_slot(exception, tag, value);

f2ptr f2__exception__new(f2ptr cause, f2ptr tag, f2ptr value) {return f2exception__new(cause, tag, value);}
def_pcfunk2(exception__new, tag, value, return f2__exception__new(this_cause, tag, value));



// bytecode

def_primobject_4_slot(bytecode, command, arg0, arg1, arg2);

f2ptr f2__bytecode__new(f2ptr cause, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2) {return f2bytecode__new(cause, command, arg0, arg1, arg2);}
def_pcfunk4(bytecode__new, command, arg0, arg1, arg2, return f2__bytecode__new(this_cause, command, arg0, arg1, arg2));


// fiber

def_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);

f2ptr f2__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args) {
  f2ptr program_counter    = nil;
  f2ptr stack              = nil;
  f2ptr iter               = nil;
  f2ptr env                = parent_env;
  f2ptr args               = nil;
  f2ptr return_reg         = nil;
  f2ptr value              = nil;
  f2ptr trace              = nil;
  f2ptr critics            = nil;
  f2ptr cause_reg          = cause;
  f2ptr keep_undead        = __funk2.globalenv.true__symbol;
  f2ptr is_zombie          = nil;
  f2ptr execute_mutex      = f2mutex__new(cause);
  f2ptr paused             = nil;
  f2ptr last_executed_time = nil;
  f2ptr sleep_until_time   = nil;
  f2ptr larva_args         = nil;
  f2ptr new_fiber = f2fiber__new(cause, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);
  f2fiber__keep_undead__set(new_fiber, cause, __funk2.globalenv.true__symbol);
  f2fiber__funk(new_fiber, cause, cfunkable, cfunkable_args);
  
  //f2cause__fibers__set(cause, cause, f2cons__new(cause, new_fiber, f2cause__fibers(cause, cause)));
  
  return new_fiber;
}

def_pcfunk4(fiber__new, parent_fiber, parent_env, cfunkable, cfunkable_args, return f2__fiber__new(this_cause, parent_fiber, parent_env, cfunkable, cfunkable_args));

f2ptr f2__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time) {
  if (! raw__time__is_type(cause, until_time)) {
    return f2larva__new(cause, 1);
  }
  f2fiber__sleep_until_time__set(this, cause, until_time);
  return nil;
}
def_pcfunk2(fiber__do_sleep_until_time, this, until_time, return f2__fiber__do_sleep_until_time(this_cause, this, until_time));

f2ptr f2__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, f2ptr nanoseconds) {
  if (! raw__integer__is_type(cause, nanoseconds)) {
    return f2larva__new(cause, 1);
  }
  s64 nanoseconds__i = f2integer__i(nanoseconds, cause);
  return f2__fiber__do_sleep_until_time(cause, this, f2time__new(cause, f2integer__new(cause, raw__nanoseconds_since_1970() + nanoseconds__i)));
}
def_pcfunk2(fiber__sleep_for_nanoseconds, this, nanoseconds, return f2__fiber__sleep_for_nanoseconds(this_cause, this, nanoseconds));


// processor

def_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);

f2ptr f2__processor__new(f2ptr cause) {
  return f2processor__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(processor__new, return f2__processor__new(this_cause));

// scheduler

def_primobject_5_slot(scheduler, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);

f2ptr f2__scheduler__new(f2ptr cause, f2ptr processors, f2ptr event_subscribers_mutex, f2ptr event_subscribers, f2ptr event_buffer_mutex, f2ptr event_buffer) {return f2scheduler__new(cause, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);}
def_pcfunk5(scheduler__new, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer, return f2__scheduler__new(this_cause, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer));


// event_subscriber

def_primobject_5_slot(event_subscriber, event_types, fiber, funkable, event_buffer, event_buffer_mutex);

f2ptr f2__event_subscriber__new(f2ptr cause, f2ptr event_types, f2ptr fiber, f2ptr funkable, f2ptr event_buffer, f2ptr event_buffer_mutex) {return f2event_subscriber__new(cause, event_types, fiber, funkable, event_buffer, event_buffer_mutex);}
def_pcfunk5(event_subscriber__new, event_types, fiber, funkable, event_buffer, event_buffer_mutex, return f2__event_subscriber__new(this_cause, event_types, fiber, funkable, event_buffer, event_buffer_mutex));


// cause

def_primobject_13_slot(cause, fibers_mutex, fibers, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_stack, event_buffer_first, event_buffer_last, current_events_mutex, current_events);

f2ptr f2__cause__define(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {
  return f2__cause__define_type_var(cause, this, __funk2.primobject__frame.variable__symbol, var, value);
}
def_pcfunk3(cause__define, this, var, value, return f2__cause__define(this_cause, this, var, value));

f2ptr f2__cause__define__funk(f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value) {
  return f2__cause__define_type_var(cause, this, __funk2.primobject__frame.funk_variable__symbol, funkvar, value);
}
def_pcfunk3(cause__define__funk, this, funkvar, value, return f2__cause__define__funk(this_cause, this, funkvar, value));


f2ptr f2__cause__new(f2ptr cause, f2ptr allocate_traced_arrays, f2ptr bytecode_tracing_on, f2ptr memory_tracing_on, f2ptr subscribers, f2ptr imagination_name, f2ptr event_buffer_first, f2ptr event_buffer_last, f2ptr current_events) {
  f2ptr fibers_mutex        = f2mutex__new(cause);
  f2ptr fibers              = nil;
  f2ptr frame                = f2__frame__new(cause);
  f2ptr subscribers_mutex    = f2mutex__new(cause);
  f2ptr current_events_mutex = f2mutex__new(cause);
  return f2cause__new(cause, fibers_mutex, fibers, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_name, event_buffer_first, event_buffer_last, current_events_mutex, current_events);
}
def_pcfunk0(cause__new, return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fibers_mutex = f2cause__fibers_mutex(this, cause);
  f2mutex__lock(fibers_mutex, cause);
  f2cause__fibers__set(this, cause, f2cons__new(cause, fiber, f2cause__fibers(this, cause)));
  f2mutex__unlock(fibers_mutex, cause);
  return nil;
}

f2ptr f2__cause__remove_fiber(f2ptr cause, f2ptr this, f2ptr fiber) {
  f2ptr fibers_mutex = f2cause__fibers_mutex(this, cause);
  f2mutex__lock(fibers_mutex, cause);
  f2ptr prev = nil;
  f2ptr iter = f2cause__fibers(this, cause);
  while (iter) {
    f2ptr next = f2cons__cdr(iter, cause);
    f2ptr iter_fiber = f2cons__car(iter, cause);
    if (iter_fiber == fiber) {
      if (prev) {
	f2cons__cdr__set(prev, cause, next);
      } else {
	f2cause__fibers__set(this, cause, next);
      }
      break;
    }
    prev = iter;
    iter = next;
  }
  f2mutex__unlock(fibers_mutex, cause);
  if (! iter) {
    printf("\nf2__cause__remove_fiber warning: could not find fiber to remove."); fflush(stdout);
  }
  return nil;
}

f2ptr f2__cause__new_with_default_properties(f2ptr cause) {
  return f2__cause__new(cause, cause__allocate_traced_arrays__default_value, nil, nil, nil, nil, nil, nil, nil);
}

f2ptr f2__cause__new_default_with_memory_tracing_on(f2ptr cause) {
  f2ptr new_cause = f2__cause__new_with_default_properties(cause);
  f2cause__memory_tracing_on__set(new_cause, cause, __funk2.globalenv.true__symbol);
  return new_cause;
}

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause) {
  f2ptr allocate_traced_arrays = nil;
  f2ptr bytecode_tracing_on    = nil;
  f2ptr memory_tracing_on      = nil;
  f2ptr subscribers            = nil;
  f2ptr imagination_stack      = nil;
  if (cause) {
    allocate_traced_arrays = f2cause__allocate_traced_arrays(cause, cause);
    bytecode_tracing_on    = f2cause__bytecode_tracing_on(cause, cause);
    memory_tracing_on      = f2cause__memory_tracing_on(cause, cause);
    subscribers            = f2cause__subscribers(cause, cause);
    imagination_stack      = f2cause__imagination_stack(cause, cause);
  }
  return f2__cause__new(cause,
			allocate_traced_arrays,
			bytecode_tracing_on,
			memory_tracing_on,
			subscribers,
			imagination_stack,
			nil,  // event_buffer_first
			nil,  // event_buffer_last
			nil); // current_events
}

f2ptr f2__cause__new_imaginary(f2ptr cause, f2ptr imagination_name) {
  f2ptr new_cause = f2__cause__new_with_inherited_properties(cause);
  f2cause__imagination_stack__set(new_cause, cause, f2cons__new(cause, imagination_name, f2cause__imagination_stack(cause, new_cause)));
  return new_cause;
}

void raw__cause__event_buffer__add(f2ptr cause, f2ptr event) {
  f2ptr event_buffer_last     = f2cause__event_buffer_last(cause, cause);
  f2ptr new_event_buffer_node = f2doublelink__new(cause, event_buffer_last, nil, event);
  if (event_buffer_last == nil) {
    f2cause__event_buffer_first__set(cause, cause, new_event_buffer_node);
  } else {
    f2doublelink__next__set(event_buffer_last, cause, new_event_buffer_node);
  }
  f2cause__event_buffer_last__set(cause, cause, new_event_buffer_node);
}

f2ptr f2__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var) {
  f2ptr     cause_iter   = this;
  f2ptr     value        = nil;
  boolean_t keep_looping;
  do {
    keep_looping = boolean__false;
    f2ptr cause_frame = f2cause__frame(cause_iter, cause);
    if (cause_frame) {
      value = f2__frame__lookup_type_var_value(cause, cause_frame, type, var, __funk2.primobject__frame.type_variable_not_defined__larva);
    }
    if ((! cause_frame) || raw__larva__is_type(cause, value)) {
      cause_iter = f2__ptype__cause(cause, cause_iter);
      if (cause_iter) {
	keep_looping = boolean__true;
      } else {
	value = f2larva__new(cause, 23);
      }
    }
  } while (keep_looping);
  return value;
}

// transframe

def_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);

f2ptr f2__transframe__new(f2ptr cause, f2ptr nanoseconds_since_1970, f2ptr symbol_old_news) {return f2transframe__new(cause, nanoseconds_since_1970, symbol_old_news);}
def_pcfunk2(transframe__new, nanoseconds_since_1970, symbol_old_news, return f2__transframe__new(this_cause, nanoseconds_since_1970, symbol_old_news));


// bug

def_primobject_1_slot(bug, bug_type);

f2ptr f2__bug__new(f2ptr cause, f2ptr type) {return f2bug__new(cause, type);}
def_pcfunk1(bug__new, type, return f2__bug__new(this_cause, type));


// time

def_primobject_1_slot(time, nanoseconds_since_1970);

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970) {return f2time__new(cause, nanoseconds_since_1970);}
def_pcfunk1(time__new, nanoseconds_since_1970, return f2__time__new(this_cause, nanoseconds_since_1970));

u64 raw__time__years(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.years;
}

f2ptr f2__time__years(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__years(cause, this));}
def_pcfunk1(time__years, this, return f2__time__years(this_cause, this));

u64 raw__time__months(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.months;
}

f2ptr f2__time__months(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__months(cause, this));}
def_pcfunk1(time__months, this, return f2__time__months(this_cause, this));

u64 raw__time__days(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.days;
}

f2ptr f2__time__days(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__days(cause, this));}
def_pcfunk1(time__days, this, return f2__time__days(this_cause, this));

u64 raw__time__hours(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.hours;
}

f2ptr f2__time__hours(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__hours(cause, this));}
def_pcfunk1(time__hours, this, return f2__time__hours(this_cause, this));

u64 raw__time__minutes(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.minutes;
}

f2ptr f2__time__minutes(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__minutes(cause, this));}
def_pcfunk1(time__minutes, this, return f2__time__minutes(this_cause, this));

u64 raw__time__seconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.seconds;
}

f2ptr f2__time__seconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__seconds(cause, this));}
def_pcfunk1(time__seconds, this, return f2__time__seconds(this_cause, this));

u64 raw__time__nanoseconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.nanoseconds;
}

f2ptr f2__time__nanoseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__nanoseconds(cause, this));}
def_pcfunk1(time__nanoseconds, this, return f2__time__nanoseconds(this_cause, this));

// size_2d

def_primobject_2_slot(size_2d, x, y);

f2ptr f2__size_2d__new(f2ptr cause, f2ptr x, f2ptr y) {return f2size_2d__new(cause, x, y);}
def_pcfunk2(size_2d__new, x, y, return f2__size_2d__new(this_cause, x, y));


// event

def_primobject_4_slot(event, node_id, event_id, event_type, data);

f2ptr f2__event__new(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data) {return f2event__new(cause, node_id, event_id, type, data);}
def_pcfunk4(event__new, node_id, event_id, type, data, return f2__event__new(this_cause, node_id, event_id, type, data));


// larva_event




// bytecode_event

def_primobject_2_slot(bytecode_event, bytecode, context);

f2ptr f2__bytecode_event__new(f2ptr cause, f2ptr bytecode, f2ptr context) {return f2bytecode_event__new(cause, bytecode, context);}
def_pcfunk2(bytecode_event__new, bytecode, context, return f2__bytecode_event__new(this_cause, bytecode, context));


// **

void f2__primobjects__reinitialize_globalvars() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobjects", "", &f2__primobjects__reinitialize_globalvars);
  
  f2ptr cause = initial_cause();
  
  __compound_object__symbol  = new__symbol(cause, "compound_object");
  __primobject__symbol       = new__symbol(cause, "primobject");
  __place__symbol            = new__symbol(cause, "place");
  __cons__symbol             = new__symbol(cause, "cons");
  __doublelink__symbol       = new__symbol(cause, "doublelink");
  __imagination_link__symbol = new__symbol(cause, "imagination_link");
  __cfunk__symbol            = new__symbol(cause, "cfunk");
  __metrocfunk__symbol       = new__symbol(cause, "metrocfunk");
  __funk__symbol             = new__symbol(cause, "funk");
  __metro__symbol            = new__symbol(cause, "metro");
  __exception__symbol        = new__symbol(cause, "exception");
  __bytecode__symbol         = new__symbol(cause, "bytecode");
  __fiber__symbol            = new__symbol(cause, "fiber");
  __processor__symbol        = new__symbol(cause, "processor");
  __scheduler__symbol        = new__symbol(cause, "scheduler");
  __event_subscriber__symbol = new__symbol(cause, "event_subscriber");
  __cause__symbol            = new__symbol(cause, "cause");
  __transframe__symbol       = new__symbol(cause, "transframe");
  __bug__symbol              = new__symbol(cause, "bug");
  __time__symbol             = new__symbol(cause, "time");
  __size_2d__symbol          = new__symbol(cause, "size_2d");
  __event__symbol            = new__symbol(cause, "event");
  __bytecode_event__symbol   = new__symbol(cause, "bytecode_event");
}


#define initialize_primobject_funk(name, funk_name) \
  {char* symbol_str = #funk_name; __funk2.globalenv.object_type.primobject.primobject_type_##name.funk_name##__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);} \
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(name##__##funk_name, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_##name.funk_name##__funk = never_gc(cfunk);}

#define initialize_primobject_common(name) \
  initialize_primobject_funk(name, is_type); \
  initialize_primobject_funk(name, type); \
  initialize_primobject_funk(name, new);

#define initialize_primobject_slot(name, slot_name) \
  initialize_primobject_funk(name, slot_name); \
  initialize_primobject_funk(name, slot_name##__set);

#define initialize_primobject_0_slot(name) \
  initialize_primobject_common(name);

#define initialize_primobject_1_slot(name, slot_1) \
  initialize_primobject_0_slot(name); \
  initialize_primobject_slot(name, slot_1);

#define initialize_primobject_2_slot(name, slot_1, slot_2) \
  initialize_primobject_1_slot(name, slot_1); \
  initialize_primobject_slot(name, slot_2);

#define initialize_primobject_3_slot(name, slot_1, slot_2, slot_3) \
  initialize_primobject_2_slot(name, slot_1, slot_2); \
  initialize_primobject_slot(name, slot_3);

#define initialize_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  initialize_primobject_3_slot(name, slot_1, slot_2, slot_3); \
  initialize_primobject_slot(name, slot_4);

#define initialize_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  initialize_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  initialize_primobject_slot(name, slot_5);

#define initialize_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  initialize_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  initialize_primobject_slot(name, slot_6);

#define initialize_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  initialize_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  initialize_primobject_slot(name, slot_7);

#define initialize_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  initialize_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  initialize_primobject_slot(name, slot_8);

#define initialize_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  initialize_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  initialize_primobject_slot(name, slot_9);

#define initialize_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  initialize_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  initialize_primobject_slot(name, slot_10);

#define initialize_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  initialize_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  initialize_primobject_slot(name, slot_11);

#define initialize_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  initialize_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  initialize_primobject_slot(name, slot_12);

#define initialize_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  initialize_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  initialize_primobject_slot(name, slot_13);

#define initialize_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  initialize_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  initialize_primobject_slot(name, slot_14);

#define initialize_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  initialize_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  initialize_primobject_slot(name, slot_15);

#define initialize_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  initialize_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  initialize_primobject_slot(name, slot_16);

#define initialize_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  initialize_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  initialize_primobject_slot(name, slot_17);

#define initialize_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  initialize_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  initialize_primobject_slot(name, slot_18);

#define initialize_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  initialize_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  initialize_primobject_slot(name, slot_19);

void f2__primobjects__initialize() {
  f2__primobjects__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // primobject
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.type__funk = never_gc(cfunk);}
  {char* symbol_str = "type-set"; __funk2.globalenv.object_type.primobject.type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(primobject__type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.type__set__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slots"; __funk2.globalenv.object_type.primobject.dynamic_slots__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__dynamic_slots, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slots__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slots-set"; __funk2.globalenv.object_type.primobject.dynamic_slots__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(primobject__dynamic_slots__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slots__set__funk = never_gc(cfunk);}
  {char* symbol_str = "add_dynamic_slot_type_value"; __funk2.globalenv.object_type.primobject.add_dynamic_slot_type_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(primobject__add_dynamic_slot_type_value, this, slot_type, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.add_dynamic_slot_type_value__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slot_type_value"; __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(primobject__dynamic_slot_type_value, this, slot_type, slot_name, no_such_slot_value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slot_type_value-set"; __funk2.globalenv.object_type.primobject.dynamic_slots__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(primobject__dynamic_slot_type_value__set, this, slot_type, slot_name, value, no_such_slot_value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__set__funk = never_gc(cfunk);}
  
  // compound_object 
  
  initialize_primobject_3_slot(compound_object, compound_object_type, frame, part_frame);
  
  // place
  
  initialize_primobject_1_slot(place, thing);

  // cons 
  
  initialize_primobject_2_slot(cons, car, cdr);

  // doublelink
  
  initialize_primobject_3_slot(doublelink, prev, next, value);

  // imagination_link
  
  initialize_primobject_5_slot(imagination_link, next, name, value, trace, imagination_frame);
  
  // cfunk
  
  initialize_primobject_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation);
  
  // metrocfunk
  
  initialize_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);
  
  // funk
  
  initialize_primobject_9_slot(funk, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);
  
  // metro
  
  initialize_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);
  
  // exception
  
  initialize_primobject_2_slot(exception, tag, value);
  
  // bytecode
  
  initialize_primobject_4_slot(bytecode, command, arg0, arg1, arg2);
  
  // fiber
  
  initialize_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);
  
  // processor
  
  initialize_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);
  
  // scheduler
  
  initialize_primobject_5_slot(scheduler, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);
  
  // event_subscriber
  
  initialize_primobject_5_slot(event_subscriber, event_type, fiber, funkable, event_buffer, event_buffer_mutex);
  
  // cause
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_cause.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_cause.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_cause.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(cause__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.new__funk = never_gc(cfunk);}
  {char* symbol_str = "fibers_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__fibers_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "fibers_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__fibers_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "fibers"; __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__fibers, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers__funk = never_gc(cfunk);}
  {char* symbol_str = "fibers-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__fibers__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.fibers__set__funk = never_gc(cfunk);}
  {char* symbol_str = "frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__frame, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__funk = never_gc(cfunk);}
  {char* symbol_str = "frame-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__frame__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__set__funk = never_gc(cfunk);}
  {char* symbol_str = "allocate_traced_arrays"; __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__allocate_traced_arrays, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__funk = never_gc(cfunk);}
  {char* symbol_str = "allocate_traced_arrays-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__allocate_traced_arrays__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__set__funk = never_gc(cfunk);}
  {char* symbol_str = "bytecode_tracing_on"; __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__bytecode_tracing_on, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__funk = never_gc(cfunk);}
  {char* symbol_str = "bytecode_tracing_on-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__bytecode_tracing_on__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__set__funk = never_gc(cfunk);}
  {char* symbol_str = "memory_tracing_on"; __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__memory_tracing_on, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__funk = never_gc(cfunk);}
  {char* symbol_str = "memory_tracing_on-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__memory_tracing_on__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__set__funk = never_gc(cfunk);}
  {char* symbol_str = "subscribers_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__subscribers_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "subscribers_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__subscribers_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "subscribers"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__subscribers, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__funk = never_gc(cfunk);}
  {char* symbol_str = "subscribers-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__subscribers__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__set__funk = never_gc(cfunk);}
  {char* symbol_str = "imagination_stack"; __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__imagination_stack, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__funk = never_gc(cfunk);}
  {char* symbol_str = "imagination_stack-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__imagination_stack__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__set__funk = never_gc(cfunk);}
  {char* symbol_str = "event_buffer_first"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__event_buffer_first, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__funk = never_gc(cfunk);}
  {char* symbol_str = "event_buffer_first-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__event_buffer_first__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__set__funk = never_gc(cfunk);}
  {char* symbol_str = "event_buffer_last"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__event_buffer_last, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__funk = never_gc(cfunk);}
  {char* symbol_str = "event_buffer_last-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__event_buffer_last__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__set__funk = never_gc(cfunk);}
  {char* symbol_str = "current_events_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__current_events_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__funk = never_gc(cfunk);}
  {char* symbol_str = "current_events_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__current_events_mutex, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__set__funk = never_gc(cfunk);}
  {char* symbol_str = "current_events"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__current_events, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__funk = never_gc(cfunk);}
  {char* symbol_str = "current_events-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__current_events__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__set__funk = never_gc(cfunk);}
  {char* symbol_str = "define"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__define, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk = never_gc(cfunk);}
  {char* symbol_str = "define-funk"; __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__define__funk, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.define__funk__funk = never_gc(cfunk);}
  
  // transframe
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(transframe__new, nanoseconds_since_1970, symbol_old_news, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.new__funk = never_gc(cfunk);}
  {char* symbol_str = "nanoseconds_since_1970"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__nanoseconds_since_1970, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__funk = never_gc(cfunk);}
  {char* symbol_str = "nanoseconds_since_1970-set"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(transframe__nanoseconds_since_1970__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__set__funk = never_gc(cfunk);}
  {char* symbol_str = "symbol_old_news"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__symbol_old_news, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__funk = never_gc(cfunk);}
  {char* symbol_str = "symbol_old_news-set"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(transframe__symbol_old_news__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__set__funk = never_gc(cfunk);}
  
  // bug
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_bug.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_bug.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_bug.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__new, type, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.new__funk = never_gc(cfunk);}
  {char* symbol_str = "bug_type"; __funk2.globalenv.object_type.primobject.primobject_type_bug.bug_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__bug_type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.bug_type__funk = never_gc(cfunk);}
  {char* symbol_str = "bug_type-set"; __funk2.globalenv.object_type.primobject.primobject_type_bug.bug_type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bug__bug_type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.bug_type__set__funk = never_gc(cfunk);}
  
  // time
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_time.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_time.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_time.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__new, type, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.new__funk = never_gc(cfunk);}
  {char* symbol_str = "nanoseconds_since_1970"; __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__nanoseconds_since_1970, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__funk = never_gc(cfunk);}
  {char* symbol_str = "nanoseconds_since_1970-set"; __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(time__nanoseconds_since_1970__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__set__funk = never_gc(cfunk);}
  {char* symbol_str = "years"; __funk2.globalenv.object_type.primobject.primobject_type_time.years__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__years, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.years__funk = never_gc(cfunk);}
  {char* symbol_str = "months"; __funk2.globalenv.object_type.primobject.primobject_type_time.months__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__months, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.months__funk = never_gc(cfunk);}
  {char* symbol_str = "days"; __funk2.globalenv.object_type.primobject.primobject_type_time.days__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__days, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.days__funk = never_gc(cfunk);}
  {char* symbol_str = "hours"; __funk2.globalenv.object_type.primobject.primobject_type_time.hours__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__hours, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.hours__funk = never_gc(cfunk);}
  {char* symbol_str = "minutes"; __funk2.globalenv.object_type.primobject.primobject_type_time.minutes__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__minutes, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.minutes__funk = never_gc(cfunk);}
  {char* symbol_str = "seconds"; __funk2.globalenv.object_type.primobject.primobject_type_time.seconds__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__seconds, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.seconds__funk = never_gc(cfunk);}
  {char* symbol_str = "nanoseconds"; __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__nanoseconds, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds__funk = never_gc(cfunk);}
  
  // size_2d
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(size_2d__new, x, y, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.new__funk = never_gc(cfunk);}
  {char* symbol_str = "x"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__x, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__funk = never_gc(cfunk);}
  {char* symbol_str = "x-set"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(size_2d__x__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__set__funk = never_gc(cfunk);}
  {char* symbol_str = "y"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__y, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__funk = never_gc(cfunk);}
  {char* symbol_str = "y-set"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(size_2d__y__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__set__funk = never_gc(cfunk);}
  
  // event
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_event.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_event.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_event.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(event__new, node_id, event_id, type, data, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.new__funk = never_gc(cfunk);}
  {char* symbol_str = "node_id"; __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__node_id, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__funk = never_gc(cfunk);}
  {char* symbol_str = "node_id-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__node_id__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__set__funk = never_gc(cfunk);}
  {char* symbol_str = "event_id"; __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__event_id, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__funk = never_gc(cfunk);}
  {char* symbol_str = "event_id-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__event_id__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__set__funk = never_gc(cfunk);}
  {char* symbol_str = "event_type"; __funk2.globalenv.object_type.primobject.primobject_type_event.event_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__event_type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.event_type__funk = never_gc(cfunk);}
  {char* symbol_str = "event_type-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.event_type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__event_type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.event_type__set__funk = never_gc(cfunk);}
  {char* symbol_str = "data"; __funk2.globalenv.object_type.primobject.primobject_type_event.data__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__data, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.data__funk = never_gc(cfunk);}
  {char* symbol_str = "data-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.data__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__data__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.data__set__funk = never_gc(cfunk);}
  
  // bytecode_event
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode_event__new, bytecode, context, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.new__funk = never_gc(cfunk);}
  {char* symbol_str = "bytecode"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__bytecode, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__funk = never_gc(cfunk);}
  {char* symbol_str = "bytecode-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode_event__bytecode__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__set__funk = never_gc(cfunk);}
  {char* symbol_str = "context"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__context, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__funk = never_gc(cfunk);}
  {char* symbol_str = "context-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode_event__context__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__set__funk = never_gc(cfunk);}
}


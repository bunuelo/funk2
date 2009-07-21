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
  return (raw__primobject__is_type(cause, x) && f2primobject__is_place(x, cause));
}


f2ptr f2__place__new(f2ptr cause, f2ptr x) {return f2place__new(cause, x);}
def_pcfunk1(place__new, x, return f2__place__new(this_cause, x));

f2ptr f2__place__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__place__is_type(cause, x));}
def_pcfunk1(place__is_type, x, return f2__place__is_type(this_cause, x));

f2ptr f2__place__thing(f2ptr cause, f2ptr x) {return f2place__thing(x, cause);}
def_pcfunk1(place__thing, x, return f2__place__thing(this_cause, x));

f2ptr f2__place__thing__set(f2ptr cause, f2ptr x, f2ptr y) {f2place__thing__set(x, cause, y); return nil;}
def_pcfunk2(place__thing__set, x, y, return f2__place__thing__set(this_cause, x, y));

f2ptr f2place__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_place.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_place.new__funk);}
  {char* slot_name = "thing";   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_place.thing__funk, __funk2.globalenv.object_type.primobject.primobject_type_place.thing__set__funk, nil);}
  return this;
}



// cons

defprimobject__static_slot(cons__car, 0);
defprimobject__static_slot(cons__cdr, 1);

f2ptr __cons__symbol = -1;

f2ptr f2cons__new__trace_depth(f2ptr cause, f2ptr car, f2ptr cdr, int trace_depth) {
  release__assert(__cons__symbol != -1, nil, "f2cons__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __cons__symbol, 2, nil, trace_depth);
  f2cons__car__set__trace_depth(this, cause, car, trace_depth);
  f2cons__cdr__set__trace_depth(this, cause, cdr, trace_depth);
  return this;
}

f2ptr f2cons__new(f2ptr cause, f2ptr car, f2ptr cdr) {
  return f2cons__new__trace_depth(cause, car, cdr, 1);
}

boolean_t raw__cons__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_cons(x, cause));
}
f2ptr f2__cons__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__cons__is_type(cause, x));}
def_pcfunk1(cons__is_type, x, return f2__cons__is_type(this_cause, x));

f2ptr f2__cons__new(f2ptr cause, f2ptr x, f2ptr y) {return f2cons__new(cause, x, y);}
def_pcfunk2(cons__new, x, y, return f2__cons__new(this_cause, x, y));

f2ptr f2__cons__car(f2ptr cause, f2ptr x) {return f2cons__car(x, cause);}
def_pcfunk1(cons__car, x, return f2__cons__car(this_cause, x));

f2ptr f2__cons__car__set(f2ptr cause, f2ptr x, f2ptr y) {f2cons__car__set(x, cause, y); return nil;}
def_pcfunk2(cons__car__set, x, y, return f2__cons__car__set(this_cause, x, y));

f2ptr f2__cons__cdr(f2ptr cause, f2ptr x) {return f2cons__cdr(x, cause);}
def_pcfunk1(cons__cdr, x, return f2__cons__cdr(this_cause, x));

f2ptr f2__cons__cdr__set(f2ptr cause, f2ptr x, f2ptr y) {f2cons__cdr__set(x, cause, y); return nil;}
def_pcfunk2(cons__cdr__set, x, y, return f2__cons__cdr__set(this_cause, x, y));

f2ptr f2cons__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cons.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cons.new__funk);}
  {char* slot_name = "car";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.car__funk, __funk2.globalenv.object_type.primobject.primobject_type_cons.car__set__funk, nil);}
  {char* slot_name = "cdr";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__funk, __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__set__funk, nil);}
  return this;
}



// doublelink

defprimobject__static_slot(doublelink__prev,  0);
defprimobject__static_slot(doublelink__next,  1);
defprimobject__static_slot(doublelink__value, 2);

f2ptr __doublelink__symbol = -1;

f2ptr f2doublelink__new__trace_depth(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value, int trace_depth) {
  release__assert(__doublelink__symbol != -1, nil, "f2doublelink__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __doublelink__symbol, 3, nil, trace_depth);
  f2doublelink__prev__set__trace_depth( this, cause, prev,  trace_depth);
  f2doublelink__next__set__trace_depth( this, cause, next,  trace_depth);
  f2doublelink__value__set__trace_depth(this, cause, value, trace_depth);
  return this;
}

f2ptr f2doublelink__new(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value) {
  return f2doublelink__new__trace_depth(cause, prev, next, value, 1);
}

boolean_t raw__doublelink__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_doublelink(x, cause));
}
f2ptr f2__doublelink__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__doublelink__is_type(cause, x));}
def_pcfunk1(doublelink__is_type, x, return f2__doublelink__is_type(this_cause, x));

f2ptr f2__doublelink__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {return f2doublelink__new(cause, x, y, z);}
def_pcfunk3(doublelink__new, x, y, z, return f2__doublelink__new(this_cause, x, y, z));

f2ptr f2__doublelink__prev(f2ptr cause, f2ptr x) {return f2doublelink__prev(x, cause);}
def_pcfunk1(doublelink__prev, x, return f2__doublelink__prev(this_cause, x));

f2ptr f2__doublelink__prev__set(f2ptr cause, f2ptr x, f2ptr y) {f2doublelink__prev__set(x, cause, y); return nil;}
def_pcfunk2(doublelink__prev__set, x, y, return f2__doublelink__prev__set(this_cause, x, y));

f2ptr f2__doublelink__next(f2ptr cause, f2ptr x) {return f2doublelink__next(x, cause);}
def_pcfunk1(doublelink__next, x, return f2__doublelink__next(this_cause, x));

f2ptr f2__doublelink__next__set(f2ptr cause, f2ptr x, f2ptr y) {f2doublelink__next__set(x, cause, y); return nil;}
def_pcfunk2(doublelink__next__set, x, y, return f2__doublelink__next__set(this_cause, x, y));

f2ptr f2__doublelink__value(f2ptr cause, f2ptr x) {return f2doublelink__value(x, cause);}
def_pcfunk1(doublelink__value, x, return f2__doublelink__value(this_cause, x));

f2ptr f2__doublelink__value__set(f2ptr cause, f2ptr x, f2ptr y) {f2doublelink__value__set(x, cause, y); return nil;}
def_pcfunk2(doublelink__value__set, x, y, return f2__doublelink__value__set(this_cause, x, y));

f2ptr f2doublelink__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_doublelink.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_doublelink.new__funk);}
  {char* slot_name = "prev";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelink.prev__funk,  __funk2.globalenv.object_type.primobject.primobject_type_doublelink.prev__set__funk, nil);}
  {char* slot_name = "next";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelink.next__funk,  __funk2.globalenv.object_type.primobject.primobject_type_doublelink.next__set__funk, nil);}
  {char* slot_name = "value";   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelink.value__funk, __funk2.globalenv.object_type.primobject.primobject_type_doublelink.value__set__funk, nil);}
  return this;
}


// imagination_link

defprimobject__static_slot(imagination_link__next,              0);
defprimobject__static_slot(imagination_link__name,              1);
defprimobject__static_slot(imagination_link__value,             2);
defprimobject__static_slot(imagination_link__trace,             3);
defprimobject__static_slot(imagination_link__imagination_frame, 4);

f2ptr __imagination_link__symbol = -1;

f2ptr f2imagination_link__new__trace_depth(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame, int trace_depth) {
  release__assert(__imagination_link__symbol != -1, nil, "f2imagination_link__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __imagination_link__symbol, 5, nil, trace_depth);
  f2imagination_link__next__set__trace_depth(             this, cause, next,              trace_depth);
  f2imagination_link__name__set__trace_depth(             this, cause, name,              trace_depth);
  f2imagination_link__value__set__trace_depth(            this, cause, value,             trace_depth);
  f2imagination_link__trace__set__trace_depth(            this, cause, trace,             trace_depth);
  f2imagination_link__imagination_frame__set__trace_depth(this, cause, imagination_frame, trace_depth);
  return this;
}

f2ptr f2imagination_link__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.is_type__funk);}
  {char* slot_name = "new";               f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.new__funk);}
  {char* slot_name = "next";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									__funk2.globalenv.object_type.primobject.primobject_type_imagination_link.next__funk,              __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.next__set__funk, nil);}
  {char* slot_name = "name";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									__funk2.globalenv.object_type.primobject.primobject_type_imagination_link.name__funk,              __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.name__set__funk, nil);}
  {char* slot_name = "value";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									__funk2.globalenv.object_type.primobject.primobject_type_imagination_link.value__funk,             __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.value__set__funk, nil);}
  {char* slot_name = "trace";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									__funk2.globalenv.object_type.primobject.primobject_type_imagination_link.trace__funk,             __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.trace__set__funk, nil);}
  {char* slot_name = "imagination_frame"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									__funk2.globalenv.object_type.primobject.primobject_type_imagination_link.imagination_frame__funk, __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.imagination_frame__set__funk, nil);}
  return this;
}

f2ptr f2imagination_link__new(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame) {
  return f2imagination_link__new__trace_depth(cause, next, name, value, trace, imagination_frame, 1);
}

boolean_t raw__imagination_link__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_imagination_link(x, cause));
}
f2ptr f2__imagination_link__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__imagination_link__is_type(cause, x));}
def_pcfunk1(imagination_link__is_type, x, return f2__imagination_link__is_type(this_cause, x));

f2ptr f2__imagination_link__new(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame) {return f2imagination_link__new(cause, next, name, value, trace, imagination_frame);}
def_pcfunk5(imagination_link__new, next, name, value, trace, imagination_frame, return f2__imagination_link__new(this_cause, next, name, value, trace, imagination_frame));

f2ptr f2__imagination_link__next(f2ptr cause, f2ptr this) {return f2imagination_link__next(this, cause);}
def_pcfunk1(imagination_link__next, x, return f2__imagination_link__next(this_cause, x));

f2ptr f2__imagination_link__next__set(f2ptr cause, f2ptr this, f2ptr value) {return f2imagination_link__next__set(this, cause, value);}
def_pcfunk2(imagination_link__next__set, x, y, return f2__imagination_link__next__set(this_cause, x, y));

f2ptr f2__imagination_link__name(f2ptr cause, f2ptr this) {return f2imagination_link__name(this, cause);}
def_pcfunk1(imagination_link__name, x, return f2__imagination_link__name(this_cause, x));

f2ptr f2__imagination_link__name__set(f2ptr cause, f2ptr this, f2ptr value) {return f2imagination_link__name__set(this, cause, value);}
def_pcfunk2(imagination_link__name__set, x, y, return f2__imagination_link__name__set(this_cause, x, y));

f2ptr f2__imagination_link__value(f2ptr cause, f2ptr this) {return f2imagination_link__value(this, cause);}
def_pcfunk1(imagination_link__value, x, return f2__imagination_link__value(this_cause, x));

f2ptr f2__imagination_link__value__set(f2ptr cause, f2ptr this, f2ptr value) {return f2imagination_link__value__set(this, cause, value);}
def_pcfunk2(imagination_link__value__set, x, y, return f2__imagination_link__value__set(this_cause, x, y));

f2ptr f2__imagination_link__trace(f2ptr cause, f2ptr this) {return f2imagination_link__trace(this, cause);}
def_pcfunk1(imagination_link__trace, x, return f2__imagination_link__trace(this_cause, x));

f2ptr f2__imagination_link__trace__set(f2ptr cause, f2ptr this, f2ptr trace) {return f2imagination_link__trace__set(this, cause, trace);}
def_pcfunk2(imagination_link__trace__set, x, y, return f2__imagination_link__trace__set(this_cause, x, y));

f2ptr f2__imagination_link__imagination_frame(f2ptr cause, f2ptr this) {return f2imagination_link__imagination_frame(this, cause);}
def_pcfunk1(imagination_link__imagination_frame, x, return f2__imagination_link__imagination_frame(this_cause, x));

f2ptr f2__imagination_link__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr value) {return f2imagination_link__imagination_frame__set(this, cause, value);}
def_pcfunk2(imagination_link__imagination_frame__set, x, y, return f2__imagination_link__imagination_frame__set(this_cause, x, y));


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

defprimobject__static_slot(cfunk__name,          0);
defprimobject__static_slot(cfunk__args,          1);
defprimobject__static_slot(cfunk__cfunkptr,      2);
defprimobject__static_slot(cfunk__env,           3);
defprimobject__static_slot(cfunk__is_funktional, 4);
defprimobject__static_slot(cfunk__documentation, 5);

f2ptr __cfunk__symbol = -1;

f2ptr f2cfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {
  /*pause_gc();*/
  release__assert(__cfunk__symbol != -1, nil, "f2cfunk__new error: used before primobjects initialized.");
  if (!cfunkptr) {return primobject_error("cfunk-cfunkptr cannot be nil.");}
  f2ptr this = f2__primobject__new(cause, __cfunk__symbol, 6, nil);
  f2cfunk__name__set(         this, cause, name);
  f2cfunk__args__set(         this, cause, args);
  f2cfunk__cfunkptr__set(     this, cause, cfunkptr);
  f2cfunk__env__set(          this, cause, env);
  f2cfunk__is_funktional__set(this, cause, is_funktional);
  f2cfunk__documentation__set(this, cause, documentation);
  /*resume_gc();*/
  return this;
}

f2ptr f2cfunk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_type__funk);}
  {char* slot_name = "new";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cfunk.new__funk);}
  {char* slot_name = "name";          f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_cfunk.name__funk,          __funk2.globalenv.object_type.primobject.primobject_type_cfunk.name__set__funk, nil);}
  {char* slot_name = "args";          f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_cfunk.args__funk,          __funk2.globalenv.object_type.primobject.primobject_type_cfunk.args__set__funk, nil);}
  {char* slot_name = "cfunkptr";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_cfunk.cfunkptr__funk,      __funk2.globalenv.object_type.primobject.primobject_type_cfunk.cfunkptr__set__funk, nil);}
  {char* slot_name = "env";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_cfunk.env__funk,           __funk2.globalenv.object_type.primobject.primobject_type_cfunk.env__set__funk, nil);}
  {char* slot_name = "is_funktional"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_funktional__funk, __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_funktional__set__funk, nil);}
  {char* slot_name = "documentation"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_cfunk.documentation__funk, __funk2.globalenv.object_type.primobject.primobject_type_cfunk.documentation__set__funk, nil);}
  return this;
}

boolean_t raw__cfunk__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_cfunk(x, cause));
}
f2ptr f2__cfunk__is_type(f2ptr cause, f2ptr this) {return f2__cfunk__is_type(cause, this);}
def_pcfunk1(cfunk__is_type, x, return f2__cfunk__is_type(this_cause, x));

f2ptr f2__cfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(cfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__cfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));

f2ptr f2__cfunk__name(f2ptr cause, f2ptr this) {return f2cfunk__name(this, cause);}
def_pcfunk1(cfunk__name, x, return f2__cfunk__name(this_cause, x));

f2ptr f2__cfunk__name__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cfunk__name__set(this, cause, value);}
def_pcfunk2(cfunk__name__set, x, y, return f2__cfunk__name__set(this_cause, x, y));

f2ptr f2__cfunk__args(f2ptr cause, f2ptr this) {return f2cfunk__args(this, cause);}
def_pcfunk1(cfunk__args, x, return f2__cfunk__args(this_cause, x));

f2ptr f2__cfunk__args__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cfunk__args__set(this, cause, value);}
def_pcfunk2(cfunk__args__set, x, y, return f2__cfunk__args__set(this_cause, x, y));

f2ptr f2__cfunk__cfunkptr(f2ptr cause, f2ptr this) {return f2cfunk__cfunkptr(this, cause);}
def_pcfunk1(cfunk__cfunkptr, x, return f2__cfunk__cfunkptr(this_cause, x));

f2ptr f2__cfunk__cfunkptr__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cfunk__cfunkptr__set(this, cause, value);}
def_pcfunk2(cfunk__cfunkptr__set, x, y, return f2__cfunk__cfunkptr__set(this_cause, x, y));

f2ptr f2__cfunk__env(f2ptr cause, f2ptr this) {return f2cfunk__env(this, cause);}
def_pcfunk1(cfunk__env, x, return f2__cfunk__env(this_cause, x));

f2ptr f2__cfunk__env__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cfunk__env__set(this, cause, value);}
def_pcfunk2(cfunk__env__set, x, y, return f2__cfunk__env__set(this_cause, x, y));

f2ptr f2__cfunk__is_funktional(f2ptr cause, f2ptr this) {return f2cfunk__is_funktional(this, cause);}
def_pcfunk1(cfunk__is_funktional, x, return f2__cfunk__is_funktional(this_cause, x));

f2ptr f2__cfunk__is_funktional__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cfunk__is_funktional__set(this, cause, value);}
def_pcfunk2(cfunk__is_funktional__set, x, y, return f2__cfunk__is_funktional__set(this_cause, x, y));

f2ptr f2__cfunk__documentation(f2ptr cause, f2ptr this) {return f2cfunk__documentation(this, cause);}
def_pcfunk1(cfunk__documentation, x, return f2__cfunk__documentation(this_cause, x));

f2ptr f2__cfunk__documentation__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cfunk__documentation__set(this, cause, value);}
def_pcfunk2(cfunk__documentation__set, x, y, return f2__cfunk__documentation__set(this_cause, x, y));


// metrocfunk

defprimobject__static_slot(metrocfunk__name,          0);
defprimobject__static_slot(metrocfunk__args,          1);
defprimobject__static_slot(metrocfunk__cfunkptr,      2);
defprimobject__static_slot(metrocfunk__env,           3);
defprimobject__static_slot(metrocfunk__is_funktional, 4);
defprimobject__static_slot(metrocfunk__documentation, 5);

f2ptr __metrocfunk__symbol = -1;

f2ptr f2metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {
  /*pause_gc();*/
  release__assert(__metrocfunk__symbol != -1, nil, "f2metrocfunk__new error: used before primobjects initialized.");
  if (!cfunkptr) {return primobject_error("metrocfunk-cfunkptr cannot be nil.");}
  f2ptr this = f2__primobject__new(cause, __metrocfunk__symbol, 6, nil);
  f2metrocfunk__name__set(         this, cause, name);
  f2metrocfunk__args__set(         this, cause, args);
  f2metrocfunk__cfunkptr__set(     this, cause, cfunkptr);
  f2metrocfunk__env__set(          this, cause, env);
  f2metrocfunk__is_funktional__set(this, cause, is_funktional);
  f2metrocfunk__documentation__set(this, cause, documentation);
  /*resume_gc();*/
  return this;
}

f2ptr f2metrocfunk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_type__funk);}
  {char* slot_name = "new";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.new__funk);}
  {char* slot_name = "name";          f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.name__funk,          __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.name__set__funk, nil);}
  {char* slot_name = "args";          f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.args__funk,          __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.args__set__funk, nil);}
  {char* slot_name = "cfunkptr";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.cfunkptr__funk,      __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.cfunkptr__set__funk, nil);}
  {char* slot_name = "env";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.env__funk,           __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.env__set__funk, nil);}
  {char* slot_name = "is_funktional"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_funktional__funk, __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_funktional__set__funk, nil);}
  {char* slot_name = "documentation"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
								    __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.documentation__funk, __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.documentation__set__funk, nil);}
  return this;
}

boolean_t raw__metrocfunk__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_metrocfunk(x, cause));
}
f2ptr f2__metrocfunk__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__metrocfunk__is_type(cause, this));}
def_pcfunk1(metrocfunk__is_type, x, return f2__metrocfunk__is_type(this_cause, x));

f2ptr f2__metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2metrocfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(metrocfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__metrocfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));

f2ptr f2__metrocfunk__name(f2ptr cause, f2ptr this) {return f2metrocfunk__name(this, cause);}
def_pcfunk1(metrocfunk__name, x, return f2__metrocfunk__name(this_cause, x));

f2ptr f2__metrocfunk__name__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metrocfunk__name__set(this, cause, value);}
def_pcfunk2(metrocfunk__name__set, x, y, return f2__metrocfunk__name__set(this_cause, x, y));

f2ptr f2__metrocfunk__args(f2ptr cause, f2ptr this) {return f2metrocfunk__args(this, cause);}
def_pcfunk1(metrocfunk__args, x, return f2__metrocfunk__args(this_cause, x));

f2ptr f2__metrocfunk__args__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metrocfunk__args__set(this, cause, value);}
def_pcfunk2(metrocfunk__args__set, x, y, return f2__metrocfunk__args__set(this_cause, x, y));

f2ptr f2__metrocfunk__cfunkptr(f2ptr cause, f2ptr this) {return f2metrocfunk__cfunkptr(this, cause);}
def_pcfunk1(metrocfunk__cfunkptr, x, return f2__metrocfunk__cfunkptr(this_cause, x));

f2ptr f2__metrocfunk__cfunkptr__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metrocfunk__cfunkptr__set(this, cause, value);}
def_pcfunk2(metrocfunk__cfunkptr__set, x, y, return f2__metrocfunk__cfunkptr__set(this_cause, x, y));

f2ptr f2__metrocfunk__env(f2ptr cause, f2ptr this) {return f2metrocfunk__env(this, cause);}
def_pcfunk1(metrocfunk__env, x, return f2__metrocfunk__env(this_cause, x));

f2ptr f2__metrocfunk__env__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metrocfunk__env__set(this, cause, value);}
def_pcfunk2(metrocfunk__env__set, x, y, return f2__metrocfunk__env__set(this_cause, x, y));

f2ptr f2__metrocfunk__is_funktional(f2ptr cause, f2ptr this) {return f2metrocfunk__is_funktional(this, cause);}
def_pcfunk1(metrocfunk__is_funktional, x, return f2__metrocfunk__is_funktional(this_cause, x));

f2ptr f2__metrocfunk__is_funktional__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metrocfunk__is_funktional__set(this, cause, value);}
def_pcfunk2(metrocfunk__is_funktional__set, x, y, return f2__metrocfunk__is_funktional__set(this_cause, x, y));

f2ptr f2__metrocfunk__documentation(f2ptr cause, f2ptr this) {return f2metrocfunk__documentation(this, cause);}
def_pcfunk1(metrocfunk__documentation, x, return f2__metrocfunk__documentation(this_cause, x));

f2ptr f2__metrocfunk__documentation__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metrocfunk__documentation__set(this, cause, value);}
def_pcfunk2(metrocfunk__documentation__set, x, y, return f2__metrocfunk__documentation__set(this_cause, x, y));


// funk

defprimobject__static_slot(funk__name,                0);
defprimobject__static_slot(funk__body_bytecodes,      1);
defprimobject__static_slot(funk__args,                2);
defprimobject__static_slot(funk__demetropolized_body, 3);
defprimobject__static_slot(funk__body,                4);
defprimobject__static_slot(funk__env,                 5);
defprimobject__static_slot(funk__machine_code,        6);
defprimobject__static_slot(funk__is_funktional,       7);
defprimobject__static_slot(funk__documentation,       8);

f2ptr __funk__symbol = -1;

f2ptr f2funk__new(f2ptr cause, f2ptr name, f2ptr body_bytecodes, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr env, f2ptr machine_code, f2ptr is_funktional, f2ptr documentation) {
  /*pause_gc();*/
  release__assert(__funk__symbol != -1, nil, "f2funk__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __funk__symbol, 9, nil);
  f2funk__name__set(               this, cause, name);
  f2funk__body_bytecodes__set(     this, cause, body_bytecodes);
  f2funk__args__set(               this, cause, args);
  f2funk__demetropolized_body__set(this, cause, demetropolized_body);
  f2funk__body__set(               this, cause, body);
  f2funk__env__set(                this, cause, env);
  f2funk__machine_code__set(       this, cause, machine_code);
  f2funk__is_funktional__set(      this, cause, is_funktional);
  f2funk__documentation__set(      this, cause, documentation);
  /*resume_gc();*/
  return this;
}

f2ptr f2funk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_funk.is_type__funk);}
  //{char* slot_name = "new";                 f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_funk.new__funk);}
  {char* slot_name = "name";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.name__funk,                __funk2.globalenv.object_type.primobject.primobject_type_funk.name__set__funk, nil);}
  {char* slot_name = "body_bytecodes";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.body_bytecodes__funk,      __funk2.globalenv.object_type.primobject.primobject_type_funk.body_bytecodes__set__funk, nil);}
  {char* slot_name = "args";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.args__funk,                __funk2.globalenv.object_type.primobject.primobject_type_funk.args__set__funk, nil);}
  {char* slot_name = "demetropolized_body"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.demetropolized_body__funk, __funk2.globalenv.object_type.primobject.primobject_type_funk.demetropolized_body__set__funk, nil);}
  {char* slot_name = "body";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.body__funk,                __funk2.globalenv.object_type.primobject.primobject_type_funk.body__set__funk, nil);}
  {char* slot_name = "env";                 f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.env__funk,                 __funk2.globalenv.object_type.primobject.primobject_type_funk.env__set__funk, nil);}
  {char* slot_name = "machine_code";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.machine_code__funk,        __funk2.globalenv.object_type.primobject.primobject_type_funk.machine_code__set__funk, nil);}
  {char* slot_name = "is_funktional";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.is_funktional__funk,       __funk2.globalenv.object_type.primobject.primobject_type_funk.is_funktional__set__funk, nil);}
  {char* slot_name = "documentation";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_funk.documentation__funk,       __funk2.globalenv.object_type.primobject.primobject_type_funk.documentation__set__funk, nil);}
  return this;
}

boolean_t raw__funk__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_funk(x, cause));
}
f2ptr f2__funk__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__funk__is_type(cause, x));}
def_pcfunk1(funk__is_type, x, return f2__funk__is_type(this_cause, x));

f2ptr f2__funk__name(f2ptr cause, f2ptr this) {return f2funk__name(this, cause);}
def_pcfunk1(funk__name, x, return f2__funk__name(this_cause, x));

f2ptr f2__funk__name__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__name__set(this, cause, value);}
def_pcfunk2(funk__name__set, x, y, return f2__funk__name__set(this_cause, x, y));

f2ptr f2__funk__body_bytecodes(f2ptr cause, f2ptr this) {return f2funk__body_bytecodes(this, cause);}
def_pcfunk1(funk__body_bytecodes, x, return f2__funk__body_bytecodes(this_cause, x));

f2ptr f2__funk__body_bytecodes__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__body_bytecodes__set(this, cause, value);}
def_pcfunk2(funk__body_bytecodes__set, x, y, return f2__funk__body_bytecodes__set(this_cause, x, y));

f2ptr f2__funk__args(f2ptr cause, f2ptr this) {return f2funk__args(this, cause);}
def_pcfunk1(funk__args, x, return f2__funk__args(this_cause, x));

f2ptr f2__funk__args__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__args__set(this, cause, value);}
def_pcfunk2(funk__args__set, x, y, return f2__funk__args__set(this_cause, x, y));

f2ptr f2__funk__demetropolized_body(f2ptr cause, f2ptr this) {return f2funk__demetropolized_body(this, cause);}
def_pcfunk1(funk__demetropolized_body, x, return f2__funk__demetropolized_body(this_cause, x));

f2ptr f2__funk__demetropolized_body__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__demetropolized_body__set(this, cause, value);}
def_pcfunk2(funk__demetropolized_body__set, x, y, return f2__funk__demetropolized_body__set(this_cause, x, y));

f2ptr f2__funk__body(f2ptr cause, f2ptr this) {return f2funk__body(this, cause);}
def_pcfunk1(funk__body, x, return f2__funk__body(this_cause, x));

f2ptr f2__funk__body__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__body__set(this, cause, value);}
def_pcfunk2(funk__body__set, x, y, return f2__funk__body__set(this_cause, x, y));

f2ptr f2__funk__env(f2ptr cause, f2ptr this) {return f2funk__env(this, cause);}
def_pcfunk1(funk__env, x, return f2__funk__env(this_cause, x));

f2ptr f2__funk__env__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__env__set(this, cause, value);}
def_pcfunk2(funk__env__set, x, y, return f2__funk__env__set(this_cause, x, y));

f2ptr f2__funk__machine_code(f2ptr cause, f2ptr this) {return f2funk__machine_code(this, cause);}
def_pcfunk1(funk__machine_code, x, return f2__funk__machine_code(this_cause, x));

f2ptr f2__funk__machine_code__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__machine_code__set(this, cause, value);}
def_pcfunk2(funk__machine_code__set, x, y, return f2__funk__machine_code__set(this_cause, x, y));

f2ptr f2__funk__is_funktional(f2ptr cause, f2ptr this) {return f2funk__is_funktional(this, cause);}
def_pcfunk1(funk__is_funktional, x, return f2__funk__is_funktional(this_cause, x));

f2ptr f2__funk__is_funktional__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__is_funktional__set(this, cause, value);}
def_pcfunk2(funk__is_funktional__set, x, y, return f2__funk__is_funktional__set(this_cause, x, y));

f2ptr f2__funk__documentation(f2ptr cause, f2ptr this) {return f2funk__documentation(this, cause);}
def_pcfunk1(funk__documentation, x, return f2__funk__documentation(this_cause, x));

f2ptr f2__funk__documentation__set(f2ptr cause, f2ptr this, f2ptr value) {return f2funk__documentation__set(this, cause, value);}
def_pcfunk2(funk__documentation__set, x, y, return f2__funk__documentation__set(this_cause, x, y));


// metro

defprimobject__static_slot(metro__name,                0);
defprimobject__static_slot(metro__body_bytecodes,      1);
defprimobject__static_slot(metro__args,                2);
defprimobject__static_slot(metro__demetropolized_body, 3);
defprimobject__static_slot(metro__body,                4);
defprimobject__static_slot(metro__env,                 5);
defprimobject__static_slot(metro__machine_code,        6);
defprimobject__static_slot(metro__is_funktional,       7);
defprimobject__static_slot(metro__documentation,       8);

f2ptr __metro__symbol = -1;

f2ptr f2metro__new(f2ptr cause, f2ptr name, f2ptr body_bytecodes, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr env, f2ptr machine_code, f2ptr is_funktional, f2ptr documentation) {
  /*pause_gc();*/
  release__assert(__metro__symbol != -1, nil, "f2metro__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __metro__symbol, 9, nil);
  f2metro__name__set(               this, cause, name);
  f2metro__body_bytecodes__set(     this, cause, body_bytecodes);
  f2metro__args__set(               this, cause, args);
  f2metro__demetropolized_body__set(this, cause, demetropolized_body);
  f2metro__body__set(               this, cause, body);
  f2metro__env__set(                this, cause, env);
  f2metro__machine_code__set(       this, cause, machine_code);
  f2metro__is_funktional__set(      this, cause, is_funktional);
  f2metro__documentation__set(      this, cause, documentation);
  /*resume_gc();*/
  return this;
}

f2ptr f2metro__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_metro.is_type__funk);}
  //{char* slot_name = "new";                 f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_metro.new__funk);}
  {char* slot_name = "name";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.name__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.name__set__funk, nil);}
  {char* slot_name = "body_bytecodes";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.body_bytecodes__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.body_bytecodes__set__funk, nil);}
  {char* slot_name = "args";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.args__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.args__set__funk, nil);}
  {char* slot_name = "demetropolized_body"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.demetropolized_body__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.demetropolized_body__set__funk, nil);}
  {char* slot_name = "body";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.body__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.body__set__funk, nil);}
  {char* slot_name = "env";                 f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.env__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.env__set__funk, nil);}
  {char* slot_name = "machine_code";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.machine_code__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.machine_code__set__funk, nil);}
  {char* slot_name = "is_funktional";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.is_funktional__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.is_funktional__set__funk, nil);}
  {char* slot_name = "documentation";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									  __funk2.globalenv.object_type.primobject.primobject_type_metro.documentation__funk, __funk2.globalenv.object_type.primobject.primobject_type_metro.documentation__set__funk, nil);}
  return this;
}

boolean_t raw__metro__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_metro(x, cause));
}
f2ptr f2__metro__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__metro__is_type(cause, x));}
def_pcfunk1(metro__is_type, x, return f2__metro__is_type(this_cause, x));

f2ptr f2__metro__name(f2ptr cause, f2ptr this) {return f2metro__name(this, cause);}
def_pcfunk1(metro__name, x, return f2__metro__name(this_cause, x));

f2ptr f2__metro__name__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__name__set(this, cause, value);}
def_pcfunk2(metro__name__set, x, y, return f2__metro__name__set(this_cause, x, y));

f2ptr f2__metro__body_bytecodes(f2ptr cause, f2ptr this) {return f2metro__body_bytecodes(this, cause);}
def_pcfunk1(metro__body_bytecodes, x, return f2__metro__body_bytecodes(this_cause, x));

f2ptr f2__metro__body_bytecodes__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__body_bytecodes__set(this, cause, value);}
def_pcfunk2(metro__body_bytecodes__set, x, y, return f2__metro__body_bytecodes__set(this_cause, x, y));

f2ptr f2__metro__args(f2ptr cause, f2ptr this) {return f2metro__args(this, cause);}
def_pcfunk1(metro__args, x, return f2__metro__args(this_cause, x));

f2ptr f2__metro__args__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__args__set(this, cause, value);}
def_pcfunk2(metro__args__set, x, y, return f2__metro__args__set(this_cause, x, y));

f2ptr f2__metro__demetropolized_body(f2ptr cause, f2ptr this) {return f2metro__demetropolized_body(this, cause);}
def_pcfunk1(metro__demetropolized_body, x, return f2__metro__demetropolized_body(this_cause, x));

f2ptr f2__metro__demetropolized_body__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__demetropolized_body__set(this, cause, value);}
def_pcfunk2(metro__demetropolized_body__set, x, y, return f2__metro__demetropolized_body__set(this_cause, x, y));

f2ptr f2__metro__body(f2ptr cause, f2ptr this) {return f2metro__body(this, cause);}
def_pcfunk1(metro__body, x, return f2__metro__body(this_cause, x));

f2ptr f2__metro__body__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__body__set(this, cause, value);}
def_pcfunk2(metro__body__set, x, y, return f2__metro__body__set(this_cause, x, y));

f2ptr f2__metro__env(f2ptr cause, f2ptr this) {return f2metro__env(this, cause);}
def_pcfunk1(metro__env, x, return f2__metro__env(this_cause, x));

f2ptr f2__metro__env__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__env__set(this, cause, value);}
def_pcfunk2(metro__env__set, x, y, return f2__metro__env__set(this_cause, x, y));

f2ptr f2__metro__machine_code(f2ptr cause, f2ptr this) {return f2metro__machine_code(this, cause);}
def_pcfunk1(metro__machine_code, x, return f2__metro__machine_code(this_cause, x));

f2ptr f2__metro__machine_code__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__machine_code__set(this, cause, value);}
def_pcfunk2(metro__machine_code__set, x, y, return f2__metro__machine_code__set(this_cause, x, y));

f2ptr f2__metro__is_funktional(f2ptr cause, f2ptr this) {return f2metro__is_funktional(this, cause);}
def_pcfunk1(metro__is_funktional, x, return f2__metro__is_funktional(this_cause, x));

f2ptr f2__metro__is_funktional__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__is_funktional__set(this, cause, value);}
def_pcfunk2(metro__is_funktional__set, x, y, return f2__metro__is_funktional__set(this_cause, x, y));

f2ptr f2__metro__documentation(f2ptr cause, f2ptr this) {return f2metro__documentation(this, cause);}
def_pcfunk1(metro__documentation, x, return f2__metro__documentation(this_cause, x));

f2ptr f2__metro__documentation__set(f2ptr cause, f2ptr this, f2ptr value) {return f2metro__documentation__set(this, cause, value);}
def_pcfunk2(metro__documentation__set, x, y, return f2__metro__documentation__set(this_cause, x, y));


// exception

defprimobject__static_slot(exception__tag,   0);
defprimobject__static_slot(exception__value, 1);

f2ptr __exception__symbol = -1;

f2ptr f2exception__new(f2ptr cause, f2ptr tag, f2ptr value) {
  /*pause_gc();*/
  release__assert(__exception__symbol != -1, nil, "f2exception__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __exception__symbol, 2, nil);
  f2exception__tag__set(  this, cause, tag);
  f2exception__value__set(this, cause, value);
  /*resume_gc();*/
  return this;
}

f2ptr f2exception__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_exception.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_exception.new__funk);}
  {char* slot_name = "tag";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_exception.tag__funk, __funk2.globalenv.object_type.primobject.primobject_type_exception.tag__set__funk, nil);}
  {char* slot_name = "value";   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_exception.value__funk, __funk2.globalenv.object_type.primobject.primobject_type_exception.value__set__funk, nil);}
  return this;
}

boolean_t raw__exception__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_exception(x, cause));
}
f2ptr f2__exception__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__exception__is_type(cause, x));}
def_pcfunk1(exception__is_type, x, return f2__exception__is_type(this_cause, x));

f2ptr f2__exception__new(f2ptr cause, f2ptr tag, f2ptr value) {return f2exception__new(cause, tag, value);}
def_pcfunk2(exception__new, tag, value, return f2__exception__new(this_cause, tag, value));

f2ptr f2__exception__tag(f2ptr cause, f2ptr this) {return f2exception__tag(this, cause);}
def_pcfunk1(exception__tag, x, return f2__exception__tag(this_cause, x));

f2ptr f2__exception__tag__set(f2ptr cause, f2ptr this, f2ptr value) {return f2exception__tag__set(this, cause, value);}
def_pcfunk2(exception__tag__set, x, y, return f2__exception__tag__set(this_cause, x, y));

f2ptr f2__exception__value(f2ptr cause, f2ptr this) {return f2exception__value(this, cause);}
def_pcfunk1(exception__value, x, return f2__exception__value(this_cause, x));

f2ptr f2__exception__value__set(f2ptr cause, f2ptr this, f2ptr value) {return f2exception__value__set(this, cause, value);}
def_pcfunk2(exception__value__set, x, y, return f2__exception__value__set(this_cause, x, y));



// bytecode

defprimobject__static_slot(bytecode__command, 0);
defprimobject__static_slot(bytecode__arg0,    1);
defprimobject__static_slot(bytecode__arg1,    2);
defprimobject__static_slot(bytecode__arg2,    3);

f2ptr __bytecode__symbol = -1;

f2ptr f2bytecode__new(f2ptr cause, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2) {
  /*pause_gc();*/
  release__assert(__bytecode__symbol != -1, nil, "f2bytecode__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __bytecode__symbol, 4, nil);
  f2bytecode__command__set(this, cause, command);
  f2bytecode__arg0__set(   this, cause, arg0);
  f2bytecode__arg1__set(   this, cause, arg1);
  f2bytecode__arg2__set(   this, cause, arg2);
  /*resume_gc();*/
  return this;
}

f2ptr f2bytecode__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_bytecode.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_bytecode.new__funk);}
  {char* slot_name = "command"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bytecode.command__funk, __funk2.globalenv.object_type.primobject.primobject_type_bytecode.command__set__funk, nil);}
  {char* slot_name = "arg0";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg0__funk, __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg0__set__funk, nil);}
  {char* slot_name = "arg1";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg1__funk, __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg1__set__funk, nil);}
  {char* slot_name = "arg2";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg2__funk, __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg2__set__funk, nil);}
  return this;
}

boolean_t raw__bytecode__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_bytecode(x, cause));
}
f2ptr f2__bytecode__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__bytecode__is_type(cause, x));}
def_pcfunk1(bytecode__is_type, x, return f2__bytecode__is_type(this_cause, x));

f2ptr f2__bytecode__new(f2ptr cause, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2) {return f2bytecode__new(cause, command, arg0, arg1, arg2);}
def_pcfunk4(bytecode__new, command, arg0, arg1, arg2, return f2__bytecode__new(this_cause, command, arg0, arg1, arg2));

f2ptr f2__bytecode__command(f2ptr cause, f2ptr this) {return f2bytecode__command(this, cause);}
def_pcfunk1(bytecode__command, x, return f2__bytecode__command(this_cause, x));

f2ptr f2__bytecode__command__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bytecode__command__set(this, cause, value);}
def_pcfunk2(bytecode__command__set, x, y, return f2__bytecode__command__set(this_cause, x, y));

f2ptr f2__bytecode__arg0(f2ptr cause, f2ptr this) {return f2bytecode__arg0(this, cause);}
def_pcfunk1(bytecode__arg0, x, return f2__bytecode__arg0(this_cause, x));

f2ptr f2__bytecode__arg0__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bytecode__arg0__set(this, cause, value);}
def_pcfunk2(bytecode__arg0__set, x, y, return f2__bytecode__arg0__set(this_cause, x, y));

f2ptr f2__bytecode__arg1(f2ptr cause, f2ptr this) {return f2bytecode__arg1(this, cause);}
def_pcfunk1(bytecode__arg1, x, return f2__bytecode__arg1(this_cause, x));

f2ptr f2__bytecode__arg1__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bytecode__arg1__set(this, cause, value);}
def_pcfunk2(bytecode__arg1__set, x, y, return f2__bytecode__arg1__set(this_cause, x, y));

f2ptr f2__bytecode__arg2(f2ptr cause, f2ptr this) {return f2bytecode__arg2(this, cause);}
def_pcfunk1(bytecode__arg2, x, return f2__bytecode__arg2(this_cause, x));

f2ptr f2__bytecode__arg2__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bytecode__arg2__set(this, cause, value);}
def_pcfunk2(bytecode__arg2__set, x, y, return f2__bytecode__arg2__set(this_cause, x, y));


// thread

defprimobject__static_slot(thread__program_counter,     0);
defprimobject__static_slot(thread__stack,               1);
defprimobject__static_slot(thread__iter,                2);
defprimobject__static_slot(thread__env,                 3);
defprimobject__static_slot(thread__args,                4);
defprimobject__static_slot(thread__return,              5);
defprimobject__static_slot(thread__value,               6);
defprimobject__static_slot(thread__trace,               7);
defprimobject__static_slot(thread__critics,             8);
defprimobject__static_slot(thread__cause_reg,           9);
defprimobject__static_slot(thread__keep_undead,        10);
defprimobject__static_slot(thread__is_zombie,          11);
defprimobject__static_slot(thread__parent_thread,      12);
defprimobject__static_slot(thread__parent_env,         13);
defprimobject__static_slot(thread__execute_mutex,      14);
defprimobject__static_slot(thread__paused,             15);
defprimobject__static_slot(thread__last_executed_time, 16);

f2ptr __thread__symbol = -1;

f2ptr f2thread__new(f2ptr cause,
		    f2ptr program_counter,
		    f2ptr stack,
		    f2ptr iter,
		    f2ptr env,
		    f2ptr args,
		    f2ptr retval,
		    f2ptr value,
		    f2ptr trace,
		    f2ptr critics,
		    f2ptr cause_reg,
		    f2ptr keep_undead,
		    f2ptr is_zombie,
		    f2ptr parent_thread,
		    f2ptr parent_env,
		    f2ptr execute_mutex,
		    f2ptr paused,
		    f2ptr last_executed_time) {
  /*pause_gc();*/
  release__assert(__thread__symbol != -1, nil, "f2thread__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __thread__symbol, 17, nil);
  f2thread__program_counter__set(   this, cause, program_counter);
  f2thread__stack__set(             this, cause, stack);
  f2thread__iter__set(              this, cause, iter);
  f2thread__env__set(               this, cause, env);
  f2thread__args__set(              this, cause, args);
  f2thread__return__set(            this, cause, retval);
  f2thread__value__set(             this, cause, value);
  f2thread__trace__set(             this, cause, trace);
  f2thread__critics__set(           this, cause, critics);
  f2thread__cause_reg__set(         this, cause, cause_reg);
  f2thread__keep_undead__set(       this, cause, keep_undead);
  f2thread__is_zombie__set(         this, cause, is_zombie);
  f2thread__parent_thread__set(     this, cause, parent_thread);
  f2thread__parent_env__set(        this, cause, parent_env);
  f2thread__execute_mutex__set(     this, cause, execute_mutex);
  f2thread__paused__set(            this, cause, paused);
  f2thread__last_executed_time__set(this, cause, last_executed_time);
  /*resume_gc();*/
  return this;
}

f2ptr f2thread__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";            f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_thread.is_type__funk);}
  //{char* slot_name = "new";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_thread.new__funk);}
  {char* slot_name = "program_counter";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.program_counter__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.program_counter__set__funk, nil);}
  {char* slot_name = "stack";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.stack__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.stack__set__funk, nil);}
  {char* slot_name = "iter";               f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.iter__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.iter__set__funk, nil);}
  {char* slot_name = "env";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.env__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.env__set__funk, nil);}
  {char* slot_name = "args";               f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.args__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.args__set__funk, nil);}
  {char* slot_name = "return";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.return__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.return__set__funk, nil);}
  {char* slot_name = "value";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.value__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.value__set__funk, nil);}
  {char* slot_name = "trace";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.trace__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.trace__set__funk, nil);}
  {char* slot_name = "critics";            f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.critics__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.critics__set__funk, nil);}
  {char* slot_name = "cause_reg";          f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.cause_reg__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.cause_reg__set__funk, nil);}
  {char* slot_name = "keep_undead";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.keep_undead__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.keep_undead__set__funk, nil);}
  {char* slot_name = "is_zombie";          f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.is_zombie__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.is_zombie__set__funk, nil);}
  {char* slot_name = "parent_thread";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_thread__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_thread__set__funk, nil);}
  {char* slot_name = "parent_env";         f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_env__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_env__set__funk, nil);}
  {char* slot_name = "execute_mutex";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.execute_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.execute_mutex__set__funk, nil);}
  {char* slot_name = "paused";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.paused__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.paused__set__funk, nil);}
  {char* slot_name = "last_executed_time"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_thread.last_executed_time__funk, __funk2.globalenv.object_type.primobject.primobject_type_thread.last_executed_time__set__funk, nil);}
  return this;
}

boolean_t raw__thread__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_thread(x, cause));
}
f2ptr f2__thread__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__thread__is_type(cause, x));}
def_pcfunk1(thread__is_type, x, return f2__thread__is_type(this_cause, x));

f2ptr f2__thread__program_counter(f2ptr cause, f2ptr this) {return f2thread__program_counter(this, cause);}
def_pcfunk1(thread__program_counter, x, return f2__thread__program_counter(this_cause, x));

f2ptr f2__thread__program_counter__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__program_counter__set(this, cause, value);}
def_pcfunk2(thread__program_counter__set, x, y, return f2__thread__program_counter__set(this_cause, x, y));

f2ptr f2__thread__stack(f2ptr cause, f2ptr this) {return f2thread__stack(this, cause);}
def_pcfunk1(thread__stack, x, return f2__thread__stack(this_cause, x));

f2ptr f2__thread__stack__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__stack__set(this, cause, value);}
def_pcfunk2(thread__stack__set, x, y, return f2__thread__stack__set(this_cause, x, y));

f2ptr f2__thread__iter(f2ptr cause, f2ptr this) {return f2thread__iter(this, cause);}
def_pcfunk1(thread__iter, x, return f2__thread__iter(this_cause, x));

f2ptr f2__thread__iter__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__iter__set(this, cause, value);}
def_pcfunk2(thread__iter__set, x, y, return f2__thread__iter__set(this_cause, x, y));

f2ptr f2__thread__env(f2ptr cause, f2ptr this) {return f2thread__env(this, cause);}
def_pcfunk1(thread__env, x, return f2__thread__env(this_cause, x));

f2ptr f2__thread__env__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__env__set(this, cause, value);}
def_pcfunk2(thread__env__set, x, y, return f2__thread__env__set(this_cause, x, y));

f2ptr f2__thread__args(f2ptr cause, f2ptr this) {return f2thread__args(this, cause);}
def_pcfunk1(thread__args, x, return f2__thread__args(this_cause, x));

f2ptr f2__thread__args__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__args__set(this, cause, value);}
def_pcfunk2(thread__args__set, x, y, return f2__thread__args__set(this_cause, x, y));

f2ptr f2__thread__return(f2ptr cause, f2ptr this) {return f2thread__return(this, cause);}
def_pcfunk1(thread__return, x, return f2__thread__return(this_cause, x));

f2ptr f2__thread__return__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__return__set(this, cause, value);}
def_pcfunk2(thread__return__set, x, y, return f2__thread__return__set(this_cause, x, y));

f2ptr f2__thread__value(f2ptr cause, f2ptr this) {return f2thread__value(this, cause);}
def_pcfunk1(thread__value, x, return f2__thread__value(this_cause, x));

f2ptr f2__thread__value__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__value__set(this, cause, value);}
def_pcfunk2(thread__value__set, x, y, return f2__thread__value__set(this_cause, x, y));

f2ptr f2__thread__trace(f2ptr cause, f2ptr this) {return f2thread__trace(this, cause);}
def_pcfunk1(thread__trace, x, return f2__thread__trace(this_cause, x));

f2ptr f2__thread__trace__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__trace__set(this, cause, value);}
def_pcfunk2(thread__trace__set, x, y, return f2__thread__trace__set(this_cause, x, y));

f2ptr f2__thread__critics(f2ptr cause, f2ptr this) {return f2thread__critics(this, cause);}
def_pcfunk1(thread__critics, x, return f2__thread__critics(this_cause, x));

f2ptr f2__thread__critics__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__critics__set(this, cause, value);}
def_pcfunk2(thread__critics__set, x, y, return f2__thread__critics__set(this_cause, x, y));

f2ptr f2__thread__cause_reg(f2ptr cause, f2ptr this) {return f2thread__cause_reg(this, cause);}
def_pcfunk1(thread__cause_reg, x, return f2__thread__cause_reg(this_cause, x));

f2ptr f2__thread__cause_reg__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__cause_reg__set(this, cause, value);}
def_pcfunk2(thread__cause_reg__set, x, y, return f2__thread__cause_reg__set(this_cause, x, y));

f2ptr f2__thread__keep_undead(f2ptr cause, f2ptr this) {return f2thread__keep_undead(this, cause);}
def_pcfunk1(thread__keep_undead, x, return f2__thread__keep_undead(this_cause, x));

f2ptr f2__thread__keep_undead__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__keep_undead__set(this, cause, value);}
def_pcfunk2(thread__keep_undead__set, x, y, return f2__thread__keep_undead__set(this_cause, x, y));

f2ptr f2__thread__is_zombie(f2ptr cause, f2ptr this) {return f2thread__is_zombie(this, cause);}
def_pcfunk1(thread__is_zombie, x, return f2__thread__is_zombie(this_cause, x));

f2ptr f2__thread__is_zombie__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__is_zombie__set(this, cause, value);}
def_pcfunk2(thread__is_zombie__set, x, y, return f2__thread__is_zombie__set(this_cause, x, y));

f2ptr f2__thread__parent_thread(f2ptr cause, f2ptr this) {return f2thread__parent_thread(this, cause);}
def_pcfunk1(thread__parent_thread, x, return f2__thread__parent_thread(this_cause, x));

f2ptr f2__thread__parent_thread__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__parent_thread__set(this, cause, value);}
def_pcfunk2(thread__parent_thread__set, x, y, return f2__thread__parent_thread__set(this_cause, x, y));

f2ptr f2__thread__parent_env(f2ptr cause, f2ptr this) {return f2thread__parent_env(this, cause);}
def_pcfunk1(thread__parent_env, x, return f2__thread__parent_env(this_cause, x));

f2ptr f2__thread__parent_env__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__parent_env__set(this, cause, value);}
def_pcfunk2(thread__parent_env__set, x, y, return f2__thread__parent_env__set(this_cause, x, y));

f2ptr f2__thread__execute_mutex(f2ptr cause, f2ptr this) {return f2thread__execute_mutex(this, cause);}
def_pcfunk1(thread__execute_mutex, x, return f2__thread__execute_mutex(this_cause, x));

f2ptr f2__thread__execute_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__execute_mutex__set(this, cause, value);}
def_pcfunk2(thread__execute_mutex__set, x, y, return f2__thread__execute_mutex__set(this_cause, x, y));

f2ptr f2__thread__paused(f2ptr cause, f2ptr this) {return f2thread__paused(this, cause);}
def_pcfunk1(thread__paused, x, return f2__thread__paused(this_cause, x));

f2ptr f2__thread__paused__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__paused__set(this, cause, value);}
def_pcfunk2(thread__paused__set, x, y, return f2__thread__paused__set(this_cause, x, y));

f2ptr f2__thread__last_executed_time(f2ptr cause, f2ptr this) {return f2thread__last_executed_time(this, cause);}
def_pcfunk1(thread__last_executed_time, x, return f2__thread__last_executed_time(this_cause, x));

f2ptr f2__thread__last_executed_time__set(f2ptr cause, f2ptr this, f2ptr value) {return f2thread__last_executed_time__set(this, cause, value);}
def_pcfunk2(thread__last_executed_time__set, x, y, return f2__thread__last_executed_time__set(this_cause, x, y));




// processor

defprimobject__static_slot(processor__scheduler,              0);
defprimobject__static_slot(processor__processor_thread,       1);
defprimobject__static_slot(processor__active_threads_mutex,   2);
defprimobject__static_slot(processor__active_threads,         3);
defprimobject__static_slot(processor__sleeping_threads_mutex, 4);
defprimobject__static_slot(processor__sleeping_threads,       5);
defprimobject__static_slot(processor__pool_index,             6);
defprimobject__static_slot(processor__desc,                   7);

f2ptr __processor__symbol = -1;

f2ptr f2processor__new(f2ptr cause, f2ptr scheduler, f2ptr processor_thread, f2ptr active_threads_mutex, f2ptr active_threads, f2ptr sleeping_threads_mutex, f2ptr sleeping_threads, f2ptr pool_index, f2ptr desc) {
  release__assert(__processor__symbol != -1, nil, "f2processor__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __processor__symbol, 8, nil);
  f2processor__scheduler__set(             this, cause, scheduler);
  f2processor__processor_thread__set(      this, cause, processor_thread);
  f2processor__active_threads_mutex__set(  this, cause, active_threads_mutex);
  f2processor__active_threads__set(        this, cause, active_threads);
  f2processor__sleeping_threads_mutex__set(this, cause, sleeping_threads_mutex);
  f2processor__sleeping_threads__set(      this, cause, sleeping_threads);
  f2processor__pool_index__set(            this, cause, pool_index);
  f2processor__desc__set(                  this, cause, desc);
  return this;
}

f2ptr f2processor__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_processor.is_type__funk);}
  //{char* slot_name = "new";                    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_processor.new__funk);}
  {char* slot_name = "scheduler";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.scheduler__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.scheduler__set__funk, nil);}
  {char* slot_name = "processor_thread";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.processor_thread__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.processor_thread__set__funk, nil);}
  {char* slot_name = "active_threads_mutex";   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads_mutex__set__funk, nil);}
  {char* slot_name = "active_threads";         f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads__set__funk, nil);}
  {char* slot_name = "sleeping_threads_mutex"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads_mutex__set__funk, nil);}
  {char* slot_name = "sleeping_threads";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads__set__funk, nil);}
  {char* slot_name = "pool_index";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.pool_index__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.pool_index__set__funk, nil);}
  {char* slot_name = "desc";                   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_processor.desc__funk, __funk2.globalenv.object_type.primobject.primobject_type_processor.desc__set__funk, nil);}
  return this;
}

boolean_t raw__processor__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_processor(x, cause));
}
f2ptr f2__processor__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__processor__is_type(cause, x));}
def_pcfunk1(processor__is_type, x, return f2__processor__is_type(this_cause, x));

f2ptr f2__processor__scheduler(f2ptr cause, f2ptr this) {return f2processor__scheduler(this, cause);}
def_pcfunk1(processor__scheduler, x, return f2__processor__scheduler(this_cause, x));

f2ptr f2__processor__scheduler__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__scheduler__set(this, cause, value);}
def_pcfunk2(processor__scheduler__set, x, y, return f2__processor__scheduler__set(this_cause, x, y));

f2ptr f2__processor__processor_thread(f2ptr cause, f2ptr this) {return f2processor__processor_thread(this, cause);}
def_pcfunk1(processor__processor_thread, x, return f2__processor__processor_thread(this_cause, x));

f2ptr f2__processor__processor_thread__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__processor_thread__set(this, cause, value);}
def_pcfunk2(processor__processor_thread__set, x, y, return f2__processor__processor_thread__set(this_cause, x, y));

f2ptr f2__processor__active_threads_mutex(f2ptr cause, f2ptr this) {return f2processor__active_threads_mutex(this, cause);}
def_pcfunk1(processor__active_threads_mutex, x, return f2__processor__active_threads_mutex(this_cause, x));

f2ptr f2__processor__active_threads_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__active_threads_mutex__set(this, cause, value);}
def_pcfunk2(processor__active_threads_mutex__set, x, y, return f2__processor__active_threads_mutex__set(this_cause, x, y));

f2ptr f2__processor__active_threads(f2ptr cause, f2ptr this) {return f2processor__active_threads(this, cause);}
def_pcfunk1(processor__active_threads, x, return f2__processor__active_threads(this_cause, x));

f2ptr f2__processor__active_threads__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__active_threads__set(this, cause, value);}
def_pcfunk2(processor__active_threads__set, x, y, return f2__processor__active_threads__set(this_cause, x, y));

f2ptr f2__processor__sleeping_threads_mutex(f2ptr cause, f2ptr this) {return f2processor__sleeping_threads_mutex(this, cause);}
def_pcfunk1(processor__sleeping_threads_mutex, x, return f2__processor__sleeping_threads_mutex(this_cause, x));

f2ptr f2__processor__sleeping_threads_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__sleeping_threads_mutex__set(this, cause, value);}
def_pcfunk2(processor__sleeping_threads_mutex__set, x, y, return f2__processor__sleeping_threads_mutex__set(this_cause, x, y));

f2ptr f2__processor__sleeping_threads(f2ptr cause, f2ptr this) {return f2processor__sleeping_threads(this, cause);}
def_pcfunk1(processor__sleeping_threads, x, return f2__processor__sleeping_threads(this_cause, x));

f2ptr f2__processor__sleeping_threads__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__sleeping_threads__set(this, cause, value);}
def_pcfunk2(processor__sleeping_threads__set, x, y, return f2__processor__sleeping_threads__set(this_cause, x, y));

f2ptr f2__processor__pool_index(f2ptr cause, f2ptr this) {return f2processor__pool_index(this, cause);}
def_pcfunk1(processor__pool_index, x, return f2__processor__pool_index(this_cause, x));

f2ptr f2__processor__pool_index__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__pool_index__set(this, cause, value);}
def_pcfunk2(processor__pool_index__set, x, y, return f2__processor__pool_index__set(this_cause, x, y));

f2ptr f2__processor__desc(f2ptr cause, f2ptr this) {return f2processor__desc(this, cause);}
def_pcfunk1(processor__desc, x, return f2__processor__desc(this_cause, x));

f2ptr f2__processor__desc__set(f2ptr cause, f2ptr this, f2ptr value) {return f2processor__desc__set(this, cause, value);}
def_pcfunk2(processor__desc__set, x, y, return f2__processor__desc__set(this_cause, x, y));



// scheduler

defprimobject__static_slot(scheduler__processors,              0);
defprimobject__static_slot(scheduler__event_subscribers_mutex, 1);
defprimobject__static_slot(scheduler__event_subscribers,       2);
defprimobject__static_slot(scheduler__event_buffer_mutex,      3);
defprimobject__static_slot(scheduler__event_buffer,            4);

f2ptr __scheduler__symbol = -1;

f2ptr f2scheduler__new(f2ptr cause, f2ptr processors, f2ptr event_subscribers_mutex, f2ptr event_subscribers, f2ptr event_buffer_mutex, f2ptr event_buffer) {
  release__assert(__scheduler__symbol != -1, nil, "f2scheduler__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __scheduler__symbol, 5, nil);
  f2scheduler__processors__set(             this, cause, processors);
  f2scheduler__event_subscribers_mutex__set(this, cause, event_subscribers_mutex);
  f2scheduler__event_subscribers__set(      this, cause, event_subscribers);
  f2scheduler__event_buffer_mutex__set(     this, cause, event_buffer_mutex);
  f2scheduler__event_buffer__set(           this, cause, event_buffer);
  return this;
}

f2ptr f2scheduler__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";                 f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.is_type__funk);}
  {char* slot_name = "new";                     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.new__funk);}
  {char* slot_name = "processors";              f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processors__funk, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processors__set__funk, nil);}
  {char* slot_name = "event_subscribers_mutex"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers_mutex__set__funk, nil);}
  {char* slot_name = "event_subscribers";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers__funk, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers__set__funk, nil);}
  {char* slot_name = "event_buffer_mutex";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer_mutex__set__funk, nil);}
  {char* slot_name = "event_buffer";            f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer__funk, __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer__set__funk, nil);}
  return this;
}

boolean_t raw__scheduler__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_scheduler(x, cause));
}
f2ptr f2__scheduler__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__scheduler__is_type(cause, x));}
def_pcfunk1(scheduler__is_type, x, return f2__scheduler__is_type(this_cause, x));

f2ptr f2__scheduler__new(f2ptr cause, f2ptr processors, f2ptr event_subscribers_mutex, f2ptr event_subscribers, f2ptr event_buffer_mutex, f2ptr event_buffer) {return f2scheduler__new(cause, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);}
def_pcfunk5(scheduler__new, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer, return f2__scheduler__new(this_cause, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer));

f2ptr f2__scheduler__processors(f2ptr cause, f2ptr this) {return f2scheduler__processors(this, cause);}
def_pcfunk1(scheduler__processors, x, return f2__scheduler__processors(this_cause, x));

f2ptr f2__scheduler__processors__set(f2ptr cause, f2ptr this, f2ptr value) {return f2scheduler__processors__set(this, cause, value);}
def_pcfunk2(scheduler__processors__set, x, y, return f2__scheduler__processors__set(this_cause, x, y));

f2ptr f2__scheduler__event_subscribers_mutex(f2ptr cause, f2ptr this) {return f2scheduler__event_subscribers_mutex(this, cause);}
def_pcfunk1(scheduler__event_subscribers_mutex, x, return f2__scheduler__event_subscribers_mutex(this_cause, x));

f2ptr f2__scheduler__event_subscribers_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2scheduler__event_subscribers_mutex__set(this, cause, value);}
def_pcfunk2(scheduler__event_subscribers_mutex__set, x, y, return f2__scheduler__event_subscribers_mutex__set(this_cause, x, y));

f2ptr f2__scheduler__event_subscribers(f2ptr cause, f2ptr this) {return f2scheduler__event_subscribers(this, cause);}
def_pcfunk1(scheduler__event_subscribers, x, return f2__scheduler__event_subscribers(this_cause, x));

f2ptr f2__scheduler__event_subscribers__set(f2ptr cause, f2ptr this, f2ptr value) {return f2scheduler__event_subscribers__set(this, cause, value);}
def_pcfunk2(scheduler__event_subscribers__set, x, y, return f2__scheduler__event_subscribers__set(this_cause, x, y));

f2ptr f2__scheduler__event_buffer_mutex(f2ptr cause, f2ptr this) {return f2scheduler__event_buffer_mutex(this, cause);}
def_pcfunk1(scheduler__event_buffer_mutex, x, return f2__scheduler__event_buffer_mutex(this_cause, x));

f2ptr f2__scheduler__event_buffer_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2scheduler__event_buffer_mutex__set(this, cause, value);}
def_pcfunk2(scheduler__event_buffer_mutex__set, x, y, return f2__scheduler__event_buffer_mutex__set(this_cause, x, y));

f2ptr f2__scheduler__event_buffer(f2ptr cause, f2ptr this) {return f2scheduler__event_buffer(this, cause);}
def_pcfunk1(scheduler__event_buffer, x, return f2__scheduler__event_buffer(this_cause, x));

f2ptr f2__scheduler__event_buffer__set(f2ptr cause, f2ptr this, f2ptr value) {return f2scheduler__event_buffer__set(this, cause, value);}
def_pcfunk2(scheduler__event_buffer__set, x, y, return f2__scheduler__event_buffer__set(this_cause, x, y));


// event_subscriber

defprimobject__static_slot(event_subscriber__event_types,        0);
defprimobject__static_slot(event_subscriber__thread,             1);
defprimobject__static_slot(event_subscriber__funkable,           2);
defprimobject__static_slot(event_subscriber__event_buffer,       3);
defprimobject__static_slot(event_subscriber__event_buffer_mutex, 4);

f2ptr __event_subscriber__symbol = -1;

f2ptr f2event_subscriber__new(f2ptr cause, f2ptr event_types, f2ptr thread, f2ptr funkable, f2ptr event_buffer, f2ptr event_buffer_mutex) {
  release__assert(__event_subscriber__symbol != -1, nil, "f2event_subscriber__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __event_subscriber__symbol, 5, nil);
  f2event_subscriber__event_types__set(       this, cause, event_types);
  f2event_subscriber__thread__set(            this, cause, thread);
  f2event_subscriber__funkable__set(          this, cause, funkable);
  f2event_subscriber__event_buffer__set(      this, cause, event_buffer);
  f2event_subscriber__event_buffer_mutex__set(this, cause, event_buffer_mutex);
  return this;
}

f2ptr f2event_subscriber__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";            f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.is_type__funk);}
  {char* slot_name = "new";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.new__funk);}
  {char* slot_name = "event_types";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_types__funk, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_types__set__funk, nil);}
  {char* slot_name = "thread";             f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.thread__funk, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.thread__set__funk, nil);}
  {char* slot_name = "funkable";           f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.funkable__funk, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.funkable__set__funk, nil);}
  {char* slot_name = "event_buffer";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer__funk, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer__set__funk, nil);}
  {char* slot_name = "event_buffer_mutex"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									 __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer_mutex__set__funk, nil);}
  return this;
}

boolean_t raw__event_subscriber__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__event_subscriber(x, cause));
}
f2ptr f2__event_subscriber__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__event_subscriber__is_type(cause, x));}
def_pcfunk1(event_subscriber__is_type, x, return f2__event_subscriber__is_type(this_cause, x));

f2ptr f2__event_subscriber__new(f2ptr cause, f2ptr event_types, f2ptr thread, f2ptr funkable, f2ptr event_buffer, f2ptr event_buffer_mutex) {return f2event_subscriber__new(cause, event_types, thread, funkable, event_buffer, event_buffer_mutex);}
def_pcfunk5(event_subscriber__new, event_types, thread, funkable, event_buffer, event_buffer_mutex, return f2__event_subscriber__new(this_cause, event_types, thread, funkable, event_buffer, event_buffer_mutex));

f2ptr f2__event_subscriber__event_types(f2ptr cause, f2ptr this) {return f2event_subscriber__event_types(this, cause);}
def_pcfunk1(event_subscriber__event_types, x, return f2__event_subscriber__event_types(this_cause, x));

f2ptr f2__event_subscriber__event_types__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event_subscriber__event_types__set(this, cause, value);}
def_pcfunk2(event_subscriber__event_types__set, x, y, return f2__event_subscriber__event_types__set(this_cause, x, y));

f2ptr f2__event_subscriber__thread(f2ptr cause, f2ptr this) {return f2event_subscriber__thread(this, cause);}
def_pcfunk1(event_subscriber__thread, x, return f2__event_subscriber__thread(this_cause, x));

f2ptr f2__event_subscriber__thread__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event_subscriber__thread__set(this, cause, value);}
def_pcfunk2(event_subscriber__thread__set, x, y, return f2__event_subscriber__thread__set(this_cause, x, y));

f2ptr f2__event_subscriber__funkable(f2ptr cause, f2ptr this) {return f2event_subscriber__funkable(this, cause);}
def_pcfunk1(event_subscriber__funkable, x, return f2__event_subscriber__funkable(this_cause, x));

f2ptr f2__event_subscriber__funkable__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event_subscriber__funkable__set(this, cause, value);}
def_pcfunk2(event_subscriber__funkable__set, x, y, return f2__event_subscriber__funkable__set(this_cause, x, y));

f2ptr f2__event_subscriber__event_buffer(f2ptr cause, f2ptr this) {return f2event_subscriber__event_buffer(this, cause);}
def_pcfunk1(event_subscriber__event_buffer, x, return f2__event_subscriber__event_buffer(this_cause, x));

f2ptr f2__event_subscriber__event_buffer__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event_subscriber__event_buffer__set(this, cause, value);}
def_pcfunk2(event_subscriber__event_buffer__set, x, y, return f2__event_subscriber__event_buffer__set(this_cause, x, y));

f2ptr f2__event_subscriber__event_buffer_mutex(f2ptr cause, f2ptr this) {return f2event_subscriber__event_buffer_mutex(this, cause);}
def_pcfunk1(event_subscriber__event_buffer_mutex, x, return f2__event_subscriber__event_buffer_mutex(this_cause, x));

f2ptr f2__event_subscriber__event_buffer_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event_subscriber__event_buffer_mutex__set(this, cause, value);}
def_pcfunk2(event_subscriber__event_buffer_mutex__set, x, y, return f2__event_subscriber__event_buffer_mutex__set(this_cause, x, y));


// cause

defprimobject__static_slot(cause__frame,                   0);
defprimobject__static_slot(cause__allocate_traced_arrays,  1);
defprimobject__static_slot(cause__bytecode_tracing_on,     2);
defprimobject__static_slot(cause__memory_tracing_on,       3);
defprimobject__static_slot(cause__subscribers_mutex,       4);
defprimobject__static_slot(cause__subscribers,             5);
defprimobject__static_slot(cause__imagination_stack,       6);
defprimobject__static_slot(cause__event_buffer_first,      7);
defprimobject__static_slot(cause__event_buffer_last,       8);
defprimobject__static_slot(cause__current_events_mutex,    9);
defprimobject__static_slot(cause__current_events,         10);

f2ptr __cause__symbol = -1;

f2ptr f2cause__new(f2ptr cause, f2ptr frame, f2ptr allocate_traced_arrays, f2ptr bytecode_tracing_on, f2ptr memory_tracing_on, f2ptr subscribers_mutex, f2ptr subscribers, f2ptr imagination_stack, f2ptr event_buffer_first, f2ptr event_buffer_last, f2ptr current_events_mutex, f2ptr current_events) {
  release__assert(__cause__symbol != -1, nil, "f2cause__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __cause__symbol, 11, nil);
  f2cause__frame__set(                 this, cause, frame);
  f2cause__allocate_traced_arrays__set(this, cause, allocate_traced_arrays);
  f2cause__bytecode_tracing_on__set(   this, cause, bytecode_tracing_on);
  f2cause__memory_tracing_on__set(     this, cause, memory_tracing_on);
  f2cause__subscribers_mutex__set(     this, cause, subscribers_mutex);
  f2cause__subscribers__set(           this, cause, subscribers);
  f2cause__imagination_stack__set(     this, cause, imagination_stack);
  f2cause__event_buffer_first__set(    this, cause, event_buffer_first);
  f2cause__event_buffer_last__set(     this, cause, event_buffer_last);
  f2cause__current_events_mutex__set(  this, cause, current_events_mutex);
  f2cause__current_events__set(        this, cause, current_events);
  return this;
}

f2ptr f2cause__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";                f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cause.is_type__funk);}
  {char* slot_name = "new";                    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_cause.new__funk);}
  {char* slot_name = "frame";                  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__set__funk, nil);}
  {char* slot_name = "allocate_traced_arrays"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__set__funk, nil);}
  {char* slot_name = "bytecode_tracing_on";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__set__funk, nil);}
  {char* slot_name = "memory_tracing_on";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__set__funk, nil);}
  {char* slot_name = "subscribers_mutex";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__set__funk, nil);}
  {char* slot_name = "subscribers";            f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__set__funk, nil);}
  {char* slot_name = "imagination_stack";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__set__funk, nil);}
  {char* slot_name = "event_buffer_first";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__set__funk, nil);}
  {char* slot_name = "event_buffer_last";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__set__funk, nil);}
  {char* slot_name = "current_events_mutex";   f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__set__funk, nil);}
  {char* slot_name = "current_events";         f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									     __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__funk, __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__set__funk, nil);}
  return this;
}

boolean_t raw__cause__is_type(f2ptr cause, f2ptr x) {
  return (raw__primobject__is_type(cause, x) && f2primobject__is_cause(x, cause));
}
f2ptr f2__cause__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__cause__is_type(cause, x));}
def_pcfunk1(cause__is_type, x, return f2__cause__is_type(this_cause, x));

f2ptr f2__cause__allocate_traced_arrays(f2ptr cause, f2ptr this) {return f2cause__allocate_traced_arrays(this, cause);}
def_pcfunk1(cause__allocate_traced_arrays, x, return f2__cause__allocate_traced_arrays(this_cause, x));

f2ptr f2__cause__allocate_traced_arrays__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__allocate_traced_arrays__set(this, cause, value);}
def_pcfunk2(cause__allocate_traced_arrays__set, x, y, return f2__cause__allocate_traced_arrays__set(this_cause, x, y));

f2ptr f2__cause__frame(f2ptr cause, f2ptr this) {return f2cause__frame(this, cause);}
def_pcfunk1(cause__frame, x, return f2__cause__frame(this_cause, x));

f2ptr f2__cause__frame__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__frame__set(this, cause, value);}
def_pcfunk2(cause__frame__set, x, y, return f2__cause__frame__set(this_cause, x, y));

f2ptr f2__cause__bytecode_tracing_on(f2ptr cause, f2ptr this) {
  if (this && (! raw__cause__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  return (this ? f2cause__bytecode_tracing_on(this, cause) : nil);
}
def_pcfunk1(cause__bytecode_tracing_on, x, return f2__cause__bytecode_tracing_on(this_cause, x));

f2ptr f2__cause__bytecode_tracing_on__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__bytecode_tracing_on__set(this, cause, value);}
def_pcfunk2(cause__bytecode_tracing_on__set, x, y, return f2__cause__bytecode_tracing_on__set(this_cause, x, y));

f2ptr f2__cause__memory_tracing_on(f2ptr cause, f2ptr this) {return f2cause__memory_tracing_on(this, cause);}
def_pcfunk1(cause__memory_tracing_on, x, return f2__cause__memory_tracing_on(this_cause, x));

f2ptr f2__cause__memory_tracing_on__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__memory_tracing_on__set(this, cause, value);}
def_pcfunk2(cause__memory_tracing_on__set, x, y, return f2__cause__memory_tracing_on__set(this_cause, x, y));

f2ptr f2__cause__subscribers_mutex(f2ptr cause, f2ptr this) {return f2cause__subscribers_mutex(this, cause);}
def_pcfunk1(cause__subscribers_mutex, x, return f2__cause__subscribers_mutex(this_cause, x));

f2ptr f2__cause__subscribers_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__subscribers_mutex__set(this, cause, value);}
def_pcfunk2(cause__subscribers_mutex__set, x, y, return f2__cause__subscribers_mutex__set(this_cause, x, y));

f2ptr f2__cause__subscribers(f2ptr cause, f2ptr this) {return f2cause__subscribers(this, cause);}
def_pcfunk1(cause__subscribers, x, return f2__cause__subscribers(this_cause, x));

f2ptr f2__cause__subscribers__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__subscribers__set(this, cause, value);}
def_pcfunk2(cause__subscribers__set, x, y, return f2__cause__subscribers__set(this_cause, x, y));

f2ptr f2__cause__imagination_stack(f2ptr cause, f2ptr this) {return f2cause__imagination_stack(this, cause);}
def_pcfunk1(cause__imagination_stack, x, return f2__cause__imagination_stack(this_cause, x));

f2ptr f2__cause__imagination_stack__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__imagination_stack__set(this, cause, value);}
def_pcfunk2(cause__imagination_stack__set, x, y, return f2__cause__imagination_stack__set(this_cause, x, y));

f2ptr f2__cause__event_buffer_first(f2ptr cause, f2ptr this) {return f2cause__event_buffer_first(this, cause);}
def_pcfunk1(cause__event_buffer_first, x, return f2__cause__event_buffer_first(this_cause, x));

f2ptr f2__cause__event_buffer_first__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__event_buffer_first__set(this, cause, value);}
def_pcfunk2(cause__event_buffer_first__set, x, y, return f2__cause__event_buffer_first__set(this_cause, x, y));

f2ptr f2__cause__event_buffer_last(f2ptr cause, f2ptr this) {return f2cause__event_buffer_last(this, cause);}
def_pcfunk1(cause__event_buffer_last, x, return f2__cause__event_buffer_last(this_cause, x));

f2ptr f2__cause__event_buffer_last__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__event_buffer_last__set(this, cause, value);}
def_pcfunk2(cause__event_buffer_last__set, x, y, return f2__cause__event_buffer_last__set(this_cause, x, y));

f2ptr f2__cause__current_events_mutex(f2ptr cause, f2ptr this) {return f2cause__current_events_mutex(this, cause);}
def_pcfunk1(cause__current_events_mutex, x, return f2__cause__current_events_mutex(this_cause, x));

f2ptr f2__cause__current_events_mutex__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__current_events_mutex__set(this, cause, value);}
def_pcfunk2(cause__current_events_mutex__set, x, y, return f2__cause__current_events_mutex__set(this_cause, x, y));

f2ptr f2__cause__current_events(f2ptr cause, f2ptr this) {return f2cause__current_events(this, cause);}
def_pcfunk1(cause__current_events, x, return f2__cause__current_events(this_cause, x));

f2ptr f2__cause__current_events__set(f2ptr cause, f2ptr this, f2ptr value) {return f2cause__current_events__set(this, cause, value);}
def_pcfunk2(cause__current_events__set, x, y, return f2__cause__current_events__set(this_cause, x, y));


f2ptr f2__cause__new(f2ptr cause, f2ptr frame, f2ptr allocate_traced_arrays, f2ptr bytecode_tracing_on, f2ptr memory_tracing_on, f2ptr subscribers, f2ptr imagination_name, f2ptr event_buffer_first, f2ptr event_buffer_last, f2ptr current_events) {
  f2ptr subscribers_mutex    = f2mutex__new(cause);
  f2ptr current_events_mutex = f2mutex__new(cause);
  return f2cause__new(cause, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_name, event_buffer_first, event_buffer_last, current_events_mutex, current_events);
}
def_pcfunk0(cause__new, return f2__cause__new(this_cause, nil, nil, nil, nil, nil, nil, nil, nil, nil));

f2ptr f2__cause__new_with_default_properties(f2ptr cause) {
  return f2__cause__new(cause, nil, cause__allocate_traced_arrays__default_value, nil, nil, nil, nil, nil, nil, nil);
}

f2ptr f2__cause__new_default_with_memory_tracing_on(f2ptr cause) {
  f2ptr new_cause = f2__cause__new_with_default_properties(cause);
  f2cause__memory_tracing_on__set(new_cause, cause, __funk2.globalenv.true__symbol);
  return new_cause;
}

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause) {
  f2ptr frame                  = nil;
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
			frame,
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

f2ptr f2__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr type) {
  f2ptr value = frame__lookup_type_var_value(cause, this, type, var, f2symbol__new(cause, strlen("not-defined"), (u8*)"not-defined"));
  return value;
}

// transframe

defprimobject__static_slot(transframe__nanoseconds_since_1970, 0);
defprimobject__static_slot(transframe__symbol_old_news,         1);

f2ptr __transframe__symbol = -1;

f2ptr f2transframe__new__trace_depth(f2ptr cause, f2ptr nanoseconds_since_1970, f2ptr symbol_old_news, int trace_depth) {
  release__assert(__transframe__symbol != -1, nil, "f2transframe__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __transframe__symbol, 2, nil, trace_depth);
  f2transframe__nanoseconds_since_1970__set__trace_depth(this, cause, nanoseconds_since_1970, trace_depth);
  f2transframe__symbol_old_news__set__trace_depth(        this, cause, symbol_old_news,         trace_depth);
  return this;
}

f2ptr f2transframe__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";                 f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_transframe.is_type__funk);}
  {char* slot_name = "new";                     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_transframe.new__funk);}
  {char* slot_name = "nanoseconds_since_1970"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__funk, __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__set__funk, nil);}
  {char* slot_name = "symbol_old_news";         f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									      __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__funk, __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__set__funk, nil);}
  return this;
}

f2ptr f2transframe__new(f2ptr cause, f2ptr nanoseconds_since_1970, f2ptr symbol_old_news) {
  return f2transframe__new__trace_depth(cause, nanoseconds_since_1970, symbol_old_news, 1);
}

boolean_t raw__transframe__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_transframe(x, cause));
}
f2ptr f2__transframe__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__transframe__is_type(cause, x));}
def_pcfunk1(transframe__is_type, x, return f2__transframe__is_type(this_cause, x));

f2ptr f2__transframe__new(f2ptr cause, f2ptr nanoseconds_since_1970, f2ptr symbol_old_news) {return f2transframe__new(cause, nanoseconds_since_1970, symbol_old_news);}
def_pcfunk2(transframe__new, nanoseconds_since_1970, symbol_old_news, return f2__transframe__new(this_cause, nanoseconds_since_1970, symbol_old_news));

f2ptr f2__transframe__nanoseconds_since_1970(f2ptr cause, f2ptr this) {return f2transframe__nanoseconds_since_1970(this, cause);}
def_pcfunk1(transframe__nanoseconds_since_1970, x, return f2__transframe__nanoseconds_since_1970(this_cause, x));

f2ptr f2__transframe__nanoseconds_since_1970__set(f2ptr cause, f2ptr this, f2ptr value) {return f2transframe__nanoseconds_since_1970__set(this, cause, value);}
def_pcfunk2(transframe__nanoseconds_since_1970__set, x, y, return f2__transframe__nanoseconds_since_1970__set(this_cause, x, y));

f2ptr f2__transframe__symbol_old_news(f2ptr cause, f2ptr this) {return f2transframe__symbol_old_news(this, cause);}
def_pcfunk1(transframe__symbol_old_news, x, return f2__transframe__symbol_old_news(this_cause, x));

f2ptr f2__transframe__symbol_old_news__set(f2ptr cause, f2ptr this, f2ptr value) {return f2transframe__symbol_old_news__set(this, cause, value);}
def_pcfunk2(transframe__symbol_old_news__set, x, y, return f2__transframe__symbol_old_news__set(this_cause, x, y));


// bug

defprimobject__static_slot(bug__type, 0);

f2ptr __bug__symbol = -1;

f2ptr f2bug__new(f2ptr cause, f2ptr type) {
  release__assert(__bug__symbol != -1, nil, "f2bug__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __bug__symbol, 1, nil);
  f2bug__type__set(this, cause, type);
  return this;
}

f2ptr f2bug__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_bug.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_bug.new__funk);}
  {char* slot_name = "type";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bug.type__funk, __funk2.globalenv.object_type.primobject.primobject_type_bug.type__set__funk, nil);}
  return this;
}

boolean_t raw__bug__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is_bug(x, cause));
}
f2ptr f2__bug__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__bug__is_type(cause, x));}
def_pcfunk1(bug__is_type, x, return f2__bug__is_type(this_cause, x));

f2ptr f2__bug__new(f2ptr cause, f2ptr type) {return f2bug__new(cause, type);}
def_pcfunk1(bug__new, type, return f2__bug__new(this_cause, type));

f2ptr f2__bug__type(f2ptr cause, f2ptr this) {return f2bug__type(this, cause);}
def_pcfunk1(bug__type, x, return f2__bug__type(this_cause, x));

f2ptr f2__bug__type__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bug__type__set(this, cause, value);}
def_pcfunk2(bug__type__set, x, y, return f2__bug__type__set(this_cause, x, y));


// time

defprimobject__static_slot(time__nanoseconds_since_1970, 0);

f2ptr __time__symbol = -1;

f2ptr f2time__new(f2ptr cause, f2ptr nanoseconds_since_1970) {
  release__assert(__time__symbol != -1, nil, "f2time__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __time__symbol, 1, nil);
  f2time__nanoseconds_since_1970__set(this, cause, nanoseconds_since_1970);
  return this;
}

f2ptr f2time__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_time.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_time.new__funk);}
  {char* slot_name = "nanoseconds_since_1970";    f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__funk, __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__set__funk, nil);}
  return this;
}

boolean_t raw__time__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__time(x, cause));
}
f2ptr f2__time__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__time__is_type(cause, x));}
def_pcfunk1(time__is_type, x, return f2__time__is_type(this_cause, x));

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970) {return f2time__new(cause, nanoseconds_since_1970);}
def_pcfunk1(time__new, nanoseconds_since_1970, return f2__time__new(this_cause, nanoseconds_since_1970));

f2ptr f2__time__nanoseconds_since_1970(f2ptr cause, f2ptr this) {return f2time__nanoseconds_since_1970(this, cause);}
def_pcfunk1(time__nanoseconds_since_1970, x, return f2__time__nanoseconds_since_1970(this_cause, x));

f2ptr f2__time__nanoseconds_since_1970__set(f2ptr cause, f2ptr this, f2ptr value) {return f2time__nanoseconds_since_1970__set(this, cause, value);}
def_pcfunk2(time__nanoseconds_since_1970__set, x, y, return f2__time__nanoseconds_since_1970__set(this_cause, x, y));


// size_2d

defprimobject__static_slot(size_2d__x, 0);
defprimobject__static_slot(size_2d__y, 1);

f2ptr __size_2d__symbol = -1;

f2ptr f2size_2d__new(f2ptr cause, f2ptr x, f2ptr y) {
  release__assert(__size_2d__symbol != -1, nil, "f2size_2d__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __size_2d__symbol, 2, nil);
  f2size_2d__x__set(this, cause, x);
  f2size_2d__y__set(this, cause, y);
  return this;
}

f2ptr f2size_2d__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_size_2d.is_type__funk);}
  {char* slot_name = "new";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_size_2d.new__funk);}
  {char* slot_name = "x";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__funk, __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__set__funk, nil);}
  {char* slot_name = "y";       f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__funk, __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__set__funk, nil);}
  return this;
}

boolean_t raw__size_2d__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__size_2d(x, cause));
}
f2ptr f2__size_2d__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__size_2d__is_type(cause, x));}
def_pcfunk1(size_2d__is_type, x, return f2__size_2d__is_type(this_cause, x));

f2ptr f2__size_2d__new(f2ptr cause, f2ptr x, f2ptr y) {return f2size_2d__new(cause, x, y);}
def_pcfunk2(size_2d__new, x, y, return f2__size_2d__new(this_cause, x, y));

f2ptr f2__size_2d__x(f2ptr cause, f2ptr this) {return f2size_2d__x(this, cause);}
def_pcfunk1(size_2d__x, x, return f2__size_2d__x(this_cause, x));

f2ptr f2__size_2d__x__set(f2ptr cause, f2ptr this, f2ptr value) {return f2size_2d__x__set(this, cause, value);}
def_pcfunk2(size_2d__x__set, x, y, return f2__size_2d__x__set(this_cause, x, y));

f2ptr f2__size_2d__y(f2ptr cause, f2ptr this) {return f2size_2d__y(this, cause);}
def_pcfunk1(size_2d__y, x, return f2__size_2d__y(this_cause, x));

f2ptr f2__size_2d__y__set(f2ptr cause, f2ptr this, f2ptr value) {return f2size_2d__y__set(this, cause, value);}
def_pcfunk2(size_2d__y__set, x, y, return f2__size_2d__y__set(this_cause, x, y));


// event

defprimobject__static_slot(event__node_id,  0);
defprimobject__static_slot(event__event_id, 1);
defprimobject__static_slot(event__type,     2);
defprimobject__static_slot(event__data,     3);

f2ptr __event__symbol = -1;

f2ptr f2event__new__trace_depth(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data, int trace_depth) {
  release__assert(__event__symbol != -1, nil, "f2event__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __event__symbol, 4, nil, trace_depth);
  f2event__node_id__set__trace_depth( this, cause, node_id,  trace_depth);
  f2event__event_id__set__trace_depth(this, cause, event_id, trace_depth);
  f2event__type__set__trace_depth(    this, cause, type,     trace_depth);
  f2event__data__set__trace_depth(    this, cause, data,     trace_depth);
  return this;
}

f2ptr f2event__new(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data) {
  return f2event__new__trace_depth(cause, node_id, event_id, type, data, 1);
}

f2ptr f2event__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_event.is_type__funk);}
  {char* slot_name = "new";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_event.new__funk);}
  {char* slot_name = "node_id";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__funk, __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__set__funk, nil);}
  {char* slot_name = "event_id"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__funk, __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__set__funk, nil);}
  {char* slot_name = "type";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_event.type__funk, __funk2.globalenv.object_type.primobject.primobject_type_event.type__set__funk, nil);}
  {char* slot_name = "data";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.primobject.primobject_type_event.data__funk, __funk2.globalenv.object_type.primobject.primobject_type_event.data__set__funk, nil);}
  return this;
}

boolean_t raw__event__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__event(x, cause));
}
f2ptr f2__event__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__event__is_type(cause, x));}
def_pcfunk1(event__is_type, x, return f2__event__is_type(this_cause, x));

f2ptr f2__event__new(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data) {return f2event__new(cause, node_id, event_id, type, data);}
def_pcfunk4(event__new, node_id, event_id, type, data, return f2__event__new(this_cause, node_id, event_id, type, data));

f2ptr f2__event__node_id(f2ptr cause, f2ptr this) {return f2event__node_id(this, cause);}
def_pcfunk1(event__node_id, x, return f2__event__node_id(this_cause, x));

f2ptr f2__event__node_id__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event__node_id__set(this, cause, value);}
def_pcfunk2(event__node_id__set, x, y, return f2__event__node_id__set(this_cause, x, y));

f2ptr f2__event__event_id(f2ptr cause, f2ptr this) {return f2event__event_id(this, cause);}
def_pcfunk1(event__event_id, x, return f2__event__event_id(this_cause, x));

f2ptr f2__event__event_id__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event__event_id__set(this, cause, value);}
def_pcfunk2(event__event_id__set, x, y, return f2__event__event_id__set(this_cause, x, y));

f2ptr f2__event__type(f2ptr cause, f2ptr this) {return f2event__type(this, cause);}
def_pcfunk1(event__type, x, return f2__event__type(this_cause, x));

f2ptr f2__event__type__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event__type__set(this, cause, value);}
def_pcfunk2(event__type__set, x, y, return f2__event__type__set(this_cause, x, y));

f2ptr f2__event__data(f2ptr cause, f2ptr this) {return f2event__data(this, cause);}
def_pcfunk1(event__data, x, return f2__event__data(this_cause, x));

f2ptr f2__event__data__set(f2ptr cause, f2ptr this, f2ptr value) {return f2event__data__set(this, cause, value);}
def_pcfunk2(event__data__set, x, y, return f2__event__data__set(this_cause, x, y));




// bytecode_event

defprimobject__static_slot(bytecode_event__bytecode, 0);
defprimobject__static_slot(bytecode_event__context,  1);

f2ptr __bytecode_event__symbol = -1;

f2ptr f2bytecode_event__new__trace_depth(f2ptr cause, f2ptr bytecode, f2ptr context, int trace_depth) {
  release__assert(__bytecode_event__symbol != -1, nil, "f2bytecode_event__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __bytecode_event__symbol, 2, nil, trace_depth);
  f2bytecode_event__bytecode__set__trace_depth(this, cause, bytecode, trace_depth);
  f2bytecode_event__context__set__trace_depth( this, cause, context,  trace_depth);
  return this;
}

f2ptr f2bytecode_event__new(f2ptr cause, f2ptr bytecode, f2ptr context) {
  return f2bytecode_event__new__trace_depth(cause, bytecode, context, 1);
}

f2ptr f2bytecode_event__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "is_type";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.is_type__funk);}
  {char* slot_name = "new";      f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.new__funk);}
  {char* slot_name = "bytecode"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
							       __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__funk, __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__set__funk, nil);}
  {char* slot_name = "context";  f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
							       __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__funk, __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__set__funk, nil);}
  return this;
}

boolean_t raw__bytecode_event__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__bytecode_event(x, cause));
}
f2ptr f2__bytecode_event__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__bytecode_event__is_type(cause, x));}
def_pcfunk1(bytecode_event__is_type, x, return f2__bytecode_event__is_type(this_cause, x));

f2ptr f2__bytecode_event__new(f2ptr cause, f2ptr bytecode, f2ptr context) {return f2bytecode_event__new(cause, bytecode, context);}
def_pcfunk2(bytecode_event__new, bytecode, context, return f2__bytecode_event__new(this_cause, bytecode, context));

f2ptr f2__bytecode_event__bytecode(f2ptr cause, f2ptr this) {return f2bytecode_event__bytecode(this, cause);}
def_pcfunk1(bytecode_event__bytecode, x, return f2__bytecode_event__bytecode(this_cause, x));

f2ptr f2__bytecode_event__bytecode__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bytecode_event__bytecode__set(this, cause, value);}
def_pcfunk2(bytecode_event__bytecode__set, x, y, return f2__bytecode_event__bytecode__set(this_cause, x, y));

f2ptr f2__bytecode_event__context(f2ptr cause, f2ptr this) {return f2bytecode_event__context(this, cause);}
def_pcfunk1(bytecode_event__context, x, return f2__bytecode_event__context(this_cause, x));

f2ptr f2__bytecode_event__context__set(f2ptr cause, f2ptr this, f2ptr value) {return f2bytecode_event__context__set(this, cause, value);}
def_pcfunk2(bytecode_event__context__set, x, y, return f2__bytecode_event__context__set(this_cause, x, y));





// **

void f2__primobjects__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __primobject__symbol       = f2symbol__new(cause, strlen("primobject"),       (u8*)"primobject");
  __place__symbol            = f2symbol__new(cause, strlen("place"),            (u8*)"place");
  __cons__symbol             = f2symbol__new(cause, strlen("cons"),             (u8*)"cons");
  __doublelink__symbol       = f2symbol__new(cause, strlen("doublelink"),       (u8*)"doublelink");
  __imagination_link__symbol = f2symbol__new(cause, strlen("imagination_link"), (u8*)"imagination_link");
  __cfunk__symbol            = f2symbol__new(cause, strlen("cfunk"),            (u8*)"cfunk");
  __metrocfunk__symbol       = f2symbol__new(cause, strlen("metrocfunk"),       (u8*)"metrocfunk");
  __funk__symbol             = f2symbol__new(cause, strlen("funk"),             (u8*)"funk");
  __metro__symbol            = f2symbol__new(cause, strlen("metro"),            (u8*)"metro");
  __exception__symbol        = f2symbol__new(cause, strlen("exception"),        (u8*)"exception");
  __bytecode__symbol         = f2symbol__new(cause, strlen("bytecode"),         (u8*)"bytecode");
  __thread__symbol           = f2symbol__new(cause, strlen("thread"),           (u8*)"thread");
  __processor__symbol        = f2symbol__new(cause, strlen("processor"),        (u8*)"processor");
  __scheduler__symbol        = f2symbol__new(cause, strlen("scheduler"),        (u8*)"scheduler");
  __event_subscriber__symbol = f2symbol__new(cause, strlen("event_subscriber"), (u8*)"event_subscriber");
  __cause__symbol            = f2symbol__new(cause, strlen("cause"),            (u8*)"cause");
  __transframe__symbol       = f2symbol__new(cause, strlen("transframe"),       (u8*)"transframe");
  __bug__symbol              = f2symbol__new(cause, strlen("bug"),              (u8*)"bug");
  __time__symbol             = f2symbol__new(cause, strlen("time"),             (u8*)"time");
  __size_2d__symbol          = f2symbol__new(cause, strlen("size_2d"),          (u8*)"size_2d");
  __event__symbol            = f2symbol__new(cause, strlen("event"),            (u8*)"event");
  __bytecode_event__symbol   = f2symbol__new(cause, strlen("bytecode_event"),   (u8*)"bytecode_event");
}

void f2__primobjects__initialize() {
  pause_gc();
  f2__primobjects__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __primobject__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __place__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __cons__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __doublelink__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __imagination_link__symbol, nil);
  environment__add_var_value(cause, global_environment(), __cfunk__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __metrocfunk__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __funk__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __metro__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __exception__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __bytecode__symbol,         nil);
  environment__add_var_value(cause, global_environment(), __thread__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __processor__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __scheduler__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __event_subscriber__symbol, nil);
  environment__add_var_value(cause, global_environment(), __cause__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __transframe__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __bug__symbol,              nil);
  environment__add_var_value(cause, global_environment(), __time__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __size_2d__symbol,          nil);
  environment__add_var_value(cause, global_environment(), __event__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __bytecode_event__symbol,   nil);
  
  // place
  
  
  //f2__funktional_primcfunk__init(placep, "");
  
  //f2__primcfunk__init(place__thing, "");
  //f2__primcfunk__init(place__thing__set, "");
  
  // cons
  
  //f2__funktional_primcfunk__init(consp, "");
  //f2__primcfunk__init(cons, "");
  //f2__primcfunk__init(cons__car, "");
  //f2__primcfunk__init(cons__car__set, "");
  //f2__primcfunk__init(cons__cdr, "");
  //f2__primcfunk__init(cons__cdr__set, "");
  
  // doublelink
  
  //f2__primcfunk__init(doublelink, "");
  //f2__funktional_primcfunk__init(doublelinkp, "");
  //f2__primcfunk__init(doublelink__prev, "");
  //f2__primcfunk__init(doublelink__prev__set, "");
  //f2__primcfunk__init(doublelink__next, "");
  //f2__primcfunk__init(doublelink__next__set, "");
  //f2__primcfunk__init(doublelink__value, "");
  //f2__primcfunk__init(doublelink__value__set, "");
  
  
  // place
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_place.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(place__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_place.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_place.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(place__new, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_place.new__funk = cfunk;}
  {char* symbol_str = "thing"; __funk2.globalenv.object_type.primobject.primobject_type_place.thing__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(place__thing, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_place.thing__funk = cfunk;}
  {char* symbol_str = "thing-set"; __funk2.globalenv.object_type.primobject.primobject_type_place.thing__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(place__thing__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_place.thing__set__funk = cfunk;}
  
  // cons 
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_cons.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cons__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_cons.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cons__new, car, cdr, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.new__funk = cfunk;}
  {char* symbol_str = "car"; __funk2.globalenv.object_type.primobject.primobject_type_cons.car__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cons__car, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.car__funk = cfunk;}
  {char* symbol_str = "car-set"; __funk2.globalenv.object_type.primobject.primobject_type_cons.car__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cons__car__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.car__set__funk = cfunk;}
  {char* symbol_str = "cdr"; __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cons__cdr, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__funk = cfunk;}
  {char* symbol_str = "cdr-set"; __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cons__cdr__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.cdr__set__funk = cfunk;}
  
  // doublelink
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelink__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(doublelink__new, prev, next, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.new__funk = cfunk;}
  {char* symbol_str = "prev"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.prev__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelink__prev, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.prev__funk = cfunk;}
  {char* symbol_str = "prev-set"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.prev__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelink__prev__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.prev__set__funk = cfunk;}
  {char* symbol_str = "next"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.next__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelink__next, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.next__funk = cfunk;}
  {char* symbol_str = "next-set"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.next__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelink__next__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.next__set__funk = cfunk;}
  {char* symbol_str = "value"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(doublelink__value, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.value__funk = cfunk;}
  {char* symbol_str = "value-set"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.value__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelink__value__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.value__set__funk = cfunk;}
  
  // imagination_link
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(imagination_link__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(imagination_link__new, next, name, value, trace, imagination_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.new__funk = cfunk;}
  {char* symbol_str = "next"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.next__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(imagination_link__next, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.next__funk = cfunk;}
  {char* symbol_str = "next-set"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.next__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(imagination_link__next__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.next__set__funk = cfunk;}
  {char* symbol_str = "name"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.name__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(imagination_link__name, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.name__funk = cfunk;}
  {char* symbol_str = "name-set"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.name__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(imagination_link__name__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.name__set__funk = cfunk;}
  {char* symbol_str = "value"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(imagination_link__value, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.value__funk = cfunk;}
  {char* symbol_str = "value-set"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.value__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(imagination_link__value__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.value__set__funk = cfunk;}
  {char* symbol_str = "trace"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.trace__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(imagination_link__trace, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.trace__funk = cfunk;}
  {char* symbol_str = "trace-set"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.trace__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(imagination_link__trace__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.trace__set__funk = cfunk;}
  {char* symbol_str = "imagination_frame"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.imagination_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(imagination_link__imagination_frame, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.imagination_frame__funk = cfunk;}
  {char* symbol_str = "imagination_frame-set"; __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.imagination_frame__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(imagination_link__imagination_frame__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_imagination_link.imagination_frame__set__funk = cfunk;}
  
  // cfunk
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(cfunk__new, name, args, cfunkptr, env, is_funktional, documentation, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.new__funk = cfunk;}
  {char* symbol_str = "name"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.name__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__name, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.name__funk = cfunk;}
  {char* symbol_str = "name-set"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.name__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__name__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.name__set__funk = cfunk;}
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.args__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__args, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.args__funk = cfunk;}
  {char* symbol_str = "args-set"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.args__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__args__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.args__set__funk = cfunk;}
  {char* symbol_str = "cfunkptr"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.cfunkptr__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__cfunkptr, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.cfunkptr__funk = cfunk;}
  {char* symbol_str = "cfunkptr-set"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.cfunkptr__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__cfunkptr__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.cfunkptr__set__funk = cfunk;}
  {char* symbol_str = "env"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.env__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__env, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.env__funk = cfunk;}
  {char* symbol_str = "env-set"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.env__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__env__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.env__set__funk = cfunk;}
  {char* symbol_str = "is_funktional"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_funktional__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__is_funktional, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_funktional__funk = cfunk;}
  {char* symbol_str = "is_funktional-set"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_funktional__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__is_funktional__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.is_funktional__set__funk = cfunk;}
  {char* symbol_str = "documentation"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.documentation__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cfunk__documentation, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.documentation__funk = cfunk;}
  {char* symbol_str = "documentation-set"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.documentation__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__documentation__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.documentation__set__funk = cfunk;}
  
  // metrocfunk
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(metrocfunk__new, name, args, cfunkptr, env, is_funktional, documentation, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.new__funk = cfunk;}
  {char* symbol_str = "name"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.name__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__name, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.name__funk = cfunk;}
  {char* symbol_str = "name-set"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.name__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__name__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.name__set__funk = cfunk;}
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.args__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__args, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.args__funk = cfunk;}
  {char* symbol_str = "args-set"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.args__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__args__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.args__set__funk = cfunk;}
  {char* symbol_str = "cfunkptr"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.cfunkptr__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__cfunkptr, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.cfunkptr__funk = cfunk;}
  {char* symbol_str = "cfunkptr-set"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.cfunkptr__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__cfunkptr__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.cfunkptr__set__funk = cfunk;}
  {char* symbol_str = "env"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.env__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__env, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.env__funk = cfunk;}
  {char* symbol_str = "env-set"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.env__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__env__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.env__set__funk = cfunk;}
  {char* symbol_str = "is_funktional"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_funktional__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__is_funktional, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_funktional__funk = cfunk;}
  {char* symbol_str = "is_funktional-set"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_funktional__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__is_funktional__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.is_funktional__set__funk = cfunk;}
  {char* symbol_str = "documentation"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.documentation__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metrocfunk__documentation, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.documentation__funk = cfunk;}
  {char* symbol_str = "documentation-set"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.documentation__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__documentation__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.documentation__set__funk = cfunk;}
  
  // funk
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_funk.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.is_type__funk = cfunk;}
  //{char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_funk.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  //{f2__primcfunk__init__with_c_cfunk_var(funk__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.new__funk = cfunk;}
  {char* symbol_str = "name"; __funk2.globalenv.object_type.primobject.primobject_type_funk.name__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__name, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.name__funk = cfunk;}
  {char* symbol_str = "name-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.name__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__name__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.name__set__funk = cfunk;}
  {char* symbol_str = "body_bytecodes"; __funk2.globalenv.object_type.primobject.primobject_type_funk.body_bytecodes__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__body_bytecodes, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.body_bytecodes__funk = cfunk;}
  {char* symbol_str = "body_bytecodes-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.body_bytecodes__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__body_bytecodes__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.body_bytecodes__set__funk = cfunk;}
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_funk.args__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__args, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.args__funk = cfunk;}
  {char* symbol_str = "args-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.args__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__args__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.args__set__funk = cfunk;}
  {char* symbol_str = "demetropolized_body"; __funk2.globalenv.object_type.primobject.primobject_type_funk.demetropolized_body__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__demetropolized_body, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.demetropolized_body__funk = cfunk;}
  {char* symbol_str = "demetropolized_body-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.demetropolized_body__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__demetropolized_body__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.demetropolized_body__set__funk = cfunk;}
  {char* symbol_str = "body"; __funk2.globalenv.object_type.primobject.primobject_type_funk.body__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__body, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.body__funk = cfunk;}
  {char* symbol_str = "body-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.body__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__body__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.body__set__funk = cfunk;}
  {char* symbol_str = "env"; __funk2.globalenv.object_type.primobject.primobject_type_funk.env__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__env, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.env__funk = cfunk;}
  {char* symbol_str = "env-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.env__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__env__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.env__set__funk = cfunk;}
  {char* symbol_str = "machine_code"; __funk2.globalenv.object_type.primobject.primobject_type_funk.machine_code__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__machine_code, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.machine_code__funk = cfunk;}
  {char* symbol_str = "machine_code-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.machine_code__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__machine_code__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.machine_code__set__funk = cfunk;}
  {char* symbol_str = "is_funktional"; __funk2.globalenv.object_type.primobject.primobject_type_funk.is_funktional__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__is_funktional, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.is_funktional__funk = cfunk;}
  {char* symbol_str = "is_funktional-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.is_funktional__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__is_funktional__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.is_funktional__set__funk = cfunk;}
  {char* symbol_str = "documentation"; __funk2.globalenv.object_type.primobject.primobject_type_funk.documentation__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__documentation, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.documentation__funk = cfunk;}
  {char* symbol_str = "documentation-set"; __funk2.globalenv.object_type.primobject.primobject_type_funk.documentation__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__documentation__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.documentation__set__funk = cfunk;}
  
  // metro
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_metro.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.is_type__funk = cfunk;}
  //{char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_metro.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  //{f2__primcfunk__init__with_c_cfunk_var(metro__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.new__funk = cfunk;}
  {char* symbol_str = "name"; __funk2.globalenv.object_type.primobject.primobject_type_metro.name__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__name, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.name__funk = cfunk;}
  {char* symbol_str = "name-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.name__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__name__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.name__set__funk = cfunk;}
  {char* symbol_str = "body_bytecodes"; __funk2.globalenv.object_type.primobject.primobject_type_metro.body_bytecodes__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__body_bytecodes, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.body_bytecodes__funk = cfunk;}
  {char* symbol_str = "body_bytecodes-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.body_bytecodes__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__body_bytecodes__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.body_bytecodes__set__funk = cfunk;}
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_metro.args__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__args, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.args__funk = cfunk;}
  {char* symbol_str = "args-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.args__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__args__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.args__set__funk = cfunk;}
  {char* symbol_str = "demetropolized_body"; __funk2.globalenv.object_type.primobject.primobject_type_metro.demetropolized_body__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__demetropolized_body, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.demetropolized_body__funk = cfunk;}
  {char* symbol_str = "demetropolized_body-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.demetropolized_body__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__demetropolized_body__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.demetropolized_body__set__funk = cfunk;}
  {char* symbol_str = "body"; __funk2.globalenv.object_type.primobject.primobject_type_metro.body__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__body, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.body__funk = cfunk;}
  {char* symbol_str = "body-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.body__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__body__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.body__set__funk = cfunk;}
  {char* symbol_str = "env"; __funk2.globalenv.object_type.primobject.primobject_type_metro.env__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__env, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.env__funk = cfunk;}
  {char* symbol_str = "env-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.env__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__env__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.env__set__funk = cfunk;}
  {char* symbol_str = "machine_code"; __funk2.globalenv.object_type.primobject.primobject_type_metro.machine_code__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__machine_code, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.machine_code__funk = cfunk;}
  {char* symbol_str = "machine_code-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.machine_code__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__machine_code__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.machine_code__set__funk = cfunk;}
  {char* symbol_str = "is_funktional"; __funk2.globalenv.object_type.primobject.primobject_type_metro.is_funktional__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__is_funktional, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.is_funktional__funk = cfunk;}
  {char* symbol_str = "is_funktional-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.is_funktional__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__is_funktional__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.is_funktional__set__funk = cfunk;}
  {char* symbol_str = "documentation"; __funk2.globalenv.object_type.primobject.primobject_type_metro.documentation__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(metro__documentation, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.documentation__funk = cfunk;}
  {char* symbol_str = "documentation-set"; __funk2.globalenv.object_type.primobject.primobject_type_metro.documentation__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__documentation__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.documentation__set__funk = cfunk;}
  
  // exception
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_exception.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(exception__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_exception.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(exception__new, tag, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.new__funk = cfunk;}
  {char* symbol_str = "tag"; __funk2.globalenv.object_type.primobject.primobject_type_exception.tag__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(exception__tag, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.tag__funk = cfunk;}
  {char* symbol_str = "tag-set"; __funk2.globalenv.object_type.primobject.primobject_type_exception.tag__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(exception__tag__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.tag__set__funk = cfunk;}
  {char* symbol_str = "value"; __funk2.globalenv.object_type.primobject.primobject_type_exception.value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(exception__value, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.value__funk = cfunk;}
  {char* symbol_str = "value-set"; __funk2.globalenv.object_type.primobject.primobject_type_exception.value__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(exception__value__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.value__set__funk = cfunk;}
  
  // bytecode
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(bytecode__new, command, arg0, arg1, arg2, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.new__funk = cfunk;}
  {char* symbol_str = "command"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.command__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode__command, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.command__funk = cfunk;}
  {char* symbol_str = "command-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.command__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode__command__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.command__set__funk = cfunk;}
  {char* symbol_str = "arg0"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg0__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode__arg0, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg0__funk = cfunk;}
  {char* symbol_str = "arg0-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg0__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode__arg0__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg0__set__funk = cfunk;}
  {char* symbol_str = "arg1"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg1__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode__arg1, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg1__funk = cfunk;}
  {char* symbol_str = "arg1-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg1__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode__arg1__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg1__set__funk = cfunk;}
  {char* symbol_str = "arg2"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg2__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode__arg2, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg2__funk = cfunk;}
  {char* symbol_str = "arg2-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg2__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode__arg2__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.arg2__set__funk = cfunk;}
  
  // thread
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_thread.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.is_type__funk = cfunk;}
  //{char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_thread.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  //{f2__primcfunk__init__with_c_cfunk_var(thread__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.new__funk = cfunk;}
  {char* symbol_str = "program_counter"; __funk2.globalenv.object_type.primobject.primobject_type_thread.program_counter__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__program_counter, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.program_counter__funk = cfunk;}
  {char* symbol_str = "program_counter-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.program_counter__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__program_counter__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.program_counter__set__funk = cfunk;}
  {char* symbol_str = "stack"; __funk2.globalenv.object_type.primobject.primobject_type_thread.stack__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__stack, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.stack__funk = cfunk;}
  {char* symbol_str = "stack-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.stack__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__stack__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.stack__set__funk = cfunk;}
  {char* symbol_str = "iter"; __funk2.globalenv.object_type.primobject.primobject_type_thread.iter__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__iter, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.iter__funk = cfunk;}
  {char* symbol_str = "iter-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.iter__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__iter__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.iter__set__funk = cfunk;}
  {char* symbol_str = "env"; __funk2.globalenv.object_type.primobject.primobject_type_thread.env__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__env, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.env__funk = cfunk;}
  {char* symbol_str = "env-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.env__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__env__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.env__set__funk = cfunk;}
  {char* symbol_str = "args"; __funk2.globalenv.object_type.primobject.primobject_type_thread.args__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__args, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.args__funk = cfunk;}
  {char* symbol_str = "args-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.args__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__args__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.args__set__funk = cfunk;}
  {char* symbol_str = "return"; __funk2.globalenv.object_type.primobject.primobject_type_thread.return__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__return, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.return__funk = cfunk;}
  {char* symbol_str = "return-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.return__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__return__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.return__set__funk = cfunk;}
  {char* symbol_str = "value"; __funk2.globalenv.object_type.primobject.primobject_type_thread.value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__value, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.value__funk = cfunk;}
  {char* symbol_str = "value-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.value__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__value__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.value__set__funk = cfunk;}
  {char* symbol_str = "trace"; __funk2.globalenv.object_type.primobject.primobject_type_thread.trace__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__trace, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.trace__funk = cfunk;}
  {char* symbol_str = "trace-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.trace__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__trace__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.trace__set__funk = cfunk;}
  {char* symbol_str = "critics"; __funk2.globalenv.object_type.primobject.primobject_type_thread.critics__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__critics, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.critics__funk = cfunk;}
  {char* symbol_str = "critics-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.critics__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__critics__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.critics__set__funk = cfunk;}
  {char* symbol_str = "cause_reg"; __funk2.globalenv.object_type.primobject.primobject_type_thread.cause_reg__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__cause_reg, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.cause_reg__funk = cfunk;}
  {char* symbol_str = "cause_reg-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.cause_reg__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__cause_reg__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.cause_reg__set__funk = cfunk;}
  {char* symbol_str = "keep_undead"; __funk2.globalenv.object_type.primobject.primobject_type_thread.keep_undead__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__keep_undead, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.keep_undead__funk = cfunk;}
  {char* symbol_str = "keep_undead-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.keep_undead__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__keep_undead__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.keep_undead__set__funk = cfunk;}
  {char* symbol_str = "is_zombie"; __funk2.globalenv.object_type.primobject.primobject_type_thread.is_zombie__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__is_zombie, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.is_zombie__funk = cfunk;}
  {char* symbol_str = "is_zombie-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.is_zombie__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__is_zombie__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.is_zombie__set__funk = cfunk;}
  {char* symbol_str = "parent_thread"; __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_thread__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__parent_thread, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_thread__funk = cfunk;}
  {char* symbol_str = "parent_thread-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_thread__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__parent_thread__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_thread__set__funk = cfunk;}
  {char* symbol_str = "parent_env"; __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_env__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__parent_env, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_env__funk = cfunk;}
  {char* symbol_str = "parent_env-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_env__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__parent_env__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.parent_env__set__funk = cfunk;}
  {char* symbol_str = "execute_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_thread.execute_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__execute_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.execute_mutex__funk = cfunk;}
  {char* symbol_str = "execute_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.execute_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__execute_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.execute_mutex__set__funk = cfunk;}
  {char* symbol_str = "paused"; __funk2.globalenv.object_type.primobject.primobject_type_thread.paused__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__paused, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.paused__funk = cfunk;}
  {char* symbol_str = "paused-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.paused__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__paused__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.paused__set__funk = cfunk;}
  {char* symbol_str = "last_executed_time"; __funk2.globalenv.object_type.primobject.primobject_type_thread.last_executed_time__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(thread__last_executed_time, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.last_executed_time__funk = cfunk;}
  {char* symbol_str = "last_executed_time-set"; __funk2.globalenv.object_type.primobject.primobject_type_thread.last_executed_time__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(thread__last_executed_time__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_thread.last_executed_time__set__funk = cfunk;}
  
  // processor
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_processor.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.is_type__funk = cfunk;}
  //{char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_processor.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  //{f2__primcfunk__init__with_c_cfunk_var__8_arg(processor__new, scheduler, processor_thread, active_threads_mutex, active_threads, sleeping_threads_mutex, sleeping_threads, pool_index, desc,
  //                                              cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.new__funk = cfunk;}
  {char* symbol_str = "scheduler"; __funk2.globalenv.object_type.primobject.primobject_type_processor.scheduler__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__scheduler, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.scheduler__funk = cfunk;}
  {char* symbol_str = "scheduler-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.scheduler__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__scheduler__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.scheduler__set__funk = cfunk;}
  {char* symbol_str = "processor_thread"; __funk2.globalenv.object_type.primobject.primobject_type_processor.processor_thread__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__processor_thread, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.processor_thread__funk = cfunk;}
  {char* symbol_str = "processor_thread-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.processor_thread__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__processor_thread__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.processor_thread__set__funk = cfunk;}
  {char* symbol_str = "active_threads_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__active_threads_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads_mutex__funk = cfunk;}
  {char* symbol_str = "active_threads_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__active_threads_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads_mutex__set__funk = cfunk;}
  {char* symbol_str = "active_threads"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__active_threads, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads__funk = cfunk;}
  {char* symbol_str = "active_threads-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__active_threads__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.active_threads__set__funk = cfunk;}
  {char* symbol_str = "sleeping_threads_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__sleeping_threads_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads_mutex__funk = cfunk;}
  {char* symbol_str = "sleeping_threads_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__sleeping_threads_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads_mutex__set__funk = cfunk;}
  {char* symbol_str = "sleeping_threads"; __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__sleeping_threads, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads__funk = cfunk;}
  {char* symbol_str = "sleeping_threads-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__sleeping_threads__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.sleeping_threads__set__funk = cfunk;}
  {char* symbol_str = "pool_index"; __funk2.globalenv.object_type.primobject.primobject_type_processor.pool_index__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__pool_index, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.pool_index__funk = cfunk;}
  {char* symbol_str = "pool_index-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.pool_index__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__pool_index__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.pool_index__set__funk = cfunk;}
  {char* symbol_str = "desc"; __funk2.globalenv.object_type.primobject.primobject_type_processor.desc__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(processor__desc, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.desc__funk = cfunk;}
  {char* symbol_str = "desc-set"; __funk2.globalenv.object_type.primobject.primobject_type_processor.desc__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(processor__desc__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_processor.desc__set__funk = cfunk;}
  
  // scheduler
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(scheduler__new, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.new__funk = cfunk;}
  {char* symbol_str = "processors"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processors__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler__processors, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processors__funk = cfunk;}
  {char* symbol_str = "processors-set"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processors__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler__processors__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.processors__set__funk = cfunk;}
  {char* symbol_str = "event_subscribers_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler__event_subscribers_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers_mutex__funk = cfunk;}
  {char* symbol_str = "event_subscribers_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler__event_subscribers_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers_mutex__set__funk = cfunk;}
  {char* symbol_str = "event_subscribers"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler__event_subscribers, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers__funk = cfunk;}
  {char* symbol_str = "event_subscribers-set"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler__event_subscribers__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_subscribers__set__funk = cfunk;}
  {char* symbol_str = "event_buffer_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler__event_buffer_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer_mutex__funk = cfunk;}
  {char* symbol_str = "event_buffer_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler__event_buffer_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer_mutex__set__funk = cfunk;}
  {char* symbol_str = "event_buffer"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(scheduler__event_buffer, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer__funk = cfunk;}
  {char* symbol_str = "event_buffer-set"; __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(scheduler__event_buffer__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_scheduler.event_buffer__set__funk = cfunk;}
  
  // event_subscriber
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event_subscriber__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(event_subscriber__new, event_type, thread, funkable, event_buffer, event_buffer_mutex, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.new__funk = cfunk;}
  {char* symbol_str = "event_type"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_types__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event_subscriber__event_types, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_types__funk = cfunk;}
  {char* symbol_str = "event_type-set"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_types__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event_subscriber__event_types__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_types__set__funk = cfunk;}
  {char* symbol_str = "thread"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.thread__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event_subscriber__thread, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.thread__funk = cfunk;}
  {char* symbol_str = "thread-set"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.thread__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event_subscriber__thread__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.thread__set__funk = cfunk;}
  {char* symbol_str = "funkable"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.funkable__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event_subscriber__funkable, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.funkable__funk = cfunk;}
  {char* symbol_str = "funkable-set"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.funkable__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event_subscriber__funkable__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.funkable__set__funk = cfunk;}
  {char* symbol_str = "event_buffer"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event_subscriber__event_buffer, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer__funk = cfunk;}
  {char* symbol_str = "event_buffer-set"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event_subscriber__event_buffer__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer__set__funk = cfunk;}
  {char* symbol_str = "event_buffer_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event_subscriber__event_buffer_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer_mutex__funk = cfunk;}
  {char* symbol_str = "event_buffer_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event_subscriber__event_buffer_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event_subscriber.event_buffer_mutex__set__funk = cfunk;}
  
  // cause
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_cause.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_cause.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(cause__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.new__funk = cfunk;}
  {char* symbol_str = "frame"; __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__frame, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__funk = cfunk;}
  {char* symbol_str = "frame-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__frame__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.frame__set__funk = cfunk;}
  {char* symbol_str = "allocate_traced_arrays"; __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__allocate_traced_arrays, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__funk = cfunk;}
  {char* symbol_str = "allocate_traced_arrays-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__allocate_traced_arrays__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.allocate_traced_arrays__set__funk = cfunk;}
  {char* symbol_str = "bytecode_tracing_on"; __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__bytecode_tracing_on, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__funk = cfunk;}
  {char* symbol_str = "bytecode_tracing_on-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__bytecode_tracing_on__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.bytecode_tracing_on__set__funk = cfunk;}
  {char* symbol_str = "memory_tracing_on"; __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__memory_tracing_on, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__funk = cfunk;}
  {char* symbol_str = "memory_tracing_on-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__memory_tracing_on__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.memory_tracing_on__set__funk = cfunk;}
  {char* symbol_str = "subscribers_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__subscribers_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__funk = cfunk;}
  {char* symbol_str = "subscribers_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__subscribers_mutex__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers_mutex__set__funk = cfunk;}
  {char* symbol_str = "subscribers"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__subscribers, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__funk = cfunk;}
  {char* symbol_str = "subscribers-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__subscribers__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.subscribers__set__funk = cfunk;}
  {char* symbol_str = "imagination_stack"; __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__imagination_stack, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__funk = cfunk;}
  {char* symbol_str = "imagination_stack-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__imagination_stack__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.imagination_stack__set__funk = cfunk;}
  {char* symbol_str = "event_buffer_first"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__event_buffer_first, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__funk = cfunk;}
  {char* symbol_str = "event_buffer_first-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__event_buffer_first__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_first__set__funk = cfunk;}
  {char* symbol_str = "event_buffer_last"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__event_buffer_last, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__funk = cfunk;}
  {char* symbol_str = "event_buffer_last-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__event_buffer_last__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.event_buffer_last__set__funk = cfunk;}
  {char* symbol_str = "current_events_mutex"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__current_events_mutex, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__funk = cfunk;}
  {char* symbol_str = "current_events_mutex-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__current_events_mutex, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events_mutex__set__funk = cfunk;}
  {char* symbol_str = "current_events"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cause__current_events, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__funk = cfunk;}
  {char* symbol_str = "current_events-set"; __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cause__current_events__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cause.current_events__set__funk = cfunk;}
  
  // transframe
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(transframe__new, nanoseconds_since_1970, symbol_old_news, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.new__funk = cfunk;}
  {char* symbol_str = "nanoseconds_since_1970"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__nanoseconds_since_1970, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__funk = cfunk;}
  {char* symbol_str = "nanoseconds_since_1970-set"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(transframe__nanoseconds_since_1970__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.nanoseconds_since_1970__set__funk = cfunk;}
  {char* symbol_str = "symbol_old_news"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(transframe__symbol_old_news, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__funk = cfunk;}
  {char* symbol_str = "symbol_old_news-set"; __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(transframe__symbol_old_news__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_transframe.symbol_old_news__set__funk = cfunk;}
  
  // bug
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_bug.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_bug.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__new, type, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.new__funk = cfunk;}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_bug.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bug__type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.type__funk = cfunk;}
  {char* symbol_str = "type-set"; __funk2.globalenv.object_type.primobject.primobject_type_bug.type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bug__type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bug.type__set__funk = cfunk;}
  
  // time
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_time.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_time.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__new, type, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.new__funk = cfunk;}
  {char* symbol_str = "nanoseconds_since_1970"; __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(time__nanoseconds_since_1970, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__funk = cfunk;}
  {char* symbol_str = "nanoseconds_since_1970-set"; __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(time__nanoseconds_since_1970__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_time.nanoseconds_since_1970__set__funk = cfunk;}
  
  // size_2d
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(size_2d__new, x, y, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.new__funk = cfunk;}
  {char* symbol_str = "x"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__x, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__funk = cfunk;}
  {char* symbol_str = "x-set"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(size_2d__x__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.x__set__funk = cfunk;}
  {char* symbol_str = "y"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(size_2d__y, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__funk = cfunk;}
  {char* symbol_str = "y-set"; __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(size_2d__y__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_size_2d.y__set__funk = cfunk;}
  
  // event
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_event.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_event.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(event__new, node_id, event_id, type, data, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.new__funk = cfunk;}
  {char* symbol_str = "node_id"; __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__node_id, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__funk = cfunk;}
  {char* symbol_str = "node_id-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__node_id__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.node_id__set__funk = cfunk;}
  {char* symbol_str = "event_id"; __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__event_id, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__funk = cfunk;}
  {char* symbol_str = "event_id-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__event_id__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.event_id__set__funk = cfunk;}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_event.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.type__funk = cfunk;}
  {char* symbol_str = "type-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.type__set__funk = cfunk;}
  {char* symbol_str = "data"; __funk2.globalenv.object_type.primobject.primobject_type_event.data__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(event__data, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.data__funk = cfunk;}
  {char* symbol_str = "data-set"; __funk2.globalenv.object_type.primobject.primobject_type_event.data__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(event__data__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_event.data__set__funk = cfunk;}
  
  // bytecode_event
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.is_type__funk = cfunk;}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode_event__new, bytecode, context, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.new__funk = cfunk;}
  {char* symbol_str = "bytecode"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__bytecode, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__funk = cfunk;}
  {char* symbol_str = "bytecode-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode_event__bytecode__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.bytecode__set__funk = cfunk;}
  {char* symbol_str = "context"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(bytecode_event__context, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__funk = cfunk;}
  {char* symbol_str = "context-set"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode_event__context__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode_event.context__set__funk = cfunk;}
  
  
  
  
  
  
  
  resume_gc();
  try_gc();
}


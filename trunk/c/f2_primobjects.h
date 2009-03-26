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

#ifndef F2__PRIMOBJECTS__H
#define F2__PRIMOBJECTS__H

#define defarray_slot__index_var(name)        array_slot__##name##__index
#define defarray_slot(           name, index)        int defarray_slot__index_var(name) = index
#define defarray_slot__prototype(name)        extern int defarray_slot__index_var(name)

#define array_slot__accessor(        this, name, cause)                     raw__array__elt(                  cause, this, defarray_slot__index_var(name))
#define array_slot__set__trace_depth(this, name, cause, value, trace_depth) raw__array__elt__set__trace_depth(cause, this, defarray_slot__index_var(name), value, trace_depth)
#define array_slot__set(             this, name, cause, value)              raw__array__elt__set(             cause, this, defarray_slot__index_var(name), value)
#define array_slot__tracing_on(      this, name, cause)                     raw__array__elt__tracing_on(      cause, this, defarray_slot__index_var(name))
#define array_slot__trace(           this, name, cause)                     raw__array__elt__trace(           cause, this, defarray_slot__index_var(name))
#define array_slot__imagination_frame(           this, name, cause)                     raw__array__elt__imagination_frame(           cause, this, defarray_slot__index_var(name))

#define primobject__header_size 3
defarray_slot__prototype(primobject__primobject_label);
#define f2primobject__primobject_label(                  this, cause)                     array_slot__accessor(        this, primobject__primobject_label, cause)
#define f2primobject__primobject_label__set__trace_depth(this, cause, value, trace_depth) array_slot__set__trace_depth(this, primobject__primobject_label, cause, value, trace_depth)
#define f2primobject__primobject_label__set(             this, cause, value)              array_slot__set(             this, primobject__primobject_label, cause, value)
#define f2primobject__primobject_label__tracing_on(      this, cause)                     array_slot__tracing_on(      this, primobject__primobject_label, cause)
#define f2primobject__primobject_label__trace(           this, cause)                     array_slot__trace(           this, primobject__primobject_label, cause)
#define f2primobject__primobject_label__imagination_frame(           this, cause)                     array_slot__imagination_frame(           this, primobject__primobject_label, cause)

defarray_slot__prototype(primobject__type);
#define f2primobject__type(                  this, cause)                     array_slot__accessor(        this, primobject__type, cause)
#define f2primobject__type__set__trace_depth(this, cause, value, trace_depth) array_slot__set__trace_depth(this, primobject__type, cause, value, trace_depth)
#define f2primobject__type__set(             this, cause, value)              array_slot__set(             this, primobject__type, cause, value)
#define f2primobject__type__tracing_on(      this, cause)                     array_slot__tracing_on(      this, primobject__type, cause)
#define f2primobject__type__trace(           this, cause)                     array_slot__trace(           this, primobject__type, cause)
#define f2primobject__type__imagination_frame(           this, cause)                     array_slot__imagination_frame(           this, primobject__type, cause)

defarray_slot__prototype(primobject__dynamic_slots);
#define f2primobject__dynamic_slots(                  this, cause)                     array_slot__accessor(        this, primobject__dynamic_slots, cause)
#define f2primobject__dynamic_slots__set__trace_depth(this, cause, value, trace_depth) array_slot__set__trace_depth(this, primobject__dynamic_slots, cause, value, trace_depth)
#define f2primobject__dynamic_slots__set(             this, cause, value)              array_slot__set(             this, primobject__dynamic_slots, cause, value)
#define f2primobject__dynamic_slots__tracing_on(      this, cause)                     array_slot__tracing_on(      this, primobject__dynamic_slots, cause)
#define f2primobject__dynamic_slots__trace(           this, cause)                     array_slot__trace(           this, primobject__dynamic_slots, cause)
#define f2primobject__dynamic_slots__imagination_frame(           this, cause)                     array_slot__imagination_frame(           this, primobject__dynamic_slots, cause)

#define defprimobject__static_slot(           name, index) defarray_slot(           name, primobject__header_size + index)
#define defprimobject__static_slot__prototype(name)        defarray_slot__prototype(name)

#define primobject__static_slot__accessor(        this, name, cause)                     array_slot__accessor(        this, name, cause)
#define primobject__static_slot__set__trace_depth(this, name, cause, value, trace_depth) array_slot__set__trace_depth(this, name, cause, value, trace_depth)
#define primobject__static_slot__set(             this, name, cause, value)              array_slot__set(             this, name, cause, value)
#define primobject__static_slot__tracing_on(      this, name, cause)                     array_slot__tracing_on(      this, name, cause)
#define primobject__static_slot__trace(           this, name, cause)                     array_slot__trace(           this, name, cause)
#define primobject__static_slot__imagination_frame(           this, name, cause)                     array_slot__imagination_frame(           this, name, cause)

#define raw__primobjectp(exp, cause) (raw__arrayp(exp, cause) && (raw__array__length(cause, exp) > defarray_slot__index_var(primobject__primobject_label)) && (raw__eq(cause, f2primobject__primobject_label(exp, cause), __primobject__symbol)))

#include "f2_memory.h"
#include "f2_ptypes.h"

// header size is measured in array slots

extern f2ptr __primobject__symbol;

extern f2ptr f2__primobject__new(             f2ptr cause, f2ptr type, int   static_slot_num, f2ptr dynamic_slots);
extern f2ptr f2__primobject__new__trace_depth(f2ptr cause, f2ptr type, int   static_slot_num, f2ptr dynamic_slots, int trace_depth);
extern f2ptr   f2primobject__new(             f2ptr cause, f2ptr type, f2ptr static_slot_num, f2ptr dynamic_slots);

// place

extern f2ptr __place__symbol;
extern f2ptr f2place__new(f2ptr cause, f2ptr thing);

#define f2primobject__is_place(this, cause)      raw__eq(cause, f2primobject__type(this, cause), __place__symbol)

defprimobject__static_slot__prototype(place__thing);
#define f2place__thing(this, cause)              primobject__static_slot__accessor(  this, place__thing, cause)
#define f2place__thing__set(this, cause, value)  primobject__static_slot__set(       this, place__thing, cause, value)
#define f2place__thing__tracing_on(this, cause)  primobject__static_slot__tracing_on(this, place__thing, cause)
#define f2place__thing__trace(this, cause)       primobject__static_slot__trace(     this, place__thing, cause)
#define f2place__thing__imagination_frame(this, cause)       primobject__static_slot__imagination_frame(     this, place__thing, cause)


// cons

extern f2ptr __cons__symbol;
extern f2ptr f2cons__new__trace_depth(f2ptr cause, f2ptr car, f2ptr cdr, int trace_depth);
extern f2ptr f2cons__new(f2ptr cause, f2ptr car, f2ptr cdr);

#define f2primobject__is_cons(this, cause) raw__eq(cause, f2primobject__type(this, cause), __cons__symbol)

defprimobject__static_slot__prototype(cons__car);
#define f2cons__car(                   this, cause)                     primobject__static_slot__accessor(         this, cons__car, cause)
#define f2cons__car__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, cons__car, cause, value, trace_depth)
#define f2cons__car__set(              this, cause, value)              primobject__static_slot__set(              this, cons__car, cause, value)
#define f2cons__car__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, cons__car, cause)
#define f2cons__car__trace(            this, cause)                     primobject__static_slot__trace(            this, cons__car, cause)
#define f2cons__car__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, cons__car, cause)

defprimobject__static_slot__prototype(cons__cdr);
#define f2cons__cdr(                   this, cause)                     primobject__static_slot__accessor(         this, cons__cdr, cause)
#define f2cons__cdr__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, cons__cdr, cause, value, trace_depth)
#define f2cons__cdr__set(              this, cause, value)              primobject__static_slot__set(              this, cons__cdr, cause, value)
#define f2cons__cdr__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, cons__cdr, cause)
#define f2cons__cdr__trace(            this, cause)                     primobject__static_slot__trace(            this, cons__cdr, cause)
#define f2cons__cdr__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, cons__cdr, cause)


// deprecated cons macros

#define f2list1__new(cause, elt0)                                                 f2cons__new(cause, elt0, nil)
#define f2list2__new(cause, elt0, elt1)                                           f2cons__new(cause, elt0, f2cons__new(cause, elt1, nil))
#define f2list3__new(cause, elt0, elt1, elt2)                                     f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, nil)))
#define f2list4__new(cause, elt0, elt1, elt2, elt3)                               f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, nil))))
#define f2list5__new(cause, elt0, elt1, elt2, elt3, elt4)                         f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, nil)))))
#define f2list6__new(cause, elt0, elt1, elt2, elt3, elt4, elt5)                   f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, nil))))))
#define f2list7__new(cause, elt0, elt1, elt2, elt3, elt4, elt5, elt6)             f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, f2cons__new(cause, elt6, nil)))))))
#define f2list8__new(cause, elt0, elt1, elt2, elt3, elt4, elt5, elt6, elt7)       f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, f2cons__new(cause, elt6, f2cons__new(cause, elt7, nil))))))))
#define f2list9__new(cause, elt0, elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8) f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, f2cons__new(cause, elt6, f2cons__new(cause, elt7, f2cons__new(cause, elt8, nil)))))))))

#define f2list__elt_0(     this, cause)        f2cons__car(                                                     this, cause)
#define f2list__elt_0__set(this, cause, value) f2cons__car__set(                                                this, cause,                                        value)
#define f2list__elt_1(     this, cause)        f2cons__car(                                         f2cons__cdr(this, cause), cause)
#define f2list__elt_1__set(this, cause, value) f2cons__car__set(                                    f2cons__cdr(this, cause), cause,                                value)
#define f2list__elt_2(     this, cause)        f2cons__car(                             f2cons__cdr(f2cons__cdr(this, cause), cause), cause)
#define f2list__elt_2__set(this, cause, value) f2cons__car__set(                        f2cons__cdr(f2cons__cdr(this, cause), cause), cause,                        value)
#define f2list__elt_3(     this, cause)        f2cons__car(                 f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause), cause)
#define f2list__elt_3__set(this, cause, value) f2cons__car__set(            f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause),  cause,               value)
#define f2list__elt_4(     this, cause)        f2cons__car(     f2cons__cdr(f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause), cause), cause)
#define f2list__elt_4__set(this, cause, value) f2cons__car__set(f2cons__cdr(f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause), cause), cause, cause, value)


// doublelink

extern f2ptr __doublelink__symbol;
extern f2ptr f2doublelink__new__trace_depth(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value, int trace_depth);
extern f2ptr f2doublelink__new(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value);
#define f2primobject__is_doublelink(this, cause) raw__eq(cause, f2primobject__type(this, cause), __doublelink__symbol)

defprimobject__static_slot__prototype(doublelink__prev);
#define f2doublelink__prev(                  this, cause)                     primobject__static_slot__accessor(        this, doublelink__prev, cause)
#define f2doublelink__prev__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, doublelink__prev, cause, value, trace_depth)
#define f2doublelink__prev__set(             this, cause, value)              primobject__static_slot__set(             this, doublelink__prev, cause, value)
#define f2doublelink__prev__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, doublelink__prev, cause)
#define f2doublelink__prev__trace(           this, cause)                     primobject__static_slot__trace(           this, doublelink__prev, cause)
#define f2doublelink__prev__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, doublelink__prev, cause)

defprimobject__static_slot__prototype(doublelink__next);
#define f2doublelink__next(                  this, cause)                     primobject__static_slot__accessor(        this, doublelink__next, cause)
#define f2doublelink__next__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, doublelink__next, cause, value, trace_depth)
#define f2doublelink__next__set(             this, cause, value)              primobject__static_slot__set(             this, doublelink__next, cause, value)
#define f2doublelink__next__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, doublelink__next, cause)
#define f2doublelink__next__trace(           this, cause)                     primobject__static_slot__trace(           this, doublelink__next, cause)
#define f2doublelink__next__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, doublelink__next, cause)

defprimobject__static_slot__prototype(doublelink__value);
#define f2doublelink__value(                  this, cause)                     primobject__static_slot__accessor(        this, doublelink__value, cause)
#define f2doublelink__value__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, doublelink__value, cause, value, trace_depth)
#define f2doublelink__value__set(             this, cause, value)              primobject__static_slot__set(             this, doublelink__value, cause, value)
#define f2doublelink__value__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, doublelink__value, cause)
#define f2doublelink__value__trace(           this, cause)                     primobject__static_slot__trace(           this, doublelink__value, cause)
#define f2doublelink__value__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, doublelink__value, cause)


// imagination_link

extern f2ptr __imagination_link__symbol;
f2ptr f2imagination_link__new__trace_depth(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame, int trace_depth);
f2ptr f2imagination_link__new(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame);
#define f2primobject__is_imagination_link(this, cause) raw__eq(cause, f2primobject__type(this, cause), __imagination_link__symbol)

defprimobject__static_slot__prototype(imagination_link__next);
#define f2imagination_link__next(                  this, cause)                     primobject__static_slot__accessor(        this, imagination_link__next, cause)
#define f2imagination_link__next__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, imagination_link__next, cause, value, trace_depth)
#define f2imagination_link__next__set(             this, cause, value)              primobject__static_slot__set(             this, imagination_link__next, cause, value)
#define f2imagination_link__next__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, imagination_link__next, cause)
#define f2imagination_link__next__trace(           this, cause)                     primobject__static_slot__trace(           this, imagination_link__next, cause)
#define f2imagination_link__next__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, imagination_link__next, cause)

defprimobject__static_slot__prototype(imagination_link__name);
#define f2imagination_link__name(                  this, cause)                     primobject__static_slot__accessor(        this, imagination_link__name, cause)
#define f2imagination_link__name__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, imagination_link__name, cause, value, trace_depth)
#define f2imagination_link__name__set(             this, cause, value)              primobject__static_slot__set(             this, imagination_link__name, cause, value)
#define f2imagination_link__name__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, imagination_link__name, cause)
#define f2imagination_link__name__trace(           this, cause)                     primobject__static_slot__trace(           this, imagination_link__name, cause)
#define f2imagination_link__name__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, imagination_link__name, cause)

defprimobject__static_slot__prototype(imagination_link__value);
#define f2imagination_link__value(                  this, cause)                     primobject__static_slot__accessor(        this, imagination_link__value, cause)
#define f2imagination_link__value__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, imagination_link__value, cause, value, trace_depth)
#define f2imagination_link__value__set(             this, cause, value)              primobject__static_slot__set(             this, imagination_link__value, cause, value)
#define f2imagination_link__value__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, imagination_link__value, cause)
#define f2imagination_link__value__trace(           this, cause)                     primobject__static_slot__trace(           this, imagination_link__value, cause)
#define f2imagination_link__value__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, imagination_link__value, cause)

defprimobject__static_slot__prototype(imagination_link__trace);
#define f2imagination_link__trace(                  this, cause)                     primobject__static_slot__accessor(        this, imagination_link__trace, cause)
#define f2imagination_link__trace__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, imagination_link__trace, cause, value, trace_depth)
#define f2imagination_link__trace__set(             this, cause, value)              primobject__static_slot__set(             this, imagination_link__trace, cause, value)
#define f2imagination_link__trace__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, imagination_link__trace, cause)
#define f2imagination_link__trace__trace(           this, cause)                     primobject__static_slot__trace(           this, imagination_link__trace, cause)
#define f2imagination_link__trace__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, imagination_link__trace, cause)

defprimobject__static_slot__prototype(imagination_link__imagination_frame);
#define f2imagination_link__imagination_frame(                  this, cause)                     primobject__static_slot__accessor(        this, imagination_link__imagination_frame, cause)
#define f2imagination_link__imagination_frame__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, imagination_link__imagination_frame, cause, value, trace_depth)
#define f2imagination_link__imagination_frame__set(             this, cause, value)              primobject__static_slot__set(             this, imagination_link__imagination_frame, cause, value)
#define f2imagination_link__imagination_frame__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, imagination_link__imagination_frame, cause)
#define f2imagination_link__imagination_frame__trace(           this, cause)                     primobject__static_slot__trace(           this, imagination_link__imagination_frame, cause)
#define f2imagination_link__imagination_frame__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, imagination_link__imagination_frame, cause)

f2ptr raw__imagination_frame__lookup_imagination_link__trace_depth(f2ptr cause, f2ptr this, f2ptr real_value, f2ptr imagination_name_stack, int trace_depth);
f2ptr raw__imagination_frame__new_with_added_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth);
void  raw__imagination_link__add_new_imagination_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth);
f2ptr  f2__imagination_frame__get_slot(f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__imagination_link__get_slot(f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__imagination_link__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value);
f2ptr  f2__imagination_frame__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value);
void   f2__imagination_link__set_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr value, int trace_depth);

// cfunk

extern f2ptr __cfunk__symbol;
f2ptr f2cfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional);

#define f2primobject__is_cfunk(this, cause) raw__eq(cause, f2primobject__type(this, cause), __cfunk__symbol)

defprimobject__static_slot__prototype(cfunk__name);
#define f2cfunk__name(                   this, cause)        primobject__static_slot__accessor(         this, cfunk__name, cause)
#define f2cfunk__name__set(              this, cause, value) primobject__static_slot__set(              this, cfunk__name, cause, value)
#define f2cfunk__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cfunk__name, cause)
#define f2cfunk__name__trace(            this, cause)        primobject__static_slot__trace(            this, cfunk__name, cause)
#define f2cfunk__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cfunk__name, cause)

defprimobject__static_slot__prototype(cfunk__args);
#define f2cfunk__args(                this, cause)        primobject__static_slot__accessor(  this, cfunk__args, cause)
#define f2cfunk__args__set(           this, cause, value) primobject__static_slot__set(       this, cfunk__args, cause, value)
#define f2cfunk__args__tracing_on(    this, cause)        primobject__static_slot__tracing_on(this, cfunk__args, cause)
#define f2cfunk__args__trace(         this, cause)        primobject__static_slot__trace(     this, cfunk__args, cause)
#define f2cfunk__args__imagination_frame(         this, cause)        primobject__static_slot__imagination_frame(     this, cfunk__args, cause)

defprimobject__static_slot__prototype(cfunk__cfunkptr);
#define f2cfunk__cfunkptr(            this, cause)        primobject__static_slot__accessor(  this, cfunk__cfunkptr, cause)
#define f2cfunk__cfunkptr__set(       this, cause, value) primobject__static_slot__set(       this, cfunk__cfunkptr, cause, value)
#define f2cfunk__cfunkptr__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, cfunk__cfunkptr, cause)
#define f2cfunk__cfunkptr__trace(     this, cause)        primobject__static_slot__trace(     this, cfunk__cfunkptr, cause)
#define f2cfunk__cfunkptr__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, cfunk__cfunkptr, cause)

defprimobject__static_slot__prototype(cfunk__env);
#define f2cfunk__env(                 this, cause)        primobject__static_slot__accessor(  this, cfunk__env, cause)
#define f2cfunk__env__set(            this, cause, value) primobject__static_slot__set(       this, cfunk__env, cause, value)
#define f2cfunk__env__tracing_on(     this, cause)        primobject__static_slot__tracing_on(this, cfunk__env, cause)
#define f2cfunk__env__trace(          this, cause)        primobject__static_slot__trace(     this, cfunk__env, cause)
#define f2cfunk__env__imagination_frame(          this, cause)        primobject__static_slot__imagination_frame(     this, cfunk__env, cause)

defprimobject__static_slot__prototype(cfunk__is_funktional);
#define f2cfunk__is_funktional(                   this, cause)        primobject__static_slot__accessor(         this, cfunk__is_funktional, cause)
#define f2cfunk__is_funktional__set(              this, cause, value) primobject__static_slot__set(              this, cfunk__is_funktional, cause, value)
#define f2cfunk__is_funktional__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cfunk__is_funktional, cause)
#define f2cfunk__is_funktional__trace(            this, cause)        primobject__static_slot__trace(            this, cfunk__is_funktional, cause)
#define f2cfunk__is_funktional__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cfunk__is_funktional, cause)


// metrocfunk

extern f2ptr __metrocfunk__symbol;
f2ptr f2metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional);

#define f2primobject__is_metrocfunk(       this, cause)        raw__eq(cause, f2primobject__type(this, cause), __metrocfunk__symbol)

defprimobject__static_slot__prototype(metrocfunk__name);
#define f2metrocfunk__name(                   this, cause)        primobject__static_slot__accessor(         this, metrocfunk__name, cause)
#define f2metrocfunk__name__set(              this, cause, value) primobject__static_slot__set(              this, metrocfunk__name, cause, value)
#define f2metrocfunk__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, metrocfunk__name, cause)
#define f2metrocfunk__name__trace(            this, cause)        primobject__static_slot__trace(            this, metrocfunk__name, cause)
#define f2metrocfunk__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, metrocfunk__name, cause)

defprimobject__static_slot__prototype(metrocfunk__args);
#define f2metrocfunk__args(                this, cause)        primobject__static_slot__accessor(  this, metrocfunk__args, cause)
#define f2metrocfunk__args__set(           this, cause, value) primobject__static_slot__set(       this, metrocfunk__args, cause, value)
#define f2metrocfunk__args__tracing_on(    this, cause)        primobject__static_slot__tracing_on(this, metrocfunk__args, cause)
#define f2metrocfunk__args__trace(         this, cause)        primobject__static_slot__trace(     this, metrocfunk__args, cause)
#define f2metrocfunk__args__imagination_frame(         this, cause)        primobject__static_slot__imagination_frame(     this, metrocfunk__args, cause)

defprimobject__static_slot__prototype(metrocfunk__cfunkptr);
#define f2metrocfunk__cfunkptr(            this, cause)        primobject__static_slot__accessor(  this, metrocfunk__cfunkptr, cause)
#define f2metrocfunk__cfunkptr__set(       this, cause, value) primobject__static_slot__set(       this, metrocfunk__cfunkptr, cause, value)
#define f2metrocfunk__cfunkptr__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, metrocfunk__cfunkptr, cause)
#define f2metrocfunk__cfunkptr__trace(     this, cause)        primobject__static_slot__trace(     this, metrocfunk__cfunkptr, cause)
#define f2metrocfunk__cfunkptr__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, metrocfunk__cfunkptr, cause)

defprimobject__static_slot__prototype(metrocfunk__env);
#define f2metrocfunk__env(                 this, cause)        primobject__static_slot__accessor(  this, metrocfunk__env, cause)
#define f2metrocfunk__env__set(            this, cause, value) primobject__static_slot__set(       this, metrocfunk__env, cause, value)
#define f2metrocfunk__env__tracing_on(     this, cause)        primobject__static_slot__tracing_on(this, metrocfunk__env, cause)
#define f2metrocfunk__env__trace(          this, cause)        primobject__static_slot__trace(     this, metrocfunk__env, cause)
#define f2metrocfunk__env__imagination_frame(          this, cause)        primobject__static_slot__imagination_frame(     this, metrocfunk__env, cause)

defprimobject__static_slot__prototype(metrocfunk__is_funktional);
#define f2metrocfunk__is_funktional(                   this, cause)        primobject__static_slot__accessor(         this, metrocfunk__is_funktional, cause)
#define f2metrocfunk__is_funktional__set(              this, cause, value) primobject__static_slot__set(              this, metrocfunk__is_funktional, cause, value)
#define f2metrocfunk__is_funktional__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, metrocfunk__is_funktional, cause)
#define f2metrocfunk__is_funktional__trace(            this, cause)        primobject__static_slot__trace(            this, metrocfunk__is_funktional, cause)
#define f2metrocfunk__is_funktional__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, metrocfunk__is_funktional, cause)


// funk

extern f2ptr __funk__symbol;
f2ptr f2funk__new(f2ptr cause, f2ptr name, f2ptr body_bytecodes, f2ptr args, f2ptr demetropolize_body, f2ptr body, f2ptr env, f2ptr machine_code, f2ptr is_funktional);

#define f2primobject__is_funk(             this, cause)        raw__eq(cause, f2primobject__type(this, cause), __funk__symbol)

defprimobject__static_slot__prototype(funk__name);
#define f2funk__name(                   this, cause)        primobject__static_slot__accessor(         this, funk__name, cause)
#define f2funk__name__set(              this, cause, value) primobject__static_slot__set(              this, funk__name, cause, value)
#define f2funk__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, funk__name, cause)
#define f2funk__name__trace(            this, cause)        primobject__static_slot__trace(            this, funk__name, cause)
#define f2funk__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, funk__name, cause)

defprimobject__static_slot__prototype(funk__body_bytecodes);
#define f2funk__body_bytecodes(            this, cause)        primobject__static_slot__accessor(  this, funk__body_bytecodes, cause)
#define f2funk__body_bytecodes__set(       this, cause, value) primobject__static_slot__set(       this, funk__body_bytecodes, cause, value)
#define f2funk__body_bytecodes__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, funk__body_bytecodes, cause)
#define f2funk__body_bytecodes__trace(     this, cause)        primobject__static_slot__trace(     this, funk__body_bytecodes, cause)
#define f2funk__body_bytecodes__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, funk__body_bytecodes, cause)

defprimobject__static_slot__prototype(funk__args);
#define f2funk__args(                      this, cause)        primobject__static_slot__accessor(  this, funk__args, cause)
#define f2funk__args__set(                 this, cause, value) primobject__static_slot__set(       this, funk__args, cause, value)
#define f2funk__args__tracing_on(          this, cause)        primobject__static_slot__tracing_on(this, funk__args, cause)
#define f2funk__args__trace(               this, cause)        primobject__static_slot__trace(     this, funk__args, cause)
#define f2funk__args__imagination_frame(               this, cause)        primobject__static_slot__imagination_frame(     this, funk__args, cause)

defprimobject__static_slot__prototype(funk__demetropolized_body);
#define f2funk__demetropolized_body(            this, cause)        primobject__static_slot__accessor(  this, funk__demetropolized_body, cause)
#define f2funk__demetropolized_body__set(       this, cause, value) primobject__static_slot__set(       this, funk__demetropolized_body, cause, value)
#define f2funk__demetropolized_body__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, funk__demetropolized_body, cause)
#define f2funk__demetropolized_body__trace(     this, cause)        primobject__static_slot__trace(     this, funk__demetropolized_body, cause)
#define f2funk__demetropolized_body__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, funk__demetropolized_body, cause)

defprimobject__static_slot__prototype(funk__body);
#define f2funk__body(            this, cause)        primobject__static_slot__accessor(  this, funk__body, cause)
#define f2funk__body__set(       this, cause, value) primobject__static_slot__set(       this, funk__body, cause, value)
#define f2funk__body__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, funk__body, cause)
#define f2funk__body__trace(     this, cause)        primobject__static_slot__trace(     this, funk__body, cause)
#define f2funk__body__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, funk__body, cause)

defprimobject__static_slot__prototype(funk__env);
#define f2funk__env(                       this, cause)        primobject__static_slot__accessor(  this, funk__env, cause)
#define f2funk__env__set(                  this, cause, value) primobject__static_slot__set(       this, funk__env, cause, value)
#define f2funk__env__tracing_on(           this, cause)        primobject__static_slot__tracing_on(this, funk__env, cause)
#define f2funk__env__trace(                this, cause)        primobject__static_slot__trace(     this, funk__env, cause)
#define f2funk__env__imagination_frame(                this, cause)        primobject__static_slot__imagination_frame(     this, funk__env, cause)

defprimobject__static_slot__prototype(funk__machine_code);
#define f2funk__machine_code(              this, cause)        primobject__static_slot__accessor(  this, funk__machine_code, cause)
#define f2funk__machine_code__set(         this, cause, value) primobject__static_slot__set(       this, funk__machine_code, cause, value)
#define f2funk__machine_code__tracing_on(  this, cause)        primobject__static_slot__tracing_on(this, funk__machine_code, cause)
#define f2funk__machine_code__trace(       this, cause)        primobject__static_slot__trace(     this, funk__machine_code, cause)
#define f2funk__machine_code__imagination_frame(       this, cause)        primobject__static_slot__imagination_frame(     this, funk__machine_code, cause)

defprimobject__static_slot__prototype(funk__is_funktional);
#define f2funk__is_funktional(                   this, cause)        primobject__static_slot__accessor(         this, funk__is_funktional, cause)
#define f2funk__is_funktional__set(              this, cause, value) primobject__static_slot__set(              this, funk__is_funktional, cause, value)
#define f2funk__is_funktional__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, funk__is_funktional, cause)
#define f2funk__is_funktional__trace(            this, cause)        primobject__static_slot__trace(            this, funk__is_funktional, cause)
#define f2funk__is_funktional__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, funk__is_funktional, cause)


// metro

extern f2ptr __metro__symbol;
f2ptr f2metro__new(f2ptr context, f2ptr name, f2ptr body_bytecodes, f2ptr args, f2ptr demetropolize_body, f2ptr body, f2ptr env, f2ptr machine_code, f2ptr is_funktional);

#define f2primobject__is_metro(             this, cause)        raw__eq(cause, f2primobject__type(this, cause), __metro__symbol)

defprimobject__static_slot__prototype(metro__name);
#define f2metro__name(                   this, cause)        primobject__static_slot__accessor(         this, metro__name, cause)
#define f2metro__name__set(              this, cause, value) primobject__static_slot__set(              this, metro__name, cause, value)
#define f2metro__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, metro__name, cause)
#define f2metro__name__trace(            this, cause)        primobject__static_slot__trace(            this, metro__name, cause)
#define f2metro__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, metro__name, cause)

defprimobject__static_slot__prototype(metro__body_bytecodes);
#define f2metro__body_bytecodes(            this, cause)        primobject__static_slot__accessor(  this, metro__body_bytecodes, cause)
#define f2metro__body_bytecodes__set(       this, cause, value) primobject__static_slot__set(       this, metro__body_bytecodes, cause, value)
#define f2metro__body_bytecodes__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, metro__body_bytecodes, cause)
#define f2metro__body_bytecodes__trace(     this, cause)        primobject__static_slot__trace(     this, metro__body_bytecodes, cause)
#define f2metro__body_bytecodes__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, metro__body_bytecodes, cause)

defprimobject__static_slot__prototype(metro__args);
#define f2metro__args(                      this, cause)        primobject__static_slot__accessor(  this, metro__args, cause)
#define f2metro__args__set(                 this, cause, value) primobject__static_slot__set(       this, metro__args, cause, value)
#define f2metro__args__tracing_on(          this, cause)        primobject__static_slot__tracing_on(this, metro__args, cause)
#define f2metro__args__trace(               this, cause)        primobject__static_slot__trace(     this, metro__args, cause)
#define f2metro__args__imagination_frame(               this, cause)        primobject__static_slot__imagination_frame(     this, metro__args, cause)

defprimobject__static_slot__prototype(metro__demetropolized_body);
#define f2metro__demetropolized_body(                      this, cause)        primobject__static_slot__accessor(  this, metro__demetropolized_body, cause)
#define f2metro__demetropolized_body__set(                 this, cause, value) primobject__static_slot__set(       this, metro__demetropolized_body, cause, value)
#define f2metro__demetropolized_body__tracing_on(          this, cause)        primobject__static_slot__tracing_on(this, metro__demetropolized_body, cause)
#define f2metro__demetropolized_body__trace(               this, cause)        primobject__static_slot__trace(     this, metro__demetropolized_body, cause)
#define f2metro__demetropolized_body__imagination_frame(               this, cause)        primobject__static_slot__imagination_frame(     this, metro__demetropolized_body, cause)

defprimobject__static_slot__prototype(metro__body);
#define f2metro__body(            this, cause)        primobject__static_slot__accessor(  this, metro__body, cause)
#define f2metro__body__set(       this, cause, value) primobject__static_slot__set(       this, metro__body, cause, value)
#define f2metro__body__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, metro__body, cause)
#define f2metro__body__trace(     this, cause)        primobject__static_slot__trace(     this, metro__body, cause)
#define f2metro__body__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, metro__body, cause)

defprimobject__static_slot__prototype(metro__env);
#define f2metro__env(                       this, cause)        primobject__static_slot__accessor(  this, metro__env, cause)
#define f2metro__env__set(                  this, cause, value) primobject__static_slot__set(       this, metro__env, cause, value)
#define f2metro__env__tracing_on(           this, cause)        primobject__static_slot__tracing_on(this, metro__env, cause)
#define f2metro__env__trace(                this, cause)        primobject__static_slot__trace(     this, metro__env, cause)
#define f2metro__env__imagination_frame(                this, cause)        primobject__static_slot__imagination_frame(     this, metro__env, cause)

defprimobject__static_slot__prototype(metro__machine_code);
#define f2metro__machine_code(              this, cause)        primobject__static_slot__accessor(  this, metro__machine_code, cause)
#define f2metro__machine_code__set(         this, cause, value) primobject__static_slot__set(       this, metro__machine_code, cause, value)
#define f2metro__machine_code__tracing_on(  this, cause)        primobject__static_slot__tracing_on(this, metro__machine_code, cause)
#define f2metro__machine_code__trace(       this, cause)        primobject__static_slot__trace(     this, metro__machine_code, cause)
#define f2metro__machine_code__imagination_frame(       this, cause)        primobject__static_slot__imagination_frame(     this, metro__machine_code, cause)

defprimobject__static_slot__prototype(metro__is_funktional);
#define f2metro__is_funktional(                   this, cause)        primobject__static_slot__accessor(         this, metro__is_funktional, cause)
#define f2metro__is_funktional__set(              this, cause, value) primobject__static_slot__set(              this, metro__is_funktional, cause, value)
#define f2metro__is_funktional__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, metro__is_funktional, cause)
#define f2metro__is_funktional__trace(            this, cause)        primobject__static_slot__trace(            this, metro__is_funktional, cause)
#define f2metro__is_funktional__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, metro__is_funktional, cause)


// exception

extern f2ptr __exception__symbol;
extern f2ptr f2exception__new(f2ptr cause, f2ptr tag, f2ptr value);

#define f2primobject__is_exception(    this, cause)        raw__eq(cause, f2primobject__type(this, cause), __exception__symbol)

defprimobject__static_slot__prototype(exception__tag);
#define f2exception__tag(              this, cause)        primobject__static_slot__accessor(  this, exception__tag, cause)
#define f2exception__tag__set(         this, cause, value) primobject__static_slot__set(       this, exception__tag, cause, value)
#define f2exception__tag__tracing_on(  this, cause)        primobject__static_slot__tracing_on(this, exception__tag, cause)
#define f2exception__tag__trace(       this, cause)        primobject__static_slot__trace(     this, exception__tag, cause)
#define f2exception__tag__imagination_frame(       this, cause)        primobject__static_slot__imagination_frame(     this, exception__tag, cause)

defprimobject__static_slot__prototype(exception__value);
#define f2exception__value(            this, cause)        primobject__static_slot__accessor(  this, exception__value, cause)
#define f2exception__value__set(       this, cause, value) primobject__static_slot__set(       this, exception__value, cause, value)
#define f2exception__value__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, exception__value, cause)
#define f2exception__value__trace(     this, cause)        primobject__static_slot__trace(     this, exception__value, cause)
#define f2exception__value__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, exception__value, cause)

// bytecode

extern f2ptr __bytecode__symbol;
f2ptr f2bytecode__new(f2ptr cause, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2);

#define f2primobject__is_bytecode(this, cause) raw__eq(cause, f2primobject__type(this, cause), __bytecode__symbol)

defprimobject__static_slot__prototype(bytecode__command);
#define f2bytecode__command(            this, cause)        primobject__static_slot__accessor(  this, bytecode__command, cause)
#define f2bytecode__command__set(       this, cause, value) primobject__static_slot__set(       this, bytecode__command, cause, value)
#define f2bytecode__command__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, bytecode__command, cause)
#define f2bytecode__command__trace(     this, cause)        primobject__static_slot__trace(     this, bytecode__command, cause)
#define f2bytecode__command__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, bytecode__command, cause)

defprimobject__static_slot__prototype(bytecode__arg0);
#define f2bytecode__arg0(               this, cause)        primobject__static_slot__accessor(  this, bytecode__arg0, cause)
#define f2bytecode__arg0__set(          this, cause, value) primobject__static_slot__set(       this, bytecode__arg0, cause, value)
#define f2bytecode__arg0__tracing_on(   this, cause)        primobject__static_slot__tracing_on(this, bytecode__arg0, cause)
#define f2bytecode__arg0__trace(        this, cause)        primobject__static_slot__trace(     this, bytecode__arg0, cause)
#define f2bytecode__arg0__imagination_frame(        this, cause)        primobject__static_slot__imagination_frame(     this, bytecode__arg0, cause)

defprimobject__static_slot__prototype(bytecode__arg1);
#define f2bytecode__arg1(               this, cause)        primobject__static_slot__accessor(  this, bytecode__arg1, cause)
#define f2bytecode__arg1__set(          this, cause, value) primobject__static_slot__set(       this, bytecode__arg1, cause, value)
#define f2bytecode__arg1__tracing_on(   this, cause)        primobject__static_slot__tracing_on(this, bytecode__arg1, cause)
#define f2bytecode__arg1__trace(        this, cause)        primobject__static_slot__trace(     this, bytecode__arg1, cause)
#define f2bytecode__arg1__imagination_frame(        this, cause)        primobject__static_slot__imagination_frame(     this, bytecode__arg1, cause)

defprimobject__static_slot__prototype(bytecode__arg2);
#define f2bytecode__arg2(               this, cause)        primobject__static_slot__accessor(  this, bytecode__arg2, cause)
#define f2bytecode__arg2__set(          this, cause, value) primobject__static_slot__set(       this, bytecode__arg2, cause, value)
#define f2bytecode__arg2__tracing_on(   this, cause)        primobject__static_slot__tracing_on(this, bytecode__arg2, cause)
#define f2bytecode__arg2__trace(        this, cause)        primobject__static_slot__trace(     this, bytecode__arg2, cause)
#define f2bytecode__arg2__imagination_frame(        this, cause)        primobject__static_slot__imagination_frame(     this, bytecode__arg2, cause)


// thread

extern f2ptr __thread__symbol;
f2ptr f2thread__new(f2ptr cause,
		    f2ptr program_counter_reg,
		    f2ptr stack_reg,
		    f2ptr iter_reg,
		    f2ptr env_reg,
		    f2ptr args_reg,
		    f2ptr return_reg,
		    f2ptr value_reg,
		    f2ptr trace_reg,
		    f2ptr critics,
		    f2ptr cause_reg,
		    f2ptr keep_undead,
		    f2ptr is_zombie,
		    f2ptr parent_thread,
		    f2ptr parent_env,
		    f2ptr execute_mutex,
		    f2ptr paused,
		    f2ptr last_executed_time);

#define f2primobject__is_thread(                 this, cause)        raw__eq(cause, f2primobject__type(this, cause), __thread__symbol)

defprimobject__static_slot__prototype(thread__program_counter);
#define f2thread__program_counter(               this, cause)        primobject__static_slot__accessor(  this, thread__program_counter, cause)
#define f2thread__program_counter__set(          this, cause, value) primobject__static_slot__set(       this, thread__program_counter, cause, value)
#define f2thread__program_counter__tracing_on(   this, cause)        primobject__static_slot__tracing_on(this, thread__program_counter, cause)
#define f2thread__program_counter__trace(        this, cause)        primobject__static_slot__trace(     this, thread__program_counter, cause)
#define f2thread__program_counter__imagination_frame(        this, cause)        primobject__static_slot__imagination_frame(     this, thread__program_counter, cause)

defprimobject__static_slot__prototype(thread__stack);
#define f2thread__stack(                         this, cause)        primobject__static_slot__accessor(  this, thread__stack, cause)
#define f2thread__stack__set(                    this, cause, value) primobject__static_slot__set(       this, thread__stack, cause, value)
#define f2thread__stack__tracing_on(             this, cause)        primobject__static_slot__tracing_on(this, thread__stack, cause)
#define f2thread__stack__trace(                  this, cause)        primobject__static_slot__trace(     this, thread__stack, cause)
#define f2thread__stack__imagination_frame(                  this, cause)        primobject__static_slot__imagination_frame(     this, thread__stack, cause)

defprimobject__static_slot__prototype(thread__iter);
#define f2thread__iter(                          this, cause)        primobject__static_slot__accessor(  this, thread__iter, cause)
#define f2thread__iter__set(                     this, cause, value) primobject__static_slot__set(       this, thread__iter, cause, value)
#define f2thread__iter__tracing_on(              this, cause)        primobject__static_slot__tracing_on(this, thread__iter, cause)
#define f2thread__iter__trace(                   this, cause)        primobject__static_slot__trace(     this, thread__iter, cause)
#define f2thread__iter__imagination_frame(                   this, cause)        primobject__static_slot__imagination_frame(     this, thread__iter, cause)

defprimobject__static_slot__prototype(thread__env);
#define f2thread__env(                           this, cause)        primobject__static_slot__accessor(  this, thread__env, cause)
#define f2thread__env__set(                      this, cause, value) primobject__static_slot__set(       this, thread__env, cause, value)
#define f2thread__env__tracing_on(               this, cause)        primobject__static_slot__tracing_on(this, thread__env, cause)
#define f2thread__env__trace(                    this, cause)        primobject__static_slot__trace(     this, thread__env, cause)
#define f2thread__env__imagination_frame(                    this, cause)        primobject__static_slot__imagination_frame(     this, thread__env, cause)

defprimobject__static_slot__prototype(thread__args);
#define f2thread__args(                          this, cause)        primobject__static_slot__accessor(  this, thread__args, cause)
#define f2thread__args__set(                     this, cause, value) primobject__static_slot__set(       this, thread__args, cause, value)
#define f2thread__args__tracing_on(              this, cause)        primobject__static_slot__tracing_on(this, thread__args, cause)
#define f2thread__args__trace(                   this, cause)        primobject__static_slot__trace(     this, thread__args, cause)
#define f2thread__args__imagination_frame(                   this, cause)        primobject__static_slot__imagination_frame(     this, thread__args, cause)

defprimobject__static_slot__prototype(thread__return);
#define f2thread__return(                        this, cause)        primobject__static_slot__accessor(  this, thread__return, cause)
#define f2thread__return__set(                   this, cause, value) primobject__static_slot__set(       this, thread__return, cause, value)
#define f2thread__return__tracing_on(            this, cause)        primobject__static_slot__tracing_on(this, thread__return, cause)
#define f2thread__return__trace(                 this, cause)        primobject__static_slot__trace(     this, thread__return, cause)
#define f2thread__return__imagination_frame(                 this, cause)        primobject__static_slot__imagination_frame(     this, thread__return, cause)

defprimobject__static_slot__prototype(thread__value);
#define f2thread__value(                         this, cause)        primobject__static_slot__accessor(  this, thread__value, cause)
#define f2thread__value__set(                    this, cause, value) primobject__static_slot__set(       this, thread__value, cause, value)
#define f2thread__value__tracing_on(             this, cause)        primobject__static_slot__tracing_on(this, thread__value, cause)
#define f2thread__value__trace(                  this, cause)        primobject__static_slot__trace(     this, thread__value, cause)
#define f2thread__value__imagination_frame(                  this, cause)        primobject__static_slot__imagination_frame(     this, thread__value, cause)

defprimobject__static_slot__prototype(thread__trace);
#define f2thread__trace(                         this, cause)        primobject__static_slot__accessor(  this, thread__trace, cause)
#define f2thread__trace__set(                    this, cause, value) primobject__static_slot__set(       this, thread__trace, cause, value)
#define f2thread__trace__tracing_on(             this, cause)        primobject__static_slot__tracing_on(this, thread__trace, cause)
#define f2thread__trace__trace(                  this, cause)        primobject__static_slot__trace(     this, thread__trace, cause)
#define f2thread__trace__imagination_frame(                  this, cause)        primobject__static_slot__imagination_frame(     this, thread__trace, cause)

defprimobject__static_slot__prototype(thread__critics);
#define f2thread__critics(                   this, cause)        primobject__static_slot__accessor(         this, thread__critics, cause)
#define f2thread__critics__set(              this, cause, value) primobject__static_slot__set(              this, thread__critics, cause, value)
#define f2thread__critics__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, thread__critics, cause)
#define f2thread__critics__trace(            this, cause)        primobject__static_slot__trace(            this, thread__critics, cause)
#define f2thread__critics__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, thread__critics, cause)

defprimobject__static_slot__prototype(thread__cause_reg);
#define f2thread__cause_reg(                   this, cause)        primobject__static_slot__accessor(         this, thread__cause_reg, cause)
#define f2thread__cause_reg__set(              this, cause, value) primobject__static_slot__set(              this, thread__cause_reg, cause, value)
#define f2thread__cause_reg__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, thread__cause_reg, cause)
#define f2thread__cause_reg__trace(            this, cause)        primobject__static_slot__trace(            this, thread__cause_reg, cause)
#define f2thread__cause_reg__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, thread__cause_reg, cause)

defprimobject__static_slot__prototype(thread__keep_undead);
#define f2thread__keep_undead(                   this, cause)        primobject__static_slot__accessor(  this, thread__keep_undead, cause)
#define f2thread__keep_undead__set(              this, cause, value) primobject__static_slot__set(       this, thread__keep_undead, cause, value)
#define f2thread__keep_undead__tracing_on(       this, cause)        primobject__static_slot__tracing_on(this, thread__keep_undead, cause)
#define f2thread__keep_undead__trace(            this, cause)        primobject__static_slot__trace(     this, thread__keep_undead, cause)
#define f2thread__keep_undead__imagination_frame(            this, cause)        primobject__static_slot__imagination_frame(     this, thread__keep_undead, cause)

defprimobject__static_slot__prototype(thread__is_zombie);
#define f2thread__is_zombie(                     this, cause)        primobject__static_slot__accessor(  this, thread__is_zombie, cause)
#define f2thread__is_zombie__set(                this, cause, value) primobject__static_slot__set(       this, thread__is_zombie, cause, value)
#define f2thread__is_zombie__tracing_on(         this, cause)        primobject__static_slot__tracing_on(this, thread__is_zombie, cause)
#define f2thread__is_zombie__trace(              this, cause)        primobject__static_slot__trace(     this, thread__is_zombie, cause)
#define f2thread__is_zombie__imagination_frame(              this, cause)        primobject__static_slot__imagination_frame(     this, thread__is_zombie, cause)

defprimobject__static_slot__prototype(thread__parent_thread);
#define f2thread__parent_thread(                 this, cause)        primobject__static_slot__accessor(  this, thread__parent_thread, cause)
#define f2thread__parent_thread__set(            this, cause, value) primobject__static_slot__set(       this, thread__parent_thread, cause, value)
#define f2thread__parent_thread__tracing_on(     this, cause)        primobject__static_slot__tracing_on(this, thread__parent_thread, cause)
#define f2thread__parent_thread__trace(          this, cause)        primobject__static_slot__trace(     this, thread__parent_thread, cause)
#define f2thread__parent_thread__imagination_frame(          this, cause)        primobject__static_slot__imagination_frame(     this, thread__parent_thread, cause)

defprimobject__static_slot__prototype(thread__parent_env);
#define f2thread__parent_env(                    this, cause)        primobject__static_slot__accessor(  this, thread__parent_env, cause)
#define f2thread__parent_env__set(               this, cause, value) primobject__static_slot__set(       this, thread__parent_env, cause, value)
#define f2thread__parent_env__tracing_on(        this, cause)        primobject__static_slot__tracing_on(this, thread__parent_env, cause)
#define f2thread__parent_env__trace(             this, cause)        primobject__static_slot__trace(     this, thread__parent_env, cause)
#define f2thread__parent_env__imagination_frame(             this, cause)        primobject__static_slot__imagination_frame(     this, thread__parent_env, cause)

defprimobject__static_slot__prototype(thread__execute_mutex);
#define f2thread__execute_mutex(                 this, cause)        primobject__static_slot__accessor(  this, thread__execute_mutex, cause)
#define f2thread__execute_mutex__set(            this, cause, value) primobject__static_slot__set(       this, thread__execute_mutex, cause, value)
#define f2thread__execute_mutex__tracing_on(     this, cause)        primobject__static_slot__tracing_on(this, thread__execute_mutex, cause)
#define f2thread__execute_mutex__trace(          this, cause)        primobject__static_slot__trace(     this, thread__execute_mutex, cause)
#define f2thread__execute_mutex__imagination_frame(          this, cause)        primobject__static_slot__imagination_frame(     this, thread__execute_mutex, cause)

defprimobject__static_slot__prototype(thread__paused);
#define f2thread__paused(                   this, cause)        primobject__static_slot__accessor(         this, thread__paused, cause)
#define f2thread__paused__set(              this, cause, value) primobject__static_slot__set(              this, thread__paused, cause, value)
#define f2thread__paused__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, thread__paused, cause)
#define f2thread__paused__trace(            this, cause)        primobject__static_slot__trace(            this, thread__paused, cause)
#define f2thread__paused__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, thread__paused, cause)

defprimobject__static_slot__prototype(thread__last_executed_time);
#define f2thread__last_executed_time(            this, cause)        primobject__static_slot__accessor(  this, thread__last_executed_time, cause)
#define f2thread__last_executed_time__set(       this, cause, value) primobject__static_slot__set(       this, thread__last_executed_time, cause, value)
#define f2thread__last_executed_time__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, thread__last_executed_time, cause)
#define f2thread__last_executed_time__trace(     this, cause)        primobject__static_slot__trace(     this, thread__last_executed_time, cause)
#define f2thread__last_executed_time__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, thread__last_executed_time, cause)

#define __pure__f2thread__is_complete(this, cause)  (!f2thread__program_counter(this, cause))
#define f2thread__is_complete(this, cause)          __pure__f2thread__is_complete(this, cause)
//extern int f2thread__is_complete(f2ptr this);

// processor

extern f2ptr __processor__symbol;
f2ptr f2processor__new(f2ptr cause, f2ptr scheduler, f2ptr pthread, f2ptr active_threads_mutex, f2ptr active_threads, f2ptr sleeping_threads_mutex, f2ptr sleeping_threads, f2ptr pool_index, f2ptr desc);

#define f2primobject__is_processor(             this, cause)        raw__eq(cause, f2primobject__type(this, cause), __processor__symbol)

defprimobject__static_slot__prototype(processor__scheduler);
#define f2processor__scheduler(                 this, cause)        primobject__static_slot__accessor(  this, processor__scheduler, cause)
#define f2processor__scheduler__set(            this, cause, value) primobject__static_slot__set(       this, processor__scheduler, cause, value)
#define f2processor__scheduler__tracing_on(     this, cause)        primobject__static_slot__tracing_on(this, processor__scheduler, cause)
#define f2processor__scheduler__trace(          this, cause)        primobject__static_slot__trace(     this, processor__scheduler, cause)
#define f2processor__scheduler__imagination_frame(          this, cause)        primobject__static_slot__imagination_frame(     this, processor__scheduler, cause)

defprimobject__static_slot__prototype(processor__pthread);
#define f2processor__pthread(                   this, cause)        primobject__static_slot__accessor(  this, processor__pthread, cause)
#define f2processor__pthread__set(              this, cause, value) primobject__static_slot__set(       this, processor__pthread, cause, value)
#define f2processor__pthread__tracing_on(       this, cause)        primobject__static_slot__tracing_on(this, processor__pthread, cause)
#define f2processor__pthread__trace(            this, cause)        primobject__static_slot__trace(     this, processor__pthread, cause)
#define f2processor__pthread__imagination_frame(            this, cause)        primobject__static_slot__imagination_frame(     this, processor__pthread, cause)

defprimobject__static_slot__prototype(processor__active_threads_mutex);
#define f2processor__active_threads_mutex(            this, cause)        primobject__static_slot__accessor(  this, processor__active_threads_mutex, cause)
#define f2processor__active_threads_mutex__set(       this, cause, value) primobject__static_slot__set(       this, processor__active_threads_mutex, cause, value)
#define f2processor__active_threads_mutex__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, processor__active_threads_mutex, cause)
#define f2processor__active_threads_mutex__trace(     this, cause)        primobject__static_slot__trace(     this, processor__active_threads_mutex, cause)
#define f2processor__active_threads_mutex__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, processor__active_threads_mutex, cause)

defprimobject__static_slot__prototype(processor__active_threads);
#define f2processor__active_threads(                   this, cause)        primobject__static_slot__accessor(  this, processor__active_threads, cause)
#define f2processor__active_threads__set(              this, cause, value) primobject__static_slot__set(       this, processor__active_threads, cause, value)
#define f2processor__active_threads__tracing_on(       this, cause)        primobject__static_slot__tracing_on(this, processor__active_threads, cause)
#define f2processor__active_threads__trace(            this, cause)        primobject__static_slot__trace(     this, processor__active_threads, cause)
#define f2processor__active_threads__imagination_frame(            this, cause)        primobject__static_slot__imagination_frame(     this, processor__active_threads, cause)

defprimobject__static_slot__prototype(processor__sleeping_threads_mutex);
#define f2processor__sleeping_threads_mutex(            this, cause)        primobject__static_slot__accessor(  this, processor__sleeping_threads_mutex, cause)
#define f2processor__sleeping_threads_mutex__set(       this, cause, value) primobject__static_slot__set(       this, processor__sleeping_threads_mutex, cause, value)
#define f2processor__sleeping_threads_mutex__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, processor__sleeping_threads_mutex, cause)
#define f2processor__sleeping_threads_mutex__trace(     this, cause)        primobject__static_slot__trace(     this, processor__sleeping_threads_mutex, cause)
#define f2processor__sleeping_threads_mutex__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, processor__sleeping_threads_mutex, cause)

defprimobject__static_slot__prototype(processor__sleeping_threads);
#define f2processor__sleeping_threads(                   this, cause)        primobject__static_slot__accessor(  this, processor__sleeping_threads, cause)
#define f2processor__sleeping_threads__set(              this, cause, value) primobject__static_slot__set(       this, processor__sleeping_threads, cause, value)
#define f2processor__sleeping_threads__tracing_on(       this, cause)        primobject__static_slot__tracing_on(this, processor__sleeping_threads, cause)
#define f2processor__sleeping_threads__trace(            this, cause)        primobject__static_slot__trace(     this, processor__sleeping_threads, cause)
#define f2processor__sleeping_threads__imagination_frame(            this, cause)        primobject__static_slot__imagination_frame(     this, processor__sleeping_threads, cause)

defprimobject__static_slot__prototype(processor__pool_index);
#define f2processor__pool_index(                this, cause)        primobject__static_slot__accessor(  this, processor__pool_index, cause)
#define f2processor__pool_index__set(           this, cause, value) primobject__static_slot__set(       this, processor__pool_index, cause, value)
#define f2processor__pool_index__tracing_on(    this, cause)        primobject__static_slot__tracing_on(this, processor__pool_index, cause)
#define f2processor__pool_index__trace(         this, cause)        primobject__static_slot__trace(     this, processor__pool_index, cause)
#define f2processor__pool_index__imagination_frame(         this, cause)        primobject__static_slot__imagination_frame(     this, processor__pool_index, cause)

defprimobject__static_slot__prototype(processor__desc);
#define f2processor__desc(                      this, cause)        primobject__static_slot__accessor(  this, processor__desc, cause)
#define f2processor__desc__set(                 this, cause, value) primobject__static_slot__set(       this, processor__desc, cause, value)
#define f2processor__desc__tracing_on(          this, cause)        primobject__static_slot__tracing_on(this, processor__desc, cause)
#define f2processor__desc__trace(               this, cause)        primobject__static_slot__trace(     this, processor__desc, cause)
#define f2processor__desc__imagination_frame(               this, cause)        primobject__static_slot__imagination_frame(     this, processor__desc, cause)


// scheduler

extern f2ptr __scheduler__symbol;
f2ptr f2scheduler__new(f2ptr cause, f2ptr processors, f2ptr event_subscribers_mutex, f2ptr event_subscribers, f2ptr event_buffer_mutex, f2ptr event_buffer);
#define f2primobject__is_scheduler(this, cause)                 raw__eq(cause, f2primobject__type(this, cause), __scheduler__symbol)

defprimobject__static_slot__prototype(scheduler__processors);
#define f2scheduler__processors(            this, cause)        primobject__static_slot__accessor(  this, scheduler__processors, cause)
#define f2scheduler__processors__set(       this, cause, value) primobject__static_slot__set(       this, scheduler__processors, cause, value)
#define f2scheduler__processors__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, scheduler__processors, cause)
#define f2scheduler__processors__trace(     this, cause)        primobject__static_slot__trace(     this, scheduler__processors, cause)
#define f2scheduler__processors__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, scheduler__processors, cause)

defprimobject__static_slot__prototype(scheduler__event_subscribers_mutex);
#define f2scheduler__event_subscribers_mutex(            this, cause)        primobject__static_slot__accessor(  this, scheduler__event_subscribers_mutex, cause)
#define f2scheduler__event_subscribers_mutex__set(       this, cause, value) primobject__static_slot__set(       this, scheduler__event_subscribers_mutex, cause, value)
#define f2scheduler__event_subscribers_mutex__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, scheduler__event_subscribers_mutex, cause)
#define f2scheduler__event_subscribers_mutex__trace(     this, cause)        primobject__static_slot__trace(     this, scheduler__event_subscribers_mutex, cause)
#define f2scheduler__event_subscribers_mutex__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, scheduler__event_subscribers_mutex, cause)

defprimobject__static_slot__prototype(scheduler__event_subscribers);
#define f2scheduler__event_subscribers(            this, cause)        primobject__static_slot__accessor(  this, scheduler__event_subscribers, cause)
#define f2scheduler__event_subscribers__set(       this, cause, value) primobject__static_slot__set(       this, scheduler__event_subscribers, cause, value)
#define f2scheduler__event_subscribers__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, scheduler__event_subscribers, cause)
#define f2scheduler__event_subscribers__trace(     this, cause)        primobject__static_slot__trace(     this, scheduler__event_subscribers, cause)
#define f2scheduler__event_subscribers__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, scheduler__event_subscribers, cause)

defprimobject__static_slot__prototype(scheduler__event_buffer_mutex);
#define f2scheduler__event_buffer_mutex(            this, cause)        primobject__static_slot__accessor(  this, scheduler__event_buffer_mutex, cause)
#define f2scheduler__event_buffer_mutex__set(       this, cause, value) primobject__static_slot__set(       this, scheduler__event_buffer_mutex, cause, value)
#define f2scheduler__event_buffer_mutex__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, scheduler__event_buffer_mutex, cause)
#define f2scheduler__event_buffer_mutex__trace(     this, cause)        primobject__static_slot__trace(     this, scheduler__event_buffer_mutex, cause)
#define f2scheduler__event_buffer_mutex__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, scheduler__event_buffer_mutex, cause)

defprimobject__static_slot__prototype(scheduler__event_buffer);
#define f2scheduler__event_buffer(            this, cause)        primobject__static_slot__accessor(  this, scheduler__event_buffer, cause)
#define f2scheduler__event_buffer__set(       this, cause, value) primobject__static_slot__set(       this, scheduler__event_buffer, cause, value)
#define f2scheduler__event_buffer__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, scheduler__event_buffer, cause)
#define f2scheduler__event_buffer__trace(     this, cause)        primobject__static_slot__trace(     this, scheduler__event_buffer, cause)
#define f2scheduler__event_buffer__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, scheduler__event_buffer, cause)


// event_subscriber

f2ptr __event_subscriber__symbol;
f2ptr f2event_subscriber__new(f2ptr cause, f2ptr event_type, f2ptr thread, f2ptr funkable, f2ptr event_buffer, f2ptr event_buffer_mutex);
#define f2primobject__is__event_subscriber(this, cause)                 raw__eq(cause, f2primobject__type(this, cause), __event_subscriber__symbol)

defprimobject__static_slot__prototype(event_subscriber__event_types);
#define f2event_subscriber__event_types(            this, cause)        primobject__static_slot__accessor(  this, event_subscriber__event_types, cause)
#define f2event_subscriber__event_types__set(       this, cause, value) primobject__static_slot__set(       this, event_subscriber__event_types, cause, value)
#define f2event_subscriber__event_types__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, event_subscriber__event_types, cause)
#define f2event_subscriber__event_types__trace(     this, cause)        primobject__static_slot__trace(     this, event_subscriber__event_types, cause)
#define f2event_subscriber__event_types__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, event_subscriber__event_types, cause)

defprimobject__static_slot__prototype(event_subscriber__thread);
#define f2event_subscriber__thread(            this, cause)        primobject__static_slot__accessor(  this, event_subscriber__thread, cause)
#define f2event_subscriber__thread__set(       this, cause, value) primobject__static_slot__set(       this, event_subscriber__thread, cause, value)
#define f2event_subscriber__thread__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, event_subscriber__thread, cause)
#define f2event_subscriber__thread__trace(     this, cause)        primobject__static_slot__trace(     this, event_subscriber__thread, cause)
#define f2event_subscriber__thread__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, event_subscriber__thread, cause)

defprimobject__static_slot__prototype(event_subscriber__funkable);
#define f2event_subscriber__funkable(            this, cause)        primobject__static_slot__accessor(  this, event_subscriber__funkable, cause)
#define f2event_subscriber__funkable__set(       this, cause, value) primobject__static_slot__set(       this, event_subscriber__funkable, cause, value)
#define f2event_subscriber__funkable__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, event_subscriber__funkable, cause)
#define f2event_subscriber__funkable__trace(     this, cause)        primobject__static_slot__trace(     this, event_subscriber__funkable, cause)
#define f2event_subscriber__funkable__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, event_subscriber__funkable, cause)

defprimobject__static_slot__prototype(event_subscriber__event_buffer);
#define f2event_subscriber__event_buffer(            this, cause)        primobject__static_slot__accessor(  this, event_subscriber__event_buffer, cause)
#define f2event_subscriber__event_buffer__set(       this, cause, value) primobject__static_slot__set(       this, event_subscriber__event_buffer, cause, value)
#define f2event_subscriber__event_buffer__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, event_subscriber__event_buffer, cause)
#define f2event_subscriber__event_buffer__trace(     this, cause)        primobject__static_slot__trace(     this, event_subscriber__event_buffer, cause)
#define f2event_subscriber__event_buffer__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, event_subscriber__event_buffer, cause)

defprimobject__static_slot__prototype(event_subscriber__event_buffer_mutex);
#define f2event_subscriber__event_buffer_mutex(            this, cause)        primobject__static_slot__accessor(  this, event_subscriber__event_buffer_mutex, cause)
#define f2event_subscriber__event_buffer_mutex__set(       this, cause, value) primobject__static_slot__set(       this, event_subscriber__event_buffer_mutex, cause, value)
#define f2event_subscriber__event_buffer_mutex__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, event_subscriber__event_buffer_mutex, cause)
#define f2event_subscriber__event_buffer_mutex__trace(     this, cause)        primobject__static_slot__trace(     this, event_subscriber__event_buffer_mutex, cause)
#define f2event_subscriber__event_buffer_mutex__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, event_subscriber__event_buffer_mutex, cause)



// cause

f2ptr __cause__symbol;
f2ptr f2cause__new(f2ptr cause, f2ptr bytecode_tracing_on, f2ptr bmemory_tracing_on, f2ptr subscribers_mutex, f2ptr subscribers, f2ptr imagination_stack, f2ptr event_buffer_first, f2ptr event_buffer_last);
f2ptr f2__cause__new(f2ptr cause, f2ptr bytecode_tracing_on, f2ptr memory_tracing_on, f2ptr subscribers, f2ptr imagination_stack, f2ptr event_buffer_first, f2ptr event_buffer_last);

#define f2primobject__is_cause(this, cause) raw__eq(cause, f2primobject__type(this, cause), __cause__symbol)

defprimobject__static_slot__prototype(cause__bytecode_tracing_on);
#define f2cause__bytecode_tracing_on(                   this, cause)        primobject__static_slot__accessor(         this, cause__bytecode_tracing_on, cause)
#define f2cause__bytecode_tracing_on__set(              this, cause, value) primobject__static_slot__set(              this, cause__bytecode_tracing_on, cause, value)
#define f2cause__bytecode_tracing_on__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__bytecode_tracing_on, cause)
#define f2cause__bytecode_tracing_on__trace(            this, cause)        primobject__static_slot__trace(            this, cause__bytecode_tracing_on, cause)
#define f2cause__bytecode_tracing_on__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__bytecode_tracing_on, cause)

defprimobject__static_slot__prototype(cause__memory_tracing_on);
#define f2cause__memory_tracing_on(                   this, cause)        primobject__static_slot__accessor(         this, cause__memory_tracing_on, cause)
#define f2cause__memory_tracing_on__set(              this, cause, value) primobject__static_slot__set(              this, cause__memory_tracing_on, cause, value)
#define f2cause__memory_tracing_on__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__memory_tracing_on, cause)
#define f2cause__memory_tracing_on__trace(            this, cause)        primobject__static_slot__trace(            this, cause__memory_tracing_on, cause)
#define f2cause__memory_tracing_on__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__memory_tracing_on, cause)

defprimobject__static_slot__prototype(cause__subscribers_mutex);
#define f2cause__subscribers_mutex(                   this, cause)        primobject__static_slot__accessor(         this, cause__subscribers_mutex, cause)
#define f2cause__subscribers_mutex__set(              this, cause, value) primobject__static_slot__set(              this, cause__subscribers_mutex, cause, value)
#define f2cause__subscribers_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__subscribers_mutex, cause)
#define f2cause__subscribers_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, cause__subscribers_mutex, cause)
#define f2cause__subscribers_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__subscribers_mutex, cause)

defprimobject__static_slot__prototype(cause__subscribers);
#define f2cause__subscribers(                   this, cause)        primobject__static_slot__accessor(         this, cause__subscribers, cause)
#define f2cause__subscribers__set(              this, cause, value) primobject__static_slot__set(              this, cause__subscribers, cause, value)
#define f2cause__subscribers__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__subscribers, cause)
#define f2cause__subscribers__trace(            this, cause)        primobject__static_slot__trace(            this, cause__subscribers, cause)
#define f2cause__subscribers__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__subscribers, cause)

defprimobject__static_slot__prototype(cause__imagination_stack);
#define f2cause__imagination_stack(                   this, cause)        primobject__static_slot__accessor(         this, cause__imagination_stack, cause)
#define f2cause__imagination_stack__set(              this, cause, value) primobject__static_slot__set(              this, cause__imagination_stack, cause, value)
#define f2cause__imagination_stack__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__imagination_stack, cause)
#define f2cause__imagination_stack__trace(            this, cause)        primobject__static_slot__trace(            this, cause__imagination_stack, cause)
#define f2cause__imagination_stack__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__imagination_stack, cause)

defprimobject__static_slot__prototype(cause__event_buffer_first);
#define f2cause__event_buffer_first(                   this, cause)        primobject__static_slot__accessor(         this, cause__event_buffer_first, cause)
#define f2cause__event_buffer_first__set(              this, cause, value) primobject__static_slot__set(              this, cause__event_buffer_first, cause, value)
#define f2cause__event_buffer_first__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__event_buffer_first, cause)
#define f2cause__event_buffer_first__trace(            this, cause)        primobject__static_slot__trace(            this, cause__event_buffer_first, cause)
#define f2cause__event_buffer_first__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__event_buffer_first, cause)

defprimobject__static_slot__prototype(cause__event_buffer_last);
#define f2cause__event_buffer_last(                   this, cause)        primobject__static_slot__accessor(         this, cause__event_buffer_last, cause)
#define f2cause__event_buffer_last__set(              this, cause, value) primobject__static_slot__set(              this, cause__event_buffer_last, cause, value)
#define f2cause__event_buffer_last__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, cause__event_buffer_last, cause)
#define f2cause__event_buffer_last__trace(            this, cause)        primobject__static_slot__trace(            this, cause__event_buffer_last, cause)
#define f2cause__event_buffer_last__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, cause__event_buffer_last, cause)


f2ptr f2__cause__bytecode_tracing_on(f2ptr cause, f2ptr this);
void  raw__cause__event_buffer__add(f2ptr cause, f2ptr event);


// transframe

extern f2ptr __transframe__symbol;
extern f2ptr f2transframe__new__trace_depth(f2ptr cause, f2ptr symbol_old_news, int trace_depth);
extern f2ptr f2transframe__new(f2ptr cause, f2ptr symbol_old_news);
#define f2primobject__is_transframe(this, cause) raw__eq(cause, f2primobject__type(this, cause), __transframe__symbol)

// symbol_old_news is a list of 3-element arrays, e.g. [(symbol-1 old-1 new-1) (symbol-2 old-2 new-2) . . .]
defprimobject__static_slot__prototype(transframe__symbol_old_news);
#define f2transframe__symbol_old_news(                  this, cause)                     primobject__static_slot__accessor(        this, transframe__symbol_old_news, cause)
#define f2transframe__symbol_old_news__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, transframe__symbol_old_news, cause, value, trace_depth)
#define f2transframe__symbol_old_news__set(             this, cause, value)              primobject__static_slot__set(             this, transframe__symbol_old_news, cause, value)
#define f2transframe__symbol_old_news__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, transframe__symbol_old_news, cause)
#define f2transframe__symbol_old_news__trace(           this, cause)                     primobject__static_slot__trace(           this, transframe__symbol_old_news, cause)
#define f2transframe__symbol_old_news__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, transframe__symbol_old_news, cause)

// bug

extern f2ptr __bug__symbol;
extern f2ptr f2bug__new(f2ptr cause, f2ptr type);
#define f2primobject__is_bug(   this, cause)        raw__eq(cause, f2primobject__type(this, cause), __bug__symbol)

defprimobject__static_slot__prototype(bug__type);
#define f2bug__type(            this, cause)        primobject__static_slot__accessor(  this, bug__type, cause)
#define f2bug__type__set(       this, cause, value) primobject__static_slot__set(       this, bug__type, cause, value)
#define f2bug__type__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, bug__type, cause)
#define f2bug__type__trace(     this, cause)        primobject__static_slot__trace(     this, bug__type, cause)
#define f2bug__type__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, bug__type, cause)


// size_2d

extern f2ptr __size_2d__symbol;
extern f2ptr f2size_2d__new(f2ptr cause, f2ptr x, f2ptr y);
#define f2primobject__is__size_2d(this, cause)        raw__eq(cause, f2primobject__type(this, cause), __size_2d__symbol)

defprimobject__static_slot__prototype(size_2d__x);
#define f2size_2d__x(             this, cause)        primobject__static_slot__accessor(  this, size_2d__x, cause)
#define f2size_2d__x__set(        this, cause, value) primobject__static_slot__set(       this, size_2d__x, cause, value)
#define f2size_2d__x__tracing_on( this, cause)        primobject__static_slot__tracing_on(this, size_2d__x, cause)
#define f2size_2d__x__trace(      this, cause)        primobject__static_slot__trace(     this, size_2d__x, cause)
#define f2size_2d__x__imagination_frame(      this, cause)        primobject__static_slot__imagination_frame(     this, size_2d__x, cause)

defprimobject__static_slot__prototype(size_2d__y);
#define f2size_2d__y(             this, cause)        primobject__static_slot__accessor(  this, size_2d__y, cause)
#define f2size_2d__y__set(        this, cause, value) primobject__static_slot__set(       this, size_2d__y, cause, value)
#define f2size_2d__y__tracing_on( this, cause)        primobject__static_slot__tracing_on(this, size_2d__y, cause)
#define f2size_2d__y__trace(      this, cause)        primobject__static_slot__trace(     this, size_2d__y, cause)
#define f2size_2d__y__imagination_frame(      this, cause)        primobject__static_slot__imagination_frame(     this, size_2d__y, cause)


// event

extern f2ptr __event__symbol;
f2ptr f2event__new__trace_depth(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data, int trace_depth);
f2ptr f2event__new(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data);
#define f2primobject__is__event(this, cause) raw__eq(cause, f2primobject__type(this, cause), __event__symbol)

defprimobject__static_slot__prototype(event__node_id);
#define f2event__node_id(                  this, cause)                     primobject__static_slot__accessor(        this, event__node_id, cause)
#define f2event__node_id__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, event__node_id, cause, value, trace_depth)
#define f2event__node_id__set(             this, cause, value)              primobject__static_slot__set(             this, event__node_id, cause, value)
#define f2event__node_id__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, event__node_id, cause)
#define f2event__node_id__trace(           this, cause)                     primobject__static_slot__trace(           this, event__node_id, cause)
#define f2event__node_id__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, event__node_id, cause)

defprimobject__static_slot__prototype(event__event_id);
#define f2event__event_id(                  this, cause)                     primobject__static_slot__accessor(        this, event__event_id, cause)
#define f2event__event_id__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, event__event_id, cause, value, trace_depth)
#define f2event__event_id__set(             this, cause, value)              primobject__static_slot__set(             this, event__event_id, cause, value)
#define f2event__event_id__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, event__event_id, cause)
#define f2event__event_id__trace(           this, cause)                     primobject__static_slot__trace(           this, event__event_id, cause)
#define f2event__event_id__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, event__event_id, cause)

defprimobject__static_slot__prototype(event__type);
#define f2event__type(                  this, cause)                     primobject__static_slot__accessor(        this, event__type, cause)
#define f2event__type__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, event__type, cause, value, trace_depth)
#define f2event__type__set(             this, cause, value)              primobject__static_slot__set(             this, event__type, cause, value)
#define f2event__type__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, event__type, cause)
#define f2event__type__trace(           this, cause)                     primobject__static_slot__trace(           this, event__type, cause)
#define f2event__type__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, event__type, cause)

defprimobject__static_slot__prototype(event__data);
#define f2event__data(                  this, cause)                     primobject__static_slot__accessor(        this, event__data, cause)
#define f2event__data__set__trace_depth(this, cause, value, trace_depth) primobject__static_slot__set__trace_depth(this, event__data, cause, value, trace_depth)
#define f2event__data__set(             this, cause, value)              primobject__static_slot__set(             this, event__data, cause, value)
#define f2event__data__tracing_on(      this, cause)                     primobject__static_slot__tracing_on(      this, event__data, cause)
#define f2event__data__trace(           this, cause)                     primobject__static_slot__trace(           this, event__data, cause)
#define f2event__data__imagination_frame(           this, cause)                     primobject__static_slot__imagination_frame(           this, event__data, cause)


// bytecode_event

extern f2ptr __bytecode_event__symbol;
f2ptr f2bytecode_event__new__trace_depth(f2ptr cause, f2ptr bytecode, f2ptr context, int trace_depth);
f2ptr f2bytecode_event__new(f2ptr cause, f2ptr bytecode, f2ptr context);
#define f2primobject__is__bytecode_event(this, cause) raw__eq(cause, f2primobject__type(this, cause), __bytecode_event__symbol)

defprimobject__static_slot__prototype(bytecode_event__bytecode);
#define f2bytecode_event__bytecode(                   this, cause)                     primobject__static_slot__accessor(         this, bytecode_event__bytecode, cause)
#define f2bytecode_event__bytecode__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, bytecode_event__bytecode, cause, value, trace_depth)
#define f2bytecode_event__bytecode__set(              this, cause, value)              primobject__static_slot__set(              this, bytecode_event__bytecode, cause, value)
#define f2bytecode_event__bytecode__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, bytecode_event__bytecode, cause)
#define f2bytecode_event__bytecode__trace(            this, cause)                     primobject__static_slot__trace(            this, bytecode_event__bytecode, cause)
#define f2bytecode_event__bytecode__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, bytecode_event__bytecode, cause)

defprimobject__static_slot__prototype(bytecode_event__context);
#define f2bytecode_event__context(                   this, cause)                     primobject__static_slot__accessor(         this, bytecode_event__context, cause)
#define f2bytecode_event__context__set__trace_depth( this, cause, value, trace_depth) primobject__static_slot__set__trace_depth( this, bytecode_event__context, cause, value, trace_depth)
#define f2bytecode_event__context__set(              this, cause, value)              primobject__static_slot__set(              this, bytecode_event__context, cause, value)
#define f2bytecode_event__context__tracing_on(       this, cause)                     primobject__static_slot__tracing_on(       this, bytecode_event__context, cause)
#define f2bytecode_event__context__trace(            this, cause)                     primobject__static_slot__trace(            this, bytecode_event__context, cause)
#define f2bytecode_event__context__imagination_frame(this, cause)                     primobject__static_slot__imagination_frame(this, bytecode_event__context, cause)


// end of objects

extern void f2__primobjects__reinitialize_globalvars();
extern void f2__primobjects__initialize();

#endif // F2__PRIMOBJECTS__H


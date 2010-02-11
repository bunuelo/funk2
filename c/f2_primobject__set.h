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

#ifndef F2__PRIMOBJECT__SET__TYPES__H
#define F2__PRIMOBJECT__SET__TYPES__H

typedef struct funk2_object_type__set__slot_s funk2_object_type__set__slot_t;

// set

struct funk2_object_type__set__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr write_mutex__symbol;
  f2ptr write_mutex__funk;
  f2ptr write_mutex__set__symbol;
  f2ptr write_mutex__set__funk;
  f2ptr key_count__symbol;
  f2ptr key_count__funk;
  f2ptr key_count__set__symbol;
  f2ptr key_count__set__funk;
  f2ptr bin_num_power__symbol;
  f2ptr bin_num_power__funk;
  f2ptr bin_num_power__set__symbol;
  f2ptr bin_num_power__set__funk;
  f2ptr bin_array__symbol;
  f2ptr bin_array__funk;
  f2ptr bin_array__set__symbol;
  f2ptr bin_array__set__funk;
  f2ptr add__symbol;
  f2ptr add__funk;
  f2ptr lookup__symbol;
  f2ptr lookup__funk;
  f2ptr elements__symbol;
  f2ptr elements__funk;
};

#endif // F2__PRIMOBJECT__SET__TYPES__H

#ifndef F2__PRIMOBJECT__SET__H
#define F2__PRIMOBJECT__SET__H

#include "f2_primobjects.h"

// set

extern f2ptr __set__symbol;
boolean_t raw__set__is_type(f2ptr cause, f2ptr this);
f2ptr f2__set__is_type(f2ptr cause, f2ptr this);
f2ptr f2set__new(f2ptr cause, f2ptr write_mutex, f2ptr key_count, f2ptr bin_num_power, f2ptr bin_array);
#define f2primobject__is_set(this, cause)                    raw__eq(cause, f2primobject__type(this, cause), __set__symbol)

defprimobject__static_slot__prototype(set__write_mutex);
#define f2set__write_mutex(                   this, cause)        primobject__static_slot__accessor(         this, set__write_mutex, cause)
#define f2set__write_mutex__set(              this, cause, value) primobject__static_slot__set(              this, set__write_mutex, cause, value)
#define f2set__write_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, set__write_mutex, cause)
#define f2set__write_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, set__write_mutex, cause)
#define f2set__write_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, set__write_mutex, cause)

defprimobject__static_slot__prototype(set__key_count);
#define f2set__key_count(                   this, cause)        primobject__static_slot__accessor(         this, set__key_count, cause)
#define f2set__key_count__set(              this, cause, value) primobject__static_slot__set(              this, set__key_count, cause, value)
#define f2set__key_count__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, set__key_count, cause)
#define f2set__key_count__trace(            this, cause)        primobject__static_slot__trace(            this, set__key_count, cause)
#define f2set__key_count__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, set__key_count, cause)

defprimobject__static_slot__prototype(set__bin_num_power);
#define f2set__bin_num_power(                   this, cause)        primobject__static_slot__accessor(         this, set__bin_num_power, cause)
#define f2set__bin_num_power__set(              this, cause, value) primobject__static_slot__set(              this, set__bin_num_power, cause, value)
#define f2set__bin_num_power__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, set__bin_num_power, cause)
#define f2set__bin_num_power__trace(            this, cause)        primobject__static_slot__trace(            this, set__bin_num_power, cause)
#define f2set__bin_num_power__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, set__bin_num_power, cause)

defprimobject__static_slot__prototype(set__bin_array);
#define f2set__bin_array(                   this, cause)        primobject__static_slot__accessor(         this, set__bin_array, cause)
#define f2set__bin_array__set(              this, cause, value) primobject__static_slot__set(              this, set__bin_array, cause, value)
#define f2set__bin_array__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, set__bin_array, cause)
#define f2set__bin_array__trace(            this, cause)        primobject__static_slot__trace(            this, set__bin_array, cause)
#define f2set__bin_array__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, set__bin_array, cause)

f2ptr raw__set__new   (f2ptr cause, s64 bin_num_power);
f2ptr  f2__set__new   (f2ptr cause);
f2ptr  f2__set__add   (f2ptr cause, f2ptr this, f2ptr key);
f2ptr  f2__set__lookup(f2ptr this, f2ptr cause, f2ptr key);

f2ptr f2__set__slot_names(f2ptr cause, f2ptr this);

f2ptr f2set__primobject_type__new(f2ptr cause);

// **

void f2__primobject_set__reinitialize_globalvars();
void f2__primobject_set__initialize();

#endif // F2__PRIMOBJECT__SET__H


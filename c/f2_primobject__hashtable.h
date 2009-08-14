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

#ifndef F2__PRIMOBJECT__HASHTABLE__TYPES__H
#define F2__PRIMOBJECT__HASHTABLE__TYPES__H

typedef struct funk2_object_type__hashtable__slot_s funk2_object_type__hashtable__slot_t;

// hashtable

struct funk2_object_type__hashtable__slot_s {
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
};

#endif // F2__PRIMOBJECT__HASHTABLE__TYPES__H

#ifndef F2__PRIMOBJECT__HASHTABLE__H
#define F2__PRIMOBJECT__HASHTABLE__H

#include "f2_primobjects.h"

// hashtable

extern f2ptr __hashtable__symbol;
boolean_t raw__hashtable__is_type(f2ptr cause, f2ptr this);
f2ptr f2__hashtable__is_type(f2ptr cause, f2ptr this);
f2ptr f2hashtable__new(f2ptr cause, f2ptr write_mutex, f2ptr key_count, f2ptr bin_num_power, f2ptr bin_array);
#define f2primobject__is_hashtable(this, cause)                    raw__eq(cause, f2primobject__type(this, cause), __hashtable__symbol)

defprimobject__static_slot__prototype(hashtable__write_mutex);
#define f2hashtable__write_mutex(                   this, cause)        primobject__static_slot__accessor(         this, hashtable__write_mutex, cause)
#define f2hashtable__write_mutex__set(              this, cause, value) primobject__static_slot__set(              this, hashtable__write_mutex, cause, value)
#define f2hashtable__write_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, hashtable__write_mutex, cause)
#define f2hashtable__write_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, hashtable__write_mutex, cause)
#define f2hashtable__write_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, hashtable__write_mutex, cause)

defprimobject__static_slot__prototype(hashtable__key_count);
#define f2hashtable__key_count(                   this, cause)        primobject__static_slot__accessor(         this, hashtable__key_count, cause)
#define f2hashtable__key_count__set(              this, cause, value) primobject__static_slot__set(              this, hashtable__key_count, cause, value)
#define f2hashtable__key_count__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, hashtable__key_count, cause)
#define f2hashtable__key_count__trace(            this, cause)        primobject__static_slot__trace(            this, hashtable__key_count, cause)
#define f2hashtable__key_count__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, hashtable__key_count, cause)

defprimobject__static_slot__prototype(hashtable__bin_num_power);
#define f2hashtable__bin_num_power(                   this, cause)        primobject__static_slot__accessor(         this, hashtable__bin_num_power, cause)
#define f2hashtable__bin_num_power__set(              this, cause, value) primobject__static_slot__set(              this, hashtable__bin_num_power, cause, value)
#define f2hashtable__bin_num_power__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, hashtable__bin_num_power, cause)
#define f2hashtable__bin_num_power__trace(            this, cause)        primobject__static_slot__trace(            this, hashtable__bin_num_power, cause)
#define f2hashtable__bin_num_power__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, hashtable__bin_num_power, cause)

defprimobject__static_slot__prototype(hashtable__bin_array);
#define f2hashtable__bin_array(                   this, cause)        primobject__static_slot__accessor(         this, hashtable__bin_array, cause)
#define f2hashtable__bin_array__set(              this, cause, value) primobject__static_slot__set(              this, hashtable__bin_array, cause, value)
#define f2hashtable__bin_array__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, hashtable__bin_array, cause)
#define f2hashtable__bin_array__trace(            this, cause)        primobject__static_slot__trace(            this, hashtable__bin_array, cause)
#define f2hashtable__bin_array__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, hashtable__bin_array, cause)

f2ptr raw__hashtable__new                (f2ptr cause, s64 bin_num_power);
f2ptr f2__hashtable__new                 (f2ptr cause, f2ptr bin_num_power);
f2ptr f2__hashtable__add_keyvalue_pair   (f2ptr cause, f2ptr this, f2ptr key, f2ptr value);
f2ptr f2__hashtable__lookup_keyvalue_pair(f2ptr this, f2ptr cause, f2ptr key);
f2ptr f2__hashtable__lookup_value        (f2ptr this, f2ptr cause, f2ptr key);

f2ptr f2__hashtable__slot_names(f2ptr cause, f2ptr this);

f2ptr f2hashtable__primobject_type__new(f2ptr cause);

// **

void f2__primobject_hashtable__reinitialize_globalvars();
void f2__primobject_hashtable__initialize();

#endif // F2__PRIMOBJECT__HASHTABLE__H


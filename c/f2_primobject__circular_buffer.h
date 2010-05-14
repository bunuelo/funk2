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

#ifndef F2__PRIMOBJECT__CIRCULAR_BUFFER__TYPES__H
#define F2__PRIMOBJECT__CIRCULAR_BUFFER__TYPES__H

// circular_buffer

/*
typedef struct funk2_object_type__circular_buffer__slot_s funk2_object_type__circular_buffer__slot_t;

struct funk2_object_type__circular_buffer__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr access_mutex__symbol;
  f2ptr access_mutex__funk;
  f2ptr access_mutex__set__symbol;
  f2ptr access_mutex__set__funk;
  f2ptr start__symbol;
  f2ptr start__funk;
  f2ptr start__set__symbol;
  f2ptr start__set__funk;
  f2ptr end__symbol;
  f2ptr end__funk;
  f2ptr end__set__symbol;
  f2ptr end__set__funk;
  f2ptr bin_array__symbol;
  f2ptr bin_array__funk;
  f2ptr bin_array__set__symbol;
  f2ptr bin_array__set__funk;
  f2ptr pop__symbol;
  f2ptr pop__funk;
  f2ptr add__symbol;
  f2ptr add__funk;
  f2ptr is_empty__symbol;
  f2ptr is_empty__funk;
};
*/

typedef struct funk2_object_type__circular_buffer__slot_s funk2_object_type__circular_buffer__slot_t;
declare_object_type_4_slot(circular_buffer, access_mutex, start, end, bin_array,
			   f2ptr pop__symbol;
			   f2ptr pop__funk;
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr is_empty__symbol;
			   f2ptr is_empty__funk;
			   );

#endif // F2__PRIMOBJECT__CIRCULAR_BUFFER__TYPES__H

#ifndef F2__PRIMOBJECT__CIRCULAR_BUFFER__H
#define F2__PRIMOBJECT__CIRCULAR_BUFFER__H

#include "f2_primobjects.h"

typedef struct funk2_primobject_circular_buffer_s {
  f2ptr symbol;
} funk2_primobject_circular_buffer_t;

// circular_buffer

/*

boolean_t raw__circular_buffer__is_type(f2ptr cause, f2ptr this);
f2ptr f2__circular_buffer__is_type(f2ptr cause, f2ptr this);
f2ptr f2circular_buffer__new(f2ptr cause, f2ptr access_mutex, f2ptr start, f2ptr end, f2ptr bin_array);
#define f2primobject__is_circular_buffer(this, cause) raw__eq(cause, f2primobject__type(this, cause), __funk2.primobject__circular_buffer.symbol)

defprimobject__static_slot__prototype(circular_buffer__access_mutex);
#define f2circular_buffer__access_mutex(                   this, cause)        primobject__static_slot__accessor(         this, circular_buffer__access_mutex, cause)
#define f2circular_buffer__access_mutex__set(              this, cause, value) primobject__static_slot__set(              this, circular_buffer__access_mutex, cause, value)
#define f2circular_buffer__access_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, circular_buffer__access_mutex, cause)
#define f2circular_buffer__access_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, circular_buffer__access_mutex, cause)
#define f2circular_buffer__access_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, circular_buffer__access_mutex, cause)

defprimobject__static_slot__prototype(circular_buffer__start);
#define f2circular_buffer__start(                   this, cause)        primobject__static_slot__accessor(         this, circular_buffer__start, cause)
#define f2circular_buffer__start__set(              this, cause, value) primobject__static_slot__set(              this, circular_buffer__start, cause, value)
#define f2circular_buffer__start__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, circular_buffer__start, cause)
#define f2circular_buffer__start__trace(            this, cause)        primobject__static_slot__trace(            this, circular_buffer__start, cause)
#define f2circular_buffer__start__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, circular_buffer__start, cause)

defprimobject__static_slot__prototype(circular_buffer__end);
#define f2circular_buffer__end(                   this, cause)        primobject__static_slot__accessor(         this, circular_buffer__end, cause)
#define f2circular_buffer__end__set(              this, cause, value) primobject__static_slot__set(              this, circular_buffer__end, cause, value)
#define f2circular_buffer__end__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, circular_buffer__end, cause)
#define f2circular_buffer__end__trace(            this, cause)        primobject__static_slot__trace(            this, circular_buffer__end, cause)
#define f2circular_buffer__end__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, circular_buffer__end, cause)

defprimobject__static_slot__prototype(circular_buffer__bin_array);
#define f2circular_buffer__bin_array(                   this, cause)        primobject__static_slot__accessor(         this, circular_buffer__bin_array, cause)
#define f2circular_buffer__bin_array__set(              this, cause, value) primobject__static_slot__set(              this, circular_buffer__bin_array, cause, value)
#define f2circular_buffer__bin_array__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, circular_buffer__bin_array, cause)
#define f2circular_buffer__bin_array__trace(            this, cause)        primobject__static_slot__trace(            this, circular_buffer__bin_array, cause)
#define f2circular_buffer__bin_array__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, circular_buffer__bin_array, cause)
*/

declare_primobject_4_slot(circular_buffer, access_mutex, start, end, bin_array);

f2ptr raw__circular_buffer__new_empty(f2ptr cause, u64 length);
f2ptr f2__circular_buffer__new(f2ptr cause);
f2ptr f2__circular_buffer__add(f2ptr cause, f2ptr this, f2ptr value);
f2ptr f2__circular_buffer__pop(f2ptr cause, f2ptr this);
boolean_t raw__circular_buffer__is_empty(f2ptr cause, f2ptr this);

f2ptr f2circular_buffer__primobject_type__new(f2ptr cause);

// **

void f2__primobject_circular_buffer__reinitialize_globalvars();
void f2__primobject_circular_buffer__initialize();



#endif // F2__PRIMOBJECT__CIRCULAR_BUFFER__H

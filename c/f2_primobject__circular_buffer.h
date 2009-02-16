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

#ifndef F2__PRIMOBJECT__CIRCULAR_BUFFER__H
#define F2__PRIMOBJECT__CIRCULAR_BUFFER__H

#include "f2_primobjects.h"

// circular_buffer

typedef struct funk2_primobject_circular_buffer_s {
  f2ptr symbol;
  f2ptr empty__symbol;
  f2ptr full__symbol;
} funk2_primobject_circular_buffer_t;

f2ptr f2circular_buffer__new(f2ptr cause, f2ptr start, f2ptr end, f2ptr bin_array);
#define f2primobject__is_circular_buffer(this, cause) raw__eq(cause, f2primobject__type(this, cause), __funk2.primobject__circular_buffer.symbol)

defprimobject__static_slot__prototype(circular_buffer__start);
#define f2circular_buffer__start(            this, cause)        primobject__static_slot__accessor(  this, circular_buffer__start, cause)
#define f2circular_buffer__start__set(       this, cause, value) primobject__static_slot__set(       this, circular_buffer__start, cause, value)
#define f2circular_buffer__start__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, circular_buffer__start, cause)
#define f2circular_buffer__start__trace(     this, cause)        primobject__static_slot__trace(     this, circular_buffer__start, cause)
#define f2circular_buffer__start__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, circular_buffer__start, cause)

defprimobject__static_slot__prototype(circular_buffer__end);
#define f2circular_buffer__end(            this, cause)        primobject__static_slot__accessor(  this, circular_buffer__end, cause)
#define f2circular_buffer__end__set(       this, cause, value) primobject__static_slot__set(       this, circular_buffer__end, cause, value)
#define f2circular_buffer__end__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, circular_buffer__end, cause)
#define f2circular_buffer__end__trace(     this, cause)        primobject__static_slot__trace(     this, circular_buffer__end, cause)
#define f2circular_buffer__end__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, circular_buffer__end, cause)

defprimobject__static_slot__prototype(circular_buffer__bin_array);
#define f2circular_buffer__bin_array(            this, cause)        primobject__static_slot__accessor(  this, circular_buffer__bin_array, cause)
#define f2circular_buffer__bin_array__set(       this, cause, value) primobject__static_slot__set(       this, circular_buffer__bin_array, cause, value)
#define f2circular_buffer__bin_array__tracing_on(this, cause)        primobject__static_slot__tracing_on(this, circular_buffer__bin_array, cause)
#define f2circular_buffer__bin_array__trace(     this, cause)        primobject__static_slot__trace(     this, circular_buffer__bin_array, cause)
#define f2circular_buffer__bin_array__imagination_frame(     this, cause)        primobject__static_slot__imagination_frame(     this, circular_buffer__bin_array, cause)

f2ptr f2__circular_buffer__new(f2ptr cause, f2ptr start, f2ptr end, f2ptr bin_array);
f2ptr raw__circular_buffer__new_empty(f2ptr cause, u64 length);
f2ptr f2__circular_bufferp(f2ptr this, f2ptr cause);
f2ptr f2__circular_buffer__add(f2ptr cause, f2ptr this, f2ptr value);
f2ptr f2__circular_buffer__remove(f2ptr cause, f2ptr this);
bool  raw__circular_buffer__is_empty(f2ptr cause, f2ptr this);

void f2__primobject_circular_buffer__reinitialize_globalvars();
void f2__primobject_circular_buffer__initialize();



#endif // F2__PRIMOBJECT__CIRCULAR_BUFFER__H

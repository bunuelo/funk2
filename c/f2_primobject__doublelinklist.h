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

#ifndef F2__PRIMOBJECT__DOUBLELINKLIST__TYPES__H
#define F2__PRIMOBJECT__DOUBLELINKLIST__TYPES__H

// doublelinklist

typedef struct funk2_object_type__doublelinklist__slot_s funk2_object_type__doublelinklist__slot_t;
declare_object_type_3_slot(doublelinklist, write_mutex, length, cons_cells,
			   f2ptr add__symbol;
			   f2ptr add__funk;
			   f2ptr lookup__symbol;
			   f2ptr lookup__funk;
			   f2ptr car__symbol;
			   f2ptr car__funk;
			   f2ptr cdr__symbol;
			   f2ptr cdr__funk;
			   );

/*
// doublelinklist

typedef struct funk2_object_type__doublelinklist__slot_s funk2_object_type__doublelinklist__slot_t;

struct funk2_object_type__doublelinklist__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr write_mutex__symbol;
  f2ptr write_mutex__funk;
  f2ptr write_mutex__set__symbol;
  f2ptr write_mutex__set__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr length__set__symbol;
  f2ptr length__set__funk;
  f2ptr cons_cells__symbol;
  f2ptr cons_cells__funk;
  f2ptr cons_cells__set__symbol;
  f2ptr cons_cells__set__funk;
  f2ptr add__symbol;
  f2ptr add__funk;
  f2ptr lookup__symbol;
  f2ptr lookup__funk;
  f2ptr car__symbol;
  f2ptr car__funk;
  f2ptr cdr__symbol;
  f2ptr cdr__funk;
};
*/

#endif // F2__PRIMOBJECT__DOUBLELINKLIST__TYPES__H

#ifndef F2__PRIMOBJECT__DOUBLELINKLIST__H
#define F2__PRIMOBJECT__DOUBLELINKLIST__H

#include "f2_primobjects.h"

// doublelinklist

extern f2ptr __doublelinklist__symbol;
boolean_t raw__doublelinklist__is_type(f2ptr cause, f2ptr this);
f2ptr f2__doublelinklist__is_type(f2ptr cause, f2ptr this);
f2ptr f2doublelinklist__new(f2ptr cause, f2ptr write_mutex, f2ptr length, f2ptr cons_cells);
#define f2primobject__is_doublelinklist(this, cause)                    raw__eq(cause, f2primobject__type(this, cause), __doublelinklist__symbol)

defprimobject__static_slot__prototype(doublelinklist__write_mutex);
#define f2doublelinklist__write_mutex(                   this, cause)        primobject__static_slot__accessor(         this, doublelinklist__write_mutex, cause)
#define f2doublelinklist__write_mutex__set(              this, cause, value) primobject__static_slot__set(              this, doublelinklist__write_mutex, cause, value)
#define f2doublelinklist__write_mutex__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, doublelinklist__write_mutex, cause)
#define f2doublelinklist__write_mutex__trace(            this, cause)        primobject__static_slot__trace(            this, doublelinklist__write_mutex, cause)
#define f2doublelinklist__write_mutex__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, doublelinklist__write_mutex, cause)

defprimobject__static_slot__prototype(doublelinklist__length);
#define f2doublelinklist__length(                   this, cause)        primobject__static_slot__accessor(         this, doublelinklist__length, cause)
#define f2doublelinklist__length__set(              this, cause, value) primobject__static_slot__set(              this, doublelinklist__length, cause, value)
#define f2doublelinklist__length__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, doublelinklist__length, cause)
#define f2doublelinklist__length__trace(            this, cause)        primobject__static_slot__trace(            this, doublelinklist__length, cause)
#define f2doublelinklist__length__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, doublelinklist__length, cause)

defprimobject__static_slot__prototype(doublelinklist__cons_cells);
#define f2doublelinklist__cons_cells(                   this, cause)        primobject__static_slot__accessor(         this, doublelinklist__cons_cells, cause)
#define f2doublelinklist__cons_cells__set(              this, cause, value) primobject__static_slot__set(              this, doublelinklist__cons_cells, cause, value)
#define f2doublelinklist__cons_cells__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, doublelinklist__cons_cells, cause)
#define f2doublelinklist__cons_cells__trace(            this, cause)        primobject__static_slot__trace(            this, doublelinklist__cons_cells, cause)
#define f2doublelinklist__cons_cells__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, doublelinklist__cons_cells, cause)

f2ptr f2__doublelinklist__new   (f2ptr cause, f2ptr elements);
f2ptr f2__doublelinklist__add   (f2ptr cause, f2ptr this, f2ptr element);
f2ptr f2__doublelinklist__lookup(f2ptr cause, f2ptr this, f2ptr element);

f2ptr f2doublelinklist__primobject_type__new(f2ptr cause);

// **

void f2__primobject_doublelinklist__reinitialize_globalvars();
void f2__primobject_doublelinklist__initialize();

#endif // F2__PRIMOBJECT__DOUBLELINKLIST__H


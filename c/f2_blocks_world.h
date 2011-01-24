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

#ifndef F2__BLOCKS_WORLD__H
#define F2__BLOCKS_WORLD__H

#include "f2_primobjects.h"

// blocks_world_rectangle

extern f2ptr __blocks_world_rectangle__symbol;
f2ptr f2blocks_world_rectangle__new(f2ptr cause, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1);
boolean_t  raw__blocks_world_rectangle__is_type(f2ptr cause, f2ptr this);

#define f2primobject__is__blocks_world_rectangle(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __blocks_world_rectangle__symbol)

defprimobject__static_slot__prototype(blocks_world_rectangle__x0);
#define f2blocks_world_rectangle__x0(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_rectangle__x0, cause)
#define f2blocks_world_rectangle__x0__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_rectangle__x0, cause, value)
#define f2blocks_world_rectangle__x0__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_rectangle__x0, cause)
#define f2blocks_world_rectangle__x0__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_rectangle__x0, cause)
#define f2blocks_world_rectangle__x0__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_rectangle__x0, cause)

defprimobject__static_slot__prototype(blocks_world_rectangle__y0);
#define f2blocks_world_rectangle__y0(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_rectangle__y0, cause)
#define f2blocks_world_rectangle__y0__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_rectangle__y0, cause, value)
#define f2blocks_world_rectangle__y0__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_rectangle__y0, cause)
#define f2blocks_world_rectangle__y0__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_rectangle__y0, cause)
#define f2blocks_world_rectangle__y0__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_rectangle__y0, cause)

defprimobject__static_slot__prototype(blocks_world_rectangle__x1);
#define f2blocks_world_rectangle__x1(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_rectangle__x1, cause)
#define f2blocks_world_rectangle__x1__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_rectangle__x1, cause, value)
#define f2blocks_world_rectangle__x1__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_rectangle__x1, cause)
#define f2blocks_world_rectangle__x1__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_rectangle__x1, cause)
#define f2blocks_world_rectangle__x1__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_rectangle__x1, cause)

defprimobject__static_slot__prototype(blocks_world_rectangle__y1);
#define f2blocks_world_rectangle__y1(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_rectangle__y1, cause)
#define f2blocks_world_rectangle__y1__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_rectangle__y1, cause, value)
#define f2blocks_world_rectangle__y1__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_rectangle__y1, cause)
#define f2blocks_world_rectangle__y1__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_rectangle__y1, cause)
#define f2blocks_world_rectangle__y1__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_rectangle__y1, cause)



// blocks_world_color

extern f2ptr __blocks_world_color__symbol;
f2ptr f2blocks_world_color__new(f2ptr cause, f2ptr name);
boolean_t raw__blocks_world_color__is_type(f2ptr cause, f2ptr this);

#define f2primobject__is__blocks_world_color(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __blocks_world_color__symbol)

defprimobject__static_slot__prototype(blocks_world_color__name);
#define f2blocks_world_color__name(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_color__name, cause)
#define f2blocks_world_color__name__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_color__name, cause, value)
#define f2blocks_world_color__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_color__name, cause)
#define f2blocks_world_color__name__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_color__name, cause)
#define f2blocks_world_color__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_color__name, cause)



// blocks_world_object

extern f2ptr __blocks_world_object__symbol;
f2ptr f2blocks_world_object__new(f2ptr cause, f2ptr name, f2ptr type, f2ptr rectangle, f2ptr color, f2ptr ignore_gravity, f2ptr holding_object);
boolean_t raw__blocks_world_object__is_type(f2ptr cause, f2ptr this);

#define f2primobject__is__blocks_world_object(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __blocks_world_object__symbol)

defprimobject__static_slot__prototype(blocks_world_object__name);
#define f2blocks_world_object__name(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_object__name, cause)
#define f2blocks_world_object__name__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_object__name, cause, value)
#define f2blocks_world_object__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_object__name, cause)
#define f2blocks_world_object__name__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_object__name, cause)
#define f2blocks_world_object__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_object__name, cause)

defprimobject__static_slot__prototype(blocks_world_object__type);
#define f2blocks_world_object__type(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_object__type, cause)
#define f2blocks_world_object__type__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_object__type, cause, value)
#define f2blocks_world_object__type__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_object__type, cause)
#define f2blocks_world_object__type__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_object__type, cause)
#define f2blocks_world_object__type__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_object__type, cause)

defprimobject__static_slot__prototype(blocks_world_object__rectangle);
#define f2blocks_world_object__rectangle(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_object__rectangle, cause)
#define f2blocks_world_object__rectangle__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_object__rectangle, cause, value)
#define f2blocks_world_object__rectangle__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_object__rectangle, cause)
#define f2blocks_world_object__rectangle__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_object__rectangle, cause)
#define f2blocks_world_object__rectangle__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_object__rectangle, cause)

defprimobject__static_slot__prototype(blocks_world_object__color);
#define f2blocks_world_object__color(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_object__color, cause)
#define f2blocks_world_object__color__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_object__color, cause, value)
#define f2blocks_world_object__color__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_object__color, cause)
#define f2blocks_world_object__color__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_object__color, cause)
#define f2blocks_world_object__color__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_object__color, cause)

defprimobject__static_slot__prototype(blocks_world_object__ignore_gravity);
#define f2blocks_world_object__ignore_gravity(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_object__ignore_gravity, cause)
#define f2blocks_world_object__ignore_gravity__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_object__ignore_gravity, cause, value)
#define f2blocks_world_object__ignore_gravity__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_object__ignore_gravity, cause)
#define f2blocks_world_object__ignore_gravity__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_object__ignore_gravity, cause)
#define f2blocks_world_object__ignore_gravity__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_object__ignore_gravity, cause)

defprimobject__static_slot__prototype(blocks_world_object__holding_object);
#define f2blocks_world_object__holding_object(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_object__holding_object, cause)
#define f2blocks_world_object__holding_object__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_object__holding_object, cause, value)
#define f2blocks_world_object__holding_object__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_object__holding_object, cause)
#define f2blocks_world_object__holding_object__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_object__holding_object, cause)
#define f2blocks_world_object__holding_object__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_object__holding_object, cause)



// blocks_world_physics

extern f2ptr __blocks_world_physics__symbol;
f2ptr f2blocks_world_physics__new(f2ptr cause, f2ptr objects);
boolean_t raw__blocks_world_physics__is_type(f2ptr cause, f2ptr this);

#define f2primobject__is__blocks_world_physics(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __blocks_world_physics__symbol)

defprimobject__static_slot__prototype(blocks_world_physics__objects);
#define f2blocks_world_physics__objects(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_physics__objects, cause)
#define f2blocks_world_physics__objects__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_physics__objects, cause, value)
#define f2blocks_world_physics__objects__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_physics__objects, cause)
#define f2blocks_world_physics__objects__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_physics__objects, cause)
#define f2blocks_world_physics__objects__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_physics__objects, cause)


typedef struct funk2_blocks_world_s {
  f2ptr red__symbol;
  f2ptr green__symbol;
  f2ptr blue__symbol;
  f2ptr white__symbol;
  f2ptr magenta__symbol;
  f2ptr yellow__symbol;
  
  f2ptr table__symbol;
  f2ptr block__symbol;
  f2ptr gripper__symbol;
} funk2_blocks_world_t;


// **

void f2__blocks_world__reinitialize_globalvars();
void f2__blocks_world__initialize();


#endif // F2__BLOCKS_WORLD__H


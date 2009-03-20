/* 
* Copyright (C) 2008, Brian Tanner

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#ifndef BLOCKS_WORLD_H
#define BLOCKS_WORLD_H


/***  RL GLUE COMMANDS *****/
/*These are implemented in game.c*/
void game_startup();
void new_game();
void play_one_step(int whichAction);


/*This is implemented in Customized_client_environment.c*/
int setup_rlglue_network();
void teardown_rlglue_network(int theConnection);
void runEnvironmentEventLoop(int theConnection);


/***  BLOCKS WORLD COMMANDS ******/

#include "funk2_primobjects_lite.h"

// blocks_world_rectangle

extern f2ptr __blocks_world_rectangle__symbol;
f2ptr f2blocks_world_rectangle__new(f2ptr cause, f2ptr x0, f2ptr y0, f2ptr x1, f2ptr y1);
bool  raw__blocks_world_rectanglep(f2ptr this, f2ptr cause);

#define f2primobject__is__blocks_world_rectangle(this, cause) raw__eq(cause, f2primobject__type(this, cause), __blocks_world_rectangle__symbol)

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
bool raw__blocks_world_colorp(f2ptr this, f2ptr cause);

#define f2primobject__is__blocks_world_color(this, cause) raw__eq(cause, f2primobject__type(this, cause), __blocks_world_color__symbol)

defprimobject__static_slot__prototype(blocks_world_color__name);
#define f2blocks_world_color__name(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world_color__name, cause)
#define f2blocks_world_color__name__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world_color__name, cause, value)
#define f2blocks_world_color__name__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world_color__name, cause)
#define f2blocks_world_color__name__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world_color__name, cause)
#define f2blocks_world_color__name__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world_color__name, cause)



// blocks_world_object

extern f2ptr __blocks_world_object__symbol;
f2ptr f2blocks_world_object__new(f2ptr cause, f2ptr name, f2ptr type, f2ptr rectangle, f2ptr color);
bool raw__blocks_world_objectp(f2ptr this, f2ptr cause);

#define f2primobject__is__blocks_world_object(this, cause) raw__eq(cause, f2primobject__type(this, cause), __blocks_world_object__symbol)

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



// blocks_world

extern f2ptr __blocks_world__symbol;
f2ptr f2blocks_world__new(f2ptr cause, f2ptr objects);
bool raw__blocks_worldp(f2ptr this, f2ptr cause);

#define f2primobject__is__blocks_world(this, cause) raw__eq(cause, f2primobject__type(this, cause), __blocks_world__symbol)

defprimobject__static_slot__prototype(blocks_world__objects);
#define f2blocks_world__objects(                   this, cause)        primobject__static_slot__accessor(         this, blocks_world__objects, cause)
#define f2blocks_world__objects__set(              this, cause, value) primobject__static_slot__set(              this, blocks_world__objects, cause, value)
#define f2blocks_world__objects__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, blocks_world__objects, cause)
#define f2blocks_world__objects__trace(            this, cause)        primobject__static_slot__trace(            this, blocks_world__objects, cause)
#define f2blocks_world__objects__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, blocks_world__objects, cause)


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


#endif

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

#ifndef F2__GTK__TYPES__H
#define F2__GTK__TYPES__H

#include "f2_processor_thread.h"


typedef struct funk2_gtk_callback_s      funk2_gtk_callback_t;
typedef struct funk2_gtk_callback_cons_s funk2_gtk_callback_cons_t;
typedef struct funk2_gtk_s               funk2_gtk_t;

struct funk2_gtk_callback_cons_s {
  funk2_gtk_callback_t*      callback;
  funk2_gtk_callback_cons_t* next;
};

struct funk2_gtk_s {
  funk2_processor_mutex_t    main_thread__mutex;
  boolean_t                  main_thread__active;
  funk2_processor_thread_t*  main_thread;
  
  funk2_processor_mutex_t    callbacks__mutex;
  funk2_gtk_callback_cons_t* callbacks;
  
  funk2_processor_mutex_t    callback_events__mutex;
  funk2_gtk_callback_cons_t* callback_events;
  funk2_gtk_callback_cons_t* callback_events__last_cons;
};

struct funk2_gtk_callback_s {
  funk2_gtk_t* gtk;
  f2ptr        funk;
  f2ptr        args;
};

#endif // F2__GTK__TYPES__H


#ifndef F2__GTK__H
#define F2__GTK__H

#include "f2_primfunks.h"

// gtk_widget

f2ptr f2gtk_widget__primobject_type__new(f2ptr cause);


// gtk_text_buffer

f2ptr f2gtk_text_buffer__primobject_type__new(f2ptr cause);


// gtk_callback

f2ptr f2gtk_callback__primobject_type__new(f2ptr cause);


// funk2_gtk

void funk2_gtk__init(funk2_gtk_t* this, int* argv, char*** argc);
void funk2_gtk__destroy(funk2_gtk_t* this);
void funk2_gtk__add_callback(funk2_gtk_t* this, funk2_gtk_callback_t* callback);
void funk2_gtk__add_callback_event(funk2_gtk_t* this, funk2_gtk_callback_t* callback);


// **

void f2__gtk__initialize();

#endif // F2__GTK__H

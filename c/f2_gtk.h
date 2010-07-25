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

typedef struct funk2_gtk_widget_s funk2_gtk_widget_t;
struct funk2_gtk_widget_s {
  u8*        name;
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget;
#endif // F2__GTK__SUPPORTED
};

typedef struct funk2_gtk_widget_cons_s funk2_gtk_widget_cons_t;
struct funk2_gtk_widget_cons_s {
  funk2_gtk_widget_t*             widget;
  struct funk2_gtk_widget_cons_s* next;
};

typedef struct funk2_gtk_s funk2_gtk_t;
struct funk2_gtk_s {
  funk2_processor_mutex_t   main_thread__mutex;
  boolean_t                 main_thread__active;
  funk2_processor_thread_t* main_thread;
  funk2_gtk_widget_cons_t*  widgets;
};

#endif // F2__GTK__TYPES__H


#ifndef F2__GTK__H
#define F2__GTK__H

#include "f2_primfunks.h"

// gtk_widget

f2ptr f2gtk_widget__primobject_type__new(f2ptr cause);


// funk2_gtk

void funk2_gtk__init(funk2_gtk_t* this, int* argv, char*** argc);
void funk2_gtk__destroy(funk2_gtk_t* this);

// funk2_gtk_widget

#ifdef F2__GTK__SUPPORTED
void funk2_gtk_widget__init(funk2_gtk_widget_t* this, u8* name, GtkWidget* gtk_widget);
void funk2_gtk_widget__destroy(funk2_gtk_widget_t* this);
#endif // F2__GTK__SUPPORTED

// **

void f2__gtk__initialize();

#endif // F2__GTK__H

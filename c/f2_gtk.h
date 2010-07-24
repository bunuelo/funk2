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

typedef struct funk2_gtk_s funk2_gtk_t;
struct funk2_gtk_s {
  funk2_processor_mutex_t   main_thread__mutex;
  boolean_t                 main_thread__active;
  funk2_processor_thread_t* main_thread;
};

#endif // F2__GTK__TYPES__H


#ifndef F2__GTK__H
#define F2__GTK__H

#include "f2_primfunks.h"

// funk2_gtk

void funk2_gtk__init(funk2_gtk_t* this, int* argv, char** argc);
void funk2_gtk__destroy(funk2_gtk_t* this);

// **

void f2__gtk__initialize();

#endif // F2__GTK__H

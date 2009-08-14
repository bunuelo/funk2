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

#ifndef F2__PRIMOBJECT_TYPE_HANDLER__H
#define F2__PRIMOBJECT_TYPE_HANDLER__H

#include "f2_primobjects.h"
#include "f2_primobject__stream.h"
#include "f2_primobject__hashtable.h"

typedef struct funk2_primobject_type_handler_s {
  funk2_processor_mutex_t type_hash_mutex;
  f2ptr                   type_hash;
} funk2_primobject_type_handler_t;

typedef struct funk2_primobject_object_types_s funk2_primobject_object_types_t;

struct funk2_primobject_object_types_s {
  funk2_object_type__place__slot_t            primobject_type_place;
  funk2_object_type__cons__slot_t             primobject_type_cons;
  funk2_object_type__doublelink__slot_t       primobject_type_doublelink;
  funk2_object_type__imagination_link__slot_t primobject_type_imagination_link;
  funk2_object_type__cfunk__slot_t            primobject_type_cfunk;
  funk2_object_type__metrocfunk__slot_t       primobject_type_metrocfunk;
  funk2_object_type__funk__slot_t             primobject_type_funk;
  funk2_object_type__metro__slot_t            primobject_type_metro;
  funk2_object_type__exception__slot_t        primobject_type_exception;
  funk2_object_type__bytecode__slot_t         primobject_type_bytecode;
  funk2_object_type__fiber__slot_t            primobject_type_fiber;
  funk2_object_type__processor__slot_t        primobject_type_processor;
  funk2_object_type__scheduler__slot_t        primobject_type_scheduler;
  funk2_object_type__event_subscriber__slot_t primobject_type_event_subscriber;
  funk2_object_type__cause__slot_t            primobject_type_cause;
  funk2_object_type__transframe__slot_t       primobject_type_transframe;
  funk2_object_type__bug__slot_t              primobject_type_bug;
  funk2_object_type__time__slot_t             primobject_type_time;
  funk2_object_type__size_2d__slot_t          primobject_type_size_2d;
  funk2_object_type__event__slot_t            primobject_type_event;
  funk2_object_type__bytecode_event__slot_t   primobject_type_bytecode_event;
  funk2_object_type__stream__slot_t           primobject_type_stream;
  funk2_object_type__hashtable__slot_t        primobject_type_hashtable;
  funk2_object_type__frame__slot_t            primobject_type_frame;
  funk2_object_type__environment__slot_t      primobject_type_environment;
  funk2_object_type__set__slot_t              primobject_type_set;
};

void funk2_primobject_type_handler__init(funk2_primobject_type_handler_t* this);
void funk2_primobject_type_handler__destroy(funk2_primobject_type_handler_t* this);
void funk2_primobject_type_handler__add_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type);
f2ptr funk2_primobject_type_handler__lookup_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name);
void funk2_primobject_type_handler__add_builtin_ptype_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);
void funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);

// **

void f2__primobject_type_handler__reinitialize_globalvars();
void f2__primobject_type_handler__initialize();


#endif // F2__PRIMOBJECT_TYPE_HANDLER__H

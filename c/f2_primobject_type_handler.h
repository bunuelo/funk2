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
#include "f2_primobject__set.h"
#include "f2_primobject__list.h"
#include "f2_primobject__circular_buffer.h"
#include "f2_physical_objects.h"

typedef struct funk2_primobject_type_handler_s {
  funk2_processor_mutex_t type_hash_mutex;
  f2ptr                   type_hash;
} funk2_primobject_type_handler_t;

void  funk2_primobject_type_handler__init(funk2_primobject_type_handler_t* this);
void  funk2_primobject_type_handler__destroy(funk2_primobject_type_handler_t* this);
void  funk2_primobject_type_handler__add_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type);
f2ptr funk2_primobject_type_handler__lookup_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name);
void  funk2_primobject_type_handler__add_builtin_ptype_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);
void  funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);
void  funk2_primobject_type_handler__add_builtin_frame_objects(funk2_primobject_type_handler_t* this, f2ptr cause);

f2ptr f2__add_type(f2ptr cause, f2ptr type_name, f2ptr type);
f2ptr f2__lookup_type(f2ptr cause, f2ptr type_name);

typedef struct funk2_primobject_object_types_s funk2_primobject_object_types_t;

struct funk2_primobject_object_types_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr type__set__symbol;
  f2ptr type__set__funk;
  f2ptr dynamic_slots__symbol;
  f2ptr dynamic_slots__funk;
  f2ptr dynamic_slots__set__symbol;
  f2ptr dynamic_slots__set__funk;
  f2ptr add_dynamic_slot_type_value__symbol;
  f2ptr add_dynamic_slot_type_value__funk;
  f2ptr dynamic_slot_type_value__symbol;
  f2ptr dynamic_slot_type_value__funk;
  f2ptr dynamic_slot_type_value__set__symbol;
  f2ptr dynamic_slot_type_value__set__funk;
  funk2_object_type__compound_object__slot_t    primobject_type_compound_object;
  funk2_object_type__place__slot_t              primobject_type_place;
  funk2_object_type__cons__slot_t               primobject_type_cons;
  funk2_object_type__doublelink__slot_t         primobject_type_doublelink;
  funk2_object_type__imagination_link__slot_t   primobject_type_imagination_link;
  funk2_object_type__cfunk__slot_t              primobject_type_cfunk;
  funk2_object_type__metrocfunk__slot_t         primobject_type_metrocfunk;
  funk2_object_type__funk__slot_t               primobject_type_funk;
  funk2_object_type__metro__slot_t              primobject_type_metro;
  funk2_object_type__exception__slot_t          primobject_type_exception;
  funk2_object_type__bytecode__slot_t           primobject_type_bytecode;
  funk2_object_type__fiber__slot_t              primobject_type_fiber;
  funk2_object_type__processor__slot_t          primobject_type_processor;
  funk2_object_type__scheduler__slot_t          primobject_type_scheduler;
  funk2_object_type__event_subscriber__slot_t   primobject_type_event_subscriber;
  funk2_object_type__cause__slot_t              primobject_type_cause;
  funk2_object_type__transframe__slot_t         primobject_type_transframe;
  funk2_object_type__bug__slot_t                primobject_type_bug;
  funk2_object_type__time__slot_t               primobject_type_time;
  funk2_object_type__size_2d__slot_t            primobject_type_size_2d;
  funk2_object_type__event__slot_t              primobject_type_event;
  funk2_object_type__bytecode_event__slot_t     primobject_type_bytecode_event;
  funk2_object_type__stream__slot_t             primobject_type_stream;
  funk2_object_type__hashtable__slot_t          primobject_type_hashtable;
  funk2_object_type__frame__slot_t              primobject_type_frame;
  funk2_object_type__environment__slot_t        primobject_type_environment;
  funk2_object_type__set__slot_t                primobject_type_set;
  funk2_object_type__list__slot_t               primobject_type_list;
  funk2_object_type__circular_buffer__slot_t    primobject_type_circular_buffer;
  funk2_object_type__physical_rotation__slot_t  primobject_type_physical_rotation;
  funk2_object_type__physical_position__slot_t  primobject_type_physical_position;
  funk2_object_type__physical_transform__slot_t primobject_type_physical_transform;
  funk2_object_type__physical_object__slot_t    primobject_type_physical_object;
  funk2_object_type__physical_place__slot_t     primobject_type_physical_place;
  funk2_object_type__physical_scene__slot_t     primobject_type_physical_scene;
};

// **

void f2__primobject_type_handler__reinitialize_globalvars();
void f2__primobject_type_handler__initialize();


#endif // F2__PRIMOBJECT_TYPE_HANDLER__H

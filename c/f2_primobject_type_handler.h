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

#ifndef F2__PRIMOBJECT_TYPE_HANDLER__H
#define F2__PRIMOBJECT_TYPE_HANDLER__H

#include "f2_primobjects.h"
#include "f2_fiber.h"
#include "f2_primobject__stream.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__set.h"
#include "f2_primobject__list.h"
#include "f2_primobject__doublelinklist.h"
#include "f2_primobject__circular_buffer.h"
#include "f2_bug.h"
#include "f2_physical_objects.h"
#include "f2_agent.h"
#include "f2_object_lattice.h"
#include "f2_primobject__hash.h"
#include "f2_cause.h"
#include "f2_graph.h"
#include "f2_perception_lattice.h"
#include "f2_primobject__largeinteger.h"
#include "f2_primobject__redblacktree.h"
#include "f2_package.h"
#include "f2_bruno_graph.h"
#include "f2_graph_match_error_correcting.h"
#include "f2_gtk.h"

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
  f2ptr object_type__symbol;
  f2ptr object_type__funk;
  f2ptr object_type__set__symbol;
  f2ptr object_type__set__funk;
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
  funk2_object_type__compound_object__slot_t                  primobject_type_compound_object;
  funk2_object_type__place__slot_t                            primobject_type_place;
  funk2_object_type__cons__slot_t                             primobject_type_cons;
  funk2_object_type__doublelink__slot_t                       primobject_type_doublelink;
  funk2_object_type__imagination_link__slot_t                 primobject_type_imagination_link;
  funk2_object_type__cfunk__slot_t                            primobject_type_cfunk;
  funk2_object_type__metrocfunk__slot_t                       primobject_type_metrocfunk;
  funk2_object_type__funk__slot_t                             primobject_type_funk;
  funk2_object_type__metro__slot_t                            primobject_type_metro;
  funk2_object_type__exception__slot_t                        primobject_type_exception;
  funk2_object_type__bytecode__slot_t                         primobject_type_bytecode;
  funk2_object_type__fiber__slot_t                            primobject_type_fiber;
  funk2_object_type__processor__slot_t                        primobject_type_processor;
  funk2_object_type__scheduler__slot_t                        primobject_type_scheduler;
  funk2_object_type__transframe__slot_t                       primobject_type_transframe;
  funk2_object_type__bug__slot_t                              primobject_type_bug;
  funk2_object_type__time__slot_t                             primobject_type_time;
  funk2_object_type__size_2d__slot_t                          primobject_type_size_2d;
  funk2_object_type__event__slot_t                            primobject_type_event;
  funk2_object_type__bytecode_event__slot_t                   primobject_type_bytecode_event;
  funk2_object_type__stream__slot_t                           primobject_type_stream;
  funk2_object_type__ptypehash__slot_t                        primobject_type_ptypehash;
  funk2_object_type__frame__slot_t                            primobject_type_frame;
  funk2_object_type__environment__slot_t                      primobject_type_environment;
  funk2_object_type__set__slot_t                              primobject_type_set;
  funk2_object_type__list__slot_t                             primobject_type_list;
  funk2_object_type__doublelinklist__slot_t                   primobject_type_doublelinklist;
  funk2_object_type__circular_buffer__slot_t                  primobject_type_circular_buffer;
  funk2_object_type__physical_rotation__slot_t                primobject_type_physical_rotation;
  funk2_object_type__physical_position__slot_t                primobject_type_physical_position;
  funk2_object_type__physical_transform__slot_t               primobject_type_physical_transform;
  funk2_object_type__physical_texture__slot_t                 primobject_type_physical_texture;
  funk2_object_type__physical_place__slot_t                   primobject_type_physical_place;
  funk2_object_type__physical_scene__slot_t                   primobject_type_physical_scene;
  funk2_object_type__agent__slot_t                            primobject_type_agent;
  funk2_object_type__object_lattice__slot_t                   primobject_type_object_lattice;
  funk2_object_type__object_lattice_node__slot_t              primobject_type_object_lattice_node;
  funk2_object_type__hash__slot_t                             primobject_type_hash;
  funk2_object_type__cause__slot_t                            primobject_type_cause;
  funk2_object_type__graph_node__slot_t                       primobject_type_graph_node;
  funk2_object_type__graph_edge__slot_t                       primobject_type_graph_edge;
  funk2_object_type__graph_edge_type__slot_t                  primobject_type_graph_edge_type;
  funk2_object_type__graph__slot_t                            primobject_type_graph;
  funk2_object_type__trans__slot_t                            primobject_type_trans;
  funk2_object_type__graph_variable__slot_t                   primobject_type_graph_variable;
  funk2_object_type__graph_map__slot_t                        primobject_type_graph_map;
  funk2_object_type__pattern_graph__slot_t                    primobject_type_pattern_graph;
  funk2_object_type__largeinteger__slot_t                     primobject_type_largeinteger;
  funk2_object_type__redblacktree__slot_t                     primobject_type_redblacktree;
  funk2_object_type__redblacktree_node__slot_t                primobject_type_redblacktree_node;
  funk2_object_type__source_expression__slot_t                primobject_type_source_expression;
  funk2_object_type__source__slot_t                           primobject_type_source;
  funk2_object_type__package__slot_t                          primobject_type_package;
  funk2_object_type__bruno_graph_node__slot_t                 primobject_type_bruno_graph_node;
  funk2_object_type__bruno_graph_edge__slot_t                 primobject_type_bruno_graph_edge;
  funk2_object_type__bruno_graph__slot_t                      primobject_type_bruno_graph;
  funk2_object_type__bruno_graph_isomorphism__slot_t          primobject_type_bruno_graph_isomorphism;
  funk2_object_type__bruno_decomposition_lattice_node__slot_t primobject_type_bruno_decomposition_lattice_node;
  funk2_object_type__bruno_decomposition_lattice__slot_t      primobject_type_bruno_decomposition_lattice;
  funk2_object_type__edit_sequence__slot_t                    primobject_type_edit_sequence;
};

// **

void f2__primobject_type_handler__reinitialize_globalvars();
void f2__primobject_type_handler__initialize();


#endif // F2__PRIMOBJECT_TYPE_HANDLER__H

// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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
#include "f2_optimize.h"
#include "f2_time.h"
#include "f2_fiber.h"
#include "f2_primobject__fiber_trigger.h"
#include "f2_primobject__stream.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__scheduler_ptypehash.h"
#include "f2_primobject__set.h"
#include "f2_primobject__list.h"
#include "f2_primobject__doublelinklist.h"
#include "f2_primobject__circular_buffer.h"
#include "f2_primobject__traced_cmutex.h"
#include "f2_bug.h"
#include "f2_primobject__hash.h"
#include "f2_cause.h"
#include "f2_primobject__largeinteger.h"
#include "f2_primobject__redblacktree.h"
#include "f2_package.h"
#include "f2_package_handler.h"
#include "f2_graph.h"
#include "f2_graph_match_error_correcting.h"
#include "f2_nil.h"
#include "f2_processor.h"
#include "f2_scheduler.h"
#include "f2_terminal_print.h"
#include "f2_natural_language.h"
#include "f2_partial_order.h"
#include "f2_dlfcn.h"
#include "f2_core_extension_funk.h"
#include "f2_core_extension.h"
#include "f2_primobject__file_handle.h"
#include "f2_primobject__matrix.h"
#include "f2_primobject__counter.h"
#include "f2_compile_x86.h"

typedef struct funk2_primobject_type_handler_s {
  funk2_processor_mutex_t type_hash_cmutex;
  f2ptr                   type_hash;
} funk2_primobject_type_handler_t;

void  funk2_primobject_type_handler__init                         (funk2_primobject_type_handler_t* this);
void  funk2_primobject_type_handler__destroy                      (funk2_primobject_type_handler_t* this);
void  funk2_primobject_type_handler__add_type                     (funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type);
f2ptr funk2_primobject_type_handler__lookup_type                  (funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name);
void  funk2_primobject_type_handler__add_nil_primobject           (funk2_primobject_type_handler_t* this, f2ptr cause);
void  funk2_primobject_type_handler__add_builtin_ptype_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);
void  funk2_primobject_type_handler__add_builtin_primobjects      (funk2_primobject_type_handler_t* this, f2ptr cause);
void  funk2_primobject_type_handler__add_builtin_frame_objects    (funk2_primobject_type_handler_t* this, f2ptr cause);

f2ptr f2__add_type   (f2ptr cause, f2ptr type_name, f2ptr type);
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
  funk2_object_type__bug__slot_t                              primobject_type_bug;
  funk2_object_type__time__slot_t                             primobject_type_time;
  funk2_object_type__relative_time__slot_t                    primobject_type_relative_time;
  funk2_object_type__size_2d__slot_t                          primobject_type_size_2d;
  funk2_object_type__event__slot_t                            primobject_type_event;
  funk2_object_type__bytecode_event__slot_t                   primobject_type_bytecode_event;
  funk2_object_type__stream_context__slot_t                   primobject_type_stream_context;
  funk2_object_type__stream__slot_t                           primobject_type_stream;
  funk2_object_type__ptypehash__slot_t                        primobject_type_ptypehash;
  funk2_object_type__scheduler_ptypehash__slot_t              primobject_type_scheduler_ptypehash;
  funk2_object_type__fiber_trigger__slot_t                    primobject_type_fiber_trigger;
  funk2_object_type__frame__slot_t                            primobject_type_frame;
  funk2_object_type__environment__slot_t                      primobject_type_environment;
  funk2_object_type__set__slot_t                              primobject_type_set;
  funk2_object_type__list__slot_t                             primobject_type_list;
  funk2_object_type__doublelinklist__slot_t                   primobject_type_doublelinklist;
  funk2_object_type__circular_buffer__slot_t                  primobject_type_circular_buffer;
  funk2_object_type__hash__slot_t                             primobject_type_hash;
  funk2_object_type__cause_group_interaction__slot_t          primobject_type_cause_group_interaction;
  funk2_object_type__cause_group__slot_t                      primobject_type_cause_group;
  funk2_object_type__cause__slot_t                            primobject_type_cause;
  funk2_object_type__largeinteger__slot_t                     primobject_type_largeinteger;
  funk2_object_type__redblacktree__slot_t                     primobject_type_redblacktree;
  funk2_object_type__redblacktree_node__slot_t                primobject_type_redblacktree_node;
  funk2_object_type__source_expression__slot_t                primobject_type_source_expression;
  funk2_object_type__source__slot_t                           primobject_type_source;
  funk2_object_type__package__slot_t                          primobject_type_package;
  funk2_object_type__package_handler__slot_t                  primobject_type_package_handler;
  funk2_object_type__graph_node__slot_t                       primobject_type_graph_node;
  funk2_object_type__graph_edge__slot_t                       primobject_type_graph_edge;
  funk2_object_type__graph__slot_t                            primobject_type_graph;
  funk2_object_type__graph_isomorphism__slot_t                primobject_type_graph_isomorphism;
  funk2_object_type__graph_decomposition_lattice_node__slot_t primobject_type_graph_decomposition_lattice_node;
  funk2_object_type__graph_decomposition_lattice__slot_t      primobject_type_graph_decomposition_lattice;
  funk2_object_type__graph_edit_sequence__slot_t              primobject_type_graph_edit_sequence;
  funk2_object_type__traced_cmutex__slot_t                    primobject_type_traced_cmutex;
  funk2_object_type__fiber_stack_trace__slot_t                primobject_type_fiber_stack_trace;
  funk2_object_type__fiber_stack_trace_block__slot_t          primobject_type_fiber_stack_trace_block;
  funk2_object_type__partial_order_node__slot_t               primobject_type_partial_order_node;
  funk2_object_type__optimize_bytecode__slot_t                primobject_type_optimize_bytecode;
  funk2_object_type__optimize_chunk__slot_t                   primobject_type_optimize_chunk;
  funk2_object_type__optimize_transition__slot_t              primobject_type_optimize_transition;
  funk2_object_type__optimize_data__slot_t                    primobject_type_optimize_data;
  funk2_object_type__optimize_fiber__slot_t                   primobject_type_optimize_fiber;
  funk2_object_type__optimize_context__slot_t                 primobject_type_optimize_context;
  funk2_object_type__file_handle__slot_t                      primobject_type_file_handle;
  funk2_object_type__matrix__slot_t                           primobject_type_matrix;
  funk2_object_type__counter__slot_t                          primobject_type_counter;
  funk2_object_type__machine_code_chunk__slot_t               primobject_type_machine_code_chunk;
  // frame objects
  funk2_object_type__terminal_print_frame__slot_t             primobject_type_terminal_print_frame;
  funk2_object_type__clause__slot_t                           primobject_type_clause;
  funk2_object_type__wh_rank_shift_clause__slot_t             primobject_type_wh_rank_shift_clause;
  funk2_object_type__noun_group__slot_t                       primobject_type_noun_group;
  funk2_object_type__preposition_group__slot_t                primobject_type_preposition_group;
  funk2_object_type__adjective_group__slot_t                  primobject_type_adjective_group;
  funk2_object_type__verb_group__slot_t                       primobject_type_verb_group;
  funk2_object_type__combination_group__slot_t                primobject_type_combination_group;
  funk2_object_type__adjective_word__slot_t                   primobject_type_adjective_word;
  funk2_object_type__adverb_word__slot_t                      primobject_type_adverb_word;
  funk2_object_type__binder_word__slot_t                      primobject_type_binder_word;
  funk2_object_type__classifier_word__slot_t                  primobject_type_classifier_word;
  funk2_object_type__determiner_word__slot_t                  primobject_type_determiner_word;
  funk2_object_type__noun_word__slot_t                        primobject_type_noun_word;
  funk2_object_type__number_word__slot_t                      primobject_type_number_word;
  funk2_object_type__number_determiner_word__slot_t           primobject_type_number_determiner_word;
  funk2_object_type__ordinal_word__slot_t                     primobject_type_ordinal_word;
  funk2_object_type__preposition_word__slot_t                 primobject_type_preposition_word;
  funk2_object_type__pronoun_word__slot_t                     primobject_type_pronoun_word;
  funk2_object_type__proper_noun_word__slot_t                 primobject_type_proper_noun_word;
  funk2_object_type__particle_word__slot_t                    primobject_type_particle_word;
  funk2_object_type__question_adjunct_word__slot_t            primobject_type_question_adjunct_word;
  funk2_object_type__thing_pronoun_word__slot_t               primobject_type_thing_pronoun_word;
  funk2_object_type__infinitive_helper_word__slot_t           primobject_type_infinitive_helper_word;
  funk2_object_type__verb_word__slot_t                        primobject_type_verb_word;
  funk2_object_type__parse_tree_node__slot_t                  primobject_type_parse_tree_node;
  funk2_object_type__parse_tree__slot_t                       primobject_type_parse_tree;
  funk2_object_type__dlfcn_dynamic_library__slot_t            primobject_type_dlfcn_dynamic_library;
  funk2_object_type__dlfcn_dynamic_library_handler__slot_t    primobject_type_dlfcn_dynamic_library_handler;
  funk2_object_type__core_extension_funk__slot_t              primobject_type_core_extension_funk;
  funk2_object_type__core_extension__slot_t                   primobject_type_core_extension;
  funk2_object_type__core_extension_handler__slot_t           primobject_type_core_extension_handler;
};

// **

void f2__primobject_type_handler__reinitialize_globalvars();
void f2__primobject_type_handler__initialize();


#endif // F2__PRIMOBJECT_TYPE_HANDLER__H

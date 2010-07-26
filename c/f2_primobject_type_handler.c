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

#include "funk2.h"

void funk2_primobject_type_handler__init(funk2_primobject_type_handler_t* this) {
  funk2_processor_mutex__init(&(this->type_hash_mutex));
  this->type_hash = nil;
}

void funk2_primobject_type_handler__destroy(funk2_primobject_type_handler_t* this) {
  funk2_processor_mutex__destroy(&(this->type_hash_mutex));
}

void funk2_primobject_type_handler__reset_type_hash(funk2_primobject_type_handler_t* this, f2ptr cause) {
  funk2_processor_mutex__user_lock(&(this->type_hash_mutex));
  f2ptr new_type_hash = raw__ptypehash__new(cause, 5);
  this->type_hash = new_type_hash;
  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen("type_hash"), (u8*)"type_hash"), new_type_hash);
  funk2_processor_mutex__unlock(&(this->type_hash_mutex));
}

void funk2_primobject_type_handler__add_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type) {
  if (this->type_hash == nil) {funk2_primobject_type_handler__reset_type_hash(this, cause);}
  funk2_processor_mutex__user_lock(&(this->type_hash_mutex));
  f2__ptypehash__add(cause, this->type_hash, type_name, type);
  funk2_processor_mutex__unlock(&(this->type_hash_mutex));
}

f2ptr f2__add_type(f2ptr cause, f2ptr type_name, f2ptr type) {funk2_primobject_type_handler__add_type(&(__funk2.primobject_type_handler), cause, type_name, type); return nil;}
def_pcfunk2(add_type, type_name, type, return f2__add_type(this_cause, type_name, type));

f2ptr funk2_primobject_type_handler__types(funk2_primobject_type_handler_t* this, f2ptr cause) {
  f2ptr types = nil;
  if (this->type_hash == nil) {funk2_primobject_type_handler__reset_type_hash(this, cause);}
  funk2_processor_mutex__user_lock(&(this->type_hash_mutex));
  ptypehash__value__iteration(cause, this->type_hash, value,
			      types = f2cons__new(cause, value, types);
			      );
  funk2_processor_mutex__unlock(&(this->type_hash_mutex));
  return types;
}

f2ptr f2__system__types(f2ptr cause) {
  return funk2_primobject_type_handler__types(&(__funk2.primobject_type_handler), cause);
}
def_pcfunk0(system__types, return f2__system__types(this_cause));

f2ptr f2__system__type_names(f2ptr cause) {
  f2ptr fiber      = f2__this__fiber(cause);
  f2ptr type_names = nil;
  f2ptr types      = f2__system__types(cause);
  {
    f2ptr iter = types;
    while (iter) {
      f2ptr type = f2__cons__car(cause, iter);
      f2ptr get_type_funk = f2__primobject_type__lookup_slot_type_funk(cause, type, new__symbol(cause, "get"), new__symbol(cause, "type"));
      f2ptr type_name = f2__force_funk_apply(cause, fiber, get_type_funk, f2cons__new(cause, nil, nil));
      type_names = f2cons__new(cause, type_name, type_names);
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return type_names;
}
def_pcfunk0(system__type_names, return f2__system__type_names(this_cause));

f2ptr funk2_primobject_type_handler__lookup_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name) {
  if (this->type_hash == nil) {funk2_primobject_type_handler__reset_type_hash(this, cause);}
  funk2_processor_mutex__user_lock(&(this->type_hash_mutex));
  f2ptr result = f2__ptypehash__lookup(cause, this->type_hash, type_name);
  funk2_processor_mutex__unlock(&(this->type_hash_mutex));
  return result;
}

f2ptr f2__lookup_type(f2ptr cause, f2ptr type_name) {return funk2_primobject_type_handler__lookup_type(&(__funk2.primobject_type_handler), cause, type_name);}
def_pcfunk1(lookup_type, type_name, return f2__lookup_type(this_cause, type_name));

void funk2_primobject_type_handler__add_builtin_ptype_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  {char* type_name = "ptype";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2ptype__primobject_type__new(cause));}
  {char* type_name = "integer";      funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),      f2integer__primobject_type__new(cause));}
  {char* type_name = "double";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2double__primobject_type__new(cause));}
  {char* type_name = "float";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2float__primobject_type__new(cause));}
  {char* type_name = "pointer";      funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),      f2pointer__primobject_type__new(cause));}
  {char* type_name = "gfunkptr";     funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),     f2gfunkptr__primobject_type__new(cause));}
  {char* type_name = "mutex";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2mutex__primobject_type__new(cause));}
  {char* type_name = "char";         funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),         f2char__primobject_type__new(cause));}
  {char* type_name = "string";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2string__primobject_type__new_aux(cause));}
  {char* type_name = "symbol";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2symbol__primobject_type__new(cause));}
  {char* type_name = "chunk";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2chunk__primobject_type__new(cause));}
  {char* type_name = "simple_array"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2simple_array__primobject_type__new(cause));}
  {char* type_name = "traced_array"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2traced_array__primobject_type__new(cause));}
  {char* type_name = "larva";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2larva__primobject_type__new(cause));}
  {char* type_name = "array";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2array__primobject_type__new(cause));} // interface defined in f2_array.c
}

void funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  {char* type_name = "primobject";                       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                       f2primobject__primobject_type__new(cause));}
  {char* type_name = "primobject_type";                  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                  f2primobject_type__primobject_type__new(cause));}
  {char* type_name = "compound_object";                  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                  f2compound_object__primobject_type__new(cause));}
  {char* type_name = "place";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2place__primobject_type__new(cause));}
  {char* type_name = "cons";                             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                             f2cons__primobject_type__new_aux(cause));}
  {char* type_name = "doublelink";                       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                       f2doublelink__primobject_type__new(cause));}
  {char* type_name = "imagination_link";                 funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                 f2imagination_link__primobject_type__new(cause));}
  {char* type_name = "cfunk";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2cfunk__primobject_type__new(cause));}
  {char* type_name = "metrocfunk";                       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                       f2metrocfunk__primobject_type__new(cause));}
  {char* type_name = "funk";                             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                             f2funk__primobject_type__new(cause));}
  {char* type_name = "metro";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2metro__primobject_type__new(cause));}
  {char* type_name = "exception";                        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                        f2exception__primobject_type__new(cause));}
  {char* type_name = "bytecode";                         funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                         f2bytecode__primobject_type__new(cause));}
  {char* type_name = "fiber";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2fiber__primobject_type__new_aux(cause));}
  {char* type_name = "processor";                        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                        f2processor__primobject_type__new(cause));}
  {char* type_name = "scheduler";                        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                        f2scheduler__primobject_type__new(cause));}
  {char* type_name = "transframe";                       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                       f2transframe__primobject_type__new(cause));}
  {char* type_name = "bug";                              funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                              f2bug__primobject_type__new(cause));}
  {char* type_name = "time";                             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                             f2time__primobject_type__new_aux(cause));}
  {char* type_name = "size_2d";                          funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                          f2size_2d__primobject_type__new(cause));}
  {char* type_name = "event";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2event__primobject_type__new(cause));}
  {char* type_name = "bytecode_event";                   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                   f2bytecode_event__primobject_type__new(cause));}
  {char* type_name = "stream";                           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                           f2stream__primobject_type__new_aux(cause));}
  {char* type_name = "ptypehash";                        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                        f2ptypehash__primobject_type__new_aux(cause));}
  {char* type_name = "frame";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2frame__primobject_type__new_aux(cause));}
  {char* type_name = "environment";                      funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                      f2environment__primobject_type__new_aux(cause));}
  {char* type_name = "set";                              funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                              f2set__primobject_type__new_aux(cause));}
  {char* type_name = "list";                             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                             f2list__primobject_type__new_aux(cause));}
  {char* type_name = "doublelinklist";                   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                   f2doublelinklist__primobject_type__new_aux(cause));}
  {char* type_name = "circular_buffer";                  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                  f2circular_buffer__primobject_type__new_aux(cause));}
  {char* type_name = "physical_rotation";                funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                f2physical_rotation__primobject_type__new(cause));}
  {char* type_name = "physical_position";                funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                f2physical_position__primobject_type__new(cause));}
  {char* type_name = "physical_transform";               funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),               f2physical_transform__primobject_type__new(cause));}
  {char* type_name = "physical_texture";                 funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                 f2physical_texture__primobject_type__new(cause));}
  {char* type_name = "physical_object";                  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                  f2physical_object__primobject_type__new(cause));}
  {char* type_name = "physical_place";                   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                   f2physical_place__primobject_type__new(cause));}
  {char* type_name = "physical_scene";                   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                   f2physical_scene__primobject_type__new(cause));}
  {char* type_name = "agent";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2agent__primobject_type__new(cause));}
  {char* type_name = "object_lattice";                   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                   f2object_lattice__primobject_type__new(cause));}
  {char* type_name = "object_lattice_node";              funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),              f2object_lattice_node__primobject_type__new(cause));}
  {char* type_name = "hash";                             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                             f2hash__primobject_type__new_aux(cause));}
  {char* type_name = "cause";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2cause__primobject_type__new_aux(cause));}
  {char* type_name = "graph_node";                       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                       f2graph_node__primobject_type__new(cause));}
  {char* type_name = "graph_edge";                       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                       f2graph_edge__primobject_type__new(cause));}
  {char* type_name = "graph_edge_type";                  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                  f2graph_edge_type__primobject_type__new(cause));}
  {char* type_name = "graph";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2graph__primobject_type__new_aux(cause));}
  {char* type_name = "trans";                            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                            f2trans__primobject_type__new_aux(cause));}
  {char* type_name = "graph_variable";                   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                   f2graph_variable__primobject_type__new_aux(cause));}
  {char* type_name = "graph_map";                        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                        f2graph_map__primobject_type__new(cause));}
  {char* type_name = "pattern_graph";                    funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                    f2pattern_graph__primobject_type__new(cause));}
  {char* type_name = "largeinteger";                     funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                     f2largeinteger__primobject_type__new(cause));}
  {char* type_name = "redblacktree";                     funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                     f2redblacktree__primobject_type__new(cause));}
  {char* type_name = "redblacktree_node";                funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                f2redblacktree_node__primobject_type__new(cause));}
  {char* type_name = "source_expression";                funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                f2source_expression__primobject_type__new_aux(cause));}
  {char* type_name = "source";                           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                           f2source__primobject_type__new_aux(cause));}
  {char* type_name = "package";                          funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                          f2package__primobject_type__new_aux(cause));}
  {char* type_name = "bruno_graph_node";                 funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                 f2bruno_graph_node__primobject_type__new(cause));}
  {char* type_name = "bruno_graph_edge";                 funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                 f2bruno_graph_edge__primobject_type__new(cause));}
  {char* type_name = "bruno_graph";                      funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),                      f2bruno_graph__primobject_type__new(cause));}
  {char* type_name = "bruno_graph_isomorphism";          funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),          f2bruno_graph_isomorphism__primobject_type__new(cause));}
  {char* type_name = "bruno_decomposition_lattice_node"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2bruno_decomposition_lattice_node__primobject_type__new(cause));}
  {char* type_name = "bruno_decomposition_lattice";      funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),      f2bruno_decomposition_lattice__primobject_type__new(cause));}
  {char* type_name = "ecs_edit_sequence";                funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),      f2ecs_edit_sequence__primobject_type__new(cause));}
  
}

void funk2_primobject_type_handler__add_builtin_frame_objects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  {char* type_name = "physical_sim_object"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2physical_sim_object__primobject_type__new(cause));}
  {char* type_name = "gtk_widget";          funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),          f2gtk_widget__primobject_type__new(cause));}
  {char* type_name = "gtk_text_buffer";     funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),     f2gtk_text_buffer__primobject_type__new(cause));}
  {char* type_name = "gtk_callback";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2gtk_callback__primobject_type__new(cause));}
}

// **

void f2__primobject_type_handler__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_primobject_type_handler_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__primobject_type_handler__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject_type_handler", "", &f2__primobject_type_handler__reinitialize_globalvars);
  
  f2__primobject_type_handler__reinitialize_globalvars();
  
  f2__primcfunk__init__2(add_type,    type_name, type, "Adds the symbolic type_name associated with type to the primobject_type_handler.");
  f2__primcfunk__init__1(lookup_type, type_name,       "Returns the type associated with the symbolic type_name, or nil if no such type has been added to the primobject_type_handler.");
  f2__primcfunk__init__0(system__types,                "Returns a new list of all of the types currently defined in the system.");
  f2__primcfunk__init__0(system__type_names,           "Returns a new list of all of the type names currently defined in the system.");
  
}


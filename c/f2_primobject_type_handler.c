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
  f2ptr new_type_hash = raw__hashtable__new(cause, 5);
  this->type_hash = new_type_hash;
  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen("type_hash"), (u8*)"type_hash"), new_type_hash);
  funk2_processor_mutex__unlock(&(this->type_hash_mutex));
}

void funk2_primobject_type_handler__add_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type) {
  if (this->type_hash == nil) {funk2_primobject_type_handler__reset_type_hash(this, cause);}
  funk2_processor_mutex__user_lock(&(this->type_hash_mutex));
  f2__hashtable__add(cause, this->type_hash, type_name, type);
  funk2_processor_mutex__unlock(&(this->type_hash_mutex));
}

f2ptr f2__add_type(f2ptr cause, f2ptr type_name, f2ptr type) {funk2_primobject_type_handler__add_type(&(__funk2.primobject_type_handler), cause, type_name, type); return nil;}
def_pcfunk2(add_type, type_name, type, return f2__add_type(this_cause, type_name, type));

f2ptr funk2_primobject_type_handler__lookup_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name) {
  if (this->type_hash == nil) {funk2_primobject_type_handler__reset_type_hash(this, cause);}
  funk2_processor_mutex__user_lock(&(this->type_hash_mutex));
  f2ptr result = f2__hashtable__lookup(cause, this->type_hash, type_name);
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
  {char* type_name = "string";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2string__primobject_type__new(cause));}
  {char* type_name = "symbol";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2symbol__primobject_type__new(cause));}
  {char* type_name = "chunk";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2chunk__primobject_type__new(cause));}
  {char* type_name = "simple_array"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2simple_array__primobject_type__new(cause));}
  {char* type_name = "traced_array"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2traced_array__primobject_type__new(cause));}
  {char* type_name = "larva";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2larva__primobject_type__new(cause));}
}

void funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  {char* type_name = "primobject";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2primobject__primobject_type__new(cause));}
  {char* type_name = "place";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2place__primobject_type__new(cause));}
  {char* type_name = "cons";             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),             f2cons__primobject_type__new(cause));}
  {char* type_name = "doublelink";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2doublelink__primobject_type__new(cause));}
  {char* type_name = "imagination_link"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2imagination_link__primobject_type__new(cause));}
  {char* type_name = "cfunk";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2cfunk__primobject_type__new(cause));}
  {char* type_name = "metrocfunk";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2metrocfunk__primobject_type__new(cause));}
  {char* type_name = "funk";             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),             f2funk__primobject_type__new(cause));}
  {char* type_name = "metro";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2metro__primobject_type__new(cause));}
  {char* type_name = "exception";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2exception__primobject_type__new(cause));}
  {char* type_name = "bytecode";         funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),         f2bytecode__primobject_type__new(cause));}
  {char* type_name = "fiber";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2fiber__primobject_type__new(cause));}
  {char* type_name = "processor";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2processor__primobject_type__new(cause));}
  {char* type_name = "scheduler";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2scheduler__primobject_type__new(cause));}
  {char* type_name = "event_subscriber"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2event_subscriber__primobject_type__new(cause));}
  {char* type_name = "cause";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2cause__primobject_type__new(cause));}
  {char* type_name = "transframe";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2transframe__primobject_type__new(cause));}
  {char* type_name = "bug";              funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),              f2bug__primobject_type__new(cause));}
  {char* type_name = "time";             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),             f2time__primobject_type__new(cause));}
  {char* type_name = "size_2d";          funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),          f2size_2d__primobject_type__new(cause));}
  {char* type_name = "event";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2event__primobject_type__new(cause));}
  {char* type_name = "bytecode_event";   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),   f2bytecode_event__primobject_type__new(cause));}
  {char* type_name = "stream";           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),           f2stream__primobject_type__new(cause));}
  {char* type_name = "hashtable";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2hashtable__primobject_type__new(cause));}
  {char* type_name = "frame";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2frame__primobject_type__new(cause));}
  {char* type_name = "environment";      funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),      f2environment__primobject_type__new(cause));}
  {char* type_name = "set";              funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),              f2set__primobject_type__new(cause));}
  {char* type_name = "list";             funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),             f2list__primobject_type__new(cause));}
  {char* type_name = "circular_buffer";  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),  f2circular_buffer__primobject_type__new(cause));}
}

void funk2_primobject_type_handler__add_builtin_frame_objects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  {char* type_name = "physical_object"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2physical_object__primobject_type__new(cause));}
  {char* type_name = "delta";           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2delta__primobject_type__new(cause));}
  {char* type_name = "gamma";           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2gamma__primobject_type__new(cause));}
  {char* type_name = "beta";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2beta__primobject_type__new(cause));}
  {char* type_name = "alpha";           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2alpha__primobject_type__new(cause));}
}

// **

void f2__primobject_type_handler__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_primobject_type_handler_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__primobject_type_handler__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject_type_handler", "", &f2__primobject_type_handler__reinitialize_globalvars);
  
  f2__primobject_type_handler__reinitialize_globalvars();
  
  f2__primcfunk__init__2(add_type, type_name, type, "adds the symbolic type_name associated with type to the primobject_type_handler.");
  f2__primcfunk__init__1(lookup_type, type_name, "returns the type associated with the symbolic type_name, or nil if no such type has been added to the primobject_type_handler.");
}


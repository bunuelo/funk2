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
  this->type_hash = nil;
}

void funk2_primobject_type_handler__destroy(funk2_primobject_type_handler_t* this) {
}

void funk2_primobject_type_handler__add_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type) {
  if (this->type_hash == nil) {this->type_hash = raw__hashtable__new(cause, 5);}
  f2__hashtable__add_keyvalue_pair(cause, this->type_hash, type_name, type);
}

f2ptr funk2_primobject_type_handler__lookup_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name) {
  if (this->type_hash == nil) {this->type_hash = raw__hashtable__new(cause, 5);}
  return f2__hashtable__lookup_value(this->type_hash, cause, type_name);
}



void funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  
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
  {char* type_name = "thread";           funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),           f2thread__primobject_type__new(cause));}
  {char* type_name = "processor";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2processor__primobject_type__new(cause));}
  {char* type_name = "scheduler";        funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),        f2scheduler__primobject_type__new(cause));}
  {char* type_name = "event_subscriber"; funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name), f2event_subscriber__primobject_type__new(cause));}
  {char* type_name = "cause";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2cause__primobject_type__new(cause));}
  {char* type_name = "transframe";       funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),       f2transframe__primobject_type__new(cause));}
  {char* type_name = "bug";              funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),              f2bug__primobject_type__new(cause));}
  {char* type_name = "size_2d";          funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),          f2size_2d__primobject_type__new(cause));}
  {char* type_name = "event";            funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),            f2event__primobject_type__new(cause));}
  {char* type_name = "bytecode_event";   funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen(type_name), (u8*)type_name),   f2bytecode_event__primobject_type__new(cause));}
  
}








































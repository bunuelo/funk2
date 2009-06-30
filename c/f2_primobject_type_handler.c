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
  if (this->type_hash == nil) {
    printf("\nfunk2_primobject_type_handler__add_type error: type_hash not initialized yet.\n"); fflush(stdout);
    error(nil, "funk2_primobject_type_handler__add_type error: type_hash not initialized yet.");
  }
  
}

void funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause) {
  if (this->type_hash == nil) {
    this->type_hash = raw__hashtable__new(cause, 5);
  }
  
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("place"),            (u8*)"place"),            f2place__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("cons"),             (u8*)"cons"),             f2cons__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("doublelink"),       (u8*)"doublelink"),       f2doublelink__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("imagination_link"), (u8*)"imagination_link"), f2imagination_link__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("cfunk"),            (u8*)"cfunk"),            f2cfunk__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("metrocfunk"),       (u8*)"metrocfunk"),       f2metrocfunk__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("funk"),             (u8*)"funk"),             f2funk__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("metro"),            (u8*)"metro"),            f2metro__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("exception"),        (u8*)"exception"),        f2exception__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("bytecode"),         (u8*)"bytecode"),         f2bytecode__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("thread"),           (u8*)"thread"),           f2thread__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("processor"),        (u8*)"processor"),        f2processor__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("scheduler"),        (u8*)"scheduler"),        f2scheduler__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("event"),            (u8*)"event"),            f2event_subscriber__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("cause"),            (u8*)"cause"),            f2cause__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("transframe"),       (u8*)"transframe"),       f2transframe__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("bug"),              (u8*)"bug"),              f2bug__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("size_2d"),          (u8*)"size_2d"),          f2size_2d__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("event"),            (u8*)"event"),            f2event__primobject_type__new(cause));
  funk2_primobject_type_handler__add_type(this, cause, f2symbol__new(cause, strlen("bytecode_event"),   (u8*)"bytecode_event"),   f2bytecode_event__primobject_type__new(cause));
  
}








































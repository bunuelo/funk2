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

typedef struct funk2_primobject_type_handler_s {
  f2ptr type_hash;
} funk2_primobject_type_handler_t;

void funk2_primobject_type_handler__init(funk2_primobject_type_handler_t* this);
void funk2_primobject_type_handler__destroy(funk2_primobject_type_handler_t* this);
void funk2_primobject_type_handler__add_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name, f2ptr type);
f2ptr funk2_primobject_type_handler__lookup_type(funk2_primobject_type_handler_t* this, f2ptr cause, f2ptr type_name);
void funk2_primobject_type_handler__add_builtin_ptype_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);
void funk2_primobject_type_handler__add_builtin_primobjects(funk2_primobject_type_handler_t* this, f2ptr cause);

#endif // F2__PRIMOBJECT_TYPE_HANDLER__H

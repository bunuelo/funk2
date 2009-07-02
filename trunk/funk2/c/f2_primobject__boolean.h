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

#ifndef F2__PRIMOBJECT_BOOLEAN__H
#define F2__PRIMOBJECT_BOOLEAN__H

#include "f2_primobjects.h"

// boolean

extern f2ptr __boolean__symbol;
boolean_t raw__boolean__is_type(f2ptr cause, f2ptr this);
f2ptr f2__boolean__is_type(f2ptr cause, f2ptr this);
f2ptr f2boolean__new(f2ptr cause, f2ptr integer_value);
#define f2primobject__is_boolean(this, cause) raw__eq(cause, f2primobject__type(this, cause), __boolean__symbol)

defprimobject__static_slot__prototype(boolean__integer_value);
#define      f2boolean__integer_value(            this)               primobject__static_slot(            this, boolean__integer_value)
#define      f2boolean__integer_value__set(       this, cause, value) primobject__static_slot__set(       this, boolean__integer_value, cause, value)
#define      f2boolean__integer_value__tracing_on(this, cause, value) primobject__static_slot__tracing_on(this, boolean__integer_value)
#define      f2boolean__integer_value__prev(      this, cause, value) primobject__static_slot__prev(      this, boolean__integer_value)
#define      f2boolean__integer_value__cause(     this, cause, value) primobject__static_slot__cause(     this, boolean__integer_value)

#endif // F2__PRIMOBJECT_BOOLEAN__H




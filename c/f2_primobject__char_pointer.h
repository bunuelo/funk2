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

#ifndef F2__PRIMOBJECT__CHAR_POINTER__H
#define F2__PRIMOBJECT__CHAR_POINTER__H

#include "f2_primobjects.h"
#include "f2_primobject__boolean.h"

// char_pointer

extern f2ptr __char_pointer__symbol;
boolean_t raw__char_pointer__is_type(f2ptr cause, f2ptr this);
f2ptr f2__char_pointer__is_type(f2ptr cause, f2ptr this);
f2ptr f2char_pointer__new(f2ptr cause, f2ptr pointer_value);
#define      f2primobject__is_char_pointer(this, cause)             raw__eq(cause, f2primobject__object_type(this, cause), __char_pointer__symbol)

defprimobject__static_slot__prototype(char_pointer__pointer_value);
#define      f2char_pointer__pointer_value(this, cause)             primobject__static_slot__accessor(  this, char_pointer__pointer_value, cause)
#define      f2char_pointer__pointer_value__set(this, cause, value) primobject__static_slot__set(       this, char_pointer__pointer_value, cause, value)
#define      f2char_pointer__pointer_value__tracing_on(this, cause) primobject__static_slot__tracing_on(this, char_pointer__pointer_value, cause)
#define      f2char_pointer__pointer_value__prev(this, cause)       primobject__static_slot__prev(      this, char_pointer__pointer_value, cause)
#define      f2char_pointer__pointer_value__cause(this, cause)      primobject__static_slot__cause(     this, char_pointer__pointer_value, cause)

#endif // F2__PRIMOBJECT__CHAR_POINTER__H




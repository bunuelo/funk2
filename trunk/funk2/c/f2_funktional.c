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


boolean_t raw__exp__is_immutable(f2ptr cause, f2ptr this) {
  if (! this) {
    return boolean__true;
  }
  ptype_t ptype = f2ptype__raw(this, cause);
  switch(ptype) {
  case ptype_integer:
  case ptype_double:
  case ptype_float:
  case ptype_pointer:
  case ptype_gfunkptr:
  case ptype_mutex:
  case ptype_char:
  case ptype_string:
  case ptype_symbol:
  case ptype_larva:
    return boolean__true;
  case ptype_chunk:
  case ptype_simple_array:
    return (f2simple_array__immutable(this, cause) != 0);
  case ptype_traced_array:
    return (f2traced_array__immutable(this, cause) != 0);
  default:
    error(nil, "raw__exp__is_funktional: shouldn't get here.");
  }
}

f2ptr f2__exp__is_immutable(f2ptr cause, f2ptr this) {
  return f2bool__new(raw__exp__is_immutable(cause, this));
}


boolean_t raw__funkable__is_funktional(f2ptr cause, f2ptr this) {
  if (raw__cfunk__is_type(cause, this)) {
    return (f2cfunk__is_funktional(this, cause) != nil);
  }
  if (raw__metrocfunk__is_type(cause, this)) {
    return (f2metrocfunk__is_funktional(this, cause) != nil);
  }
  if (raw__funk__is_type(cause, this)) {
    return (f2funk__is_funktional(this, cause) != nil);
  }
  if (raw__metro__is_type(cause, this)) {
    return (f2metro__is_funktional(this, cause) != nil);
  }
  error(nil, "raw__funkable__is_funktional (this is not funkable)");
}

f2ptr f2__funkable__is_funktional(f2ptr cause, f2ptr this) {
  if (! raw__funkable__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__funkable__is_funktional(cause, this));
}



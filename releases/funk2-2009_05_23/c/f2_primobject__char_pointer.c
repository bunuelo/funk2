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

// char_pointer primobject definition

defprimobject__static_slot(char_pointer__pointer_value, 0);

f2ptr __char_pointer__symbol = -1;

f2ptr f2char_pointer__new(f2ptr cause, f2ptr pointer_value) {
  release__assert(__char_pointer__symbol != -1, nil, "f2char_pointer__new error: used before initialized.");
  f2ptr this = f2__primobject__new(cause, __char_pointer__symbol, 1, nil);
  f2char_pointer__pointer_value__set(this, cause, pointer_value);
  return this;
}

f2ptr f2__char_pointerp(f2ptr cause, f2ptr this) {return f2boolean__new(cause, raw__arrayp(this, cause) && raw__array__length(cause, this) == 2 && f2primobject__is_char_pointer(this, cause));}


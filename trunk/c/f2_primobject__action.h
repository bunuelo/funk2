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

#ifndef F2__PRIMOBJECT__ACTION__H
#define F2__PRIMOBJECT__ACTION__H

#include "f2_primobjects.h"

// action

extern f2ptr __action__symbol;
f2ptr f2action__new(f2ptr cause, f2ptr funk, f2ptr success_pairs, f2ptr failure_pairs);
#define      f2primobject__is__action(this, cause) raw__eq(cause, f2primobject__type(this, cause), __action__symbol)

defprimobject__static_slot__prototype(action__funk);
#define      f2action__funk(                   this, cause)        primobject__static_slot__accessor(         this, action__funk, cause)
#define      f2action__funk__set(              this, cause, value) primobject__static_slot__set(              this, action__funk, cause, value)
#define      f2action__funk__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__funk, cause)
#define      f2action__funk__trace(            this, cause)        primobject__static_slot__trace(            this, action__funk, cause)
#define      f2action__funk__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__funk, cause)

defprimobject__static_slot__prototype(action__success_pairs);
#define      f2action__success_pairs(                   this, cause)        primobject__static_slot__accessor(         this, action__success_pairs, cause)
#define      f2action__success_pairs__set(              this, cause, value) primobject__static_slot__set(              this, action__success_pairs, cause, value)
#define      f2action__success_pairs__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__success_pairs, cause)
#define      f2action__success_pairs__trace(            this, cause)        primobject__static_slot__trace(            this, action__success_pairs, cause)
#define      f2action__success_pairs__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__success_pairs, cause)

defprimobject__static_slot__prototype(action__failure_pairs);
#define      f2action__failure_pairs(                   this, cause)        primobject__static_slot__accessor(         this, action__failure_pairs, cause)
#define      f2action__failure_pairs__set(              this, cause, value) primobject__static_slot__set(              this, action__failure_pairs, cause, value)
#define      f2action__failure_pairs__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, action__failure_pairs, cause)
#define      f2action__failure_pairs__trace(            this, cause)        primobject__static_slot__trace(            this, action__failure_pairs, cause)
#define      f2action__failure_pairs__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, action__failure_pairs, cause)

boolean_t raw__actionp(f2ptr this, f2ptr cause);
f2ptr      f2__actionp(f2ptr this, f2ptr cause);



// **

void f2__primobject__action__reinitialize_globalvars();
void f2__primobject__action__initialize();

#endif // F2__PRIMOBJECT__ACTION__H


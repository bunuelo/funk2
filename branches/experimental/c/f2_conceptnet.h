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

#ifndef F2__CONCEPTNET__H
#define F2__CONCEPTNET__H

#include "f2_primobjects.h"

// conceptnet_relation

extern f2ptr __conceptnet_relation__symbol;
f2ptr f2conceptnet_relation__new(f2ptr cause, f2ptr type, f2ptr left_concept, f2ptr right_concept);
#define      f2primobject__is__conceptnet_relation(this, cause) raw__eq(cause, f2primobject__type(this, cause), __conceptnet_relation__symbol)

defprimobject__static_slot__prototype(conceptnet_relation__type);
#define      f2conceptnet_relation__type(                   this, cause)        primobject__static_slot__accessor(         this, conceptnet_relation__type, cause)
#define      f2conceptnet_relation__type__set(              this, cause, value) primobject__static_slot__set(              this, conceptnet_relation__type, cause, value)
#define      f2conceptnet_relation__type__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, conceptnet_relation__type, cause)
#define      f2conceptnet_relation__type__trace(            this, cause)        primobject__static_slot__trace(            this, conceptnet_relation__type, cause)
#define      f2conceptnet_relation__type__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, conceptnet_relation__type, cause)

defprimobject__static_slot__prototype(conceptnet_relation__left_concept);
#define      f2conceptnet_relation__left_concept(                   this, cause)        primobject__static_slot__accessor(         this, conceptnet_relation__left_concept, cause)
#define      f2conceptnet_relation__left_concept__set(              this, cause, value) primobject__static_slot__set(              this, conceptnet_relation__left_concept, cause, value)
#define      f2conceptnet_relation__left_concept__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, conceptnet_relation__left_concept, cause)
#define      f2conceptnet_relation__left_concept__trace(            this, cause)        primobject__static_slot__trace(            this, conceptnet_relation__left_concept, cause)
#define      f2conceptnet_relation__left_concept__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, conceptnet_relation__left_concept, cause)

defprimobject__static_slot__prototype(conceptnet_relation__right_concept);
#define      f2conceptnet_relation__right_concept(                   this, cause)        primobject__static_slot__accessor(         this, conceptnet_relation__right_concept, cause)
#define      f2conceptnet_relation__right_concept__set(              this, cause, value) primobject__static_slot__set(              this, conceptnet_relation__right_concept, cause, value)
#define      f2conceptnet_relation__right_concept__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, conceptnet_relation__right_concept, cause)
#define      f2conceptnet_relation__right_concept__trace(            this, cause)        primobject__static_slot__trace(            this, conceptnet_relation__right_concept, cause)
#define      f2conceptnet_relation__right_concept__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, conceptnet_relation__right_concept, cause)

boolean_t raw__conceptnet_relationp(f2ptr this, f2ptr cause);
f2ptr      f2__conceptnet_relationp(f2ptr this, f2ptr cause);




#endif // F2__CONCEPTNET__H


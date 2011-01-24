// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__PRIMOBJECT__SEMANTIC_GRAPH__H
#define F2__PRIMOBJECT__SEMANTIC_GRAPH__H

#include "f2_primobjects.h"

// semantic_relation

extern f2ptr __semantic_relation__symbol;
boolean_t raw__semantic_relation__is_type(f2ptr cause, f2ptr this);
f2ptr f2__semantic_relation__is_type(f2ptr cause, f2ptr this);
f2ptr f2semantic_relation__new(f2ptr cause, f2ptr type, f2ptr left_concept, f2ptr right_concept);
#define      f2primobject__is__semantic_relation(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __semantic_relation__symbol)

defprimobject__static_slot__prototype(semantic_relation__type);
#define      f2semantic_relation__type(                   this, cause)        primobject__static_slot__accessor(         this, semantic_relation__type, cause)
#define      f2semantic_relation__type__set(              this, cause, value) primobject__static_slot__set(              this, semantic_relation__type, cause, value)
#define      f2semantic_relation__type__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, semantic_relation__type, cause)
#define      f2semantic_relation__type__trace(            this, cause)        primobject__static_slot__trace(            this, semantic_relation__type, cause)
#define      f2semantic_relation__type__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, semantic_relation__type, cause)

defprimobject__static_slot__prototype(semantic_relation__left_concept);
#define      f2semantic_relation__left_concept(                   this, cause)        primobject__static_slot__accessor(         this, semantic_relation__left_concept, cause)
#define      f2semantic_relation__left_concept__set(              this, cause, value) primobject__static_slot__set(              this, semantic_relation__left_concept, cause, value)
#define      f2semantic_relation__left_concept__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, semantic_relation__left_concept, cause)
#define      f2semantic_relation__left_concept__trace(            this, cause)        primobject__static_slot__trace(            this, semantic_relation__left_concept, cause)
#define      f2semantic_relation__left_concept__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, semantic_relation__left_concept, cause)

defprimobject__static_slot__prototype(semantic_relation__right_concept);
#define      f2semantic_relation__right_concept(                   this, cause)        primobject__static_slot__accessor(         this, semantic_relation__right_concept, cause)
#define      f2semantic_relation__right_concept__set(              this, cause, value) primobject__static_slot__set(              this, semantic_relation__right_concept, cause, value)
#define      f2semantic_relation__right_concept__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, semantic_relation__right_concept, cause)
#define      f2semantic_relation__right_concept__trace(            this, cause)        primobject__static_slot__trace(            this, semantic_relation__right_concept, cause)
#define      f2semantic_relation__right_concept__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, semantic_relation__right_concept, cause)


// semantic_graph

extern f2ptr __semantic_graph__symbol;
f2ptr f2semantic_graph__new(f2ptr cause, f2ptr relations);
#define      f2primobject__is__semantic_graph(this, cause) raw__eq(cause, f2primobject__object_type(this, cause), __semantic_graph__symbol)

defprimobject__static_slot__prototype(semantic_graph__relations);
#define      f2semantic_graph__relations(                   this, cause)        primobject__static_slot__accessor(         this, semantic_graph__relations, cause)
#define      f2semantic_graph__relations__set(              this, cause, value) primobject__static_slot__set(              this, semantic_graph__relations, cause, value)
#define      f2semantic_graph__relations__tracing_on(       this, cause)        primobject__static_slot__tracing_on(       this, semantic_graph__relations, cause)
#define      f2semantic_graph__relations__trace(            this, cause)        primobject__static_slot__trace(            this, semantic_graph__relations, cause)
#define      f2semantic_graph__relations__imagination_frame(this, cause)        primobject__static_slot__imagination_frame(this, semantic_graph__relations, cause)

boolean_t raw__semantic_graphp(f2ptr this, f2ptr cause);
f2ptr      f2__semantic_graphp(f2ptr this, f2ptr cause);



// **

void f2__primobject__semantic_graph__reinitialize_globalvars();
void f2__primobject__semantic_graph__initialize();

#endif // F2__PRIMOBJECT__SEMANTIC_GRAPH__H


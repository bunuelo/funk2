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

#ifndef F2__ARRAY__H
#define F2__ARRAY__H

// array

boolean_t  raw__cause_is_traced(f2ptr cause);
f2ptr raw__array__new(f2ptr cause, u64 length);
f2ptr raw__array__new_copy(f2ptr cause, u64 length, f2ptr init);
boolean_t raw__array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__array__is_type(f2ptr cause, f2ptr x);
u64   raw__array__length(f2ptr cause, f2ptr x);
f2ptr f2__array__length(f2ptr cause, f2ptr x);
f2ptr raw__array__elt__trace_depth(f2ptr cause, f2ptr this, u64 index, int trace_depth);
f2ptr raw__array__elt(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);
f2ptr f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth);
f2ptr raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);
f2ptr f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index);
f2ptr raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);

// **

void f2__array__initialize();

#endif // F2__ARRAY__H


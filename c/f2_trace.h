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

#ifndef F2__TRACE__H
#define F2__TRACE__H

#include "f2_primobjects.h"

// tracenode (implemented as doublelink)

#define f2tracenode__new__trace_depth        f2doublelink__new__trace_depth
#define f2tracenode__new                     f2doublelink__new
#define f2primobject__is_tracenode           f2primobject__is_doublelink

#define f2tracenode__prev                    f2doublelink__prev
#define f2tracenode__prev__set__trace_depth  f2doublelink__prev__set__trace_depth
#define f2tracenode__prev__set               f2doublelink__prev__set
#define f2tracenode__prev__tracing_on        f2doublelink__prev__tracing_on
#define f2tracenode__prev__prev              f2doublelink__prev__prev
#define f2tracenode__prev__cause             f2doublelink__prev__cause

#define f2tracenode__next                    f2doublelink__next
#define f2tracenode__next__set__trace_depth  f2doublelink__next__set__trace_depth
#define f2tracenode__next__set               f2doublelink__next__set
#define f2tracenode__next__tracing_on        f2doublelink__next__tracing_on
#define f2tracenode__next__prev              f2doublelink__next__prev
#define f2tracenode__next__cause             f2doublelink__next__cause

#define f2tracenode__value                   f2doublelink__value
#define f2tracenode__value__set__trace_depth f2doublelink__value__set__trace_depth
#define f2tracenode__value__set              f2doublelink__value__set
#define f2tracenode__value__tracing_on       f2doublelink__value__tracing_on
#define f2tracenode__value__prev             f2doublelink__value__prev
#define f2tracenode__value__cause            f2doublelink__value__cause

f2ptr f2tracenode__find_prev__primobject_of_type(f2ptr tracenode, f2ptr cause, f2ptr type);
f2ptr f2tracenode__find_next__primobject_of_type(f2ptr tracenode, f2ptr cause, f2ptr type);

typedef struct funk2_trace_s {
  f2ptr do_not_remember__symbol;
} funk2_trace_t;

f2ptr raw__trace__remember__nanoseconds_since_1970(f2ptr cause, f2ptr this, u64 nanoseconds_since_1970, f2ptr* remember_value);
f2ptr raw__array__elt__remember__nanoseconds_since_1970(f2ptr cause, f2ptr this, uint index, u64 nanoseconds_since_1970);
f2ptr raw__exp__remember__nanoseconds_since_1970(f2ptr cause, f2ptr exp, u64 nanoseconds_since_1970);
f2ptr raw__exp__remember__trans__nanoseconds_since_1970(f2ptr cause, f2ptr exp, u64 initial_nanoseconds, u64 final_nanoseconds);
void  raw__array__tracing_on__set(f2ptr cause, f2ptr this, boolean_t tracing_on);


void f2__trace__reinitialize_globalvars();
void f2__trace__initialize();

#endif // F2__TRACE__H

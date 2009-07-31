// 
// Copyright (c) 2007-2008 Bo Morgan.
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

#ifndef F2__DPTR__H
#define F2__DPTR__H

typedef struct funk2_dptr_s funk2_dptr_t;

// dptr

struct funk2_dptr_s {
  f2ptr p;
  f2ptr tracing_on;
  f2ptr trace;
  f2ptr imagination_frame;
} __attribute__((__packed__));

void funk2_dptr__init(funk2_dptr_t* dptr, f2ptr p, f2ptr tracing_on, f2ptr prev, f2ptr imagination_frame);

#define funk2_dptr__gf2_p(this)                 ((this)->p)
#define funk2_dptr__gf2_tracing_on(this)        ((this)->tracing_on)
#define funk2_dptr__gf2_trace(this)             ((this)->trace)
#define funk2_dptr__gf2_imagination_frame(this) ((this)->imagination_frame)

#define funk2_dptr__p(this)                              funk2_dptr__gf2_p(this)
#define funk2_dptr__p__set(this, value)                 (funk2_dptr__gf2_p(this) = (value))
#define funk2_dptr__tracing_on(this)                     funk2_dptr__gf2_tracing_on(this)
#define funk2_dptr__tracing_on__set(this, value)        (funk2_dptr__gf2_tracing_on(this) = (value))
#define funk2_dptr__trace(this)                          funk2_dptr__gf2_trace(this)
#define funk2_dptr__trace__set(this, value)             (funk2_dptr__gf2_trace(this) = (value))
#define funk2_dptr__imagination_frame(this)              funk2_dptr__gf2_imagination_frame(this)
#define funk2_dptr__imagination_frame__set(this, value) (funk2_dptr__gf2_imagination_frame(this) = (value))

#endif // F2__DPTR__H


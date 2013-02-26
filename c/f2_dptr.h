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

#ifndef F2__DPTR__TYPES__H
#define F2__DPTR__TYPES__H

typedef struct funk2_dptr_s funk2_dptr_t;

#endif // F2__DPTR__TYPES__H

#ifndef F2__DPTR__H
#define F2__DPTR__H

#include "f2_garbage_collector.h"

#define F2__USE_TRACED_DPTRS

// dptr

struct funk2_dptr_s {
  f2ptr p                 : f2ptr__bit_num;
#if defined(F2__USE_TRACED_DPTRS)
  f2ptr tracing_on        : f2ptr__bit_num;
  f2ptr trace             : f2ptr__bit_num;
  f2ptr imagination_frame : f2ptr__bit_num;
  f2ptr mutate_funks      : f2ptr__bit_num;
  f2ptr read_funks        : f2ptr__bit_num;
#endif // F2__USE_TRACED_DPTRS
} __attribute__((__packed__));

#define funk2_dptr__gf2_p(this)                 ((this)->p)
#if defined(F2__USE_TRACED_DPTRS)
#  define funk2_dptr__gf2_tracing_on(this)        ((this)->tracing_on)
#  define funk2_dptr__gf2_trace(this)             ((this)->trace)
#  define funk2_dptr__gf2_imagination_frame(this) ((this)->imagination_frame)
#  define funk2_dptr__gf2_mutate_funks(this)      ((this)->mutate_funks)
#  define funk2_dptr__gf2_read_funks(this)        ((this)->read_funks)
#else
#  define funk2_dptr__gf2_tracing_on(this)        nil
#  define funk2_dptr__gf2_trace(this)             nil
#  define funk2_dptr__gf2_imagination_frame(this) nil
#  define funk2_dptr__gf2_mutate_funks(this)      nil
#  define funk2_dptr__gf2_read_funks(this)        nil
#endif // F2__USE_TRACED_DPTRS

#define funk2_dptr__p(this)                              funk2_dptr__gf2_p(this)
#define funk2_dptr__p__set(this, value)                 (funk2_dptr__gf2_p(this) = (value))
#if defined(F2__USE_TRACED_DPTRS)
#  define funk2_dptr__tracing_on(this)                     funk2_dptr__gf2_tracing_on(this)
#  define funk2_dptr__tracing_on__set(this, value)        (funk2_dptr__gf2_tracing_on(this) = (value))
#  define funk2_dptr__trace(this)                          funk2_dptr__gf2_trace(this)
#  define funk2_dptr__trace__set(this, value)             (funk2_dptr__gf2_trace(this) = (value))
#  define funk2_dptr__imagination_frame(this)              funk2_dptr__gf2_imagination_frame(this)
#  define funk2_dptr__imagination_frame__set(this, value) (funk2_dptr__gf2_imagination_frame(this) = (value))
#  define funk2_dptr__mutate_funks(this)                   funk2_dptr__gf2_mutate_funks(this)
#  define funk2_dptr__mutate_funks__set(this, value)      (funk2_dptr__gf2_mutate_funks(this) = (value))
#  define funk2_dptr__read_funks(this)                     funk2_dptr__gf2_read_funks(this)
#  define funk2_dptr__read_funks__set(this, value)        (funk2_dptr__gf2_read_funks(this) = (value))
#else
#  define funk2_dptr__tracing_on(this)                     nil
#  define funk2_dptr__tracing_on__set(this, value)         nil
#  define funk2_dptr__trace(this)                          nil
#  define funk2_dptr__trace__set(this, value)              nil
#  define funk2_dptr__imagination_frame(this)              nil
#  define funk2_dptr__imagination_frame__set(this, value)  nil
#  define funk2_dptr__mutate_funks(this)                   nil
#  define funk2_dptr__mutate_funks__set(this, value)       nil
#  define funk2_dptr__read_funks(this)                     nil
#  define funk2_dptr__read_funks__set(this, value)         nil
#endif // F2__USE_TRACED_DPTRS

void      funk2_dptr__init(funk2_dptr_t* dptr, f2ptr p, f2ptr tracing_on, f2ptr prev, f2ptr imagination_frame, f2ptr mutate_funks, f2ptr read_funks);
boolean_t funk2_dptr__check_all_memory_pointers_valid_in_memory(funk2_dptr_t* this, funk2_memory_t* memory);
void      funk2_dptr__decrement_reference_counts(funk2_dptr_t* this, funk2_garbage_collector_t* garbage_collector);
void      funk2_dptr__grey_referenced_elements(funk2_dptr_t* dptr, funk2_garbage_collector_pool_t* this, int pool_index);

#endif // F2__DPTR__H


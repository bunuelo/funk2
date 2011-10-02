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

#ifndef F2__PTYPE__H
#define F2__PTYPE__H

//#define ptype__total_num 14
#define ptype__min_bits   5

extern u8 __ptype__str[][128];

typedef enum ptype_e {
  ptype_free_memory      = 16,
  ptype_newly_allocated  = 17,
  ptype_integer          = 18,
  ptype_double           = 19,
  ptype_float            = 20,
  ptype_pointer          = 21,
  ptype_gfunkptr         = 22,
  ptype_scheduler_cmutex = 23,
  ptype_cmutex           = 24,
  ptype_char             = 25,
  ptype_string           = 26,
  ptype_symbol           = 27,
  ptype_chunk            = 28,
  ptype_simple_array     = 29,
  ptype_traced_array     = 30,
  ptype_larva            = 31,
} ptype_t;

#endif // F2__PTYPE__H


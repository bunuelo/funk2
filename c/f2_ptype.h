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

#define ptype__total_num 14
#define ptype__min_bits   4

extern u8 __ptype__str[][128];

typedef enum ptype_e {
  ptype_free_memory      = 0x40 + 0x0,
  ptype_newly_allocated  = 0x40 + 0x1,
  ptype_integer          = 0x40 + 0x2,
  ptype_double           = 0x40 + 0x3,
  ptype_float            = 0x40 + 0x4,
  ptype_pointer          = 0x40 + 0x5,
  ptype_gfunkptr         = 0x40 + 0x6,
  ptype_scheduler_cmutex = 0x40 + 0x7,
  ptype_cmutex           = 0x40 + 0x8,
  ptype_char             = 0x40 + 0x9,
  ptype_string           = 0x40 + 0xA,
  ptype_symbol           = 0x40 + 0xB,
  ptype_chunk            = 0x40 + 0xC,
  ptype_simple_array     = 0x40 + 0xD,
  ptype_traced_array     = 0x40 + 0xE,
  ptype_larva            = 0x40 + 0xF,
} ptype_t;

#endif // F2__PTYPE__H


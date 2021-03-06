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

#ifndef F2__PTYPE__H
#define F2__PTYPE__H

#define ptype__min_bits 5

typedef enum ptype_e {
  ptype_free_memory           = 1,
  ptype_newly_allocated       = 2,
  ptype_integer               = 3,
  ptype_double                = 4,
  ptype_float                 = 5,
  ptype_pointer               = 6,
  ptype_cmutex                = 7,
  ptype_creadwritelock        = 8,
  ptype_char                  = 9,
  ptype_string                = 10,
  ptype_symbol                = 11,
  ptype_chunk                 = 12,
  ptype_cons                  = 13,
  ptype_simple_array          = 14,
  ptype_mutable_array_pointer = 15,
  ptype_larva                 = 16,
} ptype_t;

#endif // F2__PTYPE__H


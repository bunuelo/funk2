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

#include "funk2.h"

f2size_t raw_write(int fd, ptr p, f2size_t object_size) {
  return (f2size_t)write(fd, from_ptr(p), (size_t)object_size);
}

f2size_t raw_read(int fd, ptr p, f2size_t object_size) {
  return (f2size_t)read(fd, from_ptr(p), (size_t)object_size);
}

void safe_write(int fd, ptr p, f2size_t object_size) {
  f2size_t result = raw_write(fd, p, object_size);
  if (result != object_size) {
    error(nil, "safe_write error.");
  }
}

void safe_read(int fd, ptr p, f2size_t object_size) {
  f2size_t result = raw_read(fd, p, object_size);
  if (result != object_size) {
    error(nil, "safe_read error.");
  }
}



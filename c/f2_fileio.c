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

#include "funk2.h"

void safe_write(int fd, ptr p, f2size_t object_size) {
  size_t result = write(fd, from_ptr(p), (size_t)object_size);
  if (result != object_size) {
    error(nil, "safe_write error.");
  }
}

void safe_read(int fd, ptr p, f2size_t object_size) {
  size_t result = read(fd, from_ptr(p), (size_t)object_size);
  if (result != object_size) {
    error(nil, "safe_read error.");
  }
}



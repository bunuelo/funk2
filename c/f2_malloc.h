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

#ifndef F2__MALLOC__H
#define F2__MALLOC__H

void assert_failed           (f2ptr fiber, char* filename, int line_num, char* str);
ptr  malloc_executable       (size_t required_bytes);
void free_executable         (ptr p);
ptr  f2__malloc              (f2size_t byte_num);
void f2__free                (ptr this);
ptr  f2__new_alloc           (ptr this, f2size_t old_byte_num, f2size_t new_byte_num);
ptr  f2__malloc_executable   (f2size_t byte_num);
void f2__free_executable     (ptr this);
ptr  f2__new_alloc_executable(ptr this, f2size_t old_byte_num, f2size_t new_byte_num);

#endif // F2__MALLOC__H


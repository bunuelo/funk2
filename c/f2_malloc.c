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

boolean_t __assert_failed__global_spin_variable = boolean__true;
void assert_failed(f2ptr fiber, char* filename, int line_num, char* str) {
  status("*** %s:%d> assertion failed, '%s' ***", filename, line_num, str);
  fprintf(stderr, "\n*** %s:%d> assertion failed, '%s' ***\n", filename, line_num, str);
  kill(getpid(), SIGSTOP);
  while (__assert_failed__global_spin_variable) {
    printf("\nsomebody stop me!"); fflush(stdout);
  }
  //exit(-1);
}

size_t total_bytes_allocated = 0;

ptr malloc_executable(size_t required_bytes) {
  size_t page_size   = getpagesize();
  size_t alloc_bytes = (((required_bytes - 1) / page_size) + 1) * page_size;
  void* p = mmap(NULL, alloc_bytes, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON, -1, 0);
  if (! p) {
    perror("malloc_executable() malloc");
    error(nil, "malloc_executable malloc failed.");
  }
  total_bytes_allocated += required_bytes;
  return to_ptr(p);
}

void free_executable(ptr p) {
  munmap(from_ptr(p), 1);
}

ptr f2__malloc(f2size_t byte_num) {
  //ptr this = malloc_executable(byte_num);
  //if (this == to_ptr(NULL)) {
  //  error(nil, "f2__malloc error: out of memory.");
  //}
  void* raw_memory = malloc(byte_num);
  if (raw_memory == NULL) {
    error(nil, "f2__malloc error: out of memory.");
  }
  if (mprotect(raw_memory, byte_num, PROT_READ | PROT_WRITE | PROT_EXEC) != nil) {
    error(nil, "f2__malloc error: cannot mprotect memory.");
  }
  ptr this = to_ptr(raw_memory);
  return this;
}

void f2__free(ptr this) {
  //free_executable(this);
  free(from_ptr(this));
}

ptr f2__new_alloc(ptr this, f2size_t old_byte_num, f2size_t new_byte_num) {
  ptr new_mem = f2__malloc(new_byte_num);
  memcpy(from_ptr(new_mem), from_ptr(this), (old_byte_num < new_byte_num) ? old_byte_num : new_byte_num);
  f2__free(this);
  return new_mem;
}



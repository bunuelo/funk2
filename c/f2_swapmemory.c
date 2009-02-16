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

#include "f2_swapmemory.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swapmemory_filename__generate(char* str) {
  int fd = -1;
  do {
    if (fd != -1) {close(fd);}
    sprintf(str, "/tmp/----------------------.f2swp");
    int i;
    for (i = 0; str[i] != '-'; i++); // get to first -
    for (; str[i] == '-'; i++) { // replace all consecutive -s
      int j = random() % 62;
      str[i] =
	(j < 26) ?
	(j + 'a') :
	((j < 52) ?
	 ((j - 26) + 'A') :
	 ((j - 52) + '0'));
    }
  } while ((fd = open(str, O_RDONLY)) != -1); // assure opening the random filename fails before returning
}

void f2swapmemory__init_and_alloc(f2swapmemory_t* this, f2size_t byte_num) {
  swapmemory_filename__generate(this->filename);
  this->fd       = open(this->filename, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
  if (this->fd == -1) {
    printf("\nf2swapmemory__init_and_alloc error: couldn't open file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__init_and_alloc error: couldn't open file");
  }
  f2size_t sought_offset = (f2size_t)(f2__lseek(this->fd, byte_num + 1, SEEK_SET));
  if (sought_offset != byte_num + 1) {
    printf("\nf2swapmemory__init_and_alloc error: sought_offset=" f2size_t__fstr ", byte_num=" f2size_t__fstr, sought_offset, byte_num);
    error(nil, "f2swapmemory__init_and_alloc error");
  }
  if (write(this->fd, &"B", 1) != 1) {
    error(nil, "f2swapmemory__init_and_alloc error: write failed.");
  }
  this->byte_num = byte_num;
  
  this->ptr = f2__mmap(NULL,
		       byte_num,
		       PROT_EXEC | PROT_READ | PROT_WRITE,
		       MAP_SHARED,
		       this->fd,
		       0);
  if (this->ptr == NULL) {
    printf("\nf2swapmemory__init_and_alloc error: couldn't mmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__init_and_alloc error: couldn't mmap file");
  }
}

void f2swapmemory__destroy_and_free(f2swapmemory_t* this) {
  if (munmap(this->ptr, this->byte_num) == -1) {
    printf("\nf2swapmemory__destroy_and_free error: couldn't unmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__destroy_and_free error: couldn't unmap file");
  }
  if (close(this->fd) == -1) {
    printf("\nf2swapmemory__destroy_and_free error: couldn't close file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__destroy_and_free error: couldn't close file");
  }
  if (unlink(this->filename) == -1) {
    printf("\nf2swapmemory__destroy_and_free error: couldn't unlink file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__destroy_and_free error: couldn't unlink file");
  }
}

// bug: doesn't shorten file size
void f2swapmemory__resize(f2swapmemory_t* this, f2size_t byte_num) {
  f2size_t sought_offset = (f2size_t)(f2__lseek(this->fd, byte_num + 1, SEEK_SET));
  if (sought_offset != byte_num + 1) {
    printf("\nf2swapmemory__resize error: sought_offset=" f2size_t__fstr ", byte_num=" f2size_t__fstr, sought_offset, byte_num);
    error(nil, "f2swapmemory__resize error");
  }
  if (write(this->fd, &"B", 1) != 1) {
    printf("\nf2swapmemory__resize error: write failed.");
    error(nil, "f2swapmemory__resize error: write failed.");
  }
  if (munmap(this->ptr, this->byte_num) == -1) {
    printf("\nf2swapmemory__resize error: couldn't unmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__resize error: couldn't unmap file");
  }
  this->byte_num = byte_num;
  this->ptr = f2__mmap(NULL,
		       byte_num,
		       PROT_EXEC | PROT_READ | PROT_WRITE,
		       MAP_SHARED,
		       this->fd,
		       0);
  if (this->ptr == MAP_FAILED ||
      this->ptr == NULL) { // should never return NULL, so this would definately be an unexpected error.
    printf("\nf2swapmemory__resize error: couldn't mmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__resize error: couldn't mmap file");
  }
}

#define F2SWAPMEMORY__REALLOC_IS_RESIZE

void f2swapmemory__realloc(f2swapmemory_t* new_swapmemory, f2swapmemory_t* old_swapmemory, f2size_t byte_num) {
#ifdef F2SWAPMEMORY__REALLOC_IS_RESIZE
  f2swapmemory__resize(new_swapmemory, byte_num);
#else
  f2swapmemory_t temp_swapmemory;
  memcpy(&temp_swapmemory, old_swapmemory, sizeof(f2swapmemory_t));
  f2swapmemory__init_and_alloc(new_swapmemory, byte_num);
  memcpy(new_swapmemory->ptr, temp_swapmemory.ptr, (byte_num <= temp_swapmemory.byte_num) ? byte_num : temp_swapmemory.byte_num);
  if (byte_num > temp_swapmemory.byte_num) {
    memset(((char*)new_swapmemory->ptr) + temp_swapmemory.byte_num, 0x00, byte_num - temp_swapmemory.byte_num);
  }
  f2swapmemory__destroy_and_free(&temp_swapmemory);
#endif
}


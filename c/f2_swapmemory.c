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

void swapmemory_filename__generate_from_swap_directory(char* str, char* swap_directory) {
  int       fd                 = -1;
  int       total_tries_so_far = 0;
  boolean_t try_again          = false;
  do {
    total_tries_so_far ++;
    sprintf(str, "%s----------------------.f2swp", swap_directory);
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
    fd = open(str, O_RDONLY);
    if (fd != -1) {
      close(fd);
      try_again = true; // success means file exists.
    } else {
      try_again = false;
      switch(errno) {
      case EACCES:
	status("The requested access to the file is not allowed, or search permission is denied for one of the directories in the path prefix of pathname, or the file did not exist yet and write access to the parent directory is  not  allowed.   (See  also  path_resolu’¡¾"
	       "tion(7).)");
	try_again = true;
	break;
      case EEXIST:
	status("pathname already exists and O_CREAT and O_EXCL were used.");
	try_again = true;
	break;
      case EFAULT:
	status("pathname points outside your accessible address space.");
	error(nil, "pathname points outside your accessible address space.");
	break;
      case EFBIG:
	status("pathname refers to a regular file, too large to be opened; see O_LARGEFILE above.  (POSIX.1-2001 specifies the error EOVERFLOW for this case.)");
	try_again = true;
	break;
      case EISDIR:
	status("pathname refers to a directory and the access requested involved writing (that is, O_WRONLY or O_RDWR is set).");
	try_again = true;
	break;
      case ELOOP:
	status("Too many symbolic links were encountered in resolving pathname, or O_NOFOLLOW was specified but pathname was a symbolic link.");
	try_again = true;
	break;
      case EMFILE:
	status("The process already has the maximum number of files open.");
	error(nil, "The process already has the maximum number of files open.");
	break;
      case ENAMETOOLONG:
	status("pathname was too long.");
	error(nil, "pathname was too long.");
	break;
      case ENFILE:
	status("The system limit on the total number of open files has been reached.");
	error(nil, "The system limit on the total number of open files has been reached.");
	break;
      case ENODEV:
	status("pathname refers to a device special file and no corresponding device exists.  (This is a Linux kernel bug; in this situation ENXIO must be returned.)");
	try_again = true;
	break;
      case ENOENT:
	status("O_CREAT is not set and the named file does not exist.  Or, a directory component in pathname does not exist or is a dangling symbolic link.");
	break;
      case ENOMEM:
	status("Insufficient kernel memory was available.");
	error(nil, "Insufficient kernel memory was available.");
	break;
      case ENOSPC:
	status("pathname was to be created but the device containing pathname has no room for the new file.");
	error(nil, "pathname was to be created but the device containing pathname has no room for the new file.");
	break;
      case ENOTDIR:
	status("A component used as a directory in pathname is not, in fact, a directory, or O_DIRECTORY was specified and pathname was not a directory.");
	try_again = true;
	break;
      case ENXIO:
	status("O_NONBLOCK | O_WRONLY is set, the named file is a FIFO and no process has the file open for reading.  Or, the file is a device special file and no corresponding device exists.");
	try_again = true;
	break;
      case EPERM:
	status("The O_NOATIME flag was specified, but the effective user ID of the caller did not match the owner of the file and the caller was not privileged (CAP_FOWNER).");
	try_again = true;
	break;
      case EROFS:
	status("pathname refers to a file on a read-only file system and write access was requested.");
	try_again = true;
	break;
      case ETXTBSY:
	status("pathname refers to an executable image which is currently being executed and write access was requested.");
	try_again = true;
	break;
      case EWOULDBLOCK:
	status("The O_NONBLOCK flag was specified, and an incompatible lease was held on the file (see fcntl(2)).");
	try_again = true;
	break;
      }
    }
  } while (try_again && total_tries_so_far < 100); // assure opening the random filename fails before returning
}

void f2swapmemory__init_and_alloc(f2swapmemory_t* this, f2size_t byte_num, char* swap_directory) {
  u64 swap_directory__length = strlen(swap_directory);
  if (swap_directory__length + 1 < sizeof(this->swap_directory)) {
    memcpy(this->swap_directory, swap_directory, swap_directory__length + 1);
  }
  swapmemory_filename__generate_from_swap_directory(this->filename, this->swap_directory);
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
  
  this->ptr = to_ptr(f2__mmap(NULL,
			      byte_num,
			      PROT_EXEC | PROT_READ | PROT_WRITE,
			      MAP_SHARED,
			      this->fd,
			      0));
  if (from_ptr(this->ptr) == MAP_FAILED ||
      from_ptr(this->ptr) == NULL) {
    printf("\nf2swapmemory__init_and_alloc error: couldn't mmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__init_and_alloc error: couldn't mmap file");
  }
}

int safe_close(int fd) {
  int result = -1;
  do {
    result = close(fd);
    if (result == -1) {
      switch(errno) {
      case EBADF:
	perror("close");
	printf("\nf2swapmemory__destroy_and_free error: couldn't close file (fd isn't a valid open file descriptor).\n");
	error(nil, "f2swapmemory__destroy_and_free error: couldn't close file (fd isn't a valid open file descriptor).");
	break;
      case EINTR:
	break;
      case EIO:
	perror("close");
	printf("\nf2swapmemory__destroy_and_free error: couldn't close file (An I/O error occurred).\n");
	error(nil, "f2swapmemory__destroy_and_free error: couldn't close file (An I/O error occurred).");
	break;
      }
    }
  } while (result == -1 && errno == EINTR);
  return result;
}

void f2swapmemory__destroy_and_free(f2swapmemory_t* this) {
  if (munmap(from_ptr(this->ptr), this->byte_num) == -1) {
    printf("\nf2swapmemory__destroy_and_free error: couldn't unmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__destroy_and_free error: couldn't unmap file");
  }
  if (safe_close(this->fd) == -1) {
    perror("safe_close");
    printf("\nf2swapmemory__destroy_and_free error: couldn't close file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__destroy_and_free error: couldn't close file.");
  }
  if (unlink(this->filename) == -1) {
    printf("\nf2swapmemory__destroy_and_free error: couldn't unlink file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__destroy_and_free error: couldn't unlink file");
  }
}

// bug: doesn't shorten file size
void f2swapmemory__resize(f2swapmemory_t* this, f2size_t byte_num) {
  status("f2swapmemory__resize: byte_num=" f2size_t__fstr, byte_num);
  f2size_t sought_offset = (f2size_t)(f2__lseek(this->fd, byte_num + 1, SEEK_SET));
  if (sought_offset != byte_num + 1) {
    printf("\nf2swapmemory__resize error: sought_offset=" f2size_t__fstr ", byte_num=" f2size_t__fstr, sought_offset, byte_num);
    error(nil, "f2swapmemory__resize error");
  }
  if (write(this->fd, &"B", 1) != 1) {
    printf("\nf2swapmemory__resize error: write failed.");
    error(nil, "f2swapmemory__resize error: write failed.");
  }
  if (munmap(from_ptr(this->ptr), this->byte_num) == -1) {
    printf("\nf2swapmemory__resize error: couldn't unmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__resize error: couldn't unmap file");
  }
  u64 old_byte_num = this->byte_num;
  ptr old_ptr      = to_ptr(this->ptr);
  this->byte_num = byte_num;
  this->ptr = to_ptr(f2__mmap(NULL,
			      byte_num,
			      PROT_EXEC | PROT_READ | PROT_WRITE,
			      MAP_SHARED,
			      this->fd,
			      0));
  status("f2__mmap from " u64__fstr " bytes at address " ptr__fstr " to " u64__fstr " bytes at address " ptr__fstr ".",
	 old_byte_num,   (ptr)(old_ptr),
	 this->byte_num, (ptr)(this->ptr));
  if (from_ptr(this->ptr) == MAP_FAILED ||
      from_ptr(this->ptr) == NULL) { // should never return NULL, so this would definately be an unexpected error.
    printf("\nf2swapmemory__resize error: couldn't mmap file \"%s\".\n", this->filename);
    error(nil, "f2swapmemory__resize error: couldn't mmap file");
  }
}

#define F2SWAPMEMORY__REALLOC_IS_RESIZE

void f2swapmemory__realloc(f2swapmemory_t* new_swapmemory, f2swapmemory_t* old_swapmemory, f2size_t byte_num) {
  status("f2swapmemory__realloc: byte_num=" f2size_t__fstr, byte_num);
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


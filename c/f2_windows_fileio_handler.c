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

// funk2_windows_file

void funk2_windows_file__init(funk2_windows_file_t* this, s64 file_descriptor, char* filename, boolean_t read_access, boolean_t write_access, boolean_t nonblocking) {
  this->file_descriptor = file_descriptor;
  if (filename == NULL) {
    this->filename = NULL;
  } else {
    s64 filename__length = strlen(filename);
    this->filename = (char*)from_ptr(f2__malloc(filename__length + 1));
    memcpy(this->filename, filename, filename__length + 1);
  }
  this->read_access  = read_access;
  this->write_access = write_access;
  this->nonblocking  = nonblocking;
}

void funk2_windows_file__destroy(funk2_windows_file_t* this) {
  if (this->filename != NULL) {
    f2__free(to_ptr(this->filename));
  }
}



// funk2_windows_fileio_handler

void funk2_windows_fileio_handler__init(funk2_windows_fileio_handler_t* this) {
  funk2_hash__init(&(this->file_descriptor_hash), 10);
}

void funk2_windows_fileio_handler__destroy(funk2_windows_fileio_handler_t* this) {
  funk2_hash__destroy(&(this->file_descriptor_hash));
}

funk2_windows_file_t* funk2_windows_fileio_handler__open_file(funk2_windows_fileio_handler_t* this, char* filename, boolean_t read_access, boolean_t write_access, boolean_t nonblocking) {
#if defined(HAVE_WINDOWS_H) && defined(HAVE__OPEN_OSFHANDLE)
  HANDLE hFile;
  
  {
    DWORD desired_access = 0;
    if (read_access) {
      desired_access |= GENERIC_READ;
    }
    if (write_access) {
      desired_access |= GENERIC_WRITE;
    }
    hFile = CreateFile(filename,
		       desired_access,
		       0,
		       NULL,
		       OPEN_EXISTING,
		       FILE_FLAG_OVERLAPPED,
		       NULL);
    
    if (hFile == INVALID_HANDLE_VALUE) {
      status("funk2_windows_fileio_handler__open_file warning: error opening filename \"%s\".");
      return NULL;
    }
  }
  
  int file_descriptor_flags = 0;
  if ((! write_access) && read_access) {
    file_descriptor_flags |= _O_RDONLY;
  }
  s64 file_descriptor = _open_osfhandle((intptr_t)hFile, file_descriptor_flags);
  if (file_descriptor == -1) {
    CloseHandle(hFile);
    status("funk2_windows_fileio_handler__open_file warning: error getting file descriptor for filename \"%s\".");
    return NULL;
  }
  
  funk2_windows_file_t* windows_file = (funk2_windows_file_t*)from_ptr(f2__malloc(sizeof(funk2_windows_file_t)));
  funk2_windows_file__init(windows_file, file_descriptor, filename, read_access, write_access, nonblocking);
  
  funk2_hash__add(&(this->file_descriptor_hash), file_descriptor, (u64)to_ptr(windows_file));
  return windows_file;
#else
  status("funk2_windows_fileio_handler__open_file warning: functionality not compiled into this Funk2 build.");
  return NULL;
#endif // HAVE_WINDOWS_H && HAVE__OPEN_OSFHANDLE
}

s64 raw__windows_fileio_handler__open(char* filename, boolean_t read_access, boolean_t write_access, boolean_t nonblocking) {
  funk2_windows_file_t* windows_file = funk2_windows_fileio_handler__open_file(&(__funk2.windows_fileio_handler), filename, read_access, write_access, nonblocking);
  return windows_file->file_descriptor;
}


funk2_windows_file_t* funk2_windows_fileio_handler__lookup_file_by_descriptor(funk2_windows_fileio_handler_t* this, s64 file_descriptor) {
  funk2_windows_file_t* windows_file = (funk2_windows_file_t*)funk2_hash__lookup(&(this->file_descriptor_hash), file_descriptor);
  return windows_file;
}


boolean_t funk2_windows_fileio_handler__close_file(funk2_windows_fileio_handler_t* this, funk2_windows_file_t* windows_file) {
#if defined(HAVE_WINDOWS_H) && defined(HAVE__GET_OSFHANDLE)
  HANDLE hFile = (HANDLE)_get_osfhandle(windows_file->file_descriptor);
  if (CloseHandle(hFile) == 0) {
    status("funk2_windows_fileio_handler__close_file warning: failed to close file handle for filename \"%s\".", windows_file->filename);
    return boolean__true; // failure
  }
  funk2_hash__remove(&(this->file_descriptor_hash), windows_file->file_descriptor);
  funk2_windows_file__destroy(windows_file);
  return boolean__true; // success
#else
  status("funk2_windows_fileio_handler__close_file warning: functionality not compiled into this Funk2 build.");
  return boolean__true; // failure
#endif // HAVE_WINDOWS_H && HAVE__GET_OSFHANDLE
}

boolean_t raw__windows_fileio_handler__close(s64 file_descriptor) {
  funk2_windows_file_t* windows_file = funk2_windows_fileio_handler__lookup_file_by_descriptor(&(__funk2.windows_fileio_handler), file_descriptor);
  return funk2_windows_fileio_handler__close_file(&(__funk2.windows_fileio_handler), windows_file);
}


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

#ifndef F2__WINDOWS_FILEIO_HANDLER__TYPES__H
#define F2__WINDOWS_FILEIO_HANDLER__TYPES__H

typedef struct funk2_windows_file_s           funk2_windows_file_t;
typedef struct funk2_windows_fileio_handler_s funk2_windows_fileio_handler_t;

#endif // F2__WINDOWS_FILEIO_HANDLER__TYPES__H


#ifndef F2__WINDOWS_FILEIO_HANDLER__H
#define F2__WINDOWS_FILEIO_HANDLER__H

#include "f2_global.h"
#include "f2_hash.h"

// funk2_windows_file

struct funk2_windows_file_s {
  s64       file_descriptor;
  char*     filename;
  boolean_t read_access;
  boolean_t write_access;
  boolean_t nonblocking;
};

void funk2_windows_file__init(funk2_windows_file_t *this, s64 file_descriptor, char* filename, boolean_t nonblocking);
void funk2_windows_file__destroy(funk2_windows_file_t *this);


// funk2_windows_fileio_handler

struct funk2_windows_fileio_handler_s {
  funk2_hash_t file_descriptor_hash;
};

void funk2_windows_fileio_handler__init(funk2_windows_fileio_handler_t* this);
void funk2_windows_fileio_handler__destroy(funk2_windows_fileio_handler_t* this);


#endif // F2__WINDOWS_FILEIO_HANDLER__H

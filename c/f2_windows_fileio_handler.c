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

void funk2_windows_file__init(funk2_windows_file_t *this, s64 file_descriptor) {
  this->file_descriptor = file_descriptor;
}

void funk2_windows_file__destroy(funk2_windows_file_t *this) {
}



// funk2_windows_fileio_handler

void funk2_windows_fileio_handler__init(funk2_windows_fileio_handler_t* this) {
  funk2_hash__init(&(this->file_descriptor_hash), 10);
}

void funk2_windows_fileio_handler__destroy(funk2_windows_fileio_handler_t* this) {
  funk2_hash__destroy(&(this->file_descriptor_hash));
}


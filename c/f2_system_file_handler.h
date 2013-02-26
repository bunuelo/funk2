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

#ifndef F2__SYSTEM_FILE_HANDLER__H
#define F2__SYSTEM_FILE_HANDLER__H

#include "f2_hash.h"

typedef struct funk2_system_file_handle_s funk2_system_file_handle_t;
struct funk2_system_file_handle_s {
  funk2_processor_mutex_t access_mutex;
  int                     fd;
};

void funk2_system_file_handle__init   (funk2_system_file_handle_t* this, int fd);
void funk2_system_file_handle__destroy(funk2_system_file_handle_t* this);


typedef struct funk2_system_file_handler_s funk2_system_file_handler_t;
struct funk2_system_file_handler_s {
  funk2_hash_t system_file_handle_fd_hash;
};

void                        funk2_system_file_handler__init                        (funk2_system_file_handler_t* this);
void                        funk2_system_file_handler__destroy                     (funk2_system_file_handler_t* this);
funk2_system_file_handle_t* funk2_system_file_handler__get_system_file_handle_by_fd(funk2_system_file_handler_t* this, int fd);


// **

void f2__system_file_handler__reinitialize_globalvars();
void f2__system_file_handler__initialize();

#endif // F2__SYSTEM_FILE_HANDLER__H

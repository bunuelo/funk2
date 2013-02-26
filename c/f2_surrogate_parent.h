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

#ifndef F2__SURROGATE_PARENT__H
#define F2__SURROGATE_PARENT__H

#include "f2_global.h"

// funk2_pipe

typedef struct funk2_pipe_s {
  int read_file_descriptor;
  int write_file_descriptor;
} funk2_pipe_t;

void funk2_pipe__init(funk2_pipe_t* this, boolean_t nonblocking_read, boolean_t nonblocking_write);
void funk2_pipe__destroy(funk2_pipe_t* this);

// funk2_return_result

typedef struct funk2_return_result_s {
  f2ptr fiber;
  u64   return_value;
} funk2_return_result_t;

// funk2_return_value_node

typedef struct funk2_return_value_node_s funk2_return_value_node_t;
struct funk2_return_value_node_s {
  funk2_return_result_t      result;
  funk2_return_value_node_t* next;
};

// funk2_surrogate_parent

typedef struct funk2_surrogate_parent_s {
  funk2_processor_mutex_t    write_to_child__mutex;
  funk2_pipe_t               parent_to_child_pipe;
  funk2_pipe_t               child_to_parent_pipe;
  funk2_processor_mutex_t    return_values__mutex;
  funk2_return_value_node_t* return_values;
} funk2_surrogate_parent_t;

void      funk2_surrogate_parent__init(funk2_surrogate_parent_t* this);
void      funk2_surrogate_parent__destroy(funk2_surrogate_parent_t* this);
void      funk2_surrogate_parent__handle(funk2_surrogate_parent_t* this);
void      funk2_surrogate_parent__management_start_system_command(funk2_surrogate_parent_t* this, f2ptr fiber, u8* command);
void      funk2_surrogate_parent__user_start_system_command(funk2_surrogate_parent_t* this, f2ptr fiber, u8* command);
boolean_t funk2_surrogate_parent__management_check_return_value(funk2_surrogate_parent_t* this, f2ptr fiber, funk2_return_result_t* result);
boolean_t funk2_surrogate_parent__user_check_return_value(funk2_surrogate_parent_t* this, f2ptr fiber, funk2_return_result_t* result);

// **

void f2__surrogate_parent__initialize();

#endif // F2__SURROGATE_PARENT__H


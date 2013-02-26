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

#ifndef F2__MANAGEMENT_THREAD__H
#define F2__MANAGEMENT_THREAD__H

// management_thread_command_type

typedef enum funk2_management_thread_command_type_e {
  funk2_management_thread_command_type__save_memory_image,
  funk2_management_thread_command_type__load_memory_image,
  funk2_management_thread_command_type__exit
} funk2_management_thread_command_type_t;

// management_thread_command_header

typedef struct funk2_management_thread_command_header_s {
  u64                                    uid;
  funk2_management_thread_command_type_t type;
} funk2_management_thread_command_header_t;

// management_thread_command

typedef struct funk2_management_thread_command_s {
  funk2_management_thread_command_header_t header;
  u8                                       data[0];
} funk2_management_thread_command_t;

// save_memory_image

typedef struct funk2_management_thread_command__save_memory_image_s {
  funk2_management_thread_command_header_t header;
  u64                                      filename__length;
  u8                                       filename[0];
  boolean_t                                result;
} funk2_management_thread_command__save_memory_image_t;

funk2_management_thread_command__save_memory_image_t* funk2_management_thread_command__save_memory_image__new(u8* filename);

// load_memory_image

typedef struct funk2_management_thread_command__load_memory_image_s {
  funk2_management_thread_command_header_t header;
  u64                                      filename__length;
  u8                                       filename[0];
  boolean_t                                result;
} funk2_management_thread_command__load_memory_image_t;

funk2_management_thread_command__load_memory_image_t* funk2_management_thread_command__load_memory_image__new(u8* filename);

// exit

typedef struct funk2_management_thread_command__exit_s {
  funk2_management_thread_command_header_t header;
  s64                                      value;
} funk2_management_thread_command__exit_t;

funk2_management_thread_command__exit_t* funk2_management_thread_command__exit__new(s64 value);

// management_thread__command_node

typedef struct funk2_management_thread_command_node_s {
  funk2_management_thread_command_t*             command;
  struct funk2_management_thread_command_node_s* next;
} funk2_management_thread_command_node_t;

// management_thread

typedef struct funk2_management_thread_s {
  funk2_processor_mutex_t                 next_uid__mutex;
  u64                                     next_uid;
  funk2_processor_mutex_t                 command_list__mutex;
  funk2_management_thread_command_node_t* command_list__first;
  funk2_management_thread_command_node_t* command_list__last;
  funk2_processor_mutex_t                 finished_command_list__mutex;
  funk2_management_thread_command_node_t* finished_command_list;
} funk2_management_thread_t;

void                               funk2_management_thread__init(                                     funk2_management_thread_t* this);
void                               funk2_management_thread__destroy(                                  funk2_management_thread_t* this);
u64                                funk2_management_thread__new_uid(                                  funk2_management_thread_t* this);
void                               funk2_management_thread__add_command_node_to_command_list(         funk2_management_thread_t* this, funk2_management_thread_command_node_t* node);
u64                                funk2_management_thread__add_command(                              funk2_management_thread_t* this, funk2_management_thread_command_t* command);
boolean_t                          funk2_management_thread__command_list__is_empty(                   funk2_management_thread_t* this);
funk2_management_thread_command_t* funk2_management_thread__pop_command(                              funk2_management_thread_t* this);
u64                                funk2_management_thread__add_save_command(                         funk2_management_thread_t* this, u8* filename);
u64                                funk2_management_thread__add_load_command(                         funk2_management_thread_t* this, u8* filename);
u64                                funk2_management_thread__add_exit_command(                         funk2_management_thread_t* this, s64 value);
void                               funk2_management_thread__add_command_node_to_finished_command_list(funk2_management_thread_t* this, funk2_management_thread_command_node_t* node);
void                               funk2_management_thread__command_finished(                         funk2_management_thread_t* this, funk2_management_thread_command_t* command);
void                               funk2_management_thread__handle_user_threads(                      funk2_management_thread_t* this);
boolean_t                          funk2_management_thread__check_command_uid_finished(               funk2_management_thread_t* this, u64 uid, void* user_result);

// --

u64       raw__management_thread__add_save_memory_image_command(u8* filename);
f2ptr      f2__management_thread__add_save_memory_image_command(f2ptr cause, f2ptr filename);
u64       raw__management_thread__add_load_memory_image_command(u8* filename);
f2ptr      f2__management_thread__add_load_memory_image_command(f2ptr cause, f2ptr filename);
u64       raw__management_thread__add_exit_command(s64 value);
f2ptr      f2__management_thread__add_exit_command(f2ptr cause, f2ptr value);
boolean_t raw__management_thread__check_command_uid_finished(u64 uid, void* user_result);
f2ptr      f2__management_thread__check_command_uid_finished(f2ptr cause, f2ptr uid, f2ptr user_result_place);

// **

void f2__management_thread__initialize();

#endif // F2__MANAGEMENT_THREAD__H


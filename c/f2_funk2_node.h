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

#ifndef F2__FUNK2_NODE__H
#define F2__FUNK2_NODE__H

typedef u64 node_id_t;
typedef struct funk2_node_s funk2_node_t;

#include "f2_peer_command_server.h"
#include "f2_socket_client.h"

#define node_id__fstr X64__fstr

#define THREAD_HASH__INITIAL_ARRAY_LENGTH 1024 // must be power of 2

typedef struct thread_hash_node_s {
  f2ptr                      thread;
  union {
    funk2_node_t*            funk2_node;
    funk2_packet_t*          funk2_packet;
  };
  struct thread_hash_node_s* next;
} thread_hash_node_t;

typedef struct thread_hash_s {
  thread_hash_node_t** array;
  uint                 hash_value_bit_mask;
  int                  total_thread_num;
  int                  array_length;
} thread_hash_t;

#define max_funk2_packet_size 32768

struct funk2_node_s {
  node_id_t               node_id;
  computer_id_t           computer_id;
  funk2_processor_mutex_t socket_client_mutex;
  socket_client_t         socket_client;
  boolean_t               sent_register_request;
  u64                     last_try_reconnect__nanoseconds_since_1970;
  computer_id_t           remote_computer_id_to_local_computer_id[f2ptr__computer_id__max_value + 1];
  computer_id_t           local_computer_id_to_remote_computer_id[f2ptr__computer_id__max_value + 1];
  stream_iter_t           last_recv_packet__stream_iter;
  stream_iter_t           last_sent_packet__stream_iter;
  boolean_t               last_sent_packet__is_valid;
  union {
    funk2_packet_t        last_sent_packet;
    u8                    last_sent_packet_bytes[max_funk2_packet_size];
  };
  event_id_t              last_known_event;
};

typedef struct funk2_node_list_s {
  funk2_node_t              node;
  struct funk2_node_list_s* next;
} funk2_node_list_t;

typedef struct funk2_node_handler_s {
  funk2_processor_mutex_t next_computer_id_mutex;
  computer_id_t           next_computer_id;
  funk2_node_list_t*      node_list;
  thread_hash_t           remote_thread_hash;
  funk2_processor_mutex_t remote_thread_hash_mutex;
  thread_hash_t           local_thread_hash;
  funk2_processor_mutex_t local_thread_hash_mutex;
  funk2_node_t*           funk2_node_by_computer_id_array[f2ptr__computer_id__max_value + 1];
  u32                     new_node__send_buffer_byte_num;
  u32                     new_node__recv_buffer_byte_num;
} funk2_node_handler_t;

void            thread_hash__init(thread_hash_t* this);
void            thread_hash__destroy(thread_hash_t* this);
void            thread_hash__add_thread(thread_hash_t* this, f2ptr thread, funk2_node_t* funk2_node);
funk2_node_t*   thread_hash__lookup_funk2_node(thread_hash_t* this, f2ptr thread);
funk2_packet_t* thread_hash__lookup_packet(thread_hash_t* this, f2ptr thread);

void                   funk2_node__init(funk2_node_t* this, node_id_t node_id, computer_id_t computer_id, client_id_t* client_id, u32 send_buffer_byte_num, u32 recv_buffer_byte_num);
void                   funk2_node__destroy(funk2_node_t* this);
computer_id_t          funk2_node__remote_computer_id_to_local_computer_id(funk2_node_t* this, computer_id_t remote_computer_id);
f2ptr                  funk2_node__remote_f2ptr_to_local_f2ptr(funk2_node_t* this, f2ptr remote_f2ptr);
void                   funk2_node__handle_node(funk2_node_t* this, funk2_node_handler_t* node_handler);
void                   funk2_node__send_packet(f2ptr cause, funk2_node_t* this, funk2_packet_t* packet);
void socket_rpc_layer__funk2_node__send_packet(funk2_node_t* this, funk2_packet_t* packet);
void                   funk2_node__set_computer_id_mapping(funk2_node_t* this, computer_id_t local_computer_id, computer_id_t remote_computer_id);

void            funk2_node_handler__init(funk2_node_handler_t* this, u32 new_node__send_buffer_byte_num, u32 new_node__recv_buffer_byte_num);
void            funk2_node_handler__destroy(funk2_node_handler_t* this);
computer_id_t   funk2_node_handler__add_node(funk2_node_handler_t* this, node_id_t node_id, client_id_t* client_id);
computer_id_t   funk2_node_handler__lookup_computer_id_from_node_id(funk2_node_handler_t* this, node_id_t node_id);
funk2_node_t*   funk2_node_handler__lookup_node_by_node_id(funk2_node_handler_t* this, node_id_t node_id);
funk2_node_t*   funk2_node_handler__lookup_node_by_computer_id(funk2_node_handler_t* this, computer_id_t computer_id);
funk2_node_t*   funk2_node_handler__lookup_node_by_client_id(funk2_node_handler_t* this, client_id_t* client_id);
void            funk2_node_handler__handle_nodes(funk2_node_handler_t* this);
void            funk2_node_handler__add_remote_thread_funk2_node(funk2_node_handler_t* this, f2ptr thread, funk2_node_t* funk2_node);
funk2_node_t*   funk2_node_handler__lookup_thread_execution_node(funk2_node_handler_t* this, f2ptr thread);
funk2_node_t*   funk2_node_handler__pop_thread_execution_node(funk2_node_handler_t* this, f2ptr thread);
void            funk2_node_handler__report_thread_response_packet(funk2_node_handler_t* this, f2ptr thread, funk2_packet_t* packet);
funk2_packet_t* funk2_node_handler__wait_for_new_thread_packet(funk2_node_handler_t* this, f2ptr thread);
boolean_t            funk2_node_handler__node_event_id_is_known(funk2_node_handler_t* this, node_id_t node_id, event_id_t event_id);
boolean_t            funk2_node_handler__know_of_node_event(funk2_node_handler_t* this, f2ptr event_cause, node_id_t node_id, event_id_t event_id, f2ptr type, f2ptr data);



f2ptr raw__client_id__new_from_client_id(f2ptr cause, client_id_t* client_id);

// **

void f2__funk2_node__reinitialize_globalvars();
void f2__funk2_node__initialize();
void f2__funk2_node__destroy();

#endif // F2__FUNK2_NODE__H


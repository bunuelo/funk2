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

#ifndef F2__PEER_COMMAND_SERVER__H
#define F2__PEER_COMMAND_SERVER__H

#include "f2_socket_server.h"
#include "f2_packet.h"

typedef struct funk2_peer_command_server_s {
  socket_server_list_t* socket_servers;
  circular_buffer_t     command_input_buffer;
  u64                   last_received_packet_nanoseconds_since_1970;
} funk2_peer_command_server_t;

typedef struct funk2_peer_command_server_client_s {
  socket_server_client_t*      socket_server_client;
  funk2_peer_command_server_t* peer_command_server;
  funk2_node_t*                registered_funk2_node;
  // last_times
  u64                          last_received_packet_nanoseconds_since_1970;
  u64                          last_receive_system__node_id_request_status_nanoseconds_since_1970;
  u64                          last_receive_unexpected_packet_type_status_nanoseconds_since_1970;
  // counts
  u32                          count_receive_system__node_id_request_status;
  u32                          count_receive_unexpected_packet_type_status;
} funk2_peer_command_server_client_t;

typedef enum funk2_peer_command_server_new_port_result_e {
  funk2_peer_command_server_new_port_result__success,
  funk2_peer_command_server_new_port_result__failure
} funk2_peer_command_server_new_port_result_t;



void            funk2_peer_command_server_client__init(funk2_peer_command_server_client_t* this, socket_server_client_t* socket_server_client, funk2_peer_command_server_t* peer_command_server);
void            funk2_peer_command_server_client__reset_status_counters(funk2_peer_command_server_client_t* this);
void            funk2_peer_command_server_client__destroy(funk2_peer_command_server_client_t* this);
funk2_packet_t* funk2_peer_command_server_client__recv_new_valid_packet(funk2_peer_command_server_client_t* this);
void            funk2_peer_command_server_client__recv_packet(funk2_peer_command_server_client_t* this);
void            funk2_peer_command_server_client__buffer_request_packet(funk2_peer_command_server_client_t* this, u64 nanoseconds_since_1970, funk2_packet_t* packet);
void            funk2_peer_command_server_client__execute_request(funk2_peer_command_server_client_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* packet);

void                                        funk2_peer_command_server__init(funk2_peer_command_server_t* this, u32 command_input_buffer__byte_num);
void                                        funk2_peer_command_server__destroy(funk2_peer_command_server_t* this);
funk2_peer_command_server_new_port_result_t funk2_peer_command_server__add_new_server_port(funk2_peer_command_server_t* this, char* bind_device, u8* ip_addr, u16 port_num, u32 recv_buffer__byte_num, u32 send_buffer__byte_num);
void                                        funk2_peer_command_server__handle_clients(funk2_peer_command_server_t* this);
void                                        funk2_peer_command_server__reset_status_counters(funk2_peer_command_server_t* this);
void                                        funk2_peer_command_server__flush_command_input_buffer(funk2_peer_command_server_t* this, boolean_t log_everything);
void                                        funk2_peer_command_server__command_input_buffer__write(funk2_peer_command_server_t* this, void* data, u32 byte_num);
void                                        funk2_peer_command_server__buffer_request_packet(funk2_peer_command_server_t* this, funk2_packet_t* packet);
void                                        funk2_peer_command_server__buffer_client_request_packet(funk2_peer_command_server_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* request);
funk2_packet_t*                             funk2_peer_command_server__new_request_packet_from_buffer(funk2_peer_command_server_t* this);
funk2_peer_command_server_client_t*         funk2_peer_command_server__get_client(funk2_peer_command_server_t* this, client_id_t* client_id);
void                                        funk2_peer_command_server__execute_client_request(funk2_peer_command_server_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* request);
void                                        funk2_peer_command_server__execute_funk2_packet(funk2_peer_command_server_t* this, funk2_packet_t* packet);

// **

void f2__peer_command_server__reinitialize_globalvars();
void f2__peer_command_server__initialize();
void f2__peer_command_server__destroy();

#endif // F2__PEER_COMMAND_SERVER__H


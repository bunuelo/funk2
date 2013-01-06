// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#define funk2_peer_command_server__summary_seconds 10

void funk2_peer_command_server_client__init(funk2_peer_command_server_client_t* this, socket_server_client_t* socket_server_client, funk2_peer_command_server_t* peer_command_server) {
  this->socket_server_client  = socket_server_client;
  this->peer_command_server   = peer_command_server;
  this->registered_funk2_node = NULL;
  funk2_peer_command_server_client__reset_status_counters(this);
}

void funk2_peer_command_server_client__reset_status_counters(funk2_peer_command_server_client_t* this) {
  this->last_received_packet_nanoseconds_since_1970                        = 0;
  this->last_receive_system__node_id_request_status_nanoseconds_since_1970 = 0;
  this->last_receive_unexpected_packet_type_status_nanoseconds_since_1970  = 0;
  this->count_receive_system__node_id_request_status                        = 0;
  this->count_receive_unexpected_packet_type_status                         = 0;
}

void funk2_peer_command_server_client__destroy(funk2_peer_command_server_client_t* this) {
}

void pcs_client_request_received_packet__init(pcs_client_request_received_packet_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* request) {
  u32 request__byte_num = funk2_packet__sizeof(request);
  funk2_packet_header__init(&(this->header), sizeof(funk2_packet_payload_header_t) + sizeof(client_id_t) + sizeof(u64) + request__byte_num);
  this->payload.payload_header.type = funk2_packet_type__pcs_request__client_request_received;
  client_id__copy(&(this->payload.client_id), client_id);
  this->payload.nanoseconds_since_1970 = nanoseconds_since_1970;
  memcpy(&(this->payload.request), request, request__byte_num);
}

pcs_client_request_received_packet_t* pcs_client_request_received_packet__new(client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* request) {
  u32 request__byte_num = funk2_packet__sizeof(request);
  //status("pcs_client_request_received_packet__new: request__byte_num=%d", request__byte_num);
  pcs_client_request_received_packet_t* new_packet = (pcs_client_request_received_packet_t*)from_ptr(f2__malloc(sizeof(funk2_packet_header_t) + sizeof(funk2_packet_payload_header_t) + sizeof(client_id_t) + sizeof(u64) + request__byte_num));
  pcs_client_request_received_packet__init(new_packet, client_id, nanoseconds_since_1970, request);
  return new_packet;
}


// done with send functions

funk2_packet_t* funk2_peer_command_server_client__recv_new_valid_packet(funk2_peer_command_server_client_t* this) {
  buffered_socket_t* socket      = &(this->socket_server_client->socket);
  funk2_packet_t*    recv_packet = funk2_packet__recv_new_valid_from_buffered_socket(socket);
  
  if (recv_packet) {
    this->last_received_packet_nanoseconds_since_1970 = raw__nanoseconds_since_1970();
  }
  return recv_packet;
}

void funk2_peer_command_server_client__recv_packet(funk2_peer_command_server_client_t* this) {
  buffered_socket_t* socket      = &(this->socket_server_client->socket);
  funk2_packet_t*    recv_packet = funk2_packet__recv_new_valid_from_buffered_socket(socket);
  if (recv_packet) {
    u64 nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    this->last_received_packet_nanoseconds_since_1970 = nanoseconds_since_1970;
    funk2_peer_command_server_client__buffer_request_packet(this, nanoseconds_since_1970, recv_packet);
    f2__free(to_ptr(recv_packet)); recv_packet = NULL;
  }
}

void funk2_peer_command_server_client__buffer_request_packet(funk2_peer_command_server_client_t* this, u64 nanoseconds_since_1970, funk2_packet_t* packet) {
  //funk2_packet_header_t* packet_header = (funk2_packet_header_t*)packet;
  //{
  //  int k;
  //  for (k = 0; k < sizeof(funk2_packet_header_t) + packet_header->payload_length; k ++) {
  //    u8 b = ((u8*)(packet_header))[k];
  //    if (b >= 28) {
  //	status("funk2_peer_command_server_client__buffer_request_packet: packet header byte[%d]=0x%02X %d '%c'", k, b, b, b);
  //    } else {
  //	status("funk2_peer_command_server_client__buffer_request_packet: packet header byte[%d]=0x%02X %d", k, b, b);
  //    }
  //  }
  //}
  funk2_peer_command_server__buffer_client_request_packet(this->peer_command_server, &(this->socket_server_client->client_id), nanoseconds_since_1970, packet);
}

void funk2_peer_command_server_client__execute_request(funk2_peer_command_server_client_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* packet) {
  // warning client (this) might be NULL if not connected!
  funk2_packet_payload_header_t* payload_header          = &(packet->payload_header);
  //socket_server_client_t*           socket_server_client    = this ? this->socket_server_client : NULL;
  char bind_device[128];
  char client_id_str[128];
  if (client_id) {
    snprintf(bind_device,   128, "%s", client_id->bind_device);
    snprintf(client_id_str, 128, "([%s] %d.%d.%d.%d:%d)", client_id->bind_device, client_id->ip_addr[0], client_id->ip_addr[1], client_id->ip_addr[2], client_id->ip_addr[3], client_id->port_num);
  } else {
    snprintf(bind_device,   128, "unbound device");
    snprintf(client_id_str, 128, "disconnected client");
  }
  switch(payload_header->type) {
  case funk2_packet_type__pcs_request__system__environment:
  case funk2_packet_type__pcs_respond__system__environment:
  case funk2_packet_type__pcs_request__f2ptype__raw:
  case funk2_packet_type__pcs_respond__f2ptype__raw:
  case funk2_packet_type__pcs_request__f2ptype__cause:
  case funk2_packet_type__pcs_respond__f2ptype__cause:
  case funk2_packet_type__pcs_request__f2ptype__cause__set:
  case funk2_packet_type__pcs_respond__f2ptype__cause__set:
  case funk2_packet_type__pcs_request__f2ptype__creation_fiber:
  case funk2_packet_type__pcs_respond__f2ptype__creation_fiber:
  case funk2_packet_type__pcs_request__f2ptype__creation_fiber__set:
  case funk2_packet_type__pcs_respond__f2ptype__creation_fiber__set:
  case funk2_packet_type__pcs_request__f2integer__new:
  case funk2_packet_type__pcs_respond__f2integer__new:
  case funk2_packet_type__pcs_request__f2integer__i:
  case funk2_packet_type__pcs_respond__f2integer__i:
  case funk2_packet_type__pcs_request__f2double__new:
  case funk2_packet_type__pcs_respond__f2double__new:
  case funk2_packet_type__pcs_request__f2double__d:
  case funk2_packet_type__pcs_respond__f2double__d:
  case funk2_packet_type__pcs_request__f2float__new:
  case funk2_packet_type__pcs_respond__f2float__new:
  case funk2_packet_type__pcs_request__f2float__f:
  case funk2_packet_type__pcs_respond__f2float__f:
  case funk2_packet_type__pcs_request__f2pointer__new:
  case funk2_packet_type__pcs_respond__f2pointer__new:
  case funk2_packet_type__pcs_request__f2pointer__p:
  case funk2_packet_type__pcs_respond__f2pointer__p:
  case funk2_packet_type__pcs_request__f2cmutex__new:
  case funk2_packet_type__pcs_respond__f2cmutex__new:
  case funk2_packet_type__pcs_request__f2cmutex__is_locked:
  case funk2_packet_type__pcs_respond__f2cmutex__is_locked:
  case funk2_packet_type__pcs_request__f2cmutex__unlock:
  case funk2_packet_type__pcs_respond__f2cmutex__unlock:
  case funk2_packet_type__pcs_request__f2cmutex__trylock:
  case funk2_packet_type__pcs_respond__f2cmutex__trylock:
  case funk2_packet_type__pcs_request__f2creadwritelock__new:
  case funk2_packet_type__pcs_respond__f2creadwritelock__new:
  case funk2_packet_type__pcs_request__f2creadwritelock__is_writelocked:
  case funk2_packet_type__pcs_respond__f2creadwritelock__is_writelocked:
  case funk2_packet_type__pcs_request__f2creadwritelock__is_readlocked:
  case funk2_packet_type__pcs_respond__f2creadwritelock__is_readlocked:
  case funk2_packet_type__pcs_request__f2creadwritelock__unlock:
  case funk2_packet_type__pcs_respond__f2creadwritelock__unlock:
  case funk2_packet_type__pcs_request__f2creadwritelock__trywritelock:
  case funk2_packet_type__pcs_respond__f2creadwritelock__trywritelock:
  case funk2_packet_type__pcs_request__f2creadwritelock__tryreadlock:
  case funk2_packet_type__pcs_respond__f2creadwritelock__tryreadlock:
  case funk2_packet_type__pcs_request__f2char__new:
  case funk2_packet_type__pcs_respond__f2char__new:
  case funk2_packet_type__pcs_request__f2char__ch:
  case funk2_packet_type__pcs_respond__f2char__ch:
  case funk2_packet_type__pcs_request__f2string__new:
  case funk2_packet_type__pcs_respond__f2string__new:
  case funk2_packet_type__pcs_request__f2string__length:
  case funk2_packet_type__pcs_respond__f2string__length:
  case funk2_packet_type__pcs_request__f2string__elt:
  case funk2_packet_type__pcs_respond__f2string__elt:
  case funk2_packet_type__pcs_request__f2string__elt__set:
  case funk2_packet_type__pcs_respond__f2string__elt__set:
  case funk2_packet_type__pcs_request__f2string__str_copy:
  case funk2_packet_type__pcs_respond__f2string__str_copy:
  case funk2_packet_type__pcs_request__f2string__eq_hash_value:
  case funk2_packet_type__pcs_respond__f2string__eq_hash_value:
  case funk2_packet_type__pcs_request__f2symbol__new:
  case funk2_packet_type__pcs_respond__f2symbol__new:
  case funk2_packet_type__pcs_request__f2symbol__length:
  case funk2_packet_type__pcs_respond__f2symbol__length:
  case funk2_packet_type__pcs_request__f2symbol__eq_hash_value:
  case funk2_packet_type__pcs_respond__f2symbol__eq_hash_value:
  case funk2_packet_type__pcs_request__f2symbol__elt:
  case funk2_packet_type__pcs_respond__f2symbol__elt:
  case funk2_packet_type__pcs_request__f2symbol__str_copy:
  case funk2_packet_type__pcs_respond__f2symbol__str_copy:
  case funk2_packet_type__pcs_request__f2chunk__new:
  case funk2_packet_type__pcs_respond__f2chunk__new:
  case funk2_packet_type__pcs_request__f2chunk__new_copy:
  case funk2_packet_type__pcs_respond__f2chunk__new_copy:
  case funk2_packet_type__pcs_request__f2chunk__length:
  case funk2_packet_type__pcs_respond__f2chunk__length:
  case funk2_packet_type__pcs_request__f2chunk__str_copy:
  case funk2_packet_type__pcs_respond__f2chunk__str_copy:
  case funk2_packet_type__pcs_request__f2chunk__eq_hash_value:
  case funk2_packet_type__pcs_respond__f2chunk__eq_hash_value:
  case funk2_packet_type__pcs_request__f2chunk__equals_hash_value:
  case funk2_packet_type__pcs_respond__f2chunk__equals_hash_value:
  case funk2_packet_type__pcs_request__f2chunk__bit8__elt:
  case funk2_packet_type__pcs_respond__f2chunk__bit8__elt:
  case funk2_packet_type__pcs_request__f2chunk__bit8__elt__set:
  case funk2_packet_type__pcs_respond__f2chunk__bit8__elt__set:
  case funk2_packet_type__pcs_request__f2chunk__bit16__elt:
  case funk2_packet_type__pcs_respond__f2chunk__bit16__elt:
  case funk2_packet_type__pcs_request__f2chunk__bit16__elt__set:
  case funk2_packet_type__pcs_respond__f2chunk__bit16__elt__set:
  case funk2_packet_type__pcs_request__f2chunk__bit32__elt:
  case funk2_packet_type__pcs_respond__f2chunk__bit32__elt:
  case funk2_packet_type__pcs_request__f2chunk__bit32__elt__set:
  case funk2_packet_type__pcs_respond__f2chunk__bit32__elt__set:
  case funk2_packet_type__pcs_request__f2chunk__bit64__elt:
  case funk2_packet_type__pcs_respond__f2chunk__bit64__elt:
  case funk2_packet_type__pcs_request__f2chunk__bit64__elt__set:
  case funk2_packet_type__pcs_respond__f2chunk__bit64__elt__set:
  case funk2_packet_type__pcs_request__f2chunk__cfunk_jump:
  case funk2_packet_type__pcs_respond__f2chunk__cfunk_jump:
  case funk2_packet_type__pcs_request__f2chunk__bytecode_jump:
  case funk2_packet_type__pcs_respond__f2chunk__bytecode_jump:
  case funk2_packet_type__pcs_request__f2chunk__send:
  case funk2_packet_type__pcs_respond__f2chunk__send:
  case funk2_packet_type__pcs_request__f2chunk__recv:
  case funk2_packet_type__pcs_respond__f2chunk__recv:
  case funk2_packet_type__pcs_request__f2cons__new:
  case funk2_packet_type__pcs_respond__f2cons__new:
  case funk2_packet_type__pcs_request__f2cons__car:
  case funk2_packet_type__pcs_respond__f2cons__car:
  case funk2_packet_type__pcs_request__f2cons__car__set:
  case funk2_packet_type__pcs_respond__f2cons__car__set:
  case funk2_packet_type__pcs_request__f2cons__cdr:
  case funk2_packet_type__pcs_respond__f2cons__cdr:
  case funk2_packet_type__pcs_request__f2cons__cdr__set:
  case funk2_packet_type__pcs_respond__f2cons__cdr__set:
  case funk2_packet_type__pcs_request__f2simple_array__new:
  case funk2_packet_type__pcs_respond__f2simple_array__new:
  case funk2_packet_type__pcs_request__f2simple_array__new_copy:
  case funk2_packet_type__pcs_respond__f2simple_array__new_copy:
  case funk2_packet_type__pcs_request__f2simple_array__immutable:
  case funk2_packet_type__pcs_respond__f2simple_array__immutable:
  case funk2_packet_type__pcs_request__f2simple_array__immutable__set:
  case funk2_packet_type__pcs_respond__f2simple_array__immutable__set:
  case funk2_packet_type__pcs_request__f2simple_array__length:
  case funk2_packet_type__pcs_respond__f2simple_array__length:
  case funk2_packet_type__pcs_request__f2simple_array__elt:
  case funk2_packet_type__pcs_respond__f2simple_array__elt:
  case funk2_packet_type__pcs_request__f2simple_array__elt__set:
  case funk2_packet_type__pcs_respond__f2simple_array__elt__set:
  case funk2_packet_type__pcs_request__f2larva__new:
  case funk2_packet_type__pcs_respond__f2larva__new:
  case funk2_packet_type__pcs_request__f2larva__larva_type:
  case funk2_packet_type__pcs_respond__f2larva__larva_type:
  case funk2_packet_type__pcs_request__f2larva__bug:
  case funk2_packet_type__pcs_respond__f2larva__bug:
  case funk2_packet_type__pcs_request__f2mutable_array_pointer__new:
  case funk2_packet_type__pcs_respond__f2mutable_array_pointer__new:
  case funk2_packet_type__pcs_request__f2mutable_array_pointer__array:
  case funk2_packet_type__pcs_respond__f2mutable_array_pointer__array:
  case funk2_packet_type__pcs_request__f2mutable_array_pointer__array__set:
  case funk2_packet_type__pcs_respond__f2mutable_array_pointer__array__set:
  case funk2_packet_type__pcs_request__f2mutable_array_pointer__index:
  case funk2_packet_type__pcs_respond__f2mutable_array_pointer__index:
  case funk2_packet_type__pcs_request__f2mutable_array_pointer__index__set:
  case funk2_packet_type__pcs_respond__f2mutable_array_pointer__index__set: {
    //int k;
    //for (k = 0; k < peek_byte_num; k ++) {
    //status("packet detail byte[%d]=0x%X", k, packet_data[k]);
    //}
    if (this) {
      //pcs_action_packet_t* action_packet = (pcs_action_packet_t*)packet;
      if (! (this->registered_funk2_node)) {
	error(nil, "this->registered_funk2_node == NULL");
      }
      pcs_action_packet_t* new_packet = (pcs_action_packet_t*)funk2_packet__copy(packet);
      funk2_packet__receive(this->registered_funk2_node, new_packet);
    }
    //char temp_hostname[1024];
    //snprintf(temp_hostname, 1024, "%d.%d.%d.%d", ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
  } break;
  case funk2_packet_type__pcs_request__register_peer: {
    pcs_request__register_peer_t* request = (pcs_request__register_peer_t*)packet;
    node_id_t node_id  = request->payload.node_id;
    funk2_node_t* funk2_node;
    if (node_id == __funk2.node_id) {
      funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), 0);
      this->registered_funk2_node = funk2_node;
    } else {
      u8* ip_addr = this->socket_server_client->client_id.ip_addr;
      if (request->payload.ip_addr[0] == 0 &&
	  request->payload.ip_addr[1] == 0 &&
	  request->payload.ip_addr[2] == 0 &&
	  request->payload.ip_addr[3] == 0) {
	ip_addr = this->socket_server_client->client_id.ip_addr;
      } else {
	ip_addr = request->payload.ip_addr;
      }
      u16         port_num = request->payload.port_num;
      client_id_t client_id;
      client_id__init(&client_id, (u8*)"", ip_addr, port_num);
      funk2_node = funk2_node_handler__lookup_node_by_client_id(&(__funk2.node_handler), &client_id);
      if (funk2_node == NULL) {
	computer_id_t computer_id = funk2_node_handler__add_node(&(__funk2.node_handler), node_id, &client_id);
	funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
      }
      this->registered_funk2_node = funk2_node;
    }
    if (! funk2_node) {
      error(nil, "funk2_node == NULL");
    }
    funk2_node->node_id = node_id;
  } break;
  case funk2_packet_type__pcs_request__remote_computer_id_to_node_id: {
    pcs_request__remote_computer_id_to_node_id_t* request = (pcs_request__remote_computer_id_to_node_id_t*)packet;
    computer_id_t computer_id = request->payload.computer_id;
    funk2_node_t* funk2_node  = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    if (! funk2_node) {
      error(nil, "funk2_node == NULL");
    }
    node_id_t     node_id     = funk2_node->node_id;
    if (! (this->registered_funk2_node)) {
      error(nil, "this->registered_funk2_node == NULL");
    }
    send_packet__respond__remote_computer_id_to_node_id(this->registered_funk2_node, node_id, computer_id);
  } break;
  case funk2_packet_type__pcs_respond__remote_computer_id_to_node_id: {
    pcs_respond__remote_computer_id_to_node_id_t* request = (pcs_respond__remote_computer_id_to_node_id_t*)packet;
    node_id_t     node_id               = request->payload.node_id;
    computer_id_t requester_computer_id = request->payload.computer_id;
    funk2_node_t* funk2_node            = funk2_node_handler__lookup_node_by_node_id(&(__funk2.node_handler), node_id);
    if (! funk2_node) {
      error(nil, "funk2_node == NULL");
    }
    computer_id_t computer_id           = funk2_node->computer_id;
    if (! (this->registered_funk2_node)) {
      error(nil, "this->registered_funk2_node == NULL");
    }
    funk2_node__set_computer_id_mapping(this->registered_funk2_node, computer_id, requester_computer_id);
  } break;
  case funk2_packet_type__pcs_request__client_request_received: // this packet should have already been filtered out.
  default: {
    funk2_packet_header_t* packet_header = &(packet->header);
    if (this) {
      this->count_receive_unexpected_packet_type_status ++;
      if (nanoseconds_since_1970 - this->last_receive_unexpected_packet_type_status_nanoseconds_since_1970 > funk2_peer_command_server__summary_seconds * nanoseconds_per_second) {
	this->last_receive_unexpected_packet_type_status_nanoseconds_since_1970 = nanoseconds_since_1970;
	status("%-45s  (" u32__fstr " per %u sec) funk2_peer_command_server_client__execute_request: got unexpected packet type %d (0x%X) (payload=%d).", client_id_str, this->count_receive_unexpected_packet_type_status, funk2_peer_command_server__summary_seconds, payload_header->type, payload_header->type, packet_header->payload_length);
	this->count_receive_unexpected_packet_type_status = 0;
	{
	  int k;
	  for (k = 0; k < sizeof(funk2_packet_header_t) + packet_header->payload_length; k ++) {
	    u8 b = ((u8*)(packet_header))[k];
	    if (b >= 28) {
	      status("packet header byte[%d]=%d 0x%02X '%c'", k, b, b, b);
	    } else {
	      status("packet header byte[%d]=%d 0x%02X", k, b, b);
	    }
	  }
	}
      }
    }
  } break;
  }
}

// funk2_peer_command_server

void funk2_peer_command_server__init(funk2_peer_command_server_t* this, u32 command_input_buffer__byte_num) {
  this->socket_servers = NULL;
  circular_buffer__init(&(this->command_input_buffer), command_input_buffer__byte_num);
}

void funk2_peer_command_server__destroy(funk2_peer_command_server_t* this) {
  socket_server_list_t* socket_server__iter = this->socket_servers;
  socket_server_list_t* socket_server__next = NULL;
  while (socket_server__iter) {
    socket_server__next = socket_server__iter->next;
    socket_server_t* socket_server = &(socket_server__iter->socket_server);
    socket_server__destroy(socket_server);
    f2__free(to_ptr(socket_server__iter));
    socket_server__iter = socket_server__next;
  }
  circular_buffer__destroy(&(this->command_input_buffer));
}

funk2_peer_command_server_new_port_result_t funk2_peer_command_server__add_new_server_port(funk2_peer_command_server_t* this, char* bind_device, u8* ip_addr, u16 port_num, u32 recv_buffer__byte_num, u32 send_buffer__byte_num) {
  status("funk2_peer_command_server__add_new_server_port: bind_device=\"%s\", ip_addr=%d.%d.%d.%d, port_num=%d, recv_buffer__byte_num=%d, send_buffer__byte_num=%d.",
	 bind_device,
	 ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3],
	 port_num,
	 recv_buffer__byte_num,
	 send_buffer__byte_num);
  socket_server_list_t* socket_server_node = (socket_server_list_t*)from_ptr(f2__malloc(sizeof(socket_server_list_t)));
  if (socket_server__init(&(socket_server_node->socket_server), bind_device, ip_addr, port_num, recv_buffer__byte_num, send_buffer__byte_num) != socket_server_init_result__success) {
    f2__free(to_ptr(socket_server_node));
    return funk2_peer_command_server_new_port_result__failure;
  }
  socket_server_node->next = this->socket_servers;
  this->socket_servers     = socket_server_node;
  return funk2_peer_command_server_new_port_result__success;
}

void funk2_peer_command_server_client__destroy_and_free_callback(void* data) {
  funk2_peer_command_server_client_t* client = (funk2_peer_command_server_client_t*)data;
  funk2_peer_command_server_client__destroy(client);
  f2__free(to_ptr(client));
}

void funk2_peer_command_server__handle_clients(funk2_peer_command_server_t* this) {
  socket_server_list_t* socket_server_iter = this->socket_servers;
  while (socket_server_iter) {
    socket_server_t* socket_server = (&socket_server_iter->socket_server);
    socket_server__remove_dead_clients(socket_server);
    socket_server__accept_new_clients(socket_server);
    socket_server_client_list_t* client_iter = socket_server->clients;
    while(client_iter) {
      socket_server_client_t* client = &(client_iter->client);
      if (client->socket.disconnected && buffered_socket__recv_bytes_buffered(&(client->socket)) == 0) {
	if (client->data) {
	  // if client has just logged out of server, destroy and free old command_server_client data.
	  funk2_peer_command_server_client_t* peer_command_server_client = (funk2_peer_command_server_client_t*)client->data;
	  funk2_peer_command_server_client__destroy(peer_command_server_client);
	  f2__free(to_ptr(peer_command_server_client));
	  // set client->data to NULL to signal socket_server that client can be removed from list and freed.
	  client->data = NULL;
	  char client_id_str[128];
	  snprintf(client_id_str, 128, "([%s] %d.%d.%d.%d:%d)", client->client_id.bind_device, client->client_id.ip_addr[0], client->client_id.ip_addr[1], client->client_id.ip_addr[2], client->client_id.ip_addr[3], client->client_id.port_num);
	  status("%-45s  disconnected.", client_id_str);
	}
      } else {
	// if client just logged into server, allocate and initialize new command_server_client data.
	if (client->data == NULL) {
	  client->data = (void*)from_ptr(f2__malloc(sizeof(funk2_peer_command_server_client_t)));
	  client->data__destroy_and_free = &funk2_peer_command_server_client__destroy_and_free_callback;
	  funk2_peer_command_server_client__init((funk2_peer_command_server_client_t*)client->data, client, this);
	}
	funk2_peer_command_server_client_t* peer_command_server_client = (funk2_peer_command_server_client_t*)client->data;
	funk2_peer_command_server_client__recv_packet(peer_command_server_client);
      }
      client_iter = client_iter->next;
    }
    socket_server_iter = socket_server_iter->next;
  }
}

void funk2_peer_command_server__reset_status_counters(funk2_peer_command_server_t* this) {
  socket_server_list_t* socket_server_iter = this->socket_servers;
  while (socket_server_iter) {
    socket_server_t* socket_server = (&socket_server_iter->socket_server);
    socket_server_client_list_t* client_iter = socket_server->clients;
    while(client_iter) {
      socket_server_client_t* client = &(client_iter->client);
      if (client->data) {
	funk2_peer_command_server_client_t* peer_command_server_client = (funk2_peer_command_server_client_t*)client->data;
	funk2_peer_command_server_client__reset_status_counters(peer_command_server_client);
      }
      client_iter = client_iter->next;
    }
    socket_server_iter = socket_server_iter->next;
  }
}

void funk2_peer_command_server__flush_command_input_buffer(funk2_peer_command_server_t* this, boolean_t log_everything) {
  funk2_packet_t* packet = funk2_peer_command_server__new_request_packet_from_buffer(this);
  while (packet) {
    funk2_peer_command_server__execute_funk2_packet(this, packet);
    f2__free(to_ptr(packet));
    packet = funk2_peer_command_server__new_request_packet_from_buffer(this);
  }
}

void funk2_peer_command_server__command_input_buffer__write(funk2_peer_command_server_t* this, void* data, u32 byte_num) {
  circular_buffer_t*              command_input_buffer = &(this->command_input_buffer);
  circular_buffer__write_result_t write_result         = circular_buffer__write(command_input_buffer, data, byte_num);
  switch(write_result) {
  case circular_buffer__write_result__success:
    break;
  case circular_buffer__write_result__not_enough_room:
    status("funk2 peer command server warning: command server dropping packets because of command_input_buffer overflow.");
    break;
  }
}

void funk2_peer_command_server__buffer_request_packet(funk2_peer_command_server_t* this, funk2_packet_t* packet) {
  u8 postpacket_magic[2] = {funk2_end_of_packet_byte0, funk2_end_of_packet_byte1};
  funk2_peer_command_server__command_input_buffer__write(this, packet, sizeof(funk2_packet_header_t) + packet->header.payload_length);
  funk2_peer_command_server__command_input_buffer__write(this, postpacket_magic, 2);
}

void funk2_peer_command_server__buffer_client_request_packet(funk2_peer_command_server_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* request) {
  pcs_client_request_received_packet_t* client_request_packet = pcs_client_request_received_packet__new(client_id, nanoseconds_since_1970, request);
  funk2_peer_command_server__buffer_request_packet(this, (funk2_packet_t*)client_request_packet);
  f2__free(to_ptr(client_request_packet));
}

funk2_packet_t* funk2_peer_command_server__new_request_packet_from_buffer(funk2_peer_command_server_t* this) {
  return funk2_packet__read_valid_new_from_circular_buffer(&(this->command_input_buffer));
}

funk2_peer_command_server_client_t* funk2_peer_command_server__get_client(funk2_peer_command_server_t* this, client_id_t* client_id) {
  socket_server_list_t* socket_server_iter = this->socket_servers;
  while (socket_server_iter) {
    socket_server_t*             socket_server             = &(socket_server_iter->socket_server);
    socket_server_client_list_t* socket_server_client_iter = socket_server->clients;
    while (socket_server_client_iter) {
      if (client_id__equals(&(socket_server_client_iter->client.client_id), client_id)) {
	return (funk2_peer_command_server_client_t*)(socket_server_client_iter->client.data);
      }
      socket_server_client_iter = socket_server_client_iter->next;
    }
    socket_server_iter = socket_server_iter->next;
  }
  return NULL;
}

void funk2_peer_command_server__execute_client_request(funk2_peer_command_server_t* this, client_id_t* client_id, u64 nanoseconds_since_1970, funk2_packet_t* request) {
  funk2_peer_command_server_client_t* client = funk2_peer_command_server__get_client(this, client_id);
  // client requests have effects on the server state that can be remembered
  funk2_peer_command_server_client__execute_request(client, client_id, nanoseconds_since_1970, request);
}

void funk2_peer_command_server__execute_funk2_packet(funk2_peer_command_server_t* this, funk2_packet_t* packet) {
  funk2_packet_payload_header_t* payload_header = &(packet->payload_header);
  switch(payload_header->type) {
  case funk2_packet_type__pcs_request__client_request_received: {
    pcs_client_request_received_packet_t* client_request_received = (pcs_client_request_received_packet_t*)packet;
    client_id_t                           client_id;
    memcpy(&client_id, &(client_request_received->payload.client_id), sizeof(client_id_t));
    funk2_peer_command_server__execute_client_request(this, &client_id, client_request_received->payload.nanoseconds_since_1970, &(client_request_received->payload.request));
  } break;
  default: {
    funk2_packet_header_t* packet_header = &(packet->header);
    status("funk2_peer_command_server got unexpected packet type %d (0x%X) (payload=%d).", payload_header->type, payload_header->type, packet_header->payload_length);
    {
      int k;
      for (k = 0; k < sizeof(funk2_packet_header_t) + packet_header->payload_length; k ++) {
	u8 b = ((u8*)(packet_header))[k];
	if (b >= 28) {
	  status("packet header byte[%d]=%d 0x%02X '%c'", k, b, b, b);
	} else {
	  status("packet header byte[%d]=%d 0x%02X", k, b, b);
	}
      }
    }
  } break;
  }
}

f2ptr f2__peer_command_server__active_client_info(f2ptr cause) {
  f2ptr seq = nil;
  socket_server_list_t* socket_server_iter = __funk2.peer_command_server.socket_servers;
  while (socket_server_iter) {
    socket_server_t*             socket_server             = &(socket_server_iter->socket_server);
    socket_server_client_list_t* socket_server_client_iter = socket_server->clients;
    while (socket_server_client_iter) {
      funk2_peer_command_server_client_t* client = (funk2_peer_command_server_client_t*)(socket_server_client_iter->client.data);
      if (client != NULL) {
	f2ptr client_object = raw__array__new(cause, 2);
	f2ptr client_object__client_id   = raw__client_id__new_from_client_id(cause, &(client->socket_server_client->client_id));
	f2ptr client_object__computer_id = client->registered_funk2_node ? f2integer__new(cause, client->registered_funk2_node->computer_id) : nil;
	raw__array__elt__set(cause, client_object, 0, client_object__client_id);
	raw__array__elt__set(cause, client_object, 1, client_object__computer_id);
	seq = raw__cons__new(cause, client_object, seq);
      }
      socket_server_client_iter = socket_server_client_iter->next;
    }
    socket_server_iter = socket_server_iter->next;
  }
  return seq;
}

def_pcfunk0(peer_command_server__active_client_info,
	    "",
	    return f2__peer_command_server__active_client_info(this_cause));



// **

void f2__peer_command_server__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(peer_command_server__active_client_info);
  
}

void f2__peer_command_server__reinitialize_globalvars() {
  f2__primcfunk__init(peer_command_server__active_client_info);
}

void f2__peer_command_server__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "peer_command_server", "", &f2__peer_command_server__reinitialize_globalvars, &f2__peer_command_server__defragment__fix_pointers);
  
  f2__peer_command_server__reinitialize_globalvars();
}

void f2__peer_command_server__destroy() {
}


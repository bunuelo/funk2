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

void fiber_hash__init(fiber_hash_t* this) {
  this->array               = (fiber_hash_node_t**)from_ptr(f2__malloc(sizeof(fiber_hash_node_t*) * FIBER_HASH__INITIAL_ARRAY_LENGTH));
  bzero(this->array, sizeof(fiber_hash_node_t*) * FIBER_HASH__INITIAL_ARRAY_LENGTH);
  this->hash_value_bit_mask = FIBER_HASH__INITIAL_ARRAY_LENGTH - 1; // assumes FIBER_HASH__INITIAL_ARRAY_LENGTH is power of 2
  this->array_length        = FIBER_HASH__INITIAL_ARRAY_LENGTH;
}

void fiber_hash__destroy(fiber_hash_t* this) {
  f2__free(to_ptr(this->array));
}

void fiber_hash__add_fiber_funk2_node(fiber_hash_t* this, f2ptr fiber, funk2_node_t* funk2_node) {
  uint               bin_index = fiber & this->hash_value_bit_mask;
  fiber_hash_node_t* new_node  = (fiber_hash_node_t*)from_ptr(f2__malloc(sizeof(fiber_hash_node_t)));
  new_node->fiber        = fiber;
  new_node->funk2.node   = funk2_node;
  new_node->next         = this->array[bin_index];
  this->array[bin_index] = new_node;
}

void fiber_hash__add_fiber_funk2_packet(fiber_hash_t* this, f2ptr fiber, funk2_packet_t* funk2_packet) {
  uint               bin_index = fiber & this->hash_value_bit_mask;
  fiber_hash_node_t* new_node  = (fiber_hash_node_t*)from_ptr(f2__malloc(sizeof(fiber_hash_node_t)));
  new_node->fiber        = fiber;
  new_node->funk2.packet = funk2_packet;
  new_node->next         = this->array[bin_index];
  this->array[bin_index] = new_node;
}

fiber_hash_node_t* fiber_hash__lookup_fiber_hash_node(fiber_hash_t* this, f2ptr fiber) {
  uint bin_index = fiber & this->hash_value_bit_mask;
  fiber_hash_node_t* node = this->array[bin_index];
  while (node) {
    if (node->fiber == fiber) {
      return node;
    }
    node = node->next;
  }
  return NULL;
}

funk2_node_t* fiber_hash__lookup_funk2_node(fiber_hash_t* this, f2ptr fiber) {
  fiber_hash_node_t* fiber_hash_node = fiber_hash__lookup_fiber_hash_node(this, fiber);
  funk2_node_t* funk2_node;
  if (fiber_hash_node) {
    funk2_node = fiber_hash_node->funk2.node;
  } else {
    funk2_node = NULL;
  }
  return funk2_node;
}

funk2_node_t* fiber_hash__pop_funk2_node(fiber_hash_t* this, f2ptr fiber) {
  fiber_hash_node_t* fiber_hash_node = fiber_hash__lookup_fiber_hash_node(this, fiber);
  funk2_node_t* funk2_node;
  if (fiber_hash_node) {
    funk2_node = fiber_hash_node->funk2.node;
    fiber_hash_node->funk2.node = NULL;
  } else {
    funk2_node = NULL;
  }
  return funk2_node;
}

funk2_packet_t* fiber_hash__lookup_funk2_packet(fiber_hash_t* this, f2ptr fiber) {
  fiber_hash_node_t* fiber_hash_node = fiber_hash__lookup_fiber_hash_node(this, fiber);
  funk2_packet_t* packet;
  if (fiber_hash_node) {
    packet = fiber_hash_node->funk2.packet;
  } else {
    packet = NULL;
  }
  return packet;
}

funk2_packet_t* fiber_hash__pop_funk2_packet(fiber_hash_t* this, f2ptr fiber) {
  fiber_hash_node_t* fiber_hash_node = fiber_hash__lookup_fiber_hash_node(this, fiber);
  funk2_packet_t* packet;
  if (fiber_hash_node) {
    packet = fiber_hash_node->funk2.packet;
    fiber_hash_node->funk2.packet = NULL;
  } else {
    packet = NULL;
  }
  return packet;
}

void funk2_node__init(funk2_node_t* this, node_id_t node_id, computer_id_t computer_id, client_id_t* client_id, u32 send_buffer_byte_num, u32 recv_buffer_byte_num) {
  client_id__copy(&(this->socket_client.client_id), client_id);
  char hostname[128];
  sprintf(hostname, "%d.%d.%d.%d", client_id->ip_addr[0], client_id->ip_addr[1], client_id->ip_addr[2], client_id->ip_addr[3]);
  funk2_processor_mutex__init(&(this->socket_client_mutex));
  socket_client__init(&(this->socket_client), "", hostname, client_id->port_num, send_buffer_byte_num, recv_buffer_byte_num);
  this->node_id                                    = node_id;
  this->computer_id                                = computer_id;
  this->sent_register_request                      = boolean__false;
  this->last_try_reconnect__nanoseconds_since_1970 = 0;
  int i;
  for (i = 0; i < f2ptr__computer_id__max_value + 1; i ++) {
    this->remote_computer_id_to_local_computer_id[i] = f2ptr__computer_id__max_value;
    this->local_computer_id_to_remote_computer_id[i] = f2ptr__computer_id__max_value;
  }
  this->last_sent_packet__stream_iter = 123; // by definition, not the first packet to be received.
  this->last_sent_packet__is_valid    = boolean__false;
  this->last_known_event              = 0;
}

void funk2_node__destroy(funk2_node_t* this) {
  socket_client__destroy(&(this->socket_client));
  funk2_processor_mutex__destroy(&(this->socket_client_mutex));
}

// this can only be called from socket_rpc_layer
computer_id_t funk2_node__remote_computer_id_to_local_computer_id(funk2_node_t* this, computer_id_t remote_computer_id) {
  //printf("\nrf2_to_lf2: asking node_id=#x" X64__fstr ", remote_computer_id=%d", this->node_id, remote_computer_id);
  if (this->computer_id == 0) { // remote is local
    return remote_computer_id;
  }
  if (remote_computer_id >= f2ptr__computer_id__max_value) {
    error(nil, "funk2_node__remote_computer_id_to_local_computer_id error: remote computer_id out of range");
  }
  computer_id_t local_computer_id = this->remote_computer_id_to_local_computer_id[remote_computer_id];
  if (local_computer_id != f2ptr__computer_id__max_value) {
    //printf("\n          : local_computer_id=%d (cached)", local_computer_id);
    return local_computer_id;
  }
  send_packet__request__remote_computer_id_to_node_id(this, remote_computer_id);
  while (local_computer_id == f2ptr__computer_id__max_value) {
    local_computer_id = this->remote_computer_id_to_local_computer_id[remote_computer_id];
    funk2__handle(&__funk2);
  }
  //printf("\n          : local_computer_id=%d (fetched from peer command server)", local_computer_id);
  return local_computer_id;
}

f2ptr funk2_node__remote_f2ptr_to_local_f2ptr(funk2_node_t* this, f2ptr remote_f2ptr) {
  // nil is special because it is the only thing that is the same across the entire network.
  if (! remote_f2ptr) {
    return nil;
  }
  computer_id_t remote_computer_id = __f2ptr__computer_id(remote_f2ptr);
  computer_id_t local_computer_id  = funk2_node__remote_computer_id_to_local_computer_id(this, remote_computer_id);
  f2ptr local_f2ptr = f2ptr__new(local_computer_id, __f2ptr__pool_index(remote_f2ptr), __f2ptr__pool_block_address(remote_f2ptr));
  //status("funk2_node__remote_f2ptr_to_local_f2ptr: remote_f2ptr=" f2ptr__fstr ", local_f2ptr=" f2ptr__fstr ".", remote_f2ptr, local_f2ptr);
  return local_f2ptr;
}

void funk2_node__handle_node(funk2_node_t* this, funk2_node_handler_t* node_handler) {
  funk2_processor_mutex__lock(&(this->socket_client_mutex));
  //printf("\nfunk2_node__handle_node note: handling funk2 node (node_id=" node_id__fstr ") %d.%d.%d.%d:%d.",
  //	 this->node_id, this->socket_client.client_id.ip_addr[0], this->socket_client.client_id.ip_addr[1], this->socket_client.client_id.ip_addr[2], this->socket_client.client_id.ip_addr[3], this->socket_client.client_id.port_num);
  if (this->socket_client.socket.disconnected) {
    u64 nanoseconds_since_1970 = raw__nanoseconds_since_1970();
    if (nanoseconds_since_1970 - this->last_try_reconnect__nanoseconds_since_1970 > 10 * 1000000) {
      this->last_try_reconnect__nanoseconds_since_1970 = nanoseconds_since_1970;
      socket_client_connect_result_t result = socket_client__try_reconnect(&(this->socket_client));
      if (result != socket_client_connect_result__success) {
	status("funk2_node__handle_node error: failed to reconnect to funk2 node (node_id=" node_id__fstr ") %d.%d.%d.%d:%d.",
	       this->node_id, this->socket_client.client_id.ip_addr[0], this->socket_client.client_id.ip_addr[1], this->socket_client.client_id.ip_addr[2], this->socket_client.client_id.ip_addr[3], this->socket_client.client_id.port_num);
	funk2_processor_mutex__unlock(&(this->socket_client_mutex));
      } else {
	status("funk2_node__handle_node note: trying to reconnect to funk2 node (node_id=" node_id__fstr ") %d.%d.%d.%d:%d.",
	       this->node_id, this->socket_client.client_id.ip_addr[0], this->socket_client.client_id.ip_addr[1], this->socket_client.client_id.ip_addr[2], this->socket_client.client_id.ip_addr[3], this->socket_client.client_id.port_num);
	// after disconnect and reconnect, send last sent packet again.
	funk2_processor_mutex__unlock(&(this->socket_client_mutex));
	if (this->last_sent_packet__is_valid) {
	  socket_rpc_layer__funk2_node__send_packet(this, &(this->last_sent.packet));
	}
      }
    } else {
      funk2_processor_mutex__unlock(&(this->socket_client_mutex));
    }
  } else {
    buffered_socket__error_type_t result = buffered_socket__flush(&(this->socket_client.socket));
    if (result != buffered_socket__error_type__success) {
      status("funk2_node__handle_node error: failed to flush funk2 node socket (node_id=" node_id__fstr ") %d.%d.%d.%d:%d.",
	     this->node_id, this->socket_client.client_id.ip_addr[0], this->socket_client.client_id.ip_addr[1], this->socket_client.client_id.ip_addr[2], this->socket_client.client_id.ip_addr[3], this->socket_client.client_id.port_num);
      funk2_processor_mutex__unlock(&(this->socket_client_mutex));
    } else {
      funk2_packet_t* packet = funk2_packet__recv_new_valid_from_buffered_socket(&(this->socket_client.socket));
      if (packet) {
	funk2_processor_mutex__unlock(&(this->socket_client_mutex));
	funk2_packet__receive(this, (pcs_action_packet_t*)packet);
      } else {
	funk2_processor_mutex__unlock(&(this->socket_client_mutex));
      }
      if (! (this->sent_register_request)) {
	u8 ip_addr[4] = {0, 0, 0, 0};
	rpc_socket_layer__send_packet__request__register_peer(this, __funk2.node_id, ip_addr, __funk2.command_line.peer_command_server__port_num);
	this->sent_register_request = boolean__true;
      }
    }
  }
}

void funk2_node__set_computer_id_mapping(funk2_node_t* this, computer_id_t local_computer_id, computer_id_t remote_computer_id) {
  this->remote_computer_id_to_local_computer_id[remote_computer_id] = local_computer_id;
  this->local_computer_id_to_remote_computer_id[local_computer_id]  = remote_computer_id;
}

void funk2_node__send_packet(f2ptr cause, funk2_node_t* this, funk2_packet_t* packet) {
  funk2_processor_mutex__lock(&(this->socket_client_mutex));
  this->last_sent_packet__stream_iter ++;
  packet->header.stream_iter = this->last_sent_packet__stream_iter;
  u64 packet__size = funk2_packet__sizeof(packet);
  memcpy(&(this->last_sent.packet), packet, packet__size);
  this->last_sent_packet__is_valid = boolean__true;
  funk2_packet__send_to_socket(cause, packet, &(this->socket_client.socket));
  funk2_processor_mutex__unlock(&(this->socket_client_mutex));
}

void socket_rpc_layer__funk2_node__send_packet(funk2_node_t* this, funk2_packet_t* packet) {
  funk2_processor_mutex__lock(&(this->socket_client_mutex));
  this->last_sent_packet__stream_iter ++;
  packet->header.stream_iter = this->last_sent_packet__stream_iter;
  u64 packet__size = funk2_packet__sizeof(packet);
  memcpy(&(this->last_sent.packet), packet, packet__size);
  this->last_sent_packet__is_valid = boolean__true;
  socket_rpc_layer__funk2_packet__send_to_socket(packet, &(this->socket_client.socket));
  funk2_processor_mutex__unlock(&(this->socket_client_mutex));
}

void funk2_node_handler__init(funk2_node_handler_t* this, u32 new_node__send_buffer_byte_num, u32 new_node__recv_buffer_byte_num) {
  funk2_processor_mutex__init(&(this->next_computer_id_mutex));
  this->next_computer_id               = 0;
  this->node_list                      = NULL;
  this->new_node__send_buffer_byte_num = new_node__send_buffer_byte_num;
  this->new_node__recv_buffer_byte_num = new_node__recv_buffer_byte_num;
  funk2_processor_mutex__init(&(this->remote_fiber_hash_mutex));
  fiber_hash__init(&(this->remote_fiber_hash));
  funk2_processor_mutex__init(&(this->local_fiber_hash_mutex));
  fiber_hash__init(&(this->local_fiber_hash));
  int i;
  for (i = 0; i < f2ptr__computer_id__max_value + 1; i ++) {
    this->funk2_node_by_computer_id_array[i] = NULL;
  }
}

void funk2_node_handler__destroy(funk2_node_handler_t* this) {
  funk2_node_list_t* iter = this->node_list;
  while (iter) {
    funk2_node_t*      node = &(iter->node);
    funk2_node_list_t* next = iter->next;
    funk2_node__destroy(node);
    free(iter);
    iter = next;
  }
  funk2_processor_mutex__destroy(&(this->remote_fiber_hash_mutex));
  fiber_hash__destroy(&(this->remote_fiber_hash));
  funk2_processor_mutex__destroy(&(this->local_fiber_hash_mutex));
  fiber_hash__destroy(&(this->local_fiber_hash));
  funk2_processor_mutex__destroy(&(this->next_computer_id_mutex));
}

computer_id_t funk2_node_handler__add_node(funk2_node_handler_t* this, node_id_t node_id, client_id_t* client_id) {
  //printf("\nfunk2_node_handler__add_node note: added funk2 node (node_id=" node_id__fstr ") %d.%d.%d.%d:%d", node_id, client_id->ip_addr[0], client_id->ip_addr[1], client_id->ip_addr[2], client_id->ip_addr[3], client_id->port_num);
  computer_id_t computer_id;
  {
    funk2_processor_mutex__lock(&(this->next_computer_id_mutex));
    computer_id = this->next_computer_id;
    this->next_computer_id ++;
    funk2_processor_mutex__unlock(&(this->next_computer_id_mutex));
  }
  funk2_node_list_t* new_node_list = (funk2_node_list_t*)malloc(sizeof(funk2_node_list_t));
  funk2_node__init(&(new_node_list->node), node_id, computer_id, client_id, this->new_node__send_buffer_byte_num, this->new_node__recv_buffer_byte_num);
  new_node_list->next = this->node_list;
  this->node_list = new_node_list;
  if (computer_id > f2ptr__computer_id__max_value) {
    error(nil, "computer_id out of range.");
  }
  if (this->funk2_node_by_computer_id_array[computer_id] != NULL) {
    error(nil, "computer_id already used for node.");
  }
  this->funk2_node_by_computer_id_array[computer_id] = &(new_node_list->node);
  return computer_id;
}

funk2_node_t* funk2_node_handler__lookup_node_by_node_id(funk2_node_handler_t* this, node_id_t node_id) {
  funk2_node_list_t* iter = this->node_list;
  while (iter) {
    funk2_node_t* node = &(iter->node);
    if (node->node_id == node_id) {
      return node;
    }
    iter = iter->next;
  }
  return NULL;
}

funk2_node_t* funk2_node_handler__lookup_node_by_client_id(funk2_node_handler_t* this, client_id_t* client_id) {
  funk2_node_list_t* iter = this->node_list;
  while (iter) {
    funk2_node_t* node = &(iter->node);
    if (client_id__equals(&(node->socket_client.client_id), client_id)) {
      return node;
    }
    iter = iter->next;
  }
  return NULL;
}

computer_id_t funk2_node_handler__lookup_computer_id_from_node_id(funk2_node_handler_t* this, node_id_t node_id) {
  funk2_node_t* node = funk2_node_handler__lookup_node_by_node_id(this, node_id);
  if (! node) {
    return -1;
  }
  return node->computer_id;
}

funk2_node_t* funk2_node_handler__lookup_node_by_computer_id(funk2_node_handler_t* this, computer_id_t computer_id) {
  if (computer_id > f2ptr__computer_id__max_value) {
    error(nil, "computer_id out of range.");
  }
  return this->funk2_node_by_computer_id_array[computer_id];
}

void funk2_node_handler__handle_nodes(funk2_node_handler_t* this) {
  //printf("\nfunk2_node_handler__handle_nodes note: running.");
  funk2_node_list_t* iter = this->node_list;
  while (iter) {
    funk2_node_t* node = &(iter->node);
    funk2_node__handle_node(node, this);
    iter = iter->next;
  }
}

void funk2_node_handler__add_remote_fiber_funk2_node(funk2_node_handler_t* this, f2ptr fiber, funk2_node_t* funk2_node) {
  fiber_hash__add_fiber_funk2_node(&(this->remote_fiber_hash), fiber, funk2_node);
}

void funk2_node_handler__add_local_fiber_funk2_packet(funk2_node_handler_t* this, f2ptr fiber, funk2_packet_t* funk2_packet) {
  fiber_hash__add_fiber_funk2_packet(&(this->local_fiber_hash), fiber, funk2_packet);
}

funk2_node_t* funk2_node_handler__lookup_remote_fiber_funk2_node(funk2_node_handler_t* this, f2ptr fiber) {
  funk2_processor_mutex__lock(&(this->remote_fiber_hash_mutex));
  funk2_node_t* funk2_node = fiber_hash__lookup_funk2_node(&(this->remote_fiber_hash), fiber);
  funk2_processor_mutex__unlock(&(this->remote_fiber_hash_mutex));
  return funk2_node;
}

funk2_node_t* funk2_node_handler__pop_remote_fiber_funk2_node(funk2_node_handler_t* this, f2ptr fiber) {
  funk2_processor_mutex__lock(&(this->remote_fiber_hash_mutex));
  funk2_node_t* funk2_node = fiber_hash__pop_funk2_node(&(this->remote_fiber_hash), fiber);
  funk2_processor_mutex__unlock(&(this->remote_fiber_hash_mutex));
  return funk2_node;
}

funk2_packet_t* funk2_node_handler__lookup_local_fiber_funk2_packet(funk2_node_handler_t* this, f2ptr fiber) {
  funk2_processor_mutex__lock(&(this->local_fiber_hash_mutex));
  funk2_packet_t* funk2_packet = fiber_hash__lookup_funk2_packet(&(this->local_fiber_hash), fiber);
  funk2_processor_mutex__unlock(&(this->local_fiber_hash_mutex));
  return funk2_packet;
}

funk2_packet_t* funk2_node_handler__pop_local_fiber_funk2_packet(funk2_node_handler_t* this, f2ptr fiber) {
  funk2_processor_mutex__lock(&(this->local_fiber_hash_mutex));
  funk2_packet_t* funk2_packet = fiber_hash__pop_funk2_packet(&(this->local_fiber_hash), fiber);
  funk2_processor_mutex__unlock(&(this->local_fiber_hash_mutex));
  return funk2_packet;
}

funk2_node_t* funk2_node_handler__lookup_fiber_execution_node(funk2_node_handler_t* this, f2ptr fiber) {
  funk2_node_t* remote_node = funk2_node_handler__lookup_remote_fiber_funk2_node(this, fiber);
  if (! remote_node) {
    error(nil, "funk2_node_handler__lookup_fiber_execution_node error: don't know of fiber.");
  }
  return remote_node;
}

void funk2_node_handler__report_fiber_response_packet(funk2_node_handler_t* this, f2ptr fiber, funk2_packet_t* packet) {
  //printf ("\nfunk2_node_handler__report_fiber_response_packet: fiber=" f2ptr__fstr "\n", fiber); fflush(stdout);
  funk2_node_handler__add_local_fiber_funk2_packet(this, fiber, packet);
}

funk2_packet_t* funk2_node_handler__wait_for_new_fiber_packet(funk2_node_handler_t* this, f2ptr fiber) {
  //printf ("\nfunk2_node_handler__wait_for_new_fiber_packet: fiber=" f2ptr__fstr "\n", fiber); fflush(stdout);
  funk2_node_t*   funk2_node = funk2_node_handler__lookup_remote_fiber_funk2_node(this, fiber);;
  funk2_packet_t* response_packet = NULL;
  while (response_packet == NULL) {
    response_packet = funk2_node_handler__pop_local_fiber_funk2_packet(this, fiber);
    if ((funk2_node != NULL) &&
	(response_packet->header.stream_iter == funk2_node->last_recv_packet__stream_iter)) {
      status("funk2_node_handler__wait_for_new_fiber_packet warning: detected and dumped duplicate received packet.");
      f2__free(to_ptr(response_packet));
      response_packet = NULL;
    }
    if (! response_packet) {
      raw__spin_sleep_yield();
    }
  }
  return response_packet;
}

boolean_t funk2_node_handler__node_event_id_is_known(funk2_node_handler_t* this, node_id_t node_id, event_id_t event_id) {
  funk2_node_t* node = funk2_node_handler__lookup_node_by_node_id(this, node_id);
  if (! node) {
    error(nil, "funk2_node_handler__already_know_of_node_event error: invalid node_id.");
  }
  if (event_id <= node->last_known_event) {
    return boolean__true;
  }
  return boolean__false;
}

// **

f2ptr f2__ip_addr__new(f2ptr cause, f2ptr b0, f2ptr b1, f2ptr b2, f2ptr b3) {
  f2ptr this = raw__array__new(cause, 5);
  raw__array__elt__set(cause, this, 0, new__symbol(cause, "ip_addr"));
  raw__array__elt__set(cause, this, 1, b0);
  raw__array__elt__set(cause, this, 2, b1);
  raw__array__elt__set(cause, this, 3, b2);
  raw__array__elt__set(cause, this, 4, b3);
  return this;
}

f2ptr raw__ip_addr__new(f2ptr cause, u8* ip_addr) {
  return f2__ip_addr__new(cause, f2integer__new(cause, ip_addr[0]), f2integer__new(cause, ip_addr[1]), f2integer__new(cause, ip_addr[2]), f2integer__new(cause, ip_addr[3]));
}

f2ptr f2__client_id__new(f2ptr cause, f2ptr bind_device, f2ptr ip_addr, f2ptr port_num) {
  f2ptr this = raw__array__new(cause, 4);
  raw__array__elt__set(cause, this, 0, new__symbol(cause, "client_id"));
  raw__array__elt__set(cause, this, 1, bind_device);
  raw__array__elt__set(cause, this, 2, ip_addr);
  raw__array__elt__set(cause, this, 3, port_num);
  return this;
}

f2ptr raw__client_id__new_from_client_id(f2ptr cause, client_id_t* client_id) {
  return f2__client_id__new(cause,
			    new__symbol(cause, (char*)(client_id->bind_device)),
			    raw__ip_addr__new(cause, client_id->ip_addr),
			    f2integer__new(cause, client_id->port_num));
}

f2ptr f2__funk2_node_info__new(f2ptr cause, f2ptr node_id, f2ptr computer_id, f2ptr client_id, f2ptr disconnected) {
  f2ptr this = raw__array__new(cause, 5);
  raw__array__elt__set(cause, this, 0, new__symbol(cause, "funk2_node_info"));
  raw__array__elt__set(cause, this, 1, node_id);
  raw__array__elt__set(cause, this, 2, computer_id);
  raw__array__elt__set(cause, this, 3, client_id);
  raw__array__elt__set(cause, this, 4, disconnected);
  return this;
}

f2ptr f2__funk2_node_handler__known_node_info(f2ptr cause) {
  f2ptr seq = nil;
  funk2_node_list_t* iter = __funk2.node_handler.node_list;
  while (iter) {
    funk2_node_t* node = &(iter->node);
    seq = raw__cons__new(cause,
			 f2__funk2_node_info__new(cause,
						  f2pointer__new(cause, node->node_id),
						  f2integer__new(cause, node->computer_id),
						  raw__client_id__new_from_client_id(cause, &(node->socket_client.client_id)),
						  node->socket_client.socket.disconnected ? new__symbol(cause, "disconnected") : nil),
			 seq);
    iter = iter->next;
  }
  return seq;
}

def_pcfunk0(funk2_node_handler__known_node_info,
	    "",
	    return f2__funk2_node_handler__known_node_info(this_cause));


// **

void f2__funk2_node__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(funk2_node_handler__known_node_info);
  
}

void f2__funk2_node__reinitialize_globalvars() {
  f2__primcfunk__init(funk2_node_handler__known_node_info);
}

void f2__funk2_node__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "funk2_node", "", &f2__funk2_node__reinitialize_globalvars, &f2__funk2_node__defragment__fix_pointers);
  
  f2__funk2_node__reinitialize_globalvars();
}

void f2__funk2_node__destroy() {
}




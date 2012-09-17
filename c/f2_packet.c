// 
// Copyright (c) 2007-2008 Bo Morgan.
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

void funk2_packet_header__init(funk2_packet_header_t* this, u16 payload_length) {
  this->start_of_packet_byte = funk2_start_of_packet_byte;
  this->channel              = funk2_channel_byte;
  this->payload_length       = payload_length;
  this->stream_iter          = 0; // set at funk2_node send-time to order the stream of packets.
}

u32 funk2_packet__sizeof(funk2_packet_t* this) {
  return sizeof(funk2_packet_header_t) + this->header.payload_length;
}

funk2_packet_t* funk2_packet__copy(funk2_packet_t* this) {
  u64 packet_size = funk2_packet__sizeof(this);
  funk2_packet_t* new = (funk2_packet_t*)from_ptr(f2__malloc(packet_size));
  memcpy(new, this, packet_size);
  return new;
}

funk2_packet_t* funk2_packet__peek_read_new_from_circular_buffer(circular_buffer_t* buffer, u32* peek_byte_num, boolean_t* invalid_packet_found) {
  funk2_packet_t  temp_packet;
  funk2_packet_t* new_packet;
  boolean_t       valid_packet_found = boolean__false;
  *invalid_packet_found = boolean__false;
  *peek_byte_num        = 0;
  if (circular_buffer__get_used_byte_num(buffer) >= sizeof(funk2_packet_header_t)) {
    circular_buffer__peek_read(buffer, &temp_packet, sizeof(funk2_packet_header_t), NULL);
    if (temp_packet.header.start_of_packet_byte != funk2_start_of_packet_byte ||
	temp_packet.header.channel              != funk2_channel_byte) {
      *invalid_packet_found = boolean__true; // should scan one byte ahead
    } else {
      // start magic found
      if (circular_buffer__get_used_byte_num(buffer) >= sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2) {
	new_packet = (funk2_packet_t*)from_ptr(f2__malloc(sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2));
	circular_buffer__peek_read(buffer, new_packet, sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2, NULL);
	u8* end_of_packet_packet_bytes = ((u8*)(new_packet)) + sizeof(funk2_packet_header_t) + temp_packet.header.payload_length;
	if (end_of_packet_packet_bytes[0] != funk2_end_of_packet_byte0 ||
	    end_of_packet_packet_bytes[1] != funk2_end_of_packet_byte1) {
	  f2__free(to_ptr(new_packet)); new_packet = NULL;
	  *invalid_packet_found = boolean__true;
	} else {
	  *peek_byte_num = sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2;
	  valid_packet_found = boolean__true;
	}
      }
    }
  }
  if (! valid_packet_found) {
    return NULL;
  }
  return new_packet;
}

funk2_packet_t* funk2_packet__read_valid_new_from_circular_buffer(circular_buffer_t* buffer) {
  u32             peek_byte_num;
  boolean_t            invalid_packet_found;
  funk2_packet_t* recv_packet = funk2_packet__peek_read_new_from_circular_buffer(buffer, &peek_byte_num, &invalid_packet_found);
  
  if (invalid_packet_found) {
    circular_buffer__seek_ahead(buffer, 1, NULL); // bye bye
    recv_packet = NULL;
  }
  //printf("\n  were %d bytes left in buffer.", circular_buffer__get_used_byte_num(buffer));
  if (recv_packet) {
    if (circular_buffer__seek_ahead(buffer, peek_byte_num, NULL) != circular_buffer__seek_ahead_result__success) {
      printf("\nfunk2_packet__read_valid_new_from_circular_buffer failed to seek ahead %d bytes.", peek_byte_num);
    } else {
      //printf("\nfunk2_packet__read_valid_new_from_circular_buffer sucessfully sought ahead %d bytes.", peek_byte_num);
    }
  }
  //printf("\n   now %d bytes are left in buffer.", circular_buffer__get_used_byte_num(buffer));
  return recv_packet; // could return NULL if buffer doesn't have enough data.
}

funk2_packet_t* funk2_packet__peek_recv_new_from_buffered_socket(buffered_socket_t* socket, u32* peek_byte_num, boolean_t* invalid_packet_found) {
  funk2_packet_t  temp_packet;
  funk2_packet_t* new_packet;
  boolean_t       valid_packet_found = boolean__false;
  *invalid_packet_found = boolean__false;
  *peek_byte_num        = 0;
  buffered_socket__flush(socket);
  if (buffered_socket__recv_bytes_buffered(socket) >= sizeof(funk2_packet_header_t)) {
    buffered_socket__peek_recv(socket, &temp_packet, sizeof(funk2_packet_header_t));
    if (temp_packet.header.start_of_packet_byte != funk2_start_of_packet_byte ||
	temp_packet.header.channel              != funk2_channel_byte) {
      *invalid_packet_found = boolean__true; // should scan one byte ahead
    } else {
      // start magic found
      if (buffered_socket__recv_bytes_buffered(socket) >= sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2) {
	new_packet = (funk2_packet_t*)from_ptr(f2__malloc(sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2));
	buffered_socket__peek_recv(socket, new_packet, sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2);
	u8* end_of_packet_packet_bytes = ((u8*)(new_packet)) + sizeof(funk2_packet_header_t) + temp_packet.header.payload_length;
	if (end_of_packet_packet_bytes[0] != funk2_end_of_packet_byte0 ||
	    end_of_packet_packet_bytes[1] != funk2_end_of_packet_byte1) {
	  f2__free(to_ptr(new_packet)); new_packet = NULL;
	  *invalid_packet_found = boolean__true;
	} else {
	  *peek_byte_num = sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2;
	  valid_packet_found = boolean__true;
	}
      }
    }
  }
  if (! valid_packet_found) {
    if (socket->disconnected) {
      *invalid_packet_found = boolean__true;
    }
    return NULL;
  }
  return new_packet;
}

funk2_packet_t* funk2_packet__recv_new_valid_from_buffered_socket(buffered_socket_t* socket) {
  u32                peek_byte_num = 0;
  boolean_t               invalid_packet_found = boolean__false;
  buffered_socket__flush(socket);  
  funk2_packet_t* recv_packet = funk2_packet__peek_recv_new_from_buffered_socket(socket, &peek_byte_num, &invalid_packet_found);
  if (invalid_packet_found) {
    recv_packet = NULL;
    u8 dump_byte;
    circular_buffer__read_result_t read_result = buffered_socket__recv(socket, &dump_byte, 1); // bye bye
    if (read_result == circular_buffer__read_result__success) {
      status("invalid packet found, so dumping one byte (0x%X).", (int)dump_byte);
    }
  }
  if (recv_packet) {
    // dump peek recv data from buffer on successful read of packet.
    buffered_socket__seek_ahead(socket, peek_byte_num);
    //status("valid packet found!  peek_byte_num=%d.", peek_byte_num);
  }
  return recv_packet;
}

funk2_packet_t* funk2_packet__peek_read_new_from_buffered_file(buffered_file_t* file, u32* peek_byte_num, boolean_t* invalid_packet_found) {
  funk2_packet_t  temp_packet;
  funk2_packet_t* new_packet;
  boolean_t               valid_packet_found = boolean__false;
  *invalid_packet_found = boolean__false;
  *peek_byte_num        = 0;
  if (buffered_file__read_bytes_buffered(file) >= sizeof(funk2_packet_header_t)) {
    buffered_file__peek_read(file, &temp_packet, sizeof(funk2_packet_header_t));
    if (temp_packet.header.start_of_packet_byte != funk2_start_of_packet_byte ||
	temp_packet.header.channel              != funk2_channel_byte) {
      *invalid_packet_found = boolean__true; // should scan one byte ahead
    } else {
      // start magic found
      if (buffered_file__read_bytes_buffered(file) >= sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2) {
	new_packet = (funk2_packet_t*)from_ptr(f2__malloc(sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2));
	buffered_file__peek_read(file, new_packet, sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2);
	u8* end_of_packet_packet_bytes = ((u8*)(new_packet)) + sizeof(funk2_packet_header_t) + temp_packet.header.payload_length;
	if (end_of_packet_packet_bytes[0] != funk2_end_of_packet_byte0 ||
	    end_of_packet_packet_bytes[1] != funk2_end_of_packet_byte1) {
	  f2__free(to_ptr(new_packet)); new_packet = NULL;
	  *invalid_packet_found = boolean__true;
	} else {
	  *peek_byte_num = sizeof(funk2_packet_header_t) + temp_packet.header.payload_length + 2;
	  valid_packet_found = boolean__true;
	}
      }
    }
  }
  if (! valid_packet_found) {
    if (file->end_of_file) {
      *invalid_packet_found = boolean__true;
    }
    return NULL;
  }
  return new_packet;
}

funk2_packet_t* funk2_packet__read_new_valid_from_buffered_file(buffered_file_t* file) {
  u32                peek_byte_num = 0;
  boolean_t          invalid_packet_found = boolean__false;
  buffered_file__flush(file);  
  funk2_packet_t* read_packet = funk2_packet__peek_read_new_from_buffered_file(file, &peek_byte_num, &invalid_packet_found);
  if (invalid_packet_found) {
    read_packet = NULL;
    u8 dump_byte;
    circular_buffer__read_result_t read_result = buffered_file__read(file, &dump_byte, 1); // bye bye
    if (read_result == circular_buffer__read_result__success) {
      status("invalid packet found, so dumping one byte (0x%X).", (int)dump_byte);
    }
  }
  if (read_packet) {
    // dump peek recv data from buffer on successful read of packet.
    buffered_file__seek_ahead(file, peek_byte_num);
  }
  return read_packet;
}

// this function is for funk2d_socket_layer (sleep should be f2__scheduler__yield from funk2 proper.
void socket_rpc_layer__funk2_packet__send_to_socket(funk2_packet_t* packet, buffered_socket_t* socket) {
  circular_buffer__write_result_t result = circular_buffer__write_result__success;
  do {
    if (result != circular_buffer__write_result__success) {
      raw__spin_sleep_yield();
    }
    result = buffered_socket__send(socket, packet, sizeof(funk2_packet_header_t) + packet->header.payload_length);
    if (result == circular_buffer__write_result__not_enough_room) {
      status("socket_rpc_layer__funk2_packet__send_to_socket warning: failed to send entire packet to socket.");
      return;
    }
  } while(result == circular_buffer__write_result__not_enough_room);
  u8 end_packet_bytes[2] = {funk2_end_of_packet_byte0, funk2_end_of_packet_byte1};
  do {
    if (result != circular_buffer__write_result__success) {
      raw__spin_sleep_yield();
    }
    result = buffered_socket__send(socket, end_packet_bytes, 2);
    if (result == circular_buffer__write_result__not_enough_room) {
      status("socket_rpc_layer__funk2_packet__send_to_socket warning: failed to send entire packet to socket.");
      return;
    }
  } while(result == circular_buffer__write_result__not_enough_room);
  //{
  //  int i;
  //  int len = funk2_packet__sizeof(packet);
  //  u8* bytes = (u8*)packet;
  //  for (i = 0; i < len; i++) {
  //    u8 b = bytes[i];
  //    if (b >= 28) {
  //	status("socket_rpc_layer__funk2_packet__send_to_socket: socket_fd=%d bytes[%d]=0x%02X %d '%c'", socket->socket_fd, i, b, b, b);
  //    } else {
  //	status("socket_rpc_layer__funk2_packet__send_to_socket: socket_fd=%d bytes[%d]=0x%02X %d", socket->socket_fd, i, b, b);
  //    }
  //  }
  //}
}

void funk2_packet__send_to_socket(f2ptr cause, funk2_packet_t* packet, buffered_socket_t* socket) {
  circular_buffer__write_result_t result = circular_buffer__write_result__success;
  do {
    if (result != circular_buffer__write_result__success) {
      f2__this__fiber__yield(cause);
    }
    result = buffered_socket__send(socket, packet, sizeof(funk2_packet_header_t) + packet->header.payload_length);
  } while(result == circular_buffer__write_result__not_enough_room);
  u8 end_packet_bytes[2] = {funk2_end_of_packet_byte0, funk2_end_of_packet_byte1};
  do {
    if (result != circular_buffer__write_result__success) {
      f2__this__fiber__yield(cause);
    }
    result = buffered_socket__send(socket, end_packet_bytes, 2);
  } while(result == circular_buffer__write_result__not_enough_room);
  //{
  //  int i;
  //  int len = funk2_packet__sizeof(packet);
  //  u8* bytes = (u8*)packet;
  //  for (i = 0; i < len; i++) {
  //    u8 b = bytes[i];
  //    if (b >= 28) {
  //	status("funk2_packet__send_to_socket: socket_fd=%d bytes[%d]=0x%02X %d '%c'", socket->socket_fd, i, b, b, b);
  //    } else {
  //	status("funk2_packet__send_to_socket: socket_fd=%d bytes[%d]=0x%02X %d", socket->socket_fd, i, b, b);
  //    }
  //  }
  //}
}

void funk2_packet__receive(funk2_node_t* funk2_node, pcs_action_packet_t* packet) {
  switch(packet->action_payload_header.payload_header.type) {
  case funk2_packet_type__pcs_request__system__environment:                         recv_packet__request__system__environment(funk2_node, (pcs_request__system__environment_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__system__environment:                         recv_packet__respond__system__environment(funk2_node, (pcs_respond__system__environment_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2ptype__raw:                                recv_packet__request__f2ptype__raw(funk2_node, (pcs_request__f2ptype__raw_t*)packet);                                                               break;
  case funk2_packet_type__pcs_respond__f2ptype__raw:                                recv_packet__respond__f2ptype__raw(funk2_node, (pcs_respond__f2ptype__raw_t*)packet);                                                               break;
  case funk2_packet_type__pcs_request__f2ptype__cause:                              recv_packet__request__f2ptype__cause(funk2_node, (pcs_request__f2ptype__cause_t*)packet);                                                           break;
  case funk2_packet_type__pcs_respond__f2ptype__cause:                              recv_packet__respond__f2ptype__cause(funk2_node, (pcs_respond__f2ptype__cause_t*)packet);                                                           break;
  case funk2_packet_type__pcs_request__f2ptype__cause__set:                         recv_packet__request__f2ptype__cause__set(funk2_node, (pcs_request__f2ptype__cause__set_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2ptype__cause__set:                         recv_packet__respond__f2ptype__cause__set(funk2_node, (pcs_respond__f2ptype__cause__set_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2ptype__creation_fiber:                     recv_packet__request__f2ptype__creation_fiber(funk2_node, (pcs_request__f2ptype__creation_fiber_t*)packet);                                         break;
  case funk2_packet_type__pcs_respond__f2ptype__creation_fiber:                     recv_packet__respond__f2ptype__creation_fiber(funk2_node, (pcs_respond__f2ptype__creation_fiber_t*)packet);                                         break;
  case funk2_packet_type__pcs_request__f2ptype__creation_fiber__set:                recv_packet__request__f2ptype__creation_fiber__set(funk2_node, (pcs_request__f2ptype__creation_fiber__set_t*)packet);                               break;
  case funk2_packet_type__pcs_respond__f2ptype__creation_fiber__set:                recv_packet__respond__f2ptype__creation_fiber__set(funk2_node, (pcs_respond__f2ptype__creation_fiber__set_t*)packet);                               break;
  case funk2_packet_type__pcs_request__f2integer__new:                              recv_packet__request__f2integer__new(funk2_node, (pcs_request__f2integer__new_t*)packet);                                                           break;
  case funk2_packet_type__pcs_respond__f2integer__new:                              recv_packet__respond__f2integer__new(funk2_node, (pcs_respond__f2integer__new_t*)packet);                                                           break;
  case funk2_packet_type__pcs_request__f2integer__i:                                recv_packet__request__f2integer__i(funk2_node, (pcs_request__f2integer__i_t*)packet);                                                               break;
  case funk2_packet_type__pcs_respond__f2integer__i:                                recv_packet__respond__f2integer__i(funk2_node, (pcs_respond__f2integer__i_t*)packet);                                                               break;
  case funk2_packet_type__pcs_request__f2double__new:                               recv_packet__request__f2double__new(funk2_node, (pcs_request__f2double__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2double__new:                               recv_packet__respond__f2double__new(funk2_node, (pcs_respond__f2double__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2double__d:                                 recv_packet__request__f2double__d(funk2_node, (pcs_request__f2double__d_t*)packet);                                                                 break;
  case funk2_packet_type__pcs_respond__f2double__d:                                 recv_packet__respond__f2double__d(funk2_node, (pcs_respond__f2double__d_t*)packet);                                                                 break;
  case funk2_packet_type__pcs_request__f2float__new:                                recv_packet__request__f2float__new(funk2_node, (pcs_request__f2float__new_t*)packet);                                                               break;
  case funk2_packet_type__pcs_respond__f2float__new:                                recv_packet__respond__f2float__new(funk2_node, (pcs_respond__f2float__new_t*)packet);                                                               break;
  case funk2_packet_type__pcs_request__f2float__f:                                  recv_packet__request__f2float__f(funk2_node, (pcs_request__f2float__f_t*)packet);                                                                   break;
  case funk2_packet_type__pcs_respond__f2float__f:                                  recv_packet__respond__f2float__f(funk2_node, (pcs_respond__f2float__f_t*)packet);                                                                   break;
  case funk2_packet_type__pcs_request__f2pointer__new:                              recv_packet__request__f2pointer__new(funk2_node, (pcs_request__f2pointer__new_t*)packet);                                                           break;
  case funk2_packet_type__pcs_respond__f2pointer__new:                              recv_packet__respond__f2pointer__new(funk2_node, (pcs_respond__f2pointer__new_t*)packet);                                                           break;
  case funk2_packet_type__pcs_request__f2pointer__p:                                recv_packet__request__f2pointer__p(funk2_node, (pcs_request__f2pointer__p_t*)packet);                                                               break;
  case funk2_packet_type__pcs_respond__f2pointer__p:                                recv_packet__respond__f2pointer__p(funk2_node, (pcs_respond__f2pointer__p_t*)packet);                                                               break;
  case funk2_packet_type__pcs_request__f2scheduler_cmutex__new:                     recv_packet__request__f2scheduler_cmutex__new(funk2_node, (pcs_request__f2scheduler_cmutex__new_t*)packet);                                         break;
  case funk2_packet_type__pcs_respond__f2scheduler_cmutex__new:                     recv_packet__respond__f2scheduler_cmutex__new(funk2_node, (pcs_respond__f2scheduler_cmutex__new_t*)packet);                                         break;
  case funk2_packet_type__pcs_request__f2scheduler_cmutex__is_locked:               recv_packet__request__f2scheduler_cmutex__is_locked(funk2_node, (pcs_request__f2scheduler_cmutex__is_locked_t*)packet);                             break;
  case funk2_packet_type__pcs_respond__f2scheduler_cmutex__is_locked:               recv_packet__respond__f2scheduler_cmutex__is_locked(funk2_node, (pcs_respond__f2scheduler_cmutex__is_locked_t*)packet);                             break;
  case funk2_packet_type__pcs_request__f2scheduler_cmutex__lock:                    recv_packet__request__f2scheduler_cmutex__lock(funk2_node, (pcs_request__f2scheduler_cmutex__lock_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2scheduler_cmutex__lock:                    recv_packet__respond__f2scheduler_cmutex__lock(funk2_node, (pcs_respond__f2scheduler_cmutex__lock_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2scheduler_cmutex__unlock:                  recv_packet__request__f2scheduler_cmutex__unlock(funk2_node, (pcs_request__f2scheduler_cmutex__unlock_t*)packet);                                   break;
  case funk2_packet_type__pcs_respond__f2scheduler_cmutex__unlock:                  recv_packet__respond__f2scheduler_cmutex__unlock(funk2_node, (pcs_respond__f2scheduler_cmutex__unlock_t*)packet);                                   break;
  case funk2_packet_type__pcs_request__f2scheduler_cmutex__trylock:                 recv_packet__request__f2scheduler_cmutex__trylock(funk2_node, (pcs_request__f2scheduler_cmutex__trylock_t*)packet);                                 break;
  case funk2_packet_type__pcs_respond__f2scheduler_cmutex__trylock:                 recv_packet__respond__f2scheduler_cmutex__trylock(funk2_node, (pcs_respond__f2scheduler_cmutex__trylock_t*)packet);                                 break;
  case funk2_packet_type__pcs_request__f2cmutex__new:                               recv_packet__request__f2cmutex__new(funk2_node, (pcs_request__f2cmutex__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2cmutex__new:                               recv_packet__respond__f2cmutex__new(funk2_node, (pcs_respond__f2cmutex__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2cmutex__is_locked:                         recv_packet__request__f2cmutex__is_locked(funk2_node, (pcs_request__f2cmutex__is_locked_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2cmutex__is_locked:                         recv_packet__respond__f2cmutex__is_locked(funk2_node, (pcs_respond__f2cmutex__is_locked_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2cmutex__lock:                              recv_packet__request__f2cmutex__lock(funk2_node, (pcs_request__f2cmutex__lock_t*)packet);                                                           break;
  case funk2_packet_type__pcs_respond__f2cmutex__lock:                              recv_packet__respond__f2cmutex__lock(funk2_node, (pcs_respond__f2cmutex__lock_t*)packet);                                                           break;
  case funk2_packet_type__pcs_request__f2cmutex__unlock:                            recv_packet__request__f2cmutex__unlock(funk2_node, (pcs_request__f2cmutex__unlock_t*)packet);                                                       break;
  case funk2_packet_type__pcs_respond__f2cmutex__unlock:                            recv_packet__respond__f2cmutex__unlock(funk2_node, (pcs_respond__f2cmutex__unlock_t*)packet);                                                       break;
  case funk2_packet_type__pcs_request__f2cmutex__trylock:                           recv_packet__request__f2cmutex__trylock(funk2_node, (pcs_request__f2cmutex__trylock_t*)packet);                                                     break;
  case funk2_packet_type__pcs_respond__f2cmutex__trylock:                           recv_packet__respond__f2cmutex__trylock(funk2_node, (pcs_respond__f2cmutex__trylock_t*)packet);                                                     break;
  case funk2_packet_type__pcs_request__f2creadwritelock__new:                       recv_packet__request__f2creadwritelock__new(funk2_node, (pcs_request__f2creadwritelock__new_t*)packet);                                             break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__new:                       recv_packet__respond__f2creadwritelock__new(funk2_node, (pcs_respond__f2creadwritelock__new_t*)packet);                                             break;
  case funk2_packet_type__pcs_request__f2creadwritelock__is_writelocked:            recv_packet__request__f2creadwritelock__is_writelocked(funk2_node, (pcs_request__f2creadwritelock__is_writelocked_t*)packet);                       break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__is_writelocked:            recv_packet__respond__f2creadwritelock__is_writelocked(funk2_node, (pcs_respond__f2creadwritelock__is_writelocked_t*)packet);                       break;
  case funk2_packet_type__pcs_request__f2creadwritelock__is_readlocked:             recv_packet__request__f2creadwritelock__is_readlocked(funk2_node, (pcs_request__f2creadwritelock__is_readlocked_t*)packet);                         break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__is_readlocked:             recv_packet__respond__f2creadwritelock__is_readlocked(funk2_node, (pcs_respond__f2creadwritelock__is_readlocked_t*)packet);                         break;
  case funk2_packet_type__pcs_request__f2creadwritelock__writelock:                 recv_packet__request__f2creadwritelock__writelock(funk2_node, (pcs_request__f2creadwritelock__writelock_t*)packet);                                 break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__writelock:                 recv_packet__respond__f2creadwritelock__writelock(funk2_node, (pcs_respond__f2creadwritelock__writelock_t*)packet);                                 break;
  case funk2_packet_type__pcs_request__f2creadwritelock__readlock:                  recv_packet__request__f2creadwritelock__readlock(funk2_node, (pcs_request__f2creadwritelock__readlock_t*)packet);                                   break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__readlock:                  recv_packet__respond__f2creadwritelock__readlock(funk2_node, (pcs_respond__f2creadwritelock__readlock_t*)packet);                                   break;
  case funk2_packet_type__pcs_request__f2creadwritelock__unlock:                    recv_packet__request__f2creadwritelock__unlock(funk2_node, (pcs_request__f2creadwritelock__unlock_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__unlock:                    recv_packet__respond__f2creadwritelock__unlock(funk2_node, (pcs_respond__f2creadwritelock__unlock_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2creadwritelock__trywritelock:              recv_packet__request__f2creadwritelock__trywritelock(funk2_node, (pcs_request__f2creadwritelock__trywritelock_t*)packet);                           break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__trywritelock:              recv_packet__respond__f2creadwritelock__trywritelock(funk2_node, (pcs_respond__f2creadwritelock__trywritelock_t*)packet);                           break;
  case funk2_packet_type__pcs_request__f2creadwritelock__tryreadlock:               recv_packet__request__f2creadwritelock__tryreadlock(funk2_node, (pcs_request__f2creadwritelock__tryreadlock_t*)packet);                             break;
  case funk2_packet_type__pcs_respond__f2creadwritelock__tryreadlock:               recv_packet__respond__f2creadwritelock__tryreadlock(funk2_node, (pcs_respond__f2creadwritelock__tryreadlock_t*)packet);                             break;
  case funk2_packet_type__pcs_request__f2char__new:                                 recv_packet__request__f2char__new(funk2_node, (pcs_request__f2char__new_t*)packet);                                                                 break;
  case funk2_packet_type__pcs_respond__f2char__new:                                 recv_packet__respond__f2char__new(funk2_node, (pcs_respond__f2char__new_t*)packet);                                                                 break;
  case funk2_packet_type__pcs_request__f2char__ch:                                  recv_packet__request__f2char__ch(funk2_node, (pcs_request__f2char__ch_t*)packet);                                                                   break;
  case funk2_packet_type__pcs_respond__f2char__ch:                                  recv_packet__respond__f2char__ch(funk2_node, (pcs_respond__f2char__ch_t*)packet);                                                                   break;
  case funk2_packet_type__pcs_request__f2string__new:                               recv_packet__request__f2string__new(funk2_node, (pcs_request__f2string__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2string__new:                               recv_packet__respond__f2string__new(funk2_node, (pcs_respond__f2string__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2string__length:                            recv_packet__request__f2string__length(funk2_node, (pcs_request__f2string__length_t*)packet);                                                       break;
  case funk2_packet_type__pcs_respond__f2string__length:                            recv_packet__respond__f2string__length(funk2_node, (pcs_respond__f2string__length_t*)packet);                                                       break;
  case funk2_packet_type__pcs_request__f2string__elt:                               recv_packet__request__f2string__elt(funk2_node, (pcs_request__f2string__elt_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2string__elt:                               recv_packet__respond__f2string__elt(funk2_node, (pcs_respond__f2string__elt_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2string__str_copy:                          recv_packet__request__f2string__str_copy(funk2_node, (pcs_request__f2string__str_copy_t*)packet);                                                   break;
  case funk2_packet_type__pcs_respond__f2string__str_copy:                          recv_packet__respond__f2string__str_copy(funk2_node, (pcs_respond__f2string__str_copy_t*)packet);                                                   break;
  case funk2_packet_type__pcs_request__f2string__eq_hash_value:                     recv_packet__request__f2string__eq_hash_value(funk2_node, (pcs_request__f2string__eq_hash_value_t*)packet);                                         break;
  case funk2_packet_type__pcs_respond__f2string__eq_hash_value:                     recv_packet__respond__f2string__eq_hash_value(funk2_node, (pcs_respond__f2string__eq_hash_value_t*)packet);                                         break;
  case funk2_packet_type__pcs_request__f2symbol__new:                               recv_packet__request__f2symbol__new(funk2_node, (pcs_request__f2symbol__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2symbol__new:                               recv_packet__respond__f2symbol__new(funk2_node, (pcs_respond__f2symbol__new_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2symbol__length:                            recv_packet__request__f2symbol__length(funk2_node, (pcs_request__f2symbol__length_t*)packet);                                                       break;
  case funk2_packet_type__pcs_respond__f2symbol__length:                            recv_packet__respond__f2symbol__length(funk2_node, (pcs_respond__f2symbol__length_t*)packet);                                                       break;
  case funk2_packet_type__pcs_request__f2symbol__eq_hash_value:                     recv_packet__request__f2symbol__eq_hash_value(funk2_node, (pcs_request__f2symbol__eq_hash_value_t*)packet);                                         break;
  case funk2_packet_type__pcs_respond__f2symbol__eq_hash_value:                     recv_packet__respond__f2symbol__eq_hash_value(funk2_node, (pcs_respond__f2symbol__eq_hash_value_t*)packet);                                         break;
  case funk2_packet_type__pcs_request__f2symbol__elt:                               recv_packet__request__f2symbol__elt(funk2_node, (pcs_request__f2symbol__elt_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2symbol__elt:                               recv_packet__respond__f2symbol__elt(funk2_node, (pcs_respond__f2symbol__elt_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2symbol__str_copy:                          recv_packet__request__f2symbol__str_copy(funk2_node, (pcs_request__f2symbol__str_copy_t*)packet);                                                   break;
  case funk2_packet_type__pcs_respond__f2symbol__str_copy:                          recv_packet__respond__f2symbol__str_copy(funk2_node, (pcs_respond__f2symbol__str_copy_t*)packet);                                                   break;
  case funk2_packet_type__pcs_request__f2chunk__new:                                recv_packet__request__f2chunk__new(funk2_node, (pcs_request__f2chunk__new_t*)packet);                                                               break;
  case funk2_packet_type__pcs_respond__f2chunk__new:                                recv_packet__respond__f2chunk__new(funk2_node, (pcs_respond__f2chunk__new_t*)packet);                                                               break;
  case funk2_packet_type__pcs_request__f2chunk__new_copy:                           recv_packet__request__f2chunk__new_copy(funk2_node, (pcs_request__f2chunk__new_copy_t*)packet);                                                     break;
  case funk2_packet_type__pcs_respond__f2chunk__new_copy:                           recv_packet__respond__f2chunk__new_copy(funk2_node, (pcs_respond__f2chunk__new_copy_t*)packet);                                                     break;
  case funk2_packet_type__pcs_request__f2chunk__length:                             recv_packet__request__f2chunk__length(funk2_node, (pcs_request__f2chunk__length_t*)packet);                                                         break;
  case funk2_packet_type__pcs_respond__f2chunk__length:                             recv_packet__respond__f2chunk__length(funk2_node, (pcs_respond__f2chunk__length_t*)packet);                                                         break;
  case funk2_packet_type__pcs_request__f2chunk__str_copy:                           recv_packet__request__f2chunk__str_copy(funk2_node, (pcs_request__f2chunk__str_copy_t*)packet);                                                     break;
  case funk2_packet_type__pcs_respond__f2chunk__str_copy:                           recv_packet__respond__f2chunk__str_copy(funk2_node, (pcs_respond__f2chunk__str_copy_t*)packet);                                                     break;
  case funk2_packet_type__pcs_request__f2chunk__bit8__elt:                          recv_packet__request__f2chunk__bit8__elt(funk2_node, (pcs_request__f2chunk__bit8__elt_t*)packet);                                                   break;
  case funk2_packet_type__pcs_respond__f2chunk__bit8__elt:                          recv_packet__respond__f2chunk__bit8__elt(funk2_node, (pcs_respond__f2chunk__bit8__elt_t*)packet);                                                   break;
  case funk2_packet_type__pcs_request__f2chunk__bit8__elt__set:                     recv_packet__request__f2chunk__bit8__elt__set(funk2_node, (pcs_request__f2chunk__bit8__elt__set_t*)packet);                                         break;
  case funk2_packet_type__pcs_respond__f2chunk__bit8__elt__set:                     recv_packet__respond__f2chunk__bit8__elt__set(funk2_node, (pcs_respond__f2chunk__bit8__elt__set_t*)packet);                                         break;
  case funk2_packet_type__pcs_request__f2chunk__bit16__elt:                         recv_packet__request__f2chunk__bit16__elt(funk2_node, (pcs_request__f2chunk__bit16__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2chunk__bit16__elt:                         recv_packet__respond__f2chunk__bit16__elt(funk2_node, (pcs_respond__f2chunk__bit16__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2chunk__bit16__elt__set:                    recv_packet__request__f2chunk__bit16__elt__set(funk2_node, (pcs_request__f2chunk__bit16__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2chunk__bit16__elt__set:                    recv_packet__respond__f2chunk__bit16__elt__set(funk2_node, (pcs_respond__f2chunk__bit16__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2chunk__bit32__elt:                         recv_packet__request__f2chunk__bit32__elt(funk2_node, (pcs_request__f2chunk__bit32__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2chunk__bit32__elt:                         recv_packet__respond__f2chunk__bit32__elt(funk2_node, (pcs_respond__f2chunk__bit32__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2chunk__bit32__elt__set:                    recv_packet__request__f2chunk__bit32__elt__set(funk2_node, (pcs_request__f2chunk__bit32__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2chunk__bit32__elt__set:                    recv_packet__respond__f2chunk__bit32__elt__set(funk2_node, (pcs_respond__f2chunk__bit32__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2chunk__bit64__elt:                         recv_packet__request__f2chunk__bit64__elt(funk2_node, (pcs_request__f2chunk__bit64__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2chunk__bit64__elt:                         recv_packet__respond__f2chunk__bit64__elt(funk2_node, (pcs_respond__f2chunk__bit64__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2chunk__bit64__elt__set:                    recv_packet__request__f2chunk__bit64__elt__set(funk2_node, (pcs_request__f2chunk__bit64__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2chunk__bit64__elt__set:                    recv_packet__respond__f2chunk__bit64__elt__set(funk2_node, (pcs_respond__f2chunk__bit64__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2chunk__cfunk_jump:                         recv_packet__request__f2chunk__cfunk_jump(funk2_node, (pcs_request__f2chunk__cfunk_jump_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2chunk__cfunk_jump:                         recv_packet__respond__f2chunk__cfunk_jump(funk2_node, (pcs_respond__f2chunk__cfunk_jump_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2chunk__bytecode_jump:                      recv_packet__request__f2chunk__bytecode_jump(funk2_node, (pcs_request__f2chunk__bytecode_jump_t*)packet);                                           break;
  case funk2_packet_type__pcs_respond__f2chunk__bytecode_jump:                      recv_packet__respond__f2chunk__bytecode_jump(funk2_node, (pcs_respond__f2chunk__bytecode_jump_t*)packet);                                           break;
  case funk2_packet_type__pcs_request__f2chunk__send:                               recv_packet__request__f2chunk__send(funk2_node, (pcs_request__f2chunk__send_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2chunk__send:                               recv_packet__respond__f2chunk__send(funk2_node, (pcs_respond__f2chunk__send_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2chunk__recv:                               recv_packet__request__f2chunk__recv(funk2_node, (pcs_request__f2chunk__recv_t*)packet);                                                             break;
  case funk2_packet_type__pcs_respond__f2chunk__recv:                               recv_packet__respond__f2chunk__recv(funk2_node, (pcs_respond__f2chunk__recv_t*)packet);                                                             break;
  case funk2_packet_type__pcs_request__f2simple_array__new:                         recv_packet__request__f2simple_array__new(funk2_node, (pcs_request__f2simple_array__new_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2simple_array__new:                         recv_packet__respond__f2simple_array__new(funk2_node, (pcs_respond__f2simple_array__new_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2simple_array__new_copy:                    recv_packet__request__f2simple_array__new_copy(funk2_node, (pcs_request__f2simple_array__new_copy_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2simple_array__new_copy:                    recv_packet__respond__f2simple_array__new_copy(funk2_node, (pcs_respond__f2simple_array__new_copy_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2simple_array__immutable:                   recv_packet__request__f2simple_array__immutable(funk2_node, (pcs_request__f2simple_array__immutable_t*)packet);                                     break;
  case funk2_packet_type__pcs_respond__f2simple_array__immutable:                   recv_packet__respond__f2simple_array__immutable(funk2_node, (pcs_respond__f2simple_array__immutable_t*)packet);                                     break;
  case funk2_packet_type__pcs_request__f2simple_array__immutable__set:              recv_packet__request__f2simple_array__immutable__set(funk2_node, (pcs_request__f2simple_array__immutable__set_t*)packet);                           break;
  case funk2_packet_type__pcs_respond__f2simple_array__immutable__set:              recv_packet__respond__f2simple_array__immutable__set(funk2_node, (pcs_respond__f2simple_array__immutable__set_t*)packet);                           break;
  case funk2_packet_type__pcs_request__f2simple_array__length:                      recv_packet__request__f2simple_array__length(funk2_node, (pcs_request__f2simple_array__length_t*)packet);                                           break;
  case funk2_packet_type__pcs_respond__f2simple_array__length:                      recv_packet__respond__f2simple_array__length(funk2_node, (pcs_respond__f2simple_array__length_t*)packet);                                           break;
  case funk2_packet_type__pcs_request__f2simple_array__elt:                         recv_packet__request__f2simple_array__elt(funk2_node, (pcs_request__f2simple_array__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2simple_array__elt:                         recv_packet__respond__f2simple_array__elt(funk2_node, (pcs_respond__f2simple_array__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2simple_array__elt__set:                    recv_packet__request__f2simple_array__elt__set(funk2_node, (pcs_request__f2simple_array__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2simple_array__elt__set:                    recv_packet__respond__f2simple_array__elt__set(funk2_node, (pcs_respond__f2simple_array__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2traced_array__new:                         recv_packet__request__f2traced_array__new(funk2_node, (pcs_request__f2traced_array__new_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2traced_array__new:                         recv_packet__respond__f2traced_array__new(funk2_node, (pcs_respond__f2traced_array__new_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2traced_array__new_copy:                    recv_packet__request__f2traced_array__new_copy(funk2_node, (pcs_request__f2traced_array__new_copy_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2traced_array__new_copy:                    recv_packet__respond__f2traced_array__new_copy(funk2_node, (pcs_respond__f2traced_array__new_copy_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2traced_array__immutable:                   recv_packet__request__f2traced_array__immutable(funk2_node, (pcs_request__f2traced_array__immutable_t*)packet);                                     break;
  case funk2_packet_type__pcs_respond__f2traced_array__immutable:                   recv_packet__respond__f2traced_array__immutable(funk2_node, (pcs_respond__f2traced_array__immutable_t*)packet);                                     break;
  case funk2_packet_type__pcs_request__f2traced_array__immutable__set:              recv_packet__request__f2traced_array__immutable__set(funk2_node, (pcs_request__f2traced_array__immutable__set_t*)packet);                           break;
  case funk2_packet_type__pcs_respond__f2traced_array__immutable__set:              recv_packet__respond__f2traced_array__immutable__set(funk2_node, (pcs_respond__f2traced_array__immutable__set_t*)packet);                           break;
  case funk2_packet_type__pcs_request__f2traced_array__length:                      recv_packet__request__f2traced_array__length(funk2_node, (pcs_request__f2traced_array__length_t*)packet);                                           break;
  case funk2_packet_type__pcs_respond__f2traced_array__length:                      recv_packet__respond__f2traced_array__length(funk2_node, (pcs_respond__f2traced_array__length_t*)packet);                                           break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__trace_depth:            recv_packet__request__f2traced_array__elt__trace_depth(funk2_node, (pcs_request__f2traced_array__elt__trace_depth_t*)packet);                       break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__trace_depth:            recv_packet__respond__f2traced_array__elt__trace_depth(funk2_node, (pcs_respond__f2traced_array__elt__trace_depth_t*)packet);                       break;
  case funk2_packet_type__pcs_request__f2traced_array__elt:                         recv_packet__request__f2traced_array__elt(funk2_node, (pcs_request__f2traced_array__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt:                         recv_packet__respond__f2traced_array__elt(funk2_node, (pcs_respond__f2traced_array__elt_t*)packet);                                                 break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__set__trace_depth:       recv_packet__request__f2traced_array__elt__set__trace_depth(funk2_node, (pcs_request__f2traced_array__elt__set__trace_depth_t*)packet);             break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__set__trace_depth:       recv_packet__respond__f2traced_array__elt__set__trace_depth(funk2_node, (pcs_respond__f2traced_array__elt__set__trace_depth_t*)packet);             break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__set:                    recv_packet__request__f2traced_array__elt__set(funk2_node, (pcs_request__f2traced_array__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__set:                    recv_packet__respond__f2traced_array__elt__set(funk2_node, (pcs_respond__f2traced_array__elt__set_t*)packet);                                       break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on:             recv_packet__request__f2traced_array__elt__tracing_on(funk2_node, (pcs_request__f2traced_array__elt__tracing_on_t*)packet);                         break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__tracing_on:             recv_packet__respond__f2traced_array__elt__tracing_on(funk2_node, (pcs_respond__f2traced_array__elt__tracing_on_t*)packet);                         break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on__set:        recv_packet__request__f2traced_array__elt__tracing_on__set(funk2_node, (pcs_request__f2traced_array__elt__tracing_on__set_t*)packet);               break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__tracing_on__set:        recv_packet__respond__f2traced_array__elt__tracing_on__set(funk2_node, (pcs_respond__f2traced_array__elt__tracing_on__set_t*)packet);               break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__trace:                  recv_packet__request__f2traced_array__elt__trace(funk2_node, (pcs_request__f2traced_array__elt__trace_t*)packet);                                   break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__trace:                  recv_packet__respond__f2traced_array__elt__trace(funk2_node, (pcs_respond__f2traced_array__elt__trace_t*)packet);                                   break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__trace__set:             recv_packet__request__f2traced_array__elt__trace__set(funk2_node, (pcs_request__f2traced_array__elt__trace__set_t*)packet);                         break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__trace__set:             recv_packet__respond__f2traced_array__elt__trace__set(funk2_node, (pcs_respond__f2traced_array__elt__trace__set_t*)packet);                         break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame:      recv_packet__request__f2traced_array__elt__imagination_frame(funk2_node, (pcs_request__f2traced_array__elt__imagination_frame_t*)packet);           break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__imagination_frame:      recv_packet__respond__f2traced_array__elt__imagination_frame(funk2_node, (pcs_respond__f2traced_array__elt__imagination_frame_t*)packet);           break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame__set: recv_packet__request__f2traced_array__elt__imagination_frame__set(funk2_node, (pcs_request__f2traced_array__elt__imagination_frame__set_t*)packet); break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__imagination_frame__set: recv_packet__respond__f2traced_array__elt__imagination_frame__set(funk2_node, (pcs_respond__f2traced_array__elt__imagination_frame__set_t*)packet); break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__mutate_funks:           recv_packet__request__f2traced_array__elt__mutate_funks(funk2_node, (pcs_request__f2traced_array__elt__mutate_funks_t*)packet);                     break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__mutate_funks:           recv_packet__respond__f2traced_array__elt__mutate_funks(funk2_node, (pcs_respond__f2traced_array__elt__mutate_funks_t*)packet);                     break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__mutate_funks__set:      recv_packet__request__f2traced_array__elt__mutate_funks__set(funk2_node, (pcs_request__f2traced_array__elt__mutate_funks__set_t*)packet);           break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__mutate_funks__set:      recv_packet__respond__f2traced_array__elt__mutate_funks__set(funk2_node, (pcs_respond__f2traced_array__elt__mutate_funks__set_t*)packet);           break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__read_funks:             recv_packet__request__f2traced_array__elt__read_funks(funk2_node, (pcs_request__f2traced_array__elt__read_funks_t*)packet);                         break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__read_funks:             recv_packet__respond__f2traced_array__elt__read_funks(funk2_node, (pcs_respond__f2traced_array__elt__read_funks_t*)packet);                         break;
  case funk2_packet_type__pcs_request__f2traced_array__elt__read_funks__set:        recv_packet__request__f2traced_array__elt__read_funks__set(funk2_node, (pcs_request__f2traced_array__elt__read_funks__set_t*)packet);               break;
  case funk2_packet_type__pcs_respond__f2traced_array__elt__read_funks__set:        recv_packet__respond__f2traced_array__elt__read_funks__set(funk2_node, (pcs_respond__f2traced_array__elt__read_funks__set_t*)packet);               break;
  case funk2_packet_type__pcs_request__f2larva__new:                                recv_packet__request__f2larva__new(funk2_node, (pcs_request__f2larva__new_t*)packet);                                                               break;
  case funk2_packet_type__pcs_respond__f2larva__new:                                recv_packet__respond__f2larva__new(funk2_node, (pcs_respond__f2larva__new_t*)packet);                                                               break;
  case funk2_packet_type__pcs_request__f2larva__larva_type:                         recv_packet__request__f2larva__larva_type(funk2_node, (pcs_request__f2larva__larva_type_t*)packet);                                                 break;
  case funk2_packet_type__pcs_respond__f2larva__larva_type:                         recv_packet__respond__f2larva__larva_type(funk2_node, (pcs_respond__f2larva__larva_type_t*)packet);                                                 break;
  default: error(nil, "packet is not action_packet");
  }
}



// ******************************************************
// *                                                    *
// ******************************************************
// 
// in general, this is the execution protocol for funk2 RPCs:
//
// 
//   funk2d_socket_layer execution only
// 
//     void recv__request(pcs_request__system__environment_t* packet) {
// 
//     void send__respond(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ...) {
// 
//     void recv__respond(pcs_respond__system__environment_t* packet, ...) {
// 
// 
//   funk2_proper execution only
// 
//     void send__request(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ...) {
// 
//     node_id_t funk2_node(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ...) {
// 


#define packet_status(str, rest...) status("packet_status " str, ## rest)
//#define packet_status(str, rest...)

// ******************************************************
// * 
// * 

// funk2 execution only
void send_packet__request__register_peer(f2ptr cause, funk2_node_t* funk2_node, node_id_t node_id, u8* ip_addr, u16 port_num) {
  packet_status("send_packet__request__register_peer: executing.");
  pcs_request__register_peer_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.payload_header.type = funk2_packet_type__pcs_request__register_peer;
  packet.payload.node_id             = node_id;
  packet.payload.ip_addr[0]          = ip_addr[0];
  packet.payload.ip_addr[1]          = ip_addr[1];
  packet.payload.ip_addr[2]          = ip_addr[2];
  packet.payload.ip_addr[3]          = ip_addr[3];
  packet.payload.port_num            = port_num;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

// rpc_socket_layer execution only
void rpc_socket_layer__send_packet__request__register_peer(funk2_node_t* funk2_node, node_id_t node_id, u8* ip_addr, u16 port_num) {
  packet_status("rpc_socket_layer__send_packet__request__register_peer: executing.");
  pcs_request__register_peer_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.payload_header.type = funk2_packet_type__pcs_request__register_peer;
  packet.payload.node_id             = node_id;
  packet.payload.ip_addr[0]          = ip_addr[0];
  packet.payload.ip_addr[1]          = ip_addr[1];
  packet.payload.ip_addr[2]          = ip_addr[2];
  packet.payload.ip_addr[3]          = ip_addr[3];
  packet.payload.port_num            = port_num;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}


// ******************************************************
// * 
// * 

// socket_rpc_layer execution only
void send_packet__request__remote_computer_id_to_node_id(funk2_node_t* funk2_node, computer_id_t computer_id) {
  packet_status("send_packet__request__remote_computer_id_to_node_id: executing.");
  pcs_request__remote_computer_id_to_node_id_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.payload_header.type = funk2_packet_type__pcs_request__remote_computer_id_to_node_id;
  packet.payload.computer_id         = computer_id;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

// socket_rpc_layer execution only
void send_packet__respond__remote_computer_id_to_node_id(funk2_node_t* funk2_node, node_id_t node_id, computer_id_t computer_id) {
  packet_status("send_packet__respond__remote_computer_id_to_node_id: executing.");
  pcs_respond__remote_computer_id_to_node_id_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.payload_header.type = funk2_packet_type__pcs_respond__remote_computer_id_to_node_id;
  packet.payload.node_id             = node_id;
  packet.payload.computer_id         = computer_id;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}


// ******************************************************
// * 
// * 

// funk2 execution only
void send_packet__request__system__environment(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__request__system__environment: executing.");
  pcs_request__system__environment_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__system__environment;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet_status("send_packet__request__system__environment: fiber=" f2ptr__fstr, this_fiber);
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

// funk2d execution only
void recv_packet__request__system__environment(funk2_node_t* funk2_node, pcs_request__system__environment_t* packet) {
  packet_status("recv_packet__request__system__environment: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  packet_status("recv_packet__request__system__environment: fiber=" f2ptr__fstr, fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr environment = pfunk2__system__environment(rf2_to_lf2(cause));
  send_packet__respond__system__environment(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, environment);
}

// funk2d execution only
void send_packet__respond__system__environment(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr environment) {
  packet_status("send_packet__respond__system__environment: executing.");
  pcs_respond__system__environment_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__system__environment;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.environment                               = environment;
  packet_status("send_packet__respond__system__environment: fiber=" f2ptr__fstr, this_fiber);
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

// funk2d execution only
void recv_packet__respond__system__environment(funk2_node_t* funk2_node, pcs_respond__system__environment_t* packet) {
  packet_status("recv_packet__respond__system__environment: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  packet_status("recv_packet__respond__system__environment: fiber=" f2ptr__fstr, fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

// funk2 execution only
f2ptr funk2_node__system__environment(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  send_packet__request__system__environment(funk2_node, this_fiber, cause);
  pcs_respond__system__environment_t* packet = (pcs_respond__system__environment_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr environment = rf2_to_lf2(packet->payload.environment);
  packet_status("funk2_node__system__environment: packet->payload.environment=" f2ptr__fstr "environment=" f2ptr__fstr, packet->payload.environment, environment);
  f2__free(to_ptr(packet));
  return environment;
}

f2ptr f2system__environment(f2ptr cause, node_id_t node_id) {
  computer_id_t computer_id = funk2_node_handler__lookup_computer_id_from_node_id(&(__funk2.node_handler), node_id);
  if (computer_id == ((computer_id_t)-1)) {
    printf ("couldn't find node_id");
    return nil;
  }
  if (computer_id == 0) {
    return pfunk2__system__environment(cause);
  } else {
    f2ptr         fiber      = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__system__environment(funk2_node, fiber, cause);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2ptype__raw(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2ptype__raw: executing.");
  pcs_request__f2ptype__raw_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2ptype__raw;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2ptype__raw(funk2_node_t* funk2_node, pcs_request__f2ptype__raw_t* packet) {
  packet_status("recv_packet__request__f2ptype__raw: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  ptype_t raw = pfunk2__f2ptype__raw(this, cause);
  send_packet__respond__f2ptype__raw(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, raw);
}

void send_packet__respond__f2ptype__raw(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ptype_t raw) {
  packet_status("send_packet__respond__f2ptype__raw: executing.");
  pcs_respond__f2ptype__raw_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2ptype__raw;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.raw                                       = raw;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2ptype__raw(funk2_node_t* funk2_node, pcs_respond__f2ptype__raw_t* packet) {
  packet_status("recv_packet__respond__f2ptype__raw: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

ptype_t funk2_node__f2ptype__raw(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2ptype__raw(funk2_node, this_fiber, cause, this);
  pcs_respond__f2ptype__raw_t* packet = (pcs_respond__f2ptype__raw_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  ptype_t raw = packet->payload.raw;
  f2__free(to_ptr(packet));
  return raw;
}

ptype_t f2ptype__raw(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2ptype__raw(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2ptype__raw(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2ptype__cause(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2ptype__cause: executing.");
  pcs_request__f2ptype__cause_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2ptype__cause;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2ptype__cause(funk2_node_t* funk2_node, pcs_request__f2ptype__cause_t* packet) {
  packet_status("recv_packet__request__f2ptype__cause: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr f2ptype__cause = pfunk2__f2ptype__cause(this, cause);
  send_packet__respond__f2ptype__cause(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, f2ptype__cause);
}

void send_packet__respond__f2ptype__cause(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr ptype__cause) {
  packet_status("send_packet__respond__f2ptype__cause: executing.");
  pcs_respond__f2ptype__cause_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2ptype__cause;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.ptype__cause                              = ptype__cause;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2ptype__cause(funk2_node_t* funk2_node, pcs_respond__f2ptype__cause_t* packet) {
  packet_status("recv_packet__respond__f2ptype__cause: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2ptype__cause(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2ptype__cause(funk2_node, this_fiber, cause, this);
  pcs_respond__f2ptype__cause_t* packet = (pcs_respond__f2ptype__cause_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr ptype__cause = rf2_to_lf2(packet->payload.ptype__cause);
  f2__free(to_ptr(packet));
  return ptype__cause;
}

f2ptr f2ptype__cause(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2ptype__cause(this, cause);
  } else {
    f2ptr         fiber      = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2ptype__cause(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2ptype__cause__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr value) {
  packet_status("send_packet__request__f2ptype__cause__set: executing.");
  pcs_request__f2ptype__cause__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2ptype__cause__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2ptype__cause__set(funk2_node_t* funk2_node, pcs_request__f2ptype__cause__set_t* packet) {
  packet_status("recv_packet__request__f2ptype__cause__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2ptype__cause__set(this, cause, value);
  send_packet__respond__f2ptype__cause__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2ptype__cause__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2ptype__cause__set: executing.");
  pcs_respond__f2ptype__cause__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2ptype__cause__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2ptype__cause__set(funk2_node_t* funk2_node, pcs_respond__f2ptype__cause__set_t* packet) {
  packet_status("recv_packet__respond__f2ptype__cause__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2ptype__cause__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr value) {
  send_packet__request__f2ptype__cause__set(funk2_node, this_fiber, cause, this, value);
  pcs_respond__f2ptype__cause__set_t* packet = (pcs_respond__f2ptype__cause__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2ptype__cause__set(f2ptr this, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2ptype__cause__set(this, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2ptype__cause__set(funk2_node, fiber, cause, this, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2ptype__creation_fiber(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2ptype__creation_fiber: executing.");
  pcs_request__f2ptype__creation_fiber_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2ptype__creation_fiber;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2ptype__creation_fiber(funk2_node_t* funk2_node, pcs_request__f2ptype__creation_fiber_t* packet) {
  packet_status("recv_packet__request__f2ptype__creation_fiber: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr f2ptype__creation_fiber = pfunk2__f2ptype__creation_fiber(this, cause);
  send_packet__respond__f2ptype__creation_fiber(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, f2ptype__creation_fiber);
}

void send_packet__respond__f2ptype__creation_fiber(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr ptype__creation_fiber) {
  packet_status("send_packet__respond__f2ptype__creation_fiber: executing.");
  pcs_respond__f2ptype__creation_fiber_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2ptype__creation_fiber;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.ptype__creation_fiber                              = ptype__creation_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2ptype__creation_fiber(funk2_node_t* funk2_node, pcs_respond__f2ptype__creation_fiber_t* packet) {
  packet_status("recv_packet__respond__f2ptype__creation_fiber: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2ptype__creation_fiber(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2ptype__creation_fiber(funk2_node, this_fiber, cause, this);
  pcs_respond__f2ptype__creation_fiber_t* packet = (pcs_respond__f2ptype__creation_fiber_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr ptype__creation_fiber = rf2_to_lf2(packet->payload.ptype__creation_fiber);
  f2__free(to_ptr(packet));
  return ptype__creation_fiber;
}

f2ptr f2ptype__creation_fiber(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2ptype__creation_fiber(this, cause);
  } else {
    f2ptr         fiber      = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2ptype__creation_fiber(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2ptype__creation_fiber__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr value) {
  packet_status("send_packet__request__f2ptype__creation_fiber__set: executing.");
  pcs_request__f2ptype__creation_fiber__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2ptype__creation_fiber__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2ptype__creation_fiber__set(funk2_node_t* funk2_node, pcs_request__f2ptype__creation_fiber__set_t* packet) {
  packet_status("recv_packet__request__f2ptype__creation_fiber__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2ptype__creation_fiber__set(this, cause, value);
  send_packet__respond__f2ptype__creation_fiber__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2ptype__creation_fiber__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2ptype__creation_fiber__set: executing.");
  pcs_respond__f2ptype__creation_fiber__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2ptype__creation_fiber__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2ptype__creation_fiber__set(funk2_node_t* funk2_node, pcs_respond__f2ptype__creation_fiber__set_t* packet) {
  packet_status("recv_packet__respond__f2ptype__creation_fiber__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2ptype__creation_fiber__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr value) {
  send_packet__request__f2ptype__creation_fiber__set(funk2_node, this_fiber, cause, this, value);
  pcs_respond__f2ptype__creation_fiber__set_t* packet = (pcs_respond__f2ptype__creation_fiber__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2ptype__creation_fiber__set(f2ptr this, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2ptype__creation_fiber__set(this, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2ptype__creation_fiber__set(funk2_node, fiber, cause, this, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2integer__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 i) {
  packet_status("send_packet__request__f2integer__new: executing.");
  pcs_request__f2integer__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2integer__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.i                                         = i;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2integer__new(funk2_node_t* funk2_node, pcs_request__f2integer__new_t* packet) {
  packet_status("recv_packet__request__f2integer__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2integer__new(cause, packet->payload.i);
  send_packet__respond__f2integer__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2integer__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2integer__new: executing.");
  pcs_respond__f2integer__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2integer__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2integer__new(funk2_node_t* funk2_node, pcs_respond__f2integer__new_t* packet) {
  packet_status("recv_packet__respond__f2integer__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2integer__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 i) {
  send_packet__request__f2integer__new(funk2_node, this_fiber, cause, i);
  pcs_respond__f2integer__new_t* packet = (pcs_respond__f2integer__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2integer__new(f2ptr cause, u64 i) {
  return pfunk2__f2integer__new(cause, i);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2integer__i(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2integer__i: executing.");
  pcs_request__f2integer__i_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2integer__i;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2integer__i(funk2_node_t* funk2_node, pcs_request__f2integer__i_t* packet) {
  packet_status("recv_packet__request__f2integer__i: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int i = pfunk2__f2integer__i(this, cause);
  send_packet__respond__f2integer__i(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, i);
}

void send_packet__respond__f2integer__i(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, s64 i) {
  packet_status("send_packet__respond__f2integer__i: executing.");
  pcs_respond__f2integer__i_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2integer__i;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.i                                         = i;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2integer__i(funk2_node_t* funk2_node, pcs_respond__f2integer__i_t* packet) {
  packet_status("recv_packet__respond__f2integer__i: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

s64 funk2_node__f2integer__i(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2integer__i(funk2_node, this_fiber, cause, this);
  pcs_respond__f2integer__i_t* packet = (pcs_respond__f2integer__i_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  s64 i = packet->payload.i;
  f2__free(to_ptr(packet));
  return i;
}

s64 f2integer__i(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2integer__i(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2integer__i(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2double__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, double d) {
  packet_status("send_packet__request__f2double__new: executing.");
  pcs_request__f2double__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2double__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.d                                         = d;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2double__new(funk2_node_t* funk2_node, pcs_request__f2double__new_t* packet) {
  packet_status("recv_packet__request__f2double__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2double__new(cause, packet->payload.d);
  send_packet__respond__f2double__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2double__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2double__new: executing.");
  pcs_respond__f2double__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2double__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2double__new(funk2_node_t* funk2_node, pcs_respond__f2double__new_t* packet) {
  packet_status("recv_packet__respond__f2double__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2double__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, double d) {
  send_packet__request__f2double__new(funk2_node, this_fiber, cause, d);
  pcs_respond__f2double__new_t* packet = (pcs_respond__f2double__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2double__new(f2ptr cause, double d) {
  return pfunk2__f2double__new(cause, d);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2double__d(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2double__d: executing.");
  pcs_request__f2double__d_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2double__d;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2double__d(funk2_node_t* funk2_node, pcs_request__f2double__d_t* packet) {
  packet_status("recv_packet__request__f2double__d: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  double d = pfunk2__f2double__d(this, cause);
  send_packet__respond__f2double__d(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, d);
}

void send_packet__respond__f2double__d(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, double d) {
  packet_status("send_packet__respond__f2double__d: executing.");
  pcs_respond__f2double__d_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2double__d;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.d                                         = d;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2double__d(funk2_node_t* funk2_node, pcs_respond__f2double__d_t* packet) {
  packet_status("recv_packet__respond__f2double__d: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

double funk2_node__f2double__d(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2double__d(funk2_node, this_fiber, cause, this);
  pcs_respond__f2double__d_t* packet = (pcs_respond__f2double__d_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  double d = packet->payload.d;
  f2__free(to_ptr(packet));
  return d;
}

double f2double__d(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2double__d(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2double__d(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2float__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, float f) {
  packet_status("send_packet__request__f2float__new: executing.");
  pcs_request__f2float__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2float__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.f                                         = f;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2float__new(funk2_node_t* funk2_node, pcs_request__f2float__new_t* packet) {
  packet_status("recv_packet__request__f2float__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2float__new(cause, packet->payload.f);
  send_packet__respond__f2float__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2float__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2float__new: executing.");
  pcs_respond__f2float__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2float__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2float__new(funk2_node_t* funk2_node, pcs_respond__f2float__new_t* packet) {
  packet_status("recv_packet__respond__f2float__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2float__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, float f) {
  send_packet__request__f2float__new(funk2_node, this_fiber, cause, f);
  pcs_respond__f2float__new_t* packet = (pcs_respond__f2float__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2float__new(f2ptr cause, float f) {
  return pfunk2__f2float__new(cause, f);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2float__f(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2float__f: executing.");
  pcs_request__f2float__f_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2float__f;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2float__f(funk2_node_t* funk2_node, pcs_request__f2float__f_t* packet) {
  packet_status("recv_packet__request__f2float__f: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  float f = pfunk2__f2float__f(this, cause);
  send_packet__respond__f2float__f(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, f);
}

void send_packet__respond__f2float__f(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, float f) {
  packet_status("send_packet__respond__f2float__f: executing.");
  pcs_respond__f2float__f_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2float__f;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.f                                         = f;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2float__f(funk2_node_t* funk2_node, pcs_respond__f2float__f_t* packet) {
  packet_status("recv_packet__respond__f2float__f: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

float funk2_node__f2float__f(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2float__f(funk2_node, this_fiber, cause, this);
  pcs_respond__f2float__f_t* packet = (pcs_respond__f2float__f_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  float f = packet->payload.f;
  f2__free(to_ptr(packet));
  return f;
}

float f2float__f(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2float__f(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2float__f(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2pointer__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ptr p) {
  packet_status("send_packet__request__f2pointer__new: executing.");
  pcs_request__f2pointer__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2pointer__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.p                                         = p;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2pointer__new(funk2_node_t* funk2_node, pcs_request__f2pointer__new_t* packet) {
  packet_status("recv_packet__request__f2pointer__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2pointer__new(cause, packet->payload.p);
  send_packet__respond__f2pointer__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2pointer__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2pointer__new: executing.");
  pcs_respond__f2pointer__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2pointer__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2pointer__new(funk2_node_t* funk2_node, pcs_respond__f2pointer__new_t* packet) {
  packet_status("recv_packet__respond__f2pointer__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2pointer__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ptr p) {
  send_packet__request__f2pointer__new(funk2_node, this_fiber, cause, p);
  pcs_respond__f2pointer__new_t* packet = (pcs_respond__f2pointer__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2pointer__new(f2ptr cause, ptr p) {
  return pfunk2__f2pointer__new(cause, p);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2pointer__p(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2pointer__p: executing.");
  pcs_request__f2pointer__p_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2pointer__p;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2pointer__p(funk2_node_t* funk2_node, pcs_request__f2pointer__p_t* packet) {
  packet_status("recv_packet__request__f2pointer__p: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  ptr p = pfunk2__f2pointer__p(this, cause);
  send_packet__respond__f2pointer__p(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, p);
}

void send_packet__respond__f2pointer__p(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, ptr p) {
  packet_status("send_packet__respond__f2pointer__p: executing.");
  pcs_respond__f2pointer__p_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2pointer__p;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.p                                         = p;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2pointer__p(funk2_node_t* funk2_node, pcs_respond__f2pointer__p_t* packet) {
  packet_status("recv_packet__respond__f2pointer__p: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

ptr funk2_node__f2pointer__p(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2pointer__p(funk2_node, this_fiber, cause, this);
  pcs_respond__f2pointer__p_t* packet = (pcs_respond__f2pointer__p_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  ptr p = packet->payload.p;
  f2__free(to_ptr(packet));
  return p;
}

ptr f2pointer__p(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2pointer__p(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2pointer__p(funk2_node, fiber, cause, this);
  }
}


// scheduler_cmutex

// ******************************************************
// * 
// * 

void send_packet__request__f2scheduler_cmutex__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__request__f2scheduler_cmutex__new: executing.");
  pcs_request__f2scheduler_cmutex__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2scheduler_cmutex__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2scheduler_cmutex__new(funk2_node_t* funk2_node, pcs_request__f2scheduler_cmutex__new_t* packet) {
  packet_status("recv_packet__request__f2scheduler_cmutex__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2scheduler_cmutex__new(cause);
  send_packet__respond__f2scheduler_cmutex__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2scheduler_cmutex__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2scheduler_cmutex__new: executing.");
  pcs_respond__f2scheduler_cmutex__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2scheduler_cmutex__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2scheduler_cmutex__new(funk2_node_t* funk2_node, pcs_respond__f2scheduler_cmutex__new_t* packet) {
  packet_status("recv_packet__respond__f2scheduler_cmutex__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2scheduler_cmutex__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  send_packet__request__f2scheduler_cmutex__new(funk2_node, this_fiber, cause);
  pcs_respond__f2scheduler_cmutex__new_t* packet = (pcs_respond__f2scheduler_cmutex__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2scheduler_cmutex__new(f2ptr cause) {
  return pfunk2__f2scheduler_cmutex__new(cause);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2scheduler_cmutex__is_locked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2scheduler_cmutex__is_locked: executing.");
  pcs_request__f2scheduler_cmutex__is_locked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2scheduler_cmutex__is_locked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2scheduler_cmutex__is_locked(funk2_node_t* funk2_node, pcs_request__f2scheduler_cmutex__is_locked_t* packet) {
  packet_status("recv_packet__request__f2scheduler_cmutex__is_locked: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  boolean_t is_locked = pfunk2__f2scheduler_cmutex__is_locked(this, cause);
  send_packet__respond__f2scheduler_cmutex__is_locked(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, is_locked);
}

void send_packet__respond__f2scheduler_cmutex__is_locked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, boolean_t is_locked) {
  packet_status("send_packet__respond__f2scheduler_cmutex__is_locked: executing.");
  pcs_respond__f2scheduler_cmutex__is_locked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2scheduler_cmutex__is_locked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.is_locked                                   = is_locked;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2scheduler_cmutex__is_locked(funk2_node_t* funk2_node, pcs_respond__f2scheduler_cmutex__is_locked_t* packet) {
  packet_status("recv_packet__respond__f2scheduler_cmutex__is_locked: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

boolean_t funk2_node__f2scheduler_cmutex__is_locked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2scheduler_cmutex__is_locked(funk2_node, this_fiber, cause, this);
  pcs_respond__f2scheduler_cmutex__is_locked_t* packet = (pcs_respond__f2scheduler_cmutex__is_locked_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  boolean_t is_locked = packet->payload.is_locked;
  f2__free(to_ptr(packet));
  return is_locked;
}

boolean_t f2scheduler_cmutex__is_locked(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2scheduler_cmutex__is_locked(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2scheduler_cmutex__is_locked(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2scheduler_cmutex__lock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2scheduler_cmutex__lock: executing.");
  pcs_request__f2scheduler_cmutex__lock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2scheduler_cmutex__lock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2scheduler_cmutex__lock(funk2_node_t* funk2_node, pcs_request__f2scheduler_cmutex__lock_t* packet) {
  packet_status("recv_packet__request__f2scheduler_cmutex__lock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2scheduler_cmutex__lock(this, cause);
  send_packet__respond__f2scheduler_cmutex__lock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2scheduler_cmutex__lock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2scheduler_cmutex__lock: executing.");
  pcs_respond__f2scheduler_cmutex__lock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2scheduler_cmutex__lock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2scheduler_cmutex__lock(funk2_node_t* funk2_node, pcs_respond__f2scheduler_cmutex__lock_t* packet) {
  packet_status("recv_packet__respond__f2scheduler_cmutex__lock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2scheduler_cmutex__lock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2scheduler_cmutex__lock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2scheduler_cmutex__lock_t* packet = (pcs_respond__f2scheduler_cmutex__lock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2scheduler_cmutex__lock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2scheduler_cmutex__lock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2scheduler_cmutex__lock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2scheduler_cmutex__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2scheduler_cmutex__unlock: executing.");
  pcs_request__f2scheduler_cmutex__unlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2scheduler_cmutex__unlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2scheduler_cmutex__unlock(funk2_node_t* funk2_node, pcs_request__f2scheduler_cmutex__unlock_t* packet) {
  packet_status("recv_packet__request__f2scheduler_cmutex__unlock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2scheduler_cmutex__unlock(this, cause);
  send_packet__respond__f2scheduler_cmutex__unlock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2scheduler_cmutex__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2scheduler_cmutex__unlock: executing.");
  pcs_respond__f2scheduler_cmutex__unlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2scheduler_cmutex__unlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2scheduler_cmutex__unlock(funk2_node_t* funk2_node, pcs_respond__f2scheduler_cmutex__unlock_t* packet) {
  packet_status("recv_packet__respond__f2scheduler_cmutex__unlock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2scheduler_cmutex__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2scheduler_cmutex__unlock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2scheduler_cmutex__unlock_t* packet = (pcs_respond__f2scheduler_cmutex__unlock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2scheduler_cmutex__unlock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2scheduler_cmutex__unlock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2scheduler_cmutex__unlock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2scheduler_cmutex__trylock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2scheduler_cmutex__trylock: executing.");
  pcs_request__f2scheduler_cmutex__trylock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2scheduler_cmutex__trylock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2scheduler_cmutex__trylock(funk2_node_t* funk2_node, pcs_request__f2scheduler_cmutex__trylock_t* packet) {
  packet_status("recv_packet__request__f2scheduler_cmutex__trylock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int trylock = pfunk2__f2scheduler_cmutex__trylock(this, cause);
  send_packet__respond__f2scheduler_cmutex__trylock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, trylock);
}

void send_packet__respond__f2scheduler_cmutex__trylock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, int trylock) {
  packet_status("send_packet__respond__f2scheduler_cmutex__trylock: executing.");
  pcs_respond__f2scheduler_cmutex__trylock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2scheduler_cmutex__trylock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.trylock                                   = trylock;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2scheduler_cmutex__trylock(funk2_node_t* funk2_node, pcs_respond__f2scheduler_cmutex__trylock_t* packet) {
  packet_status("recv_packet__respond__f2scheduler_cmutex__trylock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

int funk2_node__f2scheduler_cmutex__trylock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2scheduler_cmutex__trylock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2scheduler_cmutex__trylock_t* packet = (pcs_respond__f2scheduler_cmutex__trylock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  int trylock = packet->payload.trylock;
  f2__free(to_ptr(packet));
  return trylock;
}

int f2scheduler_cmutex__trylock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2scheduler_cmutex__trylock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2scheduler_cmutex__trylock(funk2_node, fiber, cause, this);
  }
}



// cmutex

// ******************************************************
// * 
// * 

void send_packet__request__f2cmutex__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__request__f2cmutex__new: executing.");
  pcs_request__f2cmutex__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2cmutex__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2cmutex__new(funk2_node_t* funk2_node, pcs_request__f2cmutex__new_t* packet) {
  packet_status("recv_packet__request__f2cmutex__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2cmutex__new(cause);
  send_packet__respond__f2cmutex__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2cmutex__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2cmutex__new: executing.");
  pcs_respond__f2cmutex__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2cmutex__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2cmutex__new(funk2_node_t* funk2_node, pcs_respond__f2cmutex__new_t* packet) {
  packet_status("recv_packet__respond__f2cmutex__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2cmutex__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  send_packet__request__f2cmutex__new(funk2_node, this_fiber, cause);
  pcs_respond__f2cmutex__new_t* packet = (pcs_respond__f2cmutex__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2cmutex__new(f2ptr cause) {
  return pfunk2__f2cmutex__new(cause);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2cmutex__is_locked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2cmutex__is_locked: executing.");
  pcs_request__f2cmutex__is_locked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2cmutex__is_locked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2cmutex__is_locked(funk2_node_t* funk2_node, pcs_request__f2cmutex__is_locked_t* packet) {
  packet_status("recv_packet__request__f2cmutex__is_locked: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  boolean_t is_locked = pfunk2__f2cmutex__is_locked(this, cause);
  send_packet__respond__f2cmutex__is_locked(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, is_locked);
}

void send_packet__respond__f2cmutex__is_locked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, boolean_t is_locked) {
  packet_status("send_packet__respond__f2cmutex__is_locked: executing.");
  pcs_respond__f2cmutex__is_locked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2cmutex__is_locked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.is_locked                                   = is_locked;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2cmutex__is_locked(funk2_node_t* funk2_node, pcs_respond__f2cmutex__is_locked_t* packet) {
  packet_status("recv_packet__respond__f2cmutex__is_locked: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

boolean_t funk2_node__f2cmutex__is_locked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2cmutex__is_locked(funk2_node, this_fiber, cause, this);
  pcs_respond__f2cmutex__is_locked_t* packet = (pcs_respond__f2cmutex__is_locked_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  boolean_t is_locked = packet->payload.is_locked;
  f2__free(to_ptr(packet));
  return is_locked;
}

boolean_t f2cmutex__is_locked(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2cmutex__is_locked(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2cmutex__is_locked(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2cmutex__lock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2cmutex__lock: executing.");
  pcs_request__f2cmutex__lock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2cmutex__lock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2cmutex__lock(funk2_node_t* funk2_node, pcs_request__f2cmutex__lock_t* packet) {
  packet_status("recv_packet__request__f2cmutex__lock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2cmutex__lock(this, cause);
  send_packet__respond__f2cmutex__lock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2cmutex__lock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2cmutex__lock: executing.");
  pcs_respond__f2cmutex__lock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2cmutex__lock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2cmutex__lock(funk2_node_t* funk2_node, pcs_respond__f2cmutex__lock_t* packet) {
  packet_status("recv_packet__respond__f2cmutex__lock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2cmutex__lock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2cmutex__lock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2cmutex__lock_t* packet = (pcs_respond__f2cmutex__lock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2cmutex__lock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2cmutex__lock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2cmutex__lock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2cmutex__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2cmutex__unlock: executing.");
  pcs_request__f2cmutex__unlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2cmutex__unlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2cmutex__unlock(funk2_node_t* funk2_node, pcs_request__f2cmutex__unlock_t* packet) {
  packet_status("recv_packet__request__f2cmutex__unlock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2cmutex__unlock(this, cause);
  send_packet__respond__f2cmutex__unlock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2cmutex__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2cmutex__unlock: executing.");
  pcs_respond__f2cmutex__unlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2cmutex__unlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2cmutex__unlock(funk2_node_t* funk2_node, pcs_respond__f2cmutex__unlock_t* packet) {
  packet_status("recv_packet__respond__f2cmutex__unlock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2cmutex__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2cmutex__unlock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2cmutex__unlock_t* packet = (pcs_respond__f2cmutex__unlock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2cmutex__unlock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2cmutex__unlock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2cmutex__unlock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2cmutex__trylock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2cmutex__trylock: executing.");
  pcs_request__f2cmutex__trylock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2cmutex__trylock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2cmutex__trylock(funk2_node_t* funk2_node, pcs_request__f2cmutex__trylock_t* packet) {
  packet_status("recv_packet__request__f2cmutex__trylock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int trylock = pfunk2__f2cmutex__trylock(this, cause);
  send_packet__respond__f2cmutex__trylock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, trylock);
}

void send_packet__respond__f2cmutex__trylock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, int trylock) {
  packet_status("send_packet__respond__f2cmutex__trylock: executing.");
  pcs_respond__f2cmutex__trylock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2cmutex__trylock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.trylock                                   = trylock;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2cmutex__trylock(funk2_node_t* funk2_node, pcs_respond__f2cmutex__trylock_t* packet) {
  packet_status("recv_packet__respond__f2cmutex__trylock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

int funk2_node__f2cmutex__trylock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2cmutex__trylock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2cmutex__trylock_t* packet = (pcs_respond__f2cmutex__trylock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  int trylock = packet->payload.trylock;
  f2__free(to_ptr(packet));
  return trylock;
}

int f2cmutex__trylock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2cmutex__trylock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2cmutex__trylock(funk2_node, fiber, cause, this);
  }
}



// creadwritelock

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__request__f2creadwritelock__new: executing.");
  pcs_request__f2creadwritelock__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__new(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__new_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2creadwritelock__new(cause);
  send_packet__respond__f2creadwritelock__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2creadwritelock__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2creadwritelock__new: executing.");
  pcs_respond__f2creadwritelock__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__new(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__new_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2creadwritelock__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  send_packet__request__f2creadwritelock__new(funk2_node, this_fiber, cause);
  pcs_respond__f2creadwritelock__new_t* packet = (pcs_respond__f2creadwritelock__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2creadwritelock__new(f2ptr cause) {
  return pfunk2__f2creadwritelock__new(cause);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__is_writelocked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__is_writelocked: executing.");
  pcs_request__f2creadwritelock__is_writelocked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__is_writelocked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__is_writelocked(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__is_writelocked_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__is_writelocked: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  boolean_t is_writelocked = pfunk2__f2creadwritelock__is_writelocked(this, cause);
  send_packet__respond__f2creadwritelock__is_writelocked(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, is_writelocked);
}

void send_packet__respond__f2creadwritelock__is_writelocked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, boolean_t is_writelocked) {
  packet_status("send_packet__respond__f2creadwritelock__is_writelocked: executing.");
  pcs_respond__f2creadwritelock__is_writelocked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__is_writelocked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.is_writelocked                                   = is_writelocked;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__is_writelocked(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__is_writelocked_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__is_writelocked: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

boolean_t funk2_node__f2creadwritelock__is_writelocked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__is_writelocked(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__is_writelocked_t* packet = (pcs_respond__f2creadwritelock__is_writelocked_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  boolean_t is_writelocked = packet->payload.is_writelocked;
  f2__free(to_ptr(packet));
  return is_writelocked;
}

boolean_t f2creadwritelock__is_writelocked(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__is_writelocked(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__is_writelocked(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__is_readlocked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__is_readlocked: executing.");
  pcs_request__f2creadwritelock__is_readlocked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__is_readlocked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__is_readlocked(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__is_readlocked_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__is_readlocked: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  boolean_t is_readlocked = pfunk2__f2creadwritelock__is_readlocked(this, cause);
  send_packet__respond__f2creadwritelock__is_readlocked(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, is_readlocked);
}

void send_packet__respond__f2creadwritelock__is_readlocked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, boolean_t is_readlocked) {
  packet_status("send_packet__respond__f2creadwritelock__is_readlocked: executing.");
  pcs_respond__f2creadwritelock__is_readlocked_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__is_readlocked;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.is_readlocked                                   = is_readlocked;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__is_readlocked(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__is_readlocked_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__is_readlocked: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

boolean_t funk2_node__f2creadwritelock__is_readlocked(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__is_readlocked(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__is_readlocked_t* packet = (pcs_respond__f2creadwritelock__is_readlocked_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  boolean_t is_readlocked = packet->payload.is_readlocked;
  f2__free(to_ptr(packet));
  return is_readlocked;
}

boolean_t f2creadwritelock__is_readlocked(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__is_readlocked(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__is_readlocked(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__writelock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__writelock: executing.");
  pcs_request__f2creadwritelock__writelock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__writelock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__writelock(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__writelock_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__writelock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2creadwritelock__writelock(this, cause);
  send_packet__respond__f2creadwritelock__writelock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2creadwritelock__writelock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2creadwritelock__writelock: executing.");
  pcs_respond__f2creadwritelock__writelock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__writelock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__writelock(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__writelock_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__writelock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2creadwritelock__writelock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__writelock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__writelock_t* packet = (pcs_respond__f2creadwritelock__writelock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2creadwritelock__writelock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__writelock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__writelock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__readlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__readlock: executing.");
  pcs_request__f2creadwritelock__readlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__readlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__readlock(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__readlock_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__readlock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2creadwritelock__readlock(this, cause);
  send_packet__respond__f2creadwritelock__readlock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2creadwritelock__readlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2creadwritelock__readlock: executing.");
  pcs_respond__f2creadwritelock__readlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__readlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__readlock(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__readlock_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__readlock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2creadwritelock__readlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__readlock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__readlock_t* packet = (pcs_respond__f2creadwritelock__readlock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2creadwritelock__readlock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__readlock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__readlock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__unlock: executing.");
  pcs_request__f2creadwritelock__unlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__unlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__unlock(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__unlock_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__unlock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2creadwritelock__unlock(this, cause);
  send_packet__respond__f2creadwritelock__unlock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2creadwritelock__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2creadwritelock__unlock: executing.");
  pcs_respond__f2creadwritelock__unlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__unlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__unlock(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__unlock_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__unlock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2creadwritelock__unlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__unlock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__unlock_t* packet = (pcs_respond__f2creadwritelock__unlock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2creadwritelock__unlock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__unlock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__unlock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__trywritelock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__trywritelock: executing.");
  pcs_request__f2creadwritelock__trywritelock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__trywritelock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__trywritelock(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__trywritelock_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__trywritelock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int trywritelock = pfunk2__f2creadwritelock__trywritelock(this, cause);
  send_packet__respond__f2creadwritelock__trywritelock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, trywritelock);
}

void send_packet__respond__f2creadwritelock__trywritelock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, int trywritelock) {
  packet_status("send_packet__respond__f2creadwritelock__trywritelock: executing.");
  pcs_respond__f2creadwritelock__trywritelock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__trywritelock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.trywritelock                                   = trywritelock;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__trywritelock(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__trywritelock_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__trywritelock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

int funk2_node__f2creadwritelock__trywritelock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__trywritelock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__trywritelock_t* packet = (pcs_respond__f2creadwritelock__trywritelock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  int trywritelock = packet->payload.trywritelock;
  f2__free(to_ptr(packet));
  return trywritelock;
}

int f2creadwritelock__trywritelock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__trywritelock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__trywritelock(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2creadwritelock__tryreadlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2creadwritelock__tryreadlock: executing.");
  pcs_request__f2creadwritelock__tryreadlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2creadwritelock__tryreadlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2creadwritelock__tryreadlock(funk2_node_t* funk2_node, pcs_request__f2creadwritelock__tryreadlock_t* packet) {
  packet_status("recv_packet__request__f2creadwritelock__tryreadlock: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int tryreadlock = pfunk2__f2creadwritelock__tryreadlock(this, cause);
  send_packet__respond__f2creadwritelock__tryreadlock(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, tryreadlock);
}

void send_packet__respond__f2creadwritelock__tryreadlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, int tryreadlock) {
  packet_status("send_packet__respond__f2creadwritelock__tryreadlock: executing.");
  pcs_respond__f2creadwritelock__tryreadlock_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2creadwritelock__tryreadlock;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.tryreadlock                                   = tryreadlock;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2creadwritelock__tryreadlock(funk2_node_t* funk2_node, pcs_respond__f2creadwritelock__tryreadlock_t* packet) {
  packet_status("recv_packet__respond__f2creadwritelock__tryreadlock: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

int funk2_node__f2creadwritelock__tryreadlock(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2creadwritelock__tryreadlock(funk2_node, this_fiber, cause, this);
  pcs_respond__f2creadwritelock__tryreadlock_t* packet = (pcs_respond__f2creadwritelock__tryreadlock_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  int tryreadlock = packet->payload.tryreadlock;
  f2__free(to_ptr(packet));
  return tryreadlock;
}

int f2creadwritelock__tryreadlock(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2creadwritelock__tryreadlock(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2creadwritelock__tryreadlock(funk2_node, fiber, cause, this);
  }
}



// char

// ******************************************************
// * 
// * 

void send_packet__request__f2char__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 ch) {
  packet_status("send_packet__request__f2char__new: executing.");
  pcs_request__f2char__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2char__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.ch                                        = ch;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2char__new(funk2_node_t* funk2_node, pcs_request__f2char__new_t* packet) {
  packet_status("recv_packet__request__f2char__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2char__new(cause, packet->payload.ch);
  send_packet__respond__f2char__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2char__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2char__new: executing.");
  pcs_respond__f2char__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2char__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2char__new(funk2_node_t* funk2_node, pcs_respond__f2char__new_t* packet) {
  packet_status("recv_packet__respond__f2char__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2char__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 ch) {
  send_packet__request__f2char__new(funk2_node, this_fiber, cause, ch);
  pcs_respond__f2char__new_t* packet = (pcs_respond__f2char__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2char__new(f2ptr cause, u64 ch) {
  return pfunk2__f2char__new(cause, ch);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2char__ch(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2char__ch: executing.");
  pcs_request__f2char__ch_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2char__ch;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2char__ch(funk2_node_t* funk2_node, pcs_request__f2char__ch_t* packet) {
  packet_status("recv_packet__request__f2char__ch: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 ch = pfunk2__f2char__ch(this, cause);
  send_packet__respond__f2char__ch(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, ch);
}

void send_packet__respond__f2char__ch(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 ch) {
  packet_status("send_packet__respond__f2char__ch: executing.");
  pcs_respond__f2char__ch_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2char__ch;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.ch                                        = ch;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2char__ch(funk2_node_t* funk2_node, pcs_respond__f2char__ch_t* packet) {
  packet_status("recv_packet__respond__f2char__ch: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2char__ch(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2char__ch(funk2_node, this_fiber, cause, this);
  pcs_respond__f2char__ch_t* packet = (pcs_respond__f2char__ch_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 ch = packet->payload.ch;
  f2__free(to_ptr(packet));
  return ch;
}

u64 f2char__ch(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2char__ch(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2char__ch(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2string__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, funk2_character_t* init) {
  packet_status("send_packet__request__f2string__new: executing.");
  pcs_request__f2string__new_t* packet = (pcs_request__f2string__new_t*)alloca(sizeof(pcs_request__f2string__new_t) + (length * sizeof(funk2_character_t)));
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + (length * sizeof(funk2_character_t)));
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2string__new;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber               = this_fiber;
  packet->payload.length                                    = length;
  memcpy(packet->payload.init, init, length * sizeof(funk2_character_t));
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__request__f2string__new(funk2_node_t* funk2_node, pcs_request__f2string__new_t* packet) {
  packet_status("recv_packet__request__f2string__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2string__new(cause, packet->payload.length, packet->payload.init);
  send_packet__respond__f2string__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2string__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2string__new: executing.");
  pcs_respond__f2string__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2string__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2string__new(funk2_node_t* funk2_node, pcs_respond__f2string__new_t* packet) {
  packet_status("recv_packet__respond__f2string__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2string__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, funk2_character_t* init) {
  send_packet__request__f2string__new(funk2_node, this_fiber, cause, length, init);
  pcs_respond__f2string__new_t* packet = (pcs_respond__f2string__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2string__new(f2ptr cause, u64 length, funk2_character_t* init) {
  return pfunk2__f2string__new(cause, length, init);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2string__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2string__length: executing.");
  pcs_request__f2string__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2string__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2string__length(funk2_node_t* funk2_node, pcs_request__f2string__length_t* packet) {
  packet_status("recv_packet__request__f2string__length: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 length = pfunk2__f2string__length(this, cause);
  send_packet__respond__f2string__length(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, length);
}

void send_packet__respond__f2string__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length) {
  packet_status("send_packet__respond__f2string__length: executing.");
  pcs_respond__f2string__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2string__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2string__length(funk2_node_t* funk2_node, pcs_respond__f2string__length_t* packet) {
  packet_status("recv_packet__respond__f2string__length: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2string__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2string__length(funk2_node, this_fiber, cause, this);
  pcs_respond__f2string__length_t* packet = (pcs_respond__f2string__length_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 length = packet->payload.length;
  f2__free(to_ptr(packet));
  return length;
}

u64 f2string__length(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2string__length(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2string__length(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2string__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int index) {
  packet_status("send_packet__request__f2string__elt: executing.");
  pcs_request__f2string__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2string__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2string__elt(funk2_node_t* funk2_node, pcs_request__f2string__elt_t* packet) {
  packet_status("recv_packet__request__f2string__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u8 elt = pfunk2__f2string__elt(this, packet->payload.index, cause);
  send_packet__respond__f2string__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2string__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, funk2_character_t elt) {
  packet_status("send_packet__respond__f2string__elt: executing.");
  pcs_respond__f2string__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2string__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2string__elt(funk2_node_t* funk2_node, pcs_respond__f2string__elt_t* packet) {
  packet_status("recv_packet__respond__f2string__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

funk2_character_t funk2_node__f2string__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int index) {
  send_packet__request__f2string__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2string__elt_t* packet = (pcs_respond__f2string__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  funk2_character_t elt = packet->payload.elt;
  f2__free(to_ptr(packet));
  return elt;
}

funk2_character_t f2string__elt(f2ptr this, int index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2string__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2string__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2string__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2string__str_copy: executing.");
  pcs_request__f2string__str_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2string__str_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2string__str_copy(funk2_node_t* funk2_node, pcs_request__f2string__str_copy_t* packet) {
  packet_status("recv_packet__request__f2string__str_copy: executing.");
  f2ptr cause = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this  = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int                str__length = pfunk2__f2string__length(this, cause);
  funk2_character_t* str         = (funk2_character_t*)alloca(str__length * sizeof(funk2_character_t));
  f2string__str_copy(this, cause, str);
  send_packet__respond__f2string__str_copy(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, str__length, str);
}

void send_packet__respond__f2string__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, funk2_character_t* str) {
  packet_status("send_packet__respond__f2string__str_copy: executing.");
  pcs_respond__f2string__str_copy_t* packet = (pcs_respond__f2string__str_copy_t*)alloca(sizeof(pcs_respond__f2string__str_copy_t) + (length * sizeof(funk2_character_t)));
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + (length * sizeof(funk2_character_t)));
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2string__str_copy;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber               = this_fiber;
  packet->payload.length                                    = length;
  memcpy(packet->payload.str, str, length * sizeof(funk2_character_t));
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__respond__f2string__str_copy(funk2_node_t* funk2_node, pcs_respond__f2string__str_copy_t* packet) {
  packet_status("recv_packet__respond__f2string__str_copy: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2string__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, funk2_character_t* str) {
  send_packet__request__f2string__str_copy(funk2_node, this_fiber, cause, this);
  pcs_respond__f2string__str_copy_t* packet = (pcs_respond__f2string__str_copy_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  memcpy(str, packet->payload.str, packet->payload.length * sizeof(funk2_character_t));
  f2__free(to_ptr(packet));
}

void f2string__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2string__str_copy(this, cause, str);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2string__str_copy(funk2_node, fiber, cause, this, str);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2string__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2string__eq_hash_value: executing.");
  pcs_request__f2string__eq_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2string__eq_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2string__eq_hash_value(funk2_node_t* funk2_node, pcs_request__f2string__eq_hash_value_t* packet) {
  packet_status("recv_packet__request__f2string__eq_hash_value: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int eq_hash_value = pfunk2__f2string__eq_hash_value(this, cause);
  send_packet__respond__f2string__eq_hash_value(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, eq_hash_value);
}

void send_packet__respond__f2string__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, int eq_hash_value) {
  packet_status("send_packet__respond__f2string__eq_hash_value: executing.");
  pcs_respond__f2string__eq_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2string__eq_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.eq_hash_value                                = eq_hash_value;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2string__eq_hash_value(funk2_node_t* funk2_node, pcs_respond__f2string__eq_hash_value_t* packet) {
  packet_status("recv_packet__respond__f2string__eq_hash_value: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

int funk2_node__f2string__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2string__eq_hash_value(funk2_node, this_fiber, cause, this);
  pcs_respond__f2string__eq_hash_value_t* packet = (pcs_respond__f2string__eq_hash_value_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  int eq_hash_value = packet->payload.eq_hash_value;
  f2__free(to_ptr(packet));
  return eq_hash_value;
}

int f2string__eq_hash_value(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2string__eq_hash_value(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2string__eq_hash_value(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2symbol__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, funk2_character_t* init) {
  packet_status("send_packet__request__f2symbol__new: executing.");
  pcs_request__f2symbol__new_t* packet = (pcs_request__f2symbol__new_t*)alloca(sizeof(pcs_request__f2symbol__new_t) + (length * sizeof(funk2_character_t)));
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + (length * sizeof(funk2_character_t)));
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2symbol__new;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber               = this_fiber;
  packet->payload.length                                    = length;
  memcpy(packet->payload.init, init, length);
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__request__f2symbol__new(funk2_node_t* funk2_node, pcs_request__f2symbol__new_t* packet) {
  packet_status("recv_packet__request__f2symbol__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2symbol__new(cause, packet->payload.length, packet->payload.init);
  send_packet__respond__f2symbol__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2symbol__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2symbol__new: executing.");
  pcs_respond__f2symbol__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2symbol__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2symbol__new(funk2_node_t* funk2_node, pcs_respond__f2symbol__new_t* packet) {
  packet_status("recv_packet__respond__f2symbol__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2symbol__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, funk2_character_t* init) {
  send_packet__request__f2symbol__new(funk2_node, this_fiber, cause, length, init);
  pcs_respond__f2symbol__new_t* packet = (pcs_respond__f2symbol__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2symbol__new(f2ptr cause, u64 length, funk2_character_t* init) {
  return pfunk2__f2symbol__new(cause, length, init);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2symbol__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2symbol__length: executing.");
  pcs_request__f2symbol__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2symbol__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2symbol__length(funk2_node_t* funk2_node, pcs_request__f2symbol__length_t* packet) {
  packet_status("recv_packet__request__f2symbol__length: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 length = pfunk2__f2symbol__length(this, cause);
  send_packet__respond__f2symbol__length(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, length);
}

void send_packet__respond__f2symbol__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length) {
  packet_status("send_packet__respond__f2symbol__length: executing.");
  pcs_respond__f2symbol__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2symbol__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2symbol__length(funk2_node_t* funk2_node, pcs_respond__f2symbol__length_t* packet) {
  packet_status("recv_packet__respond__f2symbol__length: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2symbol__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2symbol__length(funk2_node, this_fiber, cause, this);
  pcs_respond__f2symbol__length_t* packet = (pcs_respond__f2symbol__length_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 length = packet->payload.length;
  f2__free(to_ptr(packet));
  return length;
}

u64 f2symbol__length(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2symbol__length(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2symbol__length(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2symbol__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2symbol__eq_hash_value: executing.");
  pcs_request__f2symbol__eq_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2symbol__eq_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2symbol__eq_hash_value(funk2_node_t* funk2_node, pcs_request__f2symbol__eq_hash_value_t* packet) {
  packet_status("recv_packet__request__f2symbol__eq_hash_value: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 eq_hash_value = pfunk2__f2symbol__eq_hash_value(this, cause);
  send_packet__respond__f2symbol__eq_hash_value(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, eq_hash_value);
}

void send_packet__respond__f2symbol__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 eq_hash_value) {
  packet_status("send_packet__respond__f2symbol__eq_hash_value: executing.");
  pcs_respond__f2symbol__eq_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2symbol__eq_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.eq_hash_value                                = eq_hash_value;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2symbol__eq_hash_value(funk2_node_t* funk2_node, pcs_respond__f2symbol__eq_hash_value_t* packet) {
  packet_status("recv_packet__respond__f2symbol__eq_hash_value: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2symbol__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2symbol__eq_hash_value(funk2_node, this_fiber, cause, this);
  pcs_respond__f2symbol__eq_hash_value_t* packet = (pcs_respond__f2symbol__eq_hash_value_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 eq_hash_value = packet->payload.eq_hash_value;
  f2__free(to_ptr(packet));
  return eq_hash_value;
}

u64 f2symbol__eq_hash_value(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2symbol__eq_hash_value(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2symbol__eq_hash_value(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2symbol__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int index) {
  packet_status("send_packet__request__f2symbol__elt: executing.");
  pcs_request__f2symbol__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2symbol__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2symbol__elt(funk2_node_t* funk2_node, pcs_request__f2symbol__elt_t* packet) {
  packet_status("recv_packet__request__f2symbol__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  funk2_character_t elt = pfunk2__f2symbol__elt(this, packet->payload.index, cause);
  send_packet__respond__f2symbol__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2symbol__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, funk2_character_t elt) {
  packet_status("send_packet__respond__f2symbol__elt: executing.");
  pcs_respond__f2symbol__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2symbol__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2symbol__elt(funk2_node_t* funk2_node, pcs_respond__f2symbol__elt_t* packet) {
  packet_status("recv_packet__respond__f2symbol__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

funk2_character_t funk2_node__f2symbol__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int index) {
  send_packet__request__f2symbol__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2symbol__elt_t* packet = (pcs_respond__f2symbol__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  funk2_character_t elt = packet->payload.elt;
  f2__free(to_ptr(packet));
  return elt;
}

funk2_character_t f2symbol__elt(f2ptr this, int index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2symbol__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2symbol__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2symbol__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2symbol__str_copy: executing.");
  pcs_request__f2symbol__str_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2symbol__str_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2symbol__str_copy(funk2_node_t* funk2_node, pcs_request__f2symbol__str_copy_t* packet) {
  packet_status("recv_packet__request__f2symbol__str_copy: executing.");
  f2ptr cause = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this  = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64                str__length = pfunk2__f2symbol__length(this, cause);
  funk2_character_t* str         = (funk2_character_t*)alloca(str__length * sizeof(funk2_character_t));
  pfunk2__f2symbol__str_copy(this, cause, str);
  send_packet__respond__f2symbol__str_copy(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, str__length, str);
}

void send_packet__respond__f2symbol__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, funk2_character_t* str) {
  packet_status("send_packet__respond__f2symbol__str_copy: len=" u64__fstr ".", length);
  pcs_respond__f2symbol__str_copy_t* packet = (pcs_respond__f2symbol__str_copy_t*)alloca(sizeof(pcs_respond__f2symbol__str_copy_t) + (length * sizeof(funk2_character_t)));
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + (length * sizeof(funk2_character_t)));
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2symbol__str_copy;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber               = this_fiber;
  packet->payload.length                                    = length;
  memcpy(packet->payload.str, str, length * sizeof(funk2_character_t));
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__respond__f2symbol__str_copy(funk2_node_t* funk2_node, pcs_respond__f2symbol__str_copy_t* packet) {
  //int str__size = funk2_packet__sizeof((funk2_packet_t*)packet) - sizeof(pcs_respond__f2symbol__str_copy_t);
  packet_status("recv_packet__respond__f2symbol__str_copy.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2symbol__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, funk2_character_t* str) {
  send_packet__request__f2symbol__str_copy(funk2_node, this_fiber, cause, this);
  pcs_respond__f2symbol__str_copy_t* packet = (pcs_respond__f2symbol__str_copy_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  memcpy(str, packet->payload.str, packet->payload.length * sizeof(funk2_character_t));
  f2__free(to_ptr(packet));
}

void f2symbol__str_copy(f2ptr this, f2ptr cause, funk2_character_t* str) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2symbol__str_copy(this, cause, str);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2symbol__str_copy(funk2_node, fiber, cause, this, str);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, byte* bytes) {
  packet_status("send_packet__request__f2chunk__new: executing.");
  pcs_request__f2chunk__new_t* packet = (pcs_request__f2chunk__new_t*)alloca(sizeof(pcs_request__f2chunk__new_t) + length);
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + length);
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__new;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber              = this_fiber;
  packet->payload.length                                    = length;
  memcpy(packet->payload.bytes, bytes, length);
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__request__f2chunk__new(funk2_node_t* funk2_node, pcs_request__f2chunk__new_t* packet) {
  packet_status("recv_packet__request__f2chunk__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2chunk__new(cause, packet->payload.length, packet->payload.bytes);
  send_packet__respond__f2chunk__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2chunk__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2chunk__new: executing.");
  pcs_respond__f2chunk__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__new(funk2_node_t* funk2_node, pcs_respond__f2chunk__new_t* packet) {
  packet_status("recv_packet__respond__f2chunk__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2chunk__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, byte* bytes) {
  send_packet__request__f2chunk__new(funk2_node, this_fiber, cause, length, bytes);
  pcs_respond__f2chunk__new_t* packet = (pcs_respond__f2chunk__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2chunk__new(f2ptr cause, u64 length, byte* bytes) {
  return pfunk2__f2chunk__new(cause, length, bytes);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr init_chunk) {
  packet_status("send_packet__request__f2chunk__new_copy: executing.");
  pcs_request__f2chunk__new_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__new_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.init_chunk                                = init_chunk;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__new_copy(funk2_node_t* funk2_node, pcs_request__f2chunk__new_copy_t* packet) {
  packet_status("recv_packet__request__f2chunk__new_copy: executing.");
  f2ptr cause      = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber     = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr init_chunk = rf2_to_lf2(packet->payload.init_chunk);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new_copy = pfunk2__f2chunk__new_copy(cause, init_chunk);
  send_packet__respond__f2chunk__new_copy(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new_copy);
}

void send_packet__respond__f2chunk__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new_copy) {
  packet_status("send_packet__respond__f2chunk__new_copy: executing.");
  pcs_respond__f2chunk__new_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__new_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new_copy                                  = new_copy;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__new_copy(funk2_node_t* funk2_node, pcs_respond__f2chunk__new_copy_t* packet) {
  packet_status("recv_packet__respond__f2chunk__new_copy: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2chunk__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr init_chunk) {
  send_packet__request__f2chunk__new_copy(funk2_node, this_fiber, cause, init_chunk);
  pcs_respond__f2chunk__new_copy_t* packet = (pcs_respond__f2chunk__new_copy_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new_copy = rf2_to_lf2(packet->payload.new_copy);
  f2__free(to_ptr(packet));
  return new_copy;
}

f2ptr f2chunk__new_copy(f2ptr cause, f2ptr init_chunk) {
  return pfunk2__f2chunk__new_copy(cause, init_chunk);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2chunk__length: executing.");
  pcs_request__f2chunk__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__length(funk2_node_t* funk2_node, pcs_request__f2chunk__length_t* packet) {
  packet_status("recv_packet__request__f2chunk__length: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 length = pfunk2__f2chunk__length(this, cause);
  send_packet__respond__f2chunk__length(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, length);
}

void send_packet__respond__f2chunk__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length) {
  packet_status("send_packet__respond__f2chunk__length: executing.");
  pcs_respond__f2chunk__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__length(funk2_node_t* funk2_node, pcs_respond__f2chunk__length_t* packet) {
  packet_status("recv_packet__respond__f2chunk__length: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2chunk__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2chunk__length(funk2_node, this_fiber, cause, this);
  pcs_respond__f2chunk__length_t* packet = (pcs_respond__f2chunk__length_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 length = packet->payload.length;
  f2__free(to_ptr(packet));
  return length;
}

u64 f2chunk__length(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__length(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__length(funk2_node, fiber, cause, this);
  }
}


// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2chunk__str_copy: executing.");
  pcs_request__f2chunk__str_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__str_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__str_copy(funk2_node_t* funk2_node, pcs_request__f2chunk__str_copy_t* packet) {
  packet_status("recv_packet__request__f2chunk__str_copy: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int str__size = pfunk2__f2chunk__length(this, cause) + 1;
  u8* str = (u8*)alloca(str__size);
  f2chunk__str_copy(this, cause, str);
  send_packet__respond__f2chunk__str_copy(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, str);
}

void send_packet__respond__f2chunk__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u8* str) {
  packet_status("send_packet__respond__f2chunk__str_copy: executing.");
  int str__size = strlen((char*)str) + 1;
  pcs_respond__f2chunk__str_copy_t* packet = (pcs_respond__f2chunk__str_copy_t*)alloca(sizeof(pcs_respond__f2chunk__str_copy_t) + str__size);
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + str__size);
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__str_copy;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber              = this_fiber;
  memcpy(packet->payload.str, str, str__size);
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__respond__f2chunk__str_copy(funk2_node_t* funk2_node, pcs_respond__f2chunk__str_copy_t* packet) {
  packet_status("recv_packet__respond__f2chunk__str_copy: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2chunk__str_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u8* str) {
  send_packet__request__f2chunk__str_copy(funk2_node, this_fiber, cause, this);
  pcs_respond__f2chunk__str_copy_t* packet = (pcs_respond__f2chunk__str_copy_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  strcpy((char*)str, (char*)packet->payload.str);
  f2__free(to_ptr(packet));
}

void f2chunk__str_copy(f2ptr this, f2ptr cause, u8* str) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__str_copy(this, cause, str);
  } else {
    f2ptr         fiber      = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__str_copy(funk2_node, fiber, cause, this, str);
  }
}


// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2chunk__eq_hash_value: executing.");
  pcs_request__f2chunk__eq_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__eq_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__eq_hash_value(funk2_node_t* funk2_node, pcs_request__f2chunk__eq_hash_value_t* packet) {
  packet_status("recv_packet__request__f2chunk__eq_hash_value: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 eq_hash_value = pfunk2__f2chunk__eq_hash_value(this, cause);
  send_packet__respond__f2chunk__eq_hash_value(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, eq_hash_value);
}

void send_packet__respond__f2chunk__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 eq_hash_value) {
  packet_status("send_packet__respond__f2chunk__eq_hash_value: executing.");
  pcs_respond__f2chunk__eq_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__eq_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.eq_hash_value                                    = eq_hash_value;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__eq_hash_value(funk2_node_t* funk2_node, pcs_respond__f2chunk__eq_hash_value_t* packet) {
  packet_status("recv_packet__respond__f2chunk__eq_hash_value: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2chunk__eq_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2chunk__eq_hash_value(funk2_node, this_fiber, cause, this);
  pcs_respond__f2chunk__eq_hash_value_t* packet = (pcs_respond__f2chunk__eq_hash_value_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 eq_hash_value = packet->payload.eq_hash_value;
  f2__free(to_ptr(packet));
  return eq_hash_value;
}

u64 f2chunk__eq_hash_value(f2ptr cause, f2ptr this) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__eq_hash_value(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__eq_hash_value(funk2_node, fiber, cause, this);
  }
}


// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__equals_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2chunk__equals_hash_value: executing.");
  pcs_request__f2chunk__equals_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__equals_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__equals_hash_value(funk2_node_t* funk2_node, pcs_request__f2chunk__equals_hash_value_t* packet) {
  packet_status("recv_packet__request__f2chunk__equals_hash_value: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 equals_hash_value = pfunk2__f2chunk__equals_hash_value(this, cause);
  send_packet__respond__f2chunk__equals_hash_value(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, equals_hash_value);
}

void send_packet__respond__f2chunk__equals_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 equals_hash_value) {
  packet_status("send_packet__respond__f2chunk__equals_hash_value: executing.");
  pcs_respond__f2chunk__equals_hash_value_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__equals_hash_value;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.equals_hash_value                                    = equals_hash_value;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__equals_hash_value(funk2_node_t* funk2_node, pcs_respond__f2chunk__equals_hash_value_t* packet) {
  packet_status("recv_packet__respond__f2chunk__equals_hash_value: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2chunk__equals_hash_value(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2chunk__equals_hash_value(funk2_node, this_fiber, cause, this);
  pcs_respond__f2chunk__equals_hash_value_t* packet = (pcs_respond__f2chunk__equals_hash_value_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 equals_hash_value = packet->payload.equals_hash_value;
  f2__free(to_ptr(packet));
  return equals_hash_value;
}

u64 f2chunk__equals_hash_value(f2ptr cause, f2ptr this) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__equals_hash_value(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__equals_hash_value(funk2_node, fiber, cause, this);
  }
}


// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit8__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2chunk__bit8__elt: executing.");
  pcs_request__f2chunk__bit8__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit8__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit8__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit8__elt_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit8__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u8 elt = pfunk2__f2chunk__bit8__elt(this, packet->payload.index, cause);
  send_packet__respond__f2chunk__bit8__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2chunk__bit8__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u8 elt) {
  packet_status("send_packet__respond__f2chunk__bit8__elt: executing.");
  pcs_respond__f2chunk__bit8__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit8__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit8__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit8__elt_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit8__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u8 funk2_node__f2chunk__bit8__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2chunk__bit8__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2chunk__bit8__elt_t* packet = (pcs_respond__f2chunk__bit8__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u8 elt = packet->payload.elt;
  f2__free(to_ptr(packet));
  return elt;
}

u8 f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit8__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit8__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u8 value) {
  packet_status("send_packet__request__f2chunk__bit8__elt__set: executing.");
  pcs_request__f2chunk__bit8__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit8__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit8__elt__set_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit8__elt__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2chunk__bit8__elt__set(this, packet->payload.index, cause, packet->payload.value);
  send_packet__respond__f2chunk__bit8__elt__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2chunk__bit8__elt__set: executing.");
  pcs_respond__f2chunk__bit8__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit8__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit8__elt__set_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit8__elt__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2chunk__bit8__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u8 value) {
  send_packet__request__f2chunk__bit8__elt__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2chunk__bit8__elt__set_t* packet = (pcs_respond__f2chunk__bit8__elt__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2chunk__bit8__elt__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit8__elt__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit16__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2chunk__bit16__elt: executing.");
  pcs_request__f2chunk__bit16__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit16__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit16__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit16__elt_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit16__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u16 elt = pfunk2__f2chunk__bit16__elt(this, packet->payload.index, cause);
  send_packet__respond__f2chunk__bit16__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2chunk__bit16__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u16 elt) {
  packet_status("send_packet__respond__f2chunk__bit16__elt: executing.");
  pcs_respond__f2chunk__bit16__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit16__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit16__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit16__elt_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit16__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u16 funk2_node__f2chunk__bit16__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2chunk__bit16__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2chunk__bit16__elt_t* packet = (pcs_respond__f2chunk__bit16__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u16 elt = packet->payload.elt;
  f2__free(to_ptr(packet));
  return elt;
}

u16 f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit16__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit16__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u16 value) {
  packet_status("send_packet__request__f2chunk__bit16__elt__set: executing.");
  pcs_request__f2chunk__bit16__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit16__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit16__elt__set_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit16__elt__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2chunk__bit16__elt__set(this, packet->payload.index, cause, packet->payload.value);
  send_packet__respond__f2chunk__bit16__elt__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2chunk__bit16__elt__set: executing.");
  pcs_respond__f2chunk__bit16__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit16__elt__set;
  packet.payload.action_payload_header.cause  = cause;
  packet.payload.action_payload_header.fiber = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit16__elt__set_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit16__elt__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2chunk__bit16__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u16 value) {
  send_packet__request__f2chunk__bit16__elt__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2chunk__bit16__elt_t* packet = (pcs_respond__f2chunk__bit16__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit16__elt__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit16__elt__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit32__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2chunk__bit32__elt: executing.");
  pcs_request__f2chunk__bit32__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit32__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit32__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit32__elt_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit32__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u32 elt = pfunk2__f2chunk__bit32__elt(this, packet->payload.index, cause);
  send_packet__respond__f2chunk__bit32__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2chunk__bit32__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u32 elt) {
  packet_status("send_packet__respond__f2chunk__bit32__elt: executing.");
  pcs_respond__f2chunk__bit32__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit32__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit32__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit32__elt_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit32__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u32 funk2_node__f2chunk__bit32__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2chunk__bit32__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2chunk__bit32__elt_t* packet = (pcs_respond__f2chunk__bit32__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u32 elt = packet->payload.elt;
  f2__free(to_ptr(packet));
  return elt;
}

u32 f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit32__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit32__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u32 value) {
  packet_status("send_packet__request__f2chunk__bit32__elt__set: executing.");
  pcs_request__f2chunk__bit32__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit32__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit32__elt__set_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit32__elt__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2chunk__bit32__elt__set(this, packet->payload.index, cause, packet->payload.value);
  send_packet__respond__f2chunk__bit32__elt__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2chunk__bit32__elt__set: executing.");
  pcs_respond__f2chunk__bit32__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit32__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit32__elt__set_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit32__elt__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2chunk__bit32__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u32 value) {
  send_packet__request__f2chunk__bit32__elt__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2chunk__bit32__elt__set_t* packet = (pcs_respond__f2chunk__bit32__elt__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit32__elt__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit32__elt__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit64__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2chunk__bit64__elt: executing.");
  pcs_request__f2chunk__bit64__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit64__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit64__elt(funk2_node_t* funk2_node, pcs_request__f2chunk__bit64__elt_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit64__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 elt = pfunk2__f2chunk__bit64__elt(this, packet->payload.index, cause);
  send_packet__respond__f2chunk__bit64__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2chunk__bit64__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 elt) {
  packet_status("send_packet__respond__f2chunk__bit64__elt: executing.");
  pcs_respond__f2chunk__bit64__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit64__elt;
  packet.payload.action_payload_header.cause  = cause;
  packet.payload.action_payload_header.fiber = this_fiber;
  packet.payload.elt                          = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit64__elt(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit64__elt_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit64__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2chunk__bit64__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2chunk__bit64__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2chunk__bit64__elt_t* packet = (pcs_respond__f2chunk__bit64__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 elt = packet->payload.elt;
  f2__free(to_ptr(packet));
  return elt;
}

u64 f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit64__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit64__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u64 value) {
  packet_status("send_packet__request__f2chunk__bit64__elt__set: executing.");
  pcs_request__f2chunk__bit64__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bit64__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, pcs_request__f2chunk__bit64__elt__set_t* packet) {
  packet_status("recv_packet__request__f2chunk__bit64__elt__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2chunk__bit64__elt__set(this, packet->payload.index, cause, packet->payload.value);
  send_packet__respond__f2chunk__bit64__elt__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2chunk__bit64__elt__set: executing.");
  pcs_respond__f2chunk__bit64__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bit64__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, pcs_respond__f2chunk__bit64__elt__set_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bit64__elt__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2chunk__bit64__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u64 value) {
  send_packet__request__f2chunk__bit64__elt__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2chunk__bit64__elt__set_t* packet = (pcs_respond__f2chunk__bit64__elt__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bit64__elt__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bit64__elt__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__cfunk_jump(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr fiber, f2ptr env, f2ptr args) {
  packet_status("send_packet__request__f2chunk__cfunk_jump: executing.");
  pcs_request__f2chunk__cfunk_jump_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__cfunk_jump;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.fiber                                    = fiber;
  packet.payload.env                                       = env;
  packet.payload.args                                      = args;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__cfunk_jump(funk2_node_t* funk2_node, pcs_request__f2chunk__cfunk_jump_t* packet) {
  packet_status("recv_packet__request__f2chunk__cfunk_jump: executing.");
  f2ptr cause        = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber       = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this         = rf2_to_lf2(packet->payload.this);
  f2ptr cfunk_fiber = rf2_to_lf2(packet->payload.fiber);
  f2ptr cfunk_env    = rf2_to_lf2(packet->payload.env);
  f2ptr cfunk_args   = rf2_to_lf2(packet->payload.args);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr cfunk_jump_return = pfunk2__f2chunk__cfunk_jump(this, cause, cfunk_fiber, cfunk_env, cfunk_args);
  send_packet__respond__f2chunk__cfunk_jump(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, cfunk_jump_return);
}

void send_packet__respond__f2chunk__cfunk_jump(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr cfunk_jump_return) {
  packet_status("send_packet__respond__f2chunk__cfunk_jump: executing.");
  pcs_respond__f2chunk__cfunk_jump_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__cfunk_jump;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.cfunk_jump_return                         = cfunk_jump_return;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__cfunk_jump(funk2_node_t* funk2_node, pcs_respond__f2chunk__cfunk_jump_t* packet) {
  packet_status("recv_packet__respond__f2chunk__cfunk_jump: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2chunk__cfunk_jump(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr fiber, f2ptr env, f2ptr args) {
  send_packet__request__f2chunk__cfunk_jump(funk2_node, this_fiber, cause, this, fiber, env, args);
  pcs_respond__f2chunk__cfunk_jump_t* packet = (pcs_respond__f2chunk__cfunk_jump_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr cfunk_jump_return = rf2_to_lf2(packet->payload.cfunk_jump_return);
  f2__free(to_ptr(packet));
  return cfunk_jump_return;
}

f2ptr f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr fiber, f2ptr env, f2ptr args) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__cfunk_jump(this, cause, fiber, env, args);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__cfunk_jump(funk2_node, fiber, cause, this, fiber, env, args);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__bytecode_jump(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr fiber) {
  packet_status("send_packet__request__f2chunk__bytecode_jump: executing.");
  pcs_request__f2chunk__bytecode_jump_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__bytecode_jump;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.fiber                                    = fiber;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__bytecode_jump(funk2_node_t* funk2_node, pcs_request__f2chunk__bytecode_jump_t* packet) {
  packet_status("recv_packet__request__f2chunk__bytecode_jump: executing.");
  f2ptr cause       = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber      = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this        = rf2_to_lf2(packet->payload.this);
  f2ptr jump_fiber = rf2_to_lf2(packet->payload.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  int bytecode_jump_return = pfunk2__f2chunk__bytecode_jump(this, cause, jump_fiber);
  send_packet__respond__f2chunk__bytecode_jump(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, bytecode_jump_return);
}

void send_packet__respond__f2chunk__bytecode_jump(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, int bytecode_jump_return) {
  packet_status("send_packet__respond__f2chunk__bytecode_jump: executing.");
  pcs_respond__f2chunk__bytecode_jump_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__bytecode_jump;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.bytecode_jump_return = bytecode_jump_return;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__bytecode_jump(funk2_node_t* funk2_node, pcs_respond__f2chunk__bytecode_jump_t* packet) {
  packet_status("recv_packet__respond__f2chunk__bytecode_jump: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

int funk2_node__f2chunk__bytecode_jump(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, f2ptr fiber) {
  send_packet__request__f2chunk__bytecode_jump(funk2_node, this_fiber, cause, this, fiber);
  pcs_respond__f2chunk__bytecode_jump_t* packet = (pcs_respond__f2chunk__bytecode_jump_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  int bytecode_jump_return = packet->payload.bytecode_jump_return;
  f2__free(to_ptr(packet));
  return bytecode_jump_return;
}

int f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr user_fiber) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__bytecode_jump(this, cause, user_fiber);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__bytecode_jump(funk2_node, fiber, cause, this, user_fiber);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__send(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int start, int length, int fd, int flags) {
  packet_status("send_packet__request__f2chunk__send: executing.");
  pcs_request__f2chunk__send_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__send;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.start                                     = start;
  packet.payload.length                                    = length;
  packet.payload.fd                                        = fd;
  packet.payload.flags                                     = flags;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__send(funk2_node_t* funk2_node, pcs_request__f2chunk__send_t* packet) {
  packet_status("recv_packet__request__f2chunk__send: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr send_return = pfunk2__f2chunk__send(this, cause, packet->payload.start, packet->payload.length, packet->payload.fd, packet->payload.flags);
  send_packet__respond__f2chunk__send(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, send_return);
}

void send_packet__respond__f2chunk__send(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr send_return) {
  packet_status("send_packet__respond__f2chunk__send: executing.");
  pcs_respond__f2chunk__send_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__send;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.send_return = send_return;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__send(funk2_node_t* funk2_node, pcs_respond__f2chunk__send_t* packet) {
  packet_status("recv_packet__respond__f2chunk__send: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2chunk__send(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int start, int length, int fd, int flags) {
  send_packet__request__f2chunk__send(funk2_node, this_fiber, cause, this, start, length, fd, flags);
  pcs_respond__f2chunk__send_t* packet = (pcs_respond__f2chunk__send_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr send_return = rf2_to_lf2(packet->payload.send_return);
  f2__free(to_ptr(packet));
  return send_return;
}

f2ptr f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__send(this, cause, start, length, fd, flags);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__send(funk2_node, fiber, cause, this, start, length, fd, flags);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2chunk__recv(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int start, int length, int fd, int flags) {
  packet_status("send_packet__request__f2chunk__recv: executing.");
  pcs_request__f2chunk__recv_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2chunk__recv;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.start                                     = start;
  packet.payload.length                                    = length;
  packet.payload.fd                                        = fd;
  packet.payload.flags                                     = flags;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2chunk__recv(funk2_node_t* funk2_node, pcs_request__f2chunk__recv_t* packet) {
  packet_status("recv_packet__request__f2chunk__recv: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr recv_return = pfunk2__f2chunk__recv(this, cause, packet->payload.start, packet->payload.length, packet->payload.fd, packet->payload.flags);
  send_packet__respond__f2chunk__recv(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, recv_return);
}

void send_packet__respond__f2chunk__recv(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr recv_return) {
  packet_status("send_packet__respond__f2chunk__recv: executing.");
  pcs_respond__f2chunk__recv_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2chunk__recv;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.recv_return                               = recv_return;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2chunk__recv(funk2_node_t* funk2_node, pcs_respond__f2chunk__recv_t* packet) {
  packet_status("recv_packet__respond__f2chunk__recv: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2chunk__recv(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, int start, int length, int fd, int flags) {
  send_packet__request__f2chunk__recv(funk2_node, this_fiber, cause, this, start, length, fd, flags);
  pcs_respond__f2chunk__recv_t* packet = (pcs_respond__f2chunk__recv_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr recv_return = rf2_to_lf2(packet->payload.recv_return);
  f2__free(to_ptr(packet));
  return recv_return;
}

f2ptr f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2chunk__recv(this, cause, start, length, fd, flags);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2chunk__recv(funk2_node, fiber, cause, this, start, length, fd, flags);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, ptr f2ptr_array) {
  packet_status("send_packet__request__f2simple_array__new: executing.");
  int f2ptr_array__size = f2ptr_array ? (sizeof(f2ptr) * length) : 0;
  pcs_request__f2simple_array__new_t* packet = (pcs_request__f2simple_array__new_t*)alloca(sizeof(pcs_request__f2simple_array__new_t) + f2ptr_array__size);
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + f2ptr_array__size);
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__new;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber              = this_fiber;
  packet->payload.length                                    = length;
  packet->payload.f2ptr_array__defined                      = f2ptr_array ? boolean__true : boolean__false;
  if (f2ptr_array) {
    memcpy(packet->payload.f2ptr_array, from_ptr(f2ptr_array), f2ptr_array__size);
  }
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__request__f2simple_array__new(funk2_node_t* funk2_node, pcs_request__f2simple_array__new_t* packet) {
  packet_status("recv_packet__request__f2simple_array__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  u64   length = packet->payload.length;
  f2ptr* remote_f2ptr_array = (f2ptr*)(packet->payload.f2ptr_array__defined ? packet->payload.f2ptr_array : NULL);
  f2ptr* f2ptr_array        = NULL;
  if (remote_f2ptr_array) {
    f2ptr_array = alloca(sizeof(f2ptr) * length);
    u64 i;
    for (i = 0; i < length; i ++) {
      f2ptr_array[i] = rf2_to_lf2(remote_f2ptr_array[i]);
    }
  }
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2simple_array__new(cause, packet->payload.length, to_ptr(f2ptr_array));
  send_packet__respond__f2simple_array__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2simple_array__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2simple_array__new: executing.");
  pcs_respond__f2simple_array__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__new(funk2_node_t* funk2_node, pcs_respond__f2simple_array__new_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2simple_array__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, ptr f2ptr_array) {
  send_packet__request__f2simple_array__new(funk2_node, this_fiber, cause, length, f2ptr_array);
  pcs_respond__f2simple_array__new_t* packet = (pcs_respond__f2simple_array__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_array) {
  return pfunk2__f2simple_array__new(cause, length, f2ptr_array);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, f2ptr init_array) {
  packet_status("send_packet__request__f2simple_array__new_copy: executing.");
  pcs_request__f2simple_array__new_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__new_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  packet.payload.init_array                                = init_array;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2simple_array__new_copy(funk2_node_t* funk2_node, pcs_request__f2simple_array__new_copy_t* packet) {
  packet_status("recv_packet__request__f2simple_array__new_copy: executing.");
  f2ptr cause      = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber     = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr init_array = rf2_to_lf2(packet->payload.init_array);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new_copy = pfunk2__f2simple_array__new_copy(cause, packet->payload.length, init_array);
  send_packet__respond__f2simple_array__new_copy(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new_copy);
}

void send_packet__respond__f2simple_array__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new_copy) {
  packet_status("send_packet__respond__f2simple_array__new_copy: executing.");
  pcs_respond__f2simple_array__new_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__new_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new_copy                                  = new_copy;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__new_copy(funk2_node_t* funk2_node, pcs_respond__f2simple_array__new_copy_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__new_copy: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2simple_array__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, f2ptr init_array) {
  send_packet__request__f2simple_array__new_copy(funk2_node, this_fiber, cause, length, init_array);
  pcs_respond__f2simple_array__new_copy_t* packet = (pcs_respond__f2simple_array__new_copy_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new_copy = rf2_to_lf2(packet->payload.new_copy);
  f2__free(to_ptr(packet));
  return new_copy;
}

f2ptr f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
  return pfunk2__f2simple_array__new_copy(cause, length, init_array);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__immutable(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2simple_array__immutable: executing.");
  pcs_request__f2simple_array__immutable_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__immutable;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2simple_array__immutable(funk2_node_t* funk2_node, pcs_request__f2simple_array__immutable_t* packet) {
  packet_status("recv_packet__request__f2simple_array__immutable: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u8 immutable = pfunk2__f2simple_array__immutable(this, cause);
  send_packet__respond__f2simple_array__immutable(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, immutable);
}

void send_packet__respond__f2simple_array__immutable(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u8 immutable) {
  packet_status("send_packet__respond__f2simple_array__immutable: executing.");
  pcs_respond__f2simple_array__immutable_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__immutable;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.immutable                                 = immutable;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__immutable(funk2_node_t* funk2_node, pcs_respond__f2simple_array__immutable_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__immutable: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2simple_array__immutable(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2simple_array__immutable(funk2_node, this_fiber, cause, this);
  pcs_respond__f2simple_array__immutable_t* packet = (pcs_respond__f2simple_array__immutable_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  packet_status("funk2_node__f2simple_array__immutable: packet->payload.immutable = " f2ptr__fstr, packet->payload.immutable);
  f2ptr immutable = rf2_to_lf2(packet->payload.immutable);
  packet_status("funk2_node__f2simple_array__immutable: rf2_to_lf2(packet->payload.immutable) = " f2ptr__fstr, immutable);
  f2__free(to_ptr(packet));
  return immutable;
}

f2ptr f2simple_array__immutable(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2simple_array__immutable(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2simple_array__immutable(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u8 value) {
  packet_status("send_packet__request__f2simple_array__immutable__set: executing.");
  pcs_request__f2simple_array__immutable__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__immutable__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2simple_array__immutable__set(funk2_node_t* funk2_node, pcs_request__f2simple_array__immutable__set_t* packet) {
  packet_status("recv_packet__request__f2simple_array__immutable__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  u8    value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2simple_array__immutable__set(this, cause, value);
  send_packet__respond__f2simple_array__immutable__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2simple_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2simple_array__immutable__set: executing.");
  pcs_respond__f2simple_array__immutable__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__immutable__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__immutable__set(funk2_node_t* funk2_node, pcs_respond__f2simple_array__immutable__set_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__immutable__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2simple_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u8 value) {
  packet_status("funk2_node__f2simple_array__immutable__set: executing.");
  send_packet__request__f2simple_array__immutable__set(funk2_node, this_fiber, cause, this, value);
  pcs_respond__f2simple_array__immutable__set_t* packet = (pcs_respond__f2simple_array__immutable__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2simple_array__immutable__set(this, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2simple_array__immutable__set(funk2_node, fiber, cause, this, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2simple_array__length: executing.");
  pcs_request__f2simple_array__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2simple_array__length(funk2_node_t* funk2_node, pcs_request__f2simple_array__length_t* packet) {
  packet_status("recv_packet__request__f2simple_array__length: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 length = pfunk2__f2simple_array__length(this, cause);
  send_packet__respond__f2simple_array__length(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, length);
}

void send_packet__respond__f2simple_array__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length) {
  packet_status("send_packet__respond__f2simple_array__length: executing.");
  pcs_respond__f2simple_array__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__length(funk2_node_t* funk2_node, pcs_respond__f2simple_array__length_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__length: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2simple_array__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2simple_array__length(funk2_node, this_fiber, cause, this);
  pcs_respond__f2simple_array__length_t* packet = (pcs_respond__f2simple_array__length_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 length = packet->payload.length;
  f2__free(to_ptr(packet));
  return length;
}

u64 f2simple_array__length(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2simple_array__length(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2simple_array__length(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2simple_array__elt: executing.");
  pcs_request__f2simple_array__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2simple_array__elt(funk2_node_t* funk2_node, pcs_request__f2simple_array__elt_t* packet) {
  packet_status("recv_packet__request__f2simple_array__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr elt = pfunk2__f2simple_array__elt(this, packet->payload.index, cause);
  send_packet__respond__f2simple_array__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2simple_array__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr elt) {
  packet_status("send_packet__respond__f2simple_array__elt: executing.");
  pcs_respond__f2simple_array__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__elt(funk2_node_t* funk2_node, pcs_respond__f2simple_array__elt_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2simple_array__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2simple_array__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2simple_array__elt_t* packet = (pcs_respond__f2simple_array__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  packet_status("funk2_node__f2simple_array__elt: packet->payload.elt = " f2ptr__fstr, packet->payload.elt);
  f2ptr elt = rf2_to_lf2(packet->payload.elt);
  packet_status("funk2_node__f2simple_array__elt: rf2_to_lf2(packet->payload.elt) = " f2ptr__fstr, elt);
  f2__free(to_ptr(packet));
  return elt;
}

f2ptr f2simple_array__elt(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2simple_array__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2simple_array__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2simple_array__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2simple_array__elt__set: executing.");
  pcs_request__f2simple_array__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2simple_array__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2simple_array__elt__set(funk2_node_t* funk2_node, pcs_request__f2simple_array__elt__set_t* packet) {
  packet_status("recv_packet__request__f2simple_array__elt__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2simple_array__elt__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2simple_array__elt__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2simple_array__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2simple_array__elt__set: executing.");
  pcs_respond__f2simple_array__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2simple_array__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2simple_array__elt__set(funk2_node_t* funk2_node, pcs_respond__f2simple_array__elt__set_t* packet) {
  packet_status("recv_packet__respond__f2simple_array__elt__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2simple_array__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("funk2_node__f2simple_array__elt__set: executing.");
  send_packet__request__f2simple_array__elt__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2simple_array__elt__set_t* packet = (pcs_respond__f2simple_array__elt__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2simple_array__elt__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2simple_array__elt__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, ptr dptr_array) {
  packet_status("send_packet__request__f2traced_array__new: executing.");
  int dptr_array__size = dptr_array ? (sizeof(funk2_dptr_t) * length) : 0;
  pcs_request__f2traced_array__new_t* packet = (pcs_request__f2traced_array__new_t*)alloca(sizeof(pcs_request__f2traced_array__new_t) + dptr_array__size);
  funk2_packet_header__init(&(packet->header), sizeof(packet->payload) + dptr_array__size);
  packet->payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__new;
  packet->payload.action_payload_header.cause               = cause;
  packet->payload.action_payload_header.fiber              = this_fiber;
  packet->payload.length                                    = length;
  packet->payload.dptr_array__defined                       = dptr_array ? boolean__true : boolean__false;
  if (dptr_array) {
    memcpy(packet->payload.dptr_array, from_ptr(dptr_array), dptr_array__size);
  }
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)packet);
}

void recv_packet__request__f2traced_array__new(funk2_node_t* funk2_node, pcs_request__f2traced_array__new_t* packet) {
  packet_status("recv_packet__request__f2traced_array__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  u64   length = packet->payload.length;
  funk2_dptr_t* remote_dptr_array = (funk2_dptr_t*)(packet->payload.dptr_array__defined ? packet->payload.dptr_array : NULL);
  funk2_dptr_t* dptr_array        = NULL;
  if (remote_dptr_array) {
    dptr_array = alloca(sizeof(funk2_dptr_t) * length);
    u64 i;
    for (i = 0; i < length; i ++) {
      f2ptr dptr__p                 = rf2_to_lf2(remote_dptr_array[i].p);
#if defined(F2__USE_TRACED_DPTRS)
      f2ptr dptr__tracing_on        = rf2_to_lf2(remote_dptr_array[i].tracing_on);
      f2ptr dptr__trace             = rf2_to_lf2(remote_dptr_array[i].trace);
      f2ptr dptr__imagination_frame = rf2_to_lf2(remote_dptr_array[i].imagination_frame);
      f2ptr dptr__mutate_funks      = rf2_to_lf2(remote_dptr_array[i].mutate_funks);
      f2ptr dptr__read_funks        = rf2_to_lf2(remote_dptr_array[i].read_funks);
#else
      f2ptr dptr__tracing_on        = nil;
      f2ptr dptr__trace             = nil;
      f2ptr dptr__imagination_frame = nil;
      f2ptr dptr__mutate_funks      = nil;
      f2ptr dptr__read_funks        = nil;
#endif // F2__USE_TRACED_DPTRS
      funk2_dptr__init(&(dptr_array[i]), dptr__p, dptr__tracing_on, dptr__trace, dptr__imagination_frame, dptr__mutate_funks, dptr__read_funks);
    }
  }
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2traced_array__new(cause, packet->payload.length, to_ptr(dptr_array));
  send_packet__respond__f2traced_array__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2traced_array__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2traced_array__new: executing.");
  pcs_respond__f2traced_array__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__new(funk2_node_t* funk2_node, pcs_respond__f2traced_array__new_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, ptr dptr_array) {
  send_packet__request__f2traced_array__new(funk2_node, this_fiber, cause, length, dptr_array);
  pcs_respond__f2traced_array__new_t* packet = (pcs_respond__f2traced_array__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2traced_array__new(f2ptr cause, u64 length, ptr dptr_array) {
  return pfunk2__f2traced_array__new(cause, length, dptr_array);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, f2ptr init_array) {
  packet_status("send_packet__request__f2traced_array__new_copy: executing.");
  pcs_request__f2traced_array__new_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__new_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  packet.payload.init_array                                = init_array;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__new_copy(funk2_node_t* funk2_node, pcs_request__f2traced_array__new_copy_t* packet) {
  packet_status("recv_packet__request__f2traced_array__new_copy: executing.");
  f2ptr cause      = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber     = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr init_array = rf2_to_lf2(packet->payload.init_array);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new_copy = pfunk2__f2traced_array__new_copy(cause, packet->payload.length, init_array);
  send_packet__respond__f2traced_array__new_copy(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new_copy);
}

void send_packet__respond__f2traced_array__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new_copy) {
  packet_status("send_packet__respond__f2traced_array__new_copy: executing.");
  pcs_respond__f2traced_array__new_copy_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__new_copy;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.new_copy                                  = new_copy;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__new_copy(funk2_node_t* funk2_node, pcs_respond__f2traced_array__new_copy_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__new_copy: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__new_copy(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length, f2ptr init_array) {
  send_packet__request__f2traced_array__new_copy(funk2_node, this_fiber, cause, length, init_array);
  pcs_respond__f2traced_array__new_copy_t* packet = (pcs_respond__f2traced_array__new_copy_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new_copy = rf2_to_lf2(packet->payload.new_copy);
  f2__free(to_ptr(packet));
  return new_copy;
}

f2ptr f2traced_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
  return pfunk2__f2traced_array__new_copy(cause, length, init_array);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__immutable(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2traced_array__immutable: executing.");
  pcs_request__f2traced_array__immutable_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__immutable;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__immutable(funk2_node_t* funk2_node, pcs_request__f2traced_array__immutable_t* packet) {
  packet_status("recv_packet__request__f2traced_array__immutable: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u8 immutable = pfunk2__f2traced_array__immutable(this, cause);
  send_packet__respond__f2traced_array__immutable(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, immutable);
}

void send_packet__respond__f2traced_array__immutable(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u8 immutable) {
  packet_status("send_packet__respond__f2traced_array__immutable: executing.");
  pcs_respond__f2traced_array__immutable_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__immutable;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.immutable                                 = immutable;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__immutable(funk2_node_t* funk2_node, pcs_respond__f2traced_array__immutable_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__immutable: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__immutable(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2traced_array__immutable(funk2_node, this_fiber, cause, this);
  pcs_respond__f2traced_array__immutable_t* packet = (pcs_respond__f2traced_array__immutable_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  packet_status("funk2_node__f2traced_array__immutable: packet->payload.immutable = " f2ptr__fstr, packet->payload.immutable);
  f2ptr immutable = rf2_to_lf2(packet->payload.immutable);
  packet_status("funk2_node__f2traced_array__immutable: rf2_to_lf2(packet->payload.immutable) = " f2ptr__fstr, immutable);
  f2__free(to_ptr(packet));
  return immutable;
}

f2ptr f2traced_array__immutable(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__immutable(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__immutable(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u8 value) {
  packet_status("send_packet__request__f2traced_array__immutable__set: executing.");
  pcs_request__f2traced_array__immutable__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__immutable__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__immutable__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__immutable__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__immutable__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  u8    value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__immutable__set(this, cause, value);
  send_packet__respond__f2traced_array__immutable__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__immutable__set: executing.");
  pcs_respond__f2traced_array__immutable__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__immutable__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__immutable__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__immutable__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__immutable__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__immutable__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u8 value) {
  packet_status("funk2_node__f2traced_array__immutable__set: executing.");
  send_packet__request__f2traced_array__immutable__set(funk2_node, this_fiber, cause, this, value);
  pcs_respond__f2traced_array__immutable__set_t* packet = (pcs_respond__f2traced_array__immutable__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__immutable__set(this, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__immutable__set(funk2_node, fiber, cause, this, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2traced_array__length: executing.");
  pcs_request__f2traced_array__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__length(funk2_node_t* funk2_node, pcs_request__f2traced_array__length_t* packet) {
  packet_status("recv_packet__request__f2traced_array__length: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u64 length = pfunk2__f2traced_array__length(this, cause);
  send_packet__respond__f2traced_array__length(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, length);
}

void send_packet__respond__f2traced_array__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u64 length) {
  packet_status("send_packet__respond__f2traced_array__length: executing.");
  pcs_respond__f2traced_array__length_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__length;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.length                                    = length;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__length(funk2_node_t* funk2_node, pcs_respond__f2traced_array__length_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__length: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u64 funk2_node__f2traced_array__length(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2traced_array__length(funk2_node, this_fiber, cause, this);
  pcs_respond__f2traced_array__length_t* packet = (pcs_respond__f2traced_array__length_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u64 length = packet->payload.length;
  f2__free(to_ptr(packet));
  return length;
}

u64 f2traced_array__length(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__length(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__length(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__trace_depth(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u64 trace_depth) {
  packet_status("send_packet__request__f2traced_array__elt__trace_depth: executing.");
  pcs_request__f2traced_array__elt__trace_depth_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__trace_depth;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.trace_depth                               = trace_depth;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__trace_depth(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__trace_depth_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__trace_depth: executing.");
  f2ptr cause       = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber      = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this        = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr elt = pfunk2__f2traced_array__elt__trace_depth(this, packet->payload.index, cause, packet->payload.trace_depth);
  send_packet__respond__f2traced_array__elt__trace_depth(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2traced_array__elt__trace_depth(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr elt) {
  packet_status("send_packet__respond__f2traced_array__elt__trace_depth: executing.");
  pcs_respond__f2traced_array__elt__trace_depth_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__trace_depth;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__trace_depth(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__trace_depth_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__trace_depth: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt__trace_depth(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, u64 trace_depth) {
  send_packet__request__f2traced_array__elt__trace_depth(funk2_node, this_fiber, cause, this, index, trace_depth);
  pcs_respond__f2traced_array__elt__trace_depth_t* packet = (pcs_respond__f2traced_array__elt__trace_depth_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  packet_status("funk2_node__f2traced_array__elt__trace_depth: packet->payload.elt = " f2ptr__fstr, packet->payload.elt);
  f2ptr elt = rf2_to_lf2(packet->payload.elt);
  packet_status("funk2_node__f2traced_array__elt__trace_depth: rf2_to_lf2(packet->payload.elt) = " f2ptr__fstr, elt);
  f2__free(to_ptr(packet));
  return elt;
}

f2ptr f2traced_array__elt__trace_depth(f2ptr this, u64 index, f2ptr cause, u64 trace_depth) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt__trace_depth(this, index, cause, trace_depth);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt__trace_depth(funk2_node, fiber, cause, this, index, trace_depth);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2traced_array__elt: executing.");
  pcs_request__f2traced_array__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr elt = pfunk2__f2traced_array__elt(this, packet->payload.index, cause);
  send_packet__respond__f2traced_array__elt(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, elt);
}

void send_packet__respond__f2traced_array__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr elt) {
  packet_status("send_packet__respond__f2traced_array__elt: executing.");
  pcs_respond__f2traced_array__elt_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.elt                                       = elt;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2traced_array__elt(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2traced_array__elt_t* packet = (pcs_respond__f2traced_array__elt_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  packet_status("funk2_node__f2traced_array__elt: packet->payload.elt = " f2ptr__fstr, packet->payload.elt);
  f2ptr elt = rf2_to_lf2(packet->payload.elt);
  packet_status("funk2_node__f2traced_array__elt: rf2_to_lf2(packet->payload.elt) = " f2ptr__fstr, elt);
  f2__free(to_ptr(packet));
  return elt;
}

f2ptr f2traced_array__elt(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth) {
  packet_status("send_packet__request__f2traced_array__elt__set__trace_depth: executing.");
  pcs_request__f2traced_array__elt__set__trace_depth_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__set__trace_depth;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  packet.payload.trace_depth                               = trace_depth;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__set__trace_depth_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__set__trace_depth: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__set__trace_depth(this, packet->payload.index, cause, value, packet->payload.trace_depth);
  send_packet__respond__f2traced_array__elt__set__trace_depth(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__set__trace_depth: executing.");
  pcs_respond__f2traced_array__elt__set__trace_depth_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__set__trace_depth;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__set__trace_depth_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__set__trace_depth: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__set__trace_depth(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth) {
  send_packet__request__f2traced_array__elt__set__trace_depth(funk2_node, this_fiber, cause, this, index, value, trace_depth);
  pcs_respond__f2traced_array__elt__set__trace_depth_t* packet = (pcs_respond__f2traced_array__elt__set__trace_depth_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__set__trace_depth(f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__set__trace_depth(this, index, cause, value, trace_depth);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__set__trace_depth(funk2_node, fiber, cause, this, index, value, trace_depth);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2traced_array__elt__set: executing.");
  pcs_request__f2traced_array__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2traced_array__elt__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__set: executing.");
  pcs_respond__f2traced_array__elt__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("funk2_node__f2traced_array__elt__set: executing.");
  send_packet__request__f2traced_array__elt__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2traced_array__elt__set_t* packet = (pcs_respond__f2traced_array__elt__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2traced_array__elt__tracing_on: executing.");
  pcs_request__f2traced_array__elt__tracing_on_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__tracing_on_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__tracing_on: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr tracing_on = pfunk2__f2traced_array__elt__tracing_on(this, packet->payload.index, cause);
  send_packet__respond__f2traced_array__elt__tracing_on(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, tracing_on);
}

void send_packet__respond__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr tracing_on) {
  packet_status("send_packet__respond__f2traced_array__elt__tracing_on: executing.");
  pcs_respond__f2traced_array__elt__tracing_on_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__tracing_on;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.tracing_on                                = tracing_on;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__tracing_on_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__tracing_on: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt__tracing_on(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2traced_array__elt__tracing_on(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2traced_array__elt__tracing_on_t* packet = (pcs_respond__f2traced_array__elt__tracing_on_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr tracing_on = rf2_to_lf2(packet->payload.tracing_on);
  f2__free(to_ptr(packet));
  return tracing_on;
}

f2ptr f2traced_array__elt__tracing_on(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt__tracing_on(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt__tracing_on(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2traced_array__elt__tracing_on__set: executing.");
  pcs_request__f2traced_array__elt__tracing_on__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__tracing_on__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__tracing_on__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__tracing_on__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__tracing_on__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2traced_array__elt__tracing_on__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__tracing_on__set: executing.");
  pcs_respond__f2traced_array__elt__tracing_on__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__tracing_on__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__tracing_on__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__tracing_on__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__tracing_on__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  send_packet__request__f2traced_array__elt__tracing_on__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2traced_array__elt__tracing_on__set_t* packet = (pcs_respond__f2traced_array__elt__tracing_on__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__tracing_on__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__tracing_on__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__tracing_on__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__trace(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2traced_array__elt__trace: executing.");
  pcs_request__f2traced_array__elt__trace_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__trace;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__trace(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__trace_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__trace: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr trace = pfunk2__f2traced_array__elt__trace(this, packet->payload.index, cause);
  send_packet__respond__f2traced_array__elt__trace(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, trace);
}

void send_packet__respond__f2traced_array__elt__trace(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr trace) {
  packet_status("send_packet__respond__f2traced_array__elt__trace: executing.");
  pcs_respond__f2traced_array__elt__trace_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__trace;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.trace                                     = trace;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__trace(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__trace_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__trace: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt__trace(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2traced_array__elt__trace(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2traced_array__elt__trace_t* packet = (pcs_respond__f2traced_array__elt__trace_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr trace = rf2_to_lf2(packet->payload.trace);
  f2__free(to_ptr(packet));
  return trace;
}

f2ptr f2traced_array__elt__trace(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt__trace(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt__trace(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2traced_array__elt__trace__set: executing.");
  pcs_request__f2traced_array__elt__trace__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__trace__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__trace__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__trace__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__trace__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2traced_array__elt__trace__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__trace__set: executing.");
  pcs_respond__f2traced_array__elt__trace__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__trace__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__trace__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__trace__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__trace__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  send_packet__request__f2traced_array__elt__trace__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2traced_array__elt__trace__set_t* packet = (pcs_respond__f2traced_array__elt__trace__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__trace__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__trace__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__trace__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2traced_array__elt__imagination_frame: executing.");
  pcs_request__f2traced_array__elt__imagination_frame_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__imagination_frame_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__imagination_frame: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr imagination_frame = pfunk2__f2traced_array__elt__imagination_frame(this, packet->payload.index, cause);
  send_packet__respond__f2traced_array__elt__imagination_frame(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, imagination_frame);
}

void send_packet__respond__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr imagination_frame) {
  packet_status("send_packet__respond__f2traced_array__elt__imagination_frame: executing.");
  pcs_respond__f2traced_array__elt__imagination_frame_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__imagination_frame;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.imagination_frame                         = imagination_frame;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__imagination_frame_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__imagination_frame: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt__imagination_frame(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2traced_array__elt__imagination_frame(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2traced_array__elt__imagination_frame_t* packet = (pcs_respond__f2traced_array__elt__imagination_frame_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr imagination_frame = rf2_to_lf2(packet->payload.imagination_frame);
  f2__free(to_ptr(packet));
  return imagination_frame;
}

f2ptr f2traced_array__elt__imagination_frame(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt__imagination_frame(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt__imagination_frame(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2traced_array__elt__imagination_frame__set: executing.");
  pcs_request__f2traced_array__elt__imagination_frame__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__imagination_frame__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__imagination_frame__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__imagination_frame__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__imagination_frame__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2traced_array__elt__imagination_frame__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__imagination_frame__set: executing.");
  pcs_respond__f2traced_array__elt__imagination_frame__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__imagination_frame__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__imagination_frame__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__imagination_frame__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__imagination_frame__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  send_packet__request__f2traced_array__elt__imagination_frame__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2traced_array__elt__imagination_frame__set_t* packet = (pcs_respond__f2traced_array__elt__imagination_frame__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__imagination_frame__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__imagination_frame__set(this, index, cause, value);
  } else {
    f2ptr         fiber      = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__imagination_frame__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__mutate_funks(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2traced_array__elt__mutate_funks: executing.");
  pcs_request__f2traced_array__elt__mutate_funks_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__mutate_funks;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__mutate_funks(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__mutate_funks_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__mutate_funks: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr mutate_funks = pfunk2__f2traced_array__elt__mutate_funks(this, packet->payload.index, cause);
  send_packet__respond__f2traced_array__elt__mutate_funks(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, mutate_funks);
}

void send_packet__respond__f2traced_array__elt__mutate_funks(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr mutate_funks) {
  packet_status("send_packet__respond__f2traced_array__elt__mutate_funks: executing.");
  pcs_respond__f2traced_array__elt__mutate_funks_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__mutate_funks;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.mutate_funks                         = mutate_funks;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__mutate_funks(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__mutate_funks_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__mutate_funks: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt__mutate_funks(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2traced_array__elt__mutate_funks(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2traced_array__elt__mutate_funks_t* packet = (pcs_respond__f2traced_array__elt__mutate_funks_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr mutate_funks = rf2_to_lf2(packet->payload.mutate_funks);
  f2__free(to_ptr(packet));
  return mutate_funks;
}

f2ptr f2traced_array__elt__mutate_funks(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt__mutate_funks(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt__mutate_funks(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__mutate_funks__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2traced_array__elt__mutate_funks__set: executing.");
  pcs_request__f2traced_array__elt__mutate_funks__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__mutate_funks__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__mutate_funks__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__mutate_funks__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__mutate_funks__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__mutate_funks__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2traced_array__elt__mutate_funks__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__mutate_funks__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__mutate_funks__set: executing.");
  pcs_respond__f2traced_array__elt__mutate_funks__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__mutate_funks__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__mutate_funks__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__mutate_funks__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__mutate_funks__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__mutate_funks__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  send_packet__request__f2traced_array__elt__mutate_funks__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2traced_array__elt__mutate_funks__set_t* packet = (pcs_respond__f2traced_array__elt__mutate_funks__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__mutate_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__mutate_funks__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__mutate_funks__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__read_funks(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  packet_status("send_packet__request__f2traced_array__elt__read_funks: executing.");
  pcs_request__f2traced_array__elt__read_funks_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__read_funks;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__read_funks(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__read_funks_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__read_funks: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr read_funks = pfunk2__f2traced_array__elt__read_funks(this, packet->payload.index, cause);
  send_packet__respond__f2traced_array__elt__read_funks(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, read_funks);
}

void send_packet__respond__f2traced_array__elt__read_funks(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr read_funks) {
  packet_status("send_packet__respond__f2traced_array__elt__read_funks: executing.");
  pcs_respond__f2traced_array__elt__read_funks_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__read_funks;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.read_funks                         = read_funks;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__read_funks(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__read_funks_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__read_funks: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2traced_array__elt__read_funks(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index) {
  send_packet__request__f2traced_array__elt__read_funks(funk2_node, this_fiber, cause, this, index);
  pcs_respond__f2traced_array__elt__read_funks_t* packet = (pcs_respond__f2traced_array__elt__read_funks_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr read_funks = rf2_to_lf2(packet->payload.read_funks);
  f2__free(to_ptr(packet));
  return read_funks;
}

f2ptr f2traced_array__elt__read_funks(f2ptr this, u64 index, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2traced_array__elt__read_funks(this, index, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2traced_array__elt__read_funks(funk2_node, fiber, cause, this, index);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2traced_array__elt__read_funks__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  packet_status("send_packet__request__f2traced_array__elt__read_funks__set: executing.");
  pcs_request__f2traced_array__elt__read_funks__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2traced_array__elt__read_funks__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  packet.payload.index                                     = index;
  packet.payload.value                                     = value;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2traced_array__elt__read_funks__set(funk2_node_t* funk2_node, pcs_request__f2traced_array__elt__read_funks__set_t* packet) {
  packet_status("recv_packet__request__f2traced_array__elt__read_funks__set: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  f2ptr value  = rf2_to_lf2(packet->payload.value);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  pfunk2__f2traced_array__elt__read_funks__set(this, packet->payload.index, cause, value);
  send_packet__respond__f2traced_array__elt__read_funks__set(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause);
}

void send_packet__respond__f2traced_array__elt__read_funks__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause) {
  packet_status("send_packet__respond__f2traced_array__elt__read_funks__set: executing.");
  pcs_respond__f2traced_array__elt__read_funks__set_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2traced_array__elt__read_funks__set;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2traced_array__elt__read_funks__set(funk2_node_t* funk2_node, pcs_respond__f2traced_array__elt__read_funks__set_t* packet) {
  packet_status("recv_packet__respond__f2traced_array__elt__read_funks__set: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

void funk2_node__f2traced_array__elt__read_funks__set(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  send_packet__request__f2traced_array__elt__read_funks__set(funk2_node, this_fiber, cause, this, index, value);
  pcs_respond__f2traced_array__elt__read_funks__set_t* packet = (pcs_respond__f2traced_array__elt__read_funks__set_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2__free(to_ptr(packet));
}

void f2traced_array__elt__read_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    pfunk2__f2traced_array__elt__read_funks__set(this, index, cause, value);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    funk2_node__f2traced_array__elt__read_funks__set(funk2_node, fiber, cause, this, index, value);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2larva__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u32 larva_type, f2ptr bug) {
  packet_status("send_packet__request__f2larva__new: executing.");
  pcs_request__f2larva__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2larva__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.larva_type                                = larva_type;
  packet.payload.bug                                       = bug;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2larva__new(funk2_node_t* funk2_node, pcs_request__f2larva__new_t* packet) {
  packet_status("recv_packet__request__f2larva__new: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr new = pfunk2__f2larva__new(cause, packet->payload.larva_type, packet->payload.bug);
  send_packet__respond__f2larva__new(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, new);
}

void send_packet__respond__f2larva__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr new) {
  packet_status("send_packet__respond__f2larva__new: executing.");
  pcs_respond__f2larva__new_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2larva__new;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.new                                       = new;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2larva__new(funk2_node_t* funk2_node, pcs_respond__f2larva__new_t* packet) {
  packet_status("recv_packet__respond__f2larva__new: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2larva__new(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u32 larva_type, f2ptr bug) {
  send_packet__request__f2larva__new(funk2_node, this_fiber, cause, larva_type, bug);
  pcs_respond__f2larva__new_t* packet = (pcs_respond__f2larva__new_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr new = rf2_to_lf2(packet->payload.new);
  f2__free(to_ptr(packet));
  return new;
}

f2ptr f2larva__new(f2ptr cause, u32 type, f2ptr bug) {
  return pfunk2__f2larva__new(cause, type, bug);
}

// ******************************************************
// * 
// * 

void send_packet__request__f2larva__larva_type(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2larva__larva_type: executing.");
  pcs_request__f2larva__larva_type_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2larva__larva_type;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2larva__larva_type(funk2_node_t* funk2_node, pcs_request__f2larva__larva_type_t* packet) {
  packet_status("recv_packet__request__f2larva__larva_type: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  u32 type = pfunk2__f2larva__larva_type(this, cause);
  send_packet__respond__f2larva__larva_type(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, type);
}

void send_packet__respond__f2larva__larva_type(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, u32 larva_type) {
  packet_status("send_packet__respond__f2larva__larva_type: executing.");
  pcs_respond__f2larva__larva_type_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2larva__larva_type;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.larva_type                                = larva_type;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2larva__larva_type(funk2_node_t* funk2_node, pcs_respond__f2larva__larva_type_t* packet) {
  packet_status("recv_packet__respond__f2larva__larva_type: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

u32 funk2_node__f2larva__larva_type(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2larva__larva_type(funk2_node, this_fiber, cause, this);
  pcs_respond__f2larva__larva_type_t* packet = (pcs_respond__f2larva__larva_type_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  u32 larva_type = packet->payload.larva_type;
  f2__free(to_ptr(packet));
  return larva_type;
}

u32 f2larva__larva_type(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2larva__larva_type(this, cause);
  } else {
    f2ptr         fiber     = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2larva__larva_type(funk2_node, fiber, cause, this);
  }
}

// ******************************************************
// * 
// * 

void send_packet__request__f2larva__bug(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  packet_status("send_packet__request__f2larva__bug: executing.");
  pcs_request__f2larva__bug_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_request__f2larva__bug;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber              = this_fiber;
  packet.payload.this                                      = this;
  funk2_node__send_packet(cause, funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__request__f2larva__bug(funk2_node_t* funk2_node, pcs_request__f2larva__bug_t* packet) {
  packet_status("recv_packet__request__f2larva__bug: executing.");
  f2ptr cause  = rf2_to_lf2(packet->payload.action_payload_header.cause);
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  f2ptr this   = rf2_to_lf2(packet->payload.this);
  funk2_node_handler__add_remote_fiber_funk2_node(&(__funk2.node_handler), fiber, funk2_node);
  f2ptr bug = pfunk2__f2larva__bug(this, cause);
  send_packet__respond__f2larva__bug(funk2_node_handler__lookup_fiber_execution_node(&(__funk2.node_handler), fiber), fiber, cause, bug);
}

void send_packet__respond__f2larva__bug(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr bug) {
  packet_status("send_packet__respond__f2larva__bug: executing.");
  pcs_respond__f2larva__bug_t packet;
  funk2_packet_header__init(&(packet.header), sizeof(packet.payload));
  packet.payload.action_payload_header.payload_header.type = funk2_packet_type__pcs_respond__f2larva__bug;
  packet.payload.action_payload_header.cause               = cause;
  packet.payload.action_payload_header.fiber               = this_fiber;
  packet.payload.bug                                       = bug;
  socket_rpc_layer__funk2_node__send_packet(funk2_node, (funk2_packet_t*)&packet);
}

void recv_packet__respond__f2larva__bug(funk2_node_t* funk2_node, pcs_respond__f2larva__bug_t* packet) {
  packet_status("recv_packet__respond__f2larva__bug: executing.");
  f2ptr fiber = rf2_to_lf2(packet->payload.action_payload_header.fiber);
  funk2_node_handler__report_fiber_response_packet(&(__funk2.node_handler), fiber, (funk2_packet_t*)packet);
}

f2ptr funk2_node__f2larva__bug(funk2_node_t* funk2_node, f2ptr this_fiber, f2ptr cause, f2ptr this) {
  send_packet__request__f2larva__bug(funk2_node, this_fiber, cause, this);
  pcs_respond__f2larva__bug_t* packet = (pcs_respond__f2larva__bug_t*)funk2_node_handler__wait_for_new_fiber_packet(&(__funk2.node_handler), this_fiber);
  f2ptr bug = packet->payload.bug;
  f2__free(to_ptr(packet));
  return bug;
}

f2ptr f2larva__bug(f2ptr this, f2ptr cause) {
  computer_id_t computer_id = __f2ptr__computer_id(this);
  if (computer_id == 0) {
    return pfunk2__f2larva__bug(this, cause);
  } else {
    f2ptr         fiber      = raw__global_scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
    funk2_node_t* funk2_node = funk2_node_handler__lookup_node_by_computer_id(&(__funk2.node_handler), computer_id);
    return funk2_node__f2larva__bug(funk2_node, fiber, cause, this);
  }
}


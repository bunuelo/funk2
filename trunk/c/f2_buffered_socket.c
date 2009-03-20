#include "funk2.h"

void buffered_socket__init(buffered_socket_t* this, int socket_fd, u32 recv_buffer__byte_num, u32 send_buffer__byte_num) {
  this->socket_fd    = socket_fd;
  this->disconnected = boolean__false;
  circular_buffer__init(&(this->recv_buffer), recv_buffer__byte_num);
  circular_buffer__init(&(this->send_buffer), send_buffer__byte_num);
}

void buffered_socket__destroy(buffered_socket_t* this) {
  circular_buffer__destroy(&(this->recv_buffer));
  circular_buffer__destroy(&(this->send_buffer));
}

buffered_socket__error_type_t buffered_socket__flush(buffered_socket_t* this) {
  if (this->socket_fd != -1) {
    if (! this->disconnected) {
      circular_buffer__socket_recv_result_t recv_result = circular_buffer__socket_recv(&(this->recv_buffer), this->socket_fd);
      switch(recv_result) {
      case circular_buffer__socket_recv_result__disconnected:
	status("buffered_socket__flush error: disconnected on recv!");
	this->disconnected = boolean__true;
	return buffered_socket__error_type__disconnected;
      case circular_buffer__socket_recv_result__connected:
	break;
      }
      if (! this->disconnected) {
	circular_buffer__socket_send_result_t send_result = circular_buffer__socket_send(&(this->send_buffer), this->socket_fd);
	switch(send_result) {
	case circular_buffer__socket_send_result__disconnected:
	  status("buffered_socket__flush error: disconnected on send!");
	  this->disconnected = boolean__true;
	  return buffered_socket__error_type__disconnected;
	case circular_buffer__socket_send_result__connected:
	  break;
	}
      }
    }
  }
  return buffered_socket__error_type__success;
}

circular_buffer__write_result_t buffered_socket__send(buffered_socket_t* this, void* data, u32 byte_num) {
  return circular_buffer__write(&(this->send_buffer), data, byte_num);
}

void buffered_socket__seek_ahead(buffered_socket_t* this, u32 byte_num) {
  circular_buffer__seek_ahead(&(this->recv_buffer), byte_num, NULL);
}

circular_buffer__read_result_t buffered_socket__peek_recv(buffered_socket_t* this, void* data, u32 byte_num) {
  return circular_buffer__peek_read(&(this->recv_buffer), data, byte_num, NULL);
}

circular_buffer__read_result_t buffered_socket__recv(buffered_socket_t* this, void* data, u32 byte_num) {
  return circular_buffer__read(&(this->recv_buffer), data, byte_num);
}

u32 buffered_socket__recv_bytes_free(buffered_socket_t* this) {
  return circular_buffer__get_free_byte_num(&(this->recv_buffer));
}

u32 buffered_socket__recv_bytes_buffered(buffered_socket_t* this) {
  return circular_buffer__get_used_byte_num(&(this->recv_buffer));
}

u32 buffered_socket__send_bytes_free(buffered_socket_t* this) {
  return circular_buffer__get_free_byte_num(&(this->send_buffer));
}

u32 buffered_socket__send_bytes_buffered(buffered_socket_t* this) {
  return circular_buffer__get_used_byte_num(&(this->send_buffer));
}


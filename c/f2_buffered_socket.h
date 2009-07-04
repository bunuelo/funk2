#ifndef F2__BUFFERED_SOCKET__H
#define F2__BUFFERED_SOCKET__H

#include "f2_circular_buffer.h"

typedef struct buffered_socket_s {
  int               socket_fd;
  boolean_t         disconnected;
  circular_buffer_t recv_buffer;
  circular_buffer_t send_buffer;
} buffered_socket_t;

typedef enum buffered_socket__error_type_e {
  buffered_socket__error_type__success,
  buffered_socket__error_type__disconnected,
} buffered_socket__error_type_t;

void                            buffered_socket__init(buffered_socket_t* this, int socket_fd, u32 recv_buffer__byte_num, u32 send_buffer__byte_num);
void                            buffered_socket__destroy(buffered_socket_t* this);
buffered_socket__error_type_t   buffered_socket__flush(buffered_socket_t* this);
circular_buffer__write_result_t buffered_socket__send(buffered_socket_t* this, void* data, u32 byte_num);
void                            buffered_socket__seek_ahead(buffered_socket_t* this, u32 byte_num);
circular_buffer__read_result_t  buffered_socket__peek_recv(buffered_socket_t* this, void* data, u32 byte_num);
circular_buffer__read_result_t  buffered_socket__recv(buffered_socket_t* this, void* data, u32 byte_num);
u32                             buffered_socket__recv_bytes_buffered(buffered_socket_t* this);
u32                             buffered_socket__recv_bytes_free(buffered_socket_t* this);
u32                             buffered_socket__send_bytes_buffered(buffered_socket_t* this);
u32                             buffered_socket__send_bytes_free(buffered_socket_t* this);

#endif // F2__BUFFERED_SOCKET__H

#ifndef F2__SOCKET_CLIENT__H
#define F2__SOCKET_CLIENT__H

#include "f2_global.h"
#include "f2_buffered_socket.h"
#include "f2_socket_server.h"

typedef struct socket_client_s {
  client_id_t       client_id;
  char*             bind_device;
  char*             hostname;
  int               port_num;
  buffered_socket_t socket;
} socket_client_t;

typedef enum socket_client_connect_result_e {
  socket_client_connect_result__success = 0,
  socket_client_connect_result__gethostbyname_failure,
  socket_client_connect_result__socket_failure,
  socket_client_connect_result__connect_failure
} socket_client_connect_result_t;

void                           socket_client__init(socket_client_t* this, char* bind_device, char* hostname, int port_num, u32 recv_buffer_byte_num, u32 send_buffer_byte_num);
void                           socket_client__destroy(socket_client_t* this);
socket_client_connect_result_t socket_client__try_reconnect(socket_client_t* this);

#endif // F2__SOCKET_CLIENT__H


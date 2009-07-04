#ifndef F2__SOCKET_SERVER__H
#define F2__SOCKET_SERVER__H

#include "f2_buffered_socket.h"

int file_descriptor__set_nonblocking(int fd, boolean_t value);

int socket_file_descriptor__get_keepalive(int fd);
int socket_file_descriptor__set_keepalive(int fd, boolean_t keepalive);

struct client_id_s {
  u8  bind_device[16]; // e.g. "eth0"
  u8  ip_addr[4];
  u16 port_num;
} __attribute__((__packed__));
typedef struct client_id_s client_id_t;

void         client_id__init(client_id_t* this, u8* bind_device, u8* ip_addr, u16 port_num);
client_id_t* client_id__new(u8* bind_device, u8* ip_addr, u16 port_num);
void         client_id__copy(client_id_t* this, client_id_t* client_id);
client_id_t* client_id__new_copy(client_id_t* client_id);
boolean_t    client_id__equals(client_id_t* this, client_id_t* client_id);

typedef struct socket_server_client_s {
  buffered_socket_t socket;
  client_id_t       client_id;
  void*             data; // for super-class use (set to NULL initially and then ignored) [note: should add destroy callback to avoid memory leaks]
} socket_server_client_t;

void socket_server_client__init(socket_server_client_t* this, int socket_fd, u32 recv_buffer__byte_num, u32 send_buffer__byte_num, client_id_t* client_id);
void socket_server_client__destroy(socket_server_client_t* this);

typedef struct socket_server_client_list_s {
  socket_server_client_t              client;
  struct socket_server_client_list_s* next;
} socket_server_client_list_t;

typedef struct socket_server_s {
  int                          socket_fd;
  client_id_t                  client_id;
  int                          client__recv_buffer__byte_num;
  int                          client__send_buffer__byte_num;
  socket_server_client_list_t* clients;
} socket_server_t;

typedef struct socket_server_list_s {
  socket_server_t               socket_server;
  struct socket_server_list_s* next;
} socket_server_list_t;

typedef enum socket_server_init_result_e {
  socket_server_init_result__success = 0,
  socket_server_init_result__socket_failure,
  socket_server_init_result__bind_failure,
  socket_server_init_result__bind_device_failure
} socket_server_init_result_t;

socket_server_init_result_t socket_server__init(socket_server_t* this, char* bind_device, u8* ip_addr, u16 port_num, u32 client__recv_buffer__byte_num, u32 client__send_buffer__byte_num);
int                         socket_server__accept(socket_server_t* this, client_id_t* client_id);
void                        socket_server__destroy(socket_server_t* this);
void                        socket_server__accept_new_clients(socket_server_t* this);
void                        socket_server__remove_dead_clients(socket_server_t* this);

#endif // F2__SOCKET_SERVER__H

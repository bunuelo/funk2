#include "funk2.h"

void socket_client__init(socket_client_t* this, char* bind_device, char* hostname, int port_num, u32 recv_buffer_byte_num, u32 send_buffer_byte_num) {
  int bind_device__length = strlen(bind_device);
  this->bind_device = (char*)from_ptr(f2__malloc(bind_device__length + 1));
  memcpy(this->bind_device, bind_device, bind_device__length + 1);
  
  int hostname__length = strlen(hostname);
  this->hostname = (char*)from_ptr(f2__malloc(hostname__length + 1));
  memcpy(this->hostname, hostname, hostname__length + 1);
  
  this->port_num = port_num;
  
  int socket_fd = -1;
  buffered_socket__init(&(this->socket), socket_fd, recv_buffer_byte_num, send_buffer_byte_num);
  this->socket.disconnected = boolean__true;
}

void socket_client__destroy(socket_client_t* this) {
  f2__free(to_ptr(this->bind_device));
  f2__free(to_ptr(this->hostname));
  shutdown(this->socket.socket_fd, SHUT_RDWR);
  close(this->socket.socket_fd);
  buffered_socket__destroy(&(this->socket));
}

void socket_client__close_connection(socket_client_t* this) {
  if (this->socket.socket_fd != -1) {
    close(this->socket.socket_fd);
    this->socket.socket_fd = -1;
  }
}

socket_client_connect_result_t socket_client__try_reconnect(socket_client_t* this) {
  struct sockaddr_in server_address;
  struct hostent*    host_info;
  
  socket_client__close_connection(this);
  
  host_info = gethostbyname(this->hostname);
  if (host_info == NULL) {
    status("handle_client(%s, %d): problem interpreting host", this->hostname, this->port_num);
    return socket_client_connect_result__gethostbyname_failure;
  }
  
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    status("handle_client(%s, %d): cannot create socket", this->hostname, this->port_num);
    return socket_client_connect_result__socket_failure;
  }
  
  file_descriptor__set_nonblocking(socket_fd, boolean__true);
  
  if (socket_file_descriptor__set_keepalive(socket_fd, boolean__true) < 0) {
    printf("\nsocket_server__accept error: cannot create set keepalive on socket");
    return socket_client_connect_result__socket_failure;
  }
  
  server_address.sin_family = host_info->h_addrtype;
  memcpy((char *) &server_address.sin_addr.s_addr, host_info->h_addr_list[0], host_info->h_length);
  server_address.sin_port = htons(this->port_num);
  
  char* bind_device   = (char*)(this->client_id.bind_device);
  u32   ip_addr__long = ntohl(server_address.sin_addr.s_addr);
  u8 ip_addr[4];
  ip_addr[0] = ((u8*)&ip_addr__long)[3];
  ip_addr[1] = ((u8*)&ip_addr__long)[2];
  ip_addr[2] = ((u8*)&ip_addr__long)[1];
  ip_addr[3] = ((u8*)&ip_addr__long)[0];
  u16   port_num      = ntohs(server_address.sin_port);
  client_id__init(&(this->client_id), (u8*)bind_device, ip_addr, port_num);
  
  //{
  //  char client_id_str[128];
  //  snprintf(client_id_str, 128, "([%s] %s:%d)", bind_device, inet_ntoa(server_address.sin_addr), port_num);
  //  status("%-45s  connected socket on socket_fd=%d.  ip_addr={%d %d %d %d}", client_id_str, socket_fd, ((u8*)&ip_addr)[3], ((u8*)&ip_addr)[2], ((u8*)&ip_addr)[1], ((u8*)&ip_addr)[0]);
  //}
  
  int connect_result = connect(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address));
  if (connect_result == -1 && !(connect_result == -1 && errno == EINPROGRESS)) {
    status("handle_client(%s, %d): cannot connect", this->hostname, this->port_num);
    return socket_client_connect_result__connect_failure;
  }
  
  this->socket.socket_fd    = socket_fd;
  this->socket.disconnected = boolean__false;
  
  return socket_client_connect_result__success;
}


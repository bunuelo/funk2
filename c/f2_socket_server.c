#include "funk2.h"

void client_id__bind_device__set(client_id_t* this, u8* bind_device) {
  memset(this->bind_device, 0, 16);
  if (this->bind_device != bind_device) {
    strncpy((char*)this->bind_device, (char*)bind_device, 16);
  }
  this->bind_device[15] = 0;
}

void client_id__init(client_id_t* this, u8* bind_device, u8* ip_addr, u16 port_num) {
  client_id__bind_device__set(this, bind_device);
  this->ip_addr[0] = ip_addr[0];
  this->ip_addr[1] = ip_addr[1];
  this->ip_addr[2] = ip_addr[2];
  this->ip_addr[3] = ip_addr[3];
  this->port_num   = port_num;
}

client_id_t* client_id__new(u8* bind_device, u8* ip_addr, u16 port_num) {
  client_id_t* this = (client_id_t*)from_ptr(f2__malloc(sizeof(client_id_t)));
  client_id__init(this, bind_device, ip_addr, port_num);
  return this;
}

void client_id__copy(client_id_t* this, client_id_t* client_id) {
  memcpy(this, client_id, sizeof(client_id_t));
}

client_id_t* client_id__new_copy(client_id_t* client_id) {
  client_id_t* this = (client_id_t*)from_ptr(f2__malloc(sizeof(client_id_t)));
  client_id__copy(this, client_id);
  return this;
}

boolean_t client_id__equals(client_id_t* this, client_id_t* client_id) {
  return (memcmp(this, client_id, sizeof(client_id_t)) == 0);
}

int file_descriptor__set_nonblocking(int fd, boolean_t value) {
  int flags;
  // If they have O_NONBLOCK, use the Posix way to do it
#if defined(O_NONBLOCK)
  // Fixme: O_NONBLOCK is defined but broken on SunOS 4.1.x and AIX 3.2.5.
  if (-1 == (flags = fcntl(fd, F_GETFL, 0))) {
    flags = 0;
  }
  if (value) {
    flags = flags | O_NONBLOCK;
  } else {
    flags = flags & (~ O_NONBLOCK);
  }
  return fcntl(fd, F_SETFL, flags);
#else
  // Otherwise, use the old way of doing it
  flags = value ? 1 : 0;
  return ioctl(fd, FIOBIO, &flags);
#endif
}

int socket_file_descriptor__set_bind_device(int fd, char* device) {
#if defined(SO_BINDTODEVICE)
  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  strncpy(ifr.ifr_ifrn.ifrn_name, device, IFNAMSIZ);
  if(setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, sizeof(ifr))) {
    status("can't bind to interface [%s]: %s", device, strerror(errno));
    if (errno == EPERM) {
      status("funk2: Make sure you are root!");
    }
    return -1;
  }
  return 0;
#else
  // Fixme: implement binding on OS X
	status("socket_file_descriptor__set_bind_device() not supported on this platform.");
	return -1;
#endif
}

int socket_file_descriptor__get_bind_device(int fd, char* device_name, int max_len) {
#if defined(SO_BINDTODEVICE)
  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  socklen_t socklen;
  if (max_len > 0) {
    device_name[0] = 0;
  }
  if(getsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, &ifr, &socklen)) {
    status("socket_file_descriptor__get_bind_device error: can't get interface: %s", strerror(errno));
    if (errno == EPERM) {
      status("funk2: Make sure you are root!");
    }
    return -1;
  }
  if (socklen != sizeof(ifr)) {
    status("socket_file_descriptor__get_bind_device error: socklen != sizeof(ifr)");
    return -1;
  }
  memset(device_name, 0, max_len);
  strncpy(device_name, ifr.ifr_ifrn.ifrn_name, max_len < IFNAMSIZ ? max_len : IFNAMSIZ);
  return 0;
#else
  // Fixme: implement binding on OS X
	status("socket_file_descriptor__get_bind_device() not supported on this platform.");
	return -1;
#endif
}

void socket_file_descriptor__set_rebindable(int fd) {
  int reuse_addr = 1;
  // So that we can re-bind to it without TIME_WAIT problems
  setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse_addr, sizeof(reuse_addr));
}

int socket_file_descriptor__get_keepalive(int fd) {
  int       optval;
  socklen_t optlen = sizeof(optval);
  /* Check the status for the keepalive option */
  if(getsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
    perror("getsockopt()");
    return -1;
  }
  return optval;
}

int socket_file_descriptor__set_keepalive(int fd, boolean_t keepalive) {
  int       optval;
  socklen_t optlen = sizeof(optval);
  /* Set the option active */
  optval = keepalive ? 1 : 0;
  if(setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
    perror("setsockopt()");
    return -1;
  }
  return 0;
}

socket_server_init_result_t socket_server__init(socket_server_t* this, char* bind_device, u8* ip_addr, u16 port_num, u32 client__recv_buffer__byte_num, u32 client__send_buffer__byte_num) {
  struct sockaddr_in server_address;
  
  this->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->socket_fd < 0) {
    status("socket_server__init error: cannot create listen socket");
    return socket_server_init_result__socket_failure;
  }
  
  file_descriptor__set_nonblocking(this->socket_fd, boolean__true);
  socket_file_descriptor__set_rebindable(this->socket_fd);
  if (socket_file_descriptor__set_keepalive(this->socket_fd, boolean__true) < 0) {
    status("socket_server__init error: cannot create set keepalive on socket");
    return socket_server_init_result__socket_failure;
  }
  
  if (bind_device != NULL && bind_device[0] != 0) {
    if (socket_file_descriptor__set_bind_device(this->socket_fd, bind_device)) {
      return socket_server_init_result__bind_device_failure;
    }
  }
  
  server_address.sin_family      = AF_INET;
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);
  server_address.sin_port        = htons(port_num);
  
  if (bind(this->socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
    status("socket_server__init error: cannot bind socket");
    return socket_server_init_result__bind_failure;
  }
  
  listen(this->socket_fd, 5); // non-blocking call
  
  u8 client_id__ip_addr[4];
  if (ip_addr) {
    client_id__ip_addr[0] = ip_addr[0];
    client_id__ip_addr[1] = ip_addr[1];
    client_id__ip_addr[2] = ip_addr[2];
    client_id__ip_addr[3] = ip_addr[3];
  } else {
    client_id__ip_addr[0] = 127;
    client_id__ip_addr[1] = 0;
    client_id__ip_addr[2] = 0;
    client_id__ip_addr[3] = 1;
  }
  client_id__init(&(this->client_id), (u8*)(bind_device ? bind_device : ""), (u8*)client_id__ip_addr, port_num);
  
  this->client__recv_buffer__byte_num = client__recv_buffer__byte_num;
  this->client__send_buffer__byte_num = client__send_buffer__byte_num;
  this->clients                       = NULL;
  
  return socket_server_init_result__success;
}

void socket_server__destroy(socket_server_t* this) {
  status("socket_server__destroy: destroying all socket server clients.", this->socket_fd);
  socket_server_client_list_t* iter = this->clients;
  while (iter) {
    socket_server_client_list_t* next   = iter->next;
    socket_server_client_t*      client = &(iter->client);
    socket_server_client__destroy(client);
    f2__free(to_ptr(iter));
    iter = next;
  }
  status("socket_server__destroy: closing socket server socket_fd=%d", this->socket_fd);
  close(this->socket_fd);
}

int socket_server__accept(socket_server_t* this, client_id_t* client_id) {
  socklen_t          client_address_length;
  struct sockaddr_in client_address;
  int                connect_socket_fd;
  
  client_address_length = sizeof(client_address);
  connect_socket_fd = accept(this->socket_fd, (struct sockaddr *) &client_address, &client_address_length); // blocking call
  if (connect_socket_fd < 0) {
    return -1;
  }
  
  if (socket_file_descriptor__set_keepalive(connect_socket_fd, boolean__true) < 0) {
    status("\nsocket_server__accept error: cannot create set keepalive on socket");
    return -1;
  }
  file_descriptor__set_nonblocking(connect_socket_fd, boolean__true);
  
  u32 ip_addr__long  = ntohl(client_address.sin_addr.s_addr);
  u8  ip_addr[4];
  ip_addr[0] = ((u8*)&ip_addr__long)[3];
  ip_addr[1] = ((u8*)&ip_addr__long)[2];
  ip_addr[2] = ((u8*)&ip_addr__long)[1];
  ip_addr[3] = ((u8*)&ip_addr__long)[0];
  u16 port_num = ntohs(client_address.sin_port);
  
  char* bind_device = (char*)(this->client_id.bind_device);
  char client_id_str[128];
  snprintf(client_id_str, 128, "([%s] %s:%d)", bind_device, inet_ntoa(client_address.sin_addr), port_num);
  status("%-45s  connected socket on socket_fd=%d.  ip_addr={%d %d %d %d}", client_id_str, connect_socket_fd, ip_addr[0], ip_addr[1], ip_addr[2], ip_addr[3]);
  if (client_id) {
    client_id__init(client_id, (u8*)bind_device, ip_addr, port_num);
  }
  return connect_socket_fd;
}

void socket_server_client__init(socket_server_client_t* this, int socket_fd, u32 recv_buffer__byte_num, u32 send_buffer__byte_num, client_id_t* client_id) {
  buffered_socket__init(&(this->socket), socket_fd, recv_buffer__byte_num, send_buffer__byte_num);
  client_id__copy(&(this->client_id), client_id);
  this->data                   = NULL; // user sets this (we just set to NULL initially and then ignore)
  this->data__destroy_and_free = NULL; // user sets this (we just set to NULL and call with data as argument at destroy if non-null)
}

void socket_server_client__destroy(socket_server_client_t* this) {
  buffered_socket__destroy(&(this->socket));
  close(this->socket.socket_fd);
  client_id_t* client_id = &(this->client_id);
  char client_id_str[128];
  snprintf(client_id_str, 128, "([%s] %d.%d.%d.%d:%d)", client_id->bind_device, client_id->ip_addr[0], client_id->ip_addr[1], client_id->ip_addr[2], client_id->ip_addr[3], client_id->port_num);
  status("%-45s  closing socket on socket_fd=%d.", client_id_str, this->socket.socket_fd);
  if (this->data) {
    if (this->data__destroy_and_free) {
      (*(this->data__destroy_and_free))(this->data);
    } else {
      status("socket_server_client__destroy WARNING: data is non-null and data__destroy_and_free is null.  This is a memory leak!");
    }
  }
}

void socket_server__accept_new_clients(socket_server_t* this) {
  client_id_t client_id;
  int         socket_fd = socket_server__accept(this, &client_id);
  if (socket_fd != -1) {
    socket_server_client_list_t* client_node = (socket_server_client_list_t*)from_ptr(f2__malloc(sizeof(socket_server_client_list_t)));
    client_id__bind_device__set(&client_id, this->client_id.bind_device);
    socket_server_client__init(&(client_node->client), socket_fd, this->client__recv_buffer__byte_num, this->client__send_buffer__byte_num, &client_id);
    client_node->next = this->clients;
    this->clients = client_node;
  }
}

void socket_server__remove_dead_clients(socket_server_t* this) {
  socket_server_client_list_t* prev = NULL;
  socket_server_client_list_t* iter = this->clients;
  while (iter) {
    socket_server_client_list_t* next   = iter->next;
    socket_server_client_t*      client = &(iter->client);
    if (client->socket.disconnected && buffered_socket__recv_bytes_buffered(&(client->socket)) == 0 && client->data == NULL) {
      if (prev) {
	prev->next    = iter->next;
      } else {
	this->clients = iter->next;
      }
      socket_server_client__destroy(client);
      f2__free(to_ptr(iter));
    }
    iter = next;
  }
}

/*

packet

(u8) 0x6D
(u8) 'w'/'W'
(u32) time
(u8) time_frac
(u16) node_addr
(u8) length
payload
(u8) 10
(u8) 13


payload
(u8) type
datas



*/

/*

    // Read lines from socket, using recv(), storing them in the line
    // array.  If no messages are currently available, recv() blocks
    // until one arrives.
    // First set line to all zeroes, so we'll know where the end of
    // the string is.
    memset(line, 0x0, LINE_ARRAY_SIZE);
    while (recv(connectSocket, line, MAX_MSG, 0) > 0) {
      cout << "  --  " << line << "\n";

      // Convert line to upper case.
      for (i = 0; line[i] != '\0'; i++)
        line[i] = toupper(line[i]);

      // Send converted line back to client.
      if (send(connectSocket, line, strlen(line) + 1, 0) < 0)
        cerr << "Error: cannot send modified data";

      memset(line, 0x0, LINE_ARRAY_SIZE);  // set line to all zeroes
    }

*/

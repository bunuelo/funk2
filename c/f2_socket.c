// 
// Copyright (c) 2007-2010 Bo Morgan.
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

f2ptr f2__socket__pf_unix(f2ptr cause) {return f2integer__new(cause, PF_UNIX);}
def_pcfunk0(f2__socket__pf_unix,      return f2__socket__pf_unix(this_cause));

f2ptr f2__socket__pf_local(f2ptr cause) {return f2integer__new(cause, PF_LOCAL);}
def_pcfunk0(f2__socket__pf_local,     return f2__socket__pf_local(this_cause));

f2ptr f2__socket__pf_inet(f2ptr cause) {return f2integer__new(cause, PF_INET);}
def_pcfunk0(f2__socket__pf_inet,      return f2__socket__pf_inet(this_cause));

f2ptr f2__socket__pf_inet6(f2ptr cause) {return f2integer__new(cause, PF_INET6);}
def_pcfunk0(f2__socket__pf_inet6,     return f2__socket__pf_inet6(this_cause));

#ifndef F2__CYGWIN
f2ptr f2__socket__pf_ipx(f2ptr cause) {	return f2integer__new(cause, PF_IPX);}
def_pcfunk0(f2__socket__pf_ipx,       return f2__socket__pf_ipx(this_cause));
#endif

#if (! defined(F2__CYGWIN)) && (! defined(F2__APPLE))
f2ptr f2__socket__pf_netlink(f2ptr cause) {return f2integer__new(cause, PF_NETLINK);}
def_pcfunk0(f2__socket__pf_netlink,   return f2__socket__pf_netlink(this_cause));

f2ptr f2__socket__pf_x25(f2ptr cause) {return f2integer__new(cause, PF_X25);}
def_pcfunk0(f2__socket__pf_x25,       return f2__socket__pf_x25(this_cause));

f2ptr f2__socket__pf_ax25(f2ptr cause) {return f2integer__new(cause, PF_AX25);}
def_pcfunk0(f2__socket__pf_ax25,      return f2__socket__pf_ax25(this_cause));

f2ptr f2__socket__pf_atmpvc(f2ptr cause) {return f2integer__new(cause, PF_ATMPVC);}
def_pcfunk0(f2__socket__pf_atmpvc,    return f2__socket__pf_atmpvc(this_cause));

f2ptr f2__socket__pf_packet(f2ptr cause) {return f2integer__new(cause, PF_PACKET);}
def_pcfunk0(f2__socket__pf_packet,    return f2__socket__pf_packet(this_cause));

f2ptr f2__socket__sock_packet(f2ptr cause) {return f2integer__new(cause, SOCK_PACKET);}
def_pcfunk0(f2__socket__sock_packet,    return f2__socket__sock_packet(this_cause));
#endif

f2ptr f2__socket__pf_appletalk(f2ptr cause) {return f2integer__new(cause, PF_APPLETALK);}
def_pcfunk0(f2__socket__pf_appletalk, return f2__socket__pf_appletalk(this_cause));

f2ptr f2__socket__sock_stream(f2ptr cause) {return f2integer__new(cause, SOCK_STREAM);}
def_pcfunk0(f2__socket__sock_stream,    return f2__socket__sock_stream(this_cause));

f2ptr f2__socket__sock_dgram(f2ptr cause) {return f2integer__new(cause, SOCK_DGRAM);}
def_pcfunk0(f2__socket__sock_dgram,     return f2__socket__sock_dgram(this_cause));

f2ptr f2__socket__sock_seqpacket(f2ptr cause) {return f2integer__new(cause, SOCK_SEQPACKET);}
def_pcfunk0(f2__socket__sock_seqpacket, return f2__socket__sock_seqpacket(this_cause));

f2ptr f2__socket__sock_raw(f2ptr cause) {return f2integer__new(cause, SOCK_RAW);}
def_pcfunk0(f2__socket__sock_raw,       return f2__socket__sock_raw(this_cause));

f2ptr f2__socket__sock_rdm(f2ptr cause) {return f2integer__new(cause, SOCK_RDM);}
def_pcfunk0(f2__socket__sock_rdm,       return f2__socket__sock_rdm(this_cause));


f2ptr f2__inaddr_any(f2ptr cause) {
  int sockaddr_len = sizeof(struct sockaddr);
  f2ptr this = raw__array__new(cause, sockaddr_len);
  struct sockaddr_in addr_in;
  addr_in.sin_addr.s_addr = htonl(INADDR_ANY);
  char* bytes = (char*)(&(addr_in.sin_addr.s_addr));
  int i;
  for (i = 0; i < sockaddr_len; i ++) {
    raw__array__elt__set(cause, this, i, f2integer__new(cause, (unsigned char)(bytes[i])));
  }
  return this;
}
def_pcfunk0(f2__inaddr_any, return f2__inaddr_any(this_cause));

// int socket(int domain, int type, int protocol);
f2ptr raw__socket(f2ptr cause, f2ptr domain, f2ptr type, f2ptr protocol) {
  s64 socket_fd = socket(f2integer__i(domain, cause), f2integer__i(type, cause), f2integer__i(protocol, cause));
  if (socket_fd == -1) {
    s64 error_number = errno;
    return f2larva__new(cause, 667, f2__bug__new(cause, f2integer__new(cause, 667), f2__frame__new(cause, f2list12__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "socket_creation_failure"),
															new__symbol(cause, "domain"),   domain,
															new__symbol(cause, "type"),     type,
															new__symbol(cause, "protocol"), protocol,
															new__symbol(cause, "errno"),    f2integer__new(cause, error_number),
															new__symbol(cause, "strerror"), new__string(cause, strerror(error_number))))));
  }
  return f2integer__new(cause, socket_fd);
}

f2ptr f2__socket(f2ptr cause, f2ptr domain, f2ptr type, f2ptr protocol) {
  if ((! raw__integer__is_type(cause, domain)) ||
      (! raw__integer__is_type(cause, type)) ||
      (! raw__integer__is_type(cause, protocol))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__socket(cause, domain, type, protocol);
}
def_pcfunk3(f2__socket, domain, type, protocol, return f2__socket(this_cause, domain, type, protocol));


// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
f2ptr raw__accept(f2ptr cause, f2ptr sockfd, f2ptr addr_array) {
  struct sockaddr_in addr_in;
  socklen_t          addr_len = sizeof(addr_in.sin_addr.s_addr);
  s64 result = accept(f2integer__i(sockfd, cause), (struct sockaddr*)&addr_in, &addr_len);
  if (result == -1) {
    s64 error_number = errno;
    return f2larva__new(cause, 667, f2__bug__new(cause, f2integer__new(cause, 667), f2__frame__new(cause, f2list12__new(cause,
															new__symbol(cause, "bug_type"),   new__symbol(cause, "socket_accept_failure"),
															new__symbol(cause, "sockfd"),     sockfd,
															new__symbol(cause, "addr_array"), addr_array,
															new__symbol(cause, "errno"),      f2integer__new(cause, error_number),
															new__symbol(cause, "strerror"),   new__string(cause, strerror(error_number))))));
  }
  f2ptr rv = f2integer__new(cause, result);
  // there is a bug here in getting the correct client address from accept.
  if (addr_array) {
    if (raw__array__is_type(cause, addr_array)) {
      int array_len = raw__array__length(cause, addr_array);
      int i;
      for (i = 0; i < addr_len && i < array_len; i ++) {
	raw__array__elt__set(cause, addr_array, i, f2integer__new(cause, ((unsigned char*)(&(addr_in.sin_addr.s_addr)))[i]));
      }
      for (; i < array_len; i ++) {
	raw__array__elt__set(cause, addr_array, i, nil);
      }
    } else {
      return f2larva__new(cause, 1, nil);
    }
  }
  return rv;
}

f2ptr f2__accept(f2ptr cause, f2ptr sockfd, f2ptr addr_array) {
  if ((! raw__integer__is_type(cause, sockfd)) ||
      (! raw__array__is_type(cause, addr_array))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__accept(cause, sockfd, addr_array);
}
def_pcfunk2(f2__accept, sockfd, addr_array, return f2__accept(this_cause, sockfd, addr_array));


// int connect(int sockfd, const struct sockaddr *serv_addr, socklen_t addrlen);
f2ptr raw__connect(f2ptr cause, f2ptr sockfd, f2ptr sin_family, f2ptr sin_port, f2ptr sin_addr) {
  struct sockaddr_in addr_in;
  addr_in.sin_family = f2integer__i(sin_family, cause);
  addr_in.sin_port   = htons(f2integer__i(sin_port, cause));
  const int addr_len = sizeof(addr_in.sin_addr.s_addr);
  //printf("\naddr_len = %d", addr_len);
  char addr[addr_len];
  int i;
  int sin_addr__length = raw__array__length(cause, sin_addr);
  for (i = 0; i < addr_len && i < sin_addr__length; i ++) {
    addr[i] = f2integer__i(raw__array__elt(cause, sin_addr, i), cause);
  }
  memcpy(&(addr_in.sin_addr.s_addr), addr, addr_len);
  s64 result = connect(f2integer__i(sockfd, cause), (struct sockaddr*)&addr_in, sizeof(struct sockaddr));
  if (result == -1) {
    s64 error_number = errno;
    return f2larva__new(cause, 667, f2__bug__new(cause, f2integer__new(cause, 667), f2__frame__new(cause, f2list12__new(cause,
															new__symbol(cause, "bug_type"),   new__symbol(cause, "socket_connect_failure"),
															new__symbol(cause, "sockfd"),     sockfd,
															new__symbol(cause, "sin_family"), sin_family,
															new__symbol(cause, "sin_port"),   sin_port,
															new__symbol(cause, "sin_addr"),   sin_addr,
															new__symbol(cause, "errno"),      f2integer__new(cause, error_number),
															new__symbol(cause, "strerror"),   new__string(cause, strerror(error_number))))));
  }
  return f2integer__new(cause, result);
}

f2ptr f2__connect(f2ptr cause, f2ptr sockfd, f2ptr sin_family, f2ptr sin_port, f2ptr sin_addr) {
  if ((! raw__integer__is_type(cause, sockfd)) ||
      (! raw__integer__is_type(cause, sin_family)) ||
      (! raw__integer__is_type(cause, sin_port)) ||
      (! raw__array__is_type(cause, sin_addr))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__connect(cause, sockfd, sin_family, sin_port, sin_addr);
}
def_pcfunk4(f2__connect, sockfd, sin_family, sin_port, sin_addr, return f2__connect(this_cause, sockfd, sin_family, sin_port, sin_addr));

// int bind(int sockfd, const struct sockaddr *my_addr, socklen_t addrlen);
f2ptr raw__bind(f2ptr cause, f2ptr sockfd, f2ptr sin_family, f2ptr sin_port, f2ptr sin_addr) {
  struct sockaddr_in addr_in;
  addr_in.sin_family = f2integer__i(sin_family, cause);
  addr_in.sin_port   = htons(f2integer__i(sin_port, cause));
  const int addr_len = sizeof(addr_in.sin_addr.s_addr);
  char addr[addr_len];
  int i;
  int sin_addr__length = raw__array__length(cause, sin_addr);
  for (i = 0; i < addr_len && i < sin_addr__length; i ++) {
    addr[i] = f2integer__i(raw__array__elt(cause, sin_addr, i), cause);
  }
  memcpy(&(addr_in.sin_addr.s_addr), addr, addr_len);
  s64 result = bind(f2integer__i(sockfd, cause), (struct sockaddr*)&addr_in, sizeof(struct sockaddr));
  if (result == -1) {
    s64 error_number = errno;
    return f2larva__new(cause, 667, f2__bug__new(cause, f2integer__new(cause, 667), f2__frame__new(cause, f2list12__new(cause,
															new__symbol(cause, "bug_type"),   new__symbol(cause, "socket_bind_failure"),
															new__symbol(cause, "sockfd"),     sockfd,
															new__symbol(cause, "sin_family"), sin_family,
															new__symbol(cause, "sin_port"),   sin_port,
															new__symbol(cause, "sin_addr"),   sin_addr,
															new__symbol(cause, "errno"),      f2integer__new(cause, error_number),
															new__symbol(cause, "strerror"),   new__string(cause, strerror(error_number))))));
  }
  return f2integer__new(cause, result);
}

f2ptr f2__bind(f2ptr cause, f2ptr sockfd, f2ptr sin_family, f2ptr sin_port, f2ptr sin_addr) {
  if ((! raw__integer__is_type(cause, sockfd)) ||
      (! raw__integer__is_type(cause, sin_family)) ||
      (! raw__integer__is_type(cause, sin_port)) ||
      (! raw__array__is_type(cause, sin_addr))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__bind(cause, sockfd, sin_family, sin_port, sin_addr);
}
def_pcfunk4(f2__bind, sockfd, sin_family, sin_port, sin_addr, return f2__bind(this_cause, sockfd, sin_family, sin_port, sin_addr));

// int getsockname(int s, struct sockaddr *name, socklen_t *namelen);
f2ptr raw__getsockname(f2ptr cause, f2ptr s, f2ptr name, f2ptr namelen) {
  return f2integer__new(cause, getsockname(f2integer__i(s, cause), (struct sockaddr*)from_ptr(f2pointer__p(name, cause)), (socklen_t*)from_ptr(f2pointer__p(namelen, cause))));
}

f2ptr f2__getsockname(f2ptr cause, f2ptr s, f2ptr name, f2ptr namelen) {
  if ((! raw__integer__is_type(cause, s)) ||
      (! raw__pointer__is_type(cause, name)) ||
      (! raw__pointer__is_type(cause, namelen))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__getsockname(cause, s, name, namelen);
}
def_pcfunk3(f2__getsockname, s, name, namelen, return f2__getsockname(this_cause, s, name, namelen));

// int listen(int sockfd, int backlog);
f2ptr raw__listen(f2ptr cause, f2ptr sockfd, f2ptr backlog) {
  s64 result = listen(f2integer__i(sockfd, cause), f2integer__i(backlog, cause));
  if (result == -1) {
    s64 error_number = errno;
    return f2larva__new(cause, 667, f2__bug__new(cause, f2integer__new(cause, 667), f2__frame__new(cause, f2list12__new(cause,
															new__symbol(cause, "bug_type"), new__symbol(cause, "socket_listen_failure"),
															new__symbol(cause, "sockfd"),   sockfd,
															new__symbol(cause, "backlog"),  backlog,
															new__symbol(cause, "errno"),    f2integer__new(cause, error_number),
															new__symbol(cause, "strerror"), new__string(cause, strerror(error_number))))));
  }
  return f2integer__new(cause, result);
}

f2ptr f2__listen(f2ptr cause, f2ptr sockfd, f2ptr backlog) {
  if ((! raw__integer__is_type(cause, sockfd)) ||
      (! raw__integer__is_type(cause, backlog))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__listen(cause, sockfd, backlog);
}
def_pcfunk2(f2__listen, sockfd, backlog, return f2__listen(this_cause, sockfd, backlog));

// struct hostent *gethostbyname(const char *name);
f2ptr raw__gethostbyname(f2ptr cause, f2ptr name) {
  int name__length = f2string__length(name, cause);
  char* temp_str = (char*)from_ptr(f2__malloc(sizeof(char) * (name__length + 1)));
  if (!temp_str) {return nil;}
  f2string__str_copy(name, cause, (u8*)temp_str);
  temp_str[name__length] = (char)0;
  //printf("\ntemp_str: %d \"%s\"", name__length, temp_str);
  f2ptr rv = f2pointer__new(cause, to_ptr(gethostbyname(temp_str)));
  f2__free(to_ptr(temp_str));
  return rv;
}

f2ptr f2__gethostbyname(f2ptr cause, f2ptr name) {
  if (! raw__string__is_type(cause, name)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gethostbyname(cause, name);
}
def_pcfunk1(f2__gethostbyname, name, return f2__gethostbyname(this_cause, name));

f2ptr f2__h_errno(f2ptr cause) {return f2integer__new(cause, h_errno);}
def_pcfunk0(f2__h_errno, return f2__h_errno(this_cause));

f2ptr f2__h_errno__host_not_found(f2ptr cause) {return f2integer__new(cause, HOST_NOT_FOUND);}
def_pcfunk0(f2__h_errno__host_not_found, return f2__h_errno__host_not_found(this_cause));

f2ptr f2__h_errno__no_address(f2ptr cause) {return f2integer__new(cause, NO_ADDRESS);}
def_pcfunk0(f2__h_errno__no_address, return f2__h_errno__no_address(this_cause));

f2ptr f2__h_errno__no_recovery(f2ptr cause) {return f2integer__new(cause, NO_RECOVERY);}
def_pcfunk0(f2__h_errno__no_recovery, return f2__h_errno__no_recovery(this_cause));

f2ptr f2__h_errno__try_again(f2ptr cause) {return f2integer__new(cause, TRY_AGAIN);}
def_pcfunk0(f2__h_errno__try_again, return f2__h_errno__try_again(this_cause));

f2ptr raw__hostenv__h_name(f2ptr cause, f2ptr this) {
  struct hostent* this_hostent = (struct hostent*)from_ptr(f2pointer__p(this, cause));
  return f2string__new(cause, strlen(this_hostent->h_name), (u8*)(this_hostent->h_name));
}

f2ptr f2__hostenv__h_name(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__hostenv__h_name(cause, this);
}
def_pcfunk1(f2__hostent__h_name, this, return f2__hostenv__h_name(this_cause, this));

f2ptr raw__hostent__h_aliases(f2ptr cause, f2ptr this) {
  struct hostent* this_hostent = (struct hostent*)from_ptr(f2pointer__p(this, cause));
  f2ptr seq  = nil;
  f2ptr iter = nil;
  char** aliases_iter = this_hostent->h_aliases;
  while(*aliases_iter) {
    char* alias = *aliases_iter;
    //printf("\nalias: %d \"%s\"", strlen(alias), alias);
    f2ptr new_string = f2string__new(cause, strlen(alias), (u8*)alias);
    f2ptr new_cons = f2cons__new(cause, new_string, nil);
    if (iter) {
      f2cons__cdr__set(iter, cause, new_cons);
    } else {
      seq = new_cons;
    }
    iter = new_cons;
    aliases_iter ++;
  }
  return seq;
}

f2ptr f2__hostent__h_aliases(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__hostent__h_aliases(cause, this);
}
def_pcfunk1(f2__hostent__h_aliases, this, return f2__hostent__h_aliases(this_cause, this));


f2ptr raw__hostent__h_addrtype(f2ptr cause, f2ptr this) {
  struct hostent* this_hostent = (struct hostent*)from_ptr(f2pointer__p(this, cause));
  return f2integer__new(cause, this_hostent->h_addrtype);
}

f2ptr f2__hostent__h_addrtype(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__hostent__h_addrtype(cause, this);
}
def_pcfunk1(f2__hostent__h_addrtype, this, return f2__hostent__h_addrtype(this_cause, this));


f2ptr raw__hostent__h_length(f2ptr cause, f2ptr this) {
  struct hostent* this_hostent = (struct hostent*)from_ptr(f2pointer__p(this, cause));
  return f2integer__new(cause, this_hostent->h_length);
}

f2ptr f2__hostent__h_length(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__hostent__h_length(cause, this);
}
def_pcfunk1(f2__hostent__h_length, this, return f2__hostent__h_length(this_cause, this));

f2ptr raw__hostent__h_addr_list(f2ptr cause, f2ptr this) {
  struct hostent* this_hostent = (struct hostent*)from_ptr(f2pointer__p(this, cause));
  int h_length = this_hostent->h_length;
  f2ptr seq  = nil;
  f2ptr iter = nil;
  char** addr_list_iter = this_hostent->h_addr_list;
  while(*addr_list_iter) {
    char* addr = *addr_list_iter;
    //printf("\naddr: %d.%d.%d.%d", (unsigned char)addr[0], (unsigned char)addr[1], (unsigned char)addr[2], (unsigned char)addr[3]);
    f2ptr new_array = raw__array__new(cause, h_length);
    int i;
    for (i = 0; i < h_length; i ++) {
      raw__array__elt__set(cause, new_array, i, f2integer__new(cause, (unsigned char)(addr[i])));
    }
    f2ptr new_cons = f2cons__new(cause, new_array, nil);
    if (iter) {
      f2cons__cdr__set(iter, cause, new_cons);
    } else {
      seq = new_cons;
    }
    iter = new_cons;
    addr_list_iter ++;
  }
  return seq;
}

f2ptr f2__hostent__h_addr_list(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__hostent__h_addr_list(cause, this);
}
def_pcfunk1(f2__hostent__h_addr_list, this, return f2__hostent__h_addr_list(this_cause, this));

f2ptr raw__sockaddr_in__sin_family(f2ptr cause, f2ptr this) {
  struct sockaddr_in* this__sockaddr_in = (struct sockaddr_in*)from_ptr(f2pointer__p(this, cause));
  return f2integer__new(cause, this__sockaddr_in->sin_family);
}

f2ptr f2__sockaddr_in__sin_family(f2ptr cause, f2ptr this) {
  if (! raw__pointer(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__sockaddr_in__sin_family(cause, this);
}
def_pcfunk1(f2__sockaddr_in__sin_family, this, return f2__sockaddr_in__sin_family(this_cause, this));

f2ptr raw__sockaddr_in__sin_port(f2ptr cause, f2ptr this) {
  struct sockaddr_in* this__sockaddr_in = (struct sockaddr_in*)from_ptr(f2pointer__p(this, cause));
  return f2integer__new(cause, this__sockaddr_in->sin_port);
}

f2ptr f2__sockaddr_in__sin_port(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__sockaddr_in__sin_port(cause, this);
}
def_pcfunk1(f2__sockaddr_in__sin_port, this, return f2__sockaddr_in__sin_port(this_cause, this));

f2ptr raw__sockaddr_in__sin_addr(f2ptr cause, f2ptr this) {
  struct sockaddr_in* this__sockaddr_in = (struct sockaddr_in*)from_ptr(f2pointer__p(this, cause));
  struct in_addr*     this__sin_addr    = &(this__sockaddr_in->sin_addr);
  return f2integer__new(cause, *((unsigned long*)this__sin_addr));
}

f2ptr f2__sockaddr_in__sin_addr(f2ptr cause, f2ptr this) {
  if (! raw__pointer__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__sockaddr_in__sin_addr(cause, this);
}
def_pcfunk1(f2__sockaddr_in__sin_addr, this, return f2__sockaddr_in__sin_addr(this_cause, this));

f2ptr raw__chunk__send(f2ptr cause, f2ptr chunk, f2ptr start, f2ptr length, f2ptr fd, f2ptr flags) {
  return f2chunk__send(chunk, cause, f2integer__i(start, cause), f2integer__i(length, cause), f2integer__i(fd, cause), f2integer__i(flags, cause));
}

f2ptr f2__chunk__send(f2ptr cause, f2ptr chunk, f2ptr start, f2ptr length, f2ptr fd, f2ptr flags) {
  if ((! raw__chunk__is_type(cause, chunk)) ||
      (! raw__integer__is_type(cause, start)) ||
      (! raw__integer__is_type(cause, length)) ||
      (! raw__integer__is_type(cause, fd)) ||
      (! raw__integer__is_type(cause, flags))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__send(cause, chunk, start, length, fd, flags);
}
def_pcfunk5(f2__chunk__send, chunk, start, length, fd, flags, return f2__chunk__send(this_cause, chunk, start, length, fd, flags));

f2ptr raw__chunk__recv(f2ptr cause, f2ptr chunk, f2ptr start, f2ptr length, f2ptr fd, f2ptr flags) {
  return f2chunk__recv(chunk, cause, f2integer__i(start, cause), f2integer__i(length, cause), f2integer__i(fd, cause), f2integer__i(flags, cause));
}

f2ptr f2__chunk__recv(f2ptr cause, f2ptr chunk, f2ptr start, f2ptr length, f2ptr fd, f2ptr flags) {
  if ((! raw__chunk__is_type(cause, chunk)) ||
      (! raw__integer__is_type(cause, start)) ||
      (! raw__integer__is_type(cause, length)) ||
      (! raw__integer__is_type(cause, fd)) ||
      (! raw__integer__is_type(cause, flags))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__chunk__recv(cause, chunk, start, length, fd, flags);
}
def_pcfunk5(f2__chunk__recv, chunk, start, length, fd, flags, return f2__chunk__recv(this_cause, chunk, start, length, fd, flags));

f2ptr raw__send(f2ptr cause, f2ptr fd, f2ptr pointer, f2ptr byte_num, f2ptr flags) {
  return f2integer__new(cause, send(f2integer__i(fd, cause), (void*)from_ptr(f2pointer__p(pointer, cause)), f2integer__i(byte_num, cause), f2integer__i(flags, cause)));
}

f2ptr f2__send(f2ptr cause, f2ptr fd, f2ptr pointer, f2ptr byte_num, f2ptr flags) {
  if ((! raw__integer__is_type(cause, fd)) ||
      (! raw__pointer__is_type(cause, pointer)) ||
      (! raw__integer__is_type(cause, byte_num)) ||
      (! raw__integer__is_type(cause, flags))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__send(cause, fd, pointer, byte_num, flags);
}
def_pcfunk4(f2__send, fd, pointer, byte_num, flags, return f2__send(this_cause, fd, pointer, byte_num, flags));

f2ptr raw__recv(f2ptr cause, f2ptr fd, f2ptr pointer, f2ptr byte_num, f2ptr flags) {
  return f2integer__new(cause, recv(f2integer__i(fd, cause), (void*)from_ptr(f2pointer__p(pointer, cause)), f2integer__i(byte_num, cause), f2integer__i(flags, cause)));
}

f2ptr f2__recv(f2ptr cause, f2ptr fd, f2ptr pointer, f2ptr byte_num, f2ptr flags) {
  if ((! raw__integer__is_type(cause, fd)) ||
      (! raw__pointer__is_type(cause, pointer)) ||
      (! raw__integer__is_type(cause, byte_num)) ||
      (! raw__integer__is_type(cause, flags))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__recv(cause, fd, pointer, byte_num, flags);
}
def_pcfunk4(f2__recv, fd, pointer, byte_num, flags, return f2__recv(this_cause, fd, pointer, byte_num, flags));


void f2__socket__reinitialize_globalvars() {
  //f2ptr cause = f2_socket_c__cause__new(initial_cause(), nil, nil);
}

void f2__socket__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "socket", "", &f2__socket__reinitialize_globalvars);
  
  f2__socket__reinitialize_globalvars();
  
  f2__primcfunk__init(f2__inaddr_any, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__socket, "(as defined in socket.h)");
  f2__primcfunk__init(f2__accept, "(as defined in socket.h)");
  f2__primcfunk__init(f2__connect, "(as defined in socket.h)");
  f2__primcfunk__init(f2__bind, "(as defined in socket.h)");
  f2__primcfunk__init(f2__getsockname, "(as defined in socket.h)");
  f2__primcfunk__init(f2__listen, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__socket__pf_unix, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_local, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_inet, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_inet6, "(as defined in socket.h)");

#ifndef F2__CYGWIN
  f2__primcfunk__init(f2__socket__pf_ipx, "(as defined in socket.h)");
#endif

#if (! defined(F2__CYGWIN)) && (! defined(F2__APPLE))
  f2__primcfunk__init(f2__socket__pf_netlink, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_x25, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_ax25, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_atmpvc, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__pf_packet, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__sock_packet, "(as defined in socket.h)");
#endif

  f2__primcfunk__init(f2__socket__pf_appletalk, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__sock_dgram, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__sock_seqpacket, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__sock_raw, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__sock_rdm, "(as defined in socket.h)");
  f2__primcfunk__init(f2__socket__sock_stream, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__gethostbyname, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__h_errno, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__h_errno__host_not_found, "(as defined in socket.h)");
  f2__primcfunk__init(f2__h_errno__no_address, "(as defined in socket.h)");
  f2__primcfunk__init(f2__h_errno__no_recovery, "(as defined in socket.h)");
  f2__primcfunk__init(f2__h_errno__try_again, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__hostent__h_name, "(as defined in socket.h)");
  f2__primcfunk__init(f2__hostent__h_aliases, "(as defined in socket.h)");
  f2__primcfunk__init(f2__hostent__h_addrtype, "(as defined in socket.h)");
  f2__primcfunk__init(f2__hostent__h_length, "(as defined in socket.h)");
  f2__primcfunk__init(f2__hostent__h_addr_list, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__sockaddr_in__sin_family, "(as defined in socket.h)");
  f2__primcfunk__init(f2__sockaddr_in__sin_port, "(as defined in socket.h)");
  f2__primcfunk__init(f2__sockaddr_in__sin_addr, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__chunk__send, "send a chunk of data (as defined in socket.h)");
  f2__primcfunk__init(f2__send, "(as defined in socket.h)");
  
  f2__primcfunk__init(f2__chunk__recv, "recv a chunk of data (as defined in socket.h)");
  f2__primcfunk__init(f2__recv, "(as defined in socket.h)");
}

  


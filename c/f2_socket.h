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

#ifndef F2__SOCKET__H
#define F2__SOCKET__H

#include "f2_primfunks.h"

f2ptr f2__socket__pf_unix(f2ptr cause);
f2ptr f2__socket__pf_local(f2ptr cause);
f2ptr f2__socket__pf_inet(f2ptr cause);
f2ptr f2__socket__pf_inet6(f2ptr cause);
f2ptr f2__socket__pf_ipx(f2ptr cause);
/*
f2ptr f2__socket__pf_netlink(f2ptr cause);
f2ptr f2__socket__pf_x25(f2ptr cause);
f2ptr f2__socket__pf_ax25(f2ptr cause);
f2ptr f2__socket__pf_atmpvc(f2ptr cause);
f2ptr f2__socket__pf_packet(f2ptr cause);
f2ptr f2__socket__sock_stream(f2ptr cause);
*/
f2ptr f2__socket__pf_appletalk(f2ptr cause);
f2ptr f2__socket__sock_dgram(f2ptr cause);
f2ptr f2__socket__sock_seqpacket(f2ptr cause);
f2ptr f2__socket__sock_raw(f2ptr cause);
f2ptr f2__socket__sock_rdm(f2ptr cause);
f2ptr f2__socket__sock_packet(f2ptr cause);
f2ptr f2__inaddr_any(f2ptr cause);
f2ptr f2__socket(f2ptr cause, f2ptr domain, f2ptr type, f2ptr protocol);
f2ptr f2__accept(f2ptr cause, f2ptr sockfd, f2ptr addr_array);
f2ptr f2__connect(f2ptr cause, f2ptr sockfd, f2ptr sin_family, f2ptr sin_port, f2ptr sin_addr);
f2ptr f2__bind(f2ptr cause, f2ptr sockfd, f2ptr sin_family, f2ptr sin_port, f2ptr sin_addr);
f2ptr f2__getsockname(f2ptr cause, f2ptr s, f2ptr name, f2ptr namelen);
f2ptr f2__listen(f2ptr cause, f2ptr sockfd, f2ptr backlog);
f2ptr f2__gethostbyname(f2ptr cause, f2ptr name);
f2ptr f2__h_errno(f2ptr cause);
f2ptr f2__h_errno__host_not_found(f2ptr cause);
f2ptr f2__h_errno__no_address(f2ptr cause);
f2ptr f2__h_errno__no_recovery(f2ptr cause);
f2ptr f2__h_errno__try_again(f2ptr cause);
f2ptr f2__hostenv__h_name(f2ptr cause, f2ptr this);
f2ptr f2__hostent__h_aliases(f2ptr cause, f2ptr this);
f2ptr f2__hostent__h_addrtype(f2ptr cause, f2ptr this);
f2ptr f2__hostent__h_length(f2ptr cause, f2ptr this);
f2ptr f2__hostent__h_addr_list(f2ptr cause, f2ptr this);
f2ptr f2__sockaddr_in__sin_family(f2ptr cause, f2ptr this);
f2ptr f2__sockaddr_in__sin_port(f2ptr cause, f2ptr this);
f2ptr f2__sockaddr_in__sin_addr(f2ptr cause, f2ptr this);
f2ptr f2__chunk__send(f2ptr cause, f2ptr chunk, f2ptr start, f2ptr length, f2ptr fd, f2ptr flags);
f2ptr f2__chunk__recv(f2ptr cause, f2ptr chunk, f2ptr start, f2ptr length, f2ptr fd, f2ptr flags);
f2ptr f2__send(f2ptr cause, f2ptr fd, f2ptr pointer, f2ptr byte_num, f2ptr flags);
f2ptr f2__recv(f2ptr cause, f2ptr fd, f2ptr pointer, f2ptr byte_num, f2ptr flags);
void f2__socket__reinitialize_globalvars();
void f2__socket__initialize();

#endif // F2__SOCKET__H


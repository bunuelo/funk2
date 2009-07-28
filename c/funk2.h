// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef FUNK2__H
#define FUNK2__H

#define _GNU_SOURCE

//#define F2__GMODULE__SUPPORTED
//#define F2__DLFCN__SUPPORTED

#ifdef __APPLE__
#define MAP_ANONYMOUS MAP_ANON
// see: http://www.osxfaq.com/man/4/tty.ws
#define SIOCOUTQ TIOCOUTQ
#define SIOCINQ TIOCSTI

//#define O_NOFOLLOW 0
//#define O_DIRECT 0
//#define O_NOATIME 0
//#define O_LARGEFILE 1

#include <sys/sockio.h>
#else
#include <linux/sockios.h>
#endif

#include <arpa/inet.h>
#ifdef F2__DLFCN__SUPPORTED
#  include <dlfcn.h>
#endif
#include <errno.h>
#include <fcntl.h>
#ifdef F2__GMODULE__SUPPORTED
#  include <gmodule.h>
#endif
#include <locale.h>
#include <net/if.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <pthread.h>
#include <sched.h>
#include <signal.h>
#include <stdarg.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "f2_ansi.h"
#include "f2_apropos.h"
#include "f2_blocks_world.h"
#include "f2_buffered_file.h"
#include "f2_buffered_socket.h"
#include "f2_bytecodes.h"
#include "f2_child.h"
#include "f2_child_handler.h"
#include "f2_circular_buffer.h"
#include "f2_command_line.h"
#include "f2_compile.h"
#include "f2_compile_x86.h"
#include "f2_critic.h"
#include "f2_dlfcn.h"
#include "f2_dptr.h"
#include "f2_event_router.h"
#include "f2_funk2_node.h"
#include "f2_funktional.h"
#include "f2_gc_touch_circle_buffer.h"
#include "f2_globalenv.h"
#include "f2_html.h"
#include "f2_load.h"
#include "f2_malloc.h"
#include "f2_memblock.h"
#include "f2_memory.h"
#include "f2_memorypool.h"
#include "f2_module_registration.h"
#include "f2_object.h"
#include "f2_packet.h"
#include "f2_peer_command_server.h"
#include "f2_ptype.h"
#include "f2_ptypes.h"
#include "f2_ptypes_memory.h"
#include "f2_primfunks.h"
#include "f2_primfunks__errno.h"
#include "f2_primfunks__fcntl.h"
#include "f2_primfunks__ioctl.h"
#include "f2_primfunks__locale.h"
#include "f2_primfunks__string.h"
#include "f2_primobject__action.h"
#include "f2_primobject__boolean.h"
#include "f2_primobject__char_pointer.h"
#include "f2_primobject__circular_buffer.h"
#include "f2_primobject__dynamic_library.h"
#include "f2_primobject__environment.h"
#include "f2_primobject__frame.h"
#include "f2_primobject__hashtable.h"
#include "f2_primobject__object.h"
#include "f2_primobject__object_type.h"
#include "f2_primobject__stream.h"
#include "f2_primobject__tensor.h"
#include "f2_primobject__dynamic_library.h"
#include "f2_primobject__semantic_graph.h"
#include "f2_primobject__text_buffer.h"
#include "f2_primobject_type.h"
#include "f2_primobject_type_handler.h"
#include "f2_primobjects.h"
#include "f2_print.h"
#include "f2_processor_mutex.h"
#include "f2_processor_thread.h"
#include "f2_processor_thread_handler.h"
#include "f2_protected_alloc_array.h"
#include "f2_reader.h"
#include "f2_redblacktree.h"
#include "f2_repl.h"
#include "f2_scheduler.h"
#include "f2_search.h"
#include "f2_serialize.h"
#include "f2_signal.h"
#include "f2_socket.h"
#include "f2_socket_client.h"
#include "f2_socket_server.h"
#include "f2_sort.h"
#include "f2_status.h"
#include "f2_string.h"
#include "f2_termios.h"
#include "f2_thought_process.h"
#include "f2_thread.h"
#include "f2_time.h"
#include "f2_trace.h"
#include "f2_user_thread_controller.h"

void f2__destroy();

typedef struct funk2_s {
  node_id_t                          node_id;
  event_id_t                         event_id;
  funk2_processor_mutex_t            event_id_mutex;
  funk2_module_registration_t        module_registration;
  funk2_command_line_t               command_line;
  funk2_memory_t                     memory;
  funk2_globalenv_t                  globalenv;
  funk2_operating_system_t           operating_system;
  funk2_thought_process_t            thought_process;
  funk2_bytecode_t                   bytecode;
  funk2_peer_command_server_t        peer_command_server;
  funk2_node_handler_t               node_handler;
  funk2_status_t                     status;
  funk2_locale_t                     locale;
  funk2_event_router_t               event_router;
  funk2_primobject_circular_buffer_t primobject__circular_buffer;
  funk2_child_process_handler_t      child_process_handler;
  funk2_processor_thread_handler_t   processor_thread_handler;
  funk2_primobject_type_handler_t    primobject_type_handler;
} funk2_t;

boolean_t funk2__handle(funk2_t* this);

extern funk2_t __funk2;

#endif // FUNK2__H

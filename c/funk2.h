// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#include "../config.h"

#include "f2_system_headers.h"

#include "f2_ansi.h"
#include "f2_apropos.h"
#include "f2_array.h"
#include "f2_atomic.h"
#include "f2_buffered_file.h"
#include "f2_buffered_socket.h"
#include "f2_bug.h"
#include "f2_bytecodes.h"
#include "f2_cause.h"
#include "f2_chunk.h"
#include "f2_circular_buffer.h"
#include "f2_command_line.h"
#include "f2_compile.h"
#include "f2_compile_x86.h"
#include "f2_core_extension_funk.h"
#include "f2_core_extension.h"
#include "f2_cpu.h"
#include "f2_defragmenter.h"
#include "f2_dlfcn.h"
#include "f2_dptr.h"
#include "f2_f2ptr_set.h"
#include "f2_fiber.h"
#include "f2_fileio.h"
#include "f2_frame_objects.h"
#include "f2_funk2_node.h"
#include "f2_funktional.h"
#include "f2_garbage_collector.h"
#include "f2_garbage_collector_block_header.h"
#include "f2_garbage_collector_pool.h"
#include "f2_globalenv.h"
#include "f2_graph.h"
#include "f2_graph_cluster.h"
#include "f2_graph_match_error_correcting.h"
#include "f2_graphviz.h"
#include "f2_hash.h"
#include "f2_heap.h"
#include "f2_html.h"
#include "f2_larva.h"
#include "f2_load.h"
#include "f2_malloc.h"
#include "f2_management_thread.h"
#include "f2_memblock.h"
#include "f2_memory.h"
#include "f2_memorypool.h"
#include "f2_module_registration.h"
#include "f2_nil.h"
#include "f2_number.h"
#include "f2_object.h"
#include "f2_opengl.h"
#include "f2_optimize.h"
#include "f2_package.h"
#include "f2_package_handler.h"
#include "f2_packet.h"
#include "f2_partial_order.h"
#include "f2_peer_command_server.h"
#include "f2_ptype.h"
#include "f2_ptypes.h"
#include "f2_ptypes_memory.h"
#include "f2_ptypes_object_slots.h"
#include "f2_primes.h"
#include "f2_primfunks.h"
#include "f2_primfunks__errno.h"
#include "f2_primfunks__fcntl.h"
#include "f2_primfunks__ioctl.h"
#include "f2_primfunks__locale.h"
#include "f2_primfunks__stdlib.h"
#include "f2_primobject__boolean.h"
#include "f2_primobject__char_pointer.h"
#include "f2_primobject__circular_buffer.h"
#include "f2_primobject__counter.h"
#include "f2_primobject__dynamic_library.h"
#include "f2_primobject__environment.h"
#include "f2_primobject__fiber_trigger.h"
#include "f2_primobject__file_handle.h"
#include "f2_primobject__frame.h"
#include "f2_primobject__hash.h"
#include "f2_primobject__largeinteger.h"
#include "f2_primobject__matrix.h"
#include "f2_primobject__object.h"
#include "f2_primobject__object_type.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__redblacktree.h"
#include "f2_primobject__scheduler_ptypehash.h"
#include "f2_primobject__set.h"
#include "f2_primobject__stream.h"
#include "f2_primobject__tensor.h"
#include "f2_primobject__dynamic_library.h"
#include "f2_primobject__traced_cmutex.h"
#include "f2_primobject_type.h"
#include "f2_primobject_type_handler.h"
#include "f2_primobjects.h"
#include "f2_print.h"
#include "f2_processor.h"
#include "f2_processor_mutex.h"
#include "f2_processor_readwritelock.h"
#include "f2_processor_spinlock.h"
#include "f2_processor_thread.h"
#include "f2_processor_thread_handler.h"
#include "f2_protected_alloc_array.h"
#include "f2_reader.h"
#include "f2_redblacktree.h"
#include "f2_simple_repl.h"
#include "f2_scheduler.h"
#include "f2_scheduler_thread_controller.h"
#include "f2_set.h"
#include "f2_signal.h"
#include "f2_socket.h"
#include "f2_socket_client.h"
#include "f2_socket_server.h"
#include "f2_sort.h"
#include "f2_status.h"
#include "f2_string.h"
#include "f2_surrogate_parent.h"
#include "f2_system_processor.h"
#include "f2_system_file_handler.h"
#include "f2_terminal_print.h"
#include "f2_termios.h"
#include "f2_time.h"
#include "f2_trace.h"
#include "f2_user_thread_controller.h"
#include "f2_virtual_processor.h"
#include "f2_virtual_processor_handler.h"
#include "f2_virtual_processor_thread.h"
#include "f2_xmlrpc.h"
#include "f2_zlib.h"

void f2__destroy();

#define relative_ptr__to__raw_executable(x) from_ptr(x + __funk2.funk2_main_code_position)
#define raw_executable__to__relative_ptr(x) (to_ptr(x) - __funk2.funk2_main_code_position)

typedef struct funk2_s {
  ptr                                 funk2_main_code_position;
  boolean_t                           exit_now;
  node_id_t                           node_id;
  event_id_t                          event_id;
  funk2_processor_mutex_t             event_id_cmutex;
  // global variables in other source files
  funk2_system_processor_t            system_processor;
  funk2_system_file_handler_t         system_file_handler;
  funk2_module_registration_t         module_registration;
  funk2_command_line_t                command_line;
  funk2_memory_t                      memory;
  funk2_globalenv_t                   globalenv;
  funk2_compile_t                     compile;
  funk2_operating_system_t            operating_system;
  funk2_bytecode_t                    bytecode;
  funk2_peer_command_server_t         peer_command_server;
  funk2_node_handler_t                node_handler;
  funk2_status_t                      status;
  funk2_locale_t                      locale;
  funk2_processor_thread_handler_t    processor_thread_handler;
  funk2_primobject_type_handler_t     primobject_type_handler;
  funk2_primobject__frame_t           primobject__frame;
  funk2_primobject__environment_t     primobject__environment;
  funk2_scheduler_thread_controller_t scheduler_thread_controller;
  funk2_management_thread_t           management_thread;
  funk2_garbage_collector_t           garbage_collector;
  funk2_defragmenter_t                defragmenter;
  funk2_user_thread_controller_t      user_thread_controller;
  funk2_ptypes_t                      ptypes;
  funk2_reader_t                      reader;
  funk2_opengl_t                      opengl;
  funk2_openglu_t                     openglu;
  funk2_xxf86vm_t                     xxf86vm;
  funk2_xlib_t                        xlib;
  funk2_cpu_t                         cpu;
  funk2_primes_t                      primes;
  funk2_object_t                      object;
  funk2_number_globalvars_t           number_globalvars;
  funk2_surrogate_parent_t            surrogate_parent;
  funk2_xmlrpc_t                      xmlrpc;
  funk2_trace_t                       trace;
  funk2_virtual_processor_handler_t   virtual_processor_handler;
} funk2_t;

void      funk2__init   (funk2_t* this, int argc, char** argv);
void      funk2__destroy(funk2_t* this);
boolean_t funk2__handle (funk2_t* this);

void funk2__start_main_in_separate_thread();

int funk2__main(funk2_t* this, int argc, char** argv);

// this should be the only global variable ever.
extern funk2_t __funk2;

#endif // FUNK2__H

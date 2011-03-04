# 
# Copyright (c) 2007-2011 Bo Morgan.
# All rights reserved.
# 
# Author: Bo Morgan
# 
# Permission to use, copy, modify and distribute this software and its
# documentation is hereby granted, provided that both the copyright
# notice and this permission notice appear in all copies of the
# software, derivative works or modified versions, and any portions
# thereof, and that both notices appear in supporting documentation.
# 
# BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
# BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
# WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
# 
# Bo Morgan requests users of this software to return to bo@mit.edu any
# improvements or extensions that they make and grant Bo Morgan the
# rights to redistribute these changes.
# 

plain_install_root_dir  = /
chroot_install_root_dir = $(DESTDIR)/

source__funk2__dir           = ./
source__fu2__dir             = $(source__funk2__dir)fu2/
source__bootstrap__fu2       = $(source__fu2__dir)bootstrap.fu2
source__bootstrap__repl__fu2 = $(source__fu2__dir)bootstrap-repl.fu2
source__icons__dir           = $(source__funk2__dir)icons/

compile__funk2__dir           = $(source__funk2__dir)
compile__bin__dir             = $(compile__funk2__dir)bin/
compile__lib__dir             = $(compile__funk2__dir)lib/
compile__img__dir             = $(compile__funk2__dir)img/
compile__funk2                = $(compile__bin__dir)funk2
compile__bootstrap__img       = $(compile__img__dir)bootstrap.img
compile__bootstrap__repl__img = $(compile__img__dir)bootstrap-repl.img

chroot__install__system_bin__dir     = $(chroot_install_root_dir)usr/bin/
chroot__install__bin__dir            = $(chroot_install_root_dir)usr/bin/
chroot__install__lib__dir            = $(chroot_install_root_dir)usr/lib/
chroot__install__include__dir        = $(chroot_install_root_dir)usr/include/funk2/
chroot__install__img__dir            = $(chroot_install_root_dir)usr/share/funk2/img/
chroot__install__icons__dir          = $(chroot_install_root_dir)usr/share/funk2/icons/
chroot__install__man__dir            = $(chroot_install_root_dir)usr/share/man/man1/
chroot__install__funk2               = $(chroot__install__bin__dir)funk2
chroot__install__bootstrap__img      = $(chroot__install__img__dir)bootstrap.img

plain__install__system_bin__dir     = $(plain_install_root_dir)usr/bin/
plain__install__bin__dir            = $(plain_install_root_dir)usr/bin/
plain__install__include__dir        = $(plain_install_root_dir)usr/include/funk2/
plain__install__img__dir            = $(plain_install_root_dir)usr/share/funk2/img/
plain__install__icons__dir          = $(plain_install_root_dir)usr/share/funk2/icons/
plain__install__man__dir            = $(plain_install_root_dir)usr/share/man/man1/
plain__install__funk2               = $(plain__install__bin__dir)funk2
plain__install__bootstrap__img      = $(plain__install__img__dir)bootstrap.img

# write seconds since 1980 to file (for version definition)
config_compile_time_id.h:
	echo "#ifndef F2__CONFIG_COMPILE_TIME_ID__H"    > config_compile_time_id.h
	echo "#define F2__CONFIG_COMPILE_TIME_ID__H"   >> config_compile_time_id.h
	echo ""                                        >> config_compile_time_id.h
	echo "#define F2__COMPILE_TIME_ID "`date +%s`  >> config_compile_time_id.h
	echo ""                                        >> config_compile_time_id.h
	echo "#endif // F2__CONFIG_COMPILE_TIME_ID__H" >> config_compile_time_id.h

# get the name of the architecture
#processor = $(shell uname -p)
# get the name of the operating system
#os_name = $(shell uname -s)

# determine the number of processor
#ifeq ($(os_name),Darwin)
#   processor_num = $(shell sysctl -n hw.ncpu)
#else
#  processor_num = $(shell cat /proc/cpuinfo | grep processor | grep -v type | wc -l)
#endif

libs = -lpthread

# processor_power_num description:
#   0 power => 1 processor,
#   1 power => 2 processors,
#   2 power => 4 processors,
#   3 power => 8 processors,
#   4 power => 16 processors, etc.

#ifeq ($(processor_num),0)
#  processor_flags = -Dprocessor_num_power=0
#endif
#ifeq ($(processor_num),1)
#  processor_flags = -Dprocessor_num_power=0
#endif
#ifeq ($(processor_num),2)
#  processor_flags = -Dprocessor_num_power=1
#endif
#ifeq ($(processor_num),4)
#  processor_flags = -Dprocessor_num_power=2
#endif
#ifeq ($(processor_num),8)
#  processor_flags = -Dprocessor_num_power=3
#endif
#ifeq ($(processor_num),16)
#  processor_flags = -Dprocessor_num_power=4
#endif
processor_flags = -Dprocessor_num_power=3

funk2_objs   = $(funk2_server_objs)

#version_flags = -DF2__COMPILE_TIME_ID=$(shell cat seconds.tmp)

#gmodule_linker_flags = $(shell pkg-config --libs gmodule-2.0)
dlfcn_linker_flags   = -ldl

#opengl_linker_flags = -lGL -lGLU -lXxf86vm
#`pkg-config --cflags --libs GL GLU Xxf86vm`

math_linker_flags = -lm

zlib_linker_flags = -lz

#@MK@ifeq ($(build_vendor),apple)
#  realtime_linker_flags = 
#@MK@else
#  realtime_linker_flags = -lrt
#@MK@endif

dynamic_library_flags        = -DF2__DLFCN__SUPPORTED 
dynamic_library_linker_flags = $(dlfcn_linker_flags)

#dynamic_library_linker_flags = $(dlfcn_linker_flags) $(opengl_linker_flags) -lrt
#dynamic_library_flags        = $(shell pkg-config --cflags gmodule-2.0) -DF2__GMODULE__SUPPORTED 
#dynamic_library_linker_flags = $(gmodule_linker_flags)

trace_flags           = #-DF2__TRACE__ALL_POINTERS -DF2__TRACE__ALL_COMPILES 
compiled_image__flags = -DF2__INSTALL__BOOTSTRAP_IMG__FILENAME=\"$(plain__install__bootstrap__img)\" -DF2__COMPILE__BOOTSTRAP_REPL_IMG__FILENAME=\"$(compile__bootstrap__repl__img)\" -DF2__COMPILE__BOOTSTRAP_IMG__FILENAME=\"$(compile__bootstrap__img)\"

if XMLRPC_SUPPORTED
xmlrpc_ldadd   = $(shell xmlrpc-c-config abyss-server client --ldadd)
xmlrpc_cflags  = $(shell xmlrpc-c-config abyss-server client --cflags)
xmlrpc_ldflags = $(shell xmlrpc-c-config abyss-server client --ldflags)
endif

#system_cflags = -Dbuild_os=\"$(build_os)\" -Dbuild_vendor=\"$(build_vendor)\"

debug_flags    = -g -pg -fstack-check -DDEBUG -DDEBUG_MEMORY=1 -DF2__PROCESSOR_MUTEX__DEBUG -DF2__PTYPE__TYPE_CHECK -DF2__ASSERTIONS__DEBUG -DF2__PTYPE__TYPE_CHECK -DF2__DEBUG__PROTECTED_ALLOC_ARRAY -DDEBUG_MEMORY_POINTERS -DDEBUG_LOAD -DDEBUG_COMPILE -DDEBUG_BYTECODES #-DDEBUG_REDBLACKTREE -DDEBUG_MEMORY_VALID_PTRS 

optimize_flags = 

debug__cc_flags   = -Wall $(memory_flags) $(processor_flags) $(dynamic_library_flags) $(trace_flags) $(compiled_image__flags) $(GLU_CFLAGS) $(GL_CFLAGS) $(xmlrpc_cflags) $(GTK_CFLAGS) $(GTHREAD_CFLAGS) $(LIBAVCODEC_CFLAGS) $(LIBSWSCALE_CFLAGS) $(CAIRO_CFLAGS) $(debug_flags)
release__cc_flags = -Wall $(memory_flags) $(processor_flags) $(dynamic_library_flags) $(trace_flags) $(compiled_image__flags) $(GLU_CFLAGS) $(GL_CFLAGS) $(xmlrpc_cflags) $(GTK_CFLAGS) $(GTHREAD_CFLAGS) $(LIBAVCODEC_CFLAGS) $(LIBSWSCALE_CFLAGS) $(CAIRO_CFLAGS) $(optimize_flags)
athena__cc_flags  = $(release__cc_flags) -DF2__SINGLE_USER_32BIT_VERSION

#cc_flags = $(debug__cc_flags)
cc_flags = $(release__cc_flags)
#cc_flags = $(athena__cc_flags)


# added to fix MacOS X compile
install_sh = ./install-sh
mkdir_p = ${INSTALL} -d


bin/configurator: c/configurator.c
	mkdir -p bin
	mkdir -p lib/.libs
	gcc $(cc_flags) c/configurator.c -o $@

config_bit_num.h: bin/configurator
	rm -f config_bit_num.h
	echo "" > config_bit_num.h
	echo "#define char__bit_num      `bin/configurator char-bit_num`"      >> config_bit_num.h
	echo "#define short__bit_num     `bin/configurator short-bit_num`"     >> config_bit_num.h
	echo "#define int__bit_num       `bin/configurator int-bit_num`"       >> config_bit_num.h
	echo "#define long__bit_num      `bin/configurator long-bit_num`"      >> config_bit_num.h
	echo "#define long_long__bit_num `bin/configurator long_long-bit_num`" >> config_bit_num.h
	echo "#define pointer__bit_num   `bin/configurator pointer-bit_num`"   >> config_bit_num.h
	echo "#define float__bit_num     `bin/configurator float-bit_num`"     >> config_bit_num.h
	echo "#define double__bit_num    `bin/configurator double-bit_num`"    >> config_bit_num.h
	echo ""
	echo "#define char__bit_num      `bin/configurator char-bit_num`"
	echo "#define short__bit_num     `bin/configurator short-bit_num`"
	echo "#define int__bit_num       `bin/configurator int-bit_num`"
	echo "#define long__bit_num      `bin/configurator long-bit_num`"
	echo "#define long_long__bit_num `bin/configurator long_long-bit_num`"
	echo "#define pointer__bit_num   `bin/configurator pointer-bit_num`"
	echo "#define float__bit_num     `bin/configurator float-bit_num`"
	echo "#define double__bit_num    `bin/configurator double-bit_num`"
	echo ""

# compile the repl prompt (garbage collection is disabled until funk2 is stopped and a new repl image is used).
img/bootstrap-repl.img: bin/funk2$(EXEEXT)
	mkdir -p img
	rm -f img/bootstrap-repl.img
	rm -f img/bootstrap.img
	export LD_LIBRARY_PATH=lib/.libs; export DYLD_LIBRARY_PATH=lib/.libs; export PATH="lib/.libs:$$PATH"; bin/funk2 fu2/bootstrap-repl.fu2

# bootstrap the funk2 processor from a basic repl-prompt.
img/bootstrap.img: img/bootstrap-repl.img
	mkdir -p img
	rm -f img/bootstrap.img
	export LD_LIBRARY_PATH=lib/.libs; export DYLD_LIBRARY_PATH=lib/.libs; export PATH="lib/.libs:$$PATH"; bin/funk2 fu2/bootstrap.fu2

###### Makefile.am specifics below here ######

ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = lib/libfunk2.la \
                  extension/causality/libf2e_causality.la \
                  extension/cairo/libf2e_cairo.la \
                  extension/conceptnet/libf2e_conceptnet.la \
                  extension/event_stream/libf2e_event_stream.la \
                  extension/equals_hash/libf2e_equals_hash.la \
                  extension/fibermon/libf2e_fibermon.la \
                  extension/forgetful_event_stream/libf2e_forgetful_event_stream.la \
                  extension/forward_planner/libf2e_forward_planner.la \
                  extension/frame_ball/libf2e_frame_ball.la \
                  extension/graph_isomorphism/libf2e_graph_isomorphism.la \
                  extension/image/libf2e_image.la \
                  extension/image_sequence/libf2e_image_sequence.la \
                  extension/lick/libf2e_lick.la \
                  extension/mentality/libf2e_mentality.la \
                  extension/meta_semantic_frame_ball/libf2e_meta_semantic_frame_ball.la \
                  extension/meta_semantic_knowledge_base/libf2e_meta_semantic_knowledge_base.la \
                  extension/mindmon/libf2e_mindmon.la \
                  extension/movie/libf2e_movie.la \
                  extension/propogator/libf2e_propogator.la \
                  extension/semantic_action_event/libf2e_semantic_action_event.la \
                  extension/semantic_agent/libf2e_semantic_agent.la \
                  extension/semantic_event_sequence/libf2e_semantic_event_sequence.la \
                  extension/semantic_containment_object/libf2e_semantic_containment_object.la \
                  extension/semantic_directed_action_event/libf2e_semantic_directed_action_event.la \
                  extension/semantic_event/libf2e_semantic_event.la \
                  extension/semantic_frame_ball/libf2e_semantic_frame_ball.la \
                  extension/semantic_knowledge_base/libf2e_semantic_knowledge_base.la \
                  extension/semantic_object_type/libf2e_semantic_object_type.la \
                  extension/semantic_ordered_object/libf2e_semantic_ordered_object.la \
                  extension/semantic_object/libf2e_semantic_object.la \
                  extension/semantic_packable_object/libf2e_semantic_packable_object.la \
                  extension/semantic_physical_object/libf2e_semantic_physical_object.la \
                  extension/semantic_resource/libf2e_semantic_resource.la \
                  extension/semantic_resource_action_event/libf2e_semantic_resource_action_event.la \
                  extension/semantic_resource_action_sequence/libf2e_semantic_resource_action_sequence.la \
                  extension/semantic_temporal_object/libf2e_semantic_temporal_object.la \
                  extension/semantic_visual_object/libf2e_semantic_visual_object.la \
                  extension/timeline/libf2e_timeline.la

#bin_PROGRAMS    = bin/funk2-static

lib_libfunk2_la_SOURCES = \
  c/f2_agent.c \
  c/f2_array.c \
  c/f2_ansi.c \
  c/f2_apropos.c \
  c/f2_blocks_world.c \
  c/f2_buffered_file.c \
  c/f2_buffered_socket.c \
  c/f2_bug.c \
  c/f2_bytecodes.c \
  c/f2_cause.c \
  c/f2_chunk.c \
  c/f2_circular_buffer.c \
  c/f2_command_line.c \
  c/f2_compile.c \
  c/f2_compile_x86.c \
  c/f2_core_extension.c \
  c/f2_core_extension_funk.c \
  c/f2_cpu.c \
  c/f2_dlfcn.c \
  c/f2_dptr.c \
  c/f2_dynamic_memory.c \
  c/f2_fiber.c \
  c/f2_fileio.c \
  c/f2_frame_objects.c \
  c/f2_funk2_node.c \
  c/f2_funktional.c \
  c/f2_garbage_collector.c \
  c/f2_garbage_collector_pool.c \
  c/f2_globalenv.c \
  c/f2_glwindow.c \
  c/f2_gmodule.c \
  c/f2_graph.c \
  c/f2_graph_cluster.c \
  c/f2_graph_match_error_correcting.c \
  c/f2_graphviz.c \
  c/f2_gtk.c \
  c/f2_hash.c \
  c/f2_html.c \
  c/f2_knowledge.c \
  c/f2_larva.c \
  c/f2_load.c \
  c/f2_malloc.c \
  c/f2_management_thread.c \
  c/f2_memblock.c \
  c/f2_memory.c \
  c/f2_memorypool.c \
  c/f2_module_registration.c \
  c/f2_natural_language.c \
  c/f2_never_delete_list.c \
  c/f2_nil.c \
  c/f2_number.c \
  c/f2_object.c \
  c/f2_object_lattice.c \
  c/f2_opengl.c \
  c/f2_package.c \
  c/f2_packet.c \
  c/f2_partial_order.c \
  c/f2_peer_command_server.c \
  c/f2_perception_lattice.c \
  c/f2_physical_objects.c \
  c/f2_primes.c \
  c/f2_primobjects.c \
  c/f2_primobject__boolean.c \
  c/f2_primobject__char_pointer.c \
  c/f2_primobject__circular_buffer.c \
  c/f2_primobject__doublelinklist.c \
  c/f2_primobject__dynamic_library.c \
  c/f2_primobject__environment.c \
  c/f2_primobject__fiber_trigger.c \
  c/f2_primobject__frame.c \
  c/f2_primobject__hash.c \
  c/f2_primobject__list.c \
  c/f2_primobject__largeinteger.c \
  c/f2_primobject__object.c \
  c/f2_primobject__object_type.c \
  c/f2_primobject__ptypehash.c \
  c/f2_primobject__redblacktree.c \
  c/f2_primobject__set.c \
  c/f2_primobject__stream.c \
  c/f2_primobject__tensor.c \
  c/f2_primobject__text_buffer.c \
  c/f2_primobject__traced_mutex.c \
  c/f2_primobject_type.c \
  c/f2_primobject_type_handler.c \
  c/f2_print.c \
  c/f2_primfunks.c \
  c/f2_primfunks__errno.c \
  c/f2_primfunks__fcntl.c \
  c/f2_primfunks__ioctl.c \
  c/f2_primfunks__locale.c \
  c/f2_processor.c \
  c/f2_processor_mutex.c \
  c/f2_processor_thread.c \
  c/f2_processor_thread_handler.c \
  c/f2_protected_alloc_array.c \
  c/f2_ptype.c \
  c/f2_ptypes.c \
  c/f2_reader.c \
  c/f2_redblacktree.c \
  c/f2_simple_repl.c \
  c/f2_scheduler.c \
  c/f2_scheduler_thread_controller.c \
  c/f2_search.c \
  c/f2_serialize.c \
  c/f2_set.c \
  c/f2_signal.c \
  c/f2_simple_graph.c \
  c/f2_socket.c \
  c/f2_socket_client.c \
  c/f2_socket_server.c \
  c/f2_sort.c \
  c/f2_status.c \
  c/f2_string.c \
  c/f2_surrogate_parent.c \
  c/f2_terminal_print.c \
  c/f2_termios.c \
  c/f2_thought_process.c \
  c/f2_tricolor_set.c \
  c/f2_time.c \
  c/f2_trace.c \
  c/f2_user_thread_controller.c \
  c/f2_virtual_processor.c \
  c/f2_virtual_processor_handler.c \
  c/f2_virtual_processor_thread.c \
  c/f2_xmlrpc.c \
  c/f2_zlib.c \
  c/funk2.c \
  config_bit_num.h

extension_causality_libf2e_causality_la_SOURCES                                                 = extension/causality/causality.c
extension_cairo_libf2e_cairo_la_SOURCES                                                         = extension/cairo/cairo.c
extension_conceptnet_libf2e_conceptnet_la_SOURCES                                               = extension/conceptnet/conceptnet.c
extension_event_stream_libf2e_event_stream_la_SOURCES                                           = extension/event_stream/event_stream.c
extension_equals_hash_libf2e_equals_hash_la_SOURCES                                             = extension/equals_hash/equals_hash.c
extension_fibermon_libf2e_fibermon_la_SOURCES                                                   = extension/fibermon/fibermon.c
extension_forgetful_event_stream_libf2e_forgetful_event_stream_la_SOURCES                       = extension/forgetful_event_stream/forgetful_event_stream.c
extension_forward_planner_libf2e_forward_planner_la_SOURCES                                     = extension/forward_planner/forward_planner.c
extension_frame_ball_libf2e_frame_ball_la_SOURCES                                               = extension/frame_ball/frame_ball.c
extension_graph_isomorphism_libf2e_graph_isomorphism_la_SOURCES                                 = extension/graph_isomorphism/graph_isomorphism.c
extension_image_libf2e_image_la_SOURCES                                                         = extension/image/image.c
extension_image_sequence_libf2e_image_sequence_la_SOURCES                                       = extension/image_sequence/image_sequence.c
extension_lick_libf2e_lick_la_SOURCES                                                           = extension/lick/lick.c
extension_mentality_libf2e_mentality_la_SOURCES                                                 = extension/mentality/mentality.c
extension_meta_semantic_frame_ball_libf2e_meta_semantic_frame_ball_la_SOURCES                   = extension/meta_semantic_frame_ball/meta_semantic_frame_ball.c
extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la_SOURCES           = extension/meta_semantic_knowledge_base/meta_semantic_knowledge_base.c
extension_mindmon_libf2e_mindmon_la_SOURCES                                                     = extension/mindmon/mindmon.c
extension_movie_libf2e_movie_la_SOURCES                                                         = extension/movie/movie.c
extension_propogator_libf2e_propogator_la_SOURCES                                               = extension/propogator/propogator.c
extension_semantic_action_event_libf2e_semantic_action_event_la_SOURCES                         = extension/semantic_action_event/semantic_action_event.c
extension_semantic_agent_libf2e_semantic_agent_la_SOURCES                                       = extension/semantic_agent/semantic_agent.c
extension_semantic_event_sequence_libf2e_semantic_event_sequence_la_SOURCES                     = extension/semantic_event_sequence/semantic_event_sequence.c
extension_semantic_containment_object_libf2e_semantic_containment_object_la_SOURCES             = extension/semantic_containment_object/semantic_containment_object.c
extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la_SOURCES       = extension/semantic_directed_action_event/semantic_directed_action_event.c
extension_semantic_event_libf2e_semantic_event_la_SOURCES                                       = extension/semantic_event/semantic_event.c
extension_semantic_frame_ball_libf2e_semantic_frame_ball_la_SOURCES                             = extension/semantic_frame_ball/semantic_frame_ball.c
extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la_SOURCES                     = extension/semantic_knowledge_base/semantic_knowledge_base.c
extension_semantic_ordered_object_libf2e_semantic_ordered_object_la_SOURCES                     = extension/semantic_ordered_object/semantic_ordered_object.c
extension_semantic_object_type_libf2e_semantic_object_type_la_SOURCES                           = extension/semantic_object_type/semantic_object_type.c
extension_semantic_object_libf2e_semantic_object_la_SOURCES                                     = extension/semantic_object/semantic_object.c
extension_semantic_packable_object_libf2e_semantic_packable_object_la_SOURCES                   = extension/semantic_packable_object/semantic_packable_object.c
extension_semantic_physical_object_libf2e_semantic_physical_object_la_SOURCES                   = extension/semantic_physical_object/semantic_physical_object.c
extension_semantic_resource_libf2e_semantic_resource_la_SOURCES                                 = extension/semantic_resource/semantic_resource.c
extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la_SOURCES       = extension/semantic_resource_action_event/semantic_resource_action_event.c
extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la_SOURCES = extension/semantic_resource_action_sequence/semantic_resource_action_sequence.c
extension_semantic_temporal_object_libf2e_semantic_temporal_object_la_SOURCES                   = extension/semantic_temporal_object/semantic_temporal_object.c
extension_semantic_visual_object_libf2e_semantic_visual_object_la_SOURCES                       = extension/semantic_visual_object/semantic_visual_object.c
extension_timeline_libf2e_timeline_la_SOURCES                                                   = extension/timeline/timeline.c

#bin_funk2_static_SOURCES = c/funk2_main.c $(lib_libfunk2_la_SOURCES)

FUNK2_VERSION=`cat version`

FUNK2_RELEASE=$(FUNK2_VERSION)
FUNK2_LIBRARY_VERSION=0:0:0
#                     #.#.#
#                     | | |
#              +------+ | +---+
#              |        |     |
#            current:revision:age
#              |        |     |
#              |        |     +- increment if interfaces have been added
#              |        |        set to zero if interfaces have been removed
#              |        |        or changed
#              |        +- increment if source code has changed
#              |           set to zero if current is incremented
#              +- increment if interfaces have been added, removed or changed

lib_libfunk2_la_LDFLAGS = -no-undefined -version-info $(FUNK2_LIBRARY_VERSION) -release $(FUNK2_RELEASE) $(dynamic_library_linker_flags) $(math_linker_flags) $(xmlrpc_ldflags) $(xmlrpc_ldadd) $(zlib_linker_flags) $(GTK_LIBS) $(GTHREAD_LIBS) $(LIBAVCODEC_LIBS) $(LIBSWSCALE_LIBS) $(CAIRO_LIBS) 
lib_libfunk2_la_CFLAGS  = $(cc_flags)

bin_funk2_static_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
bin_funk2_static_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

all_core_extensions = \
  $(extension_cairo_libf2e_cairo_la) \
  $(extension_causality_libf2e_causality_la) \
  $(extension_conceptnet_libf2e_conceptnet_la) \
  $(extension_equals_hash_libf2e_equals_hash_la) \
  $(extension_event_stream_libf2e_event_stream_la) \
  $(extension_fibermon_libf2e_fibermon_la) \
  $(extension_forgetful_event_stream_libf2e_forgetful_event_stream_la) \
  $(extension_forward_planner_libf2e_forward_planner_la) \
  $(extension_frame_ball_libf2e_frame_ball_la) \
  $(extension_graph_isomorphism_libf2e_graph_isomorphism_la) \
  $(extension_image_libf2e_image_la) \
  $(extension_image_sequence_libf2e_image_sequence_la) \
  $(extension_lick_libf2e_lick_la) \
  $(extension_mentality_libf2e_mentality_la) \
  $(extension_meta_semantic_frame_ball_libf2e_meta_semantic_frame_ball_la) \
  $(extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la) \
  $(extension_mindmon_libf2e_mindmon_la) \
  $(extension_movie_libf2e_movie_la) \
  $(extension_propogator_libf2e_propogator_la) \
  $(extension_semantic_action_event_libf2e_semantic_action_event_la) \
  $(extension_semantic_agent_libf2e_semantic_agent_la) \
  $(extension_semantic_containment_object_libf2e_semantic_containment_object_la) \
  $(extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la) \
  $(extension_semantic_event_libf2e_semantic_event) \
  $(extension_semantic_event_sequence_libf2e_semantic_event_sequence_la) \
  $(extension_semantic_frame_ball_libf2e_semantic_frame_ball) \
  $(extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la) \
  $(extension_semantic_ordered_object_libf2e_semantic_ordered_object_la) \
  $(extension_semantic_object_type_libf2e_semantic_object_type_la) \
  $(extension_semantic_object_libf2e_semantic_object_la) \
  $(extension_semantic_packable_object_libf2e_semantic_packable_object_la) \
  $(extension_semantic_physical_object_libf2e_semantic_physical_object_la) \
  $(extension_semantic_resource_libf2e_semantic_resource_la) \
  $(extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la) \
  $(extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la) \
  $(extension_semantic_temporal_object_libf2e_semantic_temporal_object_la) \
  $(extension_semantic_visual_object_libf2e_semantic_visual_object_la) \
  $(extension_timeline_libf2e_timeline_la)


extension_equals_hash_libf2e_equals_hash_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_equals_hash_libf2e_equals_hash_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_fibermon_libf2e_fibermon_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_fibermon_libf2e_fibermon_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_image_libf2e_image_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_image_libf2e_image_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_image_sequence_libf2e_image_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_image_sequence_libf2e_image_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_movie_libf2e_movie_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_movie_libf2e_movie_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_cairo_libf2e_cairo_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_cairo_libf2e_cairo_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_causality_libf2e_causality_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_causality_libf2e_causality_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_conceptnet_libf2e_conceptnet_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_conceptnet_libf2e_conceptnet_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_event_stream_libf2e_event_stream_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_event_stream_libf2e_event_stream_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_forgetful_event_stream_libf2e_forgetful_event_stream_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_forgetful_event_stream_libf2e_forgetful_event_stream_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_forward_planner_libf2e_forward_planner_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_forward_planner_libf2e_forward_planner_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_frame_ball_libf2e_frame_ball_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_frame_ball_libf2e_frame_ball_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_graph_isomorphism_libf2e_graph_isomorphism_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_graph_isomorphism_libf2e_graph_isomorphism_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_propogator_libf2e_propogator_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_propogator_libf2e_propogator_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_action_event_libf2e_semantic_action_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_action_event_libf2e_semantic_action_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_agent_libf2e_semantic_agent_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_agent_libf2e_semantic_agent_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_sequence_libf2e_semantic_event_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_sequence_libf2e_semantic_event_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_containment_object_libf2e_semantic_containment_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_containment_object_libf2e_semantic_containment_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_libf2e_semantic_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_libf2e_semantic_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_frame_ball_libf2e_semantic_frame_ball_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_frame_ball_libf2e_semantic_frame_ball_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_lick_libf2e_lick_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_lick_libf2e_lick_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_mentality_libf2e_mentality_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_mentality_libf2e_mentality_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_meta_semantic_frame_ball_libf2e_meta_semantic_frame_ball_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_meta_semantic_frame_ball_libf2e_meta_semantic_frame_ball_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_mindmon_libf2e_mindmon_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_mindmon_libf2e_mindmon_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_ordered_object_libf2e_semantic_ordered_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_ordered_object_libf2e_semantic_ordered_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_object_type_libf2e_semantic_object_type_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_object_type_libf2e_semantic_object_type_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_object_libf2e_semantic_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_object_libf2e_semantic_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_packable_object_libf2e_semantic_packable_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_packable_object_libf2e_semantic_packable_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_physical_object_libf2e_semantic_physical_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_physical_object_libf2e_semantic_physical_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_libf2e_semantic_resource_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_libf2e_semantic_resource_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_temporal_object_libf2e_semantic_temporal_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_temporal_object_libf2e_semantic_temporal_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_visual_object_libf2e_semantic_visual_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_visual_object_libf2e_semantic_visual_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_timeline_libf2e_timeline_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_timeline_libf2e_timeline_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)


CONFIGURE_DEPENDENCIES = config_bit_num.h config_compile_time_id.h
CONFIG_CLEAN_FILES     = config_bit_num.h config_compile_time_id.h

AM_MAKEFLAGS = img/bootstrap.img

clean-img:
	rm -f img/bootstrap-repl.img
	rm -f img/bootstrap.img

clean: clean-am clean-img
	rm -f config_compile_time_id.h
	rm -f bin/funk2$(EXEEXT)
	mkdir -p lib/.libs

make-install-sh:
	echo "#!/bin/sh"                                                                    > install-sh
	echo "echo \"\""                                                                   >> install-sh
	echo "echo \"make: performing system-wide installation of funk2\""                 >> install-sh
	echo "echo \"\""                                                                   >> install-sh
	echo "echo \"  install__bin__dir     = $(chroot__install__bin__dir)\""             >> install-sh
#	echo "echo \"  install__lib__dir     = $(chroot__install__lib__dir)\""             >> install-sh
	echo "echo \"  install__include__dir = $(chroot__install__include__dir)\""         >> install-sh
	echo "echo \"\""                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__img__dir)"                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__bin__dir)"                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__include__dir)"                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__system_bin__dir)"                          >> install-sh
	echo "mkdir -m755 -p $(chroot__install__icons__dir)"                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__man__dir)"                                 >> install-sh
	echo "install -m755 $(compile__funk2) $(chroot__install__funk2)"                   >> install-sh
	echo "install -m644 $(compile__bootstrap__img) $(chroot__install__bootstrap__img)" >> install-sh
	echo "install -m644 c/*.h $(chroot__install__include__dir)"                        >> install-sh
	echo "install -m644 $(source__icons__dir)* $(chroot__install__icons__dir)"         >> install-sh
	echo "gzip -c debian/funk2.1 > debian/funk2.1.gz"                                  >> install-sh
	echo "install -m644 debian/funk2.1.gz $(chroot__install__man__dir)"                >> install-sh
	chmod a+x install-sh

bin/funk2$(EXEEXT): lib/libfunk2.la $(all_core_extensions)
	$(COMPILE) -o $@ c/funk2_main.c $(GL_CFLAGS) $(GLU_CFLAGS) $(GTK_CFLAGS) $(GTHREAD_CFLAGS) $(LIBAVCODEC_CFLAGS) $(LIBSWSCALE_CFLAGS) $(CAIRO_CFLAGS) -Llib/.libs -lfunk2

install: install-am make-install-sh
	./install-sh


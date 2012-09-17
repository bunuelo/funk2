# 
# Copyright (c) 2007-2012 Bo Morgan.
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
source__built_in__dir        = $(source__funk2__dir)built-in/
source__extension__dir       = $(source__funk2__dir)extension/
source__test__dir            = $(source__funk2__dir)test/
source__example__dir         = $(source__funk2__dir)example/
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
chroot__install__img__dir            = $(chroot_install_root_dir)var/lib/funk2/img/
chroot__install__fu2__dir            = $(chroot_install_root_dir)var/lib/funk2/fu2/
chroot__install__built_in__dir       = $(chroot_install_root_dir)var/lib/funk2/built-in/
chroot__install__extension__dir      = $(chroot_install_root_dir)var/lib/funk2/extension/
chroot__install__test__dir           = $(chroot_install_root_dir)var/lib/funk2/test/
chroot__install__example__dir        = $(chroot_install_root_dir)var/lib/funk2/example/
chroot__install__icons__dir          = $(chroot_install_root_dir)var/lib/funk2/icons/
chroot__install__man__dir            = $(chroot_install_root_dir)usr/share/man/man1/
chroot__install__funk2               = $(chroot__install__bin__dir)funk2
chroot__install__bootstrap__img      = $(chroot__install__img__dir)bootstrap.img

plain__install__system_bin__dir     = $(plain_install_root_dir)usr/bin/
plain__install__bin__dir            = $(plain_install_root_dir)usr/bin/
plain__install__include__dir        = $(plain_install_root_dir)usr/include/funk2/
plain__install__img__dir            = $(plain_install_root_dir)var/lib/funk2/img/
plain__install__fu2__dir            = $(plain_install_root_dir)var/lib/funk2/fu2/
plain__install__built_in__dir       = $(plain_install_root_dir)var/lib/funk2/built-in/
plain__install__extension__dir      = $(plain_install_root_dir)var/lib/funk2/extension/
plain__install__test__dir           = $(plain_install_root_dir)var/lib/funk2/test/
plain__install__example__dir        = $(plain_install_root_dir)var/lib/funk2/example/
plain__install__icons__dir          = $(plain_install_root_dir)var/lib/funk2/icons/
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

libs = -lpthread

funk2_objs   = $(funk2_server_objs)

dlfcn_linker_flags   = -ldl

math_linker_flags = -lm

zlib_linker_flags = -lz

dynamic_library_flags        = -DF2__DLFCN__SUPPORTED 
dynamic_library_linker_flags = $(dlfcn_linker_flags)

compiled_image__flags = -DF2__INSTALL__BOOTSTRAP_IMG__FILENAME=\"$(plain__install__bootstrap__img)\" -DF2__COMPILE__BOOTSTRAP_REPL_IMG__FILENAME=\"$(compile__bootstrap__repl__img)\" -DF2__COMPILE__BOOTSTRAP_IMG__FILENAME=\"$(compile__bootstrap__img)\"

if NEED_REALTIME_LINK
realtime_linker_flags = -lrt
endif

if XMLRPC_SUPPORTED
xmlrpc_ldadd   = $(shell xmlrpc-c-config abyss-server client --ldadd)
xmlrpc_cflags  = $(shell xmlrpc-c-config abyss-server client --cflags)
xmlrpc_ldflags = $(shell xmlrpc-c-config abyss-server client --ldflags)
endif

debug_flags    = -g -pg -fstack-check -DDEBUG -DDEBUG_MEMORY=1 #-DF2__PROCESSOR_MUTEX__DEBUG -DF2__DEBUG__OBJECT__TYPE -DF2__PTYPE__TYPE_CHECK -DF2__ASSERTIONS__DEBUG -DF2__DEBUG__PROTECTED_ALLOC_ARRAY -DDEBUG_MEMORY_POINTERS -DDEBUG_LOAD -DDEBUG_COMPILE -DDEBUG_BYTECODES #-DDEBUG_REDBLACKTREE -DDEBUG_MEMORY_VALID_PTRS 

optimize_flags = 

debug__cc_flags   = -Wall $(memory_flags) $(processor_flags) $(dynamic_library_flags) $(compiled_image__flags) $(GLU_CFLAGS) $(GL_CFLAGS) $(xmlrpc_cflags) $(GTK_CFLAGS) $(GTHREAD_CFLAGS) $(LIBAVCODEC_CFLAGS) $(LIBSWSCALE_CFLAGS) $(CAIRO_CFLAGS) $(debug_flags)
release__cc_flags = -Wall $(memory_flags) $(processor_flags) $(dynamic_library_flags) $(compiled_image__flags) $(GLU_CFLAGS) $(GL_CFLAGS) $(xmlrpc_cflags) $(GTK_CFLAGS) $(GTHREAD_CFLAGS) $(LIBAVCODEC_CFLAGS) $(LIBSWSCALE_CFLAGS) $(CAIRO_CFLAGS) $(optimize_flags)
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
	gcc $(cc_flags) c/configurator.c -lrt -o $@

config_bit_num.h: bin/configurator
	rm -f config_bit_num.h
	echo "" > config_bit_num.h
	echo "#define char__bit_num          `bin/configurator char-bit_num`"           >> config_bit_num.h
	echo "#define short__bit_num         `bin/configurator short-bit_num`"          >> config_bit_num.h
	echo "#define int__bit_num           `bin/configurator int-bit_num`"            >> config_bit_num.h
	echo "#define long__bit_num          `bin/configurator long-bit_num`"           >> config_bit_num.h
	echo "#define long_long__bit_num     `bin/configurator long_long-bit_num`"      >> config_bit_num.h
	echo "#define pointer__bit_num       `bin/configurator pointer-bit_num`"        >> config_bit_num.h
	echo "#define float__bit_num         `bin/configurator float-bit_num`"          >> config_bit_num.h
	echo "#define double__bit_num        `bin/configurator double-bit_num`"         >> config_bit_num.h
	echo "#define processor_num          `bin/configurator processor_num`"          >> config_bit_num.h
	echo "#define deep_sleep_nanoseconds `bin/configurator deep_sleep_nanoseconds`" >> config_bit_num.h
	echo ""
	echo "#define char__bit_num          `bin/configurator char-bit_num`"
	echo "#define short__bit_num         `bin/configurator short-bit_num`"
	echo "#define int__bit_num           `bin/configurator int-bit_num`"
	echo "#define long__bit_num          `bin/configurator long-bit_num`"
	echo "#define long_long__bit_num     `bin/configurator long_long-bit_num`"
	echo "#define pointer__bit_num       `bin/configurator pointer-bit_num`"
	echo "#define float__bit_num         `bin/configurator float-bit_num`"
	echo "#define double__bit_num        `bin/configurator double-bit_num`"
	echo "#define processor_num          `bin/configurator processor_num`"
	echo "#define deep_sleep_nanoseconds `bin/configurator deep_sleep_nanoseconds`"
	echo ""

extra_library_path="lib/.libs/:/opt/intel/Compiler/11.1/038/lib/intel64/"

# compile the repl prompt (garbage collection is disabled until funk2 is stopped and a new repl image is used).
img/bootstrap-repl.img: bin/funk2$(EXEEXT)
	mkdir -p img
	rm -f img/bootstrap-repl.img
	rm -f img/bootstrap.img
	export LD_LIBRARY_PATH=$(extra_library_path); export DYLD_LIBRARY_PATH=$(extra_library_path); export PATH="lib/.libs:$$PATH"; bin/funk2 fu2/bootstrap-repl.fu2

# bootstrap the funk2 processor from a basic repl-prompt.
img/bootstrap.img: img/bootstrap-repl.img
	mkdir -p img
	rm -f img/bootstrap.img
	export LD_LIBRARY_PATH=$(extra_library_path); export DYLD_LIBRARY_PATH=$(extra_library_path); export PATH="$(extra_library_path):$$PATH"; bin/funk2 fu2/bootstrap.fu2

###### Makefile.am specifics below here ######

ACLOCAL_AMFLAGS = -I m4



all_core_extensions = extension/blocks_world/libf2e_blocks_world.la \
                      extension/cairo/libf2e_cairo.la \
                      extension/concept_version_space/libf2e_concept_version_space.la \
                      extension/conceptnet/libf2e_conceptnet.la \
                      extension/event_stream/libf2e_event_stream.la \
                      extension/equals_hash/libf2e_equals_hash.la \
                      extension/fibermon/libf2e_fibermon.la \
                      extension/forgetful_event_stream/libf2e_forgetful_event_stream.la \
                      extension/forward_planner/libf2e_forward_planner.la \
                      extension/frame_ball/libf2e_frame_ball.la \
                      extension/graph_isomorphism/libf2e_graph_isomorphism.la \
                      extension/gtk_extension/libf2e_gtk_extension.la \
                      extension/image/libf2e_image.la \
                      extension/image_sequence/libf2e_image_sequence.la \
                      extension/interval_tree/libf2e_interval_tree.la \
                      extension/lick/libf2e_lick.la \
                      extension/meta_semantic_knowledge_base/libf2e_meta_semantic_knowledge_base.la \
                      extension/movie/libf2e_movie.la \
                      extension/keyboard/libf2e_keyboard.la \
                      extension/propogator/libf2e_propogator.la \
                      extension/semantic_action/libf2e_semantic_action.la \
                      extension/semantic_action_knowledge_base/libf2e_semantic_action_knowledge_base.la \
                      extension/semantic_action_event/libf2e_semantic_action_event.la \
                      extension/semantic_agent/libf2e_semantic_agent.la \
                      extension/semantic_causal_event/libf2e_semantic_causal_event.la \
                      extension/semantic_dependency/libf2e_semantic_dependency.la \
                      extension/semantic_event_sequence/libf2e_semantic_event_sequence.la \
                      extension/semantic_causal_object/libf2e_semantic_causal_object.la \
                      extension/semantic_category/libf2e_semantic_category.la \
                      extension/semantic_causal_concept/libf2e_semantic_causal_concept.la \
                      extension/semantic_containment_object/libf2e_semantic_containment_object.la \
                      extension/semantic_counterfactual_transframe/libf2e_semantic_counterfactual_transframe.la \
                      extension/semantic_directed_action_event/libf2e_semantic_directed_action_event.la \
                      extension/semantic_event/libf2e_semantic_event.la \
                      extension/semantic_event_transframe/libf2e_semantic_event_transframe.la \
                      extension/semantic_event_tree/libf2e_semantic_event_tree.la \
                      extension/semantic_expectation_failure/libf2e_semantic_expectation_failure.la \
                      extension/semantic_frame/libf2e_semantic_frame.la \
                      extension/semantic_know_of_existence_event/libf2e_semantic_know_of_existence_event.la \
                      extension/semantic_know_of_relationship_event/libf2e_semantic_know_of_relationship_event.la \
                      extension/semantic_knowledge_base/libf2e_semantic_knowledge_base.la \
                      extension/semantic_object_type_event/libf2e_semantic_object_type_event.la \
                      extension/semantic_ordered_object/libf2e_semantic_ordered_object.la \
                      extension/semantic_object/libf2e_semantic_object.la \
                      extension/semantic_packable_object/libf2e_semantic_packable_object.la \
                      extension/semantic_partial_state/libf2e_semantic_partial_state.la \
                      extension/semantic_plan_object/libf2e_semantic_plan_object.la \
                      extension/semantic_plan_object_type_event/libf2e_semantic_plan_object_type_event.la \
                      extension/semantic_plan_object_type_relation_event/libf2e_semantic_plan_object_type_relation_event.la \
                      extension/semantic_plan_operator_activation/libf2e_semantic_plan_operator_activation.la \
                      extension/semantic_plan_operator_parallel/libf2e_semantic_plan_operator_parallel.la \
                      extension/semantic_plan_operator_sequence/libf2e_semantic_plan_operator_sequence.la \
                      extension/semantic_plan_operator_suppression/libf2e_semantic_plan_operator_suppression.la \
                      extension/semantic_reflective_object/libf2e_semantic_reflective_object.la \
                      extension/semantic_reflective_object_type_event/libf2e_semantic_reflective_object_type_event.la \
                      extension/semantic_reflective_object_type_property_event/libf2e_semantic_reflective_object_type_property_event.la \
                      extension/semantic_reflective_object_type_relation_event/libf2e_semantic_reflective_object_type_relation_event.la \
                      extension/semantic_event_knowledge_base/libf2e_semantic_event_knowledge_base.la \
                      extension/semantic_goal/libf2e_semantic_goal.la \
                      extension/semantic_goal_event/libf2e_semantic_goal_event.la \
                      extension/semantic_goal_action_causal_hypothesis/libf2e_semantic_goal_action_causal_hypothesis.la \
                      extension/semantic_planner/libf2e_semantic_planner.la \
                      extension/semantic_proprioception/libf2e_semantic_proprioception.la \
                      extension/semantic_proprioceptual_object/libf2e_semantic_proprioceptual_object.la \
                      extension/semantic_proprioceptual_orientation/libf2e_semantic_proprioceptual_orientation.la \
                      extension/semantic_proprioceptual_position/libf2e_semantic_proprioceptual_position.la \
                      extension/semantic_realm/libf2e_semantic_realm.la \
                      extension/semantic_relationship_key/libf2e_semantic_relationship_key.la \
                      extension/semantic_resource/libf2e_semantic_resource.la \
                      extension/semantic_resource_action_event/libf2e_semantic_resource_action_event.la \
                      extension/semantic_resource_action_sequence/libf2e_semantic_resource_action_sequence.la \
                      extension/semantic_resource_event_knowledge_base/libf2e_semantic_resource_event_knowledge_base.la \
                      extension/semantic_self/libf2e_semantic_self.la \
                      extension/semantic_situation/libf2e_semantic_situation.la \
                      extension/semantic_situation_category/libf2e_semantic_situation_category.la \
                      extension/semantic_situation_transition/libf2e_semantic_situation_transition.la \
                      extension/semantic_somatosensation/libf2e_semantic_somatosensation.la \
                      extension/semantic_somatosensory_object/libf2e_semantic_somatosensory_object.la \
                      extension/semantic_temporal_object/libf2e_semantic_temporal_object.la \
                      extension/semantic_time/libf2e_semantic_time.la \
                      extension/semantic_visual_object/libf2e_semantic_visual_object.la \
                      extension/timeline/libf2e_timeline.la \
                      extension/transframe/libf2e_transframe.la

finish_compiling_all_core_extensions: $(all_core_extensions)
	cp -fa extension/blocks_world/.libs/libf2e_*.*                                                                 $(compile__lib__dir)
	cp -fa extension/cairo/.libs/libf2e_*.*                                                                               $(compile__lib__dir)
	cp -fa extension/concept_version_space/.libs/libf2e_*.*                                               $(compile__lib__dir)
	cp -fa extension/conceptnet/.libs/libf2e_*.*                                                                     $(compile__lib__dir)
	cp -fa extension/event_stream/.libs/libf2e_*.*                                                                 $(compile__lib__dir)
	cp -fa extension/equals_hash/.libs/libf2e_*.*                                                                   $(compile__lib__dir)
	cp -fa extension/fibermon/.libs/libf2e_*.*                                                                         $(compile__lib__dir)
	cp -fa extension/forgetful_event_stream/.libs/libf2e_*.*                                             $(compile__lib__dir)
	cp -fa extension/forward_planner/.libs/libf2e_*.*                                                           $(compile__lib__dir)
	cp -fa extension/frame_ball/.libs/libf2e_*.*                                                                     $(compile__lib__dir)
	cp -fa extension/graph_isomorphism/.libs/libf2e_*.*                                                       $(compile__lib__dir)
	cp -fa extension/gtk_extension/.libs/libf2e_*.*                                                               $(compile__lib__dir)
	cp -fa extension/image/.libs/libf2e_*.*                                                                               $(compile__lib__dir)
	cp -fa extension/image_sequence/.libs/libf2e_*.*                                                             $(compile__lib__dir)
	cp -fa extension/interval_tree/.libs/libf2e_*.*                                                               $(compile__lib__dir)
	cp -fa extension/lick/.libs/libf2e_*.*                                                                                 $(compile__lib__dir)
	cp -fa extension/meta_semantic_knowledge_base/.libs/libf2e_*.*                                 $(compile__lib__dir)
	cp -fa extension/movie/.libs/libf2e_*.*                                                                               $(compile__lib__dir)
	cp -fa extension/keyboard/.libs/libf2e_*.*                                                                         $(compile__lib__dir)
	cp -fa extension/propogator/.libs/libf2e_*.*                                                                     $(compile__lib__dir)
	cp -fa extension/semantic_action/.libs/libf2e_*.*                                                           $(compile__lib__dir)
	cp -fa extension/semantic_action_knowledge_base/.libs/libf2e_*.*                             $(compile__lib__dir)
	cp -fa extension/semantic_action_event/.libs/libf2e_*.*                                               $(compile__lib__dir)
	cp -fa extension/semantic_agent/.libs/libf2e_*.*                                                             $(compile__lib__dir)
	cp -fa extension/semantic_causal_event/.libs/libf2e_*.*                                               $(compile__lib__dir)
	cp -fa extension/semantic_dependency/.libs/libf2e_*.*                                           $(compile__lib__dir)
	cp -fa extension/semantic_event_sequence/.libs/libf2e_*.*                                           $(compile__lib__dir)
	cp -fa extension/semantic_causal_object/.libs/libf2e_*.*                                             $(compile__lib__dir)
	cp -fa extension/semantic_category/.libs/libf2e_*.*                                                       $(compile__lib__dir)
	cp -fa extension/semantic_causal_concept/.libs/libf2e_*.*                                           $(compile__lib__dir)
	cp -fa extension/semantic_containment_object/.libs/libf2e_*.*                                   $(compile__lib__dir)
	cp -fa extension/semantic_counterfactual_transframe/.libs/libf2e_*.*                             $(compile__lib__dir)
	cp -fa extension/semantic_directed_action_event/.libs/libf2e_*.*                             $(compile__lib__dir)
	cp -fa extension/semantic_event/.libs/libf2e_*.*                                                             $(compile__lib__dir)
	cp -fa extension/semantic_event_transframe/.libs/libf2e_*.*                                       $(compile__lib__dir)
	cp -fa extension/semantic_event_tree/.libs/libf2e_*.*                                                   $(compile__lib__dir)
	cp -fa extension/semantic_expectation_failure/.libs/libf2e_*.*                                                             $(compile__lib__dir)
	cp -fa extension/semantic_frame/.libs/libf2e_*.*                                                             $(compile__lib__dir)
	cp -fa extension/semantic_know_of_existence_event/.libs/libf2e_*.*                         $(compile__lib__dir)
	cp -fa extension/semantic_know_of_relationship_event/.libs/libf2e_*.*                   $(compile__lib__dir)
	cp -fa extension/semantic_knowledge_base/.libs/libf2e_*.*                                           $(compile__lib__dir)
	cp -fa extension/semantic_object_type_event/.libs/libf2e_*.*                                     $(compile__lib__dir)
	cp -fa extension/semantic_ordered_object/.libs/libf2e_*.*                                           $(compile__lib__dir)
	cp -fa extension/semantic_object/.libs/libf2e_*.*                                                           $(compile__lib__dir)
	cp -fa extension/semantic_packable_object/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_partial_state/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_reflective_object/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_plan_object/.libs/libf2e_*.*                                                 $(compile__lib__dir)
	cp -fa extension/semantic_plan_object_type_event/.libs/libf2e_*.*                           $(compile__lib__dir)
	cp -fa extension/semantic_plan_object_type_relation_event/.libs/libf2e_*.*         $(compile__lib__dir)
	cp -fa extension/semantic_plan_operator_activation/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_plan_operator_parallel/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_plan_operator_sequence/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_plan_operator_suppression/.libs/libf2e_*.*                               $(compile__lib__dir)
	cp -fa extension/semantic_event_knowledge_base/.libs/libf2e_*.*                               $(compile__lib__dir)
	cp -fa extension/semantic_goal/.libs/libf2e_*.*                                                               $(compile__lib__dir)
	cp -fa extension/semantic_goal_event/.libs/libf2e_*.*                                                   $(compile__lib__dir)
	cp -fa extension/semantic_goal_action_causal_hypothesis/.libs/libf2e_*.*             $(compile__lib__dir)
	cp -fa extension/semantic_reflective_object_type_event/.libs/libf2e_*.*                   $(compile__lib__dir)
	cp -fa extension/semantic_reflective_object_type_property_event/.libs/libf2e_*.* $(compile__lib__dir)
	cp -fa extension/semantic_reflective_object_type_relation_event/.libs/libf2e_*.* $(compile__lib__dir)
	cp -fa extension/semantic_planner/.libs/libf2e_*.*                                                         $(compile__lib__dir)
	cp -fa extension/semantic_proprioception/.libs/libf2e_*.*                                           $(compile__lib__dir)
	cp -fa extension/semantic_proprioceptual_object/.libs/libf2e_*.*                             $(compile__lib__dir)
	cp -fa extension/semantic_proprioceptual_orientation/.libs/libf2e_*.*                   $(compile__lib__dir)
	cp -fa extension/semantic_proprioceptual_position/.libs/libf2e_*.*                         $(compile__lib__dir)
	cp -fa extension/semantic_realm/.libs/libf2e_*.*                                                             $(compile__lib__dir)
	cp -fa extension/semantic_relationship_key/.libs/libf2e_*.*                                       $(compile__lib__dir)
	cp -fa extension/semantic_resource/.libs/libf2e_*.*                                                       $(compile__lib__dir)
	cp -fa extension/semantic_resource_action_event/.libs/libf2e_*.*                             $(compile__lib__dir)
	cp -fa extension/semantic_resource_action_sequence/.libs/libf2e_*.*                       $(compile__lib__dir)
	cp -fa extension/semantic_resource_event_knowledge_base/.libs/libf2e_*.*             $(compile__lib__dir)
	cp -fa extension/semantic_self/.libs/libf2e_*.*                                                               $(compile__lib__dir)
	cp -fa extension/semantic_situation/.libs/libf2e_*.*                                                     $(compile__lib__dir)
	cp -fa extension/semantic_situation_category/.libs/libf2e_*.*                                   $(compile__lib__dir)
	cp -fa extension/semantic_situation_transition/.libs/libf2e_*.*                               $(compile__lib__dir)
	cp -fa extension/semantic_somatosensation/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_somatosensory_object/.libs/libf2e_*.*                               $(compile__lib__dir)
	cp -fa extension/semantic_temporal_object/.libs/libf2e_*.*                                         $(compile__lib__dir)
	cp -fa extension/semantic_time/.libs/libf2e_*.*                                                               $(compile__lib__dir)
	cp -fa extension/semantic_visual_object/.libs/libf2e_*.*                                             $(compile__lib__dir)
	cp -fa extension/timeline/.libs/libf2e_*.*                                                                         $(compile__lib__dir)
	cp -fa extension/transframe/.libs/libf2e_*.*                                                                     $(compile__lib__dir)

lib_LTLIBRARIES = lib/libfunk2.la $(all_core_extensions)

#bin_PROGRAMS    = bin/funk2-static

lib_libfunk2_la_SOURCES = \
  c/f2_array.c \
  c/f2_ansi.c \
  c/f2_apropos.c \
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
  c/f2_defragmenter.c \
  c/f2_dlfcn.c \
  c/f2_dptr.c \
  c/f2_dynamic_memory.c \
  c/f2_f2ptr_set.c \
  c/f2_fiber.c \
  c/f2_fileio.c \
  c/f2_frame_objects.c \
  c/f2_funk2_node.c \
  c/f2_funktional.c \
  c/f2_garbage_collector.c \
  c/f2_garbage_collector_block_header.c \
  c/f2_garbage_collector_pool.c \
  c/f2_globalenv.c \
  c/f2_gmodule.c \
  c/f2_graph.c \
  c/f2_graph_cluster.c \
  c/f2_graph_match_error_correcting.c \
  c/f2_graphviz.c \
  c/f2_hash.c \
  c/f2_heap.c \
  c/f2_html.c \
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
  c/f2_opengl.c \
  c/f2_optimize.c \
  c/f2_package.c \
  c/f2_package_handler.c \
  c/f2_packet.c \
  c/f2_partial_order.c \
  c/f2_peer_command_server.c \
  c/f2_primes.c \
  c/f2_primobjects.c \
  c/f2_primobject__boolean.c \
  c/f2_primobject__char_pointer.c \
  c/f2_primobject__circular_buffer.c \
  c/f2_primobject__doublelinklist.c \
  c/f2_primobject__dynamic_library.c \
  c/f2_primobject__environment.c \
  c/f2_primobject__fiber_trigger.c \
  c/f2_primobject__file_handle.c \
  c/f2_primobject__frame.c \
  c/f2_primobject__hash.c \
  c/f2_primobject__list.c \
  c/f2_primobject__largeinteger.c \
  c/f2_primobject__matrix.c \
  c/f2_primobject__object.c \
  c/f2_primobject__object_type.c \
  c/f2_primobject__ptypehash.c \
  c/f2_primobject__redblacktree.c \
  c/f2_primobject__scheduler_ptypehash.c \
  c/f2_primobject__set.c \
  c/f2_primobject__stream.c \
  c/f2_primobject__tensor.c \
  c/f2_primobject__traced_cmutex.c \
  c/f2_primobject_type.c \
  c/f2_primobject_type_handler.c \
  c/f2_print.c \
  c/f2_primfunks.c \
  c/f2_primfunks__errno.c \
  c/f2_primfunks__fcntl.c \
  c/f2_primfunks__ioctl.c \
  c/f2_primfunks__locale.c \
  c/f2_primfunks__stdlib.c \
  c/f2_processor.c \
  c/f2_processor_mutex.c \
  c/f2_processor_spinlock.c \
  c/f2_processor_thread.c \
  c/f2_processor_thread_handler.c \
  c/f2_protected_alloc_array.c \
  c/f2_ptype.c \
  c/f2_ptypes.c \
  c/f2_ptypes_object_slots.c \
  c/f2_reader.c \
  c/f2_redblacktree.c \
  c/f2_simple_repl.c \
  c/f2_scheduler.c \
  c/f2_scheduler_thread_controller.c \
  c/f2_set.c \
  c/f2_signal.c \
  c/f2_socket.c \
  c/f2_socket_client.c \
  c/f2_socket_server.c \
  c/f2_sort.c \
  c/f2_status.c \
  c/f2_string.c \
  c/f2_surrogate_parent.c \
  c/f2_system_processor.c \
  c/f2_system_file_handler.c \
  c/f2_terminal_print.c \
  c/f2_termios.c \
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

extension_blocks_world_libf2e_blocks_world_la_SOURCES                                                                     = extension/blocks_world/blocks_world.c
extension_cairo_libf2e_cairo_la_SOURCES                                                                                   = extension/cairo/cairo.c
extension_concept_version_space_libf2e_concept_version_space_la_SOURCES                                                   = extension/concept_version_space/concept_version_space.c
extension_conceptnet_libf2e_conceptnet_la_SOURCES                                                                         = extension/conceptnet/conceptnet.c
extension_event_stream_libf2e_event_stream_la_SOURCES                                                                     = extension/event_stream/event_stream.c
extension_equals_hash_libf2e_equals_hash_la_SOURCES                                                                       = extension/equals_hash/equals_hash.c
extension_fibermon_libf2e_fibermon_la_SOURCES                                                                             = extension/fibermon/fibermon.c
extension_forgetful_event_stream_libf2e_forgetful_event_stream_la_SOURCES                                                 = extension/forgetful_event_stream/forgetful_event_stream.c
extension_forward_planner_libf2e_forward_planner_la_SOURCES                                                               = extension/forward_planner/forward_planner.c
extension_frame_ball_libf2e_frame_ball_la_SOURCES                                                                         = extension/frame_ball/frame_ball.c
extension_graph_isomorphism_libf2e_graph_isomorphism_la_SOURCES                                                           = extension/graph_isomorphism/graph_isomorphism.c
extension_gtk_extension_libf2e_gtk_extension_la_SOURCES                                                                   = extension/gtk_extension/gtk_extension.c
extension_image_libf2e_image_la_SOURCES                                                                                   = extension/image/image.c
extension_image_sequence_libf2e_image_sequence_la_SOURCES                                                                 = extension/image_sequence/image_sequence.c
extension_interval_tree_libf2e_interval_tree_la_SOURCES                                                                   = extension/interval_tree/interval_tree.c
extension_lick_libf2e_lick_la_SOURCES                                                                                     = extension/lick/lick.c
extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la_SOURCES                                     = extension/meta_semantic_knowledge_base/meta_semantic_knowledge_base.c
extension_movie_libf2e_movie_la_SOURCES                                                                                   = extension/movie/movie.c
extension_keyboard_libf2e_keyboard_la_SOURCES                                                                             = extension/keyboard/keyboard.c
extension_propogator_libf2e_propogator_la_SOURCES                                                                         = extension/propogator/propogator.c
extension_semantic_action_libf2e_semantic_action_la_SOURCES                                                               = extension/semantic_action/semantic_action.c
extension_semantic_action_knowledge_base_libf2e_semantic_action_knowledge_base_la_SOURCES                                 = extension/semantic_action_knowledge_base/semantic_action_knowledge_base.c
extension_semantic_action_event_libf2e_semantic_action_event_la_SOURCES                                                   = extension/semantic_action_event/semantic_action_event.c
extension_semantic_agent_libf2e_semantic_agent_la_SOURCES                                                                 = extension/semantic_agent/semantic_agent.c
extension_semantic_causal_event_libf2e_semantic_causal_event_la_SOURCES                                                   = extension/semantic_causal_event/semantic_causal_event.c
extension_semantic_dependency_libf2e_semantic_dependency_la_SOURCES                                                       = extension/semantic_dependency/semantic_dependency.c
extension_semantic_event_sequence_libf2e_semantic_event_sequence_la_SOURCES                                               = extension/semantic_event_sequence/semantic_event_sequence.c
extension_semantic_causal_object_libf2e_semantic_causal_object_la_SOURCES                                                 = extension/semantic_causal_object/semantic_causal_object.c
extension_semantic_category_libf2e_semantic_category_la_SOURCES                                                           = extension/semantic_category/semantic_category.c
extension_semantic_causal_concept_libf2e_semantic_causal_concept_la_SOURCES                                               = extension/semantic_causal_concept/semantic_causal_concept.c
extension_semantic_containment_object_libf2e_semantic_containment_object_la_SOURCES                                       = extension/semantic_containment_object/semantic_containment_object.c
extension_semantic_counterfactual_transframe_libf2e_semantic_counterfactual_transframe_la_SOURCES                         = extension/semantic_counterfactual_transframe/semantic_counterfactual_transframe.c
extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la_SOURCES                                 = extension/semantic_directed_action_event/semantic_directed_action_event.c
extension_semantic_event_libf2e_semantic_event_la_SOURCES                                                                 = extension/semantic_event/semantic_event.c
extension_semantic_event_transframe_libf2e_semantic_event_transframe_la_SOURCES                                           = extension/semantic_event_transframe/semantic_event_transframe.c
extension_semantic_event_tree_libf2e_semantic_event_tree_la_SOURCES                                                       = extension/semantic_event_tree/semantic_event_tree.c
extension_semantic_expectation_failure_libf2e_semantic_expectation_failure_la_SOURCES                                     = extension/semantic_expectation_failure/semantic_expectation_failure.c
extension_semantic_frame_libf2e_semantic_frame_la_SOURCES                                                                 = extension/semantic_frame/semantic_frame.c
extension_semantic_event_knowledge_base_libf2e_semantic_event_knowledge_base_la_SOURCES                                   = extension/semantic_event_knowledge_base/semantic_event_knowledge_base.c
extension_semantic_goal_libf2e_semantic_goal_la_SOURCES                                                                   = extension/semantic_goal/semantic_goal.c
extension_semantic_goal_event_libf2e_semantic_goal_event_la_SOURCES                                                       = extension/semantic_goal_event/semantic_goal_event.c
extension_semantic_goal_action_causal_hypothesis_libf2e_semantic_goal_action_causal_hypothesis_la_SOURCES                 = extension/semantic_goal_action_causal_hypothesis/semantic_goal_action_causal_hypothesis.c
extension_semantic_know_of_existence_event_libf2e_semantic_know_of_existence_event_la_SOURCES                             = extension/semantic_know_of_existence_event/semantic_know_of_existence_event.c
extension_semantic_know_of_relationship_event_libf2e_semantic_know_of_relationship_event_la_SOURCES                       = extension/semantic_know_of_relationship_event/semantic_know_of_relationship_event.c
extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la_SOURCES                                               = extension/semantic_knowledge_base/semantic_knowledge_base.c
extension_semantic_ordered_object_libf2e_semantic_ordered_object_la_SOURCES                                               = extension/semantic_ordered_object/semantic_ordered_object.c
extension_semantic_object_type_event_libf2e_semantic_object_type_event_la_SOURCES                                         = extension/semantic_object_type_event/semantic_object_type_event.c
extension_semantic_object_libf2e_semantic_object_la_SOURCES                                                               = extension/semantic_object/semantic_object.c
extension_semantic_packable_object_libf2e_semantic_packable_object_la_SOURCES                                             = extension/semantic_packable_object/semantic_packable_object.c
extension_semantic_partial_state_libf2e_semantic_partial_state_la_SOURCES                                                 = extension/semantic_partial_state/semantic_partial_state.c
extension_semantic_reflective_object_libf2e_semantic_reflective_object_la_SOURCES                                         = extension/semantic_reflective_object/semantic_reflective_object.c
extension_semantic_reflective_object_type_event_libf2e_semantic_reflective_object_type_event_la_SOURCES                   = extension/semantic_reflective_object_type_event/semantic_reflective_object_type_event.c
extension_semantic_reflective_object_type_property_event_libf2e_semantic_reflective_object_type_property_event_la_SOURCES = extension/semantic_reflective_object_type_property_event/semantic_reflective_object_type_property_event.c
extension_semantic_reflective_object_type_relation_event_libf2e_semantic_reflective_object_type_relation_event_la_SOURCES = extension/semantic_reflective_object_type_relation_event/semantic_reflective_object_type_relation_event.c
extension_semantic_plan_object_libf2e_semantic_plan_object_la_SOURCES                                                     = extension/semantic_plan_object/semantic_plan_object.c
extension_semantic_plan_object_type_event_libf2e_semantic_plan_object_type_event_la_SOURCES                               = extension/semantic_plan_object_type_event/semantic_plan_object_type_event.c
extension_semantic_plan_object_type_relation_event_libf2e_semantic_plan_object_type_relation_event_la_SOURCES             = extension/semantic_plan_object_type_relation_event/semantic_plan_object_type_relation_event.c
extension_semantic_plan_operator_activation_libf2e_semantic_plan_operator_activation_la_SOURCES                           = extension/semantic_plan_operator_activation/semantic_plan_operator_activation.c
extension_semantic_plan_operator_parallel_libf2e_semantic_plan_operator_parallel_la_SOURCES                               = extension/semantic_plan_operator_parallel/semantic_plan_operator_parallel.c
extension_semantic_plan_operator_sequence_libf2e_semantic_plan_operator_sequence_la_SOURCES                               = extension/semantic_plan_operator_sequence/semantic_plan_operator_sequence.c
extension_semantic_plan_operator_suppression_libf2e_semantic_plan_operator_suppression_la_SOURCES                         = extension/semantic_plan_operator_suppression/semantic_plan_operator_suppression.c
extension_semantic_planner_libf2e_semantic_planner_la_SOURCES                                                             = extension/semantic_planner/semantic_planner.c
extension_semantic_proprioception_libf2e_semantic_proprioception_la_SOURCES                                               = extension/semantic_proprioception/semantic_proprioception.c
extension_semantic_proprioceptual_object_libf2e_semantic_proprioceptual_object_la_SOURCES                                 = extension/semantic_proprioceptual_object/semantic_proprioceptual_object.c
extension_semantic_proprioceptual_orientation_libf2e_semantic_proprioceptual_orientation_la_SOURCES                       = extension/semantic_proprioceptual_orientation/semantic_proprioceptual_orientation.c
extension_semantic_proprioceptual_position_libf2e_semantic_proprioceptual_position_la_SOURCES                             = extension/semantic_proprioceptual_position/semantic_proprioceptual_position.c
extension_semantic_realm_libf2e_semantic_realm_la_SOURCES                                                                 = extension/semantic_realm/semantic_realm.c
extension_semantic_relationship_key_libf2e_semantic_relationship_key_la_SOURCES                                           = extension/semantic_relationship_key/semantic_relationship_key.c
extension_semantic_resource_libf2e_semantic_resource_la_SOURCES                                                           = extension/semantic_resource/semantic_resource.c
extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la_SOURCES                                 = extension/semantic_resource_action_event/semantic_resource_action_event.c
extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la_SOURCES                           = extension/semantic_resource_action_sequence/semantic_resource_action_sequence.c
extension_semantic_resource_event_knowledge_base_libf2e_semantic_resource_event_knowledge_base_la_SOURCES                 = extension/semantic_resource_event_knowledge_base/semantic_resource_event_knowledge_base.c
extension_semantic_self_libf2e_semantic_self_la_SOURCES                                                                   = extension/semantic_self/semantic_self.c
extension_semantic_situation_libf2e_semantic_situation_la_SOURCES                                                         = extension/semantic_situation/semantic_situation.c
extension_semantic_situation_category_libf2e_semantic_situation_category_la_SOURCES                                       = extension/semantic_situation_category/semantic_situation_category.c
extension_semantic_situation_transition_libf2e_semantic_situation_transition_la_SOURCES                                   = extension/semantic_situation_transition/semantic_situation_transition.c
extension_semantic_somatosensation_libf2e_semantic_somatosensation_la_SOURCES                                             = extension/semantic_somatosensation/semantic_somatosensation.c
extension_semantic_somatosensory_object_libf2e_semantic_somatosensory_object_la_SOURCES                                   = extension/semantic_somatosensory_object/semantic_somatosensory_object.c
extension_semantic_temporal_object_libf2e_semantic_temporal_object_la_SOURCES                                             = extension/semantic_temporal_object/semantic_temporal_object.c
extension_semantic_time_libf2e_semantic_time_la_SOURCES                                                                   = extension/semantic_time/semantic_time.c
extension_semantic_visual_object_libf2e_semantic_visual_object_la_SOURCES                                                 = extension/semantic_visual_object/semantic_visual_object.c
extension_timeline_libf2e_timeline_la_SOURCES                                                                             = extension/timeline/timeline.c
extension_transframe_libf2e_transframe_la_SOURCES                                                                         = extension/transframe/transframe.c

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

lib_libfunk2_la_LDFLAGS = -no-undefined -version-info $(FUNK2_LIBRARY_VERSION) -release $(FUNK2_RELEASE) $(dynamic_library_linker_flags) $(math_linker_flags) $(realtime_linker_flags) $(xmlrpc_ldflags) $(xmlrpc_ldadd) $(zlib_linker_flags) $(GTK_LIBS) $(GTHREAD_LIBS) $(LIBAVCODEC_LIBS) $(LIBSWSCALE_LIBS) $(CAIRO_LIBS) 
lib_libfunk2_la_CFLAGS  = $(cc_flags)

bin_funk2_static_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
bin_funk2_static_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_equals_hash_libf2e_equals_hash_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_equals_hash_libf2e_equals_hash_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_fibermon_libf2e_fibermon_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_fibermon_libf2e_fibermon_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_gtk_extension_libf2e_gtk_extension_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_gtk_extension_libf2e_gtk_extension_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_image_libf2e_image_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_image_libf2e_image_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_image_sequence_libf2e_image_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_image_sequence_libf2e_image_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_movie_libf2e_movie_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_movie_libf2e_movie_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_cairo_libf2e_cairo_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_cairo_libf2e_cairo_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_blocks_world_libf2e_blocks_world_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_blocks_world_libf2e_blocks_world_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_concept_version_space_libf2e_concept_version_space_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_concept_version_space_libf2e_concept_version_space_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

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

extension_keyboard_libf2e_keyboard_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_keyboard_libf2e_keyboard_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_propogator_libf2e_propogator_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_propogator_libf2e_propogator_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_interval_tree_libf2e_interval_tree_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_interval_tree_libf2e_interval_tree_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_lick_libf2e_lick_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_lick_libf2e_lick_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_meta_semantic_knowledge_base_libf2e_meta_semantic_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_action_libf2e_semantic_action_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_action_libf2e_semantic_action_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_action_knowledge_base_libf2e_semantic_action_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_action_knowledge_base_libf2e_semantic_action_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_action_event_libf2e_semantic_action_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_action_event_libf2e_semantic_action_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_agent_libf2e_semantic_agent_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_agent_libf2e_semantic_agent_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_causal_event_libf2e_semantic_causal_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_causal_event_libf2e_semantic_causal_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_dependency_libf2e_semantic_dependency_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_dependency_libf2e_semantic_dependency_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_sequence_libf2e_semantic_event_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_sequence_libf2e_semantic_event_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_causal_object_libf2e_semantic_causal_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_causal_object_libf2e_semantic_causal_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_category_libf2e_semantic_category_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_category_libf2e_semantic_category_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_causal_concept_libf2e_semantic_causal_concept_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_causal_concept_libf2e_semantic_causal_concept_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_containment_object_libf2e_semantic_containment_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_containment_object_libf2e_semantic_containment_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_counterfactual_transframe_libf2e_semantic_counterfactual_transframe_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_counterfactual_transframe_libf2e_semantic_counterfactual_transframe_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_directed_action_event_libf2e_semantic_directed_action_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_libf2e_semantic_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_libf2e_semantic_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_transframe_libf2e_semantic_event_transframe_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_transframe_libf2e_semantic_event_transframe_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_tree_libf2e_semantic_event_tree_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_tree_libf2e_semantic_event_tree_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_expectation_failure_libf2e_semantic_expectation_failure_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_expectation_failure_libf2e_semantic_expectation_failure_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_frame_libf2e_semantic_frame_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_frame_libf2e_semantic_frame_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_event_knowledge_base_libf2e_semantic_event_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_event_knowledge_base_libf2e_semantic_event_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_goal_libf2e_semantic_goal_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_goal_libf2e_semantic_goal_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_goal_event_libf2e_semantic_goal_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_goal_event_libf2e_semantic_goal_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_goal_action_causal_hypothesis_libf2e_semantic_goal_action_causal_hypothesis_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_goal_action_causal_hypothesis_libf2e_semantic_goal_action_causal_hypothesis_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_know_of_existence_event_libf2e_semantic_know_of_existence_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_know_of_existence_event_libf2e_semantic_know_of_existence_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_know_of_relationship_event_libf2e_semantic_know_of_relationship_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_know_of_relationship_event_libf2e_semantic_know_of_relationship_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_knowledge_base_libf2e_semantic_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_ordered_object_libf2e_semantic_ordered_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_ordered_object_libf2e_semantic_ordered_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_object_type_event_libf2e_semantic_object_type_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_object_type_event_libf2e_semantic_object_type_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_object_libf2e_semantic_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_object_libf2e_semantic_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_packable_object_libf2e_semantic_packable_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_packable_object_libf2e_semantic_packable_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_partial_state_libf2e_semantic_partial_state_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_partial_state_libf2e_semantic_partial_state_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_reflective_object_libf2e_semantic_reflective_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_reflective_object_libf2e_semantic_reflective_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_reflective_object_type_event_libf2e_semantic_reflective_object_type_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_reflective_object_type_event_libf2e_semantic_reflective_object_type_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_reflective_object_type_property_event_libf2e_semantic_reflective_object_type_property_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_reflective_object_type_property_event_libf2e_semantic_reflective_object_type_property_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_reflective_object_type_relation_event_libf2e_semantic_reflective_object_type_relation_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_reflective_object_type_relation_event_libf2e_semantic_reflective_object_type_relation_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_object_libf2e_semantic_plan_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_object_libf2e_semantic_plan_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_object_type_event_libf2e_semantic_plan_object_type_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_object_type_event_libf2e_semantic_plan_object_type_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_object_type_relation_event_libf2e_semantic_plan_object_type_relation_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_object_type_relation_event_libf2e_semantic_plan_object_type_relation_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_operator_activation_libf2e_semantic_plan_operator_activation_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_operator_activation_libf2e_semantic_plan_operator_activation_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_operator_parallel_libf2e_semantic_plan_operator_parallel_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_operator_parallel_libf2e_semantic_plan_operator_parallel_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_operator_sequence_libf2e_semantic_plan_operator_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_operator_sequence_libf2e_semantic_plan_operator_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_plan_operator_suppression_libf2e_semantic_plan_operator_suppression_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_plan_operator_suppression_libf2e_semantic_plan_operator_suppression_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_planner_libf2e_semantic_planner_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_planner_libf2e_semantic_planner_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_proprioception_libf2e_semantic_proprioception_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_proprioception_libf2e_semantic_proprioception_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_proprioceptual_object_libf2e_semantic_proprioceptual_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_proprioceptual_object_libf2e_semantic_proprioceptual_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_proprioceptual_orientation_libf2e_semantic_proprioceptual_orientation_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_proprioceptual_orientation_libf2e_semantic_proprioceptual_orientation_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_proprioceptual_position_libf2e_semantic_proprioceptual_position_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_proprioceptual_position_libf2e_semantic_proprioceptual_position_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_realm_libf2e_semantic_realm_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_realm_libf2e_semantic_realm_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_relationship_key_libf2e_semantic_relationship_key_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_relationship_key_libf2e_semantic_relationship_key_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_libf2e_semantic_resource_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_libf2e_semantic_resource_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_action_event_libf2e_semantic_resource_action_event_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_action_sequence_libf2e_semantic_resource_action_sequence_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_resource_event_knowledge_base_libf2e_semantic_resource_event_knowledge_base_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_resource_event_knowledge_base_libf2e_semantic_resource_event_knowledge_base_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_self_libf2e_semantic_self_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_self_libf2e_semantic_self_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_situation_libf2e_semantic_situation_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_situation_libf2e_semantic_situation_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_situation_category_libf2e_semantic_situation_category_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_situation_category_libf2e_semantic_situation_category_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_situation_transition_libf2e_semantic_situation_transition_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_situation_transition_libf2e_semantic_situation_transition_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_somatosensation_libf2e_semantic_somatosensation_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_somatosensation_libf2e_semantic_somatosensation_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_somatosensory_object_libf2e_semantic_somatosensory_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_somatosensory_object_libf2e_semantic_somatosensory_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_temporal_object_libf2e_semantic_temporal_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_temporal_object_libf2e_semantic_temporal_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_time_libf2e_semantic_time_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_time_libf2e_semantic_time_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_semantic_visual_object_libf2e_semantic_visual_object_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_semantic_visual_object_libf2e_semantic_visual_object_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_timeline_libf2e_timeline_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_timeline_libf2e_timeline_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)

extension_transframe_libf2e_transframe_la_LDFLAGS = $(lib_libfunk2_la_LDFLAGS)
extension_transframe_libf2e_transframe_la_CFLAGS  = $(lib_libfunk2_la_CFLAGS)


CONFIGURE_DEPENDENCIES = config_bit_num.h config_compile_time_id.h
CONFIG_CLEAN_FILES     = config_bit_num.h config_compile_time_id.h

# causes building of img/bootstrap.img
#AM_MAKEFLAGS = img/bootstrap.img

clean-img:
	rm -f img/bootstrap-repl.img
	rm -f img/bootstrap.img

clean: clean-am clean-img
	rm -f config_compile_time_id.h
	rm -f config_bit_num.h
	rm -f bin/funk2$(EXEEXT)
	rm -f install.sh gprof.txt libtool Makefile
	rm -rf c/.deps c/.dirstamp
	rm -f config.h config.log config.status
	rm -rf lib bin
	find . -name ".dirstamp" -print0 | xargs -0 -n 1 rm -rf
	find . -name ".deps"     -print0 | xargs -0 -n 1 rm -rf

make-install-sh:
	echo "#!/bin/sh"                                                                                                                                                                     > install-sh
	echo "echo \"\""                                                                                                                                                                    >> install-sh
	echo "echo \"make: install-sh performing system-wide installation of funk2\""                                                                                                       >> install-sh
	echo "echo \"\""                                                                                                                                                                    >> install-sh
	echo "echo \"  install__bin__dir     = $(chroot__install__bin__dir)\""                                                                                                              >> install-sh
#	echo "echo \"  install__lib__dir     = $(chroot__install__lib__dir)\""                                                                                                              >> install-sh
	echo "echo \"  install__include__dir = $(chroot__install__include__dir)\""                                                                                                          >> install-sh
	echo "echo \"\""                                                                                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__img__dir)"                                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__bin__dir)"                                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__include__dir)"                                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__system_bin__dir)"                                                                                                                           >> install-sh
	echo "mkdir -m755 -p $(chroot__install__fu2__dir)"                                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)"                                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)alien/"                                                                                                                       >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)ansi/"                                                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)basic_bug_responses/"                                                                                                         >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)graph_cluster/"                                                                                                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)graph_match_error_correcting/"                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)graphviz/"                                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)math/"                                                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)mutex/"                                                                                                                       >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)natural_language/"                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)number/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)utilities/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__built_in__dir)xmlrpc/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)"                                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)blocks_world/"                                                                                                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)cairo/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)conceptnet/"                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)concept_version_space/"                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)equals_hash/"                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)event_stream/"                                                                                                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)fibermon/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)forgetful_event_stream/"                                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)forward_planner/"                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)frame_ball/"                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)graph_isomorphism/"                                                                                                          >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)gtk_extension/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)image/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)image_sequence/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)interval_tree/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)lick/"                                                                                                                       >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)meta_semantic_knowledge_base/"                                                                                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)movie/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)keyboard/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)propogator/"                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_action/"                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_action_knowledge_base/"                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_action_event/"                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_agent/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_category/"                                                                                                          >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_causal_event/"                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_causal_object/"                                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_causal_concept/"                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_containment_object/"                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_counterfactual_transframe/"                                                                                         >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_directed_action_event/"                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_event/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_event_knowledge_base/"                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_dependency/"                                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_event_sequence/"                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_event_transframe/"                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_event_tree/"                                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_expectation_failure/"                                                                                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_frame/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_goal/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_goal_action_causal_hypothesis/"                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_goal_event/"                                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_knowledge_base/"                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_know_of_existence_event/"                                                                                           >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_know_of_relationship_event/"                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_object/"                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_object_type_event/"                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_ordered_object/"                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_packable_object/"                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_partial_state/"                                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_reflective_object/"                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_reflective_object_type_event/"                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_reflective_object_type_property_event/"                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_reflective_object_type_relation_event/"                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_planner/"                                                                                                           >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_object/"                                                                                                       >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_object_type_event/"                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_object_type_relation_event/"                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_operator_activation/"                                                                                          >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_operator_parallel/"                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_operator_sequence/"                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_plan_operator_suppression/"                                                                                         >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_proprioception/"                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_proprioceptual_object/"                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_proprioceptual_orientation/"                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_proprioceptual_position/"                                                                                           >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_realm/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_relationship_key/"                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_resource/"                                                                                                          >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_resource_action_event/"                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_resource_action_sequence/"                                                                                          >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_resource_event_knowledge_base/"                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_self/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_situation/"                                                                                                         >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_situation_category/"                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_situation_transition/"                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_somatosensation/"                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_somatosensory_object/"                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_temporal_object/"                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_time/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)semantic_visual_object/"                                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)timeline/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__extension__dir)transframe/"                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)"                                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)cairo-test/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)concept_version_space-test/"                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)gtk-test/"                                                                                                                        >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)interval_tree-test/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)optimize-test/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)propogator-test/"                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)keyboard-test/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)timeline-test/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__test__dir)xmlrpc-test/"                                                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)"                                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)cannons_algorithm/"                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)divisi2/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)em_two_webpage/"                                                                                                               >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)english_language/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)funk2-htmldoc/"                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)funk2-webpage/"                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)graph_match/"                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)gtk_timeline/"                                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)isis_world/"                                                                                                                   >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)isis_world_client/"                                                                                                            >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)macbeth/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)mind/"                                                                                                                         >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)mindmon/"                                                                                                                      >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)mindmon-1.0/"                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)mindmon-blocks_world/"                                                                                                         >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)mindmon-isis_world/"                                                                                                           >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)moral_compass/"                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)moral_compass-isis_world/"                                                                                                     >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)rct_webpage/"                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)reflective_mind/"                                                                                                              >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)reflective_mind-blocks_world/"                                                                                                 >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)reflective_timer/"                                                                                                             >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)roboverse/"                                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)socket-client/"                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)socket-server/"                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)traced_mind/"                                                                                                                  >> install-sh
	echo "mkdir -m755 -p $(chroot__install__example__dir)visualize/"                                                                                                                    >> install-sh
	echo "mkdir -m755 -p $(chroot__install__icons__dir)"                                                                                                                                >> install-sh
	echo "mkdir -m755 -p $(chroot__install__man__dir)"                                                                                                                                  >> install-sh
	echo "install -m755 $(compile__funk2) $(chroot__install__funk2)"                                                                                                                    >> install-sh
	echo "install -m644 c/*.h $(chroot__install__include__dir)"                                                                                                                         >> install-sh
	echo "install -m644 $(source__fu2__dir)*                                                         $(chroot__install__fu2__dir)"                                                      >> install-sh
	echo "install -m644 $(source__built_in__dir)*                                                    $(chroot__install__built_in__dir)"                                                 >> install-sh
	echo "install -m644 $(source__built_in__dir)alien/*.f*                                           $(chroot__install__built_in__dir)alien/"                                           >> install-sh
	echo "install -m644 $(source__built_in__dir)ansi/*.f*                                            $(chroot__install__built_in__dir)ansi/"                                            >> install-sh
	echo "install -m644 $(source__built_in__dir)basic_bug_responses/*.f*                             $(chroot__install__built_in__dir)basic_bug_responses/"                             >> install-sh
	echo "install -m644 $(source__built_in__dir)graph_cluster/*.f*                                   $(chroot__install__built_in__dir)graph_cluster/"                                   >> install-sh
	echo "install -m644 $(source__built_in__dir)graph_match_error_correcting/*.f*                    $(chroot__install__built_in__dir)graph_match_error_correcting/"                    >> install-sh
	echo "install -m644 $(source__built_in__dir)graphviz/*.f*                                        $(chroot__install__built_in__dir)graphviz/"                                        >> install-sh
	echo "install -m644 $(source__built_in__dir)math/*.f*                                            $(chroot__install__built_in__dir)math/"                                            >> install-sh
	echo "install -m644 $(source__built_in__dir)mutex/*.f*                                           $(chroot__install__built_in__dir)mutex/"                                           >> install-sh
	echo "install -m644 $(source__built_in__dir)natural_language/*.f*                                $(chroot__install__built_in__dir)natural_language/"                                >> install-sh
	echo "install -m644 $(source__built_in__dir)number/*.f*                                          $(chroot__install__built_in__dir)number/"                                          >> install-sh
	echo "install -m644 $(source__built_in__dir)utilities/*.f*                                       $(chroot__install__built_in__dir)utilities/"                                       >> install-sh
	echo "install -m644 $(source__built_in__dir)xmlrpc/*.f*                                          $(chroot__install__built_in__dir)xmlrpc/"                                          >> install-sh
	echo "install -m644 $(source__extension__dir)*                                                   $(chroot__install__extension__dir)"                                                >> install-sh
	echo "install -m644 $(source__extension__dir)blocks_world/*.f*                                   $(chroot__install__extension__dir)blocks_world/"                                   >> install-sh
	echo "install -m644 $(source__extension__dir)cairo/*.f*                                          $(chroot__install__extension__dir)cairo/"                                          >> install-sh
	echo "install -m644 $(source__extension__dir)conceptnet/*.f*                                     $(chroot__install__extension__dir)conceptnet/"                                     >> install-sh
	echo "install -m644 $(source__extension__dir)concept_version_space/*.f*                          $(chroot__install__extension__dir)concept_version_space/"                          >> install-sh
	echo "install -m644 $(source__extension__dir)equals_hash/*.f*                                    $(chroot__install__extension__dir)equals_hash/"                                    >> install-sh
	echo "install -m644 $(source__extension__dir)event_stream/*.f*                                   $(chroot__install__extension__dir)event_stream/"                                   >> install-sh
	echo "install -m644 $(source__extension__dir)fibermon/*.f*                                       $(chroot__install__extension__dir)fibermon/"                                       >> install-sh
	echo "install -m644 $(source__extension__dir)forgetful_event_stream/*.f*                         $(chroot__install__extension__dir)forgetful_event_stream/"                         >> install-sh
	echo "install -m644 $(source__extension__dir)forward_planner/*.f*                                $(chroot__install__extension__dir)forward_planner/"                                >> install-sh
	echo "install -m644 $(source__extension__dir)frame_ball/*.f*                                     $(chroot__install__extension__dir)frame_ball/"                                     >> install-sh
	echo "install -m644 $(source__extension__dir)graph_isomorphism/*.f*                              $(chroot__install__extension__dir)graph_isomorphism/"                              >> install-sh
	echo "install -m644 $(source__extension__dir)gtk_extension/*.f*                                  $(chroot__install__extension__dir)gtk_extension/"                                  >> install-sh
	echo "install -m644 $(source__extension__dir)image/*.f*                                          $(chroot__install__extension__dir)image/"                                          >> install-sh
	echo "install -m644 $(source__extension__dir)image_sequence/*.f*                                 $(chroot__install__extension__dir)image_sequence/"                                 >> install-sh
	echo "install -m644 $(source__extension__dir)interval_tree/*.f*                                  $(chroot__install__extension__dir)interval_tree/"                                  >> install-sh
	echo "install -m644 $(source__extension__dir)lick/*.f*                                           $(chroot__install__extension__dir)lick/"                                           >> install-sh
	echo "install -m644 $(source__extension__dir)meta_semantic_knowledge_base/*.f*                   $(chroot__install__extension__dir)meta_semantic_knowledge_base/"                   >> install-sh
	echo "install -m644 $(source__extension__dir)movie/*.f*                                          $(chroot__install__extension__dir)movie/"                                          >> install-sh
	echo "install -m644 $(source__extension__dir)keyboard/*.f*                                       $(chroot__install__extension__dir)keyboard/"                                       >> install-sh
	echo "install -m644 $(source__extension__dir)propogator/*.f*                                     $(chroot__install__extension__dir)propogator/"                                     >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_action/*.f*                                $(chroot__install__extension__dir)semantic_action/"                                >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_action_knowledge_base/*.f*                 $(chroot__install__extension__dir)semantic_action_knowledge_base/"                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_action_event/*.f*                          $(chroot__install__extension__dir)semantic_action_event/"                          >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_agent/*.f*                                 $(chroot__install__extension__dir)semantic_agent/"                                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_category/*.f*                              $(chroot__install__extension__dir)semantic_category/"                              >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_causal_event/*.f*                          $(chroot__install__extension__dir)semantic_causal_event/"                          >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_causal_object/*.f*                         $(chroot__install__extension__dir)semantic_causal_object/"                         >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_causal_concept/*.f*                        $(chroot__install__extension__dir)semantic_causal_concept/"                        >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_containment_object/*.f*                    $(chroot__install__extension__dir)semantic_containment_object/"                    >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_counterfactual_transframe/*.f*             $(chroot__install__extension__dir)semantic_counterfactual_transframe/"             >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_directed_action_event/*.f*                 $(chroot__install__extension__dir)semantic_directed_action_event/"                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_event/*.f*                                 $(chroot__install__extension__dir)semantic_event/"                                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_event_knowledge_base/*.f*                  $(chroot__install__extension__dir)semantic_event_knowledge_base/"                  >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_dependency/*.f*                            $(chroot__install__extension__dir)semantic_dependency/"                            >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_event_sequence/*.f*                        $(chroot__install__extension__dir)semantic_event_sequence/"                        >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_event_transframe/*.f*                      $(chroot__install__extension__dir)semantic_event_transframe/"                      >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_event_tree/*.f*                            $(chroot__install__extension__dir)semantic_event_tree/"                            >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_expectation_failure/*.f*                   $(chroot__install__extension__dir)semantic_expectation_failure/"                   >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_frame/*.f*                                 $(chroot__install__extension__dir)semantic_frame/"                                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_goal/*.f*                                  $(chroot__install__extension__dir)semantic_goal/"                                  >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_goal_action_causal_hypothesis/*.f*         $(chroot__install__extension__dir)semantic_goal_action_causal_hypothesis/"         >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_goal_event/*.f*                            $(chroot__install__extension__dir)semantic_goal_event/"                            >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_knowledge_base/*.f*                        $(chroot__install__extension__dir)semantic_knowledge_base/"                        >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_know_of_existence_event/*.f*               $(chroot__install__extension__dir)semantic_know_of_existence_event/"               >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_know_of_relationship_event/*.f*            $(chroot__install__extension__dir)semantic_know_of_relationship_event/"            >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_object/*.f*                                $(chroot__install__extension__dir)semantic_object/"                                >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_object_type_event/*.f*                     $(chroot__install__extension__dir)semantic_object_type_event/"                     >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_ordered_object/*.f*                        $(chroot__install__extension__dir)semantic_ordered_object/"                        >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_packable_object/*.f*                       $(chroot__install__extension__dir)semantic_packable_object/"                       >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_partial_state/*.f*                         $(chroot__install__extension__dir)semantic_partial_state/"                         >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_reflective_object/*.f*                     $(chroot__install__extension__dir)semantic_reflective_object/"                     >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_reflective_object_type_event/*.f*          $(chroot__install__extension__dir)semantic_reflective_object_type_event/"          >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_reflective_object_type_property_event/*.f* $(chroot__install__extension__dir)semantic_reflective_object_type_property_event/" >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_reflective_object_type_relation_event/*.f* $(chroot__install__extension__dir)semantic_reflective_object_type_relation_event/" >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_planner/*.f*                               $(chroot__install__extension__dir)semantic_planner/"                               >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_object/*.f*                           $(chroot__install__extension__dir)semantic_plan_object/"                           >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_object_type_event/*.f*                $(chroot__install__extension__dir)semantic_plan_object_type_event/"                >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_object_type_relation_event/*.f*       $(chroot__install__extension__dir)semantic_plan_object_type_relation_event/"       >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_operator_activation/*.f*              $(chroot__install__extension__dir)semantic_plan_operator_activation/"              >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_operator_parallel/*.f*                $(chroot__install__extension__dir)semantic_plan_operator_parallel/"                >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_operator_sequence/*.f*                $(chroot__install__extension__dir)semantic_plan_operator_sequence/"                >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_plan_operator_suppression/*.f*             $(chroot__install__extension__dir)semantic_plan_operator_suppression/"             >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_proprioception/*.f*                        $(chroot__install__extension__dir)semantic_proprioception/"                        >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_proprioceptual_object/*.f*                 $(chroot__install__extension__dir)semantic_proprioceptual_object/"                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_proprioceptual_orientation/*.f*            $(chroot__install__extension__dir)semantic_proprioceptual_orientation/"            >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_proprioceptual_position/*.f*               $(chroot__install__extension__dir)semantic_proprioceptual_position/"               >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_realm/*.f*                                 $(chroot__install__extension__dir)semantic_realm/"                                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_relationship_key/*.f*                      $(chroot__install__extension__dir)semantic_relationship_key/"                      >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_resource/*.f*                              $(chroot__install__extension__dir)semantic_resource/"                              >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_resource_action_event/*.f*                 $(chroot__install__extension__dir)semantic_resource_action_event/"                 >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_resource_action_sequence/*.f*              $(chroot__install__extension__dir)semantic_resource_action_sequence/"              >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_resource_event_knowledge_base/*.f*         $(chroot__install__extension__dir)semantic_resource_event_knowledge_base/"         >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_self/*.f*                                  $(chroot__install__extension__dir)semantic_self/"                                  >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_situation/*.f*                             $(chroot__install__extension__dir)semantic_situation/"                             >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_situation_category/*.f*                    $(chroot__install__extension__dir)semantic_situation_category/"                    >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_situation_transition/*.f*                  $(chroot__install__extension__dir)semantic_situation_transition/"                  >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_somatosensation/*.f*                       $(chroot__install__extension__dir)semantic_somatosensation/"                       >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_somatosensory_object/*.f*                  $(chroot__install__extension__dir)semantic_somatosensory_object/"                  >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_temporal_object/*.f*                       $(chroot__install__extension__dir)semantic_temporal_object/"                       >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_time/*.f*                                  $(chroot__install__extension__dir)semantic_time/"                                  >> install-sh
	echo "install -m644 $(source__extension__dir)semantic_visual_object/*.f*                         $(chroot__install__extension__dir)semantic_visual_object/"                         >> install-sh
	echo "install -m644 $(source__extension__dir)timeline/*.f*                                       $(chroot__install__extension__dir)timeline/"                                       >> install-sh
	echo "install -m644 $(source__extension__dir)transframe/*.f*                                     $(chroot__install__extension__dir)transframe/"                                     >> install-sh
	echo "install -m644 $(source__test__dir)*                                                        $(chroot__install__test__dir)"                                                     >> install-sh
	echo "install -m644 $(source__test__dir)cairo-test/*.f*                                          $(chroot__install__test__dir)cairo-test/"                                          >> install-sh
	echo "install -m644 $(source__test__dir)concept_version_space-test/*.f*                          $(chroot__install__test__dir)concept_version_space-test/"                          >> install-sh
	echo "install -m644 $(source__test__dir)gtk-test/*.f*                                            $(chroot__install__test__dir)gtk-test/"                                            >> install-sh
	echo "install -m644 $(source__test__dir)interval_tree-test/*.f*                                  $(chroot__install__test__dir)interval_tree-test/"                                  >> install-sh
	echo "install -m644 $(source__test__dir)optimize-test/*.f*                                       $(chroot__install__test__dir)optimize-test/"                                       >> install-sh
	echo "install -m644 $(source__test__dir)propogator-test/*.f*                                     $(chroot__install__test__dir)propogator-test/"                                     >> install-sh
	echo "install -m644 $(source__test__dir)keyboard-test/*.f*                                       $(chroot__install__test__dir)keyboard-test/"                                       >> install-sh
	echo "install -m644 $(source__test__dir)timeline-test/*.f*                                       $(chroot__install__test__dir)timeline-test/"                                       >> install-sh
	echo "install -m644 $(source__test__dir)xmlrpc-test/*.f*                                         $(chroot__install__test__dir)xmlrpc-test/"                                         >> install-sh
	echo "install -m644 $(source__example__dir)*                                                     $(chroot__install__example__dir)"                                                  >> install-sh
	echo "install -m644 $(source__example__dir)cannons_algorithm/*.f*                                $(chroot__install__example__dir)cannons_algorithm/"                                >> install-sh
	echo "install -m644 $(source__example__dir)divisi2/*.f*                                          $(chroot__install__example__dir)divisi2/"                                          >> install-sh
	echo "install -m644 $(source__example__dir)em_two_webpage/*.f*                                   $(chroot__install__example__dir)em_two_webpage/"                                   >> install-sh
	echo "install -m644 $(source__example__dir)english_language/*.f*                                 $(chroot__install__example__dir)english_language/"                                 >> install-sh
	echo "install -m644 $(source__example__dir)funk2-htmldoc/*.f*                                    $(chroot__install__example__dir)funk2-htmldoc/"                                    >> install-sh
	echo "install -m644 $(source__example__dir)funk2-webpage/*.f*                                    $(chroot__install__example__dir)funk2-webpage/"                                    >> install-sh
	echo "install -m644 $(source__example__dir)graph_match/*.f*                                      $(chroot__install__example__dir)graph_match/"                                      >> install-sh
	echo "install -m644 $(source__example__dir)gtk_timeline/*.f*                                     $(chroot__install__example__dir)gtk_timeline/"                                     >> install-sh
	echo "install -m644 $(source__example__dir)isis_world/*.f*                                       $(chroot__install__example__dir)isis_world/"                                       >> install-sh
	echo "install -m644 $(source__example__dir)isis_world_client/*.f*                                $(chroot__install__example__dir)isis_world_client/"                                >> install-sh
	echo "install -m644 $(source__example__dir)macbeth/*.f*                                          $(chroot__install__example__dir)macbeth/"                                          >> install-sh
	echo "install -m644 $(source__example__dir)mind/*.f*                                             $(chroot__install__example__dir)mind/"                                             >> install-sh
	echo "install -m644 $(source__example__dir)mindmon/*.f*                                          $(chroot__install__example__dir)mindmon/"                                          >> install-sh
	echo "install -m644 $(source__example__dir)mindmon-1.0/*.f*                                      $(chroot__install__example__dir)mindmon-1.0/"                                      >> install-sh
	echo "install -m644 $(source__example__dir)mindmon-blocks_world/*.f*                             $(chroot__install__example__dir)mindmon-blocks_world/"                             >> install-sh
	echo "install -m644 $(source__example__dir)mindmon-isis_world/*.f*                               $(chroot__install__example__dir)mindmon-isis_world/"                               >> install-sh
	echo "install -m644 $(source__example__dir)moral_compass/*.f*                                    $(chroot__install__example__dir)moral_compass/"                                    >> install-sh
	echo "install -m644 $(source__example__dir)moral_compass-isis_world/*.f*                         $(chroot__install__example__dir)moral_compass-isis_world/"                         >> install-sh
	echo "install -m644 $(source__example__dir)rct_webpage/*.f*                                      $(chroot__install__example__dir)rct_webpage/"                                      >> install-sh
	echo "install -m644 $(source__example__dir)reflective_mind/*.f*                                  $(chroot__install__example__dir)reflective_mind/"                                  >> install-sh
	echo "install -m644 $(source__example__dir)reflective_mind-blocks_world/*.f*                     $(chroot__install__example__dir)reflective_mind-blocks_world/"                     >> install-sh
	echo "install -m644 $(source__example__dir)reflective_timer/*.f*                                 $(chroot__install__example__dir)reflective_timer/"                                 >> install-sh
	echo "install -m644 $(source__example__dir)roboverse/*.f*                                        $(chroot__install__example__dir)roboverse/"                                        >> install-sh
	echo "install -m644 $(source__example__dir)socket-client/*.f*                                    $(chroot__install__example__dir)socket-client/"                                    >> install-sh
	echo "install -m644 $(source__example__dir)socket-server/*.f*                                    $(chroot__install__example__dir)socket-server/"                                    >> install-sh
	echo "install -m644 $(source__example__dir)traced_mind/*.f*                                      $(chroot__install__example__dir)traced_mind/"                                      >> install-sh
	echo "install -m644 $(source__example__dir)visualize/*.f*                                        $(chroot__install__example__dir)visualize/"                                        >> install-sh
	echo "install -m644 $(source__icons__dir)*                                                       $(chroot__install__icons__dir)"                                                    >> install-sh
	echo "gzip -c debian/funk2.1 > debian/funk2.1.gz"                                                                                                                                   >> install-sh
	echo "install -m644 debian/funk2.1.gz $(chroot__install__man__dir)"                                                                                                                 >> install-sh
	chmod a+x install-sh

make-install-full-sh: make-install-sh
	echo "#!/bin/sh"                                                                                                                                                                 > install-full-sh
	echo "echo \"\""                                                                                                                                                                >> install-full-sh
	echo "echo \"make: install-full-sh performing system-wide installation of funk2\""                                                                                              >> install-full-sh
	echo "echo \"\""                                                                                                                                                                >> install-full-sh
	echo "echo \"  install__bin__dir     = $(chroot__install__bin__dir)\""                                                                                                          >> install-full-sh
#	echo "echo \"  install__lib__dir     = $(chroot__install__lib__dir)\""                                                                                                          >> install-full-sh
	echo "echo \"  install__include__dir = $(chroot__install__include__dir)\""                                                                                                      >> install-full-sh
	echo "echo \"\""                                                                                                                                                                >> install-full-sh
	echo "./install-sh"                                                                                                                                                             >> install-full-sh
	echo "install -m644 $(compile__bootstrap__img) $(chroot__install__bootstrap__img)"                                                                                              >> install-full-sh
	chmod a+x install-full-sh

extensions: finish_compiling_all_core_extensions

bin/funk2$(EXEEXT): lib/libfunk2.la finish_compiling_all_core_extensions
	$(COMPILE) -o $@ c/funk2_main.c $(GL_CFLAGS) $(GLU_CFLAGS) $(GTK_CFLAGS) $(GTHREAD_CFLAGS) $(LIBAVCODEC_CFLAGS) $(LIBSWSCALE_CFLAGS) $(CAIRO_CFLAGS) -Llib/.libs -lfunk2

install-minimal: install-am make-install-sh bin/funk2$(EXEEXT)
	./install-sh

install-debian: install-minimal

# full install
install: install-minimal make-install-full-sh img/bootstrap.img
	./install-full-sh



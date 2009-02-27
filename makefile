# 
# Copyright (c) 2007-2009 Bo Morgan.
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

current_dir                  = $(shell pwd | sed -e 's=^/tmp_mnt/=/=')

source__funk2__dir           = ./
source__fu2__dir             = $(source__funk2__dir)fu2/
source__bootstrap__fu2       = $(source__fu2__dir)bootstrap.fu2
source__bootstrap__repl__fu2 = $(source__fu2__dir)bootstrap-repl.fu2

compile__funk2__dir           = $(source__funk2__dir)
compile__bin__dir             = $(compile__funk2__dir)bin/
compile__img__dir             = $(compile__funk2__dir)img/
compile__funk2                = $(compile__bin__dir)funk2
compile__bootstrap__img       = $(compile__img__dir)bootstrap.img
compile__bootstrap__repl__img = $(compile__img__dir)bootstrap-repl.img

install__funk2__dir          = /usr/local/funk2/
install__img__dir            = $(install__funk2__dir)img/
install__bin__dir            = $(install__funk2__dir)bin/
install__include__dir        = $(install__funk2__dir)include/
install__funk2               = $(install__bin__dir)funk2
install__bootstrap__img      = $(install__img__dir)bootstrap.img
install__system_bin__dir     = /usr/local/bin/
install__system_include__dir = /usr/local/include/funk2/
install__funk2__system_link  = $(install__system_bin__dir)funk2
install__rlglue_dir          = $(current_dir)/extern

default: $(compile__funk2) $(compile__bootstrap__img)

gmodule_linker_flags = $(shell pkg-config --libs gmodule-2.0)

funk2_server_objs = \
  c/f2_ansi.o \
  c/f2_blocks_world.o \
  c/f2_buffered_file.o \
  c/f2_buffered_socket.o \
  c/f2_bytecodes.o \
  c/f2_circular_buffer.o \
  c/f2_command_line.o \
  c/f2_compile.o \
  c/f2_compile_x86.o \
  c/f2_critic.o \
  c/f2_event_router.o \
  c/f2_globalenv.o \
  c/f2_gmodule.o \
  c/f2_funk2_node.o \
  c/f2_funktional.o \
  c/f2_html.o \
  c/f2_load.o \
  c/f2_memory.o \
  c/f2_object.o \
  c/f2_packet.o \
  c/f2_peer_command_server.o \
  c/f2_primobjects.o \
  c/f2_primobject__boolean.o \
  c/f2_primobject__char_pointer.o \
  c/f2_primobject__environment.o \
  c/f2_primobject__frame.o \
  c/f2_primobject__hashtable.o \
  c/f2_primobject__tensor.o \
  c/f2_primobject__object.o \
  c/f2_primobject__object_type.o \
  c/f2_primobject__circular_buffer.o \
  c/f2_primobject__stream.o \
  c/f2_print.o \
  c/f2_primfunks.o \
  c/f2_primfunks__errno.o \
  c/f2_primfunks__fcntl.o \
  c/f2_primfunks__ioctl.o \
  c/f2_primfunks__locale.o \
  c/f2_primfunks__memory.o \
  c/f2_pthread.o \
  c/f2_ptypes.o \
  c/f2_reader.o \
  c/f2_redblacktree.o \
  c/f2_repl.o \
  c/f2_scheduler.o \
  c/f2_serialize.o \
  c/f2_signal.o \
  c/f2_socket.o \
  c/f2_socket_client.o \
  c/f2_socket_server.o \
  c/f2_status.o \
  c/f2_swapmemory.o \
  c/f2_termios.o \
  c/f2_thought_process.o \
  c/f2_thread.o \
  c/f2_time.o \
  c/f2_trace.o \
  c/funk2.o
funk2_headers = \
  c/f2_ansi.h \
  c/f2_blocks_world.h \
  c/f2_buffered_file.h \
  c/f2_buffered_socket.h \
  c/f2_bytecodes.h \
  c/f2_compile.h \
  c/f2_compile_x86.h \
  c/f2_critic.h \
  c/f2_event_router.h \
  c/f2_global.h \
  c/f2_globalenv.h \
  c/f2_gmodule.h \
  c/f2_funk2_node.h \
  c/f2_funktional.h \
  c/f2_html.h \
  c/f2_load.h \
  c/f2_peer_command_server.h \
  c/f2_memory.h \
  c/f2_object.h \
  c/f2_packet.h \
  c/f2_primobjects.h \
  c/f2_primobject__boolean.h \
  c/f2_primobject__char_pointer.h \
  c/f2_primobject__environment.h \
  c/f2_primobject__frame.h \
  c/f2_primobject__hashtable.h \
  c/f2_primobject__tensor.h \
  c/f2_primobject__object.h \
  c/f2_primobject__object_type.h \
  c/f2_primobject__circular_buffer.h \
  c/f2_primobject__stream.h \
  c/f2_print.h \
  c/f2_primfunks.h \
  c/f2_primfunks__errno.h \
  c/f2_primfunks__fcntl.h \
  c/f2_primfunks__ioctl.h \
  c/f2_primfunks__locale.h \
  c/f2_primfunks__memory.h \
  c/f2_pthread.h \
  c/f2_ptypes.h \
  c/f2_reader.h \
  c/f2_redblacktree.h \
  c/f2_repl.h \
  c/f2_scheduler.h \
  c/f2_serialize.h \
  c/f2_signal.h \
  c/f2_socket.h \
  c/f2_status.h \
  c/f2_swapmemory.h \
  c/f2_termios.h \
  c/f2_thought_process.h \
  c/f2_thread.h \
  c/f2_time.h \
  c/f2_trace.h

include config.mak
include makefile.cfg

bin/configurator: c/configurator.c
	gcc $(cc_flags) c/configurator.c -o $@

configure: bin/configurator
	make -s configure-silent

configure-silent:
	echo "" > config.tmp
	rm -f config.mak
	echo "" > config.mak
	echo "char__bit_num      = `bin/configurator char-bit_num`"      >> config.mak
	echo "short__bit_num     = `bin/configurator short-bit_num`"     >> config.mak
	echo "int__bit_num       = `bin/configurator int-bit_num`"       >> config.mak
	echo "long__bit_num      = `bin/configurator long-bit_num`"      >> config.mak
	echo "long_long__bit_num = `bin/configurator long_long-bit_num`" >> config.mak
	echo "pointer__bit_num   = `bin/configurator pointer-bit_num`"   >> config.mak
	echo "float__bit_num     = `bin/configurator float-bit_num`"     >> config.mak
	echo "double__bit_num    = `bin/configurator double-bit_num`"    >> config.mak
	make configure-append-defines

configure-append-defines:
	echo ""                                                          >> config.mak
	echo "type_bits_flags = \\"                                      >> config.mak
	echo "  -Dchar__bit_num=$(char__bit_num) \\"                     >> config.mak
	echo "  -Dshort__bit_num=$(short__bit_num) \\"                   >> config.mak
	echo "  -Dint__bit_num=$(int__bit_num) \\"                       >> config.mak
	echo "  -Dlong__bit_num=$(long__bit_num) \\"                     >> config.mak
	echo "  -Dlong_long__bit_num=$(long_long__bit_num) \\"           >> config.mak
	echo "  -Dpointer__bit_num=$(pointer__bit_num) \\"               >> config.mak
	echo "  -Dfloat__bit_num=$(float__bit_num) \\"                   >> config.mak
	echo "  -Ddouble__bit_num=$(double__bit_num)"                    >> config.mak
	echo ""                                                          >> config.mak
	echo ""
	echo "type_bits_flags = \\"
	echo "  -Dchar__bit_num=$(char__bit_num) \\"
	echo "  -Dshort__bit_num=$(short__bit_num) \\"
	echo "  -Dint__bit_num=$(int__bit_num) \\"
	echo "  -Dlong__bit_num=$(long__bit_num) \\"
	echo "  -Dlong_long__bit_num=$(long_long__bit_num) \\"
	echo "  -Dpointer__bit_num=$(pointer__bit_num) \\"
	echo "  -Dfloat__bit_num=$(float__bit_num) \\"
	echo "  -Ddouble__bit_num=$(double__bit_num)"
	echo ""

$(compile__funk2): $(funk2_objs) $(funk2_headers) makefile
	gcc $(cc_flags) $(type_bits_flags) $(funk2_objs) $(libs) $(gmodule_linker_flags) -o $@

# compile the repl prompt (garbage collection is disabled until funk2 is stopped and a new repl image is used).
$(compile__bootstrap__repl__img): $(compile__funk2) $(funk2_fu2s)
#	echo "break assert_failed"                 >  compile_bootstrap_repl_img.gdb
#	echo "run $(source__bootstrap__repl__fu2)" >> compile_bootstrap_repl_img.gdb
#	echo "quit"                                >> compile_bootstrap_repl_img.gdb
#	gdb -x compile_bootstrap_repl_img.gdb $(compile__funk2)
	$(compile__funk2) $(source__bootstrap__repl__fu2)

# bootstrap the funk2 processor from a basic repl-prompt.
$(compile__bootstrap__img): $(compile__bootstrap__repl__img) $(funk2_fu2s)
#	echo "break assert_failed"           >  compile_bootstrap_img.gdb
#	echo "run $(source__bootstrap__fu2)" >> compile_bootstrap_img.gdb
#	echo "quit"                          >> compile_bootstrap_img.gdb
#	gdb -x compile_bootstrap_img.gdb $(compile__funk2)
	$(compile__funk2) $(source__bootstrap__fu2)

# objdump/test.objdump is for reverse engineering a machine code compiler from c/test.c (it would be relatively easy to automate this; it would be nice to have our machine code compiler be machine independent)

objdump/test.objdump: bin/test.o makefile
	objdump -d bin/test.o > objdump/test.objdump

bin/test.o: s/test.s makefile
	gcc -c -fPIC -o bin/test.o s/test.s

s/test.s: c/test.c makefile
	gcc -o s/test.s -S c/test.c


%.o: %.c %.h *.[ch] makefile
	gcc $(cc_flags) $(type_bits_flags) -c $< -o $@

%.o: %.c makefile
	gcc $(cc_flags) $(type_bits_flags) -c $< -o $@

clean-config:
	echo "Resetting config.mak"
	rm -f config.tmp
	rm -f config.mak
	echo "" > config.mak

clean--bootstrap-repl.img:
	echo "Removing:"; ls $(compile__bootstrap__repl__img); echo ""
	rm -f $(compile__bootstrap__repl__img)

clean-img:
	echo "Removing:"; ls $(compile__bootstrap__img); echo ""
	rm -f $(compile__bootstrap__img)

clean-o:
	echo "Removing:"; ls c/*.o; echo ""
	rm -f c/*.o

clean-swp:
	echo "Removing:"; ls f2swp/*.f2swp; echo ""
	rm -f f2swp/*.f2swp

clean-trace:
	eccho "Removing:"; ls funk2_trace.log; echo ""
	rm -f funk2_trace.log

clean-install:
	rm -f $(install__funk2)
	rm -f $(install__funk2__system_link)
	rm -f $(install__bootstrap__img)


clean6:        clean-config
clean5: clean6 clean--bootstrap-repl.img
clean4: clean5 clean-img
clean3: clean4 clean-o
clean2: clean3 clean-trace
clean1: clean2 clean-swp
clean0: clean1 clean-install

install-silent: $(compile__funk2)
	echo ""
	echo "make: performing system-wide installation of funk2"
	echo ""
	echo "  install__funk2__dir          = $(install__funk2__dir)"
	echo "  install__bin__dir            = $(install__bin__dir)"
	echo "  install__include__dir        = $(install__include__dir)"
	echo "  install__system_bin__dir     = $(install__system_bin__dir)"
	echo "  install__system_include__dir = $(install__system_include__dir)"
	echo ""
	mkdir -p $(install__funk2__dir)
	mkdir -p $(install__img__dir)
	mkdir -p $(install__bin__dir)
	mkdir -p $(install__include__dir)
	mkdir -p $(install__system_bin__dir)
	mkdir -p $(install__system_include__dir)
	cp -f  $(compile__funk2) $(install__funk2)
	chmod a+rx $(install__funk2)
	ln -fs $(install__funk2) $(install__funk2__system_link)
	chmod a+rx $(install__funk2__system_link)
	cp -f $(compile__bootstrap__img) $(install__bootstrap__img)
	chmod a+r $(install__bootstrap__img)
	cp -f c/*.h $(install__include__dir)
	chmod a+r $(install__include__dir)*.h
	ln -fs $(install__include__dir)*.h $(install__system_include__dir)

clean:     clean1
uninstall: clean0

install:
	make -s install-silent

sin:
	sudo make install

unsin:
	sudo make uninstall

tags:
	cd c/; etags *.[ch]

link-grammar:
	cd extern/link-grammar-4.4.2/; ./configure; make

# RL-Glue Libraries  http://glue.rl-community.org
rlglue:
	cd extern/rlglue-3.02; ./configure --prefix=$(install__rlglue_dir); make; make install
	#cd extern/c-codec-2.0; ./configure --prefix=$(install__rlglue_dir) --with-rl-glue=$(install__rlglue_dir); make; make install



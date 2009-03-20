
CFLAGS := $(CFLAGS) -Wall -pedantic
CC := g++

all: BlocksWorld

BlocksWorld: env_codec.o blocks_world_standalone.o
	$(CC)  $(LDFLAGS) env_codec.o blocks_world_standalone.o -lrlutils -lrlgluenetdev -o BlocksWorld      

blocks_world_standalone.o: src/blocks_world_standalone.c
	$(CC)  $(CFLAGS) -c src/blocks_world_standalone.c -o blocks_world_standalone.o 

env_codec.o: src/env_codec.c
	gcc -Wall -fPIC -DF2__ARCH_32BIT  -Dprocessor_num_power=1 -DF2__COMPILE_TIME_ID=1235493750 -I/usr/include/glib-2.0/ -I/usr/lib/glib-2.0/include/  -DF2__INSTALL__BOOTSTRAP_IMG__FILENAME=\"/usr/local/funk2/img/bootstrap.img\" -DF2__COMPILE__BOOTSTRAP_REPL_IMG__FILENAME=\"./img/bootstrap-repl.img\" -DF2__COMPILE__BOOTSTRAP_IMG__FILENAME=\"./img/bootstrap.img\" -g -pg -DDEBUG -DF2__ASSERTIONS__RELEASE  -Dchar__bit_num=8 -Dshort__bit_num=16 -Dint__bit_num=32 -Dlong__bit_num=32 -Dlong_long__bit_num=64 -Dpointer__bit_num=32 -Dfloat__bit_num=32 -Ddouble__bit_num=64 -c ../../c/f2_primobjects.c -o src/f2_primobjects.o
	$(CC)  $(CFLAGS) -I../include/  -c src/env_codec.c -o env_codec.o 


clean:
	rm -rf env_codec BlocksWorld* *.o










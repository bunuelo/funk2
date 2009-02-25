LDFLAGS := -L../lib -I../include -I../../c
CFLAGS := $(CFLAGS) -Wall -pedantic
CC := g++

all: BlocksWorld

BlocksWorld: env_codec.o blocks_world_standalone.o
	$(CC)  $(LDFLAGS) env_codec.o blocks_world_standalone.o -lrlutils -lrlgluenetdev -o BlocksWorld      

blocks_world_standalone.o: src/blocks_world_standalone.c
	$(CC)  $(CFLAGS) -c src/blocks_world_standalone.c -o blocks_world_standalone.o 

env_codec.o: src/env_codec.c
	$(CC)  $(CFLAGS) -c src/env_codec.c -I/../../c -o env_codec.o 

clean:
	rm -rf env_codec BlocksWorld* *.o










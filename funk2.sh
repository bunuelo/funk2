#!/bin/bash
export UBUNTU_MENUPROXY=0
export LD_LIBRARY_PATH="lib/.libs:/opt/intel/Compiler/11.1/038/lib/intel64/"
export DYLD_LIBRARY_PATH=lib/.libs
export PATH="lib/.libs:$PATH"
bin/funk2 $@
#bin/funk2-static

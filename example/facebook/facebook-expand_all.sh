#!/bin/sh

export LD_LIBRARY_PATH="lib/.libs:/opt/intel/Compiler/11.1/038/lib/intel64/"; export DYLD_LIBRARY_PATH=lib/.libs; export PATH="lib/.libs:$PATH"; bin/funk2 -i img/bootstrap-facebook-expand_all.img


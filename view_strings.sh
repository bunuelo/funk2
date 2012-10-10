#!/bin/sh

strings lib/.libs/libfunk2.a | sed 's/-/\n/g' | sed 's/_/\n/g' | sed 's/ /\n/g' | sort | uniq | less

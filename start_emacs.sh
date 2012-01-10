#!/bin/sh

emacs start_emacs.sh \
      README \
      configure.ac \
      Makefile.am \
      funk-mode.el \
      */*.[ch] */*/*.[ch] \
      */*.fu2 */*/*.fu2 */*/*.fpkg \
      */*/*.py \
      debian/control debian/rules &


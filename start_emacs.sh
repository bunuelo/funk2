#!/bin/sh

emacs start_emacs.sh \
      README.sh \
      README.template \
      funk2.sh \
      configure.ac \
      Makefile.am \
      funk-mode.el \
      */*.[ch] */*/*.[ch] \
      */*.fu2 */*/*.fu2 */*/*.fpkg \
      */*/*.py \
      debian/control debian/rules &


#!/bin/bash -f
# 
# Copyright (c) 2007-2008 Bo Morgan.
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

echo ""
echo "Attempting to generate copyright license patches for all types of source files."
echo ""

##
# generate patch differences from old copyright licences to current copyright licences
#

# C language source files
(diff copyright/copyright_licence-c-old.txt   copyright/copyright_licence-c.txt   > copyright/copyright_licence-c.patch)
if [ $? -eq 0 ]; then echo "diff warning: maybe no upgrade necessary for c sources?  (generating difference (copyright_licence-c.patch) from copyright_licence-c-old.txt to copyright_licence-c.txt)";       fi

# funk2 language source files
(diff copyright/copyright_licence-fu2-old.txt copyright/copyright_licence-fu2.txt > copyright/copyright_licence-fu2.patch)
if [ $? -eq 0 ]; then echo "diff warning: maybe no upgrade necessary for funk2 sources?  (generating difference (copyright_licence-fu2.patch) from copyright_licence-fu2-old.txt to copyright_licence-fu2.txt)"; fi

# makefile language source files
(diff copyright/copyright_licence-mak-old.txt copyright/copyright_licence-mak.txt > copyright/copyright_licence-mak.patch)
if [ $? -eq 0 ]; then echo "diff warning: maybe no upgrade necessary for makefile sources?  (generating difference (copyright_licence-mak.patch) from copyright_licence-mak-old.txt to copyright_licence-mak.txt)"; fi

# bash language source files
(diff copyright/copyright_licence-bash-old.txt copyright/copyright_licence-bash.txt > copyright/copyright_licence-bash.patch)
if [ $? -eq 0 ]; then echo "diff warning: maybe no upgrade necessary for bash sources?  (generating difference (copyright_licence-bash.patch) from copyright_licence-bash-old.txt to copyright_licence-bash.txt)"; fi

#
##

cp -f copyright/copyright_licence-c-old.txt    copyright/copyright_licence-c-test.txt;    if [ $? -ne 0 ]; then echo "cp error: copying copyright_licence-c-old.txt to copyright_licence-c-test.txt";     fi
cp -f copyright/copyright_licence-fu2-old.txt  copyright/copyright_licence-fu2-test.txt;  if [ $? -ne 0 ]; then echo "cp error: copying copyright_licence-fu2-old.txt to copyright_licence-fu2-test.txt"; fi
cp -f copyright/copyright_licence-mak-old.txt  copyright/copyright_licence-mak-test.txt;  if [ $? -ne 0 ]; then echo "cp error: copying copyright_licence-mak-old.txt to copyright_licence-mak-test.txt"; fi
cp -f copyright/copyright_licence-bash-old.txt copyright/copyright_licence-bash-test.txt; if [ $? -ne 0 ]; then echo "cp error: copying copyright_licence-bash-old.txt to copyright_licence-bash-test.txt"; fi

patch -b copyright/copyright_licence-c-test.txt    copyright/copyright_licence-c.patch;    if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-c.patch to copyright_licence-c-test.txt";     fi
patch -b copyright/copyright_licence-fu2-test.txt  copyright/copyright_licence-fu2.patch;  if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-fu2.patch to copyright_licence-fu2-test.txt"; fi
patch -b copyright/copyright_licence-mak-test.txt  copyright/copyright_licence-mak.patch;  if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-mak.patch to copyright_licence-mak-test.txt"; fi
patch -b copyright/copyright_licence-bash-test.txt copyright/copyright_licence-bash.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-bash.patch to copyright_licence-bash-test.txt"; fi

echo ""
echo "If you see errors above, you probably don't want to upgrade all source files with new copyright patch."
echo "Do you want to continue? (yes/no/skip)"
read user_has_desire_to_continue

if [ $user_has_desire_to_continue == "yes" ]; then
  for name in `bash -c "ls -1 c/*.[ch]"`; do
    echo $name
    patch -b $name copyright/copyright_licence-c.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-c.patch to $name"; fi
  done
  
  for name in `bash -c "ls -1 fu2/*.fu2"`; do
    echo $name
    patch -b $name copyright/copyright_licence-fu2.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-fu2.patch to $name"; fi
  done
  
  for name in `bash -c "ls -1 makefile"`; do
    echo $name
    patch -b $name copyright/copyright_licence-mak.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-mak.patch to $name"; fi
  done
  
  for name in `bash -c "ls -1 copyright_licence_upgrade.sh"`; do
    echo $name
    patch -b $name copyright/copyright_licence-bash.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-bash.patch to $name"; fi
  done
fi

if [ $user_has_desire_to_continue == "no" ]; then
  exit
fi

echo ""
echo "If you see errors above, you probably don't want to upgrade old copyright references."
echo "Do you want to continue? (yes/no/skip)"
read user_has_desire_to_continue

if [ $user_has_desire_to_continue == "yes" ]; then
  for name in `bash -c "ls -1 copyright/copyright_licence-c-old.txt"`; do
    echo $name
    patch -b $name copyright/copyright_licence-c.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-c.patch to $name"; fi
  done
  
  for name in `bash -c "ls -1 copyright/copyright_licence-fu2-old.txt"`; do
    echo $name
    patch -b $name copyright/copyright_licence-fu2.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-fu2.patch to $name"; fi
  done
  
  for name in `bash -c "ls -1 copyright/copyright_licence-mak-old.txt"`; do
    echo $name
    patch -b $name copyright/copyright_licence-mak.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-mak.patch to $name"; fi
  done
  
  for name in `bash -c "ls -1 copyright/copyright_licence-bash-old.txt"`; do
    echo $name
    patch -b $name copyright/copyright_licence-bash.patch; if [ $? -ne 0 ]; then echo "patch error: applying copyright_licence-bash.patch to $name"; fi
  done
fi

if [ $user_has_desire_to_continue == "no" ]; then
  exit
fi

  

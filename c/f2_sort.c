// 
// Copyright (c) 2007-2009 Bo Morgan.
// All rights reserved.
// 
// Author: Bo Morgan
// 
// Permission to use, copy, modify and distribute this software and its
// documentation is hereby granted, provided that both the copyright
// notice and this permission notice appear in all copies of the
// software, derivative works or modified versions, and any portions
// thereof, and that both notices appear in supporting documentation.
// 
// BO MORGAN ALLOWS FREE USE OF THIS SOFTWARE IN ITS "AS IS" CONDITION.
// BO MORGAN DISCLAIMS ANY LIABILITY OF ANY KIND FOR ANY DAMAGES
// WHATSOEVER RESULTING FROM THE USE OF THIS SOFTWARE.
// 
// Bo Morgan requests users of this software to return to bo@mit.edu any
// improvements or extensions that they make and grant Bo Morgan the
// rights to redistribute these changes.
// 

#include "funk2.h"

static int f2__sort_integer_list__compare(const void* elt_x_void, const void* elt_y_void) {
  f2ptr elt_x = *((f2ptr*)elt_x_void);
  f2ptr elt_y = *((f2ptr*)elt_y_void);
  if (! raw__integer__is_type(cause, elt_x)) {
    return -1;
  }
  if (! raw__integer__is_type(cause, elt_y)) {
    return 1;
  }
  return f2integer__i(elt_x, cause) - f2integer__i(elt_y, cause);
}

f2ptr f2__sort_integer_list(f2ptr cause, f2ptr integers) {
  size_t sort_array__length = (size_t)raw__length(integers);
  f2ptr* sort_array         = malloc(sizeof(f2ptr));
  {
    size_t index = 0;
    f2ptr iter = integers;
    while (iter) {
      f2ptr car = f2cons__car(iter, cause);
      sort_array[index] = car;
      index ++;
      iter = f2cons__cdr(iter, cause);
    }
  }
  qsort(sort_array, sort_array__length, sizeof(u64), &f2__sort_integer_list__compare);
  f2ptr new_list = nil; 
  {
    u64 i;
    for (i = sort_array__length - 1; i >=  0; i --) {
      new_list = f2cons__new(cause, sort_array[i], new_list);
    }
  }
  return new_list;
}
def_pcfunk1(sort_integer_list, integers, return f2__sort_integer_list(this_cause, integers));

// **

void f2__sort__reinitialize_globalvars() {
}

void f2__sort__initialize() {
  pause_gc();
  
  f2__sort__reinitialize_globalvars();
  
  f2__primcfunk__init__1(sort_integer_list, this, "sort a list of integers into a new list using the quicksort algorithm.");
  
  resume_gc();
  try_gc();
}


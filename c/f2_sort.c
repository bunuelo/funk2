// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

void quicksort_swap_f2ptr(f2ptr cause, f2ptr array, int x_index, int y_index) {
  f2ptr x = raw__array__elt(cause, array, x_index);
  f2ptr y = raw__array__elt(cause, array, y_index);
  {
    f2ptr temp = x;
    x          = y;
    y          = temp;
  }
  raw__array__elt__set(cause, array, x_index, x);
  raw__array__elt__set(cause, array, y_index, y);
}

boolean_t quicksort_integer_greater_than_raw_integer(f2ptr cause, f2ptr x, s64 raw_y) {
  return f2integer__i(x, cause) > raw_y;
}

f2ptr integer_array__quicksort(f2ptr cause, f2ptr array, int first_element, int last_element) {
  f2ptr key;
  s64   raw_key;
  s64   i, j, k;
  if (first_element < last_element) {
    k = ((first_element + last_element) / 2);
    quicksort_swap_f2ptr(cause,  array, first_element,        k );
    key = raw__array__elt(cause, array, first_element);
    raw_key = f2integer__i(key, cause);
    i = first_element + 1;
    j = last_element;
    while (i <= j) {
      boolean_t keep_looping;
      do {
	keep_looping = boolean__false;
	if (i <= last_element) {
	  if (f2integer__i(raw__array__elt(cause, array, i), cause) <= raw_key) {
	    i ++;
	    keep_looping = boolean__true;
	  }
	}
      } while (keep_looping);
      
      do {
	keep_looping = boolean__false;
	if (j >= first_element) {
	  if (f2integer__i(raw__array__elt(cause, array, j), cause) > raw_key) {
	    j --;
	    keep_looping = boolean__true;
	  }
	}
      } while (keep_looping);
      if (i < j) {
	quicksort_swap_f2ptr(cause, array, i, j);
      }
    }
    quicksort_swap_f2ptr(cause, array, first_element, j);
    {
      f2ptr result = integer_array__quicksort(cause, array, first_element, j - 1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = integer_array__quicksort(cause, array, j + 1, last_element);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return array;
}

boolean_t raw__integer_array__is_type(f2ptr cause, f2ptr this) {
  if (! raw__array__is_type(cause, this)) {
    return boolean__false;
  }
  s64 array__length = raw__array__length(cause, this);
  {
    s64 index;
    for (index = 0; index < array__length; index ++) {
      f2ptr element = raw__array__elt(cause, this, index);
      if (! raw__integer__is_type(cause, element)) {
	return boolean__false;
      }
    }
  }
  return boolean__true;
}

f2ptr raw__integer_array__quicksort(f2ptr cause, f2ptr array) {
  s64 array__length = raw__array__length(cause, array);
  return integer_array__quicksort(cause, array, 0, array__length - 1);
}

f2ptr f2__integer_array__quicksort(f2ptr cause, f2ptr this) {
  assert_argument_type(integer_array, this);
  return raw__integer_array__quicksort(cause, this);
}

def_pcfunk1(sort_integer_array, integers,
	    "sort an array of integers in place., """,
	    return f2__integer_array__quicksort(this_cause, integers));


f2ptr array__quicksort_helper(f2ptr cause, f2ptr fiber, f2ptr array, f2ptr comparison_funk, int first_element, int last_element) {
  f2ptr key;
  //s64   raw_key;
  s64   i, j, k;
  if (first_element < last_element) {
    k = ((first_element + last_element) / 2);
    quicksort_swap_f2ptr(cause,  array, first_element,        k );
    key = raw__array__elt(cause, array, first_element);
    //raw_key = f2integer__i(key, cause);
    i = first_element + 1;
    j = last_element;
    while (i <= j) {
      boolean_t keep_looping;
      do {
	keep_looping = boolean__false;
	if (i <= last_element) {
	  f2ptr comparison_result = f2__force_funk_apply(cause, fiber, comparison_funk, f2list2__new(cause, raw__array__elt(cause, array, i), key));
          if (raw__larva__is_type(cause, comparison_result)) {
            return comparison_result;
          }
          if (! comparison_result) {
	    i ++;
	    keep_looping = boolean__true;
	  }
	}
      } while (keep_looping);
      
      do {
	keep_looping = boolean__false;
	if (j >= first_element) {
	  f2ptr comparison_result = f2__force_funk_apply(cause, fiber, comparison_funk, f2list2__new(cause, raw__array__elt(cause, array, j), key));
          if (raw__larva__is_type(cause, comparison_result)) {
            return comparison_result;
          }
          if (comparison_result) {
	    j --;
	    keep_looping = boolean__true;
	  }
	}
      } while (keep_looping);
      if (i < j) {
	quicksort_swap_f2ptr(cause, array, i, j);
      }
    }
    quicksort_swap_f2ptr(cause, array, first_element, j);
    {
      f2ptr result = array__quicksort_helper(cause, fiber, array, comparison_funk, first_element, j - 1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    {
      f2ptr result = array__quicksort_helper(cause, fiber, array, comparison_funk, j + 1, last_element);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
  }
  return array;
}

f2ptr raw__array__quicksort(f2ptr cause, f2ptr this, f2ptr comparison_funk) {
  f2ptr fiber = f2__this__fiber(cause);
  return array__quicksort_helper(cause, fiber, this, comparison_funk, 0, raw__array__length(cause, this) - 1);
}

f2ptr f2__array__quicksort(f2ptr cause, f2ptr this, f2ptr comparison_funk) {
  assert_argument_type(array,    this);
  assert_argument_type(funkable, comparison_funk);
  return raw__array__quicksort(cause, this, comparison_funk);
}
def_pcfunk2(array__quicksort, this, comparison_funk,
	    "",
	    return f2__array__quicksort(this_cause, this, comparison_funk));

f2ptr f2__array__sort(f2ptr cause, f2ptr this, f2ptr comparison_funk) {
  return f2__array__quicksort(cause, this, comparison_funk);
}
def_pcfunk2(array__sort, this, comparison_funk,
	    "sort an array of elements in place by user-provided comparison_funk.",
	    return f2__array__sort(this_cause, this, comparison_funk));


f2ptr raw__conslist__sort(f2ptr cause, f2ptr this, f2ptr comparison_funk) {
  f2ptr array = raw__conslist__as__array(cause, this);
  if (raw__larva__is_type(cause, array)) {
    return array;
  }
  f2ptr result = f2__array__sort(cause, array, comparison_funk);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  f2ptr new_conslist = f2__array__as__conslist(cause, array);
  return new_conslist;
}

f2ptr f2__conslist__sort(f2ptr cause, f2ptr this, f2ptr comparison_funk) {
  assert_argument_type(conslist, this);
  assert_argument_type(funkable, comparison_funk);
  return raw__conslist__sort(cause, this, comparison_funk);
}
def_pcfunk2(conslist__sort, this, comparison_funk,
	    "returns a new conslist that is this conslist sorted by user-provided comparison_funk.",
	    return f2__conslist__sort(this_cause, this, comparison_funk));


// **

void f2__sort__defragment__fix_pointers() {
  // -- reinitialize --
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(sort_integer_array);
  f2__primcfunk__init__defragment__fix_pointers(array__quicksort);
  f2__primcfunk__init__defragment__fix_pointers(array__sort);
  f2__primcfunk__init__defragment__fix_pointers(conslist__sort);
}

void f2__sort__reinitialize_globalvars() {
  f2__primcfunk__init__1(sort_integer_array, this);
  f2__primcfunk__init__2(array__quicksort, this, comparison_funk);
  f2__primcfunk__init__2(array__sort, this, comparison_funk);
  f2__primcfunk__init__2(conslist__sort, this, comparison_funk);
}

void f2__sort__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "sort", "", &f2__sort__reinitialize_globalvars, &f2__sort__defragment__fix_pointers);
  
  f2__sort__reinitialize_globalvars();
}


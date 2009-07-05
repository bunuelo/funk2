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

/*
void quicksort_swap(int *x, int *y) {
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

void quicksort(int* array, int first_element, int last_element_minus_one) {
  int key, i, j, k;
  if (first_element < last_element_minus_one) {
    k = ((first_element + last_element_minus_one) / 2);
    quicksort_swap(&array[first_element], &array[k]);
    key = array[first_element];
    i = first_element + 1;
    j = last_element_minus_one;
    while (i <= j) {
      while ((i <= last_element_minus_one) && (array[i] <= key)) {
	i ++;
      }
      while ((j >= first_element) && (array[j] > key)) {
	j --;
      }
      if ( i < j) {
	quicksort_swap(&array[i], &array[j]);
      }
    }
    quicksort_swap(&array[first_element], &array[j]);
    quicksort(array, first_element, j-1);
    quicksort(array, j+1, last_element_minus_one);
  }
}
*/

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
  if (! raw__integer__is_type(cause, x)) {
    return boolean__false;
  }
  return f2integer__i(x, cause) > raw_y;
}

//void quicksort(             int*  array, int first_element, int last_element) {
f2ptr integer_array__quicksort(f2ptr cause, f2ptr array, int first_element, int last_element) {
  //int key, i, j, k;
  f2ptr key;
  s64   raw_key;
  s64   i, j, k;
  //if (first_element < last_element) {
  if (first_element < last_element) {
    //k = ((first_element + last_element) / 2);
    k = ((first_element + last_element) / 2);
    //quicksort_swap    (       &array[first_element], &array[k]);
    quicksort_swap_f2ptr(cause,  array, first_element,        k );
    //key = array[first_element];
    key = raw__array__elt(cause, array, first_element);
    if (! raw__integer__is_type(cause, key)) {
      return f2larva__new(cause, 1);
    }
    //i = first_element + 1;
    i = first_element + 1;
    //j = last_element;
    j = last_element;
    //while (i <= j) {
    while (i <= j) {
      //while ((i <= last_element) && (array[i] <= key)) {
      while ((i <= last_element) && (! quicksort_integer_greater_than_raw_integer(cause, raw__array__elt(cause, array, i), raw_key))) {
	//i ++;
	i ++;
	//}
      }
      //while ((j >= first_element) && (array[j] > key)) {
      while ((j >= first_element) && quicksort_integer_greater_than_raw_integer(cause, raw__array__elt(cause, array, j), raw_key)) {
	//j --;
	j --;
	//}
      }
      //if (i < j) {
      if (i < j) {
	//quicksort_swap(&array[i], &array[j]);
	quicksort_swap_f2ptr(cause, array, i, j);
	//}
      }
      //}
    }
    //quicksort_swap(&array[first_element], &array[j]);
    quicksort_swap_f2ptr(cause, array, first_element, j);
    //quicksort(array, first_element, j-1);
    {
      f2ptr result = integer_array__quicksort(cause, array, first_element, j - 1);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    //quicksort(array, j+1, last_element);
    {
      f2ptr result = integer_array__quicksort(cause, array, j + 1, last_element);
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    //}
  }
  //}
  return array;
}


f2ptr f2__integer_array__quicksort(f2ptr cause, f2ptr array) {
  return integer_array__quicksort(cause, array, 0, raw__array__length(cause, array) - 1);
}
def_pcfunk1(sort_integer_list, integers, return f2__integer_array__quicksort(this_cause, integers));

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


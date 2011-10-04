// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#define F2__DEBUG_HEAP 1

#define funk2_heap__minimum_size (10)
#define funk2_heap__maximum_key  (((u64)1ull)<<63)

// funk2_heap

void funk2_heap__init(funk2_heap_t* this, u64 element_array_size) {
  if (element_array_size < funk2_heap__minimum_size) {
    error(nil, "funk2_heap__init error: element_array_size is less than funk2_heap__minimum_size.");
  }
  this->element_array_size     = element_array_size;
  this->element_array_used_num = 0;
  this->element_array          = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * (element_array_size + 1)));
  this->element_array[0]       = (funk2_heap_node_t*)from_ptr(f2__malloc(sizeof(funk2_heap_node_t)));
  this->element_array[0]->key  = funk2_heap__maximum_key;
}


void funk2_heap__destroy(funk2_heap_t* this) {
  f2__free(to_ptr(this->element_array));
}


void funk2_heap__make_empty(funk2_heap_t* this) {
  this->element_array_used_num = 0;
}


boolean_t funk2_heap__is_empty(funk2_heap_t* this) {
  return ((this->element_array_used_num == 0));
}


boolean_t funk2_heap__is_full(funk2_heap_t* this) {
  return ((this->element_array_used_num == (this->element_array_size)));
}


// this->element_array[0] is a sentinel
void funk2_heap__insert(funk2_heap_t* this, funk2_heap_node_t* node) {
  s64 index;
  
  if(funk2_heap__is_full(this)) {
    error(nil, "funk2_heap error: attempted to insert element into full heap.");
  }
  
  this->element_array_used_num ++;
  
  for(index = this->element_array_used_num; this->element_array[index >> 1]->key < node->key; index >>= 1) {
    this->element_array[index] = this->element_array[index >> 1];
  }
  this->element_array[index] = node;
}


funk2_heap_node_t* funk2_heap__remove_maximum(funk2_heap_t* this) {
  s64                index;
  s64                child_index;
  funk2_heap_node_t* maximum_element;
  funk2_heap_node_t* last_element;
  
  if (funk2_heap__is_empty(this)) {
    error(nil, "funk2_heap error: attempt to remove element from empty heap.");
  }
  
  maximum_element = this->element_array[1];
  last_element    = this->element_array[this->element_array_used_num];
  
  this->element_array_used_num --;
  
  for(index = 1; (index << 1) <= this->element_array_used_num; index = child_index) {
    // find smaller child
    child_index = index << 1;
    if ((child_index != this->element_array_used_num) &&
	(this->element_array[child_index + 1] < this->element_array[child_index])) {
      child_index ++;
    }
    
    // percolate one level
    if( last_element > this->element_array[child_index]) {
      this->element_array[index] = this->element_array[child_index];
    } else {
      break;
    }
  }
  this->element_array[index] = last_element;
  return maximum_element;
}


funk2_heap_node_t* funk2_heap__maximum_node(funk2_heap_t* this) {
  if (funk2_heap__is_empty(this)) {
    error(nil, "funk2_heap error: attempted to find maximum value in empty heap.");
  }
  return this->element_array[1];
}


void funk2_heap__print(funk2_heap_t* this) {
  printf("\n<funk2_heap " ptr__fstr "> = [", (ptr)(this)); fflush(stdout);
  {
    u64 index = 1;
    while (index <= this->element_array_used_num) {
      funk2_heap_node_t* node = this->element_array[index];
      if (index != 1) {
	printf(" "); fflush(stdout);
      }
      printf(" " u64__fstr, (u64)(node->key)); fflush(stdout);
      index ++;
    }
  }
  printf("]"); fflush(stdout);
}


void heap__tests() {
  printf("\nheap__tests note: here."); fflush(stdout);
  printf("\n"); fflush(stdout);
  
  {
    u64 node_num = 100;
    
    funk2_heap_t* heap = (funk2_heap_t*)from_ptr(f2__malloc(sizeof(funk2_heap_t)));
    funk2_heap__init(heap, node_num);
    
    funk2_heap_node_t** node_array = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * node_num));
    {
      u64 i;
      for (i = 0; i < node_num; i ++) {
	node_array[i] = (funk2_heap_node_t*)from_ptr(f2__malloc(sizeof(funk2_heap_node_t)));
	node_array[i]->key = i + 100;
      }
    }
    
    funk2_heap__print(heap); printf("\n"); fflush(stdout);
    
    {
      s64 i;
      for (i = 0; i < 4; i ++) {
	funk2_heap__insert(heap, node_array[i]);
      }
    }
    
    funk2_heap__print(heap); printf("\n"); fflush(stdout);
    
    
    funk2_heap__destroy(heap);
    f2__free(to_ptr(heap));
  }
  
  printf("\nheap__tests note: done."); fflush(stdout);
  printf("\n"); fflush(stdout);
}


void f2__heap__initialize() {
#if defined(F2__DEBUG_HEAP)
  heap__tests();
#endif // F2__DEBUG_HEAP
}


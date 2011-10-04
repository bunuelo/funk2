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

void funk2_heap__init(funk2_heap_t* this, u64 node_array_size) {
  if (node_array_size < funk2_heap__minimum_size) {
    error(nil, "funk2_heap__init error: node_array_size is less than funk2_heap__minimum_size.");
  }
  this->node_array_size     = node_array_size;
  this->node_array_used_num = 0;
  this->node_array          = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * (node_array_size + 1)));
  this->node_array[0]       = (funk2_heap_node_t*)from_ptr(f2__malloc(sizeof(funk2_heap_node_t)));
  this->node_array[0]->key  = funk2_heap__maximum_key;
}


void funk2_heap__destroy(funk2_heap_t* this) {
  f2__free(to_ptr(this->node_array));
}


void funk2_heap__make_empty(funk2_heap_t* this) {
  this->node_array_used_num = 0;
}


boolean_t funk2_heap__is_empty(funk2_heap_t* this) {
  return ((this->node_array_used_num == 0));
}


boolean_t funk2_heap__is_full(funk2_heap_t* this) {
  return ((this->node_array_used_num == (this->node_array_size)));
}


// this->node_array[0] is a sentinel
void funk2_heap__insert(funk2_heap_t* this, funk2_heap_node_t* node) {
  s64 index;
  
  if(funk2_heap__is_full(this)) {
    error(nil, "funk2_heap error: attempted to insert node into full heap.");
  }
  
  this->node_array_used_num ++;
  
  for(index = this->node_array_used_num; this->node_array[index >> 1]->key < node->key; index >>= 1) {
    this->node_array[index] = this->node_array[index >> 1];
  }
  this->node_array[index] = node;
}


funk2_heap_node_t* funk2_heap__remove_maximum(funk2_heap_t* this) {
  s64                index;
  s64                child_index;
  funk2_heap_node_t* maximum_node;
  funk2_heap_node_t* last_node;
  
  if (funk2_heap__is_empty(this)) {
    error(nil, "funk2_heap error: attempt to remove node from empty heap.");
  }
  
  maximum_node = this->node_array[1];
  last_node    = this->node_array[this->node_array_used_num];
  
  this->node_array_used_num --;
  
  for(index = 1; (index << 1) <= this->node_array_used_num; index = child_index) {
    // find larger child
    child_index = index << 1;
    if ((child_index != this->node_array_used_num) &&
	(this->node_array[child_index + 1]->key < this->node_array[child_index]->key)) {
      child_index ++;
    }
    
    // percolate one level
    if( last_node->key > this->node_array[child_index]->key) {
      this->node_array[index] = this->node_array[child_index];
    } else {
      break;
    }
  }
  this->node_array[index] = last_node;
  return maximum_node;
}


funk2_heap_node_t* funk2_heap__maximum_node(funk2_heap_t* this) {
  if (funk2_heap__is_empty(this)) {
    error(nil, "funk2_heap error: attempted to find maximum value in empty heap.");
  }
  return this->node_array[1];
}


void funk2_heap__print(funk2_heap_t* this) {
  printf("<funk2_heap " ptr__fstr "> = [", (ptr)(this)); fflush(stdout);
  {
    u64 index;
    for (index = 1; index <= this->node_array_used_num; index ++) {
      funk2_heap_node_t* node = this->node_array[index];
      if (index != 1) {
	printf(" "); fflush(stdout);
      }
      printf(u64__fstr, (u64)(node->key)); fflush(stdout);
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
    
    printf("\n"); funk2_heap__print(heap); fflush(stdout);
    printf("\n"); fflush(stdout);
    
    {
      s64 i;
      for (i = 0; i < node_num; i ++) {
	funk2_heap__insert(heap, node_array[i]);
	printf("\n  "); fflush(stdout); funk2_heap__print(heap); printf("\n"); fflush(stdout);
      }
    }
    
    printf("\nheap__tests note: final heap: "); fflush(stdout); funk2_heap__print(heap); printf("\n"); fflush(stdout);
    
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


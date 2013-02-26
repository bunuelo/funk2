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

//#define F2__DEBUG_HEAP 1

#define funk2_heap__minimum_size (10)
#define funk2_heap__maximum_key  ((((u64)1ull) << pool_address__bit_num) - 1)

// funk2_heap

void funk2_heap__init(funk2_heap_t* this) {
  if (heap_index__max < funk2_heap__minimum_size) {
    error(nil, "funk2_heap__init error: heap_index__max is less than funk2_heap__minimum_size.");
  }
  this->node_array_used_num       = 0;
  this->node_array                = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * (heap_index__max + 1)));
  this->node_array[0]             = (funk2_heap_node_t*)from_ptr(f2__malloc(sizeof(funk2_heap_node_t)));
  this->node_array[0]->key        = funk2_heap__maximum_key;
  this->node_array[0]->heap_index = 0;
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
  return ((this->node_array_used_num == (heap_index__max - 1)));
}


funk2_heap_node_t* funk2_heap__maximum(funk2_heap_t* this) {
  if (funk2_heap__is_empty(this)) {
    return NULL;
  }
  return this->node_array[1];
}


// this->node_array[0] is a sentinel
void funk2_heap__insert(funk2_heap_t* this, funk2_heap_node_t* node) {
  s64 index;
  
  if(funk2_heap__is_full(this)) {
    error(nil, "funk2_heap error: attempted to insert node into full heap.");
  }
  
  this->node_array_used_num ++;
  
  for(index = this->node_array_used_num; this->node_array[index >> 1]->key < node->key; index >>= 1) {
    this->node_array[index]             = this->node_array[index >> 1];
    this->node_array[index]->heap_index = index;
  }
  this->node_array[index]             = node;
  this->node_array[index]->heap_index = index;
}


funk2_heap_node_t* funk2_heap__remove_index(funk2_heap_t* this, s64 remove_index) {
  s64                index;
  s64                child_index;
  funk2_heap_node_t* old_index_node;
  funk2_heap_node_t* last_node;
  
  if (funk2_heap__is_empty(this)) {
    error(nil, "funk2_heap error: attempt to remove node from empty heap.");
  }
  
  if ((remove_index < 1) ||
      (remove_index > this->node_array_used_num)) {
    error(nil, "funk2_heap error: attempt to remove node index outside of heap.");
  }
  
  old_index_node = this->node_array[remove_index];
  last_node      = this->node_array[this->node_array_used_num];
  
  this->node_array_used_num --;
  
  for(index = remove_index; (index << 1) <= this->node_array_used_num; index = child_index) {
    // find larger child
    child_index = index << 1;
    if ((child_index != this->node_array_used_num) &&
	(this->node_array[child_index + 1]->key > this->node_array[child_index]->key)) {
      child_index ++;
    }
    
    // percolate one level
    if (last_node->key < this->node_array[child_index]->key) {
      this->node_array[index]             = this->node_array[child_index];
      this->node_array[index]->heap_index = index;
    } else {
      break;
    }
  }
  this->node_array[index]             = last_node;
  this->node_array[index]->heap_index = index;
  
  return old_index_node;
}


funk2_heap_node_t* funk2_heap__remove_maximum(funk2_heap_t* this) {
  funk2_heap_node_t* maximum_node = funk2_heap__remove_index(this, 1);
  return maximum_node;
}

void funk2_heap__remove(funk2_heap_t* this, funk2_heap_node_t* node) {
  funk2_heap_node_t* removed_node = funk2_heap__remove_index(this, node->heap_index);
  if (node != removed_node) {
    error(nil, "funk2_heap__remove fatal error: removed node is not correct.");
  }
}


u64 funk2_heap__size(funk2_heap_t* this) {
  return this->node_array_used_num;
}


void funk2_heap__print(funk2_heap_t* this) {
  printf("<funk2_heap " ptr__fstr "> = [", (ptr)(this)); fflush(stdout);
  {
    s64 index = 0;
    funk2_heap__iteration(this, node,
			  if (index != 0) {
			    printf(" "); fflush(stdout);
			  }
			  printf(u64__fstr, (u64)(node->key)); fflush(stdout);
			  index ++;
			  );
  }
  printf("]"); fflush(stdout);
}


void heap__tests() {
  printf("\nheap__tests note: here."); fflush(stdout);
  printf("\n"); fflush(stdout);
  
  {
    u64 node_num = 16;
    
    funk2_heap_t* heap = (funk2_heap_t*)from_ptr(f2__malloc(sizeof(funk2_heap_t)));
    funk2_heap__init(heap);
    
    funk2_heap_node_t** node_array = (funk2_heap_node_t**)from_ptr(f2__malloc(sizeof(funk2_heap_node_t*) * node_num));
    {
      u64 i;
      for (i = 0; i < node_num; i ++) {
	node_array[i] = (funk2_heap_node_t*)from_ptr(f2__malloc(sizeof(funk2_heap_node_t)));
	node_array[i]->key = i;
      }
    }
    
    {
      printf("\n  "); funk2_heap__print(heap); fflush(stdout);
      
      {
	s64 i;
	for (i = 0; i < node_num; i ++) {
	  funk2_heap__insert(heap, node_array[i]);
	  printf("\n  "); fflush(stdout); funk2_heap__print(heap);
	}
      }
      
      {
	s64 i;
	for (i = 0; i < node_num; i ++) {
	  funk2_heap__remove_maximum(heap);
	  printf("\n  "); fflush(stdout); funk2_heap__print(heap);
	}
      }
      
      printf("\n"); fflush(stdout);
    }
    
    printf("\nheap__tests note: final heap: "); fflush(stdout); funk2_heap__print(heap);
    printf("\n"); fflush(stdout);
    
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


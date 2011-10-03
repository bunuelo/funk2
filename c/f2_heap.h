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

#ifndef F2__HEAP__H
#define F2__HEAP__H

typedef funk2_heap_node_s funk2_heap_node_t;
struct funk2_heap_node_s {
  u64 key;
};

typedef funk2_heap_s funk2_heap_t;
struct funk2_heap_s {
  u64                 element_array_size;
  u64                 element_array_used_num;
  funk2_heap_node_t** element_array;
};

// funk2_heap

void               funk2_heap__init(          funk2_heap_t* this, u64 element_array_size);
void               funk2_heap__destroy(       funk2_heap_t* this);
void               funk2_heap__make_empty(    funk2_heap_t* this);
boolean_t          funk2_heap__is_empty(      funk2_heap_t* this);
boolean_t          funk2_heap__is_full(       funk2_heap_t* this);
void               funk2_heap__insert(        funk2_heap_t* this, funk2_heap_node_t* node);
funk2_heap_node_t* funk2_heap__remove_maximum(funk2_heap_t* this);
funk2_heap_node_t* funk2_heap__maximum_node(  funk2_heap_t* this);

#endif // F2__HEAP__H


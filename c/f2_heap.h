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

#ifndef F2__HEAP__H
#define F2__HEAP__H

#define heap_index__bit_num (7 + 10 + 10)
#define heap_index__max     ((1ull << heap_index__bit_num) - 1)

typedef struct funk2_heap_node_s funk2_heap_node_t;
struct funk2_heap_node_s {
  u64 key        : pool_address__bit_num;
  u64 heap_index : heap_index__bit_num;
} __attribute__((__packed__));

typedef struct funk2_heap_s funk2_heap_t;
struct funk2_heap_s {
  u64                 node_array_used_num;
  funk2_heap_node_t** node_array;
};

// funk2_heap

void               funk2_heap__init          (funk2_heap_t* this);
void               funk2_heap__destroy       (funk2_heap_t* this);
void               funk2_heap__make_empty    (funk2_heap_t* this);
boolean_t          funk2_heap__is_empty      (funk2_heap_t* this);
boolean_t          funk2_heap__is_full       (funk2_heap_t* this);
void               funk2_heap__insert        (funk2_heap_t* this, funk2_heap_node_t* node);
funk2_heap_node_t* funk2_heap__maximum       (funk2_heap_t* this);
funk2_heap_node_t* funk2_heap__remove_maximum(funk2_heap_t* this);
u64                funk2_heap__size          (funk2_heap_t* this);
void               funk2_heap__remove        (funk2_heap_t* this, funk2_heap_node_t* node);

#define funk2_heap__iteration(this, node, body) {			\
    funk2_heap_t*      funk2_heap__iteration__this = this;		\
    funk2_heap_node_t* node;						\
    s64                funk2_heap__iteration__index;			\
    for (funk2_heap__iteration__index = 1; funk2_heap__iteration__index <= funk2_heap__iteration__this->node_array_used_num; funk2_heap__iteration__index ++) { \
      node = funk2_heap__iteration__this->node_array[funk2_heap__iteration__index]; \
      {									\
	body;								\
      }									\
    }									\
  }



// **

void f2__heap__initialize();

#endif // F2__HEAP__H


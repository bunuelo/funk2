// 
// Copyright (c) 2007-2008 Bo Morgan.
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

// garbage_collector_set

void funk2_garbage_collector_set__init(funk2_garbage_collector_set_t* this) {
  this->first = NULL;
}

void funk2_garbage_collector_set__destroy(funk2_garbage_collector_set_t* this) {
  funk2_garbage_collector_set_node_t* iter;
  while (iter) {
    funk2_garbage_collector_set_node_t* next = iter->next;
    free(iter);
    iter = next;
  }
}

void funk2_garbage_collector_set__add_block(funk2_garbage_collector_set_t* this, funk2_memblock_t* block) {
  funk2_garbage_collector_set_node_t* new_node = (funk2_garbage_collector_set_node_t*)f2__malloc(sizeof(funk2_garbage_collector_set_node_t));
  new_node->block   = block;
  new_node->prev    = NULL;
  new_node->next    = this->first;
  this->first->prev = new_node;
  this->first       = new_node;
}

void funk2_garbage_collector_set__remove_and_free_node(funk2_garbage_collector_set_t* this, funk2_garbage_collector_set_node_t* node) {
  if (node->prev) {
    node->prev->next = node->next;
  } else {
    this->first = node->next;
  }
  if (node->next) {
    node->next->prev = node->prev;
  }
  free(node);
}

void funk2_garbage_collector_set__test() {
  funk2_garbage_collector_set_t set;
  funk2_garbage_collector_set__init(&set);
  int i;
  for (i = 1; i <= 10; i ++) {
    funk2_garbage_collector_set__add_block(&set, (funk2_memblock_t*)i);
  }
  funk2_garbage_collector_set_node_t* iter = set->first;
  printf("\ngc set test:", prev, (int)(iter->block), next);
  while (iter) {
    int prev = (int)(iter->prev ? iter->prev->block : 0);
    int next = (int)(iter->next ? iter->next->block : 0);
    printf("\n  [(%d) %d (%d)]", prev, (int)(iter->block), next);
    iter = iter->next;
  }
  printf("\n");
  funk2_garbage_collector_set__destroy(&set);
}

// garbage_collector

void funk2_garbage_collector__init(funk2_garbage_collector_t* this) {
  funk2_garbage_collector_set__init(&(this->black_set));
  funk2_garbage_collector_set__init(&(this->grey_set));
  funk2_garbage_collector_set__init(&(this->white_set));
}

void funk2_garbage_collector__destroy(funk2_garbage_collector_t* this) {
  funk2_garbage_collector_set__destroy(&(this->black_set));
  funk2_garbage_collector_set__destroy(&(this->grey_set));
  funk2_garbage_collector_set__destroy(&(this->white_set));
}

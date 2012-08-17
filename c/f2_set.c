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

// set

void funk2_set__init(funk2_set_t* this) {
  this->element_count = 0;
  this->bin_power     = 0;
  this->bin           = (funk2_set_node_t**)from_ptr(f2__malloc(sizeof(funk2_set_node_t*) << this->bin_power));
  memset(this->bin, 0, sizeof(funk2_set_node_t*) << (this->bin_power));
}

void funk2_set__destroy(funk2_set_t* this) {
  funk2_set__remove_all(this);
  f2__free(to_ptr(this->bin));
}

void funk2_set__remove_all(funk2_set_t* this) {
  u64 i;
  u64 bin_num = 1ull << this->bin_power;
  for (i = 0; i < bin_num; i ++) {
    funk2_set_node_t* iter = this->bin[i];
    while (iter) {
      funk2_set_node_t* next = iter->next;
      f2__free(to_ptr(iter));
      iter = next;
    }
  }
}

u64 funk2_set__element_bin_index(funk2_set_t* this, funk2_set_element_t element) {
  return (element * funk2_set_prime_number__32_bit) & ((1ull << (this->bin_power)) - 1);
}

u64 funk2_set__element_count(funk2_set_t* this) {
  return this->element_count;
}

void funk2_set__double_size(funk2_set_t* this) {
  u64                old_bin_power = this->bin_power;
  funk2_set_node_t** old_bin       = this->bin;
  this->bin_power ++;
  this->bin = (funk2_set_node_t**)from_ptr(f2__malloc(sizeof(funk2_set_node_t*) << (this->bin_power)));
  memset(this->bin, 0, sizeof(funk2_set_node_t*) << (this->bin_power));
  u64 old_bin_num = 1ull << old_bin_power;
  u64 i;
  for (i = 0; i < old_bin_num; i ++) {
    funk2_set_node_t* iter = old_bin[i];
    while (iter) {
      funk2_set_node_t* next = iter->next;
      u64 index = funk2_set__element_bin_index(this, iter->element);
      iter->next = this->bin[index];
      this->bin[index] = iter;
      iter = next;
    }
  }
  f2__free(to_ptr(old_bin));
}

void funk2_set__add_node(funk2_set_t* this, funk2_set_node_t* node) {
  u64 i = funk2_set__element_bin_index(this, node->element);
  node->next = this->bin[i];
  this->bin[i] = node;
  this->element_count ++;
  if (this->element_count >= (1ull << this->bin_power)) {
    funk2_set__double_size(this);
  }
}

void funk2_set__add(funk2_set_t* this, funk2_set_element_t element) {
  funk2_set_node_t* node = (funk2_set_node_t*)from_ptr(f2__malloc(sizeof(funk2_set_node_t)));
  node->element = element;
  funk2_set__add_node(this, node);
}

boolean_t funk2_set__contains(funk2_set_t* this, funk2_set_element_t element) {
  u64 i = funk2_set__element_bin_index(this, element);
  funk2_set_node_t* iter = this->bin[i];
  while (iter) {
    funk2_set_node_t* next = iter->next;
    if (iter->element == element) {
      return boolean__true;
    }
    iter = next;
  }
  return boolean__false;
}

funk2_set_node_t* funk2_set__remove_node(funk2_set_t* this, funk2_set_element_t element) {
  u64 i = funk2_set__element_bin_index(this, element);
  funk2_set_node_t* prev = NULL;
  funk2_set_node_t* iter = this->bin[i];
  while (iter) {
    funk2_set_node_t* next = iter->next;
    if (iter->element == element) {
      if (prev) {
	prev->next = iter->next;
      } else {
	this->bin[i] = iter->next;
      }
      this->element_count --;
      return iter;
    }
    prev = iter;
    iter = next;
  }
  error(nil, "funk2_set__remove_node error: element is not in set.");
}

void funk2_set__remove(funk2_set_t* this, funk2_set_element_t element) {
  f2__free(to_ptr(funk2_set__remove_node(this, element)));
}

void funk2_set__remove_and_add_to(funk2_set_t* this, funk2_set_element_t element, funk2_set_t* to_set) {
  funk2_set__add_node(to_set, funk2_set__remove_node(this, element));
}

void* funk2_set__mapc(funk2_set_t* this, void(* mapc_funk)(funk2_set_element_t element, void** user_data, boolean_t* stop, void** return_value), void** user_data) {
  u64                bin_num      = 1ull << this->bin_power;
  funk2_set_node_t** bin          = this->bin;
  boolean_t          stop         = boolean__false;
  void*              return_value = NULL;
  u64 i;
  for (i = 0; i < bin_num; i ++) {
    funk2_set_node_t* iter = bin[i];
    while (iter) {
      funk2_set_node_t*   next    = iter->next;
      funk2_set_element_t element = bin[i]->element;
      (*mapc_funk)(element, user_data, &stop, &return_value);
      iter = next;
      if (stop) {
	return return_value;
      }
    }
  }
  return return_value;
}

s64 funk2_set__calculate_save_size(funk2_set_t* this) {
  s64 save_size = 0;
  {
    u64 bin_num = 1ull << this->bin_power;
    u64 element_count = this->element_count;
    save_size += sizeof(element_count);
    u64 i;
    for (i = 0; i < bin_num; i ++) {
      funk2_set_node_t* iter = this->bin[i];
      while (iter) {
	funk2_set_element_t element = iter->element;
	save_size += sizeof(element);
	iter = iter->next;
      }
    }
  }
  return save_size;
}

void funk2_set__save_to_stream(funk2_set_t* this, int fd) {
  u64 bin_num = 1ull << this->bin_power;
  u64 element_count = this->element_count;
  safe_write(fd, to_ptr(&element_count), sizeof(element_count));
  u64 i;
  for (i = 0; i < bin_num; i ++) {
    funk2_set_node_t* iter = this->bin[i];
    while (iter) {
      funk2_set_element_t element = iter->element;
      safe_write(fd, to_ptr(&element), sizeof(element));
      iter = iter->next;
    }
  }
}

u64 funk2_set__save_to_buffer(funk2_set_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  {
    u64 bin_num = 1ull << this->bin_power;
    u64 element_count = this->element_count;
    //safe_write(fd, to_ptr(&element_count), sizeof(element_count));
    memcpy(buffer, &element_count, sizeof(element_count)); buffer += sizeof(element_count);
    u64 i;
    for (i = 0; i < bin_num; i ++) {
      funk2_set_node_t* iter = this->bin[i];
      while (iter) {
	funk2_set_element_t element = iter->element;
	//safe_write(fd, to_ptr(&element), sizeof(element));
	memcpy(buffer, &element, sizeof(element)); buffer += sizeof(element);
	iter = iter->next;
      }
    }
  }
  return (buffer - initial_buffer);
}

void funk2_set__load_from_stream(funk2_set_t* this, int fd) {
  u64 element_count;
  safe_read(fd, to_ptr(&element_count), sizeof(element_count));
  u64 index;
  for (index = 0; index < element_count; index ++) {
    funk2_set_element_t element;
    safe_read(fd, to_ptr(&element), sizeof(element));
    funk2_set__add(this, element);
  }
}

s64 funk2_set__load_from_buffer(funk2_set_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    u64 element_count;
    memcpy(&element_count, buffer_iter, sizeof(element_count)); buffer_iter += sizeof(element_count);
    u64 index;
    for (index = 0; index < element_count; index ++) {
      funk2_set_element_t element;
      memcpy(&element, buffer_iter, sizeof(element)); buffer_iter += sizeof(element);
      funk2_set__add(this, element);
    }
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_set__print(funk2_set_t* this) {
  printf("\n[set");
  u64 bin_num = 1ull << (this->bin_power);
  u64 i;
  for (i = 0; i < bin_num; i ++) {
    printf(" [");
    funk2_set_node_t* iter = this->bin[i];
    while (iter) {
      printf(" %d", (int)(iter->element));
      iter = iter->next;
    }
    printf("]");
  }
  printf("]\n");
}

void funk2_set__test() {
  funk2_set_t set;
  funk2_set__init(&set);
  {
    int i;
    for (i = 0; i < 10; i++) {
      funk2_set__print(&set);
      funk2_set__add(&set, i);
    }
  }
  {
    int i;
    for (i = 0; i < 10; i++) {
      funk2_set__print(&set);
      if ((i % 3) == 0) {
	funk2_set__remove(&set, i);
      }
    }
  }
  funk2_set__print(&set);
  funk2_set__destroy(&set);
}


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

// tricolor_set

void funk2_tricolor_set__init(funk2_tricolor_set_t* this) {
  funk2_set__init(&(this->black_set));
  funk2_set__init(&(this->grey_set));
  funk2_set__init(&(this->white_set));
}

void funk2_tricolor_set__destroy(funk2_tricolor_set_t* this) {
  funk2_set__destroy(&(this->black_set));
  funk2_set__destroy(&(this->grey_set));
  funk2_set__destroy(&(this->white_set));
}

u64 funk2_tricolor_set__black_set__element_count(funk2_tricolor_set_t* this) {return funk2_set__element_count(&(this->black_set));}
u64 funk2_tricolor_set__white_set__element_count(funk2_tricolor_set_t* this) {return funk2_set__element_count(&(this->white_set));}
u64 funk2_tricolor_set__grey_set__element_count( funk2_tricolor_set_t* this) {return funk2_set__element_count(&(this->grey_set));}

void funk2_tricolor_set__add_element(funk2_tricolor_set_t* this, funk2_set_element_t element, funk2_tricolor_t color) {
  switch(color) {
  case funk2_tricolor__black: funk2_set__add(&(this->black_set), element); break;
  case funk2_tricolor__grey:  funk2_set__add(&(this->grey_set),  element); break;
  case funk2_tricolor__white: funk2_set__add(&(this->white_set), element); break;
  }
}

void funk2_tricolor_set__remove_element(funk2_tricolor_set_t* this, funk2_set_element_t element, funk2_tricolor_t current_color) {
  switch(current_color) {
  case funk2_tricolor__black: funk2_set__remove(&(this->black_set), element); break;
  case funk2_tricolor__grey:  funk2_set__remove(&(this->grey_set),  element); break;
  case funk2_tricolor__white: funk2_set__remove(&(this->white_set), element); break;
  }
}

// not processor_thread safe.
void funk2_tricolor_set__change_element_color(funk2_tricolor_set_t* this, funk2_set_element_t element, funk2_tricolor_t from_color, funk2_tricolor_t to_color) {
  funk2_set_t* from_set = NULL;
  funk2_set_t* to_set   = NULL;
  switch(from_color) {
  case funk2_tricolor__black: from_set = &(this->black_set); break;
  case funk2_tricolor__grey:  from_set = &(this->grey_set);  break;
  case funk2_tricolor__white: from_set = &(this->white_set); break;
  }
  switch(to_color) {
  case funk2_tricolor__black: to_set = &(this->black_set); break;
  case funk2_tricolor__grey:  to_set = &(this->grey_set);  break;
  case funk2_tricolor__white: to_set = &(this->white_set); break;
  }
  funk2_set__remove_and_add_to(from_set, element, to_set);
}

void* funk2_tricolor_set__black_set__mapc(funk2_tricolor_set_t* this, void(* mapc_funk)(funk2_set_element_t element, void** user_data, boolean_t* stop, void** return_value), void** user_data) {return funk2_set__mapc(&(this->black_set), mapc_funk, user_data);}
void* funk2_tricolor_set__white_set__mapc(funk2_tricolor_set_t* this, void(* mapc_funk)(funk2_set_element_t element, void** user_data, boolean_t* stop, void** return_value), void** user_data) {return funk2_set__mapc(&(this->white_set), mapc_funk, user_data);}
void* funk2_tricolor_set__grey_set__mapc( funk2_tricolor_set_t* this, void(* mapc_funk)(funk2_set_element_t element, void** user_data, boolean_t* stop, void** return_value), void** user_data) {return funk2_set__mapc(&(this->grey_set),  mapc_funk, user_data);}

s64 funk2_tricolor_set__calculate_save_size(funk2_tricolor_set_t* this) {
  s64 save_size = 0;
  {
    save_size += funk2_set__calculate_save_size(&(this->black_set));
    save_size += funk2_set__calculate_save_size(&(this->grey_set));
    save_size += funk2_set__calculate_save_size(&(this->white_set));
  }
  return save_size;
}

void funk2_tricolor_set__save_to_stream(funk2_tricolor_set_t* this, int fd) {
  funk2_set__save_to_stream(&(this->black_set), fd);
  funk2_set__save_to_stream(&(this->grey_set),  fd);
  funk2_set__save_to_stream(&(this->white_set), fd);
}

void funk2_tricolor_set__load_from_stream(funk2_tricolor_set_t* this, int fd) {
  funk2_set__load_from_stream(&(this->black_set), fd);
  funk2_set__load_from_stream(&(this->grey_set),  fd);
  funk2_set__load_from_stream(&(this->white_set), fd);
}


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

// tricolor_set

void funk2_tricolor_set__init(funk2_tricolor_set_t* this) {
  funk2_f2ptr_set__init(&(this->grey_set));
  funk2_f2ptr_set__init(&(this->white_set));
}

void funk2_tricolor_set__destroy(funk2_tricolor_set_t* this) {
  funk2_f2ptr_set__destroy(&(this->grey_set));
  funk2_f2ptr_set__destroy(&(this->white_set));
}

u64 funk2_tricolor_set__white_set__element_count(funk2_tricolor_set_t* this) {return funk2_f2ptr_set__element_count(&(this->white_set));}
u64 funk2_tricolor_set__grey_set__element_count( funk2_tricolor_set_t* this) {return funk2_f2ptr_set__element_count(&(this->grey_set));}

void funk2_tricolor_set__add_element(funk2_tricolor_set_t* this, f2ptr element, funk2_tricolor_t color) {
  switch(color) {
  case funk2_tricolor__black:                                                    break;
  case funk2_tricolor__grey:  funk2_f2ptr_set__add(&(this->grey_set),  element); break;
  case funk2_tricolor__white: funk2_f2ptr_set__add(&(this->white_set), element); break;
  }
}

void funk2_tricolor_set__remove_element(funk2_tricolor_set_t* this, f2ptr element, funk2_tricolor_t current_color) {
  switch(current_color) {
  case funk2_tricolor__black:                                                       break;
  case funk2_tricolor__grey:  funk2_f2ptr_set__remove(&(this->grey_set),  element); break;
  case funk2_tricolor__white: funk2_f2ptr_set__remove(&(this->white_set), element); break;
  }
}

// not processor_thread safe.
void funk2_tricolor_set__change_element_color(funk2_tricolor_set_t* this, f2ptr element, funk2_tricolor_t from_color, funk2_tricolor_t to_color) {
  funk2_f2ptr_set_t* from_set = NULL;
  funk2_f2ptr_set_t* to_set   = NULL;
  switch(from_color) {
  case funk2_tricolor__black: from_set = NULL;               break;
  case funk2_tricolor__grey:  from_set = &(this->grey_set);  break;
  case funk2_tricolor__white: from_set = &(this->white_set); break;
  }
  switch(to_color) {
  case funk2_tricolor__black: to_set = NULL;               break;
  case funk2_tricolor__grey:  to_set = &(this->grey_set);  break;
  case funk2_tricolor__white: to_set = &(this->white_set); break;
  }
  if (from_set == NULL) {
    if (to_set == NULL) {
      // from black to black
    } else {
      // from black to ...
      funk2_f2ptr_set__add(to_set, element);
    }
  } else {
    if (to_set == NULL) {
      // from ... to black
      funk2_f2ptr_set__remove(from_set, element);
    } else {
      // from ... to ...
      funk2_f2ptr_set__remove_and_add_to(from_set, element, to_set);
    }
  }
}

void* funk2_tricolor_set__white_set__mapc(funk2_tricolor_set_t* this, void(* mapc_funk)(f2ptr element, void** user_data, boolean_t* stop, void** return_value), void** user_data) {return funk2_f2ptr_set__mapc(&(this->white_set), mapc_funk, user_data);}
void* funk2_tricolor_set__grey_set__mapc( funk2_tricolor_set_t* this, void(* mapc_funk)(f2ptr element, void** user_data, boolean_t* stop, void** return_value), void** user_data) {return funk2_f2ptr_set__mapc(&(this->grey_set),  mapc_funk, user_data);}

s64 funk2_tricolor_set__calculate_save_size(funk2_tricolor_set_t* this) {
  s64 save_size = 0;
  {
    //save_size += funk2_f2ptr_set__calculate_save_size(&(this->black_set));
    save_size += funk2_f2ptr_set__calculate_save_size(&(this->grey_set));
    save_size += funk2_f2ptr_set__calculate_save_size(&(this->white_set));
  }
  return save_size;
}

void funk2_tricolor_set__save_to_stream(funk2_tricolor_set_t* this, int fd) {
  funk2_f2ptr_set__save_to_stream(&(this->grey_set),  fd);
  funk2_f2ptr_set__save_to_stream(&(this->white_set), fd);
}

u64 funk2_tricolor_set__save_to_buffer(funk2_tricolor_set_t* this, u8* initial_buffer) {
  u8* buffer = initial_buffer;
  buffer += funk2_f2ptr_set__save_to_buffer(&(this->grey_set),  buffer);
  buffer += funk2_f2ptr_set__save_to_buffer(&(this->white_set), buffer);
  return (buffer - initial_buffer);
}

void funk2_tricolor_set__load_from_stream(funk2_tricolor_set_t* this, int fd) {
  funk2_f2ptr_set__load_from_stream(&(this->grey_set),  fd);
  funk2_f2ptr_set__load_from_stream(&(this->white_set), fd);
}

s64 funk2_tricolor_set__load_from_buffer(funk2_tricolor_set_t* this, u8* buffer) {
  u8* buffer_iter = buffer;
  {
    buffer_iter += funk2_f2ptr_set__load_from_buffer(&(this->grey_set),  buffer_iter);
    buffer_iter += funk2_f2ptr_set__load_from_buffer(&(this->white_set), buffer_iter);
  }
  return (s64)(buffer_iter - buffer);
}

void funk2_tricolor_set__defragment__fix_pointers(funk2_tricolor_set_t* this) {
  funk2_f2ptr_set__defragment__fix_pointers(&(this->grey_set));
  funk2_f2ptr_set__defragment__fix_pointers(&(this->white_set));
}

funk2_tricolor_t funk2_tricolor_set__element_color(funk2_tricolor_set_t* this, f2ptr element) {
  if (funk2_f2ptr_set__contains(&(this->white_set), element)) {
    return funk2_tricolor__white;
  } else if (funk2_f2ptr_set__contains(&(this->grey_set), element)) {
    return funk2_tricolor__grey;
  } else {
    return funk2_tricolor__black;
  }
}


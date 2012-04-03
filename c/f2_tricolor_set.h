// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#ifndef F2__TRICOLOR_SET__H
#define F2__TRICOLOR_SET__H

#include "f2_f2ptr_set.h"
#include "f2_defragmenter.h"

// tricolor

typedef enum funk2_tricolor_e funk2_tricolor_t;
enum funk2_tricolor_e {
  funk2_tricolor__black = 1,
  funk2_tricolor__grey,
  funk2_tricolor__white
};

// tricolor_set

typedef struct funk2_tricolor_set_s funk2_tricolor_set_t;
struct funk2_tricolor_set_s {
  funk2_f2ptr_set_t white_set;
  funk2_f2ptr_set_t grey_set;
};

void             funk2_tricolor_set__init                    (funk2_tricolor_set_t* this);
void             funk2_tricolor_set__destroy                 (funk2_tricolor_set_t* this);
u64              funk2_tricolor_set__white_set__element_count(funk2_tricolor_set_t* this);
u64              funk2_tricolor_set__grey_set__element_count (funk2_tricolor_set_t* this);
void             funk2_tricolor_set__add_element             (funk2_tricolor_set_t* this, f2ptr element, funk2_tricolor_t color);
void             funk2_tricolor_set__remove_element          (funk2_tricolor_set_t* this, f2ptr element, funk2_tricolor_t current_color);
void             funk2_tricolor_set__change_element_color    (funk2_tricolor_set_t* this, f2ptr element, funk2_tricolor_t from_color, funk2_tricolor_t to_color);
void*            funk2_tricolor_set__white_set__mapc         (funk2_tricolor_set_t* this, void(* mapc_funk)(f2ptr element, void** user_data, boolean_t* stop, void** return_value), void** user_data);
void*            funk2_tricolor_set__grey_set__mapc          (funk2_tricolor_set_t* this, void(* mapc_funk)(f2ptr element, void** user_data, boolean_t* stop, void** return_value), void** user_data);
s64              funk2_tricolor_set__calculate_save_size     (funk2_tricolor_set_t* this);
void             funk2_tricolor_set__save_to_stream          (funk2_tricolor_set_t* this, int fd);
u64              funk2_tricolor_set__save_to_buffer          (funk2_tricolor_set_t* this, u8* initial_buffer);
void             funk2_tricolor_set__load_from_stream        (funk2_tricolor_set_t* this, int fd);
s64              funk2_tricolor_set__load_from_buffer        (funk2_tricolor_set_t* this, u8* buffer);
void             funk2_tricolor_set__defragment__fix_pointers(funk2_tricolor_set_t* this);
funk2_tricolor_t funk2_tricolor_set__element_color           (funk2_tricolor_set_t* this, f2ptr element);

#endif // F2__TRICOLOR_SET__H


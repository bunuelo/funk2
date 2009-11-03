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

#ifndef F2__TRICOLOR_SET__H
#define F2__TRICOLOR_SET__H

typedef struct funk2_tricolor_set_s funk2_tricolor_set_t;

// tricolor_set

struct funk2_tricolor_set_s {
  funk2_set_t black_set;
  funk2_set_t white_set;
  funk2_set_t grey_set;
};

void  funk2_tricolor_set__init(funk2_tricolor_set_t* this);
void  funk2_tricolor_set__destroy(funk2_tricolor_set_t* this);
u64   funk2_tricolor_set__black_set__element_count(funk2_tricolor_set_t* this);
u64   funk2_tricolor_set__white_set__element_count(funk2_tricolor_set_t* this);
u64   funk2_tricolor_set__grey_set__element_count(funk2_tricolor_set_t* this);
void  funk2_tricolor_set__add_element(funk2_tricolor_set_t* this, funk2_set_element_t element, funk2_garbage_collector_tricolor_t color);
void  funk2_tricolor_set__remove_element(funk2_tricolor_set_t* this, funk2_set_element_t element, funk2_garbage_collector_tricolor_t current_color);
void  funk2_tricolor_set__change_element_color(funk2_tricolor_set_t* this, funk2_set_element_t element, funk2_garbage_collector_tricolor_t from_color, funk2_garbage_collector_tricolor_t to_color);
void* funk2_tricolor_set__black_set__mapc(funk2_set_t* this, void(* mapc_funk)(void** user_data, boolean_t* stop, void** return_value), void** user_data);
void* funk2_tricolor_set__white_set__mapc(funk2_set_t* this, void(* mapc_funk)(void** user_data, boolean_t* stop, void** return_value), void** user_data);
void* funk2_tricolor_set__grey_set__mapc( funk2_set_t* this, void(* mapc_funk)(void** user_data, boolean_t* stop, void** return_value), void** user_data);

#endif // F2__TRICOLOR_SET__H


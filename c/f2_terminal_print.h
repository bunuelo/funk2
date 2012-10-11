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

#ifndef F2__TERMINAL_PRINT__TYPES__H
#define F2__TERMINAL_PRINT__TYPES__H

typedef struct funk2_object_type__terminal_print_frame__slot_s funk2_object_type__terminal_print_frame__slot_t;
struct funk2_object_type__terminal_print_frame__slot_s {
  f2ptr new_copy__symbol;
  f2ptr new_copy__funk;
};


#endif // F2__TERMINAL_PRINT__TYPES__H

#ifndef F2__TERMINAL_PRINT__H
#define F2__TERMINAL_PRINT__H

#include "f2_primfunks.h"



// terminal_print_frame

declare_frame_object_26_slot(terminal_print_frame,
			     cmutex,
			     testing,
			     testing_max_x_constraint,
			     testing_max_height_constraint,
			     testing_x_offset,
			     stream,
			     indent_distance,
			     max_x,
			     max_height,
			     max_size,
			     use_ansi_codes,
			     use_html_codes,
			     x,
			     height,
			     size,
			     left_extent,
			     right_extent,
			     already_printed_hash,
			     use_one_line,
			     failed_max_x_constraint,
			     failed_max_height_constraint,
			     failed_max_size_constraint,
			     resize_to_fit,
			     max_nanoseconds_for_resize,
			     print_as_frame_hash,
			     escape_sequence);

f2ptr f2terminal_print_frame__primobject_type__new_aux(f2ptr cause);

boolean_t raw__terminal_print_frame__failed_test_constraint_and_should_return                                 (f2ptr cause, f2ptr this);
void      raw__terminal_print_frame__write_string__thread_unsafe                                              (f2ptr cause, f2ptr this, u64 length, funk2_character_t* string);
f2ptr      f2__terminal_print_frame__write_string__thread_unsafe                                              (f2ptr cause, f2ptr this, f2ptr string);
void      raw__terminal_print_frame__write_utf8_string__thread_unsafe                                         (f2ptr cause, f2ptr this, u8* utf8_string);
void      raw__terminal_print_frame__write_color__thread_unsafe                                               (f2ptr cause, f2ptr this, ansi_color_t color);
void      raw__terminal_print_frame__write_string__thread_unsafe                                              (f2ptr cause, f2ptr this, u64 length, funk2_character_t* string);
void      raw__terminal_print_frame__write_utf8_string__thread_unsafe                                         (f2ptr cause, f2ptr this, u8* utf8_string);
void      raw__terminal_print_frame__write_ansi__up__thread_unsafe                                            (f2ptr cause, f2ptr this);
void      raw__terminal_print_frame__write_ansi__down__thread_unsafe                                          (f2ptr cause, f2ptr this);
void      raw__terminal_print_frame__write_ansi__right__thread_unsafe                                         (f2ptr cause, f2ptr this);
void      raw__terminal_print_frame__write_ansi__left__thread_unsafe                                          (f2ptr cause, f2ptr this);
void      raw__terminal_print_frame__write_ansi__move__thread_unsafe                                          (f2ptr cause, f2ptr this, s64 x, s64 y);
void      raw__terminal_print_frame__write_ansi__hide_cursor__thread_unsafe                                   (f2ptr cause, f2ptr this);
f2ptr      f2__terminal_print_frame__write_ansi__hide_cursor__thread_unsafe                                   (f2ptr cause, f2ptr this);
void      raw__terminal_print_frame__write_ansi__show_cursor__thread_unsafe                                   (f2ptr cause, f2ptr this);
f2ptr      f2__terminal_print_frame__write_ansi__show_cursor__thread_unsafe                                   (f2ptr cause, f2ptr this);
f2ptr     raw__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe                          (f2ptr cause, f2ptr this, f2ptr expression);
f2ptr      f2__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe                          (f2ptr cause, f2ptr this, f2ptr expression);
f2ptr      f2__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression);
f2ptr     raw__terminal_print_frame__expression_x_offset__thread_unsafe                                       (f2ptr cause, f2ptr this, f2ptr expression);
f2ptr      f2__terminal_print_frame__expression_x_offset__thread_unsafe                                       (f2ptr cause, f2ptr this, f2ptr expression);
void      raw__terminal_print_frame__prepare_for_printing__thread_unsafe                                      (f2ptr cause, f2ptr this, f2ptr max_x, f2ptr additional_height);
f2ptr      f2__terminal_print_frame__prepare_for_printing__thread_unsafe                                      (f2ptr cause, f2ptr this, f2ptr max_x, f2ptr additional_height);


// exp

f2ptr raw__exp__terminal_print_with_frame__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__exp__terminal_print_with_frame__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);


//

f2ptr f2__terminal_print(f2ptr cause, f2ptr exp);


// **

void f2__terminal_print__initialize();

#endif // F2__TERMINAL_PRINT__H



// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#ifndef F2__TERMINAL_PRINT__H
#define F2__TERMINAL_PRINT__H

#include "f2_primfunks.h"



// terminal_print_frame

declare_frame_object_20_slot(terminal_print_frame,
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
			     failed_max_height_constraint);

void  raw__terminal_print_frame__write_color(                             f2ptr cause, f2ptr this, ansi_color_t color);
void  raw__terminal_print_frame__write_string(                            f2ptr cause, f2ptr this, u64 length, u8* string);
f2ptr  f2__terminal_print_frame__can_print_expression_on_one_line(        f2ptr cause, f2ptr this, f2ptr expression);
f2ptr  f2__terminal_print_frame__expression_fits_within_height_constraint(f2ptr cause, f2ptr this, f2ptr expression);
f2ptr  f2__terminal_print_frame__expression_x_offset(                     f2ptr cause, f2ptr this, f2ptr expression);

f2ptr raw__exp__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

// **

void f2__terminal_print__initialize();

#endif // F2__TERMINAL_PRINT__H



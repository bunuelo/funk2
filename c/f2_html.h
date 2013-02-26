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

#ifndef F2__HTML__H
#define F2__HTML__H

#include "f2_ansi.h"

void html__stream__protected_string(f2ptr cause, f2ptr stream, char* str);

void html__stream__font(f2ptr cause, f2ptr stream, char* face, char* size, char* color);
void html__stream__end_font(f2ptr cause, f2ptr stream);

void html__stream__font_face( f2ptr cause, f2ptr stream, char* face);
void html__stream__font_size( f2ptr cause, f2ptr stream, char* size);
void html__stream__font_color(f2ptr cause, f2ptr stream, char* color);

void html__stream__ansi_foreground(f2ptr cause, f2ptr stream, ansi_color_t color);

#endif // F2__HTML__H


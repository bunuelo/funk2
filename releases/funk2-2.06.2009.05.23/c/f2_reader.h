// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#ifndef F2__READER__H
#define F2__READER__H

#include "f2_primfunks.h"
#include "f2_signal.h"

extern f2ptr __end_parens_exception;
extern f2ptr __array_end_parens_exception;
extern f2ptr __doublelink_end_parens_exception;
extern f2ptr __end_of_file_exception;
extern f2ptr __invalid_argument_type_exception;
extern f2ptr __illegal_escape_reader_metro_exception;

extern const char __left_paren_char;
extern const char __right_paren_char;
extern const char __array_left_paren_char;
extern const char __array_right_paren_char;
extern const char __doublelink_left_paren_char;
extern const char __doublelink_right_paren_char;
extern const char __quote_char;
extern const char __comma_char;
extern const char __backquote_char;
extern const char __string_quote_char;
extern const char __string_escape_newline_char;
extern const char __string_escape_return_char;
extern const char __string_escape_tab_char;
extern const char __string_escape_backspace_char;
extern const char __funktion_char;
extern const char __escape_char;
extern const char __escape_hex_char;
extern const char __escape_hex_char_char;
extern const char __escape_larva_char;
extern const char __escape_gfunkptr_char;
extern const char __escape_char_char;
extern const char __symbol_quote_char;
extern const char __symbol_escape_char;
extern const char __symbol_key_char;

extern f2ptr raw__read(f2ptr context, f2ptr stream);
extern def_pcfunk__prototype__declare(pcfunk__read);

extern void f2__reader__initialize();

#endif // F2__READER__H

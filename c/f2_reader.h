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

typedef struct funk2_reader_s funk2_reader_t;

struct funk2_reader_s {
  f2ptr end_parens_exception;
  f2ptr unmatched_begin_paren_exception;
  f2ptr array_end_parens_exception;
  f2ptr doublelink_end_parens_exception;
  f2ptr end_of_file_exception;
  f2ptr end_of_file_exception__symbol;
  f2ptr invalid_argument_type_exception;
  f2ptr illegal_escape_reader_metro_exception;
  f2ptr gfunkptr_read__exception;
  f2ptr could_not_read_type_exception;
  f2ptr could_not_read_type_exception__symbol;
  f2ptr no_character_waiting_exception;
  f2ptr no_character_waiting_exception__symbol;
  
  f2ptr char__space;
  f2ptr char__tab;
  f2ptr char__newline;
  f2ptr char__return;
  
  f2ptr char__left_paren;
  f2ptr char__right_paren;
  f2ptr char__array_left_paren;
  f2ptr char__array_right_paren;
  f2ptr char__doublelink_right_paren;
  f2ptr char__doublelink_left_paren;
  f2ptr char__quote;
  f2ptr char__backquote;
  f2ptr char__comma;
  f2ptr char__cdr_comma;
  f2ptr char__funktion;
  f2ptr char__escape;
  f2ptr char__escape_hex;
  f2ptr char__escape_hex_char;
  f2ptr char__escape_char;
  f2ptr char__escape_larva;
  f2ptr char__escape_gfunkptr;
  f2ptr char__string_quote;
  f2ptr char__string_escape_newline;
  f2ptr char__string_escape_return;
  f2ptr char__string_escape_tab;
  f2ptr char__string_escape_backspace;
  f2ptr char__symbol_quote;
  f2ptr char__symbol_escape;
  f2ptr char__symbol_key;
};

void funk2_reader__init(funk2_reader_t* this);
void funk2_reader__destroy(funk2_reader_t* this);

f2ptr raw__read(f2ptr context, f2ptr stream);

void f2__reader__initialize();

#endif // F2__READER__H

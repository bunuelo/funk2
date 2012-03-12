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

#ifndef F2__READER__H
#define F2__READER__H

#include "f2_primfunks.h"
#include "f2_signal.h"

typedef struct funk2_reader_s funk2_reader_t;

struct funk2_reader_s {
  f2ptr end_parens_exception;
  f2ptr end_parens_exception__symbol;
  f2ptr unmatched_begin_paren_exception;
  f2ptr array_end_parens_exception;
  f2ptr array_end_parens_exception__symbol;
  f2ptr doublelink_end_parens_exception;
  f2ptr doublelink_end_parens_exception__symbol;
  f2ptr end_of_file_exception;
  f2ptr end_of_file_exception__symbol;
  f2ptr invalid_argument_type_exception;
  f2ptr illegal_escape_reader_metro_exception;
  f2ptr could_not_read_type_exception;
  f2ptr could_not_read_type_exception__symbol;
  f2ptr no_character_waiting_exception;
  f2ptr no_character_waiting_exception__symbol;
  
  f2ptr char__decimal_point;
  f2ptr char__minus_sign;
  
  f2ptr char__space;
  f2ptr char__tab;
  f2ptr char__newline;
  f2ptr char__return;
  f2ptr char__backspace;
  
  f2ptr char__0;
  f2ptr char__1;
  f2ptr char__2;
  f2ptr char__3;
  f2ptr char__4;
  f2ptr char__5;
  f2ptr char__6;
  f2ptr char__7;
  f2ptr char__8;
  f2ptr char__9;

  f2ptr char__lowercase_a;
  f2ptr char__lowercase_b;
  f2ptr char__lowercase_c;
  f2ptr char__lowercase_d;
  f2ptr char__lowercase_e;
  f2ptr char__lowercase_f;
  f2ptr char__lowercase_g;
  f2ptr char__lowercase_h;
  f2ptr char__lowercase_i;
  f2ptr char__lowercase_j;
  f2ptr char__lowercase_k;
  f2ptr char__lowercase_l;
  f2ptr char__lowercase_m;
  f2ptr char__lowercase_n;
  f2ptr char__lowercase_o;
  f2ptr char__lowercase_p;
  f2ptr char__lowercase_q;
  f2ptr char__lowercase_r;
  f2ptr char__lowercase_s;
  f2ptr char__lowercase_t;
  f2ptr char__lowercase_u;
  f2ptr char__lowercase_v;
  f2ptr char__lowercase_w;
  f2ptr char__lowercase_x;
  f2ptr char__lowercase_y;
  f2ptr char__lowercase_z;

  f2ptr char__uppercase_a;
  f2ptr char__uppercase_b;
  f2ptr char__uppercase_c;
  f2ptr char__uppercase_d;
  f2ptr char__uppercase_e;
  f2ptr char__uppercase_f;
  f2ptr char__uppercase_g;
  f2ptr char__uppercase_h;
  f2ptr char__uppercase_i;
  f2ptr char__uppercase_j;
  f2ptr char__uppercase_k;
  f2ptr char__uppercase_l;
  f2ptr char__uppercase_m;
  f2ptr char__uppercase_n;
  f2ptr char__uppercase_o;
  f2ptr char__uppercase_p;
  f2ptr char__uppercase_q;
  f2ptr char__uppercase_r;
  f2ptr char__uppercase_s;
  f2ptr char__uppercase_t;
  f2ptr char__uppercase_u;
  f2ptr char__uppercase_v;
  f2ptr char__uppercase_w;
  f2ptr char__uppercase_x;
  f2ptr char__uppercase_y;
  f2ptr char__uppercase_z;

  
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
  f2ptr char__string_quote;
  f2ptr char__string_escape_newline;
  f2ptr char__string_escape_return;
  f2ptr char__string_escape_tab;
  f2ptr char__string_escape_backspace;
  f2ptr char__symbol_quote;
  f2ptr char__symbol_escape;
  f2ptr char__symbol_key;
};

void funk2_reader__init                    (funk2_reader_t* this);
void funk2_reader__destroy                 (funk2_reader_t* this);
void funk2_reader__defragment__fix_pointers(funk2_reader_t* this);

f2ptr f2__stream__try_read(f2ptr cause, f2ptr stream);

void f2__reader__defragment__fix_pointers();
void f2__reader__initialize();

#endif // F2__READER__H

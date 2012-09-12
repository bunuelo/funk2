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

#include "funk2.h"
#include <stdio.h>

#ifdef DEBUG_READER
#  define reader_status(msg, rest...) status(msg, ## rest)
#else
#  define reader_status(msg, rest...)
#endif

boolean_t raw__exp__contains_comma(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr cdr = f2cons__cdr(this, cause);
    if (raw__eq(cause, car, __funk2.globalenv.comma__symbol) || raw__eq(cause, cdr, __funk2.globalenv.comma__symbol)) {
      return 1;
    }
    return (raw__exp__contains_comma(cause, car) || raw__exp__contains_comma(cause, cdr));
  }
  return 0;
}

f2ptr f2__exp__contains_comma(f2ptr cause, f2ptr this) {return f2bool__new(raw__exp__contains_comma(cause, this));}
def_pcfunk1(exp__contains_comma, this,
	    "",
	    return f2__exp__contains_comma(this_cause, this));

boolean_t raw__exp__contains_cdr_comma(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr cdr = f2cons__cdr(this, cause);
    if (raw__eq(cause, car, __funk2.globalenv.cdr_comma__symbol) || raw__eq(cause, cdr, __funk2.globalenv.cdr_comma__symbol)) {
      return 1;
    }
    return (raw__exp__contains_cdr_comma(cause, car) || raw__exp__contains_cdr_comma(cause, cdr));
  }
  return 0;
}

f2ptr f2__exp__contains_cdr_comma(f2ptr cause, f2ptr this) {return f2bool__new(raw__exp__contains_cdr_comma(cause, this));}
def_pcfunk1(exp__contains_cdr_comma, this,
	    "",
	    return f2__exp__contains_cdr_comma(this_cause, this));

boolean_t raw__exp__contains_cdr_comma_at_this_level(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr cdr = f2cons__cdr(this, cause);
    if (raw__cons__is_type(cause, car) && raw__eq(cause, f2cons__car(car, cause), __funk2.globalenv.cdr_comma__symbol)) {
      return 1;
    }
    return raw__exp__contains_cdr_comma_at_this_level(cause, cdr);
  }
  return 0;
}

f2ptr f2__exp__contains_cdr_comma_at_this_level(f2ptr cause, f2ptr this) {return f2bool__new(raw__exp__contains_cdr_comma_at_this_level(cause, this));}
def_pcfunk1(exp__contains_cdr_comma_at_this_level, this,
	    "",
	    return f2__exp__contains_cdr_comma_at_this_level(this_cause, this));

f2ptr f2__exp__comma_filter_backquoted(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    if(raw__cons__is_type(cause, car) && (raw__eq(cause, f2cons__car(car, cause), __funk2.globalenv.comma__symbol) || raw__eq(cause, f2cons__car(car, cause), __funk2.globalenv.cdr_comma__symbol))) {
      f2cons__car__set(this, cause, f2cons__car(f2cons__cdr(f2cons__car(this, cause), cause), cause));
    } else if (! (raw__exp__contains_comma(cause, car) || raw__exp__contains_cdr_comma(cause, car))) {
      f2cons__car__set(this, cause, raw__cons__new(cause, __funk2.globalenv.quote__symbol, raw__cons__new(cause, car, nil)));
    } else if (! raw__exp__contains_cdr_comma_at_this_level(cause, car)) {
      f2cons__car__set(this, cause, raw__cons__new(cause, __funk2.globalenv.backquote__list__symbol, f2__exp__comma_filter_backquoted(cause, car)));
    } else {
      f2cons__car__set(this, cause, raw__cons__new(cause, __funk2.globalenv.backquote__list_append__symbol, f2__exp__comma_filter_backquoted(cause, car)));
    }
    f2__exp__comma_filter_backquoted(cause, f2cons__cdr(this, cause));
  }
  return this;
}
def_pcfunk1(exp__comma_filter_backquoted, this,
	    "",
	    return f2__exp__comma_filter_backquoted(this_cause, this));

boolean_t raw__char__is_whitespace(f2ptr cause, f2ptr this) {
  //u8 ch = f2char__ch(this, cause);
  //if (ch < 28 || ch > 128) {
  //  return boolean__true;
  //}
  return (raw__eq(cause, this, __funk2.reader.char__space)          ||
	  raw__eq(cause, this, __funk2.reader.char__tab)            ||
	  raw__eq(cause, this, __funk2.reader.char__newline)        ||
	  raw__eq(cause, this, __funk2.reader.char__return));
}

f2ptr f2__stream__try_getc(f2ptr cause, f2ptr this) {
  f2ptr try_read_result = f2__stream__try_read_character(cause, this);
  if (! try_read_result) {
    return __funk2.reader.no_character_waiting_exception;
  }
  return try_read_result;
}

f2ptr f2__stream__try_read_first_non_whitespace_character(f2ptr cause, f2ptr stream) {
  f2ptr first_char;
  do {
    first_char = f2__stream__try_getc(cause, stream);
    if (raw__exception__is_type(cause, first_char)) {
      return first_char;
    }
  } while (raw__char__is_whitespace(cause, first_char));
  return first_char;
}

f2ptr f2__stream__try_skip_whitespace(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_read_first_non_whitespace_character(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  f2__stream__ungetc(cause, stream, first_char);
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__skip_whitespace(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_read_first_non_whitespace_character(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  f2__stream__ungetc(cause, stream, first_char);
  return nil;
}
def_pcfunk1(stream__skip_whitespace, stream,
	    "reads whitespace from a stream, until a non-whitespace character is encountered.",
	    return f2__stream__skip_whitespace(this_cause, stream));

f2ptr f2__stream__try_read_impossibility(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  if (raw__exception__is_type(cause, first_char) &&
      raw__eq(cause, f2exception__tag(first_char, cause), __funk2.reader.end_of_file_exception__symbol)) {
    reader_status("f2__stream__try_read_impossibility() note: end_of_file_exception.");
    return __funk2.reader.end_of_file_exception;
  }
  // check all imposibilities for first_char
  if (raw__eq(cause, first_char, __funk2.reader.char__right_paren)) {
    reader_status("f2__stream__try_read_impossibility() note: end_parens_exception.");
    return __funk2.reader.end_parens_exception;
  }
  if (raw__eq(cause, first_char, __funk2.reader.char__array_right_paren)) {
    reader_status("f2__stream__try_read_impossibility() note: array_end_parens_exception.");
    return __funk2.reader.array_end_parens_exception;
  }
  if (raw__eq(cause, first_char, __funk2.reader.char__doublelink_right_paren)) {
    reader_status("f2__stream__try_read_impossibility() note: doublelink_end_parens_exception.");
    return __funk2.reader.doublelink_end_parens_exception;
  }
  f2__stream__ungetc(cause, stream, first_char);
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_list(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read list
  if (raw__eq(cause, first_char, __funk2.reader.char__left_paren)) {
    f2ptr seq  = nil;
    f2ptr iter = nil;
    f2ptr new_cons;
    f2ptr exp;
    while (1) {
      exp = f2__stream__try_read(cause, stream);
      if (raw__exception__is_type(cause, exp) &&
	  raw__eq(cause, f2exception__tag(exp, cause), __funk2.reader.end_parens_exception__symbol)) {
	reader_status("f2__stream__try_read_list note: successfully read end of list.");
	return seq;
      }
      if (raw__exception__is_type(cause, exp) &&
	  raw__eq(cause, f2exception__tag(exp, cause), __funk2.reader.end_of_file_exception__symbol)) {
	reader_status("f2__stream__try_read_list note: unmatched begin paren exception.");
	return __funk2.reader.unmatched_begin_paren_exception;
      }
      if (raw__exception__is_type(cause, exp)) {
	// other exceptions should be propagated
	reader_status("f2__stream__try_read_list note: other exception being propogated.");
	return exp;
      }
      new_cons = raw__cons__new(cause, exp, nil);
      if (seq) {
	f2cons__cdr__set(iter, cause, new_cons);
	iter = new_cons;
      } else {
	seq  = new_cons;
	iter = new_cons;
      }
    }
    return seq;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_doublelink_list(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read doublelink list
  if (raw__eq(cause, first_char, __funk2.reader.char__doublelink_left_paren)) {
    f2ptr seq  = nil;
    f2ptr iter = nil;
    f2ptr new_doublelink;
    f2ptr exp;
    while (1) {
      exp = f2__stream__try_read(cause, stream);
      if (raw__exception__is_type(cause, exp) && raw__eq(cause, f2exception__tag(exp, cause), __funk2.reader.doublelink_end_parens_exception__symbol)) {return seq;} // successfully read end of doublelink list
      if (raw__exception__is_type(cause, exp)) {return exp;} // other exceptions should be propagated
      new_doublelink = f2doublelink__new(cause, iter, nil, exp);
      if (seq) {
	f2doublelink__next__set(iter, cause, new_doublelink);
	iter = new_doublelink;
      } else {
	seq  = new_doublelink;
	iter = new_doublelink;
      }
    }
    return seq;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_quoted(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read quoted expression
  if (raw__eq(cause, first_char, __funk2.reader.char__quote)) {
    f2ptr exp = f2__stream__try_read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return raw__cons__new(cause, __funk2.globalenv.quote__symbol, raw__cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_backquoted(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read backquoted expression
  if (raw__eq(cause, first_char, __funk2.reader.char__backquote)) {
    f2ptr exp = f2__stream__try_read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    if (raw__cons__is_type(cause, exp) && (raw__exp__contains_comma(cause, exp) || raw__exp__contains_cdr_comma(cause, exp))) {
      if (raw__exp__contains_cdr_comma_at_this_level(cause, exp)) {
	exp = f2__exp__comma_filter_backquoted(cause, exp);
	if (raw__exception__is_type(cause, exp)) {return exp;}
	return raw__cons__new(cause, __funk2.globalenv.backquote__list_append__symbol, exp);
      } else {
	exp = f2__exp__comma_filter_backquoted(cause, exp);
	if (raw__exception__is_type(cause, exp)) {return exp;}
	return raw__cons__new(cause, __funk2.globalenv.backquote__list__symbol, exp);
      }
    }
    return raw__cons__new(cause, __funk2.globalenv.quote__symbol, raw__cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_comma_exp(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read comma expression (hopefully within backquote)
  if (raw__eq(cause, first_char, __funk2.reader.char__comma)) {
    f2ptr exp = f2__stream__try_read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return raw__cons__new(cause, __funk2.globalenv.comma__symbol, raw__cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_cdr_comma_exp(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read cdr comma expression (hopefully within backquote)
  if (raw__eq(cause, first_char, __funk2.reader.char__cdr_comma)) {
    f2ptr exp = f2__stream__try_read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return raw__cons__new(cause, __funk2.globalenv.cdr_comma__symbol, raw__cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_funktion_name(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read funktion name
  if (raw__eq(cause, first_char, __funk2.reader.char__funktion)) {
    f2ptr exp = f2__stream__try_read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return raw__cons__new(cause, __funk2.globalenv.funkvar__symbol, raw__cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

boolean_t raw__char__is_decimal_digit(f2ptr cause, f2ptr this) {
  return (raw__eq(cause, this, __funk2.reader.char__0) ||
	  raw__eq(cause, this, __funk2.reader.char__1) ||
	  raw__eq(cause, this, __funk2.reader.char__2) ||
	  raw__eq(cause, this, __funk2.reader.char__3) ||
	  raw__eq(cause, this, __funk2.reader.char__4) ||
	  raw__eq(cause, this, __funk2.reader.char__5) ||
	  raw__eq(cause, this, __funk2.reader.char__6) ||
	  raw__eq(cause, this, __funk2.reader.char__7) ||
	  raw__eq(cause, this, __funk2.reader.char__8) ||
	  raw__eq(cause, this, __funk2.reader.char__9));
}

boolean_t raw__char__is_hex_digit(f2ptr cause, f2ptr this) {
  return (raw__char__is_decimal_digit(cause, this) ||
	  raw__eq(cause, this, __funk2.reader.char__lowercase_a) ||
	  raw__eq(cause, this, __funk2.reader.char__lowercase_b) ||
	  raw__eq(cause, this, __funk2.reader.char__lowercase_c) ||
	  raw__eq(cause, this, __funk2.reader.char__lowercase_d) ||
	  raw__eq(cause, this, __funk2.reader.char__lowercase_e) ||
	  raw__eq(cause, this, __funk2.reader.char__lowercase_f) ||
	  raw__eq(cause, this, __funk2.reader.char__uppercase_a) ||
	  raw__eq(cause, this, __funk2.reader.char__uppercase_b) ||
	  raw__eq(cause, this, __funk2.reader.char__uppercase_c) ||
	  raw__eq(cause, this, __funk2.reader.char__uppercase_d) ||
	  raw__eq(cause, this, __funk2.reader.char__uppercase_e) ||
	  raw__eq(cause, this, __funk2.reader.char__uppercase_f));
}

f2ptr f2__stream__try_read_hex_digits(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  if (! raw__char__is_type(cause, read_ch)) {
    return f2larva__new(cause, 19, nil);
  }
  if (! raw__char__is_hex_digit(cause, read_ch)) {
    f2__stream__ungetc(cause, stream, read_ch);
    return nil;
  }
  f2ptr rest_list = f2__stream__try_read_hex_digits(cause, stream);
  if (rest_list && (! raw__cons__is_type(cause, rest_list))) {
    f2__stream__ungetc(cause, stream, read_ch);
    return rest_list;
  }
  return raw__cons__new(cause, read_ch, rest_list);
}

s64 raw__char__decimal_digit_value(f2ptr cause, f2ptr this) {
  if (raw__eq(cause, this, __funk2.reader.char__0)) {return 0;}
  if (raw__eq(cause, this, __funk2.reader.char__1)) {return 1;}
  if (raw__eq(cause, this, __funk2.reader.char__2)) {return 2;}
  if (raw__eq(cause, this, __funk2.reader.char__3)) {return 3;}
  if (raw__eq(cause, this, __funk2.reader.char__4)) {return 4;}
  if (raw__eq(cause, this, __funk2.reader.char__5)) {return 5;}
  if (raw__eq(cause, this, __funk2.reader.char__6)) {return 6;}
  if (raw__eq(cause, this, __funk2.reader.char__7)) {return 7;}
  if (raw__eq(cause, this, __funk2.reader.char__8)) {return 8;}
  if (raw__eq(cause, this, __funk2.reader.char__9)) {return 9;}
  error(nil, "raw__char__decimal_digit_value error: tried to convert non-decimal digit to value.");
}

f2ptr f2__char__decimal_digit_value(f2ptr cause, f2ptr this) {
  assert_argument_type(char, this);
  return f2integer__new(cause, raw__char__decimal_digit_value(cause, this));
}

s64 raw__char__hex_digit_value(f2ptr cause, f2ptr this) {
  if (raw__char__is_decimal_digit(cause, this))               {return raw__char__decimal_digit_value(cause, this);}
  if (raw__eq(cause, this, __funk2.reader.char__lowercase_a)) {return 10;}
  if (raw__eq(cause, this, __funk2.reader.char__uppercase_a)) {return 10;}
  if (raw__eq(cause, this, __funk2.reader.char__lowercase_b)) {return 11;}
  if (raw__eq(cause, this, __funk2.reader.char__uppercase_b)) {return 11;}
  if (raw__eq(cause, this, __funk2.reader.char__lowercase_c)) {return 12;}
  if (raw__eq(cause, this, __funk2.reader.char__uppercase_c)) {return 12;}
  if (raw__eq(cause, this, __funk2.reader.char__lowercase_d)) {return 13;}
  if (raw__eq(cause, this, __funk2.reader.char__uppercase_d)) {return 13;}
  if (raw__eq(cause, this, __funk2.reader.char__lowercase_e)) {return 14;}
  if (raw__eq(cause, this, __funk2.reader.char__uppercase_e)) {return 14;}
  if (raw__eq(cause, this, __funk2.reader.char__lowercase_f)) {return 15;}
  if (raw__eq(cause, this, __funk2.reader.char__uppercase_f)) {return 15;}
  error(nil, "raw__char__hex_digit_value error: tried to convert non-hexadecimal digit to value.");
}

f2ptr f2__char__hex_digit_value(f2ptr cause, f2ptr this) {
  assert_argument_type(char, this);
  return f2integer__new(cause, raw__char__hex_digit_value(cause, this));
}

f2ptr f2__stream__try_read_unescaped_hex_pointer(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  // read hex pointer
  if (raw__eq(cause, read_ch, __funk2.reader.char__escape_hex)) {
    f2ptr digits = f2__stream__try_read_hex_digits(cause, stream);
    if (digits && (! raw__cons__is_type(cause, digits))) {
      f2__stream__ungetc(cause, stream, read_ch);
      return digits;
    }
    int i = raw__simple_length(cause, digits);
    int j = 0;
    ptr p = 0;
    u64 t;
    f2ptr iter = digits;
    while (iter) {
      f2ptr read_ch = f2cons__car(iter, cause);
      if ((! raw__char__is_type(cause, read_ch)) || (! raw__char__is_hex_digit(cause, read_ch))) {
	return f2larva__new(cause, 19, nil);
      }
      t = raw__char__hex_digit_value(cause, read_ch);
      i --;
      p += (t << (i << 2));
      j ++;
      
      iter = f2cons__cdr(iter, cause);
    }
    
    f2ptr exp = f2pointer__new(cause, p);
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_unescaped_hex_char(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  
  // read char hex
  if (f2__eq(cause, read_ch, __funk2.reader.char__escape_hex_char)) {
    f2ptr digits = f2__stream__try_read_hex_digits(cause, stream);
    if (digits && (! raw__cons__is_type(cause, digits))) {
      f2__stream__ungetc(cause, stream, read_ch);
      return digits;
    }
    int i = raw__simple_length(cause, digits);
    int j = 0;
    ptr p = 0;
    u64 t;
    f2ptr iter = digits;
    while (iter) {
      f2ptr read_ch = f2cons__car(iter, cause);
      if ((! raw__char__is_type(cause, read_ch)) || (! raw__char__is_hex_digit(cause, read_ch))) {
	return f2larva__new(cause, 19, nil);
      }
      t = raw__char__hex_digit_value(cause, read_ch);
      i --;
      p += (t << (i << 2));
      j ++;
      
      iter = f2cons__cdr(iter, cause);
    }
    
    f2ptr exp = f2char__new(cause, (char)p);
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_decimal_digits(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  if (! raw__char__is_type(cause, read_ch)) {
    return f2larva__new(cause, 19, nil);
  }
  if (! raw__char__is_decimal_digit(cause, read_ch)) {
    f2__stream__ungetc(cause, stream, read_ch);
    return nil;
  }
  f2ptr rest_list = f2__stream__try_read_decimal_digits(cause, stream);
  if (rest_list && (! raw__cons__is_type(cause, rest_list))) {
    f2__stream__ungetc(cause, stream, read_ch);
    return rest_list;
  }
  return raw__cons__new(cause, read_ch, rest_list);
}

f2ptr f2__stream__try_read_unescaped_larva(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  
  // read larva
  if (raw__eq(cause, read_ch, __funk2.reader.char__escape_larva)) {
    f2ptr digits = f2__stream__try_read_decimal_digits(cause, stream);
    if (digits && (! raw__cons__is_type(cause, digits))) {
      f2__stream__ungetc(cause, stream, read_ch);
      return digits;
    }
    int i = raw__simple_length(cause, digits);
    int j = 0;
    u32 type = 0;
    u64 t;
    f2ptr iter = digits;
    while (iter) {
      f2ptr read_ch = f2cons__car(iter, cause);
      if ((! raw__char__is_type(cause, read_ch)) || (! raw__char__is_decimal_digit(cause, read_ch))) {
	return f2larva__new(cause, 19, nil);
      }
      t = raw__char__decimal_digit_value(cause, read_ch);
      i --;
      u32 i_power = 1;
      {int k; for (k = i; k > 0; k --) {i_power *= 10;}}
      type += (t * i_power);
      j ++;
      
      iter = f2cons__cdr(iter, cause);
    }
    
    f2ptr exp = f2larva__new(cause, type, nil);
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_escaped(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read escaped expression
  if (raw__eq(cause, first_char, __funk2.reader.char__escape)) {
    
    {
      f2ptr try_read_result = f2__stream__try_read_unescaped_hex_pointer(cause, stream);
      if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {
	return try_read_result;
      }
    }
    
    {
      f2ptr try_read_result = f2__stream__try_read_unescaped_hex_char(cause, stream);
      if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {
	return try_read_result;
      }
    }
    
    {
      f2ptr try_read_result = f2__stream__try_read_unescaped_larva(cause, stream);
      if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {
	return try_read_result;
      }
    }
    
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__read_array_sequence_of_elements(f2ptr cause, f2ptr stream) {
  f2ptr subexp = f2__stream__try_read(cause, stream);
  if (raw__exception__is_type(cause, subexp) && raw__eq(cause, f2exception__tag(subexp, cause), __funk2.reader.array_end_parens_exception__symbol)) {
    return nil;
  }
  if (raw__exception__is_type(cause, subexp)) {
    return subexp;
  }
  f2ptr rest_sequence = f2__stream__read_array_sequence_of_elements(cause, stream);
  if (raw__exception__is_type(cause, rest_sequence)) {
    return rest_sequence;
  }
  return raw__cons__new(cause, subexp, rest_sequence);
}

f2ptr f2__stream__try_read_array(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read array
  if (raw__eq(cause, first_char, __funk2.reader.char__array_left_paren)) {
    f2ptr elements      = f2__stream__read_array_sequence_of_elements(cause, stream);
    if (elements && (! raw__cons__is_type(cause, elements))) {
      return elements;
    }
    u64   array__length = raw__simple_length(cause, elements);
    f2ptr array         = raw__array__new(cause, array__length);
    f2ptr iter          = elements;
    u64   index         = 0;
    while (iter) {
      f2ptr element = f2cons__car(iter, cause);
      raw__array__elt__set(cause, array, index, element);
      index ++;
      iter = f2cons__cdr(iter, cause);
    }
    return array;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_string(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read string
  if (raw__eq(cause, first_char, __funk2.reader.char__string_quote)) {
    int                buf_size = 64;
    funk2_character_t* str      = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * buf_size));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__try_getc(cause, stream);
      if (raw__exception__is_type(cause, read_ch)) {
	return read_ch;
      }
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {
	f2__free(to_ptr(str));
	status("raw_read() note: eof_except.");
	return __funk2.reader.end_of_file_exception;
      }
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19, nil);
      }
      funk2_character_t ch = f2char__ch(read_ch, cause);
      if (raw__eq(cause, read_ch, __funk2.reader.char__string_quote)) {break;}
      if (raw__eq(cause, read_ch, __funk2.reader.char__escape_char)) {
	read_ch = f2__stream__try_getc(cause, stream);
	if (raw__exception__is_type(cause, read_ch)) {
	  return read_ch;
	}
	if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {
	  f2__free(to_ptr(str));
	  status("raw_read() note: eof_except.");
	  return __funk2.reader.end_of_file_exception;
	}
	if (! raw__char__is_type(cause, read_ch)) {
	  return f2larva__new(cause, 19, nil);
	}
	if      (raw__eq(cause, read_ch, __funk2.reader.char__string_escape_newline))        {read_ch = __funk2.reader.char__newline;}
	else if (raw__eq(cause, read_ch, __funk2.reader.char__string_escape_return))         {read_ch = __funk2.reader.char__return;}
	else if (raw__eq(cause, read_ch, __funk2.reader.char__string_escape_tab))            {read_ch = __funk2.reader.char__tab;}
	else if (raw__eq(cause, read_ch, __funk2.reader.char__string_escape_backspace))      {read_ch = __funk2.reader.char__backspace;}
	ch = f2char__ch(read_ch, cause);
	// otherwise ignore next character
      }
      str[i] = ch;
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (funk2_character_t*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size * sizeof(funk2_character_t), buf_size * sizeof(funk2_character_t)));
      }
    } while(1);
    f2ptr exp = f2string__new(cause, i, str);
    f2__free(to_ptr(str));
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_symbol_quote(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, first_char)) {
    return first_char;
  }
  // read symbol quote
  if (raw__eq(cause, first_char, __funk2.reader.char__symbol_quote)) {
    int                buf_size = 64;
    funk2_character_t* str      = (funk2_character_t*)from_ptr(f2__malloc(buf_size * sizeof(funk2_character_t)));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__try_getc(cause, stream);
      if (raw__exception__is_type(cause, read_ch)) {
	return read_ch;
      }
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19, nil);
      }
      funk2_character_t ch = f2char__ch(read_ch, cause);
      if (raw__eq(cause, read_ch, __funk2.reader.char__symbol_quote)) {break;}
      if (raw__eq(cause, read_ch, __funk2.reader.char__symbol_escape)) {
	// ignore next character
	read_ch = f2__stream__try_getc(cause, stream);
	if (raw__exception__is_type(cause, read_ch)) {
	  return read_ch;
	}
	if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
	if (! raw__char__is_type(cause, read_ch)) {
	  return f2larva__new(cause, 19, nil);
	}
	ch = f2char__ch(read_ch, cause);
      }
      str[i] = ch;
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (funk2_character_t*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size * sizeof(funk2_character_t), buf_size * sizeof(funk2_character_t)));
      }
    } while(1);
    f2ptr exp = f2symbol__new(cause, i, str);
    f2__free(to_ptr(str));
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

boolean_t raw__char__is_symbolizable(f2ptr cause, f2ptr this) {
  return (raw__char__is_type(cause, this)                                      &&
	  (! raw__char__is_whitespace(cause, this))                            &&
	  (! raw__eq(cause, this, __funk2.reader.char__left_paren))            &&
	  (! raw__eq(cause, this, __funk2.reader.char__right_paren))           &&
	  (! raw__eq(cause, this, __funk2.reader.char__array_left_paren))      &&
	  (! raw__eq(cause, this, __funk2.reader.char__array_right_paren))     &&
	  (! raw__eq(cause, this, __funk2.reader.char__doublelink_left_paren)) &&
	  (! raw__eq(cause, this, __funk2.reader.char__doublelink_right_paren)));
}

f2ptr f2__stream__try_read_number_list_without_sign_or_decimal(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {
    status("raw_read() note: eof_except.");
    return __funk2.reader.end_of_file_exception;
  }
  if (raw__char__is_decimal_digit(cause, read_ch)) {
    f2ptr number_list = f2__stream__try_read_number_list_without_sign_or_decimal(cause, stream);
    if ((! number_list) || raw__cons__is_type(cause, number_list)) {
      return raw__cons__new(cause, read_ch, number_list);
    } else {
      f2__stream__ungetc(cause, stream, read_ch);
    }
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
    if (! raw__char__is_symbolizable(cause, read_ch)) {
      return nil;
    }
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_number_list_without_sign(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__eq(cause, read_ch, __funk2.reader.char__decimal_point)) {
    f2ptr number_list = f2__stream__try_read_number_list_without_sign_or_decimal(cause, stream);
    if ((! number_list) || raw__cons__is_type(cause, number_list)) {
      return raw__cons__new(cause, read_ch, number_list);
    } else {
      f2__stream__ungetc(cause, stream, read_ch);
    }
  } else if (raw__char__is_decimal_digit(cause, read_ch)) {
    f2ptr number_list = f2__stream__try_read_number_list_without_sign(cause, stream);
    if ((! number_list) || raw__cons__is_type(cause, number_list)) {
      return raw__cons__new(cause, read_ch, number_list);
    } else {
      f2__stream__ungetc(cause, stream, read_ch);
    }
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
    if (! raw__char__is_symbolizable(cause, read_ch)) {
      return nil;
    }
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_number_list(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {
    status("raw_read() note: eof_except.");
    return __funk2.reader.end_of_file_exception;
  }
  if (raw__eq(cause, read_ch, __funk2.reader.char__minus_sign)) {
    f2ptr number_list = f2__stream__try_read_number_list_without_sign(cause, stream);
    // cannot except nil here, because '-' should be a symbol if not followed by a number.
    if (raw__cons__is_type(cause, number_list)) {
      return raw__cons__new(cause, read_ch, number_list);
    } else {
      f2__stream__ungetc(cause, stream, read_ch);
    }
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
    f2ptr number_list = f2__stream__try_read_number_list_without_sign(cause, stream);
    if ((! number_list) || raw__cons__is_type(cause, number_list)) {
      return number_list;
    }
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_number(f2ptr cause, f2ptr stream) {
  f2ptr number_list = f2__stream__try_read_number_list(cause, stream);
  if ((! number_list) || raw__cons__is_type(cause, number_list)) {
    boolean_t is_negative = boolean__false;
    f2ptr iter = number_list;
    if (iter) {
      f2ptr read_ch = f2cons__car(iter, cause);
      if (raw__eq(cause, read_ch, __funk2.reader.char__minus_sign)) {
	is_negative = boolean__true;
	iter = f2cons__cdr(iter, cause);
      }
    }
    f2ptr whole_decimal_start  = iter;
    s64   whole_decimal_length = 0;
    while (iter) {
      f2ptr read_ch = f2cons__car(iter, cause);
      if (raw__eq(cause, read_ch, __funk2.reader.char__decimal_point)) {
	iter = f2cons__cdr(iter, cause);
	break;
      } else {
	whole_decimal_length ++;
      }
      iter = f2cons__cdr(iter, cause);
    }
    f2ptr part_decimal_start  = iter;
    s64   part_decimal_length = 0;
    while (iter) {
      part_decimal_length ++;
      iter = f2cons__cdr(iter, cause);
    }
    s64 whole_decimal_value = 0;
    {
      s64 whole_decimal_digit = whole_decimal_length - 1;
      iter = whole_decimal_start;
      while (whole_decimal_digit >= 0) {
	s64 power_i = 1;
	{s64 k; for (k = 0; k < whole_decimal_digit; k ++) {power_i *= 10;}}
	f2ptr read_ch = f2cons__car(iter, cause);
	whole_decimal_value += (((s64)raw__char__decimal_digit_value(cause, read_ch)) * power_i);
	iter = f2cons__cdr(iter, cause);
	whole_decimal_digit --;
      }
    }
    f2ptr whole_decimal_value__largeinteger = raw__largeinteger__new_from_s64(cause, 0);
    {
      f2ptr  ten__largeinteger        = raw__largeinteger__new_from_s64(cause, 10);
      f2ptr* ten_power__largeintegers = (f2ptr*)alloca(sizeof(f2ptr) * whole_decimal_length);
      ten_power__largeintegers[0]     = raw__largeinteger__new_from_s64(cause, 1);
      {
	s64 index;
	for (index = 1; index < whole_decimal_length; index ++) {
	  ten_power__largeintegers[index] = f2__largeinteger__multiplied_by(cause, ten_power__largeintegers[index - 1], ten__largeinteger);
	}
      }
      s64 whole_decimal_digit = whole_decimal_length - 1;
      iter = whole_decimal_start;
      while (whole_decimal_digit >= 0) {
	f2ptr read_ch = f2cons__car(iter, cause);
	f2ptr char_value__largeinteger = raw__largeinteger__new_from_s64(cause, (s64)raw__char__decimal_digit_value(cause, read_ch));
	whole_decimal_value__largeinteger = raw__largeinteger__add(cause, whole_decimal_value__largeinteger, (f2__largeinteger__multiplied_by(cause, char_value__largeinteger, ten_power__largeintegers[whole_decimal_digit])));
	iter = f2cons__cdr(iter, cause);
	whole_decimal_digit --;
      }
    }
    s64 part_decimal_denomenator = 1;
    {s64 k; for (k = 0; k < part_decimal_length; k ++) {part_decimal_denomenator *= 10;}}
    s64 part_decimal_value = 0;
    {
      s64 part_decimal_digit = part_decimal_length - 1;
      iter = part_decimal_start;
      while (part_decimal_digit >= 0) {
	s64 power_i = 1;
	{s64 k; for (k = 0; k < part_decimal_digit; k ++) {power_i *= 10;}}
	f2ptr read_ch = f2cons__car(iter, cause);
	part_decimal_value += (((s64)raw__char__decimal_digit_value(cause, read_ch)) * power_i);
	iter = f2cons__cdr(iter, cause);
	part_decimal_digit --;
      }
    }
    if (part_decimal_start) {
      double whole_decimal_value__d = raw__largeinteger__as__double(cause, whole_decimal_value__largeinteger);
      double d = ((is_negative ? -1.0 : 1.0) * (((double)whole_decimal_value__d) + (((double)part_decimal_value) / ((double)part_decimal_denomenator))));
      return f2double__new(cause, d);
    } else {
      f2ptr sup_integer_value__largeinteger =                                    raw__largeinteger__bitshift_left(cause, raw__largeinteger__new_from_s64(cause, 1), 63);
      f2ptr min_integer_value__largeinteger = raw__largeinteger__negative(cause, raw__largeinteger__bitshift_left(cause, raw__largeinteger__new_from_s64(cause, 1), 63));
      if ((  raw__largeinteger__less_than(cause, whole_decimal_value__largeinteger, sup_integer_value__largeinteger)) &&
	  (! raw__largeinteger__less_than(cause, whole_decimal_value__largeinteger, min_integer_value__largeinteger))) {
	s64 i = ((is_negative ? ((s64)-1) : ((s64)1)) * ((s64)whole_decimal_value));
	return f2integer__new(cause, i);
      } else {
	if (is_negative) {
	  return raw__largeinteger__negative(cause, whole_decimal_value__largeinteger);
	} else {
	  return whole_decimal_value__largeinteger;
	}
      }
    }
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_symbol_list(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__try_getc(cause, stream);
  if (raw__exception__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (! raw__char__is_type(cause, read_ch)) {
    return read_ch;
  }
  if (raw__char__is_symbolizable(cause, read_ch)) {
    f2ptr symbol_list = f2__stream__try_read_symbol_list(cause, stream);
    if ((! symbol_list) || raw__cons__is_type(cause, symbol_list)) {
      return raw__cons__new(cause, read_ch, symbol_list);
    } else {
      return symbol_list;
    }
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
    return nil;
  }
}

f2ptr f2__stream__try_read_symbol(f2ptr cause, f2ptr stream) {
  f2ptr symbol_list = f2__stream__try_read_symbol_list(cause, stream);
  if (raw__exception__is_type(cause, symbol_list)) {
    return symbol_list;
  }
  if (raw__cons__is_type(cause, symbol_list)) {
    u64 length = raw__simple_length(cause, symbol_list);
    funk2_character_t* str = (funk2_character_t*)from_ptr(f2__malloc((length + 1) * sizeof(funk2_character_t)));
    u64 i = 0;
    f2ptr iter = symbol_list;
    while (iter) {
      f2ptr read_ch = f2cons__car(iter, cause);
      str[i] = f2char__ch(read_ch, cause);
      i ++;
      iter = f2cons__cdr(iter, cause);
    }
    str[i] = 0;
    f2ptr symbol = nil;
    if (length != 3 || str[0] != (funk2_character_t)'n' || str[1] != (funk2_character_t)'i' || str[2] != (funk2_character_t)'l') {
      symbol = f2symbol__new(cause, length, str);
    }
    f2__free(to_ptr(str));
    return symbol;
  }
  return __funk2.reader.could_not_read_type_exception;
}


f2ptr f2__stream__try_read(f2ptr cause, f2ptr stream) {
  assert_argument_type(stream, stream);
  
  f2ptr begin_rewind_length = f2stream__rewind_length(stream, cause);
  if (! raw__integer__is_type(cause, begin_rewind_length)) {
    return f2larva__new(cause, 337, nil);
  }
  s64 begin_rewind_length__i = f2integer__i(begin_rewind_length, cause);
  
  {
    f2ptr try_read_result = f2__stream__try_skip_whitespace(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_impossibility(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_list(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_doublelink_list(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_quoted(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_backquoted(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_comma_exp(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_cdr_comma_exp(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_funktion_name(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_escaped(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_array(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_string(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_symbol_quote(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_number(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  {
    f2ptr try_read_result = f2__stream__try_read_symbol(cause, stream);
    if (raw__exception__is_type(cause, try_read_result)) {
      if (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol)) {
	if (raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.no_character_waiting_exception__symbol)) {
	  raw__stream__rewind_to_length(cause, stream, begin_rewind_length__i);
	}
	return try_read_result;
      }
    } else {
      return try_read_result;
    }
  }
  
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read__thread_safe(f2ptr cause, f2ptr stream) {
  if (raw__cmutex__trylock(cause, f2__stream__cmutex(cause, stream))) {
    return __funk2.reader.no_character_waiting_exception__symbol; // this should actually be an "already being read by another process" exception.
  }
  f2ptr result = f2__stream__try_read(cause, stream);
  raw__cmutex__unlock(cause, f2__stream__cmutex(cause, stream));
  return result;
}
def_pcfunk1(stream__try_read, stream,
	    "simple hardcoded reader funktion for reading from a stream (such as stdin).  returns exception if no character is waiting (non-blocking).",
	    return f2__stream__try_read__thread_safe(this_cause, stream));


void funk2_reader__init(funk2_reader_t* this) {
  f2ptr cause = f2_reader_c__cause__new(initial_cause());
  
  {
    char* str = "reader:end_parens-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->end_parens_exception__symbol = symbol;
    this->end_parens_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->end_parens_exception);
  }
  {char* str = "reader:unmatched_begin_paren-exception";       f2ptr symbol = new__symbol(cause, str); this->unmatched_begin_paren_exception       = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->unmatched_begin_paren_exception);}
  {
    char* str = "reader:array_end_parens-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->array_end_parens_exception__symbol = symbol;
    this->array_end_parens_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->array_end_parens_exception);
  }
  {
    char* str = "reader:doublelink_end_parens-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->doublelink_end_parens_exception__symbol = symbol;
    this->doublelink_end_parens_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->doublelink_end_parens_exception);
  }
  {
    char* str = "reader:end_of_file-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->end_of_file_exception__symbol = symbol;
    this->end_of_file_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->end_of_file_exception);
  }
  {char* str = "reader:invalid_argument_type-exception";       f2ptr symbol = new__symbol(cause, str); this->invalid_argument_type_exception       = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->invalid_argument_type_exception);}
  {char* str = "reader:illegal_escape_reader_metro-exception"; f2ptr symbol = new__symbol(cause, str); this->illegal_escape_reader_metro_exception = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->illegal_escape_reader_metro_exception);}
  {
    char* str = "reader:could_not_read_type-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->could_not_read_type_exception__symbol = symbol;
    this->could_not_read_type_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->could_not_read_type_exception);
  }
  {
    char* str = "reader:no_character_waiting-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->no_character_waiting_exception__symbol = symbol;
    this->no_character_waiting_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->no_character_waiting_exception);
  }
  
  {this->char__decimal_point           = f2char__new(cause, '.');  char* str = "char:decimal_point";           environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__decimal_point);}
  {this->char__minus_sign              = f2char__new(cause, '-');  char* str = "char:minus_sign";              environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__minus_sign);}
  
  {this->char__space                   = f2char__new(cause, ' ');  char* str = "char:space";                   environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__space);}
  {this->char__tab                     = f2char__new(cause, '\t'); char* str = "char:tab";                     environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__tab);}
  {this->char__newline                 = f2char__new(cause, '\n'); char* str = "char:newline";                 environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__newline);}
  {this->char__return                  = f2char__new(cause, '\r'); char* str = "char:return";                  environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__return);}
  {this->char__backspace               = f2char__new(cause, '\b'); char* str = "char:backspace";               environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__backspace);}
  
  {this->char__0                       = f2char__new(cause, '0'); char* str = "char:0"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__0);}
  {this->char__1                       = f2char__new(cause, '1'); char* str = "char:1"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__1);}
  {this->char__2                       = f2char__new(cause, '2'); char* str = "char:2"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__2);}
  {this->char__3                       = f2char__new(cause, '3'); char* str = "char:3"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__3);}
  {this->char__4                       = f2char__new(cause, '4'); char* str = "char:4"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__4);}
  {this->char__5                       = f2char__new(cause, '5'); char* str = "char:5"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__5);}
  {this->char__6                       = f2char__new(cause, '6'); char* str = "char:6"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__6);}
  {this->char__7                       = f2char__new(cause, '7'); char* str = "char:7"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__7);}
  {this->char__8                       = f2char__new(cause, '8'); char* str = "char:8"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__8);}
  {this->char__9                       = f2char__new(cause, '9'); char* str = "char:9"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__9);}
  
  {this->char__lowercase_a             = f2char__new(cause, 'a'); char* str = "char:lowercase_a"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_a);}
  {this->char__lowercase_b             = f2char__new(cause, 'b'); char* str = "char:lowercase_b"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_b);}
  {this->char__lowercase_c             = f2char__new(cause, 'c'); char* str = "char:lowercase_c"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_c);}
  {this->char__lowercase_d             = f2char__new(cause, 'd'); char* str = "char:lowercase_d"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_d);}
  {this->char__lowercase_e             = f2char__new(cause, 'e'); char* str = "char:lowercase_e"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_e);}
  {this->char__lowercase_f             = f2char__new(cause, 'f'); char* str = "char:lowercase_f"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_f);}
  {this->char__lowercase_g             = f2char__new(cause, 'g'); char* str = "char:lowercase_g"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_g);}
  {this->char__lowercase_h             = f2char__new(cause, 'h'); char* str = "char:lowercase_h"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_h);}
  {this->char__lowercase_i             = f2char__new(cause, 'i'); char* str = "char:lowercase_i"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_i);}
  {this->char__lowercase_j             = f2char__new(cause, 'j'); char* str = "char:lowercase_j"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_j);}
  {this->char__lowercase_k             = f2char__new(cause, 'k'); char* str = "char:lowercase_k"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_k);}
  {this->char__lowercase_l             = f2char__new(cause, 'l'); char* str = "char:lowercase_l"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_l);}
  {this->char__lowercase_m             = f2char__new(cause, 'm'); char* str = "char:lowercase_m"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_m);}
  {this->char__lowercase_n             = f2char__new(cause, 'n'); char* str = "char:lowercase_n"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_n);}
  {this->char__lowercase_o             = f2char__new(cause, 'o'); char* str = "char:lowercase_o"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_o);}
  {this->char__lowercase_p             = f2char__new(cause, 'p'); char* str = "char:lowercase_p"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_p);}
  {this->char__lowercase_q             = f2char__new(cause, 'q'); char* str = "char:lowercase_q"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_q);}
  {this->char__lowercase_r             = f2char__new(cause, 'r'); char* str = "char:lowercase_r"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_r);}
  {this->char__lowercase_s             = f2char__new(cause, 's'); char* str = "char:lowercase_s"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_s);}
  {this->char__lowercase_t             = f2char__new(cause, 't'); char* str = "char:lowercase_t"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_t);}
  {this->char__lowercase_u             = f2char__new(cause, 'u'); char* str = "char:lowercase_u"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_u);}
  {this->char__lowercase_v             = f2char__new(cause, 'v'); char* str = "char:lowercase_v"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_v);}
  {this->char__lowercase_w             = f2char__new(cause, 'w'); char* str = "char:lowercase_w"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_w);}
  {this->char__lowercase_x             = f2char__new(cause, 'x'); char* str = "char:lowercase_x"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_x);}
  {this->char__lowercase_y             = f2char__new(cause, 'y'); char* str = "char:lowercase_y"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_y);}
  {this->char__lowercase_z             = f2char__new(cause, 'z'); char* str = "char:lowercase_z"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__lowercase_z);}
  
  {this->char__uppercase_a             = f2char__new(cause, 'A'); char* str = "char:uppercase_a"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_a);}
  {this->char__uppercase_b             = f2char__new(cause, 'B'); char* str = "char:uppercase_b"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_b);}
  {this->char__uppercase_c             = f2char__new(cause, 'C'); char* str = "char:uppercase_c"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_c);}
  {this->char__uppercase_d             = f2char__new(cause, 'D'); char* str = "char:uppercase_d"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_d);}
  {this->char__uppercase_e             = f2char__new(cause, 'E'); char* str = "char:uppercase_e"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_e);}
  {this->char__uppercase_f             = f2char__new(cause, 'F'); char* str = "char:uppercase_f"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_f);}
  {this->char__uppercase_g             = f2char__new(cause, 'G'); char* str = "char:uppercase_g"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_g);}
  {this->char__uppercase_h             = f2char__new(cause, 'H'); char* str = "char:uppercase_h"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_h);}
  {this->char__uppercase_i             = f2char__new(cause, 'I'); char* str = "char:uppercase_i"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_i);}
  {this->char__uppercase_j             = f2char__new(cause, 'J'); char* str = "char:uppercase_j"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_j);}
  {this->char__uppercase_k             = f2char__new(cause, 'K'); char* str = "char:uppercase_k"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_k);}
  {this->char__uppercase_l             = f2char__new(cause, 'L'); char* str = "char:uppercase_l"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_l);}
  {this->char__uppercase_m             = f2char__new(cause, 'M'); char* str = "char:uppercase_m"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_m);}
  {this->char__uppercase_n             = f2char__new(cause, 'N'); char* str = "char:uppercase_n"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_n);}
  {this->char__uppercase_o             = f2char__new(cause, 'O'); char* str = "char:uppercase_o"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_o);}
  {this->char__uppercase_p             = f2char__new(cause, 'P'); char* str = "char:uppercase_p"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_p);}
  {this->char__uppercase_q             = f2char__new(cause, 'Q'); char* str = "char:uppercase_q"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_q);}
  {this->char__uppercase_r             = f2char__new(cause, 'R'); char* str = "char:uppercase_r"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_r);}
  {this->char__uppercase_s             = f2char__new(cause, 'S'); char* str = "char:uppercase_s"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_s);}
  {this->char__uppercase_t             = f2char__new(cause, 'T'); char* str = "char:uppercase_t"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_t);}
  {this->char__uppercase_u             = f2char__new(cause, 'U'); char* str = "char:uppercase_u"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_u);}
  {this->char__uppercase_v             = f2char__new(cause, 'V'); char* str = "char:uppercase_v"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_v);}
  {this->char__uppercase_w             = f2char__new(cause, 'W'); char* str = "char:uppercase_w"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_w);}
  {this->char__uppercase_x             = f2char__new(cause, 'X'); char* str = "char:uppercase_x"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_x);}
  {this->char__uppercase_y             = f2char__new(cause, 'Y'); char* str = "char:uppercase_y"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_y);}
  {this->char__uppercase_z             = f2char__new(cause, 'Z'); char* str = "char:uppercase_z"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__uppercase_z);}
  
  {this->char__left_paren              = f2char__new(cause, '[');  char* str = "char:left_paren";              environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__left_paren);}
  {this->char__right_paren             = f2char__new(cause, ']');  char* str = "char:right_paren";             environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__right_paren);}
  {this->char__array_left_paren        = f2char__new(cause, '(');  char* str = "char:array_left_paren";        environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__array_left_paren);}
  {this->char__array_right_paren       = f2char__new(cause, ')');  char* str = "char:array_right_paren";       environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__array_right_paren);}
  {this->char__doublelink_right_paren  = f2char__new(cause, '}');  char* str = "char:doublelink_right_paren";  environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__doublelink_right_paren);}
  {this->char__doublelink_left_paren   = f2char__new(cause, '{');  char* str = "char:doublelink_left_paren";   environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__doublelink_left_paren);}
  {this->char__quote                   = f2char__new(cause, '\\'); char* str = "char:quote";                   environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__quote);}
  {this->char__backquote               = f2char__new(cause, '`');  char* str = "char:backquote";               environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__backquote);}
  {this->char__comma                   = f2char__new(cause, ',');  char* str = "char:comma";                   environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__comma);}
  {this->char__cdr_comma               = f2char__new(cause, '@');  char* str = "char:cdr_comma";               environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__cdr_comma);}
  {this->char__funktion                = f2char__new(cause, '&');  char* str = "char:funktion";                environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__funktion);}
  {this->char__escape                  = f2char__new(cause, '#');  char* str = "char:escape";                  environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__escape);}
  {this->char__escape_hex              = f2char__new(cause, 'x');  char* str = "char:escape_hex";              environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__escape_hex);}
  {this->char__escape_hex_char         = f2char__new(cause, 'c');  char* str = "char:escape_hex_char";         environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__escape_hex_char);}
  {this->char__escape_char             = f2char__new(cause, '\\'); char* str = "char:escape_char";             environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__escape_char);}
  {this->char__escape_larva            = f2char__new(cause, '!');  char* str = "char:escape_larva";            environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__escape_larva);}
  {this->char__string_quote            = f2char__new(cause, '\''); char* str = "char:string_quote";            environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__string_quote);}
  {this->char__string_escape_newline   = f2char__new(cause, 'n');  char* str = "char:string_escape_newline";   environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__string_escape_newline);}
  {this->char__string_escape_return    = f2char__new(cause, 'r');  char* str = "char:string_escape_return";    environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__string_escape_return);}
  {this->char__string_escape_tab       = f2char__new(cause, 't');  char* str = "char:string_escape_tab";       environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__string_escape_tab);}
  {this->char__string_escape_backspace = f2char__new(cause, 'b');  char* str = "char:string_escape_backspace"; environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__string_escape_backspace);}
  {this->char__symbol_quote            = f2char__new(cause, '|');  char* str = "char:symbol_quote";            environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__symbol_quote);}
  {this->char__symbol_escape           = f2char__new(cause, '\\'); char* str = "char:symbol_escape";           environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__symbol_escape);}
  {this->char__symbol_key              = f2char__new(cause, ':');  char* str = "char:symbol_key";              environment__add_var_value(cause, global_environment(), new__symbol(cause, str), this->char__symbol_key);}
  
}

void funk2_reader__reinit(funk2_reader_t* this) {
  f2ptr cause = f2_reader_c__cause__new(initial_cause());
  
  this->end_parens_exception__symbol = new__symbol(cause, "reader:end_parens-exception");
  this->array_end_parens_exception__symbol = new__symbol(cause, "reader:array_end_parens-exception");
  this->doublelink_end_parens_exception__symbol = new__symbol(cause, "reader:doublelink_end_parens-exception");
  this->end_of_file_exception__symbol = new__symbol(cause, "reader:end_of_file-exception");
  this->could_not_read_type_exception__symbol = new__symbol(cause, "reader:could_not_read_type-exception");
  this->no_character_waiting_exception__symbol = new__symbol(cause, "reader:no_character_waiting-exception");
  
  {char* str = "reader:end_parens-exception";            this->end_parens_exception            = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "reader:unmatched_begin_paren-exception"; this->unmatched_begin_paren_exception = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "reader:array_end_parens-exception";      this->array_end_parens_exception      = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "reader:doublelink_end_parens-exception"; this->doublelink_end_parens_exception = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {
    char* str = "reader:end_of_file-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->end_of_file_exception__symbol = symbol;
    this->end_of_file_exception = environment__safe_lookup_var_value(cause, global_environment(), symbol);
  }
  {char* str = "reader:invalid_argument_type-exception";       this->invalid_argument_type_exception       = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "reader:illegal_escape_reader_metro-exception"; this->illegal_escape_reader_metro_exception = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {
    char* str = "reader:could_not_read_type-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->could_not_read_type_exception__symbol = symbol;
    this->could_not_read_type_exception = environment__safe_lookup_var_value(cause, global_environment(), symbol);
  }
  {
    char* str = "reader:no_character_waiting-exception";
    f2ptr symbol = new__symbol(cause, str);
    this->no_character_waiting_exception__symbol = symbol;
    this->no_character_waiting_exception = environment__safe_lookup_var_value(cause, global_environment(), symbol);
  }
  
  {char* str = "char:decimal_point";           this->char__decimal_point           = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:minus_sign";              this->char__minus_sign              = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  
  {char* str = "char:space";                   this->char__space                   = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:tab";                     this->char__tab                     = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:newline";                 this->char__newline                 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:return";                  this->char__return                  = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:backspace";               this->char__backspace               = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  
  {char* str = "char:0"; this->char__0 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:1"; this->char__1 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:2"; this->char__2 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:3"; this->char__3 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:4"; this->char__4 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:5"; this->char__5 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:6"; this->char__6 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:7"; this->char__7 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:8"; this->char__8 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:9"; this->char__9 = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  
  {char* str = "char:lowercase_a"; this->char__lowercase_a = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_b"; this->char__lowercase_b = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_c"; this->char__lowercase_c = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_d"; this->char__lowercase_d = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_e"; this->char__lowercase_e = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_f"; this->char__lowercase_f = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_g"; this->char__lowercase_g = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_h"; this->char__lowercase_h = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_i"; this->char__lowercase_i = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_j"; this->char__lowercase_j = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_k"; this->char__lowercase_k = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_l"; this->char__lowercase_l = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_m"; this->char__lowercase_m = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_n"; this->char__lowercase_n = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_o"; this->char__lowercase_o = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_p"; this->char__lowercase_p = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_q"; this->char__lowercase_q = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_r"; this->char__lowercase_r = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_s"; this->char__lowercase_s = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_t"; this->char__lowercase_t = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_u"; this->char__lowercase_u = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_v"; this->char__lowercase_v = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_w"; this->char__lowercase_w = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_x"; this->char__lowercase_x = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_y"; this->char__lowercase_y = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:lowercase_z"; this->char__lowercase_z = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  
  {char* str = "char:uppercase_a"; this->char__uppercase_a = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_b"; this->char__uppercase_b = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_c"; this->char__uppercase_c = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_d"; this->char__uppercase_d = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_e"; this->char__uppercase_e = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_f"; this->char__uppercase_f = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_g"; this->char__uppercase_g = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_h"; this->char__uppercase_h = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_i"; this->char__uppercase_i = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_j"; this->char__uppercase_j = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_k"; this->char__uppercase_k = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_l"; this->char__uppercase_l = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_m"; this->char__uppercase_m = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_n"; this->char__uppercase_n = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_o"; this->char__uppercase_o = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_p"; this->char__uppercase_p = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_q"; this->char__uppercase_q = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_r"; this->char__uppercase_r = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_s"; this->char__uppercase_s = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_t"; this->char__uppercase_t = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_u"; this->char__uppercase_u = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_v"; this->char__uppercase_v = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_w"; this->char__uppercase_w = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_x"; this->char__uppercase_x = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_y"; this->char__uppercase_y = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:uppercase_z"; this->char__uppercase_z = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  
  {char* str = "char:left_paren";              this->char__left_paren              = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:right_paren";             this->char__right_paren             = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:array_left_paren";        this->char__array_left_paren        = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:array_right_paren";       this->char__array_right_paren       = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:doublelink_right_paren";  this->char__doublelink_right_paren  = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:doublelink_left_paren";   this->char__doublelink_left_paren   = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:quote";                   this->char__quote                   = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:backquote";               this->char__backquote               = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:comma";                   this->char__comma                   = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:cdr_comma";               this->char__cdr_comma               = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:funktion";                this->char__funktion                = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:escape";                  this->char__escape                  = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:escape_hex";              this->char__escape_hex              = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:escape_hex_char";         this->char__escape_hex_char         = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:escape_char";             this->char__escape_char             = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:escape_larva";            this->char__escape_larva            = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:string_quote";            this->char__string_quote            = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:string_escape_newline";   this->char__string_escape_newline   = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:string_escape_return";    this->char__string_escape_return    = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:string_escape_tab";       this->char__string_escape_tab       = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:string_escape_backspace"; this->char__string_escape_backspace = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:symbol_quote";            this->char__symbol_quote            = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:symbol_escape";           this->char__symbol_escape           = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
  {char* str = "char:symbol_key";              this->char__symbol_key              = environment__safe_lookup_var_value(cause, global_environment(), new__symbol(cause, str));}
}

void funk2_reader__destroy(funk2_reader_t* this) {
}

void funk2_reader__defragment__fix_pointers(funk2_reader_t* this) {
  defragment__fix_pointer(this->end_parens_exception);
  defragment__fix_pointer(this->end_parens_exception__symbol);
  defragment__fix_pointer(this->unmatched_begin_paren_exception);
  defragment__fix_pointer(this->array_end_parens_exception);
  defragment__fix_pointer(this->array_end_parens_exception__symbol);
  defragment__fix_pointer(this->doublelink_end_parens_exception);
  defragment__fix_pointer(this->doublelink_end_parens_exception__symbol);
  defragment__fix_pointer(this->end_of_file_exception);
  defragment__fix_pointer(this->end_of_file_exception__symbol);
  defragment__fix_pointer(this->invalid_argument_type_exception);
  defragment__fix_pointer(this->illegal_escape_reader_metro_exception);
  defragment__fix_pointer(this->could_not_read_type_exception);
  defragment__fix_pointer(this->could_not_read_type_exception__symbol);
  defragment__fix_pointer(this->no_character_waiting_exception);
  defragment__fix_pointer(this->no_character_waiting_exception__symbol);
  
  defragment__fix_pointer(this->char__decimal_point);
  defragment__fix_pointer(this->char__minus_sign);
  
  defragment__fix_pointer(this->char__space);
  defragment__fix_pointer(this->char__tab);
  defragment__fix_pointer(this->char__newline);
  defragment__fix_pointer(this->char__return);
  defragment__fix_pointer(this->char__backspace);
  
  defragment__fix_pointer(this->char__0);
  defragment__fix_pointer(this->char__1);
  defragment__fix_pointer(this->char__2);
  defragment__fix_pointer(this->char__3);
  defragment__fix_pointer(this->char__4);
  defragment__fix_pointer(this->char__5);
  defragment__fix_pointer(this->char__6);
  defragment__fix_pointer(this->char__7);
  defragment__fix_pointer(this->char__8);
  defragment__fix_pointer(this->char__9);

  defragment__fix_pointer(this->char__lowercase_a);
  defragment__fix_pointer(this->char__lowercase_b);
  defragment__fix_pointer(this->char__lowercase_c);
  defragment__fix_pointer(this->char__lowercase_d);
  defragment__fix_pointer(this->char__lowercase_e);
  defragment__fix_pointer(this->char__lowercase_f);
  defragment__fix_pointer(this->char__lowercase_g);
  defragment__fix_pointer(this->char__lowercase_h);
  defragment__fix_pointer(this->char__lowercase_i);
  defragment__fix_pointer(this->char__lowercase_j);
  defragment__fix_pointer(this->char__lowercase_k);
  defragment__fix_pointer(this->char__lowercase_l);
  defragment__fix_pointer(this->char__lowercase_m);
  defragment__fix_pointer(this->char__lowercase_n);
  defragment__fix_pointer(this->char__lowercase_o);
  defragment__fix_pointer(this->char__lowercase_p);
  defragment__fix_pointer(this->char__lowercase_q);
  defragment__fix_pointer(this->char__lowercase_r);
  defragment__fix_pointer(this->char__lowercase_s);
  defragment__fix_pointer(this->char__lowercase_t);
  defragment__fix_pointer(this->char__lowercase_u);
  defragment__fix_pointer(this->char__lowercase_v);
  defragment__fix_pointer(this->char__lowercase_w);
  defragment__fix_pointer(this->char__lowercase_x);
  defragment__fix_pointer(this->char__lowercase_y);
  defragment__fix_pointer(this->char__lowercase_z);
  
  defragment__fix_pointer(this->char__uppercase_a);
  defragment__fix_pointer(this->char__uppercase_b);
  defragment__fix_pointer(this->char__uppercase_c);
  defragment__fix_pointer(this->char__uppercase_d);
  defragment__fix_pointer(this->char__uppercase_e);
  defragment__fix_pointer(this->char__uppercase_f);
  defragment__fix_pointer(this->char__uppercase_g);
  defragment__fix_pointer(this->char__uppercase_h);
  defragment__fix_pointer(this->char__uppercase_i);
  defragment__fix_pointer(this->char__uppercase_j);
  defragment__fix_pointer(this->char__uppercase_k);
  defragment__fix_pointer(this->char__uppercase_l);
  defragment__fix_pointer(this->char__uppercase_m);
  defragment__fix_pointer(this->char__uppercase_n);
  defragment__fix_pointer(this->char__uppercase_o);
  defragment__fix_pointer(this->char__uppercase_p);
  defragment__fix_pointer(this->char__uppercase_q);
  defragment__fix_pointer(this->char__uppercase_r);
  defragment__fix_pointer(this->char__uppercase_s);
  defragment__fix_pointer(this->char__uppercase_t);
  defragment__fix_pointer(this->char__uppercase_u);
  defragment__fix_pointer(this->char__uppercase_v);
  defragment__fix_pointer(this->char__uppercase_w);
  defragment__fix_pointer(this->char__uppercase_x);
  defragment__fix_pointer(this->char__uppercase_y);
  defragment__fix_pointer(this->char__uppercase_z);

  defragment__fix_pointer(this->char__left_paren);
  defragment__fix_pointer(this->char__right_paren);
  defragment__fix_pointer(this->char__array_left_paren);
  defragment__fix_pointer(this->char__array_right_paren);
  defragment__fix_pointer(this->char__doublelink_right_paren);
  defragment__fix_pointer(this->char__doublelink_left_paren);
  defragment__fix_pointer(this->char__quote);
  defragment__fix_pointer(this->char__backquote);
  defragment__fix_pointer(this->char__comma);
  defragment__fix_pointer(this->char__cdr_comma);
  defragment__fix_pointer(this->char__funktion);
  defragment__fix_pointer(this->char__escape);
  defragment__fix_pointer(this->char__escape_hex);
  defragment__fix_pointer(this->char__escape_hex_char);
  defragment__fix_pointer(this->char__escape_char);
  defragment__fix_pointer(this->char__escape_larva);
  defragment__fix_pointer(this->char__string_quote);
  defragment__fix_pointer(this->char__string_escape_newline);
  defragment__fix_pointer(this->char__string_escape_return);
  defragment__fix_pointer(this->char__string_escape_tab);
  defragment__fix_pointer(this->char__string_escape_backspace);
  defragment__fix_pointer(this->char__symbol_quote);
  defragment__fix_pointer(this->char__symbol_escape);
  defragment__fix_pointer(this->char__symbol_key);
}

// **

void f2__reader__defragment__fix_pointers() {
  // -- reinitialize --
  
  funk2_reader__defragment__fix_pointers(&(__funk2.reader));
  
  
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(exp__contains_comma);
  f2__primcfunk__init__defragment__fix_pointers(exp__contains_cdr_comma);
  f2__primcfunk__init__defragment__fix_pointers(exp__contains_cdr_comma_at_this_level);
  f2__primcfunk__init__defragment__fix_pointers(exp__comma_filter_backquoted);
  f2__primcfunk__init__defragment__fix_pointers(stream__skip_whitespace);
  f2__primcfunk__init__defragment__fix_pointers(stream__try_read);
}

void f2__reader__reinitialize_globalvars() {
  funk2_reader__reinit(&(__funk2.reader));
  
  f2__primcfunk__init__1(exp__contains_comma,                   this);
  f2__primcfunk__init__1(exp__contains_cdr_comma,               this);
  f2__primcfunk__init__1(exp__contains_cdr_comma_at_this_level, this);
  f2__primcfunk__init__1(exp__comma_filter_backquoted,          this);
  f2__primcfunk__init__1(stream__skip_whitespace,               stream);
  f2__primcfunk__init__1(stream__try_read,                      stream);
}

void f2__reader__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "reader", "", &f2__reader__reinitialize_globalvars, &f2__reader__defragment__fix_pointers);
  
  funk2_reader__init(&(__funk2.reader));
  
  f2__reader__reinitialize_globalvars();
}


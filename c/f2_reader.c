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

#include "funk2.h"
#include <stdio.h>

boolean_t raw__exp__contains_comma(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr cdr = f2cons__cdr(this, cause);
    if (car == __funk2.globalenv.comma__symbol || cdr == __funk2.globalenv.comma__symbol) {
      return 1;
    }
    return (raw__exp__contains_comma(cause, car) || raw__exp__contains_comma(cause, cdr));
  }
  return 0;
}

f2ptr f2__exp__contains_comma(f2ptr cause, f2ptr this) {return f2bool__new(raw__exp__contains_comma(cause, this));}
def_pcfunk1(exp__contains_comma, this, return f2__exp__contains_comma(this_cause, this));

boolean_t raw__exp__contains_cdr_comma(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr cdr = f2cons__cdr(this, cause);
    if (car == __funk2.globalenv.cdr_comma__symbol || cdr == __funk2.globalenv.cdr_comma__symbol) {
      return 1;
    }
    return (raw__exp__contains_cdr_comma(cause, car) || raw__exp__contains_cdr_comma(cause, cdr));
  }
  return 0;
}

f2ptr f2__exp__contains_cdr_comma(f2ptr cause, f2ptr this) {return f2bool__new(raw__exp__contains_cdr_comma(cause, this));}
def_pcfunk1(exp__contains_cdr_comma, this, return f2__exp__contains_cdr_comma(this_cause, this));

boolean_t raw__exp__contains_cdr_comma_at_this_level(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr cdr = f2cons__cdr(this, cause);
    if (raw__cons__is_type(cause, car) && f2cons__car(car, cause) == __funk2.globalenv.cdr_comma__symbol) {
      return 1;
    }
    return raw__exp__contains_cdr_comma_at_this_level(cause, cdr);
  }
  return 0;
}

f2ptr f2__exp__contains_cdr_comma_at_this_level(f2ptr cause, f2ptr this) {return f2bool__new(raw__exp__contains_cdr_comma_at_this_level(cause, this));}
def_pcfunk1(exp__contains_cdr_comma_at_this_level, this, return f2__exp__contains_cdr_comma_at_this_level(this_cause, this));

f2ptr f2__exp__comma_filter_backquoted(f2ptr cause, f2ptr this) {
  if (raw__cons__is_type(cause, this)) {
    f2ptr car = f2cons__car(this, cause);
    f2ptr car_car;
    if(raw__cons__is_type(cause, car) && ((car_car = f2cons__car(car, cause)) == __funk2.globalenv.comma__symbol || car_car == __funk2.globalenv.cdr_comma__symbol)) {
      f2cons__car__set(this, cause, f2cons__car(f2cons__cdr(f2cons__car(this, cause), cause), cause));
    } else if (! (raw__exp__contains_comma(cause, car) || raw__exp__contains_cdr_comma(cause, car))) {
      f2cons__car__set(this, cause, f2cons__new(cause, __funk2.globalenv.quote__symbol, f2cons__new(cause, car, nil)));
    } else if (! raw__exp__contains_cdr_comma_at_this_level(cause, car)) {
      f2cons__car__set(this, cause, f2cons__new(cause, __funk2.globalenv.backquote__list__symbol, f2__exp__comma_filter_backquoted(cause, car)));
    } else {
      f2cons__car__set(this, cause, f2cons__new(cause, __funk2.globalenv.backquote__list_append__symbol, f2__exp__comma_filter_backquoted(cause, car)));
    }
    f2__exp__comma_filter_backquoted(cause, f2cons__cdr(this, cause));
  }
  return this;
}
def_pcfunk1(exp__comma_filter_backquoted, this, return f2__exp__comma_filter_backquoted(this_cause, this));

f2ptr f2__stream__first_non_whitespace_character(f2ptr cause, f2ptr stream) {
  f2ptr first_char;
  do {
    first_char = f2__stream__try_read_character(cause, stream);
    if (! first_char) {
    }
  } while (raw__eq(cause, first_char, __funk2.reader.char__space)   ||
	   raw__eq(cause, first_char, __funk2.reader.char__tab)     ||
	   raw__eq(cause, first_char, __funk2.reader.char__newline) ||
	   raw__eq(cause, first_char, __funk2.reader.char__return));
  return first_char;
}

f2ptr f2__stream__skip_whitespace(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__first_non_whitespace_character(cause, stream);
  f2__stream__ungetc(cause, stream, first_char);
  return nil;
}

f2ptr f2__stream__try_read_impossibility(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  if (raw__exception__is_type(cause, first_char) && raw__eq(cause, f2exception__tag(first_char, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  // check all imposibilities for first_char
  if (raw__eq(cause, first_char, __funk2.reader.char__right_paren))            {return __funk2.reader.end_parens_exception;}
  if (raw__eq(cause, first_char, __funk2.reader.char__array_right_paren))      {return __funk2.reader.array_end_parens_exception;}
  if (raw__eq(cause, first_char, __funk2.reader.char__doublelink_right_paren)) {return __funk2.reader.doublelink_end_parens_exception;}
  f2__stream__ungetc(cause, stream, first_char);
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_list(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read list
  if (raw__eq(cause, first_char, __funk2.reader.char__left_paren)) {
    f2ptr seq  = nil;
    f2ptr iter = nil;
    f2ptr new_cons;
    f2ptr exp;
    while (1) {
      exp = raw__read(cause, stream);
      if (exp == __funk2.reader.end_parens_exception) {return seq;} // successfully read end of list
      if (raw__exception__is_type(cause, exp) && raw__eq(cause, f2exception__tag(exp, cause), __funk2.reader.end_of_file_exception__symbol)) {return __funk2.reader.unmatched_begin_paren_exception;}
      if (raw__exception__is_type(cause, exp)) {return exp;} // other exceptions should be propagated
      new_cons = f2cons__new(cause, exp, nil);
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
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read doublelink list
  if (raw__eq(cause, first_char, __funk2.reader.char__doublelink_left_paren)) {
    f2ptr seq  = nil;
    f2ptr iter = nil;
    f2ptr new_doublelink;
    f2ptr exp;
    while (1) {
      exp = raw__read(cause, stream);
      if (exp == __funk2.reader.doublelink_end_parens_exception) {return seq;} // successfully read end of doublelink list
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
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read quoted expression
  if (raw__eq(cause, first_char, __funk2.reader.char__quote)) {
    f2ptr exp = raw__read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return f2cons__new(cause, __funk2.globalenv.quote__symbol, f2cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_backquoted(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read backquoted expression
  if (raw__eq(cause, first_char, __funk2.reader.char__backquote)) {
    f2ptr exp = raw__read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    if (raw__cons__is_type(cause, exp) && (raw__exp__contains_comma(cause, exp) || raw__exp__contains_cdr_comma(cause, exp))) {
      if (raw__exp__contains_cdr_comma_at_this_level(cause, exp)) {
	exp = f2__exp__comma_filter_backquoted(cause, exp);
	if (raw__exception__is_type(cause, exp)) {return exp;}
	return f2cons__new(cause, __funk2.globalenv.backquote__list_append__symbol, exp);
      } else {
	exp = f2__exp__comma_filter_backquoted(cause, exp);
	if (raw__exception__is_type(cause, exp)) {return exp;}
	return f2cons__new(cause, __funk2.globalenv.backquote__list__symbol, exp);
      }
    }
    return f2cons__new(cause, __funk2.globalenv.quote__symbol, f2cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_comma_exp(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read comma expression (hopefully within backquote)
  if (raw__eq(cause, first_char, __funk2.reader.char__comma)) {
    f2ptr exp = raw__read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return f2cons__new(cause, __funk2.globalenv.comma__symbol, f2cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_cdr_comma_exp(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read cdr comma expression (hopefully within backquote)
  if (raw__eq(cause, first_char, __funk2.reader.char__cdr_comma)) {
    f2ptr exp = raw__read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return f2cons__new(cause, __funk2.globalenv.cdr_comma__symbol, f2cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_funktion_name(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read funktion name
  if (raw__eq(cause, first_char, __funk2.reader.char__funktion)) {
    f2ptr exp = raw__read(cause, stream);
    if (raw__exception__is_type(cause, exp)) {return exp;}
    return f2cons__new(cause, __funk2.globalenv.funkvar__symbol, f2cons__new(cause, exp, nil));
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_unescaped_hex_pointer(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  // read hex pointer
  if (raw__eq(cause, read_ch, __funk2.reader.char__escape_hex)) {
    int buf_size = 10; // not bigint, so no more buffer really needed
    char* str = (char*)from_ptr(f2__malloc(buf_size));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19);
      }
      char ch = f2char__ch(read_ch, cause);
      if ((ch < '0' || ch > '9') &&
	  (ch < 'a' || ch > 'f') &&
	  (ch < 'A' || ch > 'F')) {
	f2__stream__ungetc(cause, stream, read_ch);
	break;
      }
      if (ch >= '0' && ch <= '9') {str[i] = ch - '0';}
      if (ch >= 'a' && ch <= 'f') {str[i] = ch - 'a' + 10;}
      if (ch >= 'A' && ch <= 'F') {str[i] = ch - 'A' + 10;}
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (char*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size, buf_size));
      }
    } while(1);
    int j = 0;
    ptr p = 0;
    u64 t;
    i --;
    for (; i >= 0; i --) {
      t = (unsigned long long)(str[j]);
      p += (t << (i << 2));
      j ++;
    } 
    f2__free(to_ptr(str));
    f2ptr exp = f2pointer__new(cause, p);
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_unescaped_hex_char(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  
  // read char hex
  if (f2__eq(cause, read_ch, __funk2.reader.char__escape_hex_char)) {
    int buf_size = 10; // not bigint, so no more buffer really needed
    char* str = (char*)from_ptr(f2__malloc(buf_size));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19);
      }
      char ch = f2char__ch(read_ch, cause);
      if ((ch < '0' || ch > '9') &&
	  (ch < 'a' || ch > 'f') &&
	  (ch < 'A' || ch > 'F')) {
	f2__stream__ungetc(cause, stream, read_ch);
	break;
      }
      if (ch >= '0' && ch <= '9') {str[i] = ch - '0';}
      if (ch >= 'a' && ch <= 'f') {str[i] = ch - 'a' + 10;}
      if (ch >= 'A' && ch <= 'F') {str[i] = ch - 'A' + 10;}
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (char*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size, buf_size));
      }
    } while(1);
    int j = 0;
    ptr p = 0;
    u64 t;
    i --;
    for (; i >= 0; i --) {
      t = (unsigned long long)(str[j]);
      p += (t << (i << 2));
      j ++;
    } 
    f2__free(to_ptr(str));
    f2ptr exp = f2char__new(cause, (char)p);
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_unescaped_larva(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  
  // read larva
  if (raw__eq(cause, read_ch, __funk2.reader.char__escape_larva)) {
    int buf_size = 10; // not bigint, so no more buffer really needed
    char* str = (char*)from_ptr(f2__malloc(buf_size));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19);
      }
      char ch = f2char__ch(stream, cause);
      if (ch < '0' || ch > '9') {
	f2__stream__ungetc(cause, stream, read_ch);
	break;
      }
      if (ch >= '0' && ch <= '9') {str[i] = ch - '0';}
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (char*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size, buf_size));
      }
    } while(1);
    int j = 0;
    u32 type = 0;
    u32 t;
    for (; i > 0; i --) {
      t = (u64)(str[j]);
      u32 i_power = 1;
      int k; for (k = i - 1; k > 0; k --) {i_power *= 10;}
      type += (t * i_power);
      j ++;
    }
    f2__free(to_ptr(str));
    f2ptr exp = f2larva__new(cause, type);
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_unescaped_gfunkptr(f2ptr cause, f2ptr stream) {
  f2ptr read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
  
  if (raw__eq(cause, read_ch, __funk2.reader.char__escape_gfunkptr)) {
    // read gfunkptr of form #g(ip_addr pool_index pool_address)
    f2ptr gfunkptr_read_array = raw__read(cause, stream);
    if ((! raw__array__is_type(cause, gfunkptr_read_array)) || (raw__array__length(cause, gfunkptr_read_array) != 3)) {return __funk2.reader.gfunkptr_read__exception;}
    f2ptr computer_id__integer  = raw__array__elt(cause, gfunkptr_read_array, 0);
    f2ptr pool_index__integer   = raw__array__elt(cause, gfunkptr_read_array, 1);
    f2ptr pool_address__integer = raw__array__elt(cause, gfunkptr_read_array, 2);
    if ((! raw__integer__is_type(cause, computer_id__integer)) ||
	(! raw__integer__is_type(cause, pool_index__integer)) ||
	(! raw__integer__is_type(cause, pool_address__integer))) {
      return __funk2.reader.gfunkptr_read__exception;
    }
    computer_id_t  computer_id  = f2integer__i(computer_id__integer, cause);
    pool_index_t   pool_index   = f2integer__i(pool_index__integer, cause);
    pool_address_t pool_address = f2integer__i(pool_address__integer, cause);
    return f2gfunkptr__new(cause, computer_id, pool_index, pool_address);
  } else {
    f2__stream__ungetc(cause, stream, read_ch);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_escaped(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
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
    
    {
      f2ptr try_read_result = f2__stream__try_read_unescaped_gfunkptr(cause, stream);
      if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {
	return try_read_result;
      }
    }
    
    //return __funk2.reader.illegal_escape_reader_metro_exception;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_array(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read array
  if (raw__eq(cause, first_char, __funk2.reader.char__array_left_paren)) {
    int buf_size = 16;
    f2ptr* buf = (f2ptr*)from_ptr(f2__malloc(sizeof(f2ptr) * buf_size));
    int i = 0;
    f2ptr subexp;
    do {
      subexp = raw__read(cause, stream);
      if (subexp == __funk2.reader.array_end_parens_exception) {break;}
      if (raw__exception__is_type(cause, subexp)) {return subexp;}
      buf[i] = subexp;
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	buf = (f2ptr*)from_ptr(f2__new_alloc(to_ptr(buf), sizeof(f2ptr) * old_buf_size, sizeof(f2ptr) * buf_size));
      }
    } while(1);
    f2ptr exp = raw__array__new(cause, i);
    int j;
    for (j = 0; j < i; j++) {
      raw__array__elt__set(cause, exp, j, buf[j]);
    }
    f2__free(to_ptr(buf));
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_string(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read string
  if (raw__eq(cause, first_char, __funk2.reader.char__string_quote)) {
    int buf_size = 64;
    char* str = (char*)from_ptr(f2__malloc(buf_size));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19);
      }
      char ch = f2char__ch(read_ch, cause);
      if (ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {break;}
      if (ch == f2char__ch(__funk2.reader.char__escape_char, cause)) {
	read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
	if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
	if (! raw__char__is_type(cause, read_ch)) {
	  return f2larva__new(cause, 19);
	}
	ch = f2char__ch(read_ch, cause);
	if      (ch == f2char__ch(__funk2.reader.char__string_escape_newline, cause))   {ch = '\n';}
	else if (ch == f2char__ch(__funk2.reader.char__string_escape_return, cause))    {ch = '\r';}
	else if (ch == f2char__ch(__funk2.reader.char__string_escape_tab, cause))       {ch = '\t';}
	else if (ch == f2char__ch(__funk2.reader.char__string_escape_backspace, cause)) {ch = '\b';}
	// otherwise ignore next character
      }
      str[i] = ch;
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (char*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size, buf_size));
      }
    } while(1);
    f2ptr exp = f2string__new(cause, i, (u8*)str);
    f2__free(to_ptr(str));
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_symbol_quote(f2ptr cause, f2ptr stream) {
  f2ptr first_char = f2__stream__getc(cause, stream);
  // read symbol quote
  if (raw__eq(cause, first_char, __funk2.reader.char__symbol_quote)) {
    int buf_size = 64;
    char* str = (char*)from_ptr(f2__malloc(buf_size));
    int i = 0;
    f2ptr read_ch;
    do {
      read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19);
      }
      char ch = f2char__ch(read_ch, cause);
      if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {break;}
      if (ch == f2char__ch(__funk2.reader.char__symbol_escape, cause)) {
	// ignore next character
	read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
	if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
	if (! raw__char__is_type(cause, read_ch)) {
	  return f2larva__new(cause, 19);
	}
	ch = f2char__ch(read_ch, cause);
      }
      str[i] = ch;
      i ++;
      if (i >= buf_size) {
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (char*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size, buf_size));
      }
    } while(1);
    f2ptr exp = f2symbol__new(cause, i, (u8*)str);
    f2__free(to_ptr(str));
    return exp;
  } else {
    f2__stream__ungetc(cause, stream, first_char);
  }
  return __funk2.reader.could_not_read_type_exception;
}

f2ptr f2__stream__try_read_token(f2ptr cause, f2ptr stream) {
  // otherwise read a token (might be a number or a caps-insensitive symbol)
  int buf_size = 64;
  char* str = (char*)from_ptr(f2__malloc(buf_size));
  int i = 0;
  {
    f2ptr read_ch;
    do {
      read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
      if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
      if (! raw__char__is_type(cause, read_ch)) {
	return f2larva__new(cause, 19);
      }
      char ch = f2char__ch(read_ch, cause);
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren, cause)            || ch == f2char__ch(__funk2.reader.char__right_paren, cause) ||
	  ch == f2char__ch(__funk2.reader.char__array_left_paren, cause)      || ch == f2char__ch(__funk2.reader.char__array_right_paren, cause) ||
	  ch == f2char__ch(__funk2.reader.char__doublelink_left_paren, cause) || ch == f2char__ch(__funk2.reader.char__doublelink_right_paren, cause)) {
	f2__stream__ungetc(cause, stream, read_ch);
	break;
      }
      if (ch == '\\') {
	// ignore next character
	read_ch = f2__stream__getc(cause, stream); if (! read_ch) {return nil;}
	if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {f2__free(to_ptr(str)); status("raw_read() note: eof_except."); return __funk2.reader.end_of_file_exception;}
	if (! raw__char__is_type(cause, read_ch)) {
	  return f2larva__new(cause, 19);
	}
	ch = f2char__ch(read_ch, cause);
      }
      str[i] = ch;
      i ++;
      if (i >= buf_size - 1) { // -1 because we need to add a null to end for number conversion
	int old_buf_size = buf_size;
	buf_size <<= 1;
	str = (char*)from_ptr(f2__new_alloc(to_ptr(str), old_buf_size, buf_size));
      }
    } while(1);
  }
  // see if is partly and completely a number
  boolean_t has_numeric = 0;
  boolean_t all_numeric = 1;
  {
    int j;
    char ch;
    for (j = i - 1; j >= 0; j --) {
      ch = str[j];
      if (ch >= '0' && ch <= '9') {has_numeric = 1;}
      else if (ch != '.' && ch != '-') {all_numeric = 0; break;}
    }
  }
  // convert token to number
  if (has_numeric && all_numeric) {
    str[i] = (char)0;
    f2ptr exp = f2integer__new(cause, atoll(str));
    f2__free(to_ptr(str));
    return exp;
  }
  if (i == 3 && str[0] == 'n' && str[1] == 'i' && str[2] == 'l') {
    return nil;
  }
  f2ptr exp = f2symbol__new(cause, i, (u8*)str);
  f2__free(to_ptr(str));
  return exp;
}

f2ptr f2__stream__read(f2ptr cause, f2ptr stream) {
  f2__stream__skip_whitespace(cause, stream);
  
  {f2ptr try_read_result = f2__stream__try_read_impossibility(  cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_list(           cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_doublelink_list(cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_quoted(         cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_backquoted(     cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_comma_exp(      cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_cdr_comma_exp(  cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_funktion_name(  cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_escaped(        cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_array(          cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_string(         cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_symbol_quote(   cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  {f2ptr try_read_result = f2__stream__try_read_token(          cause, stream); if ((! raw__exception__is_type(cause, try_read_result)) || (! raw__eq(cause, f2exception__tag(try_read_result, cause), __funk2.reader.could_not_read_type_exception__symbol))) {return try_read_result;}}
  
  return nil;
}

f2ptr raw__read(f2ptr cause, f2ptr stream) {
  // basic type checking for stream argument
  if (!stream) {printf("\nraw__read: stream is nil."); return __funk2.reader.invalid_argument_type_exception;}
  if (! raw__stream__is_type(cause, stream)) {printf("\nraw__read: stream is not stream."); f2__print(nil, stream); return __funk2.reader.invalid_argument_type_exception;}
  return f2__stream__read(cause, stream);
}
def_pcfunk1(read, stream, return raw__read(this_cause, stream));

void funk2_reader__init(funk2_reader_t* this) {
  f2ptr cause = f2_reader_c__cause__new(initial_cause());
  
  {char* str = "reader:end_parens-exception";                  f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->end_parens_exception                  = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->end_parens_exception);}
  {char* str = "reader:unmatched_begin_paren-exception";       f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->unmatched_begin_paren_exception       = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->unmatched_begin_paren_exception);}
  {char* str = "reader:array_end_parens-exception";            f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->array_end_parens_exception            = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->array_end_parens_exception);}
  {char* str = "reader:doublelink_end_parens-exception";       f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->doublelink_end_parens_exception       = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->doublelink_end_parens_exception);}
  {
    char* str = "reader:end_of_file-exception";
    f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str);
    this->end_of_file_exception__symbol = symbol;
    this->end_of_file_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->end_of_file_exception);
  }
  {char* str = "reader:invalid_argument_type-exception";       f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->invalid_argument_type_exception       = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->invalid_argument_type_exception);}
  {char* str = "reader:illegal_escape_reader_metro-exception"; f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->illegal_escape_reader_metro_exception = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->illegal_escape_reader_metro_exception);}
  {char* str = "reader:gfunkptr_read-exception";               f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str); this->gfunkptr_read__exception              = f2exception__new(cause, symbol, nil); environment__add_var_value(cause, global_environment(), symbol, this->gfunkptr_read__exception);}
  {
    char* str = "reader:could_not_read_type-exception";
    f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str);
    this->could_not_read_type_exception__symbol = symbol;
    this->could_not_read_type_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->could_not_read_type_exception);
  }
  {
    char* str = "reader:no_character_waiting-exception";
    f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str);
    this->no_character_waiting_exception__symbol = symbol;
    this->no_character_waiting_exception = f2exception__new(cause, symbol, nil);
    environment__add_var_value(cause, global_environment(), symbol, this->no_character_waiting_exception);
  }
  
  {this->char__space                   = f2char__new(cause, ' ');  char* str = "char:space";                   environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__space);}
  {this->char__tab                     = f2char__new(cause, '\t'); char* str = "char:tab";                     environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__tab);}
  {this->char__newline                 = f2char__new(cause, '\n'); char* str = "char:newline";                 environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__newline);}
  {this->char__return                  = f2char__new(cause, '\r'); char* str = "char:return";                  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__return);}
  {this->char__left_paren              = f2char__new(cause, '[');  char* str = "char:left_paren";              environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__left_paren);}
  {this->char__right_paren             = f2char__new(cause, ']');  char* str = "char:right_paren";             environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__right_paren);}
  {this->char__array_left_paren        = f2char__new(cause, '(');  char* str = "char:array_left_paren";        environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__array_left_paren);}
  {this->char__array_right_paren       = f2char__new(cause, ')');  char* str = "char:array_right_paren";       environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__array_right_paren);}
  {this->char__doublelink_right_paren  = f2char__new(cause, '}');  char* str = "char:doublelink_right_paren";  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__doublelink_right_paren);}
  {this->char__doublelink_left_paren   = f2char__new(cause, '{');  char* str = "char:doublelink_left_paren";   environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__doublelink_left_paren);}
  {this->char__quote                   = f2char__new(cause, '\\'); char* str = "char:quote";                   environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__quote);}
  {this->char__backquote               = f2char__new(cause, '`');  char* str = "char:backquote";               environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__backquote);}
  {this->char__comma                   = f2char__new(cause, ',');  char* str = "char:comma";                   environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__comma);}
  {this->char__cdr_comma               = f2char__new(cause, '@');  char* str = "char:cdr_comma";               environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__cdr_comma);}
  {this->char__funktion                = f2char__new(cause, '&');  char* str = "char:funktion";                environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__funktion);}
  {this->char__escape                  = f2char__new(cause, '#');  char* str = "char:escape";                  environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__escape);}
  {this->char__escape_hex              = f2char__new(cause, 'x');  char* str = "char:escape_hex";              environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__escape_hex);}
  {this->char__escape_hex_char         = f2char__new(cause, 'c');  char* str = "char:escape_hex_char";         environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__escape_hex_char);}
  {this->char__escape_char             = f2char__new(cause, '\\'); char* str = "char:escape_char";             environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__escape_char);}
  {this->char__escape_larva            = f2char__new(cause, '!');  char* str = "char:escape_larva";            environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__escape_larva);}
  {this->char__escape_gfunkptr         = f2char__new(cause, 'g');  char* str = "char:escape_gfunkptr";         environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__escape_gfunkptr);}
  {this->char__string_quote            = f2char__new(cause, '\''); char* str = "char:string_quote";            environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__string_quote);}
  {this->char__string_escape_newline   = f2char__new(cause, 'n');  char* str = "char:string_escape_newline";   environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__string_escape_newline);}
  {this->char__string_escape_return    = f2char__new(cause, 'r');  char* str = "char:string_escape_return";    environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__string_escape_return);}
  {this->char__string_escape_tab       = f2char__new(cause, 't');  char* str = "char:string_escape_tab";       environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__string_escape_tab);}
  {this->char__string_escape_backspace = f2char__new(cause, 'b');  char* str = "char:string_escape_backspace"; environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__string_escape_backspace);}
  {this->char__symbol_quote            = f2char__new(cause, '|');  char* str = "char:symbol_quote";            environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__symbol_quote);}
  {this->char__symbol_escape           = f2char__new(cause, '\\'); char* str = "char:symbol_escape";           environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__symbol_escape);}
  {this->char__symbol_key              = f2char__new(cause, ':');  char* str = "char:symbol_key";              environment__add_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str), this->char__symbol_key);}
  
}

void funk2_reader__reinit(funk2_reader_t* this) {
  f2ptr cause = f2_reader_c__cause__new(initial_cause());
  
  {char* str = "reader:end_parens-exception";                  this->end_parens_exception                  = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "reader:unmatched_begin_paren-exception";       this->unmatched_begin_paren_exception       = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "reader:array_end_parens-exception";            this->array_end_parens_exception            = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "reader:doublelink_end_parens-exception";       this->doublelink_end_parens_exception       = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {
    char* str = "reader:end_of_file-exception";
    f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str);
    this->end_of_file_exception__symbol = symbol;
    this->end_of_file_exception = environment__safe_lookup_var_value(cause, global_environment(), symbol);
  }
  {char* str = "reader:invalid_argument_type-exception";       this->invalid_argument_type_exception       = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "reader:illegal_escape_reader_metro-exception"; this->illegal_escape_reader_metro_exception = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "reader:gfunkptr_read-exception";               this->gfunkptr_read__exception              = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {
    char* str = "reader:could_not_read_type-exception";
    f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str);
    this->could_not_read_type_exception__symbol = symbol;
    this->could_not_read_type_exception = environment__safe_lookup_var_value(cause, global_environment(), symbol);
  }
  {
    char* str = "reader:no_character_waiting-exception";
    f2ptr symbol = f2symbol__new(cause, strlen(str), (u8*)str);
    this->no_character_waiting_exception__symbol = symbol;
    this->no_character_waiting_exception = environment__safe_lookup_var_value(cause, global_environment(), symbol);
  }
  
  {char* str = "char:space";                   this->char__space                   = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:tab";                     this->char__tab                     = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:newline";                 this->char__newline                 = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:return";                  this->char__return                  = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:left_paren";              this->char__left_paren              = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:right_paren";             this->char__right_paren             = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:array_left_paren";        this->char__array_left_paren        = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:array_right_paren";       this->char__array_right_paren       = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:doublelink_right_paren";  this->char__doublelink_right_paren  = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:doublelink_left_paren";   this->char__doublelink_left_paren   = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:quote";                   this->char__quote                   = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:backquote";               this->char__backquote               = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:comma";                   this->char__comma                   = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:cdr_comma";               this->char__cdr_comma               = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:funktion";                this->char__funktion                = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:escape";                  this->char__escape                  = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:escape_hex";              this->char__escape_hex              = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:escape_hex_char";         this->char__escape_hex_char         = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:escape_char";             this->char__escape_char             = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:escape_larva";            this->char__escape_larva            = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:escape_gfunkptr";         this->char__escape_gfunkptr         = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:string_quote";            this->char__string_quote            = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:string_escape_newline";   this->char__string_escape_newline   = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:string_escape_return";    this->char__string_escape_return    = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:string_escape_tab";       this->char__string_escape_tab       = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:string_escape_backspace"; this->char__string_escape_backspace = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:symbol_quote";            this->char__symbol_quote            = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:symbol_escape";           this->char__symbol_escape           = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
  {char* str = "char:symbol_key";              this->char__symbol_key              = environment__safe_lookup_var_value(cause, global_environment(), f2symbol__new(cause, strlen(str), (u8*)str));}
}

void funk2_reader__destroy(funk2_reader_t* this) {
}

// **

void f2__reader__reinitialize_globalvars() {
  funk2_reader__reinit(&(__funk2.reader));
}

void f2__reader__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "reader", "", &f2__reader__reinitialize_globalvars);
  
  funk2_reader__init(&(__funk2.reader));
  
  f2__reader__reinitialize_globalvars();
  
  f2__primcfunk__init__1(exp__contains_comma,                   this,   "");
  f2__primcfunk__init__1(exp__contains_cdr_comma,               this,   "");
  f2__primcfunk__init__1(exp__contains_cdr_comma_at_this_level, this,   "");
  f2__primcfunk__init__1(exp__comma_filter_backquoted,          this,   "");
  f2__primcfunk__init__1(read,                                  stream, "simple hardcoded reader funktion for reading from a stream (such as stdin).");
}


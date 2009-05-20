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

f2ptr f2__stringlist__new_string_from_concatenation(f2ptr cause, f2ptr this) {
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__consp(iter, cause)) {return f2larva__new(cause, 1);}
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__stringp(str, cause)) {return f2larva__new(cause, 1);}
      u64 str_length = f2string__length(str, cause);
      total_length += str_length;
      iter = f2cons__cdr(iter, cause);
    }
  }
  u8* temp_str = (u8*)malloc(total_length + 1);
  u64 index = 0;
  {
    f2ptr iter = this;
    while (iter) {
      f2ptr str = f2cons__car(iter, cause);
      u64 str_length = f2string__length(str, cause);
      f2string__str_copy(str, cause, temp_str + index);
      index += str_length;
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr new_string = f2string__new(cause, total_length, temp_str);
  free(temp_str);
  return new_string;
}
def_pcfunk1(stringlist__concat, this, return f2__stringlist__new_string_from_concatenation(this_cause, this));

f2ptr f2__stringlist__new_string_from_intersperse(f2ptr cause, f2ptr this, f2ptr intersperse_string) {
  if (! raw__stringp(intersperse_string, cause)) {
    return f2larva__new(cause, 1);
  }
  u64 intersperse_string__length = f2string__length(intersperse_string, cause);
  u8* intersperse_string__str    = malloc(intersperse_string__length + 1);
  f2string__str_copy(intersperse_string, cause, intersperse_string__str);
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__consp(iter, cause)) {return f2larva__new(cause, 1);}
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__stringp(str, cause)) {return f2larva__new(cause, 1);}
      u64 str_length = f2string__length(str, cause);
      total_length += str_length;
      iter = f2cons__cdr(iter, cause);
      if (iter) {
	total_length += intersperse_string__length;
      }
    }
  }
  u8* temp_str = (u8*)malloc(total_length + 1);
  u64 index = 0;
  {
    f2ptr iter = this;
    while (iter) {
      f2ptr str = f2cons__car(iter, cause);
      u64 str_length = f2string__length(str, cause);
      f2string__str_copy(str, cause, temp_str + index);
      index += str_length;
      iter = f2cons__cdr(iter, cause);
      if (iter) {
	memcpy(temp_str + index, intersperse_string__str, intersperse_string__length);
	index += intersperse_string__length;
      }
    }
  }
  f2ptr new_string = f2string__new(cause, total_length, temp_str);
  free(temp_str);
  free(intersperse_string__str);
  return new_string;
}
def_pcfunk2(stringlist__intersperse, this, intersperse_string, return f2__stringlist__new_string_from_intersperse(this_cause, this, intersperse_string));

f2ptr f2__exp__to_new_string(f2ptr cause, f2ptr exp) {
  if (! exp) {
    return f2string__new(cause, strlen("[]"), (u8*)"[]");
  }
  ptype_t ptype = f2ptype__raw(exp, cause);
  switch(ptype) {
  case ptype_free_memory:     return f2larva__new(cause, 1);
  case ptype_newly_allocated: return f2larva__new(cause, 1);
  case ptype_integer: {
    u8 temp_str[1024];
    snprintf((char*)temp_str, 1024, s64__fstr, f2integer__i(exp, cause));
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  case ptype_double: {
    u8 temp_str[1024];
    snprintf((char*)temp_str, 1024, double__fstr, f2double__d(exp, cause));
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  case ptype_float: {
    u8 temp_str[1024];
    snprintf((char*)temp_str, 1024, float__fstr, f2float__f(exp, cause));
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  case ptype_pointer: {
    u8 temp_str[1024];
    snprintf((char*)temp_str, 1024, pointer__fstr, f2pointer__p(exp, cause));
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  case ptype_gfunkptr:
    return f2string__new(cause, strlen("<gfunkptr>"), (u8*)"<gfunkptr>");
  case ptype_mutex:
    return f2string__new(cause, strlen("[mutex]"), (u8*)"[mutex]");
  case ptype_char: {
    u8 temp_str[1024];
    u8 ch_value = f2char__ch(exp, cause);
    if (ch_value >= 28) {
      snprintf((char*)temp_str, 1024, "%c%c%c", __escape_char, __escape_char_char, ch_value);
    } else {
      snprintf((char*)temp_str, 1024, "%c%c%X", __escape_char, __escape_hex_char_char, (uint)ch_value);
    }
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  case ptype_string: {
    u64 exp__length = f2string__length(exp, cause);
    u8* temp_old_str = alloca(exp__length);
    f2string__str_copy(exp, cause, temp_old_str);
    u8* temp_str     = alloca(exp__length * 2);
    u64 index;
    u64 new_index = 0;
    for (index = 0; index < exp__length; index ++) {
      u8 ch = temp_old_str[index];
      if (ch == __string_quote_char) {
	temp_str[new_index] = __escape_char_char;
	new_index ++;
      }
      temp_str[new_index] = ch;
      new_index ++;
    }
    return f2string__new(cause, new_index, temp_str);
  } break;
  case ptype_symbol: {
    boolean_t all_cool = boolean__true;
    u64 exp__length = f2string__length(exp, cause);
    u8* temp_old_str = alloca(exp__length);
    f2string__str_copy(exp, cause, temp_old_str);
    u64 index;
    for (index = 0; index < exp__length; index ++) {
      u8 ch = temp_old_str[index];
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == __left_paren_char || ch == __right_paren_char) {
	all_cool = boolean__false;
      }
    }
    if (all_cool) {
      return f2string__new(cause, exp__length, temp_old_str);
    } else {
      u64 new_index = 0;
      u8* temp_str = alloca(exp__length * 2);
      temp_str[new_index] = __symbol_quote_char;
      new_index ++;
      for (index = 0; index < exp__length; index ++) {
	u8 ch = temp_old_str[index];
	if (ch == __symbol_quote_char) {
	  temp_str[new_index] = __symbol_escape_char;
	  new_index ++;
	}
	temp_str[new_index] = ch;
	new_index ++;
      }
      temp_str[new_index] = __symbol_quote_char;
      new_index ++;
      return f2string__new(cause, new_index, temp_str);
    }
  } break;
  case ptype_chunk:
    return f2string__new(cause, strlen("<chunk>"), (u8*)"<chunk>");
  case ptype_simple_array:
    return f2string__new(cause, strlen("<simple_array>"), (u8*)"<simple_array>");
  case ptype_traced_array:
    return f2string__new(cause, strlen("<traced_array>"), (u8*)"<traced_array>");
  case ptype_larva: {
    u8 temp_str[1024];
    u32 larva_type = f2larva__type(exp, cause);
    snprintf((char*)temp_str, 1024, "%c%c" u32__fstr, __escape_char, __escape_larva_char, larva_type);
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  }
}
def_pcfunk2(exp__to_string, exp, return f2__exp__to_new_string(this_cause, exp));


void f2__string__reinitialize_globalvars() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
}

void f2__string__initialize() {
  //f2ptr cause = initial_cause(); //f2_string_c__cause__new(initial_cause(), nil, global_environment());
  pause_gc();
  
  f2__primobject_frame__reinitialize_globalvars();
  
  f2__primcfunk__init(stringlist__concat);
  f2__primcfunk__init(stringlist__intersperse);
  f2__primcfunk__init(exp__to_string);
  
  resume_gc();
  try_gc();
}


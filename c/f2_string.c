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

#include "funk2.h"

f2ptr f2__stringlist__new_string_from_concatenation(f2ptr cause, f2ptr this) {
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__cons__is_type(cause, iter)) {return f2larva__new(cause, 1, nil);}
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__string__is_type(cause, str)) {return f2larva__new(cause, 1, nil);}
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

f2ptr f2__stringlist__concat(f2ptr cause, f2ptr this) {
  return f2__stringlist__new_string_from_concatenation(cause, this);
}
def_pcfunk1(stringlist__concat, this, return f2__stringlist__concat(this_cause, this));

f2ptr f2__stringlist__intersperse(f2ptr cause, f2ptr this, f2ptr intersperse_string) {
  if (! raw__string__is_type(cause, intersperse_string)) {
    return f2larva__new(cause, 1, nil);
  }
  u64 intersperse_string__length = f2string__length(intersperse_string, cause);
  u8* intersperse_string__str    = malloc(intersperse_string__length + 1);
  f2string__str_copy(intersperse_string, cause, intersperse_string__str);
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__cons__is_type(cause, iter)) {return f2larva__new(cause, 1, nil);}
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__string__is_type(cause, str)) {return f2larva__new(cause, 1, nil);}
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
def_pcfunk2(stringlist__intersperse, this, intersperse_string, return f2__stringlist__intersperse(this_cause, this, intersperse_string));

f2ptr f2__stringlist__rawcode(f2ptr cause, f2ptr this) {
  return f2__stringlist__intersperse(cause, this, new__string(cause, "\n"));
}
def_pcfunk1(stringlist__rawcode, this, return f2__stringlist__rawcode(this_cause, this));

f2ptr f2__exp__as__string(f2ptr cause, f2ptr exp) {
  if (! exp) {
    return new__string(cause, "[]");
  }
  ptype_t ptype = f2ptype__raw(exp, cause);
  switch(ptype) {
  case ptype_free_memory:     return f2larva__new(cause, 1, nil);
  case ptype_newly_allocated: return f2larva__new(cause, 1, nil);
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
  case ptype_mutex: {
    char temp_str[1024];
    snprintf(temp_str, 1024, "<mutex " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, strlen(temp_str), (u8*)temp_str);
  }
  case ptype_char: {
    u8 temp_str[1024];
    u8 ch_value = f2char__ch(exp, cause);
    if (ch_value >= 28) {
      snprintf((char*)temp_str, 1024, "%c%c%c", (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_char, cause), (char)ch_value);
    } else {
      snprintf((char*)temp_str, 1024, "%c%c%X", (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_hex_char, cause), (uint)ch_value);
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
    temp_str[new_index] = f2char__ch(__funk2.reader.char__string_quote, cause);
    new_index ++;
    for (index = 0; index < exp__length; index ++) {
      u8 ch = temp_old_str[index];
      if (ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	temp_str[new_index] = f2char__ch(__funk2.reader.char__escape_char, cause);
	new_index ++;
      }
      temp_str[new_index] = ch;
      new_index ++;
    }
    temp_str[new_index] = f2char__ch(__funk2.reader.char__string_quote, cause);
    new_index ++;
    return f2string__new(cause, new_index, temp_str);
  } break;
  case ptype_symbol: {
    boolean_t all_cool = boolean__true;
    u64 exp__length = f2symbol__length(exp, cause);
    u8* temp_old_str = alloca(exp__length);
    f2symbol__str_copy(exp, cause, temp_old_str);
    u64 index;
    for (index = 0; index < exp__length; index ++) {
      u8 ch = temp_old_str[index];
      if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r' || ch == f2char__ch(__funk2.reader.char__left_paren, cause) || ch == f2char__ch(__funk2.reader.char__right_paren, cause) || ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) || ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	all_cool = boolean__false;
      }
    }
    if (all_cool) {
      return f2string__new(cause, exp__length, temp_old_str);
    } else {
      u64 new_index = 0;
      u8* temp_str = alloca(exp__length * 2);
      temp_str[new_index] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
      new_index ++;
      for (index = 0; index < exp__length; index ++) {
	u8 ch = temp_old_str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  temp_str[new_index] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  new_index ++;
	}
	temp_str[new_index] = ch;
	new_index ++;
      }
      temp_str[new_index] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
      new_index ++;
      return f2string__new(cause, new_index, temp_str);
    }
  } break;
  case ptype_chunk: {
    char temp_str[1024];
    snprintf(temp_str, 1024, "<chunk " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, strlen(temp_str), (u8*)temp_str);
  }
  case ptype_simple_array:
  case ptype_traced_array: {
    if (raw__cons__is_type(cause, exp)) {
      f2ptr stringlist = nil;
      {
	f2ptr stringlist_iter = nil;
	f2ptr iter            = exp;
	while (iter) {
	  f2ptr element = f2__cons__car(cause, iter);
	  f2ptr new_cons = f2cons__new(cause, f2__exp__as__string(cause, element), nil);
	  if (stringlist_iter) {
	    f2__cons__cdr__set(cause, stringlist_iter, new_cons);
	  } else {
	    stringlist = new_cons;
	  }
	  stringlist_iter = new_cons;
	  iter            = f2__cons__cdr(cause, iter);
	}
      }
      return f2__stringlist__concat(cause, f2list3__new(cause,
							new__string(cause, "["),
							f2__stringlist__intersperse(cause, stringlist, new__string(cause, " ")),
							new__string(cause, "]")));
    } else if (raw__frame__is_type(cause, exp)) {
      f2ptr stringlist = nil;
      {
	f2ptr stringlist_iter = nil;
	frame__var__iteration(cause, exp, slot_name, slot_value,
			      {
				f2ptr new_cons = f2cons__new(cause, f2__exp__as__string(cause, slot_name), nil);
				if (stringlist_iter) {
				  f2__cons__cdr__set(cause, stringlist_iter, new_cons);
				} else {
				  stringlist = new_cons;
				}
				stringlist_iter = new_cons;
			      }
			      {
				f2ptr new_cons = f2cons__new(cause, f2__exp__as__string(cause, slot_value), nil);
				if (stringlist_iter) {
				  f2__cons__cdr__set(cause, stringlist_iter, new_cons);
				} else {
				  stringlist = new_cons;
				}
				stringlist_iter = new_cons;
			      }
			      );
      }
      stringlist = f2cons__new(cause, new__string(cause, "frame"), stringlist);
      return f2__stringlist__concat(cause, f2list3__new(cause,
							new__string(cause, "["),
							f2__stringlist__intersperse(cause, stringlist, new__string(cause, " ")),
							new__string(cause, "]")));
    } else if (raw__list__is_type(cause, exp)) {
      f2ptr cons_cells = f2__list__cons_cells(cause, exp);
      return f2__exp__as__string(cause, cons_cells);
    } else {
      char temp_str[1024];
      snprintf(temp_str, 1024, "<array " pointer__fstr ">", to_ptr(exp));
      return f2string__new(cause, strlen(temp_str), (u8*)temp_str);
    }
  }
  case ptype_larva: {
    u8 temp_str[1024];
    u32 larva_type = f2larva__larva_type(exp, cause);
    snprintf((char*)temp_str, 1024, "%c%c" u32__fstr, (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_larva, cause), larva_type);
    return f2string__new(cause, strlen((char*)temp_str), temp_str);
  } break;
  }
  return f2larva__new(cause, 1, nil);
}
def_pcfunk1(exp__as__string, exp, return f2__exp__as__string(this_cause, exp));

f2ptr raw__string__as__symbol(f2ptr cause, f2ptr this) {
  u64 this__length = f2string__length(this, cause);
  u8* temp_str = alloca(this__length);
  f2string__str_copy(this, cause, temp_str);
  f2ptr new_symbol = f2symbol__new(cause, this__length, temp_str);
  return new_symbol;
}

f2ptr f2__string__as__symbol(f2ptr cause, f2ptr this) {
  if (! raw__string__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__string__as__symbol(cause, this);
}
def_pcfunk1(string__as__symbol, this, return f2__string__as__symbol(this_cause, this));

f2ptr f2__string__save(f2ptr cause, f2ptr this, f2ptr filename) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__string__is_type(cause, filename))) {
    return f2larva__new(cause, 1, nil);
  }
  u64 filename__length = f2string__length(filename, cause);
  u8* filename__str = alloca(filename__length + 1);
  f2string__str_copy(filename, cause, filename__str);
  filename__str[filename__length] = 0;
  int fd = open((char*)filename__str, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  if (fd == -1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_file"), new__symbol(cause, __FILE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line"), f2integer__new(cause, __LINE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"), filename);
    return f2larva__new(cause, 89, bug_frame);
  }
  u64 this__length = f2string__length(this, cause);
  u8* this__str = alloca(this__length);
  f2string__str_copy(this, cause, this__str);
  u64 write_bytes = write(fd, this__str, this__length);
  f2ptr result = nil;
  if (write_bytes != this__length) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),    new__symbol(cause, "could_not_write_to_file"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_file"), new__symbol(cause, __FILE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line"), f2integer__new(cause, __LINE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"),    filename);
    return f2larva__new(cause, 89, bug_frame);
  }
  close(fd);
  return result;
}
def_pcfunk2(string__save, this, filename, return f2__string__save(this_cause, this, filename));

f2ptr f2__string__load(f2ptr cause, f2ptr filename) {
  if (! raw__string__is_type(cause, filename)) {
    return f2larva__new(cause, 1, nil);
  }
  u64 filename__length = f2string__length(filename, cause);
  u8* filename__str = alloca(filename__length + 1);
  f2string__str_copy(filename, cause, filename__str);
  filename__str[filename__length] = 0;
  int fd = open((char*)filename__str, O_RDONLY);
  if (fd == -1) {
    return f2larva__new(cause, 90, nil);
  }
  u64 file__length = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  u8* file__str = (u8*)malloc(file__length);
  u64 read_length = read(fd, file__str, file__length);
  if (read_length != file__length) {
    printf("\nread_length=" u64__fstr ", file__length=" u64__fstr "\n", read_length, file__length);
    free(file__str);
    return f2larva__new(cause, 91, nil);
  }
  f2ptr new_string = f2string__new(cause, file__length, file__str);
  free(file__str);
  close(fd);
  return new_string;
}
def_pcfunk1(string__load, filename, return f2__string__load(this_cause, filename));

f2ptr f2__string__split(f2ptr cause, f2ptr this, f2ptr token) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__string__is_type(cause, token))) {
    return f2larva__new(cause, 1, nil);
  }
  u64 token__length = f2string__length(token, cause);
  u64 this__length  = f2string__length(this,  cause);
  if (token__length == 0) {
    return f2larva__new(cause, 93, nil);
  }
  if (token__length > this__length) {
    return f2larva__new(cause, 94, nil);
  }
  u8* token__str    = (u8*)malloc(token__length);
  f2string__str_copy(token, cause, token__str);
  
  u8* this__str = (u8*)malloc(this__length);
  f2string__str_copy(this, cause, this__str);
  
  f2ptr new_seq = nil;
  f2ptr iter    = nil;
  u64 last_match_index = 0;
  u64 index            = 0;
  u64 sup_index        = this__length - token__length + 1;
  while(index <= sup_index) {
    if (index == sup_index || memcmp(this__str + index, token__str, token__length) == 0) {
      u64 substr__length = index - last_match_index;
      f2ptr new_substr = f2string__new(cause, substr__length, this__str + last_match_index);
      f2ptr new_cons = f2cons__new(cause, new_substr, nil);
      if (iter == nil) {
	new_seq = new_cons;
      } else {
	f2cons__cdr__set(iter, cause, new_cons);
      }
      iter = new_cons;
      index += token__length;
      last_match_index = index;
    } else {
      index ++;
    }
  }
  return new_seq;
}
def_pcfunk2(string__split, this, token, return f2__string__split(this_cause, this, token));

boolean_t raw__string__contains(f2ptr cause, f2ptr this, f2ptr substring) {
  u64 substring__length = f2string__length(substring, cause);
  u64 this__length      = f2string__length(this,      cause);
  if (substring__length == 0) {
    return boolean__true;
  }
  if (substring__length > this__length) {
    return boolean__false;
  }
  u8* substring__str = (u8*)malloc(substring__length);
  f2string__str_copy(substring, cause, substring__str);
  
  u8* this__str = (u8*)malloc(this__length);
  f2string__str_copy(this, cause, this__str);
  
  u64 index;
  u64 sup_index = this__length - substring__length + 1;
  for (index = 0; index <= sup_index; index ++) {
    if (memcmp(this__str + index, substring__str, substring__length) == 0) {
      return boolean__true;
    }
  }
  return boolean__false;
}

f2ptr f2__string__contains(f2ptr cause, f2ptr this, f2ptr substring) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__string__is_type(cause, substring))) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__string__contains(cause, this, substring));
}
def_pcfunk2(string__contains, this, substring, return f2__string__contains(this_cause, this, substring));

f2ptr f2__string__replace_all(f2ptr cause, f2ptr this, f2ptr token, f2ptr replacement) {
  return f2__stringlist__intersperse(cause, f2__string__split(cause, this, token), replacement);
}
def_pcfunk3(string__replace_all, this, token, replacement, return f2__string__replace_all(this_cause, this, token, replacement));

f2ptr f2string__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2string__primobject_type__new(cause);
  {char* slot_name = "as-symbol"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.as__symbol__funk);}
  {char* slot_name = "save";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.save__funk);}
  {char* slot_name = "split";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.split__funk);}
  {char* slot_name = "contains";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.contains__funk);}
  return this;
}

// **

void f2__string__reinitialize_globalvars() {
}

void f2__string__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "string", "", &f2__string__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__1(stringlist__concat,      this,                     "concatenate a list of strings together into a new resultant string.");
  f2__primcfunk__init__2(stringlist__intersperse, this, intersperse_string, "concatenate a list of strings together into a new resultant string with a extra token string placed between each of the strings.");
  f2__primcfunk__init__1(stringlist__rawcode,     this,                     "concatenate a list of strings separated by newlines ('\\n').");
  
  f2__primcfunk__init__1(exp__as__string, exp, "take any funk2 expression and turn this into a new string that can be read back into an equal expression by using string-read.");
  
  f2__primcfunk__init__1(string__load,        filename,                 "load a string from a filename");
  f2__primcfunk__init__3(string__replace_all, this, token, replacement, "replaces all occurrances of token in this with replacement.");
  
  {char* str = "as-symbol"; __funk2.globalenv.object_type.ptype.ptype_string.as__symbol__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__as__symbol, this, cfunk, 1, "convert a string to a symbol."); __funk2.globalenv.object_type.ptype.ptype_string.as__symbol__funk = never_gc(cfunk);}
  {char* str = "save"; __funk2.globalenv.object_type.ptype.ptype_string.save__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__save, this, filename, cfunk, 1, "save this string to a file of filename."); __funk2.globalenv.object_type.ptype.ptype_string.save__funk = never_gc(cfunk);}
  {char* str = "split"; __funk2.globalenv.object_type.ptype.ptype_string.split__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__split, this, token, cfunk, 1, "split a string into a list of strings (a stringlist).  this function is the inverse of stringlist-intersperse."); __funk2.globalenv.object_type.ptype.ptype_string.split__funk = never_gc(cfunk);}
  {char* str = "contains"; __funk2.globalenv.object_type.ptype.ptype_string.contains__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__contains, this, substring, cfunk, 1, "returns true when the string contains the specified substring."); __funk2.globalenv.object_type.ptype.ptype_string.contains__funk = never_gc(cfunk);}
  
  //f2__primcfunk__init__1(string__to_symbol, this, "convert any string to a new symbol.  for any two strings that are equal, the symbols returned by this function will be eq.");
  //f2__primcfunk__init__2(string__save, this, filename, "save a string to a filename");
  //f2__primcfunk__init__2(string__split, this, token, "split a string into a list of strings (a stringlist).  this function is the inverse of stringlist-intersperse.");
  //f2__primcfunk__init__2(string__contains, this, substring, "returns true when the string contains the specified substring.");
}


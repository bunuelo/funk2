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

boolean_t raw__stringlist__is_type(f2ptr cause, f2ptr object) {
  f2ptr iter = object;
  while (iter != nil) {
    if (! raw__cons__is_type(cause, iter)) {
      return boolean__false;
    }
    f2ptr element = f2cons__car(iter, cause);
    if (! raw__string__is_type(cause, element)) {
      return boolean__false;
    }
    iter = f2cons__cdr(iter, cause);
  }
  return boolean__true;
}


f2ptr raw__stringlist__new_string_from_concatenation(f2ptr cause, f2ptr this) {
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__cons__is_type(cause, iter)) {
	error(nil, "raw__stringlist__new_string_from_concatenation error: expected cons.");
      }
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__string__is_type(cause, str)) {
	error(nil, "raw__stringlist__new_string_from_concatenation error: expected string.");
      }
      u64 str_length = f2string__length(str, cause);
      total_length += str_length;
      iter = f2cons__cdr(iter, cause);
    }
  }
  funk2_character_t* temp_str = (funk2_character_t*)from_ptr(f2__malloc((total_length + 1) * sizeof(funk2_character_t)));
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
  f2__free(to_ptr(temp_str));
  return new_string;
}

f2ptr f2__stringlist__new_string_from_concatenation(f2ptr cause, f2ptr this) {
  assert_argument_type(stringlist, this);
  return raw__stringlist__new_string_from_concatenation(cause, this);
}

f2ptr f2__stringlist__concat(f2ptr cause, f2ptr this) {
  return f2__stringlist__new_string_from_concatenation(cause, this);
}
def_pcfunk1(stringlist__concat, this,
	    "concatenate a list of strings together into a new resultant string.checks for the return value for a finished system command started by this fiber.",
	    return f2__stringlist__concat(this_cause, this));

f2ptr raw__stringlist__intersperse(f2ptr cause, f2ptr this, f2ptr intersperse_string) {
  u64                intersperse_string__length = f2string__length(intersperse_string, cause);
  funk2_character_t* intersperse_string__str    = (funk2_character_t*)from_ptr(f2__malloc((intersperse_string__length + 1) * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, intersperse_string, intersperse_string__str);
  u64 total_length = 0;
  {
    f2ptr iter = this;
    while (iter) {
      if (! raw__cons__is_type(cause, iter)) {
	error(nil, "raw__stringlist__intersperse error: iter is not cons.");
      }
      f2ptr str = f2cons__car(iter, cause);
      if (! raw__string__is_type(cause, str)) {
	error(nil, "raw__stringlist__intersperse error: str is not string.");
      }
      u64 str_length = f2string__length(str, cause);
      total_length += str_length;
      iter = f2cons__cdr(iter, cause);
      if (iter) {
	total_length += intersperse_string__length;
      }
    }
  }
  funk2_character_t* temp_str = (funk2_character_t*)from_ptr(f2__malloc((total_length + 1) * sizeof(funk2_character_t)));
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
	memcpy(temp_str + index, intersperse_string__str, intersperse_string__length * sizeof(funk2_character_t));
	index += intersperse_string__length;
      }
    }
  }
  f2ptr new_string = f2string__new(cause, total_length, temp_str);
  f2__free(to_ptr(temp_str));
  f2__free(to_ptr(intersperse_string__str));
  return new_string;
}

f2ptr f2__stringlist__intersperse(f2ptr cause, f2ptr this, f2ptr intersperse_string) {
  assert_argument_type(stringlist, this);
  assert_argument_type(string,     intersperse_string);
  return raw__stringlist__intersperse(cause, this, intersperse_string);
}
def_pcfunk2(stringlist__intersperse, this, intersperse_string,
	    "concatenate a list of strings together into a new resultant string with a extra token string placed between each of the strings.",
	    return f2__stringlist__intersperse(this_cause, this, intersperse_string));

f2ptr f2__stringlist__rawcode(f2ptr cause, f2ptr this) {
  return f2__stringlist__intersperse(cause, this, new__string(cause, "\n"));
}
def_pcfunk1(stringlist__rawcode, this,
	    "concatenate a list of strings separated by newlines ('\\n').",
	    return f2__stringlist__rawcode(this_cause, this));


f2ptr f2__exp__as__string__with_hash(f2ptr cause, f2ptr exp, f2ptr element_hash) {
  assert_argument_type(ptypehash, element_hash);
  if (raw__array__is_type(cause, exp) && raw__ptypehash__contains(cause, element_hash, exp)) {
    return new__string(cause, "<>");
  }
  f2__ptypehash__add(cause, element_hash, exp, exp);
  if (! exp) {
    return new__string(cause, "[]");
  }
  ptype_t ptype = f2ptype__raw(exp, cause);
  switch(ptype) {
  case ptype_free_memory:     return f2larva__new(cause, 32551, nil);
  case ptype_newly_allocated: return f2larva__new(cause, 53241, nil);
  case ptype_integer: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, s64__fstr, f2integer__i(exp, cause));
    return f2string__new(cause, temp_str__length, temp_str);
  } break;
  case ptype_double: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, double__fstr, f2double__d(exp, cause));
    return f2string__new(cause, temp_str__length, temp_str);
  } break;
  case ptype_float: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, float__fstr, f2float__f(exp, cause));
    return f2string__new(cause, temp_str__length, temp_str);
  } break;
  case ptype_pointer: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, pointer__fstr, f2pointer__p(exp, cause));
    return f2string__new(cause, temp_str__length, temp_str);
  } break;
  case ptype_scheduler_cmutex: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "<scheduler_cmutex " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, temp_str__length, temp_str);
  }
  case ptype_cmutex: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "<cmutex " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, temp_str__length, temp_str);
  }
  case ptype_scheduler_creadwritelock: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "<scheduler_creadwritelock " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, temp_str__length, temp_str);
  }
  case ptype_creadwritelock: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "<creadwritelock " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, temp_str__length, temp_str);
  }
  case ptype_char: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length;
    funk2_character_t ch_value = f2char__ch(exp, cause);
    if (ch_value >= 28) {
      temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "%c%c%c", (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_char, cause), (char)ch_value);
    } else {
      temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "%c%c%X", (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_hex_char, cause), (uint)ch_value);
    }
    return f2string__new(cause, temp_str__length, temp_str);
  } break;
  case ptype_string: {
    u64                exp__length  = f2string__length(exp, cause);
    funk2_character_t* temp_old_str = (funk2_character_t*)from_ptr(f2__malloc(exp__length * sizeof(funk2_character_t)));
    f2string__str_copy(exp, cause, temp_old_str);
    funk2_character_t* temp_str     = (funk2_character_t*)from_ptr(f2__malloc((exp__length * 2) * sizeof(funk2_character_t)));
    u64 index;
    u64 new_index = 0;
    temp_str[new_index] = f2char__ch(__funk2.reader.char__string_quote, cause);
    new_index ++;
    for (index = 0; index < exp__length; index ++) {
      funk2_character_t ch = temp_old_str[index];
      if (ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	temp_str[new_index] = f2char__ch(__funk2.reader.char__escape_char, cause);
	new_index ++;
      }
      temp_str[new_index] = ch;
      new_index ++;
    }
    temp_str[new_index] = f2char__ch(__funk2.reader.char__string_quote, cause);
    new_index ++;
    f2ptr new_string = f2string__new(cause, new_index, temp_str);
    f2__free(to_ptr(temp_old_str));
    f2__free(to_ptr(temp_str));
    return new_string;
  } break;
  case ptype_symbol: {
    boolean_t all_cool = boolean__true;
    u64 exp__length = f2symbol__length(exp, cause);
    funk2_character_t* temp_old_str = (funk2_character_t*)from_ptr(f2__malloc(exp__length * sizeof(funk2_character_t)));
    f2symbol__str_copy(exp, cause, temp_old_str);
    u64 index;
    for (index = 0; index < exp__length; index ++) {
      funk2_character_t ch = temp_old_str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	all_cool = boolean__false;
      }
    }
    if (all_cool) {
      f2ptr new_string = f2string__new(cause, exp__length, temp_old_str);
      f2__free(to_ptr(temp_old_str));
      return new_string;
    } else {
      u64 new_index = 0;
      funk2_character_t* temp_str = (funk2_character_t*)from_ptr(f2__malloc((exp__length * 2) * sizeof(funk2_character_t)));
      temp_str[new_index] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
      new_index ++;
      for (index = 0; index < exp__length; index ++) {
	funk2_character_t ch = temp_old_str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  temp_str[new_index] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  new_index ++;
	}
	temp_str[new_index] = ch;
	new_index ++;
      }
      temp_str[new_index] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
      new_index ++;
      f2ptr new_string = f2string__new(cause, new_index, temp_str);
      f2__free(to_ptr(temp_str));
      f2__free(to_ptr(temp_old_str));
      return new_string;
    }
  } break;
  case ptype_chunk: {
    funk2_character_t temp_str[1024];
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "<chunk " pointer__fstr ">", to_ptr(exp));
    return f2string__new(cause, temp_str__length, temp_str);
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
	  f2ptr new_cons = raw__cons__new(cause, f2__exp__as__string__with_hash(cause, element, element_hash), nil);
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
				f2ptr new_cons = raw__cons__new(cause, f2__exp__as__string__with_hash(cause, slot_name, element_hash), nil);
				if (stringlist_iter) {
				  f2__cons__cdr__set(cause, stringlist_iter, new_cons);
				} else {
				  stringlist = new_cons;
				}
				stringlist_iter = new_cons;
			      }
			      {
				f2ptr new_cons = raw__cons__new(cause, f2__exp__as__string__with_hash(cause, slot_value, element_hash), nil);
				if (stringlist_iter) {
				  f2__cons__cdr__set(cause, stringlist_iter, new_cons);
				} else {
				  stringlist = new_cons;
				}
				stringlist_iter = new_cons;
			      }
			      );
      }
      stringlist = raw__cons__new(cause, new__string(cause, "frame"), stringlist);
      return f2__stringlist__concat(cause, f2list3__new(cause,
							new__string(cause, "["),
							f2__stringlist__intersperse(cause, stringlist, new__string(cause, " ")),
							new__string(cause, "]")));
    } else if (raw__list__is_type(cause, exp)) {
      f2ptr cons_cells = f2__list__cons_cells(cause, exp);
      return f2__exp__as__string__with_hash(cause, cons_cells, element_hash);
    } else {
      funk2_character_t temp_str[1024];
      u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "<array " pointer__fstr ">", to_ptr(exp));
      return f2string__new(cause, temp_str__length, temp_str);
    }
  }
  case ptype_larva: {
    funk2_character_t temp_str[1024];
    u32 larva_type = f2larva__larva_type(exp, cause);
    u64               temp_str__length = funk2_character_string__snprintf(temp_str, 1024, "%c%c" u32__fstr, (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_larva, cause), larva_type);
    return f2string__new(cause, temp_str__length, temp_str);
  } break;
  }
  return f2larva__new(cause, 23511, nil);
}

f2ptr f2__exp__as__string(f2ptr cause, f2ptr exp) {
  return f2__exp__as__string__with_hash(cause, exp, f2__ptypehash__new(cause));
}
def_pcfunk1(exp__as__string, exp,
	    "take any funk2 expression and turn this into a new string that can be read back into an equal expression by using string-read.",
	    return f2__exp__as__string(this_cause, exp));

f2ptr raw__string__as__symbol(f2ptr cause, f2ptr this) {
  u64                this__length = f2string__length(this, cause);
  funk2_character_t* temp_str     = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  f2string__str_copy(this, cause, temp_str);
  f2ptr new_symbol = f2symbol__new(cause, this__length, temp_str);
  f2__free(to_ptr(temp_str));
  return new_symbol;
}

f2ptr f2__string__as__symbol(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__string__as__symbol(cause, this);
}
def_pcfunk1(string__as__symbol, this,
	    "convert a string to a symbol.",
	    return f2__string__as__symbol(this_cause, this));

f2ptr raw__string__save(f2ptr cause, f2ptr this, f2ptr filename) {
  int fd;
  {
    u64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    
    fd = open((char*)filename__utf8_str, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    f2__free(to_ptr(filename__utf8_str));
  }
  if (fd == -1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_file"), new__string(cause, __FILE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line"), f2integer__new(cause, __LINE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"), filename);
    return f2larva__new(cause, 89, f2__bug__new(cause, f2integer__new(cause, 89), bug_frame));
  }
  u64 write_bytes;
  u64 this__utf8_length = raw__string__utf8_length(cause, this);
  {
    u8* this__utf8_str = (u8*)from_ptr(f2__malloc(this__utf8_length));
    raw__string__utf8_str_copy(cause, this, this__utf8_str);
    
    write_bytes = write(fd, this__utf8_str, this__utf8_length);
    
    f2__free(to_ptr(this__utf8_str));
  }
  f2ptr result = nil;
  if (write_bytes != this__utf8_length) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),    new__symbol(cause, "could_not_write_to_file"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_file"), new__string(cause, __FILE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line"), f2integer__new(cause, __LINE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"),    filename);
    return f2larva__new(cause, 89, f2__bug__new(cause, f2integer__new(cause, 89), bug_frame));
  }
  close(fd);
  return result;
}

f2ptr f2__string__save(f2ptr cause, f2ptr this, f2ptr filename) {
  assert_argument_type(string, this);
  assert_argument_type(string, filename);
  return raw__string__save(cause, this, filename);
}
def_pcfunk2(string__save, this, filename,
	    "save this string to a file of filename.",
	    return f2__string__save(this_cause, this, filename));


f2ptr raw__string__load(f2ptr cause, f2ptr filename) {
  int fd;
  {
    u64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    
    fd = open((char*)filename__utf8_str, O_RDONLY);
    
    f2__free(to_ptr(filename__utf8_str));
  }
  if (fd == -1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file_for_reading"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "string-load"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"), filename);
    return f2larva__new(cause, 90, f2__bug__new(cause, f2integer__new(cause, 90), bug_frame));
  }
  u64 file__utf8_length = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  u8* file__utf8_str = (u8*)from_ptr(f2__malloc(file__utf8_length + 1));
  u64 read_length = read(fd, file__utf8_str, file__utf8_length);
  if (read_length != file__utf8_length) {
    printf("\nread_length=" u64__fstr ", file__utf8_length=" u64__fstr "\n", read_length, file__utf8_length);
    f2__free(to_ptr(file__utf8_str));
    {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),         new__symbol(cause, "could_not_read_complete_file"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),         new__symbol(cause, "string-load"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"),         filename);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "read_length"),      f2integer__new(cause, read_length));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "file_utf8_length"), f2integer__new(cause, file__utf8_length));
      return f2larva__new(cause, 91, f2__bug__new(cause, f2integer__new(cause, 91), bug_frame));
    }
  }
  file__utf8_str[file__utf8_length] = 0;
  f2ptr new_string = raw__string__new_from_utf8(cause, (char*)file__utf8_str);
  f2__free(to_ptr(file__utf8_str));
  close(fd);
  return new_string;
}

f2ptr f2__string__load(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  return raw__string__load(cause, filename);
}
def_pcfunk1(string__load, filename,
	    "load a string from a filename",
	    return f2__string__load(this_cause, filename));


f2ptr f2__string__split(f2ptr cause, f2ptr this, f2ptr token) {
  assert_argument_type(string, this);
  assert_argument_type(string, token);
  s64 this__length  = raw__string__length(cause, this);
  s64 token__length = raw__string__length(cause, token);
  if (token__length == 0) {
    return f2larva__new(cause, 93, nil);
  }
  funk2_character_t* token__str = (funk2_character_t*)from_ptr(f2__malloc(token__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, token, token__str);
  
  funk2_character_t* this__str = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, this__str);
  
  f2ptr new_seq                 = nil;
  f2ptr iter                    = nil;
  s64   end_of_last_match_index = 0;
  s64   index                   = 0;
  s64   sup_index               = this__length - token__length + 1;
  while (index < sup_index) {
    if ((index < 0) || ((index + token__length) > this__length)) {
      error(nil, "\nstring-split assert failed.\n");
    }
    if (memcmp(this__str + index, token__str, token__length * sizeof(funk2_character_t)) == 0) {
      s64 substr__length = index - end_of_last_match_index;
      if ((end_of_last_match_index + substr__length) > this__length) {
	error(nil, "\nstring-split assert failed.\n");
      }
      f2ptr new_substr     = f2string__new(cause, substr__length, this__str + end_of_last_match_index);
      f2ptr new_cons       = raw__cons__new(cause, new_substr, nil);
      if (iter == nil) {
	new_seq = new_cons;
      } else {
	f2__cons__cdr__set(cause, iter, new_cons);
      }
      iter = new_cons;
      index += token__length;
      end_of_last_match_index = index;
    } else {
      index ++;
    }
  }
  {
    s64 substr__length = this__length - end_of_last_match_index;
    if ((end_of_last_match_index + substr__length) > this__length) {
      error(nil, "\nstring-split assert failed.\n");
    }
    f2ptr new_substr = f2string__new(cause, substr__length, this__str + end_of_last_match_index);
    f2ptr new_cons   = raw__cons__new(cause, new_substr, nil);
    if (iter == nil) {
      new_seq = new_cons;
    } else {
      f2__cons__cdr__set(cause, iter, new_cons);
    }
  }
  
  f2__free(to_ptr(this__str));
  f2__free(to_ptr(token__str));
  return new_seq;
}
def_pcfunk2(string__split, this, token,
	    "split a string into a list of strings (a stringlist).  this function is the inverse of stringlist-intersperse.",
	    return f2__string__split(this_cause, this, token));

boolean_t raw__string__contains(f2ptr cause, f2ptr this, f2ptr substring) {
  u64 substring__length = raw__string__length(cause, substring);
  u64 this__length      = raw__string__length(cause, this);
  if (substring__length == 0) {
    return boolean__true;
  }
  if (substring__length > this__length) {
    return boolean__false;
  }
  funk2_character_t* substring__str = (funk2_character_t*)from_ptr(f2__malloc(substring__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, substring, substring__str);
  
  funk2_character_t* this__str = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, this__str);
  
  boolean_t found_substring = boolean__false;
  {
    u64 index;
    u64 sup_index = this__length - substring__length + 1;
    for (index = 0; index <= sup_index; index ++) {
      if (memcmp(this__str + index, substring__str, substring__length) == 0) {
	found_substring = boolean__true;
	break;
      }
    }
  }
  
  f2__free(to_ptr(substring__str));
  f2__free(to_ptr(this__str));
  return found_substring;
}

f2ptr f2__string__contains(f2ptr cause, f2ptr this, f2ptr substring) {
  assert_argument_type(string, this);
  assert_argument_type(string, substring);
  return f2bool__new(raw__string__contains(cause, this, substring));
}
def_pcfunk2(string__contains, this, substring,
	    "returns true when the string contains the specified substring.",
	    return f2__string__contains(this_cause, this, substring));

f2ptr f2__string__replace_all(f2ptr cause, f2ptr this, f2ptr token, f2ptr replacement) {
  return f2__stringlist__intersperse(cause, f2__string__split(cause, this, token), replacement);
}
def_pcfunk3(string__replace_all, this, token, replacement,
	    "replaces all occurrances of token in this with replacement.",
	    return f2__string__replace_all(this_cause, this, token, replacement));


f2ptr raw__string__substring(f2ptr cause, f2ptr this, s64 start_index, s64 end_index) {
  if ((start_index < 0) || (end_index < 0)) {
    return f2larva__new(cause, 2, nil);
  }
  f2ptr substring;
  {
    u64                this__length = raw__string__length(cause, this);
    funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc((this__length + 1) * sizeof(funk2_character_t)));
    raw__string__str_copy(cause, this, this__str);
    this__str[this__length] = 0;
    if (start_index > end_index) {
      substring = f2larva__new(cause, 3, nil);
    } else if (end_index > this__length) {
      substring = f2larva__new(cause, 2, nil);
    } else {
      substring = f2string__new(cause, end_index - start_index, this__str + start_index);
    }
    f2__free(to_ptr(this__str));
  }
  return substring;
}

f2ptr f2__string__substring(f2ptr cause, f2ptr this, f2ptr start_index, f2ptr end_index) {
  assert_argument_type(string, this);
  assert_argument_type(integer, start_index);
  assert_argument_type(integer, end_index);
  s64 start_index__i = f2integer__i(start_index, cause);
  s64 end_index__i   = f2integer__i(end_index,   cause);
  return raw__string__substring(cause, this, start_index__i, end_index__i);
}
def_pcfunk3(string__substring, this, start_index, end_index,
	    "returns the substring between the given start and end indices.",
	    return f2__string__substring(this_cause, this, start_index, end_index));


boolean_t raw__string__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__string__is_type(cause, this))) {
    error(nil, "raw__string__is_greater_than error: either this or that is not of type string.");
  }
  int comparison;
  u64 this__length = raw__string__length(cause, this);
  u64 that__length = raw__string__length(cause, that);
  {
    funk2_character_t* this__str = (funk2_character_t*)from_ptr(f2__malloc((this__length + 1) * sizeof(funk2_character_t)));
    raw__string__str_copy(cause, this, this__str);
    this__str[this__length] = 0;
    
    funk2_character_t* that__str = (funk2_character_t*)from_ptr(f2__malloc((that__length + 1) * sizeof(funk2_character_t)));
    raw__string__str_copy(cause, that, that__str);
    that__str[that__length] = 0;
    
    comparison = memcmp(this__str, that__str, ((this__length < that__length) ? this__length : that__length) * sizeof(funk2_character_t));
    
    f2__free(to_ptr(this__str));
    f2__free(to_ptr(that__str));
  }
  
  if (comparison < 0) {
    return boolean__true;
  }
  if (comparison > 0) {
    return boolean__false;
  }
  if (this__length < that__length) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__string__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  assert_argument_type(string, that);
  return f2bool__new(raw__string__is_less_than(cause, this, that));
}
def_pcfunk2(string__is_less_than, this, that,
	    "returns true when this string is_less_than that string.",
	    return f2__string__is_less_than(this_cause, this, that));

boolean_t raw__string__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__string__is_type(cause, this))) {
    error(nil, "raw__string__is_greater_than error: either this or that is not of type string.");
  }
  int comparison;
  u64 this__length = raw__string__length(cause, this);
  u64 that__length = raw__string__length(cause, that);
  {
    funk2_character_t* this__str = (funk2_character_t*)from_ptr(f2__malloc((this__length + 1) * sizeof(funk2_character_t)));
    raw__string__str_copy(cause, this, this__str);
    this__str[this__length] = 0;
    
    funk2_character_t* that__str = (funk2_character_t*)from_ptr(f2__malloc((that__length + 1) * sizeof(funk2_character_t)));
    raw__string__str_copy(cause, that, that__str);
    that__str[that__length] = 0;
    
    comparison = memcmp(this__str, that__str, ((this__length < that__length) ? this__length : that__length) * sizeof(funk2_character_t));
    
    f2__free(to_ptr(this__str));
    f2__free(to_ptr(that__str));
  }
  
  if (comparison < 0) {
    return boolean__false;
  }
  if (comparison > 0) {
    return boolean__true;
  }
  if (this__length > that__length) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__string__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  assert_argument_type(string, that);
  return f2bool__new(raw__string__is_greater_than(cause, this, that));
}
def_pcfunk2(string__is_greater_than, this, that,
	    "returns true when this string is_greater_than that string.",
	    return f2__string__is_greater_than(this_cause, this, that));


f2ptr raw__string__lowercase(f2ptr cause, f2ptr this) {
  s64                this__length = raw__string__length(cause, this);
  funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc((this__length + 1) * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;
  
  s64                new_string__length = this__length;
  funk2_character_t* new_string__str    = (funk2_character_t*)from_ptr(f2__malloc((new_string__length + 1) * sizeof(funk2_character_t)));
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      funk2_character_t ch     = this__str[index];
      funk2_character_t new_ch = 0;
      if (ch >= (funk2_character_t)'A' &&
	  ch <= (funk2_character_t)'Z') {
	new_ch = ch - (funk2_character_t)'A' + (funk2_character_t)'a';
      } else {
	new_ch = ch;
      }
      new_string__str[index] = new_ch;
    }
  }
  new_string__str[new_string__length] = 0;
  f2ptr new_string = f2string__new(cause, new_string__length, new_string__str);
  f2__free(to_ptr(this__str));
  f2__free(to_ptr(new_string__str));
  return new_string;
}

f2ptr f2__string__lowercase(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__string__lowercase(cause, this);
}
def_pcfunk1(string__lowercase, this,
	    "returns a new string that represents the lowercased version of this string.",
	    return f2__string__lowercase(this_cause, this));


f2ptr raw__string__uppercase(f2ptr cause, f2ptr this) {
  s64                this__length = raw__string__length(cause, this);
  funk2_character_t* this__str    = (funk2_character_t*)from_ptr(f2__malloc((this__length + 1) * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;
  
  s64                new_string__length = this__length;
  funk2_character_t* new_string__str    = (funk2_character_t*)from_ptr(f2__malloc((new_string__length + 1) * sizeof(funk2_character_t)));
  {
    s64 index;
    for (index = 0; index < this__length; index ++) {
      funk2_character_t ch     = this__str[index];
      funk2_character_t new_ch = 0;
      if (ch >= (funk2_character_t)'a' &&
	  ch <= (funk2_character_t)'z') {
	new_ch = ch - (funk2_character_t)'a' + (funk2_character_t)'A';
      } else {
	new_ch = ch;
      }
      new_string__str[index] = new_ch;
    }
  }
  new_string__str[new_string__length] = 0;
  f2ptr new_string = f2string__new(cause, new_string__length, new_string__str);
  f2__free(to_ptr(this__str));
  f2__free(to_ptr(new_string__str));
  return new_string;
}

f2ptr f2__string__uppercase(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__string__uppercase(cause, this);
}
def_pcfunk1(string__uppercase, this,
	    "returns a new string that represents the uppercased version of this string.",
	    return f2__string__uppercase(this_cause, this));


f2ptr raw__string__multiply(f2ptr cause, f2ptr this, s64 num) {
  if (num < 0) {
    return f2larva__new(cause, 34634, nil);
  }
  s64                this__length   = raw__string__length(cause, this);
  funk2_character_t* this__str      = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (this__length + 1)));
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;
  s64                result__length = this__length * num;
  funk2_character_t* result__str    = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (result__length + 1)));
  {
    s64 i;
    for (i = 0; i < num; i ++) {
      memcpy(result__str + (i * this__length), this__str, sizeof(funk2_character_t) * this__length);
    }
  }
  result__str[result__length] = 0;
  f2ptr result = f2string__new(cause, result__length, result__str);
  f2__free(to_ptr(this__str));
  f2__free(to_ptr(result__str));
  return result;
}

f2ptr f2__string__multiply(f2ptr cause, f2ptr this, f2ptr num) {
  assert_argument_type(string,  this);
  assert_argument_type(integer, num);
  s64 num__i = f2integer__i(num, cause);
  return raw__string__multiply(cause, this, num__i);
}
def_pcfunk2(string__multiply, this, num,
	    "Returns a new string that is the given number of times copied and concatenated of the original string.",
	    return f2__string__multiply(this_cause, this, num));


f2ptr f2string__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2string__primobject_type__new(cause);
  {char* slot_name = "as-symbol";       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.as__symbol__funk);}
  {char* slot_name = "save";            f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.save__funk);}
  {char* slot_name = "split";           f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.split__funk);}
  {char* slot_name = "contains";        f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.contains__funk);}
  {char* slot_name = "substring";       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.substring__funk);}
  {char* slot_name = "is_less_than";    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.is_less_than__funk);}
  {char* slot_name = "is_greater_than"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.is_greater_than__funk);}
  {char* slot_name = "lowercase";       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.lowercase__funk);}
  {char* slot_name = "uppercase";       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.uppercase__funk);}
  {char* slot_name = "multiply";        f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.multiply__funk);}
  return this;
}

// **

void f2__string__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --

  f2__primcfunk__init__defragment__fix_pointers(stringlist__concat);
  f2__primcfunk__init__defragment__fix_pointers(stringlist__intersperse);
  f2__primcfunk__init__defragment__fix_pointers(stringlist__rawcode);
  
  f2__primcfunk__init__defragment__fix_pointers(exp__as__string);
  
  f2__primcfunk__init__defragment__fix_pointers(string__load);
  f2__primcfunk__init__defragment__fix_pointers(string__replace_all);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.as__symbol__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__as__symbol);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.as__symbol__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.save__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__save);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.save__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.split__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__split);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.split__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.contains__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__contains);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.contains__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.substring__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__substring);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.substring__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.is_less_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__is_less_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.is_less_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.is_greater_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__is_greater_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.is_greater_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.lowercase__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__lowercase);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.lowercase__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.uppercase__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__uppercase);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.uppercase__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.multiply__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__multiply);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.multiply__funk);
}

void f2__string__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  f2__primcfunk__init__1(stringlist__concat,      this);
  f2__primcfunk__init__2(stringlist__intersperse, this, intersperse_string);
  f2__primcfunk__init__1(stringlist__rawcode,     this);
  
  f2__primcfunk__init__1(exp__as__string, exp);
  
  f2__primcfunk__init__1(string__load,        filename);
  f2__primcfunk__init__3(string__replace_all, this, token, replacement);
  
  {char* str = "as-symbol"; __funk2.globalenv.object_type.ptype.ptype_string.as__symbol__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__as__symbol, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.as__symbol__funk = never_gc(cfunk);}
  {char* str = "save"; __funk2.globalenv.object_type.ptype.ptype_string.save__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__save, this, filename, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.save__funk = never_gc(cfunk);}
  {char* str = "split"; __funk2.globalenv.object_type.ptype.ptype_string.split__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__split, this, token, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.split__funk = never_gc(cfunk);}
  {char* str = "contains"; __funk2.globalenv.object_type.ptype.ptype_string.contains__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__contains, this, substring, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.contains__funk = never_gc(cfunk);}
  {char* str = "substring"; __funk2.globalenv.object_type.ptype.ptype_string.substring__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(string__substring, this, start_index, end_index, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.substring__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_string.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_string.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "lowercase"; __funk2.globalenv.object_type.ptype.ptype_string.lowercase__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__lowercase, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.lowercase__funk = never_gc(cfunk);}
  {char* str = "uppercase"; __funk2.globalenv.object_type.ptype.ptype_string.uppercase__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__uppercase, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.uppercase__funk = never_gc(cfunk);}
  {char* str = "multiply"; __funk2.globalenv.object_type.ptype.ptype_string.multiply__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__multiply, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.multiply__funk = never_gc(cfunk);}
}

void f2__string__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "string", "", &f2__string__reinitialize_globalvars, &f2__string__defragment__fix_pointers);
  
  f2__string__reinitialize_globalvars();
}


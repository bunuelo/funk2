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

#include "keyboard.h"


def_ceframe1(keyboard, termios, chunk);

f2ptr raw__termios__new(f2ptr cause, f2ptr chunk) {
  return f2termios__new(cause, chunk);
}

f2ptr f2__termios__new(f2ptr cause, f2ptr chunk) {
  assert_argument_type(chunk, chunk);
  return raw__termios__new(cause, chunk);
}
export_cefunk1(termios__new, chunk, 0, "Return a new termios object.");


f2ptr raw__termios__new_from_c_struct(f2ptr cause, struct termios* opts) {
  return raw__termios__new(cause, f2chunk__new(cause, sizeof(*opts), (u8*)opts));
}

void raw__termios__c_struct_copy(f2ptr cause, f2ptr this, struct termios* dest) {
  f2ptr chunk = raw__termios__chunk(cause, this);
  raw__chunk__str_copy(cause, chunk, (u8*)dest);
}

f2ptr f2__termios_type__new_aux(f2ptr cause) {
  f2ptr this = f2__termios_type__new(cause);
  return this;
}



f2ptr f2__keyboard__current_mode(f2ptr cause) {
  struct termios opts;
  int res = tcgetattr(STDIN_FILENO, &opts);
  if (res != 0) {
    return f2larva__new(cause, 12351, nil);
  }
  return raw__termios__new_from_c_struct(cause, &opts);
}
export_cefunk0(keyboard__current_mode, 0, "Return a termios struct containing the current standard input device attributes.");


f2ptr raw__keyboard__current_mode__set(f2ptr cause, f2ptr termios) {
  struct termios opts;
  raw__termios__c_struct_copy(cause, termios, &opts);
  int res = tcsetattr(STDIN_FILENO, TCSANOW, &opts);
  if (res != 0) {
    return f2larva__new(cause, 12353, nil);
  }
  return nil;
}

f2ptr f2__keyboard__current_mode__set(f2ptr cause, f2ptr termios) {
  assert_argument_type(termios, termios);
  return raw__keyboard__current_mode__set(cause, termios);
}
export_cefunk1(keyboard__current_mode__set, termios, 0, "Sets the current standard input device attributes to those given by the termios struct.");


f2ptr f2__keyboard__enable_noncanonical_mode(f2ptr cause) {
  struct termios opts;
  int res = tcgetattr(STDIN_FILENO, &opts);
  if (res != 0) {
    return f2larva__new(cause, 22351, nil);
  }
  opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &opts);
  return nil;
}
export_cefunk0(keyboard__enable_noncanonical_mode, 0, "Enables noncanonical mode device attributes for the standard input.");


f2ptr f2__keyboard__try_read_byte(f2ptr cause) {
  if (raw__system__received_signal__sigint(cause)) {
    f2__system__clear_signal__sigint(cause);
    return f2larva__new(cause, 777, nil);
  }
  struct termios org_opts, new_opts;
  //-----  store old settings -----------
  int res = tcgetattr(STDIN_FILENO, &org_opts);
  if (res != 0) {
    return f2larva__new(cause, 62351, nil);
  }
  //---- set new terminal parms --------
  memcpy(&new_opts, &org_opts, sizeof(new_opts));
  new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE | ICRNL);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
  u32 bytes_read = 0;
  u8  ch;
  read_nonblocking(STDIN_FILENO, &ch, 1, &bytes_read);
  //------  restore old settings ---------
  res=tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);
  if (res != 0) {
    return f2larva__new(cause, 62353, nil);
  }
  if (bytes_read == 0) {
    return nil;
  } else {
    return f2integer__new(cause, ch);
  }
}
export_cefunk0(keyboard__try_read_byte, 0, "Wait for next byte from keyboard.");

#define assert_value_with_ctrl_c(value) ({			\
      f2ptr temp_value = (value);				\
      if (raw__larva__is_type(cause, temp_value)) {		\
	if (raw__larva__larva_type(cause, temp_value) == 777) {	\
	  return temp_value;					\
	} else {						\
	  assert_value(temp_value);				\
	}							\
      }								\
      temp_value;						\
    })

f2ptr f2__keyboard__try_read_character(f2ptr cause) {
  f2ptr b0 = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
  if (b0 == nil) {
    return nil;
  }
  u64 b0__i = f2integer__i(b0, cause);
  if (b0__i <= 127) {
    // ascii one-byte character
    return f2char__new(cause, b0__i);
  } else if ((b0__i & 0xE0) == 0xC0) {
    // utf8 two-byte character
    f2ptr             b1    = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
    if (b1 == nil) {
      return f2larva__new(cause, 65424, nil);
    }
    u64               b1__i = f2integer__i(b1, cause);
    funk2_character_t ch    = ((b0__i & 0x1F) << 6) | (b1__i & 0x3F);
    return f2char__new(cause, ch);
  } else if ((b0__i & 0xF0) == 0xE0) {
    // utf8 three-byte character
    f2ptr             b1    = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
    if (b1 == nil) {
      return f2larva__new(cause, 65425, nil);
    }
    u64               b1__i = f2integer__i(b1, cause);
    f2ptr             b2    = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
    if (b2 == nil) {
      return f2larva__new(cause, 65426, nil);
    }
    u64               b2__i = f2integer__i(b2, cause);
    funk2_character_t ch    = ((b0__i & 0x0F) << 12) | ((b1__i & 0x3F) << 6) | (b2__i & 0x3F);
    return f2char__new(cause, ch);
  } else if ((b0__i & 0xF8) == 0xF0) {
    // utf8 four-byte character
    f2ptr             b1    = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
    if (b1 == nil) {
      return f2larva__new(cause, 65427, nil);
    }
    u64               b1__i = f2integer__i(b1, cause);
    f2ptr             b2    = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
    if (b2 == nil) {
      return f2larva__new(cause, 65428, nil);
    }
    u64               b2__i = f2integer__i(b2, cause);
    f2ptr             b3    = assert_value_with_ctrl_c(f2__keyboard__try_read_byte(cause));
    if (b3 == nil) {
      return f2larva__new(cause, 65429, nil);
    }
    u64               b3__i = f2integer__i(b3, cause);
    funk2_character_t ch    = ((b0__i & 0x07) << 18) | ((b1__i & 0x3F) << 12) | ((b2__i & 0x3F) << 6) | (b3__i & 0x3F);
    return f2char__new(cause, ch);
  } else {
    // invalid character.
    return f2char__new(cause, (funk2_character_t)0xFFFD);
  }
}
export_cefunk0(keyboard__try_read_character, 0, "Wait for next character from keyboard.");


f2ptr f2__keyboard__check_keypress(f2ptr cause) {
  f2ptr old_opts = assert_value(f2__keyboard__current_mode(cause));
  assert_value(f2__keyboard__enable_noncanonical_mode(cause));
  f2ptr ch     = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
  f2ptr result = nil;
  {
    if (ch != nil) {
      if (raw__char__is_type(cause, ch)) {
	funk2_character_t ch__ch = raw__char__ch(cause, ch);
	if (ch__ch == 0x00) {
	  result = new__symbol(cause, "key:ctrl_space");
	} else if (ch__ch == 0x01) {
	  result = new__symbol(cause, "key:ctrl_a");
	} else if (ch__ch == 0x02) {
	  result = new__symbol(cause, "key:ctrl_b");
	} else if (ch__ch == 0x03) {
	  result = new__symbol(cause, "key:ctrl_c");
	} else if (ch__ch == 0x04) {
	  result = new__symbol(cause, "key:ctrl_d");
	} else if (ch__ch == 0x05) {
	  result = new__symbol(cause, "key:ctrl_e");
	} else if (ch__ch == 0x06) {
	  result = new__symbol(cause, "key:ctrl_f");
	} else if (ch__ch == 0x07) {
	  result = new__symbol(cause, "key:ctrl_g");
	} else if (ch__ch == 0x08) {
	  result = new__symbol(cause, "key:ctrl_h");
	} else if (ch__ch == 0x09) {
	  result = new__symbol(cause, "key:tab");
	} else if (ch__ch == 0x0A) {
	  result = new__symbol(cause, "key:enter");
	} else if (ch__ch == 0x0B) {
	  result = new__symbol(cause, "key:ctrl_k");
	} else if (ch__ch == 0x0C) {
	  result = new__symbol(cause, "key:ctrl_l");
	} else if (ch__ch == 0x0E) {
	  result = new__symbol(cause, "key:ctrl_n");
	} else if (ch__ch == 0x0F) {
	  result = new__symbol(cause, "key:ctrl_o");
	} else if (ch__ch == 0x10) {
	  result = new__symbol(cause, "key:ctrl_p");
	} else if (ch__ch == 0x12) {
	  result = new__symbol(cause, "key:ctrl_r");
	} else if (ch__ch == 0x14) {
	  result = new__symbol(cause, "key:ctrl_t");
	} else if (ch__ch == 0x16) {
	  result = new__symbol(cause, "key:ctrl_v");
	} else if (ch__ch == 0x17) {
	  result = new__symbol(cause, "key:ctrl_w");
	} else if (ch__ch == 0x18) {
	  result = new__symbol(cause, "key:ctrl_x");
	} else if (ch__ch == 0x19) {
	  result = new__symbol(cause, "key:ctrl_y");
	} else if (ch__ch == 0x7F) {
	  result = new__symbol(cause, "key:backspace");
	} else if (ch__ch == 0x1B) {
	  f2ptr escaped_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
	  if (escaped_ch == nil) {
	    result = new__symbol(cause, "key:escape");
	  } else {
	    if (raw__char__is_type(cause, ch)) {
	      funk2_character_t escaped_ch__ch = raw__char__ch(cause, escaped_ch);
	      if (escaped_ch__ch == (funk2_character_t)'[') {
		f2ptr ansi_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
		if ((ansi_ch != nil) && raw__char__is_type(cause, ansi_ch)) {
		  funk2_character_t ansi_ch__ch = raw__char__ch(cause, ansi_ch);
		  if (ansi_ch__ch == (funk2_character_t)'A') {
		    result = new__symbol(cause, "key:up");
		  } else if (ansi_ch__ch == (funk2_character_t)'B') {
		    result = new__symbol(cause, "key:down");
		  } else if (ansi_ch__ch == (funk2_character_t)'C') {
		    result = new__symbol(cause, "key:right");
		  } else if (ansi_ch__ch == (funk2_character_t)'D') {
		    result = new__symbol(cause, "key:left");
		  } else if (ansi_ch__ch == (funk2_character_t)'2') {
		    f2ptr ansi2_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
		    if ((ansi2_ch != nil) && raw__char__is_type(cause, ansi2_ch)) {
		      funk2_character_t ansi2_ch__ch = raw__char__ch(cause, ansi2_ch);
		      if (ansi2_ch__ch == (funk2_character_t)'~') {
			result = new__symbol(cause, "key:insert");
		      }
		    }
		  } else if (ansi_ch__ch == (funk2_character_t)'3') {
		    f2ptr ansi2_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
		    if ((ansi2_ch != nil) && raw__char__is_type(cause, ansi2_ch)) {
		      funk2_character_t ansi2_ch__ch = raw__char__ch(cause, ansi2_ch);
		      if (ansi2_ch__ch == (funk2_character_t)'~') {
			result = new__symbol(cause, "key:delete");
		      }
		    }
		  } else if (ansi_ch__ch == (funk2_character_t)'5') {
		    f2ptr ansi2_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
		    if ((ansi2_ch != nil) && raw__char__is_type(cause, ansi2_ch)) {
		      funk2_character_t ansi2_ch__ch = raw__char__ch(cause, ansi2_ch);
		      if (ansi2_ch__ch == (funk2_character_t)'~') {
			result = new__symbol(cause, "key:page_up");
		      }
		    }
		  } else if (ansi_ch__ch == (funk2_character_t)'6') {
		    f2ptr ansi2_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
		    if ((ansi2_ch != nil) && raw__char__is_type(cause, ansi2_ch)) {
		      funk2_character_t ansi2_ch__ch = raw__char__ch(cause, ansi2_ch);
		      if (ansi2_ch__ch == (funk2_character_t)'~') {
			result = new__symbol(cause, "key:page_down");
		      }
		    }
		  }
		}
	      } else if (escaped_ch__ch == (funk2_character_t)'O') {
		f2ptr other_ch = assert_value_with_ctrl_c(f2__keyboard__try_read_character(cause));
		if ((other_ch != nil) && raw__char__is_type(cause, other_ch)) {
		  funk2_character_t other_ch__ch = raw__char__ch(cause, other_ch);
		  if (other_ch__ch == (funk2_character_t)'F') {
		    result = new__symbol(cause, "key:end");
		  } else if (other_ch__ch == (funk2_character_t)'H') {
		    result = new__symbol(cause, "key:home");
		  } else if (other_ch__ch == (funk2_character_t)'P') {
		    result = new__symbol(cause, "key:f1");
		  }
		}
	      }
	    }
	  }
	} else {
	  result = ch;
	}
      }
      if (result == nil) {
	result = new__symbol(cause, "key:invalid");
      }
    }
  }
  f2__keyboard__current_mode__set(cause, old_opts);
  return result;
}
export_cefunk0(keyboard__check_keypress, 0, "Check for next keypress.");


f2ptr raw__keyboard_editor__insert_char(f2ptr cause, f2ptr this, f2ptr line_index, f2ptr char_index, f2ptr ch) {
  s64   ch__ch     = f2char__ch(ch, cause);
  f2ptr line_array = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "line_array"), nil));
  assert_argument_type(array, line_array);
  f2ptr line_str   = assert_value(f2__array__elt(cause, line_array, line_index));
  assert_argument_type(string, line_str);
  f2ptr first_part  = assert_value(f2__string__substring(cause, line_str, f2integer__new(cause, 0), char_index));
  assert_argument_type(string, first_part);
  f2ptr last_part   = assert_value(f2__string__substring(cause, line_str, char_index,               f2__string__length(cause, line_str)));
  assert_argument_type(string, last_part);
  funk2_character_t middle_part__str[2];
  middle_part__str[0] = ch__ch;
  middle_part__str[1] = 0;
  f2ptr middle_part = f2string__new(cause, 1, middle_part__str);
  f2ptr new_line    = assert_value(f2__stringlist__concat(cause, f2list3__new(cause, first_part, middle_part, last_part)));
  assert_value(f2__array__elt__set(cause, line_array, line_index, new_line));
  return nil;
}

f2ptr f2__keyboard_editor__insert_char(f2ptr cause, f2ptr this, f2ptr line_index, f2ptr char_index, f2ptr ch) {
  assert_argument_type(frame,   this);
  assert_argument_type(integer, line_index);
  assert_argument_type(integer, char_index);
  assert_argument_type(char,    ch);
  return raw__keyboard_editor__insert_char(cause, this, line_index, char_index, ch);
}
export_cefunk4(keyboard_editor__insert_char, this, line_index, char_index, ch, 0, "Insert character into keyboard_editor.");


f2ptr raw__keyboard_editor__current_line(f2ptr cause, f2ptr this) {
  f2ptr line_array = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "line_array"), nil));
  f2ptr cursor_y   = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cursor_y"),   nil));
  return assert_value(f2__array__elt(cause, line_array, cursor_y));
}

f2ptr f2__keyboard_editor__current_line(f2ptr cause, f2ptr this) {
  assert_argument_type(frame, this);
  return raw__keyboard_editor__current_line(cause, this);
}
export_cefunk1(keyboard_editor__current_line, this, 0, "Returns the current line being edited.");


f2ptr raw__keyboard_editor__press_and_insert_char_key__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame, f2ptr key) {
  f2ptr cursor_x = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cursor_x"), nil));
  assert_argument_type(integer, cursor_x);
  f2ptr cursor_y = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "cursor_y"), nil));
  assert_argument_type(integer, cursor_y);
  assert_value(f2__keyboard_editor__insert_char(cause, this, cursor_y, cursor_x, key));
  s64 cursor_x__i = f2integer__i(cursor_x, cause);
  cursor_x__i ++;
  cursor_x = f2integer__new(cause, cursor_x__i);
  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "cursor_x"), cursor_x));
  {
    funk2_character_t output_string[2];
    output_string[0] = f2char__ch(key, cause);
    output_string[1] = 0;
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, 1, output_string);
  }
  f2ptr current_line         = assert_value(raw__keyboard_editor__current_line(cause, this));
  s64   current_line__length = raw__string__length(cause, current_line);
  if (cursor_x__i < current_line__length) {
    funk2_character_t* current_line__str = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (current_line__length + 1)));
    raw__string__str_copy(cause, current_line, current_line__str);
    current_line__str[current_line__length] = 0;
    //raw__terminal_print_frame__write_ansi__hide_cursor__thread_unsafe(cause, terminal_print_frame);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, current_line__length - cursor_x__i, &current_line__str[cursor_x__i]);
    raw__terminal_print_frame__write_ansi__move__thread_unsafe(cause, terminal_print_frame, -(current_line__length - cursor_x__i), 0);
    //raw__terminal_print_frame__write_ansi__show_cursor__thread_unsafe(cause, terminal_print_frame);
    f2__free(to_ptr(current_line__str));
  }
  f2ptr buffer_max_x = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "buffer_max_x"), nil));
  assert_argument_type(integer, buffer_max_x);
  s64 buffer_max_x__i = f2integer__i(buffer_max_x, cause);
  if (current_line__length > buffer_max_x__i) {
    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "buffer_max_x"), f2integer__new(cause, current_line__length)));
  }
  return nil;
}

f2ptr f2__keyboard_editor__press_and_insert_char_key__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame, f2ptr key) {
  assert_argument_type(frame,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  assert_argument_type(char,                 key);
  return raw__keyboard_editor__press_and_insert_char_key__thread_unsafe(cause, this, terminal_print_frame, key);
}
export_cefunk3(keyboard_editor__press_and_insert_char_key__thread_unsafe, this, terminal_print_frame, key, 0, "Press and insert character key into keyboard_editor (thread unsafe with respect to the terminal_print_frame).");


f2ptr raw__keyboard_editor__handle_text_keys__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr     key         = nil;
  boolean_t is_text_key = boolean__true;
  while (is_text_key) {
    key = assert_value_with_ctrl_c(f2__keyboard__check_keypress(cause));
    if (raw__char__is_type(cause, key)) {
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "saving_x_column_during_movement"), nil));
      assert_value(f2__keyboard_editor__press_and_insert_char_key__thread_unsafe(cause, this, terminal_print_frame, key));
    } else {
      is_text_key = boolean__false;
    }
  }
  return key;
}

f2ptr f2__keyboard_editor__handle_text_keys__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(frame,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__keyboard_editor__handle_text_keys__thread_unsafe(cause, this, terminal_print_frame);
}
export_cefunk2(keyboard_editor__handle_text_keys__thread_unsafe, this, terminal_print_frame, 0, "Handle text keys and return a special symbolic key when one is encountered (thread unsafe with respect to the terminal_print_frame).");


// **

f2ptr f2__keyboard__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(keyboard__core_extension__ping, 0, "");

f2ptr f2__keyboard__core_extension__initialize(f2ptr cause) {
  status("keyboard initialized.");
  return nil;
}
export_cefunk0(keyboard__core_extension__initialize, 0, "");

f2ptr f2__keyboard__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "termios"), f2__termios_type__new_aux(cause));
  status("keyboard types defined.");
  return nil;
}
export_cefunk0(keyboard__core_extension__define_types, 0, "");

f2ptr f2__keyboard__core_extension__destroy(f2ptr cause) {
  status("keyboard destroyed.");
  return nil;
}
export_cefunk0(keyboard__core_extension__destroy, 0, "");



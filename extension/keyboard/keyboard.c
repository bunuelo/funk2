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


def_ceframe1(termios, termios, chunk);

f2ptr raw__termios__new(f2ptr cause, struct termios* opts) {
  return f2termios__new(cause, f2chunk__new(cause, sizeof(*opts), (u8*)opts));
}

void raw__termios__copy_termios(f2ptr cause, f2ptr this, struct termios* dest) {
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
  return raw__termios__new(cause, &opts);
}
export_cefunk0(keyboard__current_mode, 0, "Return a termios struct containing the current standard input device attributes.");


f2ptr raw__keyboard__current_mode__set(f2ptr cause, f2ptr termios) {
  struct termios opts;
  raw__termios__copy_termios(cause, termios, &opts);
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


f2ptr f2__keyboard__try_read_character(f2ptr cause) {
  f2ptr b0    = assert_value(f2__keyboard__try_read_byte(cause));
  if (b0 == nil) {
    return nil;
  }
  u64   b0__i = f2integer__i(b0, cause);
  if (b0__i <= 127) {
    // ascii one-byte character
    return f2char__new(cause, b0__i);
  } else if ((b0__i & 0xE0) == 0xC0) {
    // utf8 two-byte character
    f2ptr             b1    = assert_value(f2__keyboard__try_read_byte(cause));
    if (b1 == nil) {
      return f2larva__new(cause, 65424, nil);
    }
    u64               b1__i = f2integer__i(b1, cause);
    funk2_character_t ch    = ((b0__i & 0x1F) << 6) | (b1__i & 0x3F);
    return f2char__new(cause, ch);
  } else if ((b0__i & 0xF0) == 0xE0) {
    // utf8 three-byte character
    f2ptr             b1    = assert_value(f2__keyboard__try_read_byte(cause));
    if (b1 == nil) {
      return f2larva__new(cause, 65425, nil);
    }
    u64               b1__i = f2integer__i(b1, cause);
    f2ptr             b2    = assert_value(f2__keyboard__try_read_byte(cause));
    if (b2 == nil) {
      return f2larva__new(cause, 65426, nil);
    }
    u64               b2__i = f2integer__i(b2, cause);
    funk2_character_t ch    = ((b0__i & 0x0F) << 12) | ((b1__i & 0x3F) << 6) | (b2__i & 0x3F);
    return f2char__new(cause, ch);
  } else if ((b0__i & 0xF8) == 0xF0) {
    // utf8 four-byte character
    f2ptr             b1    = assert_value(f2__keyboard__try_read_byte(cause));
    if (b1 == nil) {
      return f2larva__new(cause, 65427, nil);
    }
    u64               b1__i = f2integer__i(b1, cause);
    f2ptr             b2    = assert_value(f2__keyboard__try_read_byte(cause));
    if (b2 == nil) {
      return f2larva__new(cause, 65428, nil);
    }
    u64               b2__i = f2integer__i(b2, cause);
    f2ptr             b3    = assert_value(f2__keyboard__try_read_byte(cause));
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



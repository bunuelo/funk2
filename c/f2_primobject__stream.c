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

// stream

def_primobject_12_slot(stream, cmutex, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index, line_number, column_number);

f2ptr __file_stream__symbol        = -1;
f2ptr __socket_stream__symbol      = -1;
f2ptr __string_stream__symbol      = -1;
f2ptr __text_window_stream__symbol = -1;

f2ptr f2__stream__new(f2ptr cause, f2ptr stream_type, f2ptr ungetb_stack, f2ptr rewind_stack, f2ptr rewindable, f2ptr rewind_length, f2ptr file_handle, f2ptr string, f2ptr index, f2ptr character_byte_index) {
  f2ptr cmutex        = f2__cmutex__new(cause);
  f2ptr line_number   = f2integer__new(cause, 1);
  f2ptr column_number = f2integer__new(cause, 1);
  return f2stream__new(cause, cmutex, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index, line_number, column_number);
}
def_pcfunk9(stream__new, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index,
	    "",
	    return f2__stream__new(this_cause, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index));


f2ptr f2__file_stream__new(f2ptr cause, f2ptr file_handle) {
  if (__file_stream__symbol == -1) {__file_stream__symbol = new__symbol(cause, "file_stream");}
  assert_argument_type(file_handle, file_handle);
  boolean_t rewindable    = boolean__true;
  f2ptr     rewind_length = f2integer__new(cause, 0);
  return f2__stream__new(cause, __file_stream__symbol, nil, nil, f2bool__new(rewindable), rewind_length, file_handle, nil, nil, nil);
}
def_pcfunk1(file_stream__new, file_handle,
	    "",
	    return f2__file_stream__new(this_cause, file_handle));

boolean_t raw__file_stream__is_type(f2ptr cause, f2ptr this) {
  if (__file_stream__symbol == -1) {__file_stream__symbol = new__symbol(cause, "file_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__stream_type(this, cause), __file_stream__symbol));
}
f2ptr f2__file_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__file_stream__is_type(cause, this));}


f2ptr f2__socket_stream__new(f2ptr cause, f2ptr file_handle) {
  if (__socket_stream__symbol == -1) {__socket_stream__symbol = new__symbol(cause, "socket_stream");}
  assert_argument_type(file_handle, file_handle);
  boolean_t rewindable    = boolean__true;
  f2ptr     rewind_length = f2integer__new(cause, 0);
  return f2__stream__new(cause, __socket_stream__symbol, nil, nil, f2bool__new(rewindable), rewind_length, file_handle, nil, nil, nil);
}
def_pcfunk1(socket_stream__new, file_handle,
	    "",
	    return f2__socket_stream__new(this_cause, file_handle));

boolean_t raw__socket_stream__is_type(f2ptr cause, f2ptr this) {
  if (__socket_stream__symbol == -1) {__socket_stream__symbol = new__symbol(cause, "socket_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__stream_type(this, cause), __socket_stream__symbol));
}
f2ptr f2__socket_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__socket_stream__is_type(cause, this));}


f2ptr f2__string_stream__new(f2ptr cause, f2ptr string, f2ptr index) {
  if (__string_stream__symbol == -1) {__string_stream__symbol = new__symbol(cause, "string_stream");}
  assert_argument_type(string,  string);
  assert_argument_type(integer, index);
  boolean_t rewindable           = boolean__true;
  f2ptr     rewind_length        = f2integer__new(cause, 0);
  f2ptr     character_byte_index = f2integer__new(cause, 0);
  return f2__stream__new(cause, __string_stream__symbol, nil, nil, f2bool__new(rewindable), rewind_length, nil, string, index, character_byte_index);
}
def_pcfunk2(string_stream__new, string, index,
	    "",
	    return f2__string_stream__new(this_cause, string, index));

boolean_t raw__string_stream__is_type(f2ptr cause, f2ptr this) {
  if (__string_stream__symbol == -1) {__string_stream__symbol = new__symbol(cause, "string_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__stream_type(this, cause), __string_stream__symbol));
}
f2ptr f2__string_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__string_stream__is_type(cause, this));}

f2ptr f2__string_stream(f2ptr cause, f2ptr string) {
  return f2__string_stream__new(cause, string, f2integer__new(cause, 0));
}
def_pcfunk1(string_stream, string,
	    "",
	    return f2__string_stream(this_cause, string));

f2ptr raw__stream__new_open_file(f2ptr cause, char* filename, int mode) {
  int fd = open(filename, mode);
  if (fd == -1) {
    return nil;
  }
  return f2__file_stream__new(cause, f2__file_handle__new(cause, f2integer__new(cause, fd)));
}

f2ptr f2__stream__new_open_file(f2ptr cause, f2ptr filename, f2ptr mode) {
  assert_argument_type(string,  filename);
  assert_argument_type(integer, mode);
  u64   filename__utf8_length = raw__string__utf8_length(cause, filename);
  char* filename__utf8_str    = (char*)alloca(filename__utf8_length + 1);
  raw__string__utf8_str_copy(cause, filename, (u8*)filename__utf8_str);
  filename__utf8_str[filename__utf8_length] = 0;
  u64 raw_mode = f2integer__i(mode, cause);
  return raw__stream__new_open_file(cause, filename__utf8_str, raw_mode);
}
def_pcfunk2(stream__new_open_file, filename, mode,
	    "",
	    return f2__stream__new_open_file(this_cause, filename, mode));

f2ptr f2__file_stream__close(f2ptr cause, f2ptr this) {
  assert_argument_type(file_stream, this);
  f2ptr file_handle = f2stream__file_handle(this, cause);
  if (! raw__file_handle__is_type(cause, file_handle)) {
    return f2larva__new(cause, 1135156, nil);
  }
  return f2__file_handle__close(cause, file_handle);
}

f2ptr f2__socket_stream__close(f2ptr cause, f2ptr this) {
  assert_argument_type(socket_stream, this);
  f2ptr file_handle = f2stream__file_handle(this, cause);
  if (! raw__file_handle__is_type(cause, file_handle)) {
    return f2larva__new(cause, 1135157, nil);
  }
  return f2__file_handle__close(cause, file_handle);
}


boolean_t raw__closable_stream__is_type(f2ptr cause, f2ptr this) {
  return (raw__file_stream__is_type(  cause, this) ||
	  raw__socket_stream__is_type(cause, this));
}

f2ptr raw__stream__close(f2ptr cause, f2ptr this) {
  if (raw__file_stream__is_type(cause, this)) {
    return f2__file_stream__close(cause, this);
  } else if (raw__socket_stream__is_type(cause, this)) {
    return f2__socket_stream__close(cause, this);
  }
  error(nil, "raw__stream__close error: this is invalid type.");
}

f2ptr f2__stream__close(f2ptr cause, f2ptr this) {
  assert_argument_type(closable_stream, this);
  return raw__stream__close(cause, this);
}
def_pcfunk1(stream__close, this,
	    "If this stream is a closable_stream, closes this stream.",
	    return f2__stream__close(this_cause, this));

f2ptr f2__stream__file_mode__rdonly(f2ptr cause) {return f2integer__new(cause, O_RDONLY);}
def_pcfunk0(stream__file_mode__rdonly,
	    "",
	    return f2__stream__file_mode__rdonly(this_cause));

f2ptr f2__stream__file_mode__creat(f2ptr cause)  {return f2integer__new(cause, O_CREAT);}
def_pcfunk0(stream__file_mode__creat,
	    "",
	    return f2__stream__file_mode__creat(this_cause));

f2ptr f2__stream__file_mode__rdwr(f2ptr cause)   {return f2integer__new(cause, O_RDWR);}
def_pcfunk0(stream__file_mode__rdwr,
	    "",
	    return f2__stream__file_mode__rdwr(this_cause));

f2ptr f2__stream__new_open_file__rdonly(f2ptr cause, f2ptr filename) {
  f2ptr mode = f2__stream__file_mode__rdonly(cause);
  return f2__stream__new_open_file(cause, filename, mode);
}

f2ptr f2__stream__new_open_file__rdwr(f2ptr cause, f2ptr filename) {
  f2ptr mode = f2__stream__file_mode__rdwr(cause);
  return f2__stream__new_open_file(cause, filename, mode);
}

int raw__file_stream__nonblocking__set(f2ptr cause, f2ptr this, boolean_t value) {
  f2ptr file_handle = f2stream__file_handle(this, cause);
  return f2__file_handle__nonblocking__set(cause, file_handle, f2bool__new(value));
}

f2ptr f2__file_stream__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(file_stream, this);
  return raw__file_stream__nonblocking__set(cause, this, (value != nil));
}

int raw__socket_stream__nonblocking__set(f2ptr cause, f2ptr this, boolean_t value) {
  f2ptr file_handle = f2stream__file_handle(this, cause);
  return f2__file_handle__nonblocking__set(cause, file_handle, f2bool__new(value));
}

f2ptr f2__socket_stream__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(socket_stream, this);
  return raw__socket_stream__nonblocking__set(cause, this, (value != nil));
}

f2ptr f2__stream__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (raw__file_stream__is_type(cause, this)) {
    return f2__file_stream__nonblocking__set(cause, this, value);
  } else if (raw__socket_stream__is_type(cause, this)) {
    return f2__socket_stream__nonblocking__set(cause, this, value);
  }
  return f2larva__new(cause, 17531, nil);
}
def_pcfunk2(stream__nonblocking__set, this, value,
	    "",
	    return f2__stream__nonblocking__set(this_cause, this, value));

f2ptr f2__stream__ungetb(f2ptr cause, f2ptr this, f2ptr byte) {
  assert_argument_type(stream, this);
  if ((! raw__integer__is_type(cause, byte)) &&
      (! raw__exception__is_type(cause, byte))) {
    error(nil, "raw__stream__ungetb error: byte must be integer or exception.");
    return f2larva__new(cause, 11352, nil);
  }
  f2ptr rewind_byte = f2__stream__rewind(cause, this);
  if (! raw__eq(cause, byte, rewind_byte)) {
    f2__terminal_print(cause, byte);
    f2__terminal_print(cause, rewind_byte);
    error(nil, "ungetb rewind byte mismatch.");
  }
  return nil;
}
def_pcfunk2(stream__ungetb, this, character,
	    "",
	    return f2__stream__ungetb(this_cause, this, character));

void raw__stream__ungetb(f2ptr cause, f2ptr this, u8 byte__i) {
  f2ptr byte = f2integer__new(cause, byte__i);
  f2__stream__ungetb(cause, this, byte);
}


f2ptr f2__stream__ungetc(f2ptr cause, f2ptr this, f2ptr character) {
  assert_argument_type(stream, this);
  if ((! raw__char__is_type(cause, character)) &&
      (! raw__exception__is_type(cause, character))) {
    error(nil, "raw__stream__ungetc error: character must be char or exception.");
    return f2larva__new(cause, 11352, nil);
  }
  if (raw__char__is_type(cause, character)) {
    funk2_character_t ch   = f2char__ch(character, cause);
    u64               ch__utf8_length = funk2_character__utf8_length(ch);
    u8                ch__utf8_str[6];
    funk2_character__utf8_str_copy(ch, ch__utf8_str);
    {
      s64 index;
      for (index = ch__utf8_length - 1; index >= 0; index --) {
	raw__stream__ungetb(cause, this, ch__utf8_str[index]);
      }
    }
  } else {
    raw__stream__ungetb(cause, this, character);
  }
  return nil;
}
def_pcfunk2(stream__ungetc, this, character,
	    "",
	    return f2__stream__ungetc(this_cause, this, character));

void raw__stream__ungetc(f2ptr cause, f2ptr this, funk2_character_t ch) {
  f2ptr character = f2char__new(cause, ch);
  f2__stream__ungetc(cause, this, character);
}

f2ptr f2__file_stream__try_ungetbless_read_byte(f2ptr cause, f2ptr this) {
  assert_argument_type(file_stream, this);
  f2ptr file_handle = f2stream__file_handle(this, cause);
  f2ptr byte        = f2__file_handle__try_read_byte(cause, file_handle);
  if (raw__larva__is_type(cause, byte)) {
    return __funk2.reader.end_of_file_exception;
  }
  return byte;
}

f2ptr f2__socket_stream__try_ungetbless_read_byte(f2ptr cause, f2ptr this) {
  assert_argument_type(file_stream, this);
  f2ptr file_handle = f2stream__file_handle(this, cause);
  f2ptr byte        = f2__file_handle__try_read_byte(cause, file_handle);
  if (raw__larva__is_type(cause, byte)) {
    return __funk2.reader.end_of_file_exception;
  }
  return byte;
}

f2ptr f2__string_stream__try_ungetbless_read_byte(f2ptr cause, f2ptr this) {
  assert_argument_type(string_stream, this);
  f2ptr string                  = f2stream__string(              this,                 cause);
  u64   string__length          = f2string__length(              string,               cause);
  f2ptr index                   = f2stream__index(               this,                 cause);
  u64   index__i                = f2integer__i(                  index,                cause);
  f2ptr character_byte_index    = f2stream__character_byte_index(this,                 cause);
  u64   character_byte_index__i = f2integer__i(                  character_byte_index, cause);
  if (index__i < string__length) {
    funk2_character_t ch      = f2string__elt(string, index__i, cause);
    u64               ch__utf8_length = funk2_character__utf8_length(  ch);
    u8                ch__utf8_str[6];  funk2_character__utf8_str_copy(ch, ch__utf8_str);
    if (character_byte_index__i < ch__utf8_length) {
      u8    byte__i      = ch__utf8_str[character_byte_index__i];
      f2ptr return_value = f2integer__new(cause, byte__i);
      character_byte_index__i ++;
      if (character_byte_index__i >= ch__utf8_length) {
	character_byte_index__i = 0;
	index__i ++;
	f2stream__index__set(this, cause, f2integer__new(cause, index__i));
      }
      f2stream__character_byte_index__set(this, cause, f2integer__new(cause, character_byte_index__i));
      return return_value;
    }
  }
  return __funk2.reader.end_of_file_exception;
}

f2ptr f2__stream__try_read_byte(f2ptr cause, f2ptr this) {
  assert_argument_type(stream, this);
  f2ptr byte         = nil;
  f2ptr ungetb_stack = f2stream__ungetb_stack(this, cause);
  if (ungetb_stack) {
    byte = f2cons__car(ungetb_stack, cause);
    f2stream__ungetb_stack__set(this, cause, f2cons__cdr(ungetb_stack, cause));
  }
  if (byte == nil) {
    if (raw__file_stream__is_type(cause, this)) {
      byte = f2__file_stream__try_ungetbless_read_byte(cause, this);
    } else if (raw__socket_stream__is_type(cause, this)) {
      byte = f2__socket_stream__try_ungetbless_read_byte(cause, this);
    } else if (raw__string_stream__is_type(cause, this)) {
      byte = f2__string_stream__try_ungetbless_read_byte(cause, this);
    }
  }
  if (byte && f2stream__rewindable(this, cause)) {
    f2stream__rewind_stack__set(this, cause, raw__cons__new(cause, byte, f2stream__rewind_stack(this, cause)));
    f2ptr rewind_length = f2stream__rewind_length(this, cause);
    if (! raw__integer__is_type(cause, rewind_length)) {
      return f2larva__new(cause, 1135, nil);
    }
    s64 rewind_length__i = f2integer__i(rewind_length, cause);
    f2stream__rewind_length__set(this, cause, f2integer__new(cause, rewind_length__i + 1));
  }
  if (raw__integer__is_type(cause, byte)) {
    if ((byte != nil) &&
	f2integer__i(byte, cause) == f2char__ch(__funk2.reader.char__newline, cause)) {
      f2ptr line_num    = f2__stream__line_number(cause, this);
      u64   line_num__i = f2integer__i(line_num, cause);
      f2__stream__line_number__set(cause, this, f2integer__new(cause, line_num__i + 1));
      f2__stream__column_number__set(cause, this, f2integer__new(cause, 1));
    } else {
      f2ptr column_num    = f2__stream__column_number(cause, this);
      u64   column_num__i = f2integer__i(column_num, cause);
      f2__stream__column_number__set(cause, this, f2integer__new(cause, column_num__i + 1));
    }
  }
  return byte;
}
def_pcfunk1(stream__try_read_byte, stream,
	    "",
	    return f2__stream__try_read_byte(this_cause, stream));

f2ptr f2__stream__getb(f2ptr cause, f2ptr stream) {
  if (! raw__stream__is_type(cause, stream)) {error(nil, "raw__stream__getb error: stream isn't a stream.");}
  f2ptr read_byte = nil;
  while (read_byte == nil) {
    read_byte = f2__stream__try_read_byte(cause, stream);
    if (read_byte == nil) {
      f2__this__fiber__yield(cause);
      raw__spin_sleep_yield();
    }
  }
  if (raw__exception__is_type(cause, read_byte) && raw__eq(cause, f2exception__tag(read_byte, cause), __funk2.reader.end_of_file_exception__symbol)) {
    status("f2__stream__getb() note: eof reached.");
  }
  return read_byte;
}
def_pcfunk1(stream__getb, stream,
	    "",
	    return f2__stream__getb(this_cause, stream));

f2ptr f2__stream__rewind(f2ptr cause, f2ptr this) {
  assert_argument_type(stream, this);
  f2ptr rewind_stack = f2stream__rewind_stack(this, cause);
  if (! rewind_stack) {
    return f2larva__new(cause, 234, nil);
  }
  if (! raw__cons__is_type(cause, rewind_stack)) {
    return f2larva__new(cause, 2, nil);
  }
  f2ptr byte = f2cons__car(rewind_stack, cause);
  f2stream__rewind_stack__set(this, cause, f2cons__cdr(rewind_stack, cause));
  f2stream__ungetb_stack__set(this, cause, raw__cons__new(cause, byte, f2stream__ungetb_stack(this, cause)));
  f2ptr rewind_length = f2stream__rewind_length(this, cause);
  if (! raw__integer__is_type(cause, rewind_length)) {
    return f2larva__new(cause, 3, nil);
  }
  s64 rewind_length__i = f2integer__i(rewind_length, cause);
  f2ptr new_rewind_length = f2integer__new(cause, rewind_length__i - 1);
  f2stream__rewind_length__set(this, cause, new_rewind_length);
  if (raw__integer__is_type(cause, byte) && f2integer__i(byte, cause) == f2char__ch(__funk2.reader.char__newline, cause)) {
    f2ptr line_num    = f2__stream__line_number(cause, this);
    u64   line_num__i = f2integer__i(line_num, cause);
    f2__stream__line_number__set(cause, this, f2integer__new(cause, line_num__i - 1));
    {
      f2ptr rewind_stack = f2stream__rewind_stack(this, cause);
      int column_num = 1;
      {
	f2ptr iter = rewind_stack;
	while (iter) {
	  f2ptr rewind_byte = f2__cons__car(cause, iter);
	  if (raw__integer__is_type(cause, rewind_byte) && f2integer__i(rewind_byte, cause) == f2char__ch(__funk2.reader.char__newline, cause)) {
	    break;
	  }
	  column_num ++;
	  iter = f2__cons__cdr(cause, iter);
	}
      }
      f2__stream__column_number__set(cause, this, f2integer__new(cause, column_num));
    }
  } else {
    f2ptr column_num    = f2__stream__column_number(cause, this);
    u64   column_num__i = f2integer__i(column_num, cause);
    f2__stream__column_number__set(cause, this, f2integer__new(cause, column_num__i - 1));
  }
  return byte;
}
def_pcfunk1(stream__rewind, stream,
	    "",
	    return f2__stream__getc(this_cause, stream));

f2ptr raw__stream__rewind_to_length(f2ptr cause, f2ptr this, s64 length) {
  assert_argument_type(stream, this);
  f2ptr rewind_length = f2stream__rewind_length(this, cause);
  if (! raw__integer__is_type(cause, rewind_length)) {
    return f2larva__new(cause, 3, nil);
  }
  s64 rewind_length__i = f2integer__i(rewind_length, cause);
  if (rewind_length__i < length) {
    return f2larva__new(cause, 338, nil);
  }
  f2ptr rewind_result = nil;
  s64 i;
  for (i = (rewind_length__i - length); i > 0; i --) {
    rewind_result = f2__stream__rewind(cause, this);
    if (raw__larva__is_type(cause, rewind_result)) {
      return rewind_result;
    }
  }
  return rewind_result;
}
f2ptr f2__stream__rewind_to_length(f2ptr cause, f2ptr this, f2ptr length) {
  assert_argument_type(integer, length);
  return raw__stream__rewind_to_length(cause, this, f2integer__i(length, cause));
}
def_pcfunk2(stream__rewind_to_length, this, length,
	    "",
	    return f2__stream__rewind_to_length(this_cause, this, length));


f2ptr raw__stream__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list26__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "stream"),
						new__symbol(cause, "cmutex"),               f2__stream__cmutex(              cause, this),
						new__symbol(cause, "stream_type"),          f2__stream__stream_type(         cause, this),
						new__symbol(cause, "ungetb_stack"),         f2__stream__ungetb_stack(        cause, this),
						new__symbol(cause, "rewind_stack"),         f2__stream__rewind_stack(        cause, this),
						new__symbol(cause, "rewindable"),           f2__stream__rewindable(          cause, this),
						new__symbol(cause, "rewind_length"),        f2__stream__rewind_length(       cause, this),
						new__symbol(cause, "file_handle"),          f2__stream__file_handle(         cause, this),
						new__symbol(cause, "string"),               f2__stream__string(              cause, this),
						new__symbol(cause, "index"),                f2__stream__index(               cause, this),
						new__symbol(cause, "character_byte_index"), f2__stream__character_byte_index(cause, this),
						new__symbol(cause, "line_number"),          f2__stream__line_number(         cause, this),
						new__symbol(cause, "column_number"),        f2__stream__column_number(       cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__stream__try_read_character(f2ptr cause, f2ptr this) {
  assert_argument_type(stream, this);
  f2ptr character;
  f2ptr b0 = f2__stream__try_read_byte(cause, this);
  if (! raw__integer__is_type(cause, b0)) {
    character = b0;
  } else {
    u64 b0__i = f2integer__i(b0, cause);
    if (b0__i <= 127) {
      // ascii one-byte character
      character = f2char__new(cause, b0__i);
    } else if ((b0__i & 0xE0) == 0xC0) {
      // utf8 two-byte character
      f2ptr b1 = f2__stream__try_read_byte(cause, this);
      if (! raw__integer__is_type(cause, b1)) {
	character = b1;
      } else {
	u64 b1__i = f2integer__i(b1, cause);
	funk2_character_t ch = ((b0__i & 0x1F) << 6) | (b1__i & 0x3F);
	character = f2char__new(cause, ch);
      }
    } else if ((b0__i & 0xF0) == 0xE0) {
      // utf8 three-byte character
      f2ptr b1 = f2__stream__try_read_byte(cause, this);
      if (! raw__integer__is_type(cause, b1)) {
	character = b1;
      } else {
	u64 b1__i = f2integer__i(b1, cause);
	f2ptr b2 = f2__stream__try_read_byte(cause, this);
	if (! raw__integer__is_type(cause, b2)) {
	  character = b2;
	} else {
	  u64 b2__i = f2integer__i(b2, cause);
	  funk2_character_t ch = ((b0__i & 0x0F) << 12) | ((b1__i & 0x3F) << 6) | (b2__i & 0x3F);
	  character = f2char__new(cause, ch);
	}
      }
    } else if ((b0__i & 0xF8) == 0xF0) {
      // utf8 four-byte character
      f2ptr b1 = f2__stream__try_read_byte(cause, this);
      if (! raw__integer__is_type(cause, b1)) {
	character = b1;
      } else {
	u64 b1__i = f2integer__i(b1, cause);
	f2ptr b2 = f2__stream__try_read_byte(cause, this);
	if (! raw__integer__is_type(cause, b2)) {
	  character = b2;
	} else {
	  u64 b2__i = f2integer__i(b2, cause);
	  f2ptr b3 = f2__stream__try_read_byte(cause, this);
	  if (! raw__integer__is_type(cause, b3)) {
	    character = b3;
	  } else {
	    u64 b3__i = f2integer__i(b3, cause);
	    funk2_character_t ch = ((b0__i & 0x07) << 18) | ((b1__i & 0x3F) << 12) | ((b2__i & 0x3F) << 6) | (b3__i & 0x3F);
	    character = f2char__new(cause, ch);
	  }
	}
      }
    } else {
      // invalid character.
      character = f2char__new(cause, (funk2_character_t)0xFFFD);
    }
  }
  if (raw__eq(cause, character, __funk2.reader.char__newline)) {
    f2ptr line_num    = f2__stream__line_number(cause, this);
    u64   line_num__i = f2integer__i(line_num, cause);
    f2__stream__line_number__set(cause, this, f2integer__new(cause, line_num__i + 1));
    f2__stream__column_number__set(cause, this, f2integer__new(cause, 1));
  } else {
    f2ptr column_num    = f2__stream__column_number(cause, this);
    u64   column_num__i = f2integer__i(column_num, cause);
    f2__stream__column_number__set(cause, this, f2integer__new(cause, column_num__i + 1));
  }
  return character;
}
def_pcfunk1(stream__try_read_character, stream,
	    "",
	    return f2__stream__try_read_character(this_cause, stream));

f2ptr f2__stream__getc(f2ptr cause, f2ptr stream) {
  if (! raw__stream__is_type(cause, stream)) {error(nil, "raw__stream__getc error: stream isn't a stream.");}
  f2ptr read_character = nil;
  while (read_character == nil) {
    read_character = f2__stream__try_read_character(cause, stream);
    if (read_character == nil) {
      f2__this__fiber__yield(cause);
      raw__spin_sleep_yield();
    }
  }
  if (raw__exception__is_type(cause, read_character) && raw__eq(cause, f2exception__tag(read_character, cause), __funk2.reader.end_of_file_exception__symbol)) {
    status("f2__stream__getc() note: eof reached.");
  }
  return read_character;
}
def_pcfunk1(stream__getc, stream,
	    "",
	    return f2__stream__getc(this_cause, stream));

f2ptr f2__stream__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(stream,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__stream__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(stream__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__stream__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2stream__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2stream__primobject_type__new(cause);
  {char* slot_name = "try_read_byte";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_byte__funk);}
  {char* slot_name = "try_read_character";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__funk);}
  {char* slot_name = "rewind";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__funk);}
  {char* slot_name = "rewind_to_length";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.terminal_print_with_frame__funk);}
  return this;
}

// **

void f2__primobject__stream__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --
  
  // stream
  
  initialize_primobject_12_slot__defragment__fix_pointers(stream, cmutex, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index, line_number, column_number);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_byte__symbol);
  f2__primcfunk__init__defragment__fix_pointers(stream__try_read_byte);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_byte__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__symbol);
  f2__primcfunk__init__defragment__fix_pointers(stream__try_read_character);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__symbol);
  f2__primcfunk__init__defragment__fix_pointers(stream__rewind);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(stream__rewind_to_length);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(stream__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_stream.terminal_print_with_frame__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(file_stream__new);
  f2__primcfunk__init__defragment__fix_pointers(socket_stream__new);
  f2__primcfunk__init__defragment__fix_pointers(string_stream__new);
  f2__primcfunk__init__defragment__fix_pointers(string_stream);
  f2__primcfunk__init__defragment__fix_pointers(stream__new_open_file);
  f2__primcfunk__init__defragment__fix_pointers(stream__close);
  f2__primcfunk__init__defragment__fix_pointers(stream__file_mode__rdonly);
  f2__primcfunk__init__defragment__fix_pointers(stream__file_mode__creat);
  f2__primcfunk__init__defragment__fix_pointers(stream__file_mode__rdwr);
  f2__primcfunk__init__defragment__fix_pointers(stream__nonblocking__set);
  f2__primcfunk__init__defragment__fix_pointers(stream__ungetc);
  f2__primcfunk__init__defragment__fix_pointers(stream__getc);


  defragment__fix_pointer(__file_stream__symbol);
  defragment__fix_pointer(__socket_stream__symbol);
  defragment__fix_pointer(__string_stream__symbol);
  defragment__fix_pointer(__text_window_stream__symbol);
  
}

void f2__primobject__stream__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  // stream
  
  initialize_primobject_12_slot(stream, cmutex, stream_type, ungetb_stack, rewind_stack, rewindable, rewind_length, file_handle, string, index, character_byte_index, line_number, column_number);
  
  {char* symbol_str = "try_read_byte"; __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_byte__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__try_read_byte, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_byte__funk = never_gc(cfunk);}
  {char* symbol_str = "try_read_character"; __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__try_read_character, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewind, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind_to_length"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewind_to_length, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_stream.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_stream.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  f2__primcfunk__init(file_stream__new);
  f2__primcfunk__init(socket_stream__new);
  f2__primcfunk__init(string_stream__new);
  f2__primcfunk__init(string_stream);
  f2__primcfunk__init(stream__new_open_file);
  f2__primcfunk__init(stream__close);
  f2__primcfunk__init(stream__file_mode__rdonly);
  f2__primcfunk__init(stream__file_mode__creat);
  f2__primcfunk__init(stream__file_mode__rdwr);
  f2__primcfunk__init(stream__nonblocking__set);
  f2__primcfunk__init__2(stream__ungetc, this, character);
  f2__primcfunk__init__1(stream__getc,   this);
  
  
  __file_stream__symbol        = new__symbol(cause, "file_stream");
  __socket_stream__symbol      = new__symbol(cause, "socket_stream");
  __string_stream__symbol      = new__symbol(cause, "string_stream");
  __text_window_stream__symbol = new__symbol(cause, "text_window_stream");
  
}

void f2__primobject__stream__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-stream", "", &f2__primobject__stream__reinitialize_globalvars, &f2__primobject__stream__defragment__fix_pointers);
  
  f2__primobject__stream__reinitialize_globalvars();
}

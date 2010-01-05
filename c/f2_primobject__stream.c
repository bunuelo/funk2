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

// stream primobject definition

defprimobject__static_slot(stream__type,            0);
defprimobject__static_slot(stream__ungetc_stack,    1);
defprimobject__static_slot(stream__rewind_stack,    2);
defprimobject__static_slot(stream__rewindable,      3);
defprimobject__static_slot(stream__rewind_length,   4);
defprimobject__static_slot(stream__file_descriptor, 5);
defprimobject__static_slot(stream__string,          6);
defprimobject__static_slot(stream__index,           7);

f2ptr __stream__symbol             = -1;
f2ptr __file_stream__symbol        = -1;
f2ptr __string_stream__symbol      = -1;
f2ptr __text_window_stream__symbol = -1;

f2ptr f2stream__new(f2ptr cause, f2ptr type, f2ptr ungetc_stack, f2ptr rewind_stack, f2ptr rewindable, f2ptr rewind_length, f2ptr file_descriptor, f2ptr string, f2ptr index) {
  if (__stream__symbol == -1) {__stream__symbol = f2symbol__new(cause, strlen("stream"), (u8*)"stream");}
  f2ptr this = f2__primobject__new(cause, __stream__symbol, 8, nil);
  f2stream__type__set(           this, cause, type);
  f2stream__ungetc_stack__set(   this, cause, ungetc_stack);
  f2stream__rewind_stack__set(   this, cause, rewind_stack);
  f2stream__rewindable__set(     this, cause, rewindable);
  f2stream__rewind_length__set(  this, cause, rewind_length);
  f2stream__file_descriptor__set(this, cause, file_descriptor);
  f2stream__string__set(         this, cause, string);
  f2stream__index__set(          this, cause, index);
  return this;
}

boolean_t raw__stream__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PRIMOBJECT__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PRIMOBJECT__TYPE_CHECK
  return (raw__primobject__is_type(cause, x) && f2primobject__is__stream(x, cause));
}
f2ptr f2__stream__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__stream__is_type(cause, x));}
def_pcfunk1(stream__is_type, x, return f2__stream__is_type(this_cause, x));

f2ptr f2__stream__new(f2ptr cause, f2ptr type, f2ptr ungetc_stack, f2ptr rewind_stack, f2ptr rewindable, f2ptr rewind_length, f2ptr file_descriptor, f2ptr string, f2ptr index) {return f2stream__new(cause, type, ungetc_stack, rewind_stack, rewindable, rewind_length, file_descriptor, string, index);}
def_pcfunk8(stream__new, type, ungetc_stack, rewind_stack, rewindable, rewind_length, file_descriptor, string, index, return f2__stream__new(this_cause, type, ungetc_stack, rewind_stack, rewindable, rewind_length, file_descriptor, string, index));

f2ptr f2__stream__type(f2ptr cause, f2ptr this) {return f2stream__type(this, cause);}
def_pcfunk1(stream__type, x, return f2__stream__type(this_cause, x));

f2ptr f2__stream__type__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__type__set(this, cause, value);}
def_pcfunk2(stream__type__set, x, y, return f2__stream__type__set(this_cause, x, y));

f2ptr f2__stream__ungetc_stack(f2ptr cause, f2ptr this) {return f2stream__ungetc_stack(this, cause);}
def_pcfunk1(stream__ungetc_stack, x, return f2__stream__ungetc_stack(this_cause, x));

f2ptr f2__stream__ungetc_stack__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__ungetc_stack__set(this, cause, value);}
def_pcfunk2(stream__ungetc_stack__set, x, y, return f2__stream__ungetc_stack__set(this_cause, x, y));

f2ptr f2__stream__rewind_stack(f2ptr cause, f2ptr this) {return f2stream__rewind_stack(this, cause);}
def_pcfunk1(stream__rewind_stack, x, return f2__stream__rewind_stack(this_cause, x));

f2ptr f2__stream__rewind_stack__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__rewind_stack__set(this, cause, value);}
def_pcfunk2(stream__rewind_stack__set, x, y, return f2__stream__rewind_stack__set(this_cause, x, y));

f2ptr f2__stream__rewindable(f2ptr cause, f2ptr this) {return f2stream__rewindable(this, cause);}
def_pcfunk1(stream__rewindable, x, return f2__stream__rewindable(this_cause, x));

f2ptr f2__stream__rewindable__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__rewindable__set(this, cause, value);}
def_pcfunk2(stream__rewindable__set, x, y, return f2__stream__rewindable__set(this_cause, x, y));

f2ptr f2__stream__rewind_length(f2ptr cause, f2ptr this) {return f2stream__rewind_length(this, cause);}
def_pcfunk1(stream__rewind_length, x, return f2__stream__rewind_length(this_cause, x));

f2ptr f2__stream__rewind_length__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__rewind_length__set(this, cause, value);}
def_pcfunk2(stream__rewind_length__set, x, y, return f2__stream__rewind_length__set(this_cause, x, y));

f2ptr f2__stream__file_descriptor(f2ptr cause, f2ptr this) {return f2stream__file_descriptor(this, cause);}
def_pcfunk1(stream__file_descriptor, x, return f2__stream__file_descriptor(this_cause, x));

f2ptr f2__stream__file_descriptor__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__file_descriptor__set(this, cause, value);}
def_pcfunk2(stream__file_descriptor__set, x, y, return f2__stream__file_descriptor__set(this_cause, x, y));

f2ptr f2__stream__string(f2ptr cause, f2ptr this) {return f2stream__string(this, cause);}
def_pcfunk1(stream__string, x, return f2__stream__string(this_cause, x));

f2ptr f2__stream__string__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__string__set(this, cause, value);}
def_pcfunk2(stream__string__set, x, y, return f2__stream__string__set(this_cause, x, y));

f2ptr f2__stream__index(f2ptr cause, f2ptr this) {return f2stream__index(this, cause);}
def_pcfunk1(stream__index, x, return f2__stream__index(this_cause, x));

f2ptr f2__stream__index__set(f2ptr cause, f2ptr this, f2ptr value) {return f2stream__index__set(this, cause, value);}
def_pcfunk2(stream__index__set, x, y, return f2__stream__index__set(this_cause, x, y));




f2ptr f2__file_stream__new(f2ptr cause, f2ptr file_descriptor) {
  if (__file_stream__symbol == -1) {__file_stream__symbol = f2symbol__new(cause, strlen("file_stream"), (u8*)"file_stream");}
  boolean_t rewindable = boolean__true;
  f2ptr rewind_length = f2integer__new(cause, 0);
  return f2stream__new(cause, __file_stream__symbol, nil, nil, f2bool__new(rewindable), rewind_length, file_descriptor, nil, nil);
}
def_pcfunk1(file_stream__new, file_descriptor, return f2__file_stream__new(this_cause, file_descriptor));

boolean_t raw__file_stream__is_type(f2ptr cause, f2ptr this) {
  if (__file_stream__symbol == -1) {__file_stream__symbol = f2symbol__new(cause, strlen("file_stream"), (u8*)"file_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__type(this, cause), __file_stream__symbol));
}
f2ptr f2__file_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__file_stream__is_type(cause, this));}

f2ptr f2__string_stream__new(f2ptr cause, f2ptr string, f2ptr index) {
  if (__string_stream__symbol == -1) {__string_stream__symbol = f2symbol__new(cause, strlen("string_stream"), (u8*)"string_stream");}
  boolean_t rewindable = boolean__true;
  f2ptr rewind_length = f2integer__new(cause, 0);
  return f2stream__new(cause, __string_stream__symbol, nil, nil, f2bool__new(rewindable), rewind_length, nil, string, index);
}
def_pcfunk2(string_stream__new, string, index, return f2__string_stream__new(this_cause, string, index));

boolean_t raw__string_stream__is_type(f2ptr cause, f2ptr this) {
  if (__string_stream__symbol == -1) {__string_stream__symbol = f2symbol__new(cause, strlen("string_stream"), (u8*)"string_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__type(this, cause), __string_stream__symbol));
}
f2ptr f2__string_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__string_stream__is_type(cause, this));}

f2ptr f2__string_stream(f2ptr cause, f2ptr string) {
  return f2__string_stream__new(cause, string, f2integer__new(cause, 0));
}
def_pcfunk1(string_stream, string, return f2__string_stream(this_cause, string));

f2ptr raw__stream__new_open_file(f2ptr cause, char* filename, int mode) {
  int fd = open(filename, mode);
  if (fd == -1) {
    return nil;
  }
  return f2__file_stream__new(cause, f2integer__new(cause, fd));
}

f2ptr f2__stream__new_open_file(f2ptr cause, f2ptr filename, f2ptr mode) {
  if ((! raw__string__is_type(cause, filename)) || 
      (! raw__integer__is_type(cause, mode))) {
    return f2larva__new(cause, 1);
  }
  u64   filename__length = f2string__length(filename, cause);
  char* raw_filename = alloca(filename__length + 1);
  f2string__str_copy(filename, cause, (u8*)raw_filename);
  raw_filename[filename__length] = 0;
  u64 raw_mode = f2integer__i(mode, cause);
  return raw__stream__new_open_file(cause, raw_filename, raw_mode);
}
def_pcfunk2(stream__new_open_file, filename, mode, return f2__stream__new_open_file(this_cause, filename, mode));

f2ptr f2__file_stream__close(f2ptr cause, f2ptr this) {
  if ((! raw__file_stream__is_type(cause, this))) {
    return f2larva__new(cause, 1);
  }
  f2ptr file_descriptor = f2stream__file_descriptor(this, cause);
  if (! raw__integer__is_type(cause, file_descriptor)) {
    return f2larva__new(cause, 1);
  }
  int fd = f2integer__i(file_descriptor, cause);
  int result = close(fd);
  if (result == -1) {
    return nil;
  }
  return f2integer__new(cause, result);
}

f2ptr f2__stream__close(f2ptr cause, f2ptr this) {
  if (raw__file_stream__is_type(cause, this)) {
    return f2__file_stream__close(cause, this);
  } else if (raw__string_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk1(stream__close, this, return f2__stream__close(this_cause, this));

f2ptr f2__stream__file_mode__rdonly(f2ptr cause) {return f2integer__new(cause, O_RDONLY);}
def_pcfunk0(stream__file_mode__rdonly, return f2__stream__file_mode__rdonly(this_cause));

f2ptr f2__stream__file_mode__creat(f2ptr cause)  {return f2integer__new(cause, O_CREAT);}
def_pcfunk0(stream__file_mode__creat, return f2__stream__file_mode__creat(this_cause));

f2ptr f2__stream__file_mode__rdwr(f2ptr cause)   {return f2integer__new(cause, O_RDWR);}
def_pcfunk0(stream__file_mode__rdwr, return f2__stream__file_mode__rdwr(this_cause));

f2ptr f2__stream__new_open_file__rdonly(f2ptr cause, f2ptr filename) {
  f2ptr mode = f2__stream__file_mode__rdonly(cause);
  return f2__stream__new_open_file(cause, filename, mode);
}

f2ptr f2__stream__new_open_file__rdwr(f2ptr cause, f2ptr filename) {
  f2ptr mode = f2__stream__file_mode__rdwr(cause);
  return f2__stream__new_open_file(cause, filename, mode);
}

int raw__file_stream__nonblocking__set(f2ptr cause, f2ptr this, boolean_t value) {
  f2ptr file_descriptor = f2stream__file_descriptor(this, cause);
  u64 fd                = f2integer__i(file_descriptor, cause);
  return file_descriptor__set_nonblocking(fd, value);
}

f2ptr f2__file_stream__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__file_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__file_stream__nonblocking__set(cause, this, (value != nil));
}

f2ptr f2__stream__nonblocking__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (raw__file_stream__is_type(cause, this)) {
    return f2__file_stream__nonblocking__set(cause, this, value);
  }
  return f2larva__new(cause, 1);
}
def_pcfunk2(stream__nonblocking__set, this, value, return f2__stream__nonblocking__set(this_cause, this, value));

f2ptr f2__stream__ungetc(f2ptr cause, f2ptr this, f2ptr character) {
  if (! raw__stream__is_type(cause, this)) {error(nil, "raw__stream__ungetc error: this must be stream."); return f2larva__new(cause, 1);}
  if ((! raw__char__is_type(cause, character)) && (! raw__exception__is_type(cause, character))) {error(nil, "raw__stream__ungetc error: character must be char or exception."); return f2larva__new(cause, 1);}
  f2ptr rewind_character = f2__stream__rewind(cause, this);
  if (! raw__eq(cause, character, rewind_character)) {
    error(nil, "ungetc rewind character mismatch.");
  }
  //f2ptr ungetc_stack = f2stream__ungetc_stack(this, cause);
  //f2ptr new_cons = f2cons__new(cause, character, ungetc_stack);
  //f2stream__ungetc_stack__set(this, cause, new_cons);
  return nil;
}
def_pcfunk2(stream__ungetc, this, character, return f2__stream__ungetc(this_cause, this, character));

void raw__stream__ungetc(f2ptr cause, f2ptr this, char ch) {
  f2ptr character = f2char__new(cause, ch);
  f2__stream__ungetc(cause, this, character);
}

f2ptr f2__file_stream__try_ungetcless_read_character(f2ptr cause, f2ptr this) {
  if (! raw__file_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr file_descriptor = f2stream__file_descriptor(this, cause);
  if (! raw__integer__is_type(cause, file_descriptor)) {return f2larva__new(cause, 17);}
  u64 fd = f2integer__i(file_descriptor, cause);
  u8  data[2] = {0, 0};
  u32 bytes_read = 0;
  read_nonblocking_result_t result = read_nonblocking(fd, data, 1, &bytes_read);
  switch (result) {
  case read_nonblocking_result__success:
    if (bytes_read == 1) {
      return f2char__new(cause, data[0]);
    }
    break;
  case read_nonblocking_result__end_of_file:
    return __funk2.reader.end_of_file_exception;
  case read_nonblocking_result__read_failure:
  case read_nonblocking_result__select_failure:
  case read_nonblocking_result__unknown_failure:
    break;
  }
  return nil;
}

f2ptr f2__string_stream__try_ungetcless_read_character(f2ptr cause, f2ptr this) {
  if (! raw__string_stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr string = f2stream__string(this, cause);
  f2ptr index  = f2stream__index( this, cause);
  u64 string_length = f2string__length(string, cause);
  u64 raw_index     = f2integer__i(index, cause);
  if (raw_index < string_length) {
    f2ptr return_value = f2char__new(cause, f2string__elt(string, raw_index, cause));
    raw_index ++;
    f2stream__index__set(this, cause, f2integer__new(cause, raw_index));
    return return_value;
  }
  return __funk2.reader.end_of_file_exception;
}

f2ptr f2__stream__try_read_character(f2ptr cause, f2ptr this) {
  f2ptr character = nil;
  if (! raw__stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr ungetc_stack = f2stream__ungetc_stack(this, cause);
  if (ungetc_stack) {
    character = f2cons__car(ungetc_stack, cause);
    f2stream__ungetc_stack__set(this, cause, f2cons__cdr(ungetc_stack, cause));
  }
  if (! character) {
    if (raw__file_stream__is_type(cause, this)) {
      character = f2__file_stream__try_ungetcless_read_character(cause, this);
    } else if (raw__string_stream__is_type(cause, this)) {
      character = f2__string_stream__try_ungetcless_read_character(cause, this);
    }
  }
  if (character && f2stream__rewindable(this, cause)) {
    f2stream__rewind_stack__set(this, cause, f2cons__new(cause, character, f2stream__rewind_stack(this, cause)));
    f2ptr rewind_length = f2stream__rewind_length(this, cause);
    if (! raw__integer__is_type(cause, rewind_length)) {
      return f2larva__new(cause, 1);
    }
    s64 rewind_length__i = f2integer__i(rewind_length, cause);
    f2stream__rewind_length__set(this, cause, f2integer__new(cause, rewind_length__i + 1));
  }
  return character;
}
def_pcfunk1(stream__try_read_character, stream, return f2__stream__try_read_character(this_cause, stream));

f2ptr f2__stream__getc(f2ptr cause, f2ptr stream) {
  if (! raw__stream__is_type(cause, stream)) {error(nil, "raw__stream__getc error: stream isn't a stream.");}
  f2ptr read_ch = nil;
  while (read_ch == nil) {
    read_ch = f2__stream__try_read_character(cause, stream);
    if (read_ch == nil) {
      f2__scheduler__yield(cause);
      raw__spin_sleep_yield();
    }
  }
  if (raw__exception__is_type(cause, read_ch) && raw__eq(cause, f2exception__tag(read_ch, cause), __funk2.reader.end_of_file_exception__symbol)) {
    status("f2__stream__getc() note: eof reached.");
  }
  return read_ch;
}
def_pcfunk1(stream__getc, stream, return f2__stream__getc(this_cause, stream));

f2ptr f2__stream__rewind(f2ptr cause, f2ptr this) {
  if (! raw__stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr rewind_stack = f2stream__rewind_stack(this, cause);
  if (! rewind_stack) {
    return f2larva__new(cause, 234);
  }
  if (! raw__cons__is_type(cause, rewind_stack)) {
    return f2larva__new(cause, 2);
  }
  f2ptr character = f2cons__car(rewind_stack, cause);
  f2stream__rewind_stack__set(this, cause, f2cons__cdr(rewind_stack, cause));
  f2stream__ungetc_stack__set(this, cause, f2cons__new(cause, character, f2stream__ungetc_stack(this, cause)));
  f2ptr rewind_length = f2stream__rewind_length(this, cause);
  if (! raw__integer__is_type(cause, rewind_length)) {
    return f2larva__new(cause, 3);
  }
  s64 rewind_length__i = f2integer__i(rewind_length, cause);
  f2ptr new_rewind_length = f2integer__new(cause, rewind_length__i - 1);
  f2stream__rewind_length__set(this, cause, new_rewind_length);
  return character;
}
def_pcfunk1(stream__rewind, stream, return f2__stream__getc(this_cause, stream));

f2ptr raw__stream__rewind_to_length(f2ptr cause, f2ptr this, s64 length) {
  if (! raw__stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr rewind_length = f2stream__rewind_length(this, cause);
  if (! raw__integer__is_type(cause, rewind_length)) {
    return f2larva__new(cause, 3);
  }
  s64 rewind_length__i = f2integer__i(rewind_length, cause);
  if (rewind_length__i < length) {
    return f2larva__new(cause, 338);
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
  if (! raw__integer__is_type(cause, length)) {
    return f2larva__new(cause, 1);
  }
  return raw__stream__rewind_to_length(cause, this, f2integer__i(length, cause));
}
def_pcfunk2(stream__rewind_to_length, this, length, return f2__stream__rewind_to_length(this_cause, this, length));

f2ptr f2stream__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, nil);
  {char* slot_name = "is_type";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.is_type__funk);}
  {char* slot_name = "new";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.new__funk);}
  {char* slot_name = "type";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.type__funk);}
  {char* slot_name = "type";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.type__set__funk);}
  {char* slot_name = "ungetc_stack";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.ungetc_stack__funk);}
  {char* slot_name = "ungetc_stack";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.ungetc_stack__set__funk);}
  {char* slot_name = "rewind_stack";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_stack__funk);}
  {char* slot_name = "rewind_stack";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_stack__set__funk);}
  {char* slot_name = "rewindable";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewindable__funk);}
  {char* slot_name = "rewindable";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewindable__set__funk);}
  {char* slot_name = "rewind_length";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_length__funk);}
  {char* slot_name = "rewind_length";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_length__set__funk);}
  {char* slot_name = "file_descriptor";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.file_descriptor__funk);}
  {char* slot_name = "file_descriptor";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.file_descriptor__set__funk);}
  {char* slot_name = "string";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.string__funk);}
  {char* slot_name = "string";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.string__set__funk);}
  {char* slot_name = "index";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.index__funk);}
  {char* slot_name = "index";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.index__set__funk);}
  {char* slot_name = "try_read_character"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__funk);}
  {char* slot_name = "rewind";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__funk);}
  {char* slot_name = "rewind_to_length";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__funk);}
  return this;
}


// **

void f2__primobject__stream__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __stream__symbol             = f2symbol__new(cause, strlen("stream"),             (u8*)"stream");
  __file_stream__symbol        = f2symbol__new(cause, strlen("file_stream"),        (u8*)"file_stream");
  __string_stream__symbol      = f2symbol__new(cause, strlen("string_stream"),      (u8*)"string_stream");
  __text_window_stream__symbol = f2symbol__new(cause, strlen("text_window_stream"), (u8*)"text_window_stream");
}

void f2__primobject__stream__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__stream", "", &f2__primobject__stream__reinitialize_globalvars);
  
  f2__primobject__stream__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // stream
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.primobject_type_stream.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_stream.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var(stream__new, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.new__funk = never_gc(cfunk);}
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.primobject_type_stream.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.type__funk = never_gc(cfunk);}
  {char* symbol_str = "type-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.type__set__funk = never_gc(cfunk);}
  {char* symbol_str = "ungetc_stack"; __funk2.globalenv.object_type.primobject.primobject_type_stream.ungetc_stack__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__ungetc_stack, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.ungetc_stack__funk = never_gc(cfunk);}
  {char* symbol_str = "ungetc_stack-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.ungetc_stack__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__ungetc_stack__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.ungetc_stack__set__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind_stack"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_stack__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewind_stack, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_stack__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind_stack-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_stack__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__rewind_stack__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_stack__set__funk = never_gc(cfunk);}
  {char* symbol_str = "rewindable"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewindable__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewindable, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewindable__funk = never_gc(cfunk);}
  {char* symbol_str = "rewindable-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewindable__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__rewindable__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewindable__set__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind_length"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_length__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewind_length, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_length__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind_length-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_length__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__rewind_length__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_length__set__funk = never_gc(cfunk);}
  {char* symbol_str = "file_descriptor"; __funk2.globalenv.object_type.primobject.primobject_type_stream.file_descriptor__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__file_descriptor, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.file_descriptor__funk = never_gc(cfunk);}
  {char* symbol_str = "file_descriptor-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.file_descriptor__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__file_descriptor__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.file_descriptor__set__funk = never_gc(cfunk);}
  {char* symbol_str = "string"; __funk2.globalenv.object_type.primobject.primobject_type_stream.string__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__string, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.string__funk = never_gc(cfunk);}
  {char* symbol_str = "string-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.string__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__string__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.string__set__funk = never_gc(cfunk);}
  {char* symbol_str = "index"; __funk2.globalenv.object_type.primobject.primobject_type_stream.index__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__index, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.index__funk = never_gc(cfunk);}
  {char* symbol_str = "index-set"; __funk2.globalenv.object_type.primobject.primobject_type_stream.index__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(stream__index__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.index__set__funk = never_gc(cfunk);}
  {char* symbol_str = "try_read_character"; __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__try_read_character, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.try_read_character__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewind, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind__funk = never_gc(cfunk);}
  {char* symbol_str = "rewind_to_length"; __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(stream__rewind_to_length, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_stream.rewind_to_length__funk = never_gc(cfunk);}
  
  f2__primcfunk__init(file_stream__new, "");
  f2__primcfunk__init(string_stream__new, "");
  f2__primcfunk__init(string_stream, "");
  f2__primcfunk__init(stream__new_open_file, "");
  f2__primcfunk__init(stream__close, "");
  f2__primcfunk__init(stream__file_mode__rdonly, "");
  f2__primcfunk__init(stream__file_mode__creat, "");
  f2__primcfunk__init(stream__file_mode__rdwr, "");
  f2__primcfunk__init(stream__nonblocking__set, "");
  f2__primcfunk__init__2(stream__ungetc,             this, character, "");
  f2__primcfunk__init__1(stream__try_read_character, this, "");
  f2__primcfunk__init__1(stream__getc,               this, "");
  f2__primcfunk__init__1(stream__rewind, this, "");
  f2__primcfunk__init__2(stream__rewind_to_length, this, length, "");
}


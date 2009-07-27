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
defprimobject__static_slot(stream__file_descriptor, 2);
defprimobject__static_slot(stream__string,          3);
defprimobject__static_slot(stream__index,           4);

f2ptr __stream__symbol             = -1;
f2ptr __file_stream__symbol        = -1;
f2ptr __string_stream__symbol      = -1;
f2ptr __text_window_stream__symbol = -1;

f2ptr f2stream__new(f2ptr cause, f2ptr type, f2ptr ungetc_stack, f2ptr file_descriptor, f2ptr string, f2ptr index) {
  if (__stream__symbol == -1) {__stream__symbol = f2symbol__new(cause, strlen("stream"), (u8*)"stream");}
  f2ptr this = f2__primobject__new(cause, __stream__symbol, 5, nil);
  f2stream__type__set(           this, cause, type);
  f2stream__ungetc_stack__set(   this, cause, ungetc_stack);
  f2stream__file_descriptor__set(this, cause, file_descriptor);
  f2stream__string__set(         this, cause, string);
  f2stream__index__set(          this, cause, index);
  return this;
}

boolean_t raw__stream__is_type(f2ptr cause, f2ptr this) {return (raw__array__is_type(cause, this) && raw__array__length(cause, this) >= 2 && f2primobject__is__stream(this, cause));}
f2ptr f2__stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__stream__is_type(cause, this));}

f2ptr f2__file_stream__new(f2ptr cause, f2ptr file_descriptor) {
  if (__file_stream__symbol == -1) {__file_stream__symbol = f2symbol__new(cause, strlen("file_stream"), (u8*)"file_stream");}
  return f2stream__new(cause, __file_stream__symbol, nil, file_descriptor, nil, nil);
}
def_pcfunk1(file_stream__new, file_descriptor, return f2__file_stream__new(this_cause, file_descriptor));

boolean_t raw__file_stream__is_type(f2ptr cause, f2ptr this) {
  if (__file_stream__symbol == -1) {__file_stream__symbol = f2symbol__new(cause, strlen("file_stream"), (u8*)"file_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__type(this, cause), __file_stream__symbol));
}
f2ptr f2__file_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__file_stream__is_type(cause, this));}

f2ptr f2__string_stream__new(f2ptr cause, f2ptr string, f2ptr index) {
  if (__string_stream__symbol == -1) {__string_stream__symbol = f2symbol__new(cause, strlen("string_stream"), (u8*)"string_stream");}
  return f2stream__new(cause, __string_stream__symbol, nil, nil, string, index);
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
  if (! raw__char__is_type(cause, character)) {error(nil, "raw__stream__ungetc error: character must be char."); return f2larva__new(cause, 1);}
  f2ptr ungetc_stack = f2stream__ungetc_stack(this, cause);
  f2ptr new_cons = f2cons__new(cause, character, ungetc_stack);
  f2stream__ungetc_stack__set(this, cause, new_cons);
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
    return f2symbol__new(cause, strlen("eof"), (u8*)"eof");
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
  return f2symbol__new(cause, strlen("eof"), (u8*)"eof");
}

f2ptr f2__stream__try_read_character(f2ptr cause, f2ptr this) {
  if (! raw__stream__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  f2ptr ungetc_stack    = f2stream__ungetc_stack(this, cause);
  if (ungetc_stack) {
    f2ptr character = f2cons__car(ungetc_stack, cause);
    f2stream__ungetc_stack__set(this, cause, f2cons__cdr(ungetc_stack, cause));
    return character;
  }
  if (raw__file_stream__is_type(cause, this)) {
    return f2__file_stream__try_ungetcless_read_character(cause, this);
  } else if (raw__string_stream__is_type(cause, this)) {
    return f2__string_stream__try_ungetcless_read_character(cause, this);
  } else {
    return nil;
  }
}
def_pcfunk1(stream__try_read_character, stream, return f2__stream__try_read_character(this_cause, stream));

f2ptr f2__text_window_stream__new(f2ptr cause, f2ptr text_window) {
  if (__text_window_stream__symbol == -1) {__text_window_stream__symbol = f2symbol__new(cause, strlen("text_window_stream"), (u8*)"text_window_stream");}
  return f2stream__new(cause, __text_window_stream__symbol, nil, nil, text_window, nil);
}
def_pcfunk1(text_window_stream__new, text_window, return f2__text_window_stream__new(this_cause, text_window));

boolean_t raw__text_window_stream__is_type(f2ptr cause, f2ptr this) {
  if (__text_window_stream__symbol == -1) {__text_window_stream__symbol = f2symbol__new(cause, strlen("text_window_stream"), (u8*)"text_window_stream");}
  return (raw__stream__is_type(cause, this) && f2__symbol__eq(cause, f2stream__type(this, cause), __text_window_stream__symbol));
}
f2ptr f2__text_window_stream__is_type(f2ptr cause, f2ptr this) {return f2bool__new(raw__text_window_stream__is_type(cause, this));}

f2ptr f2__text_window_stream(f2ptr cause, f2ptr text_window) {
  return f2__text_window_stream__new(cause, text_window);
}
def_pcfunk1(text_window_stream, text_window, return f2__text_window_stream(this_cause, text_window));

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
  
  pause_gc();
  f2__primobject__stream__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __stream__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __file_stream__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __string_stream__symbol,      nil);
  environment__add_var_value(cause, global_environment(), __text_window_stream__symbol, nil);
  
  f2__primcfunk__init(file_stream__new, "");
  f2__primcfunk__init(string_stream__new, "");
  f2__primcfunk__init(string_stream, "");
  f2__primcfunk__init(stream__new_open_file, "");
  f2__primcfunk__init(stream__close, "");
  f2__primcfunk__init(stream__file_mode__rdonly, "");
  f2__primcfunk__init(stream__file_mode__creat, "");
  f2__primcfunk__init(stream__file_mode__rdwr, "");
  f2__primcfunk__init(stream__nonblocking__set, "");
  f2__primcfunk__init(stream__ungetc, "");
  f2__primcfunk__init(stream__try_read_character, "");
  f2__primcfunk__init(text_window_stream__new, "");
  f2__primcfunk__init(text_window_stream, "");
  
  resume_gc();
}


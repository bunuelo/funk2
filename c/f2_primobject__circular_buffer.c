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


// circular_buffer primobject definition

defprimobject__static_slot(circular_buffer__start,     0);
defprimobject__static_slot(circular_buffer__end,       1);
defprimobject__static_slot(circular_buffer__bin_array, 2);

f2ptr f2circular_buffer__new(f2ptr cause, f2ptr start, f2ptr end, f2ptr bin_array) {
  release__assert(__funk2.primobject__circular_buffer.symbol != -1, nil, "f2circular_buffer__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __funk2.primobject__circular_buffer.symbol, 3, nil);
  f2circular_buffer__start__set(    this, cause, start);
  f2circular_buffer__end__set(      this, cause, end);
  f2circular_buffer__bin_array__set(this, cause, bin_array);
  return this;
}

boolean_t raw__circular_bufferp(f2ptr this, f2ptr cause) {
  return raw__arrayp(this, cause) && f2primobject__is_circular_buffer(this, cause);
}

f2ptr f2__circular_bufferp(f2ptr this, f2ptr cause) {
  return f2bool__new(raw__circular_bufferp(this, cause));
}

f2ptr raw__circular_buffer__new_empty(f2ptr cause, u64 length) {
  return f2circular_buffer__new(cause, f2integer__new(cause, 0), f2integer__new(cause, 0), raw__array__new(cause, length));
}

f2ptr f2__circular_buffer__remove(f2ptr cause, f2ptr this) {
  u64 raw_start = f2integer__i(f2circular_buffer__start(this, cause), cause);
  u64 raw_end   = f2integer__i(f2circular_buffer__end(this, cause), cause);
  if (raw_start == raw_end) {
    return __funk2.primobject__circular_buffer.empty__symbol;
  }
  f2ptr bin_array = f2circular_buffer__bin_array(this, cause);
  u64   bin_array__length = raw__array__length(cause, bin_array);
  f2ptr elt = raw__array__elt(cause, bin_array, raw_start);
  raw_start ++;
  if (raw_start == bin_array__length) {
    raw_start = 0;
  }
  f2circular_buffer__start__set(this, cause, f2integer__new(cause, raw_start));
  return elt;
}

f2ptr f2__circular_buffer__add(f2ptr cause, f2ptr this, f2ptr value) {
  u64   raw_start         = f2integer__i(f2circular_buffer__start(this, cause), cause);
  u64   raw_end           = f2integer__i(f2circular_buffer__end(this, cause), cause);
  f2ptr bin_array         = f2circular_buffer__bin_array(this, cause);
  u64   bin_array__length = raw__array__length(cause, bin_array);
  u64 next_end = raw_end + 1;
  if (next_end == bin_array__length) {
    next_end = 0;
  }
  if (next_end == raw_start) {
    return __funk2.primobject__circular_buffer.full__symbol;
  }
  raw__array__elt__set(cause, bin_array, raw_end, value);
  f2circular_buffer__end__set(this, cause, f2integer__new(cause, next_end));
  return nil;
}

boolean_t raw__circular_buffer__is_empty(f2ptr cause, f2ptr this) {
  f2ptr start = f2circular_buffer__start(this, cause);
  f2ptr end   = f2circular_buffer__end(this, cause);
  u64 raw_start = f2integer__i(start, cause);
  u64 raw_end   = f2integer__i(end, cause);
  return (raw_start == raw_end);
}

// **

void f2__primobject_circular_buffer__reinitialize_globalvars() {
  __funk2.primobject__circular_buffer.symbol        = f2symbol__new(initial_cause(), strlen("circular_buffer"),       (u8*)"circular_buffer");
  __funk2.primobject__circular_buffer.empty__symbol = f2symbol__new(initial_cause(), strlen("circular_buffer-empty"), (u8*)"circular_buffer-empty");
  __funk2.primobject__circular_buffer.full__symbol  = f2symbol__new(initial_cause(), strlen("circular_buffer-full"),  (u8*)"circular_buffer-full");
}

void f2__primobject_circular_buffer__initialize() {
  pause_gc();
  f2__primobject_circular_buffer__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __funk2.primobject__circular_buffer.symbol,        nil);
  environment__add_var_value(initial_cause(), global_environment(), __funk2.primobject__circular_buffer.empty__symbol, nil);
  environment__add_var_value(initial_cause(), global_environment(), __funk2.primobject__circular_buffer.full__symbol,  nil);
  
  resume_gc();
  try_gc();
}


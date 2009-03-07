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

f2ptr f2tracenode__find_prev__primobject_of_type(f2ptr tracenode, f2ptr cause, f2ptr type) {
  f2ptr iter = tracenode;
  while (iter) {
    f2ptr exp = f2tracenode__value(iter, cause);
    if (raw__primobjectp(exp, cause) && f2primobject__type(exp, cause) == type) {
      return iter;
    }
    iter = f2tracenode__prev(iter, cause);
  }
  return iter;
}

f2ptr f2tracenode__find_next__primobject_of_type(f2ptr tracenode, f2ptr cause, f2ptr type) {
  f2ptr iter = tracenode;
  while (iter) {
    f2ptr exp = f2tracenode__value(iter, cause);
    if (raw__primobjectp(exp, cause) && f2primobject__type(exp, cause) == type) {
      return iter;
    }
    iter = f2tracenode__next(iter, cause);
  }
  return iter;
}

f2ptr __do_not_remember__symbol = -1;

f2ptr raw__trace__remember__microseconds_since_1970(f2ptr cause, f2ptr this, u64 microseconds_since_1970, f2ptr* remember_value) {
  release__assert(__do_not_remember__symbol != -1, nil, "raw__trace__remember__microseconds_since_1970 assertion failed: __do_not_remember__symbol != -1");
  if (! this) {return __do_not_remember__symbol;}
  error(nil, "we can't use creation microseconds of block for this...  this funktionn is not fully implemented...");
  // we can't use creation microseconds of block for this...
  // u64 this__microseconds_since_1970 = memblock__creation_microseconds_since_1970(this, cause);
  if (microseconds_since_1970 > this__microseconds_since_1970) {
    *remember_value = raw__array__elt(cause, f2cons__car( f2transframe__symbol_old_news( f2doublelink__value( this, cause), cause), cause), 2);
    return this; // used for continued tracing from this location.
  }
  return raw__trace__remember__microseconds_since_1970( cause, f2doublelink__prev(this, cause), microseconds_since_1970, remember_value);
}

// note that initial and final modifiers are arbitrarily relative to the transframe (user choice, either [< initial final] or [< final initial]), whereas past and future modifiers are relative to the order of the run-time microseconds (i.e. [< past future] always holds).
f2ptr raw__trace__remember__trans__microseconds_since_1970(f2ptr cause, f2ptr this, u64 initial_microseconds, u64 final_microseconds, f2ptr* initial_value, f2ptr* final_value) {
  release__assert(__do_not_remember__symbol != -1, nil, "raw__trace__remember__trans__microseconds_since_1970 assertion failed: __do_not_remember__symbol != -1");
  if (! this) {return __do_not_remember__symbol;} // couldn't remember one or both values
  u64 past_microseconds, future_microseconds;
  bool initial_before_final = (initial_microseconds < final_microseconds);
  if (initial_before_final) {
    past_microseconds   = initial_microseconds;
    future_microseconds = final_microseconds;
  } else {
    past_microseconds   = final_microseconds;
    future_microseconds = initial_microseconds;
  }
  f2ptr past_value, future_value;
  this = raw__trace__remember__microseconds_since_1970(cause, this, future_microseconds, &future_value);
  this = raw__trace__remember__microseconds_since_1970(cause, this, past_microseconds,   &past_value);
  if (initial_before_final) {
    *initial_value = past_value;
    *final_value   = future_value;
  } else {
    *initial_value = future_value;
    *final_value   = past_value;
  }
  return this; // to be used for continued tracing from this location
}

f2ptr raw__array__elt__remember__microseconds_since_1970(f2ptr cause, f2ptr this, uint index, u64 microseconds_since_1970) {
  f2ptr remember_value;
  raw__trace__remember__microseconds_since_1970( cause, raw__array__elt__trace(cause, this, index), microseconds_since_1970, &remember_value);
  return remember_value;
}

f2ptr raw__array__elt__remember__trans__microseconds_since_1970(f2ptr cause, f2ptr this, uint index, u64 initial_microseconds, u64 final_microseconds, f2ptr* initial_value, f2ptr* final_value) {
  return raw__trace__remember__trans__microseconds_since_1970( cause, raw__array__elt__trace(cause, this, index), initial_microseconds, final_microseconds, initial_value, final_value);
}

f2ptr raw__exp__remember__microseconds_since_1970(f2ptr cause, f2ptr exp, u64 microseconds_since_1970) {
  if (! exp) {return nil;}
  switch(f2ptype__raw(exp, cause)) {
  case ptype_free_memory:
  case ptype_newly_allocated:
  case ptype_integer:
  case ptype_double:
  case ptype_float:
  case ptype_pointer:
  case ptype_gfunkptr:
  case ptype_mutex:
  case ptype_char:
  case ptype_string:
  case ptype_symbol:
  case ptype_chunk:
  case ptype_larva:
  case ptype_simple_array:
    return exp;
  case ptype_traced_array: {
    int this__length = f2traced_array__length(exp, cause);
    int i;
    f2ptr new_array = raw__array__new(cause, this__length);
    for (i = this__length - 1; i != 0; i --) {
      raw__array__elt__set(cause, new_array, i, raw__array__elt__remember__microseconds_since_1970(cause, exp, i, microseconds_since_1970));
    }
    return new_array;
  } break;
  }
  error(nil, "raw__exp__remember__microseconds_since_1970 error: shouldn't get here.");
  return nil;
}

f2ptr raw__exp__remember__trans__microseconds_since_1970(f2ptr cause, f2ptr exp, u64 initial_microseconds, u64 final_microseconds) {
  if (! exp) {return nil;}
  switch(f2ptype__raw(exp, cause)) {
  case ptype_free_memory:
  case ptype_newly_allocated:
  case ptype_integer:
  case ptype_double:
  case ptype_float:
  case ptype_pointer:
  case ptype_gfunkptr:
  case ptype_mutex:
  case ptype_char:
  case ptype_string:
  case ptype_symbol:
  case ptype_chunk:
  case ptype_larva:
  case ptype_simple_array:
    return exp;
  case ptype_traced_array: {
    int this__length = f2traced_array__length(exp, cause);
    int i;
    f2ptr symbol_old_news = nil;
    for (i = this__length - 1; i >= 0; i --) {
      f2ptr initial_value = __do_not_remember__symbol;
      f2ptr final_value   = __do_not_remember__symbol;
      raw__array__elt__remember__trans__microseconds_since_1970(cause, exp, i, initial_microseconds, final_microseconds, &initial_value, &final_value);
      if (initial_value != final_value) { // transframe assumption: only changes are listed in the transframe, or in other words, if something doesn't change, then it isn't listed in the transframe.
	f2ptr symbol_old_new = raw__array__new(cause, 3);
	raw__array__elt__set(cause, symbol_old_new, 0, f2integer__new(cause, i));
	raw__array__elt__set(cause, symbol_old_new, 1, initial_value);
	raw__array__elt__set(cause, symbol_old_new, 2, final_value);
	symbol_old_news = f2cons__new(cause, symbol_old_new, symbol_old_news);
      }
    }
    return f2transframe__new(cause, symbol_old_news);
  } break;
  }
  error(nil, "raw__exp__remember__microseconds_since_1970 error: shouldn't get here.");
  return nil;
}

void raw__array__tracing_on__set(f2ptr cause, f2ptr this, bool tracing_on) {
  int this__length = raw__array__length(cause, this);
  int i;
  for (i = this__length - 1; i != 0; i --) {
    raw__array__elt__tracing_on__set(cause, this, i, f2bool__new(tracing_on));
    raw__array__elt__set(cause, this, i, raw__array__elt(cause, this, i));
  }
}

// beginning of fast initialization

void f2__trace__reinitialize_globalvars() {
  {char *str = "do_not_remember"; __do_not_remember__symbol = f2symbol__new(initial_cause(), strlen(str), (u8*)str);}
}

void f2__trace__initialize() {
  pause_gc();
  f2__trace__reinitialize_globalvars();
  
  environment__add_var_value(initial_cause(), global_environment(), __do_not_remember__symbol, nil);
  
  resume_gc();
  try_gc();
}


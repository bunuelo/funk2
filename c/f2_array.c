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

// array interface

f2ptr raw__array__new(f2ptr cause, u64 length) {
  f2ptr reflective_cause = nil;
  if (raw__cause__allocate_traced_arrays(reflective_cause, cause)) {
    return f2traced_array__new(cause, length, to_ptr(NULL));
  } else {
    return f2simple_array__new(cause, length, to_ptr(NULL));
  }
}

f2ptr raw__array__new_copy(f2ptr cause, u64 length, f2ptr init) {
  f2ptr reflective_cause = nil;
  if (raw__cause__allocate_traced_arrays(reflective_cause, cause)) {
    return f2traced_array__new_copy(cause, length, init);
  } else {
    return f2simple_array__new_copy(cause, length, init);
  }
}

boolean_t raw__array__is_type(f2ptr cause, f2ptr x) {
  return (raw__simple_array__is_type(cause, x) ||
	  raw__traced_array__is_type(cause, x));
}
f2ptr f2__array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__array__is_type(cause, x));}
def_pcfunk1(array__is_type, x, return f2__array__is_type(this_cause, x));

f2ptr f2__array__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "array");}
def_pcfunk1(array__type, this, return f2__array__type(this_cause, this));

f2ptr f2__array__new_1d(f2ptr cause, f2ptr length, f2ptr and_rest) {
  if ((! length) || (! raw__integer__is_type(cause, length))) {
    printf("\n[array_1d length &opt init] error: length must be integer.");
    return f2larva__new(cause, 1, nil);
    //return f2__argument_type_check_failure__exception__new(cause, nil);
  }
  int raw_length = f2integer__i(length, cause);
  f2ptr init = nil;
  //printf ("\nand_rest: "); fflush(stdout); f2__print(simple_fiber, and_rest); fflush(stdout);
  if (and_rest) {
    init = f2cons__car(and_rest, cause);
    if (!init || !raw__array__is_type(cause, init)) {
      printf("\n[array length :rest init] error: init must be array (or not included)."); fflush(stdout);
      return f2larva__new(cause, 1, nil);
      //return f2__argument_type_check_failure__exception__new(cause, nil);
    }
    if (raw__array__length(init, cause) < raw_length) {
      printf("\n[array length :rest init] error: init must be longer or equal in length to length."); fflush(stdout);
      return f2larva__new(cause, 1, nil);
      //return f2__argument_type_check_failure__exception__new(cause, nil);
    }
  }
  if (init) {return raw__array__new_copy(cause, raw_length, init);}
  else      {return raw__array__new(cause, raw_length);}
}
def_pcfunk1_and_rest(array__new_1d, length, and_rest, return f2__array__new_1d(this_cause, length, and_rest));

f2ptr f2__array__new(f2ptr cause, f2ptr lengths) {
  return f2__array__new_multidimensional(cause, lengths);
}
def_pcfunk0_and_rest(array__new, lengths, return f2__array__new(this_cause, lengths));

f2ptr raw__array__new_multidimensional(f2ptr cause, f2ptr lengths) {
  f2ptr length       = f2cons__car(lengths, cause);
  f2ptr rest_lengths = f2cons__cdr(lengths, cause);
  s64   length__i    = f2integer__i(length, cause);
  f2ptr this         = raw__array__new(cause, length__i);
  if (rest_lengths != nil) {
    u64 index;
    for (index = 0; index < length__i; index ++) {
      raw__array__elt__set(cause, this, index, raw__array__new_multidimensional(cause, rest_lengths));
    }
  }
  return this;
}

f2ptr f2__array__new_multidimensional(f2ptr cause, f2ptr lengths) {
  f2ptr iter = lengths;
  while (iter) {
    if (! raw__cons__is_type(cause, iter)) {
      return f2larva__new(cause, 1, nil);
    }
    f2ptr length = f2cons__car(iter, cause);
    if (! raw__integer__is_type(cause, length)) {
      return f2larva__new(cause, 1, nil);
    }
    iter = f2cons__cdr(iter, cause);
  }
  return raw__array__new_multidimensional(cause, lengths);
}


f2ptr f2__array(f2ptr cause, f2ptr and_rest) {
  f2ptr iter = and_rest;
  int rest_length = 0;
  while (iter) {
    rest_length ++;
    iter = f2cons__cdr(iter, cause);
  }
  f2ptr this = raw__array__new(cause, rest_length);
  int i = 0;
  iter = and_rest;
  while (iter) {
    f2ptr car = f2cons__car(iter, cause);
    raw__array__elt__set(cause, this, i, car);
    i ++;
    iter = f2cons__cdr(iter, cause);
  }
  return this;
}
def_pcfunk0_and_rest(array, and_rest, return f2__array(this_cause, and_rest));

u64 raw__array__length(f2ptr cause, f2ptr x) {
  if      (raw__simple_array__is_type(cause, x)) {return f2simple_array__length(x, cause);}
  else if (raw__traced_array__is_type(cause, x)) {return f2traced_array__length(x, cause);}
  else {error(nil, "raw__array__length: invalid type"); return 0;}
}
f2ptr f2__array__length(f2ptr cause, f2ptr x) {
  if      (raw__simple_array__is_type(cause, x)) {return f2__simple_array__length(cause, x);}
  else if (raw__traced_array__is_type(cause, x)) {return f2__traced_array__length(cause, x);}
  else {return f2larva__new(cause, 1, nil);}
}
def_pcfunk1(array__length, x, return f2__array__length(this_cause, x));

boolean_t raw__array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__array__eq(cause, this, that));
}
def_pcfunk2(array__eq, this, that, return f2__array__eq(this_cause, this, that));

u64 raw__array__eq_hash_value(f2ptr cause, f2ptr this) {
  if      (raw__simple_array__is_type(cause, this)) {return raw__simple_array__eq_hash_value(cause, this);}
  else if (raw__traced_array__is_type(cause, this)) {return raw__traced_array__eq_hash_value(cause, this);}
  else {error(nil, "raw__array__length: invalid type"); return 0;}
}
f2ptr f2__array__eq_hash_value(f2ptr cause, f2ptr this) {
  if      (raw__simple_array__is_type(cause, this)) {return f2__simple_array__eq_hash_value(cause, this);}
  else if (raw__traced_array__is_type(cause, this)) {return f2__traced_array__eq_hash_value(cause, this);}
  else {return f2larva__new(cause, 1, nil);}
}
def_pcfunk1(array__eq_hash_value, this, return f2__array__eq_hash_value(this_cause, this));

boolean_t raw__array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__array__is_type(cause, that)) {
    return boolean__false;
  }
  s64 this__length = raw__array__length(cause, this);
  s64 that__length = raw__array__length(cause, that);
  if (this__length != that__length) {
    return boolean__false;
  }
  s64 index;
  for (index = 0; index < this__length; index ++) {
    f2ptr this__subexp = raw__array__elt(cause, this, index);
    f2ptr that__subexp = raw__array__elt(cause, that, index);
    if (! raw__equals(cause, this__subexp, that__subexp)) {
      return boolean__false;
    }
  }
  return boolean__true;
}

f2ptr f2__array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__array__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__array__equals(cause, this, that));
}
def_pcfunk2(array__equals, this, that, return f2__array__equals(this_cause, this, that));

f2ptr raw__array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  if (raw__ptypehash__contains(cause, node_hash, this)) {
    return f2integer__new(cause, 1);
  }
  {
    f2ptr node_hash__key_count    = f2__ptypehash__key_count(cause, node_hash);
    u64   node_hash__key_count__i = f2integer__i(node_hash__key_count, cause);
    if (node_hash__key_count__i > max_equals_hash_value_recursion_depth) {
      return f2larva__new(cause, 334, nil);
    }
  }
  u64 hash_value = 1;
  raw__ptypehash__add(cause, node_hash, this, __funk2.globalenv.true__symbol);
  s64 this__length = raw__array__length(cause, this);
  hash_value += this__length;
  s64 index;
  for (index = 0; index < this__length; index ++) {
    f2ptr this__subexp = raw__array__elt(cause, this, index);
    if (this__subexp) {
      //f2__print(cause, this__subexp);
      f2ptr subexp__hash_value = f2__object__equals_hash_value__loop_free(cause, this__subexp, node_hash);
      if (raw__larva__is_type(cause, subexp__hash_value)) {
	return subexp__hash_value;
      }
      if (! raw__integer__is_type(cause, subexp__hash_value)) {
	return f2larva__new(cause, 4, nil);
      }
      u64 subexp__hash_value__i = f2integer__i(this__subexp, cause);
      hash_value *= ((subexp__hash_value__i == 0) ? 1 : subexp__hash_value__i);
    }
  }
  return f2integer__new(cause, hash_value);
}

f2ptr f2__array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, node_hash))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__equals_hash_value__loop_free(cause, this, node_hash);
}
def_pcfunk2(array__equals_hash_value__loop_free, this, node_hash, return f2__array__equals_hash_value__loop_free(this_cause, this, node_hash));

f2ptr raw__array__equals_hash_value(f2ptr cause, f2ptr this) {
  f2ptr node_hash = f2__ptypehash__new(cause);
  return raw__array__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__array__equals_hash_value(f2ptr cause, f2ptr this) {
  if (! raw__array__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__equals_hash_value(cause, this);
}
def_pcfunk1(array__equals_hash_value, this, return f2__array__equals_hash_value(this_cause, this));

f2ptr raw__array__elt(f2ptr cause, f2ptr this, u64 index) {
  if (raw__simple_array__is_type(cause, this)) {
    u64 length = f2simple_array__length(this, cause);
    if (index >= length) {
      return f2larva__new(cause, 2, nil);
    }
    return f2simple_array__elt(this, index, cause);
  } else if (raw__traced_array__is_type(cause, this)) {
    u64 length = f2traced_array__length(this, cause);
    if (index >= length) {
      return f2larva__new(cause, 2, nil);
    }
    return f2traced_array__elt(this, index, cause);
  } else {
    return f2larva__new(cause, 1, nil);
  }
}
f2ptr f2__array__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if (! raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt, x, y, return f2__array__elt(this_cause, x, y));

f2ptr raw__array__elt__trace_depth(f2ptr cause, f2ptr this, u64 index, int trace_depth) {
  if      (raw__simple_array__is_type(cause, this)) {f2simple_array__elt(             this, index, cause             ); return nil;}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__trace_depth(this, index, cause, trace_depth); return nil;}
  else {
    error(nil, "raw__array__elt__trace_depth: should be a type of array.");
    return nil;
  }
}

f2ptr raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {f2simple_array__elt__set(this, index, cause, value); return nil;}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__set, x, y, z, return f2__array__elt__set(this_cause, x, y, z));

f2ptr raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth) {
  if      (raw__simple_array__is_type(cause, this)) {f2simple_array__elt__set(             this, index, cause, value             ); return nil;}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__set__trace_depth(this, index, cause, value, trace_depth); return nil;}
  else {
    error(nil, "raw__array__elt__set__trace_depth: should be a type of array.");
    return nil;
  }
}

f2ptr raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__tracing_on(this, index, cause);}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__tracing_on(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__tracing_on, x, y, return f2__array__elt__tracing_on(this_cause, x, y));

f2ptr raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1, nil);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__tracing_on__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__tracing_on__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__tracing_on__set, x, y, z, return f2__array__elt__tracing_on__set(this_cause, x, y, z));

f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__trace(this, index, cause);}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__trace(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__trace, x, y, return f2__array__elt__trace(this_cause, x, y));

f2ptr raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1, nil);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__trace__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__trace__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__trace__set, x, y, z, return f2__array__elt__trace__set(this_cause, x, y, z));


f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__imagination_frame(this, index, cause);}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__imagination_frame(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__imagination_frame, x, y, return f2__array__elt__imagination_frame(this_cause, x, y));

f2ptr raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1, nil);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__imagination_frame__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__imagination_frame__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__imagination_frame__set, x, y, z, return f2__array__elt__imagination_frame__set(this_cause, x, y, z));


f2ptr raw__array__elt__mutate_funks(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__mutate_funks(this, index, cause);}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__mutate_funks(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__mutate_funks(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__mutate_funks, x, y, return f2__array__elt__mutate_funks(this_cause, x, y));

f2ptr raw__array__elt__mutate_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1, nil);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__mutate_funks__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__mutate_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__mutate_funks__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__mutate_funks__set, x, y, z, return f2__array__elt__mutate_funks__set(this_cause, x, y, z));


f2ptr raw__array__elt__read_funks(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__read_funks(this, index, cause);}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__read_funks(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__read_funks(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__read_funks, x, y, return f2__array__elt__read_funks(this_cause, x, y));

f2ptr raw__array__elt__read_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1, nil);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__read_funks__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1, nil);}
}
f2ptr f2__array__elt__read_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1, nil);}
  return raw__array__elt__read_funks__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__read_funks__set, x, y, z, return f2__array__elt__read_funks__set(this_cause, x, y, z));


f2ptr raw__array__as__conslist(f2ptr cause, f2ptr this) {
  u64 length = raw__array__length(cause, this);
  f2ptr new_seq = nil;
  s64 index;
  for (index = length - 1; index >= 0; index --) {
    new_seq = f2cons__new(cause, raw__array__elt(cause, this, index), new_seq);
  }
  return new_seq;
}

f2ptr f2__array__as__conslist(f2ptr cause, f2ptr this) {
  if (! raw__array__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__as__conslist(cause, this);
}
def_pcfunk1(array__as__conslist, this, return f2__array__as__conslist(this_cause, this));


f2ptr raw__array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr max_size           = f2__terminal_print_frame__max_size(cause, terminal_print_frame);
  s64   max_size__i        = f2integer__i(max_size, cause);
  f2ptr max_x              = f2__terminal_print_frame__max_x(cause, terminal_print_frame);
  s64   max_x__i           = f2integer__i(max_x, cause);
  f2ptr size               = f2__terminal_print_frame__size(cause, terminal_print_frame);
  s64   size__i            = f2integer__i(size, cause);
  f2ptr use_one_line       = f2__terminal_print_frame__use_one_line(    cause, terminal_print_frame);
  f2ptr indent_distance    = f2__terminal_print_frame__indent_distance( cause, terminal_print_frame);
  s64   indent_distance__i = f2integer__i(indent_distance, cause);
  f2ptr x                  = f2__terminal_print_frame__x(               cause, terminal_print_frame);
  s64   x__i               = f2integer__i(x, cause);
  {
    indent_distance__i = x__i + 1;
    indent_distance = f2integer__new(cause, indent_distance__i);
    f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
  }
  u64 array__length        = raw__array__length(cause, this);
  u8  array_string[128];
  u64 array_string__length = 0;
  {
    array_string[0]      = (u8)f2char__ch(__funk2.reader.char__array_left_paren, cause);
    array_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, array_string__length, array_string);
  }
  {
    u64 index;
    for (index = 0; index < array__length; index ++) {
      if (size__i >= (max_size__i - 1)) {
	f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	x    = f2__terminal_print_frame__x(cause, terminal_print_frame);
	x__i = f2integer__i(x, cause);
	array_string__length = sprintf((char*)array_string, "%c...", ((x__i + 4) < max_x__i) ? ' ' : '\n');
	raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
	raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, array_string__length, array_string);
	break;
      } else {
	f2ptr indent_distance = f2__terminal_print_frame__indent_distance(cause, terminal_print_frame);
	{
	  f2ptr subexp             = raw__array__elt(cause, this, index);
	  u64   array__length_left = array__length - index;
	  u64   subexp_max_size__i = (max_size__i - size__i + (array__length_left - 1)) / array__length_left;
	  f2ptr subexp_size;
	  u64   subexp_size__i;
	  f2ptr can_print_on_one_line = nil;
	  {
	    if (index > 0) {
	      {
		x    = f2__terminal_print_frame__x(cause, terminal_print_frame);
		x__i = f2integer__i(x, cause);
		if ((x__i + 1) < max_x__i) {
		  array_string__length = sprintf((char*)array_string, " ");
		  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
		  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, array_string__length, array_string);
		}
	      }
	      if (use_one_line == nil) {
		can_print_on_one_line = f2__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(cause, terminal_print_frame, subexp);
		if (raw__larva__is_type(cause, can_print_on_one_line)) {
		  return can_print_on_one_line;
		}
		if (can_print_on_one_line == nil) {
		  array_string__length = sprintf((char*)array_string, "\n");
		  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, array_string__length, array_string);
		}
	      }
	    }
	    
	    {
	      if ((use_one_line == nil) && (can_print_on_one_line != nil)) {
		f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	      }
	      f2__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, 0));
	      f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, f2integer__new(cause, subexp_max_size__i));
	      f2ptr result = raw__exp__terminal_print_with_frame(cause, subexp, terminal_print_frame);
	      if (raw__larva__is_type(cause, result)) {
		return result;
	      }
	      if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
		return nil;
	      }
	      if ((use_one_line == nil) && (can_print_on_one_line != nil)) {
		f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	      }
	    }
	    
	    subexp_size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
	    subexp_size__i = f2integer__i(subexp_size, cause);
	  }
	  size__i += subexp_size__i;
	  if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
	    return nil;
	  }
	}
	f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
      }
    }
    f2__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, size__i));
    f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
  }
  {
    array_string[0]      = (u8)f2char__ch(__funk2.reader.char__array_right_paren, cause);
    array_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, array_string__length, array_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__terminal_print_frame__is_type(cause, terminal_print_frame))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__array__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(array__terminal_print_with_frame, this, terminal_print_frame, return f2__array__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.new__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.equals__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.equals_hash_value__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.equals_hash_value__loop_free__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__set__funk);}
  {char* slot_name = "elt-tracing_on";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__tracing_on__funk);}
  {char* slot_name = "elt-tracing_on";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__tracing_on__set__funk);}
  {char* slot_name = "elt-trace";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__trace__funk);}
  {char* slot_name = "elt-trace";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__trace__set__funk);}
  {char* slot_name = "elt-imagination_frame";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__imagination_frame__funk);}
  {char* slot_name = "elt-imagination_frame";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__imagination_frame__set__funk);}
  {char* slot_name = "elt-mutate_funks";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__mutate_funks__funk);}
  {char* slot_name = "elt-mutate_funks";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__mutate_funks__set__funk);}
  {char* slot_name = "elt-read_funks";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__read_funks__funk);}
  {char* slot_name = "elt-read_funks";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.elt__read_funks__set__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__array__reinitialize_globalvars() {
  //f2ptr cause = f2_primfunks_c__cause__new(initial_cause());
  
}

void f2__array__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "array", "", &f2__array__reinitialize_globalvars);
  
  f2__array__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // array
  
  //f2__funktional_primcfunk__init__1(array__is_type,                     exp, "(cfunk defined in f2_array.c)");
  f2__primcfunk__init__1(           array__new_1d,                      length, "(cfunk defined in f2_array.c)");
  f2__primcfunk__init__0_and_rest(  array,                              elts, "(cfunk defined in f2_array.c)");
  //f2__funktional_primcfunk__init__1(array__length,                      this, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__1(           array__hash_value,                  this, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__2(           array__elt,                         this, index, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__3(           array__elt__set,                    this, index, value, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__2(           array__elt__tracing_on,             this, index, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__3(           array__elt__tracing_on__set,        this, index, value, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__2(           array__elt__trace,                  this, index, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__3(           array__elt__trace__set,             this, index, value, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__2(           array__elt__imagination_frame,      this, index, "(cfunk defined in f2_array.c)");
  //f2__primcfunk__init__3(           array__elt__imagination_frame__set, this, index, value, "(cfunk defined in f2_array.c)");
  f2__primcfunk__init__1(           array__as__conslist,                 this, "returns an array represented as a new conslist.  (cfunk defined in f2_array.c)");
  
  // array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.array.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.array.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg_and_rest(array__new, lengths, cfunk, 1, "Returns an array with the appropriate lengths for each provided dimension."); __funk2.globalenv.object_type.array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.array.eq__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__eq, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.array.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.array.equals__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__equals, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.array.equals_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__equals_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.array.equals_hash_value__loop_free__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__equals_hash_value__loop_free, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(array__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__set__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on"; __funk2.globalenv.object_type.array.elt__tracing_on__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__elt__tracing_on, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__tracing_on__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on-set"; __funk2.globalenv.object_type.array.elt__tracing_on__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(array__elt__tracing_on__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__tracing_on__set__funk = never_gc(cfunk);}
  {char* str = "elt-trace"; __funk2.globalenv.object_type.array.elt__trace__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__elt__trace, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__trace__funk = never_gc(cfunk);}
  {char* str = "elt-trace-set"; __funk2.globalenv.object_type.array.elt__trace__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(array__elt__trace__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__trace__set__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame"; __funk2.globalenv.object_type.array.elt__imagination_frame__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__elt__imagination_frame, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__imagination_frame__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame-set"; __funk2.globalenv.object_type.array.elt__imagination_frame__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(array__elt__imagination_frame__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__imagination_frame__set__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks"; __funk2.globalenv.object_type.array.elt__mutate_funks__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__elt__mutate_funks, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__mutate_funks__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks-set"; __funk2.globalenv.object_type.array.elt__mutate_funks__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(array__elt__mutate_funks__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__mutate_funks__set__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks"; __funk2.globalenv.object_type.array.elt__read_funks__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__elt__read_funks, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__read_funks__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks-set"; __funk2.globalenv.object_type.array.elt__read_funks__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(array__elt__read_funks__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.elt__read_funks__set__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.array.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(array__terminal_print_with_frame, this, terminal_print_frame, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}



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
  if (raw__cause__allocate_traced_arrays(cause, cause)) {
    return f2traced_array__new(cause, length, to_ptr(NULL));
  } else {
    return f2simple_array__new(cause, length, to_ptr(NULL));
  }
}

f2ptr raw__array__new_copy(f2ptr cause, u64 length, f2ptr init) {
  if (raw__cause__allocate_traced_arrays(cause, cause)) {
    return f2traced_array__new_copy(cause, length, init);
  } else {
    return f2simple_array__new_copy(cause, length, init);
  }
}

boolean_t raw__array__is_type(f2ptr cause, f2ptr x) {return (raw__simple_array__is_type(cause, x) || raw__traced_array__is_type(cause, x));}
f2ptr f2__array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__array__is_type(cause, x));}
def_pcfunk1(array__is_type, x, return f2__array__is_type(this_cause, x));

f2ptr f2__array__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "array");}
def_pcfunk1(array__type, this, return f2__array__type(this_cause, this));

f2ptr f2__array__new_1d(f2ptr cause, f2ptr length, f2ptr and_rest) {
  if ((! length) || (! raw__integer__is_type(cause, length))) {
    printf("\n[array_1d length &opt init] error: length must be integer.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, nil);
  }
  int raw_length = f2integer__i(length, cause);
  f2ptr init = nil;
  //printf ("\nand_rest: "); fflush(stdout); f2__print(simple_fiber, and_rest); fflush(stdout);
  if (and_rest) {
    init = f2cons__car(and_rest, cause);
    if (!init || !raw__array__is_type(cause, init)) {
      printf("\n[array length :rest init] error: init must be array (or not included)."); fflush(stdout);
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, nil);
    }
    if (raw__array__length(init, cause) < raw_length) {
      printf("\n[array length :rest init] error: init must be longer or equal in length to length."); fflush(stdout);
      return f2larva__new(cause, 1);
      //return f2__argument_type_check_failure__exception__new(cause, nil);
    }
  }
  if (init) {return raw__array__new_copy(cause, raw_length, init);}
  else      {return raw__array__new(cause, raw_length);}
}
def_pcfunk1_and_rest(array__new_1d, length, and_rest, return f2__array__new_1d(this_cause, length, and_rest));

f2ptr f2__array__new(f2ptr cause, f2ptr length) {
  if ((! length) || (! raw__integer__is_type(cause, length))) {
    printf("\n[array_1d length &opt init] error: length must be integer.");
    return f2larva__new(cause, 1);
    //return f2__argument_type_check_failure__exception__new(cause, nil);
  }
  int raw_length = f2integer__i(length, cause);
  return raw__array__new(cause, raw_length);
}
def_pcfunk1(array__new, length, return f2__array__new(this_cause, length));

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
  else {return f2larva__new(cause, 1);}
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
  else {return f2larva__new(cause, 1);}
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
    return f2larva__new(cause, 1);
  }
  return f2bool__new(raw__array__equals(cause, this, that));
}
def_pcfunk2(array__equals, this, that, return f2__array__equals(this_cause, this, that));

f2ptr raw__array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  raw__ptypehash__add(cause, node_hash, this, __funk2.globalenv.true__symbol);
  u64 hash_value   = 1 + this__length;
  {
    s64 this__length = raw__array__length(cause, this);
    s64 index;
    for (index = 0; index < this__length; index ++) {
      f2ptr this__subexp = raw__array__elt(cause, this, index);
      if (! raw__ptypehash__contains(cause, node_hash, this__subexp)) {
	if (this__subexp) {
	  f2ptr subexp__hash_value = f2__object__equals_hash_value__loop_free(cause, this__subexp, node_hash);
	  if (! raw__integer__is_type(cause, subexp__hash_value)) {
	    return f2larva__new(cause, 4);
	  }
	  u64 subexp__hash_value__i = f2integer__i(this__subexp, cause);
	  hash_value *= ((subexp__hash_value__i == 0) ? 1 : subexp__hash_value__i);
	}
      }
    }
  }
  return f2integer__new(cause, hash_value);
}

f2ptr f2__array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  if ((! raw__array__is_type(cause, this)) ||
      (! raw__ptypehash__is_type(cause, this))) {
    return f2larva__new(cause, 1);
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
    return f2larva__new(cause, 1);
  }
  return raw__array__equals_hash_value(cause, this);
}
def_pcfunk1(array__equals_hash_value, this, return f2__array__equals_hash_value(this_cause, this));

f2ptr raw__array__elt(f2ptr cause, f2ptr this, u64 index) {
  if (raw__simple_array__is_type(cause, this)) {
    u64 length = f2simple_array__length(this, cause);
    if (index >= length) {
      return f2larva__new(cause, 2);
    }
    return f2simple_array__elt(this, index, cause);
  } else if (raw__traced_array__is_type(cause, this)) {
    u64 length = f2traced_array__length(this, cause);
    if (index >= length) {
      return f2larva__new(cause, 2);
    }
    return f2traced_array__elt(this, index, cause);
  } else {
    return f2larva__new(cause, 1);
  }
}
f2ptr f2__array__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
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
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
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
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__tracing_on(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__tracing_on, x, y, return f2__array__elt__tracing_on(this_cause, x, y));

f2ptr raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__tracing_on__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__tracing_on__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__tracing_on__set, x, y, z, return f2__array__elt__tracing_on__set(this_cause, x, y, z));

f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__trace(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__trace(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__trace, x, y, return f2__array__elt__trace(this_cause, x, y));

f2ptr raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__trace__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__trace__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__trace__set, x, y, z, return f2__array__elt__trace__set(this_cause, x, y, z));


f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__imagination_frame(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__imagination_frame(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__imagination_frame, x, y, return f2__array__elt__imagination_frame(this_cause, x, y));

f2ptr raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__imagination_frame__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__imagination_frame__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__imagination_frame__set, x, y, z, return f2__array__elt__imagination_frame__set(this_cause, x, y, z));


f2ptr raw__array__elt__mutate_funks(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__mutate_funks(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__mutate_funks(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__mutate_funks(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__mutate_funks, x, y, return f2__array__elt__mutate_funks(this_cause, x, y));

f2ptr raw__array__elt__mutate_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__mutate_funks__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__mutate_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__mutate_funks__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__mutate_funks__set, x, y, z, return f2__array__elt__mutate_funks__set(this_cause, x, y, z));


f2ptr raw__array__elt__read_funks(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__read_funks(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__read_funks(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__read_funks(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__read_funks, x, y, return f2__array__elt__read_funks(this_cause, x, y));

f2ptr raw__array__elt__read_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__read_funks__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__read_funks__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__read_funks__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__read_funks__set, x, y, z, return f2__array__elt__read_funks__set(this_cause, x, y, z));


f2ptr f2__array__as_conslist(f2ptr cause, f2ptr this) {
  if (! raw__array__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  u64 length = raw__array__length(cause, this);
  f2ptr new_seq = nil;
  s64 index;
  for (index = length - 1; index >= 0; index --) {
    new_seq = f2cons__new(cause, raw__array__elt(cause, this, index), new_seq);
  }
  return new_seq;
}
def_pcfunk1(array__as_conslist, this, return f2__array__as_conslist(this_cause, this));


f2ptr f2array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.is_type__funk);}
  {char* slot_name = "type";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.type__funk);}
  {char* slot_name = "new";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.array.new__funk);}
  {char* slot_name = "length";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.length__funk);}
  {char* slot_name = "eq";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.eq__funk);}
  {char* slot_name = "eq_hash_value";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.eq_hash_value__funk);}
  {char* slot_name = "equals";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.equals__funk);}
  {char* slot_name = "equals_hash_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.equals_hash_value__funk);}
  {char* slot_name = "elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__funk);}
  {char* slot_name = "elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__set__funk);}
  {char* slot_name = "elt-tracing_on";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__tracing_on__funk);}
  {char* slot_name = "elt-tracing_on";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__tracing_on__set__funk);}
  {char* slot_name = "elt-trace";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__trace__funk);}
  {char* slot_name = "elt-trace";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__trace__set__funk);}
  {char* slot_name = "elt-imagination_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__imagination_frame__funk);}
  {char* slot_name = "elt-imagination_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__imagination_frame__set__funk);}
  {char* slot_name = "elt-mutate_funks";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__mutate_funks__funk);}
  {char* slot_name = "elt-mutate_funks";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__mutate_funks__set__funk);}
  {char* slot_name = "elt-read_funks";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__read_funks__funk);}
  {char* slot_name = "elt-read_funks";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.array.elt__read_funks__set__funk);}
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
  f2__primcfunk__init__1(           array__as_conslist,                 this, "returns an array represented as a new conslist.  (cfunk defined in f2_array.c)");
  
  // array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.array.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.array.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(array__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.array.new__funk = never_gc(cfunk);}
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
  
}



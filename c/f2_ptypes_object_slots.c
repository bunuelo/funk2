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

void raw__ptypes__read_write_reflective_tracing_enabled__set(boolean_t value) {
  __funk2.ptypes.read_write_reflective_tracing_enabled = value;
}

f2ptr f2__ptypes__read_write_reflective_tracing_enabled__set(f2ptr cause, f2ptr value) {
  raw__ptypes__read_write_reflective_tracing_enabled__set(value != nil);
  return nil;
}
def_pcfunk1(ptypes__read_write_reflective_tracing_enabled__set, value,
	    "Enables or disables ptypes read/write reflective tracing.",
	    return f2__ptypes__read_write_reflective_tracing_enabled__set(this_cause, value));


// ptype

boolean_t raw__ptype__is_type(f2ptr cause, f2ptr thing) {
  if (thing) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__ptype__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__ptype__is_type(cause, thing));}
def_pcfunk1(ptype__is_type, thing,
	    "",
	    return f2__ptype__is_type(this_cause, thing));

f2ptr f2__ptype__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "ptype");}
def_pcfunk1(ptype__type, this,
	    "",
	    return f2__ptype__type(this_cause, this));

f2ptr f2__ptype__raw(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2ptype__raw(x, cause));}
def_pcfunk1(ptype__raw, x,
	    "",
	    return f2__ptype__raw(this_cause, x));


f2ptr raw__ptype__cause(f2ptr cause, f2ptr this) {
  return f2ptype__cause(this, cause);
}

f2ptr f2__ptype__cause(f2ptr cause, f2ptr this) {
  assert_argument_type(ptype, this);
  return raw__ptype__cause(cause, this);
}
def_pcfunk1(ptype__cause, this,
	    "",
	    return f2__ptype__cause(this_cause, this));


f2ptr f2__ptype__cause__set(f2ptr cause, f2ptr x, f2ptr value) {
  assert_argument_type(ptype, x);
  f2ptype__cause__set(x, cause, value);
  return nil;
}
def_pcfunk2(ptype__cause__set, x, value,
	    "",
	    return f2__ptype__cause__set(this_cause, x, value));


f2ptr f2__ptype__creation_fiber(f2ptr cause, f2ptr x) {
  assert_argument_type(ptype, x);
  return f2ptype__creation_fiber(x, cause);
}
def_pcfunk1(ptype__creation_fiber, x,
	    "",
	    return f2__ptype__creation_fiber(this_cause, x));


f2ptr f2__ptype__creation_fiber__set(f2ptr cause, f2ptr x, f2ptr value) {
  assert_argument_type(ptype, x);
  f2ptype__creation_fiber__set(x, cause, value);
  return nil;
}
def_pcfunk2(ptype__creation_fiber__set, x, value,
	    "",
	    return f2__ptype__creation_fiber__set(this_cause, x, value));


f2ptr f2ptype__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, nil);
  {char* slot_name = "is_type";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.is_type__funk);}
  {char* slot_name = "type";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.type__funk);}
  {char* slot_name = "raw";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.raw__funk);}
  {char* slot_name = "cause";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.cause__funk);}
  {char* slot_name = "cause";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.cause__set__funk);}
  {char* slot_name = "creation_fiber"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.creation_fiber__funk);}
  {char* slot_name = "creation_fiber"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.creation_fiber__set__funk);}
  return this;
}


// integer

boolean_t raw__integer__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_integer);
}

f2ptr f2__integer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__integer__is_type(cause, x));}
def_pcfunk1(integer__is_type, this,
	    "",
	    return f2__integer__is_type(this_cause, this));

f2ptr f2__integer__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "integer");}
def_pcfunk1(integer__type,    this,
	    "",
	    return f2__integer__type(this_cause, this));

def_pcfunk1(integer__new,     this,
	    "",
	    return f2integer__new(this_cause, f2integer__i(this, this_cause)));
def_pcfunk1(integer__i,       this,
	    "",
	    return this);


boolean_t raw__integer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__integer__is_type(cause, that)) {
    return boolean__false;
  }
  return f2integer__i(this, cause) == f2integer__i(that, cause);
}

f2ptr f2__integer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__integer__eq(cause, this, that));
}
def_pcfunk2(integer__eq, this, that,
	    "",
	    return f2__integer__eq(this_cause, this, that));


u64 raw__integer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__i(this, cause);}

f2ptr f2__integer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__integer__eq_hash_value(cause, this));}
def_pcfunk1(integer__eq_hash_value, this,
	    "",
	    return f2__integer__eq_hash_value(this_cause, this));


boolean_t raw__integer__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__integer__eq(cause, this, that);}

f2ptr f2__integer__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(integer, this);
  return f2bool__new(raw__integer__equals(cause, this, that));
}
def_pcfunk2(integer__equals, this, that,
	    "",
	    return f2__integer__equals(this_cause, this, that));


u64 raw__integer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__integer__eq_hash_value(cause, this);
}

f2ptr f2__integer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(integer,   this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__integer__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(integer__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__integer__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__integer__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__integer__eq_hash_value(cause, this);
}

f2ptr f2__integer__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2integer__new(cause, raw__integer__equals_hash_value(cause, this));
}
def_pcfunk1(integer__equals_hash_value, this,
	    "",
	    return f2__integer__equals_hash_value(this_cause, this));


double raw__integer__as__double(f2ptr cause, f2ptr this) {
  return f2integer__i(this, cause);
}

f2ptr f2__integer__as__double(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2double__new(cause, raw__integer__as__double(cause, this));
}
def_pcfunk1(integer__as__double, this,
	    "",
	    return f2__integer__as__double(this_cause, this));


ptr raw__integer__as__pointer(f2ptr cause, f2ptr this) {
  return (ptr)f2integer__i(this, cause);
}

f2ptr f2__integer__as__pointer(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return f2pointer__new(cause, raw__integer__as__pointer(cause, this));
}
def_pcfunk1(integer__as__pointer, this,
	    "",
	    return f2__integer__as__pointer(this_cause, this));


f2ptr f2__integer__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__multiply_overflows(value, number_value)) {
      return f2integer__new(cause, value * number_value);
    } else {
      return f2__largeinteger__multiplied_by(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__multiplied_by(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_multiply_an_integer_by_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__multiplied_by, this, that,
	    "",
	    return f2__integer__multiplied_by(this_cause, this, that));


f2ptr f2__integer__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2integer__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__divide(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_divide_an_integer_by_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__divided_by, this, that,
	    "",
	    return f2__integer__divided_by(this_cause, this, that));


f2ptr f2__integer__plus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__add_overflows(value, number_value)) {
      return f2integer__new(cause, value + number_value);
    } else {
      return f2__largeinteger__add(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__add(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_add_integer_to_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__plus, this, that,
	    "",
	    return f2__integer__plus(this_cause, this, that));


f2ptr f2__integer__minus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    s64 number_value = f2integer__i(number, cause);
    if (! s64__add_overflows(value, -number_value) && ((number_value == 0) || (-number_value != number_value))) {
      return f2integer__new(cause, value - f2integer__i(number, cause));
    } else {
      return f2__largeinteger__subtract(cause, raw__largeinteger__new_from_s64(cause, value), raw__largeinteger__new_from_s64(cause, number_value));
    }
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__subtract(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_minus_an_integer_with_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__minus, this, that,
	    "",
	    return f2__integer__minus(this_cause, this, that));


f2ptr f2__integer__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__greater_than(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_ask_is_greater_than_with_an_integer_and_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__is_greater_than, this, that,
	    "",
	    return f2__integer__is_greater_than(this_cause, this, that));


f2ptr f2__integer__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__less_than(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_ask_is_less_than_with_an_integer_and_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__is_less_than, this, that,
	    "",
	    return f2__integer__is_less_than(this_cause, this, that));


f2ptr f2__integer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(integer, this);
  s64 value = f2integer__i(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2__largeinteger__equals(cause, raw__largeinteger__new_from_s64(cause, value), number);
  }
  return new__error(f2list6__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "tried_to_ask_is_numerically_equal_to_with_an_integer_and_an_unknown_type"),
				 new__symbol(cause, "this"),     this,
				 new__symbol(cause, "number"),   number));
}
def_pcfunk2(integer__is_numerically_equal_to, this, that,
	    "",
	    return f2__integer__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__integer__square_root(f2ptr cause, f2ptr this) {
  s64 i = f2integer__i(this, cause);
  if (i < 0) {
    return f2larva__new(cause, 5, nil);
  }
  return f2integer__new(cause, u64__sqrt(i));
}

f2ptr f2__integer__square_root(f2ptr cause, f2ptr this) {
  assert_argument_type(integer, this);
  return raw__integer__square_root(cause, this);
}
def_pcfunk1(integer__square_root, this,
	    "",
	    return f2__integer__square_root(this_cause, this));


f2ptr raw__integer__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  s64 this__i    = f2integer__i(this, cause);
  s64 that__i    = f2integer__i(that, cause);
  s64 result     = this__i % that__i;
  return f2integer__new(cause, result);
}

f2ptr f2__integer__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(integer, this);
  assert_argument_type(integer, that);
  return raw__integer__modulo(cause, this, that);
}
def_pcfunk2(integer__modulo, this, that,
	    "",
	    return f2__integer__modulo(this_cause, this, that));


f2ptr raw__integer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t integer_string[128];
  u64               integer_string__length = funk2_character_string__snprintf(integer_string, 128, s64__fstr, f2integer__i(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__integer__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, integer_string__length, integer_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__integer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(integer,              this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__integer__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(integer__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__integer__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__integer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.i__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.as__double__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.as__integer__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.as__integer__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.plus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.minus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.square_root__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.new__funk;
    }
  }
  return nil;
}

f2ptr f2integer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.new__funk);}
  {char* slot_name = "i";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.i__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk);}
  {char* slot_name = "as-double";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk);}
  {char* slot_name = "as-pointer";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__funk);}
  {char* slot_name = "multiplied_by";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk);}
  {char* slot_name = "divided_by";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk);}
  {char* slot_name = "plus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.plus__funk);}
  {char* slot_name = "minus";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.minus__funk);}
  {char* slot_name = "is_greater_than";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk);}
  {char* slot_name = "square_root";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk);}
  {char* slot_name = "modulo";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.modulo__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__funk);}
  return this;
}


// double

boolean_t raw__double__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_double);
}
f2ptr f2__double__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__double__is_type(cause, x));}
def_pcfunk1(double__is_type, x,   
	    "",
	    return f2__double__is_type(this_cause, x));

f2ptr f2__double__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "double");}
def_pcfunk1(double__type,    this,
	    "",
	    return f2__double__type(this_cause, this));

def_pcfunk1(double__new,     this,
	    "",
	    return f2double__new(this_cause, f2double__d(this, this_cause)));
def_pcfunk1(double__d,       this,
	    "",
	    return f2double__new(this_cause, f2double__d(this, this_cause)));

boolean_t raw__double__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__double__is_type(cause, that)) {
    return boolean__false;
  }
  return f2double__d(this, cause) == f2double__d(that, cause);
}

f2ptr f2__double__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__double__eq(cause, this, that));
}
def_pcfunk2(double__eq, this, that,
	    "",
	    return f2__double__eq(this_cause, this, that));

u64 raw__double__eq_hash_value(f2ptr cause, f2ptr this) {
  union {
    struct {
      double d;
      u64    zero;
    } s;
    u64 u;
  } stack_memory;
  stack_memory.s.d    = f2double__d(this, cause);
  stack_memory.s.zero = 0;
  u64 eq_hash_value = stack_memory.u;
  return eq_hash_value;
}

f2ptr f2__double__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__double__eq_hash_value(cause, this));}
def_pcfunk1(double__eq_hash_value, this,
	    "",
	    return f2__double__eq_hash_value(this_cause, this));

boolean_t raw__double__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__double__eq(cause, this, that);}

f2ptr f2__double__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(double, this);
  return f2bool__new(raw__double__equals(cause, this, that));
}
def_pcfunk2(double__equals, this, that,
	    "",
	    return f2__double__equals(this_cause, this, that));


u64 raw__double__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__double__eq_hash_value(cause, this);
}

f2ptr f2__double__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(double,    this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__double__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(double__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__double__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__double__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__double__eq_hash_value(cause, this);
}

f2ptr f2__double__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return f2integer__new(cause, raw__double__equals_hash_value(cause, this));
}
def_pcfunk1(double__equals_hash_value, this,
	    "",
	    return f2__double__equals_hash_value(this_cause, this));


double raw__double__as__double(f2ptr cause, f2ptr this) {
  return f2double__d(this, cause);
}

f2ptr f2__double__as__double(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return f2double__new(cause, raw__double__as__double(cause, this));
}
def_pcfunk1(double__as__double, this,
	    "",
	    return f2__double__as__double(this_cause, this));


f2ptr f2__double__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value * f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value * raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 1246246, nil);
}
def_pcfunk2(double__multiplied_by, this, that,
	    "",
	    return f2__double__multiplied_by(this_cause, this, that));


f2ptr f2__double__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value / raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 12634, nil);
}
def_pcfunk2(double__divided_by, this, that,
	    "",
	    return f2__double__divided_by(this_cause, this, that));


f2ptr f2__double__plus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value + f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value + raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 23441, nil);
}
def_pcfunk2(double__plus, this, that,
	    "",
	    return f2__double__plus(this_cause, this, that));


f2ptr f2__double__minus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2double__new(cause, value - f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2double__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2double__new(cause, value - raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 12642, nil);
}
def_pcfunk2(double__minus, this, that,
	    "",
	    return f2__double__minus(this_cause, this, that));


f2ptr f2__double__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value > raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 123525, nil);
}
def_pcfunk2(double__is_greater_than, this, that,
	    "",
	    return f2__double__is_greater_than(this_cause, this, that));


f2ptr f2__double__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value < raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 124624, nil);
}
def_pcfunk2(double__is_less_than, this, that,
	    "",
	    return f2__double__is_less_than(this_cause, this, that));


f2ptr f2__double__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(double, this);
  double value = f2double__d(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value == raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 124625, nil);
}
def_pcfunk2(double__is_numerically_equal_to, this, that,
	    "",
	    return f2__double__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__double__square_root(f2ptr cause, f2ptr this) {
  double d = f2double__d(this, cause);
  if (d < 0) {
    return f2larva__new(cause, 5, nil);
  }
  return f2double__new(cause, sqrt(d));
}

f2ptr f2__double__square_root(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__square_root(cause, this);
}
def_pcfunk1(double__square_root, this,
	    "",
	    return f2__double__square_root(this_cause, this));


f2ptr raw__double__radian_sine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = sin(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_sine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_sine(cause, this);
}
def_pcfunk1(double__radian_sine, this,
	    "",
	    return f2__double__radian_sine(this_cause, this));


f2ptr raw__double__radian_arcsine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = asin(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_arcsine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_arcsine(cause, this);
}
def_pcfunk1(double__radian_arcsine, this,
	    "",
	    return f2__double__radian_arcsine(this_cause, this));


f2ptr raw__double__radian_cosine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = cos(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_cosine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_cosine(cause, this);
}
def_pcfunk1(double__radian_cosine, this,
	    "",
	    return f2__double__radian_cosine(this_cause, this));


f2ptr raw__double__radian_arccosine(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = acos(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_arccosine(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_arccosine(cause, this);
}
def_pcfunk1(double__radian_arccosine, this,
	    "",
	    return f2__double__radian_arccosine(this_cause, this));


f2ptr raw__double__radian_tangent(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = tan(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_tangent(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_tangent(cause, this);
}
def_pcfunk1(double__radian_tangent, this,
	    "",
	    return f2__double__radian_tangent(this_cause, this));


f2ptr raw__double__radian_arctangent(f2ptr cause, f2ptr this) {
  double d      = f2double__d(this, cause);
  double result = atan(d);
  return f2double__new(cause, result);
}

f2ptr f2__double__radian_arctangent(f2ptr cause, f2ptr this) {
  assert_argument_type(double, this);
  return raw__double__radian_arctangent(cause, this);
}
def_pcfunk1(double__radian_arctangent, this,
	    "",
	    return f2__double__radian_arctangent(this_cause, this));


f2ptr raw__double__power(f2ptr cause, f2ptr this, f2ptr that) {
  double this__d = f2double__d(this, cause);
  double that__d = f2double__d(that, cause);
  double result  = pow(this__d, that__d);
  return f2double__new(cause, result);
}

f2ptr f2__double__power(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(double, this);
  assert_argument_type(double, that);
  return raw__double__power(cause, this, that);
}
def_pcfunk2(double__power, this, that,
	    "",
	    return f2__double__power(this_cause, this, that));


f2ptr raw__double__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  double this__d    = f2double__d(this, cause);
  double that__d    = f2double__d(that, cause);
  double whole_part = (int)(this__d / that__d);
  double result     = this__d - (that__d * whole_part);
  return f2double__new(cause, result);
}

f2ptr f2__double__modulo(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(double, this);
  assert_argument_type(double, that);
  return raw__double__modulo(cause, this, that);
}
def_pcfunk2(double__modulo, this, that,
	    "",
	    return f2__double__modulo(this_cause, this, that));


f2ptr raw__double__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  double            d = f2double__d(this, cause);
  funk2_character_t double_string[128];
  u64               double_string__length;
  if (d - floor(d) == 0.0) {
    double_string__length = funk2_character_string__snprintf(double_string, 128, "%.1f", d);
  } else {
    double_string__length = funk2_character_string__snprintf(double_string, 128, "%g", d);
  }
  //u64               double_string__length = funk2_character_string__snprintf(double_string, 128, "%1.16f", f2double__d(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__double__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, double_string__length, double_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__double__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(double,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__double__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(double__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__double__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__double__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.d__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.d__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.as__double__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.as__double__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.divided_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.plus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.minus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.square_root__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.square_root__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
  }
  return nil;
}

f2ptr f2__double__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (raw__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.new__funk;
  }
  return nil;
}

f2ptr f2double__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.new__funk);}
  {char* slot_name = "d";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.d__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk);}
  {char* slot_name = "as-double";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.as__double__funk);}
  {char* slot_name = "multiplied_by";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk);}
  {char* slot_name = "divided_by";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk);}
  {char* slot_name = "plus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.plus__funk);}
  {char* slot_name = "minus";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.minus__funk);}
  {char* slot_name = "is_greater_than";             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk);}
  {char* slot_name = "square_root";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.square_root__funk);}
  {char* slot_name = "radian_sine";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_sine__funk);}
  {char* slot_name = "radian_arcsine";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__funk);}
  {char* slot_name = "radian_cosine";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__funk);}
  {char* slot_name = "radian_arccosine";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__funk);}
  {char* slot_name = "radian_tangent";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__funk);}
  {char* slot_name = "radian_arctangent";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__funk);}
  {char* slot_name = "power";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.power__funk);}
  {char* slot_name = "modulo";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.modulo__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__funk);}
  return this;
}


// float

boolean_t raw__float__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_float);
}
f2ptr f2__float__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__float__is_type(cause, x));}
def_pcfunk1(float__is_type, x,   
	    "",
	    return f2__float__is_type(this_cause, x));

f2ptr f2__float__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "float");}
def_pcfunk1(float__type,    this,
	    "",
	    return f2__float__type(this_cause, this));

def_pcfunk1(float__new,     this,
	    "",
	    return f2float__new(this_cause, f2float__f(this_cause, this)));
def_pcfunk1(float__f,       this,
	    "",
	    return this);

boolean_t raw__float__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2float__f(this, cause) == f2float__f(that, cause);
}

f2ptr f2__float__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__float__eq(cause, this, that));
}
def_pcfunk2(float__eq, this, that,
	    "",
	    return f2__float__eq(this_cause, this, that));

u64 raw__float__eq_hash_value(f2ptr cause, f2ptr this) {
  union {
    u64 u;
    struct {
      float f;
      u64   zero;
    } s;
  } stack_memory;
  stack_memory.s.f    = f2float__f(this, cause);
  stack_memory.s.zero = 0;
  u64 eq_hash_value   = stack_memory.u;
  return eq_hash_value;
}

f2ptr f2__float__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__float__eq_hash_value(cause, this));}
def_pcfunk1(float__eq_hash_value, this,
	    "",
	    return f2__float__eq_hash_value(this_cause, this));

boolean_t raw__float__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__float__is_type(cause, that)) {
    return boolean__false;
  }
  return raw__float__eq(cause, this, that);
}

f2ptr f2__float__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(float, this);
  return f2bool__new(raw__float__equals(cause, this, that));
}
def_pcfunk2(float__equals, this, that,
	    "",
	    return f2__float__equals(this_cause, this, that));


u64 raw__float__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__float__eq_hash_value(cause, this);
}

f2ptr f2__float__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(float,     this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__float__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(float__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__float__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__float__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__float__eq_hash_value(cause, this);
}

f2ptr f2__float__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(float, this);
  return f2integer__new(cause, raw__float__equals_hash_value(cause, this));
}
def_pcfunk1(float__equals_hash_value, this,
	    "",
	    return f2__float__equals_hash_value(this_cause, this));


double raw__float__as__double(f2ptr cause, f2ptr this) {
  return f2float__f(this, cause);
}

f2ptr f2__float__as__double(f2ptr cause, f2ptr this) {
  assert_argument_type(float, this);
  return raw__float__as__double(cause, this);
}
def_pcfunk1(float__as__double, this,
	    "",
	    return f2__float__as__double(this_cause, this));


f2ptr f2__float__multiplied_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value * f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value * f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value * f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value * (float)raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 12462, nil);
}
def_pcfunk2(float__multiplied_by, this, that,
	    "",
	    return f2__float__multiplied_by(this_cause, this, that));


f2ptr f2__float__divided_by(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value / f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value / f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value / f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value / raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 123434, nil);
}
def_pcfunk2(float__divided_by, this, that,
	    "",
	    return f2__float__divided_by(this_cause, this, that));


f2ptr f2__float__plus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value + f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value + f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value + f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value + (float)raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 123256, nil);
}
def_pcfunk2(float__plus, this, that,
	    "",
	    return f2__float__plus(this_cause, this, that));


f2ptr f2__float__minus(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2float__new(cause, value - f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2double__new(cause, value - f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2float__new(cause, value - f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2float__new(cause, value - (float)raw__largeinteger__as__double(cause, number));
  }
  return f2larva__new(cause, 125335, nil);
}
def_pcfunk2(float__minus, this, that,
	    "",
	    return f2__float__minus(this_cause, this, that));


f2ptr f2__float__is_greater_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value > f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value > f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value > f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value > ((float)raw__largeinteger__as__double(cause, number)));
  }
  return f2larva__new(cause, 123552, nil);
}
def_pcfunk2(float__is_greater_than, this, that,
	    "",
	    return f2__float__is_greater_than(this_cause, this, that));


f2ptr f2__float__is_less_than(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value < f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value < f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value < f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value < ((float)raw__largeinteger__as__double(cause, number)));
  }
  return f2larva__new(cause, 124642, nil);
}
def_pcfunk2(float__is_less_than, this, that,
	    "",
	    return f2__float__is_less_than(this_cause, this, that));


f2ptr f2__float__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number) {
  assert_argument_type(float, this);
  float value = f2float__f(this, cause);
  if (raw__integer__is_type(cause, number)) {
    return f2bool__new(value == f2integer__i(number, cause));
  } else if (raw__double__is_type(cause, number)) {
    return f2bool__new(value == f2double__d(number, cause));
  } else if (raw__float__is_type(cause, number)) {
    return f2bool__new(value == f2float__f(number, cause));
  } else if (raw__largeinteger__is_type(cause, number)) {
    return f2bool__new(value == ((float)raw__largeinteger__as__double(cause, number)));
  }
  return f2larva__new(cause, 124625, nil);
}
def_pcfunk2(float__is_numerically_equal_to, this, that,
	    "",
	    return f2__float__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__float__square_root(f2ptr cause, f2ptr this) {
  float f = f2float__f(this, cause);
  if (f < 0) {
    return f2larva__new(cause, 5, nil);
  }
  return f2float__new(cause, sqrtf(f));
}

f2ptr f2__float__square_root(f2ptr cause, f2ptr this) {
  assert_argument_type(float, this);
  return raw__float__square_root(cause, this);
}
def_pcfunk1(float__square_root, this,
	    "",
	    return f2__float__square_root(this_cause, this));


f2ptr raw__float__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  float             f = f2float__f(this, cause);
  funk2_character_t float_string[128];
  u64               float_string__length;
  if (f - floor(f) == 0.0) {
    float_string__length = funk2_character_string__snprintf(float_string, 128, "%.1f", f);
  } else {
    float_string__length = funk2_character_string__snprintf(float_string, 128, "%g", f);
  }
  //u64               float_string__length = funk2_character_string__snprintf(float_string, 128, "%1.8f", f2float__f(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__float__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, float_string__length, float_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__float__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(float,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__float__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(float__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__float__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__float__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.f__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.f__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.as__double__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.as__double__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.divided_by__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.plus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.minus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.square_root__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.square_root__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.new__funk;
    }
  }
  return nil;
}

f2ptr f2float__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.new__funk);}
  {char* slot_name = "f";                            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.f__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk);}
  {char* slot_name = "as-double";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.as__double__funk);}
  {char* slot_name = "multiplied_by";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk);}
  {char* slot_name = "divided_by";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk);}
  {char* slot_name = "plus";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.plus__funk);}
  {char* slot_name = "minus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.minus__funk);}
  {char* slot_name = "is_greater_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk);}
  {char* slot_name = "square_root";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.square_root__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__funk);}
  return this;
}


// pointer

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_pointer);
}
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__pointer__is_type(cause, x));}
def_pcfunk1(pointer__is_type, x,   
	    "",
	    return f2__pointer__is_type(this_cause, x));

f2ptr f2__pointer__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "pointer");}
def_pcfunk1(pointer__type,    this,
	    "",
	    return f2__pointer__type(this_cause, this));

def_pcfunk1(pointer__new,     this,
	    "",
	    return f2pointer__new(this_cause, f2pointer__p(this_cause, this)));
def_pcfunk1(pointer__p,       this,
	    "",
	    return this);

boolean_t raw__pointer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2pointer__p(this, cause) == f2pointer__p(that, cause);
}

f2ptr f2__pointer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__pointer__eq(cause, this, that));
}
def_pcfunk2(pointer__eq, this, that,
	    "",
	    return f2__pointer__eq(this_cause, this, that));

u64 raw__pointer__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2pointer__p(this, cause);}

f2ptr f2__pointer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__pointer__eq_hash_value(cause, this));}
def_pcfunk1(pointer__eq_hash_value, this,
	    "",
	    return f2__pointer__eq_hash_value(this_cause, this));

boolean_t raw__pointer__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__pointer__eq( cause, this, that);}

f2ptr f2__pointer__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  return f2bool__new(raw__pointer__equals(cause, this, that));
}
def_pcfunk2(pointer__equals, this, that,
	    "",
	    return f2__pointer__equals(this_cause, this, that));


u64 raw__pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__pointer__eq_hash_value(cause, this);
}

f2ptr f2__pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(pointer,   this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__pointer__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(pointer__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__pointer__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__pointer__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__pointer__eq_hash_value(cause, this);
}

f2ptr f2__pointer__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(pointer, this);
  return f2integer__new(cause, raw__pointer__equals_hash_value(cause, this));
}
def_pcfunk1(pointer__equals_hash_value, this,
	    "",
	    return f2__pointer__equals_hash_value(this_cause, this));


f2ptr f2__pointer__plus(f2ptr cause, f2ptr this, f2ptr integer) {
  assert_argument_type(pointer, this);
  assert_argument_type(integer, integer);
  return f2pointer__new(cause, f2pointer__p(this, cause) + f2integer__i(integer, cause));
}
def_pcfunk2(pointer__plus, this, that,
	    "",
	    return f2__pointer__plus(this_cause, this, that));

f2ptr f2__pointer__minus(f2ptr cause, f2ptr this, f2ptr integer) {
  assert_argument_type(pointer, this);
  assert_argument_type(integer, integer);
  return f2pointer__new(cause, f2pointer__p(this, cause) - f2integer__i(integer, cause));
}
def_pcfunk2(pointer__minus, this, that,
	    "",
	    return f2__pointer__minus(this_cause, this, that));

f2ptr f2__pointer__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  assert_argument_type(pointer, that);
  return f2bool__new(f2pointer__p(this, cause) > f2pointer__p(that, cause));
}
def_pcfunk2(pointer__is_greater_than, this, that,
	    "",
	    return f2__pointer__is_greater_than(this_cause, this, that));

f2ptr f2__pointer__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  assert_argument_type(pointer, that);
  return f2bool__new(f2pointer__p(this, cause) < f2pointer__p(that, cause));
}
def_pcfunk2(pointer__is_less_than, this, that,
	    "",
	    return f2__pointer__is_less_than(this_cause, this, that));

f2ptr f2__pointer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(pointer, this);
  assert_argument_type(pointer, that);
  return f2bool__new(f2pointer__p(this, cause) == f2pointer__p(that, cause));
}
def_pcfunk2(pointer__is_numerically_equal_to, this, that,
	    "",
	    return f2__pointer__is_numerically_equal_to(this_cause, this, that));


f2ptr raw__pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t pointer_string[128];
  u64               pointer_string__length = funk2_character_string__snprintf(pointer_string, 128, "%c%c" ptr__fstr, (char)f2char__ch(__funk2.reader.char__escape, cause), (char)f2char__ch(__funk2.reader.char__escape_hex, cause), f2pointer__p(this, cause));
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__pointer__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, pointer_string__length, pointer_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(pointer,              this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__pointer__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(pointer__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__pointer__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__pointer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.plus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.minus__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk;
    }
  }
  return nil;
}

f2ptr f2pointer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk);}
  {char* slot_name = "p";                            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk);}
  {char* slot_name = "plus";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk);}
  {char* slot_name = "minus";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk);}
  {char* slot_name = "is_greater_than";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk);}
  {char* slot_name = "is_less_than";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk);}
  {char* slot_name = "is_numerically_equal_to";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__funk);}
  return this;
}


// cmutex

boolean_t raw__cmutex__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return ((x != nil) &&
	  (f2ptype__raw(x, cause) == ptype_cmutex));
}
f2ptr f2__cmutex__is_type(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__is_type(cause, this));
}
def_pcfunk1(cmutex__is_type, this,
	    "",
	    return f2__cmutex__is_type(this_cause, this));

f2ptr f2__cmutex__type(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return new__symbol(cause, "cmutex");
}
def_pcfunk1(cmutex__type, this,
	    "",
	    return f2__cmutex__type(this_cause, this));

f2ptr f2__cmutex__new(f2ptr cause) {return f2cmutex__new(cause);}
def_pcfunk0(cmutex__new,
	    "",
	    return f2__cmutex__new(this_cause));

boolean_t raw__cmutex__is_locked(f2ptr cause, f2ptr this) {
  return f2cmutex__is_locked(this, cause);
}

f2ptr f2__cmutex__is_locked(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__is_locked(cause, this));
}
def_pcfunk1(cmutex__is_locked, this,
	    "",
	    return f2__cmutex__is_locked(this_cause, this));

boolean_t raw__cmutex__trylock(f2ptr cause, f2ptr this) {
  return (f2cmutex__trylock(this, cause) != 0) ? boolean__true : boolean__false;
}

f2ptr f2__cmutex__trylock(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__trylock(cause, this));
}
def_pcfunk1(cmutex__trylock, this,
	    "",
	    return f2__cmutex__trylock(this_cause, this));

void raw__cmutex__unlock(f2ptr cause, f2ptr this) {
  f2cmutex__unlock(this, cause);
}

f2ptr f2__cmutex__unlock(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  raw__cmutex__unlock(cause, this);
  return nil;
}
def_pcfunk1(cmutex__unlock, this,
	    "",
	    return f2__cmutex__unlock(this_cause, this));

void raw__cmutex__scheduler_lock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__cmutex__trylock(cause, this)) {
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

void raw__cmutex__user_lock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__cmutex__trylock(cause, this)) {
    funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller));
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

void raw__cmutex__lock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__cmutex__trylock(cause, this)) {
    f2__this__fiber__yield(cause);
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

f2ptr f2__cmutex__lock(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  raw__cmutex__lock(cause, this);
  return nil;
}

boolean_t raw__cmutex__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__cmutex__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__eq(cause, this, that));
}
def_pcfunk2(cmutex__eq, this, that,
	    "",
	    return f2__cmutex__eq(this_cause, this, that));

u64 raw__cmutex__eq_hash_value(f2ptr cause, f2ptr this) {
  return ((u64)this);
}

f2ptr f2__cmutex__eq_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2integer__new(cause, raw__cmutex__eq_hash_value(cause, this));
}
def_pcfunk1(cmutex__eq_hash_value, this,
	    "",
	    return f2__cmutex__eq_hash_value(this_cause, this));

boolean_t raw__cmutex__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__cmutex__eq(cause, this, that);
}

f2ptr f2__cmutex__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(cmutex, this);
  return f2bool__new(raw__cmutex__equals(cause, this, that));
}
def_pcfunk2(cmutex__equals, this, that,
	    "",
	    return f2__cmutex__equals(this_cause, this, that));


u64 raw__cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  funk2_processor_mutex_t* m = __pure__f2cmutex__m(this);
  return funk2_processor_mutex__equals_hash_value(m);
}

f2ptr f2__cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(cmutex, this);
  return f2integer__new(cause, raw__cmutex__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(cmutex__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__cmutex__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__cmutex__equals_hash_value(f2ptr cause, f2ptr this) {
  funk2_processor_mutex_t* m = __pure__f2cmutex__m(this);
  return funk2_processor_mutex__equals_hash_value(m);
}

f2ptr f2__cmutex__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(cmutex, this);
  return f2integer__new(cause, raw__cmutex__equals_hash_value(cause, this));
}
def_pcfunk1(cmutex__equals_hash_value, this,
	    "",
	    return f2__cmutex__equals_hash_value(this_cause, this));


f2ptr raw__cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t cmutex_string[128];
  u64               cmutex_string__length;
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__cmutex__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__left_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "cmutex ");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "is_locked ");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, f2bool__new(f2cmutex__is_locked(this, cause)), terminal_print_frame);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
    return nil;
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__cmutex__foreground);
    cmutex_string__length = funk2_character_string__snprintf(cmutex_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__right_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cmutex_string__length, cmutex_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cmutex,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cmutex__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cmutex__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__cmutex__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__cmutex__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk;
    }
  }
  return nil;
}

f2ptr f2cmutex__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk);}
  {char* slot_name = "trylock";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk);}
  {char* slot_name = "unlock";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk);}
  {char* slot_name = "is_locked";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__funk);}
  return this;
}


// creadwritelock

boolean_t raw__creadwritelock__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return ((x != nil) &&
	  (f2ptype__raw(x, cause) == ptype_creadwritelock));
}
f2ptr f2__creadwritelock__is_type(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__is_type(cause, this));
}
def_pcfunk1(creadwritelock__is_type, this,
	    "",
	    return f2__creadwritelock__is_type(this_cause, this));

f2ptr f2__creadwritelock__type(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return new__symbol(cause, "creadwritelock");
}
def_pcfunk1(creadwritelock__type, this,
	    "",
	    return f2__creadwritelock__type(this_cause, this));

f2ptr f2__creadwritelock__new(f2ptr cause) {return f2creadwritelock__new(cause);}
def_pcfunk0(creadwritelock__new,
	    "",
	    return f2__creadwritelock__new(this_cause));

boolean_t raw__creadwritelock__is_writelocked(f2ptr cause, f2ptr this) {
  return f2creadwritelock__is_writelocked(this, cause);
}

f2ptr f2__creadwritelock__is_writelocked(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__is_writelocked(cause, this));
}
def_pcfunk1(creadwritelock__is_writelocked, this,
	    "",
	    return f2__creadwritelock__is_writelocked(this_cause, this));

boolean_t raw__creadwritelock__is_readlocked(f2ptr cause, f2ptr this) {
  return f2creadwritelock__is_readlocked(this, cause);
}

f2ptr f2__creadwritelock__is_readlocked(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__is_readlocked(cause, this));
}
def_pcfunk1(creadwritelock__is_readlocked, this,
	    "",
	    return f2__creadwritelock__is_readlocked(this_cause, this));

void raw__creadwritelock__scheduler_writelock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__creadwritelock__trywritelock(cause, this)) {
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

void raw__creadwritelock__user_writelock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__creadwritelock__trywritelock(cause, this)) {
    funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller));
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

void raw__creadwritelock__writelock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__creadwritelock__trywritelock(cause, this)) {
    f2__this__fiber__yield(cause);
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

f2ptr f2__creadwritelock__writelock(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  raw__creadwritelock__writelock(cause, this);
  return nil;
}

void raw__creadwritelock__scheduler_readlock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__creadwritelock__tryreadlock(cause, this)) {
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

void raw__creadwritelock__user_readlock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__creadwritelock__tryreadlock(cause, this)) {
    funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller));
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

void raw__creadwritelock__readlock(f2ptr cause, f2ptr this) {
  u64 lock_tries = 0;
  while (raw__creadwritelock__tryreadlock(cause, this)) {
    f2__this__fiber__yield(cause);
    if (lock_tries < 1000) {
      // spin fast
      lock_tries ++;
    } else if (lock_tries < 2000) {
      raw__fast_spin_sleep_yield();
      lock_tries ++;
    } else {
      raw__spin_sleep_yield();
    }
  }
}

f2ptr f2__creadwritelock__readlock(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  raw__creadwritelock__readlock(cause, this);
  return nil;
}

void raw__creadwritelock__unlock(f2ptr cause, f2ptr this) {
  f2creadwritelock__unlock(this, cause);
}

f2ptr f2__creadwritelock__unlock(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  raw__creadwritelock__unlock(cause, this);
  return nil;
}
def_pcfunk1(creadwritelock__unlock, this,
	    "",
	    return f2__creadwritelock__unlock(this_cause, this));

boolean_t raw__creadwritelock__trywritelock(f2ptr cause, f2ptr this) {
  return (f2creadwritelock__trywritelock(this, cause) != 0) ? boolean__true : boolean__false;
}

f2ptr f2__creadwritelock__trywritelock(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__trywritelock(cause, this));
}
def_pcfunk1(creadwritelock__trywritelock, this,
	    "",
	    return f2__creadwritelock__trywritelock(this_cause, this));

boolean_t raw__creadwritelock__tryreadlock(f2ptr cause, f2ptr this) {
  return (f2creadwritelock__tryreadlock(this, cause) != 0) ? boolean__true : boolean__false;
}

f2ptr f2__creadwritelock__tryreadlock(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__tryreadlock(cause, this));
}
def_pcfunk1(creadwritelock__tryreadlock, this,
	    "",
	    return f2__creadwritelock__tryreadlock(this_cause, this));

boolean_t raw__creadwritelock__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__creadwritelock__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__eq(cause, this, that));
}
def_pcfunk2(creadwritelock__eq, this, that,
	    "",
	    return f2__creadwritelock__eq(this_cause, this, that));

u64 raw__creadwritelock__eq_hash_value(f2ptr cause, f2ptr this) {
  return ((u64)this);
}

f2ptr f2__creadwritelock__eq_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2integer__new(cause, raw__creadwritelock__eq_hash_value(cause, this));
}
def_pcfunk1(creadwritelock__eq_hash_value, this,
	    "",
	    return f2__creadwritelock__eq_hash_value(this_cause, this));

boolean_t raw__creadwritelock__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__creadwritelock__eq(cause, this, that);
}

f2ptr f2__creadwritelock__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(creadwritelock, this);
  return f2bool__new(raw__creadwritelock__equals(cause, this, that));
}
def_pcfunk2(creadwritelock__equals, this, that,
	    "",
	    return f2__creadwritelock__equals(this_cause, this, that));


u64 raw__creadwritelock__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__creadwritelock__eq_hash_value(cause, this);
}

f2ptr f2__creadwritelock__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(creadwritelock, this);
  return f2integer__new(cause, raw__creadwritelock__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(creadwritelock__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__creadwritelock__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__creadwritelock__equals_hash_value(f2ptr cause, f2ptr this) {
  funk2_processor_readwritelock_t* rwlock = __pure__f2creadwritelock__rwlock(this);
  return funk2_processor_readwritelock__equals_hash_value(rwlock);
}

f2ptr f2__creadwritelock__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(creadwritelock, this);
  return f2integer__new(cause, raw__creadwritelock__equals_hash_value(cause, this));
}
def_pcfunk1(creadwritelock__equals_hash_value, this,
	    "",
	    return f2__creadwritelock__equals_hash_value(this_cause, this));


f2ptr raw__creadwritelock__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t creadwritelock_string[128];
  u64               creadwritelock_string__length;
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__creadwritelock__foreground);
    creadwritelock_string__length = funk2_character_string__snprintf(creadwritelock_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__left_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, creadwritelock_string__length, creadwritelock_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    creadwritelock_string__length = funk2_character_string__snprintf(creadwritelock_string, 128, "creadwritelock ");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, creadwritelock_string__length, creadwritelock_string);
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    creadwritelock_string__length = funk2_character_string__snprintf(creadwritelock_string, 128, "is_writelocked ");
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, creadwritelock_string__length, creadwritelock_string);
  }
  f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, f2bool__new(f2creadwritelock__is_writelocked(this, cause)), terminal_print_frame);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
    return nil;
  }
  {
    raw__terminal_print_frame__write_color__thread_unsafe(cause, terminal_print_frame, print__ansi__creadwritelock__foreground);
    creadwritelock_string__length = funk2_character_string__snprintf(creadwritelock_string, 128, "%c", (char)f2char__ch(__funk2.reader.char__right_paren, cause));
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, creadwritelock_string__length, creadwritelock_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__creadwritelock__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(creadwritelock,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__creadwritelock__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(creadwritelock__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__creadwritelock__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__creadwritelock__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__funk;
    }
  }
  return nil;
}

f2ptr f2creadwritelock__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__funk);}
  {char* slot_name = "trywritelock";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__funk);}
  {char* slot_name = "tryreadlock";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__funk);}
  {char* slot_name = "unlock";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__funk);}
  {char* slot_name = "is_writelocked";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_writelocked__funk);}
  {char* slot_name = "is_readlocked";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_readlocked__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_creadwritelock.terminal_print_with_frame__funk);}
  return this;
}


// char

boolean_t raw__char__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_char);
}
f2ptr f2__char__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__char__is_type(cause, x));}
def_pcfunk1(char__is_type, x,
	    "",
	    return f2__char__is_type(this_cause, x));

f2ptr f2__char__type(f2ptr cause, f2ptr this) {return new__symbol(cause, "char");}
def_pcfunk1(char__type, this,
	    "",
	    return f2__char__type(this_cause, this));

f2ptr f2__char__new(f2ptr cause, f2ptr character) {
  funk2_character_t character__ch;
  if (raw__char__is_type(cause, character)) {
    character__ch = f2char__ch(character, cause);
  } else if (raw__integer__is_type(cause, character)) {
    character__ch = f2integer__i(character, cause);
  } else {
    return f2larva__new(cause, 1, nil);
  }
  return f2char__new(cause, character__ch);
}

def_pcfunk1(char__new, ch,
	    "",
	    return f2__char__new(this_cause, ch));

funk2_character_t raw__char__ch(f2ptr cause, f2ptr this) {
  return f2char__ch(this, cause);
}

f2ptr f2__char__ch(f2ptr cause, f2ptr this) {
  return f2char__new(cause, raw__char__ch(cause, this));
}
def_pcfunk1(char__ch, this,
	    "",
	    return f2__char__ch(this_cause, this));

boolean_t raw__char__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2char__ch(this, cause) == f2char__ch(that, cause);
}

f2ptr f2__char__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__char__eq(cause, this, that));
}
def_pcfunk2(char__eq, this, that,
	    "",
	    return f2__char__eq(this_cause, this, that));

u64 raw__char__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2char__ch(this, cause);}

f2ptr f2__char__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__char__eq_hash_value(cause, this));}
def_pcfunk1(char__eq_hash_value, this,
	    "",
	    return f2__char__eq_hash_value(this_cause, this));

boolean_t raw__char__equals(f2ptr cause, f2ptr this, f2ptr that) {return raw__char__eq(cause, this, that);}

f2ptr f2__char__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(char, this);
  return f2bool__new(raw__char__equals(cause, this, that));
}
def_pcfunk2(char__equals, this, that,
	    "",
	    return f2__char__equals(this_cause, this, that));


u64 raw__char__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__char__eq_hash_value(cause, this);
}

f2ptr f2__char__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(char,      this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__char__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(char__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__char__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__char__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__char__eq_hash_value(cause, this);
}

f2ptr f2__char__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(char, this);
  return f2integer__new(cause, raw__char__equals_hash_value(cause, this));
}
def_pcfunk1(char__equals_hash_value, this,
	    "",
	    return f2__char__equals_hash_value(this_cause, this));


f2ptr raw__char__string(f2ptr cause, f2ptr this) {
  funk2_character_t temp[1];
  temp[0] = f2char__ch(this, cause);
  return f2string__new(cause, 1, temp);
}

f2ptr f2__char__string(f2ptr cause, f2ptr this) {
  assert_argument_type(char, this);
  return raw__char__string(cause, this);
}
def_pcfunk1(char__string, this,
	    "",
	    return f2__char__string(this_cause, this));


f2ptr raw__char__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  funk2_character_t char_string[128];
  u64               char_string__length;
  funk2_character_t ch = f2char__ch(this, cause);
  if (ch >= 28) {
    char_string__length = 3;
    char_string[0] = f2char__ch(__funk2.reader.char__escape, cause);
    char_string[1] = f2char__ch(__funk2.reader.char__escape_char, cause);
    char_string[2] = ch;
    char_string[3] = 0;
  } else {
    char_string__length = 2;
    char_string[0] = f2char__ch(__funk2.reader.char__escape, cause);
    char_string[1] = f2char__ch(__funk2.reader.char__escape_hex_char, cause);
    {
      char temp_str[128];
      u64  temp_str__length = snprintf(temp_str, 128, "%X", (uint)ch);
      {
	u64 index;
	for (index = 0; index < temp_str__length; index ++) {
	  char_string[2 + index] = temp_str[index];
	}
      }
      char_string__length += temp_str__length;
    }
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__char__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, char_string__length, char_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__char__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(char,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__char__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(char__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__char__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__char__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.ch__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.new__funk;
    }
  }
  return nil;
}

f2ptr f2char__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.new__funk);}
  {char* slot_name = "ch";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.ch__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk);}
  {char* slot_name = "string";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.string__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__funk);}
  return this;
}


// string

f2ptr raw__string__new(f2ptr cause, s64 length, funk2_character_t fill_char) {
  if (length < 0) {
    error(nil, "raw__string__new error: initial string length is less than zero.");
  }
  funk2_character_t* str__data = (funk2_character_t*)from_ptr(f2__malloc(length * sizeof(funk2_character_t)));
  {
    s64 index;
    for (index = 0; index < length; index ++) {
      str__data[index] = fill_char;
    }
  }
  f2ptr new = f2string__new(cause, length, str__data);
  f2__free(to_ptr(str__data));
  return new;
}

f2ptr f2__string__new(f2ptr cause, f2ptr length, f2ptr fill_char) {
  assert_argument_type(integer, length);
  assert_argument_type(char,    fill_char);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"),  new__symbol(cause, "string_length_cannot_be_negative"),
				   new__symbol(cause, "length"),    length,
				   new__symbol(cause, "fill_char"), fill_char));
  }
  funk2_character_t fill_char__ch = f2char__ch(fill_char, cause);
  return raw__string__new(cause, length__i, fill_char__ch);
}
def_pcfunk2(string__new, length, fill_char,
	    "",
	    return f2__string__new(this_cause, length, fill_char));


f2ptr raw__string__new_copy(f2ptr cause, f2ptr str) {
  int str__length = f2string__length(str, cause);
  if (str__length < 0) {
    error(nil, "f2__string__new_copy error: initial string length is less than zero.");
  }
  funk2_character_t* str__data = (funk2_character_t*)alloca(str__length * sizeof(funk2_character_t));
  f2string__str_copy(str, cause, str__data);
  return f2string__new(cause, str__length, str__data);
}

f2ptr f2__string__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__string__new_copy(cause, this);
}
def_pcfunk1(string__new_copy, this,
	    "",
	    return f2__string__new_copy(this_cause, this));

boolean_t raw__string__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_string);
}
f2ptr f2__string__is_type(f2ptr cause, f2ptr x) {
  return f2bool__new(raw__string__is_type(cause, x));
}
def_pcfunk1(string__is_type, x,
	    "",
	    return f2__string__is_type(this_cause, x));

f2ptr f2__string__type(f2ptr cause, f2ptr x) {
  return new__symbol(cause, "string");
}
def_pcfunk1(string__type, x,
	    "",
	    return f2__string__type(this_cause, x));

u64 raw__string__length(f2ptr cause, f2ptr this) {
  return f2string__length(this, cause);
}

f2ptr f2__string__length(f2ptr cause, f2ptr this) {
  return f2integer__new(cause, raw__string__length(cause, this));
}
def_pcfunk1(string__length, this,
	    "",
	    return f2__string__length(this_cause, this));

void raw__string__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str) {
  f2string__str_copy(this, cause, str);
}

funk2_character_t raw__string__elt(f2ptr cause, f2ptr this, s64 index) {
  if (index < 0) {
    error(nil, "array_access_out_of_bounds");
  }
  u64 length = f2string__length(this, cause);
  if (index >= length) {
    error(nil, "array_access_out_of_bounds");
  }
  return f2string__elt(this, index, cause);
}

f2ptr f2__string__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(string, this);
  u64 raw_index = f2integer__i(index, cause);
  return f2char__new(cause, raw__string__elt(cause, this, raw_index));
}
def_pcfunk2(string__elt, this, index,
	    "",
	    return f2__string__elt(this_cause, this, index));

void raw__string__elt__set(f2ptr cause, f2ptr this, s64 index, funk2_character_t value) {
  if (index < 0) {
    error(nil, "array_access_out_of_bounds");
  }
  u64 length = f2string__length(this, cause);
  if (index >= length) {
    error(nil, "array_access_out_of_bounds");
  }
  f2string__elt__set(this, index, cause, value);
}

f2ptr f2__string__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(string,  this);
  assert_argument_type(integer, index);
  assert_argument_type(char,    value);
  u64               index__i  = f2integer__i(index, cause);
  funk2_character_t value__ch = f2char__ch(value, cause);
  raw__string__elt__set(cause, this, index__i, value__ch);
  return nil;
}
def_pcfunk3(string__elt__set, this, index, value,
	    "",
	    return f2__string__elt__set(this_cause, this, index, value));


boolean_t raw__string__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__string__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  return f2bool__new(raw__string__eq(cause, this, that));
}
def_pcfunk2(string__eq, this, that,
	    "",
	    return f2__string__eq(this_cause, this, that));


u64 raw__string__eq_hash_value(f2ptr cause, f2ptr this) {
  return f2string__eq_hash_value(this, cause);
}

f2ptr f2__string__eq_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return f2integer__new(cause, raw__string__eq_hash_value(cause, this));
}
def_pcfunk1(string__eq_hash_value, this,
	    "",
	    return f2__string__eq_hash_value(this_cause, this));




u64 raw__string__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  f2ptr previous_equals_hash_value = raw__ptypehash__lookup(cause, node_ptypehash, this);
  if (previous_equals_hash_value != nil) {
    u64 previous_equals_hash_value__i = f2integer__i(previous_equals_hash_value, cause);
    return previous_equals_hash_value__i;
  }
  u64                len = f2string__length(this, cause);
  funk2_character_t* str = (funk2_character_t*)from_ptr(f2__malloc(len * sizeof(funk2_character_t)));
  f2string__str_copy(this, cause, str);
  u64 retval = (u64)character_array__hash_value(len, str);
  f2__free(to_ptr(str));
  raw__ptypehash__add(cause, node_ptypehash, this, f2integer__new(cause, retval));
  return retval;
}

f2ptr f2__string__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(string,    this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__string__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(string__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__string__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__string__equals_hash_value(f2ptr cause, f2ptr this) {
  u64 len                = f2string__length(this, cause);
  funk2_character_t* str = (funk2_character_t*)from_ptr(f2__malloc(len * sizeof(funk2_character_t)));
  f2string__str_copy(this, cause, str);
  u64 retval = (u64)character_array__hash_value(len, str);
  f2__free(to_ptr(str));
  return retval;
}

f2ptr f2__string__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return f2integer__new(cause, raw__string__equals_hash_value(cause, this));
}
def_pcfunk1(string__equals_hash_value, this,
	    "",
	    return f2__string__equals_hash_value(this_cause, this));


boolean_t raw__string__equals(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__string__is_type(cause, that)) {
    return boolean__false;
  }
  u64 this_len = f2string__length(this, cause);
  u64 that_len = f2string__length(that, cause);
  if (this_len != that_len) {
    return nil;
  }
  u64                both_len = this_len;
  funk2_character_t* this_str = alloca(both_len * sizeof(funk2_character_t));
  funk2_character_t* that_str = alloca(both_len * sizeof(funk2_character_t));
  f2string__str_copy(this, cause, this_str);
  f2string__str_copy(that, cause, that_str);
  return (memcmp(this_str, that_str, both_len * sizeof(funk2_character_t)) == 0);
}

f2ptr f2__string__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  return f2bool__new(raw__string__equals(cause, this, that));
}
def_pcfunk2(string__equals, this, that,
	    "",
	    return f2__string__equals(this_cause, this, that));


u64 raw__string__utf8_length(f2ptr cause, f2ptr this) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__string__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      utf8_str__index += utf8_code__length;
    }
  }
  f2__free(to_ptr(str));
  return utf8_str__index;
}


void raw__string__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__string__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      u8  utf8_code[6];       funk2_character__utf8_str_copy(str[index], utf8_code);
      {
	u64 utf8_code__index;
	for (utf8_code__index = 0; utf8_code__index < utf8_code__length; utf8_code__index ++) {
	  utf8_str[utf8_str__index] = utf8_code[utf8_code__index]; utf8_str__index ++;
	}
      }
    }
  }
  f2__free(to_ptr(str));
}


f2size_t raw__utf8_char__parse_character(char* utf8_string, funk2_character_t* result) {
  funk2_character_t ch0 = utf8_string[0];
  if ((ch0 & 0x80) == 0) {
    // normal ascii
    if (result != NULL) {
      *result = ch0;
    }
    return 1;
  } else if ((ch0 & 0x40) != 0) {
    if ((ch0 & 0x20) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	if (result != NULL) {
	  *result = ((ch0 & 0x1f) << 6) | (ch1 & 0x3f);
	}
	return 2;
      }
    } else if ((ch0 & 0x10) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  if (result != NULL) {
	    *result = ((ch0 & 0x0f) << 12) | ((ch1 & 0x3f) << 6) | (ch2 & 0x3f);
	  }
	  return 3;
	}
      }
    } else if ((ch0 & 0x08) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  funk2_character_t ch3 = utf8_string[3];
	  if ((ch3 & 0xc0) == 0x80) {
	    if (result != NULL) {
	      *result = ((ch0 & 0x07) << 18) | ((ch1 & 0x3f) << 12) | ((ch2 & 0x3f) << 6) | (ch3 & 0x3f);
	    }
	    return 4;
	  }
	}
      }
    } else if ((ch0 & 0x04) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  funk2_character_t ch3 = utf8_string[3];
	  if ((ch3 & 0xc0) == 0x80) {
	    funk2_character_t ch4 = utf8_string[4];
	    if ((ch4 & 0xc0) == 0x80) {
	      if (result != NULL) {
		*result = ((ch0 & 0x03) << 24) | ((ch1 & 0x3f) << 18) | ((ch2 & 0x3f) << 12) | ((ch3 & 0x3f) << 6) | (ch4 & 0x3f);
	      }
	      return 5;
	    }
	  }
	}
      }
    } else if ((ch0 & 0x02) == 0) {
      funk2_character_t ch1 = utf8_string[1];
      if ((ch1 & 0xc0) == 0x80) {
	funk2_character_t ch2 = utf8_string[2];
	if ((ch2 & 0xc0) == 0x80) {
	  funk2_character_t ch3 = utf8_string[3];
	  if ((ch3 & 0xc0) == 0x80) {
	    funk2_character_t ch4 = utf8_string[4];
	    if ((ch4 & 0xc0) == 0x80) {
	      funk2_character_t ch5 = utf8_string[5];
	      if ((ch5 & 0xc0) == 0x80) {
		if (result != NULL) {
		  *result = ((ch0 & 0x01) << 30) | ((ch1 & 0x3f) << 24) | ((ch2 & 0x3f) << 18) | ((ch3 & 0x3f) << 12) | ((ch4 & 0x3f) << 6) | (ch5 & 0x3f);
		}
		return 6;
	      }
	    }
	  }
	}
      }
    }
  }
  if (result != NULL) {
    *result = (funk2_character_t)0xFFFD;
  }
  return 1;
}

f2size_t raw__utf8_char__utf8_length(char* utf8_char) {
  return raw__utf8_char__parse_character(utf8_char, NULL);
}


u64 raw__utf8_string__length(char* utf8_string) {
  u64 length = 0;
  do {
    funk2_character_t ch;
    utf8_string += raw__utf8_char__parse_character(utf8_string, &ch);
    if (ch == 0) {
      return length;
    }
    length ++;
  } while (1);
}

void raw__utf8_string__str_copy(char* utf8_string, funk2_character_t* str) {
  u64 index = 0;
  do {
    funk2_character_t ch;
    utf8_string += raw__utf8_char__parse_character(utf8_string, &ch);
    if (ch == 0) {
      return;
    }
    str[index] = ch;
    index++;
  } while (1);
}


f2ptr raw__string__new_from_utf8(f2ptr cause, char* utf8_string) {
  u64                utf8_string__length = raw__utf8_string__length(utf8_string);
  funk2_character_t* utf8_string__str    = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (utf8_string__length + 1)));
  raw__utf8_string__str_copy(utf8_string, utf8_string__str);
  f2ptr new = f2string__new(cause, utf8_string__length, utf8_string__str);
  f2__free(to_ptr(utf8_string__str));
  return new;
}



f2ptr raw__string__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr              size                  = f2__terminal_print_frame__size(cause, terminal_print_frame);
  u64                size__i               = f2integer__i(size, cause);
  f2ptr              max_size              = f2__terminal_print_frame__max_size(cause, terminal_print_frame);
  u64                max_size__i           = f2integer__i(max_size, cause);
  f2ptr              use_one_line          = f2__terminal_print_frame__use_one_line(cause, terminal_print_frame);
  u64                string__length        = raw__string__length(cause, this);
  funk2_character_t* string__str           = (funk2_character_t*)from_ptr(f2__malloc((string__length + 1)          * sizeof(funk2_character_t))); raw__string__str_copy(cause, this, string__str); string__str[string__length] = 0;
  funk2_character_t* string_string         = (funk2_character_t*)from_ptr(f2__malloc(((string__length << 1) + 128) * sizeof(funk2_character_t)));
  string_string[0]                         = f2char__ch(__funk2.reader.char__string_quote, cause);
  u64                string_string__length = 1;
  {
    u64 size_index = 0;
    u64 index      = 0;
    while ((index < string__length) && (size__i < max_size__i)) {
      for (size_index = 0; (size_index < 8) && (index < string__length); index ++, size_index ++) {
	funk2_character_t ch = string__str[index];
	if (ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_quote, cause);
	  string_string__length ++;
	} else if ((use_one_line != nil) && (ch == (funk2_character_t)'\n')) {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_newline, cause);
	  string_string__length ++;
	} else if (ch == f2char__ch(__funk2.reader.char__escape_char, cause)) {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	} else if (ch == (funk2_character_t)'\r') {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_return, cause);
	  string_string__length ++;
	} else if (ch == (funk2_character_t)'\t') {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_tab, cause);
	  string_string__length ++;
	} else if (ch == (funk2_character_t)'\b') {
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__escape_char, cause);
	  string_string__length ++;
	  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_escape_backspace, cause);
	  string_string__length ++;
	} else {
	  string_string[string_string__length] = ch;
	  string_string__length ++;
	}
      }
      size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
    }
    if (index < string__length) {
      string_string[string_string__length] = (funk2_character_t)'.'; string_string__length ++;
      string_string[string_string__length] = (funk2_character_t)'.'; string_string__length ++;
      string_string[string_string__length] = (funk2_character_t)'.'; string_string__length ++;
      f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
    }
  }
  string_string[string_string__length] = f2char__ch(__funk2.reader.char__string_quote, cause);
  string_string__length ++;
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__string__foreground);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, string_string__length, string_string);
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  f2__free(to_ptr(string__str));
  f2__free(to_ptr(string_string));
  return nil;
}

f2ptr f2__string__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(string,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__string__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(string__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__string__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__string__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.length__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.elt__set__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.elt__set__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.new__funk;
    }
  }
  return nil;
}

f2ptr f2string__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.new__funk);}
  {char* slot_name = "new_copy";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.new_copy__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.length__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.elt__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.elt__set__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__funk);}
  return this;
}


// symbol

void raw__symbol__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str) {
  f2symbol__str_copy(this, cause, str);
}

boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_symbol);
}
f2ptr f2__symbol__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__symbol__is_type(cause, x));}
f2ptr f2__symbol__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "symbol");}

u64   raw__symbol__length(f2ptr cause, f2ptr this) {return f2symbol__length(this, cause);}
f2ptr  f2__symbol__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__symbol__length(cause, this));}

// this looks like a bug, but doing a big replacement -bo
f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2symbol__elt(x, f2integer__i(y, cause), cause));}

u64 raw__symbol__eq_hash_value(f2ptr cause, f2ptr this) {
  return f2symbol__eq_hash_value(this, cause);
}

f2ptr f2__symbol__eq_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(symbol, this);
  return f2integer__new(cause, raw__symbol__eq_hash_value(cause, this));
}
def_pcfunk1(symbol__eq_hash_value, this,
	    "",
	    return f2__symbol__eq_hash_value(this_cause, this));

f2ptr f2__symbol__new(f2ptr cause, f2ptr str) {
  assert_argument_type(string, str);
  int str__length = f2string__length(str, cause);
  if (str__length < 0) {
    error(nil, "f2__symbol__new error: initial string length is less than zero.");
  }
  funk2_character_t* str__data = (funk2_character_t*)alloca(str__length * sizeof(funk2_character_t));
  f2string__str_copy(str, cause, str__data);
  return f2symbol__new(cause, str__length, str__data);
}

boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (this == that) {
    return boolean__true;
  } else if (__f2ptr__computer_id(this) == __f2ptr__computer_id(that)) {
    return boolean__false;
  } else if (! raw__symbol__is_type(cause, that)) {
    return boolean__false;
  } else {
    u64 this__length = f2symbol__length(this, cause);
    u64 that__length = f2symbol__length(that, cause);
    if (this__length != that__length) {
      return boolean__false;
    }
    funk2_character_t* this__str = (funk2_character_t*)alloca((this__length + 1) * sizeof(funk2_character_t));
    funk2_character_t* that__str = (funk2_character_t*)alloca((that__length + 1) * sizeof(funk2_character_t));
    f2symbol__str_copy(this, cause, this__str);
    f2symbol__str_copy(that, cause, that__str);
    if (memcmp(this__str, that__str, this__length * sizeof(funk2_character_t)) != 0) {
      return boolean__false;
    } else {
      return boolean__true;
    }
  }
}

f2ptr f2__symbol__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(symbol, this);
  return f2bool__new(raw__symbol__eq(cause, this, that));
}
def_pcfunk2(symbol__eq, x, y,
	    "",
	    return f2__symbol__eq(this_cause, x, y));


boolean_t raw__symbol__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__symbol__eq(cause, this, that);
}

f2ptr f2__symbol__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(symbol, this);
  return f2bool__new(raw__symbol__equals(cause, this, that));
}
def_pcfunk2(symbol__equals, this, that,
	    "",
	    return f2__symbol__equals(this_cause, this, that));


u64 raw__symbol__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__symbol__eq_hash_value(cause, this);
}

f2ptr f2__symbol__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(symbol,    this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__symbol__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(symbol__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__symbol__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__symbol__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__symbol__eq_hash_value(cause, this);
}

f2ptr f2__symbol__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(symbol, this);
  return f2integer__new(cause, raw__symbol__equals_hash_value(cause, this));
}
def_pcfunk1(symbol__equals_hash_value, this,
	    "",
	    return f2__symbol__equals_hash_value(this_cause, this));


def_pcfunk1(symbol__is_type, x,
	    "",
	    return f2__symbol__is_type(this_cause, x));
def_pcfunk1(symbol__type, x,
	    "",
	    return f2__symbol__type(this_cause, x));
def_pcfunk1(symbol__new, str,
	    "",
	    return f2__symbol__new(this_cause, str));
def_pcfunk1(symbol__length, this,
	    "",
	    return f2__symbol__length(this_cause, this));
def_pcfunk2(symbol__elt, this, index,
	    "",
	    return f2__symbol__elt(this_cause, this, index));


u64 raw__symbol__utf8_length(f2ptr cause, f2ptr this) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__symbol__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__symbol__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      utf8_str__index += utf8_code__length;
    }
  }
  f2__free(to_ptr(str));
  return utf8_str__index;
}


void raw__symbol__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str) {
  u64                utf8_str__index = 0;
  u64                this__length    = raw__symbol__length(cause, this);
  funk2_character_t* str             = (funk2_character_t*)from_ptr(f2__malloc(this__length * sizeof(funk2_character_t)));
  raw__symbol__str_copy(cause, this, str);
  {
    u64 index;
    for (index = 0; index < this__length; index ++) {
      s64 utf8_code__length = funk2_character__utf8_length(  str[index]);
      u8  utf8_code[6];       funk2_character__utf8_str_copy(str[index], utf8_code);
      {
	u64 utf8_code__index;
	for (utf8_code__index = 0; utf8_code__index < utf8_code__length; utf8_code__index ++) {
	  utf8_str[utf8_str__index] = utf8_code[utf8_code__index]; utf8_str__index ++;
	}
      }
    }
  }
  f2__free(to_ptr(str));
}


f2ptr raw__symbol__new_from_utf8(f2ptr cause, char* utf8_string) {
  u64                utf8_string__length = raw__utf8_string__length(utf8_string);
  funk2_character_t* utf8_string__str    = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * (utf8_string__length + 1)));
  raw__utf8_string__str_copy(utf8_string, utf8_string__str);
  f2ptr new = f2symbol__new(cause, utf8_string__length, utf8_string__str);
  f2__free(to_ptr(utf8_string__str));
  return new;
}


f2ptr raw__symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  u64                symbol__length     = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str        = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  boolean_t          symbol_needs_quote = boolean__false;
  {
    u64 index;
    for (index = 0; index < symbol__length; index ++) {
      funk2_character_t ch = symbol__str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	symbol_needs_quote = boolean__true;
	break;
      }
    }
  }
  if (symbol_needs_quote) {
    funk2_character_t* symbol_string = (funk2_character_t*)from_ptr(f2__malloc(((symbol__length << 1) + 128) * sizeof(funk2_character_t)));
    symbol_string[0]                 = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    u64 symbol_string__length = 1;
    {
      u64 index;
      for (index = 0; index < symbol__length; index ++) {
	funk2_character_t ch = symbol__str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  symbol_string__length ++;
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
	  symbol_string__length ++;
	} else {
	  symbol_string[symbol_string__length] = ch;
	  symbol_string__length ++;
	}
      }
    }
    symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    symbol_string__length ++;
    if ((symbol__length > 0) && (symbol__str[0] == f2char__ch(__funk2.reader.char__symbol_key, cause))) {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    } else {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
    }
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol_string__length, symbol_string);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
    f2__free(to_ptr(symbol_string));
  } else {
    if ((symbol__length > 0) && (symbol__str[0] == f2char__ch(__funk2.reader.char__symbol_key, cause))) {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    } else {
      raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
    }
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol__length, symbol__str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  f2__free(to_ptr(symbol__str));
  return nil;
}

f2ptr f2__symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(symbol,               this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__symbol__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(symbol__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__symbol__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr raw__key_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  u64                symbol__length     = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str        = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  boolean_t          symbol_needs_quote = boolean__false;
  {
    u64 index;
    for (index = 0; index < symbol__length; index ++) {
      char ch = symbol__str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	symbol_needs_quote = boolean__true;
	break;
      }
    }
  }
  if (symbol_needs_quote) {
    funk2_character_t* symbol_string = (funk2_character_t*)from_ptr(f2__malloc(((symbol__length << 1) + 128) * sizeof(funk2_character_t)));
    symbol_string[0]                 = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    u64 symbol_string__length = 1;
    {
      u64 index;
      for (index = 0; index < symbol__length; index ++) {
	funk2_character_t ch = symbol__str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  symbol_string__length ++;
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
	  symbol_string__length ++;
	} else {
	  symbol_string[symbol_string__length] = ch;
	  symbol_string__length ++;
	}
      }
    }
    symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    symbol_string__length ++;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol_string__length, symbol_string);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
    f2__free(to_ptr(symbol_string));
  } else {
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__key__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol__length, symbol__str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  f2__free(to_ptr(symbol__str));
  return nil;
}


f2ptr raw__type_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  {
    f2ptr size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
    u64   size__i = f2integer__i(size, cause);
    size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  }
  u64                symbol__length     = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str        = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  boolean_t          symbol_needs_quote = boolean__false;
  {
    u64 index;
    for (index = 0; index < symbol__length; index ++) {
      funk2_character_t ch = symbol__str[index];
      if (ch == (funk2_character_t)' '  ||
	  ch == (funk2_character_t)'\t' ||
	  ch == (funk2_character_t)'\n' ||
	  ch == (funk2_character_t)'\r' ||
	  ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	  ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	  ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	  ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	symbol_needs_quote = boolean__true;
	break;
      }
    }
  }
  if (symbol_needs_quote) {
    funk2_character_t* symbol_string = (funk2_character_t*)from_ptr(f2__malloc(((symbol__length << 1) + 128) * sizeof(funk2_character_t)));
    symbol_string[0]                 = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    u64 symbol_string__length = 1;
    {
      u64 index;
      for (index = 0; index < symbol__length; index ++) {
	funk2_character_t ch = symbol__str[index];
	if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_escape, cause);
	  symbol_string__length ++;
	  symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
	  symbol_string__length ++;
	} else {
	  symbol_string[symbol_string__length] = ch;
	  symbol_string__length ++;
	}
      }
    }
    symbol_string[symbol_string__length] = f2char__ch(__funk2.reader.char__symbol_quote, cause);
    symbol_string__length ++;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol_string__length, symbol_string);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
    f2__free(to_ptr(symbol_string));
  } else {
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, symbol__length, symbol__str);
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  }
  f2__free(to_ptr(symbol__str));
  return nil;
}


f2ptr raw__symbol__as__string(f2ptr cause, f2ptr this) {
  u64                symbol__length = raw__symbol__length(cause, this);
  funk2_character_t* symbol__str    = (funk2_character_t*)from_ptr(f2__malloc((symbol__length + 1) * sizeof(funk2_character_t))); raw__symbol__str_copy(cause, this, symbol__str); symbol__str[symbol__length] = 0;
  f2ptr              string         = f2string__new(cause, symbol__length, symbol__str);
  f2__free(to_ptr(symbol__str));
  return string;
}

f2ptr f2__symbol__as__string(f2ptr cause, f2ptr this) {
  assert_argument_type(symbol, this);
  return raw__symbol__as__string(cause, this);
}
def_pcfunk1(symbol__as__string, this,
	    "",
	    return f2__symbol__as__string(this_cause, this));


f2ptr f2__symbol__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk;
    }
  }
  return nil;
}

f2ptr f2symbol__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk);}
  {char* slot_name = "type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.type__funk);}
  {char* slot_name = "new";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk);}
  {char* slot_name = "length";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk);}
  {char* slot_name = "elt";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk);}
  {char* slot_name = "eq";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk);}
  {char* slot_name = "eq_hash_value";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk);}
  {char* slot_name = "equals";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__funk);}
  {char* slot_name = "as-string";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.as__string__funk);}
  return this;
}


// chunk

f2ptr raw__chunk__new(f2ptr cause, u64 length) {
  return f2chunk__new(cause, length, NULL);
}

f2ptr f2__chunk__new(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return f2larva__new(cause, 220101, nil);
  }
  return raw__chunk__new(cause, length__i);
}

boolean_t raw__chunk__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if ((!cause) || (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_chunk);
}
f2ptr f2__chunk__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__chunk__is_type(cause, x));}
f2ptr f2__chunk__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "chunk");}

u64 raw__chunk__length(f2ptr cause, f2ptr this) {
  return f2chunk__length(this, cause);
}

f2ptr f2__chunk__length(f2ptr cause, f2ptr this) {
  assert_argument_type(chunk, this);
  return f2integer__new(cause, raw__chunk__length(cause, this));
}

void raw__chunk__str_copy(f2ptr cause, f2ptr this, u8* str) {
  f2chunk__str_copy(this, cause, str);
}

boolean_t raw__chunk__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__chunk__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(chunk, this);
  return f2bool__new(raw__chunk__eq(cause, this, that));
}
def_pcfunk2(chunk__eq, this, that,
	    "",
	    return f2__chunk__eq(this_cause, this, that));

u64   raw__chunk__eq_hash_value(f2ptr cause, f2ptr this) {return f2chunk__eq_hash_value(this, cause);}
f2ptr  f2__chunk__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__chunk__eq_hash_value(this, cause));}
def_pcfunk1(chunk__eq_hash_value, x,
	    "",
	    return f2__chunk__eq_hash_value(this_cause, x));


boolean_t raw__chunk__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__chunk__eq(cause, this, that);
}

f2ptr f2__chunk__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(chunk, this);
  return f2bool__new(raw__chunk__equals(cause, this, that));
}
def_pcfunk2(chunk__equals, this, that,
	    "",
	    return f2__chunk__equals(this_cause, this, that));


u64 raw__chunk__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  f2ptr previous_hash_value = raw__ptypehash__lookup(cause, node_ptypehash, this);
  if (previous_hash_value != nil) {
    u64 previous_hash_value__i = f2integer__i(previous_hash_value, cause);
    return previous_hash_value__i;
  }
  u64 hash_value__i = f2chunk__equals_hash_value(this, cause);
  raw__ptypehash__add(cause, node_ptypehash, this, f2integer__new(cause, hash_value__i));
  return hash_value__i;
}

f2ptr f2__chunk__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(chunk,     this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__chunk__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(chunk__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__chunk__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__chunk__equals_hash_value(f2ptr cause, f2ptr this) {
  return f2chunk__equals_hash_value(this, cause);
}

f2ptr f2__chunk__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(chunk, this);
  return f2integer__new(cause, raw__chunk__equals_hash_value(this, cause));
}
def_pcfunk1(chunk__equals_hash_value, x,
	    "",
	    return f2__chunk__equals_hash_value(this_cause, x));


def_pcfunk1(chunk__is_type, x,
	    "",
	    return f2__chunk__is_type(this_cause, x));

def_pcfunk1(chunk__type, x,
	    "",
	    return f2__chunk__type(this_cause, x));

def_pcfunk1(chunk__new, length,
	    "",
	    return f2__chunk__new(this_cause, length));

def_pcfunk1(chunk__length, x,
	    "",
	    return f2__chunk__length(this_cause, x));

u8 raw__chunk__bit8__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit8__elt(this, index, cause);
}

f2ptr f2__chunk__bit8__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  return f2pointer__new(cause, raw__chunk__bit8__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit8__elt, this, index,
	    "",
	    return f2__chunk__bit8__elt(this_cause, this, index));


void raw__chunk__bit8__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit8__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit8__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  s64 value__p = f2pointer__p(value, cause);
  if ((value__p < 0) || (value__p >= (((u64)1) << 8))) {
    return f2larva__new(cause, 3, nil);
  }
  raw__chunk__bit8__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit8__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit8__elt__set(this_cause, this, index, value));


u16 raw__chunk__bit16__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit16__elt(this, index, cause);
}

f2ptr f2__chunk__bit16__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  return f2pointer__new(cause, raw__chunk__bit16__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit16__elt, this, index,
	    "",
	    return f2__chunk__bit16__elt(this_cause, this, index));


void raw__chunk__bit16__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit16__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit16__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  s64 value__p = f2pointer__p(value, cause);
  if ((value__p < 0) || (value__p >= (((u64)1) << 16))) {
    return f2larva__new(cause, 3, nil);
  }
  raw__chunk__bit16__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit16__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit16__elt__set(this_cause, this, index, value));

//def_pcfunk2(chunk__bit16__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit16__elt(this, this_cause, f2integer__i(index, this_cause))));
//def_pcfunk3(chunk__bit16__elt__set, this, index, value, f2chunk__bit16__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);


u32 raw__chunk__bit32__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit32__elt(this, index, cause);
}

f2ptr f2__chunk__bit32__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause) - 3)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  return f2pointer__new(cause, raw__chunk__bit32__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit32__elt, this, index,
	    "",
	    return f2__chunk__bit32__elt(this_cause, this, index));


void raw__chunk__bit32__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit32__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit32__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  s64 value__p = f2pointer__p(value, cause);
  if ((value__p < 0) || (value__p >= (((u64)1) << 32))) {
    return f2larva__new(cause, 3, nil);
  }
  raw__chunk__bit32__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit32__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit32__elt__set(this_cause, this, index, value));

//def_pcfunk2(chunk__bit32__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit32__elt(this, this_cause, f2integer__i(index, this_cause))));
//def_pcfunk3(chunk__bit32__elt__set, this, index, value, f2chunk__bit32__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);


u64 raw__chunk__bit64__elt(f2ptr cause, f2ptr this, s64 index) {
  return f2chunk__bit64__elt(this, index, cause);
}

f2ptr f2__chunk__bit64__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  return f2pointer__new(cause, raw__chunk__bit64__elt(cause, this, index__i));
}
def_pcfunk2(chunk__bit64__elt, this, index,
	    "",
	    return f2__chunk__bit64__elt(this_cause, this, index));


void raw__chunk__bit64__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value) {
  f2chunk__bit64__elt__set(this, index, cause, value);
}

f2ptr f2__chunk__bit64__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  assert_argument_type(chunk,   this);
  assert_argument_type(integer, index);
  assert_argument_type(pointer, value);
  s64 index__i = f2integer__i(index, cause);
  if ((index__i < 0) || (index__i >= f2chunk__length(this, cause))) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "array_access_out_of_bounds"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "index"),    index));
  }
  s64 value__p = f2pointer__p(value, cause);
  // don't need to check range here because 64 bits is the size of our pointer object.
  raw__chunk__bit64__elt__set(cause, this, index__i, value__p);
  return nil;
}
def_pcfunk3(chunk__bit64__elt__set, this, index, value,
	    "",
	    return f2__chunk__bit64__elt__set(this_cause, this, index, value));

//def_pcfunk2(chunk__bit64__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit64__elt(this, this_cause, f2integer__i(index, this_cause))));
//def_pcfunk3(chunk__bit64__elt__set, this, index, value, f2chunk__bit64__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);


def_pcfunk4(chunk__cfunk_jump, this, fiber, env, args,
	    "",
	    return f2chunk__cfunk_jump(this, this_cause, fiber, env, args));
def_pcfunk2(chunk__bytecode_jump, this, fiber,
	    "",
	    return f2integer__new(this_cause, f2chunk__bytecode_jump(this, this_cause, fiber)));


f2ptr raw__chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr size                     = f2__terminal_print_frame__size(                    cause, terminal_print_frame);
  u64   size__i                  = f2integer__i(size, cause);
  f2ptr x                        = f2__terminal_print_frame__x(                       cause, terminal_print_frame);
  u64   x__i                     = f2integer__i(x, cause);
  f2ptr max_size                 = f2__terminal_print_frame__max_size(                cause, terminal_print_frame);
  u64   max_size__i              = f2integer__i(max_size, cause);
  f2ptr testing                  = f2__terminal_print_frame__testing(                 cause, terminal_print_frame);
  f2ptr testing_max_x_constraint = f2__terminal_print_frame__testing_max_x_constraint(cause, terminal_print_frame);
  f2ptr use_one_line             = f2__terminal_print_frame__use_one_line(            cause, terminal_print_frame);
  f2ptr indent_distance          = f2__terminal_print_frame__indent_distance(         cause, terminal_print_frame);
  u64   indent_distance__i       = f2integer__i(indent_distance, cause);
  {
    indent_distance__i = x__i + 7;
    indent_distance    = f2integer__new(cause, indent_distance__i);
    f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
  }
  f2ptr max_x                = f2__terminal_print_frame__max_x(cause, terminal_print_frame);
  u64   max_x__i             = f2integer__i(max_x, cause);
  u64   chunk__length        = raw__chunk__length(cause, this);
  u64                chunk_string__max_length = (chunk__length * 5) + max_x__i + 128;
  funk2_character_t* chunk_string             = (funk2_character_t*)from_ptr(f2__malloc(chunk_string__max_length * sizeof(funk2_character_t)));
  u64                chunk_string__length     = 0;
  {
    chunk_string[0]      = f2char__ch(__funk2.reader.char__left_paren, cause);
    chunk_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  {
    chunk_string__length = funk2_character_string__snprintf(chunk_string, chunk_string__max_length, "chunk ");
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__type__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
  {
    chunk_string__length = 0;
    {
      u64 index;
      for (index = 0; index < chunk__length; index ++) {
	if (size__i < max_size__i) {
	  size__i ++; size = f2integer__new(cause, size__i); f2__terminal_print_frame__size__set(cause, terminal_print_frame, size);
	  u64 increment_distance = funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, "#x%02x", f2chunk__bit8__elt(this, index, cause));
	  chunk_string__length += increment_distance;
	  x__i                 += increment_distance;
	  if (index < (chunk__length - 1)) {
	    if (max_x__i - x__i <= 5) {
	      chunk_string__length += funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, "\n");
	      x__i                  = indent_distance__i;
	      if ((testing != nil) && (testing_max_x_constraint != nil) && (use_one_line != nil)) {
		f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	      }
	    } else {
	      u64 increment_distance = funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, " ");
	      chunk_string__length += increment_distance;
	      x__i                 += increment_distance;
	    }
	  }
	} else {
	  f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	  u64 increment_distance = funk2_character_string__snprintf(chunk_string + chunk_string__length, chunk_string__max_length - chunk_string__length, "...");
	  chunk_string__length += increment_distance;
	  x__i                 += increment_distance;
	  break;
	}
      }
    }
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__pointer__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  {
    chunk_string[0]      = f2char__ch(__funk2.reader.char__right_paren, cause);
    chunk_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, chunk_string__length, chunk_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  f2__free(to_ptr(chunk_string));
  return nil;
}

f2ptr f2__chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(chunk,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__chunk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(chunk__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__chunk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__chunk__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk;
    }
  }
  return nil;
}

f2ptr f2chunk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk);}
  {char* slot_name = "new_copy";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.new_copy__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk);}
  {char* slot_name = "bit8-elt";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk);}
  {char* slot_name = "bit8-elt";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk);}
  {char* slot_name = "bit16-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk);}
  {char* slot_name = "bit16-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk);}
  {char* slot_name = "bit32-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk);}
  {char* slot_name = "bit32-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk);}
  {char* slot_name = "bit64-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk);}
  {char* slot_name = "bit64-elt";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk);}
  {char* slot_name = "cfunk_jump";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk);}
  {char* slot_name = "bytecode_jump";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__funk);}
  return this;
}


// simple_array

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_simple_array);
}
f2ptr f2__simple_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__simple_array__is_type(cause, x));}
f2ptr f2__simple_array__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "simple_array");}

f2ptr f2__simple_array__new(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return f2larva__new(cause, 222010, nil);
  }
  return f2simple_array__new(cause, length__i, to_ptr(NULL));
}

u64 raw__simple_array__length(f2ptr cause, f2ptr this) {return f2simple_array__length(this, cause);}
f2ptr f2__simple_array__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__simple_array__length(cause, this));}

f2ptr raw__simple_array__elt(f2ptr cause, f2ptr this, u64 index) {return f2simple_array__elt(this, index, cause);}
f2ptr f2__simple_array__elt(f2ptr cause, f2ptr this, f2ptr index) {return raw__simple_array__elt(cause, this, f2integer__i(index, cause));}

f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2simple_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}

boolean_t raw__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__simple_array__eq(cause, this, that));
}
def_pcfunk2(simple_array__eq, this, that,
	    "",
	    return f2__simple_array__eq(this_cause, this, that));

u64   raw__simple_array__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)this;}
f2ptr  f2__simple_array__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__simple_array__eq_hash_value(cause, this));}
def_pcfunk1(simple_array__eq_hash_value, this,
	    "",
	    return f2__simple_array__eq_hash_value(this_cause, this));


boolean_t raw__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__array__equals(cause, this, that);
}

f2ptr f2__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(simple_array, this);
  return f2bool__new(raw__simple_array__equals(cause, this, that));
}
def_pcfunk2(simple_array__equals, this, that,
	    "",
	    return f2__simple_array__equals(this_cause, this, that));


f2ptr raw__simple_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  return raw__array__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__simple_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  assert_argument_type(simple_array, this);
  assert_argument_type(ptypehash,    node_hash);
  return raw__simple_array__equals_hash_value__loop_free(cause, this, node_hash);
}
def_pcfunk2(simple_array__equals_hash_value__loop_free, this, node_hash,
	    "",
	    return f2__simple_array__equals_hash_value__loop_free(this_cause, this, node_hash));


f2ptr raw__simple_array__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__array__equals_hash_value(cause, this);
}


f2ptr f2__simple_array__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(simple_array, this);
  return f2__simple_array__equals_hash_value(cause, this);
}
def_pcfunk1(simple_array__equals_hash_value, this,
	    "",
	    return f2__simple_array__equals_hash_value(this_cause, this));


def_pcfunk1(simple_array__is_type, x,
	    "",
	    return f2__simple_array__is_type(this_cause, x));
def_pcfunk1(simple_array__type, x,
	    "",
	    return f2__simple_array__type(this_cause, x));
def_pcfunk1(simple_array__new, length,
	    "",
	    return f2__simple_array__new(this_cause, length));
def_pcfunk1(simple_array__length, x,
	    "",
	    return f2__simple_array__length(this_cause, x));
def_pcfunk2(simple_array__elt, x, y,
	    "",
	    return f2__simple_array__elt(this_cause, x, y));
def_pcfunk3(simple_array__elt__set, x, y, z,
	    "",
	    return f2__simple_array__elt__set(this_cause, x, y, z));


f2ptr f2__simple_array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(simple_array,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__array__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(simple_array__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__simple_array__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__simple_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk;
    }
  }
  return nil;
}

f2ptr f2simple_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk);}
  {char* slot_name = "new_copy";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.new_copy__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__funk);}
  return this;
}


// traced_array

boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_traced_array);
}
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__traced_array__is_type(cause, x));}
f2ptr f2__traced_array__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "traced_array");}

f2ptr f2__traced_array__new(f2ptr cause, f2ptr length) {
  assert_argument_type(integer, length);
  s64 length__i = f2integer__i(length, cause);
  if (length__i < 0) {
    return f2larva__new(cause, 2201, nil);
  }
  return f2traced_array__new(cause, length__i, to_ptr(NULL));
}

u64   raw__traced_array__length(f2ptr cause, f2ptr this) {return f2traced_array__length(this, cause);}
f2ptr  f2__traced_array__length(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_array, this);
  return f2integer__new(cause, raw__traced_array__length(cause, this));
}

f2ptr raw__traced_array__elt(f2ptr cause, f2ptr this, u64   index) {return f2traced_array__elt(this, index, cause);}
f2ptr  f2__traced_array__elt(f2ptr cause, f2ptr this, f2ptr index) {
  assert_argument_type(traced_array, this);
  assert_argument_type(integer,      index);
  return raw__traced_array__elt(cause, this, f2integer__i(index, cause));
}

f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__tracing_on(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__tracing_on__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__trace(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__trace__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__imagination_frame(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__imagination_frame__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__mutate_funks(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__mutate_funks(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__mutate_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__mutate_funks__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__read_funks(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__read_funks(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__read_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__read_funks__set(x, f2integer__i(y, cause), cause, z); return nil;}

def_pcfunk1(traced_array__is_type, x,
	    "",
	    return f2__traced_array__is_type(this_cause, x));
def_pcfunk1(traced_array__type, x,
	    "",
	    return f2__traced_array__type(this_cause, x));
def_pcfunk1(traced_array__new, length,
	    "",
	    return f2__traced_array__new(this_cause, length));
def_pcfunk1(traced_array__length, x,
	    "",
	    return f2__traced_array__length(this_cause, x));
def_pcfunk2(traced_array__elt, x, y,
	    "",
	    return f2__traced_array__elt(this_cause, x, y));
def_pcfunk3(traced_array__elt__set, x, y, z,
	    "",
	    return f2__traced_array__elt__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__tracing_on, x, y,
	    "",
	    return f2__traced_array__elt__tracing_on(this_cause, x, y));
def_pcfunk3(traced_array__elt__tracing_on__set, x, y, z,
	    "",
	    return f2__traced_array__elt__tracing_on__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__trace, x, y,
	    "",
	    return f2__traced_array__elt__trace(this_cause, x, y));
def_pcfunk3(traced_array__elt__trace__set, x, y, z,
	    "",
	    return f2__traced_array__elt__trace__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__imagination_frame, x, y,
	    "",
	    return f2__traced_array__elt__imagination_frame(this_cause, x, y));
def_pcfunk3(traced_array__elt__imagination_frame__set, x, y, z,
	    "",
	    return f2__traced_array__elt__imagination_frame__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__mutate_funks, x, y,
	    "",
	    return f2__traced_array__elt__mutate_funks(this_cause, x, y));
def_pcfunk3(traced_array__elt__mutate_funks__set, x, y, z,
	    "",
	    return f2__traced_array__elt__mutate_funks__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__read_funks, x, y,
	    "",
	    return f2__traced_array__elt__read_funks(this_cause, x, y));
def_pcfunk3(traced_array__elt__read_funks__set, x, y, z,
	    "",
	    return f2__traced_array__elt__read_funks__set(this_cause, x, y, z));

boolean_t raw__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return this == that;
}

f2ptr f2__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return f2bool__new(raw__traced_array__eq(cause, this, that));
}
def_pcfunk2(traced_array__eq, this, that,
	    "",
	    return f2__traced_array__eq(this_cause, this, that));

u64   raw__traced_array__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)this;}
f2ptr  f2__traced_array__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__traced_array__eq_hash_value(cause, this));}
def_pcfunk1(traced_array__eq_hash_value, this,
	    "",
	    return f2__traced_array__eq_hash_value(this_cause, this));


boolean_t raw__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__array__equals(cause, this, that);
}

f2ptr f2__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(traced_array, this);
  return f2bool__new(raw__traced_array__equals(cause, this, that));
}
def_pcfunk2(traced_array__equals, this, that,
	    "",
	    return f2__traced_array__equals(this_cause, this, that));


f2ptr raw__traced_array__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__array__equals_hash_value(cause, this);
}

f2ptr f2__traced_array__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(traced_array, this);
  return raw__traced_array__equals_hash_value(cause, this);
}
def_pcfunk1(traced_array__equals_hash_value, this,
	    "",
	    return f2__traced_array__equals_hash_value(this_cause, this));


f2ptr raw__traced_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash) {
  return raw__array__equals_hash_value__loop_free(cause, this, node_hash);
}

f2ptr f2__traced_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(traced_array, this);
  assert_argument_type(ptypehash,    node_ptypehash);
  return raw__traced_array__equals_hash_value__loop_free(cause, this, node_ptypehash);
}
def_pcfunk2(traced_array__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__traced_array__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


f2ptr f2__traced_array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(traced_array,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__array__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(traced_array__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__traced_array__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__traced_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk;
    }
  }
  return nil;
}

f2ptr f2traced_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk);}
  {char* slot_name = "length";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk);}
  {char* slot_name = "elt";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk);}
  {char* slot_name = "elt-tracing_on";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk);}
  {char* slot_name = "elt-tracing_on";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk);}
  {char* slot_name = "elt-trace";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk);}
  {char* slot_name = "elt-trace";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk);}
  {char* slot_name = "elt-imagination_frame";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk);}
  {char* slot_name = "elt-imagination_frame";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk);}
  {char* slot_name = "elt-mutate_funks";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk);}
  {char* slot_name = "elt-mutate_funks";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk);}
  {char* slot_name = "elt-read_funks";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk);}
  {char* slot_name = "elt-read_funks";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__funk);}
  return this;
}



// larva

boolean_t raw__larva__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_larva);
}
f2ptr f2__larva__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__larva__is_type(cause, x));}
def_pcfunk1(larva__is_type, x,
	    "",
	    return f2__larva__is_type(this_cause, x));

f2ptr f2__larva__type(f2ptr cause, f2ptr x) {return new__symbol(cause, "larva");}
def_pcfunk1(larva__type, x,
	    "",
	    return f2__larva__type(this_cause, x));

u32 raw__larva__larva_type(f2ptr cause, f2ptr this) {
  return f2larva__larva_type(this, cause);
}

f2ptr f2__larva__larva_type(f2ptr cause, f2ptr this) {
  assert_argument_type(larva, this);
  return f2integer__new(cause, raw__larva__larva_type(cause, this));
}

f2ptr raw__larva__bug(f2ptr cause, f2ptr this) {
  return f2larva__bug(this, cause);
}

f2ptr f2__larva__bug(f2ptr cause, f2ptr this) {
  assert_argument_type(larva, this);
  return raw__larva__bug(cause, this);
}

f2ptr f2__larva__new(f2ptr cause, f2ptr larva_type, f2ptr bug) {
  assert_argument_type(       integer, larva_type);
  assert_argument_type_or_nil(bug,     bug);
  return f2larva__new(cause, f2integer__i(larva_type, cause), bug);
}

def_pcfunk2(larva__new,        larva_type, bug,
	    "",
	    return f2__larva__new(this_cause, larva_type, bug));
def_pcfunk1(larva__larva_type, this,
	    "",
	    return f2__larva__larva_type(this_cause, this));
def_pcfunk1(larva__bug,        this,
	    "",
	    return f2__larva__bug(this_cause, this));

boolean_t raw__larva__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if (! raw__larva__is_type(cause, that)) {
    return boolean__false;
  }
  return f2larva__larva_type(this, cause) == f2larva__larva_type(that, cause);
}

f2ptr f2__larva__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(larva, this);
  return f2bool__new(raw__larva__eq(cause, this, that));
}
def_pcfunk2(larva__eq, this, that,
	    "",
	    return f2__larva__eq(this_cause, this, that));

u64 raw__larva__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2larva__larva_type(this, cause);}

f2ptr f2__larva__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__larva__eq_hash_value(cause, this));}
def_pcfunk1(larva__eq_hash_value, this,
	    "",
	    return f2__larva__eq_hash_value(this_cause, this));


boolean_t raw__larva__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__larva__eq(cause, this, that);
}

f2ptr f2__larva__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(larva, this);
  return f2bool__new(raw__larva__equals(cause, this, that));
}
def_pcfunk2(larva__equals, this, that,
	    "",
	    return f2__larva__equals(this_cause, this, that));


u64 raw__larva__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__larva__eq_hash_value(cause, this);
}

f2ptr f2__larva__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(larva,     this);
  assert_argument_type(ptypehash, node_ptypehash);
  return f2integer__new(cause, raw__larva__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(larva__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__larva__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__larva__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__larva__eq_hash_value(cause, this);
}

f2ptr f2__larva__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(larva, this);
  return f2integer__new(cause, raw__larva__equals_hash_value(cause, this));
}
def_pcfunk1(larva__equals_hash_value, this,
	    "",
	    return f2__larva__equals_hash_value(this_cause, this));


f2ptr raw__larva__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "larva"),
					       new__symbol(cause, "larva_type"),        f2__larva__larva_type(cause, this),
					       new__symbol(cause, "bug"),               f2__larva__bug(       cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__larva__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(larva,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__larva__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(larva__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__larva__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__larva__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.type__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.new__funk;
    }
  }
  return nil;
}

f2ptr f2larva__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.new__funk);}
  {char* slot_name = "larva_type";                  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__funk);}
  return this;
}


// mutable_array_pointer

f2ptr f2__mutable_array_pointer__new(f2ptr cause, f2ptr array, f2ptr index) {
  assert_argument_type_or_nil(array,   array);
  assert_argument_type(       integer, index);
  return f2mutable_array_pointer__new(cause, array, f2integer__i(index, cause));
}

def_pcfunk2(mutable_array_pointer__new, array, index,
	    "",
	    return f2__mutable_array_pointer__new(this_cause, array, index));

boolean_t raw__mutable_array_pointer__is_type(f2ptr cause, f2ptr x) {
  //check_wait_politely();
  //#ifdef F2__PTYPE__TYPE_CHECK
  //if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
  //#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_mutable_array_pointer);
}
f2ptr f2__mutable_array_pointer__is_type(f2ptr cause, f2ptr x) {
  return f2bool__new(raw__mutable_array_pointer__is_type(cause, x));
}
def_pcfunk1(mutable_array_pointer__is_type, x,
	    "",
	    return f2__mutable_array_pointer__is_type(this_cause, x));

f2ptr f2__mutable_array_pointer__type(f2ptr cause, f2ptr x) {
  return new__symbol(cause, "mutable_array_pointer");
}
def_pcfunk1(mutable_array_pointer__type, x,
	    "",
	    return f2__mutable_array_pointer__type(this_cause, x));


f2ptr raw__mutable_array_pointer__array(f2ptr cause, f2ptr this) {
  return f2mutable_array_pointer__array(this, cause);
}

f2ptr f2__mutable_array_pointer__array(f2ptr cause, f2ptr this) {
  assert_argument_type(mutable_array_pointer, this);
  return raw__mutable_array_pointer__array(cause, this);
}
def_pcfunk1(mutable_array_pointer__array, this,
	    "",
	    return f2__mutable_array_pointer__array(this_cause, this));


void raw__mutable_array_pointer__array__set(f2ptr cause, f2ptr this, f2ptr value) {
  f2mutable_array_pointer__array__set(this, cause, value);
}

f2ptr f2__mutable_array_pointer__array__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(mutable_array_pointer, this);
  assert_argument_type(array,                 value);
  raw__mutable_array_pointer__array__set(cause, this, value);
  return nil;
}
def_pcfunk2(mutable_array_pointer__array__set, this, value,
	    "",
	    return f2__mutable_array_pointer__array__set(this_cause, this, value));


u64 raw__mutable_array_pointer__index(f2ptr cause, f2ptr this) {
  return f2mutable_array_pointer__index(this, cause);
}

f2ptr f2__mutable_array_pointer__index(f2ptr cause, f2ptr this) {
  assert_argument_type(mutable_array_pointer, this);
  return f2integer__new(cause, raw__mutable_array_pointer__index(cause, this));
}
def_pcfunk1(mutable_array_pointer__index, this,
	    "",
	    return f2__mutable_array_pointer__index(this_cause, this));


void raw__mutable_array_pointer__index__set(f2ptr cause, f2ptr this, u64 value) {
  f2mutable_array_pointer__index__set(this, cause, value);
}

f2ptr f2__mutable_array_pointer__index__set(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(mutable_array_pointer, this);
  assert_argument_type(integer,               value);
  u64 value__i = f2integer__i(value, cause);
  raw__mutable_array_pointer__index__set(cause, this, value__i);
  return nil;
}
def_pcfunk2(mutable_array_pointer__index__set, this, value,
	    "",
	    return f2__mutable_array_pointer__index__set(this_cause, this, value));


boolean_t raw__mutable_array_pointer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  return (this == that);
}

f2ptr f2__mutable_array_pointer__eq(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(mutable_array_pointer, this);
  return f2bool__new(raw__mutable_array_pointer__eq(cause, this, that));
}
def_pcfunk2(mutable_array_pointer__eq, this, that,
	    "",
	    return f2__mutable_array_pointer__eq(this_cause, this, that));


u64 raw__mutable_array_pointer__eq_hash_value(f2ptr cause, f2ptr this) {
  return (u64)this;
}

f2ptr f2__mutable_array_pointer__eq_hash_value(f2ptr cause, f2ptr this) {
  return f2integer__new(cause, raw__mutable_array_pointer__eq_hash_value(cause, this));
}
def_pcfunk1(mutable_array_pointer__eq_hash_value, this,
	    "",
	    return f2__mutable_array_pointer__eq_hash_value(this_cause, this));


boolean_t raw__mutable_array_pointer__equals(f2ptr cause, f2ptr this, f2ptr that) {
  return raw__mutable_array_pointer__eq(cause, this, that);
}

f2ptr f2__mutable_array_pointer__equals(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(mutable_array_pointer, this);
  return f2bool__new(raw__mutable_array_pointer__equals(cause, this, that));
}
def_pcfunk2(mutable_array_pointer__equals, this, that,
	    "",
	    return f2__mutable_array_pointer__equals(this_cause, this, that));


u64 raw__mutable_array_pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  return raw__mutable_array_pointer__eq_hash_value(cause, this);
}

f2ptr f2__mutable_array_pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash) {
  assert_argument_type(mutable_array_pointer, this);
  assert_argument_type(ptypehash,             node_ptypehash);
  return f2integer__new(cause, raw__mutable_array_pointer__equals_hash_value__loop_free(cause, this, node_ptypehash));
}
def_pcfunk2(mutable_array_pointer__equals_hash_value__loop_free, this, node_ptypehash,
	    "",
	    return f2__mutable_array_pointer__equals_hash_value__loop_free(this_cause, this, node_ptypehash));


u64 raw__mutable_array_pointer__equals_hash_value(f2ptr cause, f2ptr this) {
  return raw__mutable_array_pointer__eq_hash_value(cause, this);
}

f2ptr f2__mutable_array_pointer__equals_hash_value(f2ptr cause, f2ptr this) {
  assert_argument_type(mutable_array_pointer, this);
  return f2integer__new(cause, raw__mutable_array_pointer__equals_hash_value(cause, this));
}
def_pcfunk1(mutable_array_pointer__equals_hash_value, this,
	    "",
	    return f2__mutable_array_pointer__equals_hash_value(this_cause, this));


f2ptr raw__mutable_array_pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "mutable_array_pointer"),
					       new__symbol(cause, "array"),             f2__mutable_array_pointer__array(cause, this),
					       new__symbol(cause, "index"),             f2__mutable_array_pointer__index(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__mutable_array_pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(mutable_array_pointer, this);
  assert_argument_type(terminal_print_frame,  terminal_print_frame);
  return raw__mutable_array_pointer__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(mutable_array_pointer__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__mutable_array_pointer__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__mutable_array_pointer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__funk;
    } else if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__funk;
    }
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (raw__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (raw__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__funk;
    }
  }
  return nil;
}

f2ptr f2mutable_array_pointer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, raw__cons__new(cause, new__symbol(cause, "ptype"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.is_type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__funk);}
  {char* slot_name = "new";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__funk);}
  {char* slot_name = "array";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__funk);}
  {char* slot_name = "array";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__set__funk);}
  {char* slot_name = "index";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__funk);}
  {char* slot_name = "index";                       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__set__funk);}
  {char* slot_name = "eq";                          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__funk);}
  {char* slot_name = "eq_hash_value";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__funk);}
  {char* slot_name = "equals";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__funk);}
  {char* slot_name = "equals_hash_value-loop_free"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__funk);}
  {char* slot_name = "equals_hash_value";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__funk);}
  {char* slot_name = "terminal_print_with_frame";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.terminal_print_with_frame__funk);}
  return this;
}


// gensym

f2ptr raw__gensym(f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string) {
  int pool_index = this_processor_thread__pool_index();
  return funk2_symbol_hash__generate_new_random_symbol(&(__funk2.ptypes.symbol_hash), pool_index, cause, initial_string_length, initial_string);
}

f2ptr f2__gensym(f2ptr cause, f2ptr initial_string) {
  assert_argument_type(string, initial_string);
  s64                initial_string__length = raw__string__length(cause, initial_string);
  funk2_character_t* initial_string__str    = (funk2_character_t*)from_ptr(f2__malloc((initial_string__length + 1) * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, initial_string, initial_string__str);
  initial_string__str[initial_string__length] = 0;
  f2ptr new_symbol = raw__gensym(cause, initial_string__length, initial_string__str);
  f2__free(to_ptr(initial_string__str));
  return new_symbol;
}
def_pcfunk1(gensym, initial_string,
	    "generates a symbol that did not exist previously.",
	    return f2__gensym(this_cause, initial_string));

f2ptr raw__gensym__new_from_utf8(f2ptr cause, char* initial_utf8_string) {
  u64                initial_string__length = raw__utf8_string__length(initial_utf8_string);
  funk2_character_t* initial_string         = (funk2_character_t*)from_ptr(f2__malloc(initial_string__length * sizeof(funk2_character_t)));
  raw__utf8_string__str_copy(initial_utf8_string, initial_string);
  f2ptr new = raw__gensym(cause, initial_string__length, initial_string);
  f2__free(to_ptr(initial_string));
  return new;
}



// **

void f2__ptypes_object_slots__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  // ptypes
  
  f2__primcfunk__init__defragment__fix_pointers(ptypes__read_write_reflective_tracing_enabled__set);
  
	      

  // ptype
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.raw__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__raw);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.raw__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.cause__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__cause);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.cause__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.cause__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__cause__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.cause__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.creation_fiber__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__creation_fiber);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.creation_fiber__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.creation_fiber__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ptype__creation_fiber__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.creation_fiber__set__funk);
  
  // integer
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.i__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__i);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.i__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.as__double__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__as__double);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__as__pointer);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__multiplied_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.divided_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__divided_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.plus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__plus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.plus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.minus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__minus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.minus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__is_greater_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__is_less_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__is_numerically_equal_to);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.square_root__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__square_root);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.modulo__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__modulo);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.modulo__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(integer__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__funk);
  
  // double
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.d__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__d);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.d__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.as__double__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__as__double);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.as__double__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__multiplied_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.divided_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__divided_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.plus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__plus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.plus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.minus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__minus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.minus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__is_greater_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_less_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__is_less_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__is_numerically_equal_to);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.square_root__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__square_root);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.square_root__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_sine__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__radian_sine);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_sine__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__radian_arcsine);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__radian_cosine);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__radian_arccosine);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__radian_tangent);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__radian_arctangent);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.power__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__power);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.power__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.modulo__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__modulo);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.modulo__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(double__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__funk);
  
  // float
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.f__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__f);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.f__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.as__double__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__as__double);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.as__double__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__multiplied_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.divided_by__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__divided_by);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.plus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__plus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.plus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.minus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__minus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.minus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__is_greater_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_less_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__is_less_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__is_numerically_equal_to);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.square_root__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__square_root);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.square_root__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(float__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__funk);
  
  // pointer
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__p);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.p__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.plus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__plus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.minus__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__minus);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__is_greater_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__is_less_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__is_numerically_equal_to);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pointer__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__funk);
  
  // cmutex
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__unlock);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__trylock);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__is_locked);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(cmutex__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__funk);
  
  // creadwritelock
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__unlock);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__trywritelock);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__tryreadlock);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_writelocked__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__is_writelocked);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_writelocked__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_readlocked__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__is_readlocked);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_readlocked__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(creadwritelock__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_creadwritelock.terminal_print_with_frame__funk);
  
  // char
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.ch__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__ch);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.ch__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.string__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__string);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.string__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(char__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__funk);
  
  // string
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.new_copy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__new_copy);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.new_copy__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__length);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(string__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__funk);
  
  // symbol
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__length);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.as__string__symbol);
  f2__primcfunk__init__defragment__fix_pointers(symbol__as__string);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_symbol.as__string__funk);
  
  // chunk
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__length);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit8__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit8__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit16__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit16__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit32__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit32__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit64__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bit64__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__cfunk_jump);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__bytecode_jump);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__funk);
  
  // simple_array
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__length);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(simple_array__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__funk);
  
  // traced_array
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__length);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__tracing_on);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__tracing_on__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__trace);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__trace__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__imagination_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__imagination_frame__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__mutate_funks);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__mutate_funks__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__read_funks);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__elt__read_funks__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(traced_array__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__funk);
  
  // larva
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.larva_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__larva_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.bug__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__bug);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.bug__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(larva__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__funk);
  
  // mutable_array_pointer
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.is_type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__is_type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.is_type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__type);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__array);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__array__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__index);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__index__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__set__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__eq);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__eq_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__equals);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__equals_hash_value__loop_free);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__equals_hash_value);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(mutable_array_pointer__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.terminal_print_with_frame__funk);
  
  // gensym
  f2__primcfunk__init__defragment__fix_pointers(gensym);
  
}

void f2__ptypes_object_slots__reinitialize_globalvars() {
  
  f2ptr cause = initial_cause();
  
  // ptypes
  
  f2__primcfunk__init__1(ptypes__read_write_reflective_tracing_enabled__set, value);
  
  // ptype
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__type, this, cfunk); __funk2.globalenv.object_type.ptype.type__funk = never_gc(cfunk);}
  {char* str = "raw"; __funk2.globalenv.object_type.ptype.raw__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__raw, this, cfunk); __funk2.globalenv.object_type.ptype.raw__funk = never_gc(cfunk);}
  {char* str = "cause"; __funk2.globalenv.object_type.ptype.cause__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__cause, this, cfunk); __funk2.globalenv.object_type.ptype.cause__funk = never_gc(cfunk);}
  {char* str = "cause-set"; __funk2.globalenv.object_type.ptype.cause__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptype__cause__set, this, value, cfunk); __funk2.globalenv.object_type.ptype.cause__set__funk = never_gc(cfunk);}
  {char* str = "creation_fiber"; __funk2.globalenv.object_type.ptype.creation_fiber__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__creation_fiber, this, cfunk); __funk2.globalenv.object_type.ptype.creation_fiber__funk = never_gc(cfunk);}
  {char* str = "creation_fiber-set"; __funk2.globalenv.object_type.ptype.creation_fiber__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptype__creation_fiber__set, this, value, cfunk); __funk2.globalenv.object_type.ptype.creation_fiber__set__funk = never_gc(cfunk);}
  
  // integer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_integer.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_integer.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.new__funk = never_gc(cfunk);}
  {char* str = "i"; __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__i, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.i__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_integer.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_integer.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__equals_hash_value__loop_free, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "as-double"; __funk2.globalenv.object_type.ptype.ptype_integer.as__double__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__as__double, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.as__double__funk = never_gc(cfunk);}
  {char* str = "as-pointer"; __funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__as__pointer, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.as__pointer__funk = never_gc(cfunk);}
  {char* str = "multiplied_by"; __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__multiplied_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.multiplied_by__funk = never_gc(cfunk);}
  {char* str = "divided_by"; __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__divided_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.divided_by__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_integer.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_integer.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "square_root"; __funk2.globalenv.object_type.ptype.ptype_integer.square_root__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__square_root, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.square_root__funk = never_gc(cfunk);}
  {char* str = "modulo"; __funk2.globalenv.object_type.ptype.ptype_integer.modulo__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__modulo, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.modulo__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(integer__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_integer.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // double
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_double.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_double.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_double.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.new__funk = never_gc(cfunk);}
  {char* str = "d"; __funk2.globalenv.object_type.ptype.ptype_double.d__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__d, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.d__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_double.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_double.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "as-double"; __funk2.globalenv.object_type.ptype.ptype_double.as__double__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__as__double, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.as__double__funk = never_gc(cfunk);}
  {char* str = "multiplied_by"; __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__multiplied_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.multiplied_by__funk = never_gc(cfunk);}
  {char* str = "divided_by"; __funk2.globalenv.object_type.ptype.ptype_double.divided_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__divided_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.divided_by__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_double.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_double.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "square_root"; __funk2.globalenv.object_type.ptype.ptype_double.square_root__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__square_root, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.square_root__funk = never_gc(cfunk);}
  {char* str = "radian_sine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_sine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_sine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_sine__funk = never_gc(cfunk);}
  {char* str = "radian_arcsine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_arcsine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_arcsine__funk = never_gc(cfunk);}
  {char* str = "radian_cosine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_cosine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_cosine__funk = never_gc(cfunk);}
  {char* str = "radian_arccosine"; __funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_arccosine, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_arccosine__funk = never_gc(cfunk);}
  {char* str = "radian_tangent"; __funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_tangent, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_tangent__funk = never_gc(cfunk);}
  {char* str = "radian_arctangent"; __funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__radian_arctangent, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.radian_arctangent__funk = never_gc(cfunk);}
  {char* str = "power"; __funk2.globalenv.object_type.ptype.ptype_double.power__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__power, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.power__funk = never_gc(cfunk);}
  {char* str = "modulo"; __funk2.globalenv.object_type.ptype.ptype_double.modulo__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__modulo, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.modulo__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(double__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_double.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // float
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_float.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_float.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_float.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.new__funk = never_gc(cfunk);}
  {char* str = "f"; __funk2.globalenv.object_type.ptype.ptype_float.f__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__f, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.f__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_float.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_float.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "as-double"; __funk2.globalenv.object_type.ptype.ptype_float.as__double__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__as__double, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.as__double__funk = never_gc(cfunk);}
  {char* str = "multiplied_by"; __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__multiplied_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.multiplied_by__funk = never_gc(cfunk);}
  {char* str = "divided_by"; __funk2.globalenv.object_type.ptype.ptype_float.divided_by__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__divided_by, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.divided_by__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_float.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_float.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "square_root"; __funk2.globalenv.object_type.ptype.ptype_float.square_root__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__square_root, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.square_root__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(float__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_float.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // pointer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_pointer.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk = never_gc(cfunk);}
  {char* str = "p"; __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__p, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_pointer.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_pointer.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "plus"; __funk2.globalenv.object_type.ptype.ptype_pointer.plus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__plus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.plus__funk = never_gc(cfunk);}
  {char* str = "minus"; __funk2.globalenv.object_type.ptype.ptype_pointer.minus__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__minus, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.minus__funk = never_gc(cfunk);}
  {char* str = "is_greater_than"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__is_greater_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_greater_than__funk = never_gc(cfunk);}
  {char* str = "is_less_than"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__is_less_than, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_less_than__funk = never_gc(cfunk);}
  {char* str = "is_numerically_equal_to"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__is_numerically_equal_to, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.is_numerically_equal_to__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(pointer__terminal_print_with_frame, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_pointer.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // cmutex
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_cmutex.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_cmutex.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.new__funk = never_gc(cfunk);}
  {char* str = "unlock"; __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__unlock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.unlock__funk = never_gc(cfunk);}
  {char* str = "trylock"; __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__trylock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.trylock__funk = never_gc(cfunk);}
  {char* str = "is_locked"; __funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__is_locked, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.is_locked__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__eq_hash_value, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cmutex__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cmutex__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_cmutex.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // creadwritelock
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.new__funk = never_gc(cfunk);}
  {char* str = "unlock"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__unlock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.unlock__funk = never_gc(cfunk);}
  {char* str = "trywritelock"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__trywritelock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.trywritelock__funk = never_gc(cfunk);}
  {char* str = "tryreadlock"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__tryreadlock, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.tryreadlock__funk = never_gc(cfunk);}
  {char* str = "is_writelocked"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_writelocked__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__is_writelocked, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_writelocked__funk = never_gc(cfunk);}
  {char* str = "is_readlocked"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_readlocked__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__is_readlocked, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.is_readlocked__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(creadwritelock__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(creadwritelock__eq_hash_value, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(creadwritelock__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(creadwritelock__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(creadwritelock__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_creadwritelock.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(creadwritelock__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_creadwritelock.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // char
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_char.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_char.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_char.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.new__funk = never_gc(cfunk);}
  {char* str = "ch"; __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__ch, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.ch__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_char.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_char.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "string"; __funk2.globalenv.object_type.ptype.ptype_char.string__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__string, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.string__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(char__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_char.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // string
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_string.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_string.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_string.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.new__funk = never_gc(cfunk);}
  {char* str = "new_copy"; __funk2.globalenv.object_type.ptype.ptype_string.new_copy__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__new_copy, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.new_copy__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_string.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.length__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_string.elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__elt__set, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.elt__set__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_string.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_string.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_string.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // symbol
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_symbol.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_symbol.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_symbol.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.terminal_print_with_frame__funk = never_gc(cfunk);}
  {char* str = "as-string"; __funk2.globalenv.object_type.ptype.ptype_symbol.as__string__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__as__string, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_symbol.as__string__funk = never_gc(cfunk);}
  
  // chunk
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_chunk.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__new, length, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_chunk.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_chunk.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "bit8-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit8__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk = never_gc(cfunk);}
  {char* str = "bit8-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit8__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit16-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit16__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk = never_gc(cfunk);}
  {char* str = "bit16-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit16__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit32-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit32__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk = never_gc(cfunk);}
  {char* str = "bit32-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit32__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit64-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit64__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk = never_gc(cfunk);}
  {char* str = "bit64-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit64__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk = never_gc(cfunk);}
  {char* str = "cfunk_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(chunk__cfunk_jump, this, fiber, env, args, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk = never_gc(cfunk);}
  {char* str = "bytecode_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bytecode_jump, this, fiber, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // simple_array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__equals_hash_value__loop_free, this, node_hash, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(simple_array__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__terminal_print_with_frame, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_simple_array.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // traced_array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__length, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__equals_hash_value__loop_free, this, node_hash, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__tracing_on, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__tracing_on__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk = never_gc(cfunk);}
  {char* str = "elt-trace"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__trace, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk = never_gc(cfunk);}
  {char* str = "elt-trace-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__trace__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__imagination_frame, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__imagination_frame__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__mutate_funks, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__mutate_funks__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__read_funks, this, index, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__read_funks__set, this, index, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_traced_array.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // larva
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_larva.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.new__funk = never_gc(cfunk);}
  {char* str = "larva_type"; __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__larva_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk = never_gc(cfunk);}
  {char* str = "bug"; __funk2.globalenv.object_type.ptype.ptype_larva.bug__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__bug, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.bug__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_larva.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_larva.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(larva__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_larva.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // mutable_array_pointer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.is_type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__is_type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__type, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__new, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.new__funk = never_gc(cfunk);}
  {char* str = "array"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__array, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__funk = never_gc(cfunk);}
  {char* str = "array-set"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(mutable_array_pointer__array__set, this, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.array__set__funk = never_gc(cfunk);}
  {char* str = "index"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__index, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__funk = never_gc(cfunk);}
  {char* str = "index-set"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__set__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(mutable_array_pointer__index__set, this, value, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.index__set__funk = never_gc(cfunk);}
  {char* str = "eq"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(mutable_array_pointer__eq, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__eq_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "equals"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(mutable_array_pointer__equals, this, that, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value-loop_free"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(mutable_array_pointer__equals_hash_value__loop_free, this, node_ptypehash, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__loop_free__funk = never_gc(cfunk);}
  {char* str = "equals_hash_value"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutable_array_pointer__equals_hash_value, this, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.equals_hash_value__funk = never_gc(cfunk);}
  {char* str = "terminal_print_with_frame"; __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.terminal_print_with_frame__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(mutable_array_pointer__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.ptype.ptype_mutable_array_pointer.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // gensym
  f2__primcfunk__init__0(gensym);
}

void f2__ptypes_object_slots__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "ptypes_object_slots", "", &f2__ptypes_object_slots__reinitialize_globalvars, &f2__ptypes_object_slots__defragment__fix_pointers);
  
  f2__ptypes_object_slots__reinitialize_globalvars();
}


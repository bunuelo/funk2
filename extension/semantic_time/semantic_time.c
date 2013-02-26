// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#include "semantic_time.h"



// semantic_time

def_ceframe1(semantic_time, semantic_time, value);

f2ptr raw__semantic_time__new(f2ptr cause, f2ptr value) {
  return f2semantic_time__new(cause, value);
}

f2ptr f2__semantic_time__new(f2ptr cause, f2ptr value) {
  if ((! raw__time__is_type(cause, value)) &&
      (! raw__eq(cause, new__symbol(cause, "before"), value)) &&
      (! raw__eq(cause, new__symbol(cause, "after"),  value)) &&
      (! raw__eq(cause, new__symbol(cause, "now"),    value))) {
    return f2larva__new(cause, 13516, nil);
  }
  return raw__semantic_time__new(cause, value);
}
export_cefunk1(semantic_time__new, value, 0, "Returns a new semantic_time object.  Possible initial values include any time object, or one of the symbols: before, after, or now.");

f2ptr raw__semantic_time(f2ptr cause) {
  return f2__semantic_time__new(cause, f2__time(cause));
}

f2ptr f2__semantic_time(f2ptr cause) {
  return raw__semantic_time(cause);
}
export_cefunk0(semantic_time, 0, "Returns a new semantic_time object with the current absolute time.");


boolean_t raw__semantic_time__is__before(f2ptr cause, f2ptr this) {
  f2ptr value = f2__semantic_time__value(cause, this);
  return raw__eq(cause, new__symbol(cause, "before"), value);
}

f2ptr f2__semantic_time__is__before(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_time, this);
  return raw__semantic_time__is__before(cause, this);
}
export_cefunk1(semantic_time__is__before, this, 0, "Returns whether this semantic_time symbolically represents the time `before.");


boolean_t raw__semantic_time__is__after(f2ptr cause, f2ptr this) {
  f2ptr value = f2__semantic_time__value(cause, this);
  return raw__eq(cause, new__symbol(cause, "after"), value);
}

f2ptr f2__semantic_time__is__after(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_time, this);
  return raw__semantic_time__is__after(cause, this);
}
export_cefunk1(semantic_time__is__after, this, 0, "Returns whether this semantic_time symbolically represents the time `after.");


boolean_t raw__semantic_time__is__now(f2ptr cause, f2ptr this) {
  f2ptr value = f2__semantic_time__value(cause, this);
  return raw__eq(cause, new__symbol(cause, "now"), value);
}

f2ptr f2__semantic_time__is__now(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_time, this);
  return raw__semantic_time__is__now(cause, this);
}
export_cefunk1(semantic_time__is__now, this, 0, "Returns whether this semantic_time symbolically represents the time `now.");


f2ptr raw__semantic_time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__value = f2__semantic_time__value(cause, this);
  f2ptr that__value = f2__semantic_time__value(cause, that);
  {
    boolean_t this__is__now = raw__eq(cause, new__symbol(cause, "now"), this__value);
    boolean_t that__is__now = raw__eq(cause, new__symbol(cause, "now"), that__value);
    f2ptr     now           = nil;
    if (this__is__now || that__is__now) {
      now = assert_value(f2__time(cause));
    }
    if (this__is__now) {
      this__value = now;
    }
    if (that__is__now) {
      that__value = now;
    }
  }
  boolean_t this__is_type__time = raw__time__is_type(cause, this__value);
  boolean_t that__is_type__time = raw__time__is_type(cause, that__value);
  if (this__is_type__time && that__is_type__time) {
    f2ptr this__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this__value);
    s64   this__value__nanoseconds_since_1970__i = f2integer__i(this__value__nanoseconds_since_1970, cause);
    f2ptr that__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that__value);
    s64   that__value__nanoseconds_since_1970__i = f2integer__i(that__value__nanoseconds_since_1970, cause);
    return f2bool__new(this__value__nanoseconds_since_1970__i < that__value__nanoseconds_since_1970__i);
  } else if (this__is_type__time) { // ! that__is_type__time
    if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
      return f2bool__new(boolean__true);
    } else {
      return f2larva__new(cause, 321515, nil);
    }
  } else if (that__is_type__time) { // ! this__is_type__time
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      return f2bool__new(boolean__true);
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      return f2bool__new(boolean__false);
    } else {
      return f2larva__new(cause, 321516, nil);
    }
  } else { // (! this__is_type__time) && (! that__is_type__time)
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
	return f2bool__new(boolean__false);
      } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
	return f2bool__new(boolean__true);
      } else {
	return f2larva__new(cause, 321517, nil);
      }
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
	return f2bool__new(boolean__false);
      } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
	return f2bool__new(boolean__false);
      } else {
	return f2larva__new(cause, 321518, nil);
      }
    } else {
      return f2larva__new(cause, 321519, nil);
    }
  }
}

f2ptr f2__semantic_time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_time, this);
  assert_argument_type(semantic_time, that);
  return raw__semantic_time__is_less_than(cause, this, that);
}
export_cefunk2(semantic_time__is_less_than, this, that, 0, "Returns whether this semantic_time is less than that semantic_time.");


f2ptr raw__semantic_time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__value = f2__semantic_time__value(cause, this);
  f2ptr that__value = f2__semantic_time__value(cause, that);
  {
    boolean_t this__is__now = raw__eq(cause, new__symbol(cause, "now"), this__value);
    boolean_t that__is__now = raw__eq(cause, new__symbol(cause, "now"), that__value);
    f2ptr     now           = nil;
    if (this__is__now || that__is__now) {
      now = assert_value(f2__time(cause));
    }
    if (this__is__now) {
      this__value = now;
    }
    if (that__is__now) {
      that__value = now;
    }
  }
  boolean_t this__is_type__time = raw__time__is_type(cause, this__value);
  boolean_t that__is_type__time = raw__time__is_type(cause, that__value);
  if (this__is_type__time && that__is_type__time) {
    f2ptr this__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this__value);
    s64   this__value__nanoseconds_since_1970__i = f2integer__i(this__value__nanoseconds_since_1970, cause);
    f2ptr that__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that__value);
    s64   that__value__nanoseconds_since_1970__i = f2integer__i(that__value__nanoseconds_since_1970, cause);
    return f2bool__new(this__value__nanoseconds_since_1970__i > that__value__nanoseconds_since_1970__i);
  } else if (this__is_type__time) { // ! that__is_type__time
    if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
      return f2bool__new(boolean__true);
    } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
      return f2bool__new(boolean__false);
    } else {
      return f2larva__new(cause, 321515, nil);
    }
  } else if (that__is_type__time) { // ! this__is_type__time
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      return f2bool__new(boolean__true);
    } else {
      return f2larva__new(cause, 321516, nil);
    }
  } else { // (! this__is_type__time) && (! that__is_type__time)
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
	return f2bool__new(boolean__false);
      } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
	return f2bool__new(boolean__false);
      } else {
	return f2larva__new(cause, 321517, nil);
      }
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
	return f2bool__new(boolean__true);
      } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
	return f2bool__new(boolean__false);
      } else {
	return f2larva__new(cause, 321518, nil);
      }
    } else {
      return f2larva__new(cause, 321519, nil);
    }
  }
}

f2ptr f2__semantic_time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_time, this);
  assert_argument_type(semantic_time, that);
  return raw__semantic_time__is_greater_than(cause, this, that);
}
export_cefunk2(semantic_time__is_greater_than, this, that, 0, "Returns whether this semantic_time is greater than that semantic_time.");


f2ptr raw__semantic_time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__value = f2__semantic_time__value(cause, this);
  f2ptr that__value = f2__semantic_time__value(cause, that);
  {
    boolean_t this__is__now = raw__eq(cause, new__symbol(cause, "now"), this__value);
    boolean_t that__is__now = raw__eq(cause, new__symbol(cause, "now"), that__value);
    f2ptr     now           = nil;
    if (this__is__now && that__is__now) {
      return f2bool__new(boolean__true);
    }
    if (this__is__now || that__is__now) {
      now = assert_value(f2__time(cause));
    }
    if (this__is__now) {
      this__value = now;
    }
    if (that__is__now) {
      that__value = now;
    }
  }
  boolean_t this__is_type__time = raw__time__is_type(cause, this__value);
  boolean_t that__is_type__time = raw__time__is_type(cause, that__value);
  if (this__is_type__time && that__is_type__time) {
    f2ptr this__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, this__value);
    s64   this__value__nanoseconds_since_1970__i = f2integer__i(this__value__nanoseconds_since_1970, cause);
    f2ptr that__value__nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, that__value);
    s64   that__value__nanoseconds_since_1970__i = f2integer__i(that__value__nanoseconds_since_1970, cause);
    return f2bool__new(this__value__nanoseconds_since_1970__i == that__value__nanoseconds_since_1970__i);
  } else if (this__is_type__time) { // ! that__is_type__time
    if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
      return f2bool__new(boolean__false);
    } else {
      return f2larva__new(cause, 321515, nil);
    }
  } else if (that__is_type__time) { // ! this__is_type__time
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      return f2bool__new(boolean__false);
    } else {
      return f2larva__new(cause, 321516, nil);
    }
  } else { // (! this__is_type__time) && (! that__is_type__time)
    if (raw__eq(cause, new__symbol(cause, "before"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
	return f2bool__new(boolean__true);
      } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
	return f2bool__new(boolean__false);
      } else {
	return f2larva__new(cause, 321517, nil);
      }
    } else if (raw__eq(cause, new__symbol(cause, "after"), this__value)) {
      if (raw__eq(cause, new__symbol(cause, "before"), that__value)) {
	return f2bool__new(boolean__false);
      } else if (raw__eq(cause, new__symbol(cause, "after"), that__value)) {
	return f2bool__new(boolean__true);
      } else {
	return f2larva__new(cause, 321518, nil);
      }
    } else {
      return f2larva__new(cause, 321519, nil);
    }
  }
}

f2ptr f2__semantic_time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_time, this);
  assert_argument_type(semantic_time, that);
  return raw__semantic_time__is_numerically_equal_to(cause, this, that);
}
export_cefunk2(semantic_time__is_numerically_equal_to, this, that, 0, "Returns whether this semantic_time is numerically equal to that semantic_time (now == now, before == before, after == after).");


f2ptr f2__semantic_time_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_time_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is-before"),               f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__is__before")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is-after"),                f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__is__after")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is-now"),                  f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__is__now")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_less_than"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__is_less_than")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_greater_than"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__is_greater_than")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_numerically_equal_to"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_time__is_numerically_equal_to")));}
  return this;
}



// semantic_relative_time

def_ceframe1(semantic_time, semantic_relative_time, value);

f2ptr raw__semantic_relative_time__new(f2ptr cause, f2ptr value) {
  return f2semantic_relative_time__new(cause, value);
}

f2ptr f2__semantic_relative_time__new(f2ptr cause, f2ptr value) {
  if ((! raw__relative_time__is_type(cause, value)) &&
      (! raw__eq(cause, new__symbol(cause, "forever_before"),  value)) &&
      (! raw__eq(cause, new__symbol(cause, "forever_after"), value))) {
    return f2larva__new(cause, 13516, nil);
  }
  return raw__semantic_relative_time__new(cause, value);
}
export_cefunk1(semantic_relative_time__new, value, 0, "Returns a new semantic_relative_time object.  Possible initial values include any relative_time object, or one of the symbols: forever_before, or forever_after.");

f2ptr raw__semantic_relative_time(f2ptr cause) {
  return f2__semantic_relative_time__new(cause, f2__time(cause));
}

f2ptr f2__semantic_relative_time(f2ptr cause) {
  return raw__semantic_relative_time(cause);
}
export_cefunk0(semantic_relative_time, 0, "Returns a new semantic_relative_time object with the current absolute time.");


boolean_t raw__semantic_relative_time__is__forever_before(f2ptr cause, f2ptr this) {
  f2ptr value = f2__semantic_relative_time__value(cause, this);
  return raw__eq(cause, new__symbol(cause, "forever_before"), value);
}

f2ptr f2__semantic_relative_time__is__forever_before(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_relative_time, this);
  return raw__semantic_relative_time__is__forever_before(cause, this);
}
export_cefunk1(semantic_relative_time__is__forever_before, this, 0, "Returns whether this semantic_relative_time symbolically represents the time `forever_before.");


boolean_t raw__semantic_relative_time__is__forever_after(f2ptr cause, f2ptr this) {
  f2ptr value = f2__semantic_relative_time__value(cause, this);
  return raw__eq(cause, new__symbol(cause, "forever_after"), value);
}

f2ptr f2__semantic_relative_time__is__forever_after(f2ptr cause, f2ptr this) {
  assert_argument_type(semantic_relative_time, this);
  return raw__semantic_relative_time__is__forever_after(cause, this);
}
export_cefunk1(semantic_relative_time__is__forever_after, this, 0, "Returns whether this semantic_relative_time symbolically represents the time `forever_after.");


f2ptr raw__semantic_relative_time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__value = raw__semantic_relative_time__value(cause, this);
  f2ptr that__value = raw__semantic_relative_time__value(cause, that);
  if (raw__relative_time__is_type(cause, this__value) &&
      raw__relative_time__is_type(cause, that__value)) {
    f2ptr this__relative_time                    = this__value;
    f2ptr that__relative_time                    = that__value;
    s64   this__relative_time__total_nanoseconds = raw__relative_time__total_nanoseconds(cause, this__relative_time);
    s64   that__relative_time__total_nanoseconds = raw__relative_time__total_nanoseconds(cause, that__relative_time);
    return f2bool__new(this__relative_time__total_nanoseconds < that__relative_time__total_nanoseconds);
  }
  if (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
    if        (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
      return f2bool__new(boolean__true);
    } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
      return f2bool__new(boolean__true);
    }
  } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
    if        (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
      return f2bool__new(boolean__false);
    }
  }
  return f2larva__new(cause, 42628, nil);
}

f2ptr f2__semantic_relative_time__is_less_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_relative_time, this);
  assert_argument_type(semantic_relative_time, that);
  return raw__semantic_relative_time__is_less_than(cause, this, that);
}
export_cefunk2(semantic_relative_time__is_less_than, this, that, 0, "Returns whether this semantic_relative_time is less than that semantic_relative_time.");


f2ptr raw__semantic_relative_time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__value = raw__semantic_relative_time__value(cause, this);
  f2ptr that__value = raw__semantic_relative_time__value(cause, that);
  if (raw__relative_time__is_type(cause, this__value) &&
      raw__relative_time__is_type(cause, that__value)) {
    f2ptr this__relative_time                    = this__value;
    f2ptr that__relative_time                    = that__value;
    s64   this__relative_time__total_nanoseconds = raw__relative_time__total_nanoseconds(cause, this__relative_time);
    s64   that__relative_time__total_nanoseconds = raw__relative_time__total_nanoseconds(cause, that__relative_time);
    return f2bool__new(this__relative_time__total_nanoseconds > that__relative_time__total_nanoseconds);
  }
  if (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
    if        (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
      return f2bool__new(boolean__false);
    }
  } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
    if        (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
      return f2bool__new(boolean__true);
    } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
      return f2bool__new(boolean__false);
    }
  }
  return f2larva__new(cause, 42629, nil);
}

f2ptr f2__semantic_relative_time__is_greater_than(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_relative_time, this);
  assert_argument_type(semantic_relative_time, that);
  return raw__semantic_relative_time__is_greater_than(cause, this, that);
}
export_cefunk2(semantic_relative_time__is_greater_than, this, that, 0, "Returns whether this semantic_relative_time is greater than that semantic_relative_time.");


f2ptr raw__semantic_relative_time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr this__value = raw__semantic_relative_time__value(cause, this);
  f2ptr that__value = raw__semantic_relative_time__value(cause, that);
  if (raw__relative_time__is_type(cause, this__value) &&
      raw__relative_time__is_type(cause, that__value)) {
    f2ptr this__relative_time                    = this__value;
    f2ptr that__relative_time                    = that__value;
    s64   this__relative_time__total_nanoseconds = raw__relative_time__total_nanoseconds(cause, this__relative_time);
    s64   that__relative_time__total_nanoseconds = raw__relative_time__total_nanoseconds(cause, that__relative_time);
    return f2bool__new(this__relative_time__total_nanoseconds == that__relative_time__total_nanoseconds);
  }
  if (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
    if        (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
      return f2bool__new(boolean__true);
    } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
      return f2bool__new(boolean__false);
    }
  } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
    if        (raw__eq(cause, this__value, new__symbol(cause, "forever_before"))) {
      return f2bool__new(boolean__false);
    } else if (raw__eq(cause, this__value, new__symbol(cause, "forever_after"))) {
      return f2bool__new(boolean__true);
    }
  }
  return f2larva__new(cause, 42630, nil);
}

f2ptr f2__semantic_relative_time__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(semantic_relative_time, this);
  assert_argument_type(semantic_relative_time, that);
  return raw__semantic_relative_time__is_numerically_equal_to(cause, this, that);
}
export_cefunk2(semantic_relative_time__is_numerically_equal_to, this, that, 0, "Returns whether this semantic_relative_time is numerically equal to that semantic_relative_time (now == now, before == before, after == after).");


f2ptr f2__semantic_relative_time_type__new_aux(f2ptr cause) {
  f2ptr this = f2__semantic_relative_time_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is-forever_before"),       f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_relative_time__is__forever_before")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is-forever_after"),        f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_relative_time__is__forever_after")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_less_than"),            f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_relative_time__is_less_than")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_greater_than"),         f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_relative_time__is_greater_than")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"), new__symbol(cause, "is_numerically_equal_to"), f2__core_extension_funk__new(cause, new__symbol(cause, "semantic_time"), new__symbol(cause, "semantic_relative_time__is_numerically_equal_to")));}
  return this;
}



// **

f2ptr f2__semantic_time__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_time__core_extension__ping, 0, "");

f2ptr f2__semantic_time__core_extension__initialize(f2ptr cause) {
  status("semantic_time initialized.");
  return nil;
}
export_cefunk0(semantic_time__core_extension__initialize, 0, "");

f2ptr f2__semantic_time__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "semantic_time"),          f2__semantic_time_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "semantic_relative_time"), f2__semantic_relative_time_type__new_aux(cause));
  status("semantic_time types defined.");
  return nil;
}
export_cefunk0(semantic_time__core_extension__define_types, 0, "");

f2ptr f2__semantic_time__core_extension__destroy(f2ptr cause) {
  status("semantic_time destroyed.");
  return nil;
}
export_cefunk0(semantic_time__core_extension__destroy, 0, "");



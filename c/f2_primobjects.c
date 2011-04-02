// 
// Copyright (c) 2007-2011 Bo Morgan.
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

defarray_slot(primobject__primobject_label, 0);
defarray_slot(primobject__object_type,      1);
defarray_slot(primobject__dynamic_slots,    2);

#define primobject_error(str) f2exception__new(cause, f2string__new(cause, strlen("primobject:error"), (u8*)"primobject:error"), f2string__new(cause, strlen(str), (u8*)str))


// primobject

f2ptr f2primobject__new(f2ptr cause, f2ptr object_type, f2ptr static_slot_num, f2ptr dynamic_slots) {return f2__primobject__new(cause, object_type, f2integer__i(static_slot_num, cause), dynamic_slots);}

f2ptr __primobject__symbol = -1;

f2ptr f2__primobject__new__trace_depth(f2ptr cause, f2ptr object_type, int static_slot_num, f2ptr dynamic_slots, int trace_depth) {
  release__assert(__primobject__symbol != -1, nil, "f2__primobject__new error: used before primobjects initialized.");
  f2ptr this = raw__array__new(cause, primobject__header_size + static_slot_num);
  f2primobject__primobject_label__set__trace_depth(this, cause, __primobject__symbol, trace_depth);
  f2primobject__object_type__set__trace_depth(     this, cause, object_type,          trace_depth);
  f2primobject__dynamic_slots__set__trace_depth(   this, cause, dynamic_slots,        trace_depth);
  return this;
}

f2ptr f2__primobject__new(f2ptr cause, f2ptr object_type, int static_slot_num, f2ptr dynamic_slots) {
  return f2__primobject__new__trace_depth(cause, object_type, static_slot_num, dynamic_slots, 1);
}

f2ptr f2__primobject__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__primobject__is_type(cause, thing));}
def_pcfunk1(primobject__is_type, thing, return f2__primobject__is_type(this_cause, thing));

f2ptr f2__primobject__object_type(f2ptr cause, f2ptr this) {return f2primobject__object_type(this, cause);}
def_pcfunk1(primobject__object_type, this, return f2__primobject__object_type(this_cause, this));

f2ptr f2__primobject__object_type__set(f2ptr cause, f2ptr this, f2ptr value) {return f2primobject__object_type__set(this, cause, value);}
def_pcfunk2(primobject__object_type__set, this, value, return f2__primobject__object_type__set(this_cause, this, value));

f2ptr f2__primobject__dynamic_slots(f2ptr cause, f2ptr this) {return f2primobject__dynamic_slots(this, cause);}
def_pcfunk1(primobject__dynamic_slots, this, return f2__primobject__dynamic_slots(this_cause, this));

f2ptr f2__primobject__dynamic_slots__set(f2ptr cause, f2ptr this, f2ptr value) {return f2primobject__dynamic_slots__set(this, cause, value);}
def_pcfunk2(primobject__dynamic_slots__set, this, value, return f2__primobject__dynamic_slots__set(this_cause, this, value));

// not thread safe (use appropriately, it would create too much of a slowdown to create a new cmutex for every primitive object)
f2ptr f2__primobject__create_new_dynamic_slots_frame(f2ptr cause, f2ptr this) {
  f2ptr dynamic_slots = f2__frame__new(cause, nil);
  f2primobject__dynamic_slots__set(this, cause, dynamic_slots);
  return dynamic_slots;
}

f2ptr f2__primobject__add_dynamic_slot_type_value(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr value) {
  f2ptr dynamic_slots = f2primobject__dynamic_slots(this, cause);
  if (! dynamic_slots) {
    dynamic_slots = f2__primobject__create_new_dynamic_slots_frame(cause, this);
  }
  return f2__frame__add_type_var_value(cause, dynamic_slots, slot_type, slot_name, value);
}
def_pcfunk4(primobject__add_dynamic_slot_type_value, this, slot_type, slot_name, value, return f2__primobject__add_dynamic_slot_type_value(this_cause, this, slot_type, slot_name, value));

f2ptr f2__primobject__dynamic_slot_type_value(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr no_such_slot_value) {
  f2ptr dynamic_slots = f2primobject__dynamic_slots(this, cause);
  if (! dynamic_slots) {
    return no_such_slot_value;
  }
  return f2__frame__lookup_type_var_value(cause, dynamic_slots, slot_type, slot_name, no_such_slot_value);
}
def_pcfunk4(primobject__dynamic_slot_type_value, this, slot_type, slot_name, no_such_slot_value, return f2__primobject__dynamic_slot_type_value(this_cause, this, slot_type, slot_name, no_such_slot_value));

f2ptr f2__primobject__dynamic_slot_type_value__set(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr value, f2ptr no_such_slot_value) {
  f2ptr dynamic_slots = f2primobject__dynamic_slots(this, cause);
  if (! dynamic_slots) {
    return no_such_slot_value;
  }
  return f2__frame__type_var_value__set(cause, dynamic_slots, slot_type, slot_name, value, no_such_slot_value);
}
def_pcfunk5(primobject__dynamic_slot_type_value__set, this, slot_type, slot_name, value, no_such_slot_value, return f2__primobject__dynamic_slot_type_value__set(this_cause, this, slot_type, slot_name, value, no_such_slot_value));

f2ptr f2primobject__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("array"), (u8*)"array"), nil));
  {char* slot_name = "is_type";                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.is_type__funk);}
  {char* slot_name = "object_type";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.object_type__funk);}
  {char* slot_name = "object_type";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.object_type__set__funk);}
  {char* slot_name = "dynamic_slots";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slots__funk);}
  {char* slot_name = "dynamic_slots";               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slots__set__funk);}
  {char* slot_name = "add_dynamic_slot_type_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.add_dynamic_slot_type_value__funk);}
  {char* slot_name = "dynamic_slot_type_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__funk);}
  {char* slot_name = "dynamic_slot_type_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__set__funk);}
  return this;
}


// place

def_primobject_1_slot(place, thing);

f2ptr f2__place__new(f2ptr cause, f2ptr thing) {
  return f2place__new(cause, thing);
}
def_pcfunk1(place__new, thing, return f2__place__new(this_cause, thing));



// compound_object

def_primobject_3_slot(compound_object, compound_object_type, frame, part_frame);

f2ptr f2__compound_object__new(f2ptr cause, f2ptr compound_object_type) {
  return f2compound_object__new(cause, compound_object_type, f2__frame__new(cause, nil), f2__frame__new(cause, nil));
}
def_pcfunk1(compound_object__new, compound_object_type, return f2__compound_object__new(this_cause, compound_object_type));



// cons

def_primobject_2_slot(cons, car, cdr);

f2ptr f2__cons__new(f2ptr cause, f2ptr x, f2ptr y) {return f2cons__new(cause, x, y);}
def_pcfunk2(cons__new, x, y, return f2__cons__new(this_cause, x, y));

u64 raw__cons__length(f2ptr cause, f2ptr this) {
  assert_argument_type(cons, this);
  return raw__simple_length(cause, this);
}

f2ptr f2__cons__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__cons__length(cause, this));}
def_pcfunk1(cons__length, this, return f2__cons__length(this_cause, this));


f2ptr raw__cons__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
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
  u64 cons__length = 0;
  {
    f2ptr iter = this;
    while (raw__cons__is_type(cause, iter) && cons__length < (max_size__i - size__i)) {
      cons__length ++;
      iter = f2__cons__cdr(cause, iter);
      if ((iter != nil) && (! raw__cons__is_type(cause, iter))) {
	iter = f2list2__new(cause, new__symbol(cause, "."), iter);
      }
    }
  }
  u8  cons_string[128];
  u64 cons_string__length = 0;
  {
    cons_string[0]      = (u8)f2char__ch(__funk2.reader.char__left_paren, cause);
    cons_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__cons__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cons_string__length, cons_string);
  }
  {
    f2ptr iter  = this;
    u64   index = 0;
    while (raw__cons__is_type(cause, iter)) {
      if ((size__i >= (max_size__i - 1)) || (index >= cons__length)) {
	f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	x    = f2__terminal_print_frame__x(cause, terminal_print_frame);
	x__i = f2integer__i(x, cause);
	if (index > 0) {
	  if (use_one_line != nil) {
	    cons_string__length = sprintf((char*)cons_string, " ...");
	  } else {
	    cons_string__length = sprintf((char*)cons_string, "%c...", ((x__i + 4) < max_x__i) ? ' ' : '\n');
	  }
	} else {
	  cons_string__length = sprintf((char*)cons_string, "...");
	}
	raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
	raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cons_string__length, cons_string);
	break;
      } else {
	f2ptr indent_distance = f2__terminal_print_frame__indent_distance(cause, terminal_print_frame);
	{
	  f2ptr subexp            = f2__cons__car(cause, iter);
	  u64   cons__length_left = cons__length - index;
	  u64   subexp_max_size__i = (max_size__i - size__i + (cons__length_left - 1)) / cons__length_left;
	  f2ptr subexp_size;
	  u64   subexp_size__i;
	  f2ptr can_print_on_one_line = nil;
	  {
	    if (index > 0) {
	      {
		x    = f2__terminal_print_frame__x(cause, terminal_print_frame);
		x__i = f2integer__i(x, cause);
		if ((x__i + 1) < max_x__i) {
		  cons_string__length = sprintf((char*)cons_string, " ");
		  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__cons__foreground);
		  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cons_string__length, cons_string);
		}
	      }
	      if (use_one_line == nil) {
		f2ptr can_print_on_one_line = f2__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(cause, terminal_print_frame, subexp);
		if (raw__larva__is_type(cause, can_print_on_one_line)) {
		  return can_print_on_one_line;
		}
		if (can_print_on_one_line == nil) {
		  cons_string__length = sprintf((char*)cons_string, "\n");
		  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cons_string__length, cons_string);
		}
	      }
	    }
	    
	    {
	      if ((use_one_line == nil) && (can_print_on_one_line != nil)) {
		f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	      }
	      f2__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, 0));
	      f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, f2integer__new(cause, subexp_max_size__i));
	      f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, subexp, terminal_print_frame);
	      if (raw__larva__is_type(cause, result)) {
		return result;
	      }
	      if ((use_one_line == nil) && (can_print_on_one_line != nil)) {
		f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	      }
	    }
	    
	    subexp_size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
	    subexp_size__i = f2integer__i(subexp_size, cause);
	  }
	  size__i += subexp_size__i;
	}
	f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
      }
      index ++;
      iter = f2__cons__cdr(cause, iter);
      if ((iter != nil) && (! raw__cons__is_type(cause, iter))) {
	iter = f2list2__new(cause, new__symbol(cause, "."), iter);
      }
    }
    f2__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, size__i));
    f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
  }
  {
    cons_string[0]      = (u8)f2char__ch(__funk2.reader.char__right_paren, cause);
    cons_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, cons_string__length, cons_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__cons__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cons,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cons__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cons__terminal_print_with_frame, this, terminal_print_frame, return f2__cons__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2cons__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cons__primobject_type__new(cause);
  {char* slot_name = "length";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.length__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.terminal_print_with_frame__funk);}
  return this;
}


// doublelink

def_primobject_3_slot(doublelink, prev, next, value);

f2ptr f2__doublelink__new(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value) {return f2doublelink__new(cause, prev, next, value);}
def_pcfunk3(doublelink__new, prev, next, value, return f2__doublelink__new(this_cause, prev, next, value));


f2ptr raw__doublelink__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
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
  u64 doublelink__length = 0;
  {
    f2ptr iter = this;
    while (raw__doublelink__is_type(cause, iter) && (doublelink__length < (max_size__i - size__i))) {
      doublelink__length ++;
      iter = f2__doublelink__next(cause, iter);
      if ((iter != nil) && (! raw__doublelink__is_type(cause, iter))) {
	iter = f2list2__new(cause, new__symbol(cause, "."), iter);
      }
    }
  }
  u8  doublelink_string[128];
  u64 doublelink_string__length = 0;
  {
    doublelink_string[0]      = (u8)f2char__ch(__funk2.reader.char__doublelink_left_paren, cause);
    doublelink_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__doublelink__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, doublelink_string__length, doublelink_string);
  }
  {
    f2ptr iter  = this;
    u64   index = 0;
    while (raw__doublelink__is_type(cause, iter)) {
      if ((size__i >= (max_size__i - 1)) || (index >= doublelink__length)) {
	f2__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	x    = f2__terminal_print_frame__x(cause, terminal_print_frame);
	x__i = f2integer__i(x, cause);
	if (index > 0) {
	  if (use_one_line != nil) {
	    doublelink_string__length = sprintf((char*)doublelink_string, " ...");
	  } else {
	    doublelink_string__length = sprintf((char*)doublelink_string, "%c...", ((x__i + 4) < max_x__i) ? ' ' : '\n');
	  }
	} else {
	  doublelink_string__length = sprintf((char*)doublelink_string, "...");
	}
	raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__symbol__foreground);
	raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, doublelink_string__length, doublelink_string);
	break;
      } else {
	f2ptr indent_distance = f2__terminal_print_frame__indent_distance(cause, terminal_print_frame);
	{
	  f2ptr subexp            = f2__doublelink__value(cause, iter);
	  u64   doublelink__length_left = doublelink__length - index;
	  u64   subexp_max_size__i = (max_size__i - size__i + (doublelink__length_left - 1)) / doublelink__length_left;
	  f2ptr subexp_size;
	  u64   subexp_size__i;
	  {
	    f2ptr can_print_on_one_line = nil;
	    if (index > 0) {
	      {
		x    = f2__terminal_print_frame__x(cause, terminal_print_frame);
		x__i = f2integer__i(x, cause);
		if ((x__i + 1) < max_x__i) {
		  doublelink_string__length = sprintf((char*)doublelink_string, " ");
		  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__doublelink__foreground);
		  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, doublelink_string__length, doublelink_string);
		}
	      }
	      if (use_one_line == nil) {
		can_print_on_one_line = f2__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(cause, terminal_print_frame, subexp);
		if (raw__larva__is_type(cause, can_print_on_one_line)) {
		  return can_print_on_one_line;
		}
		if (can_print_on_one_line == nil) {
		  doublelink_string__length = sprintf((char*)doublelink_string, "\n");
		  raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, doublelink_string__length, doublelink_string);
		}
	      }
	    }
	    
	    {
	      if ((use_one_line == nil) && (can_print_on_one_line != nil)) {
		f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	      }
	      f2__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, 0));
	      f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, f2integer__new(cause, subexp_max_size__i));
	      f2ptr result = raw__exp__terminal_print_with_frame__thread_unsafe(cause, subexp, terminal_print_frame);
	      if (raw__larva__is_type(cause, result)) {
		return result;
	      }
	      if ((use_one_line == nil) && (can_print_on_one_line != nil)) {
		f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	      }
	    }
	    
	    subexp_size    = f2__terminal_print_frame__size(cause, terminal_print_frame);
	    subexp_size__i = f2integer__i(subexp_size, cause);
	  }
	  size__i += subexp_size__i;
	}
	f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
      }
      index ++;
      iter = f2__doublelink__next(cause, iter);
      if ((iter != nil) && (! raw__doublelink__is_type(cause, iter))) {
	iter = f2list2__new(cause, new__symbol(cause, "."), iter);
      }
    }
    f2__terminal_print_frame__size__set(    cause, terminal_print_frame, f2integer__new(cause, size__i));
    f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
  }
  {
    doublelink_string[0]      = (u8)f2char__ch(__funk2.reader.char__doublelink_right_paren, cause);
    doublelink_string__length = 1;
    raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__traced_array__foreground);
    raw__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, doublelink_string__length, doublelink_string);
  }
  raw__terminal_print_frame__write_color__thread_unsafe( cause, terminal_print_frame, print__ansi__default__foreground);
  return nil;
}

f2ptr f2__doublelink__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(doublelink,           this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__doublelink__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(doublelink__terminal_print_with_frame, this, terminal_print_frame, return f2__doublelink__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2doublelink__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2doublelink__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_doublelink.terminal_print_with_frame__funk);}
  return this;
}


// imagination_link

def_primobject_5_slot(imagination_link, next, name, value, trace, imagination_frame);

f2ptr f2__imagination_link__new(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame) {return f2imagination_link__new(cause, next, name, value, trace, imagination_frame);}
def_pcfunk5(imagination_link__new, next, name, value, trace, imagination_frame, return f2__imagination_link__new(this_cause, next, name, value, trace, imagination_frame));

f2ptr raw__imagination_frame__new_with_added_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth) {
  f2ptr trace             = nil;
  f2ptr imagination_frame = nil;
  return f2imagination_link__new__trace_depth(cause, this, name, value, trace, imagination_frame, trace_depth - 1);
}

void raw__imagination_link__add_new_imagination_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth) {
  f2ptr imagination_frame     = f2imagination_link__imagination_frame(this, cause);
  f2ptr new_imagination_frame = raw__imagination_frame__new_with_added_slot__trace_depth(cause, imagination_frame, name, value, trace_depth - 1);
  f2imagination_link__imagination_frame__set__trace_depth(this, cause, new_imagination_frame, trace_depth - 1);
}

f2ptr f2__imagination_frame__get_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, int trace_depth) {
  f2ptr slot_iter = this;
  while (slot_iter) {
    f2ptr slot_name = f2imagination_link__name__trace_depth(slot_iter, cause, trace_depth);
    if (raw__symbol__eq(cause, name, slot_name)) {
      return slot_iter;
    }
    slot_iter = f2imagination_link__next__trace_depth(slot_iter, cause, trace_depth);
  }
  return nil;
}

f2ptr f2__imagination_frame__get_slot(f2ptr cause, f2ptr this, f2ptr name) {
  return f2__imagination_frame__get_slot__trace_depth(cause, this, name, 1);
}

f2ptr f2__imagination_link__get_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, int trace_depth) {
  f2ptr imagination_frame = f2imagination_link__imagination_frame__trace_depth(this, cause, trace_depth);
  return f2__imagination_frame__get_slot__trace_depth(cause, imagination_frame, name, trace_depth);
}

f2ptr f2__imagination_link__get_slot(f2ptr cause, f2ptr this, f2ptr name) {
  return f2__imagination_link__get_slot__trace_depth(cause, this, name, 1);
}

f2ptr f2__imagination_link__get_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value, u64 trace_depth) {
  f2ptr imagination_link_iter = this;
  f2ptr name_iter             = name_stack;
  while (name_iter) {
    f2ptr name = f2cons__car__trace_depth(name_iter, cause, trace_depth);
    f2ptr slot = f2__imagination_link__get_slot__trace_depth(cause, imagination_link_iter, name, trace_depth);
    if (! slot) {
      return doesnt_exist_value;
    }
    imagination_link_iter = slot;
    name_iter = f2cons__cdr(name_iter, cause);
  }
  return f2imagination_link__value__trace_depth(imagination_link_iter, cause, trace_depth);
}

f2ptr f2__imagination_link__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value) {
  return f2__imagination_link__get_value_from_name_stack__trace_depth(cause, this, name_stack, doesnt_exist_value, 1);
}

f2ptr f2__imagination_frame__get_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value, int trace_depth) {
  if (name_stack) {
    f2ptr name = f2cons__car(name_stack, cause);
    f2ptr slot = f2__imagination_frame__get_slot__trace_depth(cause, this, name, trace_depth);
    if (! slot) {
      return doesnt_exist_value;
    }
    return f2__imagination_link__get_value_from_name_stack__trace_depth(cause, slot, f2cons__cdr(name_stack, cause), doesnt_exist_value, trace_depth);
  }
  return doesnt_exist_value;
}

f2ptr f2__imagination_frame__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value) {
  return f2__imagination_frame__get_value_from_name_stack__trace_depth(cause, this, name_stack, doesnt_exist_value, 1);
}

void f2__imagination_link__set_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr value, int trace_depth) {
  f2ptr imagination_link_iter = this;
  f2ptr name_iter             = name_stack;
  while (name_iter) {
    f2ptr name = f2cons__car(name_iter, cause);
    f2ptr next = f2cons__cdr(name_iter, cause);
    f2ptr slot = f2__imagination_link__get_slot(cause, imagination_link_iter, name);
    if (! slot) {
      raw__imagination_link__add_new_imagination_slot__trace_depth(cause, imagination_link_iter, name, next ? f2imagination_link__value(imagination_link_iter, cause) : value, trace_depth - 1);
      slot = f2__imagination_link__get_slot(cause, imagination_link_iter, name);
      release__assert(slot != nil, cause, "f2__imagination_link__set_value_from_name_stack: !(slot != nil)");
    }
    imagination_link_iter = slot;
    name_iter = next;
  }
}


// cfunk

def_primobject_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation);

f2ptr f2__cfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2cfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(cfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__cfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));

f2ptr f2__cfunk__apply(f2ptr cause, f2ptr cfunk, f2ptr fiber, f2ptr args) {
  assert_argument_type(cfunk,    cfunk);
  assert_argument_type(fiber,    fiber);
  assert_argument_type(conslist, args);
  if (f2cfunk__cfunkptr(cfunk, cause) == nil) {
    printf("\ncfunk-apply error: cfunkptr object was null for cfunk.");
    return f2larva__new(cause, 123436, nil);
    //return f2__argument_type_check_failure__exception__new(cause, cfunk);
  }
  ptr cfunk_ptr = f2pointer__p(f2cfunk__cfunkptr(cfunk, cause), cause);
  if (! cfunk_ptr) {
    printf("\ncfunk-apply error: cfunk_ptr was null for cfunk.");
    return f2larva__new(cause, 246231, nil);
    //return f2__argument_type_check_failure__exception__new(cause, cfunk);
  }
  return ((cfunkptr_t)(relative_ptr__to__raw_executable(cfunk_ptr)))(cause, fiber, f2cfunk__env(cfunk, cause), args);
}
def_pcfunk3(cfunk__apply, x, y, z, return f2__cfunk__apply(this_cause, x, y, z));


f2ptr raw__cfunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "cfunk"),
						new__symbol(cause, "name"),          f2__cfunk__name(         cause, this),
						new__symbol(cause, "args"),          f2__cfunk__args(         cause, this),
						new__symbol(cause, "is_funktional"), f2__cfunk__is_funktional(cause, this),
						new__symbol(cause, "documentation"), f2__cfunk__documentation(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__cfunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(cfunk,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__cfunk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(cfunk__terminal_print_with_frame, this, terminal_print_frame, return f2__cfunk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2cfunk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cfunk__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cfunk.terminal_print_with_frame__funk);}
  return this;
}


// metrocfunk

def_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);

f2ptr f2__metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2metrocfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(metrocfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__metrocfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));

f2ptr f2__metrocfunk__apply(f2ptr cause, f2ptr metrocfunk, f2ptr fiber, f2ptr args) {
  release__assert(raw__metrocfunk__is_type(cause, metrocfunk), nil, "metrocfunk failed type assertion.");
  release__assert(raw__fiber__is_type(cause, fiber),           nil, "fiber failed type assertion.");
  release__assert(raw__cons__is_type(cause, args),             nil, "args failed type assertion.");
  return ((cfunkptr_t)relative_ptr__to__raw_executable(f2pointer__p(f2metrocfunk__cfunkptr(metrocfunk, cause), cause)))(cause, fiber, f2metrocfunk__env(metrocfunk, cause), args);
}
def_pcfunk3(metrocfunk__apply, x, y, z, return f2__metrocfunk__apply(this_cause, x, y, z));


f2ptr raw__metrocfunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "metrocfunk"),
						new__symbol(cause, "name"),          f2__metrocfunk__name(         cause, this),
						new__symbol(cause, "args"),          f2__metrocfunk__args(         cause, this),
						new__symbol(cause, "is_funktional"), f2__metrocfunk__is_funktional(cause, this),
						new__symbol(cause, "documentation"), f2__metrocfunk__documentation(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__metrocfunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(metrocfunk,           this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__metrocfunk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(metrocfunk__terminal_print_with_frame, this, terminal_print_frame, return f2__metrocfunk__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2metrocfunk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2metrocfunk__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.terminal_print_with_frame__funk);}
  return this;
}


// funk

def_primobject_10_slot(funk,
		       name,
		       body_bytecodes,
		       args,
		       demetropolized_body,
		       body,
		       env,
		       machine_code,
		       is_funktional,
		       has_no_side_effects,
		       documentation);

f2ptr f2__funk__new(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional, f2ptr documentation) {
  if (is_funktional != nil) {
    if (raw__symbol__is_type(cause, name)) {
      u64 name__length = raw__symbol__length(cause, name);
      u8* name__str    = (u8*)from_ptr(f2__malloc(name__length + 1));
      raw__symbol__str_copy(cause, name, name__str);
      name__str[name__length] = 0;
      printf("\nf2__funk__new note is_funktional: %s", name__str);
      f2__free(to_ptr(name__str));
    } else {
      printf("\nf2__funk__new note is_funktional: <unnamed>");
    }
  }
  f2ptr has_no_side_effects = nil;
  f2ptr funk   = f2funk__new(cause, name, bytecodes, args, demetropolized_body, body, environment, nil, is_funktional, has_no_side_effects, documentation);
  f2ptr result = f2__compile__funk(cause, fiber, funk);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  //f2funk__machine_code__set(funk, this_cause, f2chunk__new_compiled_from_funk(this_cause, funk));
  return funk;
}
def_pcfunk8(funk__new, environment, name, args, demetropolized_body, body, bytecodes, is_funktional, documentation, return f2__funk__new(this_cause, simple_fiber, environment, name, args, demetropolized_body, body, bytecodes, is_funktional, documentation));


f2ptr raw__funk__new_copy(f2ptr cause, f2ptr this) {
  f2ptr name                = f2funk__name(               this, cause);
  f2ptr body_bytecodes      = f2funk__body_bytecodes(     this, cause);
  f2ptr args                = f2funk__args(               this, cause);
  f2ptr demetropolized_body = f2funk__demetropolized_body(this, cause);
  f2ptr body                = f2funk__body(               this, cause);
  f2ptr env                 = f2funk__env(                this, cause);
  f2ptr machine_code        = f2funk__machine_code(       this, cause);
  f2ptr is_funktional       = f2funk__is_funktional(      this, cause);
  f2ptr documentation       = f2funk__documentation(      this, cause);
  f2ptr new_funk = f2funk__new(cause,
			       name,
			       body_bytecodes,
			       args,
			       demetropolized_body,
			       body,
			       env,
			       machine_code,
			       is_funktional,
			       documentation);
  return new_funk;
}

f2ptr f2__funk__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(funk, this);
  return raw__funk__new_copy(cause, this);
}
def_pcfunk1(funk__new_copy, this, return f2__funk__new_copy(this_cause, this));

// defined in f2_optimize.c
def_pcfunk2(funk__optimize, this, maximum_loop_count, return f2__funk__optimize(this_cause, this, maximum_loop_count));

f2ptr raw__funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "funk"),
						new__symbol(cause, "name"),          f2__funk__name(         cause, this),
						new__symbol(cause, "args"),          f2__funk__args(         cause, this),
						new__symbol(cause, "is_funktional"), f2__funk__is_funktional(cause, this),
						new__symbol(cause, "documentation"), f2__funk__documentation(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__funk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(funk,                 this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__funk__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(funk__terminal_print_with_frame, this, terminal_print_frame, return f2__funk__terminal_print_with_frame(this_cause, this, terminal_print_frame));

f2ptr f2funk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2funk__primobject_type__new(cause);
  {char* slot_name = "new_copy";                  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_funk.new_copy__funk);}
  {char* slot_name = "optimize";                  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_funk.optimize__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_funk.terminal_print_with_frame__funk);}
  return this;
}


// metro

def_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);

f2ptr f2__metro__new(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr name, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr bytecodes, f2ptr is_funktional, f2ptr documentation) {
  f2ptr metro  = f2metro__new(cause, name, bytecodes, args, demetropolized_body, body, environment, nil, is_funktional, documentation);
  f2ptr result = f2__compile__metro(cause, fiber, metro);
  if (raw__larva__is_type(cause, result)) {
    return result;
  }
  
  // metro machine code compiling bug...  temporarily disabled.
  //f2metro__machine_code__set(metro, this_cause, f2chunk__new_compiled_from_metro(this_cause, metro));
  
  return metro;
}
def_pcfunk8(metro__new, environment, name, args, demetropolized_body, body, bytecodes, is_funktional, documentation, return f2__metro__new(this_cause, simple_fiber, environment, name, args, demetropolized_body, body, bytecodes, is_funktional, documentation));


f2ptr raw__metro__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "metro"),
						new__symbol(cause, "name"),          f2__metro__name(         cause, this),
						new__symbol(cause, "args"),          f2__metro__args(         cause, this),
						new__symbol(cause, "is_funktional"), f2__metro__is_funktional(cause, this),
						new__symbol(cause, "documentation"), f2__metro__documentation(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__metro__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(metro,                this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__metro__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(metro__terminal_print_with_frame, this, terminal_print_frame, return f2__metro__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2metro__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2metro__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_metro.terminal_print_with_frame__funk);}
  return this;
}


// exception

def_primobject_2_slot(exception, tag, value);

f2ptr f2__exception__new(f2ptr cause, f2ptr tag, f2ptr value) {return f2exception__new(cause, tag, value);}
def_pcfunk2(exception__new, tag, value, return f2__exception__new(this_cause, tag, value));


f2ptr raw__exception__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list6__new(cause,
					       new__symbol(cause, "print_object_type"), new__symbol(cause, "exception"),
					       new__symbol(cause, "tag"),   f2__exception__tag(  cause, this),
					       new__symbol(cause, "value"), f2__exception__value(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__exception__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(exception,            this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__exception__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(exception__terminal_print_with_frame, this, terminal_print_frame, return f2__exception__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2exception__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2exception__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_exception.terminal_print_with_frame__funk);}
  return this;
}


// bytecode

def_primobject_4_slot(bytecode, command, arg0, arg1, arg2);

f2ptr f2__bytecode__new(f2ptr cause, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2) {return f2bytecode__new(cause, command, arg0, arg1, arg2);}
def_pcfunk4(bytecode__new, command, arg0, arg1, arg2, return f2__bytecode__new(this_cause, command, arg0, arg1, arg2));


f2ptr raw__bytecode__as__graphviz_label(f2ptr cause, f2ptr this) {
  return f2__exp__as__string(cause, f2__bytecode__command(cause, this));
}

f2ptr f2__bytecode__as__graphviz_label(f2ptr cause, f2ptr this) {
  assert_argument_type(bytecode, this);
  return raw__bytecode__as__graphviz_label(cause, this);
}
def_pcfunk1(bytecode__as__graphviz_label, this, return f2__bytecode__as__graphviz_label(this_cause, this));


f2ptr raw__bytecode__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list10__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "bytecode"),
						new__symbol(cause, "command"), f2__bytecode__command(cause, this),
						new__symbol(cause, "arg0"),    f2__bytecode__arg0(   cause, this),
						new__symbol(cause, "arg1"),    f2__bytecode__arg1(   cause, this),
						new__symbol(cause, "arg2"),    f2__bytecode__arg2(   cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__bytecode__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(bytecode,             this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__bytecode__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(bytecode__terminal_print_with_frame, this, terminal_print_frame, return f2__bytecode__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2bytecode__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2bytecode__primobject_type__new(cause);
  {char* slot_name = "as-graphviz_label";         f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bytecode.as__graphviz_label__funk);}
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_bytecode.terminal_print_with_frame__funk);}
  return this;
}


// transframe

def_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);

f2ptr f2__transframe__new(f2ptr cause, f2ptr nanoseconds_since_1970, f2ptr symbol_old_news) {return f2transframe__new(cause, nanoseconds_since_1970, symbol_old_news);}
def_pcfunk2(transframe__new, nanoseconds_since_1970, symbol_old_news, return f2__transframe__new(this_cause, nanoseconds_since_1970, symbol_old_news));


// size_2d

def_primobject_2_slot(size_2d, x, y);

f2ptr f2__size_2d__new(f2ptr cause, f2ptr x, f2ptr y) {return f2size_2d__new(cause, x, y);}
def_pcfunk2(size_2d__new, x, y, return f2__size_2d__new(this_cause, x, y));


// event

def_primobject_4_slot(event, node_id, event_id, event_type, data);

f2ptr f2__event__new(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data) {return f2event__new(cause, node_id, event_id, type, data);}
def_pcfunk4(event__new, node_id, event_id, type, data, return f2__event__new(this_cause, node_id, event_id, type, data));


// larva_event




// bytecode_event

def_primobject_2_slot(bytecode_event, bytecode, context);

f2ptr f2__bytecode_event__new(f2ptr cause, f2ptr bytecode, f2ptr context) {return f2bytecode_event__new(cause, bytecode, context);}
def_pcfunk2(bytecode_event__new, bytecode, context, return f2__bytecode_event__new(this_cause, bytecode, context));


// **

void f2__primobjects__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __compound_object__symbol  = new__symbol(cause, "compound_object");
  __primobject__symbol       = new__symbol(cause, "primobject");
  __place__symbol            = new__symbol(cause, "place");
  __cons__symbol             = new__symbol(cause, "cons");
  __doublelink__symbol       = new__symbol(cause, "doublelink");
  __imagination_link__symbol = new__symbol(cause, "imagination_link");
  __cfunk__symbol            = new__symbol(cause, "cfunk");
  __metrocfunk__symbol       = new__symbol(cause, "metrocfunk");
  __funk__symbol             = new__symbol(cause, "funk");
  __metro__symbol            = new__symbol(cause, "metro");
  __exception__symbol        = new__symbol(cause, "exception");
  __bytecode__symbol         = new__symbol(cause, "bytecode");
  __transframe__symbol       = new__symbol(cause, "transframe");
  __bug__symbol              = new__symbol(cause, "bug");
  __size_2d__symbol          = new__symbol(cause, "size_2d");
  __event__symbol            = new__symbol(cause, "event");
  __bytecode_event__symbol   = new__symbol(cause, "bytecode_event");
}


void f2__primobjects__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobjects", "", &f2__primobjects__reinitialize_globalvars);
  
  f2__primobjects__reinitialize_globalvars();
  f2ptr cause = initial_cause();
  
  // primobject
  
  {char* symbol_str = "is_type"; __funk2.globalenv.object_type.primobject.is_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__is_type, thing, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.is_type__funk = never_gc(cfunk);}
  {char* symbol_str = "object_type"; __funk2.globalenv.object_type.primobject.object_type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__object_type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.object_type__funk = never_gc(cfunk);}
  {char* symbol_str = "object_type-set"; __funk2.globalenv.object_type.primobject.object_type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(primobject__object_type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.object_type__set__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slots"; __funk2.globalenv.object_type.primobject.dynamic_slots__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__dynamic_slots, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slots__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slots-set"; __funk2.globalenv.object_type.primobject.dynamic_slots__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(primobject__dynamic_slots__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slots__set__funk = never_gc(cfunk);}
  {char* symbol_str = "add_dynamic_slot_type_value"; __funk2.globalenv.object_type.primobject.add_dynamic_slot_type_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(primobject__add_dynamic_slot_type_value, this, slot_type, slot_name, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.add_dynamic_slot_type_value__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slot_type_value"; __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(primobject__dynamic_slot_type_value, this, slot_type, slot_name, no_such_slot_value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__funk = never_gc(cfunk);}
  {char* symbol_str = "dynamic_slot_type_value-set"; __funk2.globalenv.object_type.primobject.dynamic_slots__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(primobject__dynamic_slot_type_value__set, this, slot_type, slot_name, value, no_such_slot_value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.dynamic_slot_type_value__set__funk = never_gc(cfunk);}
  
  // compound_object 
  
  initialize_primobject_3_slot(compound_object, compound_object_type, frame, part_frame);
  
  // place
  
  initialize_primobject_1_slot(place, thing);

  // cons 
  
  initialize_primobject_2_slot(cons, car, cdr);
  
  {char* symbol_str = "length"; __funk2.globalenv.object_type.primobject.primobject_type_cons.length__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(cons__length, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.length__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cons.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cons__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cons.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // doublelink
  
  initialize_primobject_3_slot(doublelink, prev, next, value);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_doublelink.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(doublelink__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_doublelink.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // imagination_link
  
  initialize_primobject_5_slot(imagination_link, next, name, value, trace, imagination_frame);
  
  // cfunk
  
  initialize_primobject_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation);
  
  f2__primcfunk__init__3(cfunk__apply, x, y, z, "");
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_cfunk.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(cfunk__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_cfunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // metrocfunk
  
  initialize_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);
  
  f2__primcfunk__init__3(metrocfunk__apply, x, y, z, "");
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metrocfunk__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metrocfunk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // funk
  
  initialize_primobject_10_slot(funk,
				name,
				body_bytecodes,
				args,
				demetropolized_body,
				body,
				env,
				machine_code,
				is_funktional,
				has_no_side_effects,
				documentation);
  
  f2__primcfunk__init__8(funk__new, environment, name, args, demetropolized_body, body, bytecodes, is_funktional, documentation, "");
  
  {char* symbol_str = "new_copy"; __funk2.globalenv.object_type.primobject.primobject_type_funk.new_copy__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__new_copy, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.new_copy__funk = never_gc(cfunk);}
  {char* symbol_str = "optimize"; __funk2.globalenv.object_type.primobject.primobject_type_funk.optimize__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(funk__optimize, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.optimize__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_funk.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(funk__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_funk.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // metro
  
  initialize_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);
  
  f2__primcfunk__init__8(metro__new, environment, name, args, demetropolized_body, body, bytecodes, is_funktional, documentation, "");
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_metro.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(metro__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_metro.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // exception
  
  initialize_primobject_2_slot(exception, tag, value);
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_exception.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(exception__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_exception.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // bytecode
  
  initialize_primobject_4_slot(bytecode, command, arg0, arg1, arg2);
  
  {char* symbol_str = "as-graphviz_label"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.as__graphviz_label__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode__as__graphviz_label, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.as__graphviz_label__funk = never_gc(cfunk);}
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_bytecode.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(bytecode__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.primobject_type_bytecode.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // transframe
  
  initialize_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);
  
  // size_2d
  
  initialize_primobject_2_slot(size_2d, x, y);
  
  // event
  
  initialize_primobject_4_slot(event, node_id, event_id, event_type, data);
  
  // bytecode_event
  
  initialize_primobject_2_slot(bytecode_event, bytecode, context);
  
}


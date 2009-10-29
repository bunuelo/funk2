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

defarray_slot(primobject__primobject_label, 0);
defarray_slot(primobject__type,             1);
defarray_slot(primobject__dynamic_slots,    2);

#define primobject_error(str) f2exception__new(cause, f2string__new(cause, strlen("primobject:error"), (u8*)"primobject:error"), f2string__new(cause, strlen(str), (u8*)str))


// primobject

f2ptr f2primobject__new(f2ptr cause, f2ptr type, f2ptr static_slot_num, f2ptr dynamic_slots) {return f2__primobject__new(cause, type, f2integer__i(static_slot_num, cause), dynamic_slots);}

f2ptr __primobject__symbol = -1;

f2ptr f2__primobject__new__trace_depth(f2ptr cause, f2ptr type, int static_slot_num, f2ptr dynamic_slots, int trace_depth) {
  release__assert(__primobject__symbol != -1, nil, "f2__primobject__new error: used before primobjects initialized.");
  f2ptr this = raw__array__new(cause, primobject__header_size + static_slot_num);
  f2primobject__primobject_label__set__trace_depth(this, cause, __primobject__symbol, trace_depth);
  f2primobject__type__set__trace_depth(            this, cause, type,                 trace_depth);
  f2primobject__dynamic_slots__set__trace_depth(   this, cause, dynamic_slots,        trace_depth);
  return this;
}

f2ptr f2__primobject__new(f2ptr cause, f2ptr type, int static_slot_num, f2ptr dynamic_slots) {
  return f2__primobject__new__trace_depth(cause, type, static_slot_num, dynamic_slots, 1);
}

f2ptr f2__primobject__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__primobject__is_type(cause, thing));}
def_pcfunk1(primobject__is_type, thing, return f2__primobject__is_type(this_cause, thing));

f2ptr f2__primobject__type(f2ptr cause, f2ptr this) {return f2primobject__type(this, cause);}
def_pcfunk1(primobject__type, this, return f2__primobject__type(this_cause, this));

f2ptr f2__primobject__type__set(f2ptr cause, f2ptr this, f2ptr value) {return f2primobject__type__set(this, cause, value);}
def_pcfunk2(primobject__type__set, this, value, return f2__primobject__type__set(this_cause, this, value));

f2ptr f2__primobject__dynamic_slots(f2ptr cause, f2ptr this) {return f2primobject__dynamic_slots(this, cause);}
def_pcfunk1(primobject__dynamic_slots, this, return f2__primobject__dynamic_slots(this_cause, this));

f2ptr f2__primobject__dynamic_slots__set(f2ptr cause, f2ptr this, f2ptr value) {return f2primobject__dynamic_slots__set(this, cause, value);}
def_pcfunk2(primobject__dynamic_slots__set, this, value, return f2__primobject__dynamic_slots__set(this_cause, this, value));

// not thread safe (use appropriately, it would create too much of a slowdown to create a new mutex for every primitive object)
f2ptr f2__primobject__create_new_dynamic_slots_frame(f2ptr cause, f2ptr this) {
  f2ptr dynamic_slots = f2__frame__new(cause);
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
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.type__funk);}
  {char* slot_name = "type";                        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.primobject.type__set__funk);}
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
  return f2compound_object__new(cause, compound_object_type, f2__frame__new(cause), f2__frame__new(cause));
}
def_pcfunk1(compound_object__new, compound_object_type, return f2__compound_object__new(this_cause, compound_object_type));



// cons

def_primobject_2_slot(cons, car, cdr);

f2ptr f2__cons__new(f2ptr cause, f2ptr x, f2ptr y) {return f2cons__new(cause, x, y);}
def_pcfunk2(cons__new, x, y, return f2__cons__new(this_cause, x, y));

u64 raw__cons__length(f2ptr cause, f2ptr this) {
  if (! raw__cons__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  return raw__simple_length(cause, this);
}

f2ptr f2__cons__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__cons__length(cause, this));}
def_pcfunk1(cons__length, this, return f2__cons__length(this_cause, this));

f2ptr f2cons__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2cons__primobject_type__new(cause);
  {char* slot_name = "length"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_cons.length__funk);}
  return this;
}


// doublelink

def_primobject_3_slot(doublelink, prev, next, value);

f2ptr f2__doublelink__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {return f2doublelink__new(cause, x, y, z);}
def_pcfunk3(doublelink__new, x, y, z, return f2__doublelink__new(this_cause, x, y, z));


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



// metrocfunk

def_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);

f2ptr f2__metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional, f2ptr documentation) {return f2metrocfunk__new(cause, name, args, cfunkptr, env, is_funktional, documentation);}
def_pcfunk6(metrocfunk__new, name, args, cfunkptr, env, is_funktional, documentation, return f2__metrocfunk__new(this_cause, name, args, cfunkptr, env, is_funktional, documentation));



// funk

def_primobject_9_slot(funk, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);

f2ptr f2__funk__new(f2ptr cause) {
  return f2funk__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(funk__new, return f2__funk__new(this_cause));


// metro

def_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);

f2ptr f2__metro__new(f2ptr cause) {
  return f2metro__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(metro__new, return f2__metro__new(this_cause));


// exception

def_primobject_2_slot(exception, tag, value);

f2ptr f2__exception__new(f2ptr cause, f2ptr tag, f2ptr value) {return f2exception__new(cause, tag, value);}
def_pcfunk2(exception__new, tag, value, return f2__exception__new(this_cause, tag, value));



// bytecode

def_primobject_4_slot(bytecode, command, arg0, arg1, arg2);

f2ptr f2__bytecode__new(f2ptr cause, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2) {return f2bytecode__new(cause, command, arg0, arg1, arg2);}
def_pcfunk4(bytecode__new, command, arg0, arg1, arg2, return f2__bytecode__new(this_cause, command, arg0, arg1, arg2));


// fiber

def_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);

f2ptr f2__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args) {
  f2ptr program_counter    = nil;
  f2ptr stack              = nil;
  f2ptr iter               = nil;
  f2ptr env                = parent_env;
  f2ptr args               = nil;
  f2ptr return_reg         = nil;
  f2ptr value              = nil;
  f2ptr trace              = nil;
  f2ptr critics            = nil;
  f2ptr cause_reg          = cause;
  f2ptr keep_undead        = __funk2.globalenv.true__symbol;
  f2ptr is_zombie          = nil;
  f2ptr execute_mutex      = f2mutex__new(cause);
  f2ptr paused             = nil;
  f2ptr last_executed_time = nil;
  f2ptr sleep_until_time   = nil;
  f2ptr larva_args         = nil;
  f2ptr new_fiber = f2fiber__new(cause, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);
  f2fiber__keep_undead__set(new_fiber, cause, __funk2.globalenv.true__symbol);
  f2fiber__funk(new_fiber, cause, cfunkable, cfunkable_args);
  
  //f2cause__fibers__set(cause, cause, f2cons__new(cause, new_fiber, f2cause__fibers(cause, cause)));
  
  return new_fiber;
}

def_pcfunk4(fiber__new, parent_fiber, parent_env, cfunkable, cfunkable_args, return f2__fiber__new(this_cause, parent_fiber, parent_env, cfunkable, cfunkable_args));

f2ptr f2__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time) {
  if (! raw__time__is_type(cause, until_time)) {
    return f2larva__new(cause, 1);
  }
  f2fiber__sleep_until_time__set(this, cause, until_time);
  return nil;
}
def_pcfunk2(fiber__do_sleep_until_time, this, until_time, return f2__fiber__do_sleep_until_time(this_cause, this, until_time));

f2ptr f2__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, f2ptr nanoseconds) {
  if (! raw__integer__is_type(cause, nanoseconds)) {
    return f2larva__new(cause, 1);
  }
  s64 nanoseconds__i = f2integer__i(nanoseconds, cause);
  return f2__fiber__do_sleep_until_time(cause, this, f2time__new(cause, f2integer__new(cause, raw__nanoseconds_since_1970() + nanoseconds__i)));
}
def_pcfunk2(fiber__sleep_for_nanoseconds, this, nanoseconds, return f2__fiber__sleep_for_nanoseconds(this_cause, this, nanoseconds));


// processor

def_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);

f2ptr f2__processor__new(f2ptr cause) {
  return f2processor__new(cause, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil, nil);
}
def_pcfunk0(processor__new, return f2__processor__new(this_cause));

// scheduler

def_primobject_5_slot(scheduler, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);

f2ptr f2__scheduler__new(f2ptr cause, f2ptr processors, f2ptr event_subscribers_mutex, f2ptr event_subscribers, f2ptr event_buffer_mutex, f2ptr event_buffer) {return f2scheduler__new(cause, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);}
def_pcfunk5(scheduler__new, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer, return f2__scheduler__new(this_cause, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer));


// event_subscriber

def_primobject_5_slot(event_subscriber, event_types, fiber, funkable, event_buffer, event_buffer_mutex);

f2ptr f2__event_subscriber__new(f2ptr cause, f2ptr event_types, f2ptr fiber, f2ptr funkable, f2ptr event_buffer, f2ptr event_buffer_mutex) {return f2event_subscriber__new(cause, event_types, fiber, funkable, event_buffer, event_buffer_mutex);}
def_pcfunk5(event_subscriber__new, event_types, fiber, funkable, event_buffer, event_buffer_mutex, return f2__event_subscriber__new(this_cause, event_types, fiber, funkable, event_buffer, event_buffer_mutex));


// transframe

def_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);

f2ptr f2__transframe__new(f2ptr cause, f2ptr nanoseconds_since_1970, f2ptr symbol_old_news) {return f2transframe__new(cause, nanoseconds_since_1970, symbol_old_news);}
def_pcfunk2(transframe__new, nanoseconds_since_1970, symbol_old_news, return f2__transframe__new(this_cause, nanoseconds_since_1970, symbol_old_news));


// time

def_primobject_1_slot(time, nanoseconds_since_1970);

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970) {return f2time__new(cause, nanoseconds_since_1970);}
def_pcfunk1(time__new, nanoseconds_since_1970, return f2__time__new(this_cause, nanoseconds_since_1970));

u64 raw__time__years(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.years;
}

f2ptr f2__time__years(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__years(cause, this));}
def_pcfunk1(time__years, this, return f2__time__years(this_cause, this));

u64 raw__time__months(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.months;
}

f2ptr f2__time__months(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__months(cause, this));}
def_pcfunk1(time__months, this, return f2__time__months(this_cause, this));

u64 raw__time__days(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.days;
}

f2ptr f2__time__days(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__days(cause, this));}
def_pcfunk1(time__days, this, return f2__time__days(this_cause, this));

u64 raw__time__hours(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.hours;
}

f2ptr f2__time__hours(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__hours(cause, this));}
def_pcfunk1(time__hours, this, return f2__time__hours(this_cause, this));

u64 raw__time__minutes(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.minutes;
}

f2ptr f2__time__minutes(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__minutes(cause, this));}
def_pcfunk1(time__minutes, this, return f2__time__minutes(this_cause, this));

u64 raw__time__seconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.seconds;
}

f2ptr f2__time__seconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__seconds(cause, this));}
def_pcfunk1(time__seconds, this, return f2__time__seconds(this_cause, this));

u64 raw__time__nanoseconds(f2ptr cause, f2ptr this) {
  u64 nanoseconds_since_1970__i = f2integer__i(f2time__nanoseconds_since_1970(this, cause), cause);
  funk2_date_t funk2_date;
  nanoseconds_since_1970__to_funk2_date(nanoseconds_since_1970__i, &funk2_date);
  return funk2_date.nanoseconds;
}

f2ptr f2__time__nanoseconds(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__time__nanoseconds(cause, this));}
def_pcfunk1(time__nanoseconds, this, return f2__time__nanoseconds(this_cause, this));

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
  __fiber__symbol            = new__symbol(cause, "fiber");
  __processor__symbol        = new__symbol(cause, "processor");
  __scheduler__symbol        = new__symbol(cause, "scheduler");
  __event_subscriber__symbol = new__symbol(cause, "event_subscriber");
  __cause__symbol            = new__symbol(cause, "cause");
  __transframe__symbol       = new__symbol(cause, "transframe");
  __bug__symbol              = new__symbol(cause, "bug");
  __time__symbol             = new__symbol(cause, "time");
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
  {char* symbol_str = "type"; __funk2.globalenv.object_type.primobject.type__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(primobject__type, this, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.type__funk = never_gc(cfunk);}
  {char* symbol_str = "type-set"; __funk2.globalenv.object_type.primobject.type__set__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(primobject__type__set, this, value, cfunk, 0, "primobject_type funktion (defined in f2_primobjects.c)"); __funk2.globalenv.object_type.primobject.type__set__funk = never_gc(cfunk);}
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
  
  // doublelink
  
  initialize_primobject_3_slot(doublelink, prev, next, value);

  // imagination_link
  
  initialize_primobject_5_slot(imagination_link, next, name, value, trace, imagination_frame);
  
  // cfunk
  
  initialize_primobject_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation);
  
  // metrocfunk
  
  initialize_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);
  
  // funk
  
  initialize_primobject_9_slot(funk, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);
  
  // metro
  
  initialize_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);
  
  // exception
  
  initialize_primobject_2_slot(exception, tag, value);
  
  // bytecode
  
  initialize_primobject_4_slot(bytecode, command, arg0, arg1, arg2);
  
  // fiber
  
  initialize_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);
  
  // processor
  
  initialize_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);
  
  // scheduler
  
  initialize_primobject_5_slot(scheduler, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);
  
  // event_subscriber
  
  initialize_primobject_5_slot(event_subscriber, event_types, fiber, funkable, event_buffer, event_buffer_mutex);
  
  // transframe
  
  initialize_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);
  
  // bug
  
  initialize_primobject_1_slot(bug, bug_type);
  
  // time
  
  initialize_primobject_1_slot(time, nanoseconds_since_1970);
  initialize_primobject_funk(time, years);
  initialize_primobject_funk(time, months);
  initialize_primobject_funk(time, days);
  initialize_primobject_funk(time, hours);
  initialize_primobject_funk(time, minutes);
  initialize_primobject_funk(time, seconds);
  initialize_primobject_funk(time, nanoseconds);
  
  // size_2d
  
  initialize_primobject_2_slot(size_2d, x, y);
  
  // event
  
  initialize_primobject_4_slot(event, node_id, event_id, event_type, data);
  
  // bytecode_event
  
  initialize_primobject_2_slot(bytecode_event, bytecode, context);
  
}


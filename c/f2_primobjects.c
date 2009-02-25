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
  f2primobject__type__set__trace_depth(            this, cause, type, trace_depth);
  f2primobject__dynamic_slots__set__trace_depth(   this, cause, dynamic_slots, trace_depth);
  return this;
}

f2ptr f2__primobject__new(f2ptr cause, f2ptr type, int static_slot_num, f2ptr dynamic_slots) {
  return f2__primobject__new__trace_depth(cause, type, static_slot_num, dynamic_slots, 1);
}


// place

defprimobject__static_slot(place__thing, 0);

f2ptr __place__symbol = -1;

f2ptr f2place__new(f2ptr cause, f2ptr p) {
  release__assert(__place__symbol != -1, nil, "f2place__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __place__symbol, 1, nil);
  f2place__thing__set(this, cause, p);
  return this;
}


// cons

defprimobject__static_slot(cons__car, 0);
defprimobject__static_slot(cons__cdr, 1);

f2ptr __cons__symbol = -1;

f2ptr f2cons__new__trace_depth(f2ptr cause, f2ptr car, f2ptr cdr, int trace_depth) {
  release__assert(__cons__symbol != -1, nil, "f2cons__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __cons__symbol, 2, nil, trace_depth);
  f2cons__car__set__trace_depth(this, cause, car, trace_depth);
  f2cons__cdr__set__trace_depth(this, cause, cdr, trace_depth);
  return this;
}

f2ptr f2cons__new(f2ptr cause, f2ptr car, f2ptr cdr) {
  return f2cons__new__trace_depth(cause, car, cdr, 1);
}


// doublelink

defprimobject__static_slot(doublelink__prev,  0);
defprimobject__static_slot(doublelink__next,  1);
defprimobject__static_slot(doublelink__value, 2);

f2ptr __doublelink__symbol = -1;

f2ptr f2doublelink__new__trace_depth(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value, int trace_depth) {
  release__assert(__doublelink__symbol != -1, nil, "f2doublelink__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __doublelink__symbol, 3, nil, trace_depth);
  f2doublelink__prev__set__trace_depth( this, cause, prev,  trace_depth);
  f2doublelink__next__set__trace_depth( this, cause, next,  trace_depth);
  f2doublelink__value__set__trace_depth(this, cause, value, trace_depth);
  return this;
}

f2ptr f2doublelink__new(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value) {
  return f2doublelink__new__trace_depth(cause, prev, next, value, 1);
}

// imagination_link

defprimobject__static_slot(imagination_link__next,              0);
defprimobject__static_slot(imagination_link__name,              1);
defprimobject__static_slot(imagination_link__value,             2);
defprimobject__static_slot(imagination_link__trace,             3);
defprimobject__static_slot(imagination_link__imagination_frame, 4);

f2ptr __imagination_link__symbol = -1;

f2ptr f2imagination_link__new__trace_depth(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame, int trace_depth) {
  release__assert(__imagination_link__symbol != -1, nil, "f2imagination_link__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __imagination_link__symbol, 5, nil, trace_depth);
  f2imagination_link__next__set__trace_depth(             this, cause, next,              trace_depth);
  f2imagination_link__name__set__trace_depth(             this, cause, name,              trace_depth);
  f2imagination_link__value__set__trace_depth(            this, cause, value,             trace_depth);
  f2imagination_link__trace__set__trace_depth(            this, cause, trace,             trace_depth);
  f2imagination_link__imagination_frame__set__trace_depth(this, cause, imagination_frame, trace_depth);
  return this;
}

f2ptr f2imagination_link__new(f2ptr cause, f2ptr next, f2ptr name, f2ptr value, f2ptr trace, f2ptr imagination_frame) {
  return f2imagination_link__new__trace_depth(cause, next, name, value, trace, imagination_frame, 1);
}

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

f2ptr f2__imagination_frame__get_slot(f2ptr cause, f2ptr this, f2ptr name) {
  f2ptr slot_iter = this;
  while (slot_iter) {
    f2ptr slot_name = f2imagination_link__name(slot_iter, cause);
    if (raw__symbol__eq(cause, name, slot_name)) {
      return slot_iter;
    }
    slot_iter = f2imagination_link__next(slot_iter, cause);
  }
  return nil;
}

f2ptr f2__imagination_link__get_slot(f2ptr cause, f2ptr this, f2ptr name) {
  f2ptr imagination_frame = f2imagination_link__imagination_frame(this, cause);
  return f2__imagination_frame__get_slot(cause, imagination_frame, name);
}

f2ptr f2__imagination_link__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value) {
  f2ptr imagination_link_iter = this;
  f2ptr name_iter             = name_stack;
  while (name_iter) {
    f2ptr name = f2cons__car(name_iter, cause);
    f2ptr slot = f2__imagination_link__get_slot(cause, imagination_link_iter, name);
    if (! slot) {
      return doesnt_exist_value;
    }
    imagination_link_iter = slot;
    name_iter = f2cons__cdr(name_iter, cause);
  }
  return f2imagination_link__value(imagination_link_iter, cause);
}

f2ptr f2__imagination_frame__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value) {
  if (name_stack) {
    f2ptr name = f2cons__car(name_stack, cause);
    f2ptr slot = f2__imagination_frame__get_slot(cause, this, name);
    if (! slot) {
      return doesnt_exist_value;
    }
    return f2__imagination_link__get_value_from_name_stack(cause, slot, f2cons__cdr(name_stack, cause), doesnt_exist_value);
  }
  return doesnt_exist_value;
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

defprimobject__static_slot(cfunk__name,          0);
defprimobject__static_slot(cfunk__args,          1);
defprimobject__static_slot(cfunk__cfunkptr,      2);
defprimobject__static_slot(cfunk__env,           3);
defprimobject__static_slot(cfunk__is_funktional, 4);

f2ptr __cfunk__symbol = -1;

f2ptr f2cfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional) {
  /*pause_gc();*/
  release__assert(__cfunk__symbol != -1, nil, "f2cfunk__new error: used before primobjects initialized.");
  if (!cfunkptr) {return primobject_error("cfunk-cfunkptr cannot be nil.");}
  f2ptr this = f2__primobject__new(cause, __cfunk__symbol, 5, nil);
  f2cfunk__name__set(         this, cause, name);
  f2cfunk__args__set(         this, cause, args);
  f2cfunk__cfunkptr__set(     this, cause, cfunkptr);
  f2cfunk__env__set(          this, cause, env);
  f2cfunk__is_funktional__set(this, cause, is_funktional);
  /*resume_gc();*/
  return this;
}

// metrocfunk

defprimobject__static_slot(metrocfunk__name,          0);
defprimobject__static_slot(metrocfunk__args,          1);
defprimobject__static_slot(metrocfunk__cfunkptr,      2);
defprimobject__static_slot(metrocfunk__env,           3);
defprimobject__static_slot(metrocfunk__is_funktional, 4);

f2ptr __metrocfunk__symbol = -1;

f2ptr f2metrocfunk__new(f2ptr cause, f2ptr name, f2ptr args, f2ptr cfunkptr, f2ptr env, f2ptr is_funktional) {
  /*pause_gc();*/
  release__assert(__metrocfunk__symbol != -1, nil, "f2metrocfunk__new error: used before primobjects initialized.");
  if (!cfunkptr) {return primobject_error("metrocfunk-cfunkptr cannot be nil.");}
  f2ptr this = f2__primobject__new(cause, __metrocfunk__symbol, 5, nil);
  f2metrocfunk__name__set(         this, cause, name);
  f2metrocfunk__args__set(         this, cause, args);
  f2metrocfunk__cfunkptr__set(     this, cause, cfunkptr);
  f2metrocfunk__env__set(          this, cause, env);
  f2metrocfunk__is_funktional__set(this, cause, env);
  /*resume_gc();*/
  return this;
}


// funk

defprimobject__static_slot(funk__name,                0);
defprimobject__static_slot(funk__body_bytecodes,      1);
defprimobject__static_slot(funk__args,                2);
defprimobject__static_slot(funk__demetropolized_body, 3);
defprimobject__static_slot(funk__body,                4);
defprimobject__static_slot(funk__env,                 5);
defprimobject__static_slot(funk__machine_code,        6);
defprimobject__static_slot(funk__is_funktional,       7);

f2ptr __funk__symbol = -1;

f2ptr f2funk__new(f2ptr cause, f2ptr name, f2ptr body_bytecodes, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr env, f2ptr machine_code, f2ptr is_funktional) {
  /*pause_gc();*/
  release__assert(__funk__symbol != -1, nil, "f2funk__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __funk__symbol, 8, nil);
  f2funk__name__set(               this, cause, name);
  f2funk__body_bytecodes__set(     this, cause, body_bytecodes);
  f2funk__args__set(               this, cause, args);
  f2funk__demetropolized_body__set(this, cause, demetropolized_body);
  f2funk__body__set(               this, cause, body);
  f2funk__env__set(                this, cause, env);
  f2funk__machine_code__set(       this, cause, machine_code);
  f2funk__is_funktional__set(      this, cause, is_funktional);
  /*resume_gc();*/
  return this;
}


// metro

defprimobject__static_slot(metro__name,                0);
defprimobject__static_slot(metro__body_bytecodes,      1);
defprimobject__static_slot(metro__args,                2);
defprimobject__static_slot(metro__demetropolized_body, 3);
defprimobject__static_slot(metro__body,                4);
defprimobject__static_slot(metro__env,                 5);
defprimobject__static_slot(metro__machine_code,        6);
defprimobject__static_slot(metro__is_funktional,       7);

f2ptr __metro__symbol = -1;

f2ptr f2metro__new(f2ptr cause, f2ptr name, f2ptr body_bytecodes, f2ptr args, f2ptr demetropolized_body, f2ptr body, f2ptr env, f2ptr machine_code, f2ptr is_funktional) {
  /*pause_gc();*/
  release__assert(__metro__symbol != -1, nil, "f2metro__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __metro__symbol, 8, nil);
  f2metro__name__set(               this, cause, name);
  f2metro__body_bytecodes__set(     this, cause, body_bytecodes);
  f2metro__args__set(               this, cause, args);
  f2metro__demetropolized_body__set(this, cause, demetropolized_body);
  f2metro__body__set(               this, cause, body);
  f2metro__env__set(                this, cause, env);
  f2metro__machine_code__set(       this, cause, machine_code);
  f2metro__is_funktional__set(      this, cause, is_funktional);
  /*resume_gc();*/
  return this;
}


// exception

defprimobject__static_slot(exception__tag,   0);
defprimobject__static_slot(exception__value, 1);

f2ptr __exception__symbol = -1;

f2ptr f2exception__new(f2ptr cause, f2ptr tag, f2ptr value) {
  /*pause_gc();*/
  release__assert(__exception__symbol != -1, nil, "f2exception__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __exception__symbol, 2, nil);
  f2exception__tag__set(  this, cause, tag);
  f2exception__value__set(this, cause, value);
  /*resume_gc();*/
  return this;
}


// bytecode

defprimobject__static_slot(bytecode__tracing_on, 0);
defprimobject__static_slot(bytecode__command,    1);
defprimobject__static_slot(bytecode__arg0,       2);
defprimobject__static_slot(bytecode__arg1,       3);
defprimobject__static_slot(bytecode__arg2,       4);

f2ptr __bytecode__symbol = -1;

f2ptr f2bytecode__new(f2ptr cause, f2ptr tracing_on, f2ptr command, f2ptr arg0, f2ptr arg1, f2ptr arg2) {
  /*pause_gc();*/
  release__assert(__bytecode__symbol != -1, nil, "f2bytecode__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __bytecode__symbol, 5, nil);
  f2bytecode__tracing_on__set(this, cause, tracing_on);
  f2bytecode__command__set(   this, cause, command);
  f2bytecode__arg0__set(      this, cause, arg0);
  f2bytecode__arg1__set(      this, cause, arg1);
  f2bytecode__arg2__set(      this, cause, arg2);
  /*resume_gc();*/
  return this;
}


// thread

defprimobject__static_slot(thread__program_counter,     0);
defprimobject__static_slot(thread__stack,               1);
defprimobject__static_slot(thread__iter,                2);
defprimobject__static_slot(thread__env,                 3);
defprimobject__static_slot(thread__args,                4);
defprimobject__static_slot(thread__return,              5);
defprimobject__static_slot(thread__value,               6);
defprimobject__static_slot(thread__trace,               7);
defprimobject__static_slot(thread__critics,             8);
defprimobject__static_slot(thread__cause_reg,           9);
defprimobject__static_slot(thread__keep_undead,        10);
defprimobject__static_slot(thread__is_zombie,          11);
defprimobject__static_slot(thread__parent_thread,      12);
defprimobject__static_slot(thread__parent_env,         13);
defprimobject__static_slot(thread__execute_mutex,      14);
defprimobject__static_slot(thread__paused,             15);
defprimobject__static_slot(thread__last_executed_time, 16);

f2ptr __thread__symbol = -1;

f2ptr f2thread__new(f2ptr cause,
		    f2ptr program_counter,
		    f2ptr stack,
		    f2ptr iter,
		    f2ptr env,
		    f2ptr args,
		    f2ptr retval,
		    f2ptr value,
		    f2ptr trace,
		    f2ptr critics,
		    f2ptr cause_reg,
		    f2ptr keep_undead,
		    f2ptr is_zombie,
		    f2ptr parent_thread,
		    f2ptr parent_env,
		    f2ptr execute_mutex,
		    f2ptr paused,
		    f2ptr last_executed_time) {
  /*pause_gc();*/
  release__assert(__thread__symbol != -1, nil, "f2thread__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __thread__symbol, 17, nil);
  f2thread__program_counter__set(   this, cause, program_counter);
  f2thread__stack__set(             this, cause, stack);
  f2thread__iter__set(              this, cause, iter);
  f2thread__env__set(               this, cause, env);
  f2thread__args__set(              this, cause, args);
  f2thread__return__set(            this, cause, retval);
  f2thread__value__set(             this, cause, value);
  f2thread__trace__set(             this, cause, trace);
  f2thread__critics__set(           this, cause, critics);
  f2thread__cause_reg__set(         this, cause, cause_reg);
  f2thread__keep_undead__set(       this, cause, keep_undead);
  f2thread__is_zombie__set(         this, cause, is_zombie);
  f2thread__parent_thread__set(     this, cause, parent_thread);
  f2thread__parent_env__set(        this, cause, parent_env);
  f2thread__execute_mutex__set(     this, cause, execute_mutex);
  f2thread__last_executed_time__set(this, cause, paused);
  f2thread__last_executed_time__set(this, cause, last_executed_time);
  /*resume_gc();*/
  return this;
}

//int f2thread__is_complete(f2ptr this) {
//  return __pure__f2thread__is_complete(this);
//}


// processor

defprimobject__static_slot(processor__scheduler,              0);
defprimobject__static_slot(processor__pthread,                1);
defprimobject__static_slot(processor__active_threads_mutex,   2);
defprimobject__static_slot(processor__active_threads,         3);
defprimobject__static_slot(processor__sleeping_threads_mutex, 4);
defprimobject__static_slot(processor__sleeping_threads,       5);
defprimobject__static_slot(processor__pool_index,             6);
defprimobject__static_slot(processor__desc,                   7);

f2ptr __processor__symbol = -1;

f2ptr f2processor__new(f2ptr cause, f2ptr scheduler, f2ptr pthread, f2ptr active_threads_mutex, f2ptr active_threads, f2ptr sleeping_threads_mutex, f2ptr sleeping_threads, f2ptr pool_index, f2ptr desc) {
  release__assert(__processor__symbol != -1, nil, "f2processor__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __processor__symbol, 8, nil);
  f2processor__scheduler__set(             this, cause, scheduler);
  f2processor__pthread__set(               this, cause, pthread);
  f2processor__active_threads_mutex__set(  this, cause, active_threads_mutex);
  f2processor__active_threads__set(        this, cause, active_threads);
  f2processor__sleeping_threads_mutex__set(this, cause, sleeping_threads_mutex);
  f2processor__sleeping_threads__set(      this, cause, sleeping_threads);
  f2processor__pool_index__set(            this, cause, pool_index);
  f2processor__desc__set(                  this, cause, desc);
  return this;
}


// scheduler

defprimobject__static_slot(scheduler__processors,              0);
defprimobject__static_slot(scheduler__event_subscribers_mutex, 1);
defprimobject__static_slot(scheduler__event_subscribers,       2);
defprimobject__static_slot(scheduler__event_buffer_mutex,      3);
defprimobject__static_slot(scheduler__event_buffer,            4);

f2ptr __scheduler__symbol = -1;

f2ptr f2scheduler__new(f2ptr cause, f2ptr processors, f2ptr event_subscribers_mutex, f2ptr event_subscribers, f2ptr event_buffer_mutex, f2ptr event_buffer) {
  release__assert(__scheduler__symbol != -1, nil, "f2scheduler__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __scheduler__symbol, 5, nil);
  f2scheduler__processors__set(             this, cause, processors);
  f2scheduler__event_subscribers_mutex__set(this, cause, event_subscribers_mutex);
  f2scheduler__event_subscribers__set(      this, cause, event_subscribers);
  f2scheduler__event_buffer_mutex__set(     this, cause, event_buffer_mutex);
  f2scheduler__event_buffer__set(           this, cause, event_buffer);
  return this;
}


// event_subscriber

defprimobject__static_slot(event_subscriber__event_types,        0);
defprimobject__static_slot(event_subscriber__thread,             1);
defprimobject__static_slot(event_subscriber__funkable,           2);
defprimobject__static_slot(event_subscriber__event_buffer,       3);
defprimobject__static_slot(event_subscriber__event_buffer_mutex, 4);

f2ptr __event_subscriber__symbol = -1;

f2ptr f2event_subscriber__new(f2ptr cause, f2ptr event_types, f2ptr thread, f2ptr funkable, f2ptr event_buffer, f2ptr event_buffer_mutex) {
  release__assert(__event_subscriber__symbol != -1, nil, "f2event_subscriber__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __event_subscriber__symbol, 5, nil);
  f2event_subscriber__event_types__set(       this, cause, event_types);
  f2event_subscriber__thread__set(            this, cause, thread);
  f2event_subscriber__funkable__set(          this, cause, funkable);
  f2event_subscriber__event_buffer__set(      this, cause, event_buffer);
  f2event_subscriber__event_buffer_mutex__set(this, cause, event_buffer_mutex);
  return this;
}


// cause

defprimobject__static_slot(cause__tracing_on,        0);
defprimobject__static_slot(cause__subscribers_mutex, 1);
defprimobject__static_slot(cause__subscribers,       2);
defprimobject__static_slot(cause__imagination_stack, 3);

f2ptr __cause__symbol = -1;

f2ptr f2cause__new(f2ptr cause, f2ptr tracing_on, f2ptr subscribers_mutex, f2ptr subscribers, f2ptr imagination_stack) {
  release__assert(__cause__symbol != -1, nil, "f2cause__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __cause__symbol, 4, nil);
  f2cause__tracing_on__set(       this, cause, tracing_on);
  f2cause__subscribers_mutex__set(this, cause, subscribers_mutex);
  f2cause__subscribers__set(      this, cause, subscribers);
  f2cause__imagination_stack__set(this, cause, imagination_stack);
  return this;
}

f2ptr f2__cause__new(f2ptr cause, f2ptr tracing_on, f2ptr subscribers, f2ptr imagination_name) {
  f2ptr subscribers_mutex = f2mutex__new(cause);
  return f2cause__new(cause, tracing_on, subscribers_mutex, subscribers, imagination_name);
}

// transframe

defprimobject__static_slot(transframe__symbol_old_news, 0);

f2ptr __transframe__symbol = -1;

f2ptr f2transframe__new__trace_depth(f2ptr cause, f2ptr symbol_old_news, int trace_depth) {
  release__assert(__transframe__symbol != -1, nil, "f2transframe__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __transframe__symbol, 1, nil, trace_depth);
  f2transframe__symbol_old_news__set__trace_depth( this, cause, symbol_old_news, trace_depth);
  return this;
}

f2ptr f2transframe__new(f2ptr cause, f2ptr symbol_old_news) {
  return f2transframe__new__trace_depth(cause, symbol_old_news, 1);
}


// bug

defprimobject__static_slot(bug__type, 0);

f2ptr __bug__symbol = -1;

f2ptr f2bug__new(f2ptr cause, f2ptr type) {
  release__assert(__bug__symbol != -1, nil, "f2bug__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __bug__symbol, 1, nil);
  f2bug__type__set(this, cause, type);
  return this;
}


// action

defprimobject__static_slot(action__funk,        0);
defprimobject__static_slot(action__transframes, 1);

f2ptr __action__symbol = -1;

f2ptr f2action__new(f2ptr cause, f2ptr funk, f2ptr transframes) {
  release__assert(__action__symbol != -1, nil, "f2action__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __action__symbol, 1, nil);
  f2action__funk__set(       this, cause, funk);
  f2action__transframes__set(this, cause, transframes);
  return this;
}


// size_2d

defprimobject__static_slot(size_2d__x, 0);
defprimobject__static_slot(size_2d__y, 1);

f2ptr __size_2d__symbol = -1;

f2ptr f2size_2d__new(f2ptr cause, f2ptr x, f2ptr y) {
  release__assert(__size_2d__symbol != -1, nil, "f2size_2d__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __size_2d__symbol, 2, nil);
  f2size_2d__x__set(this, cause, x);
  f2size_2d__y__set(this, cause, y);
  return this;
}


// event

defprimobject__static_slot(event__node_id,  0);
defprimobject__static_slot(event__event_id, 1);
defprimobject__static_slot(event__type,     2);
defprimobject__static_slot(event__data,     3);

f2ptr __event__symbol = -1;

f2ptr f2event__new__trace_depth(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data, int trace_depth) {
  release__assert(__event__symbol != -1, nil, "f2event__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new__trace_depth(cause, __event__symbol, 4, nil, trace_depth);
  f2event__node_id__set__trace_depth( this, cause, node_id,  trace_depth);
  f2event__event_id__set__trace_depth(this, cause, event_id, trace_depth);
  f2event__type__set__trace_depth(    this, cause, type,     trace_depth);
  f2event__data__set__trace_depth(    this, cause, data,     trace_depth);
  return this;
}

f2ptr f2event__new(f2ptr cause, f2ptr node_id, f2ptr event_id, f2ptr type, f2ptr data) {
  return f2event__new__trace_depth(cause, node_id, event_id, type, data, 1);
}


// **

void f2__primobjects__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __primobject__symbol       = f2symbol__new(cause, strlen("primobject"),       (u8*)"primobject");
  __place__symbol            = f2symbol__new(cause, strlen("place"),            (u8*)"place");
  __cons__symbol             = f2symbol__new(cause, strlen("cons"),             (u8*)"cons");
  __doublelink__symbol       = f2symbol__new(cause, strlen("doublelink"),       (u8*)"doublelink");
  __imagination_link__symbol = f2symbol__new(cause, strlen("imagination_link"), (u8*)"imagination_link");
  __cfunk__symbol            = f2symbol__new(cause, strlen("cfunk"),            (u8*)"cfunk");
  __metrocfunk__symbol       = f2symbol__new(cause, strlen("metrocfunk"),       (u8*)"metrocfunk");
  __funk__symbol             = f2symbol__new(cause, strlen("funk"),             (u8*)"funk");
  __metro__symbol            = f2symbol__new(cause, strlen("metro"),            (u8*)"metro");
  __exception__symbol        = f2symbol__new(cause, strlen("exception"),        (u8*)"exception");
  __bytecode__symbol         = f2symbol__new(cause, strlen("bytecode"),         (u8*)"bytecode");
  __thread__symbol           = f2symbol__new(cause, strlen("thread"),           (u8*)"thread");
  __processor__symbol        = f2symbol__new(cause, strlen("processor"),        (u8*)"processor");
  __scheduler__symbol        = f2symbol__new(cause, strlen("scheduler"),        (u8*)"scheduler");
  __event_subscriber__symbol = f2symbol__new(cause, strlen("event_subscriber"), (u8*)"event_subscriber");
  __cause__symbol            = f2symbol__new(cause, strlen("cause"),            (u8*)"cause");
  __transframe__symbol       = f2symbol__new(cause, strlen("transframe"),       (u8*)"transframe");
  __bug__symbol              = f2symbol__new(cause, strlen("bug"),              (u8*)"bug");
  __size_2d__symbol          = f2symbol__new(cause, strlen("size_2d"),          (u8*)"size_2d");
  __event__symbol            = f2symbol__new(cause, strlen("event"),            (u8*)"event");
}

void f2__primobjects__initialize() {
  pause_gc();
  f2__primobjects__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __primobject__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __place__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __cons__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __doublelink__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __imagination_link__symbol, nil);
  environment__add_var_value(cause, global_environment(), __cfunk__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __metrocfunk__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __funk__symbol,             nil);
  environment__add_var_value(cause, global_environment(), __metro__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __exception__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __bytecode__symbol,         nil);
  environment__add_var_value(cause, global_environment(), __thread__symbol,           nil);
  environment__add_var_value(cause, global_environment(), __processor__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __scheduler__symbol,        nil);
  environment__add_var_value(cause, global_environment(), __event_subscriber__symbol, nil);
  environment__add_var_value(cause, global_environment(), __cause__symbol,            nil);
  environment__add_var_value(cause, global_environment(), __transframe__symbol,       nil);
  environment__add_var_value(cause, global_environment(), __bug__symbol,              nil);
  environment__add_var_value(cause, global_environment(), __size_2d__symbol,          nil);
  environment__add_var_value(cause, global_environment(), __event__symbol,            nil);
  
  resume_gc();
  try_gc();
}


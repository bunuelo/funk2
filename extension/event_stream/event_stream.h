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

#ifndef F2__EXTENSION__EVENT_STREAM__H
#define F2__EXTENSION__EVENT_STREAM__H

#include "../../c/funk2.h"


#define def_header_ceframe__new__args0(name) \
  f2ptr cause

#define def_header_ceframe__new__args1(name, slot1)	\
  def_header_ceframe__new__args0(name), f2ptr slot1

#define def_header_ceframe__new__args2(name, slot1, slot2)	\
  def_header_ceframe__new__args1(name, slot1), f2ptr slot2


#define def_header_ceframe__new0(name)					\
  f2ptr raw__##name##__new(def_header_ceframe__new__args0(name));	\
  f2ptr  f2__##name##__new(def_header_ceframe__new__args0(name));

#define def_header_ceframe__new1(name, slot1)				\
  f2ptr raw__##name##__new(def_header_ceframe__new__args1(name, slot1)); \
  f2ptr  f2__##name##__new(def_header_ceframe__new__args1(name, slot1));

#define def_header_ceframe__new2(name, slot1, slot2)			\
  f2ptr raw__##name##__new(def_header_ceframe__new__args2(name, slot1, slot2)); \
  f2ptr  f2__##name##__new(def_header_ceframe__new__args2(name, slot1, slot2));



#define def_header_ceframe__common(name)				\
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr thing);		\
  f2ptr      f2__##name##__is_type(f2ptr cause, f2ptr thing);		\
  f2ptr     raw__##name##__type   (f2ptr cause, f2ptr this);		\
  f2ptr      f2__##name##__type   (f2ptr cause, f2ptr this);		\
  									\
  f2ptr f2__##name##_type__new(f2ptr cause);


#define def_header_ceframe__slot(name, slot)				\
  f2ptr raw__##name##__##slot       (f2ptr cause, f2ptr this);		\
  f2ptr  f2__##name##__##slot       (f2ptr cause, f2ptr this);		\
  f2ptr raw__##name##__##slot##__set(f2ptr cause, f2ptr this, f2ptr slot); \
  f2ptr  f2__##name##__##slot##__set(f2ptr cause, f2ptr this, f2ptr slot);


#define def_header_ceframe__slot0(name)

#define def_header_ceframe__slot1(name, slot1)	\
  def_header_ceframe__slot0(name)		\
  def_header_ceframe__slot(name, slot1)

#define def_header_ceframe__slot2(name, slot1, slot2)		\
  def_header_ceframe__slot1(name, slot1)			\
  def_header_ceframe__slot(name, slot2)


#define def_header_ceframe0(name)		\
  def_header_ceframe__new0(name)		\
  def_header_ceframe__common(name)		\
  def_header_ceframe__slot0(name)

#define def_header_ceframe1(name, slot1)	\
  def_header_ceframe__new1(name, slot1)		\
  def_header_ceframe__common(name)		\
  def_header_ceframe__slot1(name, slot1)

#define def_header_ceframe2(name, slot1, slot2)	\
  def_header_ceframe__new2(name, slot1, slot2)	\
  def_header_ceframe__common(name)		\
  def_header_ceframe__slot2(name, slot1, slot2)


// event_stream_event

def_header_ceframe1(event_stream_event, time);

/*

f2ptr raw__event_stream_event__time_value   (f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);
f2ptr raw__event_stream_event__compare_value(f2ptr cause, f2ptr fiber, f2ptr environment, f2ptr args);

f2ptr     raw__event_stream_event__new       (f2ptr cause, f2ptr time);
f2ptr      f2__event_stream_event__new       (f2ptr cause, f2ptr time);
boolean_t raw__event_stream_event__is_type   (f2ptr cause, f2ptr thing);
f2ptr      f2__event_stream_event__is_type   (f2ptr cause, f2ptr thing);
f2ptr     raw__event_stream_event__type      (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream_event__type      (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream_event__time      (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream_event__time      (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream_event__time__set (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__event_stream_event__time__set (f2ptr cause, f2ptr this, f2ptr value);

f2ptr f2__event_stream_event_type__new(f2ptr cause);
*/

// event_stream

def_header_ceframe1(event_stream, event_time_redblacktree);

/*
f2ptr     raw__event_stream__new                         (f2ptr cause);
f2ptr      f2__event_stream__new                         (f2ptr cause);
boolean_t raw__event_stream__is_type                     (f2ptr cause, f2ptr thing);
f2ptr      f2__event_stream__is_type                     (f2ptr cause, f2ptr thing);
f2ptr     raw__event_stream__type                        (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream__type                        (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream__event_time_redblacktree     (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream__event_time_redblacktree     (f2ptr cause, f2ptr this);
f2ptr     raw__event_stream__event_time_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__event_stream__event_time_redblacktree__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__event_stream__add                         (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr      f2__event_stream__add                         (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr     raw__event_stream__remove                      (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr      f2__event_stream__remove                      (f2ptr cause, f2ptr this, f2ptr event_stream_event);
f2ptr     raw__event_stream__size                        (f2ptr cause, f2ptr this);
f2ptr      f2__event_stream__size                        (f2ptr cause, f2ptr this);

f2ptr f2__event_stream_type__new(f2ptr cause);
*/

#define event_stream__iteration(cause, this, event, code) {		\
    redblacktree__iteration(cause, f2__event_stream__event_time_redblacktree(cause, this), event, code); \
  }


// **

f2ptr f2__event_stream__core_extension_ping(f2ptr cause);
f2ptr f2__event_stream__core_extension_initialize(f2ptr cause);
f2ptr f2__event_stream__core_extension_destroy(f2ptr cause);

#endif // F2__EXTENSION__EVENT_STREAM__H


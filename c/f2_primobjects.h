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

#ifndef F2__PRIMOBJECTS__TYPE__H
#define F2__PRIMOBJECTS__TYPE__H

typedef struct funk2_object_type__compound_object__slot_s  funk2_object_type__compound_object__slot_t;
typedef struct funk2_object_type__place__slot_s            funk2_object_type__place__slot_t;
typedef struct funk2_object_type__cons__slot_s             funk2_object_type__cons__slot_t;
typedef struct funk2_object_type__doublelink__slot_s       funk2_object_type__doublelink__slot_t;
typedef struct funk2_object_type__imagination_link__slot_s funk2_object_type__imagination_link__slot_t;
typedef struct funk2_object_type__cfunk__slot_s            funk2_object_type__cfunk__slot_t;
typedef struct funk2_object_type__metrocfunk__slot_s       funk2_object_type__metrocfunk__slot_t;
typedef struct funk2_object_type__funk__slot_s             funk2_object_type__funk__slot_t;
typedef struct funk2_object_type__metro__slot_s            funk2_object_type__metro__slot_t;
typedef struct funk2_object_type__exception__slot_s        funk2_object_type__exception__slot_t;
typedef struct funk2_object_type__bytecode__slot_s         funk2_object_type__bytecode__slot_t;
typedef struct funk2_object_type__fiber__slot_s            funk2_object_type__fiber__slot_t;
typedef struct funk2_object_type__processor__slot_s        funk2_object_type__processor__slot_t;
typedef struct funk2_object_type__scheduler__slot_s        funk2_object_type__scheduler__slot_t;
typedef struct funk2_object_type__event_subscriber__slot_s funk2_object_type__event_subscriber__slot_t;
typedef struct funk2_object_type__cause__slot_s            funk2_object_type__cause__slot_t;
typedef struct funk2_object_type__transframe__slot_s       funk2_object_type__transframe__slot_t;
typedef struct funk2_object_type__bug__slot_s              funk2_object_type__bug__slot_t;
typedef struct funk2_object_type__time__slot_s             funk2_object_type__time__slot_t;
typedef struct funk2_object_type__size_2d__slot_s          funk2_object_type__size_2d__slot_t;
typedef struct funk2_object_type__event__slot_s            funk2_object_type__event__slot_t;
typedef struct funk2_object_type__bytecode_event__slot_s   funk2_object_type__bytecode_event__slot_t;

#define defarray_slot__index_var(name)        array_slot__##name##__index
#define defarray_slot(           name, index)        int defarray_slot__index_var(name) = index
#define defarray_slot__prototype(name)        extern int defarray_slot__index_var(name)

#define array_slot__accessor__trace_depth(         this, name, cause, trace_depth)        raw__array__elt__trace_depth(                   cause, this, defarray_slot__index_var(name), trace_depth)
#define array_slot__accessor(                      this, name, cause)                     raw__array__elt(                                cause, this, defarray_slot__index_var(name))
#define array_slot__set__trace_depth(              this, name, cause, value, trace_depth) raw__array__elt__set__trace_depth(              cause, this, defarray_slot__index_var(name), value, trace_depth)
#define array_slot__set(                           this, name, cause, value)              raw__array__elt__set(                           cause, this, defarray_slot__index_var(name), value)
#define array_slot__tracing_on(                    this, name, cause)                     raw__array__elt__tracing_on(                    cause, this, defarray_slot__index_var(name))
#define array_slot__trace(                         this, name, cause)                     raw__array__elt__trace(                         cause, this, defarray_slot__index_var(name))
#define array_slot__imagination_frame(             this, name, cause)                     raw__array__elt__imagination_frame(             cause, this, defarray_slot__index_var(name))

#define primobject__header_size 3
defarray_slot__prototype(primobject__primobject_label);
#define f2primobject__primobject_label__trace_depth(                   this, cause, trace_depth)        array_slot__accessor__trace_depth(         this, primobject__primobject_label, cause, value, trace_depth)
#define f2primobject__primobject_label(                                this, cause)                     array_slot__accessor(                      this, primobject__primobject_label, cause)
#define f2primobject__primobject_label__set__trace_depth(              this, cause, value, trace_depth) array_slot__set__trace_depth(              this, primobject__primobject_label, cause, value, trace_depth)
#define f2primobject__primobject_label__set(                           this, cause, value)              array_slot__set(                           this, primobject__primobject_label, cause, value)
#define f2primobject__primobject_label__tracing_on(                    this, cause)                     array_slot__tracing_on(                    this, primobject__primobject_label, cause)
#define f2primobject__primobject_label__trace(                         this, cause)                     array_slot__trace(                         this, primobject__primobject_label, cause)
#define f2primobject__primobject_label__imagination_frame(             this, cause)                     array_slot__imagination_frame(             this, primobject__primobject_label, cause)

defarray_slot__prototype(primobject__type);
#define f2primobject__type__trace_depth(                   this, cause, trace_depth)        array_slot__accessor__trace_depth(         this, primobject__type, cause, trace_depth)
#define f2primobject__type(                                this, cause)                     array_slot__accessor(                      this, primobject__type, cause)
#define f2primobject__type__set__trace_depth(              this, cause, value, trace_depth) array_slot__set__trace_depth(              this, primobject__type, cause, value, trace_depth)
#define f2primobject__type__set(                           this, cause, value)              array_slot__set(                           this, primobject__type, cause, value)
#define f2primobject__type__tracing_on(                    this, cause)                     array_slot__tracing_on(                    this, primobject__type, cause)
#define f2primobject__type__trace(                         this, cause)                     array_slot__trace(                         this, primobject__type, cause)
#define f2primobject__type__imagination_frame(             this, cause)                     array_slot__imagination_frame(             this, primobject__type, cause)

defarray_slot__prototype(primobject__dynamic_slots);
#define f2primobject__dynamic_slots__trace_depth(                   this, cause, trace_depth)        array_slot__accessor__trace_depth(         this, primobject__dynamic_slots, cause, trace_depth)
#define f2primobject__dynamic_slots(                                this, cause)                     array_slot__accessor(                      this, primobject__dynamic_slots, cause)
#define f2primobject__dynamic_slots__set__trace_depth(              this, cause, value, trace_depth) array_slot__set__trace_depth(              this, primobject__dynamic_slots, cause, value, trace_depth)
#define f2primobject__dynamic_slots__set(                           this, cause, value)              array_slot__set(                           this, primobject__dynamic_slots, cause, value)
#define f2primobject__dynamic_slots__tracing_on(                    this, cause)                     array_slot__tracing_on(                    this, primobject__dynamic_slots, cause)
#define f2primobject__dynamic_slots__trace(                         this, cause)                     array_slot__trace(                         this, primobject__dynamic_slots, cause)
#define f2primobject__dynamic_slots__imagination_frame(             this, cause)                     array_slot__imagination_frame(             this, primobject__dynamic_slots, cause)

#define defprimobject__static_slot(           name, index) defarray_slot(           name, primobject__header_size + index)
#define defprimobject__static_slot__prototype(name)        defarray_slot__prototype(name)

#define primobject__static_slot__accessor__trace_depth(         this, name, cause, trace_depth)        array_slot__accessor__trace_depth(         this, name, cause, trace_depth)
#define primobject__static_slot__accessor(                      this, name, cause)                     array_slot__accessor(                      this, name, cause)
#define primobject__static_slot__set__trace_depth(              this, name, cause, value, trace_depth) array_slot__set__trace_depth(              this, name, cause, value, trace_depth)
#define primobject__static_slot__set(                           this, name, cause, value)              array_slot__set(                           this, name, cause, value)
#define primobject__static_slot__tracing_on(                    this, name, cause)                     array_slot__tracing_on(                    this, name, cause)
#define primobject__static_slot__trace(                         this, name, cause)                     array_slot__trace(                         this, name, cause)
#define primobject__static_slot__imagination_frame(             this, name, cause)                     array_slot__imagination_frame(             this, name, cause)

#define raw__primobject__is_type(cause, exp) (raw__array__is_type(cause, exp) && (raw__array__length(cause, exp) > defarray_slot__index_var(primobject__primobject_label)) && (raw__eq(cause, f2primobject__primobject_label(exp, cause), __primobject__symbol)))

#endif // F2__PRIMOBJECTS__TYPE__H

#ifndef F2__PRIMOBJECTS__H
#define F2__PRIMOBJECTS__H

#include "f2_memory.h"
#include "f2_ptypes.h"

boolean_t raw__eq(f2ptr cause, f2ptr x, f2ptr y);                                                          // from f2_primfunks.h
f2ptr raw__array__elt__trace_depth(f2ptr cause, f2ptr this, u64 index, int trace_depth);                   // from f2_primfunks.h
f2ptr     raw__array__elt(f2ptr cause, f2ptr this, u64 index);                                             // from f2_primfunks.h
f2ptr raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value);                               // from f2_primfunks.h
f2ptr raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth); // from f2_primfunks.h
f2ptr raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index);                                     // from f2_primfunks.h
f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index);                                          // from f2_primfunks.h
f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index);                              // from f2_primfunks.h

// primobject

extern f2ptr __primobject__symbol;

f2ptr f2__primobject__new(             f2ptr cause, f2ptr type, int   static_slot_num, f2ptr dynamic_slots);
f2ptr f2__primobject__new__trace_depth(f2ptr cause, f2ptr type, int   static_slot_num, f2ptr dynamic_slots, int trace_depth);
f2ptr   f2primobject__new(             f2ptr cause, f2ptr type, f2ptr static_slot_num, f2ptr dynamic_slots);

f2ptr f2primobject__primobject_type__new(f2ptr cause);

#define declare_primobject_common(name) \
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr x); \
  f2ptr f2__##name##__is_type(f2ptr cause, f2ptr x); \
  f2ptr f2##name##__primobject_type__new(f2ptr cause); \
  static inline boolean_t f2primobject__is__##name(f2ptr this, f2ptr cause) {return raw__eq(cause, f2primobject__type(this, cause), __##name##__symbol);}


#define declare_primobject_slot(name, slot_name) \
  defprimobject__static_slot__prototype(name##__##slot_name); \
  static inline f2ptr f2##name##__##slot_name##__trace_depth(      f2ptr this, f2ptr cause, int trace_depth)              {return primobject__static_slot__accessor__trace_depth(this, name##__##slot_name, cause, trace_depth);} \
  static inline f2ptr f2##name##__##slot_name(                     f2ptr this, f2ptr cause)                               {return primobject__static_slot__accessor(             this, name##__##slot_name, cause);} \
  static inline f2ptr f2##name##__##slot_name##__set__trace_depth( f2ptr this, f2ptr cause, f2ptr value, int trace_depth) {return primobject__static_slot__set__trace_depth(     this, name##__##slot_name, cause, value, trace_depth);} \
  static inline f2ptr f2##name##__##slot_name##__set(              f2ptr this, f2ptr cause, f2ptr value)                  {return primobject__static_slot__set(                  this, name##__##slot_name, cause, value);} \
  static inline f2ptr f2##name##__##slot_name##__tracing_on(       f2ptr this, f2ptr cause)                               {return primobject__static_slot__tracing_on(           this, name##__##slot_name, cause);} \
  static inline f2ptr f2##name##__##slot_name##__trace(            f2ptr this, f2ptr cause)                               {return primobject__static_slot__trace(                this, name##__##slot_name, cause);} \
  static inline f2ptr f2##name##__##slot_name##__imagination_frame(f2ptr this, f2ptr cause)                               {return primobject__static_slot__imagination_frame(    this, name##__##slot_name, cause);} \
  f2ptr f2__##name##__##slot_name(f2ptr cause, f2ptr x); \
  f2ptr f2__##name##__##slot_name##__set(f2ptr cause, f2ptr x, f2ptr y);

#define declare_primobject_1_slot(name, slot_1) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1);

#define declare_primobject_2_slot(name, slot_1, slot_2) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2);

#define declare_primobject_3_slot(name, slot_1, slot_2, slot_3) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3);

#define declare_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4);

#define declare_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5);

#define declare_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6);

#define declare_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7);

#define declare_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8);

#define declare_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9);

#define declare_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10);

#define declare_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11);

#define declare_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12);

#define declare_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13);

#define declare_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13); \
  declare_primobject_slot(name, slot_14);

#define declare_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13); \
  declare_primobject_slot(name, slot_14); \
  declare_primobject_slot(name, slot_15);

#define declare_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13); \
  declare_primobject_slot(name, slot_14); \
  declare_primobject_slot(name, slot_15); \
  declare_primobject_slot(name, slot_16);

#define declare_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13); \
  declare_primobject_slot(name, slot_14); \
  declare_primobject_slot(name, slot_15); \
  declare_primobject_slot(name, slot_16); \
  declare_primobject_slot(name, slot_17);

#define declare_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13); \
  declare_primobject_slot(name, slot_14); \
  declare_primobject_slot(name, slot_15); \
  declare_primobject_slot(name, slot_16); \
  declare_primobject_slot(name, slot_17); \
  declare_primobject_slot(name, slot_18);

#define declare_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19); \
  declare_primobject_common(name); \
  declare_primobject_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2); \
  declare_primobject_slot(name, slot_3); \
  declare_primobject_slot(name, slot_4); \
  declare_primobject_slot(name, slot_5); \
  declare_primobject_slot(name, slot_6); \
  declare_primobject_slot(name, slot_7); \
  declare_primobject_slot(name, slot_8); \
  declare_primobject_slot(name, slot_9); \
  declare_primobject_slot(name, slot_10); \
  declare_primobject_slot(name, slot_11); \
  declare_primobject_slot(name, slot_12); \
  declare_primobject_slot(name, slot_13); \
  declare_primobject_slot(name, slot_14); \
  declare_primobject_slot(name, slot_15); \
  declare_primobject_slot(name, slot_16); \
  declare_primobject_slot(name, slot_17); \
  declare_primobject_slot(name, slot_18); \
  declare_primobject_slot(name, slot_19);

// compound_object

declare_primobject_3_slot(compound_object, compound_object_type, frame, part_frame);

// place

declare_primobject_1_slot(place, thing);

// cons

declare_primobject_2_slot(cons, car, cdr);

// deprecated cons macros

#define f2list1__new(cause, elt0)                                                 f2cons__new(cause, elt0, nil)
#define f2list2__new(cause, elt0, elt1)                                           f2cons__new(cause, elt0, f2cons__new(cause, elt1, nil))
#define f2list3__new(cause, elt0, elt1, elt2)                                     f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, nil)))
#define f2list4__new(cause, elt0, elt1, elt2, elt3)                               f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, nil))))
#define f2list5__new(cause, elt0, elt1, elt2, elt3, elt4)                         f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, nil)))))
#define f2list6__new(cause, elt0, elt1, elt2, elt3, elt4, elt5)                   f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, nil))))))
#define f2list7__new(cause, elt0, elt1, elt2, elt3, elt4, elt5, elt6)             f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, f2cons__new(cause, elt6, nil)))))))
#define f2list8__new(cause, elt0, elt1, elt2, elt3, elt4, elt5, elt6, elt7)       f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, f2cons__new(cause, elt6, f2cons__new(cause, elt7, nil))))))))
#define f2list9__new(cause, elt0, elt1, elt2, elt3, elt4, elt5, elt6, elt7, elt8) f2cons__new(cause, elt0, f2cons__new(cause, elt1, f2cons__new(cause, elt2, f2cons__new(cause, elt3, f2cons__new(cause, elt4, f2cons__new(cause, elt5, f2cons__new(cause, elt6, f2cons__new(cause, elt7, f2cons__new(cause, elt8, nil)))))))))

#define f2list__elt_0(     this, cause)        f2cons__car(                                                     this, cause)
#define f2list__elt_0__set(this, cause, value) f2cons__car__set(                                                this, cause,                                        value)
#define f2list__elt_1(     this, cause)        f2cons__car(                                         f2cons__cdr(this, cause), cause)
#define f2list__elt_1__set(this, cause, value) f2cons__car__set(                                    f2cons__cdr(this, cause), cause,                                value)
#define f2list__elt_2(     this, cause)        f2cons__car(                             f2cons__cdr(f2cons__cdr(this, cause), cause), cause)
#define f2list__elt_2__set(this, cause, value) f2cons__car__set(                        f2cons__cdr(f2cons__cdr(this, cause), cause), cause,                        value)
#define f2list__elt_3(     this, cause)        f2cons__car(                 f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause), cause)
#define f2list__elt_3__set(this, cause, value) f2cons__car__set(            f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause),  cause,               value)
#define f2list__elt_4(     this, cause)        f2cons__car(     f2cons__cdr(f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause), cause), cause)
#define f2list__elt_4__set(this, cause, value) f2cons__car__set(f2cons__cdr(f2cons__cdr(f2cons__cdr(f2cons__cdr(this, cause), cause), cause), cause), cause, cause, value)



// doublelink

declare_primobject_3_slot(doublelink, prev, next, value);

f2ptr f2__doublelink(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);


// imagination_link

declare_primobject_5_slot(imagination_link, next, name, value, trace, imagination_frame);

f2ptr raw__imagination_frame__lookup_imagination_link__trace_depth(f2ptr cause, f2ptr this, f2ptr real_value, f2ptr imagination_name_stack, int trace_depth);
f2ptr raw__imagination_frame__new_with_added_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth);
void  raw__imagination_link__add_new_imagination_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, f2ptr value, int trace_depth);
f2ptr  f2__imagination_frame__get_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, int trace_depth);
f2ptr  f2__imagination_frame__get_slot(f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__imagination_link__get_slot__trace_depth(f2ptr cause, f2ptr this, f2ptr name, int trace_depth);
f2ptr  f2__imagination_link__get_slot(f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__imagination_link__get_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value, u64 trace_depth);
f2ptr  f2__imagination_link__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value);
f2ptr  f2__imagination_frame__get_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value, int trace_depth);
f2ptr  f2__imagination_frame__get_value_from_name_stack(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr doesnt_exist_value);
void   f2__imagination_link__set_value_from_name_stack__trace_depth(f2ptr cause, f2ptr this, f2ptr name_stack, f2ptr value, int trace_depth);



// cfunk

declare_primobject_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation);


// metrocfunk

declare_primobject_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation);


// funk

declare_primobject_9_slot(funk, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);


// metro

declare_primobject_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation);


// exception

declare_primobject_2_slot(exception, tag, value);


// bytecode

declare_primobject_4_slot(bytecode, command, arg0, arg1, arg2);


// fiber

declare_primobject_19_slot(fiber, program_counter, stack, iter, env, args, return_reg, value, trace, critics, cause_reg, keep_undead, is_zombie, parent_fiber, parent_env, execute_mutex, paused, last_executed_time, sleep_until_time, larva_args);

f2ptr f2__fiber__new(f2ptr cause, f2ptr parent_fiber, f2ptr parent_env, f2ptr cfunkable, f2ptr cfunkable_args);

#define __pure__f2fiber__is_complete(this, cause)  (!f2fiber__program_counter(this, cause))
#define f2fiber__is_complete(this, cause)          __pure__f2fiber__is_complete(this, cause)
//extern int f2fiber__is_complete(f2ptr this);

f2ptr f2__fiber__do_sleep_until_time(f2ptr cause, f2ptr this, f2ptr until_time);
f2ptr f2__fiber__sleep_for_nanoseconds(f2ptr cause, f2ptr this, f2ptr nanoseconds);

// processor

declare_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);


// scheduler

declare_primobject_5_slot(scheduler, processors, event_subscribers_mutex, event_subscribers, event_buffer_mutex, event_buffer);


// event_subscriber

declare_primobject_5_slot(event_subscriber, event_types, fiber, funkable, event_buffer, event_buffer_mutex);


// cause

#define cause__allocate_traced_arrays__default_value (__funk2.globalenv.true__symbol)

declare_primobject_13_slot(cause, fibers_mutex, fibers, frame, allocate_traced_arrays, bytecode_tracing_on, memory_tracing_on, subscribers_mutex, subscribers, imagination_stack, event_buffer_first, event_buffer_last, current_events_mutex, current_events);

f2ptr f2__cause__new_with_default_properties(f2ptr cause);
f2ptr f2__cause__new_default_with_memory_tracing_on(f2ptr cause);
f2ptr f2__cause__new_with_inherited_properties(f2ptr cause);
f2ptr f2__cause__new_imaginary(f2ptr cause, f2ptr imagination_name);
f2ptr f2__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr f2__cause__remove_fiber(f2ptr cause, f2ptr this, f2ptr fiber);

f2ptr  f2__cause__bytecode_tracing_on(f2ptr cause, f2ptr this);
void  raw__cause__event_buffer__add(f2ptr cause, f2ptr event);
f2ptr  f2__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);


// transframe

declare_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);


// bug

declare_primobject_1_slot(bug, bug_type);


// time

declare_primobject_1_slot(time, nanoseconds_since_1970);


// size_2d

declare_primobject_2_slot(size_2d, x, y);


// event

declare_primobject_4_slot(event, node_id, event_id, event_type, data);


// bytecode_event

declare_primobject_2_slot(bytecode_event, bytecode, context);


// end of objects

extern void f2__primobjects__reinitialize_globalvars();
extern void f2__primobjects__initialize();

#endif // F2__PRIMOBJECTS__H

#ifndef F2__PRIMOBJECT__GLOBALENV_STRUCTS
#define F2__PRIMOBJECT__GLOBALENV_STRUCTS

// primobject global slot definitions

#define declare_object_type_common(name, body) \
  struct funk2_object_type__##name##__slot_s { \
    f2ptr is_type__symbol; \
    f2ptr is_type__funk; \
    f2ptr type__symbol; \
    f2ptr type__funk; \
    f2ptr new__symbol; \
    f2ptr new__funk; \
    body; \
  };

#define declare_object_type_slot(slot_name) \
  f2ptr slot_name##__symbol; \
  f2ptr slot_name##__funk; \
  f2ptr slot_name##__set__symbol; \
  f2ptr slot_name##__set__funk;

#define declare_object_type_3_slot(name, slot_1, slot_2, slot_3, body) \
  declare_object_type_common(name, \
    declare_object_type_slot(slot_1); \
    declare_object_type_slot(slot_2); \
    declare_object_type_slot(slot_3); \
    body)

// compound_object

declare_object_type_3_slot(compound_object, compound_object_type, frame, part_frame, );

// place

struct funk2_object_type__place__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr thing__symbol;
  f2ptr thing__funk;
  f2ptr thing__set__symbol;
  f2ptr thing__set__funk;
};

// cons

struct funk2_object_type__cons__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr car__symbol;
  f2ptr car__funk;
  f2ptr car__set__symbol;
  f2ptr car__set__funk;
  f2ptr cdr__symbol;
  f2ptr cdr__funk;
  f2ptr cdr__set__symbol;
  f2ptr cdr__set__funk;
};

// doublelink

struct funk2_object_type__doublelink__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr prev__symbol;
  f2ptr prev__funk;
  f2ptr prev__set__symbol;
  f2ptr prev__set__funk;
  f2ptr next__symbol;
  f2ptr next__funk;
  f2ptr next__set__symbol;
  f2ptr next__set__funk;
  f2ptr value__symbol;
  f2ptr value__funk;
  f2ptr value__set__symbol;
  f2ptr value__set__funk;
};

// imagination_link

struct funk2_object_type__imagination_link__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr next__symbol;
  f2ptr next__funk;
  f2ptr next__set__symbol;
  f2ptr next__set__funk;
  f2ptr name__symbol;
  f2ptr name__funk;
  f2ptr name__set__symbol;
  f2ptr name__set__funk;
  f2ptr value__symbol;
  f2ptr value__funk;
  f2ptr value__set__symbol;
  f2ptr value__set__funk;
  f2ptr trace__symbol;
  f2ptr trace__funk;
  f2ptr trace__set__symbol;
  f2ptr trace__set__funk;
  f2ptr imagination_frame__symbol;
  f2ptr imagination_frame__funk;
  f2ptr imagination_frame__set__symbol;
  f2ptr imagination_frame__set__funk;
};

// cfunk

struct funk2_object_type__cfunk__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr name__symbol;
  f2ptr name__funk;
  f2ptr name__set__symbol;
  f2ptr name__set__funk;
  f2ptr args__symbol;
  f2ptr args__funk;
  f2ptr args__set__symbol;
  f2ptr args__set__funk;
  f2ptr cfunkptr__symbol;
  f2ptr cfunkptr__funk;
  f2ptr cfunkptr__set__symbol;
  f2ptr cfunkptr__set__funk;
  f2ptr env__symbol;
  f2ptr env__funk;
  f2ptr env__set__symbol;
  f2ptr env__set__funk;
  f2ptr is_funktional__symbol;
  f2ptr is_funktional__funk;
  f2ptr is_funktional__set__symbol;
  f2ptr is_funktional__set__funk;
  f2ptr documentation__symbol;
  f2ptr documentation__funk;
  f2ptr documentation__set__symbol;
  f2ptr documentation__set__funk;
};

// metrocfunk

struct funk2_object_type__metrocfunk__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr name__symbol;
  f2ptr name__funk;
  f2ptr name__set__symbol;
  f2ptr name__set__funk;
  f2ptr args__symbol;
  f2ptr args__funk;
  f2ptr args__set__symbol;
  f2ptr args__set__funk;
  f2ptr cfunkptr__symbol;
  f2ptr cfunkptr__funk;
  f2ptr cfunkptr__set__symbol;
  f2ptr cfunkptr__set__funk;
  f2ptr env__symbol;
  f2ptr env__funk;
  f2ptr env__set__symbol;
  f2ptr env__set__funk;
  f2ptr is_funktional__symbol;
  f2ptr is_funktional__funk;
  f2ptr is_funktional__set__symbol;
  f2ptr is_funktional__set__funk;
  f2ptr documentation__symbol;
  f2ptr documentation__funk;
  f2ptr documentation__set__symbol;
  f2ptr documentation__set__funk;
};

// funk

struct funk2_object_type__funk__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  //f2ptr new__symbol;
  //f2ptr new__funk;
  f2ptr name__symbol;
  f2ptr name__funk;
  f2ptr name__set__symbol;
  f2ptr name__set__funk;
  f2ptr body_bytecodes__symbol;
  f2ptr body_bytecodes__funk;
  f2ptr body_bytecodes__set__symbol;
  f2ptr body_bytecodes__set__funk;
  f2ptr args__symbol;
  f2ptr args__funk;
  f2ptr args__set__symbol;
  f2ptr args__set__funk;
  f2ptr demetropolized_body__symbol;
  f2ptr demetropolized_body__funk;
  f2ptr demetropolized_body__set__symbol;
  f2ptr demetropolized_body__set__funk;
  f2ptr body__symbol;
  f2ptr body__funk;
  f2ptr body__set__symbol;
  f2ptr body__set__funk;
  f2ptr env__symbol;
  f2ptr env__funk;
  f2ptr env__set__symbol;
  f2ptr env__set__funk;
  f2ptr machine_code__symbol;
  f2ptr machine_code__funk;
  f2ptr machine_code__set__symbol;
  f2ptr machine_code__set__funk;
  f2ptr is_funktional__symbol;
  f2ptr is_funktional__funk;
  f2ptr is_funktional__set__symbol;
  f2ptr is_funktional__set__funk;
  f2ptr documentation__symbol;
  f2ptr documentation__funk;
  f2ptr documentation__set__symbol;
  f2ptr documentation__set__funk;
};

// metro

struct funk2_object_type__metro__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  //f2ptr new__symbol;
  //f2ptr new__funk;
  f2ptr name__symbol;
  f2ptr name__funk;
  f2ptr name__set__symbol;
  f2ptr name__set__funk;
  f2ptr body_bytecodes__symbol;
  f2ptr body_bytecodes__funk;
  f2ptr body_bytecodes__set__symbol;
  f2ptr body_bytecodes__set__funk;
  f2ptr args__symbol;
  f2ptr args__funk;
  f2ptr args__set__symbol;
  f2ptr args__set__funk;
  f2ptr demetropolized_body__symbol;
  f2ptr demetropolized_body__funk;
  f2ptr demetropolized_body__set__symbol;
  f2ptr demetropolized_body__set__funk;
  f2ptr body__symbol;
  f2ptr body__funk;
  f2ptr body__set__symbol;
  f2ptr body__set__funk;
  f2ptr env__symbol;
  f2ptr env__funk;
  f2ptr env__set__symbol;
  f2ptr env__set__funk;
  f2ptr machine_code__symbol;
  f2ptr machine_code__funk;
  f2ptr machine_code__set__symbol;
  f2ptr machine_code__set__funk;
  f2ptr is_funktional__symbol;
  f2ptr is_funktional__funk;
  f2ptr is_funktional__set__symbol;
  f2ptr is_funktional__set__funk;
  f2ptr documentation__symbol;
  f2ptr documentation__funk;
  f2ptr documentation__set__symbol;
  f2ptr documentation__set__funk;
};

// exception

struct funk2_object_type__exception__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr tag__symbol;
  f2ptr tag__funk;
  f2ptr tag__set__symbol;
  f2ptr tag__set__funk;
  f2ptr value__symbol;
  f2ptr value__funk;
  f2ptr value__set__symbol;
  f2ptr value__set__funk;
};

// bytecode

struct funk2_object_type__bytecode__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr command__symbol;
  f2ptr command__funk;
  f2ptr command__set__symbol;
  f2ptr command__set__funk;
  f2ptr arg0__symbol;
  f2ptr arg0__funk;
  f2ptr arg0__set__symbol;
  f2ptr arg0__set__funk;
  f2ptr arg1__symbol;
  f2ptr arg1__funk;
  f2ptr arg1__set__symbol;
  f2ptr arg1__set__funk;
  f2ptr arg2__symbol;
  f2ptr arg2__funk;
  f2ptr arg2__set__symbol;
  f2ptr arg2__set__funk;
};

// fiber

struct funk2_object_type__fiber__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  //f2ptr new__symbol;
  //f2ptr new__funk;
  f2ptr program_counter__symbol;
  f2ptr program_counter__funk;
  f2ptr program_counter__set__symbol;
  f2ptr program_counter__set__funk;
  f2ptr stack__symbol;
  f2ptr stack__funk;
  f2ptr stack__set__symbol;
  f2ptr stack__set__funk;
  f2ptr iter__symbol;
  f2ptr iter__funk;
  f2ptr iter__set__symbol;
  f2ptr iter__set__funk;
  f2ptr env__symbol;
  f2ptr env__funk;
  f2ptr env__set__symbol;
  f2ptr env__set__funk;
  f2ptr args__symbol;
  f2ptr args__funk;
  f2ptr args__set__symbol;
  f2ptr args__set__funk;
  f2ptr return_reg__symbol;
  f2ptr return_reg__funk;
  f2ptr return_reg__set__symbol;
  f2ptr return_reg__set__funk;
  f2ptr value__symbol;
  f2ptr value__funk;
  f2ptr value__set__symbol;
  f2ptr value__set__funk;
  f2ptr trace__symbol;
  f2ptr trace__funk;
  f2ptr trace__set__symbol;
  f2ptr trace__set__funk;
  f2ptr critics__symbol;
  f2ptr critics__funk;
  f2ptr critics__set__symbol;
  f2ptr critics__set__funk;
  f2ptr cause_reg__symbol;
  f2ptr cause_reg__funk;
  f2ptr cause_reg__set__symbol;
  f2ptr cause_reg__set__funk;
  f2ptr keep_undead__symbol;
  f2ptr keep_undead__funk;
  f2ptr keep_undead__set__symbol;
  f2ptr keep_undead__set__funk;
  f2ptr is_zombie__symbol;
  f2ptr is_zombie__funk;
  f2ptr is_zombie__set__symbol;
  f2ptr is_zombie__set__funk;
  f2ptr parent_fiber__symbol;
  f2ptr parent_fiber__funk;
  f2ptr parent_fiber__set__symbol;
  f2ptr parent_fiber__set__funk;
  f2ptr parent_env__symbol;
  f2ptr parent_env__funk;
  f2ptr parent_env__set__symbol;
  f2ptr parent_env__set__funk;
  f2ptr execute_mutex__symbol;
  f2ptr execute_mutex__funk;
  f2ptr execute_mutex__set__symbol;
  f2ptr execute_mutex__set__funk;
  f2ptr paused__symbol;
  f2ptr paused__funk;
  f2ptr paused__set__symbol;
  f2ptr paused__set__funk;
  f2ptr last_executed_time__symbol;
  f2ptr last_executed_time__funk;
  f2ptr last_executed_time__set__symbol;
  f2ptr last_executed_time__set__funk;
  f2ptr sleep_until_time__get__symbol; // get
  f2ptr sleep_until_time__get__funk;
  f2ptr sleep_until_time__set__symbol; // set
  f2ptr sleep_until_time__set__funk;
  f2ptr do_sleep_until_time__symbol;   // execute
  f2ptr do_sleep_until_time__funk;
  f2ptr sleep_for_nanoseconds__symbol; // execute
  f2ptr sleep_for_nanoseconds__funk;
  f2ptr larva_args__symbol;            // get
  f2ptr larva_args__funk;
  f2ptr larva_args__set__symbol;       // set
  f2ptr larva_args__set__funk;
};

// processor

struct funk2_object_type__processor__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  //f2ptr new__symbol;
  //f2ptr new__funk;
  f2ptr scheduler__symbol;
  f2ptr scheduler__funk;
  f2ptr scheduler__set__symbol;
  f2ptr scheduler__set__funk;
  f2ptr processor_thread__symbol;
  f2ptr processor_thread__funk;
  f2ptr processor_thread__set__symbol;
  f2ptr processor_thread__set__funk;
  f2ptr active_fibers_mutex__symbol;
  f2ptr active_fibers_mutex__funk;
  f2ptr active_fibers_mutex__set__symbol;
  f2ptr active_fibers_mutex__set__funk;
  f2ptr active_fibers__symbol;
  f2ptr active_fibers__funk;
  f2ptr active_fibers__set__symbol;
  f2ptr active_fibers__set__funk;
  f2ptr active_fibers_iter__symbol;
  f2ptr active_fibers_iter__funk;
  f2ptr active_fibers_iter__set__symbol;
  f2ptr active_fibers_iter__set__funk;
  f2ptr active_fibers_prev__symbol;
  f2ptr active_fibers_prev__funk;
  f2ptr active_fibers_prev__set__symbol;
  f2ptr active_fibers_prev__set__funk;
  f2ptr active_fibers_next__symbol;
  f2ptr active_fibers_next__funk;
  f2ptr active_fibers_next__set__symbol;
  f2ptr active_fibers_next__set__funk;
  f2ptr sleeping_fibers_mutex__symbol;
  f2ptr sleeping_fibers_mutex__funk;
  f2ptr sleeping_fibers_mutex__set__symbol;
  f2ptr sleeping_fibers_mutex__set__funk;
  f2ptr sleeping_fibers__symbol;
  f2ptr sleeping_fibers__funk;
  f2ptr sleeping_fibers__set__symbol;
  f2ptr sleeping_fibers__set__funk;
  f2ptr pool_index__symbol;
  f2ptr pool_index__funk;
  f2ptr pool_index__set__symbol;
  f2ptr pool_index__set__funk;
  f2ptr desc__symbol;
  f2ptr desc__funk;
  f2ptr desc__set__symbol;
  f2ptr desc__set__funk;
};

// scheduler

struct funk2_object_type__scheduler__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr processors__symbol;
  f2ptr processors__funk;
  f2ptr processors__set__symbol;
  f2ptr processors__set__funk;
  f2ptr event_subscribers_mutex__symbol;
  f2ptr event_subscribers_mutex__funk;
  f2ptr event_subscribers_mutex__set__symbol;
  f2ptr event_subscribers_mutex__set__funk;
  f2ptr event_subscribers__symbol;
  f2ptr event_subscribers__funk;
  f2ptr event_subscribers__set__symbol;
  f2ptr event_subscribers__set__funk;
  f2ptr event_buffer_mutex__symbol;
  f2ptr event_buffer_mutex__funk;
  f2ptr event_buffer_mutex__set__symbol;
  f2ptr event_buffer_mutex__set__funk;
  f2ptr event_buffer__symbol;
  f2ptr event_buffer__funk;
  f2ptr event_buffer__set__symbol;
  f2ptr event_buffer__set__funk;
};

// event_subscriber

struct funk2_object_type__event_subscriber__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr event_types__symbol;
  f2ptr event_types__funk;
  f2ptr event_types__set__symbol;
  f2ptr event_types__set__funk;
  f2ptr fiber__symbol;
  f2ptr fiber__funk;
  f2ptr fiber__set__symbol;
  f2ptr fiber__set__funk;
  f2ptr funkable__symbol;
  f2ptr funkable__funk;
  f2ptr funkable__set__symbol;
  f2ptr funkable__set__funk;
  f2ptr event_buffer__symbol;
  f2ptr event_buffer__funk;
  f2ptr event_buffer__set__symbol;
  f2ptr event_buffer__set__funk;
  f2ptr event_buffer_mutex__symbol;
  f2ptr event_buffer_mutex__funk;
  f2ptr event_buffer_mutex__set__symbol;
  f2ptr event_buffer_mutex__set__funk;
};

// cause

struct funk2_object_type__cause__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr fibers_mutex__symbol;
  f2ptr fibers_mutex__funk;
  f2ptr fibers_mutex__set__symbol;
  f2ptr fibers_mutex__set__funk;
  f2ptr fibers__symbol;
  f2ptr fibers__funk;
  f2ptr fibers__set__symbol;
  f2ptr fibers__set__funk;
  f2ptr frame__symbol;
  f2ptr frame__funk;
  f2ptr frame__set__symbol;
  f2ptr frame__set__funk;
  f2ptr allocate_traced_arrays__symbol;
  f2ptr allocate_traced_arrays__funk;
  f2ptr allocate_traced_arrays__set__symbol;
  f2ptr allocate_traced_arrays__set__funk;
  f2ptr bytecode_tracing_on__symbol;
  f2ptr bytecode_tracing_on__funk;
  f2ptr bytecode_tracing_on__set__symbol;
  f2ptr bytecode_tracing_on__set__funk;
  f2ptr memory_tracing_on__symbol;
  f2ptr memory_tracing_on__funk;
  f2ptr memory_tracing_on__set__symbol;
  f2ptr memory_tracing_on__set__funk;
  f2ptr subscribers_mutex__symbol;
  f2ptr subscribers_mutex__funk;
  f2ptr subscribers_mutex__set__symbol;
  f2ptr subscribers_mutex__set__funk;
  f2ptr subscribers__symbol;
  f2ptr subscribers__funk;
  f2ptr subscribers__set__symbol;
  f2ptr subscribers__set__funk;
  f2ptr imagination_stack__symbol;
  f2ptr imagination_stack__funk;
  f2ptr imagination_stack__set__symbol;
  f2ptr imagination_stack__set__funk;
  f2ptr event_buffer_first__symbol;
  f2ptr event_buffer_first__funk;
  f2ptr event_buffer_first__set__symbol;
  f2ptr event_buffer_first__set__funk;
  f2ptr event_buffer_last__symbol;
  f2ptr event_buffer_last__funk;
  f2ptr event_buffer_last__set__symbol;
  f2ptr event_buffer_last__set__funk;
  f2ptr current_events_mutex__symbol;
  f2ptr current_events_mutex__funk;
  f2ptr current_events_mutex__set__symbol;
  f2ptr current_events_mutex__set__funk;
  f2ptr current_events__symbol;
  f2ptr current_events__funk;
  f2ptr current_events__set__symbol;
  f2ptr current_events__set__funk;
  f2ptr define__symbol;
  f2ptr define__funk;
  f2ptr define__funk__symbol;
  f2ptr define__funk__funk;
};

// transframe

struct funk2_object_type__transframe__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr nanoseconds_since_1970__symbol;
  f2ptr nanoseconds_since_1970__funk;
  f2ptr nanoseconds_since_1970__set__symbol;
  f2ptr nanoseconds_since_1970__set__funk;
  f2ptr symbol_old_news__symbol;
  f2ptr symbol_old_news__funk;
  f2ptr symbol_old_news__set__symbol;
  f2ptr symbol_old_news__set__funk;
};

// bug

struct funk2_object_type__bug__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr bug_type__symbol;
  f2ptr bug_type__funk;
  f2ptr bug_type__set__symbol;
  f2ptr bug_type__set__funk;
};

// time

struct funk2_object_type__time__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr nanoseconds_since_1970__symbol;
  f2ptr nanoseconds_since_1970__funk;
  f2ptr nanoseconds_since_1970__set__symbol;
  f2ptr nanoseconds_since_1970__set__funk;
  f2ptr years__symbol;
  f2ptr years__funk;
  f2ptr months__symbol;
  f2ptr months__funk;
  f2ptr days__symbol;
  f2ptr days__funk;
  f2ptr hours__symbol;
  f2ptr hours__funk;
  f2ptr minutes__symbol;
  f2ptr minutes__funk;
  f2ptr seconds__symbol;
  f2ptr seconds__funk;
  f2ptr nanoseconds__symbol;
  f2ptr nanoseconds__funk;
};

// size_2d

struct funk2_object_type__size_2d__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr x__symbol;
  f2ptr x__funk;
  f2ptr x__set__symbol;
  f2ptr x__set__funk;
  f2ptr y__symbol;
  f2ptr y__funk;
  f2ptr y__set__symbol;
  f2ptr y__set__funk;
};

// event

struct funk2_object_type__event__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr node_id__symbol;
  f2ptr node_id__funk;
  f2ptr node_id__set__symbol;
  f2ptr node_id__set__funk;
  f2ptr event_id__symbol;
  f2ptr event_id__funk;
  f2ptr event_id__set__symbol;
  f2ptr event_id__set__funk;
  f2ptr event_type__symbol;
  f2ptr event_type__funk;
  f2ptr event_type__set__symbol;
  f2ptr event_type__set__funk;
  f2ptr data__symbol;
  f2ptr data__funk;
  f2ptr data__set__symbol;
  f2ptr data__set__funk;
};

// bytecode_event

struct funk2_object_type__bytecode_event__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr bytecode__symbol;
  f2ptr bytecode__funk;
  f2ptr bytecode__set__symbol;
  f2ptr bytecode__set__funk;
  f2ptr context__symbol;
  f2ptr context__funk;
  f2ptr context__set__symbol;
  f2ptr context__set__funk;
};

#endif // F2__PRIMOBJECT__GLOBALENV_STRUCTS


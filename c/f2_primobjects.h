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
typedef struct funk2_object_type__processor__slot_s        funk2_object_type__processor__slot_t;
typedef struct funk2_object_type__scheduler__slot_s        funk2_object_type__scheduler__slot_t;
typedef struct funk2_object_type__transframe__slot_s       funk2_object_type__transframe__slot_t;
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

defarray_slot__prototype(primobject__object_type);
#define f2primobject__object_type__trace_depth(                   this, cause, trace_depth)        array_slot__accessor__trace_depth(         this, primobject__object_type, cause, trace_depth)
#define f2primobject__object_type(                                this, cause)                     array_slot__accessor(                      this, primobject__object_type, cause)
#define f2primobject__object_type__set__trace_depth(              this, cause, value, trace_depth) array_slot__set__trace_depth(              this, primobject__object_type, cause, value, trace_depth)
#define f2primobject__object_type__set(                           this, cause, value)              array_slot__set(                           this, primobject__object_type, cause, value)
#define f2primobject__object_type__tracing_on(                    this, cause)                     array_slot__tracing_on(                    this, primobject__object_type, cause)
#define f2primobject__object_type__trace(                         this, cause)                     array_slot__trace(                         this, primobject__object_type, cause)
#define f2primobject__object_type__imagination_frame(             this, cause)                     array_slot__imagination_frame(             this, primobject__object_type, cause)

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
#include "f2_malloc.h"

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

f2ptr f2__primobject__new(             f2ptr cause, f2ptr object_type, int   static_slot_num, f2ptr dynamic_slots);
f2ptr f2__primobject__new__trace_depth(f2ptr cause, f2ptr object_type, int   static_slot_num, f2ptr dynamic_slots, int trace_depth);
f2ptr   f2primobject__new(             f2ptr cause, f2ptr object_type, f2ptr static_slot_num, f2ptr dynamic_slots);

f2ptr f2primobject__primobject_type__new(f2ptr cause);

#define declare_primobject_common(name) \
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr x); \
  f2ptr f2__##name##__is_type(f2ptr cause, f2ptr x); \
  f2ptr f2##name##__primobject_type__new(f2ptr cause); \
  static inline boolean_t f2primobject__is__##name(f2ptr this, f2ptr cause) {return raw__eq(cause, f2primobject__object_type(this, cause), __##name##__symbol);}

#define debug_type_check(cause, this, name) debug__assert(raw__##name##__is_type(cause, this), nil, "debug error: this is not a " #name ".")

#define declare_primobject_slot(name, slot_name) \
  defprimobject__static_slot__prototype(name##__##slot_name); \
  static inline f2ptr f2##name##__##slot_name##__trace_depth(      f2ptr this, f2ptr cause, int trace_depth)              {debug_type_check(cause, this, name); return primobject__static_slot__accessor__trace_depth(this, name##__##slot_name, cause, trace_depth);} \
  static inline f2ptr f2##name##__##slot_name(                     f2ptr this, f2ptr cause)                               {debug_type_check(cause, this, name); return primobject__static_slot__accessor(             this, name##__##slot_name, cause);} \
  static inline f2ptr f2##name##__##slot_name##__set__trace_depth( f2ptr this, f2ptr cause, f2ptr value, int trace_depth) {debug_type_check(cause, this, name); return primobject__static_slot__set__trace_depth(     this, name##__##slot_name, cause, value, trace_depth);} \
  static inline f2ptr f2##name##__##slot_name##__set(              f2ptr this, f2ptr cause, f2ptr value)                  {debug_type_check(cause, this, name); return primobject__static_slot__set(                  this, name##__##slot_name, cause, value);} \
  static inline f2ptr f2##name##__##slot_name##__tracing_on(       f2ptr this, f2ptr cause)                               {debug_type_check(cause, this, name); return primobject__static_slot__tracing_on(           this, name##__##slot_name, cause);} \
  static inline f2ptr f2##name##__##slot_name##__trace(            f2ptr this, f2ptr cause)                               {debug_type_check(cause, this, name); return primobject__static_slot__trace(                this, name##__##slot_name, cause);} \
  static inline f2ptr f2##name##__##slot_name##__imagination_frame(f2ptr this, f2ptr cause)                               {debug_type_check(cause, this, name); return primobject__static_slot__imagination_frame(    this, name##__##slot_name, cause);} \
  f2ptr f2__##name##__##slot_name(f2ptr cause, f2ptr x); \
  f2ptr f2__##name##__##slot_name##__set(f2ptr cause, f2ptr x, f2ptr y);

#define declare_primobject_inline_0_slot(name) \
  declare_primobject_common(name);

#define declare_primobject_inline_1_slot(name, slot_1) \
  declare_primobject_inline_0_slot(name); \
  declare_primobject_slot(name, slot_1);

#define declare_primobject_inline_2_slot(name, slot_1, slot_2) \
  declare_primobject_inline_1_slot(name, slot_1); \
  declare_primobject_slot(name, slot_2);

#define declare_primobject_inline_3_slot(name, slot_1, slot_2, slot_3) \
  declare_primobject_inline_2_slot(name, slot_1, slot_2); \
  declare_primobject_slot(name, slot_3);

#define declare_primobject_inline_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  declare_primobject_inline_3_slot(name, slot_1, slot_2, slot_3); \
  declare_primobject_slot(name, slot_4);

#define declare_primobject_inline_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  declare_primobject_inline_4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  declare_primobject_slot(name, slot_5);

#define declare_primobject_inline_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  declare_primobject_inline_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  declare_primobject_slot(name, slot_6);

#define declare_primobject_inline_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  declare_primobject_inline_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  declare_primobject_slot(name, slot_7);

#define declare_primobject_inline_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  declare_primobject_inline_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  declare_primobject_slot(name, slot_8);

#define declare_primobject_inline_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  declare_primobject_inline_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  declare_primobject_slot(name, slot_9);

#define declare_primobject_inline_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  declare_primobject_inline_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  declare_primobject_slot(name, slot_10);

#define declare_primobject_inline_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  declare_primobject_inline_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  declare_primobject_slot(name, slot_11);

#define declare_primobject_inline_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  declare_primobject_inline_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  declare_primobject_slot(name, slot_12);

#define declare_primobject_inline_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  declare_primobject_inline_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  declare_primobject_slot(name, slot_13);

#define declare_primobject_inline_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  declare_primobject_inline_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  declare_primobject_slot(name, slot_14);

#define declare_primobject_inline_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  declare_primobject_inline_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  declare_primobject_slot(name, slot_15);

#define declare_primobject_inline_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  declare_primobject_inline_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  declare_primobject_slot(name, slot_16);

#define declare_primobject_inline_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  declare_primobject_inline_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  declare_primobject_slot(name, slot_17);

#define declare_primobject_inline_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  declare_primobject_inline_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  declare_primobject_slot(name, slot_18);

#define declare_primobject_inline_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  declare_primobject_inline_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  declare_primobject_slot(name, slot_19);

#define declare_primobject_inline_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  declare_primobject_inline_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  declare_primobject_slot(name, slot_20);

#define declare_primobject_inline_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  declare_primobject_inline_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  declare_primobject_slot(name, slot_21);


#define declare_primobject_1_slot(name, slot_1) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1); \
  declare_primobject_inline_1_slot(name, slot_1);

#define declare_primobject_2_slot(name, slot_1, slot_2) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2); \
  declare_primobject_inline_2_slot(name, slot_1, slot_2);

#define declare_primobject_3_slot(name, slot_1, slot_2, slot_3) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3); \
  declare_primobject_inline_3_slot(name, slot_1, slot_2, slot_3);

#define declare_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4); \
  declare_primobject_inline_4_slot(name, slot_1, slot_2, slot_3, slot_4);

#define declare_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5); \
  declare_primobject_inline_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5);

#define declare_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6); \
  declare_primobject_inline_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6);

#define declare_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7); \
  declare_primobject_inline_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7);

#define declare_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8); \
  declare_primobject_inline_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8);

#define declare_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9); \
  declare_primobject_inline_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9);

#define declare_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10); \
  declare_primobject_inline_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10);

#define declare_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11); \
  declare_primobject_inline_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11);

#define declare_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12); \
  declare_primobject_inline_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12);

#define declare_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13); \
  declare_primobject_inline_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13);

#define declare_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14); \
  declare_primobject_inline_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14);

#define declare_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15); \
  declare_primobject_inline_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15);

#define declare_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16); \
  declare_primobject_inline_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16);

#define declare_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17); \
  declare_primobject_inline_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17);

#define declare_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18); \
  declare_primobject_inline_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18);

#define declare_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19); \
  declare_primobject_inline_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19);

#define declare_primobject_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20); \
  declare_primobject_inline_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20);

#define declare_primobject_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  extern f2ptr __##name##__symbol; \
  f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, int trace_depth); \
  f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21); \
  declare_primobject_inline_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21);





#define def_primobject_static_slot(name, slot_number, slot_name) \
  defprimobject__static_slot(name##__##slot_name, slot_number); \
   \
  f2ptr f2__##name##__##slot_name(f2ptr cause, f2ptr x) {return f2##name##__##slot_name(x, cause);} \
  def_pcfunk1(name##__##slot_name, x, return f2__##name##__##slot_name(this_cause, x)); \
   \
  f2ptr f2__##name##__##slot_name##__set(f2ptr cause, f2ptr x, f2ptr y) {f2##name##__##slot_name##__set(x, cause, y); return nil;} \
  def_pcfunk2(name##__##slot_name##__set, x, y, return f2__##name##__##slot_name##__set(this_cause, x, y));


#define def_primobject_common(name, new_trace_depth_code, new_f2type_code, add_slots_code) \
  f2ptr __##name##__symbol = -1; \
   \
  new_trace_depth_code; \
   \
  new_f2type_code; \
   \
  boolean_t raw__##name##__is_type(f2ptr cause, f2ptr x) { \
    return (raw__primobject__is_type(cause, x) && f2primobject__is__##name(x, cause)); \
  } \
  f2ptr f2__##name##__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__##name##__is_type(cause, x));} \
  def_pcfunk1(name##__is_type, x, return f2__##name##__is_type(this_cause, x)); \
   \
  f2ptr f2__##name##__type(f2ptr cause, f2ptr x) {return __##name##__symbol;} \
  def_pcfunk1(name##__type, x, return f2__##name##__type(this_cause, x)); \
   \
  f2ptr f2##name##__primobject_type__new(f2ptr cause) { \
    f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("primobject"), (u8*)"primobject"), nil)); \
    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), __funk2.globalenv.object_type.primobject.primobject_type_##name.is_type__funk); \
    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    __funk2.globalenv.object_type.primobject.primobject_type_##name.type__funk); \
    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     __funk2.globalenv.object_type.primobject.primobject_type_##name.new__funk); \
    add_slots_code; \
    return this; \
  }

#define def_primobject_add_slot(name, slot_name) \
  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, #slot_name),   __funk2.globalenv.object_type.primobject.primobject_type_##name.slot_name##__funk); \
  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, #slot_name),   __funk2.globalenv.object_type.primobject.primobject_type_##name.slot_name##__set__funk); \

#define def_primobject_static_0_slot(name)

#define def_primobject_static_1_slot(name, slot_1) \
  def_primobject_static_0_slot(name) \
  def_primobject_static_slot(name, 0, slot_1);

#define def_primobject_static_2_slot(name, slot_1, slot_2) \
  def_primobject_static_1_slot(name, slot_1); \
  def_primobject_static_slot(name, 1, slot_2);

#define def_primobject_static_3_slot(name, slot_1, slot_2, slot_3) \
  def_primobject_static_2_slot(name, slot_1, slot_2); \
  def_primobject_static_slot(name, 2, slot_3);

#define def_primobject_static_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_primobject_static_3_slot(name, slot_1, slot_2, slot_3); \
  def_primobject_static_slot(name, 3, slot_4);

#define def_primobject_static_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_primobject_static_4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  def_primobject_static_slot(name, 4, slot_5);

#define def_primobject_static_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_primobject_static_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  def_primobject_static_slot(name, 5, slot_6);

#define def_primobject_static_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_primobject_static_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  def_primobject_static_slot(name, 6, slot_7);

#define def_primobject_static_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_primobject_static_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  def_primobject_static_slot(name, 7, slot_8);

#define def_primobject_static_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_primobject_static_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  def_primobject_static_slot(name, 8, slot_9);

#define def_primobject_static_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_primobject_static_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  def_primobject_static_slot(name, 9, slot_10);

#define def_primobject_static_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_primobject_static_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  def_primobject_static_slot(name, 10, slot_11);

#define def_primobject_static_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_primobject_static_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  def_primobject_static_slot(name, 11, slot_12);

#define def_primobject_static_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_primobject_static_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  def_primobject_static_slot(name, 12, slot_13);

#define def_primobject_static_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_primobject_static_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  def_primobject_static_slot(name, 13, slot_14);

#define def_primobject_static_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_primobject_static_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  def_primobject_static_slot(name, 14, slot_15);

#define def_primobject_static_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_primobject_static_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  def_primobject_static_slot(name, 15, slot_16);

#define def_primobject_static_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_primobject_static_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  def_primobject_static_slot(name, 16, slot_17);

#define def_primobject_static_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_primobject_static_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  def_primobject_static_slot(name, 17, slot_18);

#define def_primobject_static_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_primobject_static_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  def_primobject_static_slot(name, 18, slot_19);

#define def_primobject_static_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_primobject_static_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  def_primobject_static_slot(name, 19, slot_20);

#define def_primobject_static_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_primobject_static_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  def_primobject_static_slot(name, 20, slot_21);


#define def_primobject__0_slot__set__trace_depth(name)

#define def_primobject__1_slot__set__trace_depth(name, slot_1) \
  def_primobject__0_slot__set__trace_depth(name) \
  f2##name##__##slot_1##__set__trace_depth(this, cause, slot_1, trace_depth);

#define def_primobject__2_slot__set__trace_depth(name, slot_1, slot_2) \
  def_primobject__1_slot__set__trace_depth(name, slot_1) \
  f2##name##__##slot_2##__set__trace_depth(this, cause, slot_2, trace_depth);

#define def_primobject__3_slot__set__trace_depth(name, slot_1, slot_2, slot_3) \
  def_primobject__2_slot__set__trace_depth(name, slot_1, slot_2) \
  f2##name##__##slot_3##__set__trace_depth(this, cause, slot_3, trace_depth);

#define def_primobject__4_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4) \
  def_primobject__3_slot__set__trace_depth(name, slot_1, slot_2, slot_3) \
  f2##name##__##slot_4##__set__trace_depth(this, cause, slot_4, trace_depth);

#define def_primobject__5_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_primobject__4_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4) \
  f2##name##__##slot_5##__set__trace_depth(this, cause, slot_5, trace_depth);

#define def_primobject__6_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_primobject__5_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  f2##name##__##slot_6##__set__trace_depth(this, cause, slot_6, trace_depth);

#define def_primobject__7_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_primobject__6_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  f2##name##__##slot_7##__set__trace_depth(this, cause, slot_7, trace_depth);

#define def_primobject__8_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_primobject__7_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  f2##name##__##slot_8##__set__trace_depth(this, cause, slot_8, trace_depth);

#define def_primobject__9_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_primobject__8_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  f2##name##__##slot_9##__set__trace_depth(this, cause, slot_9, trace_depth);

#define def_primobject__10_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_primobject__9_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  f2##name##__##slot_10##__set__trace_depth(this, cause, slot_10, trace_depth);

#define def_primobject__11_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_primobject__10_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  f2##name##__##slot_11##__set__trace_depth(this, cause, slot_11, trace_depth);

#define def_primobject__12_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_primobject__11_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  f2##name##__##slot_12##__set__trace_depth(this, cause, slot_12, trace_depth);

#define def_primobject__13_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_primobject__12_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  f2##name##__##slot_13##__set__trace_depth(this, cause, slot_13, trace_depth);

#define def_primobject__14_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_primobject__13_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  f2##name##__##slot_14##__set__trace_depth(this, cause, slot_14, trace_depth);

#define def_primobject__15_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_primobject__14_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  f2##name##__##slot_15##__set__trace_depth(this, cause, slot_15, trace_depth);

#define def_primobject__16_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_primobject__15_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  f2##name##__##slot_16##__set__trace_depth(this, cause, slot_16, trace_depth);

#define def_primobject__17_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_primobject__16_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  f2##name##__##slot_17##__set__trace_depth(this, cause, slot_17, trace_depth);

#define def_primobject__18_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_primobject__17_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  f2##name##__##slot_18##__set__trace_depth(this, cause, slot_18, trace_depth);

#define def_primobject__19_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_primobject__18_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  f2##name##__##slot_19##__set__trace_depth(this, cause, slot_19, trace_depth);

#define def_primobject__20_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_primobject__19_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  f2##name##__##slot_20##__set__trace_depth(this, cause, slot_20, trace_depth);

#define def_primobject__21_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_primobject__20_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  f2##name##__##slot_21##__set__trace_depth(this, cause, slot_21, trace_depth);


#define def_primobject_add_0_slot(name)

#define def_primobject_add_1_slot(name, slot_1) \
  def_primobject_add_0_slot(name); \
  def_primobject_add_slot(name, slot_1);

#define def_primobject_add_2_slot(name, slot_1, slot_2) \
  def_primobject_add_1_slot(name, slot_1); \
  def_primobject_add_slot(name, slot_2);

#define def_primobject_add_3_slot(name, slot_1, slot_2, slot_3) \
  def_primobject_add_2_slot(name, slot_1, slot_2); \
  def_primobject_add_slot(name, slot_3);

#define def_primobject_add_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_primobject_add_3_slot(name, slot_1, slot_2, slot_3); \
  def_primobject_add_slot(name, slot_4);

#define def_primobject_add_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_primobject_add_4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  def_primobject_add_slot(name, slot_5);

#define def_primobject_add_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_primobject_add_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  def_primobject_add_slot(name, slot_6);

#define def_primobject_add_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_primobject_add_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  def_primobject_add_slot(name, slot_7);

#define def_primobject_add_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_primobject_add_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  def_primobject_add_slot(name, slot_8);

#define def_primobject_add_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_primobject_add_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  def_primobject_add_slot(name, slot_9);

#define def_primobject_add_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_primobject_add_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  def_primobject_add_slot(name, slot_10);

#define def_primobject_add_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_primobject_add_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  def_primobject_add_slot(name, slot_11);

#define def_primobject_add_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_primobject_add_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  def_primobject_add_slot(name, slot_12);

#define def_primobject_add_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_primobject_add_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  def_primobject_add_slot(name, slot_13);

#define def_primobject_add_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_primobject_add_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  def_primobject_add_slot(name, slot_14);

#define def_primobject_add_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_primobject_add_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  def_primobject_add_slot(name, slot_15);

#define def_primobject_add_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_primobject_add_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  def_primobject_add_slot(name, slot_16);

#define def_primobject_add_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_primobject_add_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  def_primobject_add_slot(name, slot_17);

#define def_primobject_add_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_primobject_add_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  def_primobject_add_slot(name, slot_18);

#define def_primobject_add_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_primobject_add_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  def_primobject_add_slot(name, slot_19);

#define def_primobject_add_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_primobject_add_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  def_primobject_add_slot(name, slot_20);

#define def_primobject_add_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_primobject_add_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  def_primobject_add_slot(name, slot_21);


#define def_primobject_1_slot(name, slot_1) \
  def_primobject_static_1_slot(name, slot_1); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 1, nil, trace_depth); \
      def_primobject__1_slot__set__trace_depth(name, slot_1); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1) { \
      return f2##name##__new__trace_depth(cause, slot_1, 1); \
    }, \
    def_primobject_add_1_slot(name, slot_1));

#define def_primobject_2_slot(name, slot_1, slot_2) \
  def_primobject_static_2_slot(name, slot_1, slot_2); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 2, nil, trace_depth); \
      def_primobject__2_slot__set__trace_depth(name, slot_1, slot_2); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, 1); \
    }, \
    def_primobject_add_2_slot(name, slot_1, slot_2));

#define def_primobject_3_slot(name, slot_1, slot_2, slot_3) \
  def_primobject_static_3_slot(name, slot_1, slot_2, slot_3); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 3, nil, trace_depth); \
      def_primobject__3_slot__set__trace_depth(name, slot_1, slot_2, slot_3); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, 1); \
    }, \
    def_primobject_add_3_slot(name, slot_1, slot_2, slot_3));

#define def_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  def_primobject_static_4_slot(name, slot_1, slot_2, slot_3, slot_4); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 4, nil, trace_depth); \
      def_primobject__4_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, 1); \
    }, \
    def_primobject_add_4_slot(name, slot_1, slot_2, slot_3, slot_4));

#define def_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  def_primobject_static_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 5, nil, trace_depth); \
      def_primobject__5_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, 1); \
    }, \
    def_primobject_add_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5));

#define def_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  def_primobject_static_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 6, nil, trace_depth); \
      def_primobject__6_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, 1); \
    }, \
    def_primobject_add_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6));

#define def_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  def_primobject_static_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 7, nil, trace_depth); \
      def_primobject__7_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, 1); \
    }, \
    def_primobject_add_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7));

#define def_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  def_primobject_static_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 8, nil, trace_depth); \
      def_primobject__8_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, 1); \
    }, \
    def_primobject_add_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8));

#define def_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  def_primobject_static_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 9, nil, trace_depth); \
      def_primobject__9_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, 1); \
    }, \
    def_primobject_add_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9));

#define def_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  def_primobject_static_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 10, nil, trace_depth); \
      def_primobject__10_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, 1); \
    }, \
    def_primobject_add_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10));

#define def_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  def_primobject_static_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 11, nil, trace_depth); \
      def_primobject__11_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, 1); \
    }, \
    def_primobject_add_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11));

#define def_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  def_primobject_static_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 12, nil, trace_depth); \
      def_primobject__12_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, 1); \
    }, \
    def_primobject_add_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12));

#define def_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  def_primobject_static_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 13, nil, trace_depth); \
      def_primobject__13_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, 1); \
    }, \
    def_primobject_add_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13));

#define def_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  def_primobject_static_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 14, nil, trace_depth); \
      def_primobject__14_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, 1); \
    }, \
    def_primobject_add_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14));

#define def_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  def_primobject_static_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 15, nil, trace_depth); \
      def_primobject__15_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, 1); \
    }, \
    def_primobject_add_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15));

#define def_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  def_primobject_static_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 16, nil, trace_depth); \
      def_primobject__16_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, 1); \
    }, \
    def_primobject_add_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16));

#define def_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  def_primobject_static_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 17, nil, trace_depth); \
      def_primobject__17_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, 1); \
    }, \
    def_primobject_add_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17));

#define def_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  def_primobject_static_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 18, nil, trace_depth); \
      def_primobject__18_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, 1); \
    }, \
    def_primobject_add_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18));

#define def_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  def_primobject_static_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 19, nil, trace_depth); \
      def_primobject__19_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, 1); \
    }, \
    def_primobject_add_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19));

#define def_primobject_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  def_primobject_static_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 20, nil, trace_depth); \
      def_primobject__20_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, 1); \
    }, \
    def_primobject_add_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20));

#define def_primobject_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  def_primobject_static_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
   \
  def_primobject_common(name, \
    f2ptr f2##name##__new__trace_depth(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21, int trace_depth) { \
      release__assert(__##name##__symbol != -1, nil, "f2" #name "__new error: used before primobjects initialized."); \
      f2ptr this = f2__primobject__new__trace_depth(cause, __##name##__symbol, 21, nil, trace_depth); \
      def_primobject__21_slot__set__trace_depth(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
      return this; \
    }, \
    f2ptr f2##name##__new(f2ptr cause, f2ptr slot_1, f2ptr slot_2, f2ptr slot_3, f2ptr slot_4, f2ptr slot_5, f2ptr slot_6, f2ptr slot_7, f2ptr slot_8, f2ptr slot_9, f2ptr slot_10, f2ptr slot_11, f2ptr slot_12, f2ptr slot_13, f2ptr slot_14, f2ptr slot_15, f2ptr slot_16, f2ptr slot_17, f2ptr slot_18, f2ptr slot_19, f2ptr slot_20, f2ptr slot_21) { \
      return f2##name##__new__trace_depth(cause, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, 1); \
    }, \
    def_primobject_add_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21));


#define stringify(x) #x
#define tostring(x) stringify(x)

#define initialize_primobject_funk__0_arg(name, funk_name, documentation) \
  {char* symbol_str = #funk_name; __funk2.globalenv.object_type.primobject.primobject_type_##name.funk_name##__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);} \
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(name##__##funk_name, this, cfunk, 0, documentation "  (cfunk " __FILE__ ":" tostring(__LINE__) ")"); __funk2.globalenv.object_type.primobject.primobject_type_##name.funk_name##__funk = never_gc(cfunk);}

#define initialize_primobject_funk__1_arg(name, funk_name, arg_1, documentation) \
  {char* symbol_str = #funk_name; __funk2.globalenv.object_type.primobject.primobject_type_##name.funk_name##__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);} \
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(name##__##funk_name, this, arg_1, cfunk, 0, documentation "  (cfunk " __FILE__ ":" tostring(__LINE__) ")"); __funk2.globalenv.object_type.primobject.primobject_type_##name.funk_name##__funk = never_gc(cfunk);}


#define initialize_primobject_funk(name, funk_name) \
  initialize_primobject_funk__0_arg(name, funk_name, "");

#define initialize_primobject_common(name)   \
  initialize_primobject_funk(name, is_type); \
  initialize_primobject_funk(name, type); \
  initialize_primobject_funk(name, new);

#define initialize_primobject_slot(name, slot_name) \
  initialize_primobject_funk(name, slot_name); \
  initialize_primobject_funk(name, slot_name##__set);

#define initialize_primobject_0_slot(name) \
  initialize_primobject_common(name);

#define initialize_primobject_1_slot(name, slot_1) \
  initialize_primobject_0_slot(name); \
  initialize_primobject_slot(name, slot_1);

#define initialize_primobject_2_slot(name, slot_1, slot_2) \
  initialize_primobject_1_slot(name, slot_1); \
  initialize_primobject_slot(name, slot_2);

#define initialize_primobject_3_slot(name, slot_1, slot_2, slot_3) \
  initialize_primobject_2_slot(name, slot_1, slot_2); \
  initialize_primobject_slot(name, slot_3);

#define initialize_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4) \
  initialize_primobject_3_slot(name, slot_1, slot_2, slot_3); \
  initialize_primobject_slot(name, slot_4);

#define initialize_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5) \
  initialize_primobject_4_slot(name, slot_1, slot_2, slot_3, slot_4); \
  initialize_primobject_slot(name, slot_5);

#define initialize_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  initialize_primobject_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5); \
  initialize_primobject_slot(name, slot_6);

#define initialize_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  initialize_primobject_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
  initialize_primobject_slot(name, slot_7);

#define initialize_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  initialize_primobject_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
  initialize_primobject_slot(name, slot_8);

#define initialize_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  initialize_primobject_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
  initialize_primobject_slot(name, slot_9);

#define initialize_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  initialize_primobject_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
  initialize_primobject_slot(name, slot_10);

#define initialize_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  initialize_primobject_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
  initialize_primobject_slot(name, slot_11);

#define initialize_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  initialize_primobject_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
  initialize_primobject_slot(name, slot_12);

#define initialize_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  initialize_primobject_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
  initialize_primobject_slot(name, slot_13);

#define initialize_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  initialize_primobject_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
  initialize_primobject_slot(name, slot_14);

#define initialize_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  initialize_primobject_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
  initialize_primobject_slot(name, slot_15);

#define initialize_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  initialize_primobject_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
  initialize_primobject_slot(name, slot_16);

#define initialize_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  initialize_primobject_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
  initialize_primobject_slot(name, slot_17);

#define initialize_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  initialize_primobject_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
  initialize_primobject_slot(name, slot_18);

#define initialize_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  initialize_primobject_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
  initialize_primobject_slot(name, slot_19);

#define initialize_primobject_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  initialize_primobject_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
  initialize_primobject_slot(name, slot_20);

#define initialize_primobject_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  initialize_primobject_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
  initialize_primobject_slot(name, slot_21);



// compound_object

declare_primobject_3_slot(compound_object, compound_object_type, frame, part_frame);

// primobject_type

declare_primobject_1_slot(primobject_type, parents);

// place

declare_primobject_1_slot(place, thing);

// cons

declare_primobject_2_slot(cons, car, cdr);

f2ptr f2cons__primobject_type__new_aux(f2ptr cause);

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

f2ptr f2__doublelink(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value);
f2ptr f2__doublelink__new(f2ptr cause, f2ptr prev, f2ptr next, f2ptr value);


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


// processor

declare_primobject_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc);


// scheduler

declare_primobject_1_slot(scheduler, processors);


// transframe

declare_primobject_2_slot(transframe, nanoseconds_since_1970, symbol_old_news);


// time

declare_primobject_1_slot(time, nanoseconds_since_1970);

f2ptr f2__time__new(f2ptr cause, f2ptr nanoseconds_since_1970);
f2ptr f2time__primobject_type__new_aux(f2ptr cause);


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

#define declare_object_type_vars_0_slot()

#define declare_object_type_vars_1_slot(slot_1) \
  declare_object_type_vars_0_slot() \
  declare_object_type_slot(slot_1);

#define declare_object_type_vars_2_slot(slot_1, slot_2) \
  declare_object_type_vars_1_slot(slot_1) \
  declare_object_type_slot(slot_2);

#define declare_object_type_vars_3_slot(slot_1, slot_2, slot_3) \
  declare_object_type_vars_2_slot(slot_1, slot_2) \
  declare_object_type_slot(slot_3);

#define declare_object_type_vars_4_slot(slot_1, slot_2, slot_3, slot_4) \
  declare_object_type_vars_3_slot(slot_1, slot_2, slot_3) \
  declare_object_type_slot(slot_4);

#define declare_object_type_vars_5_slot(slot_1, slot_2, slot_3, slot_4, slot_5) \
  declare_object_type_vars_4_slot(slot_1, slot_2, slot_3, slot_4) \
  declare_object_type_slot(slot_5);

#define declare_object_type_vars_6_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  declare_object_type_vars_5_slot(slot_1, slot_2, slot_3, slot_4, slot_5) \
  declare_object_type_slot(slot_6);

#define declare_object_type_vars_7_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  declare_object_type_vars_6_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6) \
  declare_object_type_slot(slot_7);

#define declare_object_type_vars_8_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  declare_object_type_vars_7_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7) \
  declare_object_type_slot(slot_8);

#define declare_object_type_vars_9_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  declare_object_type_vars_8_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8) \
  declare_object_type_slot(slot_9);

#define declare_object_type_vars_10_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  declare_object_type_vars_9_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9) \
  declare_object_type_slot(slot_10);

#define declare_object_type_vars_11_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  declare_object_type_vars_10_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10) \
  declare_object_type_slot(slot_11);

#define declare_object_type_vars_12_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  declare_object_type_vars_11_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11) \
  declare_object_type_slot(slot_12);

#define declare_object_type_vars_13_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  declare_object_type_vars_12_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12) \
  declare_object_type_slot(slot_13);

#define declare_object_type_vars_14_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  declare_object_type_vars_13_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13) \
  declare_object_type_slot(slot_14);

#define declare_object_type_vars_15_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  declare_object_type_vars_14_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14) \
  declare_object_type_slot(slot_15);

#define declare_object_type_vars_16_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  declare_object_type_vars_15_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15) \
  declare_object_type_slot(slot_16);

#define declare_object_type_vars_17_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  declare_object_type_vars_16_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16) \
  declare_object_type_slot(slot_17);

#define declare_object_type_vars_18_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  declare_object_type_vars_17_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17) \
  declare_object_type_slot(slot_18);

#define declare_object_type_vars_19_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  declare_object_type_vars_18_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18) \
  declare_object_type_slot(slot_19);

#define declare_object_type_vars_20_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  declare_object_type_vars_19_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19) \
  declare_object_type_slot(slot_20);

#define declare_object_type_vars_21_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21) \
  declare_object_type_vars_20_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20) \
  declare_object_type_slot(slot_21);


#define declare_object_type_1_slot(name, slot_1, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_1_slot(slot_1); \
    body)

#define declare_object_type_2_slot(name, slot_1, slot_2, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_2_slot(slot_1, slot_2); \
    body)

#define declare_object_type_3_slot(name, slot_1, slot_2, slot_3, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_3_slot(slot_1, slot_2, slot_3); \
    body)

#define declare_object_type_4_slot(name, slot_1, slot_2, slot_3, slot_4, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_4_slot(slot_1, slot_2, slot_3, slot_4); \
    body)

#define declare_object_type_5_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_5_slot(slot_1, slot_2, slot_3, slot_4, slot_5); \
    body)

#define declare_object_type_6_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_6_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6); \
    body)

#define declare_object_type_7_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_7_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7); \
    body)

#define declare_object_type_8_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_8_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8); \
    body)

#define declare_object_type_9_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_9_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9); \
    body)

#define declare_object_type_10_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_10_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10); \
    body)

#define declare_object_type_11_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_11_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11); \
    body)

#define declare_object_type_12_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_12_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12); \
    body)

#define declare_object_type_13_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_13_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13); \
    body)

#define declare_object_type_14_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_14_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14); \
    body)

#define declare_object_type_15_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_15_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15); \
    body)

#define declare_object_type_16_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_16_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16); \
    body)

#define declare_object_type_17_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_17_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17); \
    body)

#define declare_object_type_18_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_18_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18); \
    body)

#define declare_object_type_19_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_19_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19); \
    body)

#define declare_object_type_20_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_20_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20); \
    body)

#define declare_object_type_21_slot(name, slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21, body) \
  declare_object_type_common(name, \
    declare_object_type_vars_21_slot(slot_1, slot_2, slot_3, slot_4, slot_5, slot_6, slot_7, slot_8, slot_9, slot_10, slot_11, slot_12, slot_13, slot_14, slot_15, slot_16, slot_17, slot_18, slot_19, slot_20, slot_21); \
    body)

// compound_object

declare_object_type_3_slot(compound_object, compound_object_type, frame, part_frame, );

// place

declare_object_type_1_slot(place, thing, );

// cons

declare_object_type_2_slot(cons, car, cdr,
			   f2ptr length__symbol;
			   f2ptr length__funk;
			   );

f2ptr f2__cons__new(f2ptr cause, f2ptr x, f2ptr y);

// doublelink

declare_object_type_3_slot(doublelink, prev, next, value, );

// imagination_link

declare_object_type_5_slot(imagination_link, next, name, value, trace, imagination_frame, );

// cfunk

declare_object_type_6_slot(cfunk, name, args, cfunkptr, env, is_funktional, documentation, );

// metrocfunk

declare_object_type_6_slot(metrocfunk, name, args, cfunkptr, env, is_funktional, documentation, );

// funk

declare_object_type_9_slot(funk, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation, );

// metro

declare_object_type_9_slot(metro, name, body_bytecodes, args, demetropolized_body, body, env, machine_code, is_funktional, documentation, );

// exception

declare_object_type_2_slot(exception, tag, value, );

// bytecode

declare_object_type_4_slot(bytecode, command, arg0, arg1, arg2, );

// processor

declare_object_type_11_slot(processor, scheduler, processor_thread, active_fibers_mutex, active_fibers, active_fibers_iter, active_fibers_prev, active_fibers_next, sleeping_fibers_mutex, sleeping_fibers, pool_index, desc, );

// scheduler

declare_object_type_1_slot(scheduler, processors, );

// transframe

declare_object_type_2_slot(transframe, nanoseconds_since_1970, symbol_old_news, );

// time

declare_object_type_1_slot(time, nanoseconds_since_1970,
			   f2ptr equals__symbol;
			   f2ptr equals__funk;
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
			   f2ptr is_less_than__symbol;
			   f2ptr is_less_than__funk;
			   f2ptr is_greater_than__symbol;
			   f2ptr is_greater_than__funk;
			   f2ptr is_numerically_equal_to__symbol;
			   f2ptr is_numerically_equal_to__funk;
			   );

boolean_t raw__time__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__time__equals(f2ptr cause, f2ptr this, f2ptr that);
u64       raw__time__years(f2ptr cause, f2ptr this);
f2ptr      f2__time__years(f2ptr cause, f2ptr this);
u64       raw__time__months(f2ptr cause, f2ptr this);
f2ptr      f2__time__months(f2ptr cause, f2ptr this);
u64       raw__time__days(f2ptr cause, f2ptr this);
f2ptr      f2__time__days(f2ptr cause, f2ptr this);
u64       raw__time__hours(f2ptr cause, f2ptr this);
f2ptr      f2__time__hours(f2ptr cause, f2ptr this);
u64       raw__time__minutes(f2ptr cause, f2ptr this);
f2ptr      f2__time__minutes(f2ptr cause, f2ptr this);
u64       raw__time__seconds(f2ptr cause, f2ptr this);
f2ptr      f2__time__seconds(f2ptr cause, f2ptr this);
u64       raw__time__nanoseconds(f2ptr cause, f2ptr this);
f2ptr      f2__time__nanoseconds(f2ptr cause, f2ptr this);

// size_2d

declare_object_type_2_slot(size_2d, x, y, );

// event

declare_object_type_4_slot(event, node_id, event_id, event_type, data, );

// bytecode_event

declare_object_type_2_slot(bytecode_event, bytecode, context, );

#endif // F2__PRIMOBJECT__GLOBALENV_STRUCTS


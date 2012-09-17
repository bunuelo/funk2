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

#ifndef F2__PTYPES_OBJECT_SLOTS__H
#define F2__PTYPES_OBJECT_SLOTS__H

// ptype

boolean_t raw__ptype__is_type            (f2ptr cause, f2ptr thing);
f2ptr      f2__ptype__is_type            (f2ptr cause, f2ptr thing);
f2ptr      f2__ptype__type               (f2ptr cause, f2ptr this);
f2ptr      f2__ptype__raw                (f2ptr cause, f2ptr x);
f2ptr     raw__ptype__cause              (f2ptr cause, f2ptr this);
f2ptr      f2__ptype__cause              (f2ptr cause, f2ptr x);
f2ptr      f2__ptype__cause__set         (f2ptr cause, f2ptr x, f2ptr value);
f2ptr      f2__ptype__creation_fiber     (f2ptr cause, f2ptr x);
f2ptr      f2__ptype__creation_fiber__set(f2ptr cause, f2ptr x, f2ptr value);

f2ptr f2ptype__primobject_type__new(f2ptr cause);


// integer

boolean_t raw__integer__is_type(f2ptr cause, f2ptr x);
f2ptr f2__integer__is_type(f2ptr cause, f2ptr x);
f2ptr f2__integer__type(f2ptr cause, f2ptr this);
boolean_t raw__integer__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__integer__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__integer__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__integer__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__integer__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__integer__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__integer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__integer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__integer__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__integer__equals_hash_value(f2ptr cause, f2ptr this);
double raw__integer__as__double(f2ptr cause, f2ptr this);
f2ptr f2__integer__as__double(f2ptr cause, f2ptr this);
ptr raw__integer__as__pointer(f2ptr cause, f2ptr this);
f2ptr f2__integer__as__pointer(f2ptr cause, f2ptr this);
f2ptr f2__integer__multiplied_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__integer__divided_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__integer__plus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__integer__minus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__integer__is_greater_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__integer__is_less_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__integer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);
f2ptr raw__integer__square_root(f2ptr cause, f2ptr this);
f2ptr f2__integer__square_root(f2ptr cause, f2ptr this);
f2ptr raw__integer__modulo(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__integer__modulo(f2ptr cause, f2ptr this, f2ptr that);
f2ptr raw__integer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__integer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__integer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2integer__primobject_type__new(f2ptr cause);


// double

boolean_t raw__double__is_type(f2ptr cause, f2ptr x);
f2ptr f2__double__is_type(f2ptr cause, f2ptr x);
f2ptr f2__double__type(f2ptr cause, f2ptr this);
boolean_t raw__double__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__double__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__double__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__double__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__double__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__double__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__double__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__double__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__double__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__double__equals_hash_value(f2ptr cause, f2ptr this);
double raw__double__as__double(f2ptr cause, f2ptr this);
f2ptr f2__double__as__double(f2ptr cause, f2ptr this);
f2ptr f2__double__multiplied_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__double__divided_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__double__plus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__double__minus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__double__is_greater_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__double__is_less_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__double__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);
f2ptr raw__double__square_root(f2ptr cause, f2ptr this);
f2ptr f2__double__square_root(f2ptr cause, f2ptr this);
f2ptr raw__double__radian_sine(f2ptr cause, f2ptr this);
f2ptr f2__double__radian_sine(f2ptr cause, f2ptr this);
f2ptr raw__double__radian_arcsine(f2ptr cause, f2ptr this);
f2ptr f2__double__radian_arcsine(f2ptr cause, f2ptr this);
f2ptr raw__double__radian_cosine(f2ptr cause, f2ptr this);
f2ptr f2__double__radian_cosine(f2ptr cause, f2ptr this);
f2ptr raw__double__radian_arccosine(f2ptr cause, f2ptr this);
f2ptr f2__double__radian_arccosine(f2ptr cause, f2ptr this);
f2ptr raw__double__radian_tangent(f2ptr cause, f2ptr this);
f2ptr f2__double__radian_tangent(f2ptr cause, f2ptr this);
f2ptr raw__double__radian_arctangent(f2ptr cause, f2ptr this);
f2ptr f2__double__radian_arctangent(f2ptr cause, f2ptr this);
f2ptr raw__double__power(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__double__power(f2ptr cause, f2ptr this, f2ptr that);
f2ptr raw__double__modulo(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__double__modulo(f2ptr cause, f2ptr this, f2ptr that);
f2ptr raw__double__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__double__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__double__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);
f2ptr f2__double__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot);

f2ptr f2double__primobject_type__new(f2ptr cause);


// float

boolean_t raw__float__is_type(f2ptr cause, f2ptr x);
f2ptr f2__float__is_type(f2ptr cause, f2ptr x);
f2ptr f2__float__type(f2ptr cause, f2ptr this);
boolean_t raw__float__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__float__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__float__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__float__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__float__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__float__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__float__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__float__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__float__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__float__equals_hash_value(f2ptr cause, f2ptr this);
double raw__float__as__double(f2ptr cause, f2ptr this);
f2ptr f2__float__as__double(f2ptr cause, f2ptr this);
f2ptr f2__float__multiplied_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__float__divided_by(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__float__plus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__float__minus(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__float__is_greater_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__float__is_less_than(f2ptr cause, f2ptr this, f2ptr number);
f2ptr f2__float__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr number);
f2ptr raw__float__square_root(f2ptr cause, f2ptr this);
f2ptr f2__float__square_root(f2ptr cause, f2ptr this);
f2ptr raw__float__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__float__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__float__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2float__primobject_type__new(f2ptr cause);


// pointer

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr x);
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr x);
f2ptr f2__pointer__type(f2ptr cause, f2ptr this);
boolean_t raw__pointer__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__pointer__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__pointer__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__pointer__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__pointer__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__pointer__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__pointer__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__pointer__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__pointer__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__pointer__plus(f2ptr cause, f2ptr this, f2ptr integer);
f2ptr f2__pointer__minus(f2ptr cause, f2ptr this, f2ptr integer);
f2ptr f2__pointer__is_greater_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__pointer__is_less_than(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__pointer__is_numerically_equal_to(f2ptr cause, f2ptr this, f2ptr that);
f2ptr raw__pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__pointer__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__pointer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2pointer__primobject_type__new(f2ptr cause);


// scheduler_cmutex

boolean_t raw__scheduler_cmutex__is_type(f2ptr cause, f2ptr x);
f2ptr f2__scheduler_cmutex__is_type(f2ptr cause, f2ptr x);
f2ptr f2__scheduler_cmutex__type(f2ptr cause, f2ptr x);
f2ptr f2__scheduler_cmutex__new(f2ptr cause);
boolean_t raw__scheduler_cmutex__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__scheduler_cmutex__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__scheduler_cmutex__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__scheduler_cmutex__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__scheduler_cmutex__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__scheduler_cmutex__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__scheduler_cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__scheduler_cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__scheduler_cmutex__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__scheduler_cmutex__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr raw__scheduler_cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__scheduler_cmutex__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__scheduler_cmutex__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2scheduler_cmutex__primobject_type__new(f2ptr cause);


// cmutex

boolean_t raw__cmutex__is_type                     (f2ptr cause, f2ptr x);
f2ptr      f2__cmutex__is_type                     (f2ptr cause, f2ptr x);
f2ptr      f2__cmutex__type                        (f2ptr cause, f2ptr x);
f2ptr      f2__cmutex__new                         (f2ptr cause);
boolean_t raw__cmutex__is_locked                   (f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__is_locked                   (f2ptr cause, f2ptr this);
void      raw__cmutex__lock                        (f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__lock                        (f2ptr cause, f2ptr this);
void      raw__cmutex__unlock                      (f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__unlock                      (f2ptr cause, f2ptr this);
boolean_t raw__cmutex__trylock                     (f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__trylock                     (f2ptr cause, f2ptr this);
boolean_t raw__cmutex__eq                          (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__cmutex__eq                          (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__cmutex__eq_hash_value               (f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__eq_hash_value               (f2ptr cause, f2ptr this);
boolean_t raw__cmutex__equals                      (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__cmutex__equals                      (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr      f2__cmutex__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64       raw__cmutex__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr      f2__cmutex__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr     raw__cmutex__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__cmutex__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__cmutex__slot__type_funk             (f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2cmutex__primobject_type__new(f2ptr cause);


// scheduler_creadwritelock

boolean_t raw__scheduler_creadwritelock__is_type                     (f2ptr cause, f2ptr x);
f2ptr      f2__scheduler_creadwritelock__is_type                     (f2ptr cause, f2ptr x);
f2ptr      f2__scheduler_creadwritelock__type                        (f2ptr cause, f2ptr x);
f2ptr      f2__scheduler_creadwritelock__new                         (f2ptr cause);
boolean_t raw__scheduler_creadwritelock__is_writelocked              (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__is_writelocked              (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__is_readlocked               (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__is_readlocked               (f2ptr cause, f2ptr this);
void      raw__scheduler_creadwritelock__writelock                   (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__writelock                   (f2ptr cause, f2ptr this);
void      raw__scheduler_creadwritelock__readlock                    (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__readlock                    (f2ptr cause, f2ptr this);
void      raw__scheduler_creadwritelock__unlock                      (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__unlock                      (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__trywritelock                (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__trywritelock                (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__tryreadlock                 (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__tryreadlock                 (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__eq                          (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_creadwritelock__eq                          (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__scheduler_creadwritelock__eq_hash_value               (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__eq_hash_value               (f2ptr cause, f2ptr this);
boolean_t raw__scheduler_creadwritelock__equals                      (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__scheduler_creadwritelock__equals                      (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__scheduler_creadwritelock__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr      f2__scheduler_creadwritelock__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64       raw__scheduler_creadwritelock__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr      f2__scheduler_creadwritelock__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr     raw__scheduler_creadwritelock__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__scheduler_creadwritelock__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__scheduler_creadwritelock__slot__type_funk             (f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2scheduler_creadwritelock__primobject_type__new(f2ptr cause);


// creadwritelock

boolean_t raw__creadwritelock__is_type                     (f2ptr cause, f2ptr x);
f2ptr      f2__creadwritelock__is_type                     (f2ptr cause, f2ptr x);
f2ptr      f2__creadwritelock__type                        (f2ptr cause, f2ptr x);
f2ptr      f2__creadwritelock__new                         (f2ptr cause);
boolean_t raw__creadwritelock__is_writelocked              (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__is_writelocked              (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__is_readlocked               (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__is_readlocked               (f2ptr cause, f2ptr this);
void      raw__creadwritelock__writelock                   (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__writelock                   (f2ptr cause, f2ptr this);
void      raw__creadwritelock__readlock                    (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__readlock                    (f2ptr cause, f2ptr this);
void      raw__creadwritelock__unlock                      (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__unlock                      (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__trywritelock                (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__trywritelock                (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__tryreadlock                 (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__tryreadlock                 (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__eq                          (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__creadwritelock__eq                          (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__creadwritelock__eq_hash_value               (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__eq_hash_value               (f2ptr cause, f2ptr this);
boolean_t raw__creadwritelock__equals                      (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__creadwritelock__equals                      (f2ptr cause, f2ptr this, f2ptr that);
u64       raw__creadwritelock__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr      f2__creadwritelock__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64       raw__creadwritelock__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr      f2__creadwritelock__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr     raw__creadwritelock__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__creadwritelock__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__creadwritelock__slot__type_funk             (f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2creadwritelock__primobject_type__new(f2ptr cause);


// char

boolean_t raw__char__is_type(f2ptr cause, f2ptr x);
f2ptr f2__char__is_type(f2ptr cause, f2ptr x);
f2ptr f2__char__type(f2ptr cause, f2ptr this);
f2ptr f2__char__new(f2ptr cause, f2ptr character);
funk2_character_t raw__char__ch(f2ptr cause, f2ptr this);
f2ptr f2__char__ch(f2ptr cause, f2ptr this);
boolean_t raw__char__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__char__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__char__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__char__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__char__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__char__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__char__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__char__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__char__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__char__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr raw__char__string(f2ptr cause, f2ptr this);
f2ptr f2__char__string(f2ptr cause, f2ptr this);
f2ptr raw__char__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__char__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__char__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2char__primobject_type__new(f2ptr cause);


// string

boolean_t raw__string__is_type(f2ptr cause, f2ptr x);
f2ptr f2__string__is_type(f2ptr cause, f2ptr x);
f2ptr f2__string__type(f2ptr cause, f2ptr x);
u64   raw__string__length(f2ptr cause, f2ptr this);
f2ptr  f2__string__length(f2ptr cause, f2ptr this);
void raw__string__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str);
funk2_character_t raw__string__elt(f2ptr cause, f2ptr this, s64 index);
f2ptr f2__string__elt(f2ptr cause, f2ptr this, f2ptr index);
boolean_t raw__string__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__string__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__string__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__string__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__string__new(f2ptr cause, f2ptr str);
u64 raw__string__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__string__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__string__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__string__equals_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__string__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__string__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__string__utf8_length(f2ptr cause, f2ptr this);
void raw__string__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str);
f2size_t raw__utf8_char__parse_character(char* utf8_string, funk2_character_t* result);
f2size_t raw__utf8_char__utf8_length(char* utf8_char);
u64 raw__utf8_string__length(char* utf8_string);
void raw__utf8_string__str_copy(char* utf8_string, funk2_character_t* str);
f2ptr raw__string__new_from_utf8(f2ptr cause, char* utf8_string);
f2ptr raw__string__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__string__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__string__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2string__primobject_type__new(f2ptr cause);


// symbol

void raw__symbol__str_copy(f2ptr cause, f2ptr this, funk2_character_t* str);
boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x);
f2ptr f2__symbol__is_type(f2ptr cause, f2ptr x);
f2ptr f2__symbol__type(f2ptr cause, f2ptr x);
u64   raw__symbol__length(f2ptr cause, f2ptr this);
f2ptr  f2__symbol__length(f2ptr cause, f2ptr this);
f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y);
u64   raw__symbol__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__symbol__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__symbol__new(f2ptr cause, f2ptr str);
boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__symbol__eq(f2ptr cause, f2ptr this, f2ptr that);
boolean_t raw__symbol__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__symbol__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__symbol__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__symbol__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__symbol__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__symbol__equals_hash_value(f2ptr cause, f2ptr this);
u64 raw__symbol__utf8_length(f2ptr cause, f2ptr this);
void raw__symbol__utf8_str_copy(f2ptr cause, f2ptr this, u8* utf8_str);
f2ptr raw__symbol__new_from_utf8(f2ptr cause, char* utf8_string);
f2ptr raw__symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr raw__key_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr raw__type_symbol__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr raw__symbol__as__string(f2ptr cause, f2ptr this);
f2ptr f2__symbol__as__string(f2ptr cause, f2ptr this);
f2ptr f2__symbol__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);
f2ptr f2symbol__primobject_type__new(f2ptr cause);


// chunk

f2ptr raw__chunk__new(f2ptr cause, u64 length);
f2ptr f2__chunk__new(f2ptr cause, f2ptr length);
boolean_t raw__chunk__is_type(f2ptr cause, f2ptr x);
f2ptr f2__chunk__is_type(f2ptr cause, f2ptr x);
f2ptr f2__chunk__type(f2ptr cause, f2ptr x);
u64 raw__chunk__length(f2ptr cause, f2ptr this);
f2ptr f2__chunk__length(f2ptr cause, f2ptr this);
void raw__chunk__str_copy(f2ptr cause, f2ptr this, u8* str);
boolean_t raw__chunk__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__chunk__eq(f2ptr cause, f2ptr this, f2ptr that);
u64   raw__chunk__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__chunk__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__chunk__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__chunk__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__chunk__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__chunk__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__chunk__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__chunk__equals_hash_value(f2ptr cause, f2ptr this);
u8 raw__chunk__bit8__elt(f2ptr cause, f2ptr this, s64 index);
f2ptr f2__chunk__bit8__elt(f2ptr cause, f2ptr this, f2ptr index);
void raw__chunk__bit8__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value);
f2ptr f2__chunk__bit8__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
u16 raw__chunk__bit16__elt(f2ptr cause, f2ptr this, s64 index);
f2ptr f2__chunk__bit16__elt(f2ptr cause, f2ptr this, f2ptr index);
void raw__chunk__bit16__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value);
f2ptr f2__chunk__bit16__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
u32 raw__chunk__bit32__elt(f2ptr cause, f2ptr this, s64 index);
f2ptr f2__chunk__bit32__elt(f2ptr cause, f2ptr this, f2ptr index);
void raw__chunk__bit32__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value);
f2ptr f2__chunk__bit32__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
u64 raw__chunk__bit64__elt(f2ptr cause, f2ptr this, s64 index);
f2ptr f2__chunk__bit64__elt(f2ptr cause, f2ptr this, f2ptr index);
void raw__chunk__bit64__elt__set(f2ptr cause, f2ptr this, s64 index, u64 value);
f2ptr f2__chunk__bit64__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value);
f2ptr raw__chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__chunk__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__chunk__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2chunk__primobject_type__new(f2ptr cause);


// simple_array

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__simple_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__simple_array__type(f2ptr cause, f2ptr x);
f2ptr f2__simple_array__new(f2ptr cause, f2ptr length);
u64 raw__simple_array__length(f2ptr cause, f2ptr this);
f2ptr f2__simple_array__length(f2ptr cause, f2ptr this);
f2ptr raw__simple_array__elt(f2ptr cause, f2ptr this, u64 index);
f2ptr f2__simple_array__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
boolean_t raw__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__simple_array__eq(f2ptr cause, f2ptr this, f2ptr that);
u64   raw__simple_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__simple_array__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__simple_array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr raw__simple_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash);
f2ptr f2__simple_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash);
f2ptr raw__simple_array__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__simple_array__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__simple_array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__simple_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2simple_array__primobject_type__new(f2ptr cause);


// traced_array

boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__type(f2ptr cause, f2ptr x);
f2ptr f2__traced_array__new(f2ptr cause, f2ptr length);
u64   raw__traced_array__length(f2ptr cause, f2ptr this);
f2ptr  f2__traced_array__length(f2ptr cause, f2ptr this);
f2ptr raw__traced_array__elt(f2ptr cause, f2ptr this, u64   index);
f2ptr  f2__traced_array__elt(f2ptr cause, f2ptr this, f2ptr index);
f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__mutate_funks(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__mutate_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
f2ptr f2__traced_array__elt__read_funks(f2ptr cause, f2ptr x, f2ptr y);
f2ptr f2__traced_array__elt__read_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z);
boolean_t raw__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__traced_array__eq(f2ptr cause, f2ptr this, f2ptr that);
u64   raw__traced_array__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr  f2__traced_array__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__traced_array__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr raw__traced_array__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__traced_array__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr raw__traced_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_hash);
f2ptr f2__traced_array__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__traced_array__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__traced_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2traced_array__primobject_type__new(f2ptr cause);



// larva

boolean_t raw__larva__is_type(f2ptr cause, f2ptr x);
f2ptr f2__larva__is_type(f2ptr cause, f2ptr x);
f2ptr f2__larva__type(f2ptr cause, f2ptr x);
u32 raw__larva__larva_type(f2ptr cause, f2ptr this);
f2ptr f2__larva__larva_type(f2ptr cause, f2ptr this);
f2ptr raw__larva__bug(f2ptr cause, f2ptr this);
f2ptr f2__larva__bug(f2ptr cause, f2ptr this);
f2ptr f2__larva__new(f2ptr cause, f2ptr larva_type, f2ptr bug);
boolean_t raw__larva__eq(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__larva__eq(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__larva__eq_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__larva__eq_hash_value(f2ptr cause, f2ptr this);
boolean_t raw__larva__equals(f2ptr cause, f2ptr this, f2ptr that);
f2ptr f2__larva__equals(f2ptr cause, f2ptr this, f2ptr that);
u64 raw__larva__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr f2__larva__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64 raw__larva__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr f2__larva__equals_hash_value(f2ptr cause, f2ptr this);
f2ptr raw__larva__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__larva__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr f2__larva__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);

f2ptr f2larva__primobject_type__new(f2ptr cause);


// gensym

f2ptr raw__gensym(f2ptr cause, s64 initial_string_length, funk2_character_t* initial_string);
f2ptr f2__gensym(f2ptr cause, f2ptr initial_string);
f2ptr raw__gensym__new_from_utf8(f2ptr cause, char* initial_utf8_string);



// **

void f2__ptypes_object_slots__defragment__fix_pointers();
void f2__ptypes_object_slots__reinitialize_globalvars();
void f2__ptypes_object_slots__initialize();

#endif // F2__PTYPES_OBJECT_SLOTS__H

#ifndef F2__PTYPES_OBJECT_SLOTS__TYPES__H
#define F2__PTYPES_OBJECT_SLOTS__TYPES__H

// integer

typedef struct funk2_object_type__integer__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr i__symbol;
  f2ptr i__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr as__double__symbol;
  f2ptr as__double__funk;
  f2ptr as__pointer__symbol;
  f2ptr as__pointer__funk;
  f2ptr as__integer__symbol;
  f2ptr as__integer__funk;
  f2ptr multiplied_by__symbol;
  f2ptr multiplied_by__funk;
  f2ptr divided_by__symbol;
  f2ptr divided_by__funk;
  f2ptr plus__symbol;
  f2ptr plus__funk;
  f2ptr minus__symbol;
  f2ptr minus__funk;
  f2ptr is_greater_than__symbol;
  f2ptr is_greater_than__funk;
  f2ptr is_less_than__symbol;
  f2ptr is_less_than__funk;
  f2ptr is_numerically_equal_to__symbol;
  f2ptr is_numerically_equal_to__funk;
  f2ptr square_root__symbol;
  f2ptr square_root__funk;
  f2ptr modulo__symbol;
  f2ptr modulo__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__integer__slot_t;

// double

typedef struct funk2_object_type__double__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr d__symbol;
  f2ptr d__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr as__double__symbol;
  f2ptr as__double__funk;
  f2ptr multiplied_by__symbol;
  f2ptr multiplied_by__funk;
  f2ptr divided_by__symbol;
  f2ptr divided_by__funk;
  f2ptr plus__symbol;
  f2ptr plus__funk;
  f2ptr minus__symbol;
  f2ptr minus__funk;
  f2ptr is_greater_than__symbol;
  f2ptr is_greater_than__funk;
  f2ptr is_less_than__symbol;
  f2ptr is_less_than__funk;
  f2ptr is_numerically_equal_to__symbol;
  f2ptr is_numerically_equal_to__funk;
  f2ptr square_root__symbol;
  f2ptr square_root__funk;
  f2ptr radian_sine__symbol;
  f2ptr radian_sine__funk;
  f2ptr radian_arcsine__symbol;
  f2ptr radian_arcsine__funk;
  f2ptr radian_cosine__symbol;
  f2ptr radian_cosine__funk;
  f2ptr radian_arccosine__symbol;
  f2ptr radian_arccosine__funk;
  f2ptr radian_tangent__symbol;
  f2ptr radian_tangent__funk;
  f2ptr radian_arctangent__symbol;
  f2ptr radian_arctangent__funk;
  f2ptr power__symbol;
  f2ptr power__funk;
  f2ptr modulo__symbol;
  f2ptr modulo__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__double__slot_t;

// float

typedef struct funk2_object_type__float__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr f__symbol;
  f2ptr f__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr as__double__symbol;
  f2ptr as__double__funk;
  f2ptr multiplied_by__symbol;
  f2ptr multiplied_by__funk;
  f2ptr divided_by__symbol;
  f2ptr divided_by__funk;
  f2ptr plus__symbol;
  f2ptr plus__funk;
  f2ptr minus__symbol;
  f2ptr minus__funk;
  f2ptr is_greater_than__symbol;
  f2ptr is_greater_than__funk;
  f2ptr is_less_than__symbol;
  f2ptr is_less_than__funk;
  f2ptr is_numerically_equal_to__symbol;
  f2ptr is_numerically_equal_to__funk;
  f2ptr square_root__symbol;
  f2ptr square_root__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__float__slot_t;

// pointer

typedef struct funk2_object_type__pointer__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr p__symbol;
  f2ptr p__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr plus__symbol;
  f2ptr plus__funk;
  f2ptr minus__symbol;
  f2ptr minus__funk;
  f2ptr is_greater_than__symbol;
  f2ptr is_greater_than__funk;
  f2ptr is_less_than__symbol;
  f2ptr is_less_than__funk;
  f2ptr is_numerically_equal_to__symbol;
  f2ptr is_numerically_equal_to__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__pointer__slot_t;

// scheduler_cmutex

typedef struct funk2_object_type__scheduler_cmutex__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__scheduler_cmutex__slot_t;

// cmutex

typedef struct funk2_object_type__cmutex__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr is_locked__symbol;
  f2ptr is_locked__funk;
  f2ptr unlock__symbol;
  f2ptr unlock__funk;
  f2ptr trylock__symbol;
  f2ptr trylock__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__cmutex__slot_t;

// scheduler_creadwritelock

typedef struct funk2_object_type__scheduler_creadwritelock__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr is_writelocked__symbol;
  f2ptr is_writelocked__funk;
  f2ptr is_readlocked__symbol;
  f2ptr is_readlocked__funk;
  f2ptr unlock__symbol;
  f2ptr unlock__funk;
  f2ptr trywritelock__symbol;
  f2ptr trywritelock__funk;
  f2ptr tryreadlock__symbol;
  f2ptr tryreadlock__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__scheduler_creadwritelock__slot_t;

// creadwritelock

typedef struct funk2_object_type__creadwritelock__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr is_writelocked__symbol;
  f2ptr is_writelocked__funk;
  f2ptr is_readlocked__symbol;
  f2ptr is_readlocked__funk;
  f2ptr unlock__symbol;
  f2ptr unlock__funk;
  f2ptr trywritelock__symbol;
  f2ptr trywritelock__funk;
  f2ptr tryreadlock__symbol;
  f2ptr tryreadlock__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__creadwritelock__slot_t;

// char

typedef struct funk2_object_type__char__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr ch__symbol;
  f2ptr ch__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr string__symbol;
  f2ptr string__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__char__slot_t;

// string

typedef struct funk2_object_type__string__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
  // defined in f2_string.c
  f2ptr as__symbol__symbol;
  f2ptr as__symbol__funk;
  f2ptr save__symbol;
  f2ptr save__funk;
  f2ptr split__symbol;
  f2ptr split__funk;
  f2ptr contains__symbol;
  f2ptr contains__funk;
  f2ptr substring__symbol;
  f2ptr substring__funk;
  f2ptr is_less_than__symbol;
  f2ptr is_less_than__funk;
  f2ptr is_greater_than__symbol;
  f2ptr is_greater_than__funk;
  f2ptr lowercase__symbol;
  f2ptr lowercase__funk;
  f2ptr uppercase__symbol;
  f2ptr uppercase__funk;
  f2ptr multiply__symbol;
  f2ptr multiply__funk;
} funk2_object_type__string__slot_t;

// symbol

typedef struct funk2_object_type__symbol__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
  f2ptr as__string__symbol;
  f2ptr as__string__funk;
} funk2_object_type__symbol__slot_t;

// chunk

typedef struct funk2_object_type__chunk__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_copy__symbol;
  f2ptr new_copy__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr bit8__elt__symbol;
  f2ptr bit8__elt__funk;
  f2ptr bit8__elt__set__symbol;
  f2ptr bit8__elt__set__funk;
  f2ptr bit16__elt__symbol;
  f2ptr bit16__elt__funk;
  f2ptr bit16__elt__set__symbol;
  f2ptr bit16__elt__set__funk;
  f2ptr bit32__elt__symbol;
  f2ptr bit32__elt__funk;
  f2ptr bit32__elt__set__symbol;
  f2ptr bit32__elt__set__funk;
  f2ptr bit64__elt__symbol;
  f2ptr bit64__elt__funk;
  f2ptr bit64__elt__set__symbol;
  f2ptr bit64__elt__set__funk;
  f2ptr cfunk_jump__symbol;
  f2ptr cfunk_jump__funk;
  f2ptr bytecode_jump__symbol;
  f2ptr bytecode_jump__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
  f2ptr save__symbol;
  f2ptr save__funk;
} funk2_object_type__chunk__slot_t;

// simple_array

typedef struct funk2_object_type__simple_array__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_copy__symbol;
  f2ptr new_copy__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr elt__set__symbol;
  f2ptr elt__set__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__simple_array__slot_t;

// traced_array

typedef struct funk2_object_type__traced_array__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr length__symbol;
  f2ptr length__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr elt__symbol;
  f2ptr elt__funk;
  f2ptr elt__set__symbol;
  f2ptr elt__set__funk;
  f2ptr elt__tracing_on__symbol;
  f2ptr elt__tracing_on__funk;
  f2ptr elt__tracing_on__set__symbol;
  f2ptr elt__tracing_on__set__funk;
  f2ptr elt__trace__symbol;
  f2ptr elt__trace__funk;
  f2ptr elt__trace__set__symbol;
  f2ptr elt__trace__set__funk;
  f2ptr elt__imagination_frame__symbol;
  f2ptr elt__imagination_frame__funk;
  f2ptr elt__imagination_frame__set__symbol;
  f2ptr elt__imagination_frame__set__funk;
  f2ptr elt__mutate_funks__symbol;
  f2ptr elt__mutate_funks__funk;
  f2ptr elt__mutate_funks__set__symbol;
  f2ptr elt__mutate_funks__set__funk;
  f2ptr elt__read_funks__symbol;
  f2ptr elt__read_funks__funk;
  f2ptr elt__read_funks__set__symbol;
  f2ptr elt__read_funks__set__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__traced_array__slot_t;

// larva

typedef struct funk2_object_type__larva__slot_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr larva_type__symbol;
  f2ptr larva_type__funk;
  f2ptr bug__symbol;
  f2ptr bug__funk;
  f2ptr eq__symbol;
  f2ptr eq__funk;
  f2ptr eq_hash_value__symbol;
  f2ptr eq_hash_value__funk;
  f2ptr equals__symbol;
  f2ptr equals__funk;
  f2ptr equals_hash_value__loop_free__symbol;
  f2ptr equals_hash_value__loop_free__funk;
  f2ptr equals_hash_value__symbol;
  f2ptr equals_hash_value__funk;
  f2ptr terminal_print_with_frame__symbol;
  f2ptr terminal_print_with_frame__funk;
} funk2_object_type__larva__slot_t;



typedef struct funk2_ptype_object_types_s {
  f2ptr is_type__symbol;
  f2ptr is_type__funk;
  f2ptr type__symbol;
  f2ptr type__funk;
  f2ptr raw__symbol;
  f2ptr raw__funk;
  f2ptr cause__symbol;
  f2ptr cause__funk;
  f2ptr cause__set__symbol;
  f2ptr cause__set__funk;
  f2ptr creation_fiber__symbol;
  f2ptr creation_fiber__funk;
  f2ptr creation_fiber__set__symbol;
  f2ptr creation_fiber__set__funk;
  funk2_object_type__integer__slot_t                  ptype_integer;
  funk2_object_type__double__slot_t                   ptype_double;
  funk2_object_type__float__slot_t                    ptype_float;
  funk2_object_type__pointer__slot_t                  ptype_pointer;
  funk2_object_type__scheduler_cmutex__slot_t         ptype_scheduler_cmutex;
  funk2_object_type__cmutex__slot_t                   ptype_cmutex;
  funk2_object_type__scheduler_creadwritelock__slot_t ptype_scheduler_creadwritelock;
  funk2_object_type__creadwritelock__slot_t           ptype_creadwritelock;
  funk2_object_type__char__slot_t                     ptype_char;
  funk2_object_type__string__slot_t                   ptype_string;
  funk2_object_type__symbol__slot_t                   ptype_symbol;
  funk2_object_type__chunk__slot_t                    ptype_chunk;
  funk2_object_type__simple_array__slot_t             ptype_simple_array;
  funk2_object_type__traced_array__slot_t             ptype_traced_array;
  funk2_object_type__larva__slot_t                    ptype_larva;
} funk2_ptype_object_types_t;

#endif // F2__PTYPES_OBJECT_SLOTS__TYPES__H

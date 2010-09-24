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

#ifndef F2__NATURAL_LANGUAGE__TYPES__H
#define F2__NATURAL_LANGUAGE__TYPES__H

// noun_group

typedef struct funk2_object_type__noun_group__slot_s funk2_object_type__noun_group__slot_t;
struct funk2_object_type__noun_group__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// verb

typedef struct funk2_object_type__verb__slot_s funk2_object_type__verb__slot_t;
struct funk2_object_type__verb__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// clause

typedef struct funk2_object_type__clause__slot_s funk2_object_type__clause__slot_t;
struct funk2_object_type__clause__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


#endif // F2__NATURAL_LANGUAGE__TYPES__H

#ifndef F2__NATURAL_LANGUAGE__H
#define F2__NATURAL_LANGUAGE__H



// noun_group

declare_frame_object_7_slot(noun_group, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);

f2ptr f2noun_group__primobject_type__new_aux(f2ptr cause);


// verb

declare_frame_object_10_slot(verb, symbol, imperative, en, ing, to, todel, tense, be, passive, negative);

f2ptr f2verb__primobject_type__new_aux(f2ptr cause);


// clause

declare_frame_object_6_slot(clause, secondary, imperative, declarative, question, yes_no, wh);

f2ptr f2clause__primobject_type__new_aux(f2ptr cause);


// **

void f2__natural_language__initialize();

#endif // F2__NATURAL_LANGUAGE__H


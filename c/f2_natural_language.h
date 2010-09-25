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

// clause

typedef struct funk2_object_type__clause__slot_s funk2_object_type__clause__slot_t;
struct funk2_object_type__clause__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// noun_group

typedef struct funk2_object_type__noun_group__slot_s funk2_object_type__noun_group__slot_t;
struct funk2_object_type__noun_group__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// preposition_group

typedef struct funk2_object_type__preposition_group__slot_s funk2_object_type__preposition_group__slot_t;
struct funk2_object_type__preposition_group__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// adjective_group

typedef struct funk2_object_type__adjective_group__slot_s funk2_object_type__adjective_group__slot_t;
struct funk2_object_type__adjective_group__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// verb_group

typedef struct funk2_object_type__verb_group__slot_s funk2_object_type__verb_group__slot_t;
struct funk2_object_type__verb_group__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// adjective_word

typedef struct funk2_object_type__adjective_word__slot_s funk2_object_type__adjective_word__slot_t;
struct funk2_object_type__adjective_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// adverb_word

typedef struct funk2_object_type__adverb_word__slot_s funk2_object_type__adverb_word__slot_t;
struct funk2_object_type__adverb_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// binder_word

typedef struct funk2_object_type__binder_word__slot_s funk2_object_type__binder_word__slot_t;
struct funk2_object_type__binder_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// classifier_word

typedef struct funk2_object_type__classifier_word__slot_s funk2_object_type__classifier_word__slot_t;
struct funk2_object_type__classifier_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// determiner_word

typedef struct funk2_object_type__determiner_word__slot_s funk2_object_type__determiner_word__slot_t;
struct funk2_object_type__determiner_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


#endif // F2__NATURAL_LANGUAGE__TYPES__H

#ifndef F2__NATURAL_LANGUAGE__H
#define F2__NATURAL_LANGUAGE__H



// clause

declare_frame_object_6_slot(clause, secondary, imperative, declarative, question, yes_no, wh);

f2ptr f2clause__primobject_type__new_aux(f2ptr cause);


// noun_group

declare_frame_object_7_slot(noun_group, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);

f2ptr f2noun_group__primobject_type__new_aux(f2ptr cause);


// preposition_group

declare_frame_object_8_slot(preposition_group, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);

f2ptr f2preposition_group__primobject_type__new_aux(f2ptr cause);


// adjective_group

declare_frame_object_7_slot(adjective_group, complement, qualifier, adjunct, than, as, comparitive, question);

f2ptr f2adjective_group__primobject_type__new_aux(f2ptr cause);


// verb_group

declare_frame_object_9_slot(verb_group, imperative, en, ing, to, todel, tense, be, passive, negative);

f2ptr f2verb_group__primobject_type__new_aux(f2ptr cause);


// adjective_word

declare_frame_object_3_slot(adjective_word, symbol, superlative, comparative);

f2ptr f2adjective_word__primobject_type__new_aux(f2ptr cause);


// adverb_word

declare_frame_object_5_slot(adverb_word, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);

f2ptr f2adverb_word__primobject_type__new_aux(f2ptr cause);


// binder_word

declare_frame_object_1_slot(binder_word, symbol);

f2ptr f2binder_word__primobject_type__new_aux(f2ptr cause);


// classifier_word

declare_frame_object_1_slot(classifier_word, symbol);

f2ptr f2classifier_word__primobject_type__new_aux(f2ptr cause);


// determiner_word

declare_frame_object_12_slot(determiner_word, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);

f2ptr f2determiner_word__primobject_type__new_aux(f2ptr cause);


// **

void f2__natural_language__initialize();

#endif // F2__NATURAL_LANGUAGE__H


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

#ifndef F2__NATURAL_LANGUAGE__TYPES__H
#define F2__NATURAL_LANGUAGE__TYPES__H

// clause

typedef struct funk2_object_type__clause__slot_s funk2_object_type__clause__slot_t;
struct funk2_object_type__clause__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// wh_rank_shift_clause

typedef struct funk2_object_type__wh_rank_shift_clause__slot_s funk2_object_type__wh_rank_shift_clause__slot_t;
struct funk2_object_type__wh_rank_shift_clause__slot_s {
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


// combination_group

typedef struct funk2_object_type__combination_group__slot_s funk2_object_type__combination_group__slot_t;
struct funk2_object_type__combination_group__slot_s {
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


// noun_word

typedef struct funk2_object_type__noun_word__slot_s funk2_object_type__noun_word__slot_t;
struct funk2_object_type__noun_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// number_word

typedef struct funk2_object_type__number_word__slot_s funk2_object_type__number_word__slot_t;
struct funk2_object_type__number_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// number_determiner_word

typedef struct funk2_object_type__number_determiner_word__slot_s funk2_object_type__number_determiner_word__slot_t;
struct funk2_object_type__number_determiner_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// ordinal_word

typedef struct funk2_object_type__ordinal_word__slot_s funk2_object_type__ordinal_word__slot_t;
struct funk2_object_type__ordinal_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// preposition_word

typedef struct funk2_object_type__preposition_word__slot_s funk2_object_type__preposition_word__slot_t;
struct funk2_object_type__preposition_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// pronoun_word

typedef struct funk2_object_type__pronoun_word__slot_s funk2_object_type__pronoun_word__slot_t;
struct funk2_object_type__pronoun_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// proper_noun_word

typedef struct funk2_object_type__proper_noun_word__slot_s funk2_object_type__proper_noun_word__slot_t;
struct funk2_object_type__proper_noun_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// particle_word

typedef struct funk2_object_type__particle_word__slot_s funk2_object_type__particle_word__slot_t;
struct funk2_object_type__particle_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// question_adjunct_word

typedef struct funk2_object_type__question_adjunct_word__slot_s funk2_object_type__question_adjunct_word__slot_t;
struct funk2_object_type__question_adjunct_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// thing_pronoun_word

typedef struct funk2_object_type__thing_pronoun_word__slot_s funk2_object_type__thing_pronoun_word__slot_t;
struct funk2_object_type__thing_pronoun_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// infinitive_helper_word

typedef struct funk2_object_type__infinitive_helper_word__slot_s funk2_object_type__infinitive_helper_word__slot_t;
struct funk2_object_type__infinitive_helper_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// verb_word

typedef struct funk2_object_type__verb_word__slot_s funk2_object_type__verb_word__slot_t;
struct funk2_object_type__verb_word__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
};


// parse_tree_node

typedef struct funk2_object_type__parse_tree_node__slot_s funk2_object_type__parse_tree_node__slot_t;
struct funk2_object_type__parse_tree_node__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr insert_after__symbol;
  f2ptr insert_after__funk;
  f2ptr insert_below_no_children__symbol;
  f2ptr insert_below_no_children__funk;
  f2ptr add_child__symbol;
  f2ptr add_child__funk;
  f2ptr child_of_type_node__symbol;
  f2ptr child_of_type_node__funk;
  f2ptr containing_type_node__symbol;
  f2ptr containing_type_node__funk;
  f2ptr containing_type_with_true_property_node__symbol;
  f2ptr containing_type_with_true_property_node__funk;
  f2ptr containing_type_with_true_property__set__symbol;
  f2ptr containing_type_with_true_property__set__funk;
};


// parse_tree

typedef struct funk2_object_type__parse_tree__slot_s funk2_object_type__parse_tree__slot_t;
struct funk2_object_type__parse_tree__slot_s {
  f2ptr new__symbol;
  f2ptr new__funk;
  f2ptr new_copy__symbol;
  f2ptr new_copy__funk;
};


#endif // F2__NATURAL_LANGUAGE__TYPES__H

#ifndef F2__NATURAL_LANGUAGE__H
#define F2__NATURAL_LANGUAGE__H



// wh_rank_shift_clause

declare_frame_object_1_slot(wh_rank_shift_clause, symbols);

f2ptr f2wh_rank_shift_clause__primobject_type__new_aux(f2ptr cause);


// clause

declare_frame_object_13_slot(clause, symbols, secondary, imperative, declarative, question, yes_no, wh, particle, transitive, transitive_two, subject_to_object, to_object, unmatched_relative_reference);

f2ptr f2clause__primobject_type__new_aux(f2ptr cause);


// noun_group

declare_frame_object_18_slot(noun_group, symbols, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, definite, indefinite, quantifier, singular, plural, mass, object, object_one, object_two, question);

f2ptr f2noun_group__primobject_type__new_aux(f2ptr cause);


// preposition_group

declare_frame_object_9_slot(preposition_group, symbols, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);

f2ptr f2preposition_group__primobject_type__new_aux(f2ptr cause);


// adjective_group

declare_frame_object_8_slot(adjective_group, symbols, complement, qualifier, adjunct, than, as, comparitive, question);

f2ptr f2adjective_group__primobject_type__new_aux(f2ptr cause);


// verb_group

declare_frame_object_15_slot(verb_group, symbols, imperative, en, ing, to, todel, tense, be, passive, negative, auxiliary, not_only_auxiliary, singular, plural, takes_particle);

f2ptr f2verb_group__primobject_type__new_aux(f2ptr cause);


// combination_group

declare_frame_object_3_slot(combination_group, symbols, transitive, preposition);

f2ptr f2combination_group__primobject_type__new_aux(f2ptr cause);


// adjective_word

declare_frame_object_3_slot(adjective_word, symbols, superlative, comparative);

f2ptr f2adjective_word__primobject_type__new_aux(f2ptr cause);


// adverb_word

declare_frame_object_5_slot(adverb_word, symbols, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);

f2ptr f2adverb_word__primobject_type__new_aux(f2ptr cause);


// binder_word

declare_frame_object_1_slot(binder_word, symbols);

f2ptr f2binder_word__primobject_type__new_aux(f2ptr cause);


// classifier_word

declare_frame_object_1_slot(classifier_word, symbols);

f2ptr f2classifier_word__primobject_type__new_aux(f2ptr cause);


// determiner_word

declare_frame_object_12_slot(determiner_word, symbols, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);

f2ptr f2determiner_word__primobject_type__new_aux(f2ptr cause);


// noun_word

declare_frame_object_7_slot(noun_word, symbols, singular, plural, mass, possessive, time_unit, time_specific);

f2ptr f2noun_word__primobject_type__new_aux(f2ptr cause);


// number_word

declare_frame_object_3_slot(number_word, symbols, singular, plural);

f2ptr f2number_word__primobject_type__new_aux(f2ptr cause);


// number_determiner_word

declare_frame_object_5_slot(number_determiner_word, symbols, than_modifier, as_as_modifier, at_modifier, alone);

f2ptr f2number_determiner_word__primobject_type__new_aux(f2ptr cause);


// ordinal_word

declare_frame_object_1_slot(ordinal_word, symbols);

f2ptr f2ordinal_word__primobject_type__new_aux(f2ptr cause);


// preposition_word

declare_frame_object_3_slot(preposition_word, symbols, combination_first, combination_second);

f2ptr f2preposition_word__primobject_type__new_aux(f2ptr cause);


// pronoun_word

declare_frame_object_10_slot(pronoun_word, symbols, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);

f2ptr f2pronoun_word__primobject_type__new_aux(f2ptr cause);


// proper_noun_word

declare_frame_object_3_slot(proper_noun_word, symbols, singular, plural);

f2ptr f2proper_noun_word__primobject_type__new_aux(f2ptr cause);


// particle_word

declare_frame_object_1_slot(particle_word, symbols);

f2ptr f2particle_word__primobject_type__new_aux(f2ptr cause);


// question_adjunct_word

declare_frame_object_1_slot(question_adjunct_word, symbols);

f2ptr f2question_adjunct_word__primobject_type__new_aux(f2ptr cause);


// thing_pronoun_word

declare_frame_object_1_slot(thing_pronoun_word, symbols);

f2ptr f2thing_pronoun_word__primobject_type__new_aux(f2ptr cause);


// infinitive_helper_word

declare_frame_object_1_slot(infinitive_helper_word, symbols);

f2ptr f2infinitive_helper_word__primobject_type__new_aux(f2ptr cause);


// verb_word

declare_frame_object_23_slot(verb_word, symbols, auxiliary, be, Do, have, will, modal, negative, question_auxiliary, third_person_singular, plural, first_person_singular, ing, en, infinitive, past, present, Main, takes_particle, transitive, transitive_two, takes_to_object, takes_subject_to_object);

f2ptr f2verb_word__primobject_type__new_aux(f2ptr cause);


// parse_tree_node

declare_frame_object_6_slot(parse_tree_node, parse_object, parent_node, previous_node, next_node, first_child_node, last_child_node);

f2ptr f2parse_tree_node__primobject_type__new_aux(f2ptr cause);


// parse_tree

declare_frame_object_2_slot(parse_tree, root_node, current_node);

f2ptr f2parse_tree__primobject_type__new_aux(f2ptr cause);


// **

void f2__natural_language__initialize();

#endif // F2__NATURAL_LANGUAGE__H


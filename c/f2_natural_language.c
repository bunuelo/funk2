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

#include "funk2.h"





// clause

def_frame_object__global__13_slot(clause, symbols, secondary, imperative, declarative, question, yes_no, wh, particle, transitive, transitive_two, subject_to_object, to_object, unmatched_relative_reference);

f2ptr f2__clause__new(f2ptr cause) {
  f2ptr symbols                      = nil;
  f2ptr secondary                    = nil;
  f2ptr imperative                   = nil;
  f2ptr declarative                  = nil;
  f2ptr question                     = nil;
  f2ptr yes_no                       = nil;
  f2ptr wh                           = nil;
  f2ptr particle                     = nil;
  f2ptr transitive                   = nil;
  f2ptr transitive_two               = nil;
  f2ptr subject_to_object            = nil;
  f2ptr to_object                    = nil;
  f2ptr unmatched_relative_reference = nil;
  return f2clause__new(cause, symbols, secondary, imperative, declarative, question, yes_no, wh, particle, transitive, transitive_two, subject_to_object, to_object, unmatched_relative_reference);
}
def_pcfunk0(clause__new,
	    "",
	    return f2__clause__new(this_cause));


f2ptr f2clause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2clause__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_clause.new__funk);}
  return this;
}


// wh_rank_shift_clause

def_frame_object__global__1_slot(wh_rank_shift_clause, symbols);

f2ptr f2__wh_rank_shift_clause__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2wh_rank_shift_clause__new(cause, symbols);
}
def_pcfunk0(wh_rank_shift_clause__new,
	    "",
	    return f2__wh_rank_shift_clause__new(this_cause));


f2ptr f2wh_rank_shift_clause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2wh_rank_shift_clause__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_wh_rank_shift_clause.new__funk);}
  return this;
}


// noun_group

def_frame_object__global__18_slot(noun_group, symbols, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, definite, indefinite, quantifier, singular, plural, mass, object, object_one, object_two, question);

f2ptr f2__noun_group__new(f2ptr cause) {
  f2ptr symbols     = nil;
  f2ptr determiner  = nil;
  f2ptr ordinal     = nil;
  f2ptr number      = nil;
  f2ptr adjectives  = nil;
  f2ptr classifiers = nil;
  f2ptr noun        = nil;
  f2ptr qualifiers  = nil;
  f2ptr definite    = nil;
  f2ptr indefinite  = nil;
  f2ptr quantifier  = nil;
  f2ptr singular    = nil;
  f2ptr plural      = nil;
  f2ptr mass        = nil;
  f2ptr object      = nil;
  f2ptr object_one  = nil;
  f2ptr object_two  = nil;
  f2ptr question    = nil;
  return f2noun_group__new(cause, symbols, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, definite, indefinite, quantifier, singular, plural, mass, object, object_one, object_two, question);
}
def_pcfunk0(noun_group__new,
	    "",
	    return f2__noun_group__new(this_cause));


f2ptr f2noun_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2noun_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk);}
  return this;
}


// preposition_group

def_frame_object__global__9_slot(preposition_group, symbols, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);

f2ptr f2__preposition_group__new(f2ptr cause) {
  f2ptr symbols                    = nil;
  f2ptr complement                 = nil;
  f2ptr locational_object          = nil;
  f2ptr adjunct                    = nil;
  f2ptr agent                      = nil;
  f2ptr question                   = nil;
  f2ptr missing_up_relative        = nil;
  f2ptr missing_up_question        = nil;
  f2ptr relative_preposition_group = nil;
  return f2preposition_group__new(cause, symbols, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);
}
def_pcfunk0(preposition_group__new,
	    "",
	    return f2__preposition_group__new(this_cause));


f2ptr f2preposition_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2preposition_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__funk);}
  return this;
}


// adjective_group

def_frame_object__global__8_slot(adjective_group, symbols, complement, qualifier, adjunct, than, as, comparitive, question);

f2ptr f2__adjective_group__new(f2ptr cause) {
  f2ptr symbols     = nil;
  f2ptr complement  = nil;
  f2ptr qualifier   = nil;
  f2ptr adjunct     = nil;
  f2ptr than        = nil;
  f2ptr as          = nil;
  f2ptr comparitive = nil;
  f2ptr question    = nil;
  return f2adjective_group__new(cause, symbols, complement, qualifier, adjunct, than, as, comparitive, question);
}
def_pcfunk0(adjective_group__new,
	    "",
	    return f2__adjective_group__new(this_cause));


f2ptr f2adjective_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2adjective_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk);}
  return this;
}


// verb_group

def_frame_object__global__15_slot(verb_group, symbols, imperative, en, ing, to, todel, tense, be, passive, negative, auxiliary, not_only_auxiliary, singular, plural, takes_particle);

f2ptr f2__verb_group__new(f2ptr cause) {
  f2ptr symbols            = nil;
  f2ptr imperative         = nil;
  f2ptr en                 = nil;
  f2ptr ing                = nil;
  f2ptr to                 = nil;
  f2ptr todel              = nil;
  f2ptr tense              = nil;
  f2ptr be                 = nil;
  f2ptr passive            = nil;
  f2ptr negative           = nil;
  f2ptr auxiliary          = nil;
  f2ptr not_only_auxiliary = nil;
  f2ptr singular           = nil;
  f2ptr plural             = nil;
  f2ptr takes_particle     = nil;
  return f2verb_group__new(cause, symbols, imperative, en, ing, to, todel, tense, be, passive, negative, auxiliary, not_only_auxiliary, singular, plural, takes_particle);
}
def_pcfunk0(verb_group__new,
	    "",
	    return f2__verb_group__new(this_cause));


f2ptr f2verb_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2verb_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__funk);}
  return this;
}


// combination_group

def_frame_object__global__3_slot(combination_group, symbols, transitive, preposition);

f2ptr f2__combination_group__new(f2ptr cause) {
  f2ptr symbols     = nil;
  f2ptr transitive  = nil;
  f2ptr preposition = nil;
  return f2combination_group__new(cause, symbols, transitive, preposition);
}
def_pcfunk0(combination_group__new,
	    "",
	    return f2__combination_group__new(this_cause));


f2ptr f2combination_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2combination_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_combination_group.new__funk);}
  return this;
}


// adjective_word

def_frame_object__global__3_slot(adjective_word, symbols, superlative, comparative);

f2ptr f2__adjective_word__new(f2ptr cause) {
  f2ptr symbols     = nil;
  f2ptr superlative = nil;
  f2ptr comparative = nil;
  return f2adjective_word__new(cause, symbols, superlative, comparative);
}
def_pcfunk0(adjective_word__new,
	    "",
	    return f2__adjective_word__new(this_cause));


f2ptr f2adjective_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2adjective_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__funk);}
  return this;
}


// adverb_word

def_frame_object__global__5_slot(adverb_word, symbols, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);

f2ptr f2__adverb_word__new(f2ptr cause) {
  f2ptr symbols              = nil;
  f2ptr adverb_modifier      = nil;
  f2ptr verb_modifier        = nil;
  f2ptr preposition_modifier = nil;
  f2ptr clause_modifier      = nil;
  return f2adverb_word__new(cause, symbols, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);
}
def_pcfunk0(adverb_word__new,
	    "",
	    return f2__adverb_word__new(this_cause));


f2ptr f2adverb_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2adverb_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__funk);}
  return this;
}


// binder_word

def_frame_object__global__1_slot(binder_word, symbols);

f2ptr f2__binder_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2binder_word__new(cause, symbols);
}
def_pcfunk0(binder_word__new,
	    "",
	    return f2__binder_word__new(this_cause));


f2ptr f2binder_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2binder_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__funk);}
  return this;
}


// classifier_word

def_frame_object__global__1_slot(classifier_word, symbols);

f2ptr f2__classifier_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2classifier_word__new(cause, symbols);
}
def_pcfunk0(classifier_word__new,
	    "",
	    return f2__classifier_word__new(this_cause));


f2ptr f2classifier_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2classifier_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__funk);}
  return this;
}


// determiner_word

def_frame_object__global__12_slot(determiner_word, symbols, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);

f2ptr f2__determiner_word__new(f2ptr cause) {
  f2ptr symbols       = nil;
  f2ptr indefinite    = nil;
  f2ptr question      = nil;
  f2ptr definite      = nil;
  f2ptr demonstrative = nil;
  f2ptr quantifier    = nil;
  f2ptr incomplete_of = nil;
  f2ptr negative      = nil;
  f2ptr no_number     = nil;
  f2ptr singular      = nil;
  f2ptr plural        = nil;
  f2ptr mass          = nil;
  return f2determiner_word__new(cause, symbols, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);
}
def_pcfunk0(determiner_word__new,
	    "",
	    return f2__determiner_word__new(this_cause));


f2ptr f2determiner_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2determiner_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__funk);}
  return this;
}


// noun_word

def_frame_object__global__7_slot(noun_word, symbols, singular, plural, mass, possessive, time_unit, time_specific);

f2ptr f2__noun_word__new(f2ptr cause) {
  f2ptr symbols       = nil;
  f2ptr singular      = nil;
  f2ptr plural        = nil;
  f2ptr mass          = nil;
  f2ptr possessive    = nil;
  f2ptr time_unit     = nil;
  f2ptr time_specific = nil;
  return f2noun_word__new(cause, symbols, singular, plural, mass, possessive, time_unit, time_specific);
}
def_pcfunk0(noun_word__new,
	    "",
	    return f2__noun_word__new(this_cause));


f2ptr f2noun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2noun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__funk);}
  return this;
}


// number_word

def_frame_object__global__3_slot(number_word, symbols, singular, plural);

f2ptr f2__number_word__new(f2ptr cause) {
  f2ptr symbols  = nil;
  f2ptr singular = nil;
  f2ptr plural   = nil;
  return f2number_word__new(cause, symbols, singular, plural);
}
def_pcfunk0(number_word__new,
	    "",
	    return f2__number_word__new(this_cause));


f2ptr f2number_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2number_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_number_word.new__funk);}
  return this;
}


// number_determiner_word

def_frame_object__global__5_slot(number_determiner_word, symbols, than_modifier, as_as_modifier, at_modifier, alone);

f2ptr f2__number_determiner_word__new(f2ptr cause) {
  f2ptr symbols        = nil;
  f2ptr than_modifier  = nil;
  f2ptr as_as_modifier = nil;
  f2ptr at_modifier    = nil;
  f2ptr alone          = nil;
  return f2number_determiner_word__new(cause, symbols, than_modifier, as_as_modifier, at_modifier, alone);
}
def_pcfunk0(number_determiner_word__new,
	    "",
	    return f2__number_determiner_word__new(this_cause));


f2ptr f2number_determiner_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2number_determiner_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__funk);}
  return this;
}


// ordinal_word

def_frame_object__global__1_slot(ordinal_word, symbols);

f2ptr f2__ordinal_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2ordinal_word__new(cause, symbols);
}
def_pcfunk0(ordinal_word__new,
	    "",
	    return f2__ordinal_word__new(this_cause));


f2ptr f2ordinal_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2ordinal_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__funk);}
  return this;
}


// preposition_word

def_frame_object__global__3_slot(preposition_word, symbols, combination_first, combination_second);

f2ptr f2__preposition_word__new(f2ptr cause) {
  f2ptr symbols            = nil;
  f2ptr combination_first  = nil;
  f2ptr combination_second = nil;
  return f2preposition_word__new(cause, symbols, combination_first, combination_second);
}
def_pcfunk0(preposition_word__new,
	    "",
	    return f2__preposition_word__new(this_cause));


f2ptr f2preposition_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2preposition_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__funk);}
  return this;
}


// pronoun_word

def_frame_object__global__10_slot(pronoun_word, symbols, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);

f2ptr f2__pronoun_word__new(f2ptr cause) {
  f2ptr symbols               = nil;
  f2ptr singular              = nil;
  f2ptr plural                = nil;
  f2ptr first_person_singular = nil;
  f2ptr possessive            = nil;
  f2ptr subject               = nil;
  f2ptr object                = nil;
  f2ptr demonstrative         = nil;
  f2ptr relative_clause       = nil;
  f2ptr question              = nil;
  return f2pronoun_word__new(cause, symbols, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);
}
def_pcfunk0(pronoun_word__new,
	    "",
	    return f2__pronoun_word__new(this_cause));


f2ptr f2pronoun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2pronoun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__funk);}
  return this;
}


// proper_noun_word

def_frame_object__global__3_slot(proper_noun_word, symbols, singular, plural);

f2ptr f2__proper_noun_word__new(f2ptr cause) {
  f2ptr symbols  = nil;
  f2ptr singular = nil;
  f2ptr plural   = nil;
  return f2proper_noun_word__new(cause, symbols, singular, plural);
}
def_pcfunk0(proper_noun_word__new,
	    "",
	    return f2__proper_noun_word__new(this_cause));


f2ptr f2proper_noun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2proper_noun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__funk);}
  return this;
}


// particle_word

def_frame_object__global__1_slot(particle_word, symbols);

f2ptr f2__particle_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2particle_word__new(cause, symbols);
}
def_pcfunk0(particle_word__new,
	    "",
	    return f2__particle_word__new(this_cause));


f2ptr f2particle_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2particle_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__funk);}
  return this;
}


// question_adjunct_word

def_frame_object__global__1_slot(question_adjunct_word, symbols);

f2ptr f2__question_adjunct_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2question_adjunct_word__new(cause, symbols);
}
def_pcfunk0(question_adjunct_word__new,
	    "",
	    return f2__question_adjunct_word__new(this_cause));


f2ptr f2question_adjunct_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2question_adjunct_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__funk);}
  return this;
}


// thing_pronoun_word

def_frame_object__global__1_slot(thing_pronoun_word, symbols);

f2ptr f2__thing_pronoun_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2thing_pronoun_word__new(cause, symbols);
}
def_pcfunk0(thing_pronoun_word__new,
	    "",
	    return f2__thing_pronoun_word__new(this_cause));


f2ptr f2thing_pronoun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2thing_pronoun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_thing_pronoun_word.new__funk);}
  return this;
}


// infinitive_helper_word

def_frame_object__global__1_slot(infinitive_helper_word, symbols);

f2ptr f2__infinitive_helper_word__new(f2ptr cause) {
  f2ptr symbols = nil;
  return f2infinitive_helper_word__new(cause, symbols);
}
def_pcfunk0(infinitive_helper_word__new,
	    "",
	    return f2__infinitive_helper_word__new(this_cause));


f2ptr f2infinitive_helper_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2infinitive_helper_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_infinitive_helper_word.new__funk);}
  return this;
}


// verb_word

def_frame_object__global__23_slot(verb_word, symbols, auxiliary, be, Do, have, will, modal, negative, question_auxiliary, third_person_singular, plural, first_person_singular, ing, en, infinitive, past, present, Main, takes_particle, transitive, transitive_two, takes_to_object, takes_subject_to_object);

f2ptr f2__verb_word__new(f2ptr cause) {
  f2ptr symbols                 = nil;
  f2ptr auxiliary               = nil;
  f2ptr be                      = nil;
  f2ptr Do                      = nil;
  f2ptr have                    = nil;
  f2ptr will                    = nil;
  f2ptr modal                   = nil;
  f2ptr negative                = nil;
  f2ptr question_auxiliary      = nil;
  f2ptr third_person_singular   = nil;
  f2ptr plural                  = nil;
  f2ptr first_person_singular   = nil;
  f2ptr ing                     = nil;
  f2ptr en                      = nil;
  f2ptr infinitive              = nil;
  f2ptr past                    = nil;
  f2ptr present                 = nil;
  f2ptr Main                    = nil;
  f2ptr takes_particle          = nil;
  f2ptr transitive              = nil;
  f2ptr transitive_two          = nil;
  f2ptr takes_to_object         = nil;
  f2ptr takes_subject_to_object = nil;
  return f2verb_word__new(cause, symbols, auxiliary, be, Do, have, will, modal, negative, question_auxiliary, third_person_singular, plural, first_person_singular, ing, en, infinitive, past, present, Main, takes_particle, transitive, transitive_two, takes_to_object, takes_subject_to_object);
}
def_pcfunk0(verb_word__new,
	    "",
	    return f2__verb_word__new(this_cause));


f2ptr f2verb_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2verb_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_verb_word.new__funk);}
  return this;
}


// parse_tree_node

def_frame_object__global__6_slot(parse_tree_node, parse_object, parent_node, previous_node, next_node, first_child_node, last_child_node);

f2ptr f2__parse_tree_node__new(f2ptr cause) {
  f2ptr parse_object     = nil;
  f2ptr parent_node      = nil;
  f2ptr previous_node    = nil;
  f2ptr next_node        = nil;
  f2ptr first_child_node = nil;
  f2ptr last_child_node  = nil;
  return f2parse_tree_node__new(cause, parse_object, parent_node, previous_node, next_node, first_child_node, last_child_node);
}
def_pcfunk0(parse_tree_node__new,
	    "",
	    return f2__parse_tree_node__new(this_cause));


void raw__parse_tree_node__add_all_nodes_as_new_to_ptypehash(f2ptr cause, f2ptr this, f2ptr ptypehash) {
  raw__ptypehash__add(cause, ptypehash, this, f2__parse_tree_node__new(cause));
  {
    f2ptr first_child_node = raw__parse_tree_node__first_child_node(cause, this);
    if (first_child_node != nil) {
      raw__parse_tree_node__add_all_nodes_as_new_to_ptypehash(cause, first_child_node, ptypehash);
    }
  }
  {
    f2ptr next_node = raw__parse_tree_node__next_node(cause, this);
    if (next_node != nil) {
      raw__parse_tree_node__add_all_nodes_as_new_to_ptypehash(cause, next_node, ptypehash);
    }
  }
}

void raw__parse_tree_node__map_all_new_nodes_using_ptypehash(f2ptr cause, f2ptr this, f2ptr ptypehash) {
  f2ptr new_node = raw__ptypehash__lookup(cause, ptypehash, this);
  raw__parse_tree_node__parse_object__set(cause, new_node, raw__parse_tree_node__parse_object(cause, this));
  f2ptr parent_node      = raw__parse_tree_node__parent_node(     cause, this); if (parent_node      != nil) {raw__parse_tree_node__parent_node__set(     cause, new_node, raw__ptypehash__lookup(cause, ptypehash, parent_node));}
  f2ptr previous_node    = raw__parse_tree_node__previous_node(   cause, this); if (previous_node    != nil) {raw__parse_tree_node__previous_node__set(   cause, new_node, raw__ptypehash__lookup(cause, ptypehash, previous_node));}
  f2ptr next_node        = raw__parse_tree_node__next_node(       cause, this); if (next_node        != nil) {raw__parse_tree_node__next_node__set(       cause, new_node, raw__ptypehash__lookup(cause, ptypehash, next_node));}
  f2ptr first_child_node = raw__parse_tree_node__first_child_node(cause, this); if (first_child_node != nil) {raw__parse_tree_node__first_child_node__set(cause, new_node, raw__ptypehash__lookup(cause, ptypehash, first_child_node));}
  f2ptr last_child_node  = raw__parse_tree_node__last_child_node( cause, this); if (last_child_node  != nil) {raw__parse_tree_node__last_child_node__set( cause, new_node, raw__ptypehash__lookup(cause, ptypehash, last_child_node));}
  {
    f2ptr first_child_node = raw__parse_tree_node__first_child_node(cause, this);
    if (first_child_node != nil) {
      raw__parse_tree_node__map_all_new_nodes_using_ptypehash(cause, first_child_node, ptypehash);
    }
  }
  {
    f2ptr next_node = raw__parse_tree_node__next_node(cause, this);
    if (next_node != nil) {
      raw__parse_tree_node__map_all_new_nodes_using_ptypehash(cause, next_node, ptypehash);
    }
  }
}


void raw__parse_tree_node__insert_after(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr old_next_node = raw__parse_tree_node__next_node(  cause, this);
  f2ptr parent_node   = raw__parse_tree_node__parent_node(cause, this);
  raw__parse_tree_node__next_node__set(    cause, this, node);
  raw__parse_tree_node__parent_node__set(  cause, node, parent_node);
  raw__parse_tree_node__next_node__set(    cause, node, old_next_node);
  raw__parse_tree_node__previous_node__set(cause, node, this);
  if (old_next_node != nil) {
    raw__parse_tree_node__previous_node__set(cause, old_next_node, node);
  } else {
    if (parent_node != nil) {
      raw__parse_tree_node__last_child_node__set(cause, parent_node, node);
    }
  }
}

f2ptr f2__parse_tree_node__insert_after(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(parse_tree_node, this);
  raw__parse_tree_node__insert_after(cause, this, node);
  return nil;
}
def_pcfunk2(parse_tree_node__insert_after, this, node,
	    "",
	    return f2__parse_tree_node__insert_after(this_cause, this, node));


void raw__parse_tree_node__insert_below_no_children(f2ptr cause, f2ptr this, f2ptr node) {
  raw__parse_tree_node__first_child_node__set(cause, this, node);
  raw__parse_tree_node__last_child_node__set( cause, this, node);
  raw__parse_tree_node__first_child_node__set(cause, node, nil);
  raw__parse_tree_node__last_child_node__set( cause, node, nil);
  raw__parse_tree_node__parent_node__set(     cause, node, this);
  raw__parse_tree_node__previous_node__set(   cause, node, nil);
  raw__parse_tree_node__next_node__set(       cause, node, nil);
}

f2ptr f2__parse_tree_node__insert_below_no_children(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(parse_tree_node, this);
  raw__parse_tree_node__insert_below_no_children(cause, this, node);
  return nil;
}
def_pcfunk2(parse_tree_node__insert_below_no_children, this, node,
	    "",
	    return f2__parse_tree_node__insert_below_no_children(this_cause, this, node));


void raw__parse_tree_node__add_child(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr last_child_node = raw__parse_tree_node__last_child_node(cause, this);
  if (last_child_node == nil) {
    raw__parse_tree_node__insert_below_no_children(cause, this, node);
  } else {
    raw__parse_tree_node__insert_after(cause, last_child_node, node);
  }
}

f2ptr f2__parse_tree_node__add_child(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(parse_tree_node, this);
  assert_argument_type(parse_tree_node, node);
  raw__parse_tree_node__add_child(cause, this, node);
  return nil;
}
def_pcfunk2(parse_tree_node__add_child, this, node,
	    "",
	    return f2__parse_tree_node__add_child(this_cause, this, node));


f2ptr raw__parse_tree_node__child_of_type_node(f2ptr cause, f2ptr this, f2ptr type) {
  f2ptr iter = raw__parse_tree_node__first_child_node(cause, this);
  while ((iter != nil) &&
	 (! raw__object__inherits_from(cause, raw__parse_tree_node__parse_object(cause, iter), type))) {
    iter = raw__parse_tree_node__next_node(cause, iter);
  }
  if (iter == nil) {
    return f2larva__new(cause, 4346, f2__bug__new(cause, f2integer__new(cause, 4346),
						  f2__frame__new(cause, f2list4__new(cause,
										     new__symbol(cause, "bug_type"),      new__symbol(cause, "parse_tree_node-child_of_type-does_not_exist"),
										     new__symbol(cause, "child_of_type"), type))));
  }
  return iter;
}

f2ptr f2__parse_tree_node__child_of_type_node(f2ptr cause, f2ptr this, f2ptr type) {
  assert_argument_type(parse_tree_node, this);
  assert_argument_type(symbol,          type);
  return raw__parse_tree_node__child_of_type_node(cause, this, type);
}
def_pcfunk2(parse_tree_node__child_of_type_node, this, type,
	    "",
	    return f2__parse_tree_node__child_of_type_node(this_cause, this, type));


f2ptr raw__parse_tree_node__containing_type_node(f2ptr cause, f2ptr this, f2ptr type) {
  if (raw__object__inherits_from(cause, raw__parse_tree_node__parse_object(cause, this), type)) {
    return this;
  } else {
    f2ptr previous_node = raw__parse_tree_node__previous_node(cause, this);
    if (previous_node != nil) {
      return raw__parse_tree_node__containing_type_node(cause, previous_node, type);
    } else {
      f2ptr parent_node = raw__parse_tree_node__parent_node(cause, this);
      if (parent_node != nil) {
	return raw__parse_tree_node__containing_type_node(cause, parent_node, type);
      } else {
	return nil;
      }
    }
  }
}

f2ptr f2__parse_tree_node__containing_type_node(f2ptr cause, f2ptr this, f2ptr type) {
  assert_argument_type(parse_tree_node, this);
  assert_argument_type(symbol,          type);
  return raw__parse_tree_node__containing_type_node(cause, this, type);
}
def_pcfunk2(parse_tree_node__containing_type_node, this, type,
	    "",
	    return f2__parse_tree_node__containing_type_node(this_cause, this, type));


//[deftypefunk parse_tree_node get containing_type_with_true_property_node [type property]
//  [if [and [is-type type parse_object]
//	     [object-get parse_object property]]
//      this
//    [if previous_node
//	  [get previous_node containing_type_with_true_property_node type property]
//      [if parent_node
//	    [get parent_node containing_type_with_true_property_node type property]
//	  nil]]]]

f2ptr raw__parse_tree_node__containing_type_with_true_property_node(f2ptr cause, f2ptr this, f2ptr type, f2ptr property) {
  f2ptr parse_object = raw__parse_tree_node__parse_object(cause, this);
  if (raw__object__inherits_from(cause, parse_object, type) &&
      (f2__object__get_0(cause, parse_object, property) != nil)) {
    return this;
  } else {
    f2ptr previous_node = raw__parse_tree_node__previous_node(cause, this);
    if (previous_node != nil) {
      return raw__parse_tree_node__containing_type_with_true_property_node(cause, previous_node, type, property);
    } else {
      f2ptr parent_node = raw__parse_tree_node__parent_node(cause, this);
      if (parent_node != nil) {
	return raw__parse_tree_node__containing_type_with_true_property_node(cause, parent_node, type, property);
      } else {
	return nil;
      }
    }
  }
}

f2ptr f2__parse_tree_node__containing_type_with_true_property_node(f2ptr cause, f2ptr this, f2ptr type, f2ptr property) {
  assert_argument_type(parse_tree_node, this);
  assert_argument_type(symbol,          type);
  return raw__parse_tree_node__containing_type_with_true_property_node(cause, this, type, property);
}
def_pcfunk3(parse_tree_node__containing_type_with_true_property_node, this, type, property,
	    "",
	    return f2__parse_tree_node__containing_type_with_true_property_node(this_cause, this, type, property));


//[deftypefunk parse_tree_node set containing_type_with_true_property_node [type property value]
//  [if [and [is-type type parse_object]
//	     [object-get parse_object property]]
//      [object-set parse_object property value]
//    [if previous_node
//	  [get previous_node containing_type_with_true_property_node type property]
//      [if parent_node
//	    [get parent_node containing_type_with_true_property_node type property]
//	  [error bug_type        `could_not_find_containing_type_with_try_property
//	         funkname        `containing_type_with_true_property_node
//	         containing_type type
//	         property        property]]]]]

f2ptr raw__parse_tree_node__containing_type_with_true_property__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr property, f2ptr value) {
  f2ptr parse_object = raw__parse_tree_node__parse_object(cause, this);
  if (raw__object__inherits_from(cause, parse_object, type) &&
      (f2__object__get_0(cause, parse_object, property) != nil)) {
    return f2__object__set_1(cause, parse_object, property, value);
  } else {
    f2ptr previous_node = raw__parse_tree_node__previous_node(cause, this);
    if (previous_node != nil) {
      return raw__parse_tree_node__containing_type_with_true_property__set(cause, previous_node, type, property, value);
    } else {
      f2ptr parent_node = raw__parse_tree_node__parent_node(cause, this);
      if (parent_node != nil) {
	return raw__parse_tree_node__containing_type_with_true_property__set(cause, parent_node, type, property, value);
      } else {
	return f2larva__new(cause, 73589, f2__bug__new(cause, f2integer__new(cause, 73589), f2__frame__new(cause, f2list8__new(cause,
															       new__symbol(cause, "bug_type"),        new__symbol(cause, "could_not_find_containing_type_with_try_property"),
															       new__symbol(cause, "funkname"),        new__symbol(cause, "parse_tree_node-containing_type_with_true_property-set"),
															       new__symbol(cause, "containing_type"), type,
															       new__symbol(cause, "property"),        property))));
      }
    }
  }
}

f2ptr f2__parse_tree_node__containing_type_with_true_property__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr property, f2ptr value) {
  assert_argument_type(parse_tree_node, this);
  assert_argument_type(symbol,          type);
  assert_argument_type(symbol,          property);
  return raw__parse_tree_node__containing_type_with_true_property__set(cause, this, type, property, value);
}
def_pcfunk4(parse_tree_node__containing_type_with_true_property__set, this, type, property, value,
	    "",
	    return f2__parse_tree_node__containing_type_with_true_property__set(this_cause, this, type, property, value));


f2ptr f2parse_tree_node__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2parse_tree_node__primobject_type__new(cause);
  {char* slot_name = "new";                                     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.new__funk);}
  {char* slot_name = "insert_after";                            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_after__funk);}
  {char* slot_name = "insert_below_no_children";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_below_no_children__funk);}
  {char* slot_name = "add_child";                               f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.add_child__funk);}
  {char* slot_name = "child_of_type_node";                      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.child_of_type_node__funk);}
  {char* slot_name = "containing_type_node";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_node__funk);}
  {char* slot_name = "containing_type_with_true_property_node"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property_node__funk);}
  {char* slot_name = "containing_type_with_true_property";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property__set__funk);}
  return this;
}


// parse_tree

def_frame_object__global__2_slot(parse_tree, root_node, current_node);

f2ptr f2__parse_tree__new(f2ptr cause) {
  f2ptr root_node    = nil;
  f2ptr current_node = nil;
  return f2parse_tree__new(cause, root_node, current_node);
}
def_pcfunk0(parse_tree__new,
	    "",
	    return f2__parse_tree__new(this_cause));


f2ptr raw__parse_tree__new_copy(f2ptr cause, f2ptr this) {
  f2ptr parse_tree = f2__parse_tree__new(cause);
  f2ptr root_node  = raw__parse_tree__root_node(cause, this);
  if (root_node != nil) {
    f2ptr node_hash  = f2__ptypehash__new(cause);
    raw__parse_tree_node__add_all_nodes_as_new_to_ptypehash(       cause, root_node, node_hash);
    raw__parse_tree_node__map_all_new_nodes_using_ptypehash(cause, root_node, node_hash);
    raw__parse_tree__root_node__set(   cause, parse_tree, raw__ptypehash__lookup(cause, node_hash, root_node));
    f2ptr current_node = raw__parse_tree__current_node(cause, this);
    raw__parse_tree__current_node__set(cause, parse_tree, raw__ptypehash__lookup(cause, node_hash, current_node));
  }
  return parse_tree;
}

f2ptr f2__parse_tree__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(parse_tree, this);
  return raw__parse_tree__new_copy(cause, this);
}
def_pcfunk1(parse_tree__new_copy, this,
	    "",
	    return f2__parse_tree__new_copy(this_cause, this));


f2ptr f2parse_tree__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2parse_tree__primobject_type__new(cause);
  {char* slot_name = "new";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new__funk);}
  {char* slot_name = "new_copy"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new_copy__funk);}
  return this;
}



// **

void f2__natural_langauge__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  // clause
  
  init_frame_object__13_slot__defragment__fix_pointers(clause, symbols, secondary, imperative, declarative, question, yes_no, wh, particle, transitive, transitive_two, subject_to_object, to_object, unmatched_relative_reference);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_clause.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(clause__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_clause.new__funk);
  
  
  // wh_rank_shift_clause
  
  init_frame_object__1_slot__defragment__fix_pointers(wh_rank_shift_clause, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_wh_rank_shift_clause.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(wh_rank_shift_clause__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_wh_rank_shift_clause.new__funk);
  
  
  // noun_group
  
  init_frame_object__18_slot__defragment__fix_pointers(noun_group, symbols, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, definite, indefinite, quantifier, singular, plural, mass, object, object_one, object_two, question);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(noun_group__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk);
  
  
  // preposition_group
  
  init_frame_object__9_slot__defragment__fix_pointers(preposition_group, symbols, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(preposition_group__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__funk);
  
  
  // adjective_group
  
  init_frame_object__8_slot__defragment__fix_pointers(adjective_group, symbols, complement, qualifier, adjunct, than, as, comparitive, question);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(adjective_group__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk);
  
  
  // verb_group
  
  init_frame_object__15_slot__defragment__fix_pointers(verb_group, symbols, imperative, en, ing, to, todel, tense, be, passive, negative, auxiliary, not_only_auxiliary, singular, plural, takes_particle);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(verb_group__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__funk);
  
  
  // combination_group
  
  init_frame_object__3_slot__defragment__fix_pointers(combination_group, symbols, transitive, preposition);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_combination_group.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(combination_group__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_combination_group.new__funk);
  
  
  // adjective_word
  
  init_frame_object__3_slot__defragment__fix_pointers(adjective_word, symbols, superlative, comparative);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(adjective_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__funk);
  
  
  // adverb_word
  
  init_frame_object__5_slot__defragment__fix_pointers(adverb_word, symbols, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(adverb_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__funk);
  
  
  // binder_word
  
  init_frame_object__1_slot__defragment__fix_pointers(binder_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(binder_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__funk);
  
  
  // classifier_word
  
  init_frame_object__1_slot__defragment__fix_pointers(classifier_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(classifier_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__funk);
  
  
  // determiner_word
  
  init_frame_object__12_slot__defragment__fix_pointers(determiner_word, symbols, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(determiner_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__funk);
  
  
  // noun_word
  
  init_frame_object__7_slot__defragment__fix_pointers(noun_word, symbols, singular, plural, mass, possessive, time_unit, time_specific);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(noun_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__funk);
  
  
  // number_word
  
  init_frame_object__3_slot__defragment__fix_pointers(number_word, symbols, singular, plural);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_number_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(number_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_number_word.new__funk);
  
  
  // number_determiner_word
  
  init_frame_object__5_slot__defragment__fix_pointers(number_determiner_word, symbols, than_modifier, as_as_modifier, at_modifier, alone);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(number_determiner_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__funk);
  
  
  // ordinal_word
  
  init_frame_object__1_slot__defragment__fix_pointers(ordinal_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(ordinal_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__funk);
  
  
  // preposition_word
  
  init_frame_object__3_slot__defragment__fix_pointers(preposition_word, symbols, combination_first, combination_second);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(preposition_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__funk);
  
  
  // pronoun_word
  
  init_frame_object__10_slot__defragment__fix_pointers(pronoun_word, symbols, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(pronoun_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__funk);
  
  
  // proper_noun_word
  
  init_frame_object__3_slot__defragment__fix_pointers(proper_noun_word, symbols, singular, plural);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(proper_noun_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__funk);
  
  
  // particle_word
  
  init_frame_object__1_slot__defragment__fix_pointers(particle_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(particle_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__funk);
  
  
  // question_adjunct_word
  
  init_frame_object__1_slot__defragment__fix_pointers(question_adjunct_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(question_adjunct_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__funk);
  
  
  // thing_pronoun_word
  
  init_frame_object__1_slot__defragment__fix_pointers(thing_pronoun_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_thing_pronoun_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(thing_pronoun_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_thing_pronoun_word.new__funk);
  
  
  // infinitive_helper_word
  
  init_frame_object__1_slot__defragment__fix_pointers(infinitive_helper_word, symbols);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_infinitive_helper_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(infinitive_helper_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_infinitive_helper_word.new__funk);
  
  
  // verb_word
  
  init_frame_object__23_slot__defragment__fix_pointers(verb_word, symbols, auxiliary, be, Do, have, will, modal, negative, question_auxiliary, third_person_singular, plural, first_person_singular, ing, en, infinitive, past, present, Main, takes_particle, transitive, transitive_two, takes_to_object, takes_subject_to_object);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_verb_word.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(verb_word__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_verb_word.new__funk);
  
  
  // parse_tree_node
  
  init_frame_object__6_slot__defragment__fix_pointers(parse_tree_node, parse_object, parent_node, previous_node, next_node, first_child_node, last_child_node);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_after__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__insert_after);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_after__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_below_no_children__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__insert_below_no_children);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_below_no_children__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.add_child__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__add_child);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.add_child__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.child_of_type_node__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__child_of_type_node);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.child_of_type_node__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_node__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__containing_type_node);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_node__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property_node__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__containing_type_with_true_property_node);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property_node__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property__set__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree_node__containing_type_with_true_property__set);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property__set__funk);
  
  
  // parse_tree
  
  init_frame_object__2_slot__defragment__fix_pointers(parse_tree, root_node, current_node);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree__new);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new_copy__symbol);
  f2__primcfunk__init__defragment__fix_pointers(parse_tree__new_copy);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new_copy__funk);
  
  
  
}

void f2__natural_language__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // clause
  
  init_frame_object__13_slot(clause, symbols, secondary, imperative, declarative, question, yes_no, wh, particle, transitive, transitive_two, subject_to_object, to_object, unmatched_relative_reference);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_clause.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(clause__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_clause.new__funk = never_gc(cfunk);}
  
  
  // wh_rank_shift_clause
  
  init_frame_object__1_slot(wh_rank_shift_clause, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_wh_rank_shift_clause.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(wh_rank_shift_clause__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_wh_rank_shift_clause.new__funk = never_gc(cfunk);}
  
  
  // noun_group
  
  init_frame_object__18_slot(noun_group, symbols, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, definite, indefinite, quantifier, singular, plural, mass, object, object_one, object_two, question);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(noun_group__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk = never_gc(cfunk);}
  
  
  // preposition_group
  
  init_frame_object__9_slot(preposition_group, symbols, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(preposition_group__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__funk = never_gc(cfunk);}
  
  
  // adjective_group
  
  init_frame_object__8_slot(adjective_group, symbols, complement, qualifier, adjunct, than, as, comparitive, question);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(adjective_group__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk = never_gc(cfunk);}
  
  
  // verb_group
  
  init_frame_object__15_slot(verb_group, symbols, imperative, en, ing, to, todel, tense, be, passive, negative, auxiliary, not_only_auxiliary, singular, plural, takes_particle);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(verb_group__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__funk = never_gc(cfunk);}
  
  
  // combination_group
  
  init_frame_object__3_slot(combination_group, symbols, transitive, preposition);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_combination_group.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(combination_group__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_combination_group.new__funk = never_gc(cfunk);}
  
  
  // adjective_word
  
  init_frame_object__3_slot(adjective_word, symbols, superlative, comparative);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(adjective_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__funk = never_gc(cfunk);}
  
  
  // adverb_word
  
  init_frame_object__5_slot(adverb_word, symbols, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(adverb_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__funk = never_gc(cfunk);}
  
  
  // binder_word
  
  init_frame_object__1_slot(binder_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(binder_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__funk = never_gc(cfunk);}
  
  
  // classifier_word
  
  init_frame_object__1_slot(classifier_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(classifier_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__funk = never_gc(cfunk);}
  
  
  // determiner_word
  
  init_frame_object__12_slot(determiner_word, symbols, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(determiner_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__funk = never_gc(cfunk);}
  
  
  // noun_word
  
  init_frame_object__7_slot(noun_word, symbols, singular, plural, mass, possessive, time_unit, time_specific);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(noun_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__funk = never_gc(cfunk);}
  
  
  // number_word
  
  init_frame_object__3_slot(number_word, symbols, singular, plural);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_number_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(number_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_number_word.new__funk = never_gc(cfunk);}
  
  
  // number_determiner_word
  
  init_frame_object__5_slot(number_determiner_word, symbols, than_modifier, as_as_modifier, at_modifier, alone);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(number_determiner_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__funk = never_gc(cfunk);}
  
  
  // ordinal_word
  
  init_frame_object__1_slot(ordinal_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(ordinal_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__funk = never_gc(cfunk);}
  
  
  // preposition_word
  
  init_frame_object__3_slot(preposition_word, symbols, combination_first, combination_second);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(preposition_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__funk = never_gc(cfunk);}
  
  
  // pronoun_word
  
  init_frame_object__10_slot(pronoun_word, symbols, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(pronoun_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__funk = never_gc(cfunk);}
  
  
  // proper_noun_word
  
  init_frame_object__3_slot(proper_noun_word, symbols, singular, plural);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(proper_noun_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__funk = never_gc(cfunk);}
  
  
  // particle_word
  
  init_frame_object__1_slot(particle_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(particle_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__funk = never_gc(cfunk);}
  
  
  // question_adjunct_word
  
  init_frame_object__1_slot(question_adjunct_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(question_adjunct_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__funk = never_gc(cfunk);}
  
  
  // thing_pronoun_word
  
  init_frame_object__1_slot(thing_pronoun_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_thing_pronoun_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(thing_pronoun_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_thing_pronoun_word.new__funk = never_gc(cfunk);}
  
  
  // infinitive_helper_word
  
  init_frame_object__1_slot(infinitive_helper_word, symbols);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_infinitive_helper_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(infinitive_helper_word__new, cfunk);  __funk2.globalenv.object_type.primobject.primobject_type_infinitive_helper_word.new__funk = never_gc(cfunk);}
  
  
  // verb_word
  
  init_frame_object__23_slot(verb_word, symbols, auxiliary, be, Do, have, will, modal, negative, question_auxiliary, third_person_singular, plural, first_person_singular, ing, en, infinitive, past, present, Main, takes_particle, transitive, transitive_two, takes_to_object, takes_subject_to_object);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_verb_word.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(verb_word__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_verb_word.new__funk = never_gc(cfunk);}
  
  
  // parse_tree_node
  
  init_frame_object__6_slot(parse_tree_node, parse_object, parent_node, previous_node, next_node, first_child_node, last_child_node);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(parse_tree_node__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.new__funk = never_gc(cfunk);}
  {char* symbol_str = "insert_after"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_after__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(parse_tree_node__insert_after, this, node, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_after__funk = never_gc(cfunk);}
  {char* symbol_str = "insert_below_no_children"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_below_no_children__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(parse_tree_node__insert_below_no_children, this, node, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.insert_below_no_children__funk = never_gc(cfunk);}
  {char* symbol_str = "add_child"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.add_child__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(parse_tree_node__add_child, this, node, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.add_child__funk = never_gc(cfunk);}
  {char* symbol_str = "child_of_type_node"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.child_of_type_node__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(parse_tree_node__child_of_type_node, this, type, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.child_of_type_node__funk = never_gc(cfunk);}
  {char* symbol_str = "containing_type_node"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_node__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(parse_tree_node__containing_type_node, this, type, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_node__funk = never_gc(cfunk);}
  {char* symbol_str = "containing_type_with_true_property_node"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property_node__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(parse_tree_node__containing_type_with_true_property_node, this, type, property, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property_node__funk = never_gc(cfunk);}
  {char* symbol_str = "containing_type_with_true_property-set"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property__set__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(parse_tree_node__containing_type_with_true_property__set, this, type, property, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree_node.containing_type_with_true_property__set__funk = never_gc(cfunk);}
  
  
  // parse_tree
  
  init_frame_object__2_slot(parse_tree, root_node, current_node);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(parse_tree__new, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new__funk = never_gc(cfunk);}
  {char* symbol_str = "new_copy"; __funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new_copy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(parse_tree__new_copy, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_parse_tree.new_copy__funk = never_gc(cfunk);}
}

void f2__natural_language__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "natural_language", "", &f2__natural_language__reinitialize_globalvars, &f2__natural_langauge__defragment__fix_pointers);
  
  f2__natural_language__reinitialize_globalvars();
}


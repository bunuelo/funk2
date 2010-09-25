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

#include "funk2.h"





// clause

def_frame_object__global__6_slot(clause, secondary, imperative, declarative, question, yes_no, wh);

f2ptr f2__clause__new(f2ptr cause, f2ptr secondary, f2ptr imperative, f2ptr declarative, f2ptr question, f2ptr yes_no, f2ptr wh) {
  return f2clause__new(cause, secondary, imperative, declarative, question, yes_no, wh);
}
def_pcfunk6(clause__new, secondary, imperative, declarative, question, yes_no, wh, return f2__clause__new(this_cause, secondary, imperative, declarative, question, yes_no, wh));


f2ptr f2clause__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2clause__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_clause.new__funk);}
  return this;
}


// noun_group

def_frame_object__global__7_slot(noun_group, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);

f2ptr f2__noun_group__new(f2ptr cause, f2ptr determiner, f2ptr ordinal, f2ptr number, f2ptr adjectives, f2ptr classifiers, f2ptr noun, f2ptr qualifiers) {
  return f2noun_group__new(cause, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);
}
def_pcfunk7(noun_group__new, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, return f2__noun_group__new(this_cause, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers));


f2ptr f2noun_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2noun_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk);}
  return this;
}


// preposition_group

def_frame_object__global__8_slot(preposition_group, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);

f2ptr f2__preposition_group__new(f2ptr cause, f2ptr complement, f2ptr locational_object, f2ptr adjunct, f2ptr agent, f2ptr question, f2ptr missing_up_relative, f2ptr missing_up_question, f2ptr relative_preposition_group) {
  return f2preposition_group__new(cause, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);
}
def_pcfunk8(preposition_group__new, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group, return f2__preposition_group__new(this_cause, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group));


f2ptr f2preposition_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2preposition_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__funk);}
  return this;
}


// adjective_group

def_frame_object__global__7_slot(adjective_group, complement, qualifier, adjunct, than, as, comparitive, question);

f2ptr f2__adjective_group__new(f2ptr cause, f2ptr complement, f2ptr qualifier, f2ptr adjunct, f2ptr than, f2ptr as, f2ptr comparitive, f2ptr question) {
  return f2adjective_group__new(cause, complement, qualifier, adjunct, than, as, comparitive, question);
}
def_pcfunk7(adjective_group__new, complement, qualifier, adjunct, than, as, comparitive, question, return f2__adjective_group__new(this_cause, complement, qualifier, adjunct, than, as, comparitive, question));


f2ptr f2adjective_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2adjective_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk);}
  return this;
}


// verb_group

def_frame_object__global__9_slot(verb_group, imperative, en, ing, to, todel, tense, be, passive, negative);

f2ptr f2__verb_group__new(f2ptr cause, f2ptr imperative, f2ptr en, f2ptr ing, f2ptr to, f2ptr todel, f2ptr tense, f2ptr be, f2ptr passive, f2ptr negative) {
  return f2verb_group__new(cause, imperative, en, ing, to, todel, tense, be, passive, negative);
}
def_pcfunk9(verb_group__new, imperative, en, ing, to, todel, tense, be, passive, negative, return f2__verb_group__new(this_cause, imperative, en, ing, to, todel, tense, be, passive, negative));


f2ptr f2verb_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2verb_group__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__funk);}
  return this;
}


// adjective_word

def_frame_object__global__3_slot(adjective_word, symbol, superlative, comparative);

f2ptr f2__adjective_word__new(f2ptr cause, f2ptr symbol, f2ptr superlative, f2ptr comparative) {
  return f2adjective_word__new(cause, symbol, superlative, comparative);
}
def_pcfunk3(adjective_word__new, symbol, superlative, comparative, return f2__adjective_word__new(this_cause, symbol, superlative, comparative));


f2ptr f2adjective_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2adjective_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__funk);}
  return this;
}


// adverb_word

def_frame_object__global__5_slot(adverb_word, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);

f2ptr f2__adverb_word__new(f2ptr cause, f2ptr symbol, f2ptr adverb_modifier, f2ptr verb_modifier, f2ptr preposition_modifier, f2ptr clause_modifier) {
  return f2adverb_word__new(cause, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);
}
def_pcfunk5(adverb_word__new, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier, return f2__adverb_word__new(this_cause, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier));


f2ptr f2adverb_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2adverb_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__funk);}
  return this;
}


// binder_word

def_frame_object__global__1_slot(binder_word, symbol);

f2ptr f2__binder_word__new(f2ptr cause, f2ptr symbol) {
  return f2binder_word__new(cause, symbol);
}
def_pcfunk1(binder_word__new, symbol, return f2__binder_word__new(this_cause, symbol));


f2ptr f2binder_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2binder_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__funk);}
  return this;
}


// classifier_word

def_frame_object__global__1_slot(classifier_word, symbol);

f2ptr f2__classifier_word__new(f2ptr cause, f2ptr symbol) {
  return f2classifier_word__new(cause, symbol);
}
def_pcfunk1(classifier_word__new, symbol, return f2__classifier_word__new(this_cause, symbol));


f2ptr f2classifier_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2classifier_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__funk);}
  return this;
}


// determiner_word

def_frame_object__global__12_slot(determiner_word, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);

f2ptr f2__determiner_word__new(f2ptr cause, f2ptr symbol, f2ptr indefinite, f2ptr question, f2ptr definite, f2ptr demonstrative, f2ptr quantifier, f2ptr incomplete_of, f2ptr negative, f2ptr no_number, f2ptr singular, f2ptr plural, f2ptr mass) {
  return f2determiner_word__new(cause, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);
}
def_pcfunk12(determiner_word__new, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass,
	     return f2__determiner_word__new(this_cause, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass));


f2ptr f2determiner_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2determiner_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__funk);}
  return this;
}


// noun_word

def_frame_object__global__7_slot(noun_word, symbol, singular, plural, mass, possessive, time_unit, time_specific);

f2ptr f2__noun_word__new(f2ptr cause, f2ptr symbol, f2ptr singular, f2ptr plural, f2ptr mass, f2ptr possessive, f2ptr time_unit, f2ptr time_specific) {
  return f2noun_word__new(cause, symbol, singular, plural, mass, possessive, time_unit, time_specific);
}
def_pcfunk7(noun_word__new, symbol, singular, plural, mass, possessive, time_unit, time_specific, return f2__noun_word__new(this_cause, symbol, singular, plural, mass, possessive, time_unit, time_specific));


f2ptr f2noun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2noun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__funk);}
  return this;
}


// number_word

def_frame_object__global__3_slot(number_word, symbol, singular, plural);

f2ptr f2__number_word__new(f2ptr cause, f2ptr symbol, f2ptr singular, f2ptr plural) {
  return f2number_word__new(cause, symbol, singular, plural);
}
def_pcfunk3(number_word__new, symbol, singular, plural, return f2__number_word__new(this_cause, symbol, singular, plural));


f2ptr f2number_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2number_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_number_word.new__funk);}
  return this;
}


// number_determiner_word

def_frame_object__global__5_slot(number_determiner_word, symbol, than_modifier, as_as_modifier, at_modifier, alone);

f2ptr f2__number_determiner_word__new(f2ptr cause, f2ptr symbol, f2ptr than_modifier, f2ptr as_as_modifier, f2ptr at_modifier, f2ptr alone) {
  return f2number_determiner_word__new(cause, symbol, than_modifier, as_as_modifier, at_modifier, alone);
}
def_pcfunk5(number_determiner_word__new, symbol, than_modifier, as_as_modifier, at_modifier, alone, return f2__number_determiner_word__new(this_cause, symbol, than_modifier, as_as_modifier, at_modifier, alone));


f2ptr f2number_determiner_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2number_determiner_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__funk);}
  return this;
}


// ordinal_word

def_frame_object__global__1_slot(ordinal_word, symbol);

f2ptr f2__ordinal_word__new(f2ptr cause, f2ptr symbol) {
  return f2ordinal_word__new(cause, symbol);
}
def_pcfunk1(ordinal_word__new, symbol, return f2__ordinal_word__new(this_cause, symbol));


f2ptr f2ordinal_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2ordinal_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__funk);}
  return this;
}


// preposition_word

def_frame_object__global__3_slot(preposition_word, symbol, combination_first, combination_second);

f2ptr f2__preposition_word__new(f2ptr cause, f2ptr symbol, f2ptr combination_first, f2ptr combination_second) {
  return f2preposition_word__new(cause, symbol, combination_first, combination_second);
}
def_pcfunk3(preposition_word__new, symbol, combination_first, combination_second, return f2__preposition_word__new(this_cause, symbol, combination_first, combination_second));


f2ptr f2preposition_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2preposition_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__funk);}
  return this;
}


// pronoun_word

def_frame_object__global__10_slot(pronoun_word, symbol, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);

f2ptr f2__pronoun_word__new(f2ptr cause, f2ptr symbol, f2ptr singular, f2ptr plural, f2ptr first_person_singular, f2ptr possessive, f2ptr subject, f2ptr object, f2ptr demonstrative, f2ptr relative_clause, f2ptr question) {
  return f2pronoun_word__new(cause, symbol, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);
}
def_pcfunk10(pronoun_word__new, symbol, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question,
	     return f2__pronoun_word__new(this_cause, symbol, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question));


f2ptr f2pronoun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2pronoun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__funk);}
  return this;
}


// proper_noun_word

def_frame_object__global__3_slot(proper_noun_word, symbols, singular, plural);

f2ptr f2__proper_noun_word__new(f2ptr cause, f2ptr symbols, f2ptr singular, f2ptr plural) {
  return f2proper_noun_word__new(cause, symbols, singular, plural);
}
def_pcfunk3(proper_noun_word__new, symbols, singular, plural, return f2__proper_noun_word__new(this_cause, symbols, singular, plural));


f2ptr f2proper_noun_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2proper_noun_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__funk);}
  return this;
}


// particle_word

def_frame_object__global__1_slot(particle_word, symbol);

f2ptr f2__particle_word__new(f2ptr cause, f2ptr symbol) {
  return f2particle_word__new(cause, symbol);
}
def_pcfunk1(particle_word__new, symbol, return f2__particle_word__new(this_cause, symbol));


f2ptr f2particle_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2particle_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__funk);}
  return this;
}


// question_adjunct_word

def_frame_object__global__1_slot(question_adjunct_word, symbol);

f2ptr f2__question_adjunct_word__new(f2ptr cause, f2ptr symbol) {
  return f2question_adjunct_word__new(cause, symbol);
}
def_pcfunk1(question_adjunct_word__new, symbol, return f2__question_adjunct_word__new(this_cause, symbol));


f2ptr f2question_adjunct_word__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2question_adjunct_word__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__funk);}
  return this;
}




// **

void f2__natural_language__reinitialize_globalvars() {
}

void f2__natural_language__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "natural_language", "", &f2__natural_language__reinitialize_globalvars);
  
  f2__natural_language__reinitialize_globalvars();
  
  
  // clause
  
  init_frame_object__6_slot(clause, secondary, imperative, declarative, question, yes_no, wh);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_clause.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(clause__new, secondary, imperative, declarative, question, yes_no, wh, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_clause.new__funk = never_gc(cfunk);}
  
  
  // noun_group
  
  init_frame_object__7_slot(noun_group, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(noun_group__new, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk = never_gc(cfunk);}
  
  
  // preposition_group
  
  init_frame_object__8_slot(preposition_group, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__8_arg(preposition_group__new, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group, cfunk, 0, "");
    __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__funk = never_gc(cfunk);}
  
  
  // adjective_group
  
  init_frame_object__7_slot(adjective_group, complement, qualifier, adjunct, than, as, comparitive, question);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(adjective_group__new, complement, qualifier, adjunct, than, as, comparitive, question, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk = never_gc(cfunk);}
  
  
  // verb_group
  
  init_frame_object__9_slot(verb_group, imperative, en, ing, to, todel, tense, be, passive, negative);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__9_arg(verb_group__new, imperative, en, ing, to, todel, tense, be, passive, negative, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_verb_group.new__funk = never_gc(cfunk);}
  
  
  // adjective_word
  
  init_frame_object__3_slot(adjective_word, symbol, superlative, comparative);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(adjective_word__new, symbol, superlative, comparative, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_adjective_word.new__funk = never_gc(cfunk);}
  
  
  // adverb_word
  
  init_frame_object__5_slot(adverb_word, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(adverb_word__new, symbol, adverb_modifier, verb_modifier, preposition_modifier, clause_modifier, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_adverb_word.new__funk = never_gc(cfunk);}
  
  
  // binder_word
  
  init_frame_object__1_slot(binder_word, symbol);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(binder_word__new, symbol, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_binder_word.new__funk = never_gc(cfunk);}
  
  
  // classifier_word
  
  init_frame_object__1_slot(classifier_word, symbol);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(classifier_word__new, symbol, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_classifier_word.new__funk = never_gc(cfunk);}
  
  
  // determiner_word
  
  init_frame_object__12_slot(determiner_word, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__12_arg(determiner_word__new, symbol, indefinite, question, definite, demonstrative, quantifier, incomplete_of, negative, no_number, singular, plural, mass, cfunk, 0, "");
    __funk2.globalenv.object_type.primobject.primobject_type_determiner_word.new__funk = never_gc(cfunk);}
  
  
  // noun_word
  
  init_frame_object__7_slot(noun_word, symbol, singular, plural, mass, possessive, time_unit, time_specific);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(noun_word__new, symbol, singular, plural, mass, possessive, time_unit, time_specific, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_noun_word.new__funk = never_gc(cfunk);}
  
  
  // number_word
  
  init_frame_object__3_slot(number_word, symbol, singular, plural);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_number_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(number_word__new, symbol, singular, plural, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_number_word.new__funk = never_gc(cfunk);}
  
  
  // number_determiner_word
  
  init_frame_object__5_slot(number_determiner_word, symbol, than_modifier, as_as_modifier, at_modifier, alone);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(number_determiner_word__new, symbol, than_modifier, as_as_modifier, at_modifier, alone, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_number_determiner_word.new__funk = never_gc(cfunk);}
  
  
  // ordinal_word
  
  init_frame_object__1_slot(ordinal_word, symbol);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ordinal_word__new, symbol, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_ordinal_word.new__funk = never_gc(cfunk);}
  
  
  // preposition_word
  
  init_frame_object__3_slot(preposition_word, symbol, combination_first, combination_second);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(preposition_word__new, symbol, combination_first, combination_second, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_preposition_word.new__funk = never_gc(cfunk);}
  
  
  // pronoun_word
  
  init_frame_object__10_slot(pronoun_word, symbol, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__10_arg(pronoun_word__new, symbol, singular, plural, first_person_singular, possessive, subject, object, demonstrative, relative_clause, question, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_pronoun_word.new__funk = never_gc(cfunk);}
  
  
  // proper_noun_word
  
  init_frame_object__3_slot(proper_noun_word, symbols, singular, plural);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(proper_noun_word__new, symbols, singular, plural, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_proper_noun_word.new__funk = never_gc(cfunk);}
  
  
  // particle_word
  
  init_frame_object__1_slot(particle_word, symbol);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(particle_word__new, symbol, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_particle_word.new__funk = never_gc(cfunk);}
  
  
  // question_adjunct_word
  
  init_frame_object__1_slot(question_adjunct_word, symbol);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(question_adjunct_word__new, symbol, cfunk, 0, "");  __funk2.globalenv.object_type.primobject.primobject_type_question_adjunct_word.new__funk = never_gc(cfunk);}
  
  
}


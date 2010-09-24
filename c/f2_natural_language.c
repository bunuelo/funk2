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
  f2ptr this = f2verb__primobject_type__new(cause);
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
  f2ptr this = f2verb__primobject_type__new(cause);
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
  f2ptr this = f2verb__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk);}
  return this;
}


// verb

def_frame_object__global__10_slot(verb, symbol, imperative, en, ing, to, todel, tense, be, passive, negative);

f2ptr f2__verb__new(f2ptr cause, f2ptr symbol, f2ptr imperative, f2ptr en, f2ptr ing, f2ptr to, f2ptr todel, f2ptr tense, f2ptr be, f2ptr passive, f2ptr negative) {
  return f2verb__new(cause, symbol, imperative, en, ing, to, todel, tense, be, passive, negative);
}
def_pcfunk10(verb__new, symbol, imperative, en, ing, to, todel, tense, be, passive, negative, return f2__verb__new(this_cause, symbol, imperative, en, ing, to, todel, tense, be, passive, negative));


f2ptr f2verb__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2verb__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_verb.new__funk);}
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
  {f2__primcfunk__init__with_c_cfunk_var__8_arg(preposition_group__new, complement, locational_object, adjunct, agent, question, missing_up_relative, missing_up_question, relative_preposition_group, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_preposition_group.new__funk = never_gc(cfunk);}
  
  
  // adjective_group
  
  init_frame_object__7_slot(adjective_group, complement, qualifier, adjunct, than, as, comparitive, question);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(adjective_group__new, complement, qualifier, adjunct, than, as, comparitive, question, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_adjective_group.new__funk = never_gc(cfunk);}
  
  
  // verb
  
  init_frame_object__10_slot(verb, symbol, imperative, en, ing, to, todel, tense, be, passive, negative);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_verb.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__10_arg(verb__new, symbol, imperative, en, ing, to, todel, tense, be, passive, negative, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_verb.new__funk = never_gc(cfunk);}
  
  
}


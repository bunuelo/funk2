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





// noun_group

def_frame_object__global__7_slot(noun_group, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);

f2ptr f2__noun_group__new(f2ptr cause, f2ptr determiner, f2ptr ordinal, f2ptr number, f2ptr adjectives, f2ptr classifiers, f2ptr noun, f2ptr qualifiers) {
  return f2noun_group__new(cause, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);
}
def_pcfunk7(noun_group__new, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers, return f2__verb__new(this_cause, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers));


f2ptr f2noun_group__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2verb__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk);}
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


// sentence

def_frame_object__global__4_slot(sentence, subject, verb, direct_object, prepositional_frame);

f2ptr f2__sentence__new(f2ptr cause, f2ptr subject, f2ptr verb, f2ptr direct_object, f2ptr prepositional_frame) {
  return f2sentence__new(cause, subject, verb, direct_object, prepositional_frame);
}
def_pcfunk4(sentence__new, subject, verb, direct_object, prepositional_frame, return f2__sentence__new(this_cause, subject, verb, direct_object, prepositional_frame));


f2ptr f2sentence__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2sentence__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_sentence.new__funk);}
  return this;
}


// **

void f2__natural_language__reinitialize_globalvars() {
}

void f2__natural_language__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "natural_language", "", &f2__natural_language__reinitialize_globalvars);
  
  f2__natural_language__reinitialize_globalvars();
  
  
  // noun_group
  
  init_frame_object__7_slot(noun_group, determiner, ordinal, number, adjectives, classifiers, noun, qualifiers);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(noun_group__new, symbol, imperative, en, ing, to, todel, tense, be, passive, negative, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_noun_group.new__funk = never_gc(cfunk);}
  
  
  // verb
  
  init_frame_object__10_slot(verb, symbol, imperative, en, ing, to, todel, tense, be, passive, negative);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_verb.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__10_arg(verb__new, symbol, imperative, en, ing, to, todel, tense, be, passive, negative, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_verb.new__funk = never_gc(cfunk);}
  
  
  // sentence
  
  init_frame_object__4_slot(sentence, subject, verb, direct_object, prepositional_frame);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_sentence.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(sentence__new, subject, verb, direct_object, prepositional_frame, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_sentence.new__funk = never_gc(cfunk);}
  
}


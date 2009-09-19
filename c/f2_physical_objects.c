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

#include "funk2.h"

// physical_rotation

def_primobject_1_slot(physical_rotation, array);

f2ptr f2__physical_rotation__new(f2ptr cause, f2ptr array) {return f2physical_rotation__new(cause, array);}
def_pcfunk1(physical_rotation__new, array, return f2__physical_rotation__new(this_cause, array));

f2ptr f2__physical_rotation__new_identity(f2ptr cause) {
  f2ptr array = raw__array__new(cause, 9);
  raw__array__elt__set(cause, array, 0, f2double__new(cause, 1));
  raw__array__elt__set(cause, array, 1, f2double__new(cause, 0));
  raw__array__elt__set(cause, array, 2, f2double__new(cause, 0));
  raw__array__elt__set(cause, array, 3, f2double__new(cause, 0));
  raw__array__elt__set(cause, array, 4, f2double__new(cause, 1));
  raw__array__elt__set(cause, array, 5, f2double__new(cause, 0));
  raw__array__elt__set(cause, array, 6, f2double__new(cause, 0));
  raw__array__elt__set(cause, array, 7, f2double__new(cause, 0));
  raw__array__elt__set(cause, array, 8, f2double__new(cause, 1));
  return f2__physical_rotation__new(cause, array);
}
def_pcfunk0(physical_rotation__new_identity, return f2__physical_rotation__new_identity(this_cause));


// physical_position

def_primobject_3_slot(physical_position, x, y, z);

f2ptr f2__physical_position__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {
  double x__d; if (raw__double__is_type(cause, x)) {x__d = (double)f2double__d(x, cause);} else if (raw__integer__is_type(cause, x)) {x__d = (double)f2integer__i(x, cause);} else {return f2larva__new(cause, 1);}
  double y__d; if (raw__double__is_type(cause, y)) {y__d = (double)f2double__d(y, cause);} else if (raw__integer__is_type(cause, y)) {y__d = (double)f2integer__i(y, cause);} else {return f2larva__new(cause, 1);}
  double z__d; if (raw__double__is_type(cause, z)) {z__d = (double)f2double__d(z, cause);} else if (raw__integer__is_type(cause, z)) {z__d = (double)f2integer__i(z, cause);} else {return f2larva__new(cause, 1);}
  return f2physical_position__new(cause, f2double__new(cause, x__d), f2double__new(cause, y__d), f2double__new(cause, z__d));
}
def_pcfunk3(physical_position__new, x, y, z, return f2__physical_position__new(this_cause, x, y, z));


// physical_object

def_primobject_4_slot(physical_object, position, text, texture_name, size);

f2ptr f2__physical_object__new(f2ptr cause, f2ptr position, f2ptr text, f2ptr texture_name, f2ptr size) {return f2physical_object__new(cause, position, text, texture_name, size);}
def_pcfunk4(physical_object__new, position, text, texture_name, size, return f2__physical_object__new(this_cause, position, text, texture_name, size));


// physical_person

def_primobject_7_slot(physical_person, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);

f2ptr f2__physical_person__new(f2ptr cause, f2ptr body, f2ptr torso_clothing, f2ptr leg_clothing, f2ptr left_foot_clothing, f2ptr right_foot_clothing, f2ptr left_hand_object, f2ptr right_hand_object) {return f2physical_object__new(cause, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);}
def_pcfunk7(physical_object__new, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object, return f2__physical_object__new(this_cause, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object));


// physical_scene

def_primobject_2_slot(physical_scene, background_texture, physical_objects);

f2ptr f2__physical_scene__new(f2ptr cause, f2ptr background_texture, f2ptr physical_objects) {return f2physical_scene__new(cause, background_texture, physical_objects);}
def_pcfunk2(physical_scene__new, background_texture, physical_objects, return f2__physical_scene__new(this_cause, background_texture, physical_objects));


// **

void f2__physical_objects__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __physical_rotation__symbol = new__symbol(cause, "physical_rotation");
  __physical_position__symbol = new__symbol(cause, "physical_position");
  __physical_object__symbol   = new__symbol(cause, "physical_object");
  __physical_scene__symbol    = new__symbol(cause, "physical_scene");
}

void f2__physical_objects__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "physical_objects", "", &f2__physical_objects__reinitialize_globalvars);
  
  f2__physical_objects__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // physical_rotation
  initialize_primobject_1_slot(physical_rotation, array);
  f2__primcfunk__init__0(physical_rotation__new_identity, "glwindow cfunk declared in f2_glwindow.c");
  
  // physical_position
  initialize_primobject_3_slot(physical_position, x, y, z);
  
  // physical_object
  initialize_primobject_4_slot(physical_object, position, text, texture_name, size);
  
  // physical_person
  initialize_primobject_7_slot(physical_person, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);
  
  // physical_scene
  initialize_primobject_2_slot(physical_scene, background_texture, physical_objects);
}


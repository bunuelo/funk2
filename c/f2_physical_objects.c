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

f2ptr raw__physical_rotation__new_from_c_double_array(f2ptr cause, double* array) {
  f2ptr this__array = raw__array__new(cause, 9);
  int i;
  for (i = 0; i < 9; i ++) {
    raw__array__elt__set(cause, this__array, i, f2double__new(cause, array[i]));
  }
  return f2__physical_rotation__new(cause, this__array);
}

void raw__physical_rotation__to_c_double_array(f2ptr cause, f2ptr this, double* array) {
  f2ptr this__array = f2__physical_rotation__array(cause, this);
  int i;
  for (i = 0; i < 9; i ++) {
    f2ptr elt = raw__array__elt(cause, this__array, i);
    array[i] = raw__number__to_double(cause, elt);
  }
}

f2ptr f2__physical_rotation__new_identity(f2ptr cause) {
  double array[9] = {1,0,0,
		     0,1,0,
		     0,0,1};
  return f2__physical_rotation__new_from_c_double_array(cause, array);
}
def_pcfunk0(physical_rotation__new_identity, return f2__physical_rotation__new_identity(this_cause));

f2ptr raw__physical_rotation__new_rotation_around_z_axis(f2ptr cause, double radians) {
  double c_array[9];
  c_array[0] =  cos(radians);
  c_array[1] = -sin(radians);
  c_array[2] =  0;
  c_array[3] =  sin(radians);
  c_array[4] =  cos(radians);
  c_array[5] =  0;
  c_array[6] =  0;
  c_array[7] =  0;
  c_array[8] =  1;
  return raw__physical_rotation__new_from_c_double_array(cause, c_array);
}

f2ptr raw__physical_rotation__new_rotation_around_y_axis(f2ptr cause, double radians) {
  double c_array[9];
  c_array[0] =  cos(radians);
  c_array[1] =  0;
  c_array[2] =  sin(radians);
  c_array[3] =  0;
  c_array[4] =  1;
  c_array[5] =  0;
  c_array[6] = -sin(radians);
  c_array[7] =  0;
  c_array[8] =  cos(radians);
  return raw__physical_rotation__new_from_c_double_array(cause, c_array);
}

f2ptr raw__physical_rotation__new_rotation_around_x_axis(f2ptr cause, double radians) {
  double c_array[9];
  c_array[0] =  1;
  c_array[1] =  0;
  c_array[2] =  0;
  c_array[3] =  0;
  c_array[4] =  cos(radians);
  c_array[5] = -sin(radians);
  c_array[6] =  0;
  c_array[7] =  sin(radians);
  c_array[8] =  cos(radians);
  return raw__physical_rotation__new_from_c_double_array(cause, c_array);
}


// physical_position

def_primobject_3_slot(physical_position, x, y, z);

f2ptr f2__physical_position__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {
  if ((! raw__number__is_type(cause, x)) ||
      (! raw__number__is_type(cause, y)) ||
      (! raw__number__is_type(cause, z))) {
    return f2larva__new(cause, 1);
  }
  double x__d = raw__number__to_double(cause, x);
  double y__d = raw__number__to_double(cause, y);
  double z__d = raw__number__to_double(cause, x);
  return f2physical_position__new(cause, f2double__new(cause, x__d), f2double__new(cause, y__d), f2double__new(cause, z__d));
}
def_pcfunk3(physical_position__new, x, y, z, return f2__physical_position__new(this_cause, x, y, z));


// physical_object

def_primobject_5_slot(physical_object, position, rotation, text, texture_name, size);

f2ptr f2__physical_object__new(f2ptr cause, f2ptr position, f2ptr rotation, f2ptr text, f2ptr texture_name, f2ptr size) {return f2physical_object__new(cause, position, rotation, text, texture_name, size);}
def_pcfunk5(physical_object__new, position, rotation, text, texture_name, size, return f2__physical_object__new(this_cause, position, rotation, text, texture_name, size));


// physical_person

def_primobject_7_slot(physical_person, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);

f2ptr f2__physical_person__new(f2ptr cause, f2ptr body, f2ptr torso_clothing, f2ptr leg_clothing, f2ptr left_foot_clothing, f2ptr right_foot_clothing, f2ptr left_hand_object, f2ptr right_hand_object) {return f2physical_person__new(cause, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);}
def_pcfunk7(physical_person__new, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object, return f2__physical_person__new(this_cause, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object));


// physical_scene

def_primobject_2_slot(physical_scene, background_texture, physical_things);

f2ptr f2__physical_scene__new(f2ptr cause, f2ptr background_texture, f2ptr physical_things) {return f2physical_scene__new(cause, background_texture, physical_things);}
def_pcfunk2(physical_scene__new, background_texture, physical_things, return f2__physical_scene__new(this_cause, background_texture, physical_things));


// **

void f2__physical_objects__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __physical_rotation__symbol = new__symbol(cause, "physical_rotation");
  __physical_position__symbol = new__symbol(cause, "physical_position");
  __physical_object__symbol   = new__symbol(cause, "physical_object");
  __physical_person__symbol   = new__symbol(cause, "physical_person");
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
  initialize_primobject_5_slot(physical_object, position, rotation, text, texture_name, size);
  
  // physical_person
  initialize_primobject_7_slot(physical_person, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);
  
  // physical_scene
  initialize_primobject_2_slot(physical_scene, background_texture, physical_things);
}


// 
// Copyright (c) 2007-2011 Bo Morgan.
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
    array[i] = raw__number__as__raw_double(cause, elt);
  }
}

f2ptr f2__physical_rotation__new_identity(f2ptr cause) {
  double array[9] = {1,0,0,
		     0,1,0,
		     0,0,1};
  return raw__physical_rotation__new_from_c_double_array(cause, array);
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

f2ptr f2__physical_rotation__new_rotation_around_z_axis(f2ptr cause, f2ptr radians) {
  double c_radians = raw__number__as__raw_double(cause, radians);
  return raw__physical_rotation__new_rotation_around_z_axis(cause, c_radians);
}
def_pcfunk1(physical_rotation__new_rotation_around_z_axis, radians, return f2__physical_rotation__new_rotation_around_z_axis(this_cause, radians));

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

f2ptr f2__physical_rotation__new_rotation_around_y_axis(f2ptr cause, f2ptr radians) {
  double c_radians = raw__number__as__raw_double(cause, radians);
  return raw__physical_rotation__new_rotation_around_y_axis(cause, c_radians);
}
def_pcfunk1(physical_rotation__new_rotation_around_y_axis, radians, return f2__physical_rotation__new_rotation_around_y_axis(this_cause, radians));

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

f2ptr f2__physical_rotation__new_rotation_around_x_axis(f2ptr cause, f2ptr radians) {
  double c_radians = raw__number__as__raw_double(cause, radians);
  return raw__physical_rotation__new_rotation_around_x_axis(cause, c_radians);
}
def_pcfunk1(physical_rotation__new_rotation_around_x_axis, radians, return f2__physical_rotation__new_rotation_around_x_axis(this_cause, radians));

f2ptr f2__physical_rotation__multiply(f2ptr cause, f2ptr this, f2ptr that) {
  double this__c_array[9];
  double that__c_array[9];
  double  new__c_array[9];
  raw__physical_rotation__to_c_double_array(cause, this, this__c_array);
  raw__physical_rotation__to_c_double_array(cause, that, that__c_array);
  {
    int iy;
    for (iy = 0; iy < 3; iy ++) {
      int ix;
      for (ix = 0; ix < 3; ix ++) {
	new__c_array[((iy << 1) + iy) + ix] = 0;
	{
	  int j;
	  for (j = 0; j < 3; j ++) {
	    new__c_array[((iy << 1) + iy) + ix] += (this__c_array[((iy << 1) + iy) + j] * that__c_array[((j << 1) + j) + ix]);
	  }
	}
      }
    }
  }
  return raw__physical_rotation__new_from_c_double_array(cause, new__c_array);
}
def_pcfunk2(physical_rotation__multiply, this, that, return f2__physical_rotation__multiply(this_cause, this, that));

// physical_position

def_primobject_3_slot(physical_position, x, y, z);

f2ptr f2__physical_position__new(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {
  double x__d = raw__number__as__raw_double(cause, x);
  double y__d = raw__number__as__raw_double(cause, y);
  double z__d = raw__number__as__raw_double(cause, z);
  return f2physical_position__new(cause, f2double__new(cause, x__d), f2double__new(cause, y__d), f2double__new(cause, z__d));
}
def_pcfunk3(physical_position__new, x, y, z, return f2__physical_position__new(this_cause, x, y, z));


// physical_transform

def_primobject_3_slot(physical_transform, position, rotation, scale);

f2ptr f2__physical_transform__new(f2ptr cause, f2ptr position, f2ptr rotation, f2ptr scale) {return f2physical_transform__new(cause, position, rotation, scale);}
def_pcfunk3(physical_transform__new, position, rotation, scale, return f2__physical_transform__new(this_cause, position, rotation, scale));

f2ptr f2__physical_transform__new_identity(f2ptr cause) {
  f2ptr position = f2__physical_position__new(cause, f2double__new(cause, 0.0), f2double__new(cause, 0.0), f2double__new(cause, 0.0));
  f2ptr rotation = f2__physical_rotation__new_identity(cause);
  f2ptr scale    = f2double__new(cause, 1.0);
  return f2__physical_transform__new(cause, position, rotation, scale);
}
def_pcfunk0(physical_transform__new_identity, return f2__physical_transform__new_identity(this_cause));


// physical_texture

def_primobject_2_slot(physical_texture, transform, texture_name);

f2ptr f2__physical_texture__new(f2ptr cause, f2ptr transform, f2ptr texture_name) {return f2physical_texture__new(cause, transform, texture_name);}
def_pcfunk2(physical_texture__new, transform, texture_name, return f2__physical_texture__new(this_cause, transform, texture_name));


// physical_object

def_frame_object__global__5_slot(physical_object, transform, text, texture, part_place_frame, agent);

boolean_t raw__physical_object__interface_supported(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr frame = thing;
  return (raw__frame__check_has_type_slot(cause, frame, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "transform"))        &&
	  raw__frame__check_has_type_slot(cause, frame, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "text"))             &&
	  raw__frame__check_has_type_slot(cause, frame, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "texture"))          &&
	  raw__frame__check_has_type_slot(cause, frame, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "part_place_frame")) &&
	  raw__frame__check_has_type_slot(cause, frame, __funk2.primobject__frame.variable__symbol, new__symbol(cause, "agent")));
}

f2ptr f2__physical_object__interface_supported(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__physical_object__interface_supported(cause, thing));
}
def_pcfunk1(physical_object__interface_supported, thing, return f2__physical_object__interface_supported(this_cause, thing));

// physical_place

def_primobject_2_slot(physical_place, transform, thing);

f2ptr f2__physical_place__new(f2ptr cause, f2ptr transform, f2ptr thing) {return f2physical_place__new(cause, transform, thing);}
def_pcfunk2(physical_place__new, transform, thing, return f2__physical_place__new(this_cause, transform, thing));


// physical_scene

def_primobject_2_slot(physical_scene, background_texture, physical_things);

f2ptr f2__physical_scene__new(f2ptr cause, f2ptr background_texture, f2ptr physical_things) {return f2physical_scene__new(cause, background_texture, physical_things);}
def_pcfunk2(physical_scene__new, background_texture, physical_things, return f2__physical_scene__new(this_cause, background_texture, physical_things));


// **

void f2__physical_objects__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  __physical_rotation__symbol  = new__symbol(cause, "physical_rotation");
  __physical_position__symbol  = new__symbol(cause, "physical_position");
  __physical_transform__symbol = new__symbol(cause, "physical_transform");
  __physical_texture__symbol   = new__symbol(cause, "physical_texture");
  __physical_place__symbol     = new__symbol(cause, "physical_place");
  __physical_scene__symbol     = new__symbol(cause, "physical_scene");
}

void f2__physical_objects__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "physical_objects", "", &f2__physical_objects__reinitialize_globalvars);
  
  f2__physical_objects__reinitialize_globalvars();
  
  f2ptr cause = initial_cause();
  
  // physical_rotation
  initialize_primobject_1_slot(physical_rotation, array);
  f2__primcfunk__init__0(physical_rotation__new_identity, "physical_objects cfunk declared in f2_physical_objects.c");
  f2__primcfunk__init__1(physical_rotation__new_rotation_around_z_axis, radians, "physical_objects cfunk declared in f2_physical_objects.c");
  f2__primcfunk__init__1(physical_rotation__new_rotation_around_y_axis, radians, "physical_objects cfunk declared in f2_physical_objects.c");
  f2__primcfunk__init__1(physical_rotation__new_rotation_around_x_axis, radians, "physical_objects cfunk declared in f2_physical_objects.c");
  f2__primcfunk__init__2(physical_rotation__multiply, this, that, "physical_objects cfunk declared in f2_physical_objects.c");
  
  // physical_position
  initialize_primobject_3_slot(physical_position, x, y, z);
  
  // physical_transform
  initialize_primobject_3_slot(physical_transform, position, rotation, scale);
  f2__primcfunk__init__0(physical_transform__new_identity, "physical_objects cfunk declared in f2_physical_objects.c");
  
  // physical_texture
  initialize_primobject_2_slot(physical_texture, transform, texture_name);
  
  // physical_object
  init_frame_object__5_slot(physical_object, transform, text, texture, part_place_frame, agent);
  f2__primcfunk__init__1(physical_object__interface_supported, thing, "physical_objects cfunk declared in f2_physical_objects.c");
  
  // physical_place
  initialize_primobject_2_slot(physical_place, transform, thing);
  
  // physical_scene
  initialize_primobject_2_slot(physical_scene, background_texture, physical_things);
}


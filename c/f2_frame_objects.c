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

// physical_sim_object

def_frame_object__global__4_slot(physical_sim_object, position, velocity, mass, shape);


// **

void f2__frame_objects__reinitialize_globalvars() {
}

void f2__frame_objects__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "frame_objects", "", &f2__frame_objects__reinitialize_globalvars);
  
  f2__frame_objects__reinitialize_globalvars();
  
  // physical_sim_object
  
  f2ptr cause = initial_cause();
  
  init_frame_object__4_slot(physical_sim_object, position, velocity, mass, shape);
  
}


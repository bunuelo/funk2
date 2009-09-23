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

#ifndef F2__PHYSICAL_OBJECTS__TYPES__H
#define F2__PHYSICAL_OBJECTS__TYPES__H

#include "f2_primobjects.h"

typedef struct funk2_object_type__physical_rotation__slot_s funk2_object_type__physical_rotation__slot_t;
declare_object_type_1_slot(physical_rotation, array, );

typedef struct funk2_object_type__physical_position__slot_s funk2_object_type__physical_position__slot_t;
declare_object_type_3_slot(physical_position, x, y, z, );

typedef struct funk2_object_type__physical_transform__slot_s funk2_object_type__physical_transform__slot_t;
declare_object_type_3_slot(physical_transform, position, rotation, scale, );

typedef struct funk2_object_type__physical_object__slot_s funk2_object_type__physical_object__slot_t;
declare_object_type_3_slot(physical_object, transform, text, texture_name, );

typedef struct funk2_object_type__physical_place__slot_s funk2_object_type__physical_place__slot_t;
declare_object_type_2_slot(physical_place, transform, thing, );

typedef struct funk2_object_type__physical_person__slot_s funk2_object_type__physical_person__slot_t;
declare_object_type_7_slot(physical_person, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object, );

typedef struct funk2_object_type__physical_scene__slot_s funk2_object_type__physical_scene__slot_t;
declare_object_type_2_slot(physical_scene, background_texture, physical_things, );

#endif // F2__PHYSICAL_OBJECTS__TYPES__H

#ifndef F2__PHYSICAL_OBJECTS__H
#define F2__PHYSICAL_OBJECTS__H

declare_primobject_1_slot(physical_rotation, array);
declare_primobject_3_slot(physical_position, x, y, z);
declare_primobject_3_slot(physical_transform, position, rotation, scale);
declare_primobject_3_slot(physical_object, transform, text, texture_name);
declare_primobject_2_slot(physical_place, transform, thing);
declare_primobject_7_slot(physical_person, body, torso_clothing, leg_clothing, left_foot_clothing, right_foot_clothing, left_hand_object, right_hand_object);
declare_primobject_2_slot(physical_scene, background_texture, physical_things);

// **

void f2__physical_objects__initialize();

#endif // F2__PHYSICAL_OBJECTS__H

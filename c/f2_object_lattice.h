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

#ifndef F2__OBJECT_LATTICE__TYPE__H
#define F2__OBJECT_LATTICE__TYPE__H

// object_lattice
typedef struct funk2_object_type__object_lattice__slot_s  funk2_object_type__object_lattice__slot_t;
declare_object_type_1_slot(object_lattice, lattice_node_hash, );

#endif // F2__OBJECT_LATTICE__TYPE__H


#ifndef F2__OBJECT_LATTICE__H
#define F2__OBJECT_LATTICE__H

#include "f2_primobjects.h"

// object_lattice
declare_primobject_1_slot(object_lattice, lattice_node_hash);

// **

void f2__object_lattice__initialize();

#endif // F2__OBJECT_LATTICE__H

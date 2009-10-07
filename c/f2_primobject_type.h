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

#ifndef F2__PRIMOBJECT_TYPE__H
#define F2__PRIMOBJECT_TYPE__H

declare_frame_object_1_slot(primobject_type, parents);

//f2ptr    f2__primobject_type__new(f2ptr cause, f2ptr parents);
f2ptr      f2__primobject_type__add_slot_type(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name, f2ptr funkable);
f2ptr      f2__primobject_type__lookup_slot_type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name);
f2ptr      f2__primobject_type__type_funk__slot_names(f2ptr cause, f2ptr this, f2ptr type_name);
boolean_t raw__primobject_type__is_type_or_has_parent_type(f2ptr cause, f2ptr this, f2ptr type_name);
f2ptr      f2__primobject_type__is_type_or_has_parent_type(f2ptr cause, f2ptr this, f2ptr type_name);

// **

void f2__primobject_type__reinitialize_globalvars();
void f2__primobject_type__initialize();

#endif // F2__PRIMOBJECT_TYPE__H


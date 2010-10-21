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

#ifndef F2__CORE_EXTENSION__TYPES__H
#define F2__CORE_EXTENSION__TYPES__H

// core_extension

typedef struct funk2_object_type__core_extension__slot_s funk2_object_type__core_extension__slot_t;
struct funk2_object_type__core_extension__slot_s {
  f2ptr initialize__symbol;
  f2ptr initialize__funk;
  f2ptr destroy__symbol;
  f2ptr destroy__funk;
  f2ptr assure_initialized__symbol;
  f2ptr assure_initialized__funk;
};

// core_extension_handler

typedef struct funk2_object_type__core_extension_handler__slot_s funk2_object_type__core_extension_handler__slot_t;
struct funk2_object_type__core_extension_handler__slot_s {
  f2ptr add_new_core_extension__symbol;
  f2ptr add_new_core_extension__funk;
  f2ptr lookup_core_extension__symbol;
  f2ptr lookup_core_extension__funk;
};

#endif // F2__CORE_EXTENSION__TYPES__H

#ifndef F2__CORE_EXTENSION__H
#define F2__CORE_EXTENSION__H

#include "f2_primfunks.h"


// core_extension

declare_frame_object_3_slot(core_extension, name, filename, initialized);

f2ptr f2core_extension__primobject_type__new_aux(f2ptr cause);


// core_extension_handler

declare_frame_object_1_slot(core_extension_handler, core_extension_name_hash);

f2ptr raw__core_extension_handler__new(                   f2ptr cause);
f2ptr  f2__core_extension_handler__new(                   f2ptr cause);
f2ptr raw__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename);
f2ptr  f2__core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr this, f2ptr name, f2ptr filename);
f2ptr raw__core_extension_handler__lookup_core_extension( f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__core_extension_handler__lookup_core_extension( f2ptr cause, f2ptr this, f2ptr name);

f2ptr f2core_extension_handler__primobject_type__new_aux(f2ptr cause);


// global_core_extension_handler

f2ptr f2__global_core_extension_handler__add_new_core_extension(f2ptr cause, f2ptr name, f2ptr filename);
f2ptr f2__global_core_extension_handler__lookup_core_extension( f2ptr cause, f2ptr name);

// **

void f2__core_extension__initialize_module();


#endif // F2__CORE_EXTENSION__H


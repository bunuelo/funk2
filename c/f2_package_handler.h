// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__PACKAGE_HANDLER__TYPES__H
#define F2__PACKAGE_HANDLER__TYPES__H

#include "f2_primobjects.h"

// package_handler

typedef struct funk2_object_type__package_handler__slot_s funk2_object_type__package_handler__slot_t;
declare_object_type_2_slot(package_handler,
			   package_frame,
			   package_search_paths,
			   f2ptr lookup_package__symbol;
			   f2ptr lookup_package__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PACKAGE_HANDLER__TYPES__H


#ifndef F2__PACKAGE_HANDLER__H
#define F2__PACKAGE_HANDLER__H

#include "f2_primobjects.h"


// package_handler

declare_primobject_2_slot(package_handler,
			  package_frame,
			  package_search_paths);

f2ptr  f2__package_handler__new           (f2ptr cause);
f2ptr raw__package_handler__lookup_package(f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__package_handler__lookup_package(f2ptr cause, f2ptr this, f2ptr name);

f2ptr f2package_handler__primobject_type__new_aux(f2ptr cause);


// global_package_handler

f2ptr f2__global_package_handler                (f2ptr cause);
f2ptr f2__global_package_handler__lookup_package(f2ptr cause, f2ptr name);

// **

void f2__package_handler__initialize();

#endif // F2__PACKAGE_HANDLER__H


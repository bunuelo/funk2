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

#ifndef F2__PACKAGE__TYPES__H
#define F2__PACKAGE__TYPES__H

#include "f2_primobjects.h"

// source_expression

typedef struct funk2_object_type__source_expression__slot_s funk2_object_type__source_expression__slot_t;
declare_object_type_6_slot(source_expression,
			   body, first_line, last_line, first_column, last_column, subexpressions,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// source

typedef struct funk2_object_type__source__slot_s funk2_object_type__source__slot_t;
declare_object_type_1_slot(source,
			   code,
			   );

// package

typedef struct funk2_object_type__package__slot_s funk2_object_type__package__slot_t;
declare_object_type_4_slot(package,
			   pathname,
			   name,
			   package_dependencies,
			   source_dependencies,
			   );

#endif // F2__PACKAGE__TYPES__H


#ifndef F2__PACKAGE__H
#define F2__PACKAGE__H

#include "f2_primobjects.h"

// source_expression

declare_primobject_6_slot(source_expression,
			  body, first_line, last_line, first_column, last_column, subexpressions
			  );

f2ptr f2source_expression__primobject_type__new_aux(f2ptr cause);


// source

declare_primobject_1_slot(source,
			  code
			  );

f2ptr f2source__primobject_type__new_aux(f2ptr cause);


// package

declare_primobject_4_slot(package,
			  pathname,
			  name,
			  package_dependencies,
			  source_dependencies
			  );

f2ptr f2package__primobject_type__new_aux(f2ptr cause);

// **

void f2__package__initialize();

#endif // F2__PACKAGE__H


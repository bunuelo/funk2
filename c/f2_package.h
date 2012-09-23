// 
// Copyright (c) 2007-2012 Bo Morgan.
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
declare_object_type_7_slot(source_expression,
			   body, filename, first_line, last_line, first_column, last_column, subexpressions,
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
declare_object_type_15_slot(package,
			    pathname,
			    name,
			    package_dependencies_cmutex,
			    package_dependencies,
			    source_dependencies_cmutex,
			    source_dependencies,
			    load_cmutex,
			    load_fiber,
			    object_types_defined_set,
			    loaded_all_dependencies_time,
			    documentation,
			    binary_dependencies_cmutex,
			    binary_dependencies,
			    dynamic_library_dependencies_cmutex,
			    dynamic_library_dependencies,
			    f2ptr add_package_dependency__symbol;
			    f2ptr add_package_dependency__funk;
			    f2ptr add_source_dependency__symbol;
			    f2ptr add_source_dependency__funk;
			    f2ptr add_binary_dependency__symbol;
			    f2ptr add_binary_dependency__funk;
			    f2ptr add_dynamic_library_dependency__symbol;
			    f2ptr add_dynamic_library_dependency__funk;
			    f2ptr dependency_graph__symbol;
			    f2ptr dependency_graph__funk;
			    f2ptr terminal_print_with_frame__symbol;
			    f2ptr terminal_print_with_frame__funk;
			    );

#endif // F2__PACKAGE__TYPES__H


#ifndef F2__PACKAGE__H
#define F2__PACKAGE__H

#include "f2_primobjects.h"

// source_expression

declare_primobject_7_slot(source_expression,
			  body, filename, first_line, last_line, first_column, last_column, subexpressions
			  );

f2ptr f2source_expression__primobject_type__new_aux(f2ptr cause);


// source

declare_primobject_1_slot(source,
			  code
			  );

f2ptr f2source__primobject_type__new_aux(f2ptr cause);


// package

declare_primobject_15_slot(package,
			   pathname,
			   name,
			   package_dependencies_cmutex,
			   package_dependencies,
			   source_dependencies_cmutex,
			   source_dependencies,
			   load_cmutex,
			   load_fiber,
			   object_types_defined_set,
			   loaded_all_dependencies_time,
			   documentation,
			   binary_dependencies_cmutex,
			   binary_dependencies,
			   dynamic_library_dependencies_cmutex,
			   dynamic_library_dependencies);

f2ptr  f2__package__new                    (f2ptr cause, f2ptr pathname, f2ptr name, f2ptr package_dependencies, f2ptr source_dependencies, f2ptr documentation, f2ptr binary_dependencies, f2ptr dynamic_library_dependencies);
f2ptr raw__package__add_to_dependency_graph(f2ptr cause, f2ptr this, f2ptr graph);
f2ptr  f2__package__add_to_dependency_graph(f2ptr cause, f2ptr this, f2ptr graph);
f2ptr raw__package__dependency_graph       (f2ptr cause, f2ptr this);


f2ptr f2package__primobject_type__new_aux(f2ptr cause);


f2ptr f2__current_working_directory(f2ptr cause);

f2ptr     raw__pathname__concat                         (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__pathname__concat                         (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__pathnamelist__concat                     (f2ptr cause, f2ptr this);
boolean_t raw__pathname__is_absolute                    (f2ptr cause, f2ptr this);
f2ptr      f2__pathname__is_absolute                    (f2ptr cause, f2ptr this);
f2ptr     raw__pathname__as__absolute_pathname          (f2ptr cause, f2ptr this);
f2ptr      f2__pathname__as__absolute_pathname          (f2ptr cause, f2ptr this);
f2ptr     raw__pathname__directory_pathname             (f2ptr cause, f2ptr this);
f2ptr      f2__pathname__directory_pathname             (f2ptr cause, f2ptr this);
f2ptr      f2__pathname__scan_for_filenames             (f2ptr cause, f2ptr pathname);
f2ptr      f2__pathname__scan_for_filenames_by_extension(f2ptr cause, f2ptr pathname, f2ptr extension);
f2ptr     raw__pathname__stat                           (f2ptr cause, f2ptr this);
f2ptr      f2__pathname__stat                           (f2ptr cause, f2ptr this);
f2ptr     raw__getenv                                   (f2ptr cause, f2ptr environment_variable);
f2ptr      f2__getenv                                   (f2ptr cause, f2ptr environment_variable);


// **

void f2__package__initialize();

#endif // F2__PACKAGE__H


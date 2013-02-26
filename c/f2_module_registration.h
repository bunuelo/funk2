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

#ifndef F2__MODULE_REGISTRATION__H
#define F2__MODULE_REGISTRATION__H

typedef void (*funk2_module_registration_reinitialize_function_ptr_t)();
typedef void (*funk2_module_registration_defragment_fix_pointers_function_ptr_t)();

typedef struct funk2_module_registration_node_s {
  char*                                                            name;
  char*                                                            description;
  funk2_module_registration_reinitialize_function_ptr_t            reinitialize_function;
  funk2_module_registration_defragment_fix_pointers_function_ptr_t defragment_fix_pointers_function;
  struct funk2_module_registration_node_s*                         next;
} funk2_module_registration_node_t;

void funk2_module_registration_node__init(funk2_module_registration_node_t* this, char* name, char* description,
					  funk2_module_registration_reinitialize_function_ptr_t            reinitialize_function,
					  funk2_module_registration_defragment_fix_pointers_function_ptr_t defragment_fix_pointers_function);
void funk2_module_registration_node__destroy(funk2_module_registration_node_t* this);

typedef struct funk2_module_registration_s {
  funk2_module_registration_node_t* module_list;
  funk2_module_registration_node_t* end_of_module_list;
} funk2_module_registration_t;

void funk2_module_registration__init                    (funk2_module_registration_t* this);
void funk2_module_registration__destroy                 (funk2_module_registration_t* this);
void funk2_module_registration__add_module              (funk2_module_registration_t* this, char* name, char* description,
							 funk2_module_registration_reinitialize_function_ptr_t            reinitialize_function,
							 funk2_module_registration_defragment_fix_pointers_function_ptr_t defragment_fix_pointers_function);
void funk2_module_registration__reinitialize_all_modules(funk2_module_registration_t* this);
void funk2_module_registration__defragment__fix_pointers(funk2_module_registration_t* this);

// **

void f2__module_registration__initialize();
void f2__module_registration__destroy();

#endif // F2__MODULE_REGISTRATION__H


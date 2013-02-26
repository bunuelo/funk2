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

#include "funk2.h"

// funk2_module_registration_node

void funk2_module_registration_node__init(funk2_module_registration_node_t* this, char* name, char* description,
					  funk2_module_registration_reinitialize_function_ptr_t            reinitialize_function,
					  funk2_module_registration_defragment_fix_pointers_function_ptr_t defragment_fix_pointers_function) {
  {
    int name__length = strlen(name);
    this->name = (char*)from_ptr(f2__malloc(name__length + 1));
    memcpy(this->name, name, name__length + 1);
  }
  {
    int description__length = strlen(description);
    this->description = (char*)from_ptr(f2__malloc(description__length + 1));
    memcpy(this->description, description, description__length + 1);
  }
  this->reinitialize_function            = reinitialize_function;
  this->defragment_fix_pointers_function = defragment_fix_pointers_function;
}

void funk2_module_registration_node__destroy(funk2_module_registration_node_t* this) {
  f2__free(to_ptr(this->name));
  f2__free(to_ptr(this->description));
}

void funk2_module_registration_node__reinitialize(funk2_module_registration_node_t* this) {
  (*(this->reinitialize_function))();
}

void funk2_module_registration_node__defragment__fix_pointers(funk2_module_registration_node_t* this) {
  (*(this->defragment_fix_pointers_function))();
}


// funk2_module_registration

void funk2_module_registration__init(funk2_module_registration_t* this) {
  this->module_list        = NULL;
  this->end_of_module_list = NULL;
}

void funk2_module_registration__destroy(funk2_module_registration_t* this) {
  funk2_module_registration_node_t* iter = this->module_list;
  while (iter) {
    funk2_module_registration_node_t* next = iter->next;
    funk2_module_registration_node__destroy(iter);
    f2__free(to_ptr(iter));
    iter = next;
  }
}

void funk2_module_registration__add_module(funk2_module_registration_t* this, char* name, char* description,
					   funk2_module_registration_reinitialize_function_ptr_t            reinitialize_function,
					   funk2_module_registration_defragment_fix_pointers_function_ptr_t defragment_fix_pointers_function) {
  funk2_module_registration_node_t* new_node = (funk2_module_registration_node_t*)from_ptr(f2__malloc(sizeof(funk2_module_registration_node_t)));
  funk2_module_registration_node__init(new_node, name, description, reinitialize_function, defragment_fix_pointers_function);
  new_node->next = NULL;
  if (this->end_of_module_list) {
    this->end_of_module_list->next = new_node;
  } else {
    this->module_list = new_node;
  }
  this->end_of_module_list = new_node;
}

void funk2_module_registration__reinitialize_all_modules(funk2_module_registration_t* this) {
  funk2_module_registration_node_t* iter = this->module_list;
  while (iter) {
    status("reinitializing module [%s] -- '%s'", iter->name, iter->description);
    funk2_module_registration_node__reinitialize(iter);
    status("done reinitializing module [%s]", iter->name);
    iter = iter->next;
  }
}

void funk2_module_registration__defragment__fix_pointers(funk2_module_registration_t* this) {
  funk2_module_registration_node_t* iter = this->module_list;
  while (iter) {
    status("defragmenter fixing pointers in module [%s] -- '%s'", iter->name, iter->description);
    funk2_module_registration_node__defragment__fix_pointers(iter);
    status("done with defragmenter fixing pointers in module [%s]", iter->name);
    iter = iter->next;
  }
}


// **

void f2__module_registration__initialize() {
  funk2_module_registration__init(&(__funk2.module_registration));
}

void f2__module_registration__destroy() {
  funk2_module_registration__destroy(&(__funk2.module_registration));
}



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

void funk2_system_processor__init(funk2_system_processor_t* this) {
  this->processor_count = pthread_num_processors_np();
}

void funk2_system_processor__destroy(funk2_system_processor_t* this) {
}

void funk2_system_processor__print_status(funk2_system_processor_t* this) {
  status("* funk2.system_processor.processor_count = " u64__fstr, this->processor_count);
}

// **

void f2__system_processor__reinitialize_globalvars() {
}

void f2__system_processor__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "system_processor", "", &f2__system_processor__reinitialize_globalvars);
  
  f2__system_processor__reinitialize_globalvars();
  
}


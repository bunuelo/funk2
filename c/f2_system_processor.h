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

#ifndef F2__SYSTEM_PROCESSOR__H
#define F2__SYSTEM_PROCESSOR__H

#include "f2_system_headers.h"

typedef struct funk2_system_processor_s funk2_system_processor_t;
struct funk2_system_processor_s {
  u64            processor_count;
  pthread_spu_t* processor_spu;
};

void funk2_system_processor__init        (funk2_system_processor_t* this);
void funk2_system_processor__destroy     (funk2_system_processor_t* this);
void funk2_system_processor__print_status(funk2_system_processor_t* this) {


// **

void f2__system_processor__reinitialize_globalvars();
void f2__system_processor__initialize();

#endif // F2__SYSTEM_PROCESSOR__H

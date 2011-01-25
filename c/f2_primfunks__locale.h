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

#ifndef F2__PRIMCFUNKS__LOCALE__H
#define F2__PRIMCFUNKS__LOCALE__H

typedef struct funk2_locale_s {
  funk2_processor_mutex_t interface_mutex;
} funk2_locale_t;

void funk2_locale__init(funk2_locale_t* this);
void funk2_locale__destroy(funk2_locale_t* this);

// **

void f2__primfunks__locale__reinitialize_globalvars();
void f2__primfunks__locale__initialize();
void f2__primfunks__locale__destroy();

#endif // F2__PRIMCFUNKS__LOCALE__H

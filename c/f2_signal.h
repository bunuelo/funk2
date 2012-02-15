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

#ifndef F2__SIGNAL__H
#define F2__SIGNAL__H

#include "f2_global.h"

extern boolean_t __received_signal__sigint;

void funk2_receive_signal(int sig);


f2ptr raw__system__received_signal__sigint(f2ptr cause);
f2ptr  f2__system__received_signal__sigint(f2ptr cause);
f2ptr  f2__system__clear_signal__sigint(f2ptr cause);

  // **

void f2__signal__initialize();

#endif // F2__SIGNAL__H


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

boolean_t __received_signal__sigint     = 0;
boolean_t __received_segmentation_fault = 0;

void f2__receive_signal(int sig) {
  switch(sig) {
  case SIGINT:
    printf ("\nsignal note: received ctrl-c\n"); fflush(stdout);
    __received_signal__sigint = 1;
    exit(-1);
    break;
  case SIGSEGV:
    printf ("\nsignal note: received segmentation fault\n"); fflush(stdout);
    __received_segmentation_fault = 1;
    exit(-1);
    break;
  default:
    printf ("\nsignal warning: received unknown signal (%d)\n", sig);
    //signal(sig, SIG_DFL);
    break;
  }
}

void f2__signal__reinitialize_globalvars() {
  //f2ptr cause =
  f2_signal_c__cause__new(initial_cause());
  
}

void f2__signal__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "signal", "", &f2__signal__reinitialize_globalvars);
  
  //f2ptr cause =
  f2_signal_c__cause__new(initial_cause());
  
  f2__signal__reinitialize_globalvars();
  
  signal(SIGINT,  f2__receive_signal);
  signal(SIGSEGV, f2__receive_signal);
}


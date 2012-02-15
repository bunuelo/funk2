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

#include "funk2.h"

boolean_t __received_signal__sigint     = boolean__false;
boolean_t __received_segmentation_fault = boolean__false;

void funk2_receive_signal(int sig) {
  switch(sig) {
  case SIGINT:
    if (! __received_signal__sigint) {
      printf ("\nFunk2 Warning: Received Ctrl-C (SIGINT) from user.  If you press Ctrl-C once more, Funk2 will exit entirely.\n"); fflush(stdout);
    } else {
      printf ("\nFunk2 Fatal: Received more than one Ctrl-C (SIGINT) from user.  Exiting Funk2 immediately.\n"); fflush(stdout);
      exit(-1);
    }
    __received_signal__sigint = boolean__true;
    break;
  case SIGSEGV:
    printf ("\nfunk2 fatal: received segmentation fault (SIGSEGV).  calling exit.\n"); fflush(stdout);
    __received_segmentation_fault = 1;
    exit(-1);
    break;
  default:
    printf ("\nfunk2 signal warning: received unknown signal (%d).  doing nothing.\n", sig);
    //signal(sig, SIG_DFL);
    break;
  }
}


f2ptr f2__system__received_signal__sigint(f2ptr cause) {
  return f2bool__new(__received_signal__sigint);
}
def_pcfunk0(system__received_signal__sigint,
	    "Returns true if the SIGINT signal has been received.",
	    return f2__system__received_signal__sigint(this_cause));


f2ptr f2__system__clear_signal__sigint(f2ptr cause) {
  __received_signal__sigint = boolean__false;
}

def_pcfunk0(system__clear_signal__sigint,
	    "Clears the SIGINT signal.",
	    return f2__system__clear_signal__sigint(this_cause));


void f2__signal__reinitialize_globalvars() {
  //f2ptr cause =
  f2_signal_c__cause__new(initial_cause());
  
}

void f2__signal__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "signal", "", &f2__signal__reinitialize_globalvars);
  
  //f2ptr cause =
  f2_signal_c__cause__new(initial_cause());
  
  f2__signal__reinitialize_globalvars();
  
  signal(SIGINT,  funk2_receive_signal);
  signal(SIGSEGV, funk2_receive_signal);

  f2__primcfunk__init__0(system__received_signal__sigint);
  f2__primcfunk__init__0(system__clear_signal__sigint);

}


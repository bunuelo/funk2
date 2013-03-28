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

// This source file is used to print out a stack-trace when your program
// segfaults. It is relatively reliable and spot-on accurate.
//
// This code is in the public domain. Use it as you see fit, some credit
// would be appreciated, but is not a prerequisite for usage. Feedback
// on it's use would encourage further development and maintenance.
//
// Due to a bug in gcc-4.x.x you currently have to compile as C++ if you want
// demangling to work.
//
// Author: Jaco Kroon <jaco@kroon.co.za>
//
// Copyright (C) 2005 - 2010 Jaco Kroon

#include "funk2.h"

void funk2_signal_segv_handler(int signum, siginfo_t* info, void* ptr) {
  int         i;
  int         f = 0;
  ucontext_t* ucontext = (ucontext_t*)ptr;
  Dl_info     dlinfo;
  void**      bp       = 0;
  void*       ip       = 0;
  
  status("funk2_signal_segv_handler: Segmentation Fault!");
  status("funk2_signal_segv_handler: info.si_signo = %d", signum);
  status("funk2_signal_segv_handler: info.si_errno = %d", info->si_errno);
  status("funk2_signal_segv_handler: info.si_code  = %d", info->si_code);
  status("funk2_signal_segv_handler: info.si_addr  = %p", info->si_addr);
  for(i = 0; i < NGREG; i++) {
    status("funk2_signal_segv_handler: reg[%02d]       = 0x" REGFORMAT, i, ucontext->uc_mcontext.gregs[i]);
  }
  
#ifndef SIGSEGV_NOSTACK
#  if defined(SIGSEGV_STACK_IA64) || defined(SIGSEGV_STACK_X86)
#    if defined(SIGSEGV_STACK_IA64)
  ip = (void*)ucontext->uc_mcontext.gregs[REG_RIP];
  bp = (void**)ucontext->uc_mcontext.gregs[REG_RBP];
#    elif defined(SIGSEGV_STACK_X86)
  ip = (void*)ucontext->uc_mcontext.gregs[REG_EIP];
  bp = (void**)ucontext->uc_mcontext.gregs[REG_EBP];
#    endif
  
  status("funk2_signal_segv_handler: Stack trace: bp=%p, ip=%p", bp, ip);
  while(bp) {
    const char*   symname   = "unknown_symbol";
    const char*   filename  = "unknown_filename";
    unsigned long dli_saddr = 0;
    if(dladdr(ip, &dlinfo)) {
      symname   = dlinfo.dli_sname;
      filename  = dlinfo.dli_fname;
      dli_saddr = (unsigned long)dlinfo.dli_saddr;
    }
    
#    ifndef NO_CPP_DEMANGLE
    int   status_value;
    char* tmp = __cxa_demangle(symname, NULL, 0, &status_value);
    
    if (status_value == 0 && tmp) {
      symname = tmp;
    }
#    endif
    
    status("funk2_signal_segv_handler: % 2d: %p <%s+%lu> (%s)",
	   ++f,
	   ip,
	   symname,
	   (unsigned long)ip - (unsigned long)dli_saddr,
	   filename);
    
#    ifndef NO_CPP_DEMANGLE
    if (tmp) {
      free(tmp);
    }
#    endif
    
    if(symname && !strcmp(symname, "main")) {
      break;
    }
    
    ip = bp[1];
    bp = (void**)bp[0];
  }
#  else
  status("funk2_signal_segv_handler: Stack trace (non-dedicated):");
  sz = backtrace(bt, 20);
  strings = backtrace_symbols(bt, sz);
  for(i = 0; i < sz; ++i)
    status("funk2_signal_segv_handler: %s", strings[i]);
#  endif
  status("funk2_signal_segv_handler: End of stack trace.");
#else
  status("funk2_signal_segv_handler: Not printing stack strace.");
#endif
}

int __received_signal__sigint     = 0;
int __received_segmentation_fault = 0;

void funk2_receive_signal(int sig, siginfo_t *info, void *arg) {
  switch(sig) {
  case SIGINT:
    if (__received_signal__sigint == 0) {
      printf ("\nFunk2 Warning: Received Ctrl-C (SIGINT) from user.\n"); fflush(stdout);
    } else if (__received_signal__sigint == 1) {
      printf ("\nFunk2 Second Warning: Received another Ctrl-C (SIGINT) from user.  The first Ctrl-C from user has not been processed.  PRESSING CTRL-C AGAIN WILL EXIT FUNK2 ENTIRELY. \n"); fflush(stdout);
    } else {
      printf ("\nFunk2 Fatal: Received yet another Ctrl-C (SIGINT) from user.  Exiting Funk2 immediately.\n"); fflush(stdout);
      exit(-1);
    }
    __received_signal__sigint ++;
    break;
  case SIGSEGV:
    status("funk2 warning: thread received segmentation fault (SIGSEGV) at address %p.", info->si_addr);
    __received_segmentation_fault = 1;
    status_backtrace();
    funk2_signal_segv_handler(sig, info, arg);
    status("funk2 warning: thread received segmentation fault (SIGSEGV) at address %p.  calling f2__this__fiber__exit.", info->si_addr);
    f2ptr cause = nil;
    f2ptr sigsegv_larva = new__error(f2list2__new(cause,
						  new__symbol(cause, "bug_name"), new__symbol(cause, "SIGSEGV")));
    f2__this__fiber__exit(nil, sigsegv_larva);
    status("funk2 warning: thread received segmentation fault (SIGSEGV) at address %p.  should not get here.  calling exit", info->si_addr);
    //pthread_exit(NULL);
    exit(-1);
    break;
  default:
    printf ("\nfunk2 signal warning: received unknown signal (%d).  doing nothing.\n", sig);
    //signal(sig, SIG_DFL);
    break;
  }
}


boolean_t raw__system__received_signal__sigint(f2ptr cause) {
  return (__received_signal__sigint != 0);
}

f2ptr f2__system__received_signal__sigint(f2ptr cause) {
  return f2bool__new(raw__system__received_signal__sigint(cause));
}
def_pcfunk0(system__received_signal__sigint,
	    "Returns true if the SIGINT signal has been received.",
	    return f2__system__received_signal__sigint(this_cause));


f2ptr f2__system__clear_signal__sigint(f2ptr cause) {
  __received_signal__sigint = 0;
  return nil;
}

def_pcfunk0(system__clear_signal__sigint,
	    "Clears the SIGINT signal.",
	    return f2__system__clear_signal__sigint(this_cause));


// **

void f2__signal__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(system__received_signal__sigint);
  f2__primcfunk__init__defragment__fix_pointers(system__clear_signal__sigint);
}

void f2__signal__reinitialize_globalvars() {
  f2__primcfunk__init__0(system__received_signal__sigint);
  f2__primcfunk__init__0(system__clear_signal__sigint);
}

void f2__signal__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "signal", "", &f2__signal__reinitialize_globalvars, &f2__signal__defragment__fix_pointers);
  
  f2__signal__reinitialize_globalvars();
  
  {
    struct sigaction sa;
    
    memset(&sa, 0, sizeof(sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = funk2_receive_signal;
    sa.sa_flags     = SA_SIGINFO | SA_RESTART;
    
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGSEGV, &sa, NULL);
  }
}


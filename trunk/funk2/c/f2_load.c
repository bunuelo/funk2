// 
// Copyright (c) 2007-2009 Bo Morgan.
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

FILE* f2__fopen_for_read(f2ptr cause, f2ptr filename) {
  int length = f2string__length(filename, cause);
  char* str = (char*)from_ptr(f2__malloc(length + 1));
  f2string__str_copy(filename, cause, (u8*)str);
  str[length] = 0;
  FILE* retval = fopen(str, "r");
  f2__free(to_ptr(str));
  return retval;
}

f2ptr raw__load(f2ptr cause, f2ptr thread, f2ptr filename) {
  if (!raw__string__is_type(cause, filename)) {printf("\nload error: filename must be a string."); return nil;}
  f2ptr stream = f2__stream__new_open_file__rdonly(cause, filename);
  if (! stream) {f2__print(cause, filename); printf("\nload error: couldn't open file for reading."); return nil;}
#ifdef DEBUG_LOAD
  f2__print(cause, filename); printf("\nload note: opening file for reading.");
#endif // DEBUG_LOAD
  
  try_gc();
  
  f2ptr load_funk     = f2funk__new(cause, nil, nil, nil, f2cons__new(cause, nil, nil), nil, global_environment(), nil, nil, nil);
  f2ptr load_funk_bcs = f2__compile__funk(cause, thread, load_funk);
  f2ptr load_thread   = f2__thread_serial(cause, cause, thread, f2thread__env(thread, cause), load_funk, nil);
  f2ptr read_exp      = nil;
  
  while (read_exp != __end_of_file_exception) {
    
    read_exp = raw__read(cause, stream);
    if (read_exp != __end_of_file_exception) {
#ifdef DEBUG_LOAD
      f2__print_prompt(cause, "Load-F-In-> ", read_exp); fflush(stdout);
#endif
      if (raw__exception__is_type(cause, read_exp)) {
	printf("\nload exception: "); f2__write(thread, read_exp); fflush(stdout);
      } else {
	pause_gc();
	
	load_funk     = f2funk__new(cause, nil, nil, nil, f2cons__new(cause, read_exp, nil), read_exp, global_environment(), nil, nil, nil);
	load_funk_bcs = f2__compile__funk(cause,
					  thread, load_funk);
	if(raw__exception__is_type(cause, load_funk_bcs)) {
	  f2thread__value__set(thread, cause, load_funk_bcs);
	  resume_gc();
	} else {
	  f2thread__program_counter__set(load_thread, cause, nil);
	  resume_gc();
	  f2thread__force_funk(load_thread, cause, cause, load_funk, nil);
	}
	
	
	f2__scheduler__complete_thread(cause, load_thread);
	
	pause_gc();
	//printf("\nload_thread stack size = %d", raw__length(f2thread__stack(load_thread))); fflush(stdout);
	f2ptr eval_exp = f2thread__value(load_thread, cause);
	if (raw__exception__is_type(cause, eval_exp)) {
	  printf("\nload eval exception: "); f2__write(cause, eval_exp); fflush(stdout);
	  f2__stream__close(cause, stream);
	  resume_gc();
	  return f2integer__new(f2thread__cause_reg(load_thread, cause), 1);
	} else {
	  resume_gc();
	}
#ifdef DEBUG_LOAD
	printf ("\nLoad-F-Out> "); f2__write(cause, eval_exp); fflush(stdout);
#endif
      }
    }
  }  
#ifdef DEBUG_LOAD
  printf("\nload done."); fflush(stdout);
#endif // DEBUG_LOAD
  f2__stream__close(cause, stream);
  return nil;
}
def_pcfunk1(load, filename, return raw__load(this_cause, simple_thread, filename));

void f2__load__reinitialize_globalvars() {
}

void f2__load__initialize() {
  f2__load__reinitialize_globalvars();
  
  f2__primcfunk__init(load, "");
}


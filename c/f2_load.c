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

FILE* f2__fopen_for_read(f2ptr cause, f2ptr filename) {
  int length = f2string__length(filename, cause);
  char* str = (char*)from_ptr(f2__malloc(length + 1));
  f2string__str_copy(filename, cause, (u8*)str);
  str[length] = 0;
  FILE* retval = fopen(str, "r");
  f2__free(to_ptr(str));
  return retval;
}

f2ptr raw__load__original(f2ptr cause, f2ptr fiber, f2ptr filename) {
  if (!raw__string__is_type(cause, filename)) {
    status("load error: filename must be a string.");
    return nil;
  }
  f2ptr stream = f2__stream__new_open_file__rdonly(cause, filename);
  if (! stream) {
    {
      u64 filename__length = raw__string__length(cause, filename);
      u8* filename__str    = (u8*)from_ptr(f2__malloc(filename__length + 1));
      raw__string__str_copy(cause, filename, filename__str);
      filename__str[filename__length] = 0;
      status("load error: couldn't open file for reading \'%s\'.", (char*)filename__str);
      f2__free(to_ptr(filename__str));
    }
    return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list6__new(cause,
														     new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file_for_reading"),
														     new__symbol(cause, "funkname"), new__symbol(cause, "primfunk:load"),
														     new__symbol(cause, "filename"), filename))));
  }
#ifdef DEBUG_LOAD
  f2__fiber__print(cause, fiber, filename); status("load note: opening file for reading.");
#endif // DEBUG_LOAD
  
  f2ptr load_funk     = f2funk__new(cause, nil, nil, nil, f2cons__new(cause, nil, nil), nil, global_environment(), nil, nil, nil);
  f2ptr load_funk_bcs = f2__compile__funk(cause, fiber, load_funk);
  f2ptr load_fiber    = f2__fiber_serial(cause, cause, fiber, f2fiber__env(fiber, cause), load_funk, nil);
  f2ptr read_exp      = nil;
  
  while (read_exp != __funk2.reader.end_of_file_exception) {
    
    read_exp = f2__stream__try_read(cause, stream);
    if (read_exp != __funk2.reader.end_of_file_exception) {
#ifdef DEBUG_LOAD
      f2__print_prompt(cause, fiber, "Load-F-In-> ", read_exp); fflush(stdout);
#endif
      if (raw__exception__is_type(cause, read_exp)) {
	printf("\nload exception..: "); f2__write(cause, fiber, read_exp); fflush(stdout);
	printf("\ncurrent filename: "); f2__write(cause, fiber, filename); fflush(stdout);
      } else {
	load_funk     = f2funk__new(cause, nil, nil, nil, f2cons__new(cause, read_exp, nil), read_exp, global_environment(), nil, nil, nil);
	load_funk_bcs = f2__compile__funk(cause, fiber, load_funk);
	if (raw__larva__is_type(cause, load_funk_bcs)) {
	  f2__stream__close(cause, stream);
	  return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),  new__symbol(cause, "found_bug_while_compiling_load_expression"),
															   new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
															   new__symbol(cause, "filename"),  filename,
															   new__symbol(cause, "bug"),       load_funk_bcs))));
	}
	if(raw__exception__is_type(cause, load_funk_bcs)) {
	  f2fiber__value__set(fiber, cause, load_funk_bcs);
	} else {
	  f2fiber__program_counter__set(load_fiber, cause, nil);
	  f2fiber__force_funk(load_fiber, cause, load_funk, nil);
	}
	
	
	f2__global_scheduler__complete_fiber(cause, load_fiber);
	
	//printf("\nload_fiber stack size = %d", raw__simple_length(f2fiber__stack(load_fiber))); fflush(stdout);
	f2ptr eval_exp = f2fiber__value(load_fiber, cause);
	if (raw__larva__is_type(cause, eval_exp)) {
	  f2__stream__close(cause, stream);
	  return eval_exp;
	}
	if ((f2__fiber__paused(cause, load_fiber) != nil) &&
	    raw__bug__is_type(cause, eval_exp)) {
	  f2__stream__close(cause, stream);
	  return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),  new__symbol(cause, "found_bug_while_loading"),
															   new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
															   new__symbol(cause, "filename"),  filename,
															   new__symbol(cause, "bug"),       eval_exp))));
	}
	if (raw__exception__is_type(cause, eval_exp)) {
	  printf("\nload eval exception: "); f2__write(cause, fiber, eval_exp); fflush(stdout);
	  f2__stream__close(cause, stream);
	  return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),  new__symbol(cause, "found_exception_while_loading"),
															   new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
															   new__symbol(cause, "filename"),  filename,
															   new__symbol(cause, "exception"), eval_exp))));
	}
#ifdef DEBUG_LOAD
	printf ("\nLoad-F-Out> "); f2__write(cause, fiber, eval_exp); fflush(stdout);
#endif
      }
    }
  }  
  
  f2fiber__keep_undead__set(load_fiber, cause, nil);
  
#ifdef DEBUG_LOAD
  printf("\nload done."); fflush(stdout);
#endif // DEBUG_LOAD
  f2__stream__close(cause, stream);
  return nil;
}


f2ptr raw__load(f2ptr cause, f2ptr filename) {
  f2ptr stream = f2__stream__new_open_file__rdonly(cause, filename);
  if (stream == nil) {
    {
      u64 filename__length = raw__string__length(cause, filename);
      u8* filename__str    = (u8*)from_ptr(f2__malloc(filename__length + 1));
      raw__string__str_copy(cause, filename, filename__str);
      filename__str[filename__length] = 0;
      status("load error: couldn't open file for reading \'%s\'.", (char*)filename__str);
      f2__free(to_ptr(filename__str));
    }
    return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list6__new(cause,
														     new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file_for_reading"),
														     new__symbol(cause, "funkname"), new__symbol(cause, "primfunk:load"),
														     new__symbol(cause, "filename"), filename))));
  }
  
  f2ptr read_exp = nil;
  while (! raw__eq(cause, read_exp, __funk2.reader.end_of_file_exception)) {
    
    read_exp = f2__stream__try_read(cause, stream);
    if (! raw__eq(cause, read_exp, __funk2.reader.end_of_file_exception)) {
      if (raw__exception__is_type(cause, read_exp)) {
	printf("\nload exception..: "); f2__terminal_print(cause, read_exp); fflush(stdout);
	printf("\ncurrent filename: "); f2__terminal_print(cause, filename); fflush(stdout);
      } else {
	f2ptr load_funk     = f2funk__new(cause, nil, nil, nil, f2cons__new(cause, read_exp, nil), read_exp, global_environment(), nil, nil, nil);
	f2ptr load_funk_bcs = f2__compile__funk(cause, fiber, load_funk);
	if (raw__larva__is_type(cause, load_funk_bcs)) {
	  f2__stream__close(cause, stream);
	  return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),  new__symbol(cause, "found_bug_while_compiling_load_expression"),
															   new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
															   new__symbol(cause, "filename"),  filename,
															   new__symbol(cause, "bug"),       load_funk_bcs))));
	}
	if(raw__exception__is_type(cause, load_funk_bcs)) {
	  return f2larva__new(cause, 13514, nil);
	  //f2fiber__value__set(fiber, cause, load_funk_bcs);
	}
	//f2fiber__program_counter__set(load_fiber, cause, nil);
	f2__force_funk_apply(load_fiber, cause, load_funk, nil);
	f2ptr eval_exp = f2__force_funk_apply(cause, f2__this__fiber(cause), load_funk, nil);
	if (raw__larva__is_type(cause, eval_exp)) {
	  f2__stream__close(cause, stream);
	  return eval_exp;
	}
	if (raw__exception__is_type(cause, eval_exp)) {
	  printf("\nload eval exception: "); f2__terminal_print(cause, eval_exp); fflush(stdout);
	  f2__stream__close(cause, stream);
	  return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),  new__symbol(cause, "found_exception_while_loading"),
															   new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
															   new__symbol(cause, "filename"),  filename,
															   new__symbol(cause, "exception"), eval_exp))));
	}
      }
    }
  }  
  
  f2__stream__close(cause, stream);
  return nil;
}

f2ptr f2__load(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  return raw__load(cause, filename);
}
def_pcfunk1(load, filename, return f2__load(this_cause, simple_fiber, filename));

void f2__load__reinitialize_globalvars() {
}

void f2__load__initialize() {
  f2__load__reinitialize_globalvars();
  
  f2__primcfunk__init(load, "");
}


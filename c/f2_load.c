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

FILE* f2__fopen_for_read(f2ptr cause, f2ptr filename) {
  u64 utf8_length = raw__string__utf8_length(cause, filename);
  u8* utf8_str    = (u8*)from_ptr(f2__malloc(utf8_length + 1));
  raw__string__utf8_str_copy(cause, filename, utf8_str);
  utf8_str[utf8_length] = 0;
  FILE* retval = fopen((char*)utf8_str, "r");
  f2__free(to_ptr(utf8_str));
  return retval;
}

f2ptr raw__load(f2ptr cause, f2ptr filename) {
  if (!raw__string__is_type(cause, filename)) {
    error(nil, "load error: filename must be a string.");
  }
  f2ptr fiber  = f2__this__fiber(cause);
  f2ptr stream = f2__stream__new_open_file__rdonly(cause, filename);
  if (! stream) {
    {
      u64 filename__utf8_length = raw__string__utf8_length(cause, filename);
      u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
      raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
      filename__utf8_str[filename__utf8_length] = 0;
      status("load error: couldn't open file for reading \'%s\'.", (char*)filename__utf8_str);
      f2__free(to_ptr(filename__utf8_str));
    }
    return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list6__new(cause,
														     new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file_for_reading"),
														     new__symbol(cause, "funkname"), new__symbol(cause, "primfunk:load"),
														     new__symbol(cause, "filename"), filename))));
  }
#ifdef DEBUG_LOAD
  f2__fiber__print(cause, fiber, filename); status("load note: opening file for reading.");
#endif // DEBUG_LOAD
  
  f2ptr load_funk     = f2funk__new(cause, nil, nil, nil, raw__cons__new(cause, nil, nil), nil, global_environment(), nil, nil, nil, nil);
  f2ptr load_funk_bcs = f2__compile__funk(cause, fiber, load_funk);
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
	load_funk     = f2funk__new(cause, nil, nil, nil, raw__cons__new(cause, read_exp, nil), read_exp, global_environment(), nil, nil, nil, nil);
	load_funk_bcs = f2__compile__funk(cause, fiber, load_funk);
	if (raw__larva__is_type(cause, load_funk_bcs)) {
	  f2__stream__close(cause, stream);
	  return f2larva__new(cause, 49, f2__bug__new(cause, f2integer__new(cause, 49), f2__frame__new(cause, f2list8__new(cause,
															   new__symbol(cause, "bug_type"),  new__symbol(cause, "found_bug_while_compiling_load_expression"),
															   new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
															   new__symbol(cause, "filename"),  filename,
															   new__symbol(cause, "bug"),       load_funk_bcs))));
      	}
	f2ptr eval_exp = f2__force_funk_apply(cause, f2__this__fiber(cause), load_funk, nil);
	if (raw__larva__is_type(cause, eval_exp)) {
	  f2__stream__close(cause, stream);
	  return new__error(f2list8__new(cause,
					 new__symbol(cause, "bug_type"),  new__symbol(cause, "found_bug_while_loading"),
					 new__symbol(cause, "funkname"),  new__symbol(cause, "primfunk:load"),
					 new__symbol(cause, "filename"),  filename,
					 new__symbol(cause, "bug"),       eval_exp));
	}
#ifdef DEBUG_LOAD
	printf ("\nLoad-F-Out> "); f2__write(cause, fiber, eval_exp); fflush(stdout);
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


f2ptr f2__load(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  return raw__load(cause, filename);
}
def_pcfunk1(load, filename,
	    "",
	    return f2__load(this_cause, filename));

void f2__load__reinitialize_globalvars() {
}

void f2__load__initialize() {
  f2__load__reinitialize_globalvars();
  
  f2__primcfunk__init(load);
}


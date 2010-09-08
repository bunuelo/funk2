

// 
// Copyright (c) 2007-2010 Bo Morgan.
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


// terminal_print_frame

def_frame_object__global__19_slot(terminal_print_frame,
				  test_constraints,
				  stream,
				  min_x,
				  min_y,
				  max_x,
				  max_y,
				  max_size,
				  use_ansi_codes,
				  use_html_codes,
				  x,
				  y,
				  size,
				  subexp_width,
				  subexp_height,
				  subexp_size,
				  already_printed_hash,
				  use_one_line,
				  failed_max_x_constraint,
				  failed_max_y_constraint);

f2ptr f2__terminal_print_frame__new(f2ptr cause, f2ptr stream, f2ptr min_x, f2ptr min_y, f2ptr max_x, f2ptr max_y, f2ptr max_size, f2ptr use_ansi_codes, f2ptr use_html_codes, f2ptr x, f2ptr y) {
  if (((stream != nil) && (! raw__stream__is_type(cause, stream))) ||
      (! raw__integer__is_type(cause, min_x)) ||
      (! raw__integer__is_type(cause, min_y)) ||
      (! raw__integer__is_type(cause, max_x)) ||
      (! raw__integer__is_type(cause, max_y)) ||
      (! raw__integer__is_type(cause, max_size)) ||
      (! raw__integer__is_type(cause, x)) ||
      (! raw__integer__is_type(cause, y))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr test_constraints        = nil;
  f2ptr size                    = f2integer__new(cause, 0);
  f2ptr subexp_width            = nil;
  f2ptr subexp_height           = nil;
  f2ptr subexp_size             = nil;
  f2ptr already_printed_hash    = f2__ptypehash__new(cause);
  f2ptr use_one_line            = f2bool__new(boolean__true);
  f2ptr failed_max_x_constraint = f2bool__new(boolean__false);
  f2ptr failed_max_y_constraint = f2bool__new(boolean__false);
  return f2terminal_frame__new(cause,
			       test_constraints,
			       stream,
			       min_x,
			       min_y,
			       max_x,
			       max_y,
			       max_size,
			       use_ansi_codes,
			       use_html_codes,
			       x,
			       y,
			       size,
			       subexp_width,
			       subexp_height,
			       subexp_size,
			       already_printed_hash,
			       use_one_line,
			       failed_max_x_constraint,
			       failed_max_y_constraint);
}

f2ptr f2__object__eq(f2ptr cause, f2ptr this, f2ptr that) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.get__symbol, __funk2.globalenv.eq__symbol);
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(this == that);
  }
  return f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, that, nil)));
}
def_pcfunk2(object__eq, this, that, return f2__object__eq(this_cause, this, that));


f2ptr raw__exp__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"));
  if (raw__funkable__is_type(cause, funk)) {
    // try to print on one line.
    {
      f2__terminal_print_frame__use_one_line__set(           cause, terminal_print_frame, f2bool__new(boolean__true));
      f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
      f2__terminal_print_frame__failed_max_y_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
      f2__terminal_print_frame__test_constraints__set(       cause, terminal_print_frame, f2bool__new(boolean__true));
      f2__terminal_print_frame__subexp_width__set(           cause, terminal_print_frame, f2integer__new(cause, 0));
      f2__terminal_print_frame__subexp_height__set(          cause, terminal_print_frame, f2integer__new(cause, 0));
      f2__terminal_print_frame__subexp_size__set(            cause, terminal_print_frame, f2integer__new(cause, 0));
      f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    }
    if (f2__terminal_print_frame__failed_max_x_constraint(cause, terminal_print_frame) != nil) {
      // failed x constraint, so forget trying to print on one line.
      {
	f2__terminal_print_frame__use_one_line__set(           cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_y_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__test_constraints__set(       cause, terminal_print_frame, f2bool__new(boolean__true));
	f2__terminal_print_frame__subexp_width__set(           cause, terminal_print_frame, f2integer__new(cause, 0));
	f2__terminal_print_frame__subexp_height__set(          cause, terminal_print_frame, f2integer__new(cause, 0));
	f2__terminal_print_frame__subexp_size__set(            cause, terminal_print_frame, f2integer__new(cause, 0));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	if (raw__larva__is_type(cause, result)) {
	  return result;
	}
      }
      // iteratively reduce max size if we fail to satisfy y constraint.
      while (f2__terminal_print_frame__failed_y_constraint(cause, terminal_print_frame) != nil) {
	{
	  f2ptr max_size    = f2__terminal_print_frame__max_size(cause, terminal_print_frame);
	  s64   max_size__i = f2integer__i(max_size, cause);
	  max_size__i >>= 1;
	  max_size = f2integer__new(cause, max_size__i);
	  f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
	  if (max_size__i == 0) {
	    return f2larva__new(cause, 3342, nil);
	  }
	}
	{
	  f2__terminal_print_frame__use_one_line__set(           cause, terminal_print_frame, f2bool__new(boolean__false));
	  f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	  f2__terminal_print_frame__failed_max_y_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	  f2__terminal_print_frame__test_constraints__set(       cause, terminal_print_frame, f2bool__new(boolean__true));
	  f2__terminal_print_frame__subexp_width__set(           cause, terminal_print_frame, f2integer__new(cause, 0));
	  f2__terminal_print_frame__subexp_height__set(          cause, terminal_print_frame, f2integer__new(cause, 0));
	  f2__terminal_print_frame__subexp_size__set(            cause, terminal_print_frame, f2integer__new(cause, 0));
	  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	  if (raw__larva__is_type(cause, result)) {
	    return result;
	  }
	}
      }
      // failed x constraint and y constraint so reduced max_size, now ready to print.
      {
	f2__terminal_print_frame__use_one_line__set(           cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_y_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__test_constraints__set(       cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__subexp_width__set(           cause, terminal_print_frame, f2integer__new(cause, 0));
	f2__terminal_print_frame__subexp_height__set(          cause, terminal_print_frame, f2integer__new(cause, 0));
	f2__terminal_print_frame__subexp_size__set(            cause, terminal_print_frame, f2integer__new(cause, 0));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	if (raw__larva__is_type(cause, result)) {
	  return result;
	}
      }
    } else {
      // we successfully satisfied all constraints by printing on one line, so go for it.
      {
	f2__terminal_print_frame__use_one_line__set(           cause, terminal_print_frame, f2bool__new(boolean__true));
	f2__terminal_print_frame__failed_max_x_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_y_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__test_constraints__set(       cause, terminal_print_frame, f2bool__new(boolean__false));
	f2__terminal_print_frame__subexp_width__set(           cause, terminal_print_frame, f2integer__new(cause, 0));
	f2__terminal_print_frame__subexp_height__set(          cause, terminal_print_frame, f2integer__new(cause, 0));
	f2__terminal_print_frame__subexp_size__set(            cause, terminal_print_frame, f2integer__new(cause, 0));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	if (raw__larva__is_type(cause, result)) {
	  return result;
	}
      }
    }
  } else {
    // this object type doesn't have a terminal_print_with_frame funktion.
    //  ... we should print object type here and some short opaque, non-recursive description with size one.
  }
  return nil;
}

f2ptr f2__exp__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__terminal_print_frame__is_type(cause, terminal_print_frame)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__exp__terminal_print(cause, this, terminal_print_frame);
}
def_pcfunk2(exp__terminal_print, this, terminal_print_frame, return f2__exp__terminal_print(this_cause, this, terminal_print_frame));


f2ptr f2__exp__terminal_stream_print(f2ptr cause, f2ptr this, f2ptr stream) {
  f2ptr stream               = stream;
  f2ptr min_x                = f2integer__new(cause, 0);
  f2ptr min_y                = f2integer__new(cause, 0);
  f2ptr max_x                = f2integer__new(cause, raw__termios__width());
  f2ptr max_y                = f2integer__new(cause, raw__termios__height());
  f2ptr max_size             = f2integer__new(cause, 1024);
  f2ptr use_ansi_codes       = f2bool__new(boolean__true);
  f2ptr use_html_codes       = f2bool__new(boolean__false);
  f2ptr x                    = f2integer__new(cause, 0);
  f2ptr y                    = f2integer__new(cause, 0);
  f2ptr terminal_print_frame = f2__terminal_print_frame__new_default(cause, stream, min_x, min_y, max_x, max_y, max_size, use_ansi_codes, use_html_codes, x, y);
  if (raw__larva__is_type(cause, terminal_print_frame)) {
    return terminal_print_frame;
  }
  return f2__exp__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(exp__terminal_stream_print, this, stream, return f2__exp__terminal_stream_print(this_cause, this, stream));


// **

void f2__terminal_print__reinitialize_globalvars() {
}

void f2__terminal_print__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "terminal_print", "", &f2__terminal_print__reinitialize_globalvars);
  
  f2__terminal_print__reinitialize_globalvars();
  
  
  // terminal_print_frame
  
  init_frame_object__19_slot(terminal_print_frame,
			     test_constraints,
			     stream,
			     min_x,
			     min_y,
			     max_x,
			     max_y,
			     max_size,
			     use_ansi_codes,
			     use_html_codes,
			     x,
			     y,
			     size,
			     subexp_width,
			     subexp_height,
			     subexp_size,
			     already_printed_hash,
			     use_one_line,
			     failed_max_x_constraint,
			     failed_max_y_constraint);
  
  
  f2__primcfunk__init__2(exp__terminal_print,        this, terminal_print_frame, "Prints a value given a terminal_print_frame.");
  f2__primcfunk__init__2(exp__terminal_stream_print, this, stream,               "Prints a value to the given terminal stream, using a new default terminal_print_frame.");
}


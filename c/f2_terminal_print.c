

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

def_frame_object__global__20_slot(terminal_print_frame,
				  testing,
				  testing_max_x_constraint,
				  testing_max_height_constraint,
				  testing_x_offset,
				  stream,
				  indent_distance,
				  max_x,
				  max_height,
				  max_size,
				  use_ansi_codes,
				  use_html_codes,
				  x,
				  height,
				  size,
				  left_extent,
				  right_extent,
				  already_printed_hash,
				  use_one_line,
				  failed_max_x_constraint,
				  failed_max_height_constraint);

f2ptr f2__terminal_print_frame__new(f2ptr cause, f2ptr stream, f2ptr indent_distance, f2ptr max_x, f2ptr max_height, f2ptr max_size, f2ptr use_ansi_codes, f2ptr use_html_codes) {
  if ((! raw__stream__is_type(cause, stream)) ||
      (! raw__integer__is_type(cause, indent_distance)) ||
      (! raw__integer__is_type(cause, max_x)) ||
      (! raw__integer__is_type(cause, max_height)) ||
      (! raw__integer__is_type(cause, max_size))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr testing                       = nil;
  f2ptr testing_max_x_constraint      = nil;
  f2ptr testing_max_height_constraint = nil;
  f2ptr testing_x_offset              = nil;
  f2ptr x                             = f2integer__new(cause, 0);
  f2ptr height                        = f2integer__new(cause, 0);
  f2ptr size                          = f2integer__new(cause, 0);
  f2ptr left_extent                   = nil;
  f2ptr right_extent                  = nil;
  f2ptr already_printed_hash          = f2__ptypehash__new(cause);
  f2ptr use_one_line                  = f2bool__new(boolean__true);
  f2ptr failed_max_x_constraint       = f2bool__new(boolean__false);
  f2ptr failed_max_height_constraint  = f2bool__new(boolean__false);
  return f2terminal_print_frame__new(cause,
				     testing,
				     testing_max_x_constraint,
				     testing_max_height_constraint,
				     testing_x_offset,
				     stream,
				     indent_distance,
				     max_x,
				     max_height,
				     max_size,
				     use_ansi_codes,
				     use_html_codes,
				     x,
				     height,
				     size,
				     left_extent,
				     right_extent,
				     already_printed_hash,
				     use_one_line,
				     failed_max_x_constraint,
				     failed_max_height_constraint);
}
def_pcfunk7(terminal_print_frame__new, stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes, return f2__terminal_print_frame__new(this_cause, stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes));


boolean_t raw__terminal_print_frame__failed_test_constraint_and_should_return(f2ptr cause, f2ptr this) {
  boolean_t testing = (f2__terminal_print_frame__testing(cause, this) != nil);
  if (! testing) {
    return boolean__false;
  }
  boolean_t testing_x_offset = (f2__terminal_print_frame__testing_x_offset(cause, this) != nil);
  if (testing_x_offset) {
    return boolean__false;
  }
  boolean_t testing_max_x_constraint      = (f2__terminal_print_frame__testing_max_x_constraint(     cause, this) != nil);
  boolean_t testing_max_height_constraint = (f2__terminal_print_frame__testing_max_height_constraint(cause, this) != nil);
  if (testing_max_x_constraint &&
      (! testing_max_height_constraint)) {
    boolean_t failed_max_x_constraint = (f2__terminal_print_frame__failed_max_x_constraint(cause, this) != nil);
    if (failed_max_x_constraint) {
      return boolean__true;
    }
  } else if ((! testing_max_x_constraint) &&
	     testing_max_height_constraint) {
    boolean_t failed_max_height_constraint = (f2__terminal_print_frame__failed_max_height_constraint(cause, this) != nil);
    if (failed_max_height_constraint) {
      return boolean__true;
    }
  } else if (testing_max_x_constraint &&
	     testing_max_height_constraint) {
    boolean_t failed_max_x_constraint      = (f2__terminal_print_frame__failed_max_x_constraint(     cause, this) != nil);
    boolean_t failed_max_height_constraint = (f2__terminal_print_frame__failed_max_height_constraint(cause, this) != nil);
    if (failed_max_height_constraint &&
	failed_max_x_constraint) {
      return boolean__true;
    }
  }
  return boolean__false;
}


void raw__terminal_print_frame__write_color(f2ptr cause, f2ptr this, ansi_color_t color) {
  f2ptr testing        = f2__terminal_print_frame__testing(cause, this);
  f2ptr stream         = f2__terminal_print_frame__stream(cause, this);
  f2ptr use_ansi_codes = f2__terminal_print_frame__use_ansi_codes(cause, this);
  f2ptr use_html_codes = f2__terminal_print_frame__use_html_codes(cause, this);
  if ((testing == nil) && (use_ansi_codes != nil)) {f2__ansi__stream__reset(cause, stream); raw__ansi__stream__foreground(cause, stream, color);}
  if ((testing == nil) && (use_html_codes != nil)) {html__stream__ansi_foreground(cause, stream, color);}
}


void raw__terminal_print_frame__write_string(f2ptr cause, f2ptr this, u64 length, u8* string) {
  f2ptr testing            = f2__terminal_print_frame__testing(cause, this);
  f2ptr stream             = f2__terminal_print_frame__stream(cause, this);
  f2ptr indent_distance    = f2__terminal_print_frame__indent_distance(cause, this);
  s64   indent_distance__i = f2integer__i(indent_distance, cause);
  f2ptr x                  = f2__terminal_print_frame__x(cause, this);
  s64   x__i               = f2integer__i(x, cause);
  f2ptr height             = f2__terminal_print_frame__height(cause, this);
  s64   height__i          = f2integer__i(height, cause);
  f2ptr max_x              = f2__terminal_print_frame__max_x(cause, this);
  s64   max_x__i           = f2integer__i(max_x, cause);
  f2ptr max_height         = f2__terminal_print_frame__max_height(cause, this);
  s64   max_height__i      = f2integer__i(max_height, cause);
  f2ptr left_extent        = f2__terminal_print_frame__left_extent(cause, this);
  s64   left_extent__i     = left_extent ? f2integer__i(left_extent, cause) : 0;
  f2ptr right_extent       = f2__terminal_print_frame__right_extent(cause, this);
  s64   right_extent__i    = right_extent ? f2integer__i(right_extent, cause) : 0;
  f2ptr use_html_codes     = f2__terminal_print_frame__use_html_codes(cause, this);
  {
    u64 index;
    for (index = 0; index < length; index ++) {
      u8 ch = string[index];
      switch(ch) {
      case '\r':
	break;
      case '\n':
	if ((testing == nil) && (height__i < max_height__i)) {
	  if (use_html_codes) {
	    raw__stream__writef(cause, stream, "<br>");
	  }
	  
	  raw__stream__writef(cause, stream, "\n");
	  {
	    u64 index;
	    for (index = 0; index < indent_distance__i; index ++) {
	      if (use_html_codes) {
		raw__stream__writef(cause, stream, "&nbsp;");
	      } else {
		raw__stream__writef(cause, stream, " ");
	      }
	    }
	  }
	}
	if ((testing != nil) || (height__i < max_height__i)) {
	  x__i = indent_distance__i;
	  if ((! left_extent) || x__i < left_extent__i) {
	    left_extent__i = x__i;
	    if (! left_extent) {
	      left_extent = f2bool__new(boolean__true);
	    }
	  }
	  height__i ++;
	}
	break;
      case '\t':
	{
	  u64 spaces_until_next_tab = x__i - (((x__i + 7) >> 3) << 3);
	  if ((testing == nil) && (x__i + spaces_until_next_tab < max_x__i)) {
	    u64 subindex;
	    for (subindex = 0; subindex < spaces_until_next_tab; subindex ++) {
	      if (use_html_codes != nil) {
		raw__stream__writef(cause, stream, "&nbsp;");
	      } else {
		raw__stream__writef(cause, stream, " ");
	      }
	    }
	  }
	  if ((testing != nil) || (x__i + spaces_until_next_tab < max_x__i)) {
	    x__i += spaces_until_next_tab;
	    if ((! right_extent) || x__i > right_extent__i) {
	      right_extent__i = x__i;
	      if (! right_extent) {
		right_extent = f2bool__new(boolean__true);
	      }
	    }
	  }
	}
	break;
      default:
	if ((testing == nil) && (x__i < max_x__i)) {
	  if (ch >= 28 && ch <= 255) {
	    switch(ch) {
	    case ' ':
	      if (use_html_codes != nil) {
		raw__stream__writef(cause, stream, "&nbsp;");
	      } else {
		raw__stream__writef(cause, stream, " ");
	      }
	      break;
	    default:
	      raw__stream__writef(cause, stream, "%c", ch);
	      break;
	    }
	  } else {
	    raw__stream__writef(cause, stream, "?");
	  }
	}
	if ((testing != nil) || (x__i < max_x__i)) {
	  x__i ++;
	  if ((! right_extent) || x__i > right_extent__i) {
	    right_extent__i = x__i;
	    if (! right_extent) {
	      right_extent = f2bool__new(boolean__true);
	    }
	  }
	}
	break;
      }
    }
  }
  if (testing != nil) {
    if (right_extent__i >= max_x__i) {
      f2__terminal_print_frame__failed_max_x_constraint__set(cause, this, f2bool__new(boolean__true));
    }
    if (height__i >= max_height__i) {
      f2__terminal_print_frame__failed_max_height_constraint__set(cause, this, f2bool__new(boolean__true));
    }
  }
  f2__terminal_print_frame__x__set(           cause, this, f2integer__new(cause, x__i));
  f2__terminal_print_frame__height__set(      cause, this, f2integer__new(cause, height__i));
  f2__terminal_print_frame__left_extent__set( cause, this, f2integer__new(cause, left_extent__i));
  f2__terminal_print_frame__right_extent__set(cause, this, f2integer__new(cause, right_extent__i));
}

f2ptr f2__terminal_print_frame__write_string(f2ptr cause, f2ptr this, f2ptr string) {
  if ((! raw__terminal_print_frame__is_type(cause, this)) ||
      (! raw__string__is_type(cause, string))) {
    return f2larva__new(cause, 1, nil);
  }
  u64 string__length = f2string__length(string, cause);
  u8* string__str    = (u8*)alloca(string__length);
  raw__string__str_copy(cause, string, string__str);
  string__str[string__length] = '\0';
  raw__terminal_print_frame__write_string(cause, this, string__length, string__str);
  return nil;
}
def_pcfunk2(terminal_print_frame__write_string, this, string, return f2__terminal_print_frame__write_string(this_cause, this, string));


f2ptr raw__terminal_print_frame__can_print_expression_on_one_line(f2ptr cause, f2ptr this, f2ptr expression) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, expression, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"));
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(boolean__true);
  }
  f2ptr     encountered_larva = nil;
  boolean_t can_print_on_one_line;
  {
    f2ptr failed_max_x_constraint       = f2__terminal_print_frame__failed_max_x_constraint(      cause, this);
    f2ptr failed_max_height_constraint  = f2__terminal_print_frame__failed_max_height_constraint( cause, this);
    f2ptr testing                       = f2__terminal_print_frame__testing(                      cause, this);
    f2ptr testing_max_x_constraint      = f2__terminal_print_frame__testing_max_x_constraint(     cause, this);
    f2ptr testing_max_height_constraint = f2__terminal_print_frame__testing_max_height_constraint(cause, this);
    f2ptr testing_x_offset              = f2__terminal_print_frame__testing_x_offset(             cause, this);
    f2ptr use_one_line                  = f2__terminal_print_frame__use_one_line(                 cause, this);
    f2ptr max_size                      = f2__terminal_print_frame__max_size(                     cause, this);
    
    {
      f2ptr x               = f2__terminal_print_frame__x(              cause, this);
      f2ptr height          = f2__terminal_print_frame__height(         cause, this);
      f2ptr left_extent     = f2__terminal_print_frame__left_extent(    cause, this);
      f2ptr right_extent    = f2__terminal_print_frame__right_extent(   cause, this);
      f2ptr indent_distance = f2__terminal_print_frame__indent_distance(cause, this);
      f2ptr size            = f2__terminal_print_frame__size(           cause, this);
      {
	f2__terminal_print_frame__left_extent__set(                  cause, this, nil);
	f2__terminal_print_frame__right_extent__set(                 cause, this, nil);
	f2__terminal_print_frame__use_one_line__set(                 cause, this, f2bool__new(boolean__true));
	f2__terminal_print_frame__failed_max_x_constraint__set(      cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_height_constraint__set( cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing__set(                      cause, this, f2bool__new(boolean__true));
	f2__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__true));
	f2__terminal_print_frame__testing_max_height_constraint__set(cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing_x_offset__set(             cause, this, f2bool__new(boolean__false));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, expression, f2cons__new(cause, this, nil)));
	if (raw__larva__is_type(cause, result)) {
	  encountered_larva = result;
	}
      }
      f2__terminal_print_frame__x__set(              cause, this, x);
      f2__terminal_print_frame__height__set(         cause, this, height);
      f2__terminal_print_frame__left_extent__set(    cause, this, left_extent);
      f2__terminal_print_frame__right_extent__set(   cause, this, right_extent);
      f2__terminal_print_frame__indent_distance__set(cause, this, indent_distance);
      f2__terminal_print_frame__size__set(           cause, this, size);
    }
    
    can_print_on_one_line = (f2__terminal_print_frame__failed_max_x_constraint(cause, this) == nil);
    
    f2__terminal_print_frame__failed_max_x_constraint__set(      cause, this, failed_max_x_constraint);
    f2__terminal_print_frame__failed_max_height_constraint__set( cause, this, failed_max_height_constraint);
    f2__terminal_print_frame__testing__set(                      cause, this, testing);
    f2__terminal_print_frame__testing_max_x_constraint__set(     cause, this, testing_max_x_constraint);
    f2__terminal_print_frame__testing_max_height_constraint__set(cause, this, testing_max_height_constraint);
    f2__terminal_print_frame__testing_x_offset__set(             cause, this, testing_x_offset);
    f2__terminal_print_frame__use_one_line__set(                 cause, this, use_one_line);
    f2__terminal_print_frame__max_size__set(                     cause, this, max_size);
  }
  if (encountered_larva != nil) {
    return encountered_larva;
  }
  return f2bool__new(can_print_on_one_line);
}

f2ptr f2__terminal_print_frame__can_print_expression_on_one_line(f2ptr cause, f2ptr this, f2ptr expression) {
  if (! raw__terminal_print_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__terminal_print_frame__can_print_expression_on_one_line(cause, this, expression);
}
def_pcfunk2(terminal_print_frame__can_print_expression_on_one_line, this, expression, return f2__terminal_print_frame__can_print_expression_on_one_line(this_cause, this, expression));


f2ptr raw__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint(f2ptr cause, f2ptr this, f2ptr expression) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, expression, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"));
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(boolean__false);
  }
  f2ptr encountered_larva                 = nil;
  f2ptr size_that_fails_height_constraint = nil;
  {
    f2ptr failed_max_x_constraint       = f2__terminal_print_frame__failed_max_x_constraint(      cause, this);
    f2ptr failed_max_height_constraint  = f2__terminal_print_frame__failed_max_height_constraint( cause, this);
    f2ptr testing                       = f2__terminal_print_frame__testing(                      cause, this);
    f2ptr testing_max_x_constraint      = f2__terminal_print_frame__testing_max_x_constraint(     cause, this);
    f2ptr testing_max_height_constraint = f2__terminal_print_frame__testing_max_height_constraint(cause, this);
    f2ptr testing_x_offset              = f2__terminal_print_frame__testing_x_offset(             cause, this);
    f2ptr use_one_line                  = f2__terminal_print_frame__use_one_line(                 cause, this);
    f2ptr max_size                      = f2__terminal_print_frame__max_size(                     cause, this);
    
    {
      f2ptr x               = f2__terminal_print_frame__x(              cause, this);
      f2ptr height          = f2__terminal_print_frame__height(         cause, this);
      f2ptr left_extent     = f2__terminal_print_frame__left_extent(    cause, this);
      f2ptr right_extent    = f2__terminal_print_frame__right_extent(   cause, this);
      f2ptr indent_distance = f2__terminal_print_frame__indent_distance(cause, this);
      f2ptr size            = f2__terminal_print_frame__size(           cause, this);
      {
	f2__terminal_print_frame__left_extent__set(                  cause, this, nil);
	f2__terminal_print_frame__right_extent__set(                 cause, this, nil);
	f2__terminal_print_frame__use_one_line__set(                 cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_x_constraint__set(      cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_height_constraint__set( cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing__set(                      cause, this, f2bool__new(boolean__true));
	f2__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing_max_height_constraint__set(cause, this, f2bool__new(boolean__true));
	f2__terminal_print_frame__testing_x_offset__set(             cause, this, f2bool__new(boolean__false));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, expression, f2cons__new(cause, this, nil)));
	if (raw__larva__is_type(cause, result)) {
	  encountered_larva = result;
	}
      }
      
      if (f2__terminal_print_frame__failed_max_height_constraint(cause, this) != nil) {
	size_that_fails_height_constraint = f2__terminal_print_frame__size(cause, nil);
      }
      
      f2__terminal_print_frame__x__set(              cause, this, x);
      f2__terminal_print_frame__height__set(         cause, this, height);
      f2__terminal_print_frame__left_extent__set(    cause, this, left_extent);
      f2__terminal_print_frame__right_extent__set(   cause, this, right_extent);
      f2__terminal_print_frame__indent_distance__set(cause, this, indent_distance);
      f2__terminal_print_frame__size__set(           cause, this, size);
    }
    
    f2__terminal_print_frame__failed_max_x_constraint__set(      cause, this, failed_max_x_constraint);
    f2__terminal_print_frame__failed_max_height_constraint__set( cause, this, failed_max_height_constraint);
    f2__terminal_print_frame__testing__set(                      cause, this, testing);
    f2__terminal_print_frame__testing_max_x_constraint__set(     cause, this, testing_max_x_constraint);
    f2__terminal_print_frame__testing_max_height_constraint__set(cause, this, testing_max_height_constraint);
    f2__terminal_print_frame__testing_x_offset__set(             cause, this, testing_x_offset);
    f2__terminal_print_frame__use_one_line__set(                 cause, this, use_one_line);
    f2__terminal_print_frame__max_size__set(                     cause, this, max_size);
  }
  if (encountered_larva != nil) {
    return encountered_larva;
  }
  return size_that_fails_height_constraint;
}

f2ptr f2__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint(f2ptr cause, f2ptr this, f2ptr expression) {
  if (! raw__terminal_print_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint(cause, this, expression);
}
def_pcfunk2(terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint, this, expression, return f2__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint(this_cause, this, expression));


f2ptr raw__terminal_print_frame__expression_x_offset(f2ptr cause, f2ptr this, f2ptr expression) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, expression, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"));
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(boolean__false);
  }
  f2ptr encountered_larva = nil;
  s64   x_offset;
  {
    f2ptr failed_max_x_constraint       = f2__terminal_print_frame__failed_max_x_constraint(      cause, this);
    f2ptr failed_max_height_constraint  = f2__terminal_print_frame__failed_max_height_constraint( cause, this);
    f2ptr testing                       = f2__terminal_print_frame__testing(                      cause, this);
    f2ptr testing_max_x_constraint      = f2__terminal_print_frame__testing_max_x_constraint(     cause, this);
    f2ptr testing_max_height_constraint = f2__terminal_print_frame__testing_max_height_constraint(cause, this);
    f2ptr testing_x_offset              = f2__terminal_print_frame__testing_x_offset(             cause, this);
    f2ptr use_one_line                  = f2__terminal_print_frame__use_one_line(                 cause, this);
    f2ptr max_size                      = f2__terminal_print_frame__max_size(                     cause, this);
    
    {
      f2ptr x               = f2__terminal_print_frame__x(              cause, this);
      s64   x__i            = f2integer__i(x, cause);
      f2ptr height          = f2__terminal_print_frame__height(         cause, this);
      f2ptr left_extent     = f2__terminal_print_frame__left_extent(    cause, this);
      f2ptr right_extent    = f2__terminal_print_frame__right_extent(   cause, this);
      f2ptr indent_distance = f2__terminal_print_frame__indent_distance(cause, this);
      f2ptr size            = f2__terminal_print_frame__size(           cause, this);
      {
	f2__terminal_print_frame__left_extent__set(                  cause, this, nil);
	f2__terminal_print_frame__right_extent__set(                 cause, this, nil);
	f2__terminal_print_frame__use_one_line__set(                 cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_x_constraint__set(      cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__failed_max_height_constraint__set( cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing__set(                      cause, this, f2bool__new(boolean__true));
	f2__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing_max_height_constraint__set(cause, this, f2bool__new(boolean__false));
	f2__terminal_print_frame__testing_x_offset__set(             cause, this, f2bool__new(boolean__true));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, expression, f2cons__new(cause, this, nil)));
	if (raw__larva__is_type(cause, result)) {
	  encountered_larva = result;
	}
      }
      
      f2ptr new_x    = f2__terminal_print_frame__x(cause, this);
      s64   new_x__i = f2integer__i(new_x, cause);
      
      x_offset = new_x__i - x__i;
      
      f2__terminal_print_frame__x__set(              cause, this, x);
      f2__terminal_print_frame__height__set(         cause, this, height);
      f2__terminal_print_frame__left_extent__set(    cause, this, left_extent);
      f2__terminal_print_frame__right_extent__set(   cause, this, right_extent);
      f2__terminal_print_frame__indent_distance__set(cause, this, indent_distance);
      f2__terminal_print_frame__size__set(           cause, this, size);
    }
    
    f2__terminal_print_frame__failed_max_x_constraint__set(      cause, this, failed_max_x_constraint);
    f2__terminal_print_frame__failed_max_height_constraint__set( cause, this, failed_max_height_constraint);
    f2__terminal_print_frame__testing__set(                      cause, this, testing);
    f2__terminal_print_frame__testing_max_x_constraint__set(     cause, this, testing_max_x_constraint);
    f2__terminal_print_frame__testing_max_height_constraint__set(cause, this, testing_max_height_constraint);
    f2__terminal_print_frame__testing_x_offset__set(             cause, this, testing_x_offset);
    f2__terminal_print_frame__use_one_line__set(                 cause, this, use_one_line);
    f2__terminal_print_frame__max_size__set(                     cause, this, max_size);
  }
  if (encountered_larva != nil) {
    return encountered_larva;
  }
  return f2integer__new(cause, x_offset);
}

f2ptr f2__terminal_print_frame__expression_x_offset(f2ptr cause, f2ptr this, f2ptr expression) {
  if (! raw__terminal_print_frame__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__terminal_print_frame__expression_x_offset(cause, this, expression);
}
def_pcfunk2(terminal_print_frame__expression_x_offset, this, expression, return f2__terminal_print_frame__expression_x_offset(this_cause, this, expression));


f2ptr raw__exp__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr fiber            = f2__this__fiber(cause);
  f2ptr funk             = f2__object__slot__type_funk(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "terminal_print_with_frame"));
  f2ptr testing          = f2__terminal_print_frame__testing(         cause, terminal_print_frame);
  f2ptr use_one_line     = f2__terminal_print_frame__use_one_line(    cause, terminal_print_frame);
  f2ptr indent_distance  = f2__terminal_print_frame__indent_distance( cause, terminal_print_frame);
  if (raw__funkable__is_type(cause, funk)) {
    f2ptr can_print_on_one_line = f2__terminal_print_frame__can_print_expression_on_one_line(cause, terminal_print_frame, this);
    if (raw__larva__is_type(cause, can_print_on_one_line)) {
      return can_print_on_one_line;
    }
    if (can_print_on_one_line != nil) {
      // we successfully satisfied all constraints by printing on one line, so go for it.
      f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__true));
      f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else {
      f2__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__false));
      // iteratively reduce max size if we fail to satisfy y constraint.
      f2ptr original_max_size = f2__terminal_print_frame__max_size(cause, terminal_print_frame);
      {
	s64   working_size                  = 0;
	f2ptr max_size                      = original_max_size;
	s64   max_size__i                   = f2integer__i(max_size, cause);
	s64   last_max_size__i;
	f2ptr size_that_fails_to_fit_within_height_constraint = f2__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint(cause, terminal_print_frame, this);
	if (raw__larva__is_type(cause, size_that_fails_to_fit_within_height_constraint)) {
	  return size_that_fails_to_fit_within_height_constraint;
	}
	if (size_that_fails_to_fit_within_height_constraint != nil) {
	  while (max_size__i != working_size) {
	    last_max_size__i = max_size__i;
	    max_size__i      = working_size + ((max_size__i - working_size) >> 1);
	    max_size         = f2integer__new(cause, max_size__i);
	    f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
	    if (max_size__i == 0) {
	      if (testing == nil) {
		return f2larva__new(cause, 3342,
				    f2__bug__new(cause, f2integer__new(cause, 3342),
						 f2__frame__new(cause, f2list10__new(cause, 
										     new__symbol(cause, "bug_type"),       new__symbol(cause, "reduced_expression_to_print_at_size_zero_and_still_failed_height_constraint"),
										     new__symbol(cause, "funk_name"),      new__symbol(cause, "raw__exp__terminal_print_with_frame"),
										     new__symbol(cause, "source_file"),    new__string(cause, __FILE__),
										     new__symbol(cause, "source_line"),    f2integer__new(cause, __LINE__),
										     new__symbol(cause, "argument_frame"), f2__frame__new(cause, f2list4__new(cause,
																			      new__symbol(cause, "this"),                 this,
																			      new__symbol(cause, "terminal_print_frame"), terminal_print_frame))))));
	      } else {
		f2__terminal_print_frame__failed_max_height_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
	      }
	    } else {
	      size_that_fails_to_fit_within_height_constraint = f2__terminal_print_frame__size_that_fails_to_fit_within_height_constraint(cause, terminal_print_frame, this);
	      if (raw__larva__is_type(cause, size_that_fails_to_fit_within_height_constraint)) {
		return size_that_fails_to_fit_within_height_constraint;
	      }
	      if (size_that_fails_to_fit_within_height_constraint == nil) {
		working_size = max_size__i;
		if (last_max_size__i > max_size__i + 1) {
		  max_size__i = last_max_size__i;
		}
	      }
	    }
	  }
	}
	if (max_size__i > 0) {
	  f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	  if (raw__larva__is_type(cause, result)) {
	    return result;
	  }
	}
      }
      f2__terminal_print_frame__max_size__set(cause, terminal_print_frame, original_max_size);
    }
  } else {
    // this object type doesn't have a terminal_print_with_frame funktion.
    //  ... we should print object type here and some short opaque, non-recursive description with size one.
  }
  f2__terminal_print_frame__use_one_line__set(   cause, terminal_print_frame, use_one_line);
  f2__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
  return nil;
}

f2ptr f2__exp__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (! raw__terminal_print_frame__is_type(cause, terminal_print_frame)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__exp__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(exp__terminal_print_with_frame, this, terminal_print_frame, return f2__exp__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2__exp__terminal_stream_print(f2ptr cause, f2ptr this, f2ptr stream) {
  f2ptr indent_distance      = f2integer__new(cause, 0);
  s64   max_x__i             = raw__termios__width();
  f2ptr max_x                = f2integer__new(cause, max_x__i);
  s64   max_height__i        = raw__termios__height() - 3;
  if (max_height__i <= 0) {
    max_height__i = 1;
  }
  f2ptr max_height           = f2integer__new(cause, max_height__i);
  f2ptr max_size             = f2integer__new(cause, ((max_x__i * max_height__i) >> 1));
  f2ptr use_ansi_codes       = f2bool__new(boolean__true);
  f2ptr use_html_codes       = f2bool__new(boolean__false);
  f2ptr terminal_print_frame = f2__terminal_print_frame__new(cause, stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes);
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
  
  init_frame_object__20_slot(terminal_print_frame,
			     testing,
			     testing_max_x_constraint,
			     testing_max_height_constraint,
			     testing_x_offset,
			     stream,
			     indent_distance,
			     max_x,
			     max_height,
			     max_size,
			     use_ansi_codes,
			     use_html_codes,
			     x,
			     height,
			     size,
			     left_extent,
			     right_extent,
			     already_printed_hash,
			     use_one_line,
			     failed_max_x_constraint,
			     failed_max_height_constraint);
  
  f2__primcfunk__init__7(terminal_print_frame__new,                                             stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes, "");
  f2__primcfunk__init__2(terminal_print_frame__write_string,                                    this, string,                                                                         "");
  f2__primcfunk__init__2(terminal_print_frame__can_print_expression_on_one_line,                this, expression,                                                                     "");
  f2__primcfunk__init__2(terminal_print_frame__size_that_fails_to_fit_within_height_constraint, this, expression,                                                                     "");
  f2__primcfunk__init__2(terminal_print_frame__expression_x_offset,                             this, expression,                                                                     "");
  
  f2__primcfunk__init__2(exp__terminal_print_with_frame, this, terminal_print_frame, "Prints a value given a terminal_print_frame.");
  f2__primcfunk__init__2(exp__terminal_stream_print,     this, stream,               "Prints a value to the given terminal stream, using a new default terminal_print_frame.");
  
}


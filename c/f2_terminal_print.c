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


// terminal_print_frame

def_frame_object__global__25_slot(terminal_print_frame,
				  cmutex,
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
				  failed_max_height_constraint,
				  failed_max_size_constraint,
				  resize_to_fit,
				  max_nanoseconds_for_resize,
				  print_as_frame_hash);

f2ptr f2__terminal_print_frame__new(f2ptr cause, f2ptr stream, f2ptr indent_distance, f2ptr max_x, f2ptr max_height, f2ptr max_size, f2ptr use_ansi_codes, f2ptr use_html_codes, f2ptr resize_to_fit, f2ptr max_nanoseconds_for_resize) {
  assert_argument_type(stream,  stream);
  assert_argument_type(integer, indent_distance);
  assert_argument_type(integer, max_x);
  assert_argument_type(integer, max_height);
  assert_argument_type(integer, max_size);
  assert_argument_type(integer, max_nanoseconds_for_resize);
  f2ptr cmutex                         = f2__cmutex__new(cause);
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
  f2ptr use_one_line                  = f2bool__new(boolean__false);
  f2ptr failed_max_x_constraint       = f2bool__new(boolean__false);
  f2ptr failed_max_height_constraint  = f2bool__new(boolean__false);
  f2ptr failed_max_size_constraint    = f2bool__new(boolean__false);
  f2ptr print_as_frame_hash           = f2__ptypehash__new(cause);
  return f2terminal_print_frame__new(cause,
				     cmutex,
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
				     failed_max_height_constraint,
				     failed_max_size_constraint,
				     resize_to_fit,
				     max_nanoseconds_for_resize,
				     print_as_frame_hash);
}
def_pcfunk9(terminal_print_frame__new, stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes, resize_to_fit, max_nanoseconds_for_resize,
	    "",
	    return f2__terminal_print_frame__new(this_cause, stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes, resize_to_fit, max_nanoseconds_for_resize));


f2ptr raw__terminal_print_frame__new_copy(f2ptr cause, f2ptr this) {
  f2ptr cmutex                = f2__cmutex__new(cause);
  f2ptr already_printed_hash = f2__ptypehash__new(cause);
  f2ptr print_as_frame_hash  = f2__ptypehash__new(cause);
  return f2terminal_print_frame__new(cause,
				     cmutex,
				     f2__terminal_print_frame__testing(                      cause, this),
				     f2__terminal_print_frame__testing_max_x_constraint(     cause, this),
				     f2__terminal_print_frame__testing_max_height_constraint(cause, this),
				     f2__terminal_print_frame__testing_x_offset(             cause, this),
				     f2__terminal_print_frame__stream(                       cause, this),
				     f2__terminal_print_frame__indent_distance(              cause, this),
				     f2__terminal_print_frame__max_x(                        cause, this),
				     f2__terminal_print_frame__max_height(                   cause, this),
				     f2__terminal_print_frame__max_size(                     cause, this),
				     f2__terminal_print_frame__use_ansi_codes(               cause, this),
				     f2__terminal_print_frame__use_html_codes(               cause, this),
				     f2__terminal_print_frame__x(                            cause, this),
				     f2__terminal_print_frame__height(                       cause, this),
				     f2__terminal_print_frame__size(                         cause, this),
				     f2__terminal_print_frame__left_extent(                  cause, this),
				     f2__terminal_print_frame__right_extent(                 cause, this),
				     already_printed_hash,
				     f2__terminal_print_frame__use_one_line(                 cause, this),
				     f2__terminal_print_frame__failed_max_x_constraint(      cause, this),
				     f2__terminal_print_frame__failed_max_height_constraint( cause, this),
				     f2__terminal_print_frame__failed_max_size_constraint(   cause, this),
				     f2__terminal_print_frame__resize_to_fit(                cause, this),
				     f2__terminal_print_frame__max_nanoseconds_for_resize(   cause, this),
				     print_as_frame_hash);
}

f2ptr f2__terminal_print_frame__new_copy(f2ptr cause, f2ptr this) {
  assert_argument_type(terminal_print_frame, this);
  return raw__terminal_print_frame__new_copy(cause, this);
}
def_pcfunk1(terminal_print_frame__new_copy, this,
	    "",
	    return f2__terminal_print_frame__new_copy(this_cause, this));


boolean_t raw__terminal_print_frame__failed_test_constraint_and_should_return(f2ptr cause, f2ptr this) {
  boolean_t testing = (raw__terminal_print_frame__testing(cause, this) != nil);
  if (! testing) {
    return boolean__false;
  }
  boolean_t testing_x_offset = (raw__terminal_print_frame__testing_x_offset(cause, this) != nil);
  if (testing_x_offset) {
    {
      f2ptr x             = raw__terminal_print_frame__x(cause, this);
      s64   x__i          = f2integer__i(x, cause);
      f2ptr max_x         = raw__terminal_print_frame__max_x(cause, this);
      s64   max_x__i      = f2integer__i(max_x, cause);
      if (x__i >= max_x__i) {
	return boolean__true;
      }
    }
    {
      f2ptr height        = raw__terminal_print_frame__height(cause, this);
      s64   height__i     = f2integer__i(height, cause);
      f2ptr max_height    = raw__terminal_print_frame__max_height(cause, this);
      s64   max_height__i = f2integer__i(max_height, cause);
      if (height__i >= max_height__i) {
	return boolean__true;
      }
    }
    return boolean__false;
  }
  boolean_t testing_max_x_constraint      = (raw__terminal_print_frame__testing_max_x_constraint(     cause, this) != nil);
  boolean_t testing_max_height_constraint = (raw__terminal_print_frame__testing_max_height_constraint(cause, this) != nil);
  if (testing_max_x_constraint &&
      (! testing_max_height_constraint)) {
    boolean_t failed_max_x_constraint = (raw__terminal_print_frame__failed_max_x_constraint(cause, this) != nil);
    if (failed_max_x_constraint) {
      return boolean__true;
    }
  } else if ((! testing_max_x_constraint) &&
	     testing_max_height_constraint) {
    boolean_t failed_max_height_constraint = (raw__terminal_print_frame__failed_max_height_constraint(cause, this) != nil);
    if (failed_max_height_constraint) {
      return boolean__true;
    }
  } else if (testing_max_x_constraint &&
	     testing_max_height_constraint) {
    boolean_t failed_max_x_constraint      = (raw__terminal_print_frame__failed_max_x_constraint(     cause, this) != nil);
    boolean_t failed_max_height_constraint = (raw__terminal_print_frame__failed_max_height_constraint(cause, this) != nil);
    if (failed_max_height_constraint ||
	failed_max_x_constraint) {
      return boolean__true;
    }
  }
  return boolean__false;
}


void raw__terminal_print_frame__write_color__thread_unsafe(f2ptr cause, f2ptr this, ansi_color_t color) {
  f2ptr testing        = raw__terminal_print_frame__testing(cause, this);
  f2ptr stream         = raw__terminal_print_frame__stream(cause, this);
  f2ptr use_ansi_codes = raw__terminal_print_frame__use_ansi_codes(cause, this);
  f2ptr use_html_codes = raw__terminal_print_frame__use_html_codes(cause, this);
  if ((testing == nil) && (use_ansi_codes != nil)) {f2__ansi__stream__reset(cause, stream); raw__ansi__stream__foreground(cause, stream, color);}
  if ((testing == nil) && (use_html_codes != nil)) {html__stream__ansi_foreground(cause, stream, color);}
}

f2ptr f2__terminal_print_frame__write_color__thread_unsafe(f2ptr cause, f2ptr this, f2ptr color) {
  assert_argument_type(terminal_print_frame, this);
  assert_argument_type(integer,              color);
  s64 color__i = f2integer__i(color, cause);
  if (color__i < 0 || color__i > 15) {
    return f2larva__new(cause, 2, nil);
  }
  ansi_color_t ansi_color = (ansi_color_t)color__i;
  raw__terminal_print_frame__write_color__thread_unsafe(cause, this, ansi_color);
  return nil;
}
def_pcfunk2(terminal_print_frame__write_color__thread_unsafe, this, color,
	    "",
	    return f2__terminal_print_frame__write_color__thread_unsafe(this_cause, this, color));


void raw__terminal_print_frame__write_string__thread_unsafe(f2ptr cause, f2ptr this, u64 length, funk2_character_t* string) {
  f2ptr testing            = raw__terminal_print_frame__testing(cause, this);
  f2ptr stream             = raw__terminal_print_frame__stream(cause, this);
  f2ptr indent_distance    = raw__terminal_print_frame__indent_distance(cause, this);
  s64   indent_distance__i = f2integer__i(indent_distance, cause);
  f2ptr x                  = raw__terminal_print_frame__x(cause, this);
  s64   x__i               = f2integer__i(x, cause);
  f2ptr height             = raw__terminal_print_frame__height(cause, this);
  s64   height__i          = f2integer__i(height, cause);
  f2ptr max_x              = raw__terminal_print_frame__max_x(cause, this);
  s64   max_x__i           = f2integer__i(max_x, cause);
  f2ptr max_height         = raw__terminal_print_frame__max_height(cause, this);
  s64   max_height__i      = f2integer__i(max_height, cause);
  f2ptr left_extent        = raw__terminal_print_frame__left_extent(cause, this);
  s64   left_extent__i     = left_extent ? f2integer__i(left_extent, cause) : 0;
  f2ptr right_extent       = raw__terminal_print_frame__right_extent(cause, this);
  s64   right_extent__i    = right_extent ? f2integer__i(right_extent, cause) : 0;
  f2ptr use_html_codes     = raw__terminal_print_frame__use_html_codes(cause, this);
  {
    u64 index;
    for (index = 0; index < length; index ++) {
      funk2_character_t ch = string[index];
      switch(ch) {
      case (funk2_character_t)'\r':
	break;
      case (funk2_character_t)'\n':
	if ((testing == nil) && (height__i < max_height__i)) {
	  if (use_html_codes) {
	    raw__stream__writef(cause, stream, "<br>");
	  }
	  
	  raw__stream__writef(cause, stream, "\r\n");
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
      case (funk2_character_t)'\t':
	{
	  s64 spaces_until_next_tab = (x__i < 0) ? 8 : ((((x__i + 8) >> 3) << 3) - x__i);
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
      case (funk2_character_t)'\b':
	if (x__i > 0) {
	  raw__stream__writef(cause, stream, "\b");
	  x__i --;
	}
	break;
      default:
	if (testing == nil) {
	  if (x__i >= max_x__i) {
	    if (use_html_codes) {
	      raw__stream__writef(cause, stream, "<br>");
	    }
	    raw__stream__writef(cause, stream, "\r\n");
	  }
	  if (ch >= 28 && ch != 0x7F) {
	    switch(ch) {
	    case (funk2_character_t)' ':
	      if (use_html_codes != nil) {
		raw__stream__writef(cause, stream, "&nbsp;");
	      } else {
		raw__stream__writef(cause, stream, " ");
	      }
	      break;
	    default:
	      raw__stream__write_character(cause, stream, ch);
	      break;
	    }
	  } else {
	    funk2_character_t replacement_character = (funk2_character_t)0xFFFD;
	    raw__stream__write_character(cause, stream, replacement_character);
	  }
	}
	if ((testing == nil) || (x__i < max_x__i)) {
	  if ((testing == nil) && (x__i >= max_x__i)) {
	    x__i = indent_distance__i;
	    if ((! left_extent) || x__i < left_extent__i) {
	      left_extent__i = x__i;
	      if (! left_extent) {
		left_extent = f2bool__new(boolean__true);
	      }
	    }
	    height__i ++;
	  }
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
      raw__terminal_print_frame__failed_max_x_constraint__set(cause, this, f2bool__new(boolean__true));
    }
    if (height__i >= max_height__i) {
      raw__terminal_print_frame__failed_max_height_constraint__set(cause, this, f2bool__new(boolean__true));
    }
  }
  raw__terminal_print_frame__x__set(           cause, this, f2integer__new(cause, x__i));
  raw__terminal_print_frame__height__set(      cause, this, f2integer__new(cause, height__i));
  raw__terminal_print_frame__left_extent__set( cause, this, f2integer__new(cause, left_extent__i));
  raw__terminal_print_frame__right_extent__set(cause, this, f2integer__new(cause, right_extent__i));
}

f2ptr f2__terminal_print_frame__write_string__thread_unsafe(f2ptr cause, f2ptr this, f2ptr string) {
  assert_argument_type(terminal_print_frame, this);
  assert_argument_type(string,               string);
  u64                string__length = f2string__length(string, cause);
  funk2_character_t* string__str    = (funk2_character_t*)from_ptr(f2__malloc((string__length + 1) * sizeof(funk2_character_t)));
  raw__string__str_copy(cause, string, string__str);
  string__str[string__length] = 0;
  raw__terminal_print_frame__write_string__thread_unsafe(cause, this, string__length, string__str);
  f2__free(to_ptr(string__str));
  return nil;
}
def_pcfunk2(terminal_print_frame__write_string__thread_unsafe, this, string,
	    "",
	    return f2__terminal_print_frame__write_string__thread_unsafe(this_cause, this, string));


void raw__terminal_print_frame__write_utf8_string__thread_unsafe(f2ptr cause, f2ptr this, u8* utf8_string) {
  u64                temp_str__length = raw__utf8_string__length((char*)utf8_string);
  funk2_character_t* temp_str         = (funk2_character_t*)from_ptr(f2__malloc(sizeof(funk2_character_t) * temp_str__length));
  raw__utf8_string__str_copy((char*)utf8_string, temp_str);
  raw__terminal_print_frame__write_string__thread_unsafe(cause, this, temp_str__length, temp_str);
  f2__free(to_ptr(temp_str));
}


f2ptr raw__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, expression, __funk2.globalenv.execute__symbol, __funk2.globalenv.terminal_print_with_frame__symbol);
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(boolean__true);
  }
  f2ptr     encountered_larva = nil;
  boolean_t can_print_on_one_line;
  {
    f2ptr failed_max_x_constraint       = raw__terminal_print_frame__failed_max_x_constraint(      cause, this);
    f2ptr failed_max_height_constraint  = raw__terminal_print_frame__failed_max_height_constraint( cause, this);
    f2ptr testing                       = raw__terminal_print_frame__testing(                      cause, this);
    f2ptr testing_max_x_constraint      = raw__terminal_print_frame__testing_max_x_constraint(     cause, this);
    f2ptr testing_max_height_constraint = raw__terminal_print_frame__testing_max_height_constraint(cause, this);
    f2ptr testing_x_offset              = raw__terminal_print_frame__testing_x_offset(             cause, this);
    f2ptr use_one_line                  = raw__terminal_print_frame__use_one_line(                 cause, this);
    f2ptr max_size                      = raw__terminal_print_frame__max_size(                     cause, this);
    f2ptr resize_to_fit                 = raw__terminal_print_frame__resize_to_fit(                cause, this);
    
    {
      f2ptr x               = raw__terminal_print_frame__x(              cause, this);
      f2ptr height          = raw__terminal_print_frame__height(         cause, this);
      f2ptr left_extent     = raw__terminal_print_frame__left_extent(    cause, this);
      f2ptr right_extent    = raw__terminal_print_frame__right_extent(   cause, this);
      f2ptr indent_distance = raw__terminal_print_frame__indent_distance(cause, this);
      f2ptr size            = raw__terminal_print_frame__size(           cause, this);
      {
	raw__terminal_print_frame__left_extent__set(                  cause, this, nil);
	raw__terminal_print_frame__right_extent__set(                 cause, this, nil);
	raw__terminal_print_frame__use_one_line__set(                 cause, this, f2bool__new(boolean__true));
	raw__terminal_print_frame__failed_max_x_constraint__set(      cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__failed_max_height_constraint__set( cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing__set(                      cause, this, f2bool__new(boolean__true));
	raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__true));
	raw__terminal_print_frame__testing_max_height_constraint__set(cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing_x_offset__set(             cause, this, f2bool__new(boolean__false));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, expression, f2cons__new(cause, this, nil)));
	if (raw__larva__is_type(cause, result)) {
	  encountered_larva = result;
	}
      }
      raw__terminal_print_frame__x__set(              cause, this, x);
      raw__terminal_print_frame__height__set(         cause, this, height);
      raw__terminal_print_frame__left_extent__set(    cause, this, left_extent);
      raw__terminal_print_frame__right_extent__set(   cause, this, right_extent);
      raw__terminal_print_frame__indent_distance__set(cause, this, indent_distance);
      raw__terminal_print_frame__size__set(           cause, this, size);
    }
    
    can_print_on_one_line = (raw__terminal_print_frame__failed_max_x_constraint(cause, this) == nil);
    
    raw__terminal_print_frame__failed_max_x_constraint__set(      cause, this, failed_max_x_constraint);
    raw__terminal_print_frame__failed_max_height_constraint__set( cause, this, failed_max_height_constraint);
    raw__terminal_print_frame__testing__set(                      cause, this, testing);
    raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, testing_max_x_constraint);
    raw__terminal_print_frame__testing_max_height_constraint__set(cause, this, testing_max_height_constraint);
    raw__terminal_print_frame__testing_x_offset__set(             cause, this, testing_x_offset);
    raw__terminal_print_frame__use_one_line__set(                 cause, this, use_one_line);
    raw__terminal_print_frame__max_size__set(                     cause, this, max_size);
    raw__terminal_print_frame__resize_to_fit__set(                cause, this, resize_to_fit);
  }
  if (encountered_larva != nil) {
    return encountered_larva;
  }
  return f2bool__new(can_print_on_one_line);
}

f2ptr f2__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression) {
  assert_argument_type(terminal_print_frame, this);
  return raw__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(cause, this, expression);
}
def_pcfunk2(terminal_print_frame__can_print_expression_on_one_line__thread_unsafe, this, expression,
	    "",
	    return f2__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(this_cause, this, expression));


f2ptr raw__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, expression, __funk2.globalenv.execute__symbol, __funk2.globalenv.terminal_print_with_frame__symbol);
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(boolean__false);
  }
  f2ptr encountered_larva                 = nil;
  f2ptr size_that_fails_height_constraint = nil;
  {
    f2ptr failed_max_x_constraint       = raw__terminal_print_frame__failed_max_x_constraint(      cause, this);
    f2ptr failed_max_height_constraint  = raw__terminal_print_frame__failed_max_height_constraint( cause, this);
    f2ptr testing                       = raw__terminal_print_frame__testing(                      cause, this);
    f2ptr testing_max_x_constraint      = raw__terminal_print_frame__testing_max_x_constraint(     cause, this);
    f2ptr testing_max_height_constraint = raw__terminal_print_frame__testing_max_height_constraint(cause, this);
    f2ptr testing_x_offset              = raw__terminal_print_frame__testing_x_offset(             cause, this);
    f2ptr use_one_line                  = raw__terminal_print_frame__use_one_line(                 cause, this);
    f2ptr max_size                      = raw__terminal_print_frame__max_size(                     cause, this);
    f2ptr resize_to_fit                 = raw__terminal_print_frame__resize_to_fit(                cause, this);
    
    {
      f2ptr x               = raw__terminal_print_frame__x(              cause, this);
      f2ptr height          = raw__terminal_print_frame__height(         cause, this);
      f2ptr left_extent     = raw__terminal_print_frame__left_extent(    cause, this);
      f2ptr right_extent    = raw__terminal_print_frame__right_extent(   cause, this);
      f2ptr indent_distance = raw__terminal_print_frame__indent_distance(cause, this);
      f2ptr size            = raw__terminal_print_frame__size(           cause, this);
      {
	raw__terminal_print_frame__left_extent__set(                  cause, this, nil);
	raw__terminal_print_frame__right_extent__set(                 cause, this, nil);
	raw__terminal_print_frame__use_one_line__set(                 cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__failed_max_x_constraint__set(      cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__failed_max_height_constraint__set( cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing__set(                      cause, this, f2bool__new(boolean__true));
	//raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__true));
	raw__terminal_print_frame__testing_max_height_constraint__set(cause, this, f2bool__new(boolean__true));
	raw__terminal_print_frame__testing_x_offset__set(             cause, this, f2bool__new(boolean__false));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, expression, f2cons__new(cause, this, nil)));
	if (raw__larva__is_type(cause, result)) {
	  encountered_larva = result;
	}
      }
      
      //if (raw__terminal_print_frame__failed_max_height_constraint(cause, this) != nil) {
	//(raw__terminal_print_frame__failed_max_x_constraint(     cause, this) != nil)) {
      if ((raw__terminal_print_frame__failed_max_height_constraint(cause, this) != nil) ||
	  (raw__terminal_print_frame__failed_max_x_constraint(     cause, this) != nil)) {
	size_that_fails_height_constraint = raw__terminal_print_frame__size(cause, this);
      }
      
      raw__terminal_print_frame__x__set(              cause, this, x);
      raw__terminal_print_frame__height__set(         cause, this, height);
      raw__terminal_print_frame__left_extent__set(    cause, this, left_extent);
      raw__terminal_print_frame__right_extent__set(   cause, this, right_extent);
      raw__terminal_print_frame__indent_distance__set(cause, this, indent_distance);
      raw__terminal_print_frame__size__set(           cause, this, size);
    }
    
    raw__terminal_print_frame__failed_max_x_constraint__set(      cause, this, failed_max_x_constraint);
    raw__terminal_print_frame__failed_max_height_constraint__set( cause, this, failed_max_height_constraint);
    raw__terminal_print_frame__testing__set(                      cause, this, testing);
    raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, testing_max_x_constraint);
    raw__terminal_print_frame__testing_max_height_constraint__set(cause, this, testing_max_height_constraint);
    raw__terminal_print_frame__testing_x_offset__set(             cause, this, testing_x_offset);
    raw__terminal_print_frame__use_one_line__set(                 cause, this, use_one_line);
    raw__terminal_print_frame__max_size__set(                     cause, this, max_size);
    raw__terminal_print_frame__resize_to_fit__set(                cause, this, resize_to_fit);
  }
  if (encountered_larva != nil) {
    return encountered_larva;
  }
  return size_that_fails_height_constraint;
}

f2ptr f2__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression) {
  assert_argument_type(terminal_print_frame, this);
  return raw__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(cause, this, expression);
}
def_pcfunk2(terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe, this, expression,
	    "",
	    return f2__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(this_cause, this, expression));


f2ptr raw__terminal_print_frame__expression_x_offset__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression) {
  f2ptr fiber = f2__this__fiber(cause);
  f2ptr funk  = f2__object__slot__type_funk(cause, expression, __funk2.globalenv.execute__symbol, __funk2.globalenv.terminal_print_with_frame__symbol);
  if (! raw__funkable__is_type(cause, funk)) {
    return f2bool__new(boolean__false);
  }
  f2ptr encountered_larva = nil;
  s64   x_offset;
  {
    f2ptr failed_max_x_constraint       = raw__terminal_print_frame__failed_max_x_constraint(      cause, this);
    f2ptr failed_max_height_constraint  = raw__terminal_print_frame__failed_max_height_constraint( cause, this);
    f2ptr testing                       = raw__terminal_print_frame__testing(                      cause, this);
    f2ptr testing_max_x_constraint      = raw__terminal_print_frame__testing_max_x_constraint(     cause, this);
    f2ptr testing_max_height_constraint = raw__terminal_print_frame__testing_max_height_constraint(cause, this);
    f2ptr testing_x_offset              = raw__terminal_print_frame__testing_x_offset(             cause, this);
    f2ptr use_one_line                  = raw__terminal_print_frame__use_one_line(                 cause, this);
    f2ptr max_size                      = raw__terminal_print_frame__max_size(                     cause, this);
    f2ptr resize_to_fit                 = raw__terminal_print_frame__resize_to_fit(                cause, this);
    
    {
      f2ptr x               = raw__terminal_print_frame__x(              cause, this);
      s64   x__i            = f2integer__i(x, cause);
      f2ptr height          = raw__terminal_print_frame__height(         cause, this);
      f2ptr left_extent     = raw__terminal_print_frame__left_extent(    cause, this);
      f2ptr right_extent    = raw__terminal_print_frame__right_extent(   cause, this);
      f2ptr indent_distance = raw__terminal_print_frame__indent_distance(cause, this);
      f2ptr size            = raw__terminal_print_frame__size(           cause, this);
      {
	raw__terminal_print_frame__left_extent__set(                  cause, this, nil);
	raw__terminal_print_frame__right_extent__set(                 cause, this, nil);
	raw__terminal_print_frame__use_one_line__set(                 cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__failed_max_x_constraint__set(      cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__failed_max_height_constraint__set( cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing__set(                      cause, this, f2bool__new(boolean__true));
	raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing_max_height_constraint__set(cause, this, f2bool__new(boolean__false));
	raw__terminal_print_frame__testing_x_offset__set(             cause, this, f2bool__new(boolean__true));
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, expression, f2cons__new(cause, this, nil)));
	if (raw__larva__is_type(cause, result)) {
	  encountered_larva = result;
	}
      }
      
      f2ptr new_x    = raw__terminal_print_frame__x(cause, this);
      s64   new_x__i = f2integer__i(new_x, cause);
      
      x_offset = new_x__i - x__i;
      
      raw__terminal_print_frame__x__set(              cause, this, x);
      raw__terminal_print_frame__height__set(         cause, this, height);
      raw__terminal_print_frame__left_extent__set(    cause, this, left_extent);
      raw__terminal_print_frame__right_extent__set(   cause, this, right_extent);
      raw__terminal_print_frame__indent_distance__set(cause, this, indent_distance);
      raw__terminal_print_frame__size__set(           cause, this, size);
    }
    
    raw__terminal_print_frame__failed_max_x_constraint__set(      cause, this, failed_max_x_constraint);
    raw__terminal_print_frame__failed_max_height_constraint__set( cause, this, failed_max_height_constraint);
    raw__terminal_print_frame__testing__set(                      cause, this, testing);
    raw__terminal_print_frame__testing_max_x_constraint__set(     cause, this, testing_max_x_constraint);
    raw__terminal_print_frame__testing_max_height_constraint__set(cause, this, testing_max_height_constraint);
    raw__terminal_print_frame__testing_x_offset__set(             cause, this, testing_x_offset);
    raw__terminal_print_frame__use_one_line__set(                 cause, this, use_one_line);
    raw__terminal_print_frame__max_size__set(                     cause, this, max_size);
    raw__terminal_print_frame__resize_to_fit__set(                cause, this, resize_to_fit);
  }
  if (encountered_larva != nil) {
    return encountered_larva;
  }
  return f2integer__new(cause, x_offset);
}

f2ptr f2__terminal_print_frame__expression_x_offset__thread_unsafe(f2ptr cause, f2ptr this, f2ptr expression) {
  assert_argument_type(terminal_print_frame, this);
  return raw__terminal_print_frame__expression_x_offset__thread_unsafe(cause, this, expression);
}
def_pcfunk2(terminal_print_frame__expression_x_offset__thread_unsafe, this, expression,
	    "",
	    return f2__terminal_print_frame__expression_x_offset__thread_unsafe(this_cause, this, expression));


void raw__terminal_print_frame__prepare_for_printing__thread_unsafe(f2ptr cause, f2ptr this, f2ptr max_x, f2ptr additional_height) {
  if (max_x != nil) {
    raw__terminal_print_frame__max_x__set(cause, this, max_x);
  }
  if (additional_height != nil) {
    s64   additional_height__i = f2integer__i(additional_height, cause);
    f2ptr height               = raw__terminal_print_frame__height(cause, this);
    s64   height__i            = f2integer__i(height, cause);
    s64   new_max_height__i    = height__i + additional_height__i;
    f2ptr new_max_height       = f2integer__new(cause, new_max_height__i);
    raw__terminal_print_frame__max_height__set(cause, this, new_max_height);
  }
  raw__terminal_print_frame__size__set(                cause, this, f2integer__new(cause, 0));
  raw__terminal_print_frame__already_printed_hash__set(cause, this, f2__ptypehash__new(cause));
  raw__terminal_print_frame__print_as_frame_hash__set( cause, this, f2__ptypehash__new(cause));
}

f2ptr f2__terminal_print_frame__prepare_for_printing__thread_unsafe(f2ptr cause, f2ptr this, f2ptr max_x, f2ptr additional_height) {
  assert_argument_type_or_nil(integer, max_x);
  assert_argument_type_or_nil(integer, additional_height);
  raw__terminal_print_frame__prepare_for_printing__thread_unsafe(cause, this, max_x, additional_height);
  return nil;
}
def_pcfunk3(terminal_print_frame__prepare_for_printing__thread_unsafe, this, max_x, additional_height,
	    "",
	    return f2__terminal_print_frame__prepare_for_printing__thread_unsafe(this_cause, this, max_x, additional_height));


f2ptr f2terminal_print_frame__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2terminal_print_frame__primobject_type__new(cause);
  {char* slot_name = "new_copy"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_terminal_print_frame.new_copy__funk);}
  return this;
}



f2ptr raw__exp__terminal_print_with_frame__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
    return nil;
  }
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  if (! raw__ptypehash__is_type(cause, print_as_frame_hash)) {
    return f2larva__new(cause, 1232, nil);
  }
  if ((! raw__frame__is_type(cause, this)) &&
      raw__ptypehash__contains(cause, print_as_frame_hash, this)) {
    f2ptr this_as_frame = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
    if (! raw__frame__is_type(cause, this_as_frame)) {
      return f2larva__new(cause, 4939, nil);
    }
    return raw__frame__terminal_print_with_frame(cause, this_as_frame, terminal_print_frame);
  }
  f2ptr fiber            = f2__this__fiber(cause);
  f2ptr funk             = f2__object__slot__type_funk(cause, this, __funk2.globalenv.execute__symbol, __funk2.globalenv.terminal_print_with_frame__symbol);
  f2ptr testing          = raw__terminal_print_frame__testing(         cause, terminal_print_frame);
  f2ptr use_one_line     = raw__terminal_print_frame__use_one_line(    cause, terminal_print_frame);
  f2ptr indent_distance  = raw__terminal_print_frame__indent_distance( cause, terminal_print_frame);
  f2ptr resize_to_fit    = raw__terminal_print_frame__resize_to_fit(cause, terminal_print_frame);
  raw__terminal_print_frame__resize_to_fit__set(cause, terminal_print_frame, f2bool__new(boolean__false));
  if (raw__funkable__is_type(cause, funk)) {
    f2ptr can_print_on_one_line = nil;
    if (use_one_line == nil) {
      can_print_on_one_line = raw__terminal_print_frame__can_print_expression_on_one_line__thread_unsafe(cause, terminal_print_frame, this);
      if (raw__larva__is_type(cause, can_print_on_one_line)) {
	return can_print_on_one_line;
      }
    }
    if ((use_one_line != nil) || (can_print_on_one_line != nil)) {
      // we successfully satisfied all constraints by printing on one line, so go for it.
      raw__terminal_print_frame__use_one_line__set(cause, terminal_print_frame, f2bool__new(boolean__true));
      f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
      if (raw__larva__is_type(cause, result)) {
	return result;
      }
    } else {
      if (resize_to_fit != nil) {
	// iteratively reduce max size if we fail to satisfy y constraint.
	f2ptr original_max_size                   = raw__terminal_print_frame__max_size(                  cause, terminal_print_frame);
	f2ptr original_failed_max_size_constraint = raw__terminal_print_frame__failed_max_size_constraint(cause, terminal_print_frame);
	f2ptr max_nanoseconds_for_resize          = raw__terminal_print_frame__max_nanoseconds_for_resize(cause, terminal_print_frame);
	s64   max_nanoseconds_for_resize__i       = f2integer__i(max_nanoseconds_for_resize, cause);
	s64   start_nanoseconds_since_1970        = raw__nanoseconds_since_1970();
	{
	  s64   low_successful_size           = 0;
	  s64   high_unsuccessful_size        = 0;
	  f2ptr max_size                      = original_max_size;
	  s64   max_size__i                   = f2integer__i(max_size, cause);
	  s64   last_max_size__i;
	  raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
	  f2ptr size_that_fails_to_fit_within_height_constraint = raw__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(cause, terminal_print_frame, this);
	  f2ptr failed_max_size_constraint                      = f2__terminal_print_frame__failed_max_size_constraint(cause, terminal_print_frame);
	  if (raw__larva__is_type(cause, size_that_fails_to_fit_within_height_constraint)) {
	    return size_that_fails_to_fit_within_height_constraint;
	  }
	  if (size_that_fails_to_fit_within_height_constraint != nil) {
	    if (high_unsuccessful_size == 0) {
	      high_unsuccessful_size = max_size__i;
	    } else if (max_size__i < high_unsuccessful_size) {
	      high_unsuccessful_size = max_size__i;
	    }
	  } else {
	    if (max_size__i > low_successful_size) {
	      low_successful_size = max_size__i;
	    }
	  }
	  status("raw__exp__terminal_print_with_frame__thread_unsafe: failed_max_size_constraint=%s", (failed_max_size_constraint != nil) ? "t" : "nil");
	  if ((size_that_fails_to_fit_within_height_constraint != nil) ||
	      (failed_max_size_constraint                      != nil)) {
	    while ((((high_unsuccessful_size != 0) && ((low_successful_size + 1) != high_unsuccessful_size)) ||
		    ((high_unsuccessful_size == 0) && (failed_max_size_constraint != nil))) &&
		   (((raw__nanoseconds_since_1970() - start_nanoseconds_since_1970) < max_nanoseconds_for_resize__i) ||
		    (low_successful_size == 0))) {
	      last_max_size__i = max_size__i;
	      s64 binary_search_size;
	      if (high_unsuccessful_size == 0) {
		binary_search_size = ((low_successful_size + 1) << 1);
	      } else {
		binary_search_size = low_successful_size + ((high_unsuccessful_size - low_successful_size) >> 1);
	      }
	      max_size__i = binary_search_size;
	      max_size = f2integer__new(cause, max_size__i);
	      raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
	      status("raw__exp__terminal_print_with_frame__thread_unsafe: low_successful_size=" s64__fstr ", high_unsuccessful_size=" s64__fstr, low_successful_size, high_unsuccessful_size);
	      status("raw__exp__terminal_print_with_frame__thread_unsafe: last_max_size__i=" s64__fstr ", max_size__i=" s64__fstr, last_max_size__i, max_size__i);
	      if (max_size__i == 0) {
		if (testing == nil) {
		  return f2larva__new(cause, 3342,
				      f2__bug__new(cause, f2integer__new(cause, 3342),
						   f2__frame__new(cause, f2list10__new(cause, 
										       new__symbol(cause, "bug_type"),       new__symbol(cause, "reduced_expression_to_print_at_size_zero_and_still_failed_height_constraint"),
										       new__symbol(cause, "funk_name"),      new__symbol(cause, "raw__exp__terminal_print_with_frame__thread_unsafe"),
										       new__symbol(cause, "source_file"),    new__string(cause, __FILE__),
										       new__symbol(cause, "source_line"),    f2integer__new(cause, __LINE__),
										       new__symbol(cause, "argument_frame"), f2__frame__new(cause, f2list4__new(cause,
																				new__symbol(cause, "this"),                 this,
																				new__symbol(cause, "terminal_print_frame"), terminal_print_frame))))));
		} else {
		  raw__terminal_print_frame__failed_max_height_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__true));
		}
	      } else {
		raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, f2bool__new(boolean__false));
		size_that_fails_to_fit_within_height_constraint = raw__terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe(cause, terminal_print_frame, this);
		failed_max_size_constraint                      = f2__terminal_print_frame__failed_max_size_constraint(cause, terminal_print_frame);
		status("raw__exp__terminal_print_with_frame__thread_unsafe: failed_max_size_constraint=%s", (failed_max_size_constraint != nil) ? "t" : "nil");
		if (raw__larva__is_type(cause, size_that_fails_to_fit_within_height_constraint)) {
		  return size_that_fails_to_fit_within_height_constraint;
		}
		if (size_that_fails_to_fit_within_height_constraint != nil) {
		  if (high_unsuccessful_size == 0) {
		    high_unsuccessful_size = max_size__i;
		  } else if (max_size__i < high_unsuccessful_size) {
		    high_unsuccessful_size = max_size__i;
		  }
		} else {
		  if (max_size__i > low_successful_size) {
		    low_successful_size = max_size__i;
		  }
		}
	      }
	    }
	  }
	  if (low_successful_size > 0) {
	    max_size__i = low_successful_size;
	    max_size    = f2integer__new(cause, max_size__i);
	    raw__terminal_print_frame__max_size__set(cause, terminal_print_frame, max_size);
	    f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	    if (raw__larva__is_type(cause, result)) {
	      return result;
	    }
	    if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
	      f2__frame__copy(cause, terminal_print_frame, terminal_print_frame);
	      return nil;
	    }
	  }
	}
	raw__terminal_print_frame__max_size__set(                  cause, terminal_print_frame, original_max_size);
	raw__terminal_print_frame__failed_max_size_constraint__set(cause, terminal_print_frame, original_failed_max_size_constraint);
      } else {
	f2ptr result = f2__force_funk_apply(cause, fiber, funk, f2cons__new(cause, this, f2cons__new(cause, terminal_print_frame, nil)));
	if (raw__larva__is_type(cause, result)) {
	  return result;
	}
	if (raw__terminal_print_frame__failed_test_constraint_and_should_return(cause, terminal_print_frame)) {
	  return nil;
	}
      }
    }
  } else {
    // this object type doesn't have a terminal_print_with_frame funktion.
    //  ... we should print object type here and some short opaque, non-recursive description with size one.
  }
  raw__terminal_print_frame__use_one_line__set(   cause, terminal_print_frame, use_one_line);
  raw__terminal_print_frame__indent_distance__set(cause, terminal_print_frame, indent_distance);
  raw__terminal_print_frame__resize_to_fit__set(  cause, terminal_print_frame, resize_to_fit);
  return nil;
}

f2ptr f2__exp__terminal_print_with_frame__thread_unsafe(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__exp__terminal_print_with_frame__thread_unsafe(cause, this, terminal_print_frame);
}
def_pcfunk2(exp__terminal_print_with_frame__thread_unsafe, this, terminal_print_frame,
	    "Prints a value given a terminal_print_frame.",
	    return f2__exp__terminal_print_with_frame__thread_unsafe(this_cause, this, terminal_print_frame));


f2ptr f2__terminal_print(f2ptr cause, f2ptr exp) {
  if (cause == nil) {
    printf("\nterminal_print warning: tried to print to the terminal of a nil cause.");
    return nil;
  }
  if (! raw__cause__is_type(cause, cause)) {
    f2ptr invalid_cause = cause;
    f2ptr cause         = nil;
    return f2larva__new(cause, 492, f2__bug__new(cause, f2integer__new(cause, 492), f2__frame__new(cause, f2list12__new(cause,
															new__symbol(cause, "bug_type"),           new__symbol(cause, "invalid_cause"),
															new__symbol(cause, "funkname"),           new__symbol(cause, "terminal_print"),
															new__symbol(cause, "source_filename"),    new__string(cause, __FILE__),
															new__symbol(cause, "source_line_number"), f2integer__new(cause, __LINE__),
															new__symbol(cause, "bug_description"),    new__string(cause, "This bug should never occur.  "
																					      "This is a very dangerous bug for large complicated systems because there is no way to tell why this process is executing."),
															new__symbol(cause, "invalid_cause"),      invalid_cause))));
  }
  f2ptr standard_terminal_print_frame = raw__cause__lookup(cause, cause, new__symbol(cause, "standard-terminal"));
  if (! raw__terminal_print_frame__is_type(cause, standard_terminal_print_frame)) {
    return f2larva__new(cause, 1252642, f2__bug__new(cause, f2integer__new(cause, 1), f2__frame__new(cause, f2list10__new(cause,
															  new__symbol(cause, "bug_type"),           new__symbol(cause, "wrong_type"),
															  new__symbol(cause, "funkname"),           new__symbol(cause, "terminal_print"),
															  new__symbol(cause, "source_filename"),    new__string(cause, __FILE__),
															  new__symbol(cause, "source_line_number"), f2integer__new(cause, __LINE__),
															  new__symbol(cause, "standard-terminal"),  standard_terminal_print_frame))));
  }
  // how to make this thread safe?
  // we need to cmutex somehow.
  {
    funk2_character_t temp_str[1];
    temp_str[0] = (funk2_character_t)'\n';
    raw__terminal_print_frame__write_string__thread_unsafe(cause, standard_terminal_print_frame, 1, temp_str);
  }
  return f2__exp__terminal_print_with_frame__thread_unsafe(cause, exp, standard_terminal_print_frame);
}


f2ptr f2__exp__terminal_stream_print__thread_unsafe(f2ptr cause, f2ptr this, f2ptr stream) {
  f2ptr indent_distance      = f2integer__new(cause, 0);
  s64   max_x__i             = raw__termios__width();
  f2ptr max_x                = f2integer__new(cause, max_x__i);
  s64   max_height__i        = raw__termios__height() - 3;
  if (max_height__i <= 0) {
    max_height__i = 1;
  }
  f2ptr max_height           = f2integer__new(cause, max_height__i);
  f2ptr max_size             = f2integer__new(cause, ((max_x__i * max_height__i) >> 2));
  f2ptr use_ansi_codes       = f2bool__new(boolean__true);
  f2ptr use_html_codes       = f2bool__new(boolean__false);
  f2ptr resize_to_fit        = f2bool__new(boolean__true);
  f2ptr max_nanoseconds_for_resize = f2integer__new(cause, 10ull * nanoseconds_per_second);
  f2ptr terminal_print_frame = f2__terminal_print_frame__new(cause, stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes, resize_to_fit, max_nanoseconds_for_resize);
  if (raw__larva__is_type(cause, terminal_print_frame)) {
    return terminal_print_frame;
  }
  return f2__exp__terminal_print_with_frame__thread_unsafe(cause, this, terminal_print_frame);
}
def_pcfunk2(exp__terminal_stream_print__thread_unsafe, this, stream,
	    "Prints a value to the given terminal stream, using a new default terminal_print_frame.",
	    return f2__exp__terminal_stream_print__thread_unsafe(this_cause, this, stream));


// **

void f2__terminal_print__reinitialize_globalvars() {
}

void f2__terminal_print__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "terminal_print", "", &f2__terminal_print__reinitialize_globalvars);
  
  f2__terminal_print__reinitialize_globalvars();
  
  
  // terminal_print_frame
  
  init_frame_object__25_slot(terminal_print_frame,
			     cmutex,
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
			     failed_max_height_constraint,
			     failed_max_size_constraint,
			     resize_to_fit,
			     max_nanoseconds_for_resize,
			     print_as_frame_hash);
  
  {char* symbol_str = "new_copy"; __funk2.globalenv.object_type.primobject.primobject_type_terminal_print_frame.new_copy__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(terminal_print_frame__new_copy, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_terminal_print_frame.new_copy__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__9(terminal_print_frame__new,                                                                       stream, indent_distance, max_x, max_height, max_size, use_ansi_codes, use_html_codes, resize_to_fit, max_nanoseconds_for_resize);
  f2__primcfunk__init__2(terminal_print_frame__write_color__thread_unsafe,                                                this, color);
  f2__primcfunk__init__2(terminal_print_frame__write_string__thread_unsafe,                                               this, string);
  f2__primcfunk__init__2(terminal_print_frame__can_print_expression_on_one_line__thread_unsafe,                           this, expression);
  f2__primcfunk__init__2(terminal_print_frame__expression_size_that_fails_to_fit_within_height_constraint__thread_unsafe, this, expression);
  f2__primcfunk__init__2(terminal_print_frame__expression_x_offset__thread_unsafe,                                        this, expression);
  f2__primcfunk__init__3(terminal_print_frame__prepare_for_printing__thread_unsafe,                                       this, max_x, additional_height);
  
  
  f2__primcfunk__init__2(exp__terminal_print_with_frame__thread_unsafe, this, terminal_print_frame);
  f2__primcfunk__init__2(exp__terminal_stream_print__thread_unsafe,     this, stream);
  
}


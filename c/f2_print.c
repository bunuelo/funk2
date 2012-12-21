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

#define causal_debug__begin_char __funk2.reader.char__left_paren
#define causal_debug__end_char   __funk2.reader.char__right_paren

#define chunk__begin_char __funk2.reader.char__left_paren
#define chunk__end_char   __funk2.reader.char__right_paren

#define frame__begin_char __funk2.reader.char__left_paren
#define frame__end_char   __funk2.reader.char__right_paren

f2ptr f2__write_pretty(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp, int recursion_depth, int indent_space_num, int available_width, int return_size[2], boolean_t try_wide, boolean_t wide_success[1], boolean_t show_slot_causes, boolean_t use_ansi_colors, boolean_t use_html, boolean_t brief_mode);

ansi_color_t print__ansi__default__foreground                  = ansi_color__light_gray;
ansi_color_t print__ansi__nil__foreground                      = ansi_color__white;
ansi_color_t print__ansi__integer__foreground                  = ansi_color__light_blue;
ansi_color_t print__ansi__double__foreground                   = ansi_color__light_blue;
ansi_color_t print__ansi__float__foreground                    = ansi_color__light_blue;
ansi_color_t print__ansi__pointer__foreground                  = ansi_color__light_blue;
ansi_color_t print__ansi__cmutex__foreground                   = ansi_color__white;
ansi_color_t print__ansi__creadwritelock__foreground           = ansi_color__white;
ansi_color_t print__ansi__char__foreground                     = ansi_color__light_blue;
ansi_color_t print__ansi__string__foreground                   = ansi_color__light_red;
ansi_color_t print__ansi__symbol__foreground                   = ansi_color__light_blue;
ansi_color_t print__ansi__symbol__key__foreground              = ansi_color__dark_gray;
ansi_color_t print__ansi__symbol__type__foreground             = ansi_color__dark_cyan;
ansi_color_t print__ansi__chunk__foreground                    = ansi_color__white;
ansi_color_t print__ansi__simple_array__foreground             = ansi_color__white;
ansi_color_t print__ansi__traced_array__foreground             = ansi_color__white;
ansi_color_t print__ansi__larva__foreground                    = ansi_color__dark_red;
ansi_color_t print__ansi__mutable_array_pointer__foreground    = ansi_color__white;
ansi_color_t print__ansi__end_recursion__foreground            = ansi_color__white;
ansi_color_t print__ansi__error__foreground                    = ansi_color__dark_red;
ansi_color_t print__ansi__cons__foreground                     = ansi_color__white;
ansi_color_t print__ansi__doublelink__foreground               = ansi_color__white;
ansi_color_t print__ansi__frame__foreground                    = ansi_color__white;

void f2__write__ansi_color(f2ptr cause, f2ptr stream, ansi_color_t color, boolean_t use_ansi_colors, boolean_t use_html) {
  if (use_ansi_colors && stream) {f2__ansi__stream__reset(cause, stream); raw__ansi__stream__foreground(cause, stream, color);}
  if (use_html        && stream) {html__stream__ansi_foreground(cause, stream, color);}
}

void f2__write__space(f2ptr cause, f2ptr stream, boolean_t use_html) {
  if (stream) {
    if (! use_html) {raw__stream__writef(cause, stream, " ");}
    else            {raw__stream__writef(cause, stream, "&nbsp;");}
  }
}

void f2__write__line_break(f2ptr cause, f2ptr stream, boolean_t use_html) {
  if (stream) {
    if (use_html) {raw__stream__writef(cause, stream, "<br>");}
    raw__stream__writef(cause, stream, "\n");
  }
}

void f2__write__tab(f2ptr cause, f2ptr stream, boolean_t use_html) {
  if (stream) {
    if (use_html) {raw__stream__writef(cause, stream, "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;");}
    raw__stream__writef(cause, stream, "\t");
  }
}

void f2__fwrite__raw_char(f2ptr cause, f2ptr stream, funk2_character_t ch, int return_size[2], boolean_t use_html) {
  int width    = 0;
  int height   = 0;
  switch(ch) {
  case (funk2_character_t)' ':
    f2__write__space(cause, stream, use_html); width ++;
    break;
  case (funk2_character_t)'\n':
    f2__write__line_break(cause, stream, use_html); width = 0; height ++;
    break;
  case (funk2_character_t)'\t':
    f2__write__tab(cause, stream, use_html); width = 0; height ++;
    break;
  default:
    if(stream) {raw__stream__write_character(cause, stream, ch);} width ++;
    break;
  }
  if (return_size) {return_size[0] = width; return_size[1] = height;}
}

void f2__fwrite__raw_string(f2ptr cause, f2ptr stream, f2ptr str, f2ptr use_html) {
  if ((! str) || (! raw__string__is_type(cause, str))) {error(nil, "f2__write__raw_string error: str must be of type ptype_string.");}
  int length = f2string__length(str, cause);
  int i;
  for(i = 0; i < length; i ++) {
    f2__fwrite__raw_char(cause, stream, f2string__elt(str, i, cause), NULL, (use_html != nil) ? 1 : 0);
  }
}

void f2__write_pretty__dptr(f2ptr cause, f2ptr fiber, f2ptr stream,
			    f2ptr exp, f2ptr exp__tracing_on, f2ptr exp__prev, f2ptr exp__cause,
			    int recursion_depth, int indent_space_num, int available_width, int return_size[2], boolean_t try_wide, boolean_t wide_success[1], boolean_t show_slot_causes, boolean_t use_ansi_colors, boolean_t use_html, boolean_t brief_mode) {
  if (try_wide) {
    if(stream) {
      int  test_size[2];
      boolean_t test__wide_success[1] = {1};
      f2__write_pretty__dptr(cause, fiber, nil,
			     exp, exp__tracing_on, exp__prev, exp__cause,
			     recursion_depth, indent_space_num, available_width, test_size, 1, test__wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode);
      if ((! test__wide_success[0]) ||
	  (test_size[0] > available_width)) {
	if (wide_success) {wide_success[0] = 0;}
	try_wide = 0;
      }
    } else {
    }
  } else {
    if (wide_success) {wide_success[0] = 0;}    
  }
  
  int width    = 0;
  int height   = 0;
  int subexp_size[2];
  const int max_slot__length = 12;
  
  f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
  
  if (show_slot_causes) {
    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__begin_char, cause));} indent_space_num ++; available_width --; if (available_width < 0) {if (wide_success) {wide_success[0] = 0;}}
    if (stream) {raw__stream__writef(cause, stream, "dptr ");} indent_space_num += 5; available_width -= 5; if (available_width < 0) {if (wide_success) {wide_success[0] = 0;}}
    f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
    if (stream) {raw__stream__writef(cause, stream, "value");} width += 6;
    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {int i; for(i = 0; i < max_slot__length - 6; i++) {f2__write__space(cause, stream, use_html); width ++;}}
  }
  if (recursion_depth == 0) {
    f2__write__ansi_color(cause, stream, print__ansi__end_recursion__foreground, use_ansi_colors, use_html);
    if (stream) {raw__stream__writef(cause, stream, "*");} width ++;
  } else {
    f2__write_pretty(cause, fiber, stream, exp, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
    if (show_slot_causes) {
      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
      f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
      if (stream) {raw__stream__writef(cause, stream, "tracing_on");} width += 11;
      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {int i; for(i = 0; i < max_slot__length - 11; i++) {f2__write__space(cause, stream, use_html); width ++;}}
      
      f2__write_pretty(cause, fiber, stream, exp__tracing_on, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
      f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
      if (stream) {raw__stream__writef(cause, stream, "prev");} width += 5;
      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {int i; for(i = 0; i < max_slot__length - 5; i++) {f2__write__space(cause, stream, use_html); width ++;}}
      
      f2__write_pretty(cause, fiber, stream, exp__prev,       ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
      f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
      if (stream) {raw__stream__writef(cause, stream, "cause");} width += 6;
      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {int i; for(i = 0; i < max_slot__length - 6; i++) {f2__write__space(cause, stream, use_html); width ++;}}
      f2__write_pretty(cause, fiber, stream, exp__cause,      ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
    }
  }
  if (show_slot_causes) {
    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__end_char, cause));} width ++;
  }
  if (return_size) {
    return_size[0] = width;
    return_size[1] = height;
  }
  if (available_width < 0) {
    if (wide_success) {
      wide_success[0] = 0;
    }
  }
}

void f2__write_pretty__utf8_slot_key_and_value(char* slot_name, int max_slot_name_length, f2ptr cause, f2ptr fiber, f2ptr stream,
					       f2ptr exp, f2ptr exp__tracing_on, f2ptr exp__prev, f2ptr exp__cause,
					       int recursion_depth, int indent_space_num, int available_width, int return_size[2], boolean_t try_wide, boolean_t wide_success[1], boolean_t show_slot_causes, boolean_t use_ansi_colors, boolean_t use_html, boolean_t brief_mode) {
  int width    = 0;
  int height   = 0;
  int subexp_size[2];
  int slot_name__length = strlen(slot_name);
  
  f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
  
  if (stream) {raw__stream__writef(cause, stream, "%s", slot_name);} width += slot_name__length;
  if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {int i; for(i = 0; i < max_slot_name_length - slot_name__length + 1; i++) {f2__write__space(cause, stream, use_html); width ++; /*indent_space_num ++;*/}}
  if (recursion_depth == 0) {
    f2__write__ansi_color(cause, stream, print__ansi__end_recursion__foreground, use_ansi_colors, use_html);
    if (stream) {raw__stream__writef(cause, stream, "*");} width ++;
  } else {
    f2__write_pretty__dptr(cause, fiber, stream, exp, exp__tracing_on, exp__prev, exp__cause, recursion_depth, indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
  }
  if (return_size) {
    return_size[0] = width;
    return_size[1] = height;
  }
  if (available_width < 0) {
    if (wide_success) {
      wide_success[0] = 0;
    }
  }
  
  f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
}

void f2__write_pretty__slot_key_and_value(funk2_character_t* slot_name, int max_slot_name_length, f2ptr cause, f2ptr fiber, f2ptr stream,
					  f2ptr exp, f2ptr exp__tracing_on, f2ptr exp__prev, f2ptr exp__cause,
					  int recursion_depth, int indent_space_num, int available_width, int return_size[2], boolean_t try_wide, boolean_t wide_success[1], boolean_t show_slot_causes, boolean_t use_ansi_colors, boolean_t use_html, boolean_t brief_mode) {
  int width    = 0;
  int height   = 0;
  int subexp_size[2];
  int slot_name__length = 0;
  {
    u64 index;
    for (index = 0; slot_name[index] != 0; index ++);
    slot_name__length = index;
  }
  
  f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
  
  {
    u64 index;
    for (index = 0; index < slot_name__length; index ++) {
      if (stream) {raw__stream__write_character(cause, stream, slot_name[index]);} width ++;
    }
  }
  if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {int i; for(i = 0; i < max_slot_name_length - slot_name__length + 1; i++) {f2__write__space(cause, stream, use_html); width ++; /*indent_space_num ++;*/}}
  if (recursion_depth == 0) {
    f2__write__ansi_color(cause, stream, print__ansi__end_recursion__foreground, use_ansi_colors, use_html);
    if (stream) {raw__stream__writef(cause, stream, "*");} width ++;
  } else {
    f2__write_pretty__dptr(cause, fiber, stream, exp, exp__tracing_on, exp__prev, exp__cause, recursion_depth, indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
  }
  if (return_size) {
    return_size[0] = width;
    return_size[1] = height;
  }
  if (available_width < 0) {
    if (wide_success) {
      wide_success[0] = 0;
    }
  }
  
  f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
}

void found_illegal_type() {
  printf("found illegal type.");
}

f2ptr f2__write_pretty(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp, int recursion_depth, int indent_space_num, int available_width, int return_size[2], boolean_t try_wide, boolean_t wide_success[1], boolean_t show_slot_causes, boolean_t use_ansi_colors, boolean_t use_html, boolean_t brief_mode) {
  if (try_wide) {
    if(stream) {
      int  test_size[2];
      boolean_t test__wide_success[1] = {1};
      f2__write_pretty(cause, fiber, nil, exp, recursion_depth, indent_space_num, available_width, test_size, 1, test__wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode);
      if ((! test__wide_success[0]) ||
	  (test_size[0] > available_width)) {
	if (wide_success) {wide_success[0] = 0;}
	try_wide = 0;
      }
    } else {
    }
  } else {
    if (wide_success) {wide_success[0] = 0;}    
  }
  
  fflush(stdout); // for debugging
  
  int width  = 0;
  int height = 0;  
  
  f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
  
  if (recursion_depth == 0) {
    f2__write__ansi_color(cause, stream, print__ansi__end_recursion__foreground, use_ansi_colors, use_html);
    if (stream) {raw__stream__writef(cause, stream, "*");} width ++;
  } else {
    if (exp == nil) {
      f2__write__ansi_color(cause, stream, print__ansi__nil__foreground, use_ansi_colors, use_html);
      if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__left_paren, cause));} width ++;
      if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__right_paren, cause));} width ++;
      f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
    } else {
      ptype_t ptype = f2ptype__raw(exp, cause);
      
      if (show_slot_causes) {
	char temp_str[128];
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__begin_char, cause));} width ++;
	sprintf(temp_str, "%s", __ptype__str[ptype]); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	indent_space_num += 2; available_width -= 2;
	if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "value ");
	if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} indent_space_num += 7; available_width -= 7;
	if (! try_wide) {if (stream) {raw__stream__writef(cause, stream, "   ");} indent_space_num += 3; available_width -= 3;}
      }
      
      switch(ptype) {
      case ptype_integer: {
	f2__write__ansi_color(cause, stream, print__ansi__integer__foreground, use_ansi_colors, use_html);
	char temp_str[128];
	sprintf(temp_str, s64__fstr, f2integer__i(exp, cause)); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_double:  {
	f2__write__ansi_color(cause, stream, print__ansi__double__foreground, use_ansi_colors, use_html);
	char temp_str[128];
	sprintf(temp_str, "%1.16f", f2double__d(exp, cause));  if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_float:   {
	f2__write__ansi_color(cause, stream, print__ansi__float__foreground, use_ansi_colors, use_html);
	char temp_str[128];
	sprintf(temp_str, "%1.8f",  f2float__f(exp, cause));   if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_pointer: {
	f2__write__ansi_color(cause, stream, print__ansi__pointer__foreground, use_ansi_colors, use_html);
	char temp_str[128]; 
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape, cause));} width ++;
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape_hex, cause));} width ++;
	sprintf(temp_str, ptr__fstr, f2pointer__p(exp, cause)); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_cmutex: {
	int subexp_size[2];
	
	f2__write__ansi_color(cause, stream, print__ansi__cmutex__foreground, use_ansi_colors, use_html);
	char temp_str[128];
	f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__begin_char, cause));} width ++;
	
	f2__write__ansi_color(cause, stream, print__ansi__symbol__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "cmutex"); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	
	if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "is_locked "); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2ptr is_locked = f2bool__new(f2cmutex__is_locked(exp, cause));
	f2__write_pretty(cause, fiber, stream, is_locked, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__end_char, cause));} width ++;
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_creadwritelock: {
	int subexp_size[2];
	
	f2__write__ansi_color(cause, stream, print__ansi__creadwritelock__foreground, use_ansi_colors, use_html);
	char temp_str[128];
	f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__begin_char, cause));} width ++;
	
	f2__write__ansi_color(cause, stream, print__ansi__symbol__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "creadwritelock"); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	
	if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "is_writelocked "); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2ptr is_writelocked = f2bool__new(f2creadwritelock__is_writelocked(exp, cause));
	f2__write_pretty(cause, fiber, stream, is_writelocked, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__end_char, cause));} width ++;
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_char: {
	f2__write__ansi_color(cause, stream, print__ansi__char__foreground, use_ansi_colors, use_html);
	char temp_str[128]; 
	unsigned char ch = f2char__ch(exp, cause);
	if (ch >= 28) {
	  if(stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape, cause));} width ++;
	  if(stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape_char, cause));} width ++;
	  if(stream) {raw__stream__writef(cause, stream, "%c", ch);} width ++;
	} else {
	  if(stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape, cause));} width ++;
	  if(stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape_hex_char, cause));} width ++;
	  sprintf(temp_str, "%X", (uint)ch); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	}
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_string: {
	f2__write__ansi_color(cause, stream, print__ansi__string__foreground, use_ansi_colors, use_html);
	int i;
	int length = f2string__length(exp, cause);
	char ch;
	int subexp_size[2];
	
	f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__string_quote, cause), subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	
	for(i = 0; i < length; i ++) {
	  ch = f2string__elt(exp, i, cause);
	  if (ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	    f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__escape_char, cause),  subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	    f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__string_quote, cause), subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  } else if(ch == '\n') {
	    f2__fwrite__raw_char(cause, stream, '\n', subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  } else if(ch == '\t') {
	    f2__fwrite__raw_char(cause, stream, '\t', subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  } else if(ch < 28) {
	    f2__fwrite__raw_char(cause, stream, '?', subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  } else {
	    f2__fwrite__raw_char(cause, stream, ch, subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  }
	}

	f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__string_quote, cause), subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_symbol: {
	f2__write__ansi_color(cause, stream, print__ansi__symbol__foreground, use_ansi_colors, use_html);
	int  i;
	int                length = f2symbol__length(exp, cause);
	funk2_character_t* temp_str_buf = (funk2_character_t*)alloca((length + 1) * sizeof(funk2_character_t));
	f2symbol__str_copy(exp, cause, temp_str_buf);
	temp_str_buf[length] = 0;
	funk2_character_t ch;
	int  subexp_size[2];
	boolean_t all_cool = 1;
	for (i = 0; i < length; i ++) {
	  ch = temp_str_buf[i];
	  if (ch == (funk2_character_t)' '  ||
	      ch == (funk2_character_t)'\t' ||
	      ch == (funk2_character_t)'\n' ||
	      ch == (funk2_character_t)'\r' ||
	      ch == f2char__ch(__funk2.reader.char__left_paren,   cause) ||
	      ch == f2char__ch(__funk2.reader.char__right_paren,  cause) ||
	      ch == f2char__ch(__funk2.reader.char__symbol_quote, cause) ||
	      ch == f2char__ch(__funk2.reader.char__string_quote, cause)) {
	    all_cool = 0;
	  }
	}
	if (all_cool) {
	  for (i = 0; i < length; i ++) {
	    ch = temp_str_buf[i];
	    if (i == 0 && ch == f2char__ch(__funk2.reader.char__symbol_key, cause)) {
	      f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
	    }
	    if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__symbol_escape, cause), subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];}
	    f2__fwrite__raw_char(cause, stream, ch, subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  }
	} else {
	  if (stream) {raw__stream__write_character(cause, stream, f2char__ch(__funk2.reader.char__symbol_quote, cause));} width ++;
	  for(i = 0; i < length; i ++) {
	    ch = temp_str_buf[i];
	    if (ch == f2char__ch(__funk2.reader.char__symbol_quote, cause)) {
	      f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__symbol_escape, cause), subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	    }
	    f2__fwrite__raw_char(cause, stream, ch, subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	  }
	  f2__fwrite__raw_char(cause, stream, f2char__ch(__funk2.reader.char__symbol_quote, cause), subexp_size, use_html); width += subexp_size[0]; height += subexp_size[1];
	}
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_chunk: {
	f2__write__ansi_color(cause, stream, print__ansi__chunk__foreground, use_ansi_colors, use_html);
	char temp_str[128]; 
	int  subexp_size[2];
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(chunk__begin_char, cause));} indent_space_num ++; available_width --; if (available_width < 0) {if (wide_success) {wide_success[0] = 0;}}
	f2__write__ansi_color(cause, stream, print__ansi__symbol__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "chunk"); int temp_str__length = strlen(temp_str); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} indent_space_num += (temp_str__length + 1); available_width -= (temp_str__length + 1); if (available_width < 0) {if (wide_success) {wide_success[0] = 0;}}
	if (show_slot_causes) {
	  f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
	  if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	  sprintf(temp_str, "cause ");     if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	  f2__write_pretty(cause, fiber, stream, f2ptype__cause(exp, cause), ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	}
	f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
	if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	sprintf(temp_str, "bytes"); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	
	f2__write__ansi_color(cause, stream, print__ansi__pointer__foreground, use_ansi_colors, use_html);
	// this should print a 2d block when too wide, rather than a vertical line (amen).
	int i;
	int length = f2chunk__length(exp, cause);
	for(i = 0; i < length; i ++) {
	  
	  if (width < available_width) {
	    f2__write__space(cause, stream, use_html); width ++;
	  } else {
	    if (wide_success) {
	      wide_success[0] = 0;
	    }
	    f2__write__line_break(cause, stream, use_html); width = 0; height ++;
	    int i;
	    for (i = 0; i < indent_space_num + width; i++) {
	      f2__write__space(cause, stream, use_html);
	    }
	  }
	  
	  sprintf(temp_str, "#x%02x", f2chunk__bit8__elt(exp, i, cause)); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	}
	f2__write__ansi_color(cause, stream, print__ansi__chunk__foreground, use_ansi_colors, use_html);
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(chunk__end_char, cause));} width ++;
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_simple_array:
      case ptype_traced_array:
	if (ptype == ptype_simple_array) {
	  f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	} else {
	  f2__write__ansi_color(cause, stream, print__ansi__traced_array__foreground, use_ansi_colors, use_html);
	}
	int array_is_not_known_primobject = 0; // assume for the time being that we know this is a primobject (we correct this assumption after primobject recognition conditionals)
	if (! raw__primobject__is_type(cause, exp)) {
	  array_is_not_known_primobject = 1; // array is not even primobject!
	} else {
	  if (show_slot_causes ||
	      ((! f2primobject__is__largeinteger(exp, cause)) &&
	       (! f2primobject__is__cons(        exp, cause)) &&
	       (! f2primobject__is__doublelink(  exp, cause)) &&
	       (! f2primobject__is__list(        exp, cause)) &&
	       (! f2primobject__is__frame(       exp, cause)))) {
	    int subexp_size[2];
	    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__begin_char, cause));} width ++;
	    f2__write_pretty(cause, fiber, stream, f2primobject__object_type(exp, cause), recursion_depth, indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	    indent_space_num += 2; available_width -= 2;
	  }
	  if (f2primobject__is__largeinteger(exp, cause)) {
	    f2__write__ansi_color(cause, stream, print__ansi__integer__foreground, use_ansi_colors, use_html);
	    if (stream) {f2__largeinteger__print(cause, exp);}
	    f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
	  } else if (f2primobject__is__cons(exp, cause)) {
	    if (show_slot_causes) {
	      int subexp_size[2];
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("car", 3, cause, fiber, stream, f2cons__car(exp, cause),            f2cons__car__tracing_on(exp, cause), f2cons__car__trace(exp, cause), f2cons__car__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("cdr", 3, cause, fiber, stream, f2cons__cdr(exp, cause),          f2cons__cdr__tracing_on(exp, cause), f2cons__cdr__trace(exp, cause), f2cons__cdr__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    } else {
	      f2ptr car = f2cons__car(exp, cause);
	      if (car == __funk2.globalenv.quote__symbol) {
		if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__backquote, cause));} width ++;
		int subexp_size[2];
		f2__write_pretty(cause, fiber, stream, f2cons__car(f2cons__cdr(exp, cause), cause), ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	      } else if (car == __funk2.globalenv.funkvar__symbol) {
		if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__funktion, cause));} width ++;
		int subexp_size[2];
		f2__write_pretty(cause, fiber, stream, f2cons__car(f2cons__cdr(exp, cause), cause), ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	      } else {
		int subexp_size[2];
		f2ptr cdr;
		f2ptr iter = exp;
		int write_car_with_space = 0;
		if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__left_paren, cause));} indent_space_num ++; available_width --;
		while (iter) {
		  cdr       = assert_value(f2__cons__cdr(cause, iter));
		  f2ptr car = assert_value(f2__cons__car(cause, iter));
		  if (write_car_with_space) {
		    //int car__try_wide = try_wide;
		    
		    boolean_t subexp__wide_success[1] = {1};
		    f2__write_pretty(cause, fiber, nil, car, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, subexp__wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode);
		    
		    if (width < available_width && subexp__wide_success[0]) {
		      f2__write__space(cause, stream, use_html); width ++;
		    } else {
		      if (wide_success) {
			wide_success[0] = 0;
		      }
		      f2__write__line_break(cause, stream, use_html); width = 0; height ++;
		      int i;
		      for (i = 0; i < indent_space_num + width; i++) {
			f2__write__space(cause, stream, use_html);
		      }
		    }
		    
		    //if (car__try_wide) {f2__write__space(fptr, use_html); width ++;} else {f2__write__line_break(fptr, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(fptr, use_html);}}
		  }
		  f2__write_pretty(cause, fiber, stream, car, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
		  write_car_with_space = 1;
		  if (!cdr) {
		    if (ptype == ptype_simple_array) {
		      f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		    } else {
		      f2__write__ansi_color(cause, stream, print__ansi__traced_array__foreground, use_ansi_colors, use_html);
		    }
		    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__right_paren, cause));} width ++;
		    iter = nil;
		  } else if (! raw__cons__is_type(cause, cdr)) {
		    if (ptype == ptype_simple_array) {
		      f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		    } else {
		      f2__write__ansi_color(cause, stream, print__ansi__traced_array__foreground, use_ansi_colors, use_html);
		    }
		    if (stream) {raw__stream__writef(cause, stream, " .");} width += 2;
		    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
		    f2__write_pretty(cause, fiber, stream, cdr, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
		    if (ptype == ptype_simple_array) {
		      f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		    } else {
		      f2__write__ansi_color(cause, stream, print__ansi__traced_array__foreground, use_ansi_colors, use_html);
		    }
		    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__right_paren, cause));} width ++;
		    iter = nil;
		  } else {
		    iter = cdr;
		  }
		}
	      }
	    }
	  } else if (f2primobject__is__doublelink(exp, cause)) {
	    if (show_slot_causes) {
	      int subexp_size[2];
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("value", 5, cause, fiber, stream, f2doublelink__value(exp, cause),            f2doublelink__value__tracing_on(exp, cause), f2doublelink__value__trace(exp, cause), f2doublelink__value__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("prev",  5, cause, fiber, stream, f2doublelink__prev(exp, cause),          f2doublelink__prev__tracing_on(exp, cause), f2doublelink__prev__trace(exp, cause), f2doublelink__prev__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("next",  5, cause, fiber, stream, f2doublelink__next(exp, cause),         f2doublelink__next__tracing_on(exp, cause), f2doublelink__next__trace(exp, cause), f2doublelink__next__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    } else {
	      int   subexp_size[2];
	      f2ptr next;
	      f2ptr iter = exp;
	      int   write_value_with_space = 0;
	      if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__doublelink_left_paren, cause));} indent_space_num ++; available_width --;
	      f2ptr iter__prev = f2doublelink__prev(iter, cause);
	      boolean_t prev__exists = 0;
	      while (iter__prev) {
		prev__exists = 1;
		iter = iter__prev;
		iter__prev = f2doublelink__prev(iter, cause);
	      }
	      while (iter) {
		next = f2doublelink__next(iter, cause);
		f2ptr value = f2doublelink__value(iter, cause);
		if (prev__exists && iter == exp) {
		  int value__try_wide = try_wide;
		  
		  //if(fptr) {
		  //  int  test_size[2];
		  //  boolean_t test__wide_success[1] = {1};
		  //  f2__write_pretty(cause, nil, value, recursion_depth, indent_space_num, available_width, test_size, 1, test__wide_success, show_slot_causes);
		  //  if ((! test__wide_success[0]) ||
		  //      (test_size[0] > available_width)) {
		  //    if (wide_success) {wide_success[0] = 0;}
		  //    try_wide = 0;
		  //  }
		  //} else {
		  //}
		  
		  if (value__try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
		  f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		  if (stream) {raw__stream__writef(cause, stream, "*-");} width += 2;
		}
		if (write_value_with_space) {if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}}
		f2__write_pretty(cause, fiber, stream, value, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
		write_value_with_space = 1;
		if (!next) {
		  f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		  if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__doublelink_right_paren, cause));} width ++;
		  iter = nil;
		} else if (! raw__doublelink__is_type(cause, next)) {
		  f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		  if (stream) {raw__stream__writef(cause, stream, " .");} width += 2;
		  if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
		  f2__write_pretty(cause, fiber, stream, next, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
		  f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
		  if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__doublelink_right_paren, cause));} width ++;
		  iter = nil;
		} else {
		  iter = next;
		}
	      }
	    }
	  } else if (f2primobject__is__cfunk(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("name",          13, cause, fiber, stream, f2cfunk__name(exp, cause),                f2cfunk__name__tracing_on(exp, cause), f2cfunk__name__trace(exp, cause), f2cfunk__name__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("args",          13, cause, fiber, stream, f2cfunk__args(exp, cause),                f2cfunk__args__tracing_on(exp, cause), f2cfunk__args__trace(exp, cause), f2cfunk__args__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("cfunkptr",      13, cause, fiber, stream, f2cfunk__cfunkptr(exp, cause),            f2cfunk__cfunkptr__tracing_on(exp, cause), f2cfunk__cfunkptr__trace(exp, cause), f2cfunk__cfunkptr__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("env",           13, cause, fiber, stream, f2cfunk__env(exp, cause),                 f2cfunk__env__tracing_on(exp, cause), f2cfunk__env__trace(exp, cause), f2cfunk__env__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("is_funktional", 13, cause, fiber, stream, f2cfunk__is_funktional(exp, cause), f2cfunk__is_funktional__tracing_on(exp, cause), f2cfunk__is_funktional__trace(exp, cause), f2cfunk__is_funktional__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("documentation", 13, cause, fiber, stream, f2cfunk__documentation(exp, cause), f2cfunk__documentation__tracing_on(exp, cause), f2cfunk__documentation__trace(exp, cause), f2cfunk__documentation__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__metrocfunk(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("name",          13, cause, fiber, stream, f2metrocfunk__name(exp, cause),           f2metrocfunk__name__tracing_on(exp, cause), f2metrocfunk__name__trace(exp, cause), f2metrocfunk__name__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("args",          13, cause, fiber, stream, f2metrocfunk__args(exp, cause),           f2metrocfunk__args__tracing_on(exp, cause), f2metrocfunk__args__trace(exp, cause), f2metrocfunk__args__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("cfunkptr",      13, cause, fiber, stream, f2metrocfunk__cfunkptr(exp, cause),       f2metrocfunk__cfunkptr__tracing_on(exp, cause), f2metrocfunk__cfunkptr__trace(exp, cause), f2metrocfunk__cfunkptr__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("env",           13, cause, fiber, stream, f2metrocfunk__env(exp, cause),            f2metrocfunk__env__tracing_on(exp, cause), f2metrocfunk__env__trace(exp, cause), f2metrocfunk__env__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("is_funktional", 13, cause, fiber, stream, f2metrocfunk__is_funktional(exp, cause), f2metrocfunk__is_funktional__tracing_on(exp, cause), f2metrocfunk__is_funktional__trace(exp, cause), f2metrocfunk__is_funktional__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("documentation", 13, cause, fiber, stream, f2metrocfunk__documentation(exp, cause), f2metrocfunk__documentation__tracing_on(exp, cause), f2metrocfunk__documentation__trace(exp, cause), f2metrocfunk__documentation__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__funk(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("name",                19, cause, fiber, stream, f2funk__name(exp, cause),       f2funk__name__tracing_on(exp, cause), f2funk__name__trace(exp, cause), f2funk__name__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("body_bytecodes",      19, cause, fiber, stream, f2funk__body_bytecodes(exp, cause),       f2funk__body_bytecodes__tracing_on(exp, cause), f2funk__body_bytecodes__trace(exp, cause), f2funk__body_bytecodes__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("args",                19, cause, fiber, stream, f2funk__args(exp, cause),                 f2funk__args__tracing_on(exp, cause), f2funk__args__trace(exp, cause), f2funk__args__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("demetropolized_body", 19, cause, fiber, stream, f2funk__demetropolized_body(exp, cause), f2funk__demetropolized_body__tracing_on(exp, cause), f2funk__demetropolized_body__trace(exp, cause), f2funk__demetropolized_body__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("body",                19, cause, fiber, stream, f2funk__body(exp, cause), f2funk__body__tracing_on(exp, cause), f2funk__body__trace(exp, cause), f2funk__body__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("env",                 19, cause, fiber, stream, f2funk__env(exp, cause),                  f2funk__env__tracing_on(exp, cause), f2funk__env__trace(exp, cause), f2funk__env__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("machine_code",        19, cause, fiber, stream, f2funk__machine_code(exp, cause),       f2funk__machine_code__tracing_on(exp, cause), f2funk__machine_code__trace(exp, cause), f2funk__machine_code__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("is_funktional",       19, cause, fiber, stream, f2funk__is_funktional(exp, cause),      f2funk__is_funktional__tracing_on(exp, cause), f2funk__is_funktional__trace(exp, cause), f2funk__is_funktional__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("documentation",       19, cause, fiber, stream, f2funk__documentation(exp, cause),      f2funk__documentation__tracing_on(exp, cause), f2funk__documentation__trace(exp, cause), f2funk__documentation__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__metro(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("name",                19, cause, fiber, stream, raw__metro__name(cause, exp),      nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("body_bytecodes",      19, cause, fiber, stream, raw__metro__body_bytecodes(cause, exp),      nil, nil, nil,
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("args",                19, cause, fiber, stream, raw__metro__args(cause, exp),                nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("demetropolized_body", 19, cause, fiber, stream, raw__metro__demetropolized_body(cause, exp), nil, nil, nil,
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("env",                 19, cause, fiber, stream, raw__metro__env(cause, exp),                 nil, nil, nil,
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("machine_code",        19, cause, fiber, stream, raw__metro__machine_code(cause, exp),        nil, nil, nil,
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("is_funktional",       19, cause, fiber, stream, raw__metro__is_funktional(cause, exp),       nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("documentation",       19, cause, fiber, stream, raw__metro__documentation(cause, exp),       nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__exception(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("tag",   5, cause, fiber, stream, f2exception__tag(exp, cause),             f2exception__tag__tracing_on(exp, cause), f2exception__tag__trace(exp, cause), f2exception__tag__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("value", 5, cause, fiber, stream, f2exception__value(exp, cause),           f2exception__value__tracing_on(exp, cause), f2exception__value__trace(exp, cause), f2exception__value__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__bytecode(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("command",    10, cause, fiber, stream, f2bytecode__command(exp, cause), f2bytecode__command__tracing_on(exp, cause), f2bytecode__command__trace(exp, cause), f2bytecode__command__tracing_on(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("arg0",       10, cause, fiber, stream, f2bytecode__arg0(exp, cause),    f2bytecode__arg0__tracing_on(exp, cause), f2bytecode__arg0__trace(exp, cause), f2bytecode__arg0__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("arg1",       10, cause, fiber, stream, f2bytecode__arg1(exp, cause),    f2bytecode__arg1__tracing_on(exp, cause), f2bytecode__arg1__trace(exp, cause), f2bytecode__arg1__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("arg2",       10, cause, fiber, stream, f2bytecode__arg2(exp, cause),    f2bytecode__arg2__tracing_on(exp, cause), f2bytecode__arg2__trace(exp, cause), f2bytecode__arg2__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__fiber(exp, cause)) {
	    int  subexp_size[2];
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("program_counter",          26, cause, fiber, stream, f2fiber__program_counter(exp, cause),    f2fiber__program_counter__tracing_on(exp, cause), f2fiber__program_counter__trace(exp, cause), f2fiber__program_counter__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("iter",                     26, cause, fiber, stream, f2fiber__iter(exp, cause),               f2fiber__iter__tracing_on(exp, cause), f2fiber__iter__trace(exp, cause), f2fiber__iter__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("env",                      26, cause, fiber, stream, f2fiber__env(exp, cause),                f2fiber__env__tracing_on(exp, cause), f2fiber__env__trace(exp, cause), f2fiber__env__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("args",                     26, cause, fiber, stream, f2fiber__args(exp, cause),               f2fiber__args__tracing_on(exp, cause), f2fiber__args__trace(exp, cause), f2fiber__args__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("return_reg",               26, cause, fiber, stream, f2fiber__return_reg(exp, cause),             f2fiber__return_reg__tracing_on(exp, cause), f2fiber__return_reg__trace(exp, cause), f2fiber__return_reg__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("value",                    26, cause, fiber, stream, f2fiber__value(exp, cause),              f2fiber__value__tracing_on(exp, cause), f2fiber__value__trace(exp, cause), f2fiber__value__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("trace",                    26, cause, fiber, stream, f2fiber__trace(exp, cause),              f2fiber__trace__tracing_on(exp, cause), f2fiber__trace__trace(exp, cause), f2fiber__trace__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("cause_reg",                  26, cause, fiber, stream, f2fiber__cause_reg(exp, cause),          f2fiber__cause_reg__tracing_on(exp, cause), f2fiber__cause_reg__trace(exp, cause), f2fiber__cause_reg__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("is_complete",                26, cause, fiber, stream, f2__fiber__is_complete(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("parent_fiber",             26, cause, fiber, stream, f2fiber__parent_fiber(exp, cause),      f2fiber__parent_fiber__tracing_on(exp, cause), f2fiber__parent_fiber__trace(exp, cause), f2fiber__parent_fiber__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("parent_env",               26, cause, fiber, stream, f2fiber__parent_env(exp, cause),         f2fiber__parent_env__tracing_on(exp, cause), f2fiber__parent_env__trace(exp, cause), f2fiber__parent_env__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("execute_cmutex",              26, cause, fiber, stream, f2fiber__execute_cmutex(exp, cause),      f2fiber__execute_cmutex__tracing_on(exp, cause), f2fiber__execute_cmutex__trace(exp, cause), f2fiber__execute_cmutex__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("paused",                     26, cause, fiber, stream, f2fiber__paused(exp, cause),      f2fiber__paused__tracing_on(exp, cause), f2fiber__paused__trace(exp, cause), f2fiber__paused__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("sleep_until_time",           26, cause, fiber, stream, f2fiber__sleep_until_time(exp, cause), f2fiber__sleep_until_time__tracing_on(exp, cause), f2fiber__sleep_until_time__trace(exp, cause), f2fiber__sleep_until_time__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("execution_nanoseconds",      26, cause, fiber, stream, f2__fiber__execution_nanoseconds(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("bytecode_count",             26, cause, fiber, stream, f2fiber__bytecode_count(exp, cause), f2fiber__bytecode_count__tracing_on(exp, cause), f2fiber__bytecode_count__trace(exp, cause), f2fiber__bytecode_count__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("processor_assignment_index", 26, cause, fiber, stream, f2fiber__processor_assignment_index(exp, cause), f2fiber__processor_assignment_index__tracing_on(exp, cause), f2fiber__processor_assignment_index__trace(exp, cause), f2fiber__processor_assignment_index__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("stack_trace",                26, cause, fiber, stream, f2__fiber__stack_trace(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__processor(exp, cause)) {
	    int subexp_size[2];
	    //if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    //{f2__write_pretty__utf8_slot_key_and_value("scheduler",              22, cause, stream, f2processor__scheduler(exp, cause),        f2processor__scheduler__tracing_on(exp, cause), f2processor__scheduler__trace(exp, cause), f2processor__scheduler__imagination_frame(exp, cause),
	    //					  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("processor_thread",       22, cause, fiber, stream, f2processor__processor_thread(exp, cause), f2processor__processor_thread__tracing_on(exp, cause), f2processor__processor_thread__trace(exp, cause), f2processor__processor_thread__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("active_fibers",          22, cause, fiber, stream, f2processor__active_fibers(exp, cause),         f2processor__active_fibers__tracing_on(exp, cause), f2processor__active_fibers__trace(exp, cause), f2processor__active_fibers__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("pool_index",             22, cause, fiber, stream, f2processor__pool_index(exp, cause),      f2processor__pool_index__tracing_on(exp, cause), f2processor__pool_index__trace(exp, cause), f2processor__pool_index__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("desc",                   22, cause, fiber, stream, f2processor__desc(exp, cause),            f2processor__desc__tracing_on(exp, cause), f2processor__desc__trace(exp, cause), f2processor__desc__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("bytecode_count",         22, cause, fiber, stream, f2processor__bytecode_count(exp, cause),  f2processor__bytecode_count__tracing_on(exp, cause), f2processor__bytecode_count__trace(exp, cause), f2processor__bytecode_count__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__scheduler(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("processors",              23, cause, fiber, stream, f2scheduler__processors(exp, cause),      f2scheduler__processors__tracing_on(exp, cause), f2scheduler__processors__trace(exp, cause), f2scheduler__processors__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__cause(exp, cause)) {
	    // cause
	    int subexp_size[2];
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("fibers_cmutex",           22, cause, fiber, stream, f2cause__fibers_cmutex(exp, cause), f2cause__fibers_cmutex__tracing_on(exp, cause), f2cause__fibers_cmutex__trace(exp, cause), f2cause__fibers_cmutex__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("fibers",               22, cause, fiber, stream, f2cause__fibers(exp, cause), f2cause__fibers__tracing_on(exp, cause), f2cause__fibers__trace(exp, cause), f2cause__fibers__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("frame",                  22, cause, fiber, stream, f2__exp__printable_value(cause, f2cause__frame(exp, cause)), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("allocate_traced_arrays", 22, cause, fiber, stream, f2cause__allocate_traced_arrays(exp, cause), f2cause__allocate_traced_arrays__tracing_on(exp, cause), f2cause__allocate_traced_arrays__trace(exp, cause), f2cause__allocate_traced_arrays__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (! brief_mode) {
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("bytecode_tracing_on",    22, cause, fiber, stream, f2cause__bytecode_tracing_on(exp, cause), f2cause__bytecode_tracing_on__tracing_on(exp, cause), f2cause__bytecode_tracing_on__trace(exp, cause), f2cause__bytecode_tracing_on__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	      if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	      {f2__write_pretty__utf8_slot_key_and_value("memory_tracing_on",      22, cause, fiber, stream, f2cause__memory_tracing_on(exp, cause), f2cause__memory_tracing_on__tracing_on(exp, cause), f2cause__memory_tracing_on__trace(exp, cause), f2cause__memory_tracing_on__imagination_frame(exp, cause),
						    ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    }
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("imagination_stack",      22, cause, fiber, stream, f2cause__imagination_stack(exp, cause),    f2cause__imagination_stack__tracing_on(exp, cause), f2cause__imagination_stack__trace(exp, cause), f2cause__imagination_stack__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    //bytecode_branch_funks,
	    //bytecode_funk_funks,
	    //bytecode_tracer_funks,
	    //bytecode_endfunk_funks,
	  } else if (f2primobject__is_tensor(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("dimensions", 10, cause, fiber, stream, f2tensor__dimensions(exp, cause), f2tensor__dimensions__tracing_on(exp, cause), f2tensor__dimensions__trace(exp, cause), f2tensor__dimensions__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("data",       10, cause, fiber, stream, f2tensor__data(exp, cause), f2tensor__data__tracing_on(exp, cause), f2tensor__data__trace(exp, cause), f2tensor__data__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    /*
	  } else if (f2primobject__is__bug(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("type", 4, cause, fiber, stream, f2bug__type(exp, cause), f2bug__type__tracing_on(exp, cause), f2bug__type__trace(exp, cause), f2bug__type__imagination_frame(exp, cause),
	       ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is_ptypehash(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("bin_num_power", 13, cause, fiber, stream, f2ptypehash__bin_num_power(exp, cause),   f2ptypehash__bin_num_power__tracing_on(exp, cause), f2ptypehash__bin_num_power__trace(exp, cause), f2ptypehash__bin_num_power__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("bin_array",     13, cause, fiber, stream, f2ptypehash__bin_array(exp, cause),       f2ptypehash__bin_array__tracing_on(exp, cause), f2ptypehash__bin_array__trace(exp, cause), f2ptypehash__bin_array__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    */
	  } else if (f2primobject__is__redblacktree(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("leaves",          15, cause, fiber, stream, f2__redblacktree__leaves(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("value_funk", 15, cause, fiber, stream, f2redblacktree__value_funk(exp, cause), f2redblacktree__value_funk__tracing_on(exp, cause), f2redblacktree__value_funk__trace(exp, cause), f2redblacktree__value_funk__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("value_comparison_funk", 15, cause, fiber, stream, f2redblacktree__value_comparison_funk(exp, cause), f2redblacktree__value_comparison_funk__tracing_on(exp, cause), f2redblacktree__value_comparison_funk__trace(exp, cause), f2redblacktree__value_comparison_funk__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
#define debug_graph 0
	  } else if (f2primobject__is__traced_cmutex(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("cmutex",                   23, cause, fiber, stream, f2traced_cmutex__cmutex(exp, cause), f2traced_cmutex__cmutex__tracing_on(exp, cause), f2traced_cmutex__cmutex__trace(exp, cause), f2traced_cmutex__cmutex__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("fiber_with_lock",         23, cause, fiber, stream, f2traced_cmutex__fiber_with_lock(exp, cause), f2traced_cmutex__fiber_with_lock__tracing_on(exp, cause), f2traced_cmutex__fiber_with_lock__trace(exp, cause), f2traced_cmutex__fiber_with_lock__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("lock_stack_trace",        23, cause, fiber, stream, f2__traced_cmutex__lock_stack_trace(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("fibers_waiting_for_lock", 23, cause, fiber, stream, f2traced_cmutex__fibers_waiting_for_lock(exp, cause), f2traced_cmutex__fibers_waiting_for_lock__tracing_on(exp, cause), f2traced_cmutex__fibers_waiting_for_lock__trace(exp, cause), f2traced_cmutex__fibers_waiting_for_lock__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__fiber_stack_trace(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("as-printable", 13, cause, fiber, stream, f2__fiber_stack_trace__as__printable(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__fiber_stack_trace_block(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("as-printable", 13, cause, fiber, stream, f2__fiber_stack_trace_block__as__printable(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__list(exp, cause)) {
	    f2ptr cons_cells = f2list__cons_cells(exp, cause);
	    {
	      int subexp_size[2];
	      f2__write_pretty(cause, fiber, stream, cons_cells,
			       ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	    }
	  } else if (f2primobject__is__frame(exp, cause)) {
	    int   max_type_name_length = 0;
	    int   max_slot_name_length = 0;
	    
	    f2ptr type_ptypehash = f2frame__type_ptypehash(exp, cause);
	    
	    boolean_t need_to_print_type_besides_basic_variable = boolean__false; // if this is false, we can omit printing "variable" before each frame variable key.
	    
	    f2ptr frame_type_name = f2primobject__object_type(exp, cause); // defaults to "frame", but is set to :type slot name if one exists.
	    
	    ptypehash__iteration(cause, type_ptypehash, type_ptypehash__key, type_ptypehash__value,
				 
				 int type_key__length;
				 {
				   int subexp_size[2];
				   f2__write_pretty(cause, fiber, nil, type_ptypehash__key, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode);
				   int exp_width  = subexp_size[0];
				   type_key__length = exp_width;
				 }
				 
				 ptypehash__iteration(cause, type_ptypehash__value, slot_name, slot_value,
						      
						      if (raw__eq(cause, type_ptypehash__key, __funk2.primobject__frame.variable__symbol) &&
							  raw__eq(cause, slot_name, __funk2.globalenv.type__symbol) &&
							  raw__symbol__is_type(cause, slot_value)) {
							frame_type_name = slot_value;
						      } else {
							if (! raw__eq(cause, type_ptypehash__key, __funk2.primobject__frame.variable__symbol)) {
							  need_to_print_type_besides_basic_variable = boolean__true;
							}
							if (type_key__length > max_type_name_length) {
							  max_type_name_length = type_key__length;
							}
							
							int slot_name__length;
							{
							  int subexp_size[2];
							  f2__write_pretty(cause, fiber, nil, slot_name, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode);
							  int exp_width  = subexp_size[0];
							  slot_name__length = exp_width;
							}
							
							if (slot_name__length > max_slot_name_length) {
							  max_slot_name_length = slot_name__length;
							}
						      }
						      );
				 );
	    
	    {
	      int subexp_size[2];
	      if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(frame__begin_char, cause));} width ++;
	      f2__write_pretty(cause, fiber, stream, frame_type_name, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	    }
	    
	    if (! try_wide) {
	      // indent frame slots
	      indent_space_num += 2; available_width -= 2;
	    }
	    
	    ptypehash__iteration(cause, type_ptypehash, type_keyvalue_pair__key, typevar_ptypehash,
				 
				 int type_key__length;
				 {
				   int subexp_size[2];
				   f2__write_pretty(cause, fiber, nil, type_keyvalue_pair__key, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode);
				   int exp_width  = subexp_size[0];
				   type_key__length = exp_width;
				 }
				 
				 
				 ptypehash__iteration(cause, typevar_ptypehash, keyvalue_pair__key, slot_value,
						      
						      if (! (raw__eq(cause, type_keyvalue_pair__key, __funk2.primobject__frame.variable__symbol) &&
							     raw__eq(cause, keyvalue_pair__key, __funk2.globalenv.type__symbol) &&
							     raw__symbol__is_type(cause, slot_value))) {
							int key__length;
							{
							  int subexp_size[2];
							  f2__write_pretty(cause, fiber, nil, keyvalue_pair__key, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode);
							  int exp_width  = subexp_size[0];
							  key__length = exp_width;
							}
							
							{
							  int subexp_size[2];
							  if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
							  if (need_to_print_type_besides_basic_variable) {
							    if (raw__symbol__is_type(cause, type_keyvalue_pair__key)) {
							      f2ptr symbol = type_keyvalue_pair__key;
							      u64                symbol__length = raw__symbol__length(cause, symbol);
							      funk2_character_t* symbol__str    = (funk2_character_t*)alloca((symbol__length + 1) * sizeof(funk2_character_t));
							      raw__symbol__str_copy(cause, symbol, symbol__str);
							      symbol__str[symbol__length] = 0;
							      f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
							      {
								s64 index;
								for (index = 0; index < symbol__length; index ++) {
								  if (stream) {raw__stream__write_character(cause, stream, symbol__str[index]);} width ++;
								}
							      }
							      f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
							    } else {
							      f2__write_pretty(cause, fiber, stream, type_keyvalue_pair__key, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
							    }
							    if (! try_wide) {
							      int i;
							      for (i = type_key__length; i < max_type_name_length; i ++) {
								f2__write__space(cause, stream, use_html); width ++;
							      }
							    }
							    f2__write__space(cause, stream, use_html); width ++;
							  }
							  if (raw__symbol__is_type(cause, keyvalue_pair__key)) {
							    f2ptr symbol = keyvalue_pair__key;
							    u64                symbol__length = raw__symbol__length(cause, symbol);
							    funk2_character_t* symbol__str    = (funk2_character_t*)alloca((symbol__length + 1) * sizeof(funk2_character_t));
							    raw__symbol__str_copy(cause, symbol, symbol__str);
							    symbol__str[symbol__length] = 0;
							    f2__write__ansi_color(cause, stream, print__ansi__symbol__key__foreground, use_ansi_colors, use_html);
							    {
							      u64 index;
							      for (index = 0; index < symbol__length; index ++) {
								if (stream) {raw__stream__write_character(cause, stream, symbol__str[index]);} width ++;
							      }
							    }
							    f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
							  } else {
							    f2__write_pretty(cause, fiber, stream, keyvalue_pair__key, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
							  }
							  if (! try_wide) {
							    int i;
							    for (i = key__length; i < max_slot_name_length; i ++) {
							      f2__write__space(cause, stream, use_html); width ++;
							    }
							  }
							  f2__write__space(cause, stream, use_html); width ++;
							  f2__write_pretty(cause, fiber, stream, slot_value, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, 0, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
							}
						      }
						      );
				 
				 
				 //}
				 
				 );
	    
	    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(frame__end_char, cause));} width ++;
	    
	  } else if (f2primobject__is_object(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("types", 5, cause, fiber, stream, f2object__types(exp, cause), f2object__types__tracing_on(exp, cause), f2object__types__trace(exp, cause), f2object__types__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	    {f2__write_pretty__utf8_slot_key_and_value("frame", 5, cause, fiber, stream, f2object__frame(exp, cause), f2object__frame__tracing_on(exp, cause), f2object__frame__trace(exp, cause), f2object__frame__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is_object_type(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("types", 5, cause, fiber, stream, f2object_type__types(exp, cause), f2object_type__types__tracing_on(exp, cause), f2object_type__types__trace(exp, cause), f2object_type__types__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	    {f2__write_pretty__utf8_slot_key_and_value("frame", 5, cause, fiber, stream, f2object_type__frame(exp, cause), f2object_type__frame__tracing_on(exp, cause), f2object_type__frame__trace(exp, cause), f2object_type__frame__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__environment(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("frame",      10, cause, fiber, stream, f2environment__frame(exp, cause),         f2environment__frame__tracing_on(exp, cause), f2environment__frame__trace(exp, cause), f2environment__frame__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("parent_env", 10, cause, fiber, stream, f2environment__parent_env(exp, cause),    f2environment__parent_env__tracing_on(exp, cause), f2environment__parent_env__trace(exp, cause), f2environment__parent_env__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	    {f2__write_pretty__utf8_slot_key_and_value("desc",       10, cause, fiber, stream, f2environment__desc(exp, cause),          f2environment__desc__tracing_on(exp, cause), f2environment__desc__trace(exp, cause), f2environment__desc__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    /*
	  } else if (f2primobject__is__event(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("type", 4, cause, fiber, stream, f2event__type(exp, cause), f2event__type__tracing_on(exp, cause), f2event__type__trace(exp, cause), f2event__type__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("data", 4, cause, fiber, stream, f2event__data(exp, cause), f2event__data__tracing_on(exp, cause), f2event__data__trace(exp, cause), f2event__data__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    */
	  } else if (f2primobject__is__bytecode_event(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("bytecode", 8, cause, fiber, stream, f2bytecode_event__bytecode(exp, cause), f2bytecode_event__bytecode__tracing_on(exp, cause), f2bytecode_event__bytecode__trace(exp, cause), f2bytecode_event__bytecode__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("context",  8, cause, fiber, stream, f2bytecode_event__context(exp, cause), f2bytecode_event__context__tracing_on(exp, cause), f2bytecode_event__context__trace(exp, cause), f2bytecode_event__context__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    /*
	  } else if (f2primobject__is_circular_buffer(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("start",     9, cause, fiber, stream, f2circular_buffer__start(exp, cause), f2circular_buffer__start__tracing_on(exp, cause), f2circular_buffer__start__trace(exp, cause), f2circular_buffer__start__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("end",       9, cause, fiber, stream, f2circular_buffer__end(exp, cause), f2circular_buffer__end__tracing_on(exp, cause), f2circular_buffer__end__trace(exp, cause), f2circular_buffer__end__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("bin_array", 9, cause, fiber, stream, f2circular_buffer__bin_array(exp, cause), f2circular_buffer__bin_array__tracing_on(exp, cause), f2circular_buffer__bin_array__trace(exp, cause), f2circular_buffer__bin_array__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    // stream
	  } else if (f2primobject__is__stream(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("type",            15, cause, fiber, stream, f2stream__type(exp, cause), f2stream__type__tracing_on(exp, cause), f2stream__type__trace(exp, cause), f2stream__type__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("ungetc_stack",    15, cause, fiber, stream, f2stream__ungetc_stack(exp, cause), f2stream__ungetc_stack__tracing_on(exp, cause), f2stream__ungetc_stack__trace(exp, cause), f2stream__ungetc_stack__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("rewind_stack",    15, cause, fiber, stream, f2stream__rewind_stack(exp, cause), f2stream__rewind_stack__tracing_on(exp, cause), f2stream__rewind_stack__trace(exp, cause), f2stream__rewind_stack__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("rewindable",      15, cause, fiber, stream, f2stream__rewindable(exp, cause), f2stream__rewindable__tracing_on(exp, cause), f2stream__rewindable__trace(exp, cause), f2stream__rewindable__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("rewind_length",   15, cause, fiber, stream, f2stream__rewind_length(exp, cause), f2stream__rewind_length__tracing_on(exp, cause), f2stream__rewind_length__trace(exp, cause), f2stream__rewind_length__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("file_descriptor", 15, cause, fiber, stream, f2stream__file_descriptor(exp, cause), f2stream__file_descriptor__tracing_on(exp, cause), f2stream__file_descriptor__trace(exp, cause), f2stream__file_descriptor__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("string",          15, cause, fiber, stream, f2stream__string(exp, cause), f2stream__string__tracing_on(exp, cause), f2stream__string__trace(exp, cause), f2stream__string__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("index",           15, cause, fiber, stream, f2stream__index(exp, cause), f2stream__index__tracing_on(exp, cause), f2stream__index__trace(exp, cause), f2stream__index__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    */
	  } else if (f2primobject__is__time(exp, cause)) {
	    int subexp_size[2];
	    //if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    //{f2__write_pretty__utf8_slot_key_and_value("nanoseconds_since_1970",    15, cause, fiber, stream, f2time__nanoseconds_since_1970(exp, cause), f2time__nanoseconds_since_1970__tracing_on(exp, cause), f2time__nanoseconds_since_1970__trace(exp, cause), f2time__nanoseconds_since_1970__imagination_frame(exp, cause),
	    //					  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("years",    15, cause, fiber, stream, f2__time__years(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("months",    15, cause, fiber, stream, f2__time__months(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("days",    15, cause, fiber, stream, f2__time__days(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("hours",    15, cause, fiber, stream, f2__time__hours(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("minutes",    15, cause, fiber, stream, f2__time__minutes(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("seconds",    15, cause, fiber, stream, f2__time__seconds(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("nanoseconds",    15, cause, fiber, stream, f2__time__nanoseconds(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    
	  } else if (f2primobject__is__set(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("elements", 8, cause, fiber, stream, f2__set__elements(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__ptypehash(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("as-frame", 8, cause, fiber, stream, f2__ptypehash__as__frame(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__hash(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("hash_value_funk", 15, cause, fiber, stream, f2hash__hash_value_funk(exp, cause), f2hash__hash_value_funk__tracing_on(exp, cause), f2hash__hash_value_funk__trace(exp, cause), f2hash__hash_value_funk__imagination_frame(exp, cause),
	    					  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("equals_funk",     15, cause, fiber, stream, f2hash__equals_funk(exp, cause), f2hash__equals_funk__tracing_on(exp, cause), f2hash__equals_funk__trace(exp, cause), f2hash__equals_funk__imagination_frame(exp, cause),
	    					  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("as-frame",        15, cause, fiber, stream, f2__hash__as__frame(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__graph(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("node_set", 8, cause, fiber, stream, f2graph__node_set(exp, cause), f2graph__node_set__tracing_on(exp, cause), f2graph__node_set__trace(exp, cause), f2graph__node_set__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("edge_set", 8, cause, fiber, stream, f2graph__edge_set(exp, cause), f2graph__edge_set__tracing_on(exp, cause), f2graph__edge_set__trace(exp, cause), f2graph__edge_set__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__graph_decomposition_lattice(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("node_set", 8, cause, fiber, stream, f2graph_decomposition_lattice__node_set(exp, cause), f2graph_decomposition_lattice__node_set__tracing_on(exp, cause), f2graph_decomposition_lattice__node_set__trace(exp, cause), f2graph_decomposition_lattice__node_set__imagination_frame(exp, cause),
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else if (f2primobject__is__graph_isomorphism(exp, cause)) {
	    int subexp_size[2];
	    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
	    {f2__write_pretty__utf8_slot_key_and_value("as-frame", 8, cause, fiber, stream, f2__graph_isomorphism__as__frame(cause, exp), nil, nil, nil,
						  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
	  } else {
	    f2ptr type_name = f2primobject__object_type(exp, cause);
	    f2ptr primobject_type = f2__lookup_type(cause, type_name);
	    if (primobject_type) {
	      f2ptr keyvalue_pairs       = nil;
	      f2ptr get_keys             = f2__primobject_type__type_funk__keys(cause, primobject_type, __funk2.globalenv.get__symbol);
	      u64   max_slot_name_length = 0;
	      {
		f2ptr slot_iter = get_keys;
		while (slot_iter) {
		  f2ptr slot_name  = assert_value(f2__cons__car(cause, slot_iter));
		  if (! raw__eq(cause, slot_name, __funk2.globalenv.type__symbol)) {
		    if (raw__symbol__is_type(cause, slot_name)) {
		      u64 slot_name__length = f2symbol__length(slot_name, cause);
		      if (slot_name__length > max_slot_name_length) {
			max_slot_name_length = slot_name__length;
		      }
		    }
		    f2ptr slot_funk = f2__primobject_type__lookup_slot_type_funk(cause, primobject_type, __funk2.globalenv.get__symbol, slot_name);
		    f2ptr args = nil;
		    if (f2__cfunk__is_type(cause, slot_funk)) {
		      args = f2cfunk__args(slot_funk, cause);
		    } else if (f2__funk__is_type(cause, slot_funk)) {
		      args = f2funk__args(slot_funk, cause);
		    }
		    f2ptr slot_value = nil;
		    if (raw__simple_length(cause, args) == 1) {
		      if (fiber) {
			f2ptr print_get_cause = nil;
			slot_value = f2__force_funk_apply(print_get_cause, fiber, slot_funk, f2list1__new(cause, exp));
		      } else {
			slot_value = new__symbol(cause, "<>");
		      }
		    }
		    keyvalue_pairs = raw__cons__new(cause, raw__cons__new(cause, slot_name, slot_value), keyvalue_pairs);
		  }
		  slot_iter = assert_value(f2__cons__cdr(cause, slot_iter));
		}
	      }
	      {
		int subexp_size[2];
		funk2_character_t* temp_slot_name_str = (funk2_character_t*)alloca((max_slot_name_length + 1) * sizeof(funk2_character_t));
		f2ptr keyvalue_pair_iter = keyvalue_pairs;
		while (keyvalue_pair_iter) {
		  f2ptr keyvalue_pair = f2cons__car(keyvalue_pair_iter, cause);
		  f2ptr slot_name     = f2cons__car(keyvalue_pair, cause);
		  if (! raw__eq(cause, slot_name, __funk2.globalenv.type__symbol)) {
		    f2ptr slot_value    = f2cons__cdr(keyvalue_pair, cause);
		    if (raw__symbol__is_type(cause, slot_name)) {
		      raw__symbol__str_copy(cause, slot_name, temp_slot_name_str);
		      temp_slot_name_str[f2symbol__length(slot_name, cause)] = 0;
		    } else {
		      temp_slot_name_str[0] = 0;
		    }
		    if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}  
		    {f2__write_pretty__slot_key_and_value(temp_slot_name_str, max_slot_name_length, cause, fiber, stream, slot_value, nil, nil, nil,
							  ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num, available_width - width, subexp_size, try_wide, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];}
		  }
		  keyvalue_pair_iter = f2cons__cdr(keyvalue_pair_iter, cause);
		}
	      }
	    } else {
	      array_is_not_known_primobject = 1; // we print unknown primobjects in the same format of basic arrays
	    }
	  }
	}
	if (array_is_not_known_primobject) {
	  int subexp_size[2];
	  int i;
	  int write_elt_with_space = 0;
	  int length = raw__array__length(cause, exp);
	  if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__array_left_paren, cause));} indent_space_num ++; available_width --;
	  for(i = 0; i < length; i ++) {
	    f2ptr elt = raw__array__elt(cause, exp, i);
	    
	    if (write_elt_with_space) {
	      boolean_t subexp__wide_success[1] = {1};
	      f2__write_pretty(cause, fiber, nil, elt, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, subexp__wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode);
	      
	      if (width < available_width && subexp__wide_success[0]) {
		f2__write__space(cause, stream, use_html); width ++;
	      } else {
		if (wide_success) {
		  wide_success[0] = 0;
		}
		f2__write__line_break(cause, stream, use_html); width = 0; height ++;
		int i;
		for (i = 0; i < indent_space_num + width; i++) {
		  f2__write__space(cause, stream, use_html);
		}
	      }
	    }
	    f2__write_pretty(cause, fiber, stream, elt, ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	    write_elt_with_space = 1;
	  }
	  if (ptype == ptype_simple_array) {
	    f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	  } else {
	    f2__write__ansi_color(cause, stream, print__ansi__traced_array__foreground, use_ansi_colors, use_html);
	  }
	  if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__array_right_paren, cause));} width ++;
	}
	if (raw__primobject__is_type(cause, exp)) {
	  if (show_slot_causes ||
	      ((! f2primobject__is__largeinteger(exp, cause)) &&
	       (! f2primobject__is__cons(        exp, cause)) &&
	       (! f2primobject__is__doublelink(  exp, cause)) &&
	       (! f2primobject__is__list(        exp, cause)) &&
	       (! f2primobject__is__frame(       exp, cause)))) {
	    if (ptype == ptype_simple_array) {
	      f2__write__ansi_color(cause, stream, print__ansi__simple_array__foreground, use_ansi_colors, use_html);
	    } else {
	      f2__write__ansi_color(cause, stream, print__ansi__traced_array__foreground, use_ansi_colors, use_html);
	    }
	    if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__right_paren, cause));} width ++;
	    indent_space_num -= 2; available_width += 2;
	  }
	}
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
	break;
      case ptype_mutable_array_pointer: {
	char temp_str[128];
	f2__write__ansi_color(cause, stream, print__ansi__mutable_array_pointer__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "<mutable_array_pointer>"); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	if (stream) {found_illegal_type();} // set breakpoint on this function to stop here.
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      case ptype_larva: {
	f2__write__ansi_color(cause, stream, print__ansi__larva__foreground, use_ansi_colors, use_html);
	char temp_str[128]; 
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape, cause));} width ++;
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(__funk2.reader.char__escape_larva, cause));} width ++;
	sprintf(temp_str, u32__fstr, f2larva__larva_type(exp, cause)); if(stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      default: {
	char temp_str[128];
	f2__write__ansi_color(cause, stream, print__ansi__error__foreground, use_ansi_colors, use_html);
	sprintf(temp_str, "<illegal-type-%d>", (int)ptype); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	if (stream) {found_illegal_type();} // set breakpoint on this function to stop here.
	f2__write__ansi_color(cause, stream, print__ansi__default__foreground, use_ansi_colors, use_html);
      } break;
      }
      if (show_slot_causes) {
	char temp_str[128];
	int subexp_size[2];
	
	indent_space_num -= 7; available_width += 7;
	if (! try_wide) {indent_space_num -= 3; available_width += 3;}
	
	if (try_wide) {f2__write__space(cause, stream, use_html); width ++;} else {f2__write__line_break(cause, stream, use_html); width = 0; height ++; int i; for (i = 0; i < indent_space_num + width; i++) {f2__write__space(cause, stream, use_html);}}
	sprintf(temp_str, "cause "); if (stream) {raw__stream__writef(cause, stream, "%s", temp_str);} width += strlen(temp_str);
	if (! try_wide) {if (stream) {raw__stream__writef(cause, stream, "   ");} width += 3;}
	f2__write_pretty(cause, fiber, stream, f2ptype__cause(exp, cause), ((recursion_depth == -1) ? recursion_depth : (recursion_depth - 1)), indent_space_num + width, available_width - width, subexp_size, 1, wide_success, show_slot_causes, use_ansi_colors, use_html, brief_mode); width += subexp_size[0]; height += subexp_size[1];
	if (stream) {raw__stream__writef(cause, stream, "%c", f2char__ch(causal_debug__end_char, cause));} width ++;
      }
    }
  }
  if (return_size) {
    return_size[0] = width;
    return_size[1] = height;
  }
  if (available_width < 0) {
    if (wide_success) {
      wide_success[0] = 0;
    }
  }
  return exp;
}

f2ptr f2__fwrite_html(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp) {
  boolean_t brief_mode      = 1;
  int       recursion_depth = default_print_recursion_depth;
  int       screen_width    = raw__termios__width() * 3 / 4; // we shouldn't need this 3/4 factor, butwe print too wide above...
  return f2__write_pretty(cause, fiber, stream, exp, recursion_depth, 0, screen_width, NULL, 1, NULL, 0, 1, 1, brief_mode);
}

f2ptr f2__fwrite_depth(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp, int recursion_depth) {
  boolean_t brief_mode   = 1;
  int       screen_width = raw__termios__width() * 3 / 4; // we shouldn't need this 3/4 factor, butwe print too wide above...
  return f2__write_pretty(cause, fiber, stream, exp, recursion_depth, 0, screen_width, NULL, 1, NULL, 0, 1, 0, brief_mode);
}

f2ptr f2__write_depth(f2ptr cause, f2ptr fiber, f2ptr exp, int recursion_depth) {
  return f2__fwrite_depth(cause, fiber, __funk2.globalenv.stdout_stream, exp, recursion_depth);
}

f2ptr f2__exp__print_depth(f2ptr cause, f2ptr fiber, f2ptr exp, int recursion_depth) {
  return f2__write_depth(cause, fiber, exp, recursion_depth);
}
 
f2ptr f2__print_depth(f2ptr cause, f2ptr fiber, f2ptr exp, int recursion_depth) {
  raw__stream__writef(cause, __funk2.globalenv.stdout_stream, "\n");
  return f2__exp__print_depth(cause, fiber, exp, recursion_depth);
}


f2ptr f2__fwrite(f2ptr cause, f2ptr fiber, f2ptr stream, f2ptr exp) {return f2__fwrite_depth(    cause, fiber, stream,          exp, default_print_recursion_depth);}
f2ptr f2__write(f2ptr cause, f2ptr fiber, f2ptr exp)                {return f2__write_depth(     cause, fiber,                  exp, default_print_recursion_depth); fflush(stdout);}
f2ptr f2__exp__print(f2ptr cause, f2ptr fiber, f2ptr exp)           {return f2__exp__print_depth(cause, fiber,                  exp, default_print_recursion_depth);}
f2ptr f2__fiber__print(f2ptr cause, f2ptr fiber, f2ptr exp)         {return f2__print_depth(     cause, fiber,                  exp, default_print_recursion_depth);}
f2ptr f2__print(f2ptr cause, f2ptr exp)                             {return f2__fiber__print(    cause, f2__this__fiber(cause), exp);}

f2ptr f2__fprint_prompt_debug(f2ptr cause, f2ptr fiber, f2ptr stream, char* prompt, f2ptr exp) {
  int       recursion_depth = default_print_recursion_depth;
  int       screen_width    = raw__termios__width() * 3 / 4; // we shouldn't need this 3/4 factor, but we print too wide above...
  int       prompt_width    = strlen(prompt);
  boolean_t brief_mode      = 1;
  if (stream) {
    raw__stream__writef(cause, stream, "\n");
    raw__stream__writef(cause, stream, "%s", prompt);
    return f2__write_pretty(nil, fiber, stream, exp, recursion_depth, prompt_width, screen_width, NULL, 1, NULL, 1, 1, 0, brief_mode);
  } else {
    return exp;
  }
}

f2ptr f2__fprint_prompt(f2ptr cause, f2ptr fiber, f2ptr stream, char* prompt, f2ptr exp) {
  int       recursion_depth = default_print_recursion_depth;
  int       screen_width    = raw__termios__width() * 3 / 4; // we shouldn't need this 3/4 factor, butwe print too wide above...
  int       prompt_width    = strlen(prompt);
  boolean_t brief_mode      = 1;
  if (stream) {
    raw__stream__writef(cause, stream, "\n");
    raw__stream__writef(cause, stream, "%s", prompt);
    return f2__write_pretty(nil, fiber, stream, exp, recursion_depth, prompt_width, screen_width, NULL, 1, NULL, 0, 1, 0, brief_mode);
  } else {
    return exp;
  }
}

f2ptr f2__print_prompt(f2ptr cause, f2ptr fiber, char* prompt, f2ptr exp) {
  return f2__fprint_prompt(cause, fiber, __funk2.globalenv.stdout_stream, prompt, exp);
}

f2ptr f2__print_prompt_debug(f2ptr cause, f2ptr fiber, char* prompt, f2ptr exp) {
  return f2__fprint_prompt_debug(cause, fiber, __funk2.globalenv.stdout_stream, prompt, exp);
}


f2ptr raw__exp__printable_value__with_ptypehash(f2ptr cause, f2ptr this, f2ptr max_size, f2ptr size, f2ptr ptypehash, f2ptr subexp_size_place) {
  if (raw__ptypehash__contains(cause, ptypehash, this)) {
    f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, 1));
    return new__symbol(cause, "<...>");
  }
  s64 max_size__i = f2integer__i(max_size, cause);
  s64 size__i     = f2integer__i(size, cause);
  if (size__i >= max_size__i) {
    f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, 1));
    return new__symbol(cause, "...");
  }
  boolean_t this_is_printable;
  if (raw__cons__is_type(cause, this)) {
    f2__ptypehash__add(cause, ptypehash, this, f2bool__new(boolean__true));
    {
      s64   exp_size_i = 0;
      f2ptr print_seq = nil;
      {
	s64   list_element_count = 0;
	f2ptr last_cons          = nil;
	f2ptr iter               = this;
	while (iter) {
	  f2ptr element = f2__cons__car(cause, iter);
	  {
	    exp_size_i ++;
	    {
	      size__i ++;
	      size = f2integer__new(cause, size__i);
	    }
	  }
	  f2ptr element_print_value = raw__exp__printable_value__with_ptypehash(cause, element, max_size, size, ptypehash, subexp_size_place);
	  {
	    f2ptr subexp_size    = f2__place__thing(cause, subexp_size_place);
	    s64   subexp_size__i = f2integer__i(subexp_size, cause);
	    {
	      exp_size_i += subexp_size__i;
	      {
		size__i += subexp_size__i;
		size = f2integer__new(cause, size__i);
	      }
	    }
	  }
	  if (last_cons) {
	    f2ptr new_cons = raw__cons__new(cause, element_print_value, nil);
	    f2__cons__cdr__set(cause, last_cons, new_cons);
	    last_cons = new_cons;
	  } else {
	    last_cons = raw__cons__new(cause, element_print_value, nil);
	    print_seq = last_cons;
	  }
	  list_element_count ++;
	  if (list_element_count < 10) {
	    iter = f2__cons__cdr(cause, iter);
	  } else {
	    f2ptr new_cons = raw__cons__new(cause, new__symbol(cause, "..."), nil);
	    f2__cons__cdr__set(cause, last_cons, new_cons);
	    last_cons = new_cons;
	    iter = nil;
	  }
	}
      }
      f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, exp_size_i));
      return print_seq;
    }
  } else if (raw__traced_cmutex__is_type(cause, this)) {
    f2__ptypehash__add(cause, ptypehash, this, f2bool__new(boolean__true));
    {
      s64   exp_size_i = 0;
      f2ptr printable_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, printable_frame, new__symbol(cause, "printable_object_type"), new__symbol(cause, "traced_cmutex"));
      {
	exp_size_i ++;
	{
	  size__i ++;
	  size = f2integer__new(cause, size__i);
	}
      }
      f2__frame__add_var_value(cause, printable_frame, new__symbol(cause, "cmutex"), f2__traced_cmutex__cmutex(cause, this));
      {
	exp_size_i ++;
	{
	  size__i ++;
	  size = f2integer__new(cause, size__i);
	}
      }
      f2__frame__add_var_value(cause, printable_frame, new__symbol(cause, "fiber_with_lock"), raw__exp__printable_value__with_ptypehash(cause, f2__traced_cmutex__fiber_with_lock(cause, this), max_size, size, ptypehash, subexp_size_place));
      {
	f2ptr subexp_size    = f2__place__thing(cause, subexp_size_place);
	s64   subexp_size__i = f2integer__i(subexp_size, cause);
	{
	  exp_size_i += subexp_size__i;
	  {
	    size__i += subexp_size__i;
	    size = f2integer__new(cause, size__i);
	  }
	}
      }
      f2__frame__add_var_value(cause, printable_frame, new__symbol(cause, "lock_stack_trace"), raw__exp__printable_value__with_ptypehash(cause, f2__traced_cmutex__lock_stack_trace(cause, this), max_size, size, ptypehash, subexp_size_place));
      {
	f2ptr subexp_size    = f2__place__thing(cause, subexp_size_place);
	s64   subexp_size__i = f2integer__i(subexp_size, cause);
	{
	  exp_size_i += subexp_size__i;
	  {
	    size__i += subexp_size__i;
	    size = f2integer__new(cause, size__i);
	  }
	}
      }
      f2__frame__add_var_value(cause, printable_frame, new__symbol(cause, "fibers_waiting_for_lock"), raw__exp__printable_value__with_ptypehash(cause, f2__traced_cmutex__fibers_waiting_for_lock(cause, this), max_size, size, ptypehash, subexp_size_place));
      {
	f2ptr subexp_size    = f2__place__thing(cause, subexp_size_place);
	s64   subexp_size__i = f2integer__i(subexp_size, cause);
	{
	  exp_size_i += subexp_size__i;
	  {
	    size__i += subexp_size__i;
	    size = f2integer__new(cause, size__i);
	  }
	}
      }
      f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, exp_size_i));
      return printable_frame;
    }
  } else if (raw__frame__is_type(cause, this)) {
    f2__ptypehash__add(cause, ptypehash, this, f2bool__new(boolean__true));
    {
      s64   exp_size_i = 0;
      f2ptr printable_frame = f2__frame__new(cause, nil);
      frame__var__iteration(cause, this, slot_name, slot_value,
			    {
			      exp_size_i ++;
			      {
				size__i ++;
				size = f2integer__new(cause, size__i);
			      }
			    }
			    f2__frame__add_var_value(cause, printable_frame, slot_name, raw__exp__printable_value__with_ptypehash(cause, slot_value, max_size, size, ptypehash, subexp_size_place));
			    {
			      f2ptr subexp_size    = f2__place__thing(cause, subexp_size_place);
			      s64   subexp_size__i = f2integer__i(subexp_size, cause);
			      {
				exp_size_i += subexp_size__i;
				{
				  size__i += subexp_size__i;
				  size = f2integer__new(cause, size__i);
				}
			      }
			    }
			    );
      f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, exp_size_i));
      return printable_frame;
    }
  } else if (raw__array__is_type(cause, this)) {
    this_is_printable = boolean__false;
  } else {
    this_is_printable = boolean__true;
  }
  if (this_is_printable) {
    f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, 1));
    return this;
  }
  f2__place__thing__set(cause, subexp_size_place, f2integer__new(cause, 1));
  return f2list2__new(cause, f2__object__type(cause, this), new__symbol(cause, "<>"));
}

f2ptr f2__exp__printable_value(f2ptr cause, f2ptr this) {
  f2ptr max_size          = f2integer__new(cause, 100);
  f2ptr size              = f2integer__new(cause, 0);
  f2ptr ptypehash         = f2__ptypehash__new(cause);
  f2ptr subexp_size_place = f2__place__new(cause, nil);
  return raw__exp__printable_value__with_ptypehash(cause, this, max_size, size, ptypehash, subexp_size_place);
}
def_pcfunk1(exp__printable_value, this,
	    "Converts an object into a form that can be directly printed to the screen.",
	    return f2__exp__printable_value(this_cause, this));

/*
[defunk terminal_print_frame-prepare_for_printing_to_standard_terminal-thread_unsafe [this]
  [terminal_print_frame-prepare_for_printing-thread_unsafe this [termios-width] [integer-subtract [termios-height] 3]]]

[defunk terminal_format-thread_unsafe [terminal_print_frame :rest exps]
  [if [null terminal_print_frame]
      [apply &string-format exps]
    [mapc [funk [exp]
		[terminal_print_frame-prepare_for_printing_to_standard_terminal-thread_unsafe terminal_print_frame]
		[if [is-type `string exp]
		    [terminal_print_frame-write_string-thread_unsafe terminal_print_frame exp]
		  [exp-terminal_print_with_frame-thread_unsafe exp terminal_print_frame]]]
	  exps]]]

[defunk terminal_format [terminal_print_frame :rest exps]
  [if terminal_print_frame
      [while [have [get terminal_print_frame cmutex] trylock]
	[millisleep 10]]]
  [let [[result [apply &terminal_format-thread_unsafe [cons terminal_print_frame exps]]]]
    [if terminal_print_frame
	[have [get terminal_print_frame cmutex] unlock]]
    result]]
*/

f2ptr raw__terminal_print_frame__prepare_for_printing_to_standard_terminal__thread_unsafe(f2ptr cause, f2ptr this) {
  s64 width  = raw__termios__width(cause);
  s64 height = raw__termios__height(cause) - 3;
  raw__terminal_print_frame__prepare_for_printing__thread_unsafe(cause, this, f2integer__new(cause, width), f2integer__new(cause, height));
  return nil;
}

f2ptr raw__terminal_format__thread_unsafe(f2ptr cause, f2ptr terminal_print_frame, f2ptr expressions) {
  if (terminal_print_frame == nil) {
    return f2__string__format(cause, expressions);
  } else {
    f2ptr iter = expressions;
    while (iter != nil) {
      f2ptr expression = f2cons__car(iter, cause);
      assert_value(raw__terminal_print_frame__prepare_for_printing_to_standard_terminal__thread_unsafe(cause, terminal_print_frame));
      if (raw__string__is_type(cause, expression)) {
	assert_value(f2__terminal_print_frame__write_string__thread_unsafe(cause, terminal_print_frame, expression));
      } else {
	assert_value(f2__exp__terminal_print_with_frame__thread_unsafe(cause, expression, terminal_print_frame));
      }
      iter = f2cons__cdr(iter, cause);
    }
    return nil;
  }
}

f2ptr raw__terminal_format(f2ptr cause, f2ptr terminal_print_frame, f2ptr expressions) {
  f2ptr cmutex;
  if (terminal_print_frame != nil) {
    cmutex = f2__terminal_print_frame__cmutex(cause, terminal_print_frame);
    raw__cmutex__lock(cause, cmutex);
  }
  f2ptr result = raw__terminal_format__thread_unsafe(cause, terminal_print_frame, expressions);
  if (terminal_print_frame != nil) {
    f2cmutex__unlock(cmutex, cause);
  }
  return result;
}

f2ptr f2__terminal_format(f2ptr cause, f2ptr terminal_print_frame, f2ptr expressions) {
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  assert_argument_type(conslist,             expressions);
  return raw__terminal_format(cause, terminal_print_frame, expressions);
}
def_pcfunk1_and_rest(terminal_format, terminal_print_frame, expressions,
		     "Formats the given expressions to the given terminal_print_frame.",
		     return f2__terminal_format(this_cause, terminal_print_frame, expressions));



// **

void f2__print__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(exp__printable_value);
  f2__primcfunk__init__defragment__fix_pointers(terminal_format);
}

void f2__print__reinitialize_globalvars() {
  f2__primcfunk__init__1(exp__printable_value, this);
  f2__primcfunk__init__1_and_rest(terminal_format, terminal_print_frame, expressions);
}

void f2__print__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "print", "", &f2__print__reinitialize_globalvars, &f2__print__defragment__fix_pointers);
  
  f2__print__reinitialize_globalvars();
}


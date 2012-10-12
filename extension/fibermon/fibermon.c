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

#include "../../c/funk2.h"
#include "../gtk_extension/gtk_extension.h"

f2ptr f2__fibermon__bytes__to_memory_string(f2ptr cause, f2ptr this) {
  f2ptr i = object__get_0(cause, this, "as-integer");
  assert_value(i);
  if (! raw__integer__is_type(cause, i)) {
    return f2larva__new(cause, 12365, nil);
  }
  s64 i__i = f2integer__i(i, cause);
  if      (i__i <                                1024ull)  {return f2__exp__as__string(cause, i);}
  else if (i__i <                     (1024ull * 1024ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                             1024.0)),  new__string(cause, "k")));}
  else if (i__i <           (1024ull * 1024ull * 1024ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                   (1024.0 * 1024.0))), new__string(cause, "M")));}
  else if (i__i < (1024ull * 1024ull * 1024ull * 1024ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /          (1024.0 * 1024.0 * 1024.0))), new__string(cause, "G")));}
  else                                                     {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i / (1024.0 * 1024.0 * 1024.0 * 1024.0))), new__string(cause, "T")));}
}
export_cefunk1(fibermon__bytes__to_memory_string, this, 0, "");


f2ptr f2__fibermon__nanoseconds__to_time_string(f2ptr cause, f2ptr this) {
  f2ptr i = object__get_0(cause, this, "as-integer");
  assert_value(i);
  if (! raw__integer__is_type(cause, i)) {
    return f2larva__new(cause, 1245, nil);
  }
  s64 i__i = f2integer__i(i, cause);
  if      (i__i <                                              1000ull)  {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, i),                                                                                    new__string(cause, "ns")));}
  else if (i__i <                                   (1000ull * 1000ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                                         1000.0)),  new__string(cause, "us")));}
  else if (i__i <                         (1000ull * 1000ull * 1000ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                               (1000.0 * 1000.0))), new__string(cause, "ms")));}
  else if (i__i <                 (60ull * 1000ull * 1000ull * 1000ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                      (1000.0 * 1000.0 * 1000.0))), new__string(cause, "s")));}
  else if (i__i <         (60ull * 60ull * 1000ull * 1000ull * 1000ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /               (60.0 * 1000.0 * 1000.0 * 1000.0))), new__string(cause, "m")));}
  else if (i__i < (24ull * 60ull * 60ull * 1000ull * 1000ull * 1000ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /        (60.0 * 60.0 * 1000.0 * 1000.0 * 1000.0))), new__string(cause, "h")));}
  else                                                                   {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i / (24.0 * 60.0 * 60.0 * 1000.0 * 1000.0 * 1000.0))), new__string(cause, "d")));}
}
export_cefunk1(fibermon__nanoseconds__to_time_string, this, 0, "");

s64 fibermon__cause__name__row_index      = 0;
s64 fibermon__bug__cause__name__row_index = 1;
s64 fibermon__keep_undead__row_index      = 2;
s64 fibermon__is_zombie__row_index        = 3;
s64 fibermon__is_complete__row_index      = 4;
s64 fibermon__execute_cmutex__row_index   = 5;
s64 fibermon__paused__row_index           = 6;
s64 fibermon__last_executed__row_index    = 7;
s64 fibermon__sleep_until__row_index      = 8;
s64 fibermon__execution_time__row_index   = 9;
s64 fibermon__bytecode_count__row_index   = 10;
s64 fibermon__bcs__row_index              = 11;
s64 fibermon__efficiency__row_index       = 12;

f2ptr f2__fibermon_fiber__construct_fast(f2ptr cause, f2ptr this) {
  f2ptr this__frame = raw__gtk__frame__new(cause, new__string(cause, "fiber"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "frame"), this__frame);
  f2ptr this__vbox = raw__gtk__vbox__new(cause, f2integer__new(cause, 2));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "vbox"), this__vbox);
  f2ptr this__menu_bar = raw__gtk__menu_bar__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "menu_bar"), this__menu_bar);
  
  f2ptr this__command_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Command"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_menu_item"), this__command_menu_item);
  f2ptr this__command_menu = raw__gtk__menu__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_menu"), this__command_menu);
  f2ptr this__command_pause_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Pause"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_pause_menu_item"), this__command_pause_menu_item);
  f2ptr this__command_unpause_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Unpause"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_unpause_menu_item"), this__command_unpause_menu_item);
  f2ptr this__command_keep_undead_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Keep Undead"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_keep_undead_menu_item"), this__command_keep_undead_menu_item);
  f2ptr this__command_dont_keep_undead_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Don't Keep Undead"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_dont_keep_undead_menu_item"), this__command_dont_keep_undead_menu_item);
  f2ptr this__command_quit_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Quit"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_quit_menu_item"), this__command_quit_menu_item);
  
  f2ptr this__view_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "View"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_menu_item"), this__view_menu_item);
  f2ptr this__view_menu = raw__gtk__menu__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_menu"), this__view_menu);
  f2ptr this__view_fiber_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Fiber"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_fiber_menu_item"), this__view_fiber_menu_item);
  f2ptr this__view_fiber_value_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Fiber Value"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_fiber_value_menu_item"), this__view_fiber_value_menu_item);
  f2ptr this__view_bug_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Bug"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_bug_menu_item"), this__view_bug_menu_item);
  f2ptr this__view_fiber_cause_register_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Cause Register"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_fiber_cause_register_menu_item"), this__view_fiber_cause_register_menu_item);
  f2ptr this__view_creation_cause_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Creation Cause"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_creation_cause_menu_item"), this__view_creation_cause_menu_item);
  f2ptr this__view_creation_fiber_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Creation Fiber"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_creation_fiber_menu_item"), this__view_creation_fiber_menu_item);
  f2ptr this__view_stack_trace_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Stack Trace"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_stack_trace_menu_item"), this__view_stack_trace_menu_item);
  f2ptr this__view_stack_trace_first_block_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "First Block of Stack Trace"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "view_stack_trace_first_block_menu_item"), this__view_stack_trace_first_block_menu_item);
  
  f2ptr this__environment_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Environment"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_menu_item"), this__environment_menu_item);
  f2ptr this__environment_menu = raw__gtk__menu__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_menu"), this__environment_menu);
  f2ptr this__environment_define_fiber_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Fiber"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_fiber_menu_item"), this__environment_define_fiber_menu_item);
  f2ptr this__environment_define_fiber_value_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Fiber Value"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_fiber_value_menu_item"), this__environment_define_fiber_value_menu_item);
  f2ptr this__environment_define_bug_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Bug"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_bug_menu_item"), this__environment_define_bug_menu_item);
  f2ptr this__environment_define_fiber_cause_register_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Cause Register"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_fiber_cause_register_menu_item"), this__environment_define_fiber_cause_register_menu_item);
  f2ptr this__environment_define_creation_cause_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Creation Cause"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_creation_cause_menu_item"), this__environment_define_creation_cause_menu_item);
  f2ptr this__environment_define_creation_fiber_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Creation Fiber"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_creation_fiber_menu_item"), this__environment_define_creation_fiber_menu_item);
  f2ptr this__environment_define_stack_trace_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define Stack Trace"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_stack_trace_menu_item"), this__environment_define_stack_trace_menu_item);
  f2ptr this__environment_define_stack_trace_first_block_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Define First Block of Stack Trace"));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "environment_define_stack_trace_first_block_menu_item"), this__environment_define_stack_trace_first_block_menu_item);
  
  f2ptr this__hbox = raw__gtk__hbox__new(cause, f2integer__new(cause, 2));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "hbox"), this__hbox);
  f2ptr this__progress_bar = raw__gtk__progress_bar__new(cause);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "progress_bar"), this__progress_bar);
  f2ptr this__table = raw__gtk__table__new(cause, f2integer__new(cause, 12), f2integer__new(cause, 2), nil);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "table"), this__table);
  f2ptr this__table_labels = f2__array__new(cause, f2list2__new(cause, f2integer__new(cause, 12), f2integer__new(cause, 2)));
  f2__frame__add_var_value(cause, this, new__symbol(cause, "table_labels"), this__table_labels);
  
  raw__gtk__menu__append(cause, this__command_menu, this__command_pause_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_unpause_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_keep_undead_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_dont_keep_undead_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_quit_menu_item);
  raw__gtk__menu_bar__append(cause, this__menu_bar, this__command_menu_item);
  raw__gtk__menu_item__set_submenu(cause, this__command_menu_item, this__command_menu);
  
  raw__gtk__menu__append(cause, this__view_menu, this__view_fiber_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_fiber_value_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_bug_menu_item);
  raw__gtk__widget__set_sensitive(cause, this__view_bug_menu_item, f2bool__new(boolean__false));
  raw__gtk__menu__append(cause, this__view_menu, this__view_fiber_cause_register_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_creation_cause_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_creation_fiber_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_stack_trace_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_stack_trace_first_block_menu_item);
  raw__gtk__menu_bar__append(cause, this__menu_bar, this__view_menu_item);
  raw__gtk__menu_item__set_submenu(cause, this__view_menu_item, this__view_menu);
  
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_fiber_menu_item);
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_fiber_value_menu_item);
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_bug_menu_item);  raw__gtk__widget__set_sensitive(cause, this__environment_define_bug_menu_item, f2bool__new(boolean__false));
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_fiber_cause_register_menu_item);
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_creation_cause_menu_item);
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_creation_fiber_menu_item);
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_stack_trace_menu_item);
  raw__gtk__menu__append(cause, this__environment_menu, this__environment_define_stack_trace_first_block_menu_item);
  raw__gtk__menu_bar__append(cause, this__menu_bar, this__environment_menu_item);
  raw__gtk__menu_item__set_submenu(cause, this__environment_menu_item, this__environment_menu);
  
  raw__gtk__progress_bar__set_orientation(cause, this__progress_bar, new__symbol(cause, "bottom_to_top"));
  
  s64 total_row_count = 13;
  {
    u64 row;
    for (row = 0; row < total_row_count; row ++) {
      f2ptr row_labels = raw__array__elt(cause, this__table_labels, row);
      {
	u64 column;
	for (column = 0; column < 2; column ++) {
	  f2ptr table_label = raw__gtk__label__new(cause, new__string(cause, ""));
	  raw__gtk__misc__set_alignment(cause, table_label, f2double__new(cause, 0.0), f2double__new(cause, 0.0));
	  raw__array__elt__set(cause, row_labels, column, table_label);
	  raw__gtk__table__attach(cause, this__table, table_label, f2integer__new(cause, column), f2integer__new(cause, column + 1), f2integer__new(cause, row), f2integer__new(cause, row + 1), f2integer__new(cause, 0), f2integer__new(cause, 0));
	}
      }
    }
  }
  
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__cause__name__row_index),      0), new__string(cause, "cause-name"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bug__cause__name__row_index), 0), new__string(cause, "bug cause-name"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__keep_undead__row_index),      0), new__string(cause, "keep_undead"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__is_zombie__row_index),        0), new__string(cause, "is_zombie"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__is_complete__row_index),      0), new__string(cause, "is_complete"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__execute_cmutex__row_index),   0), new__string(cause, "execute_cmutex"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__paused__row_index),           0), new__string(cause, "paused"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__last_executed__row_index),    0), new__string(cause, "last executed"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__sleep_until__row_index),      0), new__string(cause, "sleep until"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__execution_time__row_index),   0), new__string(cause, "execution_time"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bytecode_count__row_index),   0), new__string(cause, "bytecode_count"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bcs__row_index),              0), new__string(cause, "Bc/s"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__efficiency__row_index),       0), new__string(cause, "efficiency"));
  
  raw__gtk__box__pack_start(cause, this__hbox, this__progress_bar, nil, nil, f2integer__new(cause, 0));
  raw__gtk__box__pack_start(cause, this__hbox, this__table,        nil, nil, f2integer__new(cause, 0));
  raw__gtk__box__pack_start(cause, this__vbox, this__menu_bar,     nil, nil, f2integer__new(cause, 0));
  raw__gtk__box__pack_start(cause, this__vbox, this__hbox,         f2bool__new(boolean__true), f2bool__new(boolean__true), f2integer__new(cause, 0));
  
  raw__gtk__container__add(cause, this__frame, this__vbox);
  
  return this;
}
export_cefunk1(fibermon_fiber__construct_fast, this, 0, "");


f2ptr f2__fibermon_fiber__redraw_fast(f2ptr cause, f2ptr this) {
  f2ptr this__fiber                 = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "fiber"),                 nil); if (! raw__fiber__is_type(cause, this__fiber))        {return f2larva__new(cause, 61, nil);}
  f2ptr this__progress_bar          = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "progress_bar"),          nil); if (! this__progress_bar)                             {return f2larva__new(cause, 62, nil);}
  f2ptr this__menu_bar              = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "menu_bar"),              nil); if (! this__menu_bar)                                 {return f2larva__new(cause, 62, nil);}
  f2ptr this__execution_efficiency  = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "execution_efficiency"),  nil);
  f2ptr this__execution_nanoseconds = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "execution_nanoseconds"), nil);
  f2ptr this__bytecode_count        = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bytecode_count"),        nil);
  f2ptr this__bytecodes_per_second  = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bytecodes_per_second"),  nil);
  f2ptr this__table_labels          = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "table_labels"),          nil); if (! raw__array__is_type(cause, this__table_labels)) {return f2larva__new(cause, 63, nil);}
  f2__gtk__progress_bar__set_fraction(cause, this__progress_bar, (this__execution_efficiency != nil) ? this__execution_efficiency : f2integer__new(cause, 0));
  
  {
    {
      f2ptr cause_reg          = f2fiber__cause_reg(this__fiber, cause);
      f2ptr cause__name__value = raw__cause__is_type(cause, cause_reg) ? f2__cause__lookup(cause, cause_reg, new__symbol(cause, "cause-name")) : nil;
      f2ptr name_string        = f2__exp__as__string(cause, cause__name__value);
      f2ptr short_name_string;
      if (raw__string__length(cause, name_string) < 16) {
	short_name_string = name_string;
      } else {
	short_name_string = f2__stringlist__concat(cause, f2list2__new(cause, f2__string__substring(cause, name_string, f2integer__new(cause, 0), f2integer__new(cause, 13)), new__string(cause, "...")));
      }
      f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__cause__name__row_index), 1), short_name_string);
    }
    {
      f2ptr value = f2fiber__value(this__fiber, cause);
      if (raw__bug__is_type(cause, value)) {
	f2ptr bug = value;
	f2ptr bug__cause = f2ptype__cause(bug, cause);
	f2ptr bug__cause__name;
	if (raw__cause__is_type(cause, bug__cause)) {
	  bug__cause__name = f2__cause__lookup(cause, bug__cause, new__symbol(cause, "cause-name"));
	} else {
	  bug__cause__name = nil;
	}
	f2ptr name_string = f2__exp__as__string(cause, bug__cause__name);
	f2ptr short_name_string;
	if (raw__string__length(cause, name_string) < 16) {
	  short_name_string = name_string;
	} else {
	  short_name_string = f2__stringlist__concat(cause, f2list2__new(cause, f2__string__substring(cause, name_string, f2integer__new(cause, 0), f2integer__new(cause, 13)), new__string(cause, "...")));
	}
	f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bug__cause__name__row_index), 1), short_name_string);
      } else {
	f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bug__cause__name__row_index), 1), new__string(cause, "N/A"));
      }
    }
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__keep_undead__row_index),    1), (f2fiber__keep_undead(this__fiber, cause) != nil) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__is_zombie__row_index),      1), (f2fiber__is_zombie(  this__fiber, cause) != nil) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__is_complete__row_index),    1), raw__fiber__is_complete(cause, this__fiber) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__execute_cmutex__row_index), 1), raw__cmutex__is_locked(cause, f2fiber__execute_cmutex(this__fiber, cause)) ? new__string(cause, "Locked") : new__string(cause, "Unlocked"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__paused__row_index),         1), (f2fiber__paused(     this__fiber, cause) != nil) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__last_executed__row_index),  1), f2__exp__as__string(cause, nil));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__sleep_until__row_index),    1), f2__exp__as__string(cause, (f2fiber__sleep_until_time(  this__fiber, cause) != nil) ? f2bool__new(boolean__true) : nil));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__execution_time__row_index), 1), f2__fibermon__nanoseconds__to_time_string(cause, ((this__execution_nanoseconds != nil) ? this__execution_nanoseconds : f2integer__new(cause, 0))));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bytecode_count__row_index), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__bytecode_count != nil) ? this__bytecode_count : f2integer__new(cause, 0))),
																						 new__string(cause, "Bc"))));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__bcs__row_index),            1),
			     f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__bytecodes_per_second != nil) ? this__bytecodes_per_second : f2integer__new(cause, 0))),
									new__string(cause, "Bc/s"))));
    
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, fibermon__efficiency__row_index),     1),
			     f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2__number__multiplied_by(cause, ((this__execution_efficiency != nil) ? this__execution_efficiency : f2integer__new(cause, 0)), f2double__new(cause, 100.0))),
									new__string(cause, "%"))));
  }
  if        (f2fiber__is_complete(this__fiber, cause) != nil) {
    // paint menu_bar if fiber is dead.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), f2__gdk__rgb_color__new(cause, f2double__new(cause, 0.5), f2double__new(cause, 0.5), f2double__new(cause, 0.5)));
  } else if ((this__bytecodes_per_second != nil) &&
	     (f2__number__is_numerically_equal_to(cause, this__bytecodes_per_second, f2integer__new(cause, 0)) != nil) &&
	     raw__cmutex__is_locked(cause, f2__fiber__execute_cmutex(cause, this__fiber))) {
    // paint menu_bar if fiber has locked-up since last redraw.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), f2__gdk__rgb_color__new(cause, f2double__new(cause, 1.0), f2double__new(cause, 0.75), f2double__new(cause, 0.75)));
  } else if ((this__bytecodes_per_second != nil) &&
	     (f2__number__is_numerically_equal_to(cause, this__bytecodes_per_second, f2integer__new(cause, 0)) == nil)) {
    // paint menu_bar if fiber has executed bytecodes since last redraw.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), f2__gdk__rgb_color__new(cause, f2double__new(cause, 0.75), f2double__new(cause, 1.0), f2double__new(cause, 0.75)));
  } else if ((f2fiber__paused(this__fiber, cause) != nil) &&
	     raw__bug__is_type(cause, f2fiber__value(this__fiber, cause))) {
    // paint menu_bar if fiber is paused and has *bug* in value register.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), f2__gdk__rgb_color__new(cause, f2double__new(cause, 1.0), f2double__new(cause, 0.5), f2double__new(cause, 0.5)));
    {
      f2ptr this__view_bug_menu_item = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "view_bug_menu_item"), nil);
      f2__gtk__widget__set_sensitive(cause, this__view_bug_menu_item, f2bool__new(boolean__true));
    }
    {
      f2ptr this__environment_define_bug_menu_item = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "environment_define_bug_menu_item"), nil);
      f2__gtk__widget__set_sensitive(cause, this__environment_define_bug_menu_item, f2bool__new(boolean__true));
    }
  } else if (f2fiber__paused(this__fiber, cause) != nil) {
    // paint menu_bar if fiber is paused.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), f2__gdk__rgb_color__new(cause, f2double__new(cause, 0.0), f2double__new(cause, 0.5), f2double__new(cause, 0.5)));
  } else if (f2fiber__sleep_until_time(this__fiber, cause) != nil) {
    // paint menu_bar if fiber is asleep.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), f2__gdk__rgb_color__new(cause, f2double__new(cause, 0.0), f2double__new(cause, 0.5), f2double__new(cause, 0.0)));
  } else {
    // paint menu_bar as the default theme color if fiber is in none of the above states.
    f2__gtk__widget__modify_bg(cause, this__menu_bar, new__symbol(cause, "normal"), nil);
  }
  return nil;
}
export_cefunk1(fibermon_fiber__redraw_fast, this, 0, "");


f2ptr f2__fibermon_fiber__recompute_statistics_fast(f2ptr cause, f2ptr this) {
  f2ptr this__fiber                         = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "fiber"),                 nil); if (! raw__fiber__is_type(cause, this__fiber)) {return f2larva__new(cause, 71, nil);}
  f2ptr last_time                           = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "time"),                  nil);
  f2ptr last_execution_nanoseconds          = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "execution_nanoseconds"), nil);
  f2ptr last_bytecode_count                 = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bytecode_count"),        nil);
  f2ptr this__time                          = f2__time(cause);                                      f2__frame__add_var_value(cause, this, new__symbol(cause, "time"),                  this__time);
  f2ptr this__execution_nanoseconds         = f2__fiber__execution_nanoseconds(cause, this__fiber); f2__frame__add_var_value(cause, this, new__symbol(cause, "execution_nanoseconds"), this__execution_nanoseconds);
  f2ptr this__bytecode_count                = f2__fiber__bytecode_count(       cause, this__fiber); f2__frame__add_var_value(cause, this, new__symbol(cause, "bytecode_count"),        this__bytecode_count);
  f2ptr this__elapsed_nanoseconds           = (last_time                  != nil) ? f2integer__new(cause, (f2integer__i(f2time__nanoseconds_since_1970(this__time, cause), cause) - f2integer__i(f2time__nanoseconds_since_1970(last_time, cause), cause))) : nil;
  f2__frame__add_var_value(cause, this, new__symbol(cause, "elapsed_nanoseconds"), this__elapsed_nanoseconds);
  f2ptr this__elapsed_execution_nanoseconds = (last_execution_nanoseconds != nil) ? f2integer__new(cause, (f2integer__i(this__execution_nanoseconds,                       cause) - f2integer__i(last_execution_nanoseconds,                       cause))) : nil;
  f2__frame__add_var_value(cause, this, new__symbol(cause, "elapsed_execution_nanoseconds"), this__elapsed_execution_nanoseconds);
  f2ptr this__elapsed_bytecode_count        = (last_bytecode_count        != nil) ? f2integer__new(cause, (f2integer__i(this__bytecode_count,                              cause) - f2integer__i(last_bytecode_count,                              cause))) : nil;
  f2__frame__add_var_value(cause, this, new__symbol(cause, "elapsed_bytecode_count"), this__elapsed_bytecode_count);
  if ((this__elapsed_bytecode_count != nil) &&
      (this__elapsed_nanoseconds    != nil)) {
    f2ptr this__bytecodes_per_second = f2double__new(cause, ((1000000000.0 * f2integer__i(this__elapsed_bytecode_count, cause)) / f2integer__i(this__elapsed_nanoseconds, cause))); f2__frame__add_var_value(cause, this, new__symbol(cause, "bytecodes_per_second"), this__bytecodes_per_second);
  }
  if ((this__elapsed_execution_nanoseconds != nil) &&
      (this__elapsed_nanoseconds           != nil)) {
    double fraction = ((double)f2integer__i(this__elapsed_execution_nanoseconds, cause)) / ((double)f2integer__i(this__elapsed_nanoseconds, cause));
    f2ptr this__execution_efficiency = f2double__new(cause, ((fraction < 0.0) ?
							     0.0 : ((fraction > 1.0) ?
								    1.0 : fraction))); 
    f2__frame__add_var_value(cause, this, new__symbol(cause, "execution_efficiency"), this__execution_efficiency);
  }
  return nil;
}
export_cefunk1(fibermon_fiber__recompute_statistics_fast, this, 0, "");


f2ptr f2__fibermon_processor__construct_fast(f2ptr cause, f2ptr this) {
  f2ptr this__vbox                = raw__gtk__vbox__new(           cause, f2integer__new(cause, 2));                                                           f2__frame__add_var_value(cause, this, new__symbol(cause, "vbox"),                this__vbox);
  f2ptr this__progress_bar        = raw__gtk__progress_bar__new(   cause);                                                                                     f2__frame__add_var_value(cause, this, new__symbol(cause, "progress_bar"),        this__progress_bar);
  f2ptr this__fiber_vbox          = raw__gtk__vbox__new(           cause, f2integer__new(cause, 2));                                                           f2__frame__add_var_value(cause, this, new__symbol(cause, "fiber_vbox"),          this__fiber_vbox);
  f2ptr this__fibermon_fiber_hash = f2__ptypehash__new(            cause);                                                                                     f2__frame__add_var_value(cause, this, new__symbol(cause, "fibermon_fiber_hash"), this__fibermon_fiber_hash);
  f2ptr this__table               = raw__gtk__table__new(          cause, f2integer__new(cause, 5), f2integer__new(cause, 2), nil);                            f2__frame__add_var_value(cause, this, new__symbol(cause, "table"),               this__table);
  f2ptr this__table_labels        = f2__array__new(cause, f2list2__new(cause, f2integer__new(cause, 5), f2integer__new(cause, 2)));                            f2__frame__add_var_value(cause, this, new__symbol(cause, "table_labels"),        this__table_labels);
  f2ptr this__index               = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "index"), nil); if (! raw__integer__is_type(cause, this__index)) {return f2larva__new(cause, 81, nil);}
  f2ptr this__frame               = raw__gtk__frame__new(          cause, f2__stringlist__concat(cause, f2list2__new(cause, new__string(cause, "processor #"), f2__exp__as__string(cause, this__index)))); f2__frame__add_var_value(cause, this, new__symbol(cause, "frame"), this__frame);
  {
    u64 row;
    for (row = 0; row < 5; row ++) {
      f2ptr row_labels = raw__array__elt(cause, this__table_labels, row);
      {
	u64 column;
	for (column = 0; column < 2; column ++) {
	  f2ptr table_label = raw__gtk__label__new(cause, new__string(cause, ""));
	  raw__gtk__misc__set_alignment(cause, table_label, f2double__new(cause, 0.0), f2double__new(cause, 0.0));
	  raw__array__elt__set(cause, row_labels, column, table_label);
	  raw__gtk__table__attach(cause, this__table, table_label, f2integer__new(cause, column), f2integer__new(cause, column + 1), f2integer__new(cause, row), f2integer__new(cause, row + 1), f2integer__new(cause, 0), f2integer__new(cause, 0));
	}
      }
    }
  }
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  0), 0), new__string(cause, "bytecodes_per_second"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  1), 0), new__string(cause, "execution_efficiency"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  2), 0), new__string(cause, "total_used_memory"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  3), 0), new__string(cause, "total_free_memory"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  4), 0), new__string(cause, "fragmentation"));
  f2__gtk__box__pack_start(cause, this__vbox, this__table,        nil, nil, f2integer__new(cause, 0));
  f2__gtk__box__pack_start(cause, this__vbox, this__progress_bar, nil, nil, f2integer__new(cause, 0));
  f2__gtk__box__pack_start(cause, this__vbox, this__fiber_vbox, f2bool__new(boolean__true), f2bool__new(boolean__true), f2integer__new(cause, 0));
  f2__gtk__container__add(cause, this__frame, this__vbox);
  return nil;
}
export_cefunk1(fibermon_processor__construct_fast, this, 0, "");


f2ptr f2__fibermon_processor__redraw_fast(f2ptr cause, f2ptr this) {
  f2ptr this__progress_bar         = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "progress_bar"),         nil); if (! this__progress_bar) {return f2larva__new(cause, 92, nil);}
  f2ptr this__table_labels         = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "table_labels"),         nil); if (! raw__array__is_type(cause, this__table_labels)) {return f2larva__new(cause, 93, nil);}
  f2ptr this__bytecodes_per_second = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bytecodes_per_second"), nil);
  f2ptr this__execution_efficiency = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "execution_efficiency"), nil);
  f2ptr this__total_used_memory    = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "total_used_memory"),    nil);
  f2ptr this__total_free_memory    = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "total_free_memory"),    nil);
  f2ptr this__fragmentation        = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "fragmentation"),        nil);
  
  f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 0), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__bytecodes_per_second != nil) ? this__bytecodes_per_second : f2integer__new(cause, 0))),
																		       new__string(cause, "Bc/s"))));
  f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 1), 1),
			   f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2__number__multiplied_by(cause, ((this__execution_efficiency != nil) ? this__execution_efficiency : f2integer__new(cause, 0)), f2double__new(cause, 100.0))),
								      new__string(cause, "%"))));
  f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 2), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__total_used_memory != nil) ? this__total_used_memory : f2integer__new(cause, 0))),
																		       new__string(cause, "b"))));
  f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 3), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__total_free_memory != nil) ? this__total_free_memory : f2integer__new(cause, 0))),
																		       new__string(cause, "b"))));
  f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 4), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2__number__multiplied_by(cause, ((this__fragmentation != nil) ? this__fragmentation : f2integer__new(cause, 0)), f2double__new(cause, 100.0))),
																		       new__string(cause, "%"))));
  {
    f2ptr progress_fraction = (this__execution_efficiency != nil) ? this__execution_efficiency : f2double__new(cause, 0.0);
    f2__gtk__progress_bar__set_text(    cause, this__progress_bar, f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2__number__multiplied_by(cause, progress_fraction, f2double__new(cause, 100.0))), new__string(cause, "%"))));
    f2__gtk__progress_bar__set_fraction(cause, this__progress_bar, progress_fraction);
  }
  return nil;
}
export_cefunk1(fibermon_processor__redraw_fast, this, 0, "");


f2ptr f2__fibermon_processor__recompute_statistics_fast(f2ptr cause, f2ptr this) {
  f2ptr this__fibermon_fiber_hash = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "fibermon_fiber_hash"), nil); if (! raw__ptypehash__is_type(cause, this__fibermon_fiber_hash)) {return f2larva__new(cause, 91, nil);}
  f2ptr this__index               = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "index"),               nil); if (! raw__integer__is_type(  cause, this__index))               {return f2larva__new(cause, 92, nil);}
  {
    f2ptr this__bytecodes_per_second = f2integer__new(cause, 0);
    f2ptr this__execution_efficiency = f2integer__new(cause, 0);
    ptypehash__value__iteration(cause, this__fibermon_fiber_hash, fibermon_fiber,
				f2ptr fiber_bytecodes_per_second = f2__frame__lookup_var_value(cause, fibermon_fiber, new__symbol(cause, "bytecodes_per_second"), nil);
				f2ptr fiber_execution_efficiency = f2__frame__lookup_var_value(cause, fibermon_fiber, new__symbol(cause, "execution_efficiency"), nil);
				if (fiber_bytecodes_per_second != nil) {
				  this__bytecodes_per_second = f2__number__plus(cause, this__bytecodes_per_second, fiber_bytecodes_per_second);
				}
				if (fiber_execution_efficiency != nil) {
				  this__execution_efficiency = f2__number__plus(cause, this__execution_efficiency, fiber_execution_efficiency);
				}
				);
    if (f2__number__is_less_than(cause, this__execution_efficiency, f2double__new(cause, 0.0)) != nil) {
      this__execution_efficiency = f2double__new(cause, 0.0);
    } else if (f2__number__is_greater_than(cause, this__execution_efficiency, f2double__new(cause, 1.0)) != nil) {
      this__execution_efficiency = f2double__new(cause, 1.0);
    }
    f2__frame__add_var_value(cause, this, new__symbol(cause, "bytecodes_per_second"), this__bytecodes_per_second);
    f2__frame__add_var_value(cause, this, new__symbol(cause, "execution_efficiency"), this__execution_efficiency);
  }
  f2ptr  this__total_global_memory  = assert_value(f2__system__memorypool__total_global_memory(cause, this__index));
  f2ptr  this__total_free_memory    = assert_value(f2__system__memorypool__total_free_memory(  cause, this__index));
  s64    this__total_free_memory__i = f2integer__i(this__total_free_memory, cause);
  f2ptr  this__total_used_memory    = assert_value(f2__number__minus(cause, this__total_global_memory, this__total_free_memory));
  f2ptr  maximum_block__byte_num    = assert_value(f2__memory__pool__maximum_block__byte_num(cause, this__index));
  s64    maximum_block__byte_num__i = f2integer__i(maximum_block__byte_num, cause);
  double this__fragmentation__d     = 1.0 - ((this__total_free_memory__i == 0) ? 0.0 : (((double)maximum_block__byte_num__i) / ((double)this__total_free_memory__i)));
  f2ptr  this__fragmentation        = f2double__new(cause, this__fragmentation__d);
  
  f2__frame__add_var_value(cause, this, new__symbol(cause, "total_used_memory"), this__total_used_memory);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "total_free_memory"), this__total_free_memory);
  f2__frame__add_var_value(cause, this, new__symbol(cause, "fragmentation"),     this__fragmentation);
  return nil;
}
export_cefunk1(fibermon_processor__recompute_statistics_fast, this, 0, "");



f2ptr f2__fibermon__core_extension__initialize(f2ptr cause) {
  printf("\nfibermon initialized."); fflush(stdout);
  return nil;
}
export_cefunk0(fibermon__core_extension__initialize, 0, "");

f2ptr f2__fibermon__core_extension__destroy(f2ptr cause) {
  printf("\nfibermon destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(fibermon__core_extension__destroy, 0, "");


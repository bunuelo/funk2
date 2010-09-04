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

f2ptr f2__fibermon__bytes__to_memory_string(f2ptr cause, f2ptr this) {
  f2ptr i = object__get_0(cause, this, "as-integer");
  if (! raw__integer__is_type(cause, i)) {
    if (raw__larva__is_type(cause, i)) {
      return i;
    }
    return f2larva__new(cause, 1, nil);
  }
  s64 i__i = f2integer__i(i, cause);
  if      (i__i <                                1024ull)  {return f2__exp__as__string(cause, i);}
  else if (i__i <                     (1024ull * 1024ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                             1024.0)),  new__string(cause, "k")));}
  else if (i__i <           (1024ull * 1024ull * 1024ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /                   (1024.0 * 1024.0))), new__string(cause, "M")));}
  else if (i__i < (1024ull * 1024ull * 1024ull * 1024ull)) {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i /          (1024.0 * 1024.0 * 1024.0))), new__string(cause, "G")));}
  else                                                     {return f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2double__new(cause, (double)i__i / (1024.0 * 1024.0 * 1024.0 * 1024.0))), new__string(cause, "T")));}
}
def_pcfunk1(fibermon__bytes__to_memory_string, this, return f2__fibermon__bytes__to_memory_string(this_cause, this));


f2ptr f2__fibermon__nanoseconds__to_time_string(f2ptr cause, f2ptr this) {
  f2ptr i = object__get_0(cause, this, "as-integer");
  if (! raw__integer__is_type(cause, i)) {
    if (raw__larva__is_type(cause, i)) {
      return i;
    }
    return f2larva__new(cause, 1, nil);
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
def_pcfunk1(fibermon__nanoseconds__to_time_string, this, return f2__fibermon__nanoseconds__to_time_string(this_cause, this));


f2ptr f2__fibermon_fiber__construct_fast(f2ptr cause, f2ptr this) {
  f2ptr this__frame                              = raw__gtk__frame__new(cause, new__string(cause, "fiber"));                                        f2__frame__add_var_value(cause, this, new__symbol(cause, "frame"),                              this__frame);
  f2ptr this__vbox                               = raw__gtk__vbox__new(cause, f2integer__new(cause, 2));                                            f2__frame__add_var_value(cause, this, new__symbol(cause, "vbox"),                               this__vbox);
  f2ptr this__menu_bar                           = raw__gtk__menu_bar__new(cause);                                                                  f2__frame__add_var_value(cause, this, new__symbol(cause, "menu_bar"),                           this__menu_bar);
  f2ptr this__command_menu_item                  = raw__gtk__menu_item__new(cause, new__string(cause, "Command"));                                  f2__frame__add_var_value(cause, this, new__symbol(cause, "command_menu_item"),                  this__command_menu_item);
  f2ptr this__command_menu                       = raw__gtk__menu__new(cause);                                                                      f2__frame__add_var_value(cause, this, new__symbol(cause, "command_menu"),                       this__command_menu);
  f2ptr this__command_pause_menu_item            = raw__gtk__menu_item__new(cause, new__string(cause, "Pause"));                                    f2__frame__add_var_value(cause, this, new__symbol(cause, "command_pause_menu_item"),            this__command_pause_menu_item);
  f2ptr this__command_continue_menu_item         = raw__gtk__menu_item__new(cause, new__string(cause, "Continue"));                                 f2__frame__add_var_value(cause, this, new__symbol(cause, "command_continue_menu_item"),         this__command_continue_menu_item);
  f2ptr this__command_keep_undead_menu_item      = raw__gtk__menu_item__new(cause, new__string(cause, "Keep Undead"));                              f2__frame__add_var_value(cause, this, new__symbol(cause, "command_keep_undead_menu_item"),      this__command_keep_undead_menu_item);
  f2ptr this__command_dont_keep_undead_menu_item = raw__gtk__menu_item__new(cause, new__string(cause, "Don't Keep Undead"));                        f2__frame__add_var_value(cause, this, new__symbol(cause, "command_dont_keep_undead_menu_item"), this__command_dont_keep_undead_menu_item);
  f2ptr this__command_quit_menu_item             = raw__gtk__menu_item__new(cause, new__string(cause, "Quit"));                                     f2__frame__add_var_value(cause, this, new__symbol(cause, "command_quit_menu_item"),             this__command_quit_menu_item);
  f2ptr this__view_menu_item                     = raw__gtk__menu_item__new(cause, new__string(cause, "View"));                                     f2__frame__add_var_value(cause, this, new__symbol(cause, "view_menu_item"),                     this__view_menu_item);
  f2ptr this__view_menu                          = raw__gtk__menu__new(cause);                                                                      f2__frame__add_var_value(cause, this, new__symbol(cause, "view_menu"),                          this__view_menu);
  f2ptr this__view_print_to_screen_menu_item     = raw__gtk__menu_item__new(cause, new__string(cause, "Print to Screen"));                          f2__frame__add_var_value(cause, this, new__symbol(cause, "view_print_to_screen_menu_item"),     this__view_print_to_screen_menu_item);
  f2ptr this__view_stack_trace_menu_item         = raw__gtk__menu_item__new(cause, new__string(cause, "Stack Trace"));                              f2__frame__add_var_value(cause, this, new__symbol(cause, "view_stack_trace_menu_item"),         this__view_stack_trace_menu_item);
  f2ptr this__hbox                               = raw__gtk__hbox__new(cause, f2integer__new(cause, 2));                                            f2__frame__add_var_value(cause, this, new__symbol(cause, "hbox"),                               this__hbox);
  f2ptr this__progress_bar                       = raw__gtk__progress_bar__new(cause);                                                              f2__frame__add_var_value(cause, this, new__symbol(cause, "progress_bar"),                       this__progress_bar);
  f2ptr this__table                              = raw__gtk__table__new(cause, f2integer__new(cause, 12), f2integer__new(cause, 2), nil);           f2__frame__add_var_value(cause, this, new__symbol(cause, "table"),                              this__table);
  f2ptr this__table_labels                       = f2__array__new(cause, f2list2__new(cause, f2integer__new(cause, 12), f2integer__new(cause, 2))); f2__frame__add_var_value(cause, this, new__symbol(cause, "table_labels"),                       this__table_labels);
  
  raw__gtk__menu__append(cause, this__command_menu, this__command_pause_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_continue_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_keep_undead_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_dont_keep_undead_menu_item);
  raw__gtk__menu__append(cause, this__command_menu, this__command_quit_menu_item);
  
  raw__gtk__menu_bar__append(cause, this__menu_bar, this__command_menu_item);
  raw__gtk__menu_item__set_submenu(cause, this__command_menu_item, this__command_menu);
  
  raw__gtk__menu__append(cause, this__view_menu, this__view_print_to_screen_menu_item);
  raw__gtk__menu__append(cause, this__view_menu, this__view_stack_trace_menu_item);
  
  raw__gtk__menu_bar__append(cause, this__menu_bar, this__view_menu_item);
  raw__gtk__menu_item__set_submenu(cause, this__view_menu_item, this__view_menu);
  
  raw__gtk__progress_bar__set_orientation(cause, this__progress_bar, new__symbol(cause, "bottom_to_top"));
  
  {
    u64 row;
    for (row = 0; row < 12; row ++) {
      f2ptr row_labels = raw__array__elt(cause, this__table_labels, row);
      {
	u64 column;
	for (column = 0; column < 2; column ++) {
	  f2ptr table_label = raw__gtk__label__new(cause, new__string(cause, ""));
	  raw__gtk__misc__set_alignment(cause, table_label, f2double__new(cause, 0.0), f2double__new(cause, 0.0));
	  raw__array__elt__set(cause, row_labels, column, table_label);
	  raw__gtk__table__attach(cause, this__table, table_label, f2integer__new(cause, column), f2integer__new(cause, column + 1), f2integer__new(cause, row), f2integer__new(cause, row + 1), f2integer__new(cause, 0), f2integer__new(cause, 0));

	  // [have table attach table_label column [+ column 1] row [+ row 1] 0 0]]]]]

	}
      }
    }
  }
  
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  0), 0), new__string(cause, "cause-name"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  1), 0), new__string(cause, "keep_undead"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  2), 0), new__string(cause, "is_zombie"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  3), 0), new__string(cause, "is_complete"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  4), 0), new__string(cause, "execute_mutex"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  5), 0), new__string(cause, "paused"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  6), 0), new__string(cause, "last_executed_time"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  7), 0), new__string(cause, "sleep_until_time"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  8), 0), new__string(cause, "execution_time"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  9), 0), new__string(cause, "bytecode_count"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 10), 0), new__string(cause, "bytecodes_per_second"));
  raw__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 11), 0), new__string(cause, "execution_efficiency"));
  
  raw__gtk__box__pack_start(cause, this__hbox, this__progress_bar, nil, nil, f2integer__new(cause, 0));
  raw__gtk__box__pack_start(cause, this__hbox, this__table,        f2bool__new(boolean__true), f2bool__new(boolean__true), f2integer__new(cause, 0));
  raw__gtk__box__pack_start(cause, this__vbox, this__menu_bar,     nil, nil, f2integer__new(cause, 0));
  raw__gtk__box__pack_start(cause, this__vbox, this__hbox,         f2bool__new(boolean__true), f2bool__new(boolean__true), f2integer__new(cause, 0));
  
  raw__gtk__container__add(cause, this__frame, this__vbox);
  
  return this;
}
def_pcfunk1(fibermon_fiber__construct_fast, this, return f2__fibermon_fiber__construct_fast(this_cause, this));


f2ptr f2__fibermon_fiber__redraw_fast(f2ptr cause, f2ptr this) {
  f2ptr this__fiber                 = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "fiber"),                 nil); if (raw__fiber__is_type(cause, this__fiber)) {return f2larva__new(cause, 1, nil);}
  f2ptr this__progress_bar          = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "progress_bar"),          nil); if (! this__progress_bar)                    {return f2larva__new(cause, 1, nil);}
  f2ptr this__execution_efficiency  = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "execution_efficiency"),  nil); if (! this__execution_efficiency)            {return f2larva__new(cause, 1, nil);}
  f2ptr this__execution_nanoseconds = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "execution_nanoseconds"), nil); if (! this__execution_nanoseconds)           {return f2larva__new(cause, 1, nil);}
  f2ptr this__bytecode_count        = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bytecode_count"),        nil); if (! this__bytecode_count)                  {return f2larva__new(cause, 1, nil);}
  f2ptr this__bytecodes_per_second  = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bytecodes_per_second"),  nil); if (! this__bytecodes_per_second)            {return f2larva__new(cause, 1, nil);}
  f2__gtk__progress_bar__set_fraction(cause, this__progress_bar, (this__execution_efficiency != nil) ? this__execution_efficiency : f2integer__new(cause, 0));
  
  {
    f2ptr this__table_labels = f2__frame__lookup_var_value(cause, this, new__symbol(cause, "table_labels"), nil); if (! this__table_labels) {return f2larva__new(cause, 1, nil);}
    
    {
      f2ptr cause_reg          = f2fiber__cause_reg(this__fiber, cause);
      f2ptr cause__name__value = raw__cause__is_type(cause, cause_reg) ? f2__cause__lookup(cause, cause_reg, new__symbol(cause, "cause-name")) : nil;
      f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  0), 1), f2__exp__as__string(cause, cause__name__value));
    }
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  1), 1), (f2fiber__keep_undead(this__fiber, cause) != nil) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  2), 1), (f2fiber__is_zombie(  this__fiber, cause) != nil) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  3), 1), raw__fiber__is_complete(cause, this__fiber) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  4), 1), f2__exp__as__string(cause, f2fiber__execute_mutex(this__fiber, cause)));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  5), 1), (f2fiber__paused(     this__fiber, cause) != nil) ? new__string(cause, "Yes") : new__string(cause, "No"));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  6), 1), f2__exp__as__string(cause, f2fiber__last_executed_time(this__fiber, cause)));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  7), 1), f2__exp__as__string(cause, f2fiber__sleep_until_time(this__fiber, cause)));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  8), 1), f2__fibermon__nanoseconds__to_time_string(cause, ((this__execution_nanoseconds != nil) ? this__execution_nanoseconds : f2integer__new(cause, 0))));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels,  9), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__bytecode_count != nil) ? this__bytecode_count : f2integer__new(cause, 0))),
																			  new__string(cause, "Bc"))));
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 10), 1), f2__stringlist__concat(cause, f2list2__new(cause, f2__fibermon__bytes__to_memory_string(cause, ((this__bytecodes_per_second != nil) ? this__bytecodes_per_second : f2integer__new(cause, 0))),
																			  new__string(cause, "Bc/s"))));
    
    f2__gtk__label__set_text(cause, raw__array__elt(cause, raw__array__elt(cause, this__table_labels, 11), 1),
			     f2__stringlist__concat(cause, f2list2__new(cause, f2__exp__as__string(cause, f2__number__multiplied_by(cause, ((this__bytecodes_per_second != nil) ? this__bytecodes_per_second : f2integer__new(cause, 0)), f2double__new(cause, 100.0))),
									new__string(cause, "%"))));
  }
  return nil;
}


// **

void f2__application__fibermon__reinitialize_globalvars() {
}

void f2__application__fibermon__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "application-fibermon", "", &f2__application__fibermon__reinitialize_globalvars);
  
  f2__application__fibermon__reinitialize_globalvars();
  
  f2__primcfunk__init__1(fibermon__bytes__to_memory_string,     this, "");
  f2__primcfunk__init__1(fibermon__nanoseconds__to_time_string, this, "");
  f2__primcfunk__init__1(fibermon_fiber__construct_fast,        this, "");
  f2__primcfunk__init__1(fibermon_fiber__redraw_fast,           this, "");
  
}


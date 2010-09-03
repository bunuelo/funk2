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

f2ptr f2__fibermon_fiber__construct_fast(f2ptr cause, f2ptr this) {
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "frame"),                              raw__gtk__frame__new(cause, new__string(cause, "fiber")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "vbox"),                               raw__gtk__vbox__new(cause, f2integer__new(cause, 2)));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "menu_bar"),                           raw__gtk__menu_bar__new(cause));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_menu_item"),                  raw__gtk__menu_item__new(cause, new__string(cause, "Command")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_menu"),                       raw__gtk__menu__new(cause));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_pause_menu_item"),            raw__gtk__menu_item__new(cause, new__string(cause, "Pause")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_continue_menu_item"),         raw__gtk__menu_item__new(cause, new__string(cause, "Continue")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_keep_undead_menu_item"),      raw__gtk__menu_item__new(cause, new__string(cause, "Keep Undead")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_dont_keep_undead_menu_item"), raw__gtk__menu_item__new(cause, new__string(cause, "Don't Keep Undead")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "command_quit_menu_item"),             raw__gtk__menu_item__new(cause, new__string(cause, "Quit")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "view_menu_item"),                     raw__gtk__menu_item__new(cause, new__string(cause, "View")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "view_menu"),                          raw__gtk__menu__new(cause));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "view_print_to_screen_menu_item"),     raw__gtk__menu_item__new(cause, new__string(cause, "Print to Screen")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "view_stack_trace_menu_item"),         raw__gtk__menu_item__new(cause, new__string(cause, "Stack Trace")));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "hbox"),                               raw__gtk__hbox__new(cause, f2integer__new(cause, 2)));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "progress_bar"),                       raw__gtk__progress_bar__new(cause));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "table"),                              raw__gtk__table__new(cause, f2integer__new(cause, 12), f2integer__new(cause, 2), nil));
  f2__fiber__add_var_value(cause, this, new__symbol(cause, "table_labels"),                       f2__array__new(cause, f2list2__new(f2integer__new(cause, 12), f2integer__new(cause, 2))));
  return this;
}


// **

void f2__application__fibermon__reinitialize_globalvars() {
}

void f2__application__fibermon__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "application-fibermon", "", &f2__application__fibermon__reinitialize_globalvars);
  
  f2__application__fibermon__reinitialize_globalvars();
  
  f2__primcfunk__init__1(fibermon_fiber__construct_fast, this, "");
  
}


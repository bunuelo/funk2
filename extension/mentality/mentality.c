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

#include "../../c/funk2.h"
#include "mentality.h"


// mentality_project

def_ceframe2(mentality, mentality_project, width, height);

f2ptr f2__mentality_project__new(f2ptr cause) {
  return f2mentality_project__new(cause, nil, nil);
}
export_cefunk0(mentality_project__new, 0, "Returns a new mentality_project object.");


// mentality_main_window

def_ceframe11(mentality, mentality_main_window,
	      mentality,
	      main_window,
	      menu_bar_vbox,
	      menu_bar,
	      file_menu_item,
	      file_menu,
	      file_new_project_menu_item,
	      file_open_project_menu_item,
	      file_close_project_menu_item,
	      file_save_project_menu_item,
	      file_exit_menu_item);

f2ptr f2__mentality_main_window__new(f2ptr cause, f2ptr mentality) {
  f2ptr main_window                  = f2__gtk__window__new(cause);
  f2ptr menu_bar_vbox                = f2__gtk__vbox__new(cause, f2integer__new(cause, 0));
  f2ptr menu_bar                     = f2__gtk__menu_bar__new(cause);
  f2ptr file_menu_item               = f2__gtk__menu_item__new(cause, new__string(cause, "File"));
  f2ptr file_menu                    = f2__gtk__menu__new(cause);
  f2ptr file_new_project_menu_item   = f2__gtk__menu_item__new(cause, new__string(cause, "New Project..."));
  f2ptr file_open_project_menu_item  = f2__gtk__menu_item__new(cause, new__string(cause, "Open Project..."));
  f2ptr file_close_project_menu_item = f2__gtk__menu_item__new(cause, new__string(cause, "Close Project..."));
  f2ptr file_save_project_menu_item  = f2__gtk__menu_item__new(cause, new__string(cause, "Save Project..."));
  f2ptr file_exit_menu_item          = f2__gtk__menu_item__new(cause, new__string(cause, "Exit"));
  
  // main_window
  f2__gtk__window__set_title(cause, main_window, new__string(cause, "Mentality"));
  f2__gtk__window__set_default_size(cause, main_window, f2integer__new(cause, 800), f2integer__new(cause, 600));
  f2__gtk__widget__connect_hide_on_delete(cause, main_window);
  
  // menu_bar_vbox
  f2__gtk__container__add(cause, main_window, menu_bar_vbox);
  
  // menu_bar
  f2__gtk__box__pack_start(cause, menu_bar_vbox, menu_bar, nil, nil, f2integer__new(cause, 0));
  
  // file_menu_item
  f2__gtk__menu_bar__append(cause, menu_bar, file_menu_item);
  
  // file_menu
  f2__gtk__menu_item__set_submenu(cause, file_menu_item, file_menu);
  
  // file_new_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_new_project_menu_item);
  
  // file_open_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_open_project_menu_item);
  
  // file_close_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_close_project_menu_item);
  
  // file_save_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_save_project_menu_item);
  
  // file_exit_menu_item
  f2__gtk__menu__append(cause, file_menu, file_exit_menu_item);
  
  
  f2__gtk__widget__show_all(cause, main_window);
  
  return f2mentality_main_window__new(cause,
				      mentality,
				      main_window,
				      menu_bar_vbox,
				      menu_bar,
				      file_menu_item,
				      file_menu,
				      file_new_project_menu_item,
				      file_open_project_menu_item,
				      file_close_project_menu_item,
				      file_save_project_menu_item,
				      file_exit_menu_item);
}
export_cefunk1(mentality_main_window__new, mentality, 0, "Given a mentality object, returns a new mentality_main_window object.");


// mentality

def_ceframe2(mentality, mentality,
	     mentality_main_window,
	     current_project);

f2ptr f2__mentality__new(f2ptr cause) {
  f2ptr mentality_main_window = nil;
  f2ptr current_project       = nil;
  f2ptr this                  = f2mentality__new(cause, mentality_main_window, current_project);
  mentality_main_window = f2__mentality_main_window__new(cause, this);
  raw__mentality__mentality_main_window__set(cause, this, mentality_main_window);
  return this;
}
export_cefunk0(mentality__new, 0, "Returns a new mentality object.");


// **

f2ptr f2__mentality__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(mentality__core_extension_ping, 0, "");

f2ptr f2__mentality__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "mentality_project"),     f2__mentality_project_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality_main_window"), f2__mentality_main_window_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality"),             f2__mentality_type__new(cause));
  status("mentality initialized.");
  return nil;
}
export_cefunk0(mentality__core_extension_initialize, 0, "");

f2ptr f2__mentality__core_extension_destroy(f2ptr cause) {
  status("mentality destroyed.");
  return nil;
}
export_cefunk0(mentality__core_extension_destroy, 0, "");



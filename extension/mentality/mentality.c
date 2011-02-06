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

#include "../../c/funk2.h"
#include "mentality.h"


// mentality_project_widget

def_ceframe2(mentality, mentality_project_widget, project, label);

f2ptr f2__mentality_project_widget__new(f2ptr cause, f2ptr project) {
  f2ptr label = f2__gtk__label__new(cause, new__string(cause, "Mentality Project"));
  f2__gtk__widget__show_all(cause, label);
  return f2mentality_project_widget__new(cause, project, label);
}
export_cefunk1(mentality_project_widget__new, project, 0, "Given a mentality_project, returns a new mentality_project_widget object.");

f2ptr raw__mentality_project_widget__gtk_widget(f2ptr cause, f2ptr this) {
  return raw__mentality_project_widget__label(cause, this);
}

f2ptr f2__mentality_project_widget__gtk_widget(f2ptr cause, f2ptr this) {
  if (! raw__mentality_project_widget__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_project_widget__gtk_widget(cause, this);
}
export_cefunk1(mentality_project_widget__gtk_widget, this, 0, "");


// mentality_project

def_ceframe3(mentality, mentality_project, widget, width, height);

f2ptr f2__mentality_project__new(f2ptr cause) {
  f2ptr this   = f2mentality_project__new(cause, nil, nil, nil);
  f2ptr widget = f2__mentality_project_widget__new(cause, this);
  f2__mentality_project__widget__set(cause, this, widget);
  return this;
}
export_cefunk0(mentality_project__new, 0, "Returns a new mentality_project object.");


// mentality_main_window

def_ceframe13(mentality, mentality_main_window,
	      mentality,
	      window,
	      menu_bar_vbox,
	      menu_bar,
	      file_menu_item,
	      file_menu,
	      file_new_project_menu_item,
	      file_open_project_menu_item,
	      file_close_project_menu_item,
	      file_save_project_menu_item,
	      file_exit_menu_item,
	      project_scrolled_window,
	      waiting_for_modal_child);

f2ptr f2__mentality_main_window__new(f2ptr cause, f2ptr mentality) {
  f2ptr window                       = f2__gtk__window__new(cause);
  f2ptr menu_bar_vbox                = f2__gtk__vbox__new(cause, f2integer__new(cause, 0));
  f2ptr menu_bar                     = f2__gtk__menu_bar__new(cause);
  f2ptr file_menu_item               = f2__gtk__menu_item__new(cause, new__string(cause, "File"));
  f2ptr file_menu                    = f2__gtk__menu__new(cause);
  f2ptr file_new_project_menu_item   = f2__gtk__menu_item__new(cause, new__string(cause, "New Project..."));
  f2ptr file_open_project_menu_item  = f2__gtk__menu_item__new(cause, new__string(cause, "Open Project..."));
  f2ptr file_close_project_menu_item = f2__gtk__menu_item__new(cause, new__string(cause, "Close Project..."));
  f2ptr file_save_project_menu_item  = f2__gtk__menu_item__new(cause, new__string(cause, "Save Project..."));
  f2ptr file_exit_menu_item          = f2__gtk__menu_item__new(cause, new__string(cause, "Exit"));
  f2ptr project_scrolled_window      = f2__gtk__scrolled_window__new(cause);
  f2ptr waiting_for_modal_child      = nil;
  
  // window
  f2__gtk__window__set_title(cause, window, new__string(cause, "Mentality"));
  f2__gtk__window__set_default_size(cause, window, f2integer__new(cause, 800), f2integer__new(cause, 600));
  f2__gtk__widget__connect_hide_on_delete(cause, window);
  
  // menu_bar_vbox
  f2__gtk__container__add(cause, window, menu_bar_vbox);
  
  // menu_bar
  f2__gtk__box__pack_start(cause, menu_bar_vbox, menu_bar, nil, nil, f2integer__new(cause, 0));
  
  // file_menu_item
  f2__gtk__menu_bar__append(cause, menu_bar, file_menu_item);
  
  // file_menu
  f2__gtk__menu_item__set_submenu(cause, file_menu_item, file_menu);
  
  // file_new_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_new_project_menu_item);
  f2__gtk__signal_connect(cause, file_new_project_menu_item, new__string(cause, "activate"),
                          new__core_extension_funk(cause, mentality, mentality__user_command__new_project),
			  f2list1__new(cause, mentality));
  
  // file_open_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_open_project_menu_item);
  f2__gtk__signal_connect(cause, file_open_project_menu_item, new__string(cause, "activate"),
                          new__core_extension_funk(cause, mentality, mentality__user_command__open_project),
			  f2list1__new(cause, mentality));
  
  // file_close_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_close_project_menu_item);
  f2__gtk__signal_connect(cause, file_close_project_menu_item, new__string(cause, "activate"),
  			  new__core_extension_funk(cause, mentality, mentality__user_command__close_project),
			  f2list1__new(cause, mentality));
  
  // file_save_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_save_project_menu_item);
  f2__gtk__signal_connect(cause, file_save_project_menu_item, new__string(cause, "activate"),
  			  new__core_extension_funk(cause, mentality, mentality__user_command__save_project),
			  f2list1__new(cause, mentality));
  
  // file_exit_menu_item
  f2__gtk__menu__append(cause, file_menu, file_exit_menu_item);
  f2__gtk__signal_connect(cause, file_exit_menu_item, new__string(cause, "activate"),
  			  new__core_extension_funk(cause, mentality, mentality__user_command__exit),
			  f2list1__new(cause, mentality));
  
  // project_scrolled_window
  f2__gtk__box__pack_start(cause, menu_bar_vbox, project_scrolled_window, f2bool__new(boolean__true), f2bool__new(boolean__true), f2integer__new(cause, 0));
  
  
  f2__gtk__widget__show_all(cause, window);
  
  return f2mentality_main_window__new(cause,
				      mentality,
				      window,
				      menu_bar_vbox,
				      menu_bar,
				      file_menu_item,
				      file_menu,
				      file_new_project_menu_item,
				      file_open_project_menu_item,
				      file_close_project_menu_item,
				      file_save_project_menu_item,
				      file_exit_menu_item,
				      project_scrolled_window,
				      waiting_for_modal_child);
}
export_cefunk1(mentality_main_window__new, mentality, 0, "Given a mentality object, returns a new mentality_main_window object.");


f2ptr raw__mentality_main_window__destroy(f2ptr cause, f2ptr this) {
  f2ptr window = raw__mentality_main_window__window(cause, this);
  return f2__gtk__widget__destroy(cause, window);
}

f2ptr f2__mentality_main_window__destroy(f2ptr cause, f2ptr this) {
  if (! raw__mentality_main_window__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_main_window__destroy(cause, this);
}
export_cefunk1(mentality_main_window__destroy, this, 0, "Destroys the main mentality window.");


f2ptr raw__mentality_main_window__project__set(f2ptr cause, f2ptr this, f2ptr project) {
  f2ptr project_scrolled_window     = raw__mentality_main_window__project_scrolled_window(cause, this);
  f2ptr project__widget             = f2__mentality_project__widget(cause, project);
  f2ptr project__widget__gtk_widget = f2__mentality_project_widget__gtk_widget(cause, project__widget);
  return f2__gtk__scrolled_window__add_with_viewport(cause, project_scrolled_window, project__widget__gtk_widget);
}

f2ptr f2__mentality_main_window__project__set(f2ptr cause, f2ptr this, f2ptr project) {
  if ((! raw__mentality_main_window__is_type(cause, this)) ||
      (! raw__mentality_project__is_type(cause, project))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_main_window__project__set(cause, this, project);
}
export_cefunk2(mentality_main_window__project__set, this, project, 0, "");



// mentality

def_ceframe2(mentality, mentality,
	     main_window,
	     current_project);

f2ptr f2__mentality__new(f2ptr cause) {
  f2ptr main_window     = nil;
  f2ptr current_project = nil;
  f2ptr this            = f2mentality__new(cause, main_window, current_project);
  main_window           = f2__mentality_main_window__new(cause, this);
  raw__mentality__main_window__set(cause, this, main_window);
  return this;
}
export_cefunk0(mentality__new, 0, "Returns a new mentality object.");


f2ptr raw__mentality__user_command__new_project(f2ptr cause, f2ptr this) {
  f2ptr main_window = f2__mentality__main_window(cause, this);
  f2ptr project = f2__mentality_project__new(cause);
  f2__mentality__current_project__set(cause, this, project);
  f2__mentality_main_window__project__set(cause, main_window, project);
  printf("\nyup.  new project."); fflush(stdout);
  return nil;
}

f2ptr f2__mentality__user_command__new_project(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__user_command__new_project(cause, this);
}
export_cefunk1(mentality__user_command__new_project, this, 0, "");


f2ptr raw__mentality__user_command__open_project(f2ptr cause, f2ptr this) {
  printf("\nyup.  open project."); fflush(stdout);
  return nil;
}

f2ptr f2__mentality__user_command__open_project(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__user_command__open_project(cause, this);
}
export_cefunk1(mentality__user_command__open_project, this, 0, "");


f2ptr raw__mentality__user_command__close_project(f2ptr cause, f2ptr this) {
  printf("\nyup.  close project."); fflush(stdout);
  return nil;
}

f2ptr f2__mentality__user_command__close_project(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__user_command__close_project(cause, this);
}
export_cefunk1(mentality__user_command__close_project, this, 0, "");


f2ptr raw__mentality__user_command__save_project(f2ptr cause, f2ptr this) {
  printf("\nyup.  save project."); fflush(stdout);
  return nil;
}

f2ptr f2__mentality__user_command__save_project(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__user_command__save_project(cause, this);
}
export_cefunk1(mentality__user_command__save_project, this, 0, "");


f2ptr raw__mentality__user_command__exit(f2ptr cause, f2ptr this) {
  f2ptr main_window = f2__mentality__main_window(cause, this);
  f2__mentality_main_window__destroy(cause, main_window);
  return nil;
}

f2ptr f2__mentality__user_command__exit(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__user_command__exit(cause, this);
}
export_cefunk1(mentality__user_command__exit, this, 0, "");



f2ptr f2__mentality_type__new_aux(f2ptr cause) {
  f2ptr this = f2__mentality_type__new(cause);
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "user_command-new_project"),   f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__user_command__new_project")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "user_command-open_project"),  f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__user_command__open_project")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "user_command-close_project"), f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__user_command__close_project")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "user_command-save_project"),  f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__user_command__save_project")));}
  {f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "user_command-exit"),          f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__user_command__exit")));}
  return this;
}

// **

f2ptr f2__mentality__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(mentality__core_extension__ping, 0, "");

f2ptr f2__mentality__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "mentality_project_widget"), f2__mentality_project_widget_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality_project"),        f2__mentality_project_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality_main_window"),    f2__mentality_main_window_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality"),                f2__mentality_type__new_aux(cause));
  status("mentality initialized.");
  return nil;
}
export_cefunk0(mentality__core_extension__initialize, 0, "");

f2ptr f2__mentality__core_extension__destroy(f2ptr cause) {
  status("mentality destroyed.");
  return nil;
}
export_cefunk0(mentality__core_extension__destroy, 0, "");



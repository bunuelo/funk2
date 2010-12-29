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

f2ptr raw__mentality_project__new(f2ptr cause, f2ptr width) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),  new__symbol(cause, "mentality_project"),
					    new__symbol(cause, "width"), width));
}

f2ptr f2__mentality_project__new(f2ptr cause, f2ptr width) {
  if (! raw__integer__is_type(cause, width)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_project__new(cause, width);
}
export_cefunk1(mentality_project__new, width, 0, "Returns a new mentality_project object.");


boolean_t raw__mentality_project__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "mentality_project");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__mentality_project__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__mentality_project__is_type(cause, thing));
}
export_cefunk1(mentality_project__is_type, thing, 0, "Returns whether or not thing is of type mentality_project.");


f2ptr raw__mentality_project__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__mentality_project__type(f2ptr cause, f2ptr this) {
  if (! raw__mentality_project__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_project__type(cause, this);
}
export_cefunk1(mentality_project__type, thing, 0, "Returns the specific type of object that this mentality_project is.");


f2ptr raw__mentality_project__width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil);
}

f2ptr f2__mentality_project__width(f2ptr cause, f2ptr this) {
  if (! raw__mentality_project__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_project__width(cause, this);
}
export_cefunk1(mentality_project__width, thing, 0, "Returns the width of the mentality_project.");


f2ptr raw__mentality_project__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "width"), value);
}

f2ptr f2__mentality_project__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__mentality_project__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality_project__width__set(cause, this, value);
}
export_cefunk2(mentality_project__width__set, thing, value, 0, "Sets the width of the mentality_project.");


f2ptr f2__mentality_project_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),     f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality_project__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"), f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality_project__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),    f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality_project__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),   f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality_project__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "width"),   f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality_project__width__set")));}
  return this;
}


// mentality

f2ptr raw__mentality__new(f2ptr cause,
			  f2ptr main_window,
			  f2ptr menu_bar_vbox,
			  f2ptr menu_bar,
			  f2ptr file_menu_item,
			  f2ptr file_menu,
			  f2ptr file_open_project_menu_item,
			  f2ptr file_close_project_menu_item,
			  f2ptr file_save_project_menu_item,
			  f2ptr file_exit_menu_item,
			  f2ptr current_project) {
  return f2__frame__new(cause, f2list22__new(cause,
					     new__symbol(cause, "type"),                         new__symbol(cause, "mentality"),
					     new__symbol(cause, "main_window"),                  main_window,
					     new__symbol(cause, "menu_bar_vbox"),                menu_bar_vbox,
					     new__symbol(cause, "menu_bar"),                     menu_bar,
					     new__symbol(cause, "file_menu_item"),               file_menu_item,
					     new__symbol(cause, "file_menu"),                    file_menu,
					     new__symbol(cause, "file_open_project_menu_item"),  file_open_project_menu_item,
					     new__symbol(cause, "file_close_project_menu_item"), file_close_project_menu_item,
					     new__symbol(cause, "file_save_project_menu_item"),  file_save_project_menu_item,
					     new__symbol(cause, "file_exit_menu_item"),          file_exit_menu_item,
					     new__symbol(cause, "current_project"),              current_project));
}

f2ptr f2__mentality__new(f2ptr cause) {
  f2ptr main_window                  = f2__gtk__window__new(cause);
  f2ptr menu_bar_vbox                = f2__gtk__vbox__new(cause, f2integer__new(cause, 0));
  f2ptr menu_bar                     = f2__gtk__menu_bar__new(cause);
  f2ptr file_menu_item               = f2__gtk__menu_item__new(cause, new__string(cause, "File"));
  f2ptr file_menu                    = f2__gtk__menu__new(cause);
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
  
  // file_open_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_open_project_menu_item);
  
  // file_close_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_close_project_menu_item);
  
  // file_save_project_menu_item
  f2__gtk__menu__append(cause, file_menu, file_save_project_menu_item);
  
  // file_exit_menu_item
  f2__gtk__menu__append(cause, file_menu, file_exit_menu_item);
  
  
  f2__gtk__widget__show_all(cause, main_window);
  
  f2ptr current_project = nil;
  return raw__mentality__new(cause,
			     main_window,
			     menu_bar_vbox,
			     menu_bar,
			     file_menu_item,
			     file_menu,
			     file_open_project_menu_item,
			     file_close_project_menu_item,
			     file_save_project_menu_item,
			     file_exit_menu_item,
			     current_project);
}
export_cefunk0(mentality__new, 0, "Returns a new mentality object.");


boolean_t raw__mentality__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "mentality");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__mentality__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__mentality__is_type(cause, thing));
}
export_cefunk1(mentality__is_type, thing, 0, "Returns whether or not thing is of type mentality.");


f2ptr raw__mentality__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__mentality__type(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__type(cause, this);
}
export_cefunk1(mentality__type, thing, 0, "Returns the specific type of object that this mentality is.");


f2ptr raw__mentality__main_window(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "main_window"), nil);
}

f2ptr f2__mentality__main_window(f2ptr cause, f2ptr this) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__main_window(cause, this);
}
export_cefunk1(mentality__main_window, thing, 0, "Returns the main_window of the mentality.");


f2ptr raw__mentality__main_window__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "main_window"), value);
}

f2ptr f2__mentality__main_window__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__mentality__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__mentality__main_window__set(cause, this, value);
}
export_cefunk2(mentality__main_window__set, thing, value, 0, "Sets the main_window of the mentality.");


f2ptr f2__mentality_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),         f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "main_window"), f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__main_window")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "main_window"), f2__core_extension_funk__new(cause, new__symbol(cause, "mentality"), new__symbol(cause, "mentality__main_window__set")));}
  return this;
}



// **

f2ptr f2__mentality__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(mentality__core_extension_ping, 0, "");

f2ptr f2__mentality__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "mentality_project"), f2__mentality_project_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "mentality"),         f2__mentality_type__new(cause));
  status("mentality initialized.");
  return nil;
}
export_cefunk0(mentality__core_extension_initialize, 0, "");

f2ptr f2__mentality__core_extension_destroy(f2ptr cause) {
  status("mentality destroyed.");
  return nil;
}
export_cefunk0(mentality__core_extension_destroy, 0, "");



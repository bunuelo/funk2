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

#if defined(F2__GTK__SUPPORTED)


// funk2_gtk_widget

void funk2_gtk_widget__init(funk2_gtk_widget_t* this, u8* name, GtkWidget* gtk_widget) {
  u64 name__length = strlen((char*)name);
  this->name = (u8*)from_ptr(f2__malloc(name__length));
  memcpy(this->name, name, name__length + 1);
  this->gtk_widget = gtk_widget;
}

void funk2_gtk_widget__destroy(funk2_gtk_widget_t* this) {
  f2__free(to_ptr(this->name));
}


// funk2_gtk

void funk2_gtk__thread__start_function(funk2_gtk_t* this) {
  funk2_processor_mutex__lock(&(this->main_thread__mutex));
  if (this->main_thread__active) {
    funk2_processor_mutex__unlock(&(this->main_thread__mutex));
    status("funk2_gtk__thread__start_function warning: NOT beginning processor_thread because already active.");
    return;
  }
  this->main_thread__active = boolean__true;
  funk2_processor_mutex__unlock(&(this->main_thread__mutex));
  
  status("funk2_gtk__thread__start_function status: beginning processor_thread.");
  status("funk2_gtk__thread__start_function status: calling gtk_main().");
  {
    gdk_threads_enter();
    gtk_main();
    gdk_threads_leave();
  }
  status("funk2_gtk__thread__start_function status: returned from gtk_main().");
  status("funk2_gtk__thread__start_function status: ending processor_thread.");
  
  funk2_processor_mutex__lock(&(this->main_thread__mutex));
  this->main_thread__active = boolean__false;
  funk2_processor_mutex__unlock(&(this->main_thread__mutex));
}

void* funk2_gtk__thread__start_function__helper(void* ptr) {
  funk2_gtk_t* this = (funk2_gtk_t*)ptr;
  funk2_gtk__thread__start_function(this);
  return NULL;
}

void funk2_gtk__init(funk2_gtk_t* this, int* argv, char*** argc) {
  g_thread_init(NULL);
  gdk_threads_init();
  gtk_init(argv, argc);
  
  this->widgets = NULL;
  
  funk2_processor_mutex__init(&(this->main_thread__mutex));
  this->main_thread__active = boolean__false;
  this->main_thread         = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), &funk2_gtk__thread__start_function__helper, (void*)this);
}

void funk2_gtk__destroy(funk2_gtk_t* this) {
  funk2_processor_mutex__destroy(&(this->main_thread__mutex));
}

void funk2_gtk__add_widget(funk2_gtk_t* this, funk2_gtk_widget_t* widget) {
  funk2_gtk_widget_cons_t* cons = (funk2_gtk_widget_cons_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_widget_cons_t)));
  cons->widget = widget;
  cons->next   = this->widgets;
  this->widgets = cons;
}

funk2_gtk_widget_t* funk2_gtk__lookup_widget(funk2_gtk_t* this, u8* name) {
  funk2_gtk_widget_cons_t* iter = this->widgets;
  while (iter) {
    funk2_gtk_widget_t* widget = iter->widget;
    if (strcmp((char*)(widget->name), (char*)name) == 0) {
      return widget;
    }
    iter = iter->next;
  }
  return NULL;
}

funk2_gtk_widget_t* funk2_gtk__window__new(funk2_gtk_t* this, u8* name) {
  GtkWidget* window = NULL;
  {
    gdk_threads_enter();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gdk_threads_leave();
  }
  funk2_gtk_widget_t* widget = (funk2_gtk_widget_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_widget_t)));
  funk2_gtk_widget__init(widget, name, window);
  funk2_gtk__add_widget(this, widget);
  return widget;
}

funk2_gtk_widget_t* funk2_gtk__vbox__new(funk2_gtk_t* this, u8* name, int row_count) {
  GtkWidget* vbox = NULL;
  {
    gdk_threads_enter();
    vbox = gtk_vbox_new(FALSE, row_count);
    gdk_threads_leave();
  }
  funk2_gtk_widget_t* widget = (funk2_gtk_widget_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_widget_t)));
  funk2_gtk_widget__init(widget, name, vbox);
  funk2_gtk__add_widget(this, widget);
  return widget;
}

funk2_gtk_widget_t* funk2_gtk__container__add(funk2_gtk_t* this, u8* name, u8* add_name) {
  funk2_gtk_widget_t* widget = funk2_gtk__lookup_widget(this, name);
  if (! widget) {
    return NULL;
  }
  funk2_gtk_widget_t* add_widget = funk2_gtk__lookup_widget(this, add_name);
  if (! add_widget) {
    return NULL;
  }
  {
    gdk_threads_enter();
    gtk_container_add(GTK_CONTAINER(widget->gtk_widget), add_widget->gtk_widget);
    gdk_threads_leave();
  }
  return widget;
}

funk2_gtk_widget_t* funk2_gtk__widget__show_all(funk2_gtk_t* this, u8* name) {
  funk2_gtk_widget_t* widget = funk2_gtk__lookup_widget(this, name);
  if (! widget) {
    return NULL;
  }
  {
    gdk_threads_enter();
    gtk_widget_show_all(widget->gtk_widget);
    gdk_threads_leave();
  }
  return widget;
}

#endif // F2__GTK__SUPPORTED


// user-space interface to gtk

boolean_t raw__gtk__is_supported(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  return boolean__true;
#else
  return boolean__false;
#endif //F2__GTK__SUPPORTED
}

f2ptr f2__gtk__is_supported(f2ptr cause) {
  return f2bool__new(raw__gtk__is_supported(cause));
}
def_pcfunk0(gtk__is_supported, return f2__gtk__is_supported(this_cause));


f2ptr raw__gtk__window__new(f2ptr cause, f2ptr name) {
#if defined(F2__GTK__SUPPORTED)
  u64 name__length = raw__symbol__length(cause, name);
  u8* name__str    = (u8*)from_ptr(f2__malloc(name__length + 1));
  raw__symbol__str_copy(cause, name, name__str);
  name__str[name__length] = 0;
  
  funk2_gtk__window__new(&(__funk2.gtk), name__str);
  
  return name;
#else
  return nil;
#endif
}

f2ptr f2__gtk__window__new(f2ptr cause, f2ptr name) {
  if (! raw__symbol__is_type(cause, name)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__window__new(cause, name);
}
def_pcfunk1(gtk__window__new, name, return f2__gtk__window__new(this_cause, name));


f2ptr raw__gtk__vbox__new(f2ptr cause, f2ptr name, f2ptr row_count) {
#if defined(F2__GTK__SUPPORTED)
  u64 name__length = raw__symbol__length(cause, name);
  u8* name__str    = (u8*)from_ptr(f2__malloc(name__length + 1));
  raw__symbol__str_copy(cause, name, name__str);
  name__str[name__length] = 0;
  
  u64 row_count__i = f2integer__i(row_count, cause);
  
  funk2_gtk__vbox__new(&(__funk2.gtk), name__str, row_count__i);
  
  return name;
#else
  return nil;
#endif
}

f2ptr f2__gtk__vbox__new(f2ptr cause, f2ptr name, f2ptr row_count) {
  if ((! raw__symbol__is_type(cause, name)) ||
      (! raw__integer__is_type(cause, row_count))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__vbox__new(cause, name, row_count);
}
def_pcfunk2(gtk__vbox__new, name, row_count, return f2__gtk__vbox__new(this_cause, name, row_count));


f2ptr raw__gtk__widget__show_all(f2ptr cause, f2ptr name) {
#if defined(F2__GTK__SUPPORTED)
  u64 name__length = raw__symbol__length(cause, name);
  u8* name__str    = (u8*)from_ptr(f2__malloc(name__length + 1));
  raw__symbol__str_copy(cause, name, name__str);
  name__str[name__length] = 0;
  
  if (! funk2_gtk__widget__show_all(&(__funk2.gtk), name__str)) {
    return nil;
  }
  return name;
#else
  return nil;
#endif
}

f2ptr f2__gtk__widget__show_all(f2ptr cause, f2ptr name) {
  if (! raw__symbol__is_type(cause, name)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__widget__show_all(cause, name);
}
def_pcfunk1(gtk__widget__show_all, name, return f2__gtk__widget__show_all(this_cause, name));


f2ptr raw__gtk__container__add(f2ptr cause, f2ptr name, f2ptr add_name) {
#if defined(F2__GTK__SUPPORTED)
  u64 name__length = raw__symbol__length(cause, name);
  u8* name__str    = (u8*)from_ptr(f2__malloc(name__length + 1));
  raw__symbol__str_copy(cause, name, name__str);
  name__str[name__length] = 0;
  
  u64 add_name__length = raw__symbol__length(cause, add_name);
  u8* add_name__str    = (u8*)from_ptr(f2__malloc(add_name__length + 1));
  raw__symbol__str_copy(cause, add_name, add_name__str);
  add_name__str[add_name__length] = 0;
  
  if (! funk2_gtk__container__add(&(__funk2.gtk), name__str, add_name__str)) {
    return nil;
  }
  return name;
#else
  return nil;
#endif
}

f2ptr f2__gtk__container__add(f2ptr cause, f2ptr name, f2ptr add_name) {
  if ((! raw__symbol__is_type(cause, name)) ||
      (! raw__symbol__is_type(cause, add_name))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__container__add(cause, name, add_name);
}
def_pcfunk2(gtk__container__add, name, add_name, return f2__gtk__container__add(this_cause, name, add_name));


// **

void f2__gtk__reinitialize_globalvars() {
}

void f2__gtk__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "gtk", "", &f2__string__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  f2__primcfunk__init__0(gtk__is_supported,                      "Returns true if GIMP ToolKit (GTK) support has been compiled into this version of Funk2.");
  f2__primcfunk__init__1(gtk__window__new,      name,            "Returns the name of a new window widget.");
  f2__primcfunk__init__2(gtk__vbox__new,        name, row_count, "Returns the name of a new vbox widget with row_count rows.");
  f2__primcfunk__init__1(gtk__widget__show_all, name,            "Shows the widget referenced by name.");
  f2__primcfunk__init__2(gtk__container__add,   name, add_name   "Adds a widget to a container.");
  
}


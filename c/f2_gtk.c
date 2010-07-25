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

// gtk_widget

def_frame_object__global__1_slot(gtk_widget, pointer);


#if defined(F2__GTK__SUPPORTED)

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
    gtk_main();
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
  
  funk2_processor_mutex__init(&(this->main_thread__mutex));
  this->main_thread__active = boolean__false;
  this->main_thread         = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), &funk2_gtk__thread__start_function__helper, (void*)this);
}


void funk2_gtk__destroy(funk2_gtk_t* this) {
  funk2_processor_mutex__destroy(&(this->main_thread__mutex));
}


GtkWidget* funk2_gtk__window__new(funk2_gtk_t* this) {
  GtkWidget* window = NULL;
  {
    gdk_threads_enter();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gdk_threads_leave();
  }
  return window;
}

GtkWidget* funk2_gtk__vbox__new(funk2_gtk_t* this, int row_count) {
  GtkWidget* vbox = NULL;
  {
    gdk_threads_enter();
    vbox = gtk_vbox_new(FALSE, row_count);
    gdk_threads_leave();
  }
  return vbox;
}

GtkWidget* funk2_gtk__hbox__new(funk2_gtk_t* this, int column_count) {
  GtkWidget* hbox = NULL;
  {
    gdk_threads_enter();
    hbox = gtk_hbox_new(FALSE, column_count);
    gdk_threads_leave();
  }
  return hbox;
}

void funk2_gtk__container__add(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* add_widget) {
  {
    gdk_threads_enter();
    gtk_container_add(GTK_CONTAINER(widget), add_widget);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__show_all(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_show_all(widget);
    gdk_threads_leave();
  }
}

void funk2_gtk__box__pack_start(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* child_widget, boolean_t expand, boolean_t fill, u64 padding) {
  {
    gdk_threads_enter();
    gtk_box_pack_start(GTK_BOX(widget), child_widget, expand, fill, padding);
    gdk_threads_leave();
  }
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


f2ptr raw__gtk__window__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* window = funk2_gtk__window__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(window)));
#else
  return nil;
#endif
}

f2ptr f2__gtk__window__new(f2ptr cause) {
  return raw__gtk__window__new(cause);
}
def_pcfunk0(gtk__window__new, return f2__gtk__window__new(this_cause));


f2ptr raw__gtk__vbox__new(f2ptr cause, f2ptr row_count) {
#if defined(F2__GTK__SUPPORTED)
  u64        row_count__i = f2integer__i(row_count, cause);
  GtkWidget* vbox         = funk2_gtk__vbox__new(&(__funk2.gtk), row_count__i);
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(vbox)));
#else
  return nil;
#endif
}

f2ptr f2__gtk__vbox__new(f2ptr cause, f2ptr row_count) {
  if (! raw__integer__is_type(cause, row_count)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__vbox__new(cause, row_count);
}
def_pcfunk1(gtk__vbox__new, row_count, return f2__gtk__vbox__new(this_cause, row_count));


f2ptr raw__gtk__hbox__new(f2ptr cause, f2ptr column_count) {
#if defined(F2__GTK__SUPPORTED)
  u64        column_count__i = f2integer__i(column_count, cause);
  GtkWidget* hbox            = funk2_gtk__hbox__new(&(__funk2.gtk), column_count__i);
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(hbox)));
#else
  return nil;
#endif
}

f2ptr f2__gtk__hbox__new(f2ptr cause, f2ptr column_count) {
  if (! raw__integer__is_type(cause, column_count)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__hbox__new(cause, column_count);
}
def_pcfunk1(gtk__hbox__new, column_count, return f2__gtk__hbox__new(this_cause, column_count));


void raw__gtk__container__add(f2ptr cause, f2ptr widget, f2ptr add_widget) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget     = (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, widget),     cause));
  GtkWidget* add_gtk_widget = (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, add_widget), cause));
  funk2_gtk__container__add(&(__funk2.gtk), gtk_widget, add_gtk_widget)) {
#endif
}

f2ptr f2__gtk__container__add(f2ptr cause, f2ptr widget, f2ptr add_widget) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__gtk_widget__is_type(cause, add_widget))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__gtk__container__add(cause, widget, add_widget);
  return nil;
}
def_pcfunk2(gtk__container__add, widget, add_widget, return f2__gtk__container__add(this_cause, widget, add_widget));


void raw__gtk__widget__show_all(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, widget), cause));
  funk2_gtk__widget__show_all(&(__funk2.gtk), gtk_widget);
#endif
}

f2ptr f2__gtk__widget__show_all(f2ptr cause, f2ptr widget) {
  if (! raw__gtk_widget__is_type(cause, widget)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__widget__show_all(cause, widget);
}
def_pcfunk1(gtk__widget__show_all, widget, return f2__gtk__widget__show_all(this_cause, widget));


void raw__gtk__box__pack_start(f2ptr cause, f2ptr widget, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget       = (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, widget),       cause));
  GtkWidget* child_gtk_widget = (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, child_widget), cause));
  u64        padding__i       = f2integer__i(padding, cause);
  funk2_gtk__box__pack_start(&(__funk2.gtk), gtk_widget, child_gtk_widget, expand != nil, fill != nil, padding__i);
#endif
}

f2ptr f2__gtk__box__pack_start(f2ptr cause, f2ptr widget, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__gtk_widget__is_type(cause, child_widget)) ||
      (! raw__integer__is_type(cause, padding))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__box__pack_start(cause, widget, child_widget, expand, fill, padding);
}
def_pcfunk5(gtk__box__pack_start, widget, child_widget, expand, fill, padding, return f2__gtk__box__pack_start(this_cause, widget, child_widget, expand, fill, padding));


// **

void f2__gtk__reinitialize_globalvars() {
}

void f2__gtk__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "gtk", "", &f2__string__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  // gtk_widget
  
  init_frame_object__1_slot(gtk_widget, pointer);
  
  f2__primcfunk__init__0(gtk__is_supported,                                                  "Returns true if GIMP ToolKit (GTK) support has been compiled into this version of Funk2.");
  f2__primcfunk__init__0(gtk__window__new,                                                   "Returns the name of a new window widget.");
  f2__primcfunk__init__1(gtk__vbox__new,        row_count,                                   "Returns the name of a new vbox widget with row_count rows.");
  f2__primcfunk__init__1(gtk__hbox__new,        column_count,                                "Returns the name of a new vbox widget with column_count columns.");
  f2__primcfunk__init__1(gtk__widget__show_all, widget,                                      "Shows the widget referenced by name.");
  f2__primcfunk__init__2(gtk__container__add,   widget, add_widget,                          "Adds a widget to a container.");
  f2__primcfunk__init__5(gtk__box__pack_start,  widget, child_widget, expand, fill, padding, "Packs a child widget in a box.");
  
}


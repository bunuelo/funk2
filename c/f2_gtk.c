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

GtkWidget* raw__gtk_widget__as__GtkWidget(f2ptr cause, f2ptr this) {
  return (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, this), cause));
}

#endif // F2__GTK__SUPPORTED


// gtk_text_buffer

def_frame_object__global__1_slot(gtk_text_buffer, pointer);

#if defined(F2__GTK__SUPPORTED)

GtkTextBuffer* raw__gtk_text_buffer__as__GtkTextBuffer(f2ptr cause, f2ptr this) {
  return (GtkTextBuffer*)from_ptr(f2pointer__p(f2__gtk_text_buffer__pointer(cause, this), cause));
}

#endif // F2__GTK__SUPPORTED


// gtk_text_iter

def_frame_object__global__1_slot(gtk_text_iter, chunk);

#if defined(F2__GTK__SUPPORTED)

void raw__gtk_text_iter__as__GtkTextIter(f2ptr cause, f2ptr this, GtkTextIter* text_iter) {
  f2ptr chunk = f2__gtk_text_iter__chunk(cause, this);
  raw__chunk__str_copy(cause, chunk, (u8*)text_iter);
}

#endif // F2__GTK__SUPPORTED


// gtk_text_mark

def_frame_object__global__1_slot(gtk_text_mark, pointer);

#if defined(F2__GTK__SUPPORTED)

GtkTextMark* raw__gtk_text_mark__as__GtkTextMark(f2ptr cause, f2ptr this) {
  return (GtkTextMark*)from_ptr(f2pointer__p(f2__gtk_text_mark__pointer(cause, this), cause));
}

#endif // F2__GTK__SUPPORTED


// gtk_callback

def_frame_object__global__2_slot(gtk_callback, funk, args);


// gtk_text_range

def_frame_object__global__2_slot(gtk_text_range, start, end);




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
  this->main_thread__active        = boolean__false;
  
  funk2_processor_mutex__init(&(this->callbacks__mutex));
  this->callbacks                  = NULL;
  
  funk2_processor_mutex__init(&(this->callback_events__mutex));
  this->callback_events            = NULL;
  this->callback_events__last_cons = NULL;
  
  this->main_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), &funk2_gtk__thread__start_function__helper, (void*)this);
}


void funk2_gtk__destroy(funk2_gtk_t* this) {
  funk2_processor_mutex__destroy(&(this->main_thread__mutex));
}


void funk2_gtk__add_callback(funk2_gtk_t* this, funk2_gtk_callback_t* callback) {
  funk2_gtk_callback_cons_t* cons = (funk2_gtk_callback_cons_t*)f2__malloc(sizeof(funk2_gtk_callback_cons_t));
  cons->callback = callback;
  
  funk2_processor_mutex__user_lock(&(this->callbacks__mutex));
  cons->next      = this->callbacks;
  this->callbacks = cons->next;
  funk2_processor_mutex__unlock(&(this->callbacks__mutex));
}

void funk2_gtk__add_callback_event(funk2_gtk_t* this, funk2_gtk_callback_t* callback) {
  funk2_gtk_callback_cons_t* cons = (funk2_gtk_callback_cons_t*)f2__malloc(sizeof(funk2_gtk_callback_cons_t));
  cons->callback = callback;
  cons->next     = NULL;
  
  funk2_processor_mutex__user_lock(&(this->callback_events__mutex));
  if (this->callback_events__last_cons) {
    this->callback_events__last_cons->next = cons;
    this->callback_events__last_cons       = cons;
  } else {
    this->callback_events            = cons;
    this->callback_events__last_cons = cons;
  }
  funk2_processor_mutex__unlock(&(this->callback_events__mutex));
}

funk2_gtk_callback_t* funk2_gtk__pop_callback_event(funk2_gtk_t* this) {
  funk2_gtk_callback_t* callback = NULL;
  funk2_processor_mutex__user_lock(&(this->callback_events__mutex));
  if (this->callback_events) {
    funk2_gtk_callback_cons_t* cons = this->callback_events;
    this->callback_events = this->callback_events->next;
    callback = cons->callback;
    f2__free(to_ptr(cons));
    if (this->callback_events == NULL) {
      this->callback_events__last_cons = NULL;
    }
  }
  funk2_processor_mutex__unlock(&(this->callback_events__mutex));
  return callback;
}

void funk2_gtk__callback_handler(GtkWidget *widget, funk2_gtk_callback_t* callback) {
  funk2_gtk__add_callback_event(callback->gtk, callback);
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

GtkWidget* funk2_gtk__button__new_with_label(funk2_gtk_t* this, u8* label) {
  GtkWidget* button = NULL;
  {
    gdk_threads_enter();
    button = gtk_button_new_with_label((char*)label);
    gdk_threads_leave();
  }
  return button;
}

GtkWidget* funk2_gtk__entry__new(funk2_gtk_t* this) {
  GtkWidget* entry = NULL;
  {
    gdk_threads_enter();
    entry = gtk_entry_new();
    gdk_threads_leave();
  }
  return entry;
}

char* funk2_gtk__entry__get_text(funk2_gtk_t* this, GtkWidget* widget) {
  char* text = NULL;
  {
    gdk_threads_enter();
    text = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    gdk_threads_leave();
  }
  return text;
}

GtkWidget* funk2_gtk__scrolled_window__new(funk2_gtk_t* this) {
  GtkWidget* scrolled_window = NULL;
  {
    gdk_threads_enter();
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
				   GTK_POLICY_AUTOMATIC,
				   GTK_POLICY_AUTOMATIC);
    gdk_threads_leave();
  }
  return scrolled_window;
}

GtkWidget* funk2_gtk__text_view__new(funk2_gtk_t* this) {
  GtkWidget* text_view = NULL;
  {
    gdk_threads_enter();
    text_view = gtk_text_view_new();
    gdk_threads_leave();
  }
  return text_view;
}

GtkTextBuffer* funk2_gtk__text_view__get_buffer(funk2_gtk_t* this, GtkWidget* text_view) {
  GtkTextBuffer* buffer = NULL;
  {
    gdk_threads_enter();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gdk_threads_leave();
  }
  return buffer;
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

void funk2_gtk__signal_connect(funk2_gtk_t* this, GtkWidget* widget, u8* signal_name, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)f2__malloc(sizeof(funk2_gtk_callback_t));
  callback->gtk  = this;
  callback->funk = funk;
  callback->args = args;
  // never gc these (they are not referenced in the global environment)
  if (funk) {
    never_gc(funk);
  }
  if (args) {
    never_gc(args);
  }
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), (char*)signal_name, G_CALLBACK(funk2_gtk__callback_handler), callback);
    gdk_threads_leave();
  }
}

void funk2_gtk__text_buffer__get_start_iter(funk2_gtk_t* this, GtkTextBuffer* text_buffer, GtkTextIter* text_iter) {
  {
    gdk_threads_enter();
    gtk_text_buffer_get_start_iter(text_buffer, text_iter);
    gdk_threads_leave();
  }
}

boolean_t funk2_gtk__text_iter__forward_search(GtkTextiter* iter, char* text, GtkTextIter* mstart, GtkTextIter* mend) {
  boolean_t found;
  {
    gdk_threads_enter();
    found = (gtk_text_iter_forward_search(iter, (gchar*)text, 0, mstart, mend, NULL) ? boolean__true : boolean__false);
    gdk_threads_leave();
  }
  return found;
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_not_supported_larva__new(f2ptr cause) {
  f2ptr bug_frame = f2__frame__new(cause, nil);
  f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "gtk_support_not_compiled_into_this_version_of_funk2"));
  return f2larva__new(cause, 534, f2__bug__new(cause, f2integer__new(cause, 534), bug_frame));
}


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
  return f2__gtk_not_supported_larva__new(cause);
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
  return f2__gtk_not_supported_larva__new(cause);
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
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__hbox__new(f2ptr cause, f2ptr column_count) {
  if (! raw__integer__is_type(cause, column_count)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__hbox__new(cause, column_count);
}
def_pcfunk1(gtk__hbox__new, column_count, return f2__gtk__hbox__new(this_cause, column_count));


f2ptr raw__gtk__button__new_with_label(f2ptr cause, f2ptr label) {
#if defined(F2__GTK__SUPPORTED)
  u64 label__length = raw__string__length(cause, label);
  u8* label__str    = (u8*)alloca(label__length + 1);
  raw__string__str_copy(cause, label, label__str);
  label__str[label__length] = 0;
  
  GtkWidget* button = funk2_gtk__button__new_with_label(&(__funk2.gtk), label__str);
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(button)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__button__new_with_label(f2ptr cause, f2ptr label) {
  if (! raw__string__is_type(cause, label)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__button__new_with_label(cause, label);
}
def_pcfunk1(gtk__button__new_with_label, label, return f2__gtk__button__new_with_label(this_cause, label));


f2ptr raw__gtk__entry__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* entry = funk2_gtk__entry__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(entry)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__entry__new(f2ptr cause) {
  return raw__gtk__entry__new(cause);
}
def_pcfunk0(gtk__entry__new, return f2__gtk__entry__new(this_cause));


f2ptr raw__gtk__entry__get_text(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  char* text = funk2_gtk__entry__get_text(&(__funk2.gtk), gtk_widget);
  if (! text) {
    return nil;
  }
  return new__string(cause, text);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__entry__get_text(f2ptr cause, f2ptr widget) {
  if (! raw__gtk_widget__is_type(cause, widget)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__entry__get_text(cause, widget);
}
def_pcfunk1(gtk__entry__get_text, widget, return f2__gtk__entry__get_text(this_cause, widget));


f2ptr raw__gtk__scrolled_window__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* scrolled_window = funk2_gtk__scrolled_window__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(scrolled_window)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scrolled_window__new(f2ptr cause) {
  return raw__gtk__scrolled_window__new(cause);
}
def_pcfunk0(gtk__scrolled_window__new, return f2__gtk__scrolled_window__new(this_cause));


f2ptr raw__gtk__text_view__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* text_view = funk2_gtk__text_view__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(text_view)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_view__new(f2ptr cause) {
  return raw__gtk__text_view__new(cause);
}
def_pcfunk0(gtk__text_view__new, return f2__gtk__text_view__new(this_cause));


f2ptr raw__gtk__text_view__get_buffer(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  GtkTextBuffer* buffer = funk2_gtk__text_view__get_buffer(&(__funk2.gtk), gtk_widget);
  if (! buffer) {
    return nil;
  }
  return f2__gtk_text_buffer__new(cause, f2pointer__new(cause, to_ptr(buffer)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_view__get_buffer(f2ptr cause, f2ptr widget) {
  if (! raw__gtk_widget__is_type(cause, widget)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__text_view__get_buffer(cause, widget);
}
def_pcfunk1(gtk__text_view__get_buffer, widget, return f2__gtk__text_view__get_buffer(this_cause, widget));


f2ptr raw__gtk__container__add(f2ptr cause, f2ptr widget, f2ptr add_widget) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget     = raw__gtk_widget__as__GtkWidget(cause, widget);
  GtkWidget* add_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, add_widget);
  funk2_gtk__container__add(&(__funk2.gtk), gtk_widget, add_gtk_widget);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__container__add(f2ptr cause, f2ptr widget, f2ptr add_widget) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__gtk_widget__is_type(cause, add_widget))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__container__add(cause, widget, add_widget);
}
def_pcfunk2(gtk__container__add, widget, add_widget, return f2__gtk__container__add(this_cause, widget, add_widget));


f2ptr raw__gtk__widget__show_all(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  funk2_gtk__widget__show_all(&(__funk2.gtk), gtk_widget);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__show_all(f2ptr cause, f2ptr widget) {
  if (! raw__gtk_widget__is_type(cause, widget)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__widget__show_all(cause, widget);
}
def_pcfunk1(gtk__widget__show_all, widget, return f2__gtk__widget__show_all(this_cause, widget));


f2ptr raw__gtk__box__pack_start(f2ptr cause, f2ptr widget, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget       = raw__gtk_widget__as__GtkWidget(cause, widget);
  GtkWidget* child_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, child_widget);
  u64        padding__i       = f2integer__i(padding, cause);
  funk2_gtk__box__pack_start(&(__funk2.gtk), gtk_widget, child_gtk_widget, expand != nil, fill != nil, padding__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
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


f2ptr raw__gtk__signal_connect(f2ptr cause, f2ptr widget, f2ptr signal_name, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  
  u64 signal_name__length = raw__string__length(cause, signal_name);
  u8* signal_name__str    = (u8*)alloca(signal_name__length + 1);
  raw__string__str_copy(cause, signal_name, signal_name__str);
  signal_name__str[signal_name__length] = 0;
  
  funk2_gtk__signal_connect(&(__funk2.gtk), gtk_widget, signal_name__str, funk, args);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__signal_connect(f2ptr cause, f2ptr widget, f2ptr signal_name, f2ptr funk, f2ptr args) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__string__is_type(cause, signal_name)) ||
      (! raw__funkable__is_type(cause, funk)) ||
      (args && (! raw__cons__is_type(cause, args)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__signal_connect(cause, widget, signal_name, funk, args);
}
def_pcfunk4(gtk__signal_connect, widget, signal_name, funk, args, return f2__gtk__signal_connect(this_cause, widget, signal_name, funk, args));

f2ptr f2__gtk__pop_callback_event(f2ptr cause) {
  funk2_gtk_callback_t* callback = funk2_gtk__pop_callback_event(&(__funk2.gtk));
  if (! callback) {
    return nil;
  }
  f2ptr funk = callback->funk;
  f2ptr args = callback->args;
  return f2__gtk_callback__new(cause, funk, args);
}
def_pcfunk0(gtk__pop_callback_event, return f2__gtk__pop_callback_event(this_cause));


f2ptr raw__gtk__text_buffer__get_start_iter(f2ptr cause, f2ptr text_buffer) {
#if defined(F2__GTK__SUPPORTED)
  GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
  GtkTextIter    text_iter;
  funk2_gtk__text_buffer__get_start_iter(&(__funk2.gtk), gtk_text_buffer, &text_iter);
  return f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&text_iter));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__get_start_iter(f2ptr cause, f2ptr text_buffer) {
  if (! raw__gtk_text_buffer__is_type(cause, text_buffer)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__text_buffer__get_start_iter(cause, text_buffer);
}
def_pcfunk1(gtk__text_buffer__get_start_iter, text_buffer, return f2__gtk__text_buffer__get_start_iter(this_cause, text_buffer));


f2ptr raw__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text) {
  GtkTextIter gtk_text_iter;
  raw__gtk_text_iter__as__GtkTextIter(cause, text_iter, &gtk_text_iter);
  
  u64 text__length = raw__string__length(cause, text);
  u8* text__str    = (u8*)alloca(text__length + 1);
  raw__string__str_copy(cause, text, text__str);
  text__str[text__length] = 0;
  
  GtkTextIter mstart;
  GtkTextIter mend;
  boolean_t   found = funk2_gtk__text_iter__forward_search(gtk_text_iter, text__str, &mstart, &mend);
  if (! found) {
    return nil;
  }
  return f2__gtk_text_range__new(cause, f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&mstart)), f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&mend)));
}

// **

void f2__gtk__reinitialize_globalvars() {
}

void f2__gtk__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "gtk", "", &f2__string__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  // gtk_widget
  
  init_frame_object__1_slot(gtk_widget, pointer);
  
  
  // gtk_text_buffer
  
  init_frame_object__1_slot(gtk_text_buffer, pointer);
  
  
  // gtk_text_iter
  
  init_frame_object__1_slot(gtk_text_iter, chunk);
  
  
  // gtk_text_mark
  
  init_frame_object__1_slot(gtk_text_mark, pointer);
  
  
  // gtk_callback
  
  init_frame_object__2_slot(gtk_callback, funk, args);
  
  
  // gtk_text_range
  
  init_frame_object__2_slot(gtk_text_range, start, end);
  
  
  f2__primcfunk__init__0(gtk__is_supported,                                                             "Returns true if GIMP ToolKit (GTK) support has been compiled into this version of Funk2.");
  f2__primcfunk__init__0(gtk__window__new,                                                              "Returns the name of a new window widget.");
  f2__primcfunk__init__1(gtk__vbox__new,                   row_count,                                   "Returns the name of a new vbox widget with row_count rows.");
  f2__primcfunk__init__1(gtk__hbox__new,                   column_count,                                "Returns the name of a new hbox widget with column_count columns.");
  f2__primcfunk__init__1(gtk__button__new_with_label,      label,                                       "Returns the name of a new button widget with label.");
  f2__primcfunk__init__0(gtk__entry__new,                                                               "Returns the name of a new entry widget.");
  f2__primcfunk__init__1(gtk__entry__get_text,             widget,                                      "Returns the text of an entry widget as a string.");
  f2__primcfunk__init__0(gtk__scrolled_window__new,                                                     "Returns the name of a new scrolled_window widget.");
  f2__primcfunk__init__0(gtk__text_view__new,                                                           "Returns the name of a new text_view widget.");
  f2__primcfunk__init__1(gtk__text_view__get_buffer,       text_view,                                   "Returns the buffer widget of a text_view widget.");
  f2__primcfunk__init__1(gtk__widget__show_all,            widget,                                      "Shows the widget and all children.");
  f2__primcfunk__init__2(gtk__container__add,              widget, add_widget,                          "Adds a widget to a container.");
  f2__primcfunk__init__5(gtk__box__pack_start,             widget, child_widget, expand, fill, padding, "Packs a child widget in a box.");
  f2__primcfunk__init__4(gtk__signal_connect,              widget, signal_name, funk, args,             "Creates a callback for a widget (see gtk-pop_callback_event).");
  f2__primcfunk__init__0(gtk__pop_callback_event,                                                       "Returns the next waiting callback event, if one exists, nil otherwise.");
  f2__primcfunk__init__1(gtk__text_buffer__get_start_iter, text_buffer,                                 "Returns the starting text_iter of a text_buffer.");
  
}


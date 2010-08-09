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


// gtk_box

def_frame_object__global__1_slot(gtk_box, pointer);

#if defined(F2__GTK__SUPPORTED)

GtkBox* raw__gtk_box__as__GtkBox(f2ptr cause, f2ptr this) {
  return (GtkBox*)from_ptr(f2pointer__p(f2__gtk_box__pointer(cause, this), cause));
}

#endif // F2__GTK__SUPPORTED


f2ptr f2gtk_box__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2gtk_box__primobject_type__new(cause);
  f2__primobject_type__parents__set(cause, this, f2cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}



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
  gdk_rgb_init();
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
  funk2_gtk_callback_cons_t* cons = (funk2_gtk_callback_cons_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_cons_t)));
  cons->callback = callback;
  
  funk2_processor_mutex__user_lock(&(this->callbacks__mutex));
  cons->next      = this->callbacks;
  this->callbacks = cons->next;
  funk2_processor_mutex__unlock(&(this->callbacks__mutex));
  
  // never gc these (they are not referenced in the global environment)
  if (callback->funk) {
    never_gc(callback->funk);
  }
  if (callback->args) {
    never_gc(callback->args);
  }
}

void funk2_gtk__add_callback_event(funk2_gtk_t* this, funk2_gtk_callback_t* callback) {
  funk2_gtk_callback_cons_t* cons = (funk2_gtk_callback_cons_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_cons_t)));
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
  funk2_gtk__add_callback_event(&(__funk2.gtk), callback);
}

void funk2_gtk__signal_connect(funk2_gtk_t* this, GtkWidget* widget, u8* signal_name, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->funk = funk;
  callback->args = args;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), (char*)signal_name, G_CALLBACK(funk2_gtk__callback_handler), callback);
    gdk_threads_leave();
  }
}


// expose_event

gboolean funk2_gtk__expose_event__signal_connect__callback_handler(GtkWidget *widget, GdkEventExpose *event, gpointer data) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)data;
  funk2_gtk__add_callback_event(&(__funk2.gtk), callback);
  return TRUE;
}

void funk2_gtk__expose_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->funk = funk;
  callback->args = args;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "expose_event", G_CALLBACK(funk2_gtk__expose_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// widget

void funk2_gtk__widget__show_all(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_show_all(widget);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__set_size_request(funk2_gtk_t* this, GtkWidget* widget, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gtk_widget_set_size_request(widget, width, height);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__queue_draw_area(funk2_gtk_t* this, GtkWidget* widget, s64 x, s64 y, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gtk_widget_queue_draw_area(widget, x, y, width, height);
    gdk_threads_leave();
  }
}



// GtkWidget.GdkWindow ? widget draw functions...

//void gdk_draw_point    (GdkDrawable* drawable,                GdkGC* gc, gint x, gint y);
//void gdk_draw_points   (GdkDrawable* drawable,                GdkGC* gc, GdkPoint* points, gint npoints); 
//void gdk_draw_line     (GdkDrawable* drawable,                GdkGC* gc, gint x1, gint y1, gint x2, gint y2);
//void gdk_draw_lines    (GdkDrawable* drawable,                GdkGC* gc, GdkPoint* points, gint npoints);
//void gdk_draw_segments (GdkDrawable* drawable,                GdkGC* gc, GdkSegment* segments, gint nsegments); 
//void gdk_draw_polygon  (GdkDrawable* drawable,                GdkGC* gc, gint filled, GdkPoint* points, gint npoints);
//void gdk_draw_string   (GdkDrawable* drawable, GdkFont* font, GdkGC* gc, gint x, gint y, const gchar* text);
//void gdk_draw_pixmap   (GdkDrawable* drawable,                GdkGC* gc, GdkDrawable* src, gint xsrc, gint ysrc, gint xdest, gint ydest, gint width, gint height);
//void gdk_draw_rgb_image(GdkDrawable* drawable,                GdkGC* gc, gint x, gint y, gint width, gint height, GdkRGBDither dither, guchar* rgb_buf, gint rowstride);

void funk2_gtk__widget__draw_line(funk2_gtk_t* this, GtkWidget* widget, boolean_t filled, s64 x, s64 y, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gdk_draw_rectangle(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], filled ? TRUE : FALSE, x, y, width, height);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__draw_arc(funk2_gtk_t* this, GtkWidget* widget, boolean_t filled, s64 x, s64 y, s64 width, s64 height, s64 angle1, s64 angle2) {
  {
    gdk_threads_enter();
    gdk_draw_arc(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], filled ? TRUE : FALSE, x, y, width, height, angle1, angle2);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__draw_rectangle(funk2_gtk_t* this, GtkWidget* widget, boolean_t filled, s64 x, s64 y, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gdk_draw_rectangle(widget->window, widget->style->fg_gc[GTK_WIDGET_STATE(widget)], filled ? TRUE : FALSE, x, y, width, height);
    gdk_threads_leave();
  }
}





// window

GtkWidget* funk2_gtk__window__new(funk2_gtk_t* this) {
  GtkWidget* window = NULL;
  {
    gdk_threads_enter();
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gdk_threads_leave();
  }
  return window;
}

void funk2_gtk__window__set_title(funk2_gtk_t* this, GtkWidget* window, u8* title) {
  {
    gdk_threads_enter();
    gtk_window_set_title(GTK_WINDOW(window), (char*)title);
    gdk_threads_leave();
  }
}

void funk2_gtk__window__set_default_size(funk2_gtk_t* this, GtkWidget* window, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
    gdk_threads_leave();
  }
}


// vbox

GtkWidget* funk2_gtk__vbox__new(funk2_gtk_t* this, int row_count) {
  GtkWidget* vbox = NULL;
  {
    gdk_threads_enter();
    vbox = gtk_vbox_new(FALSE, row_count);
    gdk_threads_leave();
  }
  return vbox;
}


// hbox

GtkWidget* funk2_gtk__hbox__new(funk2_gtk_t* this, int column_count) {
  GtkWidget* hbox = NULL;
  {
    gdk_threads_enter();
    hbox = gtk_hbox_new(FALSE, column_count);
    gdk_threads_leave();
  }
  return hbox;
}


// button

GtkWidget* funk2_gtk__button__new_with_label(funk2_gtk_t* this, u8* label) {
  GtkWidget* button = NULL;
  {
    gdk_threads_enter();
    button = gtk_button_new_with_label((char*)label);
    gdk_threads_leave();
  }
  return button;
}


// entry

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


// scrolled_window

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

void funk2_gtk__scrolled_window__add_with_viewport(funk2_gtk_t* this, GtkWidget* scrolled_window, GtkWidget* child) {
  {
    gdk_threads_enter();
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolled_window), GTK_WIDGET(child));
    gdk_threads_leave();
  }
}


// text_view

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


// container

void funk2_gtk__container__add(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* add_widget) {
  {
    gdk_threads_enter();
    gtk_container_add(GTK_CONTAINER(widget), add_widget);
    gdk_threads_leave();
  }
}


// box

void funk2_gtk__box__pack_start(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* child_widget, boolean_t expand, boolean_t fill, u64 padding) {
  {
    gdk_threads_enter();
    gtk_box_pack_start(GTK_BOX(widget), child_widget, expand, fill, padding);
    gdk_threads_leave();
  }
}


// text_buffer

void funk2_gtk__text_buffer__get_start_iter(funk2_gtk_t* this, GtkTextBuffer* text_buffer, GtkTextIter* text_iter) {
  {
    gdk_threads_enter();
    gtk_text_buffer_get_start_iter(text_buffer, text_iter);
    gdk_threads_leave();
  }
}

void funk2_gtk__text_buffer__select_range(funk2_gtk_t* this, GtkTextBuffer* text_buffer, GtkTextIter* start, GtkTextIter* end) {
  {
    gdk_threads_enter();
    gtk_text_buffer_select_range(text_buffer, start, end);
    gdk_threads_leave();
  }
}

char* funk2_gtk__text_buffer__get_text(funk2_gtk_t* this, GtkTextBuffer* text_buffer) {
  char* text;
  {
    GtkTextIter start;
    GtkTextIter end;
    gdk_threads_enter();
    gtk_text_buffer_get_start_iter(text_buffer, &start);
    gtk_text_buffer_get_end_iter(text_buffer, &end);
    text = (char*)gtk_text_buffer_get_text(text_buffer, &start, &end, FALSE);
    gdk_threads_leave();
  }
  return text;
}

void funk2_gtk__text_buffer__set_text(funk2_gtk_t* this, GtkTextBuffer* text_buffer, u8* text) {
  {
    gdk_threads_enter();
    gtk_text_buffer_set_text(text_buffer, (char*)text, strlen((char*)text));
    gdk_threads_leave();
  }
}


// text_iter

boolean_t funk2_gtk__text_iter__forward_search(funk2_gtk_t* this, GtkTextIter* iter, u8* text, GtkTextIter* start, GtkTextIter* end) {
  boolean_t found;
  {
    gdk_threads_enter();
    found = (gtk_text_iter_forward_search(iter, (gchar*)text, 0, start, end, NULL) ? boolean__true : boolean__false);
    gdk_threads_leave();
  }
  return found;
}


// paned

void funk2_gtk__paned__pack1(funk2_gtk_t* this, GtkWidget* paned, GtkWidget* child, boolean_t resize, boolean_t shrink) {
  {
    gdk_threads_enter();
    gtk_paned_pack1(GTK_PANED(paned), child, resize ? TRUE : FALSE, shrink ? TRUE : FALSE);
    gdk_threads_leave();
  }
}

void funk2_gtk__paned__pack2(funk2_gtk_t* this, GtkWidget* paned, GtkWidget* child, boolean_t resize, boolean_t shrink) {
  {
    gdk_threads_enter();
    gtk_paned_pack2(GTK_PANED(paned), child, resize ? TRUE : FALSE, shrink ? TRUE : FALSE);
    gdk_threads_leave();
  }
}

void funk2_gtk__paned__set_position(funk2_gtk_t* this, GtkWidget* paned, s64 position) {
  {
    gdk_threads_enter();
    gtk_paned_set_position(GTK_PANED(paned), position);
    gdk_threads_leave();
  }
}


// vpaned

GtkWidget* funk2_gtk__vpaned__new(funk2_gtk_t* this) {
  GtkWidget* vpaned;
  {
    gdk_threads_enter();
    vpaned = gtk_vpaned_new();
    gdk_threads_leave();
  }
  return vpaned;
}


// hpaned

GtkWidget* funk2_gtk__hpaned__new(funk2_gtk_t* this) {
  GtkWidget* hpaned;
  {
    gdk_threads_enter();
    hpaned = gtk_hpaned_new();
    gdk_threads_leave();
  }
  return hpaned;
}


// progress_bar

GtkWidget* funk2_gtk__progress_bar__new(funk2_gtk_t* this) {
  GtkWidget* progress_bar;
  {
    gdk_threads_enter();
    progress_bar = gtk_progress_bar_new();
    gdk_threads_leave();
  }
  return progress_bar;
}

void funk2_gtk__progress_bar__set_fraction(GtkWidget* progress_bar, double fraction) {
  {
    gdk_threads_enter();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), fraction);
    gdk_threads_leave();
  }
}


// notebook

GtkWidget* funk2_gtk__notebook__new(funk2_gtk_t* this) {
  GtkWidget* notebook;
  {
    gdk_threads_enter();
    notebook = gtk_notebook_new();
    gdk_threads_leave();
  }
  return notebook;
}

s64 funk2_gtk__notebook__append_page(funk2_gtk_t* this, GtkWidget* notebook, GtkWidget* child, GtkWidget* tab_label) {
  s64 index;
  {
    gdk_threads_enter();
    // returns -1 on failure (according to gtk docs).
    index = gtk_notebook_append_page(GTK_NOTEBOOK(notebook), GTK_WIDGET(child), GTK_WIDGET(tab_label));
    gdk_threads_leave();
  }
  return index;
}

s64 funk2_gtk__notebook__prepend_page(funk2_gtk_t* this, GtkWidget* notebook, GtkWidget* child, GtkWidget* tab_label) {
  s64 index;
  {
    gdk_threads_enter();
    // returns -1 on failure (according to gtk docs).
    index = gtk_notebook_prepend_page(GTK_NOTEBOOK(notebook), GTK_WIDGET(child), GTK_WIDGET(tab_label));
    gdk_threads_leave();
  }
  return index;
}

s64 funk2_gtk__notebook__insert_page(funk2_gtk_t* this, GtkWidget* notebook, GtkWidget* child, GtkWidget* tab_label, s64 position) {
  s64 index;
  {
    gdk_threads_enter();
    // returns -1 on failure (according to gtk docs).
    index = gtk_notebook_insert_page(GTK_NOTEBOOK(notebook), GTK_WIDGET(child), GTK_WIDGET(tab_label), position);
    gdk_threads_leave();
  }
  return index;
}

void funk2_gtk__notebook__remove_page(funk2_gtk_t* this, GtkWidget* notebook, s64 index) {
  {
    gdk_threads_enter();
    gtk_notebook_remove_page(GTK_NOTEBOOK(notebook), index);
    gdk_threads_leave();
  }
}

s64 funk2_gtk__notebook__get_current_page(funk2_gtk_t* this, GtkWidget* notebook) {
  s64 index;
  {
    gdk_threads_enter();
    index = gtk_notebook_get_current_page(GTK_NOTEBOOK(notebook));
    gdk_threads_leave();
  }
  return index;
}

void funk2_gtk__notebook__set_scrollable(funk2_gtk_t* this, GtkWidget* notebook, boolean_t scrollable) {
  {
    gdk_threads_enter();
    gtk_notebook_set_scrollable(GTK_NOTEBOOK(notebook), scrollable ? TRUE : FALSE);
    gdk_threads_leave();
  }
}


// label

GtkWidget* funk2_gtk__label__new(funk2_gtk_t* this, u8* text) {
  GtkWidget* label;
  {
    gdk_threads_enter();
    label = gtk_label_new((char*)text);
    gdk_threads_leave();
  }
  return label;
}


// drawing_area

GtkWidget* funk2_gtk__drawing_area__new(funk2_gtk_t* this) {
  GtkWidget* drawing_area;
  {
    gdk_threads_enter();
    drawing_area = gtk_drawing_area_new();
    gdk_threads_leave();
  }
  return drawing_area;
}


// table

GtkWidget* funk2_gtk__table__new(funk2_gtk_t* this, s64 rows, s64 columns, boolean_t homogenous) {
  GtkWidget* table;
  {
    gdk_threads_enter();
    table = gtk_table_new(rows, columns, homogenous);
    gdk_threads_leave();
  }
  return table;
}

//void gtk_table_attach(GtkTable *table,
//                      GtkWidget *child,
//                      guint left_attach,
//                      guint right_attach,
//                      guint top_attach,
//                      guint bottom_attach,
//                      GtkAttachOptions xoptions,
//                      GtkAttachOptions yoptions,
//                      guint xpadding,
//                      guint ypadding);

void funk2_gtk__table__attach(funk2_gtk_t* this, GtkWidget* table, GtkWidget* child, u64 left_attach, u64 right_attach, u64 top_attach, u64 bottom_attach, u64 xpadding, u64 ypadding) {
  GtkAttachOptions xoptions = GTK_EXPAND | GTK_SHRINK | GTK_FILL;
  GtkAttachOptions yoptions = GTK_EXPAND | GTK_SHRINK | GTK_FILL;
  {
    gdk_threads_enter();
    gtk_table_attach(GTK_TABLE(table), GTK_WIDGET(child), left_attach, right_attach, top_attach, bottom_attach, xoptions, yoptions, xpadding, ypadding);
    gdk_threads_leave();
  }
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


f2ptr raw__gtk__window__set_title(f2ptr cause, f2ptr window, f2ptr title) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_window = raw__gtk_widget__as__GtkWidget(cause, window);
  
  u64 title__length = raw__string__length(cause, title);
  u8* title__str    = (u8*)alloca(title__length + 1);
  raw__string__str_copy(cause, title, title__str);
  title__str[title__length] = 0;
  
  funk2_gtk__window__set_title(&(__funk2.gtk), gtk_window, title__str);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__set_title(f2ptr cause, f2ptr window, f2ptr title) {
  if ((! raw__gtk_widget__is_type(cause, window)) ||
      (! raw__string__is_type(cause, title))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__window__set_title(cause, window, title);
}
def_pcfunk2(gtk__window__set_title, window, title, return f2__gtk__window__set_title(this_cause, window, title));


f2ptr raw__gtk__window__set_default_size(f2ptr cause, f2ptr window, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_window = raw__gtk_widget__as__GtkWidget(cause, window);
  s64        width__i   = f2integer__i(width,  cause);
  s64        height__i  = f2integer__i(height, cause);
  funk2_gtk__window__set_default_size(&(__funk2.gtk), gtk_window, width__i, height__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__set_default_size(f2ptr cause, f2ptr window, f2ptr width, f2ptr height) {
  if ((! raw__gtk_widget__is_type(cause, window)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__window__set_default_size(cause, window, width, height);
}
def_pcfunk3(gtk__window__set_default_size, window, width, height, return f2__gtk__window__set_default_size(this_cause, window, width, height));


f2ptr raw__gtk__vbox__new(f2ptr cause, f2ptr row_count) {
#if defined(F2__GTK__SUPPORTED)
  u64        row_count__i = f2integer__i(row_count, cause);
  GtkWidget* vbox         = funk2_gtk__vbox__new(&(__funk2.gtk), row_count__i);
  return f2__gtk_box__new(cause, f2pointer__new(cause, to_ptr(vbox)));
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
  return f2__gtk_box__new(cause, f2pointer__new(cause, to_ptr(hbox)));
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


f2ptr raw__gtk__scrolled_window__add_with_viewport(f2ptr cause, f2ptr scrolled_window, f2ptr child) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_scrolled_window = raw__gtk_widget__as__GtkWidget(cause, scrolled_window);
  GtkWidget* gtk_child           = raw__gtk_widget__as__GtkWidget(cause, child);
  funk2_gtk__scrolled_window__add_with_viewport(&(__funk2.gtk), gtk_scrolled_window, gtk_child);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scrolled_window__add_with_viewport(f2ptr cause, f2ptr scrolled_window, f2ptr child) {
  return raw__gtk__scrolled_window__add_with_viewport(cause, scrolled_window, child);
}
def_pcfunk2(gtk__scrolled_window__add_with_viewport, scrolled_window, child, return f2__gtk__scrolled_window__add_with_viewport(this_cause, scrolled_window, child));


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


// expose_event

f2ptr raw__gtk__expose_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  funk2_gtk__expose_event__signal_connect(&(__funk2.gtk), gtk_widget, funk, args);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__expose_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__funkable__is_type(cause, funk)) ||
      (args && (! raw__cons__is_type(cause, args)))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__expose_event__signal_connect(cause, widget, funk, args);
}
def_pcfunk3(gtk__expose_event__signal_connect, widget, funk, args, return f2__gtk__expose_event__signal_connect(this_cause, widget, funk, args));


// works for 'clicked' event but not 'expose_event'

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



// widget

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


f2ptr raw__gtk__widget__set_size_request(f2ptr cause, f2ptr widget, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  s64        width__i   = f2integer__i(width,  cause);
  s64        height__i  = f2integer__i(height, cause);
  funk2_gtk__widget__set_size_request(&(__funk2.gtk), gtk_widget, width__i, height__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__set_size_request(f2ptr cause, f2ptr widget, f2ptr width, f2ptr height) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__widget__set_size_request(cause, widget, width, height);
}
def_pcfunk3(gtk__widget__set_size_request, widget, width, height, return f2__gtk__widget__set_size_request(this_cause, widget, width, height));


f2ptr raw__gtk__widget__queue_draw_area(f2ptr cause, f2ptr widget, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  s64        x__i       = f2integer__i(x,  cause);
  s64        y__i       = f2integer__i(y, cause);
  s64        width__i   = f2integer__i(width,  cause);
  s64        height__i  = f2integer__i(height, cause);
  funk2_gtk__widget__queue_draw_area(&(__funk2.gtk), gtk_widget, x__i, y__i, width__i, height__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__queue_draw_area(f2ptr cause, f2ptr widget, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__integer__is_type(cause, x)) ||
      (! raw__integer__is_type(cause, y)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__widget__queue_draw_area(cause, widget, x, y, width, height);
}
def_pcfunk5(gtk__widget__queue_draw_area, widget, x, y, width, height, return f2__gtk__widget__queue_draw_area(this_cause, widget, x, y, width, height));


f2ptr raw__gtk__widget__draw_arc(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height, f2ptr angle1, f2ptr angle2) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  s64        x__i       = f2integer__i(x,      cause);
  s64        y__i       = f2integer__i(y,      cause);
  s64        width__i   = f2integer__i(width,  cause);
  s64        height__i  = f2integer__i(height, cause);
  s64        angle1__i  = f2integer__i(angle1, cause);
  s64        angle2__i  = f2integer__i(angle2, cause);
  funk2_gtk__widget__draw_arc(&(__funk2.gtk), gtk_widget, (filled != nil) ? TRUE : FALSE, x__i, y__i, width__i, height__i, angle1__i, angle2__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__draw_arc(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height, f2ptr angle1, f2ptr angle2) {
  if (! raw__gtk_widget__is_type(cause, widget)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "widget"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "gtk_widget"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, widget));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "widget"),        widget);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  if (! raw__integer__is_type(cause, x)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "x"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "integer"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, x));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "x"),             x);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  if (! raw__integer__is_type(cause, y)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "y"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "integer"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, y));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "y"),             y);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  if (! raw__integer__is_type(cause, width)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "width"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "integer"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, width));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "width"),         width);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  if (! raw__integer__is_type(cause, height)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "height"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "integer"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, height));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "height"),        height);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  if (! raw__integer__is_type(cause, angle1)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "angle1"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "integer"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, angle1));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "angle1"),        angle1);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  if (! raw__integer__is_type(cause, angle2)) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),      new__symbol(cause, "unexpected_type"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funk_name"),     new__symbol(cause, "gtk-widget-draw_arc"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "variable_name"), new__symbol(cause, "angle2"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "expected_type"), new__symbol(cause, "integer"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "actual_type"),   f2__object__type(cause, angle2));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "angle2"),        angle2);
    return f2larva__new(cause, 1, f2__bug__new(cause, f2integer__new(cause, 1), bug_frame));
  }
  return raw__gtk__widget__draw_arc(cause, widget, filled, x, y, width, height, angle1, angle2);
}
def_pcfunk8(gtk__widget__draw_arc, widget, filled, x, y, width, height, angle1, angle2, return f2__gtk__widget__draw_arc(this_cause, widget, filled, x, y, width, height, angle1, angle2));


f2ptr raw__gtk__widget__draw_rectangle(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
  s64        x__i       = f2integer__i(x,      cause);
  s64        y__i       = f2integer__i(y,      cause);
  s64        width__i   = f2integer__i(width,  cause);
  s64        height__i  = f2integer__i(height, cause);
  funk2_gtk__widget__draw_rectangle(&(__funk2.gtk), gtk_widget, (filled != nil) ? TRUE : FALSE, x__i, y__i, width__i, height__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__draw_rectangle(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
  if ((! raw__gtk_widget__is_type(cause, widget)) ||
      (! raw__integer__is_type(cause, x)) ||
      (! raw__integer__is_type(cause, y)) ||
      (! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__widget__draw_rectangle(cause, widget, filled, x, y, width, height);
}
def_pcfunk6(gtk__widget__draw_rectangle, widget, filled, x, y, width, height, return f2__gtk__widget__draw_rectangle(this_cause, widget, filled, x, y, width, height));


// box

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

f2ptr f2__gtk__box__pack_start(f2ptr cause, f2ptr box, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding) {
  if ((! raw__gtk_widget__is_type(cause, box)) ||
      (! raw__gtk_widget__is_type(cause, child_widget)) ||
      (! raw__integer__is_type(cause, padding))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__box__pack_start(cause, box, child_widget, expand, fill, padding);
}
def_pcfunk5(gtk__box__pack_start, box, child_widget, expand, fill, padding, return f2__gtk__box__pack_start(this_cause, box, child_widget, expand, fill, padding));


f2ptr f2__gtk__pop_callback_event(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  funk2_gtk_callback_t* callback = funk2_gtk__pop_callback_event(&(__funk2.gtk));
  if (! callback) {
    return nil;
  }
  f2ptr funk = callback->funk;
  f2ptr args = callback->args;
  return f2__gtk_callback__new(cause, funk, args);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
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


f2ptr raw__gtk__text_buffer__select_range(f2ptr cause, f2ptr text_buffer, f2ptr range) {
#if defined(F2__GTK__SUPPORTED)
  GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
  f2ptr          start_iter = f2__gtk_text_range__start(cause, range);
  f2ptr          end_iter   = f2__gtk_text_range__end(cause, range);
  GtkTextIter    gtk_start_iter;
  GtkTextIter    gtk_end_iter;
  raw__gtk_text_iter__as__GtkTextIter(cause, start_iter, &gtk_start_iter);
  raw__gtk_text_iter__as__GtkTextIter(cause, end_iter,   &gtk_end_iter);
  funk2_gtk__text_buffer__select_range(&(__funk2.gtk), gtk_text_buffer, &gtk_start_iter, &gtk_end_iter);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__select_range(f2ptr cause, f2ptr text_buffer, f2ptr range) {
  if ((! raw__gtk_text_buffer__is_type(cause, text_buffer)) ||
      (! raw__gtk_text_range__is_type(cause, range))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__text_buffer__select_range(cause, text_buffer, range);
}
def_pcfunk2(gtk__text_buffer__select_range, text_buffer, range, return f2__gtk__text_buffer__select_range(this_cause, text_buffer, range));


f2ptr raw__gtk__text_buffer__get_text(f2ptr cause, f2ptr text_buffer) {
#if defined(F2__GTK__SUPPORTED)
  GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
  char* text = funk2_gtk__text_buffer__get_text(&(__funk2.gtk), gtk_text_buffer);
  return new__string(cause, text);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__get_text(f2ptr cause, f2ptr text_buffer) {
  if (! raw__gtk_text_buffer__is_type(cause, text_buffer)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__text_buffer__get_text(cause, text_buffer);
}
def_pcfunk1(gtk__text_buffer__get_text, text_buffer, return f2__gtk__text_buffer__get_text(this_cause, text_buffer));


f2ptr raw__gtk__text_buffer__set_text(f2ptr cause, f2ptr text_buffer, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
  
  u64 text__length = raw__string__length(cause, text);
  u8* text__str    = (u8*)alloca(text__length + 1);
  raw__string__str_copy(cause, text, text__str);
  text__str[text__length] = 0;
  
  funk2_gtk__text_buffer__set_text(&(__funk2.gtk), gtk_text_buffer, text__str);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__set_text(f2ptr cause, f2ptr text_buffer, f2ptr text) {
  if ((! raw__gtk_text_buffer__is_type(cause, text_buffer)) ||
      (! raw__string__is_type(cause, text))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__text_buffer__set_text(cause, text_buffer, text);
}
def_pcfunk2(gtk__text_buffer__set_text, text_buffer, text, return f2__gtk__text_buffer__set_text(this_cause, text_buffer, text));


f2ptr raw__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  GtkTextIter gtk_text_iter;
  raw__gtk_text_iter__as__GtkTextIter(cause, text_iter, &gtk_text_iter);
  
  u64 text__length = raw__string__length(cause, text);
  u8* text__str    = (u8*)alloca(text__length + 1);
  raw__string__str_copy(cause, text, text__str);
  text__str[text__length] = 0;
  
  GtkTextIter mstart;
  GtkTextIter mend;
  boolean_t   found = funk2_gtk__text_iter__forward_search(&(__funk2.gtk), &gtk_text_iter, text__str, &mstart, &mend);
  if (! found) {
    return nil;
  }
  return f2__gtk_text_range__new(cause, f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&mstart)), f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&mend)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text) {
  if ((! raw__gtk_text_iter__is_type(cause, text_iter)) ||
      (! raw__string__is_type(cause, text))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__text_iter__forward_search(cause, text_iter, text);
}
def_pcfunk2(gtk__text_iter__forward_search, text_iter, text, return f2__gtk__text_iter__forward_search(this_cause, text_iter, text));


// paned

f2ptr raw__gtk__paned__pack1(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_paned = raw__gtk_widget__as__GtkWidget(cause, paned);
  GtkWidget* gtk_child = raw__gtk_widget__as__GtkWidget(cause, child);
  funk2_gtk__paned__pack1(&(__funk2.gtk), gtk_paned, gtk_child, (resize != nil) ? TRUE : FALSE, (shrink != nil) ? TRUE : FALSE);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__paned__pack1(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
  if ((! inherits_from(cause, paned, gtk_widget)) ||
      (! inherits_from(cause, child, gtk_widget))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__paned__pack1(cause, paned, child, resize, shrink);
}
def_pcfunk4(gtk__paned__pack1, paned, child, resize, shrink, return f2__gtk__paned__pack1(this_cause, paned, child, resize, shrink));


f2ptr raw__gtk__paned__pack2(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_paned = raw__gtk_widget__as__GtkWidget(cause, paned);
  GtkWidget* gtk_child = raw__gtk_widget__as__GtkWidget(cause, child);
  funk2_gtk__paned__pack2(&(__funk2.gtk), gtk_paned, gtk_child, (resize != nil) ? TRUE : FALSE, (shrink != nil) ? TRUE : FALSE);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__paned__pack2(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
  if ((! inherits_from(cause, paned, gtk_widget)) ||
      (! inherits_from(cause, child, gtk_widget))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__paned__pack2(cause, paned, child, resize, shrink);
}
def_pcfunk4(gtk__paned__pack2, paned, child, resize, shrink, return f2__gtk__paned__pack2(this_cause, paned, child, resize, shrink));


//void funk2_gtk__paned__set_position(funk2_gtk_t* this, GtkWidget* paned, s64 position) {

f2ptr raw__gtk__paned__set_position(f2ptr cause, f2ptr paned, f2ptr position) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_paned   = raw__gtk_widget__as__GtkWidget(cause, paned);
  s64        position__i = f2integer__i(position, cause);
  funk2_gtk__paned__set_position(&(__funk2.gtk), gtk_paned, position__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__paned__set_position(f2ptr cause, f2ptr paned, f2ptr position) {
  if ((! inherits_from(cause, paned,    gtk_widget)) ||
      (! inherits_from(cause, position, integer))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__paned__set_position(cause, paned, position);
}
def_pcfunk2(gtk__paned__set_position, paned, position, return f2__gtk__paned__set_position(this_cause, paned, position));


// vpaned

f2ptr raw__gtk__vpaned__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = funk2_gtk__vpaned__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__vpaned__new(f2ptr cause) {
  return raw__gtk__vpaned__new(cause);
}
def_pcfunk0(gtk__vpaned__new, return f2__gtk__vpaned__new(this_cause));


// hpaned

f2ptr raw__gtk__hpaned__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = funk2_gtk__hpaned__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__hpaned__new(f2ptr cause) {
  return raw__gtk__hpaned__new(cause);
}
def_pcfunk0(gtk__hpaned__new, return f2__gtk__hpaned__new(this_cause));


// progress_bar

f2ptr raw__gtk__progress_bar__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = funk2_gtk__progress_bar__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__new(f2ptr cause) {
  return raw__gtk__progress_bar__new(cause);
}
def_pcfunk0(gtk__progress_bar__new, return f2__gtk__progress_bar__new(this_cause));


f2ptr raw__gtk__progress_bar__set_fraction(f2ptr cause, f2ptr this, f2ptr fraction) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_this        = raw__gtk_widget__as__GtkWidget(cause, this);
  f2ptr      fraction_double = f2__number__as__double(cause, fraction);
  if (! raw__double__is_type(cause, fraction_double)) {
    return f2larva__new(cause, 1, nil);
  }
  double fraction_double__d = f2double__d(fraction_double, cause);
  funk2_gtk__progress_bar__set_fraction(gtk_this, fraction_double__d);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__set_fraction(f2ptr cause, f2ptr this, f2ptr fraction) {
  if (! raw__gtk_widget__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__progress_bar__set_fraction(cause, this, fraction);
}
def_pcfunk2(gtk__progress_bar__set_fraction, this, fraction, return f2__gtk__progress_bar__set_fraction(this_cause, this, fraction));


// notebook

f2ptr raw__gtk__notebook__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_widget = funk2_gtk__notebook__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__new(f2ptr cause) {
  return raw__gtk__notebook__new(cause);
}
def_pcfunk0(gtk__notebook__new, return f2__gtk__notebook__new(this_cause));


f2ptr raw__gtk__notebook__append_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_notebook  = raw__gtk_widget__as__GtkWidget(cause, notebook);
  GtkWidget* gtk_child     = raw__gtk_widget__as__GtkWidget(cause, child);
  GtkWidget* gtk_tab_label = raw__gtk_widget__as__GtkWidget(cause, tab_label);
  s64 index = funk2_gtk__notebook__append_page(&(__funk2.gtk), gtk_notebook, gtk_child, gtk_tab_label);
  if (index == -1) {
    return nil;
  }
  return f2integer__new(cause, index);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__append_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
  if ((! raw__gtk_widget__is_type(cause, notebook)) ||
      (! raw__gtk_widget__is_type(cause, child)) ||
      (! raw__gtk_widget__is_type(cause, tab_label))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__notebook__append_page(cause, notebook, child, tab_label);
}
def_pcfunk3(gtk__notebook__append_page, notebook, child, tab_label, return f2__gtk__notebook__append_page(this_cause, notebook, child, tab_label));


f2ptr raw__gtk__notebook__prepend_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_notebook  = raw__gtk_widget__as__GtkWidget(cause, notebook);
  GtkWidget* gtk_child     = raw__gtk_widget__as__GtkWidget(cause, child);
  GtkWidget* gtk_tab_label = raw__gtk_widget__as__GtkWidget(cause, tab_label);
  s64 index = funk2_gtk__notebook__prepend_page(&(__funk2.gtk), gtk_notebook, gtk_child, gtk_tab_label);
  if (index == -1) {
    return nil;
  }
  return f2integer__new(cause, index);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__prepend_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
  if ((! raw__gtk_widget__is_type(cause, notebook)) ||
      (! raw__gtk_widget__is_type(cause, child)) ||
      (! raw__gtk_widget__is_type(cause, tab_label))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__notebook__prepend_page(cause, notebook, child, tab_label);
}
def_pcfunk3(gtk__notebook__prepend_page, notebook, child, tab_label, return f2__gtk__notebook__prepend_page(this_cause, notebook, child, tab_label));


f2ptr raw__gtk__notebook__insert_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label, f2ptr position) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_notebook  = raw__gtk_widget__as__GtkWidget(cause, notebook);
  GtkWidget* gtk_child     = raw__gtk_widget__as__GtkWidget(cause, child);
  GtkWidget* gtk_tab_label = raw__gtk_widget__as__GtkWidget(cause, tab_label);
  s64        position__i   = f2integer__i(position, cause);
  s64 index = funk2_gtk__notebook__insert_page(&(__funk2.gtk), gtk_notebook, gtk_child, gtk_tab_label, position__i);
  if (index == -1) {
    return nil;
  }
  return f2integer__new(cause, index);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__insert_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label, f2ptr position) {
  if ((! raw__gtk_widget__is_type(cause, notebook)) ||
      (! raw__gtk_widget__is_type(cause, child)) ||
      (! raw__gtk_widget__is_type(cause, tab_label)) ||
      (! raw__integer__is_type(cause, position))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__notebook__insert_page(cause, notebook, child, tab_label, position);
}
def_pcfunk4(gtk__notebook__insert_page, notebook, child, tab_label, position, return f2__gtk__notebook__insert_page(this_cause, notebook, child, tab_label, position));


f2ptr raw__gtk__notebook__remove_page(f2ptr cause, f2ptr notebook, f2ptr position) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_notebook = raw__gtk_widget__as__GtkWidget(cause, notebook);
  s64        position__i  = f2integer__i(position, cause);
  funk2_gtk__notebook__remove_page(&(__funk2.gtk), gtk_notebook, position__i);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__remove_page(f2ptr cause, f2ptr notebook, f2ptr position) {
  if ((! raw__gtk_widget__is_type(cause, notebook)) ||
      (! raw__integer__is_type(cause, position))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__notebook__remove_page(cause, notebook, position);
}
def_pcfunk2(gtk__notebook__remove_page, notebook, position, return f2__gtk__notebook__remove_page(this_cause, notebook, position));


f2ptr raw__gtk__notebook__get_current_page(f2ptr cause, f2ptr notebook) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_notebook = raw__gtk_widget__as__GtkWidget(cause, notebook);
  s64 index = funk2_gtk__notebook__get_current_page(&(__funk2.gtk), gtk_notebook);
  if (index == -1) {
    return nil;
  }
  return f2integer__new(cause, index);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__get_current_page(f2ptr cause, f2ptr notebook) {
  if (! raw__gtk_widget__is_type(cause, notebook)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__notebook__get_current_page(cause, notebook);
}
def_pcfunk1(gtk__notebook__get_current_page, notebook, return f2__gtk__notebook__get_current_page(this_cause, notebook));


f2ptr raw__gtk__notebook__set_scrollable(f2ptr cause, f2ptr notebook, f2ptr scrollable) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* gtk_notebook = raw__gtk_widget__as__GtkWidget(cause, notebook);
  funk2_gtk__notebook__set_scrollable(&(__funk2.gtk), gtk_notebook, (scrollable != nil) ? TRUE : FALSE);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__set_scrollable(f2ptr cause, f2ptr notebook, f2ptr scrollable) {
  if (! raw__gtk_widget__is_type(cause, notebook)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__notebook__set_scrollable(cause, notebook, scrollable);
}
def_pcfunk2(gtk__notebook__set_scrollable, notebook, scrollable, return f2__gtk__notebook__set_scrollable(this_cause, notebook, scrollable));


// label

f2ptr raw__gtk__label__new(f2ptr cause, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  u64 text__length = raw__string__length(cause, text);
  u8* text__str    = (u8*)alloca(text__length + 1);
  raw__string__str_copy(cause, text, text__str);
  text__str[text__length] = 0;
  
  GtkWidget* label = funk2_gtk__label__new(&(__funk2.gtk), text__str);
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(label)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__label__new(f2ptr cause, f2ptr text) {
  if (! raw__string__is_type(cause, text)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__label__new(cause, text);
}
def_pcfunk1(gtk__label__new, text, return f2__gtk__label__new(this_cause, text));


// drawing_area

f2ptr raw__gtk__drawing_area__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  GtkWidget* drawing_area = funk2_gtk__drawing_area__new(&(__funk2.gtk));
  return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(drawing_area)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__drawing_area__new(f2ptr cause) {
  return raw__gtk__drawing_area__new(cause);
}
def_pcfunk0(gtk__drawing_area__new, return f2__gtk__drawing_area__new(this_cause));


// table

f2ptr raw__gtk__table__new(f2ptr cause, f2ptr rows, f2ptr columns, f2ptr homogenous) {
#if defined(F2__GTK__SUPPORTED)
  s64 rows__i    = f2integer__i(rows,    cause);
  s64 columns__i = f2integer__i(columns, cause);
  funk2_gtk__table__new(&(__funk2.gtk), rows__i, columns__i, (homogenous != nil) ? TRUE : FALSE);
  return nil;
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__table__new(f2ptr cause, f2ptr rows, f2ptr columns, f2ptr homogenous) {
  if ((! raw__integer__is_type(cause, rows)) ||
      (! raw__integer__is_type(cause, columns))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__table__new(cause, rows, columns, homogenous);
}
def_pcfunk3(gtk__table__new, rows, columns, homogenous, return f2__gtk__table__new(this_cause, rows, columns, homogenous));


//void funk2_gtk__table__attach(funk2_gtk_t* this, GtkWidget* table, GtkWidget* child, u64 left_attach, u64 right_attach, u64 top_attach, u64 bottom_attach, u64 xpadding, u64 ypadding) {

f2ptr raw__gtk__table__attach(f2ptr cause, f2ptr table, f2ptr child, f2ptr left_attach, f2ptr right_attach, f2ptr top_attach, f2ptr bottom_attach, f2ptr xpadding, f2ptr ypadding) {
  GtkWidget* gtk_table        = raw__gtk_widget__as__GtkWidget(cause, table);
  GtkWidget* gtk_child        = raw__gtk_widget__as__GtkWidget(cause, child);
  s64        left_attach__i   = f2integer__i(left_attach, cause);
  s64        right_attach__i  = f2integer__i(right_attach, cause);
  s64        top_attach__i    = f2integer__i(top_attach, cause);
  s64        bottom_attach__i = f2integer__i(bottom_attach, cause);
  s64        xpadding__i      = f2integer__i(xpadding, cause);
  s64        ypadding__i      = f2integer__i(ypadding, cause);
  funk2_gtk__table__attach(&(__funk2.gtk), gtk_table, gtk_child, left_attach__i, right_attach__i, top_attach__i, bottom_attach__i, xpadding__i, ypadding__i);
}

f2ptr f2__gtk__table__attach(f2ptr cause, f2ptr table, f2ptr child, f2ptr left_attach, f2ptr right_attach, f2ptr top_attach, f2ptr bottom_attach, f2ptr xpadding, f2ptr ypadding) {
  if ((! raw__gtk_widget__is_type(cause, table)) ||
      (! raw__gtk_widget__is_type(cause, child)) ||
      (! raw__integer__is_type(cause, left_attach)) ||
      (! raw__integer__is_type(cause, right_attach)) ||
      (! raw__integer__is_type(cause, top_attach)) ||
      (! raw__integer__is_type(cause, bottom_attach)) ||
      (! raw__integer__is_type(cause, xpadding)) ||
      (! raw__integer__is_type(cause, ypadding))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__gtk__table__attach(cause, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding);
}
def_pcfunk8(gtk__table__attach, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding, return f2__gtk__table__attach(this_cause, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding));


// **

void f2__gtk__reinitialize_globalvars() {
}

void f2__gtk__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "gtk", "", &f2__string__reinitialize_globalvars);
  
  f2__string__reinitialize_globalvars();
  
  // gtk_widget
  
  init_frame_object__1_slot(gtk_widget, pointer);
  
  
  // gtk_box
  
  init_frame_object__1_slot(gtk_box, pointer);
  
  
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
  

  f2__primcfunk__init__0(gtk__is_supported,                                                                            "Returns true if GIMP ToolKit (GTK) support has been compiled into this version of Funk2.");
  
  // expose_event
  
  f2__primcfunk__init__3(gtk__expose_event__signal_connect,       widget, funk, args,                                  "Connects an expose_event signal handler to a GtkWidget.");
  
  // widget
  
  f2__primcfunk__init__1(gtk__widget__show_all,                   widget,                                              "Shows the widget and all children.");
  f2__primcfunk__init__3(gtk__widget__set_size_request,           widget, width, height,                               "Requests that the widget be a specific size.");
  f2__primcfunk__init__5(gtk__widget__queue_draw_area,            widget, x, y, width, height,                         "Requests that a specific rectangle of the widget be redrawn.");
  f2__primcfunk__init__8(gtk__widget__draw_arc,                   widget, filled, x, y, width, height, angle1, angle2, "Draws an arc in a GtkWidget.  Only works with GtkWidgets that have a GdkWindow!");
  f2__primcfunk__init__6(gtk__widget__draw_rectangle,             widget, filled, x, y, width, height,                 "Draws a rectangle in a GtkWidget.  Only works with GtkWidgets that have a GdkWindow!");
  f2__primcfunk__init__0(gtk__window__new,                                                                             "Returns a new window widget.");
  f2__primcfunk__init__2(gtk__window__set_title,                  window, title,                                       "Sets the title of this gtk_window.");
  f2__primcfunk__init__3(gtk__window__set_default_size,           window, width, height,                               "Sets the default width and height of this gtk_window.");
  f2__primcfunk__init__1(gtk__vbox__new,                          row_count,                                           "Returns a new vbox widget with row_count rows.");
  f2__primcfunk__init__1(gtk__hbox__new,                          column_count,                                        "Returns a new hbox widget with column_count columns.");
  f2__primcfunk__init__1(gtk__button__new_with_label,             label,                                               "Returns a new button widget with label.");
  f2__primcfunk__init__0(gtk__entry__new,                                                                              "Returns a new entry widget.");
  f2__primcfunk__init__1(gtk__entry__get_text,                    widget,                                              "Returns the text of an entry widget as a string.");
  f2__primcfunk__init__0(gtk__scrolled_window__new,                                                                    "Returns a new scrolled_window widget.");
  f2__primcfunk__init__2(gtk__scrolled_window__add_with_viewport, scrolled_window, child,                              "Adds a non-scrollable widget to a scroll window.");
  f2__primcfunk__init__0(gtk__text_view__new,                                                                          "Returns a new text_view widget.");
  f2__primcfunk__init__1(gtk__text_view__get_buffer,              text_view,                                           "Returns the buffer widget of a text_view widget.");
  

  f2__primcfunk__init__2(gtk__container__add,                     widget, add_widget,                                  "Adds a widget to a container.");
  f2__primcfunk__init__5(gtk__box__pack_start,                    widget, child_widget, expand, fill, padding,         "Packs a child widget in a box.");
  f2__primcfunk__init__4(gtk__signal_connect,                     widget, signal_name, funk, args,                     "Creates a callback for a widget (see gtk-pop_callback_event).");
  f2__primcfunk__init__0(gtk__pop_callback_event,                                                                      "Returns the next waiting callback event, if one exists, nil otherwise.");
  f2__primcfunk__init__1(gtk__text_buffer__get_start_iter,        text_buffer,                                         "Returns the starting text_iter of a text_buffer.");
  f2__primcfunk__init__2(gtk__text_buffer__select_range,          text_buffer, range,                                  "Sets select range in this text_buffer.");
  f2__primcfunk__init__1(gtk__text_buffer__get_text,              text_buffer,                                         "Gets the text as a string from a gtk text_buffer widget.");
  f2__primcfunk__init__2(gtk__text_buffer__set_text,              text_buffer, text,                                   "Sets the text for a gtk text_buffer widget.");
  f2__primcfunk__init__2(gtk__text_iter__forward_search,          text_iter, text,                                     "Returns a range composed of two text_iters that represent the successful search forward from the text_iter for a string.  Returns nil on failure to find the text.");
  
  // paned
  
  f2__primcfunk__init__4(gtk__paned__pack1,        paned, child, resize, shrink, "Packs the first child of the Paned.");
  f2__primcfunk__init__4(gtk__paned__pack2,        paned, child, resize, shrink, "Packs the second child of the Paned.");
  f2__primcfunk__init__2(gtk__paned__set_position, paned, position,              "Sets the pixel position of the Paned.");
  
  // vpaned
  
  f2__primcfunk__init__0(gtk__vpaned__new, "Returns a new GtkVPaned widget.");

  // hpaned

  f2__primcfunk__init__0(gtk__hpaned__new, "Returns a new GtkHPaned widget.");
  
  // progress_bar
  
  f2__primcfunk__init__0(gtk__progress_bar__new,                          "Returns a new GtkProgressBar widget.");
  f2__primcfunk__init__2(gtk__progress_bar__set_fraction, this, fraction, "Sets the fraction done of the progress bar.");
  
  // notebook
  
  f2__primcfunk__init__0(gtk__notebook__new,                                                    "Returns a new GtkNotebook widget.");
  f2__primcfunk__init__3(gtk__notebook__append_page,      notebook, child, tab_label,           "Adds a new GtkNotebookPage to the end of GtkNotebook.");
  f2__primcfunk__init__3(gtk__notebook__prepend_page,     notebook, child, tab_label,           "Adds a new GtkNotebookPage to the beginning of a GtkNotebook.");
  f2__primcfunk__init__4(gtk__notebook__insert_page,      notebook, child, tab_label, position, "Inserts a new GtkNotebookPage to a specific position within a GtkNotebook.");
  f2__primcfunk__init__4(gtk__notebook__remove_page,      notebook, child, tab_label, position, "Removes the GtkNotebookPage at a specific position within a GtkNotebook");
  f2__primcfunk__init__1(gtk__notebook__get_current_page, notebook,                             "Returns the index of the current page in a GtkNotebook.");
  f2__primcfunk__init__2(gtk__notebook__set_scrollable,   notebook, scrollable,                 "Sets a GtkNotebook to be either scollable (True) [t] or not scrollable (False) [nil].");
  
  // label
  
  f2__primcfunk__init__1(gtk__label__new, text, "Returns a new GtkLabel.");
  
  // drawing_area
  
  f2__primcfunk__init__0(gtk__drawing_area__new, "Returns a new GtkDrawingArea.");
  
  // table
  
  f2__primcfunk__init__3(gtk__table__new,    rows, columns, homogenous,                                                              "Returns a new GtkTable.");
  f2__primcfunk__init__8(gtk__table__attach, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding, "Adds a child GtkWidget to the GtkTable.");
  
  
}


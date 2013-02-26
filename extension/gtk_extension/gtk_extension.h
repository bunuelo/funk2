// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__GTK_EXTENSION__TYPES__H
#define F2__GTK_EXTENSION__TYPES__H

#include "../../c/funk2.h"

#ifndef XLIB_IMAGE_SIDE_SIZE_LIMIT
#define XLIB_IMAGE_SIDE_SIZE_LIMIT ((s64)(0xffffull))
#endif // XLIB_IMAGE_SIDE_SIZE_LIMIT

typedef enum   funk2_gtk_callback_args_type_e  funk2_gtk_callback_args_type_t;
typedef struct funk2_gtk_callback_s            funk2_gtk_callback_t;
typedef struct funk2_gtk_callback_event_s      funk2_gtk_callback_event_t;
typedef struct funk2_gtk_callback_cons_s       funk2_gtk_callback_cons_t;
typedef struct funk2_gtk_callback_event_cons_s funk2_gtk_callback_event_cons_t;
typedef struct funk2_gtk_s                     funk2_gtk_t;

enum funk2_gtk_callback_args_type_e {
  funk2_gtk_callback_args_type__nil = 0,
  funk2_gtk_callback_args_type__expose,
  funk2_gtk_callback_args_type__key_press,
  funk2_gtk_callback_args_type__response,
  funk2_gtk_callback_args_type__update_preview,
  funk2_gtk_callback_args_type__value_changed,
  funk2_gtk_callback_args_type__size_allocate
};

struct funk2_gtk_callback_s {
  f2ptr                          cause;
  f2ptr                          funk;
  f2ptr                          args;
  funk2_gtk_callback_args_type_t args_type;
};

struct funk2_gtk_callback_cons_s {
  funk2_gtk_callback_t*      callback;
  funk2_gtk_callback_cons_t* next;
};

struct funk2_gtk_callback_event_s {
  funk2_gtk_callback_t* callback;
  void*                 args;
};

struct funk2_gtk_callback_event_cons_s {
  funk2_gtk_callback_event_t*      callback_event;
  funk2_gtk_callback_event_cons_t* next;
};

struct funk2_gtk_s {
  boolean_t                        initialized_successfully;
  
  funk2_processor_mutex_t          main_thread__mutex;
  boolean_t                        main_thread__active;
  funk2_processor_thread_t*        main_thread;
  
  funk2_processor_mutex_t          callbacks__mutex;
  funk2_gtk_callback_cons_t*       callbacks;
  
  funk2_processor_mutex_t          callback_events__mutex;
  funk2_gtk_callback_event_cons_t* callback_events;
  funk2_gtk_callback_event_cons_t* callback_events__last_cons;
  
  f2ptr                            session_symbol;
};

#endif // F2__GTK_EXTENSION__TYPES__H


#ifndef F2__GTK_EXTENSION__H
#define F2__GTK_EXTENSION__H

#include "../../c/funk2.h"

// g_object

f2ptr f2g_object__primobject_type__new(f2ptr cause);

// gtk_widget

f2ptr f2gtk_widget__primobject_type__new_aux(f2ptr cause);


// gtk_box

f2ptr f2gtk_box__primobject_type__new_aux(f2ptr cause);


// gtk_label

f2ptr f2gtk_label__primobject_type__new_aux(f2ptr cause);


// gtk_scale

f2ptr f2gtk_scale__primobject_type__new_aux(f2ptr cause);


// gtk_entry

f2ptr f2gtk_entry__primobject_type__new_aux(f2ptr cause);


// gtk_text_buffer

f2ptr f2gtk_text_buffer__primobject_type__new_aux(f2ptr cause);


// gdk_pixbuf

f2ptr f2gdk_pixbuf__primobject_type__new_aux(f2ptr cause);


// gtk_text_iter

f2ptr f2gtk_text_iter__primobject_type__new(f2ptr cause);


// gtk_callback

f2ptr f2gtk_callback__primobject_type__new(f2ptr cause);


// gtk_text_mark

f2ptr f2gtk_text_mark__primobject_type__new(f2ptr cause);


// gtk_text_range

f2ptr f2gtk_text_range__primobject_type__new(f2ptr cause);


// gtk_progress_bar

f2ptr f2gtk_progress_bar__primobject_type__new_aux(f2ptr cause);


// gtk_menu_bar

f2ptr f2gtk_menu_bar__primobject_type__new_aux(f2ptr cause);


// gtk_menu

f2ptr f2gtk_menu__primobject_type__new_aux(f2ptr cause);


// gtk_check_button

f2ptr f2gtk_check_button__primobject_type__new_aux(f2ptr cause);


// gtk_file_chooser_dialog

f2ptr f2gtk_file_chooser_dialog__primobject_type__new_aux(f2ptr cause);


// gtk_image

f2ptr f2gtk_image__primobject_type__new_aux(f2ptr cause);


// funk2_gtk

void funk2_gtk__init              (funk2_gtk_t* this, int* argv, char*** argc);
void funk2_gtk__start_gtk_main    (funk2_gtk_t* this);
void funk2_gtk__destroy           (funk2_gtk_t* this);
void funk2_gtk__add_callback      (funk2_gtk_t* this, funk2_gtk_callback_t* callback);
void funk2_gtk__add_callback_event(funk2_gtk_t* this, funk2_gtk_callback_t* callback, void* args);


// user-space funktions

boolean_t raw__gtk__is_supported(f2ptr cause);
f2ptr      f2__gtk__is_supported(f2ptr cause);


// window

f2ptr raw__gtk__window__new(f2ptr cause);
f2ptr  f2__gtk__window__new(f2ptr cause);
f2ptr raw__gtk__window__set_title(f2ptr cause, f2ptr window, f2ptr title);
f2ptr  f2__gtk__window__set_title(f2ptr cause, f2ptr window, f2ptr title);
f2ptr raw__gtk__window__set_default_size(f2ptr cause, f2ptr window, f2ptr width, f2ptr height);
f2ptr  f2__gtk__window__set_default_size(f2ptr cause, f2ptr window, f2ptr width, f2ptr height);


// vbox

f2ptr raw__gtk__vbox__new(f2ptr cause, f2ptr spacing);
f2ptr  f2__gtk__vbox__new(f2ptr cause, f2ptr spacing);


// hbox

f2ptr raw__gtk__hbox__new(f2ptr cause, f2ptr spacing);
f2ptr  f2__gtk__hbox__new(f2ptr cause, f2ptr spacing);


// button

f2ptr raw__gtk__button__new_with_label(f2ptr cause, f2ptr label);
f2ptr  f2__gtk__button__new_with_label(f2ptr cause, f2ptr label);


// entry

f2ptr raw__gtk__entry__new(f2ptr cause);
f2ptr  f2__gtk__entry__new(f2ptr cause);
f2ptr raw__gtk__entry__get_text(f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__entry__get_text(f2ptr cause, f2ptr widget);


// scrolled_window

f2ptr raw__gtk__scrolled_window__new(              f2ptr cause);
f2ptr  f2__gtk__scrolled_window__new(              f2ptr cause);
f2ptr raw__gtk__scrolled_window__add_with_viewport(f2ptr cause, f2ptr scrolled_window, f2ptr child);
f2ptr  f2__gtk__scrolled_window__add_with_viewport(f2ptr cause, f2ptr scrolled_window, f2ptr child);
f2ptr raw__gtk__scrolled_window__set_policy(       f2ptr cause, f2ptr scrolled_window, f2ptr hscrollbar_policy, f2ptr vscrollbar_policy);
f2ptr  f2__gtk__scrolled_window__set_policy(       f2ptr cause, f2ptr scrolled_window, f2ptr hscrollbar_policy, f2ptr vscrollbar_policy);


// text_view

f2ptr raw__gtk__text_view__new(f2ptr cause);
f2ptr  f2__gtk__text_view__new(f2ptr cause);
f2ptr raw__gtk__text_view__get_buffer(f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__text_view__get_buffer(f2ptr cause, f2ptr widget);


// container

f2ptr raw__gtk__container__add    (f2ptr cause, f2ptr widget, f2ptr add_widget);
f2ptr  f2__gtk__container__add    (f2ptr cause, f2ptr widget, f2ptr add_widget);
f2ptr raw__gtk__container__remove (f2ptr cause, f2ptr widget, f2ptr remove_widget);
f2ptr  f2__gtk__container__remove (f2ptr cause, f2ptr widget, f2ptr remove_widget);
f2ptr raw__gtk__container__replace(f2ptr cause, f2ptr widget, f2ptr remove_widget, f2ptr add_widget);
f2ptr  f2__gtk__container__replace(f2ptr cause, f2ptr widget, f2ptr remove_widget, f2ptr add_widget);


// expose_event

f2ptr raw__gtk__expose_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args);
f2ptr  f2__gtk__expose_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args);


// works for 'clicked' event but not 'expose_event'

f2ptr raw__gtk__signal_connect(f2ptr cause, f2ptr widget, f2ptr signal_name, f2ptr funk, f2ptr args);
f2ptr  f2__gtk__signal_connect(f2ptr cause, f2ptr widget, f2ptr signal_name, f2ptr funk, f2ptr args);


// widget

f2ptr raw__gtk__widget__show_all              (f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__widget__show_all              (f2ptr cause, f2ptr widget);
f2ptr raw__gtk__widget__hide_all              (f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__widget__hide_all              (f2ptr cause, f2ptr widget);
f2ptr raw__gtk__widget__set_size_request      (f2ptr cause, f2ptr widget, f2ptr width, f2ptr height);
f2ptr  f2__gtk__widget__set_size_request      (f2ptr cause, f2ptr widget, f2ptr width, f2ptr height);
f2ptr raw__gtk__widget__get_visible           (f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__widget__get_visible           (f2ptr cause, f2ptr widget);
f2ptr raw__gtk__widget__destroy               (f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__widget__destroy               (f2ptr cause, f2ptr widget);
f2ptr raw__gtk__widget__connect_hide_on_delete(f2ptr cause, f2ptr widget);
f2ptr  f2__gtk__widget__connect_hide_on_delete(f2ptr cause, f2ptr widget);
f2ptr raw__gtk__widget__modify_fg             (f2ptr cause, f2ptr widget, f2ptr state, f2ptr color);
f2ptr  f2__gtk__widget__modify_fg             (f2ptr cause, f2ptr widget, f2ptr state, f2ptr color);
f2ptr raw__gtk__widget__modify_bg             (f2ptr cause, f2ptr widget, f2ptr state, f2ptr color);
f2ptr  f2__gtk__widget__modify_bg             (f2ptr cause, f2ptr widget, f2ptr state, f2ptr color);
f2ptr raw__gtk__widget__set_sensitive         (f2ptr cause, f2ptr widget, f2ptr sensitive);
f2ptr  f2__gtk__widget__set_sensitive         (f2ptr cause, f2ptr widget, f2ptr sensitive);


// beginning of GtkWidget drawing fuctions, which are not really GtkWidget functions in the GTK library.

f2ptr raw__gtk__widget__queue_draw_area(f2ptr cause, f2ptr widget, f2ptr x, f2ptr y, f2ptr width, f2ptr height);
f2ptr  f2__gtk__widget__queue_draw_area(f2ptr cause, f2ptr widget, f2ptr x, f2ptr y, f2ptr width, f2ptr height);
f2ptr raw__gtk__widget__draw_arc(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height, f2ptr angle1, f2ptr angle2);
f2ptr  f2__gtk__widget__draw_arc(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height, f2ptr angle1, f2ptr angle2);
f2ptr raw__gtk__widget__draw_rectangle(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height);
f2ptr  f2__gtk__widget__draw_rectangle(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height);


// misc (GtkMisc)

f2ptr raw__gtk__misc__set_alignment(f2ptr cause, f2ptr misc, f2ptr xalign, f2ptr yalign);
f2ptr  f2__gtk__misc__set_alignment(f2ptr cause, f2ptr misc, f2ptr xalign, f2ptr yalign);


// box

f2ptr raw__gtk__box__pack_start(f2ptr cause, f2ptr widget, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding);
f2ptr  f2__gtk__box__pack_start(f2ptr cause, f2ptr box, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding);

  // text_buffer

f2ptr raw__gtk__text_buffer__get_start_iter(f2ptr cause, f2ptr text_buffer);
f2ptr  f2__gtk__text_buffer__get_start_iter(f2ptr cause, f2ptr text_buffer);
f2ptr raw__gtk__text_buffer__select_range(f2ptr cause, f2ptr text_buffer, f2ptr range);
f2ptr  f2__gtk__text_buffer__select_range(f2ptr cause, f2ptr text_buffer, f2ptr range);
f2ptr raw__gtk__text_buffer__get_text(f2ptr cause, f2ptr text_buffer);
f2ptr  f2__gtk__text_buffer__get_text(f2ptr cause, f2ptr text_buffer);
f2ptr raw__gtk__text_buffer__set_text(f2ptr cause, f2ptr text_buffer, f2ptr text);
f2ptr  f2__gtk__text_buffer__set_text(f2ptr cause, f2ptr text_buffer, f2ptr text);
f2ptr raw__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text);
f2ptr  f2__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text);


// paned

f2ptr raw__gtk__paned__pack1(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink);
f2ptr  f2__gtk__paned__pack1(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink);
f2ptr raw__gtk__paned__pack2(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink);
f2ptr  f2__gtk__paned__pack2(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink);
f2ptr raw__gtk__paned__set_position(f2ptr cause, f2ptr paned, f2ptr position);
f2ptr  f2__gtk__paned__set_position(f2ptr cause, f2ptr paned, f2ptr position);


// vpaned

f2ptr raw__gtk__vpaned__new(f2ptr cause);
f2ptr  f2__gtk__vpaned__new(f2ptr cause);


// hpaned

f2ptr raw__gtk__hpaned__new(f2ptr cause);
f2ptr  f2__gtk__hpaned__new(f2ptr cause);


// color

f2ptr f2__gdk__color__new(f2ptr cause, f2ptr pixel, f2ptr red, f2ptr green, f2ptr blue);
f2ptr f2__gdk__rgb_color__new(f2ptr cause, f2ptr red, f2ptr green, f2ptr blue);


// progress_bar

f2ptr raw__gtk__progress_bar__new(f2ptr cause);
f2ptr  f2__gtk__progress_bar__new(f2ptr cause);
f2ptr raw__gtk__progress_bar__set_fraction(f2ptr cause, f2ptr this, f2ptr fraction);
f2ptr  f2__gtk__progress_bar__set_fraction(f2ptr cause, f2ptr this, f2ptr fraction);
f2ptr raw__gtk__progress_bar__set_text(f2ptr cause, f2ptr this, f2ptr text);
f2ptr  f2__gtk__progress_bar__set_text(f2ptr cause, f2ptr this, f2ptr text);
f2ptr raw__gtk__progress_bar__set_orientation(f2ptr cause, f2ptr this, f2ptr orientation);
f2ptr  f2__gtk__progress_bar__set_orientation(f2ptr cause, f2ptr this, f2ptr orientation);
f2ptr raw__gtk__progress_bar__pulse(f2ptr cause, f2ptr this);
f2ptr  f2__gtk__progress_bar__pulse(f2ptr cause, f2ptr this);
f2ptr raw__gtk__progress_bar__set_pulse_step(f2ptr cause, f2ptr this, f2ptr fraction);
f2ptr  f2__gtk__progress_bar__set_pulse_step(f2ptr cause, f2ptr this, f2ptr fraction);


// notebook

f2ptr raw__gtk__notebook__new(f2ptr cause);
f2ptr f2__gtk__notebook__new(f2ptr cause);
f2ptr raw__gtk__notebook__append_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label);
f2ptr f2__gtk__notebook__append_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label);
f2ptr raw__gtk__notebook__prepend_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label);
f2ptr f2__gtk__notebook__prepend_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label);
f2ptr raw__gtk__notebook__insert_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label, f2ptr position);
f2ptr f2__gtk__notebook__insert_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label, f2ptr position);
f2ptr raw__gtk__notebook__remove_page(f2ptr cause, f2ptr notebook, f2ptr position);
f2ptr f2__gtk__notebook__remove_page(f2ptr cause, f2ptr notebook, f2ptr position);
f2ptr raw__gtk__notebook__get_current_page(f2ptr cause, f2ptr notebook);
f2ptr f2__gtk__notebook__get_current_page(f2ptr cause, f2ptr notebook);
f2ptr raw__gtk__notebook__set_scrollable(f2ptr cause, f2ptr notebook, f2ptr scrollable);
f2ptr f2__gtk__notebook__set_scrollable(f2ptr cause, f2ptr notebook, f2ptr scrollable);


// label

f2ptr raw__gtk__label__new(f2ptr cause, f2ptr text);
f2ptr f2__gtk__label__new(f2ptr cause, f2ptr text);
f2ptr raw__gtk__label__set_text(f2ptr cause, f2ptr label, f2ptr text);
f2ptr f2__gtk__label__set_text(f2ptr cause, f2ptr label, f2ptr text);
f2ptr raw__gtk__label__set_selectable(f2ptr cause, f2ptr label, f2ptr selectable);
f2ptr f2__gtk__label__set_selectable(f2ptr cause, f2ptr label, f2ptr selectable);


// drawing_area

f2ptr raw__gtk__drawing_area__new(f2ptr cause);
f2ptr f2__gtk__drawing_area__new(f2ptr cause);


// table

f2ptr raw__gtk__table__new(f2ptr cause, f2ptr rows, f2ptr columns, f2ptr homogenous);
f2ptr  f2__gtk__table__new(f2ptr cause, f2ptr rows, f2ptr columns, f2ptr homogenous);
f2ptr raw__gtk__table__attach(f2ptr cause, f2ptr table, f2ptr child, f2ptr left_attach, f2ptr right_attach, f2ptr top_attach, f2ptr bottom_attach, f2ptr xpadding, f2ptr ypadding);
f2ptr  f2__gtk__table__attach(f2ptr cause, f2ptr table, f2ptr child, f2ptr left_attach, f2ptr right_attach, f2ptr top_attach, f2ptr bottom_attach, f2ptr xpadding, f2ptr ypadding);


// frame

f2ptr raw__gtk__frame__new(f2ptr cause, f2ptr label);
f2ptr  f2__gtk__frame__new(f2ptr cause, f2ptr label);


// menu_bar

f2ptr raw__gtk__menu_bar__new(f2ptr cause);
f2ptr  f2__gtk__menu_bar__new(f2ptr cause);
f2ptr raw__gtk__menu_bar__append(f2ptr cause, f2ptr menu_bar, f2ptr append_widget);
f2ptr  f2__gtk__menu_bar__append(f2ptr cause, f2ptr menu_bar, f2ptr append_widget);


// menu_item

f2ptr raw__gtk__menu_item__new(f2ptr cause, f2ptr label);
f2ptr  f2__gtk__menu_item__new(f2ptr cause, f2ptr label);
f2ptr raw__gtk__menu_item__set_submenu(f2ptr cause, f2ptr widget, f2ptr submenu);
f2ptr  f2__gtk__menu_item__set_submenu(f2ptr cause, f2ptr widget, f2ptr submenu);


// menu

f2ptr raw__gtk__menu__new(f2ptr cause);
f2ptr  f2__gtk__menu__new(f2ptr cause);
f2ptr raw__gtk__menu__append(f2ptr cause, f2ptr menu, f2ptr append_widget);
f2ptr  f2__gtk__menu__append(f2ptr cause, f2ptr menu, f2ptr append_widget);


// check_button

f2ptr raw__gtk__check_button__new(f2ptr cause, f2ptr label);
f2ptr  f2__gtk__check_button__new(f2ptr cause, f2ptr label);


// **

void f2__gtk__initialize();

#endif // F2__GTK_EXTENSION__H

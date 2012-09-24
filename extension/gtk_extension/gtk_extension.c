// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#include "gtk_extension.h"


funk2_gtk_t* __funk2__gtk = NULL;

f2ptr f2__gtk__session_symbol(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (__funk2__gtk->session_symbol == nil) {
    __funk2__gtk->session_symbol = f2__gensym(cause, new__string(cause, "gtk_session"));
  }
  return __funk2__gtk->session_symbol;
#else
  return nil;
#endif // F2__GTK__SUPPORTED
}

// g_object

//def_frame_object__global__2_slot(g_object, gtk_session, pointer);
def_ceframe2(gtk_extension, g_object, gtk_session, pointer);

f2ptr f2__g_object__new(f2ptr cause, f2ptr pointer) {
  return f2g_object__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(g_object__new, pointer, 0, "Returns a new g_object object.");

#if defined(F2__GTK__SUPPORTED)

GObject* raw__g_object__as__GObject(f2ptr cause, f2ptr this) {
  return (GObject*)from_ptr(f2pointer__p(f2__g_object__pointer(cause, this), cause));
}

boolean_t raw__g_object__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__g_object__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


// gtk_widget

//def_frame_object__global__2_slot(gtk_widget, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_widget, gtk_session, pointer);

f2ptr f2__gtk_widget__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_widget__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_widget__new, pointer, 0, "Returns a new gtk_widget object.");

#if defined(F2__GTK__SUPPORTED)

GtkWidget* raw__gtk_widget__as__GtkWidget(f2ptr cause, f2ptr this) {
  return (GtkWidget*)from_ptr(f2pointer__p(f2__gtk_widget__pointer(cause, this), cause));
}

boolean_t raw__gtk_widget__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_widget__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


f2ptr f2__gtk_widget_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_widget_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "g_object"), f2__primobject_type__parents(cause, this)));
  return this;
}



// gtk_box

//def_frame_object__global__2_slot(gtk_box, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_box, gtk_session, pointer);

f2ptr f2__gtk_box__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_box__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_box__new, pointer, 0, "Returns a new gtk_box object.");

#if defined(F2__GTK__SUPPORTED)

GtkBox* raw__gtk_box__as__GtkBox(f2ptr cause, f2ptr this) {
  return (GtkBox*)from_ptr(f2pointer__p(f2__gtk_box__pointer(cause, this), cause));
}

boolean_t raw__gtk_box__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_box__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


f2ptr f2__gtk_box_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_box_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}



// gtk_text_buffer

//def_frame_object__global__2_slot(gtk_text_buffer, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_text_buffer, gtk_session, pointer);

f2ptr f2__gtk_text_buffer__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_text_buffer__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_text_buffer__new, pointer, 0, "Returns a new gtk_text_buffer object.");

#if defined(F2__GTK__SUPPORTED)

GtkTextBuffer* raw__gtk_text_buffer__as__GtkTextBuffer(f2ptr cause, f2ptr this) {
  return (GtkTextBuffer*)from_ptr(f2pointer__p(f2__gtk_text_buffer__pointer(cause, this), cause));
}

boolean_t raw__gtk_text_buffer__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_text_buffer__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_text_buffer_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_text_buffer_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}



// gtk_label

//def_frame_object__global__2_slot(gtk_label, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_label, gtk_session, pointer);

f2ptr f2__gtk_label__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_label__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_label__new, pointer, 0, "Returns a new gtk_label object.");

#if defined(F2__GTK__SUPPORTED)

GtkLabel* raw__gtk_label__as__GtkLabel(f2ptr cause, f2ptr this) {
  return (GtkLabel*)from_ptr(f2pointer__p(f2__gtk_label__pointer(cause, this), cause));
}

boolean_t raw__gtk_label__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_label__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


f2ptr f2__gtk_label_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_label_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_scale

//def_frame_object__global__2_slot(gtk_scale, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_scale, gtk_session, pointer);

f2ptr f2__gtk_scale__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_scale__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_scale__new, pointer, 0, "Returns a new gtk_scale object.");

#if defined(F2__GTK__SUPPORTED)

GtkScale* raw__gtk_scale__as__GtkScale(f2ptr cause, f2ptr this) {
  return (GtkScale*)from_ptr(f2pointer__p(f2__gtk_scale__pointer(cause, this), cause));
}

boolean_t raw__gtk_scale__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_scale__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


f2ptr f2__gtk_scale_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_scale_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}



// gtk_entry

//def_frame_object__global__2_slot(gtk_entry, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_entry, gtk_session, pointer);

f2ptr f2__gtk_entry__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_entry__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_entry__new, pointer, 0, "Returns a new gtk_entry object.");

#if defined(F2__GTK__SUPPORTED)

GtkEntry* raw__gtk_entry__as__GtkEntry(f2ptr cause, f2ptr this) {
  return (GtkEntry*)from_ptr(f2pointer__p(f2__gtk_entry__pointer(cause, this), cause));
}

boolean_t raw__gtk_entry__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_entry__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


f2ptr f2__gtk_entry_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_entry_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}



// gtk_image

//def_frame_object__global__2_slot(gtk_image, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_image, gtk_session, pointer);

f2ptr f2__gtk_image__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_image__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_image__new, pointer, 0, "Returns a new gtk_image object.");

#if defined(F2__GTK__SUPPORTED)

GtkImage* raw__gtk_image__as__GtkImage(f2ptr cause, f2ptr this) {
  return (GtkImage*)from_ptr(f2pointer__p(f2__gtk_image__pointer(cause, this), cause));
}

boolean_t raw__gtk_image__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_image__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_image_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_image_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_text_iter

//def_frame_object__global__2_slot(gtk_text_iter, gtk_session, chunk);
def_ceframe2(gtk_extension, gtk_text_iter, gtk_session, chunk);

f2ptr f2__gtk_text_iter__new(f2ptr cause, f2ptr chunk) {
  return f2gtk_text_iter__new(cause, f2__gtk__session_symbol(cause), chunk);
}
export_cefunk1(gtk_text_iter__new, pointer, 0, "Returns a new gtk_text_iter object.");

#if defined(F2__GTK__SUPPORTED)

void raw__gtk_text_iter__as__GtkTextIter(f2ptr cause, f2ptr this, GtkTextIter* text_iter) {
  f2ptr chunk = f2__gtk_text_iter__chunk(cause, this);
  raw__chunk__str_copy(cause, chunk, (u8*)text_iter);
}

boolean_t raw__gtk_text_iter__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_text_iter__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


// gdk_color

def_ceframe4(gtk_extension, gdk_color, pixel, red, green, blue);

f2ptr f2__gdk_color__new(f2ptr cause, f2ptr pixel, f2ptr red, f2ptr green, f2ptr blue) {
  return f2gdk_color__new(cause, pixel, red, green, blue);
}
export_cefunk4(gdk_color__new, pixel, red, green, blue, 0, "Returns a new gdk_color object.");

#if defined(F2__GTK__SUPPORTED)

void raw__gdk_color__as__GdkColor(f2ptr cause, f2ptr this, GdkColor* color) {
  f2ptr pixel = f2__gdk_color__pixel(cause, this);
  f2ptr red   = f2__gdk_color__red(  cause, this);
  f2ptr green = f2__gdk_color__green(cause, this);
  f2ptr blue  = f2__gdk_color__blue( cause, this);
  color->pixel = f2integer__i(pixel, cause);
  color->red   = f2integer__i(red,   cause);
  color->green = f2integer__i(green, cause);
  color->blue  = f2integer__i(blue,  cause);
}

#endif // F2__GTK__SUPPORTED


// color

f2ptr f2__gdk__color__new(f2ptr cause, f2ptr pixel, f2ptr red, f2ptr green, f2ptr blue) {
  assert_argument_type(integer, pixel);
  assert_argument_type(integer, red);
  assert_argument_type(integer, green);
  assert_argument_type(integer, blue);
  s64 pixel__i = f2integer__i(pixel, cause);
  s64 red__i   = f2integer__i(red,   cause);
  s64 green__i = f2integer__i(green, cause);
  s64 blue__i  = f2integer__i(blue,  cause);
  if ((pixel__i < 0 || pixel__i >= (1ull << 32)) ||
      (red__i   < 0 || red__i   >= (1ull << 16)) ||
      (green__i < 0 || green__i >= (1ull << 16)) ||
      (blue__i  < 0 || blue__i  >= (1ull << 16))) {
    return new__error(f2list10__new(cause,
				    new__symbol(cause, "bug_name"), new__symbol(cause, "gdk_color_out_of_bounds"),
				    new__symbol(cause, "pixel"),    pixel,
				    new__symbol(cause, "red"),      red,
				    new__symbol(cause, "green"),    green,
				    new__symbol(cause, "blue"),     blue));
  }
  return f2gdk_color__new(cause, pixel, red, green, blue);
}
export_cefunk4(gdk__color__new, pixel, red, green, blue, 0,
	       "Accepts integer pixel, red, green, and blue values.  Returns a new GtkColor object.");
//def_pcfunk4(gdk__color__new, pixel, red, green, blue,
//	    "Accepts integer pixel, red, green, and blue values.  Returns a new GtkColor object.",
//	    return f2__gdk__color__new(this_cause, pixel, red, green, blue));


f2ptr f2__gdk__rgb_color__new(f2ptr cause, f2ptr red, f2ptr green, f2ptr blue) {
  f2ptr red__double   = f2__number__as__double(cause, red);
  f2ptr green__double = f2__number__as__double(cause, green);
  f2ptr blue__double  = f2__number__as__double(cause, blue);
  if ((! raw__double__is_type(cause, red__double)) ||
      (! raw__double__is_type(cause, green__double)) ||
      (! raw__double__is_type(cause, blue__double))) {
    return f2larva__new(cause, 1, nil);
  }
  double red__d   = f2double__d(red__double,   cause);
  double green__d = f2double__d(green__double, cause);
  double blue__d  = f2double__d(blue__double,  cause);
  if ((red__d   < 0.0 || red__d   > 1.0) ||
      (green__d < 0.0 || green__d > 1.0) ||
      (blue__d  < 0.0 || blue__d  > 1.0)) {
    return f2larva__new(cause, 2, nil);
  }
  s64 red__i   = 65535.0 * red__d;
  s64 green__i = 65535.0 * green__d;
  s64 blue__i  = 65535.0 * blue__d;
  return f2__gdk__color__new(cause, f2integer__new(cause, 0), f2integer__new(cause, red__i), f2integer__new(cause, green__i), f2integer__new(cause, blue__i));
}
export_cefunk3(gdk__rgb_color__new, red, green, blue, 0,
	       "Accepts double red, green, and blue values between 0.0 and 1.0.  Returns a new rgb_color object.");
//def_pcfunk3(gdk__rgb_color__new, red, green, blue,
//	    "Accepts red, green, and blue values between 0 and 1.  Returns a new GtkColor object.",
//	    return f2__gdk__rgb_color__new(this_cause, red, green, blue));


// gdk_pixbuf

//def_frame_object__global__2_slot(gdk_pixbuf, gtk_session, pointer);
def_ceframe2(gtk_extension, gdk_pixbuf, gtk_session, pointer);

f2ptr f2__gdk_pixbuf__new(f2ptr cause, f2ptr pointer) {
  return f2gdk_pixbuf__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gdk_pixbuf__new, pointer, 0, "Returns a new gdk_pixbuf object.");

#if defined(F2__GTK__SUPPORTED)

GdkPixbuf* raw__gdk_pixbuf__as__GdkPixbuf(f2ptr cause, f2ptr this) {
  return (GdkPixbuf*)from_ptr(f2pointer__p(f2__gdk_pixbuf__pointer(cause, this), cause));
}

boolean_t raw__gdk_pixbuf__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gdk_pixbuf__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gdk_pixbuf_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gdk_pixbuf_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "g_object"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_text_mark

//def_frame_object__global__2_slot(gtk_text_mark, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_text_mark, gtk_session, pointer);

f2ptr f2__gtk_text_mark__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_text_mark__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_text_mark__new, pointer, 0, "Returns a new gtk_text_mark object.");

#if defined(F2__GTK__SUPPORTED)

GtkTextMark* raw__gtk_text_mark__as__GtkTextMark(f2ptr cause, f2ptr this) {
  return (GtkTextMark*)from_ptr(f2pointer__p(f2__gtk_text_mark__pointer(cause, this), cause));
}

boolean_t raw__gtk_text_mark__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_text_mark__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED


// gtk_callback

//def_frame_object__global__2_slot(gtk_callback, funk, args);
def_ceframe2(gtk_extension, gtk_callback, funk, args);

f2ptr f2__gtk_callback__new(f2ptr cause, f2ptr funk, f2ptr args) {
  return f2gtk_callback__new(cause, funk, args);
}
export_cefunk2(gtk_callback__new, funk, args, 0, "Returns a new gtk_callback object.");


// gtk_text_range

//def_frame_object__global__2_slot(gtk_text_range, start, end);
def_ceframe2(gtk_extension, gtk_text_range, start, end);

f2ptr f2__gtk_text_range__new(f2ptr cause, f2ptr start, f2ptr end) {
  return f2gtk_text_range__new(cause, start, end);
}
export_cefunk2(gtk_text_range__new, start, end, 0, "Returns a new gtk_text_range object.");


// gtk_progress_bar

//def_frame_object__global__2_slot(gtk_progress_bar, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_progress_bar, gtk_session, pointer);

f2ptr f2__gtk_progress_bar__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_progress_bar__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_progress_bar__new, pointer, 0, "Returns a new gtk_progress_bar object.");

#if defined(F2__GTK__SUPPORTED)

GtkProgressBar* raw__gtk_progress_bar__as__GtkProgressBar(f2ptr cause, f2ptr this) {
  return (GtkProgressBar*)from_ptr(f2pointer__p(f2__gtk_progress_bar__pointer(cause, this), cause));
}

boolean_t raw__gtk_progress_bar__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_progress_bar__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_progress_bar_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_progress_bar_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_menu

//def_frame_object__global__2_slot(gtk_menu, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_menu, gtk_session, pointer);

f2ptr f2__gtk_menu__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_menu__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_menu__new, pointer, 0, "Returns a new gtk_menu object.");

#if defined(F2__GTK__SUPPORTED)

GtkMenu* raw__gtk_menu__as__GtkMenu(f2ptr cause, f2ptr this) {
  return (GtkMenu*)from_ptr(f2pointer__p(f2__gtk_menu__pointer(cause, this), cause));
}

boolean_t raw__gtk_menu__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_menu__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_menu_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_menu_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_menu_bar

//def_frame_object__global__2_slot(gtk_menu_bar, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_menu_bar, gtk_session, pointer);

f2ptr f2__gtk_menu_bar__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_menu_bar__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_menu_bar__new, pointer, 0, "Returns a new gtk_menu_bar object.");

#if defined(F2__GTK__SUPPORTED)

GtkMenuBar* raw__gtk_menu_bar__as__GtkMenuBar(f2ptr cause, f2ptr this) {
  return (GtkMenuBar*)from_ptr(f2pointer__p(f2__gtk_menu_bar__pointer(cause, this), cause));
}

boolean_t raw__gtk_menu_bar__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_menu_bar__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_menu_bar_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_menu_bar_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_check_button

//def_frame_object__global__2_slot(gtk_check_button, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_check_button, gtk_session, pointer);

f2ptr f2__gtk_check_button__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_check_button__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_check_button__new, pointer, 0, "Returns a new gtk_check_button object.");

#if defined(F2__GTK__SUPPORTED)

GtkCheckButton* raw__gtk_check_button__as__GtkCheckButton(f2ptr cause, f2ptr this) {
  return (GtkCheckButton*)from_ptr(f2pointer__p(f2__gtk_check_button__pointer(cause, this), cause));
}

boolean_t raw__gtk_check_button__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_check_button__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_check_button_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_check_button_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}


// gtk_file_chooser_dialog

//def_frame_object__global__2_slot(gtk_file_chooser_dialog, gtk_session, pointer);
def_ceframe2(gtk_extension, gtk_file_chooser_dialog, gtk_session, pointer);

f2ptr f2__gtk_file_chooser_dialog__new(f2ptr cause, f2ptr pointer) {
  return f2gtk_file_chooser_dialog__new(cause, f2__gtk__session_symbol(cause), pointer);
}
export_cefunk1(gtk_file_chooser_dialog__new, pointer, 0, "Returns a new gtk_file_chooser_dialog object.");

#if defined(F2__GTK__SUPPORTED)

GtkFileChooserDialog* raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(f2ptr cause, f2ptr this) {
  return (GtkFileChooserDialog*)from_ptr(f2pointer__p(f2__gtk_file_chooser_dialog__pointer(cause, this), cause));
}

boolean_t raw__gtk_file_chooser_dialog__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__eq(cause, f2__gtk__session_symbol(cause), f2__gtk_file_chooser_dialog__gtk_session(cause, this));
}

#endif // F2__GTK__SUPPORTED

f2ptr f2__gtk_file_chooser_dialog_type__new_aux(f2ptr cause) {
  f2ptr this = f2__gtk_file_chooser_dialog_type__new(cause);
  f2__primobject_type__parents__set(cause, this, raw__cons__new(cause, new__symbol(cause, "gtk_widget"), f2__primobject_type__parents(cause, this)));
  return this;
}



#if defined(F2__GTK__SUPPORTED)


// funk2_gtk

void funk2_gtk__thread__start_function(funk2_gtk_t* this) {
  status("funk2_gtk__thread__start_function: waiting for main_thread__mutex to unlock.");
  funk2_processor_mutex__lock(&(this->main_thread__mutex));
  status("funk2_gtk__thread__start_function: got main_thread__mutex lock and continuing.");
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
  
  if (! gtk_init_check(argv, argc)) {
    
    this->initialized_successfully = boolean__false;
    
  } else {
    
    this->initialized_successfully = boolean__true;
    
    funk2_processor_mutex__init(&(this->main_thread__mutex));
    this->main_thread__active        = boolean__false;
    
    funk2_processor_mutex__init(&(this->callbacks__mutex));
    this->callbacks                  = NULL;
    
    funk2_processor_mutex__init(&(this->callback_events__mutex));
    this->callback_events            = NULL;
    this->callback_events__last_cons = NULL;
    
    this->session_symbol = nil;
    
    // keeps gtk_main from starting until we unlock this mutex.
    funk2_processor_mutex__lock(&(this->main_thread__mutex));
    this->main_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), &funk2_gtk__thread__start_function__helper, (void*)this);
  }
}

void funk2_gtk__start_gtk_main(funk2_gtk_t* this) {
  funk2_processor_mutex__unlock(&(this->main_thread__mutex));
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
  if (callback->cause) {
    never_gc(callback->cause);
  }
  if (callback->funk) {
    never_gc(callback->funk);
  }
  if (callback->args) {
    never_gc(callback->args);
  }
}

void funk2_gtk__add_callback_event(funk2_gtk_t* this, f2ptr cause, funk2_gtk_callback_t* callback, void* args) {
  funk2_gtk_callback_event_cons_t* cons  = (funk2_gtk_callback_event_cons_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_event_cons_t)));
  funk2_gtk_callback_event_t*      event = (funk2_gtk_callback_event_t*)     from_ptr(f2__malloc(sizeof(funk2_gtk_callback_event_t)));
  event->callback = callback;
  event->args     = args;
  cons->callback_event = event;
  cons->next           = NULL;
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

funk2_gtk_callback_event_t* funk2_gtk__pop_callback_event(funk2_gtk_t* this) {
  funk2_gtk_callback_event_t* callback_event = NULL;
  funk2_processor_mutex__user_lock(&(this->callback_events__mutex));
  if (this->callback_events) {
    funk2_gtk_callback_event_cons_t* cons = this->callback_events;
    this->callback_events = this->callback_events->next;
    callback_event = cons->callback_event;
    f2__free(to_ptr(cons));
    if (this->callback_events == NULL) {
      this->callback_events__last_cons = NULL;
    }
  }
  funk2_processor_mutex__unlock(&(this->callback_events__mutex));
  return callback_event;
}

void funk2_gtk__callback_handler(GtkWidget *widget, funk2_gtk_callback_t* callback) {
  funk2_gtk__add_callback_event(__funk2__gtk, callback, NULL);
}

void funk2_gtk__signal_connect(funk2_gtk_t* this, GtkWidget* widget, u8* signal_name, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__nil;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), (char*)signal_name, G_CALLBACK(funk2_gtk__callback_handler), callback);
    gdk_threads_leave();
  }
}


// expose_event

gboolean funk2_gtk__expose_event__signal_connect__callback_handler(GtkWidget* widget, GdkEventExpose* expose, gpointer data) {
  funk2_gtk_callback_t* callback    = (funk2_gtk_callback_t*)data;
  GdkEventExpose*       expose_copy = (GdkEventExpose*)from_ptr(f2__malloc(sizeof(GdkEventExpose)));
  memcpy(expose_copy, expose, sizeof(GdkEventExpose));
  funk2_gtk__add_callback_event(__funk2__gtk, callback, expose_copy);
  return TRUE;
}

void funk2_gtk__expose_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__expose;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "expose_event", G_CALLBACK(funk2_gtk__expose_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// key_press_event

gboolean funk2_gtk__key_press_event__signal_connect__callback_handler(GtkWidget* widget, GdkEventKey* key, gpointer data) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)data;
  GdkEventKey*          key_copy = (GdkEventKey*)from_ptr(f2__malloc(sizeof(GdkEventKey)));
  memcpy(key_copy, key, sizeof(GdkEventKey));
  funk2_gtk__add_callback_event(__funk2__gtk, callback, key_copy);
  return FALSE;
}

void funk2_gtk__key_press_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__key_press;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "key-press-event", G_CALLBACK(funk2_gtk__key_press_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// response_event

void funk2_gtk__response_event__signal_connect__callback_handler(GtkWidget* widget, gint gtk_response_id, gpointer data) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)data;
  s64* response_id = (s64*)from_ptr(f2__malloc(sizeof(s64)));
  *response_id = (s64)gtk_response_id;
  funk2_gtk__add_callback_event(__funk2__gtk, callback, response_id);
}

void funk2_gtk__response_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__response;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "response", G_CALLBACK(funk2_gtk__response_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// update_preview_event

void funk2_gtk__update_preview_event__signal_connect__callback_handler(GtkWidget* widget, gpointer data) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)data;
  funk2_gtk__add_callback_event(__funk2__gtk, callback, NULL);
}

void funk2_gtk__update_preview_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__update_preview;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "update-preview", G_CALLBACK(funk2_gtk__update_preview_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// value_changed

void funk2_gtk__value_changed_event__signal_connect__callback_handler(GtkWidget* widget, gpointer data) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)data;
  funk2_gtk__add_callback_event(__funk2__gtk, callback, NULL);
}

void funk2_gtk__value_changed_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__value_changed;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "value-changed", G_CALLBACK(funk2_gtk__value_changed_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// size_allocate_event

gboolean funk2_gtk__size_allocate_event__signal_connect__callback_handler(GtkWidget* widget, GtkAllocation* gtk_allocation, gpointer data) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)data;
  GtkAllocation*        allocation = (GtkAllocation*)from_ptr(f2__malloc(sizeof(GtkAllocation)));
  memcpy(allocation, gtk_allocation, sizeof(GtkAllocation));
  funk2_gtk__add_callback_event(__funk2__gtk, callback, allocation);
  return FALSE;
}

void funk2_gtk__size_allocate_event__signal_connect(funk2_gtk_t* this, GtkWidget* widget, f2ptr cause, f2ptr funk, f2ptr args) {
  funk2_gtk_callback_t* callback = (funk2_gtk_callback_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_callback_t)));
  callback->cause     = cause;
  callback->funk      = funk;
  callback->args      = args;
  callback->args_type = funk2_gtk_callback_args_type__size_allocate;
  funk2_gtk__add_callback(this, callback);
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "size-allocate", G_CALLBACK(funk2_gtk__size_allocate_event__signal_connect__callback_handler), callback);
    gdk_threads_leave();
  }
}


// object

void funk2_g__object__ref(funk2_gtk_t* this, GObject* object) {
  {
    gdk_threads_enter();
    g_object_ref(G_OBJECT(object));
    gdk_threads_leave();
  }
}

void funk2_g__object__unref(funk2_gtk_t* this, GObject* object) {
  {
    gdk_threads_enter();
    g_object_unref(G_OBJECT(object));
    gdk_threads_leave();
  }
}


// widget
 
void funk2_gtk__widget__show(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_show(GTK_WIDGET(widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__show_all(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_show_all(GTK_WIDGET(widget));
    gdk_threads_leave();
  }
}
 
void funk2_gtk__widget__hide(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_hide(GTK_WIDGET(widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__hide_all(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_hide_all(GTK_WIDGET(widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__set_size_request(funk2_gtk_t* this, GtkWidget* widget, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gtk_widget_set_size_request(GTK_WIDGET(widget), width, height);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__queue_draw_area(funk2_gtk_t* this, GtkWidget* widget, s64 x, s64 y, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gtk_widget_queue_draw_area(GTK_WIDGET(widget), x, y, width, height);
    gdk_threads_leave();
  }
}

boolean_t funk2_gtk__widget__get_visible(funk2_gtk_t* this, GtkWidget* widget) {
  boolean_t visible;
  {
    gdk_threads_enter();
    visible = gtk_widget_get_visible(GTK_WIDGET(widget)) ? boolean__true : boolean__false;
    gdk_threads_leave();
  }
  return visible;
}

void funk2_gtk__widget__destroy(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_widget_destroy(GTK_WIDGET(widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__connect_hide_on_delete(funk2_gtk_t* this, GtkWidget* widget) {
  {
    gdk_threads_enter();
    g_signal_connect(G_OBJECT(widget), "delete-event", G_CALLBACK(gtk_widget_hide_on_delete), NULL);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__modify_fg(funk2_gtk_t* this, GtkWidget* widget, GtkStateType state, GdkColor* color) {
  {
    gdk_threads_enter();
    gtk_widget_modify_fg(GTK_WIDGET(widget), state, color);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__modify_bg(funk2_gtk_t* this, GtkWidget* widget, GtkStateType state, GdkColor* color) {
  {
    gdk_threads_enter();
    gtk_widget_modify_bg(GTK_WIDGET(widget), state, color);
    gdk_threads_leave();
  }
}

void funk2_gtk__widget__set_sensitive(funk2_gtk_t* this, GtkWidget* widget, boolean_t sensitive) {
  {
    gdk_threads_enter();
    gtk_widget_set_sensitive(GTK_WIDGET(widget), sensitive ? TRUE : FALSE);
    gdk_threads_leave();
  }
}
 
void funk2_gtk__widget__set_no_show_all(funk2_gtk_t* this, GtkWidget* widget, boolean_t no_show_all) {
  {
    gdk_threads_enter();
    gtk_widget_set_no_show_all(GTK_WIDGET(widget), no_show_all ? TRUE : FALSE);
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


// misc

void funk2_gtk__misc__set_alignment(funk2_gtk_t* this, GtkWidget* misc, double xalign, double yalign) {
  {
    gdk_threads_enter();
    gtk_misc_set_alignment(GTK_MISC(misc), xalign, yalign);
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

void funk2_gtk__window__resize(funk2_gtk_t* this, GtkWidget* window, s64 width, s64 height) {
  {
    gdk_threads_enter();
    gtk_window_resize(GTK_WINDOW(window), width, height);
    gdk_threads_leave();
  }
}

void funk2_gtk__window__set_transient_for(funk2_gtk_t* this, GtkWidget* window, GtkWidget* parent) {
  {
    gdk_threads_enter();
    gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(parent));
    gdk_threads_leave();
  }
}

void funk2_gtk__window__set_destroy_with_parent(funk2_gtk_t* this, GtkWidget* window, boolean_t setting) {
  {
    gdk_threads_enter();
    gtk_window_set_destroy_with_parent(GTK_WINDOW(window), setting ? TRUE : FALSE);
    gdk_threads_leave();
  }
}


// vbox

GtkWidget* funk2_gtk__vbox__new(funk2_gtk_t* this, int spacing) {
  GtkWidget* vbox = NULL;
  {
    gdk_threads_enter();
    vbox = gtk_vbox_new(FALSE, spacing);
    gdk_threads_leave();
  }
  return vbox;
}


// hbox

GtkWidget* funk2_gtk__hbox__new(funk2_gtk_t* this, int spacing) {
  GtkWidget* hbox = NULL;
  {
    gdk_threads_enter();
    hbox = gtk_hbox_new(FALSE, spacing);
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

void funk2_gtk__scrolled_window__set_policy(funk2_gtk_t* this, GtkWidget* scrolled_window, GtkPolicyType hscrollbar_policy, GtkPolicyType vscrollbar_policy) {
  {
    gdk_threads_enter();
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), hscrollbar_policy, vscrollbar_policy);
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

void funk2_gtk__text_view__set_wrap_mode(funk2_gtk_t* this, GtkWidget* text_view, GtkWrapMode wrap_mode) {
  {
    gdk_threads_enter();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), wrap_mode);
    gdk_threads_leave();
  }
}


// gdk_pixbuf

//GdkPixbuf* gdk_pixbuf_new_from_data(const guchar *data,
//                                    GdkColorspace colorspace,
//                                    gboolean has_alpha,
//                                    int bits_per_sample,
//                                    int width,
//                                    int height,
//                                    int rowstride,
//                                    GdkPixbufDestroyNotify destroy_fn,
//                                    gpointer destroy_fn_data);

void funk2_gtk__pixbuf__destroy_notify_function(guchar *pixels, gpointer data) {
  f2__free(to_ptr(pixels));
}

GdkPixbuf* funk2_gtk__pixbuf__new(funk2_gtk_t* this, u64 width, u64 height, u8* rgb_data) {
  if ((width  > XLIB_IMAGE_SIDE_SIZE_LIMIT) ||
      (height > XLIB_IMAGE_SIDE_SIZE_LIMIT)) {
    return NULL;
  }
  GdkPixbuf* pixbuf;
  {
    gdk_threads_enter();
    pixbuf = gdk_pixbuf_new_from_data((guchar*)rgb_data, GDK_COLORSPACE_RGB, FALSE, 8, width, height, 3 * width, &funk2_gtk__pixbuf__destroy_notify_function, NULL);
    gdk_threads_leave();
  }
  return pixbuf;
}

GdkPixbuf* funk2_gtk__pixbuf__new_from_file(funk2_gtk_t* this, u8* filename, GError** g_error) {
  GdkPixbuf* pixbuf;
  {
    gdk_threads_enter();
    pixbuf = gdk_pixbuf_new_from_file((char*)filename, g_error);
    gdk_threads_leave();
  }
  return pixbuf;
}

s64 funk2_gtk__pixbuf__get_width(funk2_gtk_t* this, GdkPixbuf* pixbuf) {
  s64 width;
  {
    gdk_threads_enter();
    width = gdk_pixbuf_get_width(pixbuf);
    gdk_threads_leave();
  }
  return width;
}

s64 funk2_gtk__pixbuf__get_height(funk2_gtk_t* this, GdkPixbuf* pixbuf) {
  s64 height;
  {
    gdk_threads_enter();
    height = gdk_pixbuf_get_height(pixbuf);
    gdk_threads_leave();
  }
  return height;
}

boolean_t funk2_gtk__pixbuf__copy_rgba_pixel_data(funk2_gtk_t* this, GdkPixbuf* pixbuf, u8* rgba_pixel_data) {
  boolean_t success;
  {
    gdk_threads_enter();
    if (! (gdk_pixbuf_get_colorspace(pixbuf) == GDK_COLORSPACE_RGB)) {
      success = boolean__false;
    } else {
      if (! (gdk_pixbuf_get_bits_per_sample(pixbuf) == 8)) {
	success = boolean__false;
      } else {
	boolean_t has_alpha  = gdk_pixbuf_get_has_alpha(pixbuf);
	int       n_channels = gdk_pixbuf_get_n_channels(pixbuf);
	if (! ((n_channels == 4) || (n_channels == 3))) {
	  printf("\nfunk2_gtk__pixbuf__copy_rgb_pixel_data error: pixbuf channel number is not 3 or 4.\n"); fflush(stdout);
	  success = boolean__false;
	} else {
	  int     width          = gdk_pixbuf_get_width(pixbuf);
	  int     height         = gdk_pixbuf_get_height(pixbuf);
	  int     rowstride      = gdk_pixbuf_get_rowstride(pixbuf);
	  s64     dest_rowstride = width * 4;
	  guchar* pixels         = gdk_pixbuf_get_pixels(pixbuf);
	  {
	    guchar* row      = pixels;
	    u8*     dest_row = rgba_pixel_data;
	    s64     y;
	    for (y = 0; y < height; y ++) {
	      {
		guchar* pixel      = row;
		u8*     dest_pixel = dest_row;
		s64 x;
		for (x = 0; x < width; x ++) {
		  {
		    dest_pixel[0] = pixel[0];
		    dest_pixel[1] = pixel[1];
		    dest_pixel[2] = pixel[2];
		    if (has_alpha) {
		      dest_pixel[3] = pixel[3];
		    } else {
		      dest_pixel[3] = 0;
		    }
		  }
		  pixel      += n_channels;
		  dest_pixel += 4;
		}
	      }
	      row      += rowstride;
	      dest_row += dest_rowstride;
	    }
	  }
	  success = boolean__true;
	}
      }
    }
    gdk_threads_leave();
  }
  return success;
}

boolean_t funk2_gtk__pixbuf__copy_rgb_pixel_data(funk2_gtk_t* this, GdkPixbuf* pixbuf, u8* rgb_pixel_data) {
  boolean_t success;
  {
    gdk_threads_enter();
    if (! (gdk_pixbuf_get_colorspace(pixbuf) == GDK_COLORSPACE_RGB)) {
      printf("\nfunk2_gtk__pixbuf__copy_rgb_pixel_data error: pixbuf colorspace is not RGB.\n"); fflush(stdout);
      success = boolean__false;
    } else {
      if (! (gdk_pixbuf_get_bits_per_sample(pixbuf) == 8)) {
	printf("\nfunk2_gtk__pixbuf__copy_rgb_pixel_data error: pixbuf bits per sample is not 8.\n"); fflush(stdout);
	success = boolean__false;
      } else {
	int n_channels = gdk_pixbuf_get_n_channels(pixbuf);
	if (! ((n_channels == 4) || (n_channels == 3))) {
	  printf("\nfunk2_gtk__pixbuf__copy_rgb_pixel_data error: pixbuf channel number is not 3 or 4.\n"); fflush(stdout);
	  success = boolean__false;
	} else {
	  int     width          = gdk_pixbuf_get_width(pixbuf);
	  int     height         = gdk_pixbuf_get_height(pixbuf);
	  int     rowstride      = gdk_pixbuf_get_rowstride(pixbuf);
	  s64     dest_rowstride = width * 3;
	  guchar* pixels         = gdk_pixbuf_get_pixels(pixbuf);
	  {
	    guchar* row      = pixels;
	    u8*     dest_row = rgb_pixel_data;
	    s64     y;
	    for (y = 0; y < height; y ++) {
	      {
		guchar* pixel      = row;
		u8*     dest_pixel = dest_row;
		s64 x;
		for (x = 0; x < width; x ++) {
		  {
		    dest_pixel[0] = pixel[0];
		    dest_pixel[1] = pixel[1];
		    dest_pixel[2] = pixel[2];
		  }
		  pixel      += n_channels;
		  dest_pixel += 3;
		}
	      }
	      row      += rowstride;
	      dest_row += dest_rowstride;
	    }
	  }
	  success = boolean__true;
	}
      }
    }
    gdk_threads_leave();
  }
  return success;
}

// container

void funk2_gtk__container__add(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* add_widget) {
  {
    gdk_threads_enter();
    gtk_container_add(GTK_CONTAINER(widget), GTK_WIDGET(add_widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__container__remove(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* remove_widget) {
  {
    gdk_threads_enter();
    gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(remove_widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__container__replace(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* remove_widget, GtkWidget* add_widget) {
  {
    gdk_threads_enter();
    gtk_container_remove(GTK_CONTAINER(widget), GTK_WIDGET(remove_widget));
    gtk_container_add(   GTK_CONTAINER(widget), GTK_WIDGET(add_widget));
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


u64 funk2_gtk__gdk_keyval_to_unicode(funk2_gtk_t* this, u64 keyval) {
  u64 unicode;
  {
    gdk_threads_enter();
    unicode = gdk_keyval_to_unicode(keyval);
    gdk_threads_leave();
  }
  return unicode;
}


// progress_bar

GtkProgressBar* funk2_gtk__progress_bar__new(funk2_gtk_t* this) {
  GtkProgressBar* progress_bar;
  {
    gdk_threads_enter();
    progress_bar = GTK_PROGRESS_BAR(gtk_progress_bar_new());
    gdk_threads_leave();
  }
  return progress_bar;
}

void funk2_gtk__progress_bar__set_fraction(GtkProgressBar* progress_bar, double fraction) {
  {
    gdk_threads_enter();
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), fraction);
    gdk_threads_leave();
  }
}

void funk2_gtk__progress_bar__set_text(GtkProgressBar* progress_bar, u8* text) {
  {
    gdk_threads_enter();
    gtk_progress_bar_set_text(GTK_PROGRESS_BAR(progress_bar), (char*)text);
    gdk_threads_leave();
  }
}

void funk2_gtk__progress_bar__set_orientation(GtkProgressBar* progress_bar, GtkProgressBarOrientation orientation) {
  {
    gdk_threads_enter();
    gtk_progress_bar_set_orientation(GTK_PROGRESS_BAR(progress_bar), orientation);
    gdk_threads_leave();
  }
}

void funk2_gtk__progress_bar__pulse(GtkProgressBar* progress_bar) {
  {
    gdk_threads_enter();
    gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progress_bar));
    gdk_threads_leave();
  }
}

void funk2_gtk__progress_bar__set_pulse_step(GtkProgressBar* progress_bar, double fraction) {
  {
    gdk_threads_enter();
    gtk_progress_bar_set_pulse_step(GTK_PROGRESS_BAR(progress_bar), fraction);
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

GtkLabel* funk2_gtk__label__new(funk2_gtk_t* this, u8* text) {
  GtkLabel* label;
  {
    gdk_threads_enter();
    label = GTK_LABEL(gtk_label_new((char*)text));
    gdk_threads_leave();
  }
  return label;
}

void funk2_gtk__label__set_text(funk2_gtk_t* this, GtkLabel* label, u8* text) {
  {
    gdk_threads_enter();
    gtk_label_set_text(GTK_LABEL(label), (char*)text);
    gdk_threads_leave();
  }
}

void funk2_gtk__label__set_selectable(funk2_gtk_t* this, GtkLabel* label, boolean_t selectable) {
  {
    gdk_threads_enter();
    gtk_label_set_selectable(GTK_LABEL(label), selectable ? TRUE : FALSE);
    gdk_threads_leave();
  }
}


// hscale

GtkScale* funk2_gtk__hscale__new_with_range(funk2_gtk_t* this, double min, double max, double step) {
  GtkScale* scale;
  {
    gdk_threads_enter();
    scale = GTK_SCALE(gtk_hscale_new_with_range(min, max, step));
    gdk_threads_leave();
  }
  return scale;
}


// vscale

GtkScale* funk2_gtk__vscale__new_with_range(funk2_gtk_t* this, double min, double max, double step) {
  GtkScale* scale;
  {
    gdk_threads_enter();
    scale = GTK_SCALE(gtk_vscale_new_with_range(min, max, step));
    gdk_threads_leave();
  }
  return scale;
}


// scale

void funk2_gtk__scale__set_digits(funk2_gtk_t* this, GtkScale* scale, s64 digits) {
  {
    gdk_threads_enter();
    gtk_scale_set_digits(scale, digits);
    gdk_threads_leave();
  }
}



// range

double funk2_gtk__range__get_value(funk2_gtk_t* this, GtkRange* range) {
  double value;
  {
    gdk_threads_enter();
    value = gtk_range_get_value(GTK_RANGE(range));
    gdk_threads_leave();
  }
  return value;
}

void funk2_gtk__range__set_value(funk2_gtk_t* this, GtkRange* range, double value) {
  {
    gdk_threads_enter();
    gtk_range_set_value(GTK_RANGE(range), value);
    gdk_threads_leave();
  }
}

void funk2_gtk__range__set_range(funk2_gtk_t* this, GtkRange* range, double min, double max) {
  {
    gdk_threads_enter();
    gtk_range_set_range(GTK_RANGE(range), min, max);
    gdk_threads_leave();
  }
}

void funk2_gtk__range__set_increments(funk2_gtk_t* this, GtkRange* range, double step, double page) {
  {
    gdk_threads_enter();
    gtk_range_set_increments(GTK_RANGE(range), step, page);
    gdk_threads_leave();
  }
}


// entry

GtkEntry* funk2_gtk__entry__new(funk2_gtk_t* this) {
  GtkEntry* entry = NULL;
  {
    gdk_threads_enter();
    entry = GTK_ENTRY(gtk_entry_new());
    gdk_threads_leave();
  }
  return entry;
}

char* funk2_gtk__entry__get_text(funk2_gtk_t* this, GtkEntry* widget) {
  char* text = NULL;
  {
    gdk_threads_enter();
    text = (char*)gtk_entry_get_text(GTK_ENTRY(widget));
    gdk_threads_leave();
  }
  return text;
}

void funk2_gtk__entry__set_text(funk2_gtk_t* this, GtkEntry* widget, u8* text) {
  {
    gdk_threads_enter();
    gtk_entry_set_text(GTK_ENTRY(widget), (char*)text);
    gdk_threads_leave();
  }
}


// image

GtkImage* funk2_gtk__image__new_from_pixbuf(funk2_gtk_t* this, GdkPixbuf* pixbuf) {
  GtkImage* image;
  {
    gdk_threads_enter();
    image = GTK_IMAGE(gtk_image_new_from_pixbuf(pixbuf));
    gdk_threads_leave();
  }
  return image;
}

void funk2_gtk__image__set_from_pixbuf(funk2_gtk_t* this, GtkImage* image, GdkPixbuf* pixbuf) {
  {
    gdk_threads_enter();
    gtk_image_set_from_pixbuf(image, pixbuf);
    gdk_threads_leave();
  }
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

void funk2_gtk__table__attach(funk2_gtk_t* this, GtkWidget* table, GtkWidget* child, u64 left_attach, u64 right_attach, u64 top_attach, u64 bottom_attach, u64 xpadding, u64 ypadding) {
  GtkAttachOptions xoptions = GTK_EXPAND | GTK_SHRINK | GTK_FILL;
  GtkAttachOptions yoptions = GTK_EXPAND | GTK_SHRINK | GTK_FILL;
  {
    gdk_threads_enter();
    gtk_table_attach(GTK_TABLE(table), GTK_WIDGET(child), left_attach, right_attach, top_attach, bottom_attach, xoptions, yoptions, xpadding, ypadding);
    gdk_threads_leave();
  }
}


// frame

GtkWidget* funk2_gtk__frame__new(funk2_gtk_t* this, u8* label) {
  GtkWidget* frame;
  {
    gdk_threads_enter();
    frame = gtk_frame_new((char*)label);
    gdk_threads_leave();
  }
  return frame;
}


// menu_bar

GtkMenuBar* funk2_gtk__menu_bar__new(funk2_gtk_t* this) {
  GtkMenuBar* menu_bar;
  {
    gdk_threads_enter();
    menu_bar = GTK_MENU_BAR(gtk_menu_bar_new());
    gdk_threads_leave();
  }
  return menu_bar;
}

void funk2_gtk__menu_bar__append(funk2_gtk_t* this, GtkMenuBar* menu_bar, GtkWidget* append_widget) {
  {
    gdk_threads_enter();
    gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), GTK_WIDGET(append_widget));
    gdk_threads_leave();
  }
}


// menu_item

GtkWidget* funk2_gtk__menu_item__new(funk2_gtk_t* this, u8* label) {
  GtkWidget* menu_item;
  {
    gdk_threads_enter();
    menu_item = gtk_menu_item_new_with_label((char*)label);
    gdk_threads_leave();
  }
  return menu_item;
}

void funk2_gtk__menu_item__set_submenu(funk2_gtk_t* this, GtkWidget* widget, GtkWidget* submenu) {
  {
    gdk_threads_enter();
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(widget), GTK_WIDGET(submenu));
    gdk_threads_leave();
  }
}



// check_menu_item

GtkWidget* funk2_gtk__check_menu_item__new(funk2_gtk_t* this, u8* label) {
  GtkWidget* check_menu_item;
  {
    gdk_threads_enter();
    check_menu_item = gtk_check_menu_item_new_with_label((char*)label);
    gdk_threads_leave();
  }
  return check_menu_item;
}

boolean_t funk2_gtk__check_menu_item__get_active(funk2_gtk_t* this, GtkWidget* widget) {
  boolean_t active;
  {
    gdk_threads_enter();
    active = gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget)) ? boolean__true : boolean__false;
    gdk_threads_leave();
  }
  return active;
}

void funk2_gtk__check_menu_item__set_active(funk2_gtk_t* this, GtkWidget* widget, boolean_t active) {
  {
    gdk_threads_enter();
    gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(widget), active ? TRUE : FALSE);
    gdk_threads_leave();
  }
}


// menu

GtkMenu* funk2_gtk__menu__new(funk2_gtk_t* this) {
  GtkMenu* menu;
  {
    gdk_threads_enter();
    menu = GTK_MENU(gtk_menu_new());
    gdk_threads_leave();
  }
  return menu;
}

void funk2_gtk__menu__append(funk2_gtk_t* this, GtkMenu* menu, GtkWidget* append_widget) {
  {
    gdk_threads_enter();
    gtk_menu_append(GTK_MENU(menu), GTK_WIDGET(append_widget));
    gdk_threads_leave();
  }
}


// check_button

GtkCheckButton* funk2_gtk__check_button__new(funk2_gtk_t* this, char* label) {
  GtkCheckButton* check_button;
  {
    gdk_threads_enter();
    check_button = GTK_CHECK_BUTTON(gtk_check_button_new_with_label(label));
    gdk_threads_leave();
  }
  return check_button;
}

boolean_t funk2_gtk__check_button__get_active(funk2_gtk_t* this, GtkCheckButton* check_button) {
  boolean_t active;
  {
    gdk_threads_enter();
    active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_button)) ? boolean__true : boolean__false;
    gdk_threads_leave();
  }
  return active;
}

void funk2_gtk__check_button__set_active(funk2_gtk_t* this, GtkCheckButton* check_button, boolean_t active) {
  {
    gdk_threads_enter();
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(check_button), active ? TRUE : FALSE);
    gdk_threads_leave();
  }
}


// file_chooser_dialog

GtkFileChooserDialog* funk2_gtk__file_chooser_dialog__new_for_file_open(funk2_gtk_t* this, GtkWidget* parent_window) {
  GtkFileChooserDialog* file_chooser_dialog;
  {
    gdk_threads_enter();
    file_chooser_dialog = GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new("Open File",
									      (GtkWindow*)parent_window,
									      GTK_FILE_CHOOSER_ACTION_OPEN,
									      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
									      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
									      NULL));
    gtk_file_chooser_set_show_hidden(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE);
    gdk_threads_leave();
  }
  return file_chooser_dialog;
}

GtkFileChooserDialog* funk2_gtk__file_chooser_dialog__new_for_folder_select(funk2_gtk_t* this, GtkWidget* parent_window) {
  GtkFileChooserDialog* file_chooser_dialog;
  {
    gdk_threads_enter();
    file_chooser_dialog = GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new("Select Folder",
									      (GtkWindow*)parent_window,
									      GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
									      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
									      GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
									      NULL));
    gtk_file_chooser_set_show_hidden(   GTK_FILE_CHOOSER(file_chooser_dialog), TRUE);
    gtk_file_chooser_set_create_folders(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE);
    gdk_threads_leave();
  }
  return file_chooser_dialog;
}

GtkFileChooserDialog* funk2_gtk__file_chooser_dialog__new_for_file_save(funk2_gtk_t* this, GtkWidget* parent_window) {
  GtkFileChooserDialog* file_chooser_dialog;
  {
    gdk_threads_enter();
    file_chooser_dialog = GTK_FILE_CHOOSER_DIALOG(gtk_file_chooser_dialog_new("Save File",
									      (GtkWindow*)parent_window,
									      GTK_FILE_CHOOSER_ACTION_SAVE,
									      GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
									      GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
									      NULL));
    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER(file_chooser_dialog), TRUE);
    gtk_file_chooser_set_create_folders(           GTK_FILE_CHOOSER(file_chooser_dialog), TRUE);
    gtk_file_chooser_set_show_hidden(              GTK_FILE_CHOOSER(file_chooser_dialog), TRUE);
    gdk_threads_leave();
  }
  return file_chooser_dialog;
}

boolean_t funk2_gtk__file_chooser_dialog__set_current_folder(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, u8* filename) {
  boolean_t success;
  {
    gdk_threads_enter();
    success = gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file_chooser_dialog), (char*)filename) ? boolean__true : boolean__false;
    gdk_threads_leave();
  }
  return success;
}

void funk2_gtk__file_chooser_dialog__set_current_name(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, u8* current_name) {
  {
    gdk_threads_enter();
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(file_chooser_dialog), (char*)current_name);
    gdk_threads_leave();
  }
}

boolean_t funk2_gtk__file_chooser_dialog__set_filename(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, u8* filename) {
  boolean_t success;
  {
    gdk_threads_enter();
    success = gtk_file_chooser_set_filename(GTK_FILE_CHOOSER(file_chooser_dialog), (char*)filename) ? boolean__true : boolean__false;
    gdk_threads_leave();
  }
  return success;
}

f2ptr funk2_gtk__file_chooser_dialog__get_filenames(funk2_gtk_t* this, f2ptr cause, GtkFileChooserDialog* file_chooser_dialog) {
  f2ptr filenames = nil;
  {
    gdk_threads_enter();
    GSList* gs_list = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(file_chooser_dialog));
    while (gs_list != NULL) {
      char* filename_str = (char*)(gs_list->data);
      {
	filenames = raw__cons__new(cause, new__string(cause, filename_str), filenames);
	g_free(filename_str);
      }
      gs_list = gs_list->next;
    }
    g_slist_free(gs_list);
    gdk_threads_leave();
  }
  return filenames;
}

void funk2_gtk__file_chooser_dialog__set_select_multiple(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, boolean_t select_multiple) {
  {
    gdk_threads_enter();
    gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser_dialog), select_multiple ? TRUE : FALSE);
    gdk_threads_leave();
  }
}

void funk2_gtk__file_chooser_dialog__add_file_filter_pattern(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, u8* name, u8* pattern) {
  {
    gdk_threads_enter();
    GtkFileFilter* file_filter = gtk_file_filter_new();
    gtk_file_filter_set_name(   file_filter, (char*)name);
    gtk_file_filter_add_pattern(file_filter, (char*)pattern);
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser_dialog), file_filter);
    gdk_threads_leave();
  }
}

void funk2_gtk__file_chooser_dialog__set_preview_widget(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, GtkWidget* widget) {
  {
    gdk_threads_enter();
    gtk_file_chooser_set_preview_widget(GTK_FILE_CHOOSER(file_chooser_dialog), GTK_WIDGET(widget));
    gdk_threads_leave();
  }
}

void funk2_gtk__file_chooser_dialog__set_preview_widget_active(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog, boolean_t preview_widget_active) {
  {
    gdk_threads_enter();
    gtk_file_chooser_set_preview_widget_active(GTK_FILE_CHOOSER(file_chooser_dialog), preview_widget_active ? TRUE : FALSE);
    gdk_threads_leave();
  }
}

char* funk2_gtk__file_chooser_dialog__get_preview_filename(funk2_gtk_t* this, GtkFileChooserDialog* file_chooser_dialog) {
  char* filename;
  {
    gdk_threads_enter();
    filename = gtk_file_chooser_get_preview_filename(GTK_FILE_CHOOSER(file_chooser_dialog));
    gdk_threads_leave();
  }
  return filename;
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
  if (&(__funk2__gtk->initialized_successfully)) {
    return boolean__true;
  } else {
    return boolean__false;
  }
#else
  return boolean__false;
#endif //F2__GTK__SUPPORTED
}

f2ptr f2__gtk__is_supported(f2ptr cause) {
  return f2bool__new(raw__gtk__is_supported(cause));
}
export_cefunk0(gtk__is_supported, 0,
	       "Returns true if GIMP ToolKit (GTK) support has been compiled into this version of Funk2.");
//def_pcfunk0(gtk__is_supported,
//	    "Returns true if GIMP ToolKit (GTK) support has been compiled into this version of Funk2.",
//	    return f2__gtk__is_supported(this_cause));


f2ptr raw__gtk__window__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* window = funk2_gtk__window__new(__funk2__gtk);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(window)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__new(f2ptr cause) {
  return raw__gtk__window__new(cause);
}
export_cefunk0(gtk__window__new, 0,
	       "Returns a new window widget.");
//def_pcfunk0(gtk__window__new,
//	    "Returns a new window widget.",
//	    return f2__gtk__window__new(this_cause));


#define assert_g_type(g_type, variable) {				\
    if (! G_TYPE_CHECK_INSTANCE_TYPE(variable, g_type)) {		\
      return f2larva__new(cause, 511, f2__bug__new(cause, f2integer__new(cause, 511), f2__frame__new(cause, f2list10__new(cause, \
															  new__symbol(cause, "bug_type"),           new__symbol(cause, "invalid_g_type"), \
															  new__symbol(cause, "source_filename"),    new__string(cause, (char*)__FILE__), \
															  new__symbol(cause, "source_line_number"), f2integer__new(cause, (s64)__LINE__), \
															  new__symbol(cause, "correct_g_type"),     new__symbol(cause, #g_type), \
															  new__symbol(cause, "funktion"),           new__symbol(cause, (char*)__FUNCTION__))))); \
    }									\
  }

#define assert_gtk_object_is_from_this_session(object_type, object) ({	\
      f2ptr assert_gtk_object_is_from_this_session__temp_object = (object); \
      if (! raw__##object_type##__is_from_this_session(cause, assert_gtk_object_is_from_this_session__temp_object)) { \
	return new__error(f2list4__new(cause,				\
				       new__symbol(cause, "bug_name"),            new__symbol(cause, #object_type "_is_not_from_this_session"), \
				       new__symbol(cause, #object_type "-value"), assert_gtk_object_is_from_this_session__temp_object)); \
      }									\
      assert_gtk_object_is_from_this_session__temp_object;		\
    })

f2ptr raw__gtk__window__set_title(f2ptr cause, f2ptr window, f2ptr title) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, window);
    GtkWidget* gtk_window = raw__gtk_widget__as__GtkWidget(cause, window);
    
    assert_g_type(GTK_TYPE_WINDOW, gtk_window);
    
    u64 title__utf8_length = raw__string__utf8_length(cause, title);
    u8* title__utf8_str    = (u8*)alloca(title__utf8_length + 1);
    raw__string__utf8_str_copy(cause, title, title__utf8_str);
    title__utf8_str[title__utf8_length] = 0;
    
    funk2_gtk__window__set_title(__funk2__gtk, gtk_window, title__utf8_str);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__set_title(f2ptr cause, f2ptr window, f2ptr title) {
  assert_argument_type(gtk_widget, window);
  assert_argument_type(string,     title);
  return raw__gtk__window__set_title(cause, window, title);
}
export_cefunk2(gtk__window__set_title, window, title, 0,
	       "Sets the title of this gtk_window.");
//def_pcfunk2(gtk__window__set_title, window, title,
//	    "Sets the title of this gtk_window.",
//	    return f2__gtk__window__set_title(this_cause, window, title));


f2ptr raw__gtk__window__set_default_size(f2ptr cause, f2ptr window, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, window);
    GtkWidget* gtk_window = raw__gtk_widget__as__GtkWidget(cause, window);
    
    assert_g_type(GTK_TYPE_WINDOW, gtk_window);
    
    s64        width__i   = f2integer__i(width,  cause);
    s64        height__i  = f2integer__i(height, cause);
    funk2_gtk__window__set_default_size(__funk2__gtk, gtk_window, width__i, height__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__set_default_size(f2ptr cause, f2ptr window, f2ptr width, f2ptr height) {
  assert_argument_type(gtk_widget, window);
  assert_argument_type(integer,    width);
  assert_argument_type(integer,    height);
  return raw__gtk__window__set_default_size(cause, window, width, height);
}
export_cefunk3(gtk__window__set_default_size, window, width, height, 0,
	       "Sets the default width and height of this gtk_window.");
//def_pcfunk3(gtk__window__set_default_size, window, width, height,
//	    "Sets the default width and height of this gtk_window.",
//	    return f2__gtk__window__set_default_size(this_cause, window, width, height));


f2ptr raw__gtk__window__resize(f2ptr cause, f2ptr window, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, window);
    GtkWidget* gtk_window = raw__gtk_widget__as__GtkWidget(cause, window);
    
    assert_g_type(GTK_TYPE_WINDOW, gtk_window);
    
    s64        width__i   = f2integer__i(width,  cause);
    s64        height__i  = f2integer__i(height, cause);
    funk2_gtk__window__resize(__funk2__gtk, gtk_window, width__i, height__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__resize(f2ptr cause, f2ptr window, f2ptr width, f2ptr height) {
  assert_argument_type(gtk_widget, window);
  assert_argument_type(integer,    width);
  assert_argument_type(integer,    height);
  return raw__gtk__window__resize(cause, window, width, height);
}
export_cefunk3(gtk__window__resize, window, width, height, 0,
	       "Resizes the gtk_window.");
//def_pcfunk3(gtk__window__resize, window, width, height,
//	    "Resizes the gtk_window.",
//	    return f2__gtk__window__resize(this_cause, window, width, height));


f2ptr raw__gtk__window__set_transient_for(f2ptr cause, f2ptr window, f2ptr parent) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, window);
    assert_gtk_object_is_from_this_session(gtk_widget, parent);
    GtkWidget* gtk_window        = raw__gtk_widget__as__GtkWidget(cause, window);
    GtkWidget* gtk_parent_window = raw__gtk_widget__as__GtkWidget(cause, parent);
    
    assert_g_type(GTK_TYPE_WINDOW, gtk_window);
    assert_g_type(GTK_TYPE_WINDOW, gtk_parent_window);
    
    funk2_gtk__window__set_transient_for(__funk2__gtk, gtk_window, gtk_parent_window);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__set_transient_for(f2ptr cause, f2ptr window, f2ptr parent) {
  assert_argument_type(gtk_widget, window);
  assert_argument_type(gtk_widget, parent);
  return raw__gtk__window__set_transient_for(cause, window, parent);
}
export_cefunk2(gtk__window__set_transient_for, window, parent, 0,
	       "Dialog windows should be set transient for the main application window they were spawned from. This allows window managers to e.g. keep the dialog on top of the main window, or center the dialog over the main window. gtk_dialog_new_with_buttons() and other convenience functions in GTK+ will sometimes call gtk_window_set_transient_for() on your behalf.\n"
	       "\n"
	       "Passing NULL for parent unsets the current transient window.\n"
	       "\n"
	       "On Windows, this function puts the child window on top of the parent, much as the window manager would have done on X.\n"
	       "\n"
	       "window :\n"
	       "	a GtkWindow\n"
	       "\n"
	       "parent :\n"
	       "	parent window, or NULL. [allow-none]");
//def_pcfunk2(gtk__window__set_transient_for, window, parent,
//  "Dialog windows should be set transient for the main application window they were spawned from. This allows window managers to e.g. keep the dialog on top of the main window, or center the dialog over the main window. gtk_dialog_new_with_buttons() and other convenience functions in GTK+ will sometimes call gtk_window_set_transient_for() on your behalf.\n"
//	    "\n"
//	    "Passing NULL for parent unsets the current transient window.\n"
//	    "\n"
//	    "On Windows, this function puts the child window on top of the parent, much as the window manager would have done on X.\n"
//	    "\n"
//	    "window :\n"
//	    "	a GtkWindow\n"
//  "\n"
//	    "parent :\n"
//	    "	parent window, or NULL. [allow-none]",
//	    return f2__gtk__window__set_transient_for(this_cause, window, parent));


f2ptr raw__gtk__window__set_destroy_with_parent(f2ptr cause, f2ptr window, f2ptr setting) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, window);
    GtkWidget* gtk_window = raw__gtk_widget__as__GtkWidget(cause, window);
    
    assert_g_type(GTK_TYPE_WINDOW, gtk_window);
    
    funk2_gtk__window__set_destroy_with_parent(__funk2__gtk, gtk_window, (setting != nil) ? boolean__true : boolean__false);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__window__set_destroy_with_parent(f2ptr cause, f2ptr window, f2ptr setting) {
  assert_argument_type(gtk_widget, window);
  return raw__gtk__window__set_destroy_with_parent(cause, window, setting);
}
export_cefunk2(gtk__window__set_destroy_with_parent, window, setting, 0,
	       "If setting is TRUE, then destroying the transient parent of window will also destroy window itself. This is useful for dialogs that shouldn't persist beyond the lifetime of the main window they're associated with, for example.\n"
	       "\n"
	       "window :\n"
	       "	a GtkWindow\n"
	       "\n"
	       "setting :\n"
	       "	whether to destroy window with its transient parent");
//def_pcfunk2(gtk__window__set_destroy_with_parent, window, setting,
//    "If setting is TRUE, then destroying the transient parent of window will also destroy window itself. This is useful for dialogs that shouldn't persist beyond the lifetime of the main window they're associated with, for example.\n"
//	    "\n"
//	    "window :\n"
//	    "	a GtkWindow\n"
//	    "\n"
//	    "setting :\n"
//	    "	whether to destroy window with its transient parent",
//	    return f2__gtk__window__set_destroy_with_parent(this_cause, window, setting));


// vbox

f2ptr raw__gtk__vbox__new(f2ptr cause, f2ptr spacing) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64        spacing__i = f2integer__i(spacing, cause);
    GtkWidget* vbox       = funk2_gtk__vbox__new(__funk2__gtk, spacing__i);
    return f2__gtk_box__new(cause, f2pointer__new(cause, to_ptr(vbox)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__vbox__new(f2ptr cause, f2ptr spacing) {
  assert_argument_type(integer, spacing);
  return raw__gtk__vbox__new(cause, spacing);
}
export_cefunk1(gtk__vbox__new, spacing, 0,
	       "Returns a new vbox widget with spacing.");
//def_pcfunk1(gtk__vbox__new, spacing,
//	    "Returns a new vbox widget with spacing.",
//	    return f2__gtk__vbox__new(this_cause, spacing));


f2ptr raw__gtk__hbox__new(f2ptr cause, f2ptr spacing) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64        spacing__i = f2integer__i(spacing, cause);
    GtkWidget* hbox       = funk2_gtk__hbox__new(__funk2__gtk, spacing__i);
    return f2__gtk_box__new(cause, f2pointer__new(cause, to_ptr(hbox)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__hbox__new(f2ptr cause, f2ptr spacing) {
  assert_argument_type(integer, spacing);
  return raw__gtk__hbox__new(cause, spacing);
}
export_cefunk1(gtk__hbox__new, spacing, 0,
	       "Returns a new hbox widget with spacing.");
//def_pcfunk1(gtk__hbox__new, spacing,
//	    "Returns a new hbox widget with spacing.",
//	    return f2__gtk__hbox__new(this_cause, spacing));


f2ptr raw__gtk__button__new_with_label(f2ptr cause, f2ptr label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64 label__length = raw__string__utf8_length(cause, label);
    u8* label__str    = (u8*)alloca(label__length + 1);
    raw__string__utf8_str_copy(cause, label, label__str);
    label__str[label__length] = 0;
    
    GtkWidget* button = funk2_gtk__button__new_with_label(__funk2__gtk, label__str);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(button)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__button__new_with_label(f2ptr cause, f2ptr label) {
  assert_argument_type(string, label);
  return raw__gtk__button__new_with_label(cause, label);
}
export_cefunk1(gtk__button__new_with_label, label, 0,
	       "Returns a new button widget with label.");
//def_pcfunk1(gtk__button__new_with_label, label,
//	    "Returns a new button widget with label.",
//	    return f2__gtk__button__new_with_label(this_cause, label));


f2ptr raw__gtk__scrolled_window__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* scrolled_window = funk2_gtk__scrolled_window__new(__funk2__gtk);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(scrolled_window)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scrolled_window__new(f2ptr cause) {
  return raw__gtk__scrolled_window__new(cause);
}
export_cefunk0(gtk__scrolled_window__new, 0,
	       "Returns a new scrolled_window widget.");
//def_pcfunk0(gtk__scrolled_window__new,
//	    "Returns a new scrolled_window widget.",
//	    return f2__gtk__scrolled_window__new(this_cause));


f2ptr raw__gtk__scrolled_window__add_with_viewport(f2ptr cause, f2ptr scrolled_window, f2ptr child) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, scrolled_window);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    GtkWidget* gtk_scrolled_window = raw__gtk_widget__as__GtkWidget(cause, scrolled_window);
    GtkWidget* gtk_child           = raw__gtk_widget__as__GtkWidget(cause, child);
    
    assert_g_type(GTK_TYPE_SCROLLED_WINDOW, gtk_scrolled_window);
    assert_g_type(GTK_TYPE_WIDGET,          gtk_child);
    
    funk2_gtk__scrolled_window__add_with_viewport(__funk2__gtk, gtk_scrolled_window, gtk_child);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scrolled_window__add_with_viewport(f2ptr cause, f2ptr scrolled_window, f2ptr child) {
  assert_argument_type(gtk_widget, scrolled_window);
  assert_argument_type(gtk_widget, child);
  return raw__gtk__scrolled_window__add_with_viewport(cause, scrolled_window, child);
}
export_cefunk2(gtk__scrolled_window__add_with_viewport, scrolled_window, child, 0,
	       "Adds a non-scrollable widget to a scroll window.");
//def_pcfunk2(gtk__scrolled_window__add_with_viewport, scrolled_window, child,
//	    "Adds a non-scrollable widget to a scroll window.",
//	    return f2__gtk__scrolled_window__add_with_viewport(this_cause, scrolled_window, child));


boolean_t raw__gtk_policy_type__is_type(f2ptr cause, f2ptr this) {
  return (raw__symbol__is_type(cause, this) &&
	  (raw__eq(cause, this, new__symbol(cause, "always"))    ||
	   raw__eq(cause, this, new__symbol(cause, "automatic")) ||
	   raw__eq(cause, this, new__symbol(cause, "never"))));
}

#if defined(F2__GTK__SUPPORTED)
GtkPolicyType raw__gtk_policy_type__as__GtkPolicyType(f2ptr cause, f2ptr this) {
  if (raw__eq(cause, this, new__symbol(cause, "always"))) {
    return GTK_POLICY_ALWAYS;
  } else if (raw__eq(cause, this, new__symbol(cause, "automatic"))) {
    return GTK_POLICY_AUTOMATIC;
  } else if (raw__eq(cause, this, new__symbol(cause, "never"))) {
    return GTK_POLICY_NEVER;
  }
  error(nil, "raw__gtk_policy_type__as__GtkPolicyType ERROR: this is not gtk_policy_type.");
}
#endif

f2ptr raw__gtk__scrolled_window__set_policy(f2ptr cause, f2ptr scrolled_window, f2ptr hscrollbar_policy, f2ptr vscrollbar_policy) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, scrolled_window);
    GtkWidget* gtk_scrolled_window = raw__gtk_widget__as__GtkWidget(cause, scrolled_window);
    
    assert_g_type(GTK_TYPE_SCROLLED_WINDOW, gtk_scrolled_window);
    
    GtkPolicyType gtk_hscrollbar_policy = raw__gtk_policy_type__as__GtkPolicyType(cause, hscrollbar_policy);
    GtkPolicyType gtk_vscrollbar_policy = raw__gtk_policy_type__as__GtkPolicyType(cause, vscrollbar_policy);
    funk2_gtk__scrolled_window__set_policy(__funk2__gtk, gtk_scrolled_window, gtk_hscrollbar_policy, gtk_vscrollbar_policy);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scrolled_window__set_policy(f2ptr cause, f2ptr scrolled_window, f2ptr hscrollbar_policy, f2ptr vscrollbar_policy) {
  assert_argument_type(gtk_widget,      scrolled_window);
  assert_argument_type(gtk_policy_type, hscrollbar_policy);
  assert_argument_type(gtk_policy_type, vscrollbar_policy);
  return raw__gtk__scrolled_window__set_policy(cause, scrolled_window, hscrollbar_policy, vscrollbar_policy);
}
export_cefunk3(gtk__scrolled_window__set_policy, scrolled_window, hscrollbar_policy, vscrollbar_policy, 0,
	       "Sets the policy for the vertical and horizontal scrollbars of a scrolled window.  Valid policies are (1) `always, (2) `automatic, and (3) `never.");
//def_pcfunk3(gtk__scrolled_window__set_policy, scrolled_window, hscrollbar_policy, vscrollbar_policy,
//	    "Sets the policy for the vertical and horizontal scrollbars of a scrolled window.  Valid policies are (1) `always, (2) `automatic, and (3) `never.",
//	    return f2__gtk__scrolled_window__set_policy(this_cause, scrolled_window, hscrollbar_policy, vscrollbar_policy));


f2ptr raw__gtk__text_view__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* text_view = funk2_gtk__text_view__new(__funk2__gtk);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(text_view)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_view__new(f2ptr cause) {
  return raw__gtk__text_view__new(cause);
}
export_cefunk0(gtk__text_view__new, 0,
	       "Returns a new text_view widget.");
//def_pcfunk0(gtk__text_view__new,
//	    "Returns a new text_view widget.",
//	    return f2__gtk__text_view__new(this_cause));


f2ptr raw__gtk__text_view__get_buffer(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_TEXT_VIEW, gtk_widget);
    
    GtkTextBuffer* buffer = funk2_gtk__text_view__get_buffer(__funk2__gtk, gtk_widget);
    if (! buffer) {
      return nil;
    }
    
    assert_g_type(GTK_TYPE_TEXT_BUFFER, buffer);
    
    return f2__gtk_text_buffer__new(cause, f2pointer__new(cause, to_ptr(buffer)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_view__get_buffer(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__text_view__get_buffer(cause, widget);
}
export_cefunk1(gtk__text_view__get_buffer, widget, 0,
	       "Returns the buffer widget of a text_view widget.");
//def_pcfunk1(gtk__text_view__get_buffer, widget,
//	    "Returns the buffer widget of a text_view widget.",
//	    return f2__gtk__text_view__get_buffer(this_cause, widget));


f2ptr raw__gtk__text_view__set_wrap_mode(f2ptr cause, f2ptr widget, f2ptr wrap_mode) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_TEXT_VIEW, gtk_widget);

    GtkWrapMode gtk_wrap_mode = GTK_WRAP_NONE;
    if ((wrap_mode == nil) ||
	raw__eq(cause, new__symbol(cause, "none"), wrap_mode)) {
      gtk_wrap_mode = GTK_WRAP_NONE;
    } else if (raw__eq(cause, new__symbol(cause, "char"), wrap_mode)) {
      gtk_wrap_mode = GTK_WRAP_CHAR;
    } else if (raw__eq(cause, new__symbol(cause, "word"), wrap_mode)) {
      gtk_wrap_mode = GTK_WRAP_WORD;
    } else if (raw__eq(cause, new__symbol(cause, "word_char"), wrap_mode)) {
      gtk_wrap_mode = GTK_WRAP_WORD_CHAR;
    } else {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),  new__symbol(cause, "unknown_word_wrap_mode"),
				     new__symbol(cause, "this"),      widget,
				     new__symbol(cause, "wrap_mode"), wrap_mode));
    }
    
    funk2_gtk__text_view__set_wrap_mode(__funk2__gtk, gtk_widget, gtk_wrap_mode);
    
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_view__set_wrap_mode(f2ptr cause, f2ptr widget, f2ptr wrap_mode) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__text_view__set_wrap_mode(cause, widget, wrap_mode);
}
export_cefunk2(gtk__text_view__set_wrap_mode, widget, wrap_mode, 0,
	       "Sets the wrap mode of this text_view widget.");
//def_pcfunk2(gtk__text_view__set_wrap_mode, widget, wrap_mode,
//	    "Sets the wrap mode of this text_view widget.",
//	    return f2__gtk__text_view__set_wrap_mode(this_cause, widget, wrap_mode));


// gdk_pixbuf

f2ptr raw__gtk__pixbuf__new_from_rgb_data(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    s64 width__i  = f2integer__i(width,  cause);
    s64 height__i = f2integer__i(height, cause);
    if (width__i <= 0 || height__i <= 0) {
      return f2larva__new(cause, 2, nil);
    }
    if ((width__i  > XLIB_IMAGE_SIDE_SIZE_LIMIT) ||
	(height__i > XLIB_IMAGE_SIDE_SIZE_LIMIT)) {
      return new__error(f2list8__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "gdk_pixbuf_larger_than_XLIB_IMAGE_SIDE_SIZE_LIMIT"),
				     new__symbol(cause, "width"),    width,
				     new__symbol(cause, "height"),   height,
				     new__symbol(cause, "rgb_data"), rgb_data));
    }
    s64 chunk__length = f2chunk__length(rgb_data, cause);
    if (chunk__length != (width__i * height__i * 3)) {
      return f2larva__new(cause, 3, nil);
    }
    u8* pixbuf_rgb_data = (u8*)from_ptr(f2__malloc(chunk__length));
    raw__chunk__str_copy(cause, rgb_data, pixbuf_rgb_data);
    GdkPixbuf* pixbuf = funk2_gtk__pixbuf__new(__funk2__gtk, width__i, height__i, pixbuf_rgb_data);
    return f2__gdk_pixbuf__new(cause, f2pointer__new(cause, to_ptr(pixbuf)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__new_from_rgb_data(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgb_data) {
  assert_argument_type(integer, width);
  assert_argument_type(integer, height);
  assert_argument_type(chunk,   rgb_data);
  return raw__gtk__pixbuf__new_from_rgb_data(cause, width, height, rgb_data);
}
export_cefunk3(gtk__pixbuf__new_from_rgb_data, width, height, rgb_data, 0,
	       "Returns a new gdk_pixbuf object.");
//def_pcfunk3(gtk__pixbuf__new_from_rgb_data, width, height, rgb_data,
//	    "Returns a new gdk_pixbuf object.",
//	    return f2__gtk__pixbuf__new_from_rgb_data(this_cause, width, height, rgb_data));


f2ptr raw__gtk__pixbuf__new_from_rgba_data(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgba_data) {
#if defined(F2__GTK__SUPPORTED)
  s64 width__i  = f2integer__i(width,  cause);
  s64 height__i = f2integer__i(height, cause);
  if (width__i <= 0 || height__i <= 0) {
    return f2larva__new(cause, 2, nil);
  }
  s64 chunk__length = f2chunk__length(rgba_data, cause);
  if (chunk__length != (width__i * height__i * 4)) {
    return f2larva__new(cause, 3, nil);
  }
  u8* pixbuf_rgb_data = (u8*)from_ptr(f2__malloc(width__i * height__i * 3));
  {
    u8* pixbuf_rgba_data = (u8*)from_ptr(f2__malloc(chunk__length));
    raw__chunk__str_copy(cause, rgba_data, pixbuf_rgba_data);
    {
      s64 y;
      for (y = 0; y < height__i; y ++) {
	s64 x;
	for (x = 0; x < width__i; x ++) {
	  s64 rgb_pixel  = (((y * width__i) + x) * 3);
	  s64 rgba_pixel = (((y * width__i) + x) * 4);
	  pixbuf_rgb_data[rgb_pixel + 0] = pixbuf_rgba_data[rgba_pixel + 0];
	  pixbuf_rgb_data[rgb_pixel + 1] = pixbuf_rgba_data[rgba_pixel + 1];
	  pixbuf_rgb_data[rgb_pixel + 2] = pixbuf_rgba_data[rgba_pixel + 2];
	}
      }
    }
    f2__free(to_ptr(pixbuf_rgba_data));
  }
  GdkPixbuf* pixbuf = funk2_gtk__pixbuf__new(__funk2__gtk, width__i, height__i, pixbuf_rgb_data);
  return f2__gdk_pixbuf__new(cause, f2pointer__new(cause, to_ptr(pixbuf)));
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__new_from_rgba_data(f2ptr cause, f2ptr width, f2ptr height, f2ptr rgba_data) {
  assert_argument_type(integer, width);
  assert_argument_type(integer, height);
  assert_argument_type(chunk,   rgba_data);
  return raw__gtk__pixbuf__new_from_rgba_data(cause, width, height, rgba_data);
}
export_cefunk3(gtk__pixbuf__new_from_rgba_data, width, height, rgba_data, 0,
	       "Returns a new gdk_pixbuf object.");
//def_pcfunk3(gtk__pixbuf__new_from_rgba_data, width, height, rgba_data,
//	    "Returns a new gdk_pixbuf object.",
//	    return f2__gtk__pixbuf__new_from_rgba_data(this_cause, width, height, rgba_data));


f2ptr raw__gtk__pixbuf__new_from_file(f2ptr cause, f2ptr filename) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    s64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    GError*    g_error = NULL;
    GdkPixbuf* pixbuf  = funk2_gtk__pixbuf__new_from_file(__funk2__gtk, filename__utf8_str, &g_error);
    f2ptr      this    = nil;
    if (pixbuf != NULL) {
      this = f2__gdk_pixbuf__new(cause, f2pointer__new(cause, to_ptr(pixbuf)));
    } else {
      if (g_error == NULL) {
	this = f2larva__new(cause, 2135, f2__bug__new(cause, f2integer__new(cause, 2135), f2__frame__new(cause, f2list4__new(cause,
															     new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_load_pixbuf_from_file-no_specific_gtk_error"),
															     new__symbol(cause, "filename"), filename))));
      } else {
	this = f2larva__new(cause, 2135, f2__bug__new(cause, f2integer__new(cause, 2135), f2__frame__new(cause, f2list8__new(cause,
															     new__symbol(cause, "bug_type"),          new__symbol(cause, "could_not_load_pixbuf_from_file"),
															     new__symbol(cause, "filename"),          filename,
															     new__symbol(cause, "gtk-error-code"),    f2integer__new(cause, g_error->code),
															     new__symbol(cause, "gtk-error-message"), new__string(cause, g_error->message)))));
      }
    }
    f2__free(to_ptr(filename__utf8_str));
    return this;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__new_from_file(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  return raw__gtk__pixbuf__new_from_file(cause, filename);
}
export_cefunk1(gtk__pixbuf__new_from_file, filename, 0,
	       "Loads the given file, and returns a new gdk_pixbuf object.");
//def_pcfunk1(gtk__pixbuf__new_from_file, filename,
//	    "Loads the given file, and returns a new gdk_pixbuf object.",
//	    return f2__gtk__pixbuf__new_from_file(this_cause, filename));


f2ptr raw__gtk__pixbuf__get_width(f2ptr cause, f2ptr pixbuf) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gdk_pixbuf, pixbuf);
    GdkPixbuf* gdk_pixbuf = raw__gdk_pixbuf__as__GdkPixbuf(cause, pixbuf);
    
    assert_g_type(GDK_TYPE_PIXBUF, gdk_pixbuf);
    
    s64        width      = funk2_gtk__pixbuf__get_width(__funk2__gtk, gdk_pixbuf);
    return f2integer__new(cause, width);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__get_width(f2ptr cause, f2ptr pixbuf) {
  assert_argument_type(gdk_pixbuf, pixbuf);
  return raw__gtk__pixbuf__get_width(cause, pixbuf);
}
export_cefunk1(gtk__pixbuf__get_width, pixbuf, 0,
	       "Returns the width of this gdk_pixbuf.");
//def_pcfunk1(gtk__pixbuf__get_width, pixbuf,
//	    "Returns the width of this gdk_pixbuf.",
//	    return f2__gtk__pixbuf__get_width(this_cause, pixbuf));


f2ptr raw__gtk__pixbuf__get_height(f2ptr cause, f2ptr pixbuf) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gdk_pixbuf, pixbuf);
    GdkPixbuf* gdk_pixbuf = raw__gdk_pixbuf__as__GdkPixbuf(cause, pixbuf);
    
    assert_g_type(GDK_TYPE_PIXBUF, gdk_pixbuf);
    
    s64        height     = funk2_gtk__pixbuf__get_height(__funk2__gtk, gdk_pixbuf);
    return f2integer__new(cause, height);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__get_height(f2ptr cause, f2ptr pixbuf) {
  assert_argument_type(gdk_pixbuf, pixbuf);
  return raw__gtk__pixbuf__get_height(cause, pixbuf);
}
export_cefunk1(gtk__pixbuf__get_height, pixbuf, 0,
	       "Returns the height of this gdk_pixbuf.");
//def_pcfunk1(gtk__pixbuf__get_height, pixbuf,
//	    "Returns the height of this gdk_pixbuf.",
//	    return f2__gtk__pixbuf__get_height(this_cause, pixbuf));


f2ptr raw__gtk__pixbuf__get_rgba_pixel_data(f2ptr cause, f2ptr pixbuf) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gdk_pixbuf, pixbuf);
    GdkPixbuf* gdk_pixbuf = raw__gdk_pixbuf__as__GdkPixbuf(cause, pixbuf);
    
    assert_g_type(GDK_TYPE_PIXBUF, gdk_pixbuf);
    
    s64        width      = funk2_gtk__pixbuf__get_width(__funk2__gtk, gdk_pixbuf);
    s64        height     = funk2_gtk__pixbuf__get_height(__funk2__gtk, gdk_pixbuf);
    u8*        rgba_data  = (u8*)from_ptr(f2__malloc(width * height * 4));
    boolean_t  success    = funk2_gtk__pixbuf__copy_rgba_pixel_data(__funk2__gtk, gdk_pixbuf, rgba_data);
    if (! success) {
      return f2larva__new(cause, 13451, nil);
    }
    f2ptr this = f2chunk__new(cause, width * height * 4, rgba_data);
    f2__free(to_ptr(rgba_data));
    return this;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__get_rgba_pixel_data(f2ptr cause, f2ptr pixbuf) {
  assert_argument_type(gdk_pixbuf, pixbuf);
  return raw__gtk__pixbuf__get_rgba_pixel_data(cause, pixbuf);
}
export_cefunk1(gtk__pixbuf__get_rgba_pixel_data, pixbuf, 0,
	       "Returns a chunk containing the rgba data of this gdk_pixbuf.");
//def_pcfunk1(gtk__pixbuf__get_rgba_pixel_data, pixbuf,
//	    "Returns a chunk containing the rgba data of this gdk_pixbuf.",
//	    return f2__gtk__pixbuf__get_rgba_pixel_data(this_cause, pixbuf));


f2ptr raw__gtk__pixbuf__get_rgb_pixel_data(f2ptr cause, f2ptr pixbuf) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gdk_pixbuf, pixbuf);
    GdkPixbuf* gdk_pixbuf = raw__gdk_pixbuf__as__GdkPixbuf(cause, pixbuf);
    
    assert_g_type(GDK_TYPE_PIXBUF, gdk_pixbuf);
    
    s64        width      = funk2_gtk__pixbuf__get_width(__funk2__gtk, gdk_pixbuf);
    s64        height     = funk2_gtk__pixbuf__get_height(__funk2__gtk, gdk_pixbuf);
    u8*        rgb_data   = (u8*)from_ptr(f2__malloc(width * height * 3));
    boolean_t  success    = funk2_gtk__pixbuf__copy_rgb_pixel_data(__funk2__gtk, gdk_pixbuf, rgb_data);
    if (! success) {
      return f2larva__new(cause, 13452, nil);
    }
    f2ptr this = f2chunk__new(cause, width * height * 3, rgb_data);
    f2__free(to_ptr(rgb_data));
    return this;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__pixbuf__get_rgb_pixel_data(f2ptr cause, f2ptr pixbuf) {
  assert_argument_type(gdk_pixbuf, pixbuf);
  return raw__gtk__pixbuf__get_rgb_pixel_data(cause, pixbuf);
}
export_cefunk1(gtk__pixbuf__get_rgb_pixel_data, pixbuf, 0,
	       "Returns a chunk containing the rgb data of this gdk_pixbuf.");
//def_pcfunk1(gtk__pixbuf__get_rgb_pixel_data, pixbuf,
//	    "Returns a chunk containing the rgb data of this gdk_pixbuf.",
//	    return f2__gtk__pixbuf__get_rgb_pixel_data(this_cause, pixbuf));


// container

f2ptr raw__gtk__container__add(f2ptr cause, f2ptr widget, f2ptr add_widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    assert_gtk_object_is_from_this_session(gtk_widget, add_widget);
    GtkWidget* gtk_widget     = raw__gtk_widget__as__GtkWidget(cause, widget);
    GtkWidget* add_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, add_widget);
    
    assert_g_type(GTK_TYPE_CONTAINER, gtk_widget);
    assert_g_type(GTK_TYPE_WIDGET,    add_gtk_widget);
    
    funk2_gtk__container__add(__funk2__gtk, gtk_widget, add_gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__container__add(f2ptr cause, f2ptr widget, f2ptr add_widget) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(gtk_widget, add_widget);
  return raw__gtk__container__add(cause, widget, add_widget);
}
export_cefunk2(gtk__container__add, widget, add_widget, 0,
	       "Adds a widget to a container.");
//def_pcfunk2(gtk__container__add, widget, add_widget,
//	    "Adds a widget to a container.",
//	    return f2__gtk__container__add(this_cause, widget, add_widget));


f2ptr raw__gtk__container__remove(f2ptr cause, f2ptr widget, f2ptr remove_widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    assert_gtk_object_is_from_this_session(gtk_widget, remove_widget);
    GtkWidget* gtk_widget        = raw__gtk_widget__as__GtkWidget(cause, widget);
    GtkWidget* remove_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, remove_widget);

    assert_g_type(GTK_TYPE_CONTAINER, gtk_widget);
    assert_g_type(GTK_TYPE_WIDGET,    remove_gtk_widget);
    
    funk2_gtk__container__remove(__funk2__gtk, gtk_widget, remove_gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__container__remove(f2ptr cause, f2ptr widget, f2ptr remove_widget) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(gtk_widget, remove_widget);
  return raw__gtk__container__remove(cause, widget, remove_widget);
}
export_cefunk2(gtk__container__remove, widget, remove_widget, 0,
	       "Removes a widget from a container.");
//def_pcfunk2(gtk__container__remove, widget, remove_widget,
//	    "Removes a widget from a container.",
//	    return f2__gtk__container__remove(this_cause, widget, remove_widget));



f2ptr raw__gtk__container__replace(f2ptr cause, f2ptr widget, f2ptr remove_widget, f2ptr add_widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    assert_gtk_object_is_from_this_session(gtk_widget, remove_widget);
    assert_gtk_object_is_from_this_session(gtk_widget, add_widget);
    GtkWidget* gtk_widget        = raw__gtk_widget__as__GtkWidget(cause, widget);
    GtkWidget* remove_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, remove_widget);
    GtkWidget* add_gtk_widget    = raw__gtk_widget__as__GtkWidget(cause, add_widget);
    
    assert_g_type(GTK_TYPE_CONTAINER, gtk_widget);
    assert_g_type(GTK_TYPE_WIDGET,    remove_gtk_widget);
    assert_g_type(GTK_TYPE_WIDGET,    add_gtk_widget);
    
    funk2_gtk__container__replace(__funk2__gtk, gtk_widget, remove_gtk_widget, add_gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__container__replace(f2ptr cause, f2ptr widget, f2ptr remove_widget, f2ptr add_widget) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(gtk_widget, remove_widget);
  assert_argument_type(gtk_widget, add_widget);
  return raw__gtk__container__replace(cause, widget, remove_widget, add_widget);
}
export_cefunk3(gtk__container__replace, widget, remove_widget, add_widget, 0,
	       "Atomically removes one and then adds another widget to a container.");
//def_pcfunk3(gtk__container__replace, widget, remove_widget, add_widget,
//	    "Atomically removes one and then adds another widget to a container.",
//	    return f2__gtk__container__replace(this_cause, widget, remove_widget, add_widget));


// expose_event

f2ptr raw__gtk__expose_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__expose_event__signal_connect(__funk2__gtk, gtk_widget, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__expose_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__expose_event__signal_connect(cause, widget, cause, funk, args);
}
export_cefunk3(gtk__expose_event__signal_connect, widget, funk, args, 0,
	       "Connects an expose_event signal handler to a GtkWidget.");
//def_pcfunk3(gtk__expose_event__signal_connect, widget, funk, args,
//	    "Connects an expose_event signal handler to a GtkWidget.",
//	    return f2__gtk__expose_event__signal_connect(this_cause, widget, funk, args));


// key_press_event

f2ptr raw__gtk__key_press_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__key_press_event__signal_connect(__funk2__gtk, gtk_widget, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__key_press_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__key_press_event__signal_connect(cause, widget, cause, funk, args);
}
export_cefunk3(gtk__key_press_event__signal_connect, widget, funk, args, 0,
	       "Connects an key_press_event signal handler to a GtkWidget.");
//def_pcfunk3(gtk__key_press_event__signal_connect, widget, funk, args,
//	    "Connects an key_press_event signal handler to a GtkWidget.",
//	    return f2__gtk__key_press_event__signal_connect(this_cause, widget, funk, args));


// response_event

f2ptr raw__gtk__response_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__response_event__signal_connect(__funk2__gtk, gtk_widget, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__response_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__response_event__signal_connect(cause, widget, funk, args);
}
export_cefunk3(gtk__response_event__signal_connect, widget, funk, args, 0,
	       "Connects an response_event signal handler to a GtkWidget.");
//def_pcfunk3(gtk__response_event__signal_connect, widget, funk, args,
//	    "Connects an response_event signal handler to a GtkWidget.",
//	    return f2__gtk__response_event__signal_connect(this_cause, widget, funk, args));


// update_preview_event

f2ptr raw__gtk__update_preview_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__update_preview_event__signal_connect(__funk2__gtk, gtk_widget, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__update_preview_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__update_preview_event__signal_connect(cause, widget, funk, args);
}
export_cefunk3(gtk__update_preview_event__signal_connect, widget, funk, args, 0,
	       "Connects an update_preview_event signal handler to a GtkWidget.");


// value_changed_event

f2ptr raw__gtk__value_changed_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__value_changed_event__signal_connect(__funk2__gtk, gtk_widget, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__value_changed_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__value_changed_event__signal_connect(cause, widget, funk, args);
}
export_cefunk3(gtk__value_changed_event__signal_connect, widget, funk, args, 0,
	       "Connects an value_changed_event signal handler to a GtkWidget.");



// size_allocate_event

f2ptr raw__gtk__size_allocate_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__size_allocate_event__signal_connect(__funk2__gtk, gtk_widget, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__size_allocate_event__signal_connect(f2ptr cause, f2ptr widget, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__size_allocate_event__signal_connect(cause, widget, funk, args);
}
export_cefunk3(gtk__size_allocate_event__signal_connect, widget, funk, args, 0,
	       "Connects an size_allocate_event signal handler to a GtkWidget.");


// works for 'clicked' event but not 'expose_event'

f2ptr raw__gtk__signal_connect(f2ptr cause, f2ptr widget, f2ptr signal_name, f2ptr funk, f2ptr args) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    u64 signal_name__utf8_length = raw__string__utf8_length(cause, signal_name);
    u8* signal_name__utf8_str    = (u8*)alloca(signal_name__utf8_length + 1);
    raw__string__utf8_str_copy(cause, signal_name, signal_name__utf8_str);
    signal_name__utf8_str[signal_name__utf8_length] = 0;
    
    funk2_gtk__signal_connect(__funk2__gtk, gtk_widget, signal_name__utf8_str, cause, funk, args);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__signal_connect(f2ptr cause, f2ptr widget, f2ptr signal_name, f2ptr funk, f2ptr args) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(string,     signal_name);
  assert_argument_type(funkable,   funk);
  assert_argument_type(conslist,   args);
  return raw__gtk__signal_connect(cause, widget, signal_name, funk, args);
}
export_cefunk4(gtk__signal_connect, widget, signal_name, funk, args, 0,
	       "Creates a callback for a widget (see gtk-pop_callback_event).");
//def_pcfunk4(gtk__signal_connect, widget, signal_name, funk, args,
//	    "Creates a callback for a widget (see gtk-pop_callback_event).",
//	    return f2__gtk__signal_connect(this_cause, widget, signal_name, funk, args));



// g_object

f2ptr raw__g__object__ref(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(g_object, this);
    GObject* g_object = raw__g_object__as__GObject(cause, this);
    
    assert_g_type(G_TYPE_OBJECT, g_object);
    
    funk2_g__object__ref(__funk2__gtk, g_object);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__g__object__ref(f2ptr cause, f2ptr this) {
  assert_argument_type(g_object, this);
  return raw__g__object__ref(cause, this);
}
export_cefunk1(g__object__ref, this, 0,
	       "Adds one reference to a widget.  Use this if you need a Funk2 reference to a GObject.  "
	       "Use unref to release the Funk2 reference when you are finished, so that GTK can garbage collect the object.  ");
//def_pcfunk1(g__object__ref, this,
//	    "Adds one reference to a widget.  Use this if you need a Funk2 reference to a GObject.  "
//	    "Use unref to release the Funk2 reference when you are finished, so that GTK can garbage collect the object.  ",
//	    return f2__g__object__ref(this_cause, this));


f2ptr raw__g__object__unref(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(g_object, this);
    GObject* g_object = raw__g_object__as__GObject(cause, this);
    
    assert_g_type(G_TYPE_OBJECT, g_object);
    
    funk2_g__object__unref(__funk2__gtk, g_object);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__g__object__unref(f2ptr cause, f2ptr this) {
  assert_argument_type(g_object, this);
  return raw__g__object__unref(cause, this);
}
export_cefunk1(g__object__unref, this, 0,
	       "Removes one reference to a GTK object.  Use this if you don't need a funk2 reference to a GObject anymore.");
//def_pcfunk1(g__object__unref, this,
//	    "Removes one reference to a GTK object.  Use this if you don't need a funk2 reference to a GObject anymore.",
//	    return f2__g__object__unref(this_cause, this));


// widget

f2ptr raw__gtk__widget__show(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__show(__funk2__gtk, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__show(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__show(cause, widget);
}
export_cefunk1(gtk__widget__show, widget, 0,
	       "Shows the widget and all children.");
//def_pcfunk1(gtk__widget__show, widget,
//	    "Shows the widget and all children.",
//	    return f2__gtk__widget__show(this_cause, widget));


f2ptr raw__gtk__widget__show_all(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__show_all(__funk2__gtk, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__show_all(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__show_all(cause, widget);
}
export_cefunk1(gtk__widget__show_all, widget, 0,
	       "Shows the widget and all children.");
//def_pcfunk1(gtk__widget__show_all, widget,
//	    "Shows the widget and all children.",
//	    return f2__gtk__widget__show_all(this_cause, widget));


f2ptr raw__gtk__widget__hide(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__hide(__funk2__gtk, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__hide(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__hide(cause, widget);
}
export_cefunk1(gtk__widget__hide, widget, 0,
	       "Hides the widget and all children.");
//def_pcfunk1(gtk__widget__hide, widget,
//	    "Hides the widget and all children.",
//	    return f2__gtk__widget__hide(this_cause, widget));


f2ptr raw__gtk__widget__hide_all(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__hide_all(__funk2__gtk, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__hide_all(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__hide_all(cause, widget);
}
export_cefunk1(gtk__widget__hide_all, widget, 0,
	       "Hides the widget and all children.");
//def_pcfunk1(gtk__widget__hide_all, widget,
//	    "Hides the widget and all children.",
//	    return f2__gtk__widget__hide_all(this_cause, widget));


f2ptr raw__gtk__widget__set_size_request(f2ptr cause, f2ptr widget, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    s64        width__i   = f2integer__i(width,  cause);
    s64        height__i  = f2integer__i(height, cause);
    funk2_gtk__widget__set_size_request(__funk2__gtk, gtk_widget, width__i, height__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__set_size_request(f2ptr cause, f2ptr widget, f2ptr width, f2ptr height) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(integer,    width);
  assert_argument_type(integer,    height);
  return raw__gtk__widget__set_size_request(cause, widget, width, height);
}
export_cefunk3(gtk__widget__set_size_request, widget, width, height, 0,
	       "Requests that the widget be a specific size.");
//def_pcfunk3(gtk__widget__set_size_request, widget, width, height,
//	    "Requests that the widget be a specific size.",
//	    return f2__gtk__widget__set_size_request(this_cause, widget, width, height));


f2ptr raw__gtk__widget__get_visible(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    return f2bool__new(funk2_gtk__widget__get_visible(__funk2__gtk, gtk_widget));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__get_visible(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__get_visible(cause, widget);
}
export_cefunk1(gtk__widget__get_visible, widget, 0,
	       "Returns whether or not a window is visible, which does not mean the window is viewable, which wouold require all parents to also be visible.");
//def_pcfunk1(gtk__widget__get_visible, widget,
//	    "Returns whether or not a window is visible, which does not mean the window is viewable, which wouold require all parents to also be visible.",
//	    return f2__gtk__widget__get_visible(this_cause, widget));


f2ptr raw__gtk__widget__destroy(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__destroy(__funk2__gtk, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__destroy(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__destroy(cause, widget);
}
export_cefunk1(gtk__widget__destroy, widget, 0,
	       "Destroys the widget.");
//def_pcfunk1(gtk__widget__destroy, widget,
//	    "Destroys the widget.",
//	    return f2__gtk__widget__destroy(this_cause, widget));


f2ptr raw__gtk__widget__connect_hide_on_delete(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__connect_hide_on_delete(__funk2__gtk, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__connect_hide_on_delete(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__connect_hide_on_delete(cause, widget);
}
export_cefunk1(gtk__widget__connect_hide_on_delete, widget, 0,
	       "Add a delete-event callback handler to the widget that hides the window rather than destroying the window.");
//def_pcfunk1(gtk__widget__connect_hide_on_delete, widget,
//	    "Add a delete-event callback handler to the widget that hides the window rather than destroying the window.",
//	    return f2__gtk__widget__connect_hide_on_delete(this_cause, widget));


boolean_t raw__gtk_state_type__is_type(f2ptr cause, f2ptr this) {
  return (raw__symbol__is_type(cause, this) &&
	  (raw__eq(cause, this, new__symbol(cause, "normal"))   ||
	   raw__eq(cause, this, new__symbol(cause, "active"))   ||
	   raw__eq(cause, this, new__symbol(cause, "prelight")) ||
	   raw__eq(cause, this, new__symbol(cause, "selected")) ||
	   raw__eq(cause, this, new__symbol(cause, "insensitive"))));
}

#if defined(F2__GTK__SUPPORTED)
GtkStateType raw__gtk_state_type__as__GtkStateType(f2ptr cause, f2ptr this) {
  if      (raw__eq(cause, this, new__symbol(cause, "normal")))      {return GTK_STATE_NORMAL;}
  else if (raw__eq(cause, this, new__symbol(cause, "active")))      {return GTK_STATE_ACTIVE;}
  else if (raw__eq(cause, this, new__symbol(cause, "prelight")))    {return GTK_STATE_PRELIGHT;}
  else if (raw__eq(cause, this, new__symbol(cause, "selected")))    {return GTK_STATE_SELECTED;}
  else if (raw__eq(cause, this, new__symbol(cause, "insensitive"))) {return GTK_STATE_INSENSITIVE;}
  error(nil, "raw__gtk_state_type__as__GtkStateType error: received wrong type of value.");
  return 0; // won't ever get here.
}
#endif

f2ptr raw__gtk__widget__modify_fg(f2ptr cause, f2ptr widget, f2ptr state, f2ptr color) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget*   gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    GtkStateType gtk_state  = raw__gtk_state_type__as__GtkStateType(cause, state);
    if (color != nil) {
      GdkColor     gdk_color;   raw__gdk_color__as__GdkColor(cause, color, &gdk_color);
      funk2_gtk__widget__modify_fg(__funk2__gtk, gtk_widget, gtk_state, &gdk_color);
    } else {
      funk2_gtk__widget__modify_fg(__funk2__gtk, gtk_widget, gtk_state, NULL);
    }
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__modify_fg(f2ptr cause, f2ptr widget, f2ptr state, f2ptr color) {
  assert_argument_type(       gtk_widget,     widget);
  assert_argument_type(       gtk_state_type, state);
  assert_argument_type_or_nil(gdk_color,      color);
  return raw__gtk__widget__modify_fg(cause, widget, state, color);
}
export_cefunk3(gtk__widget__modify_fg, widget, state, color, 0,
	       "Sets the foreground color of a widget.  State must be one of the following symbolic values: normal, active, prelight, selected, or insensitive.  Color must be a GdkColor object (see gdk-color-new).");
//def_pcfunk3(gtk__widget__modify_fg, widget, state, color,
//	    "Sets the foreground color of a widget.  State must be one of the following symbolic values: normal, active, prelight, selected, or insensitive.  Color must be a GdkColor object (see gdk-color-new).",
//	    return f2__gtk__widget__modify_fg(this_cause, widget, state, color));


f2ptr raw__gtk__widget__modify_bg(f2ptr cause, f2ptr widget, f2ptr state, f2ptr color) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget*   gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    GtkStateType gtk_state  = raw__gtk_state_type__as__GtkStateType(cause, state);
    if (color != nil) {
      GdkColor     gdk_color;   raw__gdk_color__as__GdkColor(cause, color, &gdk_color);
      funk2_gtk__widget__modify_bg(__funk2__gtk, gtk_widget, gtk_state, &gdk_color);
    } else {
      funk2_gtk__widget__modify_bg(__funk2__gtk, gtk_widget, gtk_state, NULL);
    }
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__modify_bg(f2ptr cause, f2ptr widget, f2ptr state, f2ptr color) {
  assert_argument_type(       gtk_widget,     widget);
  assert_argument_type(       gtk_state_type, state);
  assert_argument_type_or_nil(gdk_color,      color);
  return raw__gtk__widget__modify_bg(cause, widget, state, color);
}
export_cefunk3(gtk__widget__modify_bg, widget, state, color, 0,
	       "Sets the background color of a widget.  State must be one of the following symbolic values: normal, active, prelight, selected, or insensitive.  Color must be a GdkColor object (see gdk-color-new).");
//def_pcfunk3(gtk__widget__modify_bg, widget, state, color,
//	    "Sets the background color of a widget.  State must be one of the following symbolic values: normal, active, prelight, selected, or insensitive.  Color must be a GdkColor object (see gdk-color-new).",
//	    return f2__gtk__widget__modify_bg(this_cause, widget, state, color));


f2ptr raw__gtk__widget__set_sensitive(f2ptr cause, f2ptr widget, f2ptr sensitive) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__set_sensitive(__funk2__gtk, gtk_widget, (sensitive != nil));
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__set_sensitive(f2ptr cause, f2ptr widget, f2ptr sensitive) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__set_sensitive(cause, widget, sensitive);
}
export_cefunk2(gtk__widget__set_sensitive, widget, sensitive, 0,
	       "Sets the sensitivity of a widget.  Insensitive widgets are greyed out.");
//def_pcfunk2(gtk__widget__set_sensitive, widget, sensitive,
//	    "Sets the sensitivity of a widget.  Insensitive widgets are greyed out.",
//	    return f2__gtk__widget__set_sensitive(this_cause, widget, sensitive));


f2ptr raw__gtk__widget__set_no_show_all(f2ptr cause, f2ptr widget, f2ptr no_show_all) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    funk2_gtk__widget__set_no_show_all(__funk2__gtk, gtk_widget, (no_show_all != nil));
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__set_no_show_all(f2ptr cause, f2ptr widget, f2ptr no_show_all) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__widget__set_no_show_all(cause, widget, no_show_all);
}
export_cefunk2(gtk__widget__set_no_show_all, widget, no_show_all, 0,
	       "Sets whether this widget is affected by show_all or hide_all events.");
//def_pcfunk2(gtk__widget__set_no_show_all, widget, no_show_all,
//	    "Sets whether this widget is affected by show_all or hide_all events.",
//	    return f2__gtk__widget__set_no_show_all(this_cause, widget, no_show_all));


// beginning of GtkWidget drawing fuctions, which are not really GtkWidget functions in the GTK library.

f2ptr raw__gtk__widget__queue_draw_area(f2ptr cause, f2ptr widget, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    s64        x__i       = f2integer__i(x,  cause);
    s64        y__i       = f2integer__i(y, cause);
    s64        width__i   = f2integer__i(width,  cause);
    s64        height__i  = f2integer__i(height, cause);
    funk2_gtk__widget__queue_draw_area(__funk2__gtk, gtk_widget, x__i, y__i, width__i, height__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__queue_draw_area(f2ptr cause, f2ptr widget, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(integer,    x);
  assert_argument_type(integer,    y);
  assert_argument_type(integer,    width);
  assert_argument_type(integer,    height);
  return raw__gtk__widget__queue_draw_area(cause, widget, x, y, width, height);
}
export_cefunk5(gtk__widget__queue_draw_area, widget, x, y, width, height, 0,
	       "Requests that a specific rectangle of the widget be redrawn.");
//def_pcfunk5(gtk__widget__queue_draw_area, widget, x, y, width, height,
//	    "Requests that a specific rectangle of the widget be redrawn.",
//	    return f2__gtk__widget__queue_draw_area(this_cause, widget, x, y, width, height));


f2ptr raw__gtk__widget__draw_arc(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height, f2ptr angle1, f2ptr angle2) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    s64        x__i       = f2integer__i(x,      cause);
    s64        y__i       = f2integer__i(y,      cause);
    s64        width__i   = f2integer__i(width,  cause);
    s64        height__i  = f2integer__i(height, cause);
    s64        angle1__i  = f2integer__i(angle1, cause);
    s64        angle2__i  = f2integer__i(angle2, cause);
    funk2_gtk__widget__draw_arc(__funk2__gtk, gtk_widget, (filled != nil) ? TRUE : FALSE, x__i, y__i, width__i, height__i, angle1__i, angle2__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
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
export_cefunk8(gtk__widget__draw_arc, widget, filled, x, y, width, height, angle1, angle2, 0,
	       "Draws an arc in a GtkWidget.  Only works with GtkWidgets that have a GdkWindow!");
//def_pcfunk8(gtk__widget__draw_arc, widget, filled, x, y, width, height, angle1, angle2,
//	    "Draws an arc in a GtkWidget.  Only works with GtkWidgets that have a GdkWindow!",
//	    return f2__gtk__widget__draw_arc(this_cause, widget, filled, x, y, width, height, angle1, angle2));


f2ptr raw__gtk__widget__draw_rectangle(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_WIDGET, gtk_widget);
    
    s64        x__i       = f2integer__i(x,      cause);
    s64        y__i       = f2integer__i(y,      cause);
    s64        width__i   = f2integer__i(width,  cause);
    s64        height__i  = f2integer__i(height, cause);
    funk2_gtk__widget__draw_rectangle(__funk2__gtk, gtk_widget, (filled != nil) ? TRUE : FALSE, x__i, y__i, width__i, height__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__widget__draw_rectangle(f2ptr cause, f2ptr widget, f2ptr filled, f2ptr x, f2ptr y, f2ptr width, f2ptr height) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(integer,    x);
  assert_argument_type(integer,    y);
  assert_argument_type(integer,    width);
  assert_argument_type(integer,    height);
  return raw__gtk__widget__draw_rectangle(cause, widget, filled, x, y, width, height);
}
export_cefunk6(gtk__widget__draw_rectangle, widget, filled, x, y, width, height, 0,
	       "Draws a rectangle in a GtkWidget.  Only works with GtkWidgets that have a GdkWindow!");
//def_pcfunk6(gtk__widget__draw_rectangle, widget, filled, x, y, width, height,
//	    "Draws a rectangle in a GtkWidget.  Only works with GtkWidgets that have a GdkWindow!",
//	    return f2__gtk__widget__draw_rectangle(this_cause, widget, filled, x, y, width, height));


// misc (GtkMisc)

f2ptr raw__gtk__misc__set_alignment(f2ptr cause, f2ptr misc, f2ptr xalign, f2ptr yalign) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, misc);
    GtkWidget* gtk_misc  = raw__gtk_widget__as__GtkWidget(cause, misc);
    
    assert_g_type(GTK_TYPE_MISC, gtk_misc);
    
    double     xalign__d = f2double__d(xalign, cause);
    double     yalign__d = f2double__d(yalign, cause);
    funk2_gtk__misc__set_alignment(__funk2__gtk, gtk_misc, xalign__d, yalign__d);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__misc__set_alignment(f2ptr cause, f2ptr misc, f2ptr xalign, f2ptr yalign) {
  assert_argument_type(gtk_widget, misc);
  assert_argument_type(double,     xalign);
  assert_argument_type(double,     yalign);
  return raw__gtk__misc__set_alignment(cause, misc, xalign, yalign);
}
export_cefunk3(gtk__misc__set_alignment, misc, xalign, yalign, 0,
	       "Sets the alignment is the widget.  xalign and yalign should be between 0.0, left, and 1.0, right.  For example, 0.5 would be centered.");
//def_pcfunk3(gtk__misc__set_alignment, misc, xalign, yalign,
//	    "Sets the alignment is the widget.  xalign and yalign should be between 0.0, left, and 1.0, right.  For example, 0.5 would be centered.",
//	    return f2__gtk__misc__set_alignment(this_cause, misc, xalign, yalign));


// box

f2ptr raw__gtk__box__pack_start(f2ptr cause, f2ptr widget, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    assert_gtk_object_is_from_this_session(gtk_widget, child_widget);
    GtkWidget* gtk_widget       = raw__gtk_widget__as__GtkWidget(cause, widget);
    GtkWidget* child_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, child_widget);
    
    assert_g_type(GTK_TYPE_BOX,    gtk_widget);
    assert_g_type(GTK_TYPE_WIDGET, child_gtk_widget);
    
    u64        padding__i       = f2integer__i(padding, cause);
    funk2_gtk__box__pack_start(__funk2__gtk, gtk_widget, child_gtk_widget, expand != nil, fill != nil, padding__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__box__pack_start(f2ptr cause, f2ptr box, f2ptr child_widget, f2ptr expand, f2ptr fill, f2ptr padding) {
  assert_argument_type(gtk_widget, box);
  assert_argument_type(gtk_widget, child_widget);
  assert_argument_type(integer,    padding);
  return raw__gtk__box__pack_start(cause, box, child_widget, expand, fill, padding);
}
export_cefunk5(gtk__box__pack_start, box, child_widget, expand, fill, padding, 0,
	       "Packs a child widget in a box.");
//def_pcfunk5(gtk__box__pack_start, box, child_widget, expand, fill, padding,
//	    "Packs a child widget in a box.",
//	    return f2__gtk__box__pack_start(this_cause, box, child_widget, expand, fill, padding));


f2ptr f2__gtk__pop_callback_event(f2ptr pop_cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    funk2_gtk_callback_event_t* callback_event = funk2_gtk__pop_callback_event(__funk2__gtk);
    if (! callback_event) {
      return nil;
    }
    f2ptr cause     = callback_event->callback->cause;
    f2ptr funk      = callback_event->callback->funk;
    f2ptr funk_args = callback_event->callback->args;
    f2ptr args;
    {
      switch (callback_event->callback->args_type) {
      case funk2_gtk_callback_args_type__nil:
	args = funk_args;
	break;
      case funk2_gtk_callback_args_type__expose: {
	GdkEventExpose* expose = (GdkEventExpose*)(callback_event->args);
	// should use expose event here... :-)
	
	f2ptr expose_event_frame__event_type;
	if (expose->type == GDK_EXPOSE) {
	  expose_event_frame__event_type = new__symbol(cause, "expose");
	} else if (expose->type == GDK_DAMAGE) {
	  expose_event_frame__event_type = new__symbol(cause, "damage");
	} else {
	  expose_event_frame__event_type = new__symbol(cause, "unknown");
	}
	f2ptr expose_event_frame = f2__frame__new(cause, f2list12__new(cause,
								       new__symbol(cause, "event_type"), expose_event_frame__event_type,
								       new__symbol(cause, "window"),     f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(expose->window))),
								       new__symbol(cause, "send_event"), f2integer__new(cause, expose->send_event),
								       new__symbol(cause, "area"),       f2__frame__new(cause, f2list8__new(cause,
																	    new__symbol(cause, "x"),      f2integer__new(cause, expose->area.x),
																	    new__symbol(cause, "y"),      f2integer__new(cause, expose->area.y),
																	    new__symbol(cause, "width"),  f2integer__new(cause, expose->area.width),
																	    new__symbol(cause, "height"), f2integer__new(cause, expose->area.height))),
								       new__symbol(cause, "region"),     f2pointer__new(cause, to_ptr(expose->region)),
								       new__symbol(cause, "count"),      f2integer__new(cause, expose->count)));
	f2__free(to_ptr(expose));
	args = raw__cons__new(cause, expose_event_frame, funk_args);
      } break;
      case funk2_gtk_callback_args_type__key_press: {
	GdkEventKey* key = (GdkEventKey*)(callback_event->args);
	f2ptr key_event_frame__event_type;
	if (key->type == GDK_KEY_PRESS) {
	  key_event_frame__event_type = new__symbol(cause, "press");
	} else if (key->type == GDK_KEY_RELEASE) {
	  key_event_frame__event_type = new__symbol(cause, "release");
	} else {
	  key_event_frame__event_type = new__symbol(cause, "unknown");
	}
	f2ptr key_event_frame = f2__frame__new(cause, f2list20__new(cause,
								    new__symbol(cause, "event_type"),       key_event_frame__event_type,
								    new__symbol(cause, "window"),           f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(key->window))),
								    new__symbol(cause, "send_event"),       f2integer__new(cause, key->send_event),
								    new__symbol(cause, "time"),             f2integer__new(cause, key->time),
								    new__symbol(cause, "state"),            f2integer__new(cause, key->state),
								    new__symbol(cause, "keyval"),           f2integer__new(cause, key->keyval),
								    new__symbol(cause, "length"),           f2integer__new(cause, key->length),
								    new__symbol(cause, "hardware_keycode"), f2integer__new(cause, key->hardware_keycode),
								    new__symbol(cause, "group"),            f2integer__new(cause, key->group),
								    new__symbol(cause, "is_modifier"),      f2bool__new(key->is_modifier)));
	f2__free(to_ptr(key));
	args = raw__cons__new(cause, key_event_frame, funk_args);
      } break;
      case funk2_gtk_callback_args_type__response: {
	gint* response_id = (gint*)(callback_event->args);
	f2ptr key_event_frame = f2__frame__new(cause, f2list2__new(cause,
								   new__symbol(cause, "response_id"), f2integer__new(cause, *response_id)));
	f2__free(to_ptr(response_id));
	args = raw__cons__new(cause, key_event_frame, funk_args);
      } break;
      case funk2_gtk_callback_args_type__update_preview: {
	args = funk_args;
      } break;
      case funk2_gtk_callback_args_type__value_changed: {
	args = funk_args;
      } break;
      case funk2_gtk_callback_args_type__size_allocate: {
	GtkAllocation* allocation = (GtkAllocation*)(callback_event->args);
	f2ptr size_allocate_event_frame = f2__frame__new(cause, f2list8__new(cause,
									     new__symbol(cause, "x"),      f2integer__new(cause, allocation->x),
									     new__symbol(cause, "y"),      f2integer__new(cause, allocation->y),
									     new__symbol(cause, "width"),  f2integer__new(cause, allocation->width),
									     new__symbol(cause, "height"), f2integer__new(cause, allocation->height)));
	f2__free(to_ptr(allocation));
	args = raw__cons__new(cause, size_allocate_event_frame, funk_args);
      } break;
      default:
	error(nil, "invalid gtk callback event args_type.");
      }
    }
    f2__free(to_ptr(callback_event));
    return f2__gtk_callback__new(cause, funk, args);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}
export_cefunk0(gtk__pop_callback_event, 0,
	       "Returns the next waiting callback event, if one exists, nil otherwise.");
//def_pcfunk0(gtk__pop_callback_event,
//	    "Returns the next waiting callback event, if one exists, nil otherwise.",
//	    return f2__gtk__pop_callback_event(this_cause));


f2ptr raw__gtk__text_buffer__get_start_iter(f2ptr cause, f2ptr text_buffer) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_text_buffer, text_buffer);
    GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
    
    assert_g_type(GTK_TYPE_TEXT_BUFFER, gtk_text_buffer);
    
    GtkTextIter    text_iter;
    funk2_gtk__text_buffer__get_start_iter(__funk2__gtk, gtk_text_buffer, &text_iter);
    return f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&text_iter));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__get_start_iter(f2ptr cause, f2ptr text_buffer) {
  assert_argument_type(gtk_text_buffer, text_buffer);
  return raw__gtk__text_buffer__get_start_iter(cause, text_buffer);
}
export_cefunk1(gtk__text_buffer__get_start_iter, text_buffer, 0,
	       "Returns the starting text_iter of a text_buffer.");
//def_pcfunk1(gtk__text_buffer__get_start_iter, text_buffer,
//	    "Returns the starting text_iter of a text_buffer.",
//	    return f2__gtk__text_buffer__get_start_iter(this_cause, text_buffer));


f2ptr raw__gtk__text_buffer__select_range(f2ptr cause, f2ptr text_buffer, f2ptr range) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_text_buffer, text_buffer);
    GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
    
    assert_g_type(GTK_TYPE_TEXT_BUFFER, gtk_text_buffer);
    
    f2ptr          start_iter = f2__gtk_text_range__start(cause, range);
    f2ptr          end_iter   = f2__gtk_text_range__end(cause, range);
    GtkTextIter    gtk_start_iter;
    GtkTextIter    gtk_end_iter;
    raw__gtk_text_iter__as__GtkTextIter(cause, start_iter, &gtk_start_iter);
    raw__gtk_text_iter__as__GtkTextIter(cause, end_iter,   &gtk_end_iter);
    funk2_gtk__text_buffer__select_range(__funk2__gtk, gtk_text_buffer, &gtk_start_iter, &gtk_end_iter);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__select_range(f2ptr cause, f2ptr text_buffer, f2ptr range) {
  assert_argument_type(gtk_text_buffer, text_buffer);
  assert_argument_type(gtk_text_range,  range);
  return raw__gtk__text_buffer__select_range(cause, text_buffer, range);
}
export_cefunk2(gtk__text_buffer__select_range, text_buffer, range, 0,
	       "Sets select range in this text_buffer.");
//def_pcfunk2(gtk__text_buffer__select_range, text_buffer, range,
//	    "Sets select range in this text_buffer.",
//	    return f2__gtk__text_buffer__select_range(this_cause, text_buffer, range));


f2ptr raw__gtk__text_buffer__get_text(f2ptr cause, f2ptr text_buffer) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_text_buffer, text_buffer);
    GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
    
    assert_g_type(GTK_TYPE_TEXT_BUFFER, gtk_text_buffer);
    
    char* text = funk2_gtk__text_buffer__get_text(__funk2__gtk, gtk_text_buffer);
    return new__string(cause, text);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__get_text(f2ptr cause, f2ptr text_buffer) {
  assert_argument_type(gtk_text_buffer, text_buffer);
  return raw__gtk__text_buffer__get_text(cause, text_buffer);
}
export_cefunk1(gtk__text_buffer__get_text, text_buffer, 0,
	       "Gets the text as a string from a gtk text_buffer widget.");
//def_pcfunk1(gtk__text_buffer__get_text, text_buffer,
//	    "Gets the text as a string from a gtk text_buffer widget.",
//	    return f2__gtk__text_buffer__get_text(this_cause, text_buffer));


f2ptr raw__gtk__text_buffer__set_text(f2ptr cause, f2ptr text_buffer, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_text_buffer, text_buffer);
    GtkTextBuffer* gtk_text_buffer = raw__gtk_text_buffer__as__GtkTextBuffer(cause, text_buffer);
    
    assert_g_type(GTK_TYPE_TEXT_BUFFER, gtk_text_buffer);
    
    u64 text__utf8_length = raw__string__utf8_length(cause, text);
    u8* text__utf8_str    = (u8*)alloca(text__utf8_length + 1);
    raw__string__utf8_str_copy(cause, text, text__utf8_str);
    text__utf8_str[text__utf8_length] = 0;
  
    funk2_gtk__text_buffer__set_text(__funk2__gtk, gtk_text_buffer, text__utf8_str);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_buffer__set_text(f2ptr cause, f2ptr text_buffer, f2ptr text) {
  assert_argument_type(gtk_text_buffer, text_buffer);
  assert_argument_type(string,          text);
  return raw__gtk__text_buffer__set_text(cause, text_buffer, text);
}
export_cefunk2(gtk__text_buffer__set_text, text_buffer, text, 0,
	       "Sets the text for a gtk text_buffer widget.");
//def_pcfunk2(gtk__text_buffer__set_text, text_buffer, text,
//	    "Sets the text for a gtk text_buffer widget.",
//	    return f2__gtk__text_buffer__set_text(this_cause, text_buffer, text));


f2ptr raw__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkTextIter gtk_text_iter;
    raw__gtk_text_iter__as__GtkTextIter(cause, text_iter, &gtk_text_iter);
    u64 text__utf8_length = raw__string__utf8_length(cause, text);
    u8* text__utf8_str    = (u8*)alloca(text__utf8_length + 1);
    raw__string__utf8_str_copy(cause, text, text__utf8_str);
    text__utf8_str[text__utf8_length] = 0;
    
    GtkTextIter mstart;
    GtkTextIter mend;
    boolean_t   found = funk2_gtk__text_iter__forward_search(__funk2__gtk, &gtk_text_iter, text__utf8_str, &mstart, &mend);
    if (! found) {
      return nil;
    }
    return f2__gtk_text_range__new(cause, f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&mstart)), f2__gtk_text_iter__new(cause, f2chunk__new(cause, sizeof(GtkTextIter), (u8*)&mend)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__text_iter__forward_search(f2ptr cause, f2ptr text_iter, f2ptr text) {
  assert_argument_type(gtk_text_iter, text_iter);
  assert_argument_type(string,        text);
  return raw__gtk__text_iter__forward_search(cause, text_iter, text);
}
export_cefunk2(gtk__text_iter__forward_search, text_iter, text, 0,
	       "Returns a range composed of two text_iters that represent the successful search forward from the text_iter for a string.  Returns nil on failure to find the text.");
//def_pcfunk2(gtk__text_iter__forward_search, text_iter, text,
//	    "Returns a range composed of two text_iters that represent the successful search forward from the text_iter for a string.  Returns nil on failure to find the text.",
//	    return f2__gtk__text_iter__forward_search(this_cause, text_iter, text));


// paned

f2ptr raw__gtk__paned__pack1(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, paned);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    GtkWidget* gtk_paned = raw__gtk_widget__as__GtkWidget(cause, paned);
    GtkWidget* gtk_child = raw__gtk_widget__as__GtkWidget(cause, child);
    
    assert_g_type(GTK_TYPE_PANED,  gtk_paned);
    assert_g_type(GTK_TYPE_WIDGET, gtk_child);
    
    funk2_gtk__paned__pack1(__funk2__gtk, gtk_paned, gtk_child, (resize != nil) ? TRUE : FALSE, (shrink != nil) ? TRUE : FALSE);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__paned__pack1(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
  assert_argument_type(gtk_widget, paned);
  assert_argument_type(gtk_widget, child);
  return raw__gtk__paned__pack1(cause, paned, child, resize, shrink);
}
export_cefunk4(gtk__paned__pack1, paned, child, resize, shrink, 0,
	       "Packs the first child of the Paned.");
//def_pcfunk4(gtk__paned__pack1, paned, child, resize, shrink,
//	    "Packs the first child of the Paned.",
//	    return f2__gtk__paned__pack1(this_cause, paned, child, resize, shrink));


f2ptr raw__gtk__paned__pack2(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, paned);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    GtkWidget* gtk_paned = raw__gtk_widget__as__GtkWidget(cause, paned);
    GtkWidget* gtk_child = raw__gtk_widget__as__GtkWidget(cause, child);
    
    assert_g_type(GTK_TYPE_PANED,  gtk_paned);
    assert_g_type(GTK_TYPE_WIDGET, gtk_child);
    
    funk2_gtk__paned__pack2(__funk2__gtk, gtk_paned, gtk_child, (resize != nil) ? TRUE : FALSE, (shrink != nil) ? TRUE : FALSE);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__paned__pack2(f2ptr cause, f2ptr paned, f2ptr child, f2ptr resize, f2ptr shrink) {
  assert_argument_type(gtk_widget, paned);
  assert_argument_type(gtk_widget, child);
  return raw__gtk__paned__pack2(cause, paned, child, resize, shrink);
}
export_cefunk4(gtk__paned__pack2, paned, child, resize, shrink, 0,
	       "Packs the second child of the Paned.");
//def_pcfunk4(gtk__paned__pack2, paned, child, resize, shrink,
//	    "Packs the second child of the Paned.",
//	    return f2__gtk__paned__pack2(this_cause, paned, child, resize, shrink));


//void funk2_gtk__paned__set_position(funk2_gtk_t* this, GtkWidget* paned, s64 position) {

f2ptr raw__gtk__paned__set_position(f2ptr cause, f2ptr paned, f2ptr position) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, paned);
    GtkWidget* gtk_paned   = raw__gtk_widget__as__GtkWidget(cause, paned);
    
    assert_g_type(GTK_TYPE_PANED, gtk_paned);
    
    s64        position__i = f2integer__i(position, cause);
    funk2_gtk__paned__set_position(__funk2__gtk, gtk_paned, position__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__paned__set_position(f2ptr cause, f2ptr paned, f2ptr position) {
  assert_argument_type(gtk_widget, paned);
  assert_argument_type(integer,    position);
  return raw__gtk__paned__set_position(cause, paned, position);
}
export_cefunk2(gtk__paned__set_position, paned, position, 0,
	       "Sets the pixel position of the Paned.");
//def_pcfunk2(gtk__paned__set_position, paned, position,
//	    "Sets the pixel position of the Paned.",
//	    return f2__gtk__paned__set_position(this_cause, paned, position));


// vpaned

f2ptr raw__gtk__vpaned__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* gtk_widget = funk2_gtk__vpaned__new(__funk2__gtk);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__vpaned__new(f2ptr cause) {
  return raw__gtk__vpaned__new(cause);
}
export_cefunk0(gtk__vpaned__new, 0,
	       "Returns a new GtkVPaned widget.");
//def_pcfunk0(gtk__vpaned__new,
//	    "Returns a new GtkVPaned widget.",
//	    return f2__gtk__vpaned__new(this_cause));


// hpaned

f2ptr raw__gtk__hpaned__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* gtk_widget = funk2_gtk__hpaned__new(__funk2__gtk);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__hpaned__new(f2ptr cause) {
  return raw__gtk__hpaned__new(cause);
}
export_cefunk0(gtk__hpaned__new, 0,
	       "Returns a new GtkHPaned widget.");
//def_pcfunk0(gtk__hpaned__new,
//	    "Returns a new GtkHPaned widget.",
//	    return f2__gtk__hpaned__new(this_cause));


// progress_bar

f2ptr raw__gtk__progress_bar__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkProgressBar* gtk_progress_bar = funk2_gtk__progress_bar__new(__funk2__gtk);
    return f2__gtk_progress_bar__new(cause, f2pointer__new(cause, to_ptr(gtk_progress_bar)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__new(f2ptr cause) {
  return raw__gtk__progress_bar__new(cause);
}
export_cefunk0(gtk__progress_bar__new, 0,
	       "Returns a new GtkProgressBar widget.");
//def_pcfunk0(gtk__progress_bar__new,
//	    "Returns a new GtkProgressBar widget.",
//	    return f2__gtk__progress_bar__new(this_cause));


f2ptr raw__gtk__progress_bar__set_fraction(f2ptr cause, f2ptr this, f2ptr fraction) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_progress_bar, this);
    GtkProgressBar* gtk_this = raw__gtk_progress_bar__as__GtkProgressBar(cause, this);
    
    assert_g_type(GTK_TYPE_PROGRESS_BAR, gtk_this);
    
    f2ptr fraction_double = f2__number__as__double(cause, fraction);
    if (! raw__double__is_type(cause, fraction_double)) {
      return f2larva__new(cause, 1, nil);
    }
    double fraction_double__d = f2double__d(fraction_double, cause);
    funk2_gtk__progress_bar__set_fraction(gtk_this, fraction_double__d);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__set_fraction(f2ptr cause, f2ptr this, f2ptr fraction) {
  assert_argument_type(gtk_progress_bar, this);
  return raw__gtk__progress_bar__set_fraction(cause, this, fraction);
}
export_cefunk2(gtk__progress_bar__set_fraction, this, fraction, 0,
	       "Sets the fraction done of the progress bar.");
//def_pcfunk2(gtk__progress_bar__set_fraction, this, fraction,
//	    "Sets the fraction done of the progress bar.",
//	    return f2__gtk__progress_bar__set_fraction(this_cause, this, fraction));


f2ptr raw__gtk__progress_bar__set_text(f2ptr cause, f2ptr this, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_progress_bar, this);
    GtkProgressBar* gtk_this = raw__gtk_progress_bar__as__GtkProgressBar(cause, this);
    
    assert_g_type(GTK_TYPE_PROGRESS_BAR, gtk_this);
    
    u64 text__utf8_length = raw__string__utf8_length(cause, text);
    u8* text__utf8_str    = (u8*)alloca(text__utf8_length + 1);
    raw__string__utf8_str_copy(cause, text, text__utf8_str);
    text__utf8_str[text__utf8_length] = 0;
    
    funk2_gtk__progress_bar__set_text(gtk_this, text__utf8_str);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__set_text(f2ptr cause, f2ptr this, f2ptr text) {
  assert_argument_type(gtk_progress_bar, this);
  assert_argument_type(string,           text);
  return raw__gtk__progress_bar__set_text(cause, this, text);
}
export_cefunk2(gtk__progress_bar__set_text, this, text, 0,
	       "Sets the text of the progress bar.");
//def_pcfunk2(gtk__progress_bar__set_text, this, text,
//	    "Sets the text of the progress bar.",
//	    return f2__gtk__progress_bar__set_text(this_cause, this, text));


f2ptr raw__gtk__progress_bar__set_orientation(f2ptr cause, f2ptr this, f2ptr orientation) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_progress_bar, this);
    GtkProgressBar* gtk_this = raw__gtk_progress_bar__as__GtkProgressBar(cause, this);
    
    assert_g_type(GTK_TYPE_PROGRESS_BAR, gtk_this);
    
    GtkProgressBarOrientation gtk_orientation;
    if      (raw__eq(cause, orientation, new__symbol(cause, "left_to_right"))) {gtk_orientation = GTK_PROGRESS_LEFT_TO_RIGHT;}
    else if (raw__eq(cause, orientation, new__symbol(cause, "right_to_left"))) {gtk_orientation = GTK_PROGRESS_RIGHT_TO_LEFT;}
    else if (raw__eq(cause, orientation, new__symbol(cause, "bottom_to_top"))) {gtk_orientation = GTK_PROGRESS_BOTTOM_TO_TOP;}
    else if (raw__eq(cause, orientation, new__symbol(cause, "top_to_bottom"))) {gtk_orientation = GTK_PROGRESS_TOP_TO_BOTTOM;}
    else {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "invalid_progress_bar_orientation_symbol"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "valid_orientation_symbols"), f2list4__new(cause, new__symbol(cause, "left_to_right"), new__symbol(cause, "right_to_left"), new__symbol(cause, "bottom_to_top"), new__symbol(cause, "top_to_bottom")));
      return f2larva__new(cause, 636, f2__bug__new(cause, f2integer__new(cause, 636), bug_frame));
    }
    
    funk2_gtk__progress_bar__set_orientation(gtk_this, gtk_orientation);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__set_orientation(f2ptr cause, f2ptr this, f2ptr orientation) {
  assert_argument_type(gtk_progress_bar, this);
  assert_argument_type(symbol,           orientation);
  return raw__gtk__progress_bar__set_orientation(cause, this, orientation);
}
export_cefunk2(gtk__progress_bar__set_orientation, this, orientation, 0,
	       "Sets the orientation of the progress bar to one of four possible symbolic values: left_to_right, right_to_left, top_to_bottom, or bottom_to_top.");
//def_pcfunk2(gtk__progress_bar__set_orientation, this, orientation,
//	    "Sets the orientation of the progress bar to one of four possible symbolic values: left_to_right, right_to_left, top_to_bottom, or bottom_to_top.",
//	    return f2__gtk__progress_bar__set_orientation(this_cause, this, orientation));


f2ptr raw__gtk__progress_bar__pulse(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_progress_bar, this);
    GtkProgressBar* gtk_this = raw__gtk_progress_bar__as__GtkProgressBar(cause, this);
    
    assert_g_type(GTK_TYPE_PROGRESS_BAR, gtk_this);
    
    funk2_gtk__progress_bar__pulse(gtk_this);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__pulse(f2ptr cause, f2ptr this) {
  assert_argument_type(gtk_progress_bar, this);
  return raw__gtk__progress_bar__pulse(cause, this);
}
export_cefunk1(gtk__progress_bar__pulse, this, 0,
	       "Pulses the progress bar to indicate that an unknown amount of progress has been made.");
//def_pcfunk1(gtk__progress_bar__pulse, this,
//	    "Pulses the progress bar to indicate that an unknown amount of progress has been made.",
//	    return f2__gtk__progress_bar__pulse(this_cause, this));


f2ptr raw__gtk__progress_bar__set_pulse_step(f2ptr cause, f2ptr this, f2ptr fraction) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_progress_bar, this);
    GtkProgressBar* gtk_this = raw__gtk_progress_bar__as__GtkProgressBar(cause, this);
    
    assert_g_type(GTK_TYPE_PROGRESS_BAR, gtk_this);
    
    f2ptr fraction_double = f2__number__as__double(cause, fraction);
    if (! raw__double__is_type(cause, fraction_double)) {
      return f2larva__new(cause, 1, nil);
    }
    double fraction_double__d = f2double__d(fraction_double, cause);
    funk2_gtk__progress_bar__set_pulse_step(gtk_this, fraction_double__d);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__progress_bar__set_pulse_step(f2ptr cause, f2ptr this, f2ptr fraction) {
  assert_argument_type(gtk_progress_bar, this);
  return raw__gtk__progress_bar__set_pulse_step(cause, this, fraction);
}
export_cefunk2(gtk__progress_bar__set_pulse_step, this, fraction, 0,
	       "Sets the pulse step of the progress bar.");
//def_pcfunk2(gtk__progress_bar__set_pulse_step, this, fraction,
//	    "Sets the pulse step of the progress bar.",
//	    return f2__gtk__progress_bar__set_pulse_step(this_cause, this, fraction));


// notebook

f2ptr raw__gtk__notebook__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* gtk_widget = funk2_gtk__notebook__new(__funk2__gtk);

    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_widget);

    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(gtk_widget)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__new(f2ptr cause) {
  return raw__gtk__notebook__new(cause);
}
export_cefunk0(gtk__notebook__new, 0,
	       "Returns a new GtkNotebook widget.");
//def_pcfunk0(gtk__notebook__new,
//	    "Returns a new GtkNotebook widget.",
//	    return f2__gtk__notebook__new(this_cause));


f2ptr raw__gtk__notebook__append_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, notebook);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    assert_gtk_object_is_from_this_session(gtk_widget, tab_label);
    GtkWidget* gtk_notebook  = raw__gtk_widget__as__GtkWidget(cause, notebook);
    GtkWidget* gtk_child     = raw__gtk_widget__as__GtkWidget(cause, child);
    GtkWidget* gtk_tab_label = raw__gtk_widget__as__GtkWidget(cause, tab_label);

    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_notebook);
    assert_g_type(GTK_TYPE_WIDGET,   gtk_child);
    assert_g_type(GTK_TYPE_WIDGET,   gtk_tab_label);
    
    s64 index = funk2_gtk__notebook__append_page(__funk2__gtk, gtk_notebook, gtk_child, gtk_tab_label);
    if (index == -1) {
      return nil;
    }
    return f2integer__new(cause, index);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__append_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
  assert_argument_type(gtk_widget, notebook);
  assert_argument_type(gtk_widget, child);
  assert_argument_type(gtk_widget, tab_label);
  return raw__gtk__notebook__append_page(cause, notebook, child, tab_label);
}
export_cefunk3(gtk__notebook__append_page, notebook, child, tab_label, 0,
	       "Adds a new GtkNotebookPage to the end of GtkNotebook.");
//def_pcfunk3(gtk__notebook__append_page, notebook, child, tab_label,
//	    "Adds a new GtkNotebookPage to the end of GtkNotebook.",
//	    return f2__gtk__notebook__append_page(this_cause, notebook, child, tab_label));


f2ptr raw__gtk__notebook__prepend_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, notebook);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    assert_gtk_object_is_from_this_session(gtk_widget, tab_label);
    GtkWidget* gtk_notebook  = raw__gtk_widget__as__GtkWidget(cause, notebook);
    GtkWidget* gtk_child     = raw__gtk_widget__as__GtkWidget(cause, child);
    GtkWidget* gtk_tab_label = raw__gtk_widget__as__GtkWidget(cause, tab_label);

    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_notebook);
    assert_g_type(GTK_TYPE_WIDGET,   gtk_child);
    assert_g_type(GTK_TYPE_WIDGET,   gtk_tab_label);

    s64 index = funk2_gtk__notebook__prepend_page(__funk2__gtk, gtk_notebook, gtk_child, gtk_tab_label);
    if (index == -1) {
      return nil;
    }
    return f2integer__new(cause, index);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__prepend_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label) {
  assert_argument_type(gtk_widget, notebook);
  assert_argument_type(gtk_widget, child);
  assert_argument_type(gtk_widget, tab_label);
  return raw__gtk__notebook__prepend_page(cause, notebook, child, tab_label);
}
export_cefunk3(gtk__notebook__prepend_page, notebook, child, tab_label, 0,
	       "Adds a new GtkNotebookPage to the beginning of a GtkNotebook.");
//def_pcfunk3(gtk__notebook__prepend_page, notebook, child, tab_label,
//	    "Adds a new GtkNotebookPage to the beginning of a GtkNotebook.",
//	    return f2__gtk__notebook__prepend_page(this_cause, notebook, child, tab_label));


f2ptr raw__gtk__notebook__insert_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label, f2ptr position) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, notebook);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    assert_gtk_object_is_from_this_session(gtk_widget, tab_label);
    GtkWidget* gtk_notebook  = raw__gtk_widget__as__GtkWidget(cause, notebook);
    GtkWidget* gtk_child     = raw__gtk_widget__as__GtkWidget(cause, child);
    GtkWidget* gtk_tab_label = raw__gtk_widget__as__GtkWidget(cause, tab_label);
    
    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_notebook);
    assert_g_type(GTK_TYPE_WIDGET,   gtk_child);
    assert_g_type(GTK_TYPE_WIDGET,   gtk_tab_label);
    
    s64        position__i   = f2integer__i(position, cause);
    s64 index = funk2_gtk__notebook__insert_page(__funk2__gtk, gtk_notebook, gtk_child, gtk_tab_label, position__i);
    if (index == -1) {
      return nil;
    }
    return f2integer__new(cause, index);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__insert_page(f2ptr cause, f2ptr notebook, f2ptr child, f2ptr tab_label, f2ptr position) {
  assert_argument_type(gtk_widget, notebook);
  assert_argument_type(gtk_widget, child);
  assert_argument_type(gtk_widget, tab_label);
  return raw__gtk__notebook__insert_page(cause, notebook, child, tab_label, position);
}
export_cefunk4(gtk__notebook__insert_page, notebook, child, tab_label, position, 0,
	       "Inserts a new GtkNotebookPage to a specific position within a GtkNotebook.");
//def_pcfunk4(gtk__notebook__insert_page, notebook, child, tab_label, position,
//	    "Inserts a new GtkNotebookPage to a specific position within a GtkNotebook.",
//	    return f2__gtk__notebook__insert_page(this_cause, notebook, child, tab_label, position));


f2ptr raw__gtk__notebook__remove_page(f2ptr cause, f2ptr notebook, f2ptr position) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, notebook);
    GtkWidget* gtk_notebook = raw__gtk_widget__as__GtkWidget(cause, notebook);

    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_notebook);
    
    s64        position__i  = f2integer__i(position, cause);
    funk2_gtk__notebook__remove_page(__funk2__gtk, gtk_notebook, position__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__remove_page(f2ptr cause, f2ptr notebook, f2ptr position) {
  assert_argument_type(gtk_widget, notebook);
  assert_argument_type(integer,    position);
  return raw__gtk__notebook__remove_page(cause, notebook, position);
}
export_cefunk2(gtk__notebook__remove_page, notebook, position, 0,
	       "Removes the GtkNotebookPage at a specific position within a GtkNotebook.");
//def_pcfunk2(gtk__notebook__remove_page, notebook, position,
//	    "Removes the GtkNotebookPage at a specific position within a GtkNotebook",
//	    return f2__gtk__notebook__remove_page(this_cause, notebook, position));


f2ptr raw__gtk__notebook__get_current_page(f2ptr cause, f2ptr notebook) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, notebook);
    GtkWidget* gtk_notebook = raw__gtk_widget__as__GtkWidget(cause, notebook);
    
    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_notebook);
    
    s64 index = funk2_gtk__notebook__get_current_page(__funk2__gtk, gtk_notebook);
    if (index == -1) {
      return nil;
    }
    return f2integer__new(cause, index);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__get_current_page(f2ptr cause, f2ptr notebook) {
  assert_argument_type(gtk_widget, notebook);
  return raw__gtk__notebook__get_current_page(cause, notebook);
}
export_cefunk1(gtk__notebook__get_current_page, notebook, 0,
	       "Returns the index of the current page in a GtkNotebook.");
//def_pcfunk1(gtk__notebook__get_current_page, notebook,
//	    "Returns the index of the current page in a GtkNotebook.",
//	    return f2__gtk__notebook__get_current_page(this_cause, notebook));


f2ptr raw__gtk__notebook__set_scrollable(f2ptr cause, f2ptr notebook, f2ptr scrollable) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, notebook);
    GtkWidget* gtk_notebook = raw__gtk_widget__as__GtkWidget(cause, notebook);
    
    assert_g_type(GTK_TYPE_NOTEBOOK, gtk_notebook);
    
    funk2_gtk__notebook__set_scrollable(__funk2__gtk, gtk_notebook, (scrollable != nil) ? TRUE : FALSE);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__notebook__set_scrollable(f2ptr cause, f2ptr notebook, f2ptr scrollable) {
  assert_argument_type(gtk_widget, notebook);
  return raw__gtk__notebook__set_scrollable(cause, notebook, scrollable);
}
export_cefunk2(gtk__notebook__set_scrollable, notebook, scrollable, 0,
	       "Sets a GtkNotebook to be either scollable (True) [t] or not scrollable (False) [nil].");
//def_pcfunk2(gtk__notebook__set_scrollable, notebook, scrollable,
//	    "Sets a GtkNotebook to be either scollable (True) [t] or not scrollable (False) [nil].",
//	    return f2__gtk__notebook__set_scrollable(this_cause, notebook, scrollable));


// label

f2ptr raw__gtk__label__new(f2ptr cause, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64 text__utf8_length = raw__string__utf8_length(cause, text);
    u8* text__utf8_str    = (u8*)alloca(text__utf8_length + 1);
    raw__string__utf8_str_copy(cause, text, text__utf8_str);
    text__utf8_str[text__utf8_length] = 0;
    
    GtkLabel* label = funk2_gtk__label__new(__funk2__gtk, text__utf8_str);
    return f2__gtk_label__new(cause, f2pointer__new(cause, to_ptr(label)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__label__new(f2ptr cause, f2ptr text) {
  assert_argument_type(string, text);
  return raw__gtk__label__new(cause, text);
}
export_cefunk1(gtk__label__new, text, 0,
	       "Returns a new GtkLabel.");
//def_pcfunk1(gtk__label__new, text,
//	    "Returns a new GtkLabel.",
//	    return f2__gtk__label__new(this_cause, text));


f2ptr raw__gtk__label__set_text(f2ptr cause, f2ptr label, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_label, label);
    GtkLabel* gtk_label = raw__gtk_label__as__GtkLabel(cause, label);
    
    assert_g_type(GTK_TYPE_LABEL, gtk_label);
    
    u64 text__utf8_length = raw__string__utf8_length(cause, text);
    u8* text__utf8_str    = (u8*)alloca(text__utf8_length + 1);
    raw__string__utf8_str_copy(cause, text, text__utf8_str);
    text__utf8_str[text__utf8_length] = 0;
    
    funk2_gtk__label__set_text(__funk2__gtk, gtk_label, text__utf8_str);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__label__set_text(f2ptr cause, f2ptr label, f2ptr text) {
  assert_argument_type(gtk_label, label);
  assert_argument_type(string,    text);
  return raw__gtk__label__set_text(cause, label, text);
}
export_cefunk2(gtk__label__set_text, label, text, 0,
	       "Sets the text displayed by a GtkLabel.");
//def_pcfunk2(gtk__label__set_text, label, text,
//	    "Sets the text displayed by a GtkLabel.",
//	    return f2__gtk__label__set_text(this_cause, label, text));


f2ptr raw__gtk__label__set_selectable(f2ptr cause, f2ptr label, f2ptr selectable) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_label, label);
    GtkLabel* gtk_label = raw__gtk_label__as__GtkLabel(cause, label);
    
    assert_g_type(GTK_TYPE_LABEL, gtk_label);
    
    funk2_gtk__label__set_selectable(__funk2__gtk, gtk_label, (selectable != nil));
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__label__set_selectable(f2ptr cause, f2ptr label, f2ptr selectable) {
  assert_argument_type(gtk_label, label);
  return raw__gtk__label__set_selectable(cause, label, selectable);
}
export_cefunk2(gtk__label__set_selectable, label, selectable, 0,
	       "Sets whether the text displayed by a GtkLabel is selectable for copy and paste.");
//def_pcfunk2(gtk__label__set_selectable, label, selectable,
//	    "Sets whether the text displayed by a GtkLabel is selectable for copy and paste.",
//	    return f2__gtk__label__set_selectable(this_cause, label, selectable));


boolean_t raw__gtk_orientation__is_type(f2ptr cause, f2ptr thing) {
  return (raw__symbol__is_type(cause, thing) &&
	  (raw__eq(cause, thing, new__symbol(cause, "horizontal")) ||
	   raw__eq(cause, thing, new__symbol(cause, "vertical"))));
}

#if defined(F2__GTK__SUPPORTED)

GtkOrientation raw__gtk_orientation__as__GtkOrientation(f2ptr cause, f2ptr this) {
  if (raw__eq(cause, this, new__symbol(cause, "horizontal"))) {
    return GTK_ORIENTATION_HORIZONTAL;
  }
  return GTK_ORIENTATION_VERTICAL;
}

#endif


// scale

f2ptr raw__gtk__scale__new_with_range(f2ptr cause, f2ptr orientation, f2ptr min, f2ptr max, f2ptr step) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkOrientation gtk_orientation = raw__gtk_orientation__as__GtkOrientation(cause, orientation);
    double         min__d          = f2double__d(min,  cause);
    double         max__d          = f2double__d(max,  cause);
    double         step__d         = f2double__d(step, cause);
    GtkScale*      scale;
    if (gtk_orientation == GTK_ORIENTATION_HORIZONTAL) {
      scale = funk2_gtk__hscale__new_with_range(__funk2__gtk, min__d, max__d, step__d);
    } else {
      scale = funk2_gtk__vscale__new_with_range(__funk2__gtk, min__d, max__d, step__d);
    }
    return f2__gtk_scale__new(cause, f2pointer__new(cause, to_ptr(scale)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scale__new_with_range(f2ptr cause, f2ptr orientation, f2ptr min, f2ptr max, f2ptr step) {
  assert_argument_type(gtk_orientation, orientation);
  assert_argument_type(double,          min);
  assert_argument_type(double,          max);
  assert_argument_type(double,          step);
  return raw__gtk__scale__new_with_range(cause, orientation, min, max, step);
}
export_cefunk4(gtk__scale__new_with_range, orientation, min, max, step, 0,
	       "Returns a new GtkScale.  orientation can be either `vertical or `horizontal.");
//def_pcfunk4(gtk__scale__new_with_range, orientation, min, max, step,
//	    "Returns a new GtkScale.  orientation can be either `vertical or `horizontal.",
//	    return f2__gtk__scale__new_with_range(this_cause, orientation, min, max, step));


f2ptr raw__gtk__scale__set_digits(f2ptr cause, f2ptr this, f2ptr digits) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_scale, this);
    GtkScale* gtk_scale = raw__gtk_scale__as__GtkScale(cause, this);
    
    assert_g_type(GTK_TYPE_SCALE, gtk_scale);
    
    s64       digits__i  = f2integer__i(digits, cause);
    if (digits__i < 0) {
      return f2larva__new(cause, 3, nil);
    }
    funk2_gtk__scale__set_digits(__funk2__gtk, gtk_scale, digits__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__scale__set_digits(f2ptr cause, f2ptr this, f2ptr digits) {
  assert_argument_type(gtk_scale, this);
  assert_argument_type(integer,   digits);
  return raw__gtk__scale__set_digits(cause, this, digits);
}
export_cefunk2(gtk__scale__set_digits, this, digits, 0,
	       "Sets the number of digits after the decimal point to show.");
//def_pcfunk2(gtk__scale__set_digits, this, digits,
//	    "Sets the number of digits after the decimal point to show.",
//	    return f2__gtk__scale__set_digits(this_cause, this, digits));


// range

boolean_t raw__gtk_range__is_type(f2ptr cause, f2ptr thing) {
  return raw__gtk_scale__is_type(cause, thing);
}

#if defined(F2__GTK__SUPPORTED)
GtkRange* raw__gtk_range__as__GtkRange(f2ptr cause, f2ptr this) {
  return (GtkRange*)raw__gtk_scale__as__GtkScale(cause, this);
}

boolean_t raw__gtk_range__is_from_this_session(f2ptr cause, f2ptr this) {
  return raw__gtk_scale__is_from_this_session(cause, this);
}

#endif

f2ptr raw__gtk__range__get_value(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_range, this);
    GtkRange* gtk_range = raw__gtk_range__as__GtkRange(cause, this);
    
    assert_g_type(GTK_TYPE_RANGE, gtk_range);
    
    return f2double__new(cause, funk2_gtk__range__get_value(__funk2__gtk, gtk_range));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__range__get_value(f2ptr cause, f2ptr this) {
  assert_argument_type(gtk_range, this);
  return raw__gtk__range__get_value(cause, this);
}
export_cefunk1(gtk__range__get_value, this, 0,
	       "Returns the current value of the GtkRange object.");
//def_pcfunk1(gtk__range__get_value, this,
//	    "Returns the current value of the GtkRange object.",
//	    return f2__gtk__range__get_value(this_cause, this));


f2ptr raw__gtk__range__set_value(f2ptr cause, f2ptr this, f2ptr value) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_range, this);
    GtkRange* gtk_range = raw__gtk_range__as__GtkRange(cause, this);
    
    assert_g_type(GTK_TYPE_RANGE, gtk_range);
    
    double    value__d  = f2double__d(value, cause);
    funk2_gtk__range__set_value(__funk2__gtk, gtk_range, value__d);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__range__set_value(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(gtk_range, this);
  assert_argument_type(double,    value);
  return raw__gtk__range__set_value(cause, this, value);
}
export_cefunk2(gtk__range__set_value, this, value, 0,
	       "Sets the current value of the GtkRange object.");
//def_pcfunk2(gtk__range__set_value, this, value,
//	    "Sets the current value of the GtkRange object.",
//	    return f2__gtk__range__set_value(this_cause, this, value));


f2ptr raw__gtk__range__set_range(f2ptr cause, f2ptr this, f2ptr min, f2ptr max) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_range, this);
    GtkRange* gtk_range = raw__gtk_range__as__GtkRange(cause, this);
    
    assert_g_type(GTK_TYPE_RANGE, gtk_range);
    
    double    min__d    = f2double__d(min, cause);
    double    max__d    = f2double__d(max, cause);
    funk2_gtk__range__set_range(__funk2__gtk, gtk_range, min__d, max__d);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__range__set_range(f2ptr cause, f2ptr this, f2ptr min, f2ptr max) {
  assert_argument_type(gtk_range, this);
  assert_argument_type(double,    min);
  assert_argument_type(double,    max);
  return raw__gtk__range__set_range(cause, this, min, max);
}
export_cefunk3(gtk__range__set_range, this, min, max, 0,
	       "Sets the range of the GtkRange object.");
//def_pcfunk3(gtk__range__set_range, this, min, max,
//	    "Sets the range of the GtkRange object.",
//	    return f2__gtk__range__set_range(this_cause, this, min, max));


f2ptr raw__gtk__range__set_increments(f2ptr cause, f2ptr this, f2ptr step, f2ptr page) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_range, this);
    GtkRange* gtk_range = raw__gtk_range__as__GtkRange(cause, this);
    
    assert_g_type(GTK_TYPE_RANGE, gtk_range);
    
    double    step__d   = f2double__d(step, cause);
    double    page__d   = f2double__d(page, cause);
    funk2_gtk__range__set_increments(__funk2__gtk, gtk_range, step__d, page__d);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__range__set_increments(f2ptr cause, f2ptr this, f2ptr step, f2ptr page) {
  assert_argument_type(gtk_range, this);
  assert_argument_type(double,    step);
  assert_argument_type(double,    page);
  return raw__gtk__range__set_increments(cause, this, step, page);
}
export_cefunk3(gtk__range__set_increments, this, step, page, 0,
	       "Sets the step and page increments for the GtkRange object.");
//def_pcfunk3(gtk__range__set_increments, this, step, page,
//	    "Sets the step and page increments for the GtkRange object.",
//	    return f2__gtk__range__set_increments(this_cause, this, step, page));


// entry

f2ptr raw__gtk__entry__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkEntry* entry = funk2_gtk__entry__new(__funk2__gtk);
    
    assert_g_type(GTK_TYPE_ENTRY, entry);
    
    return f2__gtk_entry__new(cause, f2pointer__new(cause, to_ptr(entry)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__entry__new(f2ptr cause) {
  return raw__gtk__entry__new(cause);
}
export_cefunk0(gtk__entry__new, 0,
	       "Returns a new entry widget.");
//def_pcfunk0(gtk__entry__new,
//	    "Returns a new entry widget.",
//	    return f2__gtk__entry__new(this_cause));


f2ptr raw__gtk__entry__get_text(f2ptr cause, f2ptr entry) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_entry, entry);
    GtkEntry* gtk_entry = raw__gtk_entry__as__GtkEntry(cause, entry);
    
    assert_g_type(GTK_TYPE_ENTRY, gtk_entry);
    
    char* text = funk2_gtk__entry__get_text(__funk2__gtk, gtk_entry);
    if (! text) {
      return nil;
    }
    return new__string(cause, text);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__entry__get_text(f2ptr cause, f2ptr entry) {
  assert_argument_type(gtk_entry, entry);
  return raw__gtk__entry__get_text(cause, entry);
}
export_cefunk1(gtk__entry__get_text, entry, 0,
	       "Returns the text of an entry widget as a string.");
//def_pcfunk1(gtk__entry__get_text, entry,
//	    "Returns the text of an entry widget as a string.",
//	    return f2__gtk__entry__get_text(this_cause, entry));


f2ptr raw__gtk__entry__set_text(f2ptr cause, f2ptr entry, f2ptr text) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_entry, entry);
    GtkEntry* gtk_entry = raw__gtk_entry__as__GtkEntry(cause, entry);
    
    assert_g_type(GTK_TYPE_ENTRY, gtk_entry);
    
    u64 text__utf8_length = raw__string__utf8_length(cause, text);
    u8* text__utf8_str    = (u8*)from_ptr(f2__malloc(text__utf8_length + 1));
    raw__string__utf8_str_copy(cause, text, text__utf8_str);
    text__utf8_str[text__utf8_length] = 0;
    funk2_gtk__entry__set_text(__funk2__gtk, gtk_entry, text__utf8_str);
    f2__free(to_ptr(text__utf8_str));
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__entry__set_text(f2ptr cause, f2ptr entry, f2ptr text) {
  assert_argument_type(gtk_entry, entry);
  assert_argument_type(string,    text);
  return raw__gtk__entry__set_text(cause, entry, text);
}
export_cefunk2(gtk__entry__set_text, entry, text, 0,
	       "Sets the text of an entry widget to the given string.");
//def_pcfunk2(gtk__entry__set_text, entry, text,
//	    "Sets the text of an entry widget to the given string.",
//	    return f2__gtk__entry__set_text(this_cause, entry, text));


// image

f2ptr raw__gtk__image__new_from_pixbuf(f2ptr cause, f2ptr pixbuf) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gdk_pixbuf, pixbuf);
    GdkPixbuf* gdk_pixbuf = raw__gdk_pixbuf__as__GdkPixbuf(cause, pixbuf);
    
    assert_g_type(GDK_TYPE_PIXBUF, gdk_pixbuf);
    
    GtkImage*  image      = funk2_gtk__image__new_from_pixbuf(__funk2__gtk, gdk_pixbuf);
    return f2__gtk_image__new(cause, f2pointer__new(cause, to_ptr(image)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__image__new_from_pixbuf(f2ptr cause, f2ptr pixbuf) {
  assert_argument_type(gdk_pixbuf, pixbuf);
  return raw__gtk__image__new_from_pixbuf(cause, pixbuf);
}
export_cefunk1(gtk__image__new_from_pixbuf, pixbuf, 0,
	       "Returns a new image widget for displaying the given pixbuf.");
//def_pcfunk1(gtk__image__new_from_pixbuf, pixbuf,
//	    "Returns a new image widget for displaying the given pixbuf.",
//	    return f2__gtk__image__new_from_pixbuf(this_cause, pixbuf));


f2ptr raw__gtk__image__set_from_pixbuf(f2ptr cause, f2ptr image, f2ptr pixbuf) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_image,  image);
    assert_gtk_object_is_from_this_session(gdk_pixbuf, pixbuf);
    GtkImage*  gdk_image  = raw__gtk_image__as__GtkImage(  cause, image);
    GdkPixbuf* gdk_pixbuf = raw__gdk_pixbuf__as__GdkPixbuf(cause, pixbuf);
    
    assert_g_type(GTK_TYPE_IMAGE,  gdk_image);
    assert_g_type(GDK_TYPE_PIXBUF, gdk_pixbuf);
    
    funk2_gtk__image__set_from_pixbuf(__funk2__gtk, gdk_image, gdk_pixbuf);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__image__set_from_pixbuf(f2ptr cause, f2ptr image, f2ptr pixbuf) {
  assert_argument_type(gtk_image,  image);
  assert_argument_type(gdk_pixbuf, pixbuf);
  return raw__gtk__image__set_from_pixbuf(cause, image, pixbuf);
}
export_cefunk2(gtk__image__set_from_pixbuf, image, pixbuf, 0,
	       "Sets the pixbuf of the image.");
//def_pcfunk2(gtk__image__set_from_pixbuf, image, pixbuf,
//	    "Sets the pixbuf of the image.",
//	    return f2__gtk__image__set_from_pixbuf(this_cause, image, pixbuf));


// drawing_area

f2ptr raw__gtk__drawing_area__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* drawing_area = funk2_gtk__drawing_area__new(__funk2__gtk);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(drawing_area)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__drawing_area__new(f2ptr cause) {
  return raw__gtk__drawing_area__new(cause);
}
export_cefunk0(gtk__drawing_area__new, 0,
	       "Returns a new GtkDrawingArea.");
//def_pcfunk0(gtk__drawing_area__new,
//	    "Returns a new GtkDrawingArea.",
//	    return f2__gtk__drawing_area__new(this_cause));


// table

f2ptr raw__gtk__table__new(f2ptr cause, f2ptr rows, f2ptr columns, f2ptr homogenous) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    s64        rows__i    = f2integer__i(rows,    cause);
    s64        columns__i = f2integer__i(columns, cause);
    GtkWidget* table      = funk2_gtk__table__new(__funk2__gtk, rows__i, columns__i, (homogenous != nil) ? TRUE : FALSE);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(table)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__table__new(f2ptr cause, f2ptr rows, f2ptr columns, f2ptr homogenous) {
  assert_argument_type(integer, rows);
  assert_argument_type(integer, columns);
  return raw__gtk__table__new(cause, rows, columns, homogenous);
}
export_cefunk3(gtk__table__new, rows, columns, homogenous, 0,
	       "Returns a new GtkTable.");
//def_pcfunk3(gtk__table__new, rows, columns, homogenous,
//	    "Returns a new GtkTable.",
//	    return f2__gtk__table__new(this_cause, rows, columns, homogenous));


f2ptr raw__gtk__table__attach(f2ptr cause, f2ptr table, f2ptr child, f2ptr left_attach, f2ptr right_attach, f2ptr top_attach, f2ptr bottom_attach, f2ptr xpadding, f2ptr ypadding) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, table);
    assert_gtk_object_is_from_this_session(gtk_widget, child);
    GtkWidget* gtk_table        = raw__gtk_widget__as__GtkWidget(cause, table);
    GtkWidget* gtk_child        = raw__gtk_widget__as__GtkWidget(cause, child);

    assert_g_type(GTK_TYPE_TABLE,  gtk_table);
    assert_g_type(GTK_TYPE_WIDGET, gtk_child);

    s64        left_attach__i   = f2integer__i(left_attach, cause);
    s64        right_attach__i  = f2integer__i(right_attach, cause);
    s64        top_attach__i    = f2integer__i(top_attach, cause);
    s64        bottom_attach__i = f2integer__i(bottom_attach, cause);
    s64        xpadding__i      = f2integer__i(xpadding, cause);
    s64        ypadding__i      = f2integer__i(ypadding, cause);
    funk2_gtk__table__attach(__funk2__gtk, gtk_table, gtk_child, left_attach__i, right_attach__i, top_attach__i, bottom_attach__i, xpadding__i, ypadding__i);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__table__attach(f2ptr cause, f2ptr table, f2ptr child, f2ptr left_attach, f2ptr right_attach, f2ptr top_attach, f2ptr bottom_attach, f2ptr xpadding, f2ptr ypadding) {
  assert_argument_type(gtk_widget, table);
  assert_argument_type(gtk_widget, child);
  assert_argument_type(integer,    left_attach);
  assert_argument_type(integer,    right_attach);
  assert_argument_type(integer,    top_attach);
  assert_argument_type(integer,    bottom_attach);
  assert_argument_type(integer,    xpadding);
  assert_argument_type(integer,    ypadding);
  return raw__gtk__table__attach(cause, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding);
}
export_cefunk8(gtk__table__attach, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding, 0,
	       "Adds a child GtkWidget to the GtkTable.");
//def_pcfunk8(gtk__table__attach, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding,
//	    "Adds a child GtkWidget to the GtkTable.",
//	    return f2__gtk__table__attach(this_cause, table, child, left_attach, right_attach, top_attach, bottom_attach, xpadding, ypadding));


// frame

f2ptr raw__gtk__frame__new(f2ptr cause, f2ptr label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64 label__utf8_length;
    u8* label__utf8_str;
    if (label) {
      label__utf8_length = raw__string__utf8_length(cause, label);
      label__utf8_str    = (u8*)alloca(label__utf8_length + 1);
      raw__string__utf8_str_copy(cause, label, label__utf8_str);
      label__utf8_str[label__utf8_length] = 0;
    } else {
      label__utf8_length = 0;
      label__utf8_str    = NULL;
    }
    
    GtkWidget* frame = funk2_gtk__frame__new(__funk2__gtk, label__utf8_str);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(frame)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__frame__new(f2ptr cause, f2ptr label) {
  assert_argument_type_or_nil(string, label);
  return raw__gtk__frame__new(cause, label);
}
export_cefunk1(gtk__frame__new, label, 0,
	       "Returns a new GtkFrame with optional label.");
//def_pcfunk1(gtk__frame__new, label,
//	    "Returns a new GtkFrame with optional label.",
//	    return f2__gtk__frame__new(this_cause, label));


// menu_bar

f2ptr raw__gtk__menu_bar__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkMenuBar* menu_bar = funk2_gtk__menu_bar__new(__funk2__gtk);
    return f2__gtk_menu_bar__new(cause, f2pointer__new(cause, to_ptr(menu_bar)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__menu_bar__new(f2ptr cause) {
  return raw__gtk__menu_bar__new(cause);
}
export_cefunk0(gtk__menu_bar__new, 0,
	       "Returns a new GtkMenuBar.");
//def_pcfunk0(gtk__menu_bar__new,
//	    "Returns a new GtkMenuBar.",
//	    return f2__gtk__menu_bar__new(this_cause));


f2ptr raw__gtk__menu_bar__append(f2ptr cause, f2ptr menu_bar, f2ptr append_widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_menu_bar, menu_bar);
    assert_gtk_object_is_from_this_session(gtk_widget,   append_widget);
    GtkMenuBar* gtk_menu_bar      = raw__gtk_menu_bar__as__GtkMenuBar(cause, menu_bar);
    GtkWidget*  append_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, append_widget);

    assert_g_type(GTK_TYPE_MENU_BAR, gtk_menu_bar);
    assert_g_type(GTK_TYPE_WIDGET,   append_gtk_widget);

    funk2_gtk__menu_bar__append(__funk2__gtk, gtk_menu_bar, append_gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__menu_bar__append(f2ptr cause, f2ptr menu_bar, f2ptr append_widget) {
  assert_argument_type(gtk_menu_bar, menu_bar);
  assert_argument_type(gtk_widget,   append_widget);
  return raw__gtk__menu_bar__append(cause, menu_bar, append_widget);
}
export_cefunk2(gtk__menu_bar__append, menu_bar, append_widget, 0,
	       "Appends a widget to a menu_bar.");
//def_pcfunk2(gtk__menu_bar__append, menu_bar, append_widget,
//	    "Appends a widget to a menu_bar.",
//	    return f2__gtk__menu_bar__append(this_cause, menu_bar, append_widget));


// menu_item

f2ptr raw__gtk__menu_item__new(f2ptr cause, f2ptr label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64 label__utf8_length;
    u8* label__utf8_str;
    label__utf8_length = raw__string__utf8_length(cause, label);
    label__utf8_str    = (u8*)alloca(label__utf8_length + 1);
    raw__string__utf8_str_copy(cause, label, label__utf8_str);
    label__utf8_str[label__utf8_length] = 0;
    
    GtkWidget* menu_item = funk2_gtk__menu_item__new(__funk2__gtk, label__utf8_str);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(menu_item)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__menu_item__new(f2ptr cause, f2ptr label) {
  assert_argument_type(string, label);
  return raw__gtk__menu_item__new(cause, label);
}
export_cefunk1(gtk__menu_item__new, label, 0,
	       "Returns a new GtkMenuItem with label.");
//def_pcfunk1(gtk__menu_item__new, label,
//	    "Returns a new GtkMenuItem with label.",
//	    return f2__gtk__menu_item__new(this_cause, label));


f2ptr raw__gtk__menu_item__set_submenu(f2ptr cause, f2ptr widget, f2ptr submenu) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    assert_gtk_object_is_from_this_session(gtk_widget, submenu);
    GtkWidget* gtk_widget         = raw__gtk_widget__as__GtkWidget(cause, widget);
    GtkWidget* submenu_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, submenu);

    assert_g_type(GTK_TYPE_MENU_ITEM, gtk_widget);
    assert_g_type(GTK_TYPE_WIDGET,    submenu_gtk_widget);
    
    funk2_gtk__menu_item__set_submenu(__funk2__gtk, gtk_widget, submenu_gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__menu_item__set_submenu(f2ptr cause, f2ptr widget, f2ptr submenu) {
  assert_argument_type(gtk_widget, widget);
  assert_argument_type(gtk_widget, submenu);
  return raw__gtk__menu_item__set_submenu(cause, widget, submenu);
}
export_cefunk2(gtk__menu_item__set_submenu, widget, submenu, 0,
	       "Sets the submenu for a menu_item.");
//def_pcfunk2(gtk__menu_item__set_submenu, widget, submenu,
//	    "Sets the submenu for a menu_item.",
//	    return f2__gtk__menu_item__set_submenu(this_cause, widget, submenu));


// check_menu_item

f2ptr raw__gtk__check_menu_item__new(f2ptr cause, f2ptr label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64 label__utf8_length;
    u8* label__utf8_str;
    label__utf8_length = raw__string__utf8_length(cause, label);
    label__utf8_str    = (u8*)alloca(label__utf8_length + 1);
    raw__string__utf8_str_copy(cause, label, label__utf8_str);
    label__utf8_str[label__utf8_length] = 0;
    
    GtkWidget* check_menu_item = funk2_gtk__check_menu_item__new(__funk2__gtk, label__utf8_str);
    return f2__gtk_widget__new(cause, f2pointer__new(cause, to_ptr(check_menu_item)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__check_menu_item__new(f2ptr cause, f2ptr label) {
  assert_argument_type(string, label);
  return raw__gtk__check_menu_item__new(cause, label);
}
export_cefunk1(gtk__check_menu_item__new, label, 0,
	       "Returns a new GtkCheckMenuItem with label.");
//def_pcfunk1(gtk__check_menu_item__new, label,
//	    "Returns a new GtkCheckMenuItem with label.",
//	    return f2__gtk__check_menu_item__new(this_cause, label));


f2ptr raw__gtk__check_menu_item__get_active(f2ptr cause, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_CHECK_MENU_ITEM, gtk_widget);
    
    return f2bool__new(funk2_gtk__check_menu_item__get_active(__funk2__gtk, gtk_widget));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__check_menu_item__get_active(f2ptr cause, f2ptr widget) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__check_menu_item__get_active(cause, widget);
}
export_cefunk1(gtk__check_menu_item__get_active, widget, 0,
	       "Returns true if this check_menu_item's check box is checked, false otherwise.");
//def_pcfunk1(gtk__check_menu_item__get_active, widget, 
//	    "Returns true if this check_menu_item's check box is checked, false otherwise.",
//	    return f2__gtk__check_menu_item__get_active(this_cause, widget));


f2ptr raw__gtk__check_menu_item__set_active(f2ptr cause, f2ptr widget, f2ptr active) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_widget, widget);
    GtkWidget* gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_CHECK_MENU_ITEM, gtk_widget);
    
    funk2_gtk__check_menu_item__set_active(__funk2__gtk, gtk_widget, (active != nil) ? boolean__true : boolean__false);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__check_menu_item__set_active(f2ptr cause, f2ptr widget, f2ptr active) {
  assert_argument_type(gtk_widget, widget);
  return raw__gtk__check_menu_item__set_active(cause, widget, active);
}
export_cefunk2(gtk__check_menu_item__set_active, widget, active, 0,
	       "Sets this check_menu_item's check box as checked (active) depending on the given boolean active value.");
//def_pcfunk2(gtk__check_menu_item__set_active, widget, active,
//	    "Sets this check_menu_item's check box as checked (active) depending on the given boolean active value.",
//	    return f2__gtk__check_menu_item__set_active(this_cause, widget, active));


// menu

f2ptr raw__gtk__menu__new(f2ptr cause) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkMenu* menu = funk2_gtk__menu__new(__funk2__gtk);
    return f2__gtk_menu__new(cause, f2pointer__new(cause, to_ptr(menu)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__menu__new(f2ptr cause) {
  return raw__gtk__menu__new(cause);
}
export_cefunk0(gtk__menu__new, 0,
	       "Returns a new GtkMenu.");
//def_pcfunk0(gtk__menu__new,
//	    "Returns a new GtkMenu.",
//	    return f2__gtk__menu__new(this_cause));


f2ptr raw__gtk__menu__append(f2ptr cause, f2ptr menu, f2ptr append_widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_menu,   menu);
    assert_gtk_object_is_from_this_session(gtk_widget, append_widget);
    GtkMenu*   gtk_menu          = raw__gtk_menu__as__GtkMenu(cause, menu);
    GtkWidget* append_gtk_widget = raw__gtk_widget__as__GtkWidget(cause, append_widget);

    assert_g_type(GTK_TYPE_MENU,   gtk_menu);
    assert_g_type(GTK_TYPE_WIDGET, append_gtk_widget);

    funk2_gtk__menu__append(__funk2__gtk, gtk_menu, append_gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__menu__append(f2ptr cause, f2ptr menu, f2ptr append_widget) {
  assert_argument_type(gtk_menu,   menu);
  assert_argument_type(gtk_widget, append_widget);
  return raw__gtk__menu__append(cause, menu, append_widget);
}
export_cefunk2(gtk__menu__append, menu, append_widget, 0,
	       "Appends a widget to a menu.");
//def_pcfunk2(gtk__menu__append, menu, append_widget,
//	    "Appends a widget to a menu.",
//	    return f2__gtk__menu__append(this_cause, menu, append_widget));


// check_button

f2ptr raw__gtk__check_button__new(f2ptr cause, f2ptr label) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    u64 label__utf8_length = raw__string__utf8_length(cause, label);
    u8* label__utf8_str    = (u8*)from_ptr(f2__malloc(label__utf8_length + 1));
    raw__string__utf8_str_copy(cause, label, label__utf8_str);
    label__utf8_str[label__utf8_length] = 0;
    GtkCheckButton* check_button = funk2_gtk__check_button__new(__funk2__gtk, (char*)label__utf8_str);
    f2__free(to_ptr(label__utf8_str));
    return f2__gtk_check_button__new(cause, f2pointer__new(cause, to_ptr(check_button)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__check_button__new(f2ptr cause, f2ptr label) {
  assert_argument_type(string, label);
  return raw__gtk__check_button__new(cause, label);
}
export_cefunk1(gtk__check_button__new, label, 0,
	       "Returns a new GtkCheckButton with the given label.");
//def_pcfunk1(gtk__check_button__new, label,
//	    "Returns a new GtkCheckButton with the given label.",
//	    return f2__gtk__check_button__new(this_cause, label));


f2ptr raw__gtk__check_button__get_active(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_check_button, this);
    GtkCheckButton* gtk_check_button = raw__gtk_check_button__as__GtkCheckButton(cause, this);
    
    assert_g_type(GTK_TYPE_CHECK_BUTTON, gtk_check_button);
    
    return f2bool__new(funk2_gtk__check_button__get_active(__funk2__gtk, gtk_check_button));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__check_button__get_active(f2ptr cause, f2ptr this) {
  assert_argument_type(gtk_check_button, this);
  return raw__gtk__check_button__get_active(cause, this);
}
export_cefunk1(gtk__check_button__get_active, this, 0,
	       "Returns true if this check_button's check box is checked, false otherwise.");
//def_pcfunk1(gtk__check_button__get_active, this, 
//	    "Returns true if this check_button's check box is checked, false otherwise.",
//	    return f2__gtk__check_button__get_active(this_cause, this));


f2ptr raw__gtk__check_button__set_active(f2ptr cause, f2ptr this, f2ptr active) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_check_button, this);
    GtkCheckButton* gtk_check_button = raw__gtk_check_button__as__GtkCheckButton(cause, this);
    
    assert_g_type(GTK_TYPE_CHECK_BUTTON, gtk_check_button);
    
    funk2_gtk__check_button__set_active(__funk2__gtk, gtk_check_button, (active != nil) ? boolean__true : boolean__false);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__check_button__set_active(f2ptr cause, f2ptr this, f2ptr active) {
  assert_argument_type(gtk_check_button, this);
  return raw__gtk__check_button__set_active(cause, this, active);
}
export_cefunk2(gtk__check_button__set_active, this, active, 0,
	       "Sets this check_button's check box as checked (active) depending on the given boolean active value.");
//def_pcfunk2(gtk__check_button__set_active, this, active,
//	    "Sets this check_button's check box as checked (active) depending on the given boolean active value.",
//	    return f2__gtk__check_button__set_active(this_cause, this, active));


// file_chooser_dialog

f2ptr raw__gtk__file_chooser_dialog__new_for_file_open(f2ptr cause, f2ptr parent_window) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* gtk_parent_window;
    if (parent_window == nil) {
      gtk_parent_window = NULL;
    } else {
      assert_gtk_object_is_from_this_session(gtk_widget, parent_window);
      gtk_parent_window = raw__gtk_widget__as__GtkWidget(cause, parent_window);
    }
    GtkFileChooserDialog* file_chooser_dialog = funk2_gtk__file_chooser_dialog__new_for_file_open(__funk2__gtk, gtk_parent_window);
    return f2__gtk_file_chooser_dialog__new(cause, f2pointer__new(cause, to_ptr(file_chooser_dialog)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__new_for_file_open(f2ptr cause, f2ptr parent_window) {
  assert_argument_type_or_nil(gtk_widget, parent_window);
  return raw__gtk__file_chooser_dialog__new_for_file_open(cause, parent_window);
}
export_cefunk1(gtk__file_chooser_dialog__new_for_file_open, parent_window, 0,
	       "Given a parent_window, which can be nil, returns a new GtkFileChooserDialog for opening a file.");
//def_pcfunk1(gtk__file_chooser_dialog__new_for_file_open, parent_window,
//	    "Given a parent_window, which can be nil, returns a new GtkFileChooserDialog for opening a file.",
//	    return f2__gtk__file_chooser_dialog__new_for_file_open(this_cause, parent_window));


f2ptr raw__gtk__file_chooser_dialog__new_for_folder_select(f2ptr cause, f2ptr parent_window) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* gtk_parent_window;
    if (parent_window == nil) {
      gtk_parent_window = NULL;
    } else {
      assert_gtk_object_is_from_this_session(gtk_widget, parent_window);
      gtk_parent_window = raw__gtk_widget__as__GtkWidget(cause, parent_window);
    }
    GtkFileChooserDialog* file_chooser_dialog = funk2_gtk__file_chooser_dialog__new_for_folder_select(__funk2__gtk, gtk_parent_window);
    return f2__gtk_file_chooser_dialog__new(cause, f2pointer__new(cause, to_ptr(file_chooser_dialog)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__new_for_folder_select(f2ptr cause, f2ptr parent_window) {
  assert_argument_type_or_nil(gtk_widget, parent_window);
  return raw__gtk__file_chooser_dialog__new_for_folder_select(cause, parent_window);
}
export_cefunk1(gtk__file_chooser_dialog__new_for_folder_select, parent_window, 0,
	       "Given a parent_window, which can be nil, returns a new GtkFileChooserDialog for selecting a folder.");
//def_pcfunk1(gtk__file_chooser_dialog__new_for_folder_select, parent_window,
//	    "Given a parent_window, which can be nil, returns a new GtkFileChooserDialog for selecting a folder.",
//	    return f2__gtk__file_chooser_dialog__new_for_folder_select(this_cause, parent_window));


f2ptr raw__gtk__file_chooser_dialog__new_for_file_save(f2ptr cause, f2ptr parent_window) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    GtkWidget* gtk_parent_window;
    if (parent_window == nil) {
      gtk_parent_window = NULL;
    } else {
      assert_gtk_object_is_from_this_session(gtk_widget, parent_window);
      gtk_parent_window = raw__gtk_widget__as__GtkWidget(cause, parent_window);
    }
    GtkFileChooserDialog* file_chooser_dialog = funk2_gtk__file_chooser_dialog__new_for_file_save(__funk2__gtk, gtk_parent_window);
    return f2__gtk_file_chooser_dialog__new(cause, f2pointer__new(cause, to_ptr(file_chooser_dialog)));
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__new_for_file_save(f2ptr cause, f2ptr parent_window) {
  assert_argument_type_or_nil(gtk_widget, parent_window);
  return raw__gtk__file_chooser_dialog__new_for_file_save(cause, parent_window);
}
export_cefunk1(gtk__file_chooser_dialog__new_for_file_save, parent_window, 0,
	       "Given a parent_window, which can be nil, returns a new GtkFileChooserDialog for saving a file.");
//def_pcfunk1(gtk__file_chooser_dialog__new_for_file_save, parent_window,
//	    "Given a parent_window, which can be nil, returns a new GtkFileChooserDialog for saving a file.",
//	    return f2__gtk__file_chooser_dialog__new_for_file_save(this_cause, parent_window));


f2ptr raw__gtk__file_chooser_dialog__set_current_folder(f2ptr cause, f2ptr this, f2ptr filename) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    s64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    f2ptr success = f2bool__new(funk2_gtk__file_chooser_dialog__set_current_folder(__funk2__gtk, gtk_this, filename__utf8_str));
    f2__free(to_ptr(filename__utf8_str));
    return success;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__set_current_folder(f2ptr cause, f2ptr this, f2ptr filename) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  assert_argument_type(string,                  filename);
  return raw__gtk__file_chooser_dialog__set_current_folder(cause, this, filename);
}
export_cefunk2(gtk__file_chooser_dialog__set_current_folder, this, filename, 0,
	       "Given a filename string, sets this gtk_file_chooser_dialog's current folder.");
//def_pcfunk2(gtk__file_chooser_dialog__set_current_folder, this, filename,
//	    "Given a filename string, sets this gtk_file_chooser_dialog's current folder.",
//	    return f2__gtk__file_chooser_dialog__set_current_folder(this_cause, this, filename));


f2ptr raw__gtk__file_chooser_dialog__set_current_name(f2ptr cause, f2ptr this, f2ptr current_name) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    s64 current_name__utf8_length = raw__string__utf8_length(cause, current_name);
    u8* current_name__utf8_str    = (u8*)from_ptr(f2__malloc(current_name__utf8_length + 1));
    raw__string__utf8_str_copy(cause, current_name, current_name__utf8_str);
    current_name__utf8_str[current_name__utf8_length] = 0;
    funk2_gtk__file_chooser_dialog__set_current_name(__funk2__gtk, gtk_this, current_name__utf8_str);
    f2__free(to_ptr(current_name__utf8_str));
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__set_current_name(f2ptr cause, f2ptr this, f2ptr current_name) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  assert_argument_type(string,                  current_name);
  return raw__gtk__file_chooser_dialog__set_current_name(cause, this, current_name);
}
export_cefunk2(gtk__file_chooser_dialog__set_current_name, this, current_name, 0,
	       "Given a current_name string, sets this gtk_file_chooser_dialog's current name.");
//def_pcfunk2(gtk__file_chooser_dialog__set_current_name, this, current_name,
//	    "Given a current_name string, sets this gtk_file_chooser_dialog's current name.",
//	    return f2__gtk__file_chooser_dialog__set_current_name(this_cause, this, current_name));


f2ptr raw__gtk__file_chooser_dialog__set_filename(f2ptr cause, f2ptr this, f2ptr filename) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    s64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    f2ptr success = f2bool__new(funk2_gtk__file_chooser_dialog__set_filename(__funk2__gtk, gtk_this, filename__utf8_str));
    f2__free(to_ptr(filename__utf8_str));
    return success;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__set_filename(f2ptr cause, f2ptr this, f2ptr filename) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  assert_argument_type(string,                  filename);
  return raw__gtk__file_chooser_dialog__set_filename(cause, this, filename);
}
export_cefunk2(gtk__file_chooser_dialog__set_filename, this, filename, 0,
	       "Given a filename string, sets this gtk_file_chooser_dialog's filename.");
//def_pcfunk2(gtk__file_chooser_dialog__set_filename, this, filename,
//	    "Given a filename string, sets this gtk_file_chooser_dialog's filename.",
//	    return f2__gtk__file_chooser_dialog__set_filename(this_cause, this, filename));


f2ptr raw__gtk__file_chooser_dialog__get_filenames(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    return funk2_gtk__file_chooser_dialog__get_filenames(__funk2__gtk, cause, gtk_this);
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__get_filenames(f2ptr cause, f2ptr this) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  return raw__gtk__file_chooser_dialog__get_filenames(cause, this);
}
export_cefunk1(gtk__file_chooser_dialog__get_filenames, this, 0,
	       "Gets this gtk_file_chooser_dialog's currently selected filenames.");
//def_pcfunk1(gtk__file_chooser_dialog__get_filenames, this,
//	    "Gets this gtk_file_chooser_dialog's currently selected filenames.",
//	    return f2__gtk__file_chooser_dialog__get_filenames(this_cause, this));


f2ptr raw__gtk__file_chooser_dialog__set_select_multiple(f2ptr cause, f2ptr this, f2ptr select_multiple) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    funk2_gtk__file_chooser_dialog__set_select_multiple(__funk2__gtk, gtk_this, (select_multiple != nil) ? boolean__true : boolean__false);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__set_select_multiple(f2ptr cause, f2ptr this, f2ptr select_multiple) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  return raw__gtk__file_chooser_dialog__set_select_multiple(cause, this, select_multiple);
}
export_cefunk2(gtk__file_chooser_dialog__set_select_multiple, this, select_multiple, 0,
	       "Given a boolean value, sets whether this gtk_file_chooser_dialog allows the user to select multiple files or folders.");
//def_pcfunk2(gtk__file_chooser_dialog__set_select_multiple, this, select_multiple,
//	    "Given a boolean value, sets whether this gtk_file_chooser_dialog allows the user to select multiple files or folders.",
//	    return f2__gtk__file_chooser_dialog__set_select_multiple(this_cause, this, select_multiple));


f2ptr raw__gtk__file_chooser_dialog__add_file_filter_pattern(f2ptr cause, f2ptr this, f2ptr name, f2ptr pattern) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    s64 pattern__utf8_length = raw__string__utf8_length(cause, pattern);
    u8* pattern__utf8_str    = (u8*)from_ptr(f2__malloc(pattern__utf8_length + 1));
    raw__string__utf8_str_copy(cause, pattern, pattern__utf8_str);
    pattern__utf8_str[pattern__utf8_length] = 0;
    s64 name__utf8_length = raw__string__utf8_length(cause, name);
    u8* name__utf8_str    = (u8*)from_ptr(f2__malloc(name__utf8_length + 1));
    raw__string__utf8_str_copy(cause, name, name__utf8_str);
    name__utf8_str[name__utf8_length] = 0;
    funk2_gtk__file_chooser_dialog__add_file_filter_pattern(__funk2__gtk, gtk_this, name__utf8_str, pattern__utf8_str);
    f2__free(to_ptr(name__utf8_str));
    f2__free(to_ptr(pattern__utf8_str));
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__add_file_filter_pattern(f2ptr cause, f2ptr this, f2ptr name, f2ptr pattern) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  assert_argument_type(string,                  name);
  assert_argument_type(string,                  pattern);
  return raw__gtk__file_chooser_dialog__add_file_filter_pattern(cause, this, name, pattern);
}
export_cefunk3(gtk__file_chooser_dialog__add_file_filter_pattern, this, name, pattern, 0,
	       "Given a name string and a pattern string, adds the name and pattern as a gtk_file_filter to this gtk_file_chooser_dialog.");
//def_pcfunk3(gtk__file_chooser_dialog__add_file_filter_pattern, this, name, pattern,
//	    "Given a name string and a pattern string, adds the name and pattern as a gtk_file_filter to this gtk_file_chooser_dialog.",
//	    return f2__gtk__file_chooser_dialog__add_file_filter_pattern(this_cause, this, name, pattern));


f2ptr raw__gtk__file_chooser_dialog__set_preview_widget(f2ptr cause, f2ptr this, f2ptr widget) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    assert_gtk_object_is_from_this_session(gtk_widget,              widget);
    GtkFileChooserDialog* gtk_this   = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    GtkWidget*            gtk_widget = raw__gtk_widget__as__GtkWidget(cause, widget);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    assert_g_type(GTK_TYPE_WIDGET,              gtk_widget);
    
    funk2_gtk__file_chooser_dialog__set_preview_widget(__funk2__gtk, gtk_this, gtk_widget);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__set_preview_widget(f2ptr cause, f2ptr this, f2ptr widget) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  assert_argument_type(gtk_widget,              widget);
  return raw__gtk__file_chooser_dialog__set_preview_widget(cause, this, widget);
}
export_cefunk2(gtk__file_chooser_dialog__set_preview_widget, this, widget, 0,
	       "Given a gtk_widget, sets the preview widget of this gtk_file_chooser_dialog.");
//def_pcfunk2(gtk__file_chooser_dialog__set_preview_widget, this, widget,
//	    "Given a gtk_widget, sets the preview widget of this gtk_file_chooser_dialog.",
//	    return f2__gtk__file_chooser_dialog__set_preview_widget(this_cause, this, widget));


f2ptr raw__gtk__file_chooser_dialog__set_preview_widget_active(f2ptr cause, f2ptr this, f2ptr preview_widget_active) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    funk2_gtk__file_chooser_dialog__set_preview_widget_active(__funk2__gtk, gtk_this, (preview_widget_active != nil) ? boolean__true : boolean__false);
    return nil;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__set_preview_widget_active(f2ptr cause, f2ptr this, f2ptr preview_widget_active) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  return raw__gtk__file_chooser_dialog__set_preview_widget_active(cause, this, preview_widget_active);
}
export_cefunk2(gtk__file_chooser_dialog__set_preview_widget_active, this, preview_widget_active, 0,
	       "Given a boolean value, sets whether this gtk_file_chooser_dialog has an active preview widget.");
//def_pcfunk2(gtk__file_chooser_dialog__set_preview_widget_active, this, preview_widget_active,
//	    "Given a boolean value, sets whether this gtk_file_chooser_dialog has an active preview widget.",
//	    return f2__gtk__file_chooser_dialog__set_preview_widget_active(this_cause, this, preview_widget_active));


f2ptr raw__gtk__file_chooser_dialog__get_preview_filename(f2ptr cause, f2ptr this) {
#if defined(F2__GTK__SUPPORTED)
  if (&(__funk2__gtk->initialized_successfully)) {
    assert_gtk_object_is_from_this_session(gtk_file_chooser_dialog, this);
    GtkFileChooserDialog* gtk_this = raw__gtk_file_chooser_dialog__as__GtkFileChooserDialog(cause, this);
    
    assert_g_type(GTK_TYPE_FILE_CHOOSER_DIALOG, gtk_this);
    
    char* gtk_filename = funk2_gtk__file_chooser_dialog__get_preview_filename(__funk2__gtk, gtk_this);
    f2ptr filename;
    if (gtk_filename != NULL) {
      filename = new__string(cause, gtk_filename);
    } else {
      filename = nil;
    }
    g_free(gtk_filename);
    return filename;
  } else {
    return f2__gtk_not_supported_larva__new(cause);
  }
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__file_chooser_dialog__get_preview_filename(f2ptr cause, f2ptr this) {
  assert_argument_type(gtk_file_chooser_dialog, this);
  return raw__gtk__file_chooser_dialog__get_preview_filename(cause, this);
}
export_cefunk1(gtk__file_chooser_dialog__get_preview_filename, this, 0,
	       "Gets this gtk_file_chooser_dialog's preview filename, or nil if one is no file is currently selected.");
//def_pcfunk1(gtk__file_chooser_dialog__get_preview_filename, this,
//	    "Gets this gtk_file_chooser_dialog's preview filename, or nil if one is no file is currently selected.",
//	    return f2__gtk__file_chooser_dialog__get_preview_filename(this_cause, this));


// gdk_keyval

f2ptr raw__gtk__gdk_keyval_to_unicode(f2ptr cause, f2ptr keyval) {
#if defined(F2__GTK__SUPPORTED)
  u64   keyval__i  = f2integer__i(keyval, cause);
  f2ptr unicode__i = funk2_gtk__gdk_keyval_to_unicode(__funk2__gtk, keyval__i);
  return f2integer__new(cause, unicode__i);
#else
  return f2__gtk_not_supported_larva__new(cause);
#endif
}

f2ptr f2__gtk__gdk_keyval_to_unicode(f2ptr cause, f2ptr keyval) {
  assert_argument_type(integer, keyval);
  return raw__gtk__gdk_keyval_to_unicode(cause, keyval);
}
export_cefunk1(gtk__gdk_keyval_to_unicode, keyval, 0,
	       "converts a keyval integer to a unicode integer");
//def_pcfunk1(gtk__gdk_keyval_to_unicode, keyval,
//	    "converts a keyval integer to a unicode integer",
//	    return f2__gtk__gdk_keyval_to_unicode(this_cause, keyval));


f2ptr f2__gtk__responses_frame__new(f2ptr cause) {
  f2ptr responses_frame = f2__frame__new(cause, nil);
#if defined(F2__GTK__SUPPORTED)
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_NONE"),         f2integer__new(cause, GTK_RESPONSE_NONE));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_REJECT"),       f2integer__new(cause, GTK_RESPONSE_REJECT));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_ACCEPT"),       f2integer__new(cause, GTK_RESPONSE_ACCEPT));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_DELETE_EVENT"), f2integer__new(cause, GTK_RESPONSE_DELETE_EVENT));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_OK"),           f2integer__new(cause, GTK_RESPONSE_OK));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_CANCEL"),       f2integer__new(cause, GTK_RESPONSE_CANCEL));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_CLOSE"),        f2integer__new(cause, GTK_RESPONSE_CLOSE));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_YES"),          f2integer__new(cause, GTK_RESPONSE_YES));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_NO"),           f2integer__new(cause, GTK_RESPONSE_NO));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_APPLY"),        f2integer__new(cause, GTK_RESPONSE_APPLY));
  f2__frame__add_var_value(cause, responses_frame, new__symbol(cause, "GTK_RESPONSE_HELP"),         f2integer__new(cause, GTK_RESPONSE_HELP));
#endif
  return responses_frame;
}
export_cefunk0(gtk__responses_frame__new, 0,
	       "creates a new responses frame.");
//def_pcfunk0(gtk__responses_frame__new,
//	    "creates a new responses frame.",
//	    return f2__gtk__responses_frame__new(this_cause));

f2ptr f2__gtk__gdk_keysyms_frame__new(f2ptr cause) {
  f2ptr gdk_keysyms_frame = f2__frame__new(cause, nil);
#if defined(F2__GTK__SUPPORTED)
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_BackSpace"), f2integer__new(cause, GDK_BackSpace));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Tab"), f2integer__new(cause, GDK_Tab));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Linefeed"), f2integer__new(cause, GDK_Linefeed));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Clear"), f2integer__new(cause, GDK_Clear));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Return"), f2integer__new(cause, GDK_Return));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Pause"), f2integer__new(cause, GDK_Pause));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Scroll_Lock"), f2integer__new(cause, GDK_Scroll_Lock));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Sys_Req"), f2integer__new(cause, GDK_Sys_Req));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Escape"), f2integer__new(cause, GDK_Escape));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Delete"), f2integer__new(cause, GDK_Delete));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Multi_key"), f2integer__new(cause, GDK_Multi_key));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Codeinput"), f2integer__new(cause, GDK_Codeinput));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_SingleCandidate"), f2integer__new(cause, GDK_SingleCandidate));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_MultipleCandidate"), f2integer__new(cause, GDK_MultipleCandidate));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_PreviousCandidate"), f2integer__new(cause, GDK_PreviousCandidate));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Kanji"), f2integer__new(cause, GDK_Kanji));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Muhenkan"), f2integer__new(cause, GDK_Muhenkan));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Henkan_Mode"), f2integer__new(cause, GDK_Henkan_Mode));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Henkan"), f2integer__new(cause, GDK_Henkan));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Romaji"), f2integer__new(cause, GDK_Romaji));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Hiragana"), f2integer__new(cause, GDK_Hiragana));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Katakana"), f2integer__new(cause, GDK_Katakana));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Hiragana_Katakana"), f2integer__new(cause, GDK_Hiragana_Katakana));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Zenkaku"), f2integer__new(cause, GDK_Zenkaku));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Hankaku"), f2integer__new(cause, GDK_Hankaku));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Zenkaku_Hankaku"), f2integer__new(cause, GDK_Zenkaku_Hankaku));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Touroku"), f2integer__new(cause, GDK_Touroku));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Massyo"), f2integer__new(cause, GDK_Massyo));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Kana_Lock"), f2integer__new(cause, GDK_Kana_Lock));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Kana_Shift"), f2integer__new(cause, GDK_Kana_Shift));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Eisu_Shift"), f2integer__new(cause, GDK_Eisu_Shift));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Eisu_toggle"), f2integer__new(cause, GDK_Eisu_toggle));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Kanji_Bangou"), f2integer__new(cause, GDK_Kanji_Bangou));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Zen_Koho"), f2integer__new(cause, GDK_Zen_Koho));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Mae_Koho"), f2integer__new(cause, GDK_Mae_Koho));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Home"), f2integer__new(cause, GDK_Home));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Left"), f2integer__new(cause, GDK_Left));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Up"), f2integer__new(cause, GDK_Up));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Right"), f2integer__new(cause, GDK_Right));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Down"), f2integer__new(cause, GDK_Down));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Prior"), f2integer__new(cause, GDK_Prior));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Page_Up"), f2integer__new(cause, GDK_Page_Up));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Next"), f2integer__new(cause, GDK_Next));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Page_Down"), f2integer__new(cause, GDK_Page_Down));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_End"), f2integer__new(cause, GDK_End));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Begin"), f2integer__new(cause, GDK_Begin));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Select"), f2integer__new(cause, GDK_Select));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Print"), f2integer__new(cause, GDK_Print));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Execute"), f2integer__new(cause, GDK_Execute));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Insert"), f2integer__new(cause, GDK_Insert));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Undo"), f2integer__new(cause, GDK_Undo));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Redo"), f2integer__new(cause, GDK_Redo));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Menu"), f2integer__new(cause, GDK_Menu));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Find"), f2integer__new(cause, GDK_Find));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Cancel"), f2integer__new(cause, GDK_Cancel));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Help"), f2integer__new(cause, GDK_Help));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Break"), f2integer__new(cause, GDK_Break));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Mode_switch"), f2integer__new(cause, GDK_Mode_switch));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_script_switch"), f2integer__new(cause, GDK_script_switch));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Num_Lock"), f2integer__new(cause, GDK_Num_Lock));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Space"), f2integer__new(cause, GDK_KP_Space));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Tab"), f2integer__new(cause, GDK_KP_Tab));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Enter"), f2integer__new(cause, GDK_KP_Enter));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_F1"), f2integer__new(cause, GDK_KP_F1));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_F2"), f2integer__new(cause, GDK_KP_F2));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_F3"), f2integer__new(cause, GDK_KP_F3));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_F4"), f2integer__new(cause, GDK_KP_F4));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Home"), f2integer__new(cause, GDK_KP_Home));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Left"), f2integer__new(cause, GDK_KP_Left));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Up"), f2integer__new(cause, GDK_KP_Up));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Right"), f2integer__new(cause, GDK_KP_Right));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Down"), f2integer__new(cause, GDK_KP_Down));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Prior"), f2integer__new(cause, GDK_KP_Prior));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Page_Up"), f2integer__new(cause, GDK_KP_Page_Up));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Next"), f2integer__new(cause, GDK_KP_Next));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Page_Down"), f2integer__new(cause, GDK_KP_Page_Down));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_End"), f2integer__new(cause, GDK_KP_End));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Begin"), f2integer__new(cause, GDK_KP_Begin));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Insert"), f2integer__new(cause, GDK_KP_Insert));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Delete"), f2integer__new(cause, GDK_KP_Delete));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Equal"), f2integer__new(cause, GDK_KP_Equal));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Multiply"), f2integer__new(cause, GDK_KP_Multiply));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Add"), f2integer__new(cause, GDK_KP_Add));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Separator"), f2integer__new(cause, GDK_KP_Separator));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Subtract"), f2integer__new(cause, GDK_KP_Subtract));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Decimal"), f2integer__new(cause, GDK_KP_Decimal));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_Divide"), f2integer__new(cause, GDK_KP_Divide));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_0"), f2integer__new(cause, GDK_KP_0));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_1"), f2integer__new(cause, GDK_KP_1));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_2"), f2integer__new(cause, GDK_KP_2));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_3"), f2integer__new(cause, GDK_KP_3));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_4"), f2integer__new(cause, GDK_KP_4));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_5"), f2integer__new(cause, GDK_KP_5));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_6"), f2integer__new(cause, GDK_KP_6));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_7"), f2integer__new(cause, GDK_KP_7));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_8"), f2integer__new(cause, GDK_KP_8));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_KP_9"), f2integer__new(cause, GDK_KP_9));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F1"), f2integer__new(cause, GDK_F1));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F2"), f2integer__new(cause, GDK_F2));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F3"), f2integer__new(cause, GDK_F3));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F4"), f2integer__new(cause, GDK_F4));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F5"), f2integer__new(cause, GDK_F5));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F6"), f2integer__new(cause, GDK_F6));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F7"), f2integer__new(cause, GDK_F7));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F8"), f2integer__new(cause, GDK_F8));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F9"), f2integer__new(cause, GDK_F9));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F10"), f2integer__new(cause, GDK_F10));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F11"), f2integer__new(cause, GDK_F11));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Shift_L"), f2integer__new(cause, GDK_Shift_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Shift_R"), f2integer__new(cause, GDK_Shift_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Control_L"), f2integer__new(cause, GDK_Control_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Control_R"), f2integer__new(cause, GDK_Control_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Caps_Lock"), f2integer__new(cause, GDK_Caps_Lock));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Shift_Lock"), f2integer__new(cause, GDK_Shift_Lock));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Meta_L"), f2integer__new(cause, GDK_Meta_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Meta_R"), f2integer__new(cause, GDK_Meta_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Alt_L"), f2integer__new(cause, GDK_Alt_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Alt_R"), f2integer__new(cause, GDK_Alt_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Super_L"), f2integer__new(cause, GDK_Super_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Super_R"), f2integer__new(cause, GDK_Super_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Hyper_L"), f2integer__new(cause, GDK_Hyper_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Hyper_R"), f2integer__new(cause, GDK_Hyper_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_3270_PrintScreen"), f2integer__new(cause, GDK_3270_PrintScreen));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_3270_Enter"), f2integer__new(cause, GDK_3270_Enter));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_space"), f2integer__new(cause, GDK_space));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_exclam"), f2integer__new(cause, GDK_exclam));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_quotedbl"), f2integer__new(cause, GDK_quotedbl));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_numbersign"), f2integer__new(cause, GDK_numbersign));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_dollar"), f2integer__new(cause, GDK_dollar));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_percent"), f2integer__new(cause, GDK_percent));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_ampersand"), f2integer__new(cause, GDK_ampersand));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_apostrophe"), f2integer__new(cause, GDK_apostrophe));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_quoteright"), f2integer__new(cause, GDK_quoteright));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_parenleft"), f2integer__new(cause, GDK_parenleft));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_parenright"), f2integer__new(cause, GDK_parenright));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_asterisk"), f2integer__new(cause, GDK_asterisk));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_plus"), f2integer__new(cause, GDK_plus));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_comma"), f2integer__new(cause, GDK_comma));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_minus"), f2integer__new(cause, GDK_minus));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_period"), f2integer__new(cause, GDK_period));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_slash"), f2integer__new(cause, GDK_slash));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_0"), f2integer__new(cause, GDK_0));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_1"), f2integer__new(cause, GDK_1));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_2"), f2integer__new(cause, GDK_2));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_3"), f2integer__new(cause, GDK_3));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_4"), f2integer__new(cause, GDK_4));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_5"), f2integer__new(cause, GDK_5));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_6"), f2integer__new(cause, GDK_6));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_7"), f2integer__new(cause, GDK_7));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_8"), f2integer__new(cause, GDK_8));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_9"), f2integer__new(cause, GDK_9));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_colon"), f2integer__new(cause, GDK_colon));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_semicolon"), f2integer__new(cause, GDK_semicolon));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_less"), f2integer__new(cause, GDK_less));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_equal"), f2integer__new(cause, GDK_equal));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_greater"), f2integer__new(cause, GDK_greater));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_question"), f2integer__new(cause, GDK_question));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_at"), f2integer__new(cause, GDK_at));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_A"), f2integer__new(cause, GDK_A));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_B"), f2integer__new(cause, GDK_B));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_C"), f2integer__new(cause, GDK_C));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_D"), f2integer__new(cause, GDK_D));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_E"), f2integer__new(cause, GDK_E));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_F"), f2integer__new(cause, GDK_F));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_G"), f2integer__new(cause, GDK_G));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_H"), f2integer__new(cause, GDK_H));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_I"), f2integer__new(cause, GDK_I));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_J"), f2integer__new(cause, GDK_J));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_K"), f2integer__new(cause, GDK_K));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_L"), f2integer__new(cause, GDK_L));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_M"), f2integer__new(cause, GDK_M));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_N"), f2integer__new(cause, GDK_N));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_O"), f2integer__new(cause, GDK_O));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_P"), f2integer__new(cause, GDK_P));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Q"), f2integer__new(cause, GDK_Q));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_R"), f2integer__new(cause, GDK_R));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_S"), f2integer__new(cause, GDK_S));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_T"), f2integer__new(cause, GDK_T));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_U"), f2integer__new(cause, GDK_U));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_V"), f2integer__new(cause, GDK_V));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_W"), f2integer__new(cause, GDK_W));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_X"), f2integer__new(cause, GDK_X));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Y"), f2integer__new(cause, GDK_Y));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_Z"), f2integer__new(cause, GDK_Z));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_bracketleft"), f2integer__new(cause, GDK_bracketleft));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_backslash"), f2integer__new(cause, GDK_backslash));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_bracketright"), f2integer__new(cause, GDK_bracketright));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_asciicircum"), f2integer__new(cause, GDK_asciicircum));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_underscore"), f2integer__new(cause, GDK_underscore));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_grave"), f2integer__new(cause, GDK_grave));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_quoteleft"), f2integer__new(cause, GDK_quoteleft));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_a"), f2integer__new(cause, GDK_a));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_b"), f2integer__new(cause, GDK_b));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_c"), f2integer__new(cause, GDK_c));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_d"), f2integer__new(cause, GDK_d));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_e"), f2integer__new(cause, GDK_e));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_f"), f2integer__new(cause, GDK_f));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_g"), f2integer__new(cause, GDK_g));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_h"), f2integer__new(cause, GDK_h));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_i"), f2integer__new(cause, GDK_i));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_j"), f2integer__new(cause, GDK_j));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_k"), f2integer__new(cause, GDK_k));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_l"), f2integer__new(cause, GDK_l));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_m"), f2integer__new(cause, GDK_m));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_n"), f2integer__new(cause, GDK_n));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_o"), f2integer__new(cause, GDK_o));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_p"), f2integer__new(cause, GDK_p));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_q"), f2integer__new(cause, GDK_q));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_r"), f2integer__new(cause, GDK_r));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_s"), f2integer__new(cause, GDK_s));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_t"), f2integer__new(cause, GDK_t));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_u"), f2integer__new(cause, GDK_u));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_v"), f2integer__new(cause, GDK_v));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_w"), f2integer__new(cause, GDK_w));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_x"), f2integer__new(cause, GDK_x));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_y"), f2integer__new(cause, GDK_y));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_z"), f2integer__new(cause, GDK_z));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_braceleft"), f2integer__new(cause, GDK_braceleft));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_bar"), f2integer__new(cause, GDK_bar));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_braceright"), f2integer__new(cause, GDK_braceright));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_asciitilde"), f2integer__new(cause, GDK_asciitilde));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_nobreakspace"), f2integer__new(cause, GDK_nobreakspace));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_exclamdown"), f2integer__new(cause, GDK_exclamdown));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_cent"), f2integer__new(cause, GDK_cent));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_sterling"), f2integer__new(cause, GDK_sterling));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_currency"), f2integer__new(cause, GDK_currency));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_yen"), f2integer__new(cause, GDK_yen));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_brokenbar"), f2integer__new(cause, GDK_brokenbar));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_section"), f2integer__new(cause, GDK_section));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_diaeresis"), f2integer__new(cause, GDK_diaeresis));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_copyright"), f2integer__new(cause, GDK_copyright));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_ordfeminine"), f2integer__new(cause, GDK_ordfeminine));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_guillemotleft"), f2integer__new(cause, GDK_guillemotleft));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_notsign"), f2integer__new(cause, GDK_notsign));
  f2__frame__add_var_value(cause, gdk_keysyms_frame, new__symbol(cause, "GDK_hyphen"), f2integer__new(cause, GDK_hyphen));
#endif
  return gdk_keysyms_frame;
}
export_cefunk0(gtk__gdk_keysyms_frame__new, 0,
	       "creates a new keysyms frame.");
//def_pcfunk0(gtk__gdk_keysyms_frame__new,
//	    "creates a new keysyms frame.",
//	    return f2__gtk__gdk_keysyms_frame__new(this_cause));



// **

f2ptr f2__gtk_extension__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(gtk_extension__core_extension__ping, 0, "");

f2ptr f2__gtk_extension__core_extension__initialize(f2ptr cause) {
  if (__funk2__gtk != NULL) {
    printf("\nTried to initialize gtk while gtk is already initialized.");
    status(  "Tried to initialize gtk while gtk is already initialized.");
  } else {
    __funk2__gtk = (funk2_gtk_t*)from_ptr(f2__malloc(sizeof(funk2_gtk_t)));
    __funk2__gtk->initialized_successfully = boolean__false;
    {
#if defined(F2__GTK__SUPPORTED)
      int*    argc = &(__funk2.command_line.argc);
      char*** argv = &(__funk2.command_line.argv);
      funk2_gtk__init(__funk2__gtk, argc, argv);
      funk2_gtk__start_gtk_main(__funk2__gtk);
#else  // not F2__GTK__SUPPORTED
      printf("\nTried to initialize gtk but gtk is not supported.");
      status(  "Tried to initialize gtk but gtk is not supported.");
#endif // F2__GTK__SUPPORTED
    }
  }
  
  status("gtk_extension finished initializing.");
  return nil;
}
export_cefunk0(gtk_extension__core_extension__initialize, 0, "");

f2ptr f2__gtk_extension__core_extension__define_types(f2ptr cause) {
  
  f2__add_type(cause, new__symbol(cause, "g_object"),                f2__g_object_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_widget"),              f2__gtk_widget_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_box"),                 f2__gtk_box_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_label"),               f2__gtk_label_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_scale"),               f2__gtk_scale_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_entry"),               f2__gtk_entry_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_image"),               f2__gtk_image_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_text_buffer"),         f2__gtk_text_buffer_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_text_iter"),           f2__gtk_text_iter_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "gdk_color"),               f2__gdk_color_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "gdk_pixbuf"),              f2__gdk_pixbuf_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_text_mark"),           f2__gtk_text_mark_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_callback"),            f2__gtk_callback_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_text_range"),          f2__gtk_text_range_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_progress_bar"),        f2__gtk_progress_bar_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_menu"),                f2__gtk_menu_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_menu_bar"),            f2__gtk_menu_bar_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_check_button"),        f2__gtk_check_button_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "gtk_file_chooser_dialog"), f2__gtk_file_chooser_dialog_type__new_aux(cause));
  
  status("gtk_extension types defined.");
  return nil;
}
export_cefunk0(gtk_extension__core_extension__define_types, 0, "");

f2ptr f2__gtk_extension__core_extension__destroy(f2ptr cause) {
  status("gtk_extension destroyed.");
  return nil;
}
export_cefunk0(gtk_extension__core_extension__destroy, 0, "");



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

#include "funk2.h"

void funk2_locale__init(funk2_locale_t* this) {
  funk2_processor_mutex__init(&(this->interface_mutex));
}

void funk2_locale__destroy(funk2_locale_t* this) {
  funk2_processor_mutex__destroy(&(this->interface_mutex));
}


// char *setlocale(int category, const char *locale);

f2ptr raw__setlocale(f2ptr cause, int category, char* locale_str) {
  funk2_processor_mutex__user_lock(&(__funk2.locale.interface_mutex));
  char* old_locale_str = setlocale(f2integer__i(category, cause), locale_str);
  if (old_locale_str == NULL) {
    funk2_processor_mutex__unlock(&(__funk2.locale.interface_mutex));
    return nil;
  }
  f2ptr retval = f2string__new(cause, strlen(old_locale_str), (u8*)old_locale_str);
  funk2_processor_mutex__unlock(&(__funk2.locale.interface_mutex));
  return retval;
}

f2ptr f2__setlocale(f2ptr cause, f2ptr category, f2ptr locale) {
  assert_argument_type(       integer, category);
  assert_argument_type_or_nil(string,  locale);
  char* locale_str = NULL;
  if (locale != nil) {
    int   locale_str__length = f2string__length(locale, cause);
    locale_str               = alloca(locale_str__length + 1); f2string__str_copy(locale, cause, (u8*)locale_str); locale_str[locale_str__length] = 0;
  }
  return raw__setlocale(cause, f2integer__i(category, cause), locale_str);
} 
def_pcfunk2(locale__setlocale, category, locale, return f2__setlocale(this_cause, category, locale));

def_pcfunk0(locale__lc_all,      return f2integer__new(this_cause, LC_ALL));
def_pcfunk0(locale__lc_collate,  return f2integer__new(this_cause, LC_COLLATE));
def_pcfunk0(locale__lc_ctype,    return f2integer__new(this_cause, LC_CTYPE));
def_pcfunk0(locale__lc_messages, return f2integer__new(this_cause, LC_MESSAGES));
def_pcfunk0(locale__lc_monetary, return f2integer__new(this_cause, LC_MONETARY));
def_pcfunk0(locale__lc_numeric,  return f2integer__new(this_cause, LC_NUMERIC));
def_pcfunk0(locale__lc_time,     return f2integer__new(this_cause, LC_TIME));


// **

void f2__primfunks__locale__reinitialize_globalvars() {
  //f2ptr cause = f2_primfunks__locale_c__cause__new(initial_cause(), nil, nil);
}

void f2__primfunks__locale__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks__locale", "", &f2__primfunks__locale__reinitialize_globalvars);
  
  f2__primfunks__locale__reinitialize_globalvars();
  
  f2__primcfunk__init(locale__setlocale, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_all, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_collate, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_ctype, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_messages, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_monetary, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_numeric, "(as defined in locale.h)");
  f2__primcfunk__init(locale__lc_time, "(as defined in locale.h)");
}

void f2__primfunks__locale__destroy() {
}

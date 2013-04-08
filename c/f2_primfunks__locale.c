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

#include "funk2.h"

void funk2_locale__init(funk2_locale_t* this) {
  funk2_processor_mutex__init(&(this->interface_mutex));
}

void funk2_locale__destroy(funk2_locale_t* this) {
  funk2_processor_mutex__destroy(&(this->interface_mutex));
}


// char *setlocale(int category, const char *locale);

f2ptr raw__locale__setlocale(f2ptr cause, int category, char* locale_str) {
  funk2_processor_mutex__user_lock(&(__funk2.locale.interface_mutex));
  char* old_locale_str = setlocale(f2integer__i(category, cause), locale_str);
  if (old_locale_str == NULL) {
    funk2_processor_mutex__unlock(&(__funk2.locale.interface_mutex));
    return nil;
  }
  f2ptr retval = new__string(cause, old_locale_str);
  funk2_processor_mutex__unlock(&(__funk2.locale.interface_mutex));
  return retval;
}

f2ptr f2__locale__setlocale(f2ptr cause, f2ptr category, f2ptr locale) {
  assert_argument_type(       integer, category);
  assert_argument_type_or_nil(string,  locale);
  u8* locale__utf8_str = NULL;
  if (locale != nil) {
    u64 locale_str__utf8_length = raw__string__utf8_length(cause, locale);
    locale__utf8_str            = alloca(locale_str__utf8_length + 1); raw__string__utf8_str_copy(cause, locale, locale__utf8_str); locale__utf8_str[locale_str__utf8_length] = 0;
  }
  return raw__locale__setlocale(cause, f2integer__i(category, cause), (char*)locale__utf8_str);
} 
def_pcfunk2(locale__setlocale, category, locale,
	    "",
	    return f2__locale__setlocale(this_cause, category, locale));

f2ptr f2__locale__lc_all(f2ptr cause) {
  return f2integer__new(cause, LC_ALL);
}
def_pcfunk0(locale__lc_all,
	    "",
	    return f2__locale__lc_all(this_cause));

f2ptr f2__locale__lc_collate(f2ptr cause) {
  return f2integer__new(cause, LC_COLLATE);
}
def_pcfunk0(locale__lc_collate,
	    "",
	    return f2__locale__lc_collate(this_cause));

f2ptr f2__locale__lc_ctype(f2ptr cause) {
  return f2integer__new(cause, LC_CTYPE);
}
def_pcfunk0(locale__lc_ctype,
	    "",
	    return f2__locale__lc_ctype(this_cause));

f2ptr f2__locale__lc_messages(f2ptr cause) {
#if defined(LC_MESSAGES)
  return f2integer__new(cause, LC_MESSAGES);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "locale-lc_messages-constant_not_compiled_into_this_funk2_build")));
#endif // LC_MESSAGES
}
def_pcfunk0(locale__lc_messages,
	    "",
	    return f2__locale__lc_messages(this_cause));

f2ptr f2__locale__lc_monetary(f2ptr cause) {
  return f2integer__new(cause, LC_MONETARY);
}
def_pcfunk0(locale__lc_monetary,
	    "",
	    return f2__locale__lc_monetary(this_cause));

f2ptr f2__locale__lc_numeric(f2ptr cause) {
  return f2integer__new(cause, LC_NUMERIC);
}
def_pcfunk0(locale__lc_numeric,
	    "",
	    return f2__locale__lc_numeric(this_cause));

f2ptr f2__locale__lc_time(f2ptr cause) {
  return f2integer__new(cause, LC_TIME);
}
def_pcfunk0(locale__lc_time,
	    "",
	    return f2__locale__lc_time(this_cause));


// **

void f2__primfunks__locale__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --

  f2__primcfunk__init__defragment__fix_pointers(locale__setlocale);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_all);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_collate);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_ctype);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_messages);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_monetary);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_numeric);
  f2__primcfunk__init__defragment__fix_pointers(locale__lc_time);
}

void f2__primfunks__locale__reinitialize_globalvars() {
  f2__primcfunk__init(locale__setlocale);
  f2__primcfunk__init(locale__lc_all);
  f2__primcfunk__init(locale__lc_collate);
  f2__primcfunk__init(locale__lc_ctype);
  f2__primcfunk__init(locale__lc_messages);
  f2__primcfunk__init(locale__lc_monetary);
  f2__primcfunk__init(locale__lc_numeric);
  f2__primcfunk__init(locale__lc_time);
}

void f2__primfunks__locale__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks-locale", "", &f2__primfunks__locale__reinitialize_globalvars, &f2__primfunks__locale__defragment__fix_pointers);
  
  f2__primfunks__locale__reinitialize_globalvars();
}

void f2__primfunks__locale__destroy() {
}

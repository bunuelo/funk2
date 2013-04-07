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

// int ioctl(int d, int request, ...);

f2ptr raw__ioctl__int(f2ptr cause, f2ptr d, f2ptr request, f2ptr value_place) {
#if defined(HAVE_IOCTL)
  int i;
  f2ptr rv = f2integer__new(cause, ioctl(f2integer__i(d, cause), f2integer__i(request, cause), &i));
  f2place__thing__set(value_place, cause, f2integer__new(cause, i));
  return rv;
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "ioctl-int-not_compiled_into_this_funk2_build")));
#endif // HAVE_IOCTL
}

f2ptr f2__ioctl__int(f2ptr cause, f2ptr d, f2ptr request, f2ptr value_place) {
  assert_argument_type(integer, d);
  assert_argument_type(integer, request);
  assert_argument_type(place,   value_place);
  return raw__ioctl__int(cause, d, request, value_place);
}
def_pcfunk3(ioctl__int, d, request, value_place,
	    "",
	    return f2__ioctl__int(this_cause, d, request, value_place));


f2ptr f2__ioctl__siocinq(f2ptr cause) {
#if defined(SIOCINQ)
  return f2integer__new(cause, SIOCINQ);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "ioctl-siocinq-constant_value_not_compiled_into_this_funk2_build")));
#endif // SIOCINQ
}
def_pcfunk0(ioctl__siocinq,
	    "",
	    return f2__ioctl__siocinq(this_cause));

f2ptr f2__ioctl__siocoutq(f2ptr cause) {
#if defined(SIOCOUTQ)
  return f2integer__new(cause, SIOCOUTQ);
#else
  return new__error(f2list2__new(cause,
				 new__symbol(cause, "bug_name"), new__symbol(cause, "ioctl-siocoutq-constant_value_not_compiled_into_this_funk2_build")));
#endif // SIOCOUTQ
}
def_pcfunk0(ioctl__siocoutq,
	    "",
	    return f2__ioctl__siocoutq(this_cause));
#endif


// **

void f2__primfunks__ioctl__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(ioctl__int);
  
  f2__primcfunk__init__defragment__fix_pointers(ioctl__siocinq);
  f2__primcfunk__init__defragment__fix_pointers(ioctl__siocoutq);
}

void f2__primfunks__ioctl__reinitialize_globalvars() {
  f2__primcfunk__init(ioctl__int);
  
  f2__primcfunk__init(ioctl__siocinq);
  f2__primcfunk__init(ioctl__siocoutq);
}

void f2__primfunks__ioctl__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primfunks-ioctl", "", &f2__primfunks__ioctl__reinitialize_globalvars, &f2__primfunks__ioctl__defragment__fix_pointers);
  
  f2__primfunks__ioctl__reinitialize_globalvars();
}


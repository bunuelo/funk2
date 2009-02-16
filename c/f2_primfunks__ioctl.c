// 
// Copyright (c) 2007-2008 Bo Morgan.
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

// int ioctl(int d, int request, ...);

f2ptr f2__ioctl__int(f2ptr cause, f2ptr d, f2ptr request, f2ptr value_place) {
  int i;
  f2ptr rv = f2integer__new(cause, ioctl(f2integer__i(d, cause), f2integer__i(request, cause), &i));
  f2place__thing__set(value_place, cause, f2integer__new(cause, i));
  return rv;
}
def_pcfunk3(f2__ioctl__int, d, request, value_place, return f2__ioctl__int(this_cause, d, request, value_place));

f2ptr f2__ioctl__siocinq(f2ptr cause) {return f2integer__new(cause, SIOCINQ);}
def_pcfunk0(f2__ioctl__siocinq, return f2__ioctl__siocinq(this_cause));

f2ptr f2__ioctl__siocoutq(f2ptr cause) {return f2integer__new(cause, SIOCOUTQ);}
def_pcfunk0(f2__ioctl__siocoutq, return f2__ioctl__siocoutq(this_cause));

void f2__primfunks__ioctl__reinitialize_globalvars() {
  //f2ptr cause = f2_primfunks__ioctl_c__cause__new(initial_cause(), nil, nil);
}

void f2__primfunks__ioctl__initialize() {
  pause_gc();
  //f2ptr cause = f2_primfunks__ioctl_c__cause__new(initial_cause(), nil, nil);
  
  f2__primfunks__ioctl__reinitialize_globalvars();
  
  f2__primcfunk__init(f2__ioctl__int);
  
  f2__primcfunk__init(f2__ioctl__siocinq);
  f2__primcfunk__init(f2__ioctl__siocoutq);
  
  resume_gc();
}


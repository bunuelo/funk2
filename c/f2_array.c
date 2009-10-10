// 
// Copyright (c) 2007-2009 Bo Morgan.
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

// array interface

f2ptr raw__array__new(f2ptr cause, u64 length) {
  if (raw__cause__allocate_traced_arrays(cause, cause)) {
    return f2traced_array__new(cause, length, to_ptr(NULL));
  } else {
    return f2simple_array__new(cause, length, to_ptr(NULL));
  }
}

f2ptr raw__array__new_copy(f2ptr cause, u64 length, f2ptr init) {
  if (raw__cause__allocate_traced_arrays(cause, cause)) {
    return f2traced_array__new_copy(cause, length, init);
  } else {
    return f2simple_array__new_copy(cause, length, init);
  }
}

boolean_t raw__array__is_type(f2ptr cause, f2ptr x) {return (raw__simple_array__is_type(cause, x) || raw__traced_array__is_type(cause, x));}
f2ptr f2__array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__array__is_type(cause, x));}
def_pcfunk1(array__is_type, x, return f2__array__is_type(this_cause, x));

u64 raw__array__length(f2ptr cause, f2ptr x) {
  if      (raw__simple_array__is_type(cause, x)) {return f2simple_array__length(x, cause);}
  else if (raw__traced_array__is_type(cause, x)) {return f2traced_array__length(x, cause);}
  else {error(nil, "raw__array__length: invalid type"); return 0;}
}
f2ptr f2__array__length(f2ptr cause, f2ptr x) {
  if      (raw__simple_array__is_type(cause, x)) {return f2__simple_array__length(cause, x);}
  else if (raw__traced_array__is_type(cause, x)) {return f2__traced_array__length(cause, x);}
  else {return f2larva__new(cause, 1);}
}
def_pcfunk1(array__length, x, return f2__array__length(this_cause, x));

f2ptr raw__array__elt(f2ptr cause, f2ptr this, u64 index) {
  if (raw__simple_array__is_type(cause, this)) {
    u64 length = f2simple_array__length(this, cause);
    if (index >= length) {
      return f2larva__new(cause, 2);
    }
    return f2simple_array__elt(this, index, cause);
  } else if (raw__traced_array__is_type(cause, this)) {
    u64 length = f2traced_array__length(this, cause);
    if (index >= length) {
      return f2larva__new(cause, 2);
    }
    return f2traced_array__elt(this, index, cause);
  } else {
    return f2larva__new(cause, 1);
  }
}
f2ptr f2__array__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt, x, y, return f2__array__elt(this_cause, x, y));

f2ptr raw__array__elt__trace_depth(f2ptr cause, f2ptr this, u64 index, int trace_depth) {
  if      (raw__simple_array__is_type(cause, this)) {f2simple_array__elt(             this, index, cause             ); return nil;}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__trace_depth(this, index, cause, trace_depth); return nil;}
  else {
    error(nil, "raw__array__elt__trace_depth: should be a type of array.");
    return nil;
  }
}

f2ptr raw__array__elt__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {f2simple_array__elt__set(this, index, cause, value); return nil;}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__set, x, y, z, return f2__array__elt__set(this_cause, x, y, z));

f2ptr raw__array__elt__set__trace_depth(f2ptr cause, f2ptr this, u64 index, f2ptr value, int trace_depth) {
  if      (raw__simple_array__is_type(cause, this)) {f2simple_array__elt__set(             this, index, cause, value             ); return nil;}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__set__trace_depth(this, index, cause, value, trace_depth); return nil;}
  else {
    error(nil, "raw__array__elt__set__trace_depth: should be a type of array.");
    return nil;
  }
}

f2ptr raw__array__elt__tracing_on(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__tracing_on(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__tracing_on(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__tracing_on(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__tracing_on, x, y, return f2__array__elt__tracing_on(this_cause, x, y));

f2ptr raw__array__elt__tracing_on__set(f2ptr cause, f2ptr this, u64 index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__tracing_on__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__tracing_on__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__tracing_on__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__tracing_on__set, x, y, z, return f2__array__elt__tracing_on__set(this_cause, x, y, z));

f2ptr raw__array__elt__trace(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__trace(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__trace(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__trace(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__trace, x, y, return f2__array__elt__trace(this_cause, x, y));

f2ptr raw__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__trace__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__trace__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__trace__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__trace__set, x, y, z, return f2__array__elt__trace__set(this_cause, x, y, z));

f2ptr raw__array__elt__imagination_frame(f2ptr cause, f2ptr this, u64 index) {
  if      (raw__simple_array__is_type(cause, this)) {return nil;}
  else if (raw__traced_array__is_type(cause, this)) {return f2traced_array__elt__imagination_frame(this, index, cause);}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__imagination_frame(f2ptr cause, f2ptr this, f2ptr index) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__imagination_frame(cause, this, f2integer__i(index, cause));
}
def_pcfunk2(array__elt__imagination_frame, x, y, return f2__array__elt__imagination_frame(this_cause, x, y));

f2ptr raw__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if      (raw__simple_array__is_type(cause, this)) {return f2larva__new(cause, 1);}
  else if (raw__traced_array__is_type(cause, this)) {f2traced_array__elt__imagination_frame__set(this, index, cause, value); return nil;}
  else {return f2larva__new(cause, 1);}
}
f2ptr f2__array__elt__imagination_frame__set(f2ptr cause, f2ptr this, f2ptr index, f2ptr value) {
  if (!raw__integer__is_type(cause, index)) {return f2larva__new(cause, 1);}
  return raw__array__elt__imagination_frame__set(cause, this, f2integer__i(index, cause), value);
}
def_pcfunk3(array__elt__imagination_frame__set, x, y, z, return f2__array__elt__imagination_frame__set(this_cause, x, y, z));


f2ptr f2__array__as_conslist(f2ptr cause, f2ptr this) {
  if (! raw__array__is_type(cause, this)) {
    return f2larva__new(cause, 1);
  }
  u64 length = raw__array__length(cause, this);
  f2ptr new_seq = nil;
  s64 index;
  for (index = length - 1; index >= 0; index --) {
    new_seq = f2cons__new(cause, raw__array__elt(cause, this, index), new_seq);
  }
  return new_seq;
}
def_pcfunk1(array__as_conslist, this, return f2__array__as_conslist(this_cause, this));



// **

void f2__array__reinitialize_globalvars() {
  //f2ptr cause = f2_primfunks_c__cause__new(initial_cause());
  
}

void f2__array__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "array", "", &f2__array__reinitialize_globalvars);
  
  f2__array__reinitialize_globalvars();
  
  // array
  
  f2__funktional_primcfunk__init__1(array__is_type,                     exp, "");
  f2__primcfunk__init__1(           array__new_1d,                      length, "");
  f2__primcfunk__init__0_and_rest(  array,                              elts, "");
  f2__funktional_primcfunk__init__1(array__length,                      this, "");
  f2__primcfunk__init__2(           array__elt,                         this, index, "");
  f2__primcfunk__init__3(           array__elt__set,                    this, index, value, "");
  f2__primcfunk__init__2(           array__elt__tracing_on,             this, index, "");
  f2__primcfunk__init__3(           array__elt__tracing_on__set,        this, index, value, "");
  f2__primcfunk__init__2(           array__elt__trace,                  this, index, "");
  f2__primcfunk__init__3(           array__elt__trace__set,             this, index, value, "");
  f2__primcfunk__init__2(           array__elt__imagination_frame,      this, index, "");
  f2__primcfunk__init__3(           array__elt__imagination_frame__set, this, index, value, "");
  f2__primcfunk__init__1(           array__as_conslist,                 this, "returns an array represented as a new conslist.");
  
}



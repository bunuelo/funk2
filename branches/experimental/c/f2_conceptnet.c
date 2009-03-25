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

// conceptnet_relation primobject definition

defprimobject__static_slot(conceptnet_relation__type,          0);
defprimobject__static_slot(conceptnet_relation__left_concept,  1);
defprimobject__static_slot(conceptnet_relation__right_concept, 2);

f2ptr __conceptnet_relation__symbol = -1;

f2ptr f2conceptnet_relation__new(f2ptr cause, f2ptr type, f2ptr left_concept, f2ptr right_concept) {
  if (__conceptnet_relation__symbol == -1) {__conceptnet_relation__symbol = f2symbol__new(cause, strlen("conceptnet_relation"), (u8*)"conceptnet_relation");}
  f2ptr this = f2__primobject__new(cause, __conceptnet_relation__symbol, 3, nil);
  f2conceptnet_relation__type__set(         this, cause, type);
  f2conceptnet_relation__left_concept__set( this, cause, left_concept);
  f2conceptnet_relation__right_concept__set(this, cause, right_concept);
  return this;
}

boolean_t raw__conceptnet_relationp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__conceptnet_relation(this, cause));}
f2ptr f2__conceptnet_relationp(f2ptr this, f2ptr cause) {return f2bool__new(raw__conceptnet_relationp(this, cause));}


// conceptnet_graph primobject definition

defprimobject__static_slot(conceptnet_graph__relations, 0);

f2ptr __conceptnet_graph__symbol = -1;

f2ptr f2conceptnet_graph__new(f2ptr cause, f2ptr relations) {
  if (__conceptnet_graph__symbol == -1) {__conceptnet_graph__symbol = f2symbol__new(cause, strlen("conceptnet_graph"), (u8*)"conceptnet_graph");}
  f2ptr this = f2__primobject__new(cause, __conceptnet_graph__symbol, 1, nil);
  f2conceptnet_graph__relations__set( this, cause, relations);
  return this;
}

boolean_t raw__conceptnet_graphp(f2ptr this, f2ptr cause) {return (raw__arrayp(this, cause) && raw__array__length(cause, this) >= 2 && f2primobject__is__conceptnet_graph(this, cause));}
f2ptr f2__conceptnet_graphp(f2ptr this, f2ptr cause) {return f2bool__new(raw__conceptnet_graphp(this, cause));}




// **

void f2__conceptnet__reinitialize_globalvars() {
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  __conceptnet_relation__symbol = f2symbol__new(cause, strlen("conceptnet_relation"), (u8*)"conceptnet_relation");
  __conceptnet_graph__symbol    = f2symbol__new(cause, strlen("conceptnet_graph"),    (u8*)"conceptnet_graph");
}

void f2__conceptnet__initialize() {
  pause_gc();
  f2__conceptnet__reinitialize_globalvars();
  f2ptr cause = initial_cause(); //f2_primobjects_c__cause__new(initial_cause(), nil, nil);
  
  environment__add_var_value(cause, global_environment(), __conceptnet_relation__symbol, nil);
  environment__add_var_value(cause, global_environment(), __conceptnet_graph__symbol, nil);
  
  resume_gc();
  try_gc();
}


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

void funk2_primobject__frame__init(funk2_primobject__frame_t* this) {
  f2ptr cause = initial_cause();
  
  environment__add_var_value(cause, global_environment(), this->type_variable_not_defined__symbol, nil);
  environment__add_var_value(cause, global_environment(), this->frame__symbol,                     nil);
  environment__add_var_value(cause, global_environment(), this->variable__symbol,                  nil);
  environment__add_var_value(cause, global_environment(), this->funk_variable__symbol,             nil);
}

void funk2_primobject__frame__reinit(funk2_primobject__frame_t* this) {
  f2ptr cause = initial_cause(); //f2_primobject_frame_c__cause__new(initial_cause(), nil, global_environment());
  char* symbol_str;
  symbol_str = "type_variable_not_defined"; this->type_variable_not_defined__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "frame";                     this->frame__symbol                     = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "variable";                  this->variable__symbol                  = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
  symbol_str = "funk_variable";             this->funk_variable__symbol             = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);
}

void funk2_primobject__frame__destroy(funk2_primobject__frame_t* this) {
}

// frame

defprimobject__static_slot(frame__type_hashtable, 0);

f2ptr f2frame__new__raw(f2ptr cause, f2ptr type_hashtable) {
  release__assert(__frame__symbol != -1, nil, "f2hashtable__new error: used before primobjects initialized.");
  f2ptr this = f2__primobject__new(cause, __funk2.primobject__frame.frame__symbol, 1, nil);
  f2frame__type_hashtable__set(this, cause, type_hashtable);
  return this;
}

f2ptr f2frame__new(f2ptr cause, f2ptr var_hashtable, f2ptr funkvar_hashtable) {
  f2ptr type_hashtable = f2__hashtable__new(cause, f2integer__new(cause, 3));
  f2__hashtable__add_keyvalue_pair(cause, type_hashtable, __funk2.primobject__frame.variable__symbol,      var_hashtable);
  f2__hashtable__add_keyvalue_pair(cause, type_hashtable, __funk2.primobject__frame.funk_variable__symbol, funkvar_hashtable);
  f2ptr result = f2frame__new__raw(cause, type_hashtable);
  return result;
}

boolean_t raw__frame__is_type(f2ptr cause, f2ptr x) {return (raw__primobject__is_type(cause, x) && f2primobject__is_frame(x, cause));}
f2ptr f2__frame__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__frame__is_type(cause, x));}
def_pcfunk1(frame__is_type, x, return f2__frame__is_type(this_cause, x));

void  frame__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value) {
  f2ptr frame__type_hashtable = f2frame__type_hashtable(this, cause);
  f2ptr type__hashtable = f2__hashtable__lookup_value(frame__type_hashtable, cause, type);
  if (! type__hashtable) {
    type__hashtable = f2__hashtable__new(cause, f2integer__new(cause, 5));
    f2__hashtable__add_keyvalue_pair(cause, frame__type_hashtable, type, type__hashtable);
  }
  f2__hashtable__add_keyvalue_pair(cause, type__hashtable, var, value);
}

f2ptr frame__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value) {
  f2ptr type__keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(f2frame__type_hashtable(this, cause), cause, type);
  if (type__keyvalue_pair) {
    f2ptr type__hashtable = f2cons__cdr(type__keyvalue_pair, cause);
    f2ptr keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(type__hashtable, cause, var);
    if (keyvalue_pair) {
      return keyvalue_pair;
    }
  }
  return not_defined_value;
}

f2ptr frame__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr not_defined_value) {
  f2ptr type__keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(f2frame__type_hashtable(this, cause), cause, type);
  if (type__keyvalue_pair) {
    f2ptr type__hashtable = f2cons__cdr(type__keyvalue_pair, cause);
    f2ptr keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(type__hashtable, cause, var);
    if (keyvalue_pair) {
      f2ptr retval = f2cons__cdr(keyvalue_pair, cause);
      return retval;
    }
  }
  return not_defined_value;
}

f2ptr frame__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value, f2ptr not_defined_value) {
  f2ptr type__keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(f2frame__type_hashtable(this, cause), cause, type);
  if (type__keyvalue_pair) {
    f2ptr type__hashtable = f2cons__cdr(type__keyvalue_pair, cause);
    f2ptr keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(type__hashtable, cause, var);
    if (keyvalue_pair) {
      f2cons__cdr__set(keyvalue_pair, cause, value);
      return nil;
    }
  }
  return not_defined_value;
}

f2ptr frame__type_var__slot_names(f2ptr cause, f2ptr this, f2ptr type) {
  f2ptr retval = nil;
  f2ptr type__keyvalue_pair = f2__hashtable__lookup_keyvalue_pair(f2frame__type_hashtable(this, cause), cause, type);
  if (type__keyvalue_pair) {
    f2ptr type__hashtable = f2cons__cdr(type__keyvalue_pair, cause);
    retval = f2__hashtable__slot_names(cause, type__hashtable);
  }
  return retval;
}

f2ptr frame__var_hashtable(f2ptr cause, f2ptr this) {return f2__hashtable__lookup_value(f2frame__type_hashtable(this, cause), cause, __funk2.primobject__frame.variable__symbol);}

void frame__add_var_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {frame__add_type_var_value(cause, this, __frame__variable_type__symbol, var, value);}
def_pcfunk3(frame__add_var_value, this, var, value, frame__add_var_value(this_cause, this, var, value); return nil);

f2ptr frame__lookup_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return frame__lookup_type_var_assignment_cons(cause, this, __funk2.primobject__frame.variable__symbol, var, not_defined_value);}

f2ptr frame__lookup_var_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, var, not_defined_value);}
def_pcfunk3(frame__lookup_var_value, this, var, not_defined_value, return frame__lookup_var_value(this_cause, this, var, not_defined_value));

f2ptr frame__var_value__set(f2ptr cause, f2ptr this, f2ptr var, f2ptr value, f2ptr not_defined_value) {return frame__type_var_value__set(cause, this, __funk2.primobject__frame.variable__symbol, var, value, not_defined_value);}
def_pcfunk4(frame__var_value__set, this, var, value, not_defined_value, return frame__var_value__set(this_cause, this, var, value, not_defined_value));

f2ptr frame__funkvar_hashtable(f2ptr cause, f2ptr this) {return f2__hashtable__lookup_value(f2frame__type_hashtable(this, cause), cause, __funk2.primobject__frame.funk_variable__symbol);}

void  frame__add_funkvar_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr value) {frame__add_type_var_value(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value);}
def_pcfunk3(frame__add_funkvar_value, this, funkvar, value, frame__add_var_value(this_cause, this, funkvar, value); return nil);

f2ptr frame__lookup_funkvar_assignment_cons(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return frame__lookup_type_var_assignment_cons(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, not_defined_value);}

f2ptr frame__lookup_funkvar_value(f2ptr cause, f2ptr this, f2ptr var, f2ptr not_defined_value) {return frame__lookup_type_var_value(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, not_defined_value);}
def_pcfunk3(frame__lookup_funkvar_value, this, funkvar, not_defined_value, return frame__lookup_funkvar_value(this_cause, this, funkvar, not_defined_value));

f2ptr frame__funkvar_value__set(f2ptr cause, f2ptr this, f2ptr var, f2ptr value, f2ptr not_defined_value) {return frame__type_var_value__set(cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value, not_defined_value);}
def_pcfunk4(frame__funkvar_value__set, this, funkvar, value, not_defined_value, return frame__var_value__set(this_cause, this, funkvar, value, not_defined_value));

f2ptr frame__new_empty(f2ptr cause) {
  f2ptr this = f2frame__new(cause,
			    f2__hashtable__new(cause, f2integer__new(cause, 5)),
			    f2__hashtable__new(cause, f2integer__new(cause, 5)));
  return this;
}

def_pcfunk0(frame__new, return frame__new_empty(this_cause));

f2ptr frame__new_empty_globalsize(f2ptr cause) {
  f2ptr this = f2frame__new(cause,
			    f2__hashtable__new(cause, f2integer__new(cause, 24)),
			    f2__hashtable__new(cause, f2integer__new(cause, 24)));
  return this;
}

f2ptr frame__var__slot_names(f2ptr cause, f2ptr this) {
  return f2__hashtable__slot_names(cause, frame__var_hashtable(cause, this));
}
def_pcfunk1(frame__var__slot_names, this, return frame__var__slot_names(this_cause, this));

f2ptr frame__funkvar__slot_names(f2ptr cause, f2ptr this) {
  return f2__hashtable__slot_names(cause, frame__funkvar_hashtable(cause, this));
}
def_pcfunk1(frame__funkvar__slot_names, this, return frame__funkvar__slot_names(this_cause, this));


// **

void f2__primobject_frame__reinitialize_globalvars() {
  funk2_primobject__frame__reinit(&(__funk2.primobject__frame));
}

void f2__primobject_frame__initialize() {
  f2__primobject_frame__reinitialize_globalvar__symbols();
  
  f2__primcfunk__init__1(frame__is_type, exp, "checks to see if object is a frame.  returns true is object is a frame and false otherwise.");
  f2__primcfunk__init(frame__new, "");
  f2__primcfunk__init(frame__add_var_value, "");
  f2__primcfunk__init(frame__lookup_var_value, "");
  f2__primcfunk__init(frame__var_value__set, "");
  f2__primcfunk__init(frame__add_funkvar_value, "");
  f2__primcfunk__init(frame__lookup_funkvar_value, "");
  f2__primcfunk__init(frame__funkvar_value__set, "");
  f2__primcfunk__init(frame__var__slot_names, "");
  f2__primcfunk__init(frame__funkvar__slot_names, "");
  
  funk2_primobject__frame__init(&(__funk2.primobject__frame));
}


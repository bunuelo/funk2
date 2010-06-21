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

// source_expression

def_primobject_6_slot(source_expression,
		      body, first_line, last_line, first_column, last_column, subexpressions);

f2ptr f2__source_expression__new(f2ptr cause, f2ptr body, f2ptr first_line, f2ptr last_line, f2ptr first_column, f2ptr last_column, f2ptr subexpressions) {return f2source_expression__new(cause, body, first_line, last_line, first_column, last_column, subexpressions);}
def_pcfunk6(source_expression__new, body, first_line, last_line, first_column, last_column, subexpressions, return f2__source_expression__new(this_cause, body, first_line, last_line, first_column, last_column, subexpressions));

f2ptr f2source_expression__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2source_expression__primobject_type__new(cause);
  return this;
}


// source

def_primobject_1_slot(source,
		      code);

f2ptr f2__source__new(f2ptr cause, f2ptr code) {return f2source__new(cause, code);}
def_pcfunk1(source__new, code, return f2__source__new(this_cause, code));

f2ptr f2__source__load(f2ptr cause, f2ptr filename) {
  f2ptr code = f2__string__load(cause, filename);
  return f2__source__new(cause, code);
}
def_pcfunk1(source__load, filename, return f2__source__load(this_cause, filename));

f2ptr f2source__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2source__primobject_type__new(cause);
  return this;
}


// package

def_primobject_1_slot(package,
		      dependencies);

f2ptr f2__package__new(f2ptr cause, f2ptr dependencies) {return f2package__new(cause, dependencies);}
def_pcfunk1(package__new, dependencies, return f2__package__new(this_cause, dependencies));



f2ptr f2package__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2package__primobject_type__new(cause);
  return this;
}

// **

void f2__package__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __source_expression__symbol = new__symbol(cause, "source_expression");
  __source__symbol            = new__symbol(cause, "source");
  __package__symbol           = new__symbol(cause, "package");
}

void f2__package__initialize() {
  f2__package__reinitialize_globalvars();
  funk2_module_registration__add_module(&(__funk2.module_registration), "package", "", &f2__cause__reinitialize_globalvars);
  f2ptr cause = initial_cause();
  
  //--
  
  // source_expression
  
  initialize_primobject_6_slot(source_expression,
			       body, first_line, last_line, first_column, last_column, subexpressions);
  
  // source
  
  initialize_primobject_1_slot(source,
			       code);
  
  f2__primcfunk__init__1(source__load, filename, "load source code from a file named by filename.");
  
  // package
  
  initialize_primobject_1_slot(package,
			       dependencies);
  
}


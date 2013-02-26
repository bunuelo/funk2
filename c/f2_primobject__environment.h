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

#ifndef F2__PRIMOBJECT__ENVIRONMENT__TYPES__H
#define F2__PRIMOBJECT__ENVIRONMENT__TYPES__H

// environment

typedef struct funk2_object_type__environment__slot_s funk2_object_type__environment__slot_t;

declare_object_type_3_slot(environment, frame, parent_env, desc,
			   f2ptr add_type_var_value__symbol;
			   f2ptr add_type_var_value__funk;
			   f2ptr lookup_type_var_value__symbol;
			   f2ptr lookup_type_var_value__funk;
			   f2ptr type_var_value__set__symbol;
			   f2ptr type_var_value__set__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );


#endif // F2__PRIMOBJECT__ENVIRONMENT__TYPES__H

#ifndef F2__PRIMOBJECT__ENVIRONMENT__H
#define F2__PRIMOBJECT__ENVIRONMENT__H

#include "f2_ptypes.h"
#include "f2_primfunks.h"
#include "f2_globalenv.h"
#include "f2_print.h"
#include "f2_primobjects.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__frame.h"

declare_primobject_3_slot(environment, frame, parent_env, desc);

f2ptr f2__environment__add_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr f2__environment__lookup_type_var_assignment_cons(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr f2__environment__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr f2__environment__safe_lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr f2__environment__define_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr f2__environment__type_var_value__set(f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);

#define environment__add_var_value(cause, this, var, value)        f2__environment__add_type_var_value(        cause, this, __funk2.primobject__frame.variable__symbol, var, value)
#define environment__lookup_var_value(cause, this, var)            f2__environment__lookup_type_var_value(     cause, this, __funk2.primobject__frame.variable__symbol, var)
#define environment__safe_lookup_var_value(cause, this, var)       f2__environment__safe_lookup_type_var_value(cause, this, __funk2.primobject__frame.variable__symbol, var)
#define environment__define_var_value(cause, this, var, value)     f2__environment__define_type_var_value(     cause, this, __funk2.primobject__frame.variable__symbol, var, value)
#define environment__var_value__set(cause, this, var, value)       f2__environment__type_var_value__set(       cause, this, __funk2.primobject__frame.variable__symbol, var, value)

#define environment__add_funkvar_value(cause, this, var, value)    f2__environment__add_type_var_value(        cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value)
#define environment__lookup_funkvar_value(cause, this, var)        f2__environment__lookup_type_var_value(     cause, this, __funk2.primobject__frame.funk_variable__symbol, var)
#define environment__safe_lookup_funkvar_value(cause, this, var)   f2__environment__safe_lookup_type_var_value(cause, this, __funk2.primobject__frame.funk_variable__symbol, var)
#define environment__define_funkvar_value(cause, this, var, value) f2__environment__define_type_var_value(     cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value)
#define environment__funkvar_value__set(cause, this, var, value)   f2__environment__type_var_value__set(       cause, this, __funk2.primobject__frame.funk_variable__symbol, var, value)

void print_environment_backtrace(f2ptr env);

typedef struct funk2_primobject__environment_s {
  f2ptr environment__symbol;
  f2ptr current_environment__symbol;
  f2ptr environment__last_23_larva_symbol;
} funk2_primobject__environment_t;

void funk2_primobject__environment__init(funk2_primobject__environment_t* this);
void funk2_primobject__environment__reinit(funk2_primobject__environment_t* this);
void funk2_primobject__environment__destroy(funk2_primobject__environment_t* this);

f2ptr f2environment__primobject_type__new_aux(f2ptr cause);

// **

void f2__primobject_environment__reinitialize_globalvars();
void f2__primobject_environment__initialize();

#endif // F2__PRIMOBJECT__ENVIRONMENT__H


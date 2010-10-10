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

#ifndef F2__STRING__H
#define F2__STRING__H

#include "f2_primfunks.h"

f2ptr f2__stringlist__new_string_from_concatenation(f2ptr cause, f2ptr this);
f2ptr f2__stringlist__concat                       (f2ptr cause, f2ptr this);
f2ptr f2__stringlist__intersperse                  (f2ptr cause, f2ptr this, f2ptr intersperse_string);
f2ptr f2__stringlist__rawcode                      (f2ptr cause, f2ptr this);

f2ptr f2__exp__as__string(f2ptr cause, f2ptr exp);

f2ptr     raw__string__as__symbol( f2ptr cause, f2ptr this);
f2ptr      f2__string__as__symbol( f2ptr cause, f2ptr this);
f2ptr      f2__string__save(       f2ptr cause, f2ptr this, f2ptr filename);
f2ptr      f2__string__load(       f2ptr cause, f2ptr filename);
f2ptr      f2__string__split(      f2ptr cause, f2ptr this, f2ptr token);
boolean_t raw__string__contains(   f2ptr cause, f2ptr this, f2ptr substring);
f2ptr      f2__string__contains(   f2ptr cause, f2ptr this, f2ptr substring);
f2ptr     raw__string__substring(  f2ptr cause, f2ptr this, s64 start_index, s64 end_index);
f2ptr      f2__string__substring(  f2ptr cause, f2ptr this, f2ptr start_index, f2ptr end_index);
f2ptr      f2__string__replace_all(f2ptr cause, f2ptr this, f2ptr token, f2ptr replacement);


f2ptr f2string__primobject_type__new_aux(f2ptr cause);

// **

void f2__string__reinitialize_globalvars();
void f2__string__initialize();

#endif // F2__STRING__H


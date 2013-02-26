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

#ifndef F2__PRIMMETROS__H
#define F2__PRIMMETROS__H

f2ptr raw__cfunk__as__metrocfunk(f2ptr cause, f2ptr this);
f2ptr  f2__cfunk__as__metrocfunk(f2ptr cause, f2ptr this);

f2ptr raw__primmetro__let                                 (f2ptr cause, f2ptr variable_definitions, f2ptr body_expressions);
f2ptr  f2__primmetro__let                                 (f2ptr cause, f2ptr variable_definitions, f2ptr body_expressions);
f2ptr raw__primmetro__prog                                (f2ptr cause, f2ptr body_expressions);
f2ptr  f2__primmetro__prog                                (f2ptr cause, f2ptr body_expressions);
f2ptr raw__primmetro__apply                               (f2ptr cause, f2ptr funkable, f2ptr arguments);
f2ptr  f2__primmetro__apply                               (f2ptr cause, f2ptr funkable, f2ptr arguments);
f2ptr raw__primmetro__funk                                (f2ptr cause, f2ptr variables, f2ptr body_expressions);
f2ptr  f2__primmetro__funk                                (f2ptr cause, f2ptr variables, f2ptr body_expressions);
f2ptr raw__primmetro__funk__new_with_name_and_environment (f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions);
f2ptr  f2__primmetro__funk__new_with_name_and_environment (f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions);
f2ptr raw__primmetro__funk__new_with_name                 (f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions);
f2ptr  f2__primmetro__funk__new_with_name                 (f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions);
f2ptr raw__primmetro__metro__new_with_name_and_environment(f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions);
f2ptr  f2__primmetro__metro__new_with_name_and_environment(f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions);
f2ptr raw__primmetro__metro__new_with_name                (f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions);
f2ptr  f2__primmetro__metro__new_with_name                (f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions);
f2ptr raw__primmetro__cond                                (f2ptr cause, f2ptr clauses);
f2ptr  f2__primmetro__cond                                (f2ptr cause, f2ptr clauses);
f2ptr  f2__primobject__frametype__slotdef__name           (f2ptr cause, f2ptr this);
f2ptr  f2__primobject__frametype__slotdef__value          (f2ptr cause, f2ptr this);
f2ptr  f2__primobject__frametype__type__has_parent        (f2ptr cause, f2ptr frame_object, f2ptr body_expressions);
f2ptr  f2__primobject__frametype__with                    (f2ptr cause, f2ptr frame_object, f2ptr body_expressions);
f2ptr  f2__primobject__frametype__add_type_funk           (f2ptr cause, f2ptr type_name, f2ptr slot_type, f2ptr slot_name, f2ptr funk);

// **

void f2__primmetros__reinitialize_globalvars();
void f2__primmetros__initialize();

#endif // F2__PRIMMETROS__H

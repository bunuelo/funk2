// 
// Copyright (c) 2007-2012 Bo Morgan.
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

#ifndef F2__EXTENSION__SEMANTIC_DEPENDENCY__H
#define F2__EXTENSION__SEMANTIC_DEPENDENCY__H

#include "../semantic_object/semantic_object.h"


// dependency_callback

def_header_ceframe2(dependency_callback,
		    funk,
		    args);

f2ptr raw__dependency_callback__new (f2ptr cause, f2ptr funk, f2ptr args);
f2ptr  f2__dependency_callback__new (f2ptr cause, f2ptr funk, f2ptr args);
f2ptr raw__dependency_callback__call(f2ptr cause, f2ptr this);
f2ptr  f2__dependency_callback__call(f2ptr cause, f2ptr this);

f2ptr f2__dependency_callback_type__primobject_type__new_aux(f2ptr cause);


// semantic_dependency

f2ptr     raw__semantic_dependency__type_create                              (f2ptr cause, f2ptr this, f2ptr semantic_realm);
f2ptr     raw__semantic_dependency__new                                      (f2ptr cause, f2ptr semantic_realm);
f2ptr      f2__semantic_dependency__new                                      (f2ptr cause, f2ptr semantic_realm);
boolean_t raw__semantic_dependency__is_type                                  (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_dependency__is_type                                  (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_dependency__type                                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__type                                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__resource_activation                      (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__resource_activation                      (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__resource_activation__set                 (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_dependency__resource_activation__set                 (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_dependency__precondition_time                        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__precondition_time                        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__precondition_time__set                   (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_dependency__precondition_time__set                   (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_dependency__precondition_event__lookup_set           (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__precondition_event__lookup_set           (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__precondition_event__add                  (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_dependency__precondition_event__add                  (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_dependency__precondition_event__remove               (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_dependency__precondition_event__remove               (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_dependency__change_hypothesis__lookup_set            (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__change_hypothesis__lookup_set            (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__change_hypothesis__add                   (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_dependency__change_hypothesis__add                   (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_dependency__change_hypothesis__remove                (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_dependency__change_hypothesis__remove                (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_dependency__know_of_precondition_lost_grounding      (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__know_of_precondition_lost_grounding      (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__know_of_change_hypothesis_removal        (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__know_of_change_hypothesis_removal        (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__know_of_decision_to_not_activate_resource(f2ptr cause, f2ptr this);
f2ptr      f2__semantic_dependency__know_of_decision_to_not_activate_resource(f2ptr cause, f2ptr this);
f2ptr     raw__semantic_dependency__terminal_print_with_frame                (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_dependency__terminal_print_with_frame                (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_dependency__primobject_type__new(f2ptr cause);


// **

f2ptr f2__semantic_dependency__core_extension__ping      (f2ptr cause);
f2ptr f2__semantic_dependency__core_extension__initialize(f2ptr cause);
f2ptr f2__semantic_dependency__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_DEPENDENCY__H


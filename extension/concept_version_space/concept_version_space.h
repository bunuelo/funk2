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

#ifndef F2__EXTENSION__CONCEPT_VERSION_SPACE__H
#define F2__EXTENSION__CONCEPT_VERSION_SPACE__H

#include "../../c/funk2.h"

// concept_version_space_example

def_header_ceframe2(concept_version_space_example,
		    positive,
		    value_variable_name_ptypehash);

f2ptr raw__concept_version_space_example__new                      (f2ptr cause, f2ptr positive);
f2ptr  f2__concept_version_space_example__new                      (f2ptr cause, f2ptr positive);
f2ptr raw__concept_version_space_example__add_variable_value       (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr  f2__concept_version_space_example__add_variable_value       (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr raw__concept_version_space_example__lookup_variable_value    (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr  f2__concept_version_space_example__lookup_variable_value    (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__concept_version_space_example__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__concept_version_space_example__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__concept_version_space_example_type__new_aux(f2ptr cause);


// concept_version_space_hypothesis

def_header_ceframe4(concept_version_space_hypothesis,
		    value_variable_name_ptypehash,
		    removal_callbacks_cmutex,
		    removal_callbacks,
		    is_removed);


f2ptr raw__concept_version_space_hypothesis__new                                                (f2ptr cause);
f2ptr  f2__concept_version_space_hypothesis__new                                                (f2ptr cause);
f2ptr raw__concept_version_space_hypothesis__new_copy                                           (f2ptr cause, f2ptr this);
f2ptr  f2__concept_version_space_hypothesis__new_copy                                           (f2ptr cause, f2ptr this);
f2ptr raw__concept_version_space_hypothesis__add_variable_value                                 (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr  f2__concept_version_space_hypothesis__add_variable_value                                 (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr raw__concept_version_space_hypothesis__lookup_variable_value                              (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr  f2__concept_version_space_hypothesis__lookup_variable_value                              (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__concept_version_space_hypothesis__exclude_variable_value                             (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr  f2__concept_version_space_hypothesis__exclude_variable_value                             (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr raw__concept_version_space_hypothesis__include_variable_value                             (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr  f2__concept_version_space_hypothesis__include_variable_value                             (f2ptr cause, f2ptr this, f2ptr variable_name, f2ptr value);
f2ptr raw__concept_version_space_hypothesis__is_consistent_with_example                         (f2ptr cause, f2ptr this, f2ptr example);
f2ptr  f2__concept_version_space_hypothesis__is_consistent_with_example                         (f2ptr cause, f2ptr this, f2ptr example);
f2ptr raw__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr  f2__concept_version_space_hypothesis__is_consistent_with_or_more_general_than_hypothesis (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr raw__concept_version_space_hypothesis__is_consistent_with_hypothesis                      (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr  f2__concept_version_space_hypothesis__is_consistent_with_hypothesis                      (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr raw__concept_version_space_hypothesis__is_more_general_than_hypothesis                    (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr  f2__concept_version_space_hypothesis__is_more_general_than_hypothesis                    (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr raw__concept_version_space_hypothesis__is_more_specific_than_hypothesis                   (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr  f2__concept_version_space_hypothesis__is_more_specific_than_hypothesis                   (f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr raw__concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr  f2__concept_version_space_hypothesis__is_consistent_with_or_more_specific_than_hypothesis(f2ptr cause, f2ptr this, f2ptr hypothesis);
f2ptr raw__concept_version_space_hypothesis__minimal_generalizations_consistent_with_example    (f2ptr cause, f2ptr this, f2ptr example);
f2ptr  f2__concept_version_space_hypothesis__minimal_generalizations_consistent_with_example    (f2ptr cause, f2ptr this, f2ptr example);
f2ptr raw__concept_version_space_hypothesis__minimal_specializations_consistent_with_example    (f2ptr cause, f2ptr this, f2ptr example);
f2ptr  f2__concept_version_space_hypothesis__minimal_specializations_consistent_with_example    (f2ptr cause, f2ptr this, f2ptr example);
f2ptr raw__concept_version_space_hypothesis__add_removal_callback                               (f2ptr cause, f2ptr this, f2ptr funk, f2ptr args);
f2ptr  f2__concept_version_space_hypothesis__add_removal_callback                               (f2ptr cause, f2ptr this, f2ptr funk, f2ptr args);
f2ptr raw__concept_version_space_hypothesis__know_of_removal                                    (f2ptr cause, f2ptr this);
f2ptr  f2__concept_version_space_hypothesis__know_of_removal                                    (f2ptr cause, f2ptr this);
f2ptr raw__concept_version_space_hypothesis__terminal_print_with_frame                          (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__concept_version_space_hypothesis__terminal_print_with_frame                          (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__concept_version_space_hypothesis_type__new_aux(f2ptr cause);


// concept_version_space

def_header_ceframe3(concept_version_space,
		    variable_name_set,
		    specific_hypotheses,
		    general_hypotheses);

f2ptr raw__concept_version_space__new                                        (f2ptr cause);
f2ptr  f2__concept_version_space__new                                        (f2ptr cause);
f2ptr raw__concept_version_space__add_variable                               (f2ptr cause, f2ptr this, f2ptr variable_name);
f2ptr raw__concept_version_space__train_on_example                           (f2ptr cause, f2ptr this, f2ptr example);
f2ptr  f2__concept_version_space__train_on_example                           (f2ptr cause, f2ptr this, f2ptr example);
f2ptr raw__concept_version_space__specific_hypotheses_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example);
f2ptr  f2__concept_version_space__specific_hypotheses_consistent_with_example(f2ptr cause, f2ptr this, f2ptr example);

f2ptr f2__concept_version_space_type__new_aux(f2ptr cause);


// **

f2ptr f2__concept_version_space__core_extension__ping      (f2ptr cause);
f2ptr f2__concept_version_space__core_extension__initialize(f2ptr cause);
f2ptr f2__concept_version_space__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__CONCEPT_VERSION_SPACE__H


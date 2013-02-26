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

#ifndef F2__EXTENSION__SEMANTIC_RELATIONSHIP_KEY__H
#define F2__EXTENSION__SEMANTIC_RELATIONSHIP_KEY__H

#include "../../c/funk2.h"


// semantic_relationship_key

def_header_ceframe4(semantic_relationship_key,
		    source,
		    key_type,
		    key,
		    target);

f2ptr     raw__semantic_relationship_key__new                         (f2ptr cause, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target);
f2ptr      f2__semantic_relationship_key__new                         (f2ptr cause, f2ptr source, f2ptr key_type, f2ptr key, f2ptr target);
u64       raw__semantic_relationship_key__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
f2ptr      f2__semantic_relationship_key__equals_hash_value__loop_free(f2ptr cause, f2ptr this, f2ptr node_ptypehash);
u64       raw__semantic_relationship_key__equals_hash_value           (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_relationship_key__equals_hash_value           (f2ptr cause, f2ptr this);
boolean_t raw__semantic_relationship_key__equals                      (f2ptr cause, f2ptr this, f2ptr that);
f2ptr      f2__semantic_relationship_key__equals                      (f2ptr cause, f2ptr this, f2ptr that);
f2ptr     raw__semantic_relationship_key__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_relationship_key__terminal_print_with_frame   (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_relationship_key_type__new_aux(f2ptr cause);

// **

f2ptr f2__semantic_relationship_key__core_extension__ping        (f2ptr cause);
f2ptr f2__semantic_relationship_key__core_extension__initialize  (f2ptr cause);
f2ptr f2__semantic_relationship_key__core_extension__define_types(f2ptr cause);
f2ptr f2__semantic_relationship_key__core_extension__destroy     (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_RELATIONSHIP_KEY__H


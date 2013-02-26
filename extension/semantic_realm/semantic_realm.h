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

#ifndef F2__EXTENSION__SEMANTIC_REALM__H
#define F2__EXTENSION__SEMANTIC_REALM__H

#include "../../c/funk2.h"
#include "../semantic_relationship_key/semantic_relationship_key.h"
#include "../semantic_frame/semantic_frame.h"
#include "../equals_hash/equals_hash.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"
#include "../forgetful_event_stream/forgetful_event_stream.h"
#include "../lick/lick.h"

// semantic_realm

def_header_ceframe4(semantic_realm,
		    semantic_hash,
		    meta_relationship_hash,
		    semantic_knowledge_base_frame,
		    semantic_frame_phenomenon_hash);

f2ptr raw__semantic_realm__new                               (f2ptr cause);
f2ptr  f2__semantic_realm__new                               (f2ptr cause);
f2ptr raw__semantic_realm__lookup_object_key                 (f2ptr cause, f2ptr this, f2ptr object);
f2ptr  f2__semantic_realm__lookup_object_key                 (f2ptr cause, f2ptr this, f2ptr object);
f2ptr raw__semantic_realm__add_object_key                    (f2ptr cause, f2ptr this, f2ptr object);
f2ptr  f2__semantic_realm__add_object_key                    (f2ptr cause, f2ptr this, f2ptr object);
f2ptr raw__semantic_realm__object_key                        (f2ptr cause, f2ptr this, f2ptr object);
f2ptr  f2__semantic_realm__object_key                        (f2ptr cause, f2ptr this, f2ptr object);
f2ptr raw__semantic_realm__key_count                         (f2ptr cause, f2ptr this);
f2ptr  f2__semantic_realm__key_count                         (f2ptr cause, f2ptr this);
f2ptr raw__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr  f2__semantic_realm__lookup_or_create_meta_relationship(f2ptr cause, f2ptr this, f2ptr semantic_frame, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr raw__semantic_realm__add_semantic_knowledge_base       (f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base);
f2ptr  f2__semantic_realm__add_semantic_knowledge_base       (f2ptr cause, f2ptr this, f2ptr semantic_knowledge_base);
f2ptr raw__semantic_realm__lookup_semantic_knowledge_base    (f2ptr cause, f2ptr this, f2ptr name);
f2ptr  f2__semantic_realm__lookup_semantic_knowledge_base    (f2ptr cause, f2ptr this, f2ptr name);
f2ptr raw__semantic_realm__add_phenomenon_semantic_frame     (f2ptr cause, f2ptr this, f2ptr phenomenon, f2ptr semantic_frame);
f2ptr  f2__semantic_realm__add_phenomenon_semantic_frame     (f2ptr cause, f2ptr this, f2ptr phenomenon, f2ptr semantic_frame);
f2ptr raw__semantic_realm__lookup_phenomenon_semantic_frame  (f2ptr cause, f2ptr this, f2ptr phenomenon);
f2ptr  f2__semantic_realm__lookup_phenomenon_semantic_frame  (f2ptr cause, f2ptr this, f2ptr phenomenon);
f2ptr raw__semantic_realm__terminal_print_with_frame         (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__semantic_realm__terminal_print_with_frame         (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_realm_type__new_aux(f2ptr cause);



// **

f2ptr f2__semantic_realm__core_extension__ping        (f2ptr cause);
f2ptr f2__semantic_realm__core_extension__initialize  (f2ptr cause);
f2ptr f2__semantic_realm__core_extension__define_types(f2ptr cause);
f2ptr f2__semantic_realm__core_extension__destroy     (f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_REALM__H


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

#ifndef F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H
#define F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H


// semantic_realm

f2ptr     raw__semantic_realm__new                      (f2ptr cause);
f2ptr      f2__semantic_realm__new                      (f2ptr cause);
boolean_t raw__semantic_realm__is_type                  (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_realm__is_type                  (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_realm__type                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__type                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__semantic_hash            (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__semantic_hash            (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__semantic_hash__set       (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_realm__semantic_hash__set       (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_realm__lookup_object_key        (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__semantic_realm__lookup_object_key        (f2ptr cause, f2ptr this, f2ptr object);
f2ptr     raw__semantic_realm__add_object_key           (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__semantic_realm__add_object_key           (f2ptr cause, f2ptr this, f2ptr object);
f2ptr     raw__semantic_realm__object_key               (f2ptr cause, f2ptr this, f2ptr object);
f2ptr      f2__semantic_realm__object_key               (f2ptr cause, f2ptr this, f2ptr object);
f2ptr     raw__semantic_realm__key_count                (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_realm__key_count                (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_realm__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__semantic_realm__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__semantic_realm_type__new(f2ptr cause);




// semantic_frame

f2ptr     raw__semantic_frame__new       (f2ptr cause, f2ptr realm);
f2ptr      f2__semantic_frame__new       (f2ptr cause, f2ptr realm);
boolean_t raw__semantic_frame__is_type   (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame__is_type   (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame__type      (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__type      (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__realm     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__realm     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__realm__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__realm__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__frame     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame__frame     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame__frame__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame__frame__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame__add       (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr      f2__semantic_frame__add       (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key, f2ptr value);
f2ptr     raw__semantic_frame__lookup    (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);
f2ptr      f2__semantic_frame__lookup    (f2ptr cause, f2ptr this, f2ptr key_type, f2ptr key);

f2ptr f2__semantic_frame_type__new(f2ptr cause);

#define semantic_frame__iteration(cause, this, key_type_name, key_name, slot_value, code) { \
    frame__iteration(cause, this, key_type_name, key_name, semantic_frame__iteration__slot_values, \
		     f2ptr semantic_frame__iteration__slot_value__iter = semantic_frame__iteration__slot_values; \
		     while (semantic_frame__iteration__slot_value__iter != nil) { \
		       f2ptr slot_value = f2__cons__car(cause, semantic_frame__iteration__slot_value__iter); \
		       {						\
			 code;						\
		       }						\
		       semantic_frame__iteration__slot_value__iter = f2__cons__cdr(cause, semantic_frame__iteration__slot_value__iter); \
		     }							\
		     );							\
  }



// semantic_knowledge_base

f2ptr     raw__semantic_knowledge_base__new                 (f2ptr cause, f2ptr semantic_frames);
f2ptr      f2__semantic_knowledge_base__new                 (f2ptr cause, f2ptr semantic_frames);
boolean_t raw__semantic_knowledge_base__is_type             (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_knowledge_base__is_type             (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_knowledge_base__type                (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__type                (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__semantic_frames     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__semantic_frames     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_knowledge_base__semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_knowledge_base__as__graph           (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_knowledge_base__as__graph           (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_knowledge_base__add_semantic_frame  (f2ptr cause, f2ptr this, f2ptr semantic_frame);
f2ptr      f2__semantic_knowledge_base__add_semantic_frame  (f2ptr cause, f2ptr this, f2ptr semantic_frame);

f2ptr f2__semantic_knowledge_base_type__new(f2ptr cause);


// noun_semantic_frame

f2ptr     raw__noun_semantic_frame__new            (f2ptr cause, f2ptr realm);
f2ptr      f2__noun_semantic_frame__new            (f2ptr cause, f2ptr realm);
boolean_t raw__noun_semantic_frame__is_type        (f2ptr cause, f2ptr thing);
f2ptr      f2__noun_semantic_frame__is_type        (f2ptr cause, f2ptr thing);
f2ptr     raw__noun_semantic_frame__type           (f2ptr cause, f2ptr this);
f2ptr      f2__noun_semantic_frame__type           (f2ptr cause, f2ptr this);
f2ptr     raw__noun_semantic_frame__add_noun       (f2ptr cause, f2ptr this, f2ptr noun);
f2ptr      f2__noun_semantic_frame__add_noun       (f2ptr cause, f2ptr this, f2ptr noun);
f2ptr     raw__noun_semantic_frame__add_classifier (f2ptr cause, f2ptr this, f2ptr classifier);
f2ptr      f2__noun_semantic_frame__add_classifier (f2ptr cause, f2ptr this, f2ptr classifier);
f2ptr     raw__noun_semantic_frame__add_adjective  (f2ptr cause, f2ptr this, f2ptr adjective);
f2ptr      f2__noun_semantic_frame__add_adjective  (f2ptr cause, f2ptr this, f2ptr adjective);
f2ptr     raw__noun_semantic_frame__add_preposition(f2ptr cause, f2ptr this, f2ptr preposition, f2ptr semantic_object);
f2ptr      f2__noun_semantic_frame__add_preposition(f2ptr cause, f2ptr this, f2ptr preposition, f2ptr semantic_object);

f2ptr f2__noun_semantic_frame_type__new(f2ptr cause);


// visual_object_semantic_frame

f2ptr     raw__visual_object_semantic_frame__new                   (f2ptr cause, f2ptr realm);
f2ptr      f2__visual_object_semantic_frame__new                   (f2ptr cause, f2ptr realm);
boolean_t raw__visual_object_semantic_frame__is_type               (f2ptr cause, f2ptr thing);
f2ptr      f2__visual_object_semantic_frame__is_type               (f2ptr cause, f2ptr thing);
f2ptr     raw__visual_object_semantic_frame__type                  (f2ptr cause, f2ptr this);
f2ptr      f2__visual_object_semantic_frame__type                  (f2ptr cause, f2ptr this);
f2ptr     raw__visual_object_semantic_frame__add_visual_object_name(f2ptr cause, f2ptr this, f2ptr visual_object_name);
f2ptr      f2__visual_object_semantic_frame__add_visual_object_name(f2ptr cause, f2ptr this, f2ptr visual_object_name);

f2ptr f2__visual_object_semantic_frame_type__new(f2ptr cause);

// **

f2ptr f2__semantic_knowledge_base__core_extension_ping(f2ptr cause);
f2ptr f2__semantic_knowledge_base__core_extension_initialize(f2ptr cause);
f2ptr f2__semantic_knowledge_base__core_extension_destroy(f2ptr cause);




#endif // F2__EXTENSION__SEMANTIC_KNOWLEDGE_BASE__H


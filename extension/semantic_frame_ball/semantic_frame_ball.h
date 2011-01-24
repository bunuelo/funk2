// 
// Copyright (c) 2007-2011 Bo Morgan.
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

#ifndef F2__EXTENSION__SEMANTIC_FRAME_BALL__H
#define F2__EXTENSION__SEMANTIC_FRAME_BALL__H

boolean_t raw__semantic_frame__ball_size_is_less_than_with_ptypehash(f2ptr cause, f2ptr this, f2ptr ptypehash, s64 maximum_size, s64* exact_size);
boolean_t raw__semantic_frame__ball_size_is_less_than(f2ptr cause, f2ptr this, s64 maximum_size, s64* possibly_null_exact_size);
boolean_t raw__semantic_frame__wishes_to_be_a_baller(f2ptr cause, f2ptr this);
f2ptr raw__semantic_frame__copy_recursively_with_ptypehash(f2ptr cause, f2ptr this, f2ptr ptypehash);



// semantic_frame_ball

f2ptr     raw__semantic_frame_ball__new                      (f2ptr cause, f2ptr user_root_semantic_frames);
f2ptr      f2__semantic_frame_ball__new                      (f2ptr cause, f2ptr root_semantic_frames);
boolean_t raw__semantic_frame_ball__is_type                  (f2ptr cause, f2ptr thing);
f2ptr      f2__semantic_frame_ball__is_type                  (f2ptr cause, f2ptr thing);
f2ptr     raw__semantic_frame_ball__type                     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_ball__type                     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_ball__root_semantic_frames     (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_ball__root_semantic_frames     (f2ptr cause, f2ptr this);
f2ptr     raw__semantic_frame_ball__root_semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__semantic_frame_ball__root_semantic_frames__set(f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__semantic_frame_ball__as__graph                (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_ball__as__graph                (f2ptr cause, f2ptr this);
f2ptr      f2__semantic_frame_ball_type__new                 (f2ptr cause);



// **

f2ptr f2__semantic_frame_ball__core_extension_ping(f2ptr cause);
f2ptr f2__semantic_frame_ball__core_extension_initialize(f2ptr cause);
f2ptr f2__semantic_frame_ball__core_extension_destroy(f2ptr cause);

#endif // F2__EXTENSION__SEMANTIC_FRAME_BALL__H


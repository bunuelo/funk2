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

#ifndef F2__EXTENSION__TRANSFRAME__H
#define F2__EXTENSION__TRANSFRAME__H

#include "../../c/funk2.h"
#include "../semantic_frame/semantic_frame.h"
#include "../semantic_knowledge_base/semantic_knowledge_base.h"

def_header_ceframe5(transframe_change, change_type, change_object, change_slot_type, change_slot, change_target);

f2ptr raw__transframe_change__new(f2ptr cause, f2ptr change_type, f2ptr change_object, f2ptr change_slot_type, f2ptr change_slot, f2ptr change_target);
f2ptr f2__transframe_change__new(f2ptr cause, f2ptr change_type, f2ptr change_object, f2ptr change_slot_type, f2ptr change_slot, f2ptr change_target);

f2ptr f2__transframe_change_type__new_aux(f2ptr cause);


def_header_ceframe1(transframe, change_set);

f2ptr     raw__transframe__new(f2ptr cause);
f2ptr      f2__transframe__new(f2ptr cause);

f2ptr f2__transframe_type__new_aux(f2ptr cause);


// **

f2ptr f2__transframe__core_extension__ping      (f2ptr cause);
f2ptr f2__transframe__core_extension__initialize(f2ptr cause);
f2ptr f2__transframe__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__TRANSFRAME__H


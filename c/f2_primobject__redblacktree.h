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

#ifndef F2__PRIMOBJECT__REDBLACKTREE__TYPES__H
#define F2__PRIMOBJECT__REDBLACKTREE__TYPES__H

// redblacktree

typedef struct funk2_object_type__redblacktree__slot_s funk2_object_type__redblacktree__slot_t;
declare_object_type_1_slot(redblacktree, head, );

// redblacktree_node

typedef struct funk2_object_type__redblacktree_node__slot_s funk2_object_type__redblacktree_node__slot_t;
declare_object_type_5_slot(redblacktree_node, parent, left, right, color, key, );

#endif // F2__PRIMOBJECT__REDBLACKTREE__TYPES__H

#ifndef F2__PRIMOBJECT__REDBLACKTREE__H
#define F2__PRIMOBJECT__REDBLACKTREE__H

#include "f2_primobjects.h"

// redblacktree

declare_primobject_1_slot(redblacktree, head);

f2ptr raw__redblacktree__new(f2ptr cause, f2ptr head);
f2ptr  f2__redblacktree__new(f2ptr cause);

f2ptr f2redblacktree__primobject_type__new(f2ptr cause);

// redblacktree_node

declare_primobject_5_slot(redblacktree_node, parent, left, right, color, key);

f2ptr raw__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color, f2ptr key);
f2ptr  f2__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color, f2ptr key);

f2ptr f2redblacktree_node__primobject_type__new(f2ptr cause);

// **

void f2__primobject__redblacktree__reinitialize_globalvars();
void f2__primobject__redblacktree__initialize();

#endif // F2__PRIMOBJECT__REDBLACKTREE__H



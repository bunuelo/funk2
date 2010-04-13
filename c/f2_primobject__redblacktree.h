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
declare_object_type_2_slot(redblacktree, head, comparison_funk, );

// redblacktree_node

typedef struct funk2_object_type__redblacktree_node__slot_s funk2_object_type__redblacktree_node__slot_t;
declare_object_type_5_slot(redblacktree_node, parent, left, right, color, key, );

#endif // F2__PRIMOBJECT__REDBLACKTREE__TYPES__H

#ifndef F2__PRIMOBJECT__REDBLACKTREE__H
#define F2__PRIMOBJECT__REDBLACKTREE__H

#include "f2_primobjects.h"

// redblacktree

declare_primobject_2_slot(redblacktree, head, comparison_funk);

#define redblacktree__iteration_forward_by_node(cause, this, node, code) \
  {									\
    f2ptr node = f2__redblacktree__minimum_node(cause, this);		\
    while (node) {							\
      {									\
	code;								\
      }									\
      node = raw__redblacktree_node__next(cause, node);	\
    }									\
  }

#define redblacktree__iteration_forward(cause, this, key, code) \
  redblacktree__iteration_forward_by_node(cause, this, redblacktree_node, \
					  f2ptr key = f2__redblacktree_node__key(cause, redblacktree_node); \
					  {				\
					    code;			\
					  }				\
					  )

#define redblacktree__iteration(cause, this, key, code) \
  redblacktree__iteration_forward(cause, this, key, code)

#define redblacktree__iteration_backward_by_node(cause, this, node, code) \
  {									\
    f2ptr node = f2__redblacktree__maximum_node(cause, this);		\
    while (node) {							\
      {									\
	code;								\
      }									\
      node = raw__redblacktree_node__prev(cause, node);	\
    }									\
  }

#define redblacktree__iteration_backward(cause, this, key, code)	\
  redblacktree__iteration_backward_by_node(cause, this, redblacktree_node, \
					   f2ptr key = f2__redblacktree_node__key(cause, redblacktree_node); \
					   {				\
					     code;			\
					   }				\
					   )

f2ptr raw__redblacktree__new(    f2ptr cause, f2ptr head, f2ptr comparison_funk);
f2ptr  f2__redblacktree__new(    f2ptr cause, f2ptr comparison_funk);
f2ptr raw__redblacktree__insert( f2ptr cause, f2ptr this, f2ptr key);
f2ptr  f2__redblacktree__insert( f2ptr cause, f2ptr this, f2ptr key);
f2ptr raw__redblacktree__remove( f2ptr cause, f2ptr this, f2ptr key);
f2ptr  f2__redblacktree__remove( f2ptr cause, f2ptr this, f2ptr key);
f2ptr raw__redblacktree__minimum(f2ptr cause, f2ptr this);
f2ptr  f2__redblacktree__minimum(f2ptr cause, f2ptr this);
f2ptr raw__redblacktree__maximum(f2ptr cause, f2ptr this);
f2ptr  f2__redblacktree__maximum(f2ptr cause, f2ptr this);
f2ptr raw__redblacktree__leaves( f2ptr cause, f2ptr this);
f2ptr  f2__redblacktree__leaves( f2ptr cause, f2ptr this);
u64   raw__redblacktree__size(   f2ptr cause, f2ptr this);
f2ptr  f2__redblacktree__size(   f2ptr cause, f2ptr this);

f2ptr f2redblacktree__primobject_type__new(f2ptr cause);

// redblacktree_node

declare_primobject_5_slot(redblacktree_node, parent, left, right, color, key);

f2ptr f2redblacktree_node__primobject_type__new(f2ptr cause);

// **

void f2__primobject__redblacktree__reinitialize_globalvars();
void f2__primobject__redblacktree__initialize();

#endif // F2__PRIMOBJECT__REDBLACKTREE__H



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

#include "funk2.h"

// interval_tree

def_primobject_9_slot(interval_tree, mutate_cmutex, head, all_left_redblacktree, all_right_redblacktree, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);

f2ptr raw__interval_tree__new(f2ptr cause, f2ptr head, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr mutate_cmutex          = f2__cmutex__new(cause);
  f2ptr all_left_redblacktree  = f2__redblacktree__new(cause, left_value_funk,  value_comparison_funk);
  f2ptr all_right_redblacktree = f2__redblacktree__new(cause, right_value_funk, value_comparison_funk);
  return f2interval_tree__new(cause,
			      mutate_cmutex,
			      head,
			      all_left_redblacktree,
			      all_right_redblacktree,
			      left_value_funk,
			      right_value_funk,
			      value_equality_funk,
			      value_comparison_funk,
			      value_center_funk);
}

f2ptr f2__interval_tree__new(f2ptr cause, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  return raw__interval_tree__new(cause, nil, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
def_pcfunk5(interval_tree__new, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk,
	    "Returns a new interval_tree object.",
	    return f2__interval_tree__new(this_cause, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));


f2ptr raw__interval_tree__insert__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr head                   = f2__interval_tree__head(cause, this);
  f2ptr left_value_funk        = f2__interval_tree__left_value_funk(       cause, this);
  f2ptr right_value_funk       = f2__interval_tree__right_value_funk(      cause, this);
  f2ptr value_equality_funk    = f2__interval_tree__value_equality_funk(   cause, this);
  f2ptr value_comparison_funk  = f2__interval_tree__value_comparison_funk( cause, this);
  f2ptr value_center_funk      = f2__interval_tree__value_center_funk(     cause, this);
  f2ptr all_left_redblacktree  = f2__interval_tree__all_left_redblacktree( cause, this);
  f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
  
  f2ptr left_value            = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, element)));
  f2ptr right_value           = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, element)));
  f2ptr left_right_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, left_value, right_value)));
  f2ptr left_right_equality   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, left_value, right_value)));
  if ((left_right_comparison == nil) &&
      (left_right_equality   == nil)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "element_left_is_greater_than_element_right"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "element"),  element));
  }
  
  assert_value(f2__redblacktree__insert(cause, all_left_redblacktree,  element));
  assert_value(f2__redblacktree__insert(cause, all_right_redblacktree, element));
  if (head == nil) {
    f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, left_value, right_value)));
    head = f2__interval_tree_node__new(cause, nil, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
    f2__interval_tree__head__set(cause, this, head);
  }
  assert_value(raw__interval_tree_node__insert(cause, head, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  do {
    f2ptr head__parent_node = f2__interval_tree_node__parent_node(cause, head);
    if (head__parent_node == nil) {
      break;
    }
    head = head__parent_node;
  } while (1);
  f2__interval_tree__head__set(cause, this, head);
  return nil;
}

f2ptr raw__interval_tree__insert(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__insert__thread_unsafe(cause, this, element);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__insert(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__insert(cause, this, element);
}
def_pcfunk2(interval_tree__insert, this, element,
	    "Inserts a new interval element into this interval_tree.",
	    return f2__interval_tree__insert(this_cause, this, element));


f2ptr raw__interval_tree__remove__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr all_left_redblacktree  = f2__interval_tree__all_left_redblacktree( cause, this);
  f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
  assert_value(raw__redblacktree__remove(cause, all_left_redblacktree,  element));
  assert_value(raw__redblacktree__remove(cause, all_right_redblacktree, element));
  f2ptr head = f2__interval_tree__head(cause, this);
  if (head == nil) {
    return f2larva__new(cause, 23516, nil);
  }
  f2ptr left_value_funk       = f2__interval_tree__left_value_funk(      cause, this);
  f2ptr right_value_funk      = f2__interval_tree__right_value_funk(     cause, this);
  f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(  cause, this);
  f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
  // we could check the returned removed_from_node from the simple_remove command, and do the red-black tree deletion cases here.
  f2ptr remove_node = assert_value(raw__interval_tree_node__simple_remove(cause, head, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
  if (raw__interval_tree_node__is_empty(cause, remove_node)) {
    printf("\nbleh.");
  }
  return nil;
}

f2ptr raw__interval_tree__remove(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__remove__thread_unsafe(cause, this, element);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__remove(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__remove(cause, this, element);
}
def_pcfunk2(interval_tree__remove, this, element,
	    "Removes an interval element from this interval_tree.",
	    return f2__interval_tree__remove(this_cause, this, element));


///vvvvv

void raw__interval_tree__remove_node_with_at_most_one_child(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node__child  = (f2__interval_tree_node__left_node(cause, node) != nil) ? f2__interval_tree_node__left_node(cause, node) : f2__interval_tree_node__right_node(cause, node);
  f2ptr node__parent = f2__interval_tree_node__parent_node(cause, node);
  f2ptr node__left   = f2__interval_tree_node__left_node(  cause, node);
  f2ptr node__right  = f2__interval_tree_node__right_node( cause, node);
  if (node__left == nil) { 
    if (node__parent) {
      if (f2__interval_tree_node__right_node(cause, node__parent) == node) {
	f2__interval_tree_node__right_node__set(cause, node__parent, node__right);
	if (node__right) {
	  f2__interval_tree_node__parent_node__set(cause, node__right, node__parent);
	}
      } else {
	f2__interval_tree_node__left_node__set(cause, node__parent, node__right);
	if (node__right) {
	  f2__interval_tree_node__parent_node__set(cause, node__right, node__parent);
	}
      }
    } else {
      f2__interval_tree__head__set(cause, this, node__right);
      if (node__right) {
	f2__interval_tree_node__parent_node__set(cause, node__right, nil);
      }
    }
  } else { // (node->right == NULL)
    if (node__parent) {
      if (f2__interval_tree_node__right_node(cause, node__parent) == node) {
	f2__interval_tree_node__right_node__set(cause, node__parent, node__left);
	if (node__left) {
	  f2__interval_tree_node__parent_node__set(cause, node__left, node__parent);
	}
      } else {
	f2__interval_tree_node__left_node__set(cause, node__parent, node__left);
	if (node__left) {
	  f2__interval_tree_node__parent_node__set(cause, node__left, node__parent);
	}
      }
    } else {
      f2__interval_tree__head__set(cause, this, node__left);
      if (node__left) {
	f2__interval_tree_node__parent_node__set(cause, node__left, nil);
      }
    }
  }
  
  if (node__child) {
    if (raw__eq(cause, f2__interval_tree_node__color(cause, node), new__symbol(cause, "black"))) {
      if (raw__eq(cause, f2__interval_tree_node__color(cause, node__child), new__symbol(cause, "red"))) {
	f2__interval_tree_node__color__set(cause, node__child, new__symbol(cause, "black"));
      } else {
	f2ptr left_value_funk       = f2__interval_tree__left_value_funk(cause, this);
	f2ptr right_value_funk      = f2__interval_tree__right_value_funk(cause, this);
	f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(cause, this);
	f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
	f2ptr value_center_funk     = f2__interval_tree__value_center_funk(cause, this);
	raw__interval_tree_node__delete_case_1(cause, node__child, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
      }
    }
  }
}

void raw__interval_tree__remove_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (f2__interval_tree_node__left_node(cause, node) == nil || f2__interval_tree_node__right_node(cause, node) == nil) { 
    raw__interval_tree__remove_node_with_at_most_one_child(cause, this, node);
  } else {
    f2ptr node__left__max = raw__interval_tree_node__maximum_node(cause, f2__interval_tree_node__left_node(cause, node));
    
    //debug__assert(f2__interval_tree_node__right_node(cause, node__left__max) == nil, nil, "interval_tree_node__remove_node: (node__left__max->right == NULL) failed.");
    
    raw__interval_tree_node__swap_nodes(cause, node__left__max, node);
    
    raw__interval_tree__remove_node_with_at_most_one_child(cause, this, node);
    
    if (f2__interval_tree_node__parent_node(cause, node__left__max) == nil) {
      f2__interval_tree__head__set(cause, this, node__left__max);
    }
  }
  
  f2__interval_tree__head__set(cause, this, raw__interval_tree_node__head(cause, f2__interval_tree__head(cause, this))); 
  
  if (f2__interval_tree__head(cause, this) != nil) {
    if (raw__eq(cause, f2__interval_tree_node__color(cause, f2__interval_tree__head(cause, this)), new__symbol(cause, "red"))) {
      f2__interval_tree_node__color__set(cause, f2__interval_tree__head(cause, this), new__symbol(cause, "black"));
    }
  }
  
  //#ifdef DEBUG_REDBLACKTREE
  //debug__assert(! raw__interval_tree__contains_node(this, node), nil, "raw__interval_tree__remove_node failed: tree still contains node.");
  //#endif
}

///^^^^


f2ptr raw__interval_tree__intervals__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr all_left_redblacktree = f2__interval_tree__all_left_redblacktree(cause, this);
  return raw__redblacktree__leaves(cause, all_left_redblacktree);
}

f2ptr raw__interval_tree__intervals(f2ptr cause, f2ptr this) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__intervals__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__intervals(f2ptr cause, f2ptr this) {
  return raw__interval_tree__intervals(cause, this);
}
def_pcfunk1(interval_tree__intervals, this,
	    "Returns all of the intervals in this interval_tree.",
	    return f2__interval_tree__intervals(this_cause, this));


f2ptr raw__interval_tree__add_intervals_containing_value_to_list__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value, f2ptr list) {
  f2ptr head = f2__interval_tree__head(cause, this);
  if (head != nil) {
    f2ptr left_value_funk       = f2__interval_tree__left_value_funk(      cause, this);
    f2ptr right_value_funk      = f2__interval_tree__right_value_funk(     cause, this);
    f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
    f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(  cause, this);
    assert_value(raw__interval_tree_node__add_intervals_containing_value_to_list(cause, head, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
  }
  return nil;
}

f2ptr raw__interval_tree__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__add_intervals_containing_value_to_list__thread_unsafe(cause, this, value, list);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list) {
  assert_argument_type(interval_tree, this);
  assert_argument_type(set,           list);
  return raw__interval_tree__add_intervals_containing_value_to_list(cause, this, value, list);
}
def_pcfunk3(interval_tree__add_intervals_containing_value_to_list, this, value, list,
	    "Adds intervals from this interval_tree that contain the given value to the given list.",
	    return f2__interval_tree__add_intervals_containing_value_to_list(this_cause, this, value, list));


f2ptr raw__interval_tree__intervals_containing_value__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr list = f2__list__new(cause, nil);
  assert_value(raw__interval_tree__add_intervals_containing_value_to_list(cause, this, value, list));
  return list;
}

f2ptr raw__interval_tree__intervals_containing_value(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__intervals_containing_value__thread_unsafe(cause, this, value);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__intervals_containing_value(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__intervals_containing_value(cause, this, value);
}
def_pcfunk2(interval_tree__intervals_containing_value, this, value,
	    "Returns a new set that contains the intervals in this interval_tree that contain the given value.",
	    return f2__interval_tree__intervals_containing_value(this_cause, this, value));


f2ptr raw__interval_tree__intervals_overlapping_interval__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr list = f2__list__new(cause, nil);
  {
    f2ptr all_left_redblacktree  = f2__interval_tree__all_left_redblacktree( cause, this);
    f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
    f2ptr left_value_funk        = f2__interval_tree__left_value_funk(       cause, this);
    f2ptr right_value_funk       = f2__interval_tree__right_value_funk(      cause, this);
    f2ptr value_equality_funk    = f2__interval_tree__value_equality_funk(   cause, this);
    f2ptr value_comparison_funk  = f2__interval_tree__value_comparison_funk( cause, this);
    f2ptr element__left_value    = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,  f2list1__new(cause, element)));
    f2ptr element__right_value   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk, f2list1__new(cause, element)));
    {
      f2ptr redblacktree_node = raw__redblacktree__minimum_not_less_than__node(cause, all_left_redblacktree, element__left_value);
      while (redblacktree_node != nil) {
	f2ptr redblacktree_node__count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, redblacktree_node);
	f2ptr redblacktree_node__element             = f2__ptypehash__an_arbitrary_key(cause, redblacktree_node__count_key_ptypehash);
	f2ptr redblacktree_node__element__left_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, redblacktree_node__element)));
	f2ptr equality                               = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, redblacktree_node__element__left_value, element__right_value)));
	f2ptr comparison                             = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, redblacktree_node__element__left_value, element__right_value)));
	if ((equality != nil) || (comparison != nil)) {
	  ptypehash__iteration(cause, redblacktree_node__count_key_ptypehash, element_iter, count,
			       s64 count__i = f2integer__i(count, cause);
			       {
				 s64 index;
				 for (index = 0; index < count__i; index ++) {
				   raw__list__add(cause, list, element_iter);
				 }
			       }
			       );
	} else {
	  break;
	}
	redblacktree_node = raw__redblacktree_node__next(cause, redblacktree_node);
      }
    }
    {
      f2ptr redblacktree_node = raw__redblacktree__minimum_not_less_than__node(cause, all_right_redblacktree, element__left_value);
      while (redblacktree_node != nil) {
	f2ptr redblacktree_node__count_key_ptypehash  = f2__redblacktree_node__count_key_ptypehash(cause, redblacktree_node);
	f2ptr redblacktree_node__element              = f2__ptypehash__an_arbitrary_key(cause, redblacktree_node__count_key_ptypehash);
	f2ptr redblacktree_node__element__right_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, redblacktree_node__element)));
	f2ptr equality                                = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, redblacktree_node__element__right_value, element__right_value)));
	f2ptr comparison                              = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, redblacktree_node__element__right_value, element__right_value)));
	if ((equality != nil) || (comparison != nil)) {
	  ptypehash__iteration(cause, redblacktree_node__count_key_ptypehash, element_iter, count,
			       s64 count__i = f2integer__i(count, cause);
			       {
				 s64 index;
				 for (index = 0; index < count__i; index ++) {
				   raw__list__add(cause, list, element_iter);
				 }
			       }
			       );
	} else {
	  break;
	}
	redblacktree_node = raw__redblacktree_node__next(cause, redblacktree_node);
      }
    }
    f2ptr value_center_funk     = f2__interval_tree__value_center_funk(cause, this);
    f2ptr element__center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, element__left_value, element__right_value)));
    assert_value(raw__interval_tree__add_intervals_containing_value_to_list(cause, this, element__center_value, list));
  }
  return list;
}

f2ptr raw__interval_tree__intervals_overlapping_interval(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__intervals_overlapping_interval__thread_unsafe(cause, this, element);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__intervals_overlapping_interval(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__intervals_overlapping_interval(cause, this, element);
}
def_pcfunk2(interval_tree__intervals_overlapping_interval, this, element,
	    "Returns a new set that contains the intervals in this interval_tree that overlap with the given interval.",
	    return f2__interval_tree__intervals_overlapping_interval(this_cause, this, element));


f2ptr raw__interval_tree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "interval_tree"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "intervals"),         f2__interval_tree__intervals(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__interval_tree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(interval_tree,        this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__interval_tree__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(interval_tree__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__interval_tree__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2interval_tree__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2interval_tree__primobject_type__new(cause);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                                 __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.insert__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove"),                                 __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.remove__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "intervals"),                              __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_intervals_containing_value_to_list"), __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.add_intervals_containing_value_to_list__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "intervals_containing_value"),             __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals_containing_value__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "intervals_overlapping_interval"),         __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals_overlapping_interval__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),              __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.terminal_print_with_frame__funk);
  return this;
}


// interval_tree_node

def_primobject_7_slot(interval_tree_node, color, center_value, parent_node, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);

f2ptr raw__interval_tree_node__new(f2ptr cause, f2ptr color, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  f2ptr parent_node                    = nil;
  f2ptr left_node                      = nil;
  f2ptr right_node                     = nil;
  f2ptr overlapping_left_redblacktree  = f2__redblacktree__new(cause, left_value_funk,  value_comparison_funk);
  f2ptr overlapping_right_redblacktree = f2__redblacktree__new(cause, right_value_funk, value_comparison_funk);
  return f2interval_tree_node__new(cause,
				   color,
				   center_value,
				   parent_node,
				   left_node,
				   right_node,
				   overlapping_left_redblacktree,
				   overlapping_right_redblacktree);
}

f2ptr f2__interval_tree_node__new(f2ptr cause, f2ptr color, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  return raw__interval_tree_node__new(cause, color, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
}
def_pcfunk6(interval_tree_node__new, color, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk,
	    "Returns a new interval_tree_node object.",
	    return f2__interval_tree_node__new(this_cause, color, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));


f2ptr raw__interval_tree_node__assert_valid(f2ptr cause, f2ptr this) {
  { // make sure overlapping_left_redblacktree and overlapping_right_redblacktree have the same elements.
    f2ptr overlapping_left_redblacktree  = f2__interval_tree_node__overlapping_left_redblacktree( cause, this);
    f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
    f2ptr left_element_set  = f2__set__new(cause);
    f2ptr right_element_set = f2__set__new(cause);
    redblacktree__iteration(cause, overlapping_left_redblacktree, element,
			    raw__set__add(cause, left_element_set, element);
			    );
    redblacktree__iteration(cause, overlapping_right_redblacktree, element,
			    raw__set__add(cause, right_element_set, element);
			    );
    set__iteration(cause, left_element_set, element,
		   if (! raw__set__contains(cause, right_element_set, element)) {
		     return new__error(f2list4__new(cause,
						    new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_node_failed_validity_assertion"),
						    new__symbol(cause, "this"),     this));
		   }
		   );
    set__iteration(cause, right_element_set, element,
		   if (! raw__set__contains(cause, left_element_set, element)) {
		     return new__error(f2list4__new(cause,
						    new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_node_failed_validity_assertion"),
						    new__symbol(cause, "this"),     this));
		   }
		   );
  }
  { // 
    
  }
  return nil;
}

f2ptr f2__interval_tree_node__assert_valid(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__assert_valid(cause, this);
}

#define F2__DEBUG__INTERVAL_TREE_NODE 1


boolean_t raw__interval_tree_node__is_empty(f2ptr cause, f2ptr this) {
  f2ptr overlapping_left_redblacktree  = f2__interval_tree_node__overlapping_left_redblacktree( cause, this);
  return raw__redblacktree__is_empty(cause, overlapping_left_redblacktree);
}


f2ptr raw__interval_tree_node__simple_insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr center_value            = f2__interval_tree_node__center_value(cause, this);
  f2ptr left_value              = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, element)));
  f2ptr right_value             = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, element)));
  f2ptr left_center_equality    = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, left_value,   center_value)));
  f2ptr center_right_equality   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, center_value, right_value)));
  f2ptr left_center_comparison  = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, left_value,   center_value)));
  f2ptr center_right_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, center_value, right_value)));
  if ((left_center_equality  != nil) ||
      (center_right_equality != nil) ||
      ((left_center_comparison != nil) && (center_right_comparison != nil))) {
    // interval overlaps with center value of this node
    f2ptr overlapping_left_redblacktree  = f2__interval_tree_node__overlapping_left_redblacktree( cause, this);
    f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    assert_value(f2__redblacktree__insert(cause, overlapping_left_redblacktree,  element));
    assert_value(f2__redblacktree__insert(cause, overlapping_right_redblacktree, element));
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    return this;
  } else {
    f2ptr right_center_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, right_value, center_value)));
    if (right_center_comparison != nil) {
      // interval is completely to the left of the center value of this node
      f2ptr left_node = f2__interval_tree_node__left_node(cause, this);
      if (left_node == nil) {
	f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, left_value, right_value)));
	left_node = f2__interval_tree_node__new(cause, nil, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
	f2__interval_tree_node__parent_node__set(cause, left_node, this);
	f2__interval_tree_node__left_node__set(  cause, this,      left_node);
      }
      return raw__interval_tree_node__simple_insert(cause, left_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
    } else {
      // interval is completely to the right of the center value of this node
      f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
      if (right_node == nil) {
	f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, left_value, right_value)));
	right_node = f2__interval_tree_node__new(cause, nil, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
	f2__interval_tree_node__parent_node__set(cause, right_node, this);
	f2__interval_tree_node__right_node__set( cause, this,       right_node);
      }
      return raw__interval_tree_node__simple_insert(cause, right_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
    }
  }
}

f2ptr f2__interval_tree_node__simple_insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__simple_insert(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
def_pcfunk7(interval_tree_node__simple_insert, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk,
	    "Inserts a new interval element into this interval_tree.",
	    return f2__interval_tree_node__simple_insert(this_cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));


f2ptr raw__interval_tree_node__simple_remove(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  f2ptr center_value            = f2__interval_tree_node__center_value(cause, this);
  f2ptr left_value              = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, element)));
  f2ptr right_value             = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, element)));
  f2ptr left_center_equality    = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, left_value,   center_value)));
  f2ptr center_right_equality   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, center_value, right_value)));
  f2ptr left_center_comparison  = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, left_value,   center_value)));
  f2ptr center_right_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, center_value, right_value)));
  if ((left_center_equality  != nil) ||
      (center_right_equality != nil) ||
      ((left_center_comparison != nil) && (center_right_comparison != nil))) {
    // interval overlaps with center value of this node
    f2ptr overlapping_left_redblacktree  = f2__interval_tree_node__overlapping_left_redblacktree( cause, this);
    f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    assert_value(f2__redblacktree__remove(cause, overlapping_left_redblacktree,  element));
    assert_value(f2__redblacktree__remove(cause, overlapping_right_redblacktree, element));
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    return this;
  } else {
    f2ptr right_center_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, right_value, center_value)));
    if (right_center_comparison != nil) {
      // interval is completely to the left of the center value of this node
      f2ptr left_node = f2__interval_tree_node__left_node(cause, this);
      if (left_node == nil) {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"), new__symbol(cause, "failure_to_find_element"),
				       new__symbol(cause, "this"),     this,
				       new__symbol(cause, "element"),  element));
      }
      return raw__interval_tree_node__simple_remove(cause, left_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
    } else {
      // interval is completely to the right of the center value of this node
      f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
      if (right_node == nil) {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"), new__symbol(cause, "failure_to_find_element"),
				       new__symbol(cause, "this"),     this,
				       new__symbol(cause, "element"),  element));
      }
      return raw__interval_tree_node__simple_remove(cause, right_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
    }
  }
}

f2ptr f2__interval_tree_node__simple_remove(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__simple_remove(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
}
def_pcfunk6(interval_tree_node__simple_remove, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk,
	    "Inserts a new interval element into this interval_tree.",
	    return f2__interval_tree_node__simple_remove(this_cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));


boolean_t raw__interval_tree_node__is_black(f2ptr cause, f2ptr this) {
  if ((this == nil) ||
      (raw__eq(cause, new__symbol(cause, "black"), f2__interval_tree_node__color(cause, this)))) {
    return boolean__true;
  }
  return boolean__false;
}

boolean_t raw__interval_tree_node__is_red(f2ptr cause, f2ptr this) {
  if ((this != nil) &&
      (raw__eq(cause, new__symbol(cause, "red"), f2__interval_tree_node__color(cause, this)))) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr raw__interval_tree_node__grandparent_node(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr parent_node = f2__interval_tree_node__parent_node(cause, this);
  if (parent_node == nil) {
    return nil;
  }
  return f2__interval_tree_node__parent_node(cause, parent_node);
}

f2ptr raw__interval_tree_node__rotate_left(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  //    this                 right    //
  //        \       =>      /         //
  //         right      this          //
  
  f2ptr right_node            = f2__interval_tree_node__right_node(cause, this);
  f2ptr right_node__left_node = f2__interval_tree_node__left_node(cause, right_node);
  
  // before node rotation, we remove elements that will need to be moved up.
  f2ptr move_up_element_list = f2__list__new(cause, nil);
  {
    f2ptr upper_node               = right_node;
    f2ptr lower_node               = this;
    f2ptr upper_node__center_value = f2__interval_tree_node__center_value(cause, upper_node);
    assert_value(raw__interval_tree_node__add_intervals_containing_value_to_list(cause, lower_node, upper_node__center_value, move_up_element_list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
    list__iteration(cause, move_up_element_list, element,
		    catch_value(raw__interval_tree_node__simple_remove(cause, lower_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk),
				f2list4__new(cause,
					     new__symbol(cause, "bug_name"), new__symbol(cause, "bad_value_returned_by_add_intervals_containing_value_could_not_be_found_in_simple_remove"),
					     new__symbol(cause, "this"),     this));
		    );
  }
  
  // begin rotate.
  f2__interval_tree_node__right_node__set(cause, this, right_node__left_node);
  
  if (right_node__left_node != nil) {
    f2__interval_tree_node__parent_node__set(cause, right_node__left_node, this);
  }
  
  f2ptr parent_node = f2__interval_tree_node__parent_node(cause, this);
  f2__interval_tree_node__parent_node__set(cause, right_node, parent_node);
  
  if (parent_node != nil) {
    f2ptr parent_node__left_node = f2__interval_tree_node__left_node(cause, parent_node);
    if (raw__eq(cause, this, parent_node__left_node)) {
      f2__interval_tree_node__left_node__set(cause, parent_node, right_node);
    } else {
      f2__interval_tree_node__right_node__set(cause, parent_node, right_node);
    }
  }
  
  f2__interval_tree_node__left_node__set(  cause, right_node, this);
  f2__interval_tree_node__parent_node__set(cause, this,       right_node);
  // end rotate.
  
  // node rotation is done, so now fix overlapping sets.
  {
    f2ptr upper_node = right_node;
    list__iteration(cause, move_up_element_list, element,
		    assert_value(f2__interval_tree_node__insert(cause, upper_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
		    );
  }
  return nil;
}

f2ptr raw__interval_tree_node__rotate_right(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  //         this      left         //
  //        /      =>      \        //
  //    left                this    //
  
  f2ptr left_node             = f2__interval_tree_node__left_node( cause, this);
  f2ptr left_node__right_node = f2__interval_tree_node__right_node(cause, left_node);
  
  // before node rotation, we remove elements that will need to be moved up.
  f2ptr move_up_element_list = f2__list__new(cause, nil);
  {
    f2ptr upper_node               = left_node;
    f2ptr lower_node               = this;
    f2ptr upper_node__center_value = f2__interval_tree_node__center_value(cause, upper_node);
    assert_value(raw__interval_tree_node__add_intervals_containing_value_to_list(cause, lower_node, upper_node__center_value, move_up_element_list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
    list__iteration(cause, move_up_element_list, element,
		    catch_value(raw__interval_tree_node__simple_remove(cause, lower_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk),
				f2list4__new(cause,
					     new__symbol(cause, "bug_name"), new__symbol(cause, "bad_value_returned_by_add_intervals_containing_value_could_not_be_found_in_simple_remove"),
					     new__symbol(cause, "this"),     this));
		    );
  }
  
  // begin rotate.
  f2__interval_tree_node__left_node__set(cause, this, left_node__right_node);
  
  if (left_node__right_node != nil) {
    f2__interval_tree_node__parent_node__set(cause, left_node__right_node, this);
  }
  
  f2ptr parent_node = f2__interval_tree_node__parent_node(cause, this);
  f2__interval_tree_node__parent_node__set(cause, left_node, parent_node);
  
  if (parent_node != nil) {
    f2ptr parent_node__left_node = f2__interval_tree_node__left_node(cause, parent_node);
    if (raw__eq(cause, this, parent_node__left_node)) {
      f2__interval_tree_node__left_node__set(cause, parent_node, left_node);
    } else {
      f2__interval_tree_node__right_node__set(cause, parent_node, left_node);
    }
  }
  
  f2__interval_tree_node__right_node__set( cause, left_node, this);
  f2__interval_tree_node__parent_node__set(cause, this,      left_node);
  // end rotate.
  
  // node rotation is done, so now fix overlapping sets.
  {
    f2ptr upper_node = left_node;
    list__iteration(cause, move_up_element_list, element,
		    assert_value(f2__interval_tree_node__insert(cause, upper_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
		    );
  }
  return nil;
}


f2ptr raw__interval_tree_node__uncle_node(f2ptr cause, f2ptr this) {
  if (this == nil) {
    error(nil, "cannot get uncle of leaf node.");
  }
  f2ptr grandparent_node = raw__interval_tree_node__grandparent_node(cause, this);
  if (grandparent_node == nil) {
    return nil;
  }
  f2ptr parent_node                  = f2__interval_tree_node__parent_node(cause, this);
  f2ptr grandparent_node__left_node  = f2__interval_tree_node__left_node(  cause, grandparent_node);
  f2ptr grandparent_node__right_node = f2__interval_tree_node__right_node( cause, grandparent_node);
  if (raw__eq(cause, parent_node, grandparent_node__left_node)) {
    return grandparent_node__right_node;
  } else {
    return grandparent_node__left_node;
  }
}


f2ptr raw__interval_tree_node__sibling_node(f2ptr cause, f2ptr node) {
  if (raw__eq(cause, node, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, node)))) {
    return f2__interval_tree_node__right_node(cause, f2__interval_tree_node__parent_node(cause, node));
  } else {
    return f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, node));
  }
}


f2ptr raw__interval_tree_node__head(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter        = this;
  f2ptr parent_node = f2__interval_tree_node__parent_node(cause, this);
  while (parent_node != nil) {
    iter        = parent_node;
    parent_node = f2__interval_tree_node__parent_node(cause, iter);
  }
  return iter;
}


f2ptr raw__interval_tree_node__minimum_node(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter      = this;
  f2ptr left_node = f2__interval_tree_node__left_node(cause, this);
  while (left_node != nil) {
    iter      = left_node;
    left_node = f2__interval_tree_node__left_node(cause, iter);
  }
  return iter;
}


f2ptr raw__interval_tree_node__maximum_node(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter       = this;
  f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
  while (right_node != nil) {
    iter       = right_node;
    right_node = f2__interval_tree_node__right_node(cause, iter);
  }
  return iter;
}


f2ptr raw__interval_tree_node__insert_case_5(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr grandparent_node            = raw__interval_tree_node__grandparent_node(cause, this);
  f2ptr grandparent_node__left_node =  f2__interval_tree_node__left_node(       cause, grandparent_node);
  f2ptr parent_node                 =  f2__interval_tree_node__parent_node(     cause, this);
  f2ptr parent_node__left_node      =  f2__interval_tree_node__left_node(       cause, parent_node);
  f2__interval_tree_node__color__set(cause, parent_node,      new__symbol(cause, "black"));
  f2__interval_tree_node__color__set(cause, grandparent_node, new__symbol(cause, "red"));
  if (raw__eq(cause, this, parent_node__left_node) && raw__eq(cause, parent_node, grandparent_node__left_node)) {
    assert_value(raw__interval_tree_node__rotate_right(cause, grandparent_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  } else { // (raw__eq(cause, this, parent_node__right_node) && raw__eq(cause, parent_node, grandparent_node__right_node)) {
    assert_value(raw__interval_tree_node__rotate_left(cause, grandparent_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr raw__interval_tree_node__insert_case_4(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr grandparent_node             = raw__interval_tree_node__grandparent_node(cause, this);
  f2ptr grandparent_node__left_node  =  f2__interval_tree_node__left_node(       cause, grandparent_node);
  f2ptr grandparent_node__right_node =  f2__interval_tree_node__right_node(      cause, grandparent_node);
  f2ptr parent_node                  =  f2__interval_tree_node__parent_node(     cause, this);
  f2ptr parent_node__right_node      =  f2__interval_tree_node__right_node(      cause, parent_node);
  f2ptr parent_node__left_node       =  f2__interval_tree_node__left_node(       cause, parent_node);
  {
    f2ptr next_node = this;
    if (raw__eq(cause, this, parent_node__right_node) && raw__eq(cause, parent_node, grandparent_node__left_node)) {
      assert_value(raw__interval_tree_node__rotate_left(cause, parent_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
      next_node = f2__interval_tree_node__left_node(cause, this);
    } else if (raw__eq(cause, this, parent_node__left_node)  && raw__eq(cause, parent_node, grandparent_node__right_node)) {
      assert_value(raw__interval_tree_node__rotate_right(cause, parent_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
      next_node = f2__interval_tree_node__right_node(cause, this);
    }
    assert_value(raw__interval_tree_node__insert_case_5(cause, next_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr raw__interval_tree_node__insert_case_3(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr uncle_node = raw__interval_tree_node__uncle_node(cause, this);
  if ((uncle_node != nil) && raw__interval_tree_node__is_red(cause, uncle_node)) {
    f2ptr parent_node      =  f2__interval_tree_node__parent_node(     cause, this);
    f2ptr grandparent_node = raw__interval_tree_node__grandparent_node(cause, this);
    f2__interval_tree_node__color__set(cause, parent_node,      new__symbol(cause, "black"));
    f2__interval_tree_node__color__set(cause, uncle_node,       new__symbol(cause, "black"));
    f2__interval_tree_node__color__set(cause, grandparent_node, new__symbol(cause, "red"));
    assert_value(raw__interval_tree_node__insert_case_1(cause, grandparent_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  } else {
    assert_value(raw__interval_tree_node__insert_case_4(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr raw__interval_tree_node__insert_case_2(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr parent_node = f2__interval_tree_node__parent_node(cause, this);
  if (raw__interval_tree_node__is_black(cause, parent_node)) {
    return nil;
  } else {
    assert_value(raw__interval_tree_node__insert_case_3(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr raw__interval_tree_node__insert_case_1(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr parent_node = f2__interval_tree_node__parent_node(cause, this);
  if (parent_node == nil) {
    f2__interval_tree_node__color__set(cause, this, new__symbol(cause, "black"));
  } else {
    // check insert case 2
    assert_value(raw__interval_tree_node__insert_case_2(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}



f2ptr raw__interval_tree_node__insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr insert_node        = assert_value(raw__interval_tree_node__simple_insert(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  f2ptr insert_node__color = f2__interval_tree_node__color(cause, insert_node);
  if (insert_node__color == nil) {
    // node is new, so we need to check the structure of the red-black tree.
    insert_node__color = new__symbol(cause, "red");
    f2__interval_tree_node__color__set(cause, insert_node, insert_node__color);
    // check insert case 1
    assert_value(raw__interval_tree_node__insert_case_1(cause, insert_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr f2__interval_tree_node__insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__insert(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
def_pcfunk7(interval_tree_node__insert, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk,
	    "Inserts a new interval element into this interval_tree.",
	    return f2__interval_tree_node__insert(this_cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));



///vvvv

void raw__interval_tree_node__delete_case_6(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  f2__interval_tree_node__color__set(cause, this__sibling, f2__interval_tree_node__color(cause, f2__interval_tree_node__parent_node(cause, this)));
  f2__interval_tree_node__color__set(cause, f2__interval_tree_node__parent_node(cause, this), new__symbol(cause, "black"));
  if (raw__eq(cause, this, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, this)))) {
    // Here, this__sibling->right->color == rbt_color__red.
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__right_node(cause, this__sibling), new__symbol(cause, "black"));
    raw__interval_tree_node__rotate_left(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  } else {
    // Here, this__sibling->left->color == rbt_color__red.
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__left_node(cause, this__sibling), new__symbol(cause, "black"));
    raw__interval_tree_node__rotate_right(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  }
}

void raw__interval_tree_node__delete_case_5(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (raw__eq(cause, this, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, this))) &&
      raw__interval_tree_node__is_black(cause, this__sibling) &&
      raw__interval_tree_node__is_red(  cause, f2__interval_tree_node__left_node( cause, this__sibling)) &&
      raw__interval_tree_node__is_black(cause, f2__interval_tree_node__right_node(cause, this__sibling))) {
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__left_node(cause, this__sibling), new__symbol(cause, "black"));
    raw__interval_tree_node__rotate_right(cause, this__sibling, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  } else if (raw__eq(cause, this, f2__interval_tree_node__right_node(cause, f2__interval_tree_node__parent_node(cause, this))) &&
	     raw__interval_tree_node__is_black(cause, this__sibling) &&
	     raw__interval_tree_node__is_red(  cause, f2__interval_tree_node__right_node(cause, this__sibling)) &&
	     raw__interval_tree_node__is_black(cause, f2__interval_tree_node__left_node( cause, this__sibling))) {
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__right_node(cause, this__sibling), new__symbol(cause, "black"));
    raw__interval_tree_node__rotate_left(cause, this__sibling, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  }
  raw__interval_tree_node__delete_case_6(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}

void raw__interval_tree_node__delete_case_4(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (raw__interval_tree_node__is_red(  cause, f2__interval_tree_node__parent_node(cause, this)) &&
      raw__interval_tree_node__is_black(cause, this__sibling) &&
      raw__interval_tree_node__is_black(cause, f2__interval_tree_node__left_node( cause, this__sibling)) &&
      raw__interval_tree_node__is_black(cause, f2__interval_tree_node__right_node(cause, this__sibling))) {
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__parent_node(cause, this), new__symbol(cause, "black"));
  } else if (f2__interval_tree_node__parent_node(cause, this) != nil) {
    raw__interval_tree_node__delete_case_5(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  }
}

void raw__interval_tree_node__delete_case_3(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (this__sibling) {
    if (raw__interval_tree_node__is_black(cause, f2__interval_tree_node__parent_node(cause, this)) &&
	raw__interval_tree_node__is_black(cause, this__sibling) &&
	raw__interval_tree_node__is_black(cause, f2__interval_tree_node__left_node( cause, this__sibling)) &&
	raw__interval_tree_node__is_black(cause, f2__interval_tree_node__right_node(cause, this__sibling))) {
      f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
      raw__interval_tree_node__delete_case_1(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
    } else {
      raw__interval_tree_node__delete_case_4(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
    }
  }
}

void raw__interval_tree_node__delete_case_2(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (raw__interval_tree_node__is_red(cause, this__sibling)) {
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__parent_node(cause, this), new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "black"));
    if (raw__eq(cause, this, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, this)))) {
      raw__interval_tree_node__rotate_left(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
    } else {
      raw__interval_tree_node__rotate_right(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
    }
  }
  raw__interval_tree_node__delete_case_3(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}

void raw__interval_tree_node__delete_case_1(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  if (f2__interval_tree_node__parent_node(cause, this) != nil) {
    raw__interval_tree_node__delete_case_2(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  }
}

void raw__interval_tree_node__replace_node(f2ptr cause, f2ptr dest, f2ptr src) {
  f2ptr src__parent = f2__interval_tree_node__parent_node(cause, src);
  f2ptr src__left   = f2__interval_tree_node__left_node(  cause, src);
  f2ptr src__right  = f2__interval_tree_node__right_node( cause, src);
  f2__interval_tree_node__parent_node__set(cause, dest, src__parent);
  f2__interval_tree_node__left_node__set(  cause, dest, src__left);
  f2__interval_tree_node__right_node__set( cause, dest, src__right);
  if (src__parent) {
    if (raw__eq(cause, f2__interval_tree_node__left_node(cause, src__parent), src)) {
      f2__interval_tree_node__left_node__set(cause, src__parent, dest);
    } else { // (src__parent->right == src)
      //#ifdef DEBUG_REDBLACKTREE
      //debug__assert(f2__redblacktree_node__right(cause, src__parent) == src, nil, "raw__redblacktree_node__replace_node assertion failure: src__parent->right == src.");
      //#endif
      f2__interval_tree_node__right_node__set(cause, src__parent, dest);
    }
  }
  if (src__left != nil) {
    f2__interval_tree_node__parent_node__set(cause, src__left, dest);
  }
  if (src__right != nil) {
    f2__interval_tree_node__parent_node__set(cause, src__right, dest);
  }
  //#ifdef DEBUG_REDBLACKTREE
  //debug__assert(raw__redblacktree_node__is_valid(cause, dest), nil, "raw__redblacktree_node__replace_node assertion failure: raw__redblacktree_node__is_valid(cause, dest).");
  //#endif
}

void raw__interval_tree_node__swap_nodes(f2ptr cause, f2ptr node1, f2ptr node2) {
  f2ptr node1__parent       = f2__interval_tree_node__parent_node(cause, node1);
  f2ptr node1__parent__left = f2__interval_tree_node__parent_node(cause, node1) ? f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, node1)) : nil;
  f2ptr node1__left         = f2__interval_tree_node__left_node(  cause, node1);
  f2ptr node1__right        = f2__interval_tree_node__right_node( cause, node1);
  f2ptr node1__color        = f2__interval_tree_node__color(      cause, node1);
  f2ptr node2__parent       = f2__interval_tree_node__parent_node(cause, node2);
  f2ptr node2__parent__left = f2__interval_tree_node__parent_node(cause, node2) ? f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, node2)) : nil;
  f2ptr node2__left         = f2__interval_tree_node__left_node(  cause, node2);
  f2ptr node2__right        = f2__interval_tree_node__right_node( cause, node2);
  f2ptr node2__color        = f2__interval_tree_node__color(      cause, node2);
  
  // copy values to node2
  if (raw__eq(cause, node1__parent, node2)) {
    f2__interval_tree_node__parent_node__set(cause, node2, node1);
  } else {
    f2__interval_tree_node__parent_node__set(cause, node2, node1__parent);
    if (node1__parent) {
      if (raw__eq(cause, node1__parent__left, node1)) {
	f2__interval_tree_node__left_node__set(cause, node1__parent, node2);
      } else { // (node1__parent->right == node1)
	//#ifdef DEBUG_REDBLACKTREE
	//debug__assert(f2__redblacktree_node__right(cause, node1__parent) == node1, nil, "raw__redblacktree_node__replace_node assertion failure: node1__parent->right == node1.");
	//#endif
	f2__interval_tree_node__right_node__set(cause, node1__parent, node2);
      }
    }
  }
  if (raw__eq(cause, node1__left, node2)) {
    f2__interval_tree_node__left_node__set(cause, node2, node1);
  } else {
    f2__interval_tree_node__left_node__set(cause, node2, node1__left);
    if (node1__left) {
      f2__interval_tree_node__parent_node__set(cause, node1__left, node2);
    }
  }
  if (raw__eq(cause, node1__right, node2)) {
    f2__interval_tree_node__right_node__set(cause, node2, node1);
  } else {
    f2__interval_tree_node__right_node__set(cause, node2, node1__right);
    if (node1__right) {
      f2__interval_tree_node__parent_node__set(cause, node1__right, node2);
    }
  }
  f2__interval_tree_node__color__set(cause, node2, node1__color);
  
  // copy values to node1
  if (raw__eq(cause, node2__parent, node1)) {
    f2__interval_tree_node__parent_node__set(cause, node1, node2);
  } else {
    f2__interval_tree_node__parent_node__set(cause, node1, node2__parent);
    if (node2__parent != nil) {
      if (raw__eq(cause, node2__parent__left, node2)) {
	f2__interval_tree_node__left_node__set(cause, node2__parent, node1);
      } else { // (node1__parent->right == node1)
	//#ifdef DEBUG_REDBLACKTREE
	//debug__assert(f2__redblacktree_node__right(cause, node2__parent) == node2, nil, "raw__redblacktree_node__replace_node assertion failure: node2__parent->right == node2.");
	//#endif
	f2__interval_tree_node__right_node__set(cause, node2__parent, node1);
      }
    }
  }
  if (raw__eq(cause, node2__left, node1)) {
    f2__interval_tree_node__left_node__set(cause, node1, node2);
  } else {
    f2__interval_tree_node__left_node__set(cause, node1, node2__left);
    if (node2__left != nil) {
      f2__interval_tree_node__parent_node__set(cause, node2__left, node1);
    }
  }
  if (raw__eq(cause, node2__right, node1)) {
    f2__interval_tree_node__right_node__set(cause, node1, node2);
  } else {
    f2__interval_tree_node__right_node__set(cause, node1, node2__right);
    if (node2__right != nil) {
      f2__interval_tree_node__parent_node__set(cause, node2__right, node1);
    }
  }
  f2__interval_tree_node__color__set(cause, node1, node2__color);
  //#ifdef DEBUG_REDBLACKTREE
  //debug__assert(raw__interval_tree_node__is_valid(cause, node1), nil, "raw__redblacktree_node__swap_node assertion failure: raw__redblacktree_node__is_valid(cause, node1).");
  //debug__assert(raw__interval_tree_node__is_valid(cause, node2), nil, "raw__redblacktree_node__swap_node assertion failure: raw__redblacktree_node__is_valid(cause, node2).");
  //#endif
}

///^^^^^

f2ptr raw__interval_tree_node__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  f2ptr center_value            = f2__interval_tree_node__center_value(cause, this);
  f2ptr center_value_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, center_value, value)));
  f2ptr value_center_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, value,        center_value)));
  f2ptr center_value_equality   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, center_value, value)));
  if ((center_value_comparison != nil) ||
      (center_value_equality   != nil)) {
    // value is to the right of center_value
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
    redblacktree__iteration_backward(cause, overlapping_right_redblacktree, element,
				     f2ptr right_value            = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, element)));
				     f2ptr value_right_equality   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, value, right_value)));
				     f2ptr value_right_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, value, right_value)));
				     if ((value_right_equality   != nil) ||
					 (value_right_comparison != nil)) {
				       // value is less than the right_value of element
				       f2__list__add(cause, list, element);
				       // keep looping backwards
				     } else {
				       // value is greater than right_value of element, so stop looping.
				       goto raw__interval_tree_node__add_intervals_containing_value_to_list____overlapping_right_redblacktree__done_with_redblacktree_iteration;
				     }
				     );
  raw__interval_tree_node__add_intervals_containing_value_to_list____overlapping_right_redblacktree__done_with_redblacktree_iteration:
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    //if (center_value_equality == nil) {
      // descend right branch of tree
      {
	f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
	if (right_node != nil) {
	  assert_value(raw__interval_tree_node__add_intervals_containing_value_to_list(cause, right_node, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
	}
      }
      //}
  }
  if ((value_center_comparison != nil) ||
      (center_value_equality   != nil)) {
    // value is to the left of center_value
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    f2ptr overlapping_left_redblacktree = f2__interval_tree_node__overlapping_left_redblacktree(cause, this);
    redblacktree__iteration_forward(cause, overlapping_left_redblacktree, element,
				    f2ptr left_value            = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, element)));
				    f2ptr left_value_equality   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, left_value, value)));
				    f2ptr left_value_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, left_value, value)));
				    if ((left_value_equality   != nil) ||
					(left_value_comparison != nil)) {
				      // left_value of element is less than the value
				      f2__list__add(cause, list, element);
				      // keep looping forwards
				    } else {
				      // left_value of element is greater than the value, so stop looping.
				      goto raw__interval_tree_node__add_intervals_containing_value_to_list____overlapping_left_redblacktree__done_with_redblacktree_iteration;
				    }
				    );
  raw__interval_tree_node__add_intervals_containing_value_to_list____overlapping_left_redblacktree__done_with_redblacktree_iteration:
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    //if (center_value_equality == nil) {
      // descend left branch of tree
      {
	f2ptr left_node = f2__interval_tree_node__left_node(cause, this);
	if (left_node != nil) {
	  return raw__interval_tree_node__add_intervals_containing_value_to_list(cause, left_node, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
	}
      }
      //}
  }
  return nil;
}

f2ptr f2__interval_tree_node__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  assert_argument_type(interval_tree_node, this);
  assert_argument_type(list,               list);
  assert_argument_type(funkable,           left_value_funk);
  assert_argument_type(funkable,           right_value_funk);
  assert_argument_type(funkable,           value_equality_funk);
  assert_argument_type(funkable,           value_comparison_funk);
  return raw__interval_tree_node__add_intervals_containing_value_to_list(cause, this, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
}
def_pcfunk7(interval_tree_node__add_intervals_containing_value_to_list, this, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk,
	    "Adds intervals from this interval_tree_node that contain the given value to the given list.",
	    return f2__interval_tree_node__add_intervals_containing_value_to_list(this_cause, this, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));


f2ptr raw__interval_tree_node__overlapping_elements(f2ptr cause, f2ptr this) {
  f2ptr overlapping_left_redblacktree = f2__interval_tree_node__overlapping_left_redblacktree(cause, this);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return raw__redblacktree__leaves(cause, overlapping_left_redblacktree);
}

f2ptr f2__interval_tree_node__overlapping_elements(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__overlapping_elements(cause, this);
}
def_pcfunk1(interval_tree_node__overlapping_elements, this,
	    "Returns a new list containing the interval elements that overlap this node's center_value.",
	    return f2__interval_tree_node__overlapping_elements(this_cause, this));


f2ptr raw__interval_tree_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"),              new__symbol(cause, "interval_tree_node"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "color"),                          f2__interval_tree_node__color(                         cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "center_value"),                   f2__interval_tree_node__center_value(                  cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "overlapping_left_redblacktree"),  f2__interval_tree_node__overlapping_left_redblacktree( cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "overlapping_right_redblacktree"), f2__interval_tree_node__overlapping_right_redblacktree(cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "left_node"),                      f2__interval_tree_node__left_node(                     cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "right_node"),                     f2__interval_tree_node__right_node(                    cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__interval_tree_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(interval_tree_node,        this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__interval_tree_node__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(interval_tree_node__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__interval_tree_node__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2interval_tree_node__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2interval_tree_node__primobject_type__new(cause);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "simple_insert"),                          __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.simple_insert__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "simple_remove"),                          __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.simple_remove__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                                 __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.insert__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_intervals_containing_value_to_list"), __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.add_intervals_containing_value_to_list__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "overlapping_elements"),                   __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.overlapping_elements__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),              __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.terminal_print_with_frame__funk);
  return this;
}



// **

void f2__primobject__interval_tree__reinitialize_globalvars() {
  __interval_tree__symbol      = new__symbol(initial_cause(), "interval_tree");
  __interval_tree_node__symbol = new__symbol(initial_cause(), "interval_tree_node");
}

void f2__primobject__interval_tree__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__interval_tree", "", &f2__primobject__interval_tree__reinitialize_globalvars);
  
  f2__primobject__interval_tree__reinitialize_globalvars();
  
  // interval_tree
  
  initialize_primobject_9_slot(interval_tree, mutate_cmutex, head, all_left_redblacktree, all_right_redblacktree, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
  
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.new__symbol = new__symbol(cause, "new");
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(interval_tree__new, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.new__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.insert__symbol = new__symbol(cause, "insert");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__insert, this, element, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.insert__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.remove__symbol = new__symbol(cause, "remove");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__remove, this, element, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.remove__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.add_intervals_containing_value_to_list__symbol = new__symbol(cause, "add_intervals_containing_value_to_list");
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(interval_tree__add_intervals_containing_value_to_list, this, value, list, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.add_intervals_containing_value_to_list__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals_containing_value__symbol = new__symbol(cause, "intervals_containing_value");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__intervals_containing_value, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals_containing_value__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals_overlapping_interval__symbol = new__symbol(cause, "intervals_overlapping_interval");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__intervals_overlapping_interval, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.intervals_overlapping_interval__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // interval_tree_node
  
  initialize_primobject_7_slot(interval_tree_node, color, center_value, parent_node, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);
  
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.new__symbol = new__symbol(cause, "new");
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(interval_tree_node__new, color, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.new__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.simple_insert__symbol = new__symbol(cause, "simple_insert");
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(interval_tree_node__simple_insert, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.simple_insert__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.simple_remove__symbol = new__symbol(cause, "simple_remove");
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(interval_tree_node__simple_remove, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.simple_remove__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.insert__symbol = new__symbol(cause, "insert");
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(interval_tree_node__insert, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.insert__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.add_intervals_containing_value_to_list__symbol = new__symbol(cause, "add_intervals_containing_value_to_list");
  {f2__primcfunk__init__with_c_cfunk_var__7_arg(interval_tree_node__add_intervals_containing_value_to_list, this, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, cfunk);
    __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.add_intervals_containing_value_to_list__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.overlapping_elements__symbol = new__symbol(cause, "overlapping_elements");
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(interval_tree_node__overlapping_elements, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.overlapping_elements__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree_node__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}


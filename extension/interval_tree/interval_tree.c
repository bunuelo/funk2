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

#include "interval_tree.h"

def_ceframe9(interval_tree, interval_tree, mutate_cmutex, head, all_left_redblacktree, all_right_redblacktree, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);

f2ptr raw__interval_tree__new(f2ptr cause, f2ptr head, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr mutate_cmutex          = f2__cmutex__new(cause);
  f2ptr all_left_redblacktree  = f2__redblacktree__new(cause, left_value_funk,  value_comparison_funk);
  f2ptr all_right_redblacktree = f2__redblacktree__new(cause, right_value_funk, value_comparison_funk);
  return f2interval_tree__new(cause, mutate_cmutex, head, all_left_redblacktree, all_right_redblacktree, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}

f2ptr f2__interval_tree__new(f2ptr cause, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr head = nil;
  return raw__interval_tree__new(cause, head, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
export_cefunk5(interval_tree__new, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk, 0,
	       "Returns a new interval_tree object.");



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
def_cefunk2(interval_tree__insert, this, element, 0,
	    "Inserts a new interval element into this interval_tree.");


f2ptr raw__interval_tree__remove__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr all_left_redblacktree  = f2__interval_tree__all_left_redblacktree( cause, this);
  f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
  assert_value(f2__redblacktree__remove(cause, all_left_redblacktree,  element));
  assert_value(f2__redblacktree__remove(cause, all_right_redblacktree, element));
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
    raw__interval_tree__remove_node(cause, this, remove_node);
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
def_cefunk2(interval_tree__remove, this, element, 0,
	    "Removes an interval element from this interval_tree.");


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
  return f2__redblacktree__leaves(cause, all_left_redblacktree);
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
def_cefunk1(interval_tree__intervals, this, 0,
	    "Returns all of the intervals in this interval_tree.");


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
def_cefunk3(interval_tree__add_intervals_containing_value_to_list, this, value, list, 0,
	    "Adds intervals from this interval_tree that contain the given value to the given list.");


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
def_cefunk2(interval_tree__intervals_containing_value, this, value, 0,
	    "Returns a new set that contains the intervals in this interval_tree that contain the given value.");


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
      f2ptr redblacktree_node = f2__redblacktree__minimum_not_less_than__node(cause, all_left_redblacktree, element__left_value);
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
	redblacktree_node = f2__redblacktree_node__next(cause, redblacktree_node);
      }
    }
    {
      f2ptr redblacktree_node = f2__redblacktree__minimum_not_less_than__node(cause, all_right_redblacktree, element__left_value);
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
	redblacktree_node = f2__redblacktree_node__next(cause, redblacktree_node);
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
def_cefunk2(interval_tree__intervals_overlapping_interval, this, element, 0,
	    "Returns a new set that contains the intervals in this interval_tree that overlap with the given interval.");


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
def_cefunk2(interval_tree__terminal_print_with_frame, this, terminal_print_frame, 0,
	    "");


f2ptr f2__interval_tree_type__new_aux(f2ptr cause) {
  f2ptr this = f2__interval_tree_type__new(cause);
  return this;
}



// **

f2ptr f2__interval_tree__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(interval_tree__core_extension__ping, 0, "");

f2ptr f2__interval_tree__core_extension__initialize(f2ptr cause) {
  status("interval_tree initialized.");
  return nil;
}
export_cefunk0(interval_tree__core_extension__initialize, 0, "");

f2ptr f2__interval_tree__core_extension__define_types(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "interval_tree"), f2__interval_tree_type__new_aux(cause));
  status("interval_tree types defined.");
  return nil;
}
export_cefunk0(interval_tree__core_extension__define_types, 0, "");

f2ptr f2__interval_tree__core_extension__destroy(f2ptr cause) {
  status("interval_tree destroyed.");
  return nil;
}
export_cefunk0(interval_tree__core_extension__destroy, 0, "");



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

#include "interval_tree.h"

//#define F2__DEBUG__INTERVAL_TREE_NODE 1

// interval_tree

def_ceframe10(interval_tree, interval_tree,
	      mutate_cmutex,
	      interval_set,
	      head,
	      all_left_redblacktree,
	      all_right_redblacktree,
	      left_value_funk,
	      right_value_funk,
	      value_equality_funk,
	      value_comparison_funk,
	      value_center_funk);

f2ptr raw__interval_tree__new(f2ptr cause,
			      f2ptr head,
			      f2ptr left_value_funk,
			      f2ptr right_value_funk,
			      f2ptr value_equality_funk,
			      f2ptr value_comparison_funk,
			      f2ptr value_center_funk) {
  f2ptr mutate_cmutex          = f2__cmutex__new(cause);
  f2ptr interval_set           = f2__set__new(cause);
  f2ptr all_left_redblacktree  = f2__redblacktree__new(cause, left_value_funk,  value_comparison_funk);
  f2ptr all_right_redblacktree = f2__redblacktree__new(cause, right_value_funk, value_comparison_funk);
  return f2interval_tree__new(cause,
			      mutate_cmutex,
			      interval_set,
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
  f2ptr head = nil;
  return raw__interval_tree__new(cause, head, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
export_cefunk5(interval_tree__new, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk, 0,
	       "Returns a new interval_tree object.");


f2ptr raw__interval_tree__assert_valid__thread_unsafe(f2ptr cause, f2ptr this) {
  {
    f2ptr interval_set = assert_value(f2__interval_tree__interval_set(cause, this));
    set__iteration(cause, interval_set, interval,
		   if (assert_value(f2__interval_tree__contains(cause, this, interval)) == nil) {
		     return new__error(f2list4__new(cause,
						    new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree-assert_valid-does_not_contain_entire_interval_set"),
						    new__symbol(cause, "this"),     this));
		   }
		   );
  }
  {
    f2ptr head = f2__interval_tree__head(cause, this);
    if (head != nil) {
      assert_value(f2__interval_tree_node__assert_valid_recursively(cause, head));
    }
  }
  return nil;
}

f2ptr f2__interval_tree__assert_valid__thread_unsafe(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__assert_valid__thread_unsafe(cause, this);
}


f2ptr raw__interval_tree__assert_valid(f2ptr cause, f2ptr this) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__assert_valid__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__assert_valid(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__assert_valid(cause, this);
}
export_cefunk1(interval_tree__assert_valid, this, 0,
	       "Asserts the validity of this interval_tree object.");





f2ptr raw__interval_tree__insert__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  catch_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this),
	      f2list6__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_failed_validity_assertion"),
			   new__symbol(cause, "this"),     this,
			   new__symbol(cause, "element"),  element));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
  {
    f2ptr interval_set = assert_value(f2__interval_tree__interval_set(cause, this));
    assert_value(f2__set__add(cause, interval_set, element));
  }
  f2ptr head                   = f2__interval_tree__head(                  cause, this);
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
  catch_value(f2__interval_tree_node__insert(cause, head, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk),
	      f2list6__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_failed_to_insert_element"),
			   new__symbol(cause, "this"),     this,
			   new__symbol(cause, "element"),  element));
  do {
    f2ptr head__parent_node = f2__interval_tree_node__parent_node(cause, head);
    if (head__parent_node == nil) {
      break;
    }
    head = head__parent_node;
  } while (1);
  f2__interval_tree__head__set(cause, this, head);
  
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit before.", __FUNCTION__, this);
  catch_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this),
	      f2list6__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_failed_validity_assertion"),
			   new__symbol(cause, "this"),     this,
			   new__symbol(cause, "element"),  element));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit after.", __FUNCTION__, this);
#endif
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
export_cefunk2(interval_tree__insert, this, element, 0,
	       "Inserts a new interval element into this interval_tree.");


f2ptr raw__interval_tree__remove__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  catch_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this),
	      f2list6__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_failed_validity_assertion"),
			   new__symbol(cause, "this"),     this,
			   new__symbol(cause, "element"),  element));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
  {
    f2ptr interval_set = assert_value(f2__interval_tree__interval_set(cause, this));
    assert_value(f2__set__remove(cause, interval_set, element));
  }
  {
    f2ptr all_left_redblacktree  = f2__interval_tree__all_left_redblacktree( cause, this);
    f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
    catch_value(f2__redblacktree__remove(cause, all_left_redblacktree,  element),
		f2list6__new(cause,
			     new__symbol(cause, "bug_name"),    new__symbol(cause, "inconsistency_failure_in_all_left_redblacktree-possibly_changed_left_value"),
			     new__symbol(cause, "description"), new__string(cause, "This bug often arises when the start time of an interval has been changed while being part of the redblacktree."),
			     new__symbol(cause, "this"),        this));
    catch_value(f2__redblacktree__remove(cause, all_right_redblacktree, element),
		f2list6__new(cause,
			     new__symbol(cause, "bug_name"),    new__symbol(cause, "inconsistency_failure_in_all_right_redblacktree-possibly_changed_right_value"),
			     new__symbol(cause, "description"), new__string(cause, "This bug often arises when the ending time of an interval has been changed while being part of the redblacktree."),
			     new__symbol(cause, "this"),        this));
    f2ptr head = f2__interval_tree__head(cause, this);
    if (head == nil) {
      return f2larva__new(cause, 23516, nil);
    }
    f2ptr left_value_funk       = f2__interval_tree__left_value_funk(      cause, this);
    f2ptr right_value_funk      = f2__interval_tree__right_value_funk(     cause, this);
    f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(  cause, this);
    f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
    // we could check the returned removed_from_node from the simple_remove command, and do the red-black tree deletion cases here.
    f2ptr remove_node = f2__interval_tree_node__simple_remove(cause, head, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
    assert_value(remove_node);
    if (remove_node != nil) {
      if (f2__interval_tree_node__is_empty(cause, remove_node) != nil) {
	//assert_value(raw__interval_tree__remove_node(cause, this, remove_node));
      }
    }
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  before.", __FUNCTION__, this);
  catch_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this),
	      f2list6__new(cause,
			   new__symbol(cause, "bug_name"), new__symbol(cause, "interval_tree_failed_validity_assertion"),
			   new__symbol(cause, "this"),     this,
			   new__symbol(cause, "element"),  element));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  after.", __FUNCTION__, this);
#endif
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
export_cefunk2(interval_tree__remove, this, element, 0,
	    "Removes an interval element from this interval_tree.");


///vvvvv

f2ptr raw__interval_tree__remove_node_with_at_most_one_child(f2ptr cause, f2ptr this, f2ptr node) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
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
	assert_value(f2__interval_tree_node__delete_case_1(cause, node__child,
							   left_value_funk,
							   right_value_funk,
							   value_equality_funk,
							   value_comparison_funk,
							   value_center_funk));
      }
    }
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  after.", __FUNCTION__, this);
#endif
  return nil;
}

f2ptr f2__interval_tree__remove_node_with_at_most_one_child(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(interval_tree,      this);
  assert_argument_type(interval_tree_node, node);
  return raw__interval_tree__remove_node_with_at_most_one_child(cause, this, node);
}

f2ptr raw__interval_tree__remove_node(f2ptr cause, f2ptr this, f2ptr node) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
  if ((f2__interval_tree_node__left_node(cause, node) == nil) || (f2__interval_tree_node__right_node(cause, node) == nil)) { 
    assert_value(f2__interval_tree__remove_node_with_at_most_one_child(cause, this, node));
  } else {
    f2ptr node__left__max = f2__interval_tree_node__maximum_node(cause, f2__interval_tree_node__left_node(cause, node));
    
    //debug__assert(f2__interval_tree_node__right_node(cause, node__left__max) == nil, nil, "interval_tree_node__remove_node: (node__left__max->right == NULL) failed.");
    
    assert_value(f2__interval_tree_node__swap_nodes(cause, node__left__max, node));
    
    assert_value(f2__interval_tree__remove_node_with_at_most_one_child(cause, this, node));
    
    if (f2__interval_tree_node__parent_node(cause, node__left__max) == nil) {
      f2__interval_tree__head__set(cause, this, node__left__max);
    }
  }
  
  f2__interval_tree__head__set(cause, this, f2__interval_tree_node__head(cause, f2__interval_tree__head(cause, this))); 
  
  if (f2__interval_tree__head(cause, this) != nil) {
    if (raw__eq(cause, f2__interval_tree_node__color(cause, f2__interval_tree__head(cause, this)), new__symbol(cause, "red"))) {
      f2__interval_tree_node__color__set(cause, f2__interval_tree__head(cause, this), new__symbol(cause, "black"));
    }
  }
  
  //#ifdef DEBUG_REDBLACKTREE
  //debug__assert(! raw__interval_tree__contains_node(this, node), nil, "raw__interval_tree__remove_node failed: tree still contains node.");
  //#endif
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  after.", __FUNCTION__, this);
#endif
  return nil;
}

///^^^^


f2ptr raw__interval_tree__lookup_key_count(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr all_left_redblacktree = f2__interval_tree__all_left_redblacktree(cause, this);
  return assert_value(f2__redblacktree__lookup_key_count(cause, all_left_redblacktree, element));
}

f2ptr f2__interval_tree__lookup_key_count(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__lookup_key_count(cause, this, element);
}
export_cefunk2(interval_tree__lookup_key_count, this, element, 0,
	       "Returns the number of times the given element exists with this interval_tree.");


f2ptr raw__interval_tree__contains(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr count    = assert_value(raw__interval_tree__lookup_key_count(cause, this, element));
  s64   count__i = f2integer__i(count, cause);
  if (count__i == 0) {
    return f2bool__new(boolean__false);
  }
  return f2bool__new(boolean__true);
}

f2ptr f2__interval_tree__contains(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__contains(cause, this, element);
}
export_cefunk2(interval_tree__contains, this, element, 0,
	       "Returns whether or not the given element exists with this interval_tree.");


f2ptr raw__interval_tree__intervals__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr all_left_redblacktree = f2__interval_tree__all_left_redblacktree(cause, this);
  return assert_value(f2__redblacktree__leaves(cause, all_left_redblacktree));
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
export_cefunk1(interval_tree__intervals, this, 0,
	    "Returns all of the intervals in this interval_tree.");


f2ptr raw__interval_tree__add_intervals_containing_value_to_list__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value, f2ptr list) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
  f2ptr head = f2__interval_tree__head(cause, this);
  if (head != nil) {
    f2ptr left_value_funk       = f2__interval_tree__left_value_funk(      cause, this);
    f2ptr right_value_funk      = f2__interval_tree__right_value_funk(     cause, this);
    f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
    f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(  cause, this);
    assert_value(raw__interval_tree_node__add_intervals_containing_value_to_list(cause, head, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  after.", __FUNCTION__, this);
#endif
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
  assert_argument_type(list,          list);
  return raw__interval_tree__add_intervals_containing_value_to_list(cause, this, value, list);
}
export_cefunk3(interval_tree__add_intervals_containing_value_to_list, this, value, list, 0,
	    "Adds intervals from this interval_tree that contain the given value to the given list.");


f2ptr raw__interval_tree__intervals_containing_value__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
  f2ptr list = f2__list__new(cause, nil);
  assert_value(raw__interval_tree__add_intervals_containing_value_to_list__thread_unsafe(cause, this, value, list));
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  after.", __FUNCTION__, this);
#endif
  f2ptr list__cons_cells = f2__list__cons_cells(cause, list);
  {
    f2ptr left_value_funk       = f2__interval_tree__left_value_funk(      cause, this);
    f2ptr right_value_funk      = f2__interval_tree__right_value_funk(     cause, this);
    f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
    f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(  cause, this);
    {
      f2ptr iter = list__cons_cells;
      while (iter != nil) {
	f2ptr interval = f2cons__car(iter, cause);
	{
	  f2ptr     fiber                       = f2__this__fiber(cause);
	  f2ptr     interval_args               = f2list1__new(cause, interval);
	  f2ptr     interval__left_value        = f2__force_funk_apply(cause, fiber, left_value_funk,  interval_args);
	  f2ptr     interval__right_value       = f2__force_funk_apply(cause, fiber, right_value_funk, interval_args);
	  f2ptr     left_consistent_args        = f2list2__new(cause, interval__left_value, value);
	  boolean_t left_consistent_with_value  = ((f2__force_funk_apply(cause, fiber, value_comparison_funk, left_consistent_args) != nil) ||
						   (f2__force_funk_apply(cause, fiber, value_equality_funk,   left_consistent_args) != nil));
	  f2ptr     right_consistent_args       = f2list2__new(cause, value, interval__right_value);
	  boolean_t right_consistent_with_value = ((f2__force_funk_apply(cause, fiber, value_comparison_funk, right_consistent_args) != nil) ||
						   (f2__force_funk_apply(cause, fiber, value_equality_funk,   right_consistent_args) != nil));
	  if ((! left_consistent_with_value)  ||
	      (! right_consistent_with_value)) {
	    return new__error(f2list14__new(cause,
					    new__symbol(cause, "bug_name"),                    new__symbol(cause, "interval_tree-returning_inconsistent_left_value_of_interval"),
					    new__symbol(cause, "this"),                        this,
					    new__symbol(cause, "interval-left_value"),         interval__left_value,
					    new__symbol(cause, "interval-right_value"),        interval__right_value,
					    new__symbol(cause, "left_consistent_with_value"),  f2bool__new(left_inconsistent_with_value),
					    new__symbol(cause, "right_consistent_with_value"), f2bool__new(right_inconsistent_with_value),
					    new__symbol(cause, "value"),                       value));
	  }
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
  }
  return list__cons_cells;
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
export_cefunk2(interval_tree__intervals_containing_value, this, value, 0,
	    "Returns a new set that contains the intervals in this interval_tree that contain the given value.");


f2ptr raw__interval_tree__intervals_overlapping_range__thread_unsafe(f2ptr cause, f2ptr this, f2ptr range_left_value, f2ptr range_right_value) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " enter after.", __FUNCTION__, this);
#endif
  f2ptr list = f2__list__new(cause, nil);
  {
    f2ptr all_left_redblacktree  = f2__interval_tree__all_left_redblacktree( cause, this);
    f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
    f2ptr left_value_funk        = f2__interval_tree__left_value_funk(       cause, this);
    f2ptr right_value_funk       = f2__interval_tree__right_value_funk(      cause, this);
    f2ptr value_equality_funk    = f2__interval_tree__value_equality_funk(   cause, this);
    f2ptr value_comparison_funk  = f2__interval_tree__value_comparison_funk( cause, this);
    {
      f2ptr redblacktree_node = f2__redblacktree__minimum_not_less_than__node(cause, all_left_redblacktree, range_left_value);
      while (redblacktree_node != nil) {
	f2ptr redblacktree_node__count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, redblacktree_node);
	f2ptr redblacktree_node__element             = f2__ptypehash__an_arbitrary_key(cause, redblacktree_node__count_key_ptypehash);
	f2ptr redblacktree_node__element__left_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, redblacktree_node__element)));
	f2ptr equality                               = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, redblacktree_node__element__left_value, range_right_value)));
	f2ptr comparison                             = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, redblacktree_node__element__left_value, range_right_value)));
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
      f2ptr redblacktree_node = f2__redblacktree__minimum_not_less_than__node(cause, all_right_redblacktree, range_left_value);
      while (redblacktree_node != nil) {
	f2ptr redblacktree_node__count_key_ptypehash  = f2__redblacktree_node__count_key_ptypehash(cause, redblacktree_node);
	f2ptr redblacktree_node__element              = f2__ptypehash__an_arbitrary_key(cause, redblacktree_node__count_key_ptypehash);
	f2ptr redblacktree_node__element__right_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, redblacktree_node__element)));
	f2ptr equality                                = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, redblacktree_node__element__right_value, range_right_value)));
	f2ptr comparison                              = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, redblacktree_node__element__right_value, range_right_value)));
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
    f2ptr element__center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, range_left_value, range_right_value)));
    assert_value(raw__interval_tree__add_intervals_containing_value_to_list__thread_unsafe(cause, this, element__center_value, list));
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  before.", __FUNCTION__, this);
  assert_value(f2__interval_tree__assert_valid__thread_unsafe(cause, this));
  status("INTERVAL_TREE DEBUG %s " f2ptr__fstr " exit  after.", __FUNCTION__, this);
#endif
  f2ptr list__cons_cells = f2__list__cons_cells(cause, list);
  {
    f2ptr left_value_funk       = f2__interval_tree__left_value_funk(      cause, this);
    f2ptr right_value_funk      = f2__interval_tree__right_value_funk(     cause, this);
    f2ptr value_comparison_funk = f2__interval_tree__value_comparison_funk(cause, this);
    f2ptr value_equality_funk   = f2__interval_tree__value_equality_funk(  cause, this);
    {
      f2ptr iter = list__cons_cells;
      while (iter != nil) {
	f2ptr interval = f2cons__car(iter, cause);
	{
	  f2ptr     fiber                                     = f2__this__fiber(cause);
	  f2ptr     interval_args                             = f2list1__new(cause, interval);
	  f2ptr     interval__left                            = f2__force_funk_apply(cause, fiber, left_value_funk,  interval_args);
	  f2ptr     interval__right                           = f2__force_funk_apply(cause, fiber, right_value_funk, interval_args);
	  //boolean_t interval_left__less_than__interval_right  = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, interval__left_value,  interval__right_value)) != nil);
	  //boolean_t interval_left__less_than__range_left      = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, interval__left_value,  range_left_value))      != nil);
	  //boolean_t interval_left__less_than__range_right     = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, interval__left_value,  range_right_value))     != nil);
	  boolean_t interval_right__less_than__interval_left  = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, interval__right_value, interval__left_value))  != nil);
	  boolean_t interval_right__less_than__range_left     = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, interval__right_value, range_left_value))      != nil);
	  //boolean_t interval_right__less_than__range_right    = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, interval__right_value, range_right_value))     != nil);
	  //boolean_t range_left__less_than__interval_left      = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, range_left_value,      interval__left_value))  != nil);
	  //boolean_t range_left__less_than__interval_right     = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, range_left_value,      interval__right_value)) != nil);
	  //boolean_t range_left__less_than__range_right        = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, range_left_value,      range_right_value))     != nil);
	  boolean_t range_right__less_than__interval_left     = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, range_right_value,     interval__left_value))  != nil);
	  //boolean_t range_right__less_than__interval_right    = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, range_right_value,     interval__right_value)) != nil);
	  boolean_t range_right__less_than__range_left        = (f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, range_right_value,     range_left_value))      != nil);
	  
	  boolean_t interval_right_less_than_interval_left_bug = interval_right__less_than__interval_left;
	  boolean_t interval_right_less_than_range_left_bug    = interval_right__less_than__range_left;
	  boolean_t range_right_less_than_interval_left_bug    = range_right__less_than__interval_left;
	  boolean_t range_right_less_than_range_left_bug       = range_right__less_than__range_left;
	  
	  if (interval_right_less_than_interval_left_bug ||
	      interval_right_less_than_range_left_bug    ||
	      range_right_less_than_interval_left_bug    ||
	      range_right_less_than_range_left_bug) {
	    return new__error(f2list18__new(cause,
					    new__symbol(cause, "bug_name"),                                   new__symbol(cause, "interval_tree-returning_inconsistent_left_value_of_interval"),
					    new__symbol(cause, "this"),                                       this,
					    new__symbol(cause, "interval_left_value"),                        interval_left_value,
					    new__symbol(cause, "interval_right_value"),                       interval_right_value,
					    new__symbol(cause, "interval_right_less_than_interval_left_bug"), f2bool__new(interval_right_less_than_interval_left_bug),
					    new__symbol(cause, "interval_right_less_than_range_left_bug"),    f2bool__new(interval_right_less_than_range_left_bug),
					    new__symbol(cause, "range_right_less_than_interval_left_bug"),    f2bool__new(range_right_less_than_interval_left_bug),
					    new__symbol(cause, "range_right_less_than_range_left_bug"),       f2bool__new(range_right_less_than_range_left_bug),
					    new__symbol(cause, "value"),                                      value));
	  }
	}
	iter = f2cons__cdr(iter, cause);
      }
    }
  }
  return list;
}

f2ptr raw__interval_tree__intervals_overlapping_range(f2ptr cause, f2ptr this, f2ptr range_left_value, f2ptr range_right_value) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__intervals_overlapping_range__thread_unsafe(cause, this, range_left_value, range_right_value);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__intervals_overlapping_range(f2ptr cause, f2ptr this, f2ptr range_left_value, f2ptr range_right_value) {
  assert_argument_type(interval_tree, this);
  return raw__interval_tree__intervals_overlapping_range(cause, this, range_left_value, range_right_value);
}
export_cefunk3(interval_tree__intervals_overlapping_range, this, range_left_value, range_right_value, 0,
	       "Returns a new list that contains the intervals in this interval_tree that overlap with the given range specified by the range_left_value and range_right_value.");


f2ptr raw__interval_tree__intervals_overlapping_interval__thread_unsafe(f2ptr cause, f2ptr this, f2ptr element) {
  f2ptr left_value_funk      = f2__interval_tree__left_value_funk( cause, this);
  f2ptr right_value_funk     = f2__interval_tree__right_value_funk(cause, this);
  f2ptr element__left_value  = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,  f2list1__new(cause, element)));
  f2ptr element__right_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk, f2list1__new(cause, element)));
  return raw__interval_tree__intervals_overlapping_range__thread_unsafe(cause, this, element__left_value, element__right_value);
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
export_cefunk2(interval_tree__intervals_overlapping_interval, this, element, 0,
	       "Returns a new list that contains the intervals in this interval_tree that overlap with the given interval.");


f2ptr raw__interval_tree__most_recent_filtered_intervals__thread_unsafe(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr maximum_value) {
  f2ptr return_intervals = nil;
  {
    f2ptr all_right_redblacktree = f2__interval_tree__all_right_redblacktree(cause, this);
    {
      f2ptr redblacktree_node = f2__redblacktree__maximum_not_greater_than_or_equal_to__node(cause, all_right_redblacktree, maximum_value);
      while (redblacktree_node != nil) {
	f2ptr redblacktree_node__count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, redblacktree_node);
	ptypehash__key__iteration(cause, redblacktree_node__count_key_ptypehash, element_iter,
				  f2ptr filter_success = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), filter_funk, f2list2__new(cause, user_filter_data, element_iter)));
				  if (filter_success != nil) {
				    return_intervals = raw__cons__new(cause, element_iter, return_intervals);
				  }
				  );
	if (return_intervals != nil) {
	  break;
	}
	redblacktree_node = f2__redblacktree_node__prev(cause, redblacktree_node);
      }
    }
  }
  return return_intervals;
}

f2ptr raw__interval_tree__most_recent_filtered_intervals(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr maximum_value) {
  f2ptr mutate_cmutex = f2__interval_tree__mutate_cmutex(cause, this);
  raw__cmutex__lock(cause, mutate_cmutex);
  f2ptr result = raw__interval_tree__most_recent_filtered_intervals__thread_unsafe(cause, this, filter_funk, user_filter_data, maximum_value);
  raw__cmutex__unlock(cause, mutate_cmutex);
  return result;
}

f2ptr f2__interval_tree__most_recent_filtered_intervals(f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr maximum_value) {
  assert_argument_type(interval_tree, this);
  assert_argument_type(funkable,      filter_funk);
  return assert_value(raw__interval_tree__most_recent_filtered_intervals(cause, this, filter_funk, user_filter_data, maximum_value));
}
export_cefunk4(interval_tree__most_recent_filtered_intervals, this, filter_funk, user_filter_data, maximum_value, 0,
	       "Returns the maximum intervals that overlap with or are less than the given maximum_value and for which the given filter_funk also returns true.");


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
export_cefunk2(interval_tree__terminal_print_with_frame, this, terminal_print_frame, 0,
	       "");


f2ptr f2__interval_tree_type__new_aux(f2ptr cause) {
  f2ptr this = f2__interval_tree_type__new(cause);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "assert_valid"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__assert_valid")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                                 f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__insert")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "remove"),                                 f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__remove")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "lookup_key_count"),                       f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__lookup_key_count")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "contains"),                               f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__contains")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "intervals"),                              f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__intervals")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_intervals_containing_value_to_list"), f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__add_intervals_containing_value_to_list")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "intervals_containing_value"),             f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__intervals_containing_value")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "intervals_overlapping_range"),            f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__intervals_overlapping_range")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "intervals_overlapping_interval"),         f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__intervals_overlapping_interval")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "most_recent_filtered_intervals"),         f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__most_recent_filtered_intervals")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),              f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree__terminal_print_with_frame")));
  return this;
}



// interval_tree_node

def_ceframe7(interval_tree, interval_tree_node, color, center_value, parent_node, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);

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
export_cefunk6(interval_tree_node__new, color, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, 0,
	    "Returns a new interval_tree_node object.");


f2ptr raw__interval_tree_node__assert_valid(f2ptr cause, f2ptr this) {
  { // make sure overlapping_left_redblacktree and overlapping_right_redblacktree have the same elements.
    f2ptr overlapping_left_redblacktree  = f2__interval_tree_node__overlapping_left_redblacktree( cause, this);
    f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
    f2ptr left_element_ptypehash         = f2__ptypehash__new(cause);
    f2ptr right_element_ptypehash        = f2__ptypehash__new(cause);
    {
      f2ptr leaf_iter = assert_value(f2__redblacktree__leaves(cause, overlapping_left_redblacktree));
      while (leaf_iter != nil) {
	f2ptr element = f2__cons__car(cause, leaf_iter);
	{
	  f2ptr count = assert_value(f2__redblacktree__lookup_key_count(cause, overlapping_left_redblacktree, element));
	  raw__ptypehash__add(cause, left_element_ptypehash, element, count);
	}
	leaf_iter = f2__cons__cdr(cause, leaf_iter);
      }
    }
    {
      f2ptr leaf_iter = assert_value(f2__redblacktree__leaves(cause, overlapping_right_redblacktree));
      while (leaf_iter != nil) {
	f2ptr element = f2__cons__car(cause, leaf_iter);
	{
	  f2ptr count = assert_value(f2__redblacktree__lookup_key_count(cause, overlapping_right_redblacktree, element));
	  raw__ptypehash__add(cause, right_element_ptypehash, element, count);
	}
	leaf_iter = f2__cons__cdr(cause, leaf_iter);
      }
    }
    ptypehash__iteration(cause, left_element_ptypehash, element, count,
			 f2ptr right__count = raw__ptypehash__lookup(cause, right_element_ptypehash, element);
			 if ((! raw__ptypehash__contains(cause, right_element_ptypehash, element)) ||
			     (! raw__eq(cause, count, right__count))) {
			   return new__error(f2list10__new(cause,
							   new__symbol(cause, "bug_name"),     new__symbol(cause, "interval_tree_node_failed_validity_assertion"),
							   new__symbol(cause, "this"),         this,
							   new__symbol(cause, "count"),        count,
							   new__symbol(cause, "right__count"), right__count,
							   new__symbol(cause, "element"),      element));
			 }
			 );
    ptypehash__iteration(cause, right_element_ptypehash, element, count,
			 f2ptr left__count = raw__ptypehash__lookup(cause, left_element_ptypehash, element);
			 if ((! raw__ptypehash__contains(cause, left_element_ptypehash, element)) ||
			     (! raw__eq(cause, count, left__count))) {
			   return new__error(f2list10__new(cause,
							   new__symbol(cause, "bug_name"),    new__symbol(cause, "interval_tree_node_failed_validity_assertion"),
							   new__symbol(cause, "this"),        this,
							   new__symbol(cause, "count"),       count,
							   new__symbol(cause, "left__count"), left__count,
							   new__symbol(cause, "element"),     element));
			 }
			 );
  }
  return nil;
}

f2ptr f2__interval_tree_node__assert_valid(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__assert_valid(cause, this);
}
export_cefunk1(interval_tree_node__assert_valid, this, 0,
	       "Asserts the validity of this interval_tree_node object.");


f2ptr raw__interval_tree_node__assert_valid_recursively(f2ptr cause, f2ptr this) {
  assert_value(raw__interval_tree_node__assert_valid(cause, this));
  f2ptr left_node  = f2__interval_tree_node__left_node( cause, this);
  f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
  if (left_node != nil) {
    assert_value(raw__interval_tree_node__assert_valid(cause, left_node));
  }
  if (right_node != nil) {
    assert_value(raw__interval_tree_node__assert_valid(cause, right_node));
  }
  return nil;
}

f2ptr f2__interval_tree_node__assert_valid_recursively(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__assert_valid_recursively(cause, this);
}


boolean_t raw__interval_tree_node__is_empty(f2ptr cause, f2ptr this) {
  f2ptr overlapping_left_redblacktree = f2__interval_tree_node__overlapping_left_redblacktree(cause, this);
  return (f2__redblacktree__is_empty(cause, overlapping_left_redblacktree) != nil);
}

f2ptr f2__interval_tree_node__is_empty(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return f2bool__new(raw__interval_tree_node__is_empty(cause, this));
}


f2ptr raw__interval_tree_node__simple_insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr return_value = nil;
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  {
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
      return_value = this;
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
	return_value = assert_value(raw__interval_tree_node__simple_insert(cause, left_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
      } else {
	// interval is completely to the right of the center value of this node
	f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
	if (right_node == nil) {
	  f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, left_value, right_value)));
	  right_node = f2__interval_tree_node__new(cause, nil, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
	  f2__interval_tree_node__parent_node__set(cause, right_node, this);
	  f2__interval_tree_node__right_node__set( cause, this,       right_node);
	}
	return_value = assert_value(raw__interval_tree_node__simple_insert(cause, right_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
      }
    }
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return return_value;
}

f2ptr f2__interval_tree_node__simple_insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__simple_insert(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
export_cefunk7(interval_tree_node__simple_insert, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk, 0,
	    "Inserts a new interval element into this interval_tree.");


f2ptr raw__interval_tree_node__simple_remove(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  f2ptr return_value = nil;
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  {
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
      return_value = this;
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
	return_value = catch_value(raw__interval_tree_node__simple_remove(cause, left_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk),
				   f2list6__new(cause,
						new__symbol(cause, "bug_name"), new__symbol(cause, "error_in_recursive_simple_remove"),
						new__symbol(cause, "this"),     this,
						new__symbol(cause, "element"),  element));
      } else {
	// interval is completely to the right of the center value of this node
	f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
	if (right_node == nil) {
	  return new__error(f2list6__new(cause,
					 new__symbol(cause, "bug_name"), new__symbol(cause, "failure_to_find_element"),
					 new__symbol(cause, "this"),     this,
					 new__symbol(cause, "element"),  element));
	}
	return_value = catch_value(raw__interval_tree_node__simple_remove(cause, right_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk),
				   f2list6__new(cause,
						new__symbol(cause, "bug_name"), new__symbol(cause, "error_in_recursive_simple_remove"),
						new__symbol(cause, "this"),     this,
						new__symbol(cause, "element"),  element));			 
      }
    }
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return return_value;
}

f2ptr f2__interval_tree_node__simple_remove(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__simple_remove(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
}
export_cefunk6(interval_tree_node__simple_remove, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, 0,
	    "Inserts a new interval element into this interval_tree.");


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

f2ptr raw__interval_tree_node__list_of_found_and_removed_overlapping_intervals(f2ptr cause, f2ptr this, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  // remove elements that will need to be moved up.
  f2ptr found_and_removed_element_list = f2__list__new(cause, nil);
  {
    f2ptr overlapping_interval = assert_value(f2__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(cause, this, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
    while (overlapping_interval != nil) {
      //catch_value(raw__interval_tree_node__simple_remove(cause, lower_node, overlapping_interval, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk),
      //	    f2list10__new(cause,
      //			  new__symbol(cause, "bug_name"),             new__symbol(cause, "bad_value_returned_by_add_intervals_containing_value_could_not_be_found_in_simple_remove"),
      //			  new__symbol(cause, "move_up_element_list"), move_up_element_list,
      //			  new__symbol(cause, "center_value"),         upper_node__center_value,
      //			  new__symbol(cause, "upper_node"),           upper_node,
      //			  new__symbol(cause, "lower_node"),           lower_node));
      raw__list__add(cause, found_and_removed_element_list, overlapping_interval);
      overlapping_interval = assert_value(f2__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(cause, this, center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
    }
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return found_and_removed_element_list;
}

f2ptr raw__interval_tree_node__insert_list_of_intervals(f2ptr cause, f2ptr this, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  // now fix overlapping sets.
  {
    f2ptr upper_node = this;
    list__iteration(cause, list, element,
		    assert_value(f2__interval_tree_node__simple_insert(cause, upper_node, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
		    );
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return nil;
}

f2ptr raw__interval_tree_node__rotate_left(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  
  //    this                 right    //
  //        \       =>      /         //
  //         right      this          //
  
  f2ptr right_node            = f2__interval_tree_node__right_node(cause, this);
  f2ptr right_node__left_node = f2__interval_tree_node__left_node(cause, right_node);
  
  f2ptr right_node__center_value = f2__interval_tree_node__center_value(cause, right_node);
  f2ptr move_up_interval_list    = assert_value(raw__interval_tree_node__list_of_found_and_removed_overlapping_intervals(cause, this, right_node__center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  
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
  
  assert_value(raw__interval_tree_node__insert_list_of_intervals(cause, right_node, move_up_interval_list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return nil;
}

f2ptr raw__interval_tree_node__rotate_right(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  
  //         this      left         //
  //        /      =>      \        //
  //    left                this    //
  
  f2ptr left_node             = f2__interval_tree_node__left_node( cause, this);
  f2ptr left_node__right_node = f2__interval_tree_node__right_node(cause, left_node);
  
  f2ptr left_node__center_value = f2__interval_tree_node__center_value(cause, left_node);
  f2ptr move_up_interval_list   = assert_value(raw__interval_tree_node__list_of_found_and_removed_overlapping_intervals(cause, this, left_node__center_value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  
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
  
  assert_value(raw__interval_tree_node__insert_list_of_intervals(cause, left_node, move_up_interval_list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
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

f2ptr f2__interval_tree_node__head(f2ptr cause, f2ptr this) {
  assert_argument_type_or_nil(interval_tree_node, this);
  return raw__interval_tree_node__head(cause, this);
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

f2ptr f2__interval_tree_node__minimum_node(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__minimum_node(cause, this);
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

f2ptr f2__interval_tree_node__maximum_node(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__maximum_node(cause, this);
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
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  f2ptr insert_node        = assert_value(raw__interval_tree_node__simple_insert(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  f2ptr insert_node__color = f2__interval_tree_node__color(cause, insert_node);
  if (insert_node__color == nil) {
    // node is new, so we need to check the structure of the red-black tree.
    insert_node__color = new__symbol(cause, "red");
    f2__interval_tree_node__color__set(cause, insert_node, insert_node__color);
    // check insert case 1
    assert_value(raw__interval_tree_node__insert_case_1(cause, insert_node, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return nil;
}

f2ptr f2__interval_tree_node__insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__insert(cause, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
}
export_cefunk7(interval_tree_node__insert, this, element, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk, 0,
	    "Inserts a new interval element into this interval_tree.");



///vvvv

f2ptr raw__interval_tree_node__delete_case_6(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  f2__interval_tree_node__color__set(cause, this__sibling, f2__interval_tree_node__color(cause, f2__interval_tree_node__parent_node(cause, this)));
  f2__interval_tree_node__color__set(cause, f2__interval_tree_node__parent_node(cause, this), new__symbol(cause, "black"));
  if (raw__eq(cause, this, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, this)))) {
    // Here, this__sibling->right->color == rbt_color__red.
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__right_node(cause, this__sibling), new__symbol(cause, "black"));
    assert_value(raw__interval_tree_node__rotate_left(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  } else {
    // Here, this__sibling->left->color == rbt_color__red.
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__left_node(cause, this__sibling), new__symbol(cause, "black"));
    assert_value(raw__interval_tree_node__rotate_right(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr raw__interval_tree_node__delete_case_5(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (raw__eq(cause, this, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, this))) &&
      raw__interval_tree_node__is_black(cause, this__sibling) &&
      raw__interval_tree_node__is_red(  cause, f2__interval_tree_node__left_node( cause, this__sibling)) &&
      raw__interval_tree_node__is_black(cause, f2__interval_tree_node__right_node(cause, this__sibling))) {
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__left_node(cause, this__sibling), new__symbol(cause, "black"));
    assert_value(raw__interval_tree_node__rotate_right(cause, this__sibling, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  } else if (raw__eq(cause, this, f2__interval_tree_node__right_node(cause, f2__interval_tree_node__parent_node(cause, this))) &&
	     raw__interval_tree_node__is_black(cause, this__sibling) &&
	     raw__interval_tree_node__is_red(  cause, f2__interval_tree_node__right_node(cause, this__sibling)) &&
	     raw__interval_tree_node__is_black(cause, f2__interval_tree_node__left_node( cause, this__sibling))) {
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__right_node(cause, this__sibling), new__symbol(cause, "black"));
    assert_value(raw__interval_tree_node__rotate_left(cause, this__sibling, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  assert_value(raw__interval_tree_node__delete_case_6(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  return nil;
}

f2ptr raw__interval_tree_node__delete_case_4(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (raw__interval_tree_node__is_red(  cause, f2__interval_tree_node__parent_node(cause, this)) &&
      raw__interval_tree_node__is_black(cause, this__sibling) &&
      raw__interval_tree_node__is_black(cause, f2__interval_tree_node__left_node( cause, this__sibling)) &&
      raw__interval_tree_node__is_black(cause, f2__interval_tree_node__right_node(cause, this__sibling))) {
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__parent_node(cause, this), new__symbol(cause, "black"));
  } else if (f2__interval_tree_node__parent_node(cause, this) != nil) {
    assert_value(raw__interval_tree_node__delete_case_5(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr raw__interval_tree_node__delete_case_3(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (this__sibling) {
    if (raw__interval_tree_node__is_black(cause, f2__interval_tree_node__parent_node(cause, this)) &&
	raw__interval_tree_node__is_black(cause, this__sibling) &&
	raw__interval_tree_node__is_black(cause, f2__interval_tree_node__left_node( cause, this__sibling)) &&
	raw__interval_tree_node__is_black(cause, f2__interval_tree_node__right_node(cause, this__sibling))) {
      f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
      assert_value(raw__interval_tree_node__delete_case_1(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
    } else {
      assert_value(raw__interval_tree_node__delete_case_4(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
    }
  }
  return nil;
}

f2ptr raw__interval_tree_node__delete_case_2(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr this__sibling = raw__interval_tree_node__sibling_node(cause, this);
  if (raw__interval_tree_node__is_red(cause, this__sibling)) {
    f2__interval_tree_node__color__set(cause, f2__interval_tree_node__parent_node(cause, this), new__symbol(cause, "red"));
    f2__interval_tree_node__color__set(cause, this__sibling, new__symbol(cause, "black"));
    if (raw__eq(cause, this, f2__interval_tree_node__left_node(cause, f2__interval_tree_node__parent_node(cause, this)))) {
      assert_value(raw__interval_tree_node__rotate_left(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
    } else {
      assert_value(raw__interval_tree_node__rotate_right(cause, f2__interval_tree_node__parent_node(cause, this), left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
    }
  }
  assert_value(raw__interval_tree_node__delete_case_3(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  return nil;
}

f2ptr raw__interval_tree_node__delete_case_1(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  if (f2__interval_tree_node__parent_node(cause, this) != nil) {
    assert_value(raw__interval_tree_node__delete_case_2(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk));
  }
  return nil;
}

f2ptr f2__interval_tree_node__delete_case_1(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  assert_argument_type(interval_tree_node, this);
  assert_argument_type(funkable,           left_value_funk);
  assert_argument_type(funkable,           right_value_funk);
  assert_argument_type(funkable,           value_equality_funk);
  assert_argument_type(funkable,           value_comparison_funk);
  assert_argument_type(funkable,           value_center_funk);
  return raw__interval_tree_node__delete_case_1(cause, this, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);
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

f2ptr raw__interval_tree_node__swap_nodes(f2ptr cause, f2ptr node1, f2ptr node2) {
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
  return nil;
}

f2ptr f2__interval_tree_node__swap_nodes(f2ptr cause, f2ptr node1, f2ptr node2) {
  assert_argument_type(interval_tree_node, node1);
  assert_argument_type(interval_tree_node, node2);
  return raw__interval_tree_node__swap_nodes(cause, node1, node2);
}

///^^^^^

f2ptr raw__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(f2ptr cause, f2ptr this, f2ptr value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
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
				       f2ptr overlapping_left_redblacktree = f2__interval_tree_node__overlapping_left_redblacktree(cause, this);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
				       assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
				       catch_value(f2__redblacktree__remove(cause, overlapping_right_redblacktree, element),
						   f2list10__new(cause,
								 new__symbol(cause, "bug_name"),                       new__symbol(cause, "element_is_not_in_overlapping_right_redblacktree"),
								 new__symbol(cause, "this"),                           this,
								 new__symbol(cause, "center_value"),                   value,
								 new__symbol(cause, "element"),                        element,
								 new__symbol(cause, "overlapping_right_redblacktree"), overlapping_right_redblacktree));
				       catch_value(f2__redblacktree__remove(cause, overlapping_left_redblacktree, element),
						   f2list10__new(cause,
								 new__symbol(cause, "bug_name"),                      new__symbol(cause, "element_is_not_in_overlapping_left_redblacktree"),
								 new__symbol(cause, "this"),                          this,
								 new__symbol(cause, "center_value"),                  value,
								 new__symbol(cause, "element"),                       element,
								 new__symbol(cause, "overlapping_left_redblacktree"), overlapping_left_redblacktree));
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
				       assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
				       return element;
				     } else {
				       // value is greater than right_value of element, so stop looping.
				       goto raw__interval_tree_node__an_arbitrary_interval_containing_value____overlapping_right_redblacktree__done_with_redblacktree_iteration;
				     }
				     );
  raw__interval_tree_node__an_arbitrary_interval_containing_value____overlapping_right_redblacktree__done_with_redblacktree_iteration:
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    //if (center_value_equality == nil) {
      // descend right branch of tree
      {
	f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
	if (right_node != nil) {
	  f2ptr interval = assert_value(raw__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(cause, right_node, value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
	  if (interval != nil) {
	    return interval;
	  }
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
				      f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
				      assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
				      catch_value(f2__redblacktree__remove(cause, overlapping_left_redblacktree, element),
						  f2list10__new(cause,
								new__symbol(cause, "bug_name"),                      new__symbol(cause, "element_is_not_in_overlapping_left_redblacktree"),
								new__symbol(cause, "this"),                          this,
								new__symbol(cause, "center_value"),                  value,
								new__symbol(cause, "element"),                       element,
								new__symbol(cause, "overlapping_left_redblacktree"), overlapping_left_redblacktree));
				      catch_value(f2__redblacktree__remove(cause, overlapping_right_redblacktree, element),
						  f2list10__new(cause,
								new__symbol(cause, "bug_name"),                       new__symbol(cause, "element_is_not_in_overlapping_right_redblacktree"),
								new__symbol(cause, "this"),                           this,
								new__symbol(cause, "center_value"),                   value,
								new__symbol(cause, "element"),                        element,
								new__symbol(cause, "overlapping_right_redblacktree"), overlapping_right_redblacktree));
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
				      assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
				      return element;
				    } else {
				      // left_value of element is greater than the value, so stop looping.
				      goto raw__interval_tree_node__an_arbitrary_interval_containing_value____overlapping_left_redblacktree__done_with_redblacktree_iteration;
				    }
				    );
  raw__interval_tree_node__an_arbitrary_interval_containing_value____overlapping_left_redblacktree__done_with_redblacktree_iteration:
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
    assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
    //if (center_value_equality == nil) {
      // descend left branch of tree
      {
	f2ptr left_node = f2__interval_tree_node__left_node(cause, this);
	if (left_node != nil) {
	  f2ptr interval = assert_value(raw__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(cause, left_node, value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
	  if (interval != nil) {
	    return interval;
	  }
	}
      }
      //}
  }
  return nil;
}

f2ptr f2__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(f2ptr cause, f2ptr this, f2ptr value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
  assert_argument_type(interval_tree_node, this);
  assert_argument_type(funkable,           left_value_funk);
  assert_argument_type(funkable,           right_value_funk);
  assert_argument_type(funkable,           value_equality_funk);
  assert_argument_type(funkable,           value_comparison_funk);
  return raw__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(cause, this, value, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk);
}


f2ptr raw__interval_tree_node__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  f2ptr center_value                   = f2__interval_tree_node__center_value(cause, this);
  f2ptr center_value_comparison        = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, center_value, value)));
  f2ptr value_center_comparison        = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, value,        center_value)));
  f2ptr center_value_equality          = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_equality_funk,   f2list2__new(cause, center_value, value)));
  f2ptr set_found_in_right_overlapping = f2__set__new(cause);
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
				       f2__set__add(cause, set_found_in_right_overlapping, element);
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
				    if (! raw__set__contains(cause, set_found_in_right_overlapping, element)) {
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
	  assert_value(raw__interval_tree_node__add_intervals_containing_value_to_list(cause, left_node, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk));
	}
      }
      //}
  }

#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
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
export_cefunk7(interval_tree_node__add_intervals_containing_value_to_list, this, value, list, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, 0,
	       "Adds intervals from this interval_tree_node that contain the given value to the given list.");


f2ptr raw__interval_tree_node__overlapping_elements(f2ptr cause, f2ptr this) {
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  f2ptr overlapping_left_redblacktree = f2__interval_tree_node__overlapping_left_redblacktree(cause, this);
  f2ptr return_value = f2__redblacktree__leaves(cause, overlapping_left_redblacktree);
#if (F2__DEBUG__INTERVAL_TREE_NODE == 1)
  assert_value(f2__interval_tree_node__assert_valid(cause, this));
#endif
  return return_value;
}

f2ptr f2__interval_tree_node__overlapping_elements(f2ptr cause, f2ptr this) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__overlapping_elements(cause, this);
}
export_cefunk1(interval_tree_node__overlapping_elements, this, 0,
	       "Returns a new list containing the interval elements that overlap this node's center_value.");


f2ptr raw__interval_tree_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
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
export_cefunk2(interval_tree_node__terminal_print_with_frame, this, terminal_print_frame, 0,
	       "");


f2ptr f2__interval_tree_node_type__new_aux(f2ptr cause) {
  f2ptr this = f2__interval_tree_node_type__new(cause);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "assert_valid"),                           f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__assert_valid")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "simple_insert"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__simple_insert")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "simple_remove"),                          f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__simple_remove")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                                 f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__insert")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "add_intervals_containing_value_to_list"), f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__add_intervals_containing_value_to_list")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, "overlapping_elements"),                   f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__overlapping_elements")));
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"),              f2__core_extension_funk__new(cause, new__symbol(cause, "interval_tree"), new__symbol(cause, "interval_tree_node__terminal_print_with_frame")));
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
  f2__add_type(cause, new__symbol(cause, "interval_tree"),      f2__interval_tree_type__new_aux(cause));
  f2__add_type(cause, new__symbol(cause, "interval_tree_node"), f2__interval_tree_node_type__new_aux(cause));
  status("interval_tree types defined.");
  return nil;
}
export_cefunk0(interval_tree__core_extension__define_types, 0, "");

f2ptr f2__interval_tree__core_extension__destroy(f2ptr cause) {
  status("interval_tree destroyed.");
  return nil;
}
export_cefunk0(interval_tree__core_extension__destroy, 0, "");



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

#include "funk2.h"

// redblacktree

def_primobject_4_slot(redblacktree, mutate_mutex, head, value_funk, value_comparison_funk);

f2ptr raw__redblacktree__new(f2ptr cause, f2ptr head, f2ptr value_funk, f2ptr value_comparison_funk) {
  f2ptr mutate_mutex = f2__cmutex__new(cause);
  return f2redblacktree__new(cause, mutate_mutex, head, value_funk, value_comparison_funk);
}

f2ptr f2__redblacktree__new(f2ptr cause, f2ptr value_funk, f2ptr value_comparison_funk) {
  return raw__redblacktree__new(cause, nil, value_funk, value_comparison_funk);
}
def_pcfunk2(redblacktree__new, value_funk, value_comparison_funk,
	    "Returns a new redblacktree object.",
	    return f2__redblacktree__new(this_cause, value_funk, value_comparison_funk));


// redblacktree_node

def_primobject_5_slot(redblacktree_node, parent, left, right, color, count_key_ptypehash);

f2ptr raw__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color) {
  f2ptr count_key_ptypehash = f2__ptypehash__new(cause);
  return f2redblacktree_node__new(cause, parent, left, right, color, count_key_ptypehash);
}

f2ptr f2__redblacktree_node__new(f2ptr cause) {
  return raw__redblacktree_node__new(cause, nil, nil, nil, nil);
}
def_pcfunk0(redblacktree_node__new,
	    "",
	    return f2__redblacktree_node__new(this_cause));


// ******************************************************************
// **                                                              **
// ** The following code was originally downloaded from a webpage. **
// ** Please see the original source for further information about **
// ** the community of authors:                                    **
// **                                                              **
// **   http://en.wikipedia.org/wiki/Red-black_tree                **
// **                                                              **
// ******************************************************************

boolean_t raw__redblacktree_node__is_black(f2ptr cause, f2ptr this) {
  if ((! this) ||
      raw__eq(cause, f2__redblacktree_node__color(cause, this), new__symbol(cause, "black"))) {
    return boolean__true;
  }
  return boolean__false;
}

boolean_t raw__redblacktree_node__is_red(f2ptr cause, f2ptr this) {
  return (! raw__redblacktree_node__is_black(cause, this));
}

void raw__redblacktree_node__rotate_left(f2ptr cause, f2ptr this) {
  f2ptr that = f2__redblacktree_node__right(cause, this);                                   // Set that.
  f2__redblacktree_node__right__set(cause, this, f2__redblacktree_node__left(cause, that)); // Turn that's left subtree into this's right subtree.
  if (f2__redblacktree_node__left(cause, that)) {
    f2__redblacktree_node__parent__set(cause, f2__redblacktree_node__left(cause, that), this);
  }
  f2__redblacktree_node__parent__set(cause, that, f2__redblacktree_node__parent(cause, this)); // Link this's parent to that.
  if (f2__redblacktree_node__parent(cause, this) != nil) {
    if (raw__eq(cause, this, f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this)))) {
      f2__redblacktree_node__left__set(cause, f2__redblacktree_node__parent(cause, this), that);
    } else {
      f2__redblacktree_node__right__set(cause, f2__redblacktree_node__parent(cause, this), that);
    }
  }
  f2__redblacktree_node__left__set(cause, that, this); // Put this on that's left.
  f2__redblacktree_node__parent__set(cause, this, that);
}

void raw__redblacktree_node__rotate_right(f2ptr cause, f2ptr this) {
  f2ptr that = f2__redblacktree_node__left(cause, this);      // Set that.
  f2__redblacktree_node__left__set(cause, this, f2__redblacktree_node__right(cause, that));     // Turn that's right subtree into this's left subtree.
  if (f2__redblacktree_node__right(cause, that)) {
    f2__redblacktree_node__parent__set(cause, f2__redblacktree_node__right(cause, that), this);
  }
  f2__redblacktree_node__parent__set(cause, that, f2__redblacktree_node__parent(cause, this));    // Link this's parent to that.
  if (f2__redblacktree_node__parent(cause, this) != nil) {
    if (raw__eq(cause, this, f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this)))) {
      f2__redblacktree_node__left__set(cause, f2__redblacktree_node__parent(cause, this), that);
    } else {
      f2__redblacktree_node__right__set(cause, f2__redblacktree_node__parent(cause, this), that);
    }
  }
  f2__redblacktree_node__right__set(cause, that, this);             // Put this on that's left.
  f2__redblacktree_node__parent__set(cause, this, that);
}

f2ptr raw__redblacktree_node__grandparent(f2ptr cause, f2ptr this) {
  if ((this != nil) && (f2__redblacktree_node__parent(cause, this) != nil)) {
    return f2__redblacktree_node__parent(cause, f2__redblacktree_node__parent(cause, this));
  } else {
    return nil;
  }
}

f2ptr raw__redblacktree_node__uncle(f2ptr cause, f2ptr this) {
  f2ptr this__grandparent = raw__redblacktree_node__grandparent(cause, this);
  //
  // Here we blindly assume that this__grandparent != nil, i.e. we
  // suppose a rootless tree.  However, a real tree always have an
  // uppermost root node which we can't go past, so an appropriate
  // tree boundary check would be required here, such as the
  // following:
  //
  //if (this__grandparent == nil) {
  //  return nil;
  //}
  if (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__left(cause, this__grandparent)) {
    return f2__redblacktree_node__right(cause, this__grandparent);
  }
  return f2__redblacktree_node__left(cause, this__grandparent);
}

f2ptr raw__redblacktree_node__sibling(f2ptr cause, f2ptr node) {
  if (node == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, node))) {
    return f2__redblacktree_node__right(cause, f2__redblacktree_node__parent(cause, node));
  } else {
    return f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, node));
  }
}

// Case 5: The parent P is red but the uncle U is black, the new node
// N is the left child of P, and P is the left child of its parent
// G. In this case, a right rotation on the parent P is performed; the
// result is a tree where the former parent P is now the parent of
// both the new node N and the former grandparent G. G is known to be
// black, since its former child P could not have been red
// otherwise. Then, the colors of P and G are switched, and the
// resulting tree satisfies Property 4 (Both children of every red
// node are black). Property 5 (All paths from any given node to its
// leaf nodes contain the same number of black nodes) also remains
// satisfied, since all paths that went through any of these three
// nodes went through G before, and now they all go through P. In each
// case, this is the only black node of the three.

void raw__redblacktree_node__insert_case5(f2ptr cause, f2ptr this) {
  f2ptr this__grandparent = raw__redblacktree_node__grandparent(cause, this);
  //printf("\ninsert_case5: setting to black...");
  //rbt_node__print(this->parent);
  f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "black"));
  //printf("\ninsert_case5: setting to red...");
  //rbt_node__print(node__grandparent);
  f2__redblacktree_node__color__set(cause, this__grandparent, new__symbol(cause, "red"));
  if ((this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) && (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__left(cause, this__grandparent))) {
    raw__redblacktree_node__rotate_right(cause, this__grandparent);
  } else {
    //
    // Here, (this == this->parent->right) && (this->parent == this__grandparent->right).
    //
    raw__redblacktree_node__rotate_left(cause, this__grandparent);
  }
}

// Case 4: The parent P is red but the uncle U is black; also, the new
// node N is the right child of P, and P in turn is the left child of
// its parent G. In this case, a left rotation that switches the roles
// of the new node N and its parent P can be performed; then, the
// former parent node P is dealt with using Case 5 (relabeling N and
// P) because property 4 (Both children of every red node are black)
// is still violated. The rotation causes some paths (those in the
// sub-tree labelled "1") to pass through the new node where they did
// not before, but both these nodes are red, so Property 5 (All paths
// from any given node to its leaf nodes contain the same number of
// black nodes) is not violated by the rotation.

void raw__redblacktree_node__insert_case4(f2ptr cause, f2ptr this) {
  f2ptr this__grandparent = raw__redblacktree_node__grandparent(cause, this);
  if ((this == f2__redblacktree_node__right(cause, f2__redblacktree_node__parent(cause, this))) && (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__left(cause, this__grandparent))) {
    raw__redblacktree_node__rotate_left(cause, f2__redblacktree_node__parent(cause, this));
    this = f2__redblacktree_node__left(cause, this);
  } else if ((this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) && (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__right(cause, this__grandparent))) {
    raw__redblacktree_node__rotate_right(cause, f2__redblacktree_node__parent(cause, this));
    this = f2__redblacktree_node__right(cause, this);
  }
  raw__redblacktree_node__insert_case5(cause, this);
}

// Note: In the previous insert cases, it is assumed that the parent node P
// is the left child of its parent. If it is the right child, left and
// right should be reversed throughout cases 4 and 5. The code samples
// take care of this.

// Case 3: If both the parent P and the uncle U are red, then both
// nodes can be repainted black and the grandparent G becomes red (to
// maintain Property 5 (All paths from any given node to its leaf
// nodes contain the same number of black nodes)). Now, the new red
// node N has a black parent. Since any path through the parent or
// uncle must pass through the grandparent, the number of black nodes
// on these paths has not changed. However, the grandparent G may now
// violate properties 2 (The root is black) or 4 (Both children of
// every red node are black) (property 4 possibly being violated since
// G may have a red parent). To fix this, this entire procedure is
// recursively performed on G from case 1.

// forward declaration
void raw__redblacktree_node__insert_case1(f2ptr cause, f2ptr this);

void raw__redblacktree_node__insert_case3(f2ptr cause, f2ptr this) {
  f2ptr this__uncle = raw__redblacktree_node__uncle(cause, this);
  f2ptr this__grandparent;
  if ((this__uncle != nil) && (raw__eq(cause, f2__redblacktree_node__color(cause, this__uncle), new__symbol(cause, "red")))) {
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "black"));
    f2__redblacktree_node__color__set(cause, this__uncle, new__symbol(cause, "black"));
    this__grandparent = raw__redblacktree_node__grandparent(cause, this);
    f2__redblacktree_node__color__set(cause, this__grandparent, new__symbol(cause, "red"));
    raw__redblacktree_node__insert_case1(cause, this__grandparent);
  } else {
    raw__redblacktree_node__insert_case4(cause, this);
  }
}

// Case 2: The new node's parent P is black, so Property 4 (Both
// children of every red node are black) is not invalidated. In this
// case, the tree is still valid. Property 5 (All paths from any given
// node to its leaf nodes contain the same number of black nodes) is
// not threatened, because the new node N has two black leaf children,
// but because N is red, the paths through each of its children have
// the same number of black nodes as the path through the leaf it
// replaced, which was black, and so this property remains satisfied.

void raw__redblacktree_node__insert_case2(f2ptr cause, f2ptr this) {
  if (raw__eq(cause, f2__redblacktree_node__color(cause, f2__redblacktree_node__parent(cause, this)), new__symbol(cause, "black"))) {
    return; // Tree is still valid
  } else {
    raw__redblacktree_node__insert_case3(cause, this);
  }
}

// Note: In the previous insert cases it can be assumed that N has a
// grandparent node G, because its parent P is red, and if it were the
// root, it would be black. Thus, N also has an uncle node U, although
// it may be a leaf in cases 4 and 5.

// Case 1: The new node N is at the root of the tree. In this case, it
// is repainted black to satisfy Property 2 (The root is black). Since
// this adds one black node to every path at once, Property 5 (All
// paths from any given node to its leaf nodes contain the same number
// of black nodes) is not violated.

void raw__redblacktree_node__insert_case1(f2ptr cause, f2ptr this) {
  if (f2__redblacktree_node__parent(cause, this) == nil) {
    f2__redblacktree_node__color__set(cause, this, new__symbol(cause, "black"));
  } else {
    raw__redblacktree_node__insert_case2(cause, this);
  }
}


f2ptr raw__redblacktree_node__head(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter   = this;
  f2ptr parent = f2__redblacktree_node__parent(cause, this);
  while (parent) {
    iter   = parent;
    parent = f2__redblacktree_node__parent(cause, iter);
  }
  return iter;
}


f2ptr raw__redblacktree_node__minimum_node(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter = this;
  f2ptr left = f2__redblacktree_node__left(cause, this);
  while (left) {
    iter = left;
    left = f2__redblacktree_node__left(cause, iter);
  }
  return iter;
}


f2ptr raw__redblacktree_node__maximum_node(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter  = this;
  f2ptr right = f2__redblacktree_node__right(cause, this);
  while (right) {
    iter  = right;
    right = f2__redblacktree_node__right(cause, iter);
  }
  return iter;
}


f2ptr raw__redblacktree_node__minimum_not_less_than__node(f2ptr cause, f2ptr this, f2ptr value_funk, f2ptr value_comparison_funk, f2ptr value) {
  f2ptr fiber               = f2__this__fiber(cause);
  f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, this);
  f2ptr key                 = f2__ptypehash__an_arbitrary_key(cause, count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this,
				     new__symbol(cause, "value"),    value));
    }
  }
  f2ptr key__value        = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, key)));
  f2ptr comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, key__value, value)));
  if (comparison_result != nil) {
    f2ptr right_node        = f2__redblacktree_node__right(cause, this);
    if (right_node == nil) {
      return nil;
    } else {
      f2ptr better_right_node = assert_value(raw__redblacktree_node__minimum_not_less_than__node(cause, right_node, value_funk, value_comparison_funk, value));
      if (better_right_node == nil) {
	return nil;
      } else {
	return better_right_node;
      }
    }
  } else {
    f2ptr left_node = f2__redblacktree_node__left(cause, this);
    if (left_node == nil) {
      return this;
    } else {
      f2ptr better_left_node = assert_value(raw__redblacktree_node__minimum_not_less_than__node(cause, left_node, value_funk, value_comparison_funk, value));
      if (better_left_node == nil) {
	return this;
      } else {
	return better_left_node;
      }
    }
  }
}


f2ptr raw__redblacktree_node__maximum_not_greater_than_or_equal_to__node(f2ptr cause, f2ptr this, f2ptr value_funk, f2ptr value_comparison_funk, f2ptr value) {
  f2ptr fiber               = f2__this__fiber(cause);
  f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, this);
  f2ptr key                 = f2__ptypehash__an_arbitrary_key(cause, count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this,
				     new__symbol(cause, "value"),    value));
    }
  }
  f2ptr key__value        = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, key)));
  f2ptr comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, key__value, value)));
  if (comparison_result == nil) {
    f2ptr left_node        = f2__redblacktree_node__left(cause, this);
    if (left_node == nil) {
      return nil;
    } else {
      f2ptr better_left_node = assert_value(raw__redblacktree_node__maximum_not_greater_than_or_equal_to__node(cause, left_node, value_funk, value_comparison_funk, value));
      if (better_left_node == nil) {
	return nil;
      } else {
	return better_left_node;
      }
    }
  } else {
    f2ptr right_node = f2__redblacktree_node__right(cause, this);
    if (right_node == nil) {
      return this;
    } else {
      f2ptr better_right_node = assert_value(raw__redblacktree_node__maximum_not_greater_than_or_equal_to__node(cause, right_node, value_funk, value_comparison_funk, value));
      if (better_right_node == nil) {
	return this;
      } else {
	return better_right_node;
      }
    }
  }
}


f2ptr raw__redblacktree_node__simple_binary_insert_key(f2ptr cause, f2ptr this, f2ptr key, f2ptr value_funk, f2ptr value_comparison_funk) {
#ifdef DEBUG_REDBLACKTREE
  //debug__assert(!raw__redblacktree_node__contains_node(cause, this, new_node), nil, "raw__redblacktree_node__simple_binary_insert failed: node already exists in root.");
#endif
  f2ptr new_node                       = nil;
  f2ptr this__count_key_ptypehash      = f2__redblacktree_node__count_key_ptypehash(cause, this);
  f2ptr this__key                      = f2__ptypehash__an_arbitrary_key(cause, this__count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, this__count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this,
				     new__symbol(cause, "key"),      key));
    }
  }
  f2ptr fiber                          = f2__this__fiber(cause);
  f2ptr key__value                     = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, key)));
  f2ptr this__key__value               = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, this__key)));
  f2ptr key_this_key_comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, key__value, this__key__value)));
  if (key_this_key_comparison_result != nil) {
    if (f2__redblacktree_node__left(cause, this) == nil) {
      
      new_node                  = assert_value(f2__redblacktree_node__new(cause));
      f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, new_node);
      f2__ptypehash__add(cause, count_key_ptypehash, key, f2integer__new(cause, 1));
      f2__redblacktree_node__color__set( cause, new_node, new__symbol(cause, "red"));
      //f2__redblacktree_node__parent__set(cause, new_node, nil);
      //f2__redblacktree_node__left__set(  cause, new_node, nil);
      //f2__redblacktree_node__right__set( cause, new_node, nil);
      
      f2__redblacktree_node__parent__set(cause, new_node, this);
      f2__redblacktree_node__left__set(  cause, new_node, nil);
      f2__redblacktree_node__right__set( cause, new_node, nil);
      f2__redblacktree_node__left__set(  cause, this,     new_node);
    } else {
      new_node = assert_value(raw__redblacktree_node__simple_binary_insert_key(cause, f2__redblacktree_node__left(cause, this), key, value_funk, value_comparison_funk));
    }
  } else {
    f2ptr this_key_key_comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, this__key__value, key__value)));
    if (this_key_key_comparison_result != nil) {
      if (f2__redblacktree_node__right(cause, this) == nil) {
	
	new_node                  = assert_value(f2__redblacktree_node__new(cause));
	f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, new_node);
	f2__ptypehash__add(cause, count_key_ptypehash, key, f2integer__new(cause, 1));
	f2__redblacktree_node__color__set( cause, new_node, new__symbol(cause, "red"));
	//f2__redblacktree_node__parent__set(cause, new_node, nil);
	//f2__redblacktree_node__left__set(  cause, new_node, nil);
	//f2__redblacktree_node__right__set( cause, new_node, nil);
	
	f2__redblacktree_node__parent__set(cause, new_node, this);
	f2__redblacktree_node__left__set(  cause, new_node, nil);
	f2__redblacktree_node__right__set( cause, new_node, nil);
	f2__redblacktree_node__right__set( cause, this,     new_node);
	
      } else {
	new_node = assert_value(raw__redblacktree_node__simple_binary_insert_key(cause, f2__redblacktree_node__right(cause, this), key, value_funk, value_comparison_funk));
      }
    } else { // key is equal to keys in this node
      // add to this node set
      
      f2ptr old_count = f2__ptypehash__lookup(cause, this__count_key_ptypehash, key);
      if (old_count == nil) {
	f2__ptypehash__add(cause, this__count_key_ptypehash, key, f2integer__new(cause, 1));
      } else {
	s64 old_count__i = f2integer__i(old_count, cause);
	f2__ptypehash__add(cause, this__count_key_ptypehash, key, f2integer__new(cause, old_count__i + 1));
      }
      
      // no need for creating a new node.
      //new_node = nil;
    }
  }
  return new_node;
}

f2ptr raw__redblacktree_node__lookup_node_with_key(f2ptr cause, f2ptr this, f2ptr key, f2ptr value_funk, f2ptr value_comparison_funk) {
  f2ptr     this__count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, this);
  f2ptr     this__key                 = f2__ptypehash__an_arbitrary_key(cause, this__count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, this__count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this,
				     new__symbol(cause, "key"),      key));
    }
  }
  f2ptr fiber                          = f2__this__fiber(cause);
  f2ptr key__value                     = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, key)));
  f2ptr this__key__value               = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, this__key)));
  f2ptr key_this_key_comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, key__value, this__key__value)));
  if (key_this_key_comparison_result != nil) {
    f2ptr this__left = f2__redblacktree_node__left(cause, this);
    if (this__left == nil) {
      return nil;
    } else {
      return raw__redblacktree_node__lookup_node_with_key(cause, this__left, key, value_funk, value_comparison_funk);
    }
  } else {
    f2ptr this_key_key_comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, this__key__value, key__value)));
    if (this_key_key_comparison_result != nil) {
      f2ptr this__right = f2__redblacktree_node__right(cause, this);
      if (this__right == nil) {
	return nil;
      } else {
	return raw__redblacktree_node__lookup_node_with_key(cause, this__right, key, value_funk, value_comparison_funk);
      }
    } else {
      return this;
    }
  }
}

f2ptr raw__redblacktree__lookup_node_with_key(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr this__head = f2__redblacktree__head(cause, this);
  if (this__head == nil) {
    return nil;
  }
  f2ptr value_funk            = f2__redblacktree__value_funk(           cause, this);
  f2ptr value_comparison_funk = f2__redblacktree__value_comparison_funk(cause, this);
  return raw__redblacktree_node__lookup_node_with_key(cause, this__head, key, value_funk, value_comparison_funk);
}


f2ptr raw__redblacktree_node__lookup_key_count(f2ptr cause, f2ptr this, f2ptr key, f2ptr value_funk, f2ptr value_comparison_funk) {
  f2ptr this__count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, this);
  f2ptr this__key                 = f2__ptypehash__an_arbitrary_key(cause, this__count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, this__count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this,
				     new__symbol(cause, "key"),      key));
    }
  }
  f2ptr fiber                          = f2__this__fiber(cause);
  f2ptr key__value                     = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, key)));
  f2ptr this__key__value               = assert_value(f2__force_funk_apply(cause, fiber, value_funk, f2list1__new(cause, this__key)));
  f2ptr key_this_key_comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, key__value, this__key__value)));
  if (key_this_key_comparison_result != nil) {
    f2ptr this__left = f2__redblacktree_node__left(cause, this);
    if (this__left == nil) {
      return f2integer__new(cause, 0);
    } else {
      return raw__redblacktree_node__lookup_key_count(cause, this__left, key, value_funk, value_comparison_funk);
    }
  } else {
    f2ptr this_key_key_comparison_result = assert_value(f2__force_funk_apply(cause, fiber, value_comparison_funk, f2list2__new(cause, this__key__value, key__value)));
    if (this_key_key_comparison_result != nil) {
      f2ptr this__right = f2__redblacktree_node__right(cause, this);
      if (this__right == nil) {
	return f2integer__new(cause, 0);
      } else {
	return raw__redblacktree_node__lookup_key_count(cause, this__right, key, value_funk, value_comparison_funk);
      }
    } else {
      f2ptr count = raw__ptypehash__lookup(cause, this__count_key_ptypehash, key);
      if (count == nil) {
	return f2integer__new(cause, 0);
      }
      return count;
    }
  }
}

f2ptr raw__redblacktree__lookup_key_count(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr this__head = f2__redblacktree__head(cause, this);
  if (this__head == nil) {
    return f2integer__new(cause, 0);
  }
  f2ptr value_funk            = f2__redblacktree__value_funk(           cause, this);
  f2ptr value_comparison_funk = f2__redblacktree__value_comparison_funk(cause, this);
  return raw__redblacktree_node__lookup_key_count(cause, this__head, key, value_funk, value_comparison_funk);
}

f2ptr f2__redblacktree__lookup_key_count(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__lookup_key_count(cause, this, key);
}
def_pcfunk2(redblacktree__lookup_key_count, this, key,
	    "Returns the number of times the given key exists within this redblacktree.",
	    return f2__redblacktree__lookup_key_count(this_cause, this, key));


f2ptr raw__redblacktree_node__contains(f2ptr cause, f2ptr this, f2ptr key, f2ptr value_funk, f2ptr value_comparison_funk) {
  f2ptr count    = assert_value(raw__redblacktree_node__lookup_key_count(cause, this, key, value_funk, value_comparison_funk));
  s64   count__i = f2integer__i(count, cause);
  if (count__i != 0) {
    return f2bool__new(boolean__true);
  }
  return f2bool__new(boolean__false);
}

f2ptr f2__redblacktree_node__contains(f2ptr cause, f2ptr this, f2ptr key, f2ptr value_funk, f2ptr value_comparison_funk) {
  assert_argument_type(redblacktree_node, this);
  assert_argument_type(funkable,          value_funk);
  assert_argument_type(funkable,          value_comparison_funk);
  return raw__redblacktree_node__contains(cause, this, key, value_funk, value_comparison_funk);
}


f2ptr raw__redblacktree__contains(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr this__head = f2__redblacktree__head(cause, this);
  if (this__head == nil) {
    return f2bool__new(boolean__false);
  }
  f2ptr value_funk            = f2__redblacktree__value_funk(           cause, this);
  f2ptr value_comparison_funk = f2__redblacktree__value_comparison_funk(cause, this);
  return raw__redblacktree_node__contains(cause, this__head, key, value_funk, value_comparison_funk);
}

f2ptr f2__redblacktree__contains(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__contains(cause, this, key);
}
def_pcfunk2(redblacktree__contains, this, key,
	    "Returns the whether or not the given key exists within this redblacktree.",
	    return f2__redblacktree__contains(this_cause, this, key));



//void rbt_node__print(rbt_node_t* node) {
//  if (node == NULL) {
//    printf("nil");
//  } else {
//    printf("[%lx " f2size_t__fstr " %s ", (unsigned long)node, node->key, (node->color == rbt_color__red) ? "red" : ((node->color == rbt_color__black) ? "black" : "unknown"));
//    rbt_node__print(node->left);
//    printf(" . ");
//    rbt_node__print(node->right);
//    printf("]");
//  }
//}

//void rbt_tree__init(rbt_tree_t* tree, rbt_node_t* head) {
//  tree->head = head;
//}

//void rbt_tree__print(rbt_tree_t* tree) {
//  rbt_node__print(tree->head);
//}

f2ptr raw__redblacktree__simple_binary_insert_key(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr new_node = nil;
  if (f2__redblacktree__head(cause, this) == nil) {
    
    new_node                  = assert_value(f2__redblacktree_node__new(cause));
    f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, new_node);
    f2__ptypehash__add(cause, count_key_ptypehash, key, f2integer__new(cause, 1));
    f2__redblacktree_node__parent__set(cause, new_node, nil);
    f2__redblacktree_node__left__set(  cause, new_node, nil);
    f2__redblacktree_node__right__set( cause, new_node, nil);
    f2__redblacktree_node__color__set( cause, new_node, new__symbol(cause, "red"));
    
    f2__redblacktree__head__set(cause, this, new_node);
  } else {
    f2ptr value_funk            = f2__redblacktree__value_funk(           cause, this);
    f2ptr value_comparison_funk = f2__redblacktree__value_comparison_funk(cause, this);
    new_node = assert_value(raw__redblacktree_node__simple_binary_insert_key(cause, f2__redblacktree__head(cause, this), key, value_funk, value_comparison_funk));
  }
  return new_node;
}

f2ptr raw__redblacktree__insert_key(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr new_node = assert_value(raw__redblacktree__simple_binary_insert_key(cause, this, key));
  if (new_node != nil) {
    raw__redblacktree_node__insert_case1(cause, new_node);
    f2__redblacktree__head__set(cause, this, raw__redblacktree_node__head(cause, f2__redblacktree__head(cause, this)));
  }
  return nil;
}

f2ptr raw__redblacktree__insert__thread_unsafe(f2ptr cause, f2ptr this, f2ptr key) {
  assert_value(key);
  //f2ptr new_node    = assert_value(f2__redblacktree_node__new(cause));
  //f2ptr key_set = f2__redblacktree_node__key_set(cause, new_node);
  //f2__set__add(cause, key_set, key);
  //f2__redblacktree_node__parent__set(cause, new_node, nil);
  //f2__redblacktree_node__left__set(  cause, new_node, nil);
  //f2__redblacktree_node__right__set( cause, new_node, nil);
  //f2__redblacktree_node__color__set( cause, new_node, new__symbol(cause, "red"));
  assert_value(raw__redblacktree__insert_key(cause, this, key));
  return nil;
}

f2ptr raw__redblacktree__insert(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__insert__thread_unsafe(cause, this, key);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__insert(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__insert(cause, this, key);
}
def_pcfunk2(redblacktree__insert, this, key,
	    "Insert one instance of a key into a red-black-tree.",
	    return f2__redblacktree__insert(this_cause, this, key));





void raw__redblacktree_node__delete_case6(f2ptr cause, f2ptr this) {
  f2ptr this__sibling = raw__redblacktree_node__sibling(cause, this);
  f2__redblacktree_node__color__set(cause, this__sibling, f2__redblacktree_node__color(cause, f2__redblacktree_node__parent(cause, this)));
  f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "black"));
  if (this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) {
    // Here, this__sibling->right->color == rbt_color__red.
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__right(cause, this__sibling), new__symbol(cause, "black"));
    raw__redblacktree_node__rotate_left(cause, f2__redblacktree_node__parent(cause, this));
  } else {
    // Here, this__sibling->left->color == rbt_color__red.
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__left(cause, this__sibling), new__symbol(cause, "black"));
    raw__redblacktree_node__rotate_right(cause, f2__redblacktree_node__parent(cause, this));
  }
}

void raw__redblacktree_node__delete_case5(f2ptr cause, f2ptr this) {
  f2ptr this__sibling = raw__redblacktree_node__sibling(cause, this);
  if ((this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) &&
      raw__redblacktree_node__is_black(cause, this__sibling) &&
      raw__redblacktree_node__is_red(  cause, f2__redblacktree_node__left( cause, this__sibling)) &&
      raw__redblacktree_node__is_black(cause, f2__redblacktree_node__right(cause, this__sibling))) {
    f2__redblacktree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__left(cause, this__sibling), new__symbol(cause, "black"));
    raw__redblacktree_node__rotate_right(cause, this__sibling);
  } else if ((this == f2__redblacktree_node__right(cause, f2__redblacktree_node__parent(cause, this))) &&
	     raw__redblacktree_node__is_black(cause, this__sibling) &&
	     raw__redblacktree_node__is_red(  cause, f2__redblacktree_node__right(cause, this__sibling)) &&
	     raw__redblacktree_node__is_black(cause, f2__redblacktree_node__left( cause, this__sibling))) {
    f2__redblacktree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__right(cause, this__sibling), new__symbol(cause, "black"));
    raw__redblacktree_node__rotate_left(cause, this__sibling);
  }
  raw__redblacktree_node__delete_case6(cause, this);
}

void raw__redblacktree_node__delete_case4(f2ptr cause, f2ptr this) {
  f2ptr this__sibling = raw__redblacktree_node__sibling(cause, this);
  if (raw__redblacktree_node__is_red(  cause, f2__redblacktree_node__parent(cause, this)) &&
      raw__redblacktree_node__is_black(cause, this__sibling) &&
      raw__redblacktree_node__is_black(cause, f2__redblacktree_node__left( cause, this__sibling)) &&
      raw__redblacktree_node__is_black(cause, f2__redblacktree_node__right(cause, this__sibling))) {
    f2__redblacktree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "black"));
  } else if (f2__redblacktree_node__parent(cause, this)) {
    raw__redblacktree_node__delete_case5(cause, this);
  }
}

void raw__redblacktree_node__delete_case1(f2ptr cause, f2ptr this);

void raw__redblacktree_node__delete_case3(f2ptr cause, f2ptr this) {
  f2ptr this__sibling = raw__redblacktree_node__sibling(cause, this);
  if (this__sibling) {
    if (raw__redblacktree_node__is_black(cause, f2__redblacktree_node__parent(cause, this)) &&
	raw__redblacktree_node__is_black(cause, this__sibling) &&
	raw__redblacktree_node__is_black(cause, f2__redblacktree_node__left( cause, this__sibling)) &&
	raw__redblacktree_node__is_black(cause, f2__redblacktree_node__right(cause, this__sibling))) {
      f2__redblacktree_node__color__set(cause, this__sibling, new__symbol(cause, "red"));
      raw__redblacktree_node__delete_case1(cause, f2__redblacktree_node__parent(cause, this));
    } else {
      raw__redblacktree_node__delete_case4(cause, this);
    }
  }
}

void raw__redblacktree_node__delete_case2(f2ptr cause, f2ptr this) {
  f2ptr this__sibling = raw__redblacktree_node__sibling(cause, this);
  if (raw__redblacktree_node__is_red(cause, this__sibling)) {
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "red"));
    f2__redblacktree_node__color__set(cause, this__sibling, new__symbol(cause, "black"));
    if (this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) {
      raw__redblacktree_node__rotate_left(cause, f2__redblacktree_node__parent(cause, this));
    } else {
      raw__redblacktree_node__rotate_right(cause, f2__redblacktree_node__parent(cause, this));
    }
  }
  raw__redblacktree_node__delete_case3(cause, this);
}

void raw__redblacktree_node__delete_case1(f2ptr cause, f2ptr this) {
  if (f2__redblacktree_node__parent(cause, this)) {
    raw__redblacktree_node__delete_case2(cause, this);
  }
}

void raw__redblacktree__remove_node_with_at_most_one_child(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr node__child  = (f2__redblacktree_node__left(cause, node) != nil) ? f2__redblacktree_node__left(cause, node) : f2__redblacktree_node__right(cause, node);
  f2ptr node__parent = f2__redblacktree_node__parent(cause, node);
  f2ptr node__left   = f2__redblacktree_node__left(  cause, node);
  f2ptr node__right  = f2__redblacktree_node__right( cause, node);
  if (node__left == nil) { 
    if (node__parent) {
      if (f2__redblacktree_node__right(cause, node__parent) == node) {
	f2__redblacktree_node__right__set(cause, node__parent, node__right);
	if (node__right) {
	  f2__redblacktree_node__parent__set(cause, node__right, node__parent);
	}
      } else {
	f2__redblacktree_node__left__set(cause, node__parent, node__right);
	if (node__right) {
	  f2__redblacktree_node__parent__set(cause, node__right, node__parent);
	}
      }
    } else {
      f2__redblacktree__head__set(cause, this, node__right);
      if (node__right) {
	f2__redblacktree_node__parent__set(cause, node__right, nil);
      }
    }
  } else { // (node->right == NULL)
    if (node__parent) {
      if (f2__redblacktree_node__right(cause, node__parent) == node) {
	f2__redblacktree_node__right__set(cause, node__parent, node__left);
	if (node__left) {
	  f2__redblacktree_node__parent__set(cause, node__left, node__parent);
	}
      } else {
	f2__redblacktree_node__left__set(cause, node__parent, node__left);
	if (node__left) {
	  f2__redblacktree_node__parent__set(cause, node__left, node__parent);
	}
      }
    } else {
      f2__redblacktree__head__set(cause, this, node__left);
      if (node__left) {
	f2__redblacktree_node__parent__set(cause, node__left, nil);
      }
    }
  }
  
  if (node__child) {
    if (raw__eq(cause, f2__redblacktree_node__color(cause, node), new__symbol(cause, "black"))) {
      if (raw__eq(cause, f2__redblacktree_node__color(cause, node__child), new__symbol(cause, "red"))) {
	f2__redblacktree_node__color__set(cause, node__child, new__symbol(cause, "black"));
      } else {
	raw__redblacktree_node__delete_case1(cause, node__child);
      }
    }
  }
}

void raw__redblacktree_node__replace_node(f2ptr cause, f2ptr dest, f2ptr src) {
  f2ptr src__parent = f2__redblacktree_node__parent(cause, src);
  f2ptr src__left   = f2__redblacktree_node__left(  cause, src);
  f2ptr src__right  = f2__redblacktree_node__right( cause, src);
  f2__redblacktree_node__parent__set(cause, dest, src__parent);
  f2__redblacktree_node__left__set(  cause, dest, src__left);
  f2__redblacktree_node__right__set( cause, dest, src__right);
  if (src__parent) {
    if (f2__redblacktree_node__left(cause, src__parent) == src) {
      f2__redblacktree_node__left__set(cause, src__parent, dest);
    } else { // (src__parent->right == src)
#ifdef DEBUG_REDBLACKTREE
      debug__assert(f2__redblacktree_node__right(cause, src__parent) == src, nil, "raw__redblacktree_node__replace_node assertion failure: src__parent->right == src.");
#endif
      f2__redblacktree_node__right__set(cause, src__parent, dest);
    }
  }
  if (src__left) {
    f2__redblacktree_node__parent__set(cause, src__left, dest);
  }
  if (src__right) {
    f2__redblacktree_node__parent__set(cause, src__right, dest);
  }
#ifdef DEBUG_REDBLACKTREE
  //debug__assert(raw__redblacktree_node__is_valid(cause, dest), nil, "raw__redblacktree_node__replace_node assertion failure: raw__redblacktree_node__is_valid(cause, dest).");
#endif
}

void raw__redblacktree_node__swap_nodes(f2ptr cause, f2ptr node1, f2ptr node2) {
  f2ptr node1__parent       = f2__redblacktree_node__parent(cause, node1);
  f2ptr node1__parent__left = f2__redblacktree_node__parent(cause, node1) ? f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, node1)) : nil;
  f2ptr node1__left         = f2__redblacktree_node__left(  cause, node1);
  f2ptr node1__right        = f2__redblacktree_node__right( cause, node1);
  f2ptr node1__color        = f2__redblacktree_node__color( cause, node1);
  f2ptr node2__parent       = f2__redblacktree_node__parent(cause, node2);
  f2ptr node2__parent__left = f2__redblacktree_node__parent(cause, node2) ? f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, node2)) : nil;
  f2ptr node2__left         = f2__redblacktree_node__left(  cause, node2);
  f2ptr node2__right        = f2__redblacktree_node__right( cause, node2);
  f2ptr node2__color        = f2__redblacktree_node__color( cause, node2);
  
  // copy values to node2
  if (node1__parent == node2) {
    f2__redblacktree_node__parent__set(cause, node2, node1);
  } else {
    f2__redblacktree_node__parent__set(cause, node2, node1__parent);
    if (node1__parent) {
      if (node1__parent__left == node1) {
	f2__redblacktree_node__left__set(cause, node1__parent, node2);
      } else { // (node1__parent->right == node1)
#ifdef DEBUG_REDBLACKTREE
	debug__assert(f2__redblacktree_node__right(cause, node1__parent) == node1, nil, "raw__redblacktree_node__replace_node assertion failure: node1__parent->right == node1.");
#endif
	f2__redblacktree_node__right__set(cause, node1__parent, node2);
      }
    }
  }
  if (node1__left == node2) {
    f2__redblacktree_node__left__set(cause, node2, node1);
  } else {
    f2__redblacktree_node__left__set(cause, node2, node1__left);
    if (node1__left) {
      f2__redblacktree_node__parent__set(cause, node1__left, node2);
    }
  }
  if (node1__right  == node2) {
    f2__redblacktree_node__right__set(cause, node2, node1);
  } else {
    f2__redblacktree_node__right__set(cause, node2, node1__right);
    if (node1__right) {
      f2__redblacktree_node__parent__set(cause, node1__right, node2);
    }
  }
  f2__redblacktree_node__color__set(cause, node2, node1__color);
  
  // copy values to node1
  if (node2__parent == node1) {
    f2__redblacktree_node__parent__set(cause, node1, node2);
  } else {
    f2__redblacktree_node__parent__set(cause, node1, node2__parent);
    if (node2__parent) {
      if (node2__parent__left == node2) {
	f2__redblacktree_node__left__set(cause, node2__parent, node1);
      } else { // (node1__parent->right == node1)
#ifdef DEBUG_REDBLACKTREE
	debug__assert(f2__redblacktree_node__right(cause, node2__parent) == node2, nil, "raw__redblacktree_node__replace_node assertion failure: node2__parent->right == node2.");
#endif
	f2__redblacktree_node__right__set(cause, node2__parent, node1);
      }
    }
  }
  if (node2__left == node1) {
    f2__redblacktree_node__left__set(cause, node1, node2);
  } else {
    f2__redblacktree_node__left__set(cause, node1, node2__left);
    if (node2__left) {
      f2__redblacktree_node__parent__set(cause, node2__left, node1);
    }
  }
  if (node2__right == node1) {
    f2__redblacktree_node__right__set(cause, node1, node2);
  } else {
    f2__redblacktree_node__right__set(cause, node1, node2__right);
    if (node2__right) {
      f2__redblacktree_node__parent__set(cause, node2__right, node1);
    }
  }
  f2__redblacktree_node__color__set(cause, node1, node2__color);
#ifdef DEBUG_REDBLACKTREE
  //debug__assert(raw__redblacktree_node__is_valid(cause, node1), nil, "raw__redblacktree_node__swap_node assertion failure: raw__redblacktree_node__is_valid(cause, node1).");
  //debug__assert(raw__redblacktree_node__is_valid(cause, node2), nil, "raw__redblacktree_node__swap_node assertion failure: raw__redblacktree_node__is_valid(cause, node2).");
#endif
}

f2ptr raw__redblacktree__remove_node(f2ptr cause, f2ptr this, f2ptr node) {
  if (f2__redblacktree_node__left(cause, node) == nil || f2__redblacktree_node__right(cause, node) == nil) { 
    raw__redblacktree__remove_node_with_at_most_one_child(cause, this, node);
  } else {
    f2ptr node__left__max = raw__redblacktree_node__maximum_node(cause, f2__redblacktree_node__left(cause, node));
    
    debug__assert(f2__redblacktree_node__right(cause, node__left__max) == nil, nil, "rbt_node__remove_node: (node__left__max->right == NULL) failed.");
    
    raw__redblacktree_node__swap_nodes(cause, node__left__max, node);
    
    raw__redblacktree__remove_node_with_at_most_one_child(cause, this, node);
    
    if (f2__redblacktree_node__parent(cause, node__left__max) == nil) {
      f2__redblacktree__head__set(cause, this, node__left__max);
    }
  }
  
  f2__redblacktree__head__set(cause, this, raw__redblacktree_node__head(cause, f2__redblacktree__head(cause, this))); 
  
  if (f2__redblacktree__head(cause, this)) {
    if (f2__redblacktree_node__color(cause, f2__redblacktree__head(cause, this)) == new__symbol(cause, "red")) {
      f2__redblacktree_node__color__set(cause, f2__redblacktree__head(cause, this), new__symbol(cause, "black"));
    }
  }
  
  if (raw__redblacktree__contains_node(cause, this, node)) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "redblacktree_still_contains_node_after_removal"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "node"),     node));
  }
  return nil;
}


boolean_t raw__redblacktree_node__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  boolean_t this_does_contain_node = boolean__false;
  if (this != nil) {
    f2ptr iter = node;
    while(iter != nil) {
      f2ptr parent = f2__redblacktree_node__parent(cause, iter);
      if (parent == nil) {
	break;
      }
      f2ptr parent__left  = f2__redblacktree_node__left(  cause, parent);
      f2ptr parent__right = f2__redblacktree_node__right( cause, parent);
      if ((! raw__eq(cause, parent__left, iter)) && (! raw__eq(cause, parent__right, iter))) {
	break;
      }
      if (raw__eq(cause, this, iter)) {
	this_does_contain_node = boolean__true;
	break;
      }
      iter = parent;
    }
  }
  return this_does_contain_node;
}

f2ptr f2__redblacktree_node__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(redblacktree_node, this);
  assert_argument_type(redblacktree_node, node);
  return f2bool__new(raw__redblacktree_node__contains_node(cause, this, node));
}


f2ptr raw__redblacktree_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"),   new__symbol(cause, "redblacktree_node"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "left"),                f2__redblacktree_node__left(               cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "right"),               f2__redblacktree_node__right(              cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "color"),               f2__redblacktree_node__color(              cause, this));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "count_key_ptypehash"), f2__redblacktree_node__count_key_ptypehash(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__redblacktree_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(redblacktree_node,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__redblacktree_node__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(redblacktree_node__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__redblacktree_node__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2redblacktree_node__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2redblacktree_node__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.terminal_print_with_frame__funk);}
  return this;
}


boolean_t raw__redblacktree__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  f2ptr head = f2__redblacktree__head(cause, this);
  if (head == nil) {
    return boolean__false;
  }
  return raw__redblacktree_node__contains_node(cause, head, node);
}

f2ptr f2__redblacktree__contains_node(f2ptr cause, f2ptr this, f2ptr node) {
  assert_argument_type(redblacktree,      this);
  assert_argument_type(redblacktree_node, node);
  return f2bool__new(raw__redblacktree__contains_node(cause, this, node));
}

f2ptr raw__redblacktree__remove__thread_unsafe(f2ptr cause, f2ptr this, f2ptr key) {
  assert_value(key);
  f2ptr node = assert_value(raw__redblacktree__lookup_node_with_key(cause, this, key));
  if (node == nil) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "key_is_not_in_redblacktree"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "key"),      key));
  }
  f2ptr node__count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, node);
  f2ptr old_count                 = raw__ptypehash__lookup(cause, node__count_key_ptypehash, key);
  if (old_count == nil) {
    return new__error(f2list6__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "key_is_not_in_redblacktree"),
				   new__symbol(cause, "this"),     this,
				   new__symbol(cause, "key"),      key));
  }
  s64 old_count__i = f2integer__i(old_count, cause);
  if (old_count__i == 1) {
    assert_value(raw__ptypehash__remove(cause, node__count_key_ptypehash, key));
    if (raw__ptypehash__is_empty(cause, node__count_key_ptypehash)) {
      assert_value(raw__redblacktree__remove_node(cause, this, node));
    }
  } else {
    raw__ptypehash__add(cause, node__count_key_ptypehash, key, f2integer__new(cause, old_count__i - 1));
  }
  return nil;
}

f2ptr raw__redblacktree__remove(f2ptr cause, f2ptr this, f2ptr key) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__remove__thread_unsafe(cause, this, key);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__remove(f2ptr cause, f2ptr this, f2ptr key) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__remove(cause, this, key);
}
def_pcfunk2(redblacktree__remove, this, key,
	    "Remove one instance of a key from a red-black-tree.",
	    return f2__redblacktree__remove(this_cause, this, key));

f2ptr raw__redblacktree__minimum_node(f2ptr cause, f2ptr this) {
  f2ptr head = f2__redblacktree__head(cause, this);
  if (head == nil) {
    return nil;
  }
  return raw__redblacktree_node__minimum_node(cause, head);
}


f2ptr raw__redblacktree__minimum__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr minimum_node = raw__redblacktree__minimum_node(cause, this);
  if (minimum_node == nil) {
    return nil;
  }
  f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, minimum_node);
  f2ptr key                 = f2__ptypehash__an_arbitrary_key(cause, count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, count_key_ptypehash)) {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this));
    }
  }
  return key;
}

f2ptr raw__redblacktree__minimum(f2ptr cause, f2ptr this) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__minimum__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__minimum(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__minimum(cause, this);
}
def_pcfunk1(redblacktree__minimum, this,
	    "Returns the minimum key within a red-black-tree or nil if tree is empty.",
	    return f2__redblacktree__minimum(this_cause, this));

f2ptr raw__redblacktree__maximum_node(f2ptr cause, f2ptr this) {
  f2ptr head = f2__redblacktree__head(cause, this);
  if (head == nil) {
    return nil;
  }
  return raw__redblacktree_node__maximum_node(cause, head);
}


f2ptr raw__redblacktree__maximum__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr maximum_node = raw__redblacktree__maximum_node(cause, this);
  if (maximum_node == nil) {
    return nil;
  }
  f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, maximum_node);
  f2ptr key                 = f2__ptypehash__an_arbitrary_key(cause, count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, count_key_ptypehash)) {
      return new__error(f2list4__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this));
    }
  }
  return key;
}

f2ptr raw__redblacktree__maximum(f2ptr cause, f2ptr this) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__maximum__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__maximum(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__maximum(cause, this);
}
def_pcfunk1(redblacktree__maximum, this,
	    "Returns the maximum key within a red-black-tree or nil if tree is empty.",
	    return f2__redblacktree__maximum(this_cause, this));


f2ptr raw__redblacktree_node__next(f2ptr cause, f2ptr this) {
  if (f2__redblacktree_node__right(cause, this) != nil) {
    return raw__redblacktree_node__minimum_node(cause, f2__redblacktree_node__right(cause, this));
  } else {
    if (f2__redblacktree_node__parent(cause, this) == nil) {
      return nil;
    } else {
      while (this && f2__redblacktree_node__parent(cause, this)) {
	if (f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this)) == this) {
	  return f2__redblacktree_node__parent(cause, this);
	}
	this = f2__redblacktree_node__parent(cause, this);
      }
      return nil;
    }
  }
}

f2ptr f2__redblacktree_node__next(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree_node, this);
  return raw__redblacktree_node__next(cause, this);
}


f2ptr raw__redblacktree_node__prev(f2ptr cause, f2ptr this) {
  if (f2__redblacktree_node__left(cause, this) != nil) {
    return raw__redblacktree_node__maximum_node(cause, f2__redblacktree_node__left(cause, this));
  } else {
    if (f2__redblacktree_node__parent(cause, this) == nil) {
      return nil;
    } else {
      while (this && f2__redblacktree_node__parent(cause, this)) {
	if (f2__redblacktree_node__right(cause, f2__redblacktree_node__parent(cause, this)) == this) {
	  return f2__redblacktree_node__parent(cause, this);
	}
	this = f2__redblacktree_node__parent(cause, this);
      }
      return nil;
    }
  }
}

f2ptr f2__redblacktree_node__prev(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree_node, this);
  return raw__redblacktree_node__prev(cause, this);
}


f2ptr raw__redblacktree__minimum_not_less_than__node(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr head = f2__redblacktree__head(cause, this);
  if (head == nil) {
    return nil;
  }
  f2ptr value_funk            = f2__redblacktree__value_funk(           cause, this);
  f2ptr value_comparison_funk = f2__redblacktree__value_comparison_funk(cause, this);
  return catch_value(raw__redblacktree_node__minimum_not_less_than__node(cause, head, value_funk, value_comparison_funk, value),
		     f2list6__new(cause,
				  new__symbol(cause, "bug_name"),        new__symbol(cause, "error_finding_minimum_node_not_less_than"),
				  new__symbol(cause, "this"),            this,
				  new__symbol(cause, "less_than_value"), value));
}

f2ptr f2__redblacktree__minimum_not_less_than__node(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__minimum_not_less_than__node(cause, this, value);
}
def_pcfunk2(redblacktree__minimum_not_less_than__node, this, value,
	    "Returns the node whose key value as retrieved by value_funk is the minimum that is not less than the given value.",
	    return f2__redblacktree__minimum_not_less_than__node(this_cause, this, value));


f2ptr raw__redblacktree__minimum_not_less_than__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr node = assert_value(raw__redblacktree__minimum_not_less_than__node(cause, this, value));
  if (node == nil) {
    return nil;
  }
  f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, node);
  f2ptr key                 = f2__ptypehash__an_arbitrary_key(cause, count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"),        new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),            this,
				     new__symbol(cause, "less_than_value"), value));
    }
  }
  return key;
}

f2ptr raw__redblacktree__minimum_not_less_than(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__minimum_not_less_than__thread_unsafe(cause, this, value);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__minimum_not_less_than(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__minimum_not_less_than(cause, this, value);
}
def_pcfunk2(redblacktree__minimum_not_less_than, this, value,
	    "Returns the key of the node whose key value is the minimum that is not less than the given value.",
	    return f2__redblacktree__minimum_not_less_than(this_cause, this, value));


f2ptr raw__redblacktree__maximum_not_greater_than_or_equal_to__node(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr head = f2__redblacktree__head(cause, this);
  if (head == nil) {
    return nil;
  }
  f2ptr value_funk            = f2__redblacktree__value_funk(           cause, this);
  f2ptr value_comparison_funk = f2__redblacktree__value_comparison_funk(cause, this);
  return raw__redblacktree_node__maximum_not_greater_than_or_equal_to__node(cause, head, value_funk, value_comparison_funk, value);
}

f2ptr f2__redblacktree__maximum_not_greater_than_or_equal_to__node(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__maximum_not_greater_than_or_equal_to__node(cause, this, value);
}
def_pcfunk2(redblacktree__maximum_not_greater_than_or_equal_to__node, this, value,
	    "Returns the node whose key value is the maximum that is not greater than the given value.",
	    return f2__redblacktree__maximum_not_greater_than_or_equal_to__node(this_cause, this, value));


f2ptr raw__redblacktree__maximum_not_greater_than_or_equal_to__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr node = assert_value(raw__redblacktree__maximum_not_greater_than_or_equal_to__node(cause, this, value));
  if (node == nil) {
    return nil;
  }
  f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, node);
  f2ptr key                 = f2__ptypehash__an_arbitrary_key(cause, count_key_ptypehash);
  if (key == nil) {
    if (raw__ptypehash__is_empty(cause, count_key_ptypehash)) {
      return new__error(f2list6__new(cause,
				     new__symbol(cause, "bug_name"), new__symbol(cause, "unexpected_empty_count_key_ptypehash"),
				     new__symbol(cause, "this"),     this,
				     new__symbol(cause, "value"),    value));
    }
  }
  return key;
}

f2ptr raw__redblacktree__maximum_not_greater_than_or_equal_to(f2ptr cause, f2ptr this, f2ptr value) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__maximum_not_greater_than_or_equal_to__thread_unsafe(cause, this, value);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__maximum_not_greater_than_or_equal_to(f2ptr cause, f2ptr this, f2ptr value) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__maximum_not_greater_than_or_equal_to(cause, this, value);
}
def_pcfunk2(redblacktree__maximum_not_greater_than_or_equal_to, this, value,
	    "Returns the key of the node whose key value is the maximum that is not greater than the given value.",
	    return f2__redblacktree__maximum_not_greater_than_or_equal_to(this_cause, this, value));


f2ptr raw__redblacktree__leaves__thread_unsafe(f2ptr cause, f2ptr this) {
  f2ptr leaves = nil;
  redblacktree__iteration_backward(cause, this, key,
				   leaves = f2cons__new(cause, key, leaves);
				   );
  return leaves;
}

f2ptr raw__redblacktree__leaves(f2ptr cause, f2ptr this) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__leaves__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__leaves(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__leaves(cause, this);
}
def_pcfunk1(redblacktree__leaves, this,
	    "Returns all leaves in this red-black-tree in order in a new list.",
	    return f2__redblacktree__leaves(this_cause, this));


boolean_t raw__redblacktree__is_empty(f2ptr cause, f2ptr this) {
  return (f2__redblacktree__head(cause, this) == nil);
}

f2ptr f2__redblacktree__is_empty(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__is_empty(cause, this);
}
def_pcfunk1(redblacktree__is_empty, this,
	    "Returns whether this redblacktree is empty.",
	    return f2__redblacktree__is_empty(this_cause, this));


u64 raw__redblacktree__size__thread_unsafe(f2ptr cause, f2ptr this) {
  u64 size = 0;
  f2ptr iter = raw__redblacktree__minimum_node(cause, this);
  while (iter) {
    size ++;
    iter = raw__redblacktree_node__next(cause, iter);
  }
  return size;
}

u64 raw__redblacktree__size(f2ptr cause, f2ptr this) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  u64 result = raw__redblacktree__size__thread_unsafe(cause, this);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__size(f2ptr cause, f2ptr this) {
  assert_argument_type(redblacktree, this);
  return f2integer__new(cause, raw__redblacktree__size(cause, this));
}
def_pcfunk1(redblacktree__size, this,
	    "Returns the number of leaves in this red-black-tree.",
	    return f2__redblacktree__size(this_cause, this));


f2ptr raw__redblacktree__leaves_within_range__thread_unsafe(f2ptr cause, f2ptr this, f2ptr minimum, f2ptr maximum) {
  f2ptr     maximum_node = assert_value(raw__redblacktree__maximum_not_greater_than_or_equal_to__node(cause, this, maximum));
  f2ptr     minimum_node = assert_value(raw__redblacktree__minimum_not_less_than__node(cause, this, minimum));
  f2ptr     sequence     = nil;
  f2ptr     iter_node    = maximum_node;
  boolean_t done         = boolean__false;
  while (! done) {
    f2ptr count_key_ptypehash = f2__redblacktree_node__count_key_ptypehash(cause, iter_node);
    ptypehash__iteration(cause, count_key_ptypehash, key, count,
			 s64 count__i = f2integer__i(count, cause);
			 {
			   s64 index;
			   for (index = 0; index < count__i; index ++) {
			     sequence = f2cons__new(cause, key, sequence);
			   }
			 }
			 );
    if (raw__eq(cause, iter_node, minimum_node)) {
      done = boolean__true;
    }
    iter_node = raw__redblacktree_node__prev(cause, iter_node);
    if (iter_node == nil) {
      done = boolean__true;
    }
  }
  return sequence;
}

f2ptr raw__redblacktree__leaves_within_range(f2ptr cause, f2ptr this, f2ptr minimum, f2ptr maximum) {
  f2ptr mutate_mutex = f2redblacktree__mutate_mutex(this, cause);
  raw__cmutex__lock(cause, mutate_mutex);
  f2ptr result = raw__redblacktree__leaves_within_range__thread_unsafe(cause, this, minimum, maximum);
  raw__cmutex__unlock(cause, mutate_mutex);
  return result;
}

f2ptr f2__redblacktree__leaves_within_range(f2ptr cause, f2ptr this, f2ptr minimum, f2ptr maximum) {
  assert_argument_type(redblacktree, this);
  return raw__redblacktree__leaves_within_range(cause, this, minimum, maximum);
}
def_pcfunk3(redblacktree__leaves_within_range, this, minimum, maximum,
	    "Returns leaves within the range.",
	    return f2__redblacktree__leaves_within_range(this_cause, this, minimum, maximum));


f2ptr raw__redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "redblacktree"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "leaves"),            f2__redblacktree__leaves(cause, this));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__redblacktree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(redblacktree,         this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__redblacktree__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(redblacktree__terminal_print_with_frame, this, terminal_print_frame,
	    "",
	    return f2__redblacktree__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2redblacktree__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2redblacktree__primobject_type__new(cause);
  {char* slot_name = "insert";                                    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.insert__funk);}
  {char* slot_name = "remove";                                    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.remove__funk);}
  {char* slot_name = "lookup_key_count";                          f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.lookup_key_count__funk);}
  {char* slot_name = "contains";                                  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.contains__funk);}
  {char* slot_name = "minimum";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum__funk);}
  {char* slot_name = "maximum";                                   f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum__funk);}
  {char* slot_name = "minimum_not_less_than-node";                f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__node__funk);}
  {char* slot_name = "minimum_not_less_than";                     f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__funk);}
  {char* slot_name = "maximum_not_greater_than_or_equal_to-node"; f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__node__funk);}
  {char* slot_name = "maximum_not_greater_than_or_equal_to";      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__funk);}
  {char* slot_name = "leaves";                                    f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves__funk);}
  {char* slot_name = "size";                                      f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.size__funk);}
  {char* slot_name = "is_empty";                                  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.is_empty__funk);}
  {char* slot_name = "leaves_within_range";                       f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "get"),     new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves_within_range__funk);}
  {char* slot_name = "terminal_print_with_frame";                 f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.terminal_print_with_frame__funk);}
  return this;
}


// **

void f2__primobject__redblacktree__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  // -- initialize --

  // redblacktree
  
  initialize_primobject_4_slot__defragment__fix_pointers(redblacktree, mutate_mutex, head, value_funk, value_comparison_funk);
  
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__symbol);
  //f2__primcfunk__init__defragment__fix_pointers(redblacktree__new);
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.insert__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__insert);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.insert__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.remove__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__remove);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.remove__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.lookup_key_count__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__lookup_key_count);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.lookup_key_count__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.contains__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__contains);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.contains__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__minimum);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__maximum);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__node__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__minimum_not_less_than__node);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__node__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__minimum_not_less_than);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__node__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__maximum_not_greater_than_or_equal_to__node);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__node__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__maximum_not_greater_than_or_equal_to);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__leaves);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.size__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__size);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.size__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.is_empty__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__is_empty);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.is_empty__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves_within_range__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__leaves_within_range);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves_within_range__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree.terminal_print_with_frame__funk);
  
  // redblacktree_node
  
  initialize_primobject_5_slot__defragment__fix_pointers(redblacktree_node, parent, left, right, color, count_key_ptypehash);
  
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__symbol);
  //f2__primcfunk__init__defragment__fix_pointers(redblacktree_node__new);
  //defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__funk);
  
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.terminal_print_with_frame__symbol);
  f2__primcfunk__init__defragment__fix_pointers(redblacktree_node__terminal_print_with_frame);
  defragment__fix_pointer(__funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.terminal_print_with_frame__funk);
}

void f2__primobject__redblacktree__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  // redblacktree
  
  initialize_primobject_4_slot(redblacktree, mutate_mutex, head, value_funk, value_comparison_funk);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__new, value_funk, value_comparison_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__funk = never_gc(cfunk);}
  
  {char* symbol_str = "insert"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.insert__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__insert, this, key, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.insert__funk = never_gc(cfunk);}
  
  {char* symbol_str = "remove"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.remove__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__remove, this, key, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.remove__funk = never_gc(cfunk);}
  
  {char* symbol_str = "lookup_key_count"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.lookup_key_count__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__lookup_key_count, this, key, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.lookup_key_count__funk = never_gc(cfunk);}
  
  {char* symbol_str = "contains"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.contains__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__contains, this, key, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.contains__funk = never_gc(cfunk);}
  
  {char* symbol_str = "minimum"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(redblacktree__minimum, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum__funk = never_gc(cfunk);}
  
  {char* symbol_str = "maximum"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(redblacktree__maximum, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum__funk = never_gc(cfunk);}
  
  {char* symbol_str = "minimum_not_less_than-node"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__node__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__minimum_not_less_than__node, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__node__funk = never_gc(cfunk);}
  
  {char* symbol_str = "minimum_not_less_than"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__minimum_not_less_than, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.minimum_not_less_than__funk = never_gc(cfunk);}
  
  {char* symbol_str = "maximum_not_greater_than_or_equal_to-node"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__node__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__maximum_not_greater_than_or_equal_to__node, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__node__funk = never_gc(cfunk);}
  
  {char* symbol_str = "maximum_not_greater_than_or_equal_to"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__maximum_not_greater_than_or_equal_to, this, value, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.maximum_not_greater_than_or_equal_to__funk = never_gc(cfunk);}
  
  {char* symbol_str = "leaves"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(redblacktree__leaves, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves__funk = never_gc(cfunk);}
  
  {char* symbol_str = "size"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.size__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(redblacktree__size, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.size__funk = never_gc(cfunk);}
  
  {char* symbol_str = "is_empty"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.is_empty__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(redblacktree__is_empty, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.is_empty__funk = never_gc(cfunk);}
  
  {char* symbol_str = "leaves_within_range"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves_within_range__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(redblacktree__leaves_within_range, this, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.leaves_within_range__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // redblacktree_node
  
  initialize_primobject_5_slot(redblacktree_node, parent, left, right, color, count_key_ptypehash);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(redblacktree_node__new, parent, left, right, color, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__funk = never_gc(cfunk);}
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.terminal_print_with_frame__symbol = new__symbol(cause, symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(redblacktree_node__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.terminal_print_with_frame__funk = never_gc(cfunk);}
}

void f2__primobject__redblacktree__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject-redblacktree", "", &f2__primobject__redblacktree__reinitialize_globalvars, &f2__primobject__redblacktree__defragment__fix_pointers);
  
  f2__primobject__redblacktree__reinitialize_globalvars();
}


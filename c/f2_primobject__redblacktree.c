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

#include "funk2.h"

// redblacktree

def_primobject_1_slot(redblacktree, head);

f2ptr raw__redblacktree__new(f2ptr cause, f2ptr head) {
  return f2redblacktree__new(cause, head);
}

f2ptr f2__redblacktree__new(f2ptr cause) {
  return raw__redblacktree__new(cause, nil);
}
def_pcfunk0(redblacktree__new, return f2__redblacktree__new(this_cause));

// redblacktree_node

def_primobject_5_slot(redblacktree_node, parent, left, right, color, key);

f2ptr raw__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color, f2ptr key) {
  return f2redblacktree_node__new(cause, parent, left, right, color, key);
}

f2ptr f2__redblacktree_node__new(f2ptr cause, f2ptr parent, f2ptr left, f2ptr right, f2ptr color, f2ptr key) {
  return raw__redblacktree_node__new(cause, parent, left, right, color, key);
}
def_pcfunk5(redblacktree_node__new, parent, left, right, color, key, return f2__redblacktree_node__new(this_cause, parent, left, right, color, key));


// *****************************************************************
// **                                                             **
// ** The following code was not originally written by Bo Morgan, **
// ** but was downloaded from a webpage and modified.  The        **
// ** original source was found here:                             **
// **                                                             **
// **   http://en.wikipedia.org/wiki/Red-black_tree               **
// **                                                             **
// *****************************************************************

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
  f2ptr that = f2__redblacktree_node__right(cause, this);                                    // Set that.
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
  f2ptr this__grandparent = f2__redblacktree_node__grandparent(cause, this);
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
  f2ptr this__grandparent = f2__redblacktree_node__grandparent(cause, this);
  //printf("\ninsert_case5: setting to black...");
  //rbt_node__print(this->parent);
  f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "black"));
  //printf("\ninsert_case5: setting to red...");
  //rbt_node__print(node__grandparent);
  f2__redblacktree_node__color__set(cause, this__grandparent, new__symbol(cause, "red"));
  if ((this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) && (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__left(cause, this__grandparent))) {
    f2__redblacktree_node__rotate_right(cause, this__grandparent);
  } else {
    //
    // Here, (this == this->parent->right) && (this->parent == this__grandparent->right).
    //
    f2__redblacktree_node__rotate_left(cause, this__grandparent);
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
  f2ptr this__grandparent = f2__redblacktree_node__grandparent(cause, this);
  if ((this == f2__redblacktree_node__right(cause, f2__redblacktree_node__parent(cause, this))) && (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__left(cause, this__grandparent))) {
    f2__redblacktree_node__rotate_left(cause, f2__redblacktree_node__parent(cause, this));
    this = f2__redblacktree_node__left(cause, this);
  } else if ((this == f2__redblacktree_node__left(cause, f2__redblacktree_node__parent(cause, this))) && (f2__redblacktree_node__parent(cause, this) == f2__redblacktree_node__right(cause, this__grandparent))) {
    f2__redblacktree_node__rotate_right(cause, f2__redblacktree_node__parent(cause, this));
    this = f2__redblacktree_node__right(cause, this);
  }
  f2__redblacktree_node__insert_case5(cause, this);
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
  f2ptr this__uncle = f2__redblacktree_node__uncle(cause, this);
  f2ptr this__grandparent;
  if ((this__uncle != nil) && (f2__redblacktree_node__color(cause, this__uncle) == new__symbol(cause, "red"))) {
    f2__redblacktree_node__color__set(cause, f2__redblacktree_node__parent(cause, this), new__symbol(cause, "black"));
    f2__redblacktree_node__color__set(cause, this__uncle, new__symbol(cause, "black"));
    this__grandparent = f2__redblacktree_node__grandparent(cause, this);
    f2__redblacktree_node__color__set(cause, this__grandparent, new__symbol(cause, "red"));
    f2__redblacktree_node__insert_case1(cause, this__grandparent);
  } else {
    f2__redblacktree_node__insert_case4(cause, this);
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
  if (f2__redblacktree_node__color(cause, this->parent) == new__symbol(cause, "black")) {
    return; // Tree is still valid
  } else {
    f2__redblacktree_node__insert_case3(cause, this);
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
    f2__redblacktree_node__insert_case2(cause, this);
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

f2ptr raw__redblacktree_node__minimum(f2ptr cause, f2ptr this) {
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

f2ptr raw__redblacktree_node__maximum(f2ptr cause, f2ptr this) {
  if (this == nil) {
    return nil;
  }
  f2ptr iter  = node;
  f2ptr right = f2__redblacktree_node__right(cause, this);
  while (right) {
    iter  = right;
    right = f2__redblacktree_node__right(cause, iter);
  }
  return iter;
}

boolean_t raw__redblacktree_node__contains(f2ptr cause, f2ptr this, f2ptr node) {
  if (this == nil) {
    return boolean__false;
  }
  f2ptr iter = node;
  while(iter && this != iter) {
    f2ptr parent = f2__redblacktree_node__parent(cause, iter);
    if (!parent || (f2__redblacktree_node__left(cause, parent) != iter && f2__redblacktree_node__right(cause, parent) != iter)) {
      iter = nil;
    }
  }
  if (this == iter) {
    return boolean__true;
  }
  return boolean__false;
}

boolean_t raw__redblacktree__contains(f2ptr this, f2ptr node) {
  return raw__redblacktree_node__contains(f2__redblacktree__head(cause, this), node);
}

void raw__redblacktree_node__simple_binary_insert(f2ptr this, f2ptr new_node) {
#ifdef DEBUG_REDBLACKTREE
  debug__assert(!raw__redblacktree_node__contains(cause, this, new_node), nil, "raw__redblacktree_node__simple_binary_insert failed: node already exists in root.");
#endif
  f2ptr new_node__key     = f2__redblacktree_node__key(cause, node_node);
  f2ptr this__key         = f2__redblacktree_node__key(cause, this);
  f2ptr comparison_result = object__get_1(cause, new_node__key, "is_less_than", this__key);
  if (comparison_result != nil) {
    if (f2__redblacktree_node__left(cause, this) == nil) {
      f2__redblacktree_node__parent__set(cause, new_node, this);
      f2__redblacktree_node__left__set(  cause, new_node, nil);
      f2__redblacktree_node__right__set( cause, new_node, nil);
      f2__redblacktree_node__left__set(  cause, this,     new_node);
    } else {
      rbt_node__simple_binary_insert(f2__redblacktree_node__left(cause, this), new_node);
    }
  } else {
    if (f2__redblacktree_node__right(cause, this) == nil) {
      f2__redblacktree_node__parent__set(cause, new_node, this);
      f2__redblacktree_node__left__set(  cause, new_node, nil);
      f2__redblacktree_node__right__set( cause, new_node, nil);
      f2__redblacktree_node__right__set( cause, this,     new_node);
    } else {
      f2__redblacktree_node__simple_binary_insert(cause, f2__redblacktree_node__right(cause, this), new_node);
    }
  }
}

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

void raw__redblacktree__simple_binary_insert(f2ptr cause, f2ptr this, f2ptr node) {
  f2__redblacktree_node__parent__set(cause, node, nil);
  f2__redblacktree_node__left__set(  cause, node, nil);
  f2__redblacktree_node__right__set( cause, node, nil);
  if (f2__redblacktree__head(cause, this) == nil) {
    f2__redblacktree__head__set(cause, this, node);
  } else {
    raw__redblacktree_node__simple_binary_insert(f2__redblacktree__head(cause, this), node);
  }
}

void raw__redblacktree__insert(f2ptr cause, f2ptr this, f2ptr node) {
  raw__redblacktree__simple_binary_insert(cause, this, node);
  f2__redblacktree_node__color__set(cause, node, new__symbol(cause, "red"));
  raw__redblacktree_node__insert_case1(cause, node);
  f2__redblacktree__head__set(cause, this, f2__redblacktree_node__head(cause, f2__redblacktree__head(cause, this)));
}

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
    raw__redblacktree_node__rotate_right(cause, f2__redblacktree_nodee__parent(cause, this));
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
  f2ptr this__sibling = rbt_node__sibling(this);
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

void raw__redblacktree__remove_with_at_most_one_child(f2ptr cause, f2ptr this, f2ptr node) {
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
      f2__redblacktree_node__head__set(cause, this, node__right);
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
    if (f2__redblacktree_node__color(cause, node) == new__symbol(cause, "black")) {
      if (f2__redblacktree_node__color(cause, node__child) == new__symbol(cause, "red")) {
	f2__redblacktree_node__color__set(cause, node__child, new__symbol(cause, "black"));
      } else {
	raw__redblacktree_node__delete_case1(cause, node__child);
      }
    }
  }
}

void raw__redblacktree_node__replace_node(f2ptr dest, f2ptr src) {
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
  debug__assert(raw__redblacktree_node__is_valid(cause, dest), nil, "raw__redblacktree_node__replace_node assertion failure: raw__redblacktree_node__is_valid(cause, dest).");
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
  debug__assert(raw__redblacktree_node__is_valid(cause, node1), nil, "raw__redblacktree_node__swap_node assertion failure: raw__redblacktree_node__is_valid(cause, node1).");
  debug__assert(raw__redblacktree_node__is_valid(cause, node2), nil, "raw__redblacktree_node__swap_node assertion failure: raw__redblacktree_node__is_valid(cause, node2).");
#endif
}

void raw__redblacktree__remove(f2ptr cause, f2ptr this, f2ptr node) {
  if (f2__redblacktree_node__left(cause, node) == nil || f2__redblacktree_node__right(cause, node) == nil) { 
    raw__redblacktree__remove_with_at_most_one_child(cause, this, node);
  } else {
    f2ptr node__left__max = raw__redblacktree_node__maximum(cause, f2__redblacktree_node__left(cause, node));
    
    debug__assert(f2__redblacktree_node__right(cause, node__left__max) == nil, nil, "rbt_node__simple_binary_remove: (node__left__max->right == NULL) failed.");
    
    raw__redblacktree_node__swap_nodes(cause, node__left__max, node);
    
    raw__redblacktree__remove_with_at_most_one_child(cause, this, node);
    
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
  
#ifdef DEBUG_REDBLACKTREE
  debug__assert(! raw__redblacktree__contains(this, node), nil, "raw__redblacktree__remove failed: tree still contains node.");
#endif
}

f2ptr raw__redblacktree__minimum(f2ptr cause, f2ptr this) {
  return raw__redblacktree_node__minimum(cause, f2__redblacktree__head(cause, this));
}

f2ptr raw__redblacktree__maximum(f2ptr cause, f2ptr this) {
  return raw__redblacktree_node__maximum(cause, f2__redblacktree__head(cause, this));
}

int raw__redblacktree__size(f2ptr cause, f2ptr this) {
  int size = 0;
  f2ptr iter = raw__redblacktree__minimum(cause, this);
  while (iter) {
    size ++;
    iter = raw__redblacktree_node__next(cause, iter);
  }
  return size;
}

f2ptr raw__redblacktree_node__next(f2ptr cause, f2ptr this) {
  if (f2__redblacktree_node__right(cause, this) != nil) {
    return raw__redblacktree_node__minimum(cause, f2__redblacktree_node__right(cause, this));
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

f2ptr raw__redblacktree_node__prev(f2ptr cause, f2ptr this) {
  if (f2__redblacktree_node__left(cause, this) != nil) {
    return raw__redblacktree_node__maximum(cause, f2__redblacktree_node__left(cause, this));
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



// **

void f2__primobject__redblacktree__reinitialize_globalvars() {
  __redblacktree__symbol      = f2symbol__new(initial_cause(), strlen("redblacktree"),      (u8*)"redblacktree");
  __redblacktree_node__symbol = f2symbol__new(initial_cause(), strlen("redblacktree_node"), (u8*)"redblacktree_node");
}

void f2__primobject__redblacktree__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "primobject__redblacktree", "", &f2__primobject__redblacktree__reinitialize_globalvars);
  
  f2__primobject__redblacktree__reinitialize_globalvars();
  
  // redblacktree

  initialize_primobject_1_slot(redblacktree, head);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__0_arg(redblacktree__new, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree.new__funk = never_gc(cfunk);}
  
  // redblacktree_node
  
  initialize_primobject_5_slot(redblacktree_node, parent, left, right, color, key);
  
  {char* symbol_str = "new"; __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__5_arg(redblacktree_node__new, parent, left, right, color, key, cfunk, 0, ""); __funk2.globalenv.object_type.primobject.primobject_type_redblacktree_node.new__funk = never_gc(cfunk);}
  
}


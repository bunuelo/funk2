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

#include "funk2.h"

// ****************************************************************
// **                                                            **
// ** This code was originally downloaded from here:             **
// **                                                            **
// **   http://en.wikipedia.org/wiki/Red-black_tree              **
// **                                                            **
// ** It has been funkified by Bo Morgan.                        **
// **                                                            **
// ****************************************************************


void rbt_node__free_all_nodes(rbt_node_t* node) {
  rbt_node_t* left  = node->left;
  rbt_node_t* right = node->right;
  f2__free(to_ptr(node));
  if (left != NULL) {
    rbt_node__free_all_nodes(left);
  }
  if (right != NULL) {
    rbt_node__free_all_nodes(right);
  }
}

int rbt_node__is_black(rbt_node_t* node) {
  if (!node || node->color == rbt_color__black) {
    return 1;
  }
  return 0;
}

int rbt_node__is_red(rbt_node_t* node) {
  return !rbt_node__is_black(node);
}

void rbt_node__rotate_left(rbt_node_t* x) {
  rbt_node_t* y;
  y               = x->right;     // Set y.
  x->right        = y->left;      // Turn y's left subtree into x's right subtree.
  if (y->left) {
    y->left->parent = x;
  }
  y->parent       = x->parent;    // Link x's parent to y.
  if (x->parent != NULL) {
    if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
  }
  y->left   = x;             // Put x on y's left.
  x->parent = y;
}

void rbt_node__rotate_right(rbt_node_t* x) {
  rbt_node_t* y;
  y               = x->left;      // Set y.
  x->left         = y->right;     // Turn y's right subtree into x's left subtree.
  if (y->right) {
    y->right->parent = x;
  }
  y->parent       = x->parent;    // Link x's parent to y.
  if (x->parent != NULL) {
    if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
  }
  y->right  = x;             // Put x on y's left.
  x->parent = y;
}


rbt_node_t* rbt_node__grandparent(rbt_node_t* node) {
  if ((node != NULL) && (node->parent != NULL)) {
    return node->parent->parent;
  } else {
    return NULL;
  }
}

rbt_node_t* rbt_node__uncle(rbt_node_t* node) {
  rbt_node_t* node__grandparent = rbt_node__grandparent(node);
  //
  // Here we blindly assume that node__grandparent != NULL, i.e. we
  // suppose a rootless tree.  However, a real tree always have an
  // uppermost root node which we can't go past, so an appropriate
  // tree boundary check would be required here, such as the
  // following:
  //
  //if (node__grandparent == NULL) {
  //  return NULL;
  //}
  if (node->parent == node__grandparent->left) {
    return node__grandparent->right;
  }
  return node__grandparent->left;
}

rbt_node_t* rbt_node__sibling(rbt_node_t* node) {
  if (node == node->parent->left) {
    return node->parent->right;
  } else {
    return node->parent->left;
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

void rbt_node__insert_case5(rbt_node_t* node) {
  rbt_node_t* node__grandparent = rbt_node__grandparent(node);
  
  //printf("\ninsert_case5: setting to black...");
  //rbt_node__print(node->parent);
  node->parent->color      = rbt_color__black;
  //printf("\ninsert_case5: setting to red...");
  //rbt_node__print(node__grandparent);
  node__grandparent->color = rbt_color__red;
  if ((node == node->parent->left) && (node->parent == node__grandparent->left)) {
    rbt_node__rotate_right(node__grandparent);
  } else {
    //
    // Here, (node == node->parent->right) && (node->parent == node__grandparent->right).
    //
    rbt_node__rotate_left(node__grandparent);
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

void rbt_node__insert_case4(rbt_node_t* node) {
  rbt_node_t* node__grandparent = rbt_node__grandparent(node);
  
  if ((node == node->parent->right) && (node->parent == node__grandparent->left)) {
    rbt_node__rotate_left(node->parent);
    node = node->left;
  } else if ((node == node->parent->left) && (node->parent == node__grandparent->right)) {
    rbt_node__rotate_right(node->parent);
    node = node->right;
  }
  rbt_node__insert_case5(node);
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
void rbt_node__insert_case1(rbt_node_t* node);

void rbt_node__insert_case3(rbt_node_t* node) {
  rbt_node_t* node__uncle = rbt_node__uncle(node);
  rbt_node_t* node__grandparent;
  
  if ((node__uncle != NULL) && (node__uncle->color == rbt_color__red)) {
    //printf("\ninsert_case3: setting to black...");
    //rbt_node__print(node->parent);
    node->parent->color = rbt_color__black;
    //printf("\ninsert_case3: setting to black...");
    //rbt_node__print(node__uncle);
    node__uncle->color = rbt_color__black;
    node__grandparent = rbt_node__grandparent(node);
    //printf("\ninsert_case3: setting to red...");
    //rbt_node__print(node__grandparent);
    node__grandparent->color = rbt_color__red;
    rbt_node__insert_case1(node__grandparent);
  } else {
    rbt_node__insert_case4(node);
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

void rbt_node__insert_case2(rbt_node_t* node) {
  if (node->parent->color == rbt_color__black) {
    return; // Tree is still valid
  } else {
    rbt_node__insert_case3(node);
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

void rbt_node__insert_case1(rbt_node_t* node) {
  if (node->parent == NULL) {
    //printf("\ninsert_case1: setting to black...");
    //rbt_node__print(node);
    node->color = rbt_color__black;
  } else {
    rbt_node__insert_case2(node);
  }
}

rbt_node_t* rbt_node__head(rbt_node_t* node) {
  if (node == NULL) {
    return NULL;
  }
  rbt_node_t* iter   = node;
  rbt_node_t* parent = node->parent;
  while (parent) {
    iter   = parent;
    parent = iter->parent;
  }
  return iter;
}

rbt_node_t* rbt_node__minimum(rbt_node_t* node) {
  if (node == NULL) {
    return NULL;
  }
  rbt_node_t* iter = node;
  rbt_node_t* left = node->left;
  while (left) {
    iter = left;
    left = iter->left;
  }
  return iter;
}

rbt_node_t* rbt_node__maximum(rbt_node_t* node) {
  if (node == NULL) {
    return NULL;
  }
  rbt_node_t* iter  = node;
  rbt_node_t* right = node->right;
  while (right) {
    iter  = right;
    right = iter->right;
  }
  return iter;
}

rbt_node_t* rbt_node__minimum_not_less_than(rbt_node_t* node, f2size_t size) {
  if (node == NULL) {
    return NULL;
  }
  if (node->key >= size) {
    rbt_node_t* left__minimum_not_less_than = NULL;
    if (node->left) {
      left__minimum_not_less_than = rbt_node__minimum_not_less_than(node->left, size);
    }
    if (left__minimum_not_less_than) {
      return left__minimum_not_less_than;
    } else {
      return node;
    }
  } else {
    rbt_node_t* right__minimum_not_less_than = NULL;
    if (node->right) {
      right__minimum_not_less_than = rbt_node__minimum_not_less_than(node->right, size);
    }
    if (right__minimum_not_less_than) {
      return right__minimum_not_less_than;
    } else {
      return NULL;
    }
  }
}

int rbt_node__contains(rbt_node_t* root_node, rbt_node_t* node) {
  if (root_node == NULL) {
    return 0;
  }
  rbt_node_t* iter = node;
  while(iter && root_node != iter) {
    rbt_node_t* parent = iter->parent;
    if (!parent || (parent->left != iter && parent->right != iter)) {
      iter = NULL;
    }
  }
  if (root_node == iter) {
    return 1;
  }
  return 0;
}

int rbt_tree__contains(rbt_tree_t* tree, rbt_node_t* node) {
  return rbt_node__contains(tree->head, node);
}

void rbt_node__simple_binary_insert(rbt_node_t* root_node, rbt_node_t* new_node) {
#ifdef DEBUG_REDBLACKTREE
  debug__assert(!rbt_node__contains(root_node, new_node), nil, "rbt_node__simple_binary_insert failed: node already exists in root.");
#endif
  if (new_node->key < root_node->key) {
    if (root_node->left == NULL) {
      new_node->parent = root_node;
      new_node->left   = NULL;
      new_node->right  = NULL;
      root_node->left  = new_node;
    } else {
      rbt_node__simple_binary_insert(root_node->left, new_node);
    }
  } else {
    if (root_node->right == NULL) {
      new_node->parent = root_node;
      new_node->left   = NULL;
      new_node->right  = NULL;
      root_node->right = new_node;
    } else {
      rbt_node__simple_binary_insert(root_node->right, new_node);
    }
  }
}

void rbt_node__print(rbt_node_t* node) {
  if (node == NULL) {
    printf("nil");
  } else {
    printf("[%lx " f2size_t__fstr " %s ", (unsigned long)node, node->key, (node->color == rbt_color__red) ? "red" : ((node->color == rbt_color__black) ? "black" : "unknown"));
    rbt_node__print(node->left);
    printf(" . ");
    rbt_node__print(node->right);
    printf("]");
  }
}

void rbt_tree__init(rbt_tree_t* tree, rbt_node_t* head, ptr memorypool_beginning) {
  tree->memorypool_beginning = memorypool_beginning;
  tree->head                 = head;
  status("rbt_tree__init: memorypool_beginning=" u64__fstr ".", memorypool_beginning);
}

// reinitialize this node and all children of this node.
void rbt_node__reinit(rbt_node_t* node, s64 difference) {
  if (node->parent != NULL) {
    ptr parent    = to_ptr(node->parent);
    parent       += difference;
    node->parent  = (rbt_node_t*)from_ptr(parent);
  }
  if (node->left != NULL) {
    ptr left    = to_ptr(node->left);
    left       += difference;
    node->left  = (rbt_node_t*)from_ptr(left);
    rbt_node__reinit(node->left, difference);
  }
  if (node->right != NULL) {
    ptr right    = to_ptr(node->right);
    right       += difference;
    node->right  = (rbt_node_t*)from_ptr(right);
    rbt_node__reinit(node->right, difference);
  }
}

// reinitialize tree and all nodes within tree.
void rbt_tree__reinit(rbt_tree_t* tree, ptr new_memorypool_beginning) {
  ptr old_memorypool_beginning = tree->memorypool_beginning;
  s64 difference               = new_memorypool_beginning - old_memorypool_beginning;
  status("rbt_tree__reinit: new_memorypool_beginning=" u64__fstr ".", new_memorypool_beginning);
  status("rbt_tree__reinit: old_memorypool_beginning=" u64__fstr ".", old_memorypool_beginning);
  status("rbt_tree__reinit: difference=" s64__fstr ".", difference);
  if (tree->head != NULL) {
    ptr head    = to_ptr(tree->head);
    status("rbt_tree__reinit: old head=" s64__fstr ".", head);
    head       += difference;
    tree->head  = (rbt_node_t*)from_ptr(head);
    status("rbt_tree__reinit: new head=" s64__fstr ".", head);
    rbt_node__reinit(tree->head, difference);
  }
  tree->memorypool_beginning = new_memorypool_beginning;
}

void rbt_tree__free_all_nodes(rbt_tree_t* tree) {
  if (tree->head != NULL) {
    rbt_node__free_all_nodes(tree->head);
  }
}

boolean_t rbt_tree__empty(rbt_tree_t* tree) {
  return (tree->head == NULL);
}

void rbt_tree__print(rbt_tree_t* tree) {
  rbt_node__print(tree->head);
}

void rbt_tree__simple_binary_insert(rbt_tree_t* tree, rbt_node_t* node) {
  node->parent = NULL;
  node->left   = NULL;
  node->right  = NULL;
  if (tree->head == NULL) {
    tree->head = node;
  } else {
    rbt_node__simple_binary_insert(tree->head, node);
  }
}

void rbt_tree__insert(rbt_tree_t* tree, rbt_node_t* node) {
  rbt_tree__simple_binary_insert(tree, node);
  node->color = rbt_color__red;
  rbt_node__insert_case1(node);
  tree->head = rbt_node__head(tree->head);
}

void rbt_node__delete_case6(rbt_node_t* node) {
  rbt_node_t* node__sibling = rbt_node__sibling(node);
  node__sibling->color = node->parent->color;
  node->parent->color = rbt_color__black;
  if (node == node->parent->left) {
    // Here, node__sibling->right->color == rbt_color__red.
    node__sibling->right->color = rbt_color__black;
    rbt_node__rotate_left(node->parent);
  } else {
    // Here, node__sibling->left->color == rbt_color__red.
    node__sibling->left->color = rbt_color__black;
    rbt_node__rotate_right(node->parent);
  }
}

void rbt_node__delete_case5(rbt_node_t* node) {
  rbt_node_t* node__sibling = rbt_node__sibling(node);
  if ((node == node->parent->left) &&
      rbt_node__is_black(node__sibling) &&
      rbt_node__is_red(node__sibling->left) &&
      rbt_node__is_black(node__sibling->right)) {
    node__sibling->color       = rbt_color__red;
    node__sibling->left->color = rbt_color__black;
    rbt_node__rotate_right(node__sibling);
  } else if ((node == node->parent->right) &&
	     rbt_node__is_black(node__sibling) &&
	     rbt_node__is_red(node__sibling->right) &&
	     rbt_node__is_black(node__sibling->left)) {
    node__sibling->color        = rbt_color__red;
    node__sibling->right->color = rbt_color__black;
    rbt_node__rotate_left(node__sibling);
  }
  rbt_node__delete_case6(node);
}

void rbt_node__delete_case4(rbt_node_t* node) {
  rbt_node_t* node__sibling = rbt_node__sibling(node);
  if (rbt_node__is_red(node->parent) &&
      rbt_node__is_black(node__sibling) &&
      rbt_node__is_black(node__sibling->left) &&
      rbt_node__is_black(node__sibling->right)) {
    node__sibling->color = rbt_color__red;
    node->parent->color = rbt_color__black;
  } else if (node->parent) {
    rbt_node__delete_case5(node);
  }
}

void rbt_node__delete_case1(rbt_node_t* node);

void rbt_node__delete_case3(rbt_node_t* node) {
  rbt_node_t* node__sibling = rbt_node__sibling(node);
  if (node__sibling) {
    if (rbt_node__is_black(node->parent) &&
	rbt_node__is_black(node__sibling) &&
	rbt_node__is_black(node__sibling->left) &&
	rbt_node__is_black(node__sibling->right)) {
      node__sibling->color = rbt_color__red;
      rbt_node__delete_case1(node->parent);
    } else {
      rbt_node__delete_case4(node);
    }
  }
}

void rbt_node__delete_case2(rbt_node_t* node) {
  rbt_node_t* node__sibling = rbt_node__sibling(node);
  
  if (rbt_node__is_red(node__sibling)) {
    node->parent->color  = rbt_color__red;
    node__sibling->color = rbt_color__black;
    if (node == node->parent->left)
      rbt_node__rotate_left(node->parent);
    else
      rbt_node__rotate_right(node->parent);
  }
  rbt_node__delete_case3(node);
}

void rbt_node__delete_case1(rbt_node_t* node) {
  if (node->parent) {
    rbt_node__delete_case2(node);
  }
}

void rbt_tree__remove_with_at_most_one_child(rbt_tree_t* tree, rbt_node_t* node) {
  rbt_node_t* node__child  = (node->left != NULL) ? node->left : node->right;
  rbt_node_t* node__parent = node->parent;
  rbt_node_t* node__left   = node->left;
  rbt_node_t* node__right  = node->right;
  
  if (node__left == NULL) { 
    if (node__parent) {
      if (node__parent->right == node) {
	node__parent->right = node__right;
	if (node__right) {
	  node__right->parent = node__parent;
	}
      } else {
	node__parent->left = node__right;
	if (node__right) {
	  node__right->parent = node__parent;
	}
      }
    } else {
      tree->head = node__right;
      if (node__right) {
	node__right->parent = NULL;
      }
    }
  } else { // (node->right == NULL)
    if (node__parent) {
      if (node__parent->right == node) {
	node__parent->right = node__left;
	if (node__left) {
	  node__left->parent = node__parent;
	}
      } else {
	node__parent->left = node__left;
	if (node__left) {
	  node__left->parent = node__parent;
	}
      }
    } else {
      tree->head = node__left;
      if (node__left) {
	node__left->parent = NULL;
      }
    }
  }
  
  if (node__child) {
    if (node->color == rbt_color__black) {
      if (node__child->color == rbt_color__red) {
	node__child->color = rbt_color__black;
      } else {
	rbt_node__delete_case1(node__child);
      }
    }
  }
}

void rbt_node__replace_node(rbt_node_t* dest, rbt_node_t* src) {
  rbt_node_t* src__parent = src->parent;
  rbt_node_t* src__left   = src->left;
  rbt_node_t* src__right  = src->right;
  dest->parent = src__parent;
  dest->left   = src__left;
  dest->right  = src__right;
  if (src__parent) {
    if (src__parent->left == src) {
      src__parent->left = dest;
    } else { // (src__parent->right == src)
#ifdef DEBUG_REDBLACKTREE
      debug__assert(src__parent->right == src, nil, "rbt_node__replace_node assertion failure: src__parent->right == src.");
#endif
      src__parent->right = dest;
    }
  }
  if (src__left) {
    src__left->parent = dest;
  }
  if (src__right) {
    src__right->parent = dest;
  }
#ifdef DEBUG_REDBLACKTREE
  debug__assert(rbt_node__is_valid(dest), nil, "rbt_node__replace_node assertion failure: rbt_node__is_valid(dest).");
#endif
}

void rbt_node__swap_nodes(rbt_node_t* node1, rbt_node_t* node2) {
  rbt_node_t* node1__parent       = node1->parent;
  rbt_node_t* node1__parent__left = node1->parent ? node1->parent->left : NULL;
  rbt_node_t* node1__left         = node1->left;
  rbt_node_t* node1__right        = node1->right;
  rbt_color_t node1__color        = node1->color;
  rbt_node_t* node2__parent       = node2->parent;
  rbt_node_t* node2__parent__left = node2->parent ? node2->parent->left : NULL;
  rbt_node_t* node2__left         = node2->left;
  rbt_node_t* node2__right        = node2->right;
  rbt_color_t node2__color        = node2->color;
  
  // copy values to node2
  if (node1__parent == node2) {
    node2->parent = node1;
  } else {
    node2->parent = node1__parent;
    if (node1__parent) {
      if (node1__parent__left == node1) {
	node1__parent->left = node2;
      } else { // (node1__parent->right == node1)
#ifdef DEBUG_REDBLACKTREE
	debug__assert(node1__parent->right == node1, nil, "rbt_node__replace_node assertion failure: node1__parent->right == node1.");
#endif
	node1__parent->right = node2;
      }
    }
  }
  if (node1__left == node2) {
    node2->left = node1;
  } else {
    node2->left = node1__left;
    if (node1__left) {
      node1__left->parent = node2;
    }
  }
  if (node1__right  == node2) {
    node2->right = node1;
  } else {
    node2->right = node1__right;
    if (node1__right) {
      node1__right->parent = node2;
    }
  }
  node2->color = node1__color;
  
  // copy values to node1
  if (node2__parent == node1) {
    node1->parent = node2;
  } else {
    node1->parent = node2__parent;
    if (node2__parent) {
      if (node2__parent__left == node2) {
	node2__parent->left = node1;
      } else { // (node1__parent->right == node1)
#ifdef DEBUG_REDBLACKTREE
	debug__assert(node2__parent->right == node2, nil, "rbt_node__replace_node assertion failure: node2__parent->right == node2.");
#endif
	node2__parent->right = node1;
      }
    }
  }
  if (node2__left == node1) {
    node1->left = node2;
  } else {
    node1->left = node2__left;
    if (node2__left) {
      node2__left->parent = node1;
    }
  }
  if (node2__right == node1) {
    node1->right = node2;
  } else {
    node1->right = node2__right;
    if (node2__right) {
      node2__right->parent = node1;
    }
  }
  node1->color = node2__color;
#ifdef DEBUG_REDBLACKTREE
  debug__assert(rbt_node__is_valid(node1), nil, "rbt_node__swap_node assertion failure: rbt_node__is_valid(node1).");
  debug__assert(rbt_node__is_valid(node2), nil, "rbt_node__swap_node assertion failure: rbt_node__is_valid(node2).");
#endif
}

void rbt_tree__remove(rbt_tree_t* tree, rbt_node_t* node) {
  if (node->left == NULL || node->right == NULL) { 
    rbt_tree__remove_with_at_most_one_child(tree, node);
  } else {
    rbt_node_t* node__left__max = rbt_node__maximum(node->left);
    
    debug__assert(node__left__max->right == NULL, nil, "rbt_node__simple_binary_remove: (node__left__max->right == NULL) failed.");
    
    rbt_node__swap_nodes(node__left__max, node);
    
    rbt_tree__remove_with_at_most_one_child(tree, node);
    
    if (node__left__max->parent == NULL) {
      tree->head = node__left__max;
    }
  }
  
  tree->head = rbt_node__head(tree->head); 
  
  if (tree->head) {
    if (tree->head->color == rbt_color__red) {
      tree->head->color = rbt_color__black;
    }
  }
  
#ifdef DEBUG_REDBLACKTREE
  debug__assert(! rbt_tree__contains(tree, node), nil, "rbt_tree__remove failed: tree still contains node.");
#endif
}

rbt_node_t* rbt_tree__minimum(rbt_tree_t* tree) {
  return rbt_node__minimum(tree->head);
}

rbt_node_t* rbt_tree__maximum(rbt_tree_t* tree) {
  return rbt_node__maximum(tree->head);
}

rbt_node_t* rbt_tree__minimum_not_less_than(rbt_tree_t* tree, f2size_t size) {
  return rbt_node__minimum_not_less_than(tree->head, size);
}

int rbt_tree__size(rbt_tree_t* tree) {
  int size = 0;
  rbt_node_t* iter = rbt_tree__minimum(tree);
  while (iter) {
    size ++;
    iter = rbt_node__next(iter);
  }
  return size;
}

rbt_node_t* rbt_node__next(rbt_node_t* node) {
  if (node->right != NULL) {
    return rbt_node__minimum(node->right);
  } else {
    if (node->parent == NULL) {
      return NULL;
    } else {
      while (node && node->parent) {
	if (node->parent->left == node) {
	  return node->parent;
	}
	node = node->parent;
      }
      return NULL;
    }
  }
}

rbt_node_t* rbt_node__prev(rbt_node_t* node) {
  if (node->left != NULL) {
    return rbt_node__maximum(node->left);
  } else {
    if (node->parent == NULL) {
      return NULL;
    } else {
      while (node && node->parent) {
	if (node->parent->right == node) {
	  return node->parent;
	}
	node = node->parent;
      }
      return NULL;
    }
  }
}

int rbt_node__is_valid(rbt_node_t* node) {
  if (node->left) {
    if (node->left == node) {
      printf("\nrbt_node__is_valid failure: node->left == node."); fflush(stdout);
      return 0;
    }
    if (node->color == rbt_color__red && node->left->color != rbt_color__black) {
      printf("\nrbt_node__is_valid failure: node->color == rbt_color__red && node->left->color != rbt_color__black."); fflush(stdout);
      return 0;
    }
    if (node->left->parent != node) {
      printf("\nrbt_node__is_valid failure: node->left->parent != node."); fflush(stdout);
      return 0;
    }
    if (! rbt_node__is_valid(node->left)) {
      printf("\nrbt_node__is_valid failure: ! rbt_node__is_valid(node->left)."); fflush(stdout);
      return 0;
    }
  }
  if (node->right) {
    if (node->right == node) {
      printf("\nrbt_node__is_valid failure: node->right == node."); fflush(stdout);
      return 0;
    }
    if (node->color == rbt_color__red && node->right->color != rbt_color__black) {
      printf("\nrbt_node__is_valid failure: node->color == rbt_color__red && node->right->color != rbt_color__black."); fflush(stdout);
      return 0;
    }
    if (node->right->parent != node) {
      printf("\nrbt_node__is_valid failure: node->right->parent != node."); fflush(stdout);
      return 0;
    }
    if (! rbt_node__is_valid(node->right)) {
      printf("\nrbt_node__is_valid failure: ! rbt_node__is_valid(node->right)."); fflush(stdout);
      return 0;
    }
  }
  if (node->parent) {
    if (node->parent == node) {
      printf("\nrbt_node__is_valid failure: node->parent == node."); fflush(stdout);
      return 0;
    }
  }
  return 1;
}

void rbt_tree__load_from_stream(rbt_tree_t* tree, int fd) {
  {
    ptr memorypool_beginning;
    safe_read(fd, to_ptr(&memorypool_beginning), sizeof(ptr));
    tree->memorypool_beginning = memorypool_beginning;
    status("rbt_tree__load_from_stream: memorypool_beginning=" u64__fstr ".", memorypool_beginning);
  }
  {
    ptr head;
    safe_read(fd, to_ptr(&head), sizeof(ptr));
    tree->head = (rbt_node_t*)from_ptr(head);
    status("rbt_tree__load_from_stream: head=" u64__fstr ".", head);
  }
}

void rbt_tree__save_to_stream(rbt_tree_t* tree, int fd) {
  {
    ptr memorypool_beginning = tree->memorypool_beginning;
    safe_write(fd, to_ptr(&memorypool_beginning), sizeof(ptr));
    status("rbt_tree__save_to_stream: memorypool_beginning=" u64__fstr ".", memorypool_beginning);
  }
  {
    ptr head = to_ptr(tree->head);
    safe_write(fd, to_ptr(&head), sizeof(ptr));
    status("rbt_tree__save_to_stream: head=" u64__fstr ".", head);
  }
}



// debugging and test code




int rbt_tree__is_valid(rbt_tree_t* tree) {
  if (tree->head == NULL) {
    return 1;
  } else {
    if (tree->head->parent != NULL) {
      printf("\nrbt_tree__is_valid failure: tree->head->parent != NULL."); fflush(stdout);
      return 0;
    }
    if (tree->head->color != rbt_color__black) {
      printf("\nrbt_tree__is_valid failure: tree->head->color != rbt_color__black."); fflush(stdout);
      return 0;
    }
    return rbt_node__is_valid(tree->head);
  }
}

void redblacktree__test__insert_randoms(rbt_tree_t* tree, int count) {
  int i;
  rbt_node_t* node;
  for (i = 0; i < count; i++) {
    node = (rbt_node_t*)from_ptr(f2__malloc(sizeof(rbt_node_t)));
    node->parent = NULL;
    node->left   = NULL;
    node->right  = NULL;
    node->key = random() & 0x7;
    //printf("\n  insert key: %d", node->key);
    rbt_tree__insert(tree, node);
    
    printf("\ntree: ");
    rbt_tree__print(tree);
    
    release__assert(rbt_tree__is_valid(tree), nil, "tree is not valid after insert");
  }
}

void redblacktree__test__remove_maximums() {
  rbt_tree_t  tree;
  
  printf("\ntesting maximum removal");
  
  rbt_tree__init(&tree, NULL, (ptr)0);
  
  redblacktree__test__insert_randoms(&tree, 10);
  
  printf("\ntree: ");
  rbt_tree__print(&tree);
  
  rbt_node_t* min = rbt_tree__minimum(&tree);
  rbt_node_t* max = rbt_tree__maximum(&tree);
  
  printf("\n  min key: ");
  if (min) {printf(f2size_t__fstr, min->key);} else {printf("NULL");}
  printf("\n  min tree: ");
  rbt_node__print(min);
  printf("\n  max key: ");
  if (max) {printf(f2size_t__fstr, max->key);} else {printf("NULL");}
  printf("\n  max tree: ");
  rbt_node__print(max);
  
  int count = 0;
  while (max) {
    count ++;
    printf("\n  removing max key: ");
    if (max) {printf(f2size_t__fstr, max->key);} else {printf("NULL");}
    rbt_tree__remove(&tree, max);
    
    printf("\ntree: ");
    rbt_tree__print(&tree);
    
    release__assert(rbt_tree__is_valid(&tree), nil, "tree is not valid after remove");
    
    max = rbt_tree__maximum(&tree);
  }
  release__assert(count == 10, nil, "removed incorrect number of maximum elements!");
}

void redblacktree__test__remove_minimums() {
  rbt_tree_t  tree;
  
  printf("\ntesting minimum removal");
  
  rbt_tree__init(&tree, NULL, (ptr)0);
  
  redblacktree__test__insert_randoms(&tree, 10);
  
  printf("\ntree: ");
  rbt_tree__print(&tree);
  
  rbt_node_t* min = rbt_tree__minimum(&tree);
  rbt_node_t* max = rbt_tree__maximum(&tree);
  
  printf("\n  min key: ");
  if (min) {printf(f2size_t__fstr, min->key);} else {printf("NULL");}
  printf("\n  min tree: ");
  rbt_node__print(min);
  printf("\n  max key: ");
  if (max) {printf(f2size_t__fstr, max->key);} else {printf("NULL");}
  printf("\n  max tree: ");
  rbt_node__print(max);
  
  int count = 0;
  while (min) {
    count ++;
    printf("\n  removing min key: ");
    if (min) {printf(f2size_t__fstr, min->key);} else {printf("NULL");}
    rbt_tree__remove(&tree, min);
    
    release__assert(rbt_tree__is_valid(&tree), nil, "tree is not valid after remove");
    
    printf("\ntree: ");
    rbt_tree__print(&tree);
    
    min = rbt_tree__minimum(&tree);
  }
  release__assert(count == 10, nil, "removed incorrect number of minimum elements!");
}

void redblacktree__test__iterators() {
  rbt_tree_t  tree;
  rbt_node_t* node;
  
  printf("\ntesting minimum removal");
  
  rbt_tree__init(&tree, NULL, (ptr)0);
  
  redblacktree__test__insert_randoms(&tree, 10);
  
  {
    printf("\niterating through next of minimum");
    node = rbt_tree__minimum(&tree);
    int count = 0;
    while(node) {
      printf("\niterated: " f2size_t__fstr, node->key); fflush(stdout);
      count ++;
      node = rbt_node__next(node);
    }
    release__assert(count == 10, nil, "should have iterated through 10 elements for next of minimum!");
  }
  
  {
    printf("\niterating through prev of minimum");
    node = rbt_tree__minimum(&tree);
    int count = 0;
    while(node) {
      printf("\niterated: " f2size_t__fstr, node->key); fflush(stdout);
      count ++;
      node = rbt_node__prev(node);
    }
    release__assert(count == 1, nil, "should have iterated through zero elements for previous of minimum!");
  }
  
  {
    printf("\niterating through prev of maximum");
    node = rbt_tree__maximum(&tree);
    int count = 0;
    while(node) {
      printf("\niterated: " f2size_t__fstr, node->key); fflush(stdout);
      count ++;
      node = rbt_node__prev(node);
    }
    release__assert(count == 10, nil, "should have iterated through 10 elements for prev of maximum!");
  }
  
  {
    printf("\niterating through next of maximum");
    node = rbt_tree__maximum(&tree);
    int count = 0;
    while(node) {
      printf("\niterated: " f2size_t__fstr, node->key); fflush(stdout);
      count ++;
      node = rbt_node__next(node);
    }
    release__assert(count == 1, nil, "should have iterated through zero elements for next of maximum!");
  }
}

void redblacktree__test__remove_all_with_iterators() {
  rbt_tree_t  tree;
  
  printf("\ntesting iterator removal");
  
  rbt_tree__init(&tree, NULL, (ptr)0);
  
  redblacktree__test__insert_randoms(&tree, 10);
  
  printf("\ntree: ");
  rbt_tree__print(&tree);
  
  rbt_node_t* iter = rbt_tree__minimum(&tree);
  while (iter) {
    rbt_node_t* next = rbt_node__next(iter);
    printf("\ntree: ");
    rbt_tree__print(&tree);
    
    printf("\nbefore remove: size=%d", rbt_tree__size(&tree)); fflush(stdout);
    printf("\n  removing iter key: ");
    printf(f2size_t__fstr " %lx", iter->key, (unsigned long)iter); fflush(stdout);
    
    rbt_tree__remove(&tree, iter);
    printf("\nafter remove: size=%d", rbt_tree__size(&tree)); fflush(stdout);
    
    printf("\n"); rbt_tree__print(&tree); fflush(stdout);
    
    release__assert(rbt_tree__is_valid(&tree), nil, "tree is not valid after remove");
    
    iter = next;
  }
  release__assert(tree.head == NULL, nil, "empty tree does not have NULL head");
}

void redblacktree__test__remove_with_iterators() {
  rbt_tree_t  tree;
  
  printf("\ntesting iterator removal");
  
  rbt_tree__init(&tree, NULL, (ptr)0);
  
  redblacktree__test__insert_randoms(&tree, 10);
  
  printf("\ntree: ");
  rbt_tree__print(&tree);
  
  rbt_node_t* iter = rbt_tree__minimum(&tree);
  while (iter) {
    rbt_node_t* next = rbt_node__next(iter);
    if ((random() % 2) == 0) {
      printf("\ntree: ");
      rbt_tree__print(&tree);
      
      printf("\nbefore remove: size=%d", rbt_tree__size(&tree)); fflush(stdout);
      printf("\n  removing iter key: ");
      printf(f2size_t__fstr " %lx", iter->key, (unsigned long)iter); fflush(stdout);
      
      rbt_tree__remove(&tree, iter);
      printf("\nafter remove: size=%d", rbt_tree__size(&tree)); fflush(stdout);
      
      printf("\n"); rbt_tree__print(&tree); fflush(stdout);
      
      release__assert(rbt_tree__is_valid(&tree), nil, "tree is not valid after remove");
    }
    iter = next;
  }
}

void redblacktree__tests() {
  printf("\nredblacktree__tests.");
  redblacktree__test__remove_maximums();
  redblacktree__test__remove_minimums();
  redblacktree__test__iterators();
  redblacktree__test__remove_all_with_iterators();
  // test randomized functions repeatedly
  int i;
  for(i = 0; i < 10; i++) {
    redblacktree__test__remove_with_iterators();
  }
}

void f2__redblacktree__initialize() {
#ifdef DEBUG_REDBLACKTREE
  redblacktree__tests();
#endif
}


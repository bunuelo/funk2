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

def_primobject_6_slot(interval_tree, mutate_mutex, head, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);

f2ptr raw__interval_tree__new(f2ptr cause, f2ptr head, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr mutate_mutex = f2__cmutex__new(cause);
  return f2interval_tree__new(cause,
			      mutate_mutex,
			      head,
			      left_value_funk,
			      right_value_funk,
			      value_comparison_funk,
			      value_center_funk);
}

f2ptr f2__interval_tree__new(f2ptr cause, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  return raw__interval_tree__new(cause, nil, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);
}
def_pcfunk4(interval_tree__new, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk,
	    "Returns a new interval_tree object.",
	    return f2__interval_tree__new(this_cause, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk));


f2ptr raw__interval_tree__insert(f2ptr cause, f2ptr this, f2ptr element) {
  assert_argument_type(interval_tree, this);
  f2ptr head                  = f2__interval_tree__head(cause, this);
  f2ptr left_value_funk       = f2__interval_tree__left_value_funk(  cause, this);
  f2ptr right_value_funk      = f2__interval_tree__right_value_funk( cause, this);
  f2ptr value_comparison_funk = f2__interval_tree__right_value_funk( cause, this);
  f2ptr value_center_funk     = f2__interval_tree__value_center_funk(cause, this);
  if (head == nil) {
    f2ptr left_value   = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,   f2list1__new(cause, element)));
    f2ptr right_value  = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,  f2list1__new(cause, element)));
    f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, left_value, right_value)));
    head = f2__interval_tree_node__new(cause, center_value, left_value_funk, right_value_funk, value_comparison_funk);
    f2__interval_tree__head__set(cause, this, head);
  }
  return raw__interval_tree_node__insert(cause, head, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);
}

f2ptr f2__interval_tree__insert(f2ptr cause, f2ptr this, f2ptr element) {
  return raw__interval_tree__insert(cause, this, element);
}
def_pcfunk2(interval_tree__insert, this, element,
	    "Inserts a new interval element into this interval_tree.",
	    return f2__interval_tree__insert(this_cause, this, element));


f2ptr raw__interval_tree__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "interval_tree"));
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "head"),              f2__interval_tree__head(cause, this));
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
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                    __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.insert__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.terminal_print_with_frame__funk);
  return this;
}


// interval_tree_node

def_primobject_5_slot(interval_tree_node, center_value, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);

f2ptr raw__interval_tree_node__new(f2ptr cause, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_comparison_funk) {
  f2ptr left_node                      = nil;
  f2ptr right_node                     = nil;
  f2ptr overlapping_left_redblacktree  = f2__redblacktree__new(cause, left_value_funk,  value_comparison_funk);
  f2ptr overlapping_right_redblacktree = f2__redblacktree__new(cause, right_value_funk, value_comparison_funk);
  return f2interval_tree_node__new(cause,
				   center_value,
				   left_node,
				   right_node,
				   overlapping_left_redblacktree,
				   overlapping_right_redblacktree);
}

f2ptr f2__interval_tree_node__new(f2ptr cause, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_comparison_funk) {
  return raw__interval_tree_node__new(cause, center_value, left_value_funk, right_value_funk, value_comparison_funk);
}
def_pcfunk4(interval_tree_node__new, center_value, left_value_funk, right_value_funk, value_comparison_funk,
	    "Returns a new interval_tree_node object.",
	    return f2__interval_tree_node__new(this_cause, center_value, left_value_funk, right_value_funk, value_comparison_funk));


f2ptr raw__interval_tree_node__insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  f2ptr center_value            = f2__interval_tree_node__center_value(cause, this);
  f2ptr left_value              = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), left_value_funk,       f2list1__new(cause, element)));
  f2ptr right_value             = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), right_value_funk,      f2list1__new(cause, element)));
  f2ptr left_center_comparison  = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, left_value,   center_value)));
  f2ptr center_right_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, center_value, right_value)));
  if ((left_center_comparison  != nil) &&
      (right_center_comparison != nil)) {
    // interval overlaps with center value of this node
    f2ptr overlapping_left_redblacktree  = f2__interval_tree_node__overlapping_left_redblacktree( cause, this);
    f2ptr overlapping_right_redblacktree = f2__interval_tree_node__overlapping_right_redblacktree(cause, this);
    f2__redblacktree__insert(cause, overlapping_left_redblacktree,  element);
    f2__redblacktree__insert(cause, overlapping_right_redblacktree, element);
    return nil;
  } else {
    f2ptr right_center_comparison = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_comparison_funk, f2list2__new(cause, right_value,  center_value)));
    if (right_center_comparison != nil) {
      // interval is completely to the left of the center value of this node
      f2ptr left_node = f2__interval_tree_node__left_node(cause, this);
      if (left_node == nil) {
	f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, left_value, right_value)));
	left_node = f2__interval_tree_node__new(cause, center_value, left_value_funk, right_value_funk, value_comparison_funk);
	f2__interval_tree_interval__left_node__set(cause, this, left_node);
      }
      return raw__interval_tree_node__insert(cause, left_node, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);
    } else {
      // interval is completely to the right of the center value of this node
      f2ptr right_node = f2__interval_tree_node__right_node(cause, this);
      if (right_node == nil) {
	f2ptr center_value = assert_value(f2__force_funk_apply(cause, f2__this__fiber(cause), value_center_funk, f2list2__new(cause, right_value, right_value)));
	right_node = f2__interval_tree_node__new(cause, center_value, left_value_funk, right_value_funk, value_comparison_funk);
	f2__interval_tree_interval__right_node__set(cause, this, right_node);
      }
      return raw__interval_tree_node__insert(cause, right_node, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);
    }
  }
}

f2ptr f2__interval_tree_node__insert(f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_comparison_funk, f2ptr value_center_funk) {
  assert_argument_type(interval_tree_node, this);
  return raw__interval_tree_node__insert(cause, this, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);
}
def_pcfunk6(interval_tree_node__insert, this, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk,
	    "Inserts a new interval element into this interval_tree.",
	    return f2__interval_tree_node__insert(this_cause, this, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk));




f2ptr raw__interval_tree_node__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, frame, new__symbol(cause, "print_object_type"), new__symbol(cause, "interval_tree_node"));
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
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "insert"),                    __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.insert__funk);
  f2__primobject_type__add_slot_type(cause, this, new__symbol(cause, "execute"), new__symbol(cause, "terminal_print_with_frame"), __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.terminal_print_with_frame__funk);
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
  
  initialize_primobject_6_slot(interval_tree, mutate_mutex, head, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk);
  
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.new__symbol = new__symbol(cause, "new");
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(interval_tree__new, left_value_funk, right_value_funk, value_comparison_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.new__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.insert__symbol = new__symbol(cause, "insert");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__insert, this, element, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.insert__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  
  // interval_tree_node
  
  initialize_primobject_5_slot(interval_tree_node, center_value, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);
  
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.new__symbol = new__symbol(cause, "new");
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(interval_tree_node__new, center_value, left_value_funk, right_value_funk, value_comparison_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.new__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.insert__symbol = new__symbol(cause, "insert");
  {f2__primcfunk__init__with_c_cfunk_var__6_arg(interval_tree_node__insert, this, element, left_value_funk, right_value_funk, value_comparison_funk, value_center_funk, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.insert__funk = never_gc(cfunk);}
  __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(interval_tree_node__terminal_print_with_frame, this, terminal_print_frame, cfunk); __funk2.globalenv.object_type.primobject.primobject_type_interval_tree_node.terminal_print_with_frame__funk = never_gc(cfunk);}
  
}


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



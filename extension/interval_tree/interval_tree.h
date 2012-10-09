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

#ifndef F2__EXTENSION__INTERVAL_TREE__H
#define F2__EXTENSION__INTERVAL_TREE__H

#include "../../c/funk2.h"

// interval_tree

def_header_ceframe10(interval_tree,
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

f2ptr raw__interval_tree__new                                                  (f2ptr cause, f2ptr head, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr  f2__interval_tree__new                                                  (f2ptr cause, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree__assert_valid                                         (f2ptr cause, f2ptr this);
f2ptr  f2__interval_tree__assert_valid                                         (f2ptr cause, f2ptr this);
f2ptr raw__interval_tree__insert__thread_unsafe                                (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__insert                                               (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__insert                                               (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__remove__thread_unsafe                                (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__remove                                               (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__remove                                               (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__remove_node_with_at_most_one_child                   (f2ptr cause, f2ptr this, f2ptr node);
f2ptr  f2__interval_tree__remove_node_with_at_most_one_child                   (f2ptr cause, f2ptr this, f2ptr node);
f2ptr raw__interval_tree__remove_node                                          (f2ptr cause, f2ptr this, f2ptr node);
f2ptr raw__interval_tree__lookup_key_count                                     (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__lookup_key_count                                     (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__contains                                             (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__contains                                             (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__intervals__thread_unsafe                             (f2ptr cause, f2ptr this);
f2ptr raw__interval_tree__intervals                                            (f2ptr cause, f2ptr this);
f2ptr  f2__interval_tree__intervals                                            (f2ptr cause, f2ptr this);
f2ptr raw__interval_tree__add_intervals_containing_value_to_list__thread_unsafe(f2ptr cause, f2ptr this, f2ptr value, f2ptr list);
f2ptr raw__interval_tree__add_intervals_containing_value_to_list               (f2ptr cause, f2ptr this, f2ptr value, f2ptr list);
f2ptr  f2__interval_tree__add_intervals_containing_value_to_list               (f2ptr cause, f2ptr this, f2ptr value, f2ptr list);
f2ptr raw__interval_tree__intervals_containing_value__thread_unsafe            (f2ptr cause, f2ptr this, f2ptr value);
f2ptr raw__interval_tree__intervals_containing_value                           (f2ptr cause, f2ptr this, f2ptr value);
f2ptr  f2__interval_tree__intervals_containing_value                           (f2ptr cause, f2ptr this, f2ptr value);
f2ptr raw__interval_tree__intervals_overlapping_range__thread_unsafe           (f2ptr cause, f2ptr this, f2ptr range_left_value, f2ptr range_right_value);
f2ptr raw__interval_tree__intervals_overlapping_range                          (f2ptr cause, f2ptr this, f2ptr range_left_value, f2ptr range_right_value);
f2ptr  f2__interval_tree__intervals_overlapping_range                          (f2ptr cause, f2ptr this, f2ptr range_left_value, f2ptr range_right_value);
f2ptr raw__interval_tree__intervals_overlapping_interval__thread_unsafe        (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__intervals_overlapping_interval                       (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__intervals_overlapping_interval                       (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__most_recent_filtered_intervals__thread_unsafe        (f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr maximum_value);
f2ptr raw__interval_tree__most_recent_filtered_intervals                       (f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr maximum_value);
f2ptr  f2__interval_tree__most_recent_filtered_intervals                       (f2ptr cause, f2ptr this, f2ptr filter_funk, f2ptr user_filter_data, f2ptr maximum_value);
f2ptr raw__interval_tree__terminal_print_with_frame                            (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr  f2__interval_tree__terminal_print_with_frame                            (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__interval_tree_type__new_aux(f2ptr cause);


// interval_tree_node

def_header_ceframe7(interval_tree_node, color, center_value, parent_node, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);

f2ptr     raw__interval_tree_node__new                                                   (f2ptr cause, f2ptr color, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr      f2__interval_tree_node__new                                                   (f2ptr cause, f2ptr color, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr     raw__interval_tree_node__assert_valid                                          (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__assert_valid                                          (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__assert_valid_recursively                              (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__assert_valid_recursively                              (f2ptr cause, f2ptr this);
boolean_t raw__interval_tree_node__is_empty                                              (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__is_empty                                              (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__simple_insert                                         (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr      f2__interval_tree_node__simple_insert                                         (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__simple_remove                                         (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr      f2__interval_tree_node__simple_remove                                         (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
boolean_t raw__interval_tree_node__is_black                                              (f2ptr cause, f2ptr this);
boolean_t raw__interval_tree_node__is_red                                                (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__grandparent_node                                      (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__rotate_left                                           (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__rotate_right                                          (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__uncle_node                                            (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__sibling_node                                          (f2ptr cause, f2ptr node);
f2ptr     raw__interval_tree_node__head                                                  (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__head                                                  (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__minimum_node                                          (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__minimum_node                                          (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__maximum_node                                          (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__maximum_node                                          (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__insert_case_5                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__insert_case_4                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__insert_case_3                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__insert_case_2                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__insert_case_1                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__insert                                                (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr      f2__interval_tree_node__insert                                                (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__delete_case_6                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__delete_case_5                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__delete_case_4                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__delete_case_3                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__delete_case_2                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr     raw__interval_tree_node__delete_case_1                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr      f2__interval_tree_node__delete_case_1                                         (f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
void      raw__interval_tree_node__replace_node                                          (f2ptr cause, f2ptr dest, f2ptr src);
f2ptr     raw__interval_tree_node__swap_nodes                                            (f2ptr cause, f2ptr node1, f2ptr node2);
f2ptr      f2__interval_tree_node__swap_nodes                                            (f2ptr cause, f2ptr node1, f2ptr node2);
f2ptr     raw__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(f2ptr cause, f2ptr this, f2ptr value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr      f2__interval_tree_node__find_and_remove_an_arbitrary_interval_containing_value(f2ptr cause, f2ptr this, f2ptr value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr     raw__interval_tree_node__add_intervals_containing_value_to_list                (f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr      f2__interval_tree_node__add_intervals_containing_value_to_list                (f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr     raw__interval_tree_node__overlapping_elements                                  (f2ptr cause, f2ptr this);
f2ptr      f2__interval_tree_node__overlapping_elements                                  (f2ptr cause, f2ptr this);
f2ptr     raw__interval_tree_node__terminal_print_with_frame                             (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);
f2ptr      f2__interval_tree_node__terminal_print_with_frame                             (f2ptr cause, f2ptr this, f2ptr terminal_print_frame);

f2ptr f2__interval_tree_node_type__new_aux(f2ptr cause);





// **

f2ptr f2__interval_tree__core_extension__ping      (f2ptr cause);
f2ptr f2__interval_tree__core_extension__initialize(f2ptr cause);
f2ptr f2__interval_tree__core_extension__destroy   (f2ptr cause);

#endif // F2__EXTENSION__INTERVAL_TREE__H


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

#ifndef F2__PRIMOBJECT__INTERVAL_TREE__TYPES__H
#define F2__PRIMOBJECT__INTERVAL_TREE__TYPES__H

// interval_tree

typedef struct funk2_object_type__interval_tree__slot_s funk2_object_type__interval_tree__slot_t;
declare_object_type_9_slot(interval_tree, mutate_cmutex, head, all_left_redblacktree, all_right_redblacktree, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk,
			   f2ptr insert__symbol;
			   f2ptr insert__funk;
			   f2ptr remove__symbol;
			   f2ptr remove__funk;
			   f2ptr intervals__symbol;
			   f2ptr intervals__funk;
			   f2ptr intervals_containing_value__symbol;
			   f2ptr intervals_containing_value__funk;
			   f2ptr intervals_overlapping_interval__symbol;
			   f2ptr intervals_overlapping_interval__funk;
			   f2ptr add_intervals_containing_value_to_list__symbol;
			   f2ptr add_intervals_containing_value_to_list__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );


// interval_tree_node

typedef struct funk2_object_type__interval_tree_node__slot_s funk2_object_type__interval_tree_node__slot_t;
declare_object_type_7_slot(interval_tree_node, color, center_value, parent_node, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree,
			   f2ptr simple_insert__symbol;
			   f2ptr simple_insert__funk;
			   f2ptr simple_remove__symbol;
			   f2ptr simple_remove__funk;
			   f2ptr insert__symbol;
			   f2ptr insert__funk;
			   f2ptr add_intervals_containing_value_to_list__symbol;
			   f2ptr add_intervals_containing_value_to_list__funk;
			   f2ptr overlapping_elements__symbol;
			   f2ptr overlapping_elements__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__PRIMOBJECT__INTERVAL_TREE__TYPES__H


#ifndef F2__PRIMOBJECT__INTERVAL_TREE__H
#define F2__PRIMOBJECT__INTERVAL_TREE__H

#include "f2_primobjects.h"

// interval_tree

declare_primobject_9_slot(interval_tree, mutate_cmutex, head, all_left_redblacktree, all_right_redblacktree, left_value_funk, right_value_funk, value_equality_funk, value_comparison_funk, value_center_funk);

f2ptr raw__interval_tree__new                                   (f2ptr cause, f2ptr head, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr  f2__interval_tree__new                                   (f2ptr cause, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree__insert                                (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__insert                                (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__remove                                (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__remove                                (f2ptr cause, f2ptr this, f2ptr element);
f2ptr raw__interval_tree__intervals                             (f2ptr cause, f2ptr this);
f2ptr  f2__interval_tree__intervals                             (f2ptr cause, f2ptr this);
f2ptr raw__interval_tree__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list);
f2ptr  f2__interval_tree__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list);
f2ptr raw__interval_tree__intervals_containing_value            (f2ptr cause, f2ptr this, f2ptr value);
f2ptr  f2__interval_tree__intervals_containing_value            (f2ptr cause, f2ptr this, f2ptr value);
f2ptr raw__interval_tree__intervals_overlapping_interval        (f2ptr cause, f2ptr this, f2ptr element);
f2ptr  f2__interval_tree__intervals_overlapping_interval        (f2ptr cause, f2ptr this, f2ptr element);

void  raw__interval_tree__remove_node_with_at_most_one_child(f2ptr cause, f2ptr this, f2ptr node);
void  raw__interval_tree__remove_node                       (f2ptr cause, f2ptr this, f2ptr node);


f2ptr f2interval_tree__primobject_type__new_aux(f2ptr cause);


// interval_tree_node

declare_primobject_7_slot(interval_tree_node, color, center_value, parent_node, left_node, right_node, overlapping_left_redblacktree, overlapping_right_redblacktree);

f2ptr raw__interval_tree_node__new                                   (f2ptr cause, f2ptr color, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr  f2__interval_tree_node__new                                   (f2ptr cause, f2ptr color, f2ptr center_value, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr raw__interval_tree_node__insert                                (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr  f2__interval_tree_node__insert                                (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree_node__simple_remove                         (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr  f2__interval_tree_node__simple_remove                         (f2ptr cause, f2ptr this, f2ptr element, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr raw__interval_tree_node__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);
f2ptr  f2__interval_tree_node__add_intervals_containing_value_to_list(f2ptr cause, f2ptr this, f2ptr value, f2ptr list, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk);

f2ptr raw__interval_tree_node__head         (f2ptr cause, f2ptr this);
f2ptr raw__interval_tree_node__minimum_node (f2ptr cause, f2ptr this);
f2ptr raw__interval_tree_node__maximum_node (f2ptr cause, f2ptr this);

f2ptr raw__interval_tree_node__insert_case_5(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree_node__insert_case_4(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree_node__insert_case_3(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree_node__insert_case_2(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);
f2ptr raw__interval_tree_node__insert_case_1(f2ptr cause, f2ptr this, f2ptr left_value_funk, f2ptr right_value_funk, f2ptr value_equality_funk, f2ptr value_comparison_funk, f2ptr value_center_funk);

void  raw__interval_tree_node__delete_case_6(f2ptr cause, f2ptr this);
void  raw__interval_tree_node__delete_case_5(f2ptr cause, f2ptr this);
void  raw__interval_tree_node__delete_case_4(f2ptr cause, f2ptr this);
void  raw__interval_tree_node__delete_case_3(f2ptr cause, f2ptr this);
void  raw__interval_tree_node__delete_case_2(f2ptr cause, f2ptr this);
void  raw__interval_tree_node__delete_case_1(f2ptr cause, f2ptr this);
void  raw__interval_tree_node__replace_node (f2ptr cause, f2ptr dest, f2ptr src);
void  raw__interval_tree_node__swap_nodes   (f2ptr cause, f2ptr node1, f2ptr node2);




f2ptr f2interval_tree_node__primobject_type__new_aux(f2ptr cause);


// **

void f2__primobject__interval_tree__reinitialize_globalvars();
void f2__primobject__interval_tree__initialize();

#endif // F2__PRIMOBJECT__INTERVAL_TREE__H



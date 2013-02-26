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

#ifndef F2__GRAPHVIZ__H
#define F2__GRAPHVIZ__H

f2ptr f2__graphviz__digraph          (f2ptr cause, f2ptr codes);
f2ptr f2__graphviz__node_color       (f2ptr cause, f2ptr color);
f2ptr f2__graphviz__edge_color       (f2ptr cause, f2ptr color);
f2ptr f2__graphviz__node             (f2ptr cause, f2ptr name, f2ptr label, f2ptr color);
f2ptr f2__graphviz__box_node         (f2ptr cause, f2ptr name, f2ptr label, f2ptr color);
f2ptr f2__graphviz__edge_tail_head   (f2ptr cause, f2ptr tail, f2ptr head);
f2ptr f2__graphviz__edge             (f2ptr cause, f2ptr from_node, f2ptr to_node, f2ptr color);
f2ptr f2__graphviz__exp__as__color   (f2ptr cause, f2ptr exp);
f2ptr f2__graphviz__exp__as__label   (f2ptr cause, f2ptr exp);
f2ptr f2__graphviz__exp__as__name    (f2ptr cause, f2ptr exp);
f2ptr f2__graphviz__edge_name        (f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node);
f2ptr f2__graphviz__raw_labelled_edge(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node, f2ptr color);
f2ptr f2__graphviz__labelled_edge    (f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node);

// **

void f2__graphviz__initialize();

#endif // F2__GRAPHVIZ__H


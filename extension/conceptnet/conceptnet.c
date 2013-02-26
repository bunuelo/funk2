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

#include "../../c/funk2.h"
#include "conceptnet.h"


def_ceframe1(conceptnet, conceptnet, graph);

f2ptr raw__conceptnet__new(f2ptr cause, f2ptr graph) {
  return f2conceptnet__new(cause, graph);
}

f2ptr f2__conceptnet__new(f2ptr cause) {
  f2ptr graph = f2__graph__new(cause);
  return raw__conceptnet__new(cause, graph);
}
export_cefunk0(conceptnet__new, 0, "Returns a new conceptnet object.");


f2ptr f2__conceptnet__new_from_graph_file(f2ptr cause, f2ptr filename, f2ptr max_edges_to_load) {
  if ((! raw__string__is_type(cause, filename)) ||
      (! raw__integer__is_type(cause, max_edges_to_load))) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr graph_file_string = f2__string__load(cause, filename);
  s64 max_edges_to_load__i = f2integer__i(max_edges_to_load, cause);
  if (raw__larva__is_type(cause, graph_file_string)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr this           = f2__conceptnet__new(cause);
  f2ptr graph          = f2__conceptnet__graph(cause, this);
  f2ptr node_ptypehash = f2__ptypehash__new(cause);
  f2ptr empty_string         = new__string(cause, "");
  f2ptr newline_string       = new__string(cause, "\n");
  f2ptr tab_string           = new__string(cause, "\t");
  f2ptr begin_squigly_string = new__string(cause, "{");
  f2ptr end_squigly_string   = new__string(cause, "}");
  f2ptr comma_space_string   = new__string(cause, ", ");
  f2ptr colon_space_string   = new__string(cause, ": ");
  f2ptr quote_string         = new__string(cause, "\'");
  f2ptr u_quote_string       = new__string(cause, "u\'");
  {
    f2ptr graph_file_line_strings = f2__string__split(cause, graph_file_string, newline_string);
    {
      s64 line_index = 0;
      f2ptr iter = graph_file_line_strings;
      while (iter != nil) {
	f2ptr graph_file_line_string = f2__cons__car(cause, iter);
	if (line_index < max_edges_to_load__i) {
	  f2ptr graph_file_line_tab_strings = f2__string__split(cause, graph_file_line_string, tab_string);
	  f2ptr tab_iter = graph_file_line_tab_strings;
	  {
	    f2ptr left_concept      = f2__cons__car(cause, tab_iter); tab_iter = f2__cons__cdr(cause, tab_iter);
	    f2ptr right_concept     = f2__cons__car(cause, tab_iter); tab_iter = f2__cons__cdr(cause, tab_iter);
	    f2ptr edge_label_string = f2__cons__car(cause, tab_iter); tab_iter = f2__cons__cdr(cause, tab_iter);
	    //printf("\nleft_concept.....: "); f2__print(cause, left_concept);
	    //printf("\nright_concept....: "); f2__print(cause, right_concept);
	    //printf("\nedge_label_string: "); f2__print(cause, edge_label_string);
	    {
	      f2ptr edge_label_string_without_left_squiglies = f2__string__replace_all(cause, edge_label_string,                        begin_squigly_string, empty_string);
	      f2ptr edge_label_string_without_squiglies      = f2__string__replace_all(cause, edge_label_string_without_left_squiglies, end_squigly_string,   empty_string);
	      //printf("\nedge_label_string_without_squiglies: "); f2__print(cause, edge_label_string_without_squiglies);
	      f2ptr edge_label_strings = f2__string__split(cause, edge_label_string_without_squiglies, comma_space_string);
	      {
		f2ptr edge_label_iter = edge_label_strings;
		while (edge_label_iter != nil) {
		  f2ptr edge_label_pair_string = f2__cons__car(cause, edge_label_iter);
		  {
		    //printf("\nedge_label_pair_string: "); f2__print(cause, edge_label_pair_string);
		    f2ptr edge_label_pair = f2__string__split(cause, edge_label_pair_string, colon_space_string);
		    {
		      f2ptr edge_label_pair_iter = edge_label_pair;
		      f2ptr edge_key_string   = f2__cons__car(cause, edge_label_pair_iter); edge_label_pair_iter = f2__cons__cdr(cause, edge_label_pair_iter);
		      f2ptr edge_value_string = f2__cons__car(cause, edge_label_pair_iter); edge_label_pair_iter = f2__cons__cdr(cause, edge_label_pair_iter);
		      if (edge_label_pair_iter != nil) {
			printf("\nconceptnet-new_from_graph_file warning: edge_label_pair_iter != nil."); fflush(stdout);
		      }
		      //printf("\nedge_key_string: ");   f2__print(cause, edge_key_string);
		      //printf("\nedge_value_string: "); f2__print(cause, edge_value_string);
		      f2ptr edge_key_string_without_quotes   = f2__string__replace_all(cause, f2__string__replace_all(cause, edge_key_string, u_quote_string, empty_string),
										       quote_string, empty_string);
		      f2ptr edge_value_string_without_quotes = f2__string__replace_all(cause, f2__string__replace_all(cause, edge_value_string, u_quote_string, empty_string),
										       quote_string, empty_string);
		      //printf("\nedge_key_string_without_quotes: ");   f2__print(cause, edge_key_string_without_quotes);
		      //printf("\nedge_value_string_without_quotes: "); f2__print(cause, edge_value_string_without_quotes);
		      
		      f2ptr edge_key = f2__string__as__symbol(cause, edge_key_string_without_quotes);
		      if (raw__eq(cause, edge_key, new__symbol(cause, "rel"))) {
			f2ptr edge_symbol          = f2__string__as__symbol(cause, edge_value_string_without_quotes);
			f2ptr left_concept_symbol  = f2__string__as__symbol(cause, left_concept);
			f2ptr right_concept_symbol = f2__string__as__symbol(cause, right_concept);
			//printf("\nedge: "); f2__print(cause, f2list3__new(cause, edge_symbol, left_concept_symbol, right_concept_symbol));
			{
			  f2ptr left_graph_node  = raw__ptypehash__lookup(cause, node_ptypehash, left_concept_symbol);
			  if (left_graph_node == nil) {
			    left_graph_node = f2__graph_node__new(cause, left_concept_symbol);
			    raw__ptypehash__add(cause, node_ptypehash, left_concept_symbol, left_graph_node);
			  }
			  f2ptr right_graph_node = raw__ptypehash__lookup(cause, node_ptypehash, right_concept_symbol);
			  if (right_graph_node == nil) {
			    right_graph_node = f2__graph_node__new(cause, right_concept_symbol);
			    raw__ptypehash__add(cause, node_ptypehash, right_concept_symbol, right_graph_node);
			  }
			  f2__graph__add_new_edge(cause, graph, edge_symbol, left_graph_node, right_graph_node);
			}
		      }
		    }
		  }
		  edge_label_iter = f2__cons__cdr(cause, edge_label_iter);
		}
	      }
	    }
	  }
	  if (tab_iter != nil) {
	    printf("\nconceptnet-new_from_graph_file warning: tab_iter != nil."); fflush(stdout);
	  }
	  line_index ++;
	  if ((line_index % 100) == 0) {
	    printf("."); fflush(stdout);
	  }
	}
	iter = f2__cons__cdr(cause, iter);
      }
      //printf("\nconceptnet lines counted: " s64__fstr, line_index); fflush(stdout);
    }
  }
  //printf("\n"); fflush(stdout);
  return this;
}
export_cefunk2(conceptnet__new_from_graph_file, filename, max_edges_to_load, 0, "Loads a conceptnet graph file.");


// **

f2ptr f2__conceptnet__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(conceptnet__core_extension__ping, 0, "");

f2ptr f2__conceptnet__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "conceptnet"), f2__conceptnet_type__new(cause));
  status("conceptnet initialized.");
  return nil;
}
export_cefunk0(conceptnet__core_extension__initialize, 0, "");

f2ptr f2__conceptnet__core_extension__destroy(f2ptr cause) {
  status("conceptnet destroyed.");
  return nil;
}
export_cefunk0(conceptnet__core_extension__destroy, 0, "");



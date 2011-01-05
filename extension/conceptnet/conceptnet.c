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


f2ptr f2__conceptnet__new_from_graph_file(f2ptr cause, f2ptr filename) {
  f2ptr graph_file_string = f2__string__load(cause, filename);
  if (raw__larva__is_type(cause, graph_file_string)) {
    return f2larva__new(cause, 1, nil);
  }
  f2ptr graph_file_line_strings = f2__string__split(cause, graph_file_string, new__string(cause, "\n"));
  {
    s64 line_index = 0;
    f2ptr iter = graph_file_line_strings;
    while (iter != nil) {
      f2ptr graph_file_line_string = f2__cons__car(cause, iter);
      {
	if (line_index == 0) {
	  f2ptr graph_file_line_tab_strings = f2__string__split(cause, graph_file_line_string, new__string(cause, "\t"));
	  f2ptr tab_iter = graph_file_line_tab_strings;
	  {
	    f2ptr left_concept      = f2__cons__car(cause, tab_iter); tab_iter = f2__cons__cdr(cause, tab_iter);
	    f2ptr right_concept     = f2__cons__car(cause, tab_iter); tab_iter = f2__cons__cdr(cause, tab_iter);
	    f2ptr edge_label_string = f2__cons__car(cause, tab_iter); tab_iter = f2__cons__cdr(cause, tab_iter);
	    printf("\nleft_concept.....: "); f2__print(cause, left_concept);
	    printf("\nright_concept....: "); f2__print(cause, right_concept);
	    printf("\nedge_label_string: "); f2__print(cause, edge_label_string);
	    {
	      f2ptr edge_label_string_without_left_squiglies = f2__string__replace_all(cause, edge_label_string,                        new__string(cause, "{"), new__string(cause, ""));
	      f2ptr edge_label_string_without_squiglies      = f2__string__replace_all(cause, edge_label_string_without_left_squiglies, new__string(cause, "}"), new__string(cause, ""));
	      printf("\nedge_label_string_without_squiglies: "); f2__print(cause, edge_label_string_without_squiglies);
	      f2ptr edge_label_strings = f2__string__split(cause, edge_label_string_without_squiglies, new__string(cause, ", "));
	      {
		f2ptr edge_label_iter = edge_label_strings;
		while (edge_label_iter != nil) {
		  f2ptr edge_label_pair_string = f2__cons__car(cause, edge_label_iter);
		  {
		    printf("\nedge_label_pair_string: "); f2__print(cause, edge_label_pair_string);
		    f2ptr edge_label_pair = f2__string__split(cause, edge_label_pair_string, new__string(cause, ": "));
		    {
		      f2ptr edge_label_pair_iter = edge_label_pair;
		      f2ptr edge_key   = f2__cons__car(cause, edge_label_pair_iter); edge_label_pair_iter = f2__cons__cdr(cause, edge_label_pair_iter);
		      f2ptr edge_value = f2__cons__car(cause, edge_label_pair_iter); edge_label_pair_iter = f2__cons__cdr(cause, edge_label_pair_iter);
		      if (edge_label_pair_iter != nil) {
			printf("\nconceptnet-new_from_graph_file warning: edge_label_pair_iter != nil."); fflush(stdout);
		      }
		      printf("\nedge_key: ");   f2__print(cause, edge_key);
		      printf("\nedge_value: "); f2__print(cause, edge_value);
		    }
		  }
		  edge_label_iter = f2__cons__cdr(cause, edge_label_iter);
		}
	      }
	    }
	    fflush(stdout);
	  }
	  if (tab_iter != nil) {
	    printf("\nconceptnet-new_from_graph_file warning: tab_iter != nil."); fflush(stdout);
	  }
	}
	line_index ++;
      }
      iter = f2__cons__cdr(cause, iter);
    }
    printf("\nconceptnet lines counted: " s64__fstr, line_index); fflush(stdout);
  }
  f2ptr conceptnet = f2__conceptnet__new(cause);
  
  return conceptnet;
}
export_cefunk1(conceptnet__new_from_graph_file, filename, 0, "Loads a conceptnet graph file.");


// **

f2ptr f2__conceptnet__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(conceptnet__core_extension_ping, 0, "");

f2ptr f2__conceptnet__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "conceptnet"), f2__conceptnet_type__new(cause));
  status("conceptnet initialized.");
  return nil;
}
export_cefunk0(conceptnet__core_extension_initialize, 0, "");

f2ptr f2__conceptnet__core_extension_destroy(f2ptr cause) {
  status("conceptnet destroyed.");
  return nil;
}
export_cefunk0(conceptnet__core_extension_destroy, 0, "");



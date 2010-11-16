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

f2ptr f2__graphviz__digraph(f2ptr cause, f2ptr codes) {
  return f2__stringlist__rawcode(cause, f2__conslistlist__append(cause, f2list3__new(cause,
										     f2cons__new(cause, new__string(cause, "digraph G {"), nil),
										     codes,
										     f2cons__new(cause, new__string(cause, "}"), nil))));
}
def_pcfunk0_and_rest(graphviz__digraph, codes, return f2__graphviz__digraph(this_cause, codes));

f2ptr f2__graphviz__node_color(f2ptr cause, f2ptr color) {
  return f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "node [fillcolor = white, color = \""), color, new__string(cause, "\", style = filled];")));
}
def_pcfunk1(graphviz__node_color, color, return f2__graphviz__node_color(this_cause, color));

f2ptr f2__graphviz__edge_color(f2ptr cause, f2ptr color) {
  return f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "edge [color = \""), color, new__string(cause, "\"];")));
}
def_pcfunk1(graphviz__edge_color, color, return f2__graphviz__edge_color(this_cause, color));

f2ptr f2__graphviz__node(f2ptr cause, f2ptr name, f2ptr label, f2ptr color) {
  if (! color) {
    return f2__stringlist__concat(cause, f2list4__new(cause, name, new__string(cause, " [label = <"), label, new__string(cause, ">];")));
  } else {
    return f2__stringlist__concat(cause, f2list6__new(cause, name, new__string(cause, " [label = <"), label, new__string(cause, ">, color=\""), color, new__string(cause, "\"];")));
  }
}
def_pcfunk3(graphviz__node, name, label, color, return f2__graphviz__node(this_cause, name, label, color));

f2ptr f2__graphviz__box_node(f2ptr cause, f2ptr name, f2ptr label, f2ptr color) {
  if (! color) {
    return f2__stringlist__concat(cause, f2list4__new(cause, name, new__string(cause, " [shape=box,fillcolor=white,style=filled,label=<"), label, new__string(cause, ">,height=.1,width=.1];")));
  } else {
    return f2__stringlist__concat(cause, f2list6__new(cause, name, new__string(cause, " [shape=box,fillcolor=white,style=filled,label=<"), label, new__string(cause, ">,height=.1,width=.1,color=\""), color, new__string(cause, "\"];")));
  }
}
def_pcfunk3(graphviz__box_node, name, label, color, return f2__graphviz__box_node(this_cause, name, label, color));

f2ptr f2__graphviz__edge_tail_head(f2ptr cause, f2ptr tail, f2ptr head) {
  return f2__stringlist__concat(cause, f2list5__new(cause, new__string(cause, "edge [arrowtail = "), tail, new__string(cause, ", arrowhead = "), head, new__string(cause, "];")));
}
def_pcfunk2(graphviz__edge_tail_head, tail, head, return f2__graphviz__edge_tail_head(this_cause, tail, head));

f2ptr f2__graphviz__edge(f2ptr cause, f2ptr from_node, f2ptr to_node, f2ptr color) {
  if (! color) {
    return f2__stringlist__concat(cause, f2list4__new(cause, from_node, new__string(cause, " -> "), to_node, new__string(cause, ";")));
  } else {
    return f2__stringlist__concat(cause, f2list6__new(cause, from_node, new__string(cause, " -> "), to_node, new__string(cause, " [color=\""), color, new__string(cause, "\"];")));
  }
}
def_pcfunk3(graphviz__edge, from_node, to_node, color, return f2__graphviz__edge(this_cause, from_node, to_node, color));

f2ptr f2__graphviz__exp__as__label(f2ptr cause, f2ptr exp) {
  f2ptr string = nil;
  if (exp == nil) {
    string = new__string(cause, "[]");
  } else if (raw__string__is_type(cause, exp)) {
    string = exp;
  } else if (raw__symbol__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__integer__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__double__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__char__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__cons__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__frame__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__list__is_type(cause, exp)) {
    string = f2__exp__as__string(cause, exp);
  } else if (raw__simple_graph_variable__is_type(cause, exp)) {
    return f2__stringlist__concat(cause, f2list3__new(cause,
						      new__string(cause, "<font color=\"#CF0000\">?"),
						      f2__graphviz__exp__as__label(cause, f2__simple_graph_variable__name(cause, exp)),
						      new__string(cause, "</font>")));
  } else if (raw__array__is_type(cause, exp) && (! raw__primobject__is_type(cause, exp))) {
    string = f2__exp__as__string(cause, exp);
  } else {
    f2ptr type = f2__object__type(cause, exp);
    string = f2__stringlist__concat(cause, f2list3__new(cause,
							f2__exp__as__string(cause, type),
							new__string(cause, "_"),
							f2__exp__as__string(cause, f2__pointer(cause, exp))));
  }
  char* replacement_pairs[][2] = {{"&",  "&amp;"},
				  {"\"", "&quot;"},
				  {"'",  "&apos;"},
				  {"<",  "&lt;"},
				  {">",  "&gt;"},
				  {NULL, NULL}};
  {
    int index;
    for (index = 0; replacement_pairs[index][0] != NULL; index ++) {
      f2ptr token = new__string(cause, replacement_pairs[index][0]);
      if (raw__string__contains(cause, string, token)) {
	string = f2__string__replace_all(cause, string, token, new__string(cause, replacement_pairs[index][1]));
      }
    }
  }
  return string;
}
def_pcfunk1(graphviz__exp__as__label, exp, return f2__graphviz__exp__as__label(this_cause, exp));

f2ptr f2__graphviz__exp__as__name(f2ptr cause, f2ptr exp) {
  return f2__stringlist__concat(cause, f2list2__new(cause,
						    new__string(cause, "ptr_"),
						    f2__exp__as__string(cause, f2__object__eq_hash_value(cause, exp))));
  /*
    if (exp == nil) {
    return new__string(cause, "nil");
    }
  f2ptr string;
  if (raw__string__is_type(cause, exp)) {
    if (f2string__length(exp, cause) == 0) {
      return new__string(cause, "empty_string");
    }
    string = exp;
  } else {
    string = f2__exp__as__string(cause, exp);
  }
  char* replacement_pairs[][2] = {{" ",  "_SPACE_"},
				  {"-",  "_DASH_"},
				  {"#",  "_HASH_"},
				  {"[",  "_BSQPAREN_"},
				  {"]",  "_ESQPAREN_"},
				  {"(",  "_BPAREN_"},
				  {")",  "_EPAREN_"},
				  {"<",  "_LTHAN_"},
				  {">",  "_GTHAN_"},
				  {"'",  "_SQUOTE_"},
				  {"\"", "_DQUOTE_"},
				  {"=",  "_EQUALS_"},
				  {"/",  "_SLASH_"},
				  {"\\", "_BSLASH_"},
				  {":",  "_COLON_"},
				  {NULL, NULL}};
  {
    int index;
    for (index = 0; replacement_pairs[index][0] != NULL; index ++) {
      f2ptr token = new__string(cause, replacement_pairs[index][0]);
      if (raw__string__contains(cause, string, token)) {
	string = f2__string__replace_all(cause, string, token, new__string(cause, replacement_pairs[index][1]));
      }
    }
  }
  return string;
  */
}
def_pcfunk1(graphviz__exp__as__name, exp, return f2__graphviz__exp__as__name(this_cause, exp));

f2ptr f2__graphviz__edge_name(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2__stringlist__concat(cause, f2list6__new(cause, new__string(cause, "LABEL__"), f2__graphviz__exp__as__name(cause, label), new__string(cause, "__LEFT_NODE__"), f2__graphviz__exp__as__name(cause, left_node), new__string(cause, "__RIGHT_NODE__"), f2__graphviz__exp__as__name(cause, right_node)));
}
def_pcfunk3(graphviz__edge_name, label, left_node, right_node, return f2__graphviz__edge_name(this_cause, label, left_node, right_node));

f2ptr f2__graphviz__raw_labelled_edge(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge__name = f2__graphviz__edge_name(cause, label, left_node, right_node);
  f2ptr color      = nil;
  if (raw__simple_graph_variable__is_type(cause, label)) {
    color = new__string(cause, "#CF0000");
  }
  return f2__stringlist__rawcode(cause, f2list5__new(cause,
						     f2__graphviz__box_node(      cause, edge__name, f2__graphviz__exp__as__label(cause, label), color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "crow"), new__string(cause, "none")),
						     f2__graphviz__edge(          cause, left_node, edge__name, color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "none"), new__string(cause, "normal")),
						     f2__graphviz__edge(          cause, edge__name, right_node, color)));
}
def_pcfunk3(graphviz__raw_labelled_edge, label, left_node, right_node, return f2__graphviz__raw_labelled_edge(this_cause, label, left_node, right_node));

f2ptr f2__graphviz__labelled_edge(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge__name = f2__graphviz__edge_name(cause, label, left_node, right_node);
  f2ptr color      = nil;
  if (raw__simple_graph_variable__is_type(cause, label)) {
    color = new__string(cause, "#CF0000");
  }
  return f2__stringlist__rawcode(cause, f2list5__new(cause,
						     f2__graphviz__box_node(      cause, edge__name, f2__graphviz__exp__as__label(cause, label), color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "crow"), new__string(cause, "none")),
						     f2__graphviz__edge(          cause, f2__graphviz__exp__as__name(cause, left_node), edge__name, color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "none"), new__string(cause, "normal")),
						     f2__graphviz__edge(          cause, edge__name, f2__graphviz__exp__as__name(cause, right_node), color)));
}
def_pcfunk3(graphviz__labelled_edge, label, left_node, right_node, return f2__graphviz__labelled_edge(this_cause, label, left_node, right_node));

// **

void f2__graphviz__reinitialize_globalvars() {
}

void f2__graphviz__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "graphviz", "", &f2__graphviz__reinitialize_globalvars);
  
  f2__graphviz__reinitialize_globalvars();
  
  f2__primcfunk__init__1(graphviz__digraph,           codes,                        "compiles code for graphviz.");
  f2__primcfunk__init__1(graphviz__node_color,        color,                        "compiles code for graphviz.");
  f2__primcfunk__init__1(graphviz__edge_color,        color,                        "compiles code for graphviz.");
  f2__primcfunk__init__3(graphviz__node,              name, label, color,           "compiles code for graphviz.");
  f2__primcfunk__init__3(graphviz__box_node,          name, label, color,           "compiles code for graphviz.");
  f2__primcfunk__init__2(graphviz__edge_tail_head,    tail, head,                   "compiles code for graphviz.");
  f2__primcfunk__init__3(graphviz__edge,              from_node, to_node, color,    "compiles code for graphviz.");
  f2__primcfunk__init__1(graphviz__exp__as__label,    exp,                          "compiles code for graphviz.");
  f2__primcfunk__init__1(graphviz__exp__as__name,     exp,                          "compiles code for graphviz.");
  f2__primcfunk__init__3(graphviz__edge_name,         label, left_node, right_node, "compiles code for graphviz.");
  f2__primcfunk__init__3(graphviz__raw_labelled_edge, label, left_node, right_node, "compiles code for graphviz.");
  f2__primcfunk__init__3(graphviz__labelled_edge,     label, left_node, right_node, "compiles code for graphviz.");
  
  
}


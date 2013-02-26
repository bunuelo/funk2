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

f2ptr f2__graphviz__digraph(f2ptr cause, f2ptr codes) {
  return f2__stringlist__rawcode(cause, f2__conslistlist__append(cause, f2list3__new(cause,
										     raw__cons__new(cause, new__string(cause, "digraph G {"), nil),
										     codes,
										     raw__cons__new(cause, new__string(cause, "}"), nil))));
}
def_pcfunk0_and_rest(graphviz__digraph, codes,
		     "",
		     return f2__graphviz__digraph(this_cause, codes));

f2ptr f2__graphviz__node_color(f2ptr cause, f2ptr color) {
  return f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "node [fillcolor = white, color = \""), color, new__string(cause, "\", style = filled];")));
}
def_pcfunk1(graphviz__node_color, color,
	    "",
	    return f2__graphviz__node_color(this_cause, color));

f2ptr f2__graphviz__edge_color(f2ptr cause, f2ptr color) {
  return f2__stringlist__concat(cause, f2list3__new(cause, new__string(cause, "edge [color = \""), color, new__string(cause, "\"];")));
}
def_pcfunk1(graphviz__edge_color, color,
	    "",
	    return f2__graphviz__edge_color(this_cause, color));

f2ptr f2__graphviz__node(f2ptr cause, f2ptr name, f2ptr label, f2ptr color) {
  if (! color) {
    return f2__stringlist__concat(cause, f2list4__new(cause, name, new__string(cause, " [label = <"), label, new__string(cause, ">];")));
  } else {
    return f2__stringlist__concat(cause, f2list6__new(cause, name, new__string(cause, " [label = <"), label, new__string(cause, ">, color=\""), color, new__string(cause, "\"];")));
  }
}
def_pcfunk3(graphviz__node, name, label, color,
	    "",
	    return f2__graphviz__node(this_cause, name, label, color));

f2ptr f2__graphviz__box_node(f2ptr cause, f2ptr name, f2ptr label, f2ptr color) {
  if (! color) {
    return f2__stringlist__concat(cause, f2list4__new(cause, name, new__string(cause, " [shape=box,fillcolor=white,style=filled,label=<"), label, new__string(cause, ">,height=.1,width=.1];")));
  } else {
    return f2__stringlist__concat(cause, f2list6__new(cause, name, new__string(cause, " [shape=box,fillcolor=white,style=filled,label=<"), label, new__string(cause, ">,height=.1,width=.1,color=\""), color, new__string(cause, "\"];")));
  }
}
def_pcfunk3(graphviz__box_node, name, label, color,
	    "",
	    return f2__graphviz__box_node(this_cause, name, label, color));

f2ptr f2__graphviz__edge_tail_head(f2ptr cause, f2ptr tail, f2ptr head) {
  return f2__stringlist__concat(cause, f2list5__new(cause, new__string(cause, "edge [arrowtail = "), tail, new__string(cause, ", arrowhead = "), head, new__string(cause, "];")));
}
def_pcfunk2(graphviz__edge_tail_head, tail, head,
	    "",
	    return f2__graphviz__edge_tail_head(this_cause, tail, head));

f2ptr f2__graphviz__edge(f2ptr cause, f2ptr from_node, f2ptr to_node, f2ptr color) {
  if (! color) {
    return f2__stringlist__concat(cause, f2list4__new(cause, from_node, new__string(cause, " -> "), to_node, new__string(cause, ";")));
  } else {
    return f2__stringlist__concat(cause, f2list6__new(cause, from_node, new__string(cause, " -> "), to_node, new__string(cause, " [color=\""), color, new__string(cause, "\"];")));
  }
}
def_pcfunk3(graphviz__edge, from_node, to_node, color,
	    "",
	    return f2__graphviz__edge(this_cause, from_node, to_node, color));

f2ptr f2__graphviz__exp__as__color(f2ptr cause, f2ptr exp) {
  f2ptr as_graphviz_color_funk = f2__object__slot__type_funk(cause, exp, new__symbol(cause, "get"), new__symbol(cause, "as-graphviz_color"));
  if (raw__funkable__is_type(cause, as_graphviz_color_funk)) {
    return f2__force_funk_apply(cause, f2__this__fiber(cause), as_graphviz_color_funk, f2list1__new(cause, exp));
  }
  return nil;
}

f2ptr f2__graphviz__exp__as__label(f2ptr cause, f2ptr exp) {
  f2ptr string = nil;
  {
    f2ptr as_graphviz_label_funk = f2__object__slot__type_funk(cause, exp, new__symbol(cause, "get"), new__symbol(cause, "as-graphviz_label"));
    if (raw__funkable__is_type(cause, as_graphviz_label_funk)) {
      string = f2__force_funk_apply(cause, f2__this__fiber(cause), as_graphviz_label_funk, f2list1__new(cause, exp));
    }
  }
  if (string == nil) {
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
    } else if (raw__array__is_type(cause, exp) && (! raw__primobject__is_type(cause, exp))) {
      string = f2__exp__as__string(cause, exp);
    } else {
      f2ptr type = f2__object__type(cause, exp);
      string = f2__stringlist__concat(cause, f2list3__new(cause,
							  f2__exp__as__string(cause, type),
							  new__string(cause, "_"),
							  f2__exp__as__string(cause, f2__pointer(cause, exp))));
    }
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
  {
    f2ptr color = f2__graphviz__exp__as__color(cause, exp);
    if (raw__larva__is_type(cause, color)) {
      return color;
    }
    if (color != nil) {
      string = f2__stringlist__concat(cause, f2list5__new(cause,
							  new__string(cause, "<font color=\""),
							  color,
							  new__string(cause, "\">"),
							  string,
							  new__string(cause, "</font>")));
    }
  }
  return string;
}
def_pcfunk1(graphviz__exp__as__label, exp,
	    "",
	    return f2__graphviz__exp__as__label(this_cause, exp));

f2ptr f2__graphviz__exp__as__name(f2ptr cause, f2ptr exp) {
  f2ptr string = nil;
  {
    f2ptr as_graphviz_name_funk = f2__object__slot__type_funk(cause, exp, new__symbol(cause, "get"), new__symbol(cause, "as-graphviz_name"));
    if (raw__funkable__is_type(cause, as_graphviz_name_funk)) {
      string = f2__force_funk_apply(cause, f2__this__fiber(cause), as_graphviz_name_funk, f2list1__new(cause, exp));
      if (raw__larva__is_type(cause, string)) {
	return string;
      }
      if (! raw__string__is_type(cause, string)) {
	return f2larva__new(cause, 24521, nil);
      }
    }
  }
  if (string == nil) {
    if (raw__integer__is_type(cause, exp)) {
      u64  exp__i = f2integer__i(exp, cause);
      char name_str[128];
      snprintf(name_str, 127, "integer_" u64__fstr, (u64)exp__i);
      string = new__string(cause, name_str);
    } else if (raw__float__is_type(cause, exp)) {
      union {
	float f;
	u64   uid;
      } u;
      u.uid = 0;
      u.f   = f2float__f(exp, cause);
      char name_str[128];
      snprintf(name_str, 127, "float_" u64__fstr, (u64)u.uid);
      string = new__string(cause, name_str);
    } else if (raw__double__is_type(cause, exp)) {
      union {
	double d;
	u64    uid;
      } u;
      u.uid = 0;
      u.d   = f2double__d(exp, cause);
      char name_str[128];
      snprintf(name_str, 127, "double_" u64__fstr, (u64)u.uid);
      string = new__string(cause, name_str);
    } else {
      char name_str[128];
      snprintf(name_str, 127, "ptr_" u64__fstr, (u64)exp);
      string = new__string(cause, name_str);
    }
  }
  return string;
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
def_pcfunk1(graphviz__exp__as__name, exp,
	    "",
	    return f2__graphviz__exp__as__name(this_cause, exp));

f2ptr f2__graphviz__edge_name(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  return f2__stringlist__concat(cause, f2list6__new(cause, new__string(cause, "LABEL__"), f2__graphviz__exp__as__name(cause, label), new__string(cause, "__LEFT_NODE__"), f2__graphviz__exp__as__name(cause, left_node), new__string(cause, "__RIGHT_NODE__"), f2__graphviz__exp__as__name(cause, right_node)));
}
def_pcfunk3(graphviz__edge_name, label, left_node, right_node,
	    "",
	    return f2__graphviz__edge_name(this_cause, label, left_node, right_node));

f2ptr f2__graphviz__raw_labelled_edge(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node, f2ptr color) {
  f2ptr edge__name = f2__graphviz__edge_name(cause, label, left_node, right_node);
  return f2__stringlist__rawcode(cause, f2list5__new(cause,
						     f2__graphviz__box_node(      cause, edge__name, f2__graphviz__exp__as__label(cause, label), color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "crow"), new__string(cause, "none")),
						     f2__graphviz__edge(          cause, left_node, edge__name, color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "none"), new__string(cause, "normal")),
						     f2__graphviz__edge(          cause, edge__name, right_node, color)));
}
def_pcfunk4(graphviz__raw_labelled_edge, label, left_node, right_node, color,
	    "",
	    return f2__graphviz__raw_labelled_edge(this_cause, label, left_node, right_node, color));

f2ptr f2__graphviz__labelled_edge(f2ptr cause, f2ptr label, f2ptr left_node, f2ptr right_node) {
  f2ptr edge__name = f2__graphviz__edge_name(cause, label, left_node, right_node);
  f2ptr color      = nil;
  color = f2__graphviz__exp__as__color(cause, label);
  if (raw__larva__is_type(cause, color)) {
    return color;
  }
  return f2__stringlist__rawcode(cause, f2list5__new(cause,
						     f2__graphviz__box_node(      cause, edge__name, f2__graphviz__exp__as__label(cause, label), color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "crow"), new__string(cause, "none")),
						     f2__graphviz__edge(          cause, f2__graphviz__exp__as__name(cause, left_node), edge__name, color),
						     f2__graphviz__edge_tail_head(cause, new__string(cause, "none"), new__string(cause, "normal")),
						     f2__graphviz__edge(          cause, edge__name, f2__graphviz__exp__as__name(cause, right_node), color)));
}
def_pcfunk3(graphviz__labelled_edge, label, left_node, right_node,
	    "",
	    return f2__graphviz__labelled_edge(this_cause, label, left_node, right_node));

// **

void f2__graphviz__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(graphviz__digraph);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__node_color);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__edge_color);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__node);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__box_node);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__edge_tail_head);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__edge);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__exp__as__label);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__exp__as__name);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__edge_name);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__raw_labelled_edge);
  f2__primcfunk__init__defragment__fix_pointers(graphviz__labelled_edge);
}

void f2__graphviz__reinitialize_globalvars() {
  f2__primcfunk__init__1(graphviz__digraph,           codes);
  f2__primcfunk__init__1(graphviz__node_color,        color);
  f2__primcfunk__init__1(graphviz__edge_color,        color);
  f2__primcfunk__init__3(graphviz__node,              name, label, color);
  f2__primcfunk__init__3(graphviz__box_node,          name, label, color);
  f2__primcfunk__init__2(graphviz__edge_tail_head,    tail, head);
  f2__primcfunk__init__3(graphviz__edge,              from_node, to_node, color);
  f2__primcfunk__init__1(graphviz__exp__as__label,    exp);
  f2__primcfunk__init__1(graphviz__exp__as__name,     exp);
  f2__primcfunk__init__3(graphviz__edge_name,         label, left_node, right_node);
  f2__primcfunk__init__4(graphviz__raw_labelled_edge, label, left_node, right_node, color);
  f2__primcfunk__init__3(graphviz__labelled_edge,     label, left_node, right_node);
}

void f2__graphviz__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "graphviz", "", &f2__graphviz__reinitialize_globalvars, &f2__graphviz__defragment__fix_pointers);
  
  f2__graphviz__reinitialize_globalvars();
}


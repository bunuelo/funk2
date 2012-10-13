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

#include "pattern_match.h"

/*
[defunk pattern-match_with_frame [pattern expression frame]
  `[terminal_format standard-terminal
		    '\n'
		    '\npattern    = ' pattern
		    '\nexpression = ' expression]
  [if [and [null pattern]
	   [null expression]]
      [cons frame nil]
    [if [or [null pattern]
	    [null expression]]
	nil
      [let [[pattern-car [car pattern]]]
	[if [eq pattern-car [car expression]]
	    [pattern-match_with_frame [cdr pattern] [cdr expression] frame]
	  [if [is-type `cons pattern-car]
	      [let [[command [car pattern-car]]]
		[cond [[eq command `?] [let [[variable_name  [elt pattern-car 1]]
					     [variable_value nil]]
					 [let [[expression_length [length expression]]
					       [done              nil]
					       [parses            nil]]
					   [dotimes [index expression_length]
					     [let [[subframe     [get frame new_copy]]
						   [match_length [+ index 1]]]
					       [have subframe add variable_name [firstn match_length expression]]
					       [let [[subparses [pattern-match_with_frame [cdr pattern] [restn match_length expression] subframe]]]
						 [= parses [append parses
								   subparses]]]]]
					   parses]]]
		      [t               [error bug_name `pattern-invalid_command]]]]
	    nil]]]]]]
*/



f2ptr raw__conslist_pattern__match_with_frame(f2ptr cause, f2ptr pattern, f2ptr expression, f2ptr frame) {
  if ((pattern    == nil) &&
      (expression == nil)) {
    return raw__cons__new(cause, frame, nil);
  } else if ((pattern    == nil) ||
	     (expression == nil)) {
    return nil;
  } else {
    f2ptr pattern__car    = f2cons__car(pattern, cause);
    f2ptr expression__car = f2cons__car(expression, cause);
    if (raw__eq(cause, pattern__car, expression__car)) {
      f2ptr pattern__cdr    = f2cons__cdr(pattern, cause);
      f2ptr expression__cdr = f2cons__cdr(expression, cause);
      return raw__conslist_pattern__match_with_frame(cause, pattern__cdr, expression__cdr, frame);
    } else if (raw__cons__is_type(cause, pattern__car)) {
      f2ptr pattern__car__car = f2cons__car(pattern__car, cause);
      f2ptr command           = pattern__car__car;
      if (raw__eq(cause, command, new__symbol(cause, "?"))) {
	f2ptr pattern__car__cdr      = f2cons__cdr(pattern__car, cause);
	if (pattern__car__cdr == nil) {
	  return new__error(f2list8__new(cause,
					 new__symbol(cause, "conslist_pattern-match_with_frame"), new__symbol(cause, "?_command_must_specify_variable_name"),
					 new__symbol(cause, "pattern"),                           pattern,
					 new__symbol(cause, "expression"),                        expression,
					 new__symbol(cause, "frame"),                             frame));
	} else {
	  f2ptr pattern__car__cdr__car = f2cons__car(pattern__car__cdr, cause);
	  s64   expression__length     = 0;
	  {
	    f2ptr iter = expression;
	    while (iter != nil) {
	      expression__length ++;
	      iter = f2cons__cdr(iter, cause);
	    }
	  }
	  f2ptr variable_name = pattern__car__cdr__car;
	  f2ptr subparses_seq = nil;
	  {
	    s64 index;
	    for (index = 0; index < expression__length; index ++) {
	      f2ptr subframe     = f2__frame__new_copy(cause, frame);
	      s64   match_length = index + 1;
	      raw__frame__add_var_value(cause, subframe, variable_name, raw__firstn(cause, expression, match_length));
	      f2ptr pattern__cdr = f2cons__cdr(pattern, cause);
	      f2ptr subparses    = raw__conslist_pattern__match_with_frame(cause, pattern__cdr, raw__restn(cause, expression, match_length), subframe);
	      subparses_seq = raw__cons__new(cause, subparses, subparses_seq);
	    }
	  }
	  f2ptr parses = f2__conslistlist__append(cause, subparses_seq);
	  return parses;
	}
      } else {
	return new__error(f2list10__new(cause,
					new__symbol(cause, "conslist_pattern-match_with_frame"), new__symbol(cause, "invalid_command"),
					new__symbol(cause, "command"),                           command,
					new__symbol(cause, "pattern"),                           pattern,
					new__symbol(cause, "expression"),                        expression,
					new__symbol(cause, "frame"),                             frame));
      }
    } else {
      return nil;
    }
  }
}

f2ptr f2__conslist_pattern__match_with_frame(f2ptr cause, f2ptr pattern, f2ptr expression, f2ptr frame) {
  assert_argument_type(conslist, pattern);
  assert_argument_type(conslist, expression);
  assert_argument_type(frame,    frame);
  return raw__conslist_pattern__match_with_frame(cause, pattern, expression, frame);
}
export_cefunk3(conslist_pattern__match_with_frame, pattern, expression, frame, 0, "");


f2ptr raw__conslist_pattern__match(f2ptr cause, f2ptr pattern, f2ptr expression) {
  f2ptr frame = assert_value(f2__frame__new(cause, nil));
  return raw__conslist_pattern__match_with_frame(cause, pattern, expression, frame);
}

f2ptr f2__conslist_pattern__match(f2ptr cause, f2ptr pattern, f2ptr expression) {
  assert_argument_type(conslist, pattern);
  assert_argument_type(conslist, expression);
  return raw__conslist_pattern__match(cause, pattern, expression);
}
export_cefunk2(conslist_pattern__match, pattern, expression, 0, "");

/*
[defunk string_pattern-as_conslist_pattern [string_pattern]
  [let [[string_pattern-length [get string_pattern length]]
	[index                 0]
	[begin_variable_char   #\[]
        [conslist_pattern      nil]
	[conslist_pattern_iter nil]]
    [while [< index string_pattern-length]
      [let [[next_char [get string_pattern elt index]]]
	[cond [[eq next_char begin_variable_char] [let [[stream [string_stream-new string_pattern index]]]
						    [let [[variable_expression [stream-try_read stream]]]
						      [let [[variable_command [first variable_expression]]]
							[cond [[eq variable_command `?] [let [[variable_name [second variable_expression]]]
											  [let [[new_cons [cons `[? ,variable_name] nil]]]
											    [if [null conslist_pattern]
												[prog [= conslist_pattern      new_cons]
												      [= conslist_pattern_iter new_cons]]
											      [prog [set conslist_pattern_iter cdr new_cons]
												    [= conslist_pattern_iter new_cons]]]]
											  [= index [get stream index]]]]
							      [t                        [error bug_name            `string_pattern-parse-invalid_variable_command
											       string_pattern      string_pattern
											       variable_expression variable_expression]]]]]]]
	      [t                                  [let [[new_cons [cons next_char nil]]]
						    [if [null conslist_pattern]
							[prog [= conslist_pattern      new_cons]
							      [= conslist_pattern_iter new_cons]]
						      [prog [set conslist_pattern_iter cdr new_cons]
							    [= conslist_pattern_iter new_cons]]]
						    [++ index]]]]]]
    conslist_pattern]]
*/

f2ptr raw__string_pattern__as__conslist_pattern(f2ptr cause, f2ptr this) {
  return nil;
}

f2ptr f2__string_pattern__as__conslist_pattern(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__string_pattern__as__conslist_pattern(cause, this);
}
export_cefunk1(string_pattern__as__conslist_pattern, this, 0, "");


/*
[defunk string_pattern-match [string_pattern string]
  [let [[matches [conslist_pattern-match [string_pattern-as_conslist_pattern string_pattern] [string_pattern-as_conslist_pattern string]]]]
    [mapc [funk [match]
		[mapc [funk [key]
			    [let* [[conslist        [have match lookup key]]
				   [conslist-length [length conslist]]
				   [string          [new string conslist-length #\ ]]
				   [index           0]]
			      [mapc [funk [char]
					  [set string elt index char]
					  [++ index]]
				    [have match lookup key]]
			      [have match add key string]]]
		      [get match keys]]]
	  matches]
    matches]]
*/

f2ptr raw__string_pattern__match(f2ptr cause, f2ptr this, f2ptr string) {
  return nil;
}

f2ptr f2__string_pattern__match(f2ptr cause, f2ptr this, f2ptr string) {
  assert_argument_type(string, this);
  assert_argument_type(string, string);
  return raw__string_pattern__match(cause, this, string);
}
export_cefunk2(string_pattern__match, this, string, 0, "");


// **

f2ptr f2__pattern_match__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(pattern_match__core_extension__ping, 0, "");

f2ptr f2__pattern_match__core_extension__initialize(f2ptr cause) {
  status("pattern_match initialized.");
  return nil;
}
export_cefunk0(pattern_match__core_extension__initialize, 0, "");

f2ptr f2__pattern_match__core_extension__define_types(f2ptr cause) {
  status("pattern_match types defined.");
  return nil;
}
export_cefunk0(pattern_match__core_extension__define_types, 0, "");

f2ptr f2__pattern_match__core_extension__destroy(f2ptr cause) {
  status("pattern_match destroyed.");
  return nil;
}
export_cefunk0(pattern_match__core_extension__destroy, 0, "");



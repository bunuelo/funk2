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

#include "funk2.h"


/*
 *  [defmetro let [varpairs :rest body]
 *    [define let-vars [mapcar [funk [varpair] [car varpair]] varpairs]]
 *    `[apply [funk-new_with_name let ,let-vars
 *	                          @body]
 *	      [immutable_conslist @[mapcar [funk [varpair] [car [cdr varpair]]] varpairs]]]]
 *
 */

/*
 *  [defmetro let [varpairs :rest body]
 *    [define let-vars [mapcar [funk [varpair] [car varpair]] varpairs]]
 *    [conslist `apply [conslist-append_last_at_end `funk-new_with_name `let let-vars
 *	                                            body]
 *	        [conslist-append_last_at_end `immutable_conslist
 *                                           [mapcar [funk [varpair]
 *                                                         [car [cdr varpair]]]
 *                                                   varpairs]]]]
 */

/*
 *  [defmetro let [variable_definitions :rest body_expressions]
 *    [define variables [mapcar [funk [varpair] [car varpair]] variable_definitions]]
 *    [conslist `apply [conslist-append_last_at_end `funk-new_with_name `let variables
 *	                                            body_expressions]
 *	        [conslist-append_last_at_end `immutable_conslist
 *                                           [mapcar [funk [varpair]
 *                                                         [car [cdr varpair]]]
 *                                                   variable_definitions]]]]
 */

f2ptr raw__primmetro__let(f2ptr cause, f2ptr variable_definitions, f2ptr body_expressions) {
  f2ptr variables   = nil;
  f2ptr definitions = nil;
  {
    f2ptr iter             = variable_definitions;
    f2ptr variables_iter   = nil;
    f2ptr definitions_iter = nil;
    while (iter != nil) {
      f2ptr variable_definition  = f2cons__car(iter, cause);
      f2ptr variable             = f2cons__car(variable_definition, cause);
      f2ptr definition           = f2cons__car(f2cons__cdr(variable_definition, cause), cause);
      f2ptr new_variables_cons   = f2cons__new(cause, variable, nil);
      f2ptr new_definitions_cons = f2cons__new(cause, definition, nil);
      if (variables == nil) {
	variables        = new_variables_cons;
        variables_iter   = new_variables_cons;
	definitions      = new_definitions_cons;
        definitions_iter = new_definitions_cons;
      } else {
	f2cons__cdr__set(variables_iter,   cause, new_variables_cons);
	variables_iter   =                        new_variables_cons;
	f2cons__cdr__set(definitions_iter, cause, new_definitions_cons);
	definitions_iter =                        new_definitions_cons;
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return f2list3__new(cause,
		      new__symbol(cause, "funk-apply"),
		      f2cons__new(cause,
				  new__symbol(cause, "funk-new_with_name"),
				  f2cons__new(cause,
					      new__symbol(cause, "let"),
					      f2cons__new(cause,
							  variables,
							  body_expressions))),
		      
		      f2cons__new(cause,
				  new__symbol(cause, "immutable_conslist"),
				  definitions));
}

f2ptr f2__primmetro__let(f2ptr cause, f2ptr variable_definitions, f2ptr body_expressions) {
  assert_argument_type(conslist, variable_definitions);
  assert_argument_type(conslist, body_expressions);
  {
    f2ptr iter = variable_definitions;
    while (iter != nil) {
      f2ptr variable_definition = f2cons__car(iter, cause);
      assert_argument_type(conslist, variable_definition);
      s64 variable_definition__length = 0;
      {
	f2ptr iter = variable_definition;
	while (iter != nil) {
	  variable_definition__length ++;
	  iter = f2cons__cdr(iter, cause);
	}
      }
      if (variable_definition__length != 2) {
	return new__error(f2list8__new(cause,
				       new__symbol(cause, "bug_name"),             new__symbol(cause, "let-found_invalid_variable_definition"),
				       new__symbol(cause, "variable_definition"),  variable_definition,
				       new__symbol(cause, "variable_definitions"), variable_definitions,
				       new__symbol(cause, "body_expressions"),     body_expressions));
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return raw__primmetro__let(cause, variable_definitions, body_expressions);
}
def_pcfunk1_and_rest(primmetro__let, variable_definitions, body_expressions,
		     "",
		     return f2__primmetro__let(this_cause, variable_definitions, body_expressions));


/*  
 *  [defmetro prog [:rest body]
 *    [if body
 *        [conslist `funk-apply
 *                  [cons `funk-new_with_name [cons `prog [cons nil body]]]
 *  		    nil]
 *      nil]]
 */

f2ptr raw__primmetro__prog(f2ptr cause, f2ptr body_expressions) {
  if (body_expressions == nil) {
    return nil;
  }
  return f2list3__new(cause,
		      new__symbol(cause, "funk-apply"),
		      f2cons__new(cause,
				  new__symbol(cause, "funk-new_with_name"),
				  f2cons__new(cause,
					      new__symbol(cause, "prog"),
					      f2cons__new(cause,
							  nil,
							  body_expressions))),
		      nil);
}

f2ptr f2__primmetro__prog(f2ptr cause, f2ptr body_expressions) {
  assert_argument_type(conslist, body_expressions);
  return raw__primmetro__prog(cause, body_expressions);
}
def_pcfunk0_and_rest(primmetro__prog, body_expressions,
		     "",
		     return f2__primmetro__prog(this_cause, body_expressions));



f2ptr raw__primmetro__apply(f2ptr cause, f2ptr funkable, f2ptr arguments) {
  return f2list3__new(cause,
		      new__symbol(cause, "funk-apply"),
		      funkable,
		      arguments);
}

f2ptr f2__primmetro__apply(f2ptr cause, f2ptr funkable, f2ptr arguments) {
  return raw__primmetro__apply(cause, funkable, arguments);
}
def_pcfunk2(primmetro__apply, funkable, arguments,
	    "",
	    return f2__primmetro__apply(this_cause, funkable, arguments));


/*
 * [defmetro funk [args :rest body]
 *   `[funk-new_with_name funk ,args
 *	  	          @body]]
 */

f2ptr raw__primmetro__funk(f2ptr cause, f2ptr variables, f2ptr body_expressions) {
  return f2cons__new(cause,
		     new__symbol(cause, "funk-new_with_name"),
		     f2cons__new(cause,
				 new__symbol(cause, "funk"),
				 f2cons__new(cause,
					     variables,
					     body_expressions)));
}

f2ptr f2__primmetro__funk(f2ptr cause, f2ptr variables, f2ptr body_expressions) {
  assert_argument_type(conslist, variables);
  assert_argument_type(conslist, body_expressions);
  return raw__primmetro__funk(cause, variables, body_expressions);
}
def_pcfunk1_and_rest(primmetro__funk, variables, body_expressions,
		     "",
		     return f2__primmetro__funk(this_cause, variables, body_expressions));



/*
[globalize-funk funk-new_with_name_and_environment-original [metro-new [bytecode copy env value nil] `funk-new_with_name_and_environment `[name environment args :rest body]
								       `[[define body_expressions__demetropolize_full [exps-demetropolize_full body]]
									 [define compiled_funk  [funk-new [bytecode copy env value nil] name args
													  body_expressions__demetropolize_full
													  body
													  nil
													  nil
													  nil]]
									 [define compiled_bcs   [primfunk:array__elt compiled_funk  4]]
									 [define is_funktional  [primfunk:array__elt compiled_funk 10]]
       							                 [conslist `funk-new
									           environment
									           [conslist `quote name]
                                                                                   [conslist `quote args]
									           [conslist `quote body_expressions__demetropolize_full]
										   [conslist `quote body]
										   [conslist `quote compiled_bcs]
										   is_funktional
										   nil]]]
								       nil
								       nil
								       nil
								       nil]]
*/

f2ptr raw__primmetro__funk__new_with_name_and_environment(f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions) {
  f2ptr fiber                                = f2__this__fiber(cause);
  f2ptr fiber__environment                   = f2__fiber__env(cause, fiber);
  f2ptr body_expressions__demetropolize_full = f2__exps__demetropolize_full(cause, fiber, env, body_expressions);
  f2ptr compiled_funk                        = f2__funk__new(cause, fiber, fiber__environment, name, variables, body_expressions__demetropolize_full, body_expressions, nil, nil, nil);
  f2ptr compiled_bytecodes                   = f2__funk__body_bytecodes(cause, compiled_funk);
  f2ptr is_funktional                        = f2__funk__is_funktional(cause, compiled_funk);
  return f2list9__new(cause,
		      new__symbol(cause, "funk-new"),
		      environment,
		      f2list2__new(cause,
				   new__symbol(cause, "quote"),
				   name),
		      f2list2__new(cause,
				   new__symbol(cause, "quote"),
				   variables),
		      f2list2__new(cause,
				   new__symbol(cause, "quote"),
				   body_expressions__demetropolize_full),
		      f2list2__new(cause,
				   new__symbol(cause, "quote"),
				   body_expressions),
		      f2list2__new(cause,
				   new__symbol(cause, "quote"),
				   compiled_bytecodes),
		      is_funktional,
		      nil);
}

f2ptr f2__primmetro__funk__new_with_name_and_environment(f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions) {
  assert_argument_type(environment, environment);
  assert_argument_type(conslist,    variables);
  assert_argument_type(conslist,    body_expressions);
  return raw__primmetro__funk(cause, name, environment, variables, body_expressions);
}
def_pcfunk4_and_rest(primmetro__funk__new_with_name_and_environment, name, environment, variables, body_expressions
		     "",
		     return f2__primmetro__funk__new_with_name_and_environment(this_cause, name, environment, variables, body_expressions));



// **

void f2__primmetros__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --

  f2__primcfunk__init__defragment__fix_pointers(primmetro__let);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__prog);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__apply);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__funk);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__funk__new_with_name_and_environment);
  
}

void f2__primmetros__reinitialize_globalvars() {
  f2__primcfunk__init__1_and_rest(primmetro__let, variable_definitions, body_expressions);
  f2__primcfunk__init__0_and_rest(primmetro__prog, body_expressions);
  f2__primcfunk__init__1_and_rest(primmetro__apply, funkable, arguments);
  f2__primcfunk__init__1_and_rest(primmetro__funk, variables, body_expressions);
  f2__primcfunk__init__1_and_rest(primmetro__funk__new_with_name_and_environment, name, environment, variables, body_expressions);
}

void f2__primmetros__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primmetros", "", &f2__primmetros__reinitialize_globalvars, &f2__primmetros__defragment__fix_pointers);
  
  f2__primmetros__reinitialize_globalvars();
}



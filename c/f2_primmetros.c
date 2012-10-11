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


f2ptr raw__cfunk__as__metrocfunk(f2ptr cause, f2ptr this) {
  return f2metrocfunk__new(cause,
			   f2__cfunk__name(         cause, this),
			   f2__cfunk__args(         cause, this),
			   f2__cfunk__cfunkptr(     cause, this),
			   f2__cfunk__env(          cause, this),
			   f2__cfunk__is_funktional(cause, this),
			   f2__cfunk__documentation(cause, this));
}

f2ptr f2__cfunk__as__metrocfunk(f2ptr cause, f2ptr this) {
  assert_argument_type(cfunk, this);
  return raw__cfunk__as__metrocfunk(cause, this);
}
def_pcfunk1(cfunk__as__metrocfunk, this,
	    "",
	    return f2__cfunk__as__metrocfunk(this_cause, this));




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
  f2ptr body_expressions__demetropolize_full = f2__exps_demetropolize_full(cause, fiber, environment, body_expressions);
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
  assert_argument_type(conslist, variables);
  assert_argument_type(conslist, body_expressions);
  return raw__primmetro__funk__new_with_name_and_environment(cause, name, environment, variables, body_expressions);
}
def_pcfunk3_and_rest(primmetro__funk__new_with_name_and_environment, name, environment, variables, body_expressions,
		     "",
		     return f2__primmetro__funk__new_with_name_and_environment(this_cause, name, environment, variables, body_expressions));



f2ptr raw__primmetro__funk__new_with_name(f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions) {
  f2ptr environment                          = f2list5__new(cause,
							    new__symbol(cause, "bytecode"),
							    new__symbol(cause, "copy"),
							    new__symbol(cause, "env"),
							    new__symbol(cause, "value"),
							    nil);
  f2ptr fiber                                = f2__this__fiber(cause);
  f2ptr fiber__environment                   = f2__fiber__env(cause, fiber);
  f2ptr body_expressions__demetropolize_full = f2__exps_demetropolize_full(cause, fiber, environment, body_expressions);
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

f2ptr f2__primmetro__funk__new_with_name(f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions) {
  assert_argument_type(conslist, variables);
  assert_argument_type(conslist, body_expressions);
  return raw__primmetro__funk__new_with_name(cause, name, variables, body_expressions);
}
def_pcfunk2_and_rest(primmetro__funk__new_with_name, name, variables, body_expressions,
		     "",
		     return f2__primmetro__funk__new_with_name(this_cause, name, variables, body_expressions));



f2ptr raw__primmetro__metro__new_with_name_and_environment(f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions) {
  f2ptr fiber                                = f2__this__fiber(cause);
  f2ptr fiber__environment                   = f2__fiber__env(cause, fiber);
  f2ptr body_expressions__demetropolize_full = f2__exps_demetropolize_full(cause, fiber, environment, body_expressions);
  f2ptr compiled_funk                        = f2__funk__new(cause, fiber, fiber__environment, name, variables, body_expressions__demetropolize_full, body_expressions, nil, nil, nil);
  f2ptr compiled_bytecodes                   = f2__funk__body_bytecodes(cause, compiled_funk);
  f2ptr is_funktional                        = f2__funk__is_funktional(cause, compiled_funk);
  return f2list2__new(cause,
		      new__symbol(cause, "metro-new"),
		      f2list9__new(cause,
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
				   nil));
}

f2ptr f2__primmetro__metro__new_with_name_and_environment(f2ptr cause, f2ptr name, f2ptr environment, f2ptr variables, f2ptr body_expressions) {
  assert_argument_type(conslist, variables);
  assert_argument_type(conslist, body_expressions);
  return raw__primmetro__metro__new_with_name_and_environment(cause, name, environment, variables, body_expressions);
}
def_pcfunk3_and_rest(primmetro__metro__new_with_name_and_environment, name, environment, variables, body_expressions,
		     "",
		     return f2__primmetro__metro__new_with_name_and_environment(this_cause, name, environment, variables, body_expressions));



f2ptr raw__primmetro__metro__new_with_name(f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions) {
  f2ptr environment                          = f2list5__new(cause,
							    new__symbol(cause, "bytecode"),
							    new__symbol(cause, "copy"),
							    new__symbol(cause, "env"),
							    new__symbol(cause, "value"),
							    nil);
  f2ptr fiber                                = f2__this__fiber(cause);
  f2ptr fiber__environment                   = f2__fiber__env(cause, fiber);
  f2ptr body_expressions__demetropolize_full = f2__exps_demetropolize_full(cause, fiber, environment, body_expressions);
  f2ptr compiled_funk                        = f2__funk__new(cause, fiber, fiber__environment, name, variables, body_expressions__demetropolize_full, body_expressions, nil, nil, nil);
  f2ptr compiled_bytecodes                   = f2__funk__body_bytecodes(cause, compiled_funk);
  f2ptr is_funktional                        = f2__funk__is_funktional(cause, compiled_funk);
  return f2list2__new(cause,
		      new__symbol(cause, "metro-new"),
		      f2list9__new(cause,
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
				   nil));
}

f2ptr f2__primmetro__metro__new_with_name(f2ptr cause, f2ptr name, f2ptr variables, f2ptr body_expressions) {
  assert_argument_type(conslist, variables);
  assert_argument_type(conslist, body_expressions);
  return raw__primmetro__metro__new_with_name(cause, name, variables, body_expressions);
}
def_pcfunk2_and_rest(primmetro__metro__new_with_name, name, variables, body_expressions,
		     "",
		     return f2__primmetro__metro__new_with_name(this_cause, name, variables, body_expressions));


/*
 *  [defmetro cond [:rest clauses]
 *    [if [null clauses]
 *        nil
 *      [let [[clause [car clauses]]]
 *        [conslist `if
 *                  [car clause]
 *	            [cons `prog [cdr clause]]
 *	            [apply &cond [cdr clauses]]]]]]
*/

f2ptr raw__primmetro__cond(f2ptr cause, f2ptr clauses) {
  if (clauses == nil) {
    return nil;
  }
  f2ptr clause                   = f2cons__car(clauses, cause);
  f2ptr clause__condition        = f2cons__car(clause, cause);
  f2ptr clause__body_expressions = f2cons__cdr(clause, cause);
  return f2list4__new(cause,
		      new__symbol(cause, "if"),
		      clause__condition,
		      raw__primmetro__prog(cause, clause__body_expressions),
		      raw__primmetro__cond(cause, f2cons__cdr(clauses, cause)));
}

f2ptr f2__primmetro__cond(f2ptr cause, f2ptr clauses) {
  assert_argument_type(conslist, clauses);
  {
    f2ptr iter = clauses;
    while (iter != nil) {
      f2ptr clause = f2cons__car(iter, cause);
      assert_argument_type(conslist, clause);
      s64 clause__length = 0;
      {
	f2ptr iter = clause;
	while (iter != nil) {
	  clause__length ++;
	  iter = f2cons__cdr(iter, cause);
	}
      }
      if (clause__length == 0) {
	return new__error(f2list6__new(cause,
				       new__symbol(cause, "bug_name"), new__symbol(cause, "cond-found_invalid_clause"),
				       new__symbol(cause, "clause"),   clause,
				       new__symbol(cause, "clauses"),  clauses));
      }
      iter = f2cons__cdr(iter, cause);
    }
  }
  return raw__primmetro__cond(cause, clauses);
}
def_pcfunk0_and_rest(primmetro__cond, clauses,
		     "",
		     return f2__primmetro__cond(this_cause, clauses));


// bootstrap-primobject metro helpers

f2ptr f2__primobject__frametype__slotdef__name(f2ptr cause, f2ptr this) {
  if (raw__symbol__is_type(cause, this)) {
    return this;
  } else if (raw__cons__is_type(cause, this)) {
    return f2cons__car(this, cause);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "invalid_type_for_frame_type_slotdef"),
				   new__symbol(cause, "this"),     this));
  }
}
def_pcfunk1(primobject__frametype__slotdef__name, this,
	    "",
	    return f2__primobject__frametype__slotdef__name(this_cause, this));


f2ptr f2__primobject__frametype__slotdef__value(f2ptr cause, f2ptr this) {
  if (raw__symbol__is_type(cause, this)) {
    return nil;
  } else if (raw__cons__is_type(cause, this)) {
    f2ptr this__cdr = f2cons__cdr(this, cause);
    assert_argument_type(cons, this__cdr);
    return f2cons__car(this__cdr, cause);
  } else {
    return new__error(f2list4__new(cause,
				   new__symbol(cause, "bug_name"), new__symbol(cause, "invalid_type_for_frame_type_slotdef"),
				   new__symbol(cause, "this"),     this));
  }
}
def_pcfunk1(primobject__frametype__slotdef__value, this,
	    "",
	    return f2__primobject__frametype__slotdef__value(this_cause, this));


f2ptr f2__primobject__frametype__type__has_parent(f2ptr cause, f2ptr frame_object, f2ptr body_expressions) {
  f2ptr     primobject_type = assert_value(f2__lookup_type(cause, frame_object));
  assert_argument_type(primobject_type, primobject_type);
  return f2bool__new(raw__primobject_type__has_parent_type(cause, primobject_type, body_expressions));
}
def_pcfunk2(primobject__frametype__type__has_parent, frame_object, body_expressions,
	    "",
	    return f2__primobject__frametype__type__has_parent(this_cause, frame_object, body_expressions));


/*
[defmetro with [frame_object :rest body]
  [let [[frame_object-gensym [gensym 'with']]]
    `[let [[,frame_object-gensym ,frame_object]]
       [if
        [object-inherits_from ,frame_object-gensym `frame]
	[let [[frame_object_environment [new
                                         environment
                                         ,frame_object-gensym
                                         [this-env]
                                         nil]]]
	  [let [[with_funk [funk-new_with_name_and_environment with frame_object_environment []
							       @body]]]
	    [apply with_funk nil]]]
	[error bug_type `cannot_execute_with_object_that_does_not_inherit_from_frame
	       object   ,frame_object-gensym]]]]]
*/

f2ptr f2__primobject__frametype__with(f2ptr cause, f2ptr frame_object, f2ptr body_expressions) {
  f2ptr frame_object__gensym = raw__gensym__new_from_utf8(cause, "with");
  return f2__primmetro__let(cause,
			    f2list1__new(cause, f2list2__new(cause, frame_object__gensym, frame_object)),
			    f2list4__new(cause,
					 new__symbol(cause, "if"),
					 f2list3__new(cause, new__symbol(cause, "object-inherits_from"), frame_object__gensym, f2list2__new(cause, new__symbol(cause, "quote"), new__symbol(cause, "frame"))),
					 f2__primmetro__let(cause,
							    f2list1__new(cause, f2list2__new(cause, new__symbol(cause, "frame_object_environment"), f2list5__new(cause,
																				 new__symbol(cause, "new"),
																				 new__symbol(cause, "environment"),
																				 frame_object__gensym
																				 f2list1__new(cause, new__symbol(cause, "this-env"))
																				 nil))),
							    f2list1__new(cause, f2__primmetro__let(cause,
												   f2list1__new(cause, f2list2__new(cause, new__symbol(cause, "with_funk"), f2__primmetro__metro__new_with_name_and_environment(cause,
																												new__symbol(cause, "with"),
																												new__symbol(cause, "frame_object_environment"),
																												nil,
																												body_expressions))),
												   f2list1__new(cause, f2list3__new(cause,
																    new__symbol(cause, "funk-apply"),
																    new__symbol(cause, "with_funk"),
																    nil))))),
					 f2list5__new(cause,
						      new__symbol(cause, "error"),
						      new__symbol(cause, "bug_type"), f2list2__new(cause, new__symbol(cause, "quote"), new_symbol(cause, "cannot_execute_with_object_that_does_not_inherit_from_frame")),
						      new__symbol(cause, "object"),   frame_object__gensym)));
}
def_pcfunk2(primobject__frametype__with, frame_object, body_expressions,
	    "",
	    return f2__primobject__frametype__with(this_cause, frame_object, body_expressions));






// **

void f2__primmetros__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --

  f2__primcfunk__init__defragment__fix_pointers(cfunk__as__metrocfunk);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__let);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__prog);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__apply);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__funk);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__funk__new_with_name_and_environment);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__funk__new_with_name);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__metro__new_with_name_and_environment);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__metro__new_with_name);
  f2__primcfunk__init__defragment__fix_pointers(primmetro__cond);
  
  // bootstrap-primobject metro helpers
  
  f2__primcfunk__init__defragment__fix_pointers(primobject__frametype__slotdef__name);
  f2__primcfunk__init__defragment__fix_pointers(primobject__frametype__slotdef__value);
  f2__primcfunk__init__defragment__fix_pointers(primobject__frametype__type__has_parent);
  f2__primcfunk__init__defragment__fix_pointers(primobject__frametype__with);
  
}

void f2__primmetros__reinitialize_globalvars() {
  f2__primcfunk__init__1(cfunk__as__metrocfunk, this);
  f2__primcfunk__init__1_and_rest(primmetro__let, variable_definitions, body_expressions);
  f2__primcfunk__init__0_and_rest(primmetro__prog, body_expressions);
  f2__primcfunk__init__1_and_rest(primmetro__apply, funkable, arguments);
  f2__primcfunk__init__1_and_rest(primmetro__funk, variables, body_expressions);
  f2__primcfunk__init__3_and_rest(primmetro__funk__new_with_name_and_environment, name, environment, variables, body_expressions);
  f2__primcfunk__init__2_and_rest(primmetro__funk__new_with_name, name, variables, body_expressions);
  f2__primcfunk__init__3_and_rest(primmetro__metro__new_with_name_and_environment, name, environment, variables, body_expressions);
  f2__primcfunk__init__2_and_rest(primmetro__metro__new_with_name, name, variables, body_expressions);
  f2__primcfunk__init__0_and_rest(primmetro__cond, clauses);
  
  // bootstrap-primobject metro helpers
  
  f2__primcfunk__init__1(primobject__frametype__slotdef__name,    this);
  f2__primcfunk__init__1(primobject__frametype__slotdef__value,   this);
  f2__primcfunk__init__2(primobject__frametype__type__has_parent, type_name, parent_name);
  f2__primcfunk__init__2(primobject__frametype__with,             frame_object, body_expressions);

}

void f2__primmetros__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "primmetros", "", &f2__primmetros__reinitialize_globalvars, &f2__primmetros__defragment__fix_pointers);
  
  f2__primmetros__reinitialize_globalvars();
}



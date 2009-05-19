// 
// Copyright (c) 2007-2009 Bo Morgan.
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

//f2ptr f2__dptr__trace_for_primobject_type(f2ptr dptr_array, f2ptr dptr_index, f2ptr type) {
//  f2ptr cause = nil;
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  dptr_array=", dptr_array);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  dptr_index=", dptr_index);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  dptr_trace=", f2__array__elt__trace(cause, dptr_array, dptr_index));
//  
//  error(nil, "f2__dptr__trace_for_primobject_type error: not implemented.");
//}

//f2ptr f2__primobject_argument_type_check_failure__bytecode__critic(f2ptr cause, f2ptr expected_type, f2ptr argument_value, f2ptr argument_dptr_array, f2ptr argument_dptr_index, f2ptr bytecode) {
//  //f2ptr bytecode__command = f2bytecode__command(bytecode, cause);
//  return nil; // shouldn't get here.
//}

//f2ptr f2__primobject_argument_type_check_failure__critic(f2ptr cause, f2ptr expected_type, f2ptr argument_value, f2ptr argument_dptr_array, f2ptr argument_dptr_index) {
//  fprintf(__funk2.globalenv.stdtrace, "\nf2__primobject_argument_type_check_failure__critic here."); fflush(__funk2.globalenv.stdtrace);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  cause=               ", cause);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  expected_type=       ", expected_type);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  argument_value=      ", argument_value);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  argument_dptr_array= ", argument_dptr_array);
//  f2__fprint_prompt(cause, __funk2.globalenv.stdtrace_stream, "  argument_dptr_index= ", argument_dptr_index);
//  
//  f2__fprint_prompt_debug(cause, __funk2.globalenv.stdtrace_stream, "  cause (with extended debug info)=               ", cause);
//  f2__fprint_prompt_debug(cause, __funk2.globalenv.stdtrace_stream, "  expected_type (with extended debug info)=       ", expected_type);
//  f2__fprint_prompt_debug(cause, __funk2.globalenv.stdtrace_stream, "  argument_value (with extended debug info)=      ", argument_value);
//  f2__fprint_prompt_debug(cause, __funk2.globalenv.stdtrace_stream, "  argument_dptr_array (with extended debug info)= ", argument_dptr_array);
//  f2__fprint_prompt_debug(cause, __funk2.globalenv.stdtrace_stream, "  argument_dptr_index (with extended debug info)= ", argument_dptr_index);
//  
//  if (! raw__symbolp(expected_type, cause))                                 {error(nil, "f2__primobject_argument_type_check_failure__critic error: expected_type must be symbol.");}
//  if (argument_dptr_array && (! raw__arrayp(argument_dptr_array, cause)))   {error(nil, "f2__primobject_argument_type_check_failure__critic error: argument_dptr_array must be nil or array.");}
//  if (argument_dptr_index && (! raw__integerp(argument_dptr_array, cause))) {error(nil, "f2__primobject_argument_type_check_failure__critic error: argument_dptr_index must be nil or integer.");}
//  
//  fprintf(__funk2.globalenv.stdtrace_fptr, "\nf2__primobject_argument_type_check_failure__critic tracing..."); fflush(__funk2.globalenv.stdtrace_fptr);
//  
//  if (raw__causep(cause, cause)) {
//    //f2ptr cause__name = f2cause__name(cause, cause);
//    //if (cause__name == __thread__execute_bytecode__cause__symbol) {
//    //  f2ptr bytecode = f2cause__args(cause, cause);
//    //  if (raw__bytecodep(bytecode, cause)) {
//    //	return f2__primobject_argument_type_check_failure__bytecode__critic(cause, expected_type, argument_value, argument_dptr_array, argument_dptr_index, bytecode);
//    //  }
//    //}
//  }
//  
//  error(nil, "f2__primobject_argument_type_check_failure__critic error: not implemented.");
//  return nil;
//}


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

#ifndef F2__DEBUG_MACROS__H
#define F2__DEBUG_MACROS__H

#define trace_type__function_symbol(trace_type) __trace__##trace_type

#define trace1(trace_type, exp1)                       (trace_type__function_symbol(trace_type)(exp1))
#define deftrace1(trace_type, exp1_symbol, trace_body) f2ptr trace_type__function_symbol(trace_type)(f2ptr exp1_symbol) {trace_body;}

#define trace2(trace_type, exp1, exp2)                              (trace_type__function_symbol(trace_type)(exp1, exp2))
#define deftrace2(trace_type, exp1_symbol, exp2_symbol, trace_body) f2ptr trace_type__function_symbol(trace_type)(f2ptr exp1_symbol, f2ptr exp2_symbol) {trace_body;}

#ifdef DEBUG

#define debug_trace1(trace_type, exp1)       trace1(trace_type, exp1)
#define debug_trace2(trace_type, exp1, exp2) trace2(trace_type, exp1, exp2)

#else // DEBUG

#define debug_trace1(trace_type, exp1)       exp1
#define debug_trace2(trace_type, exp1, exp2) exp1

#endif // DEBUG

#endif // F2__DEBUG_MACROS__H

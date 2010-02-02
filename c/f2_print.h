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

#ifndef F2__PRINT__H
#define F2__PRINT__H

#include "f2_ptypes.h"
#include "f2_primobjects.h"
#include "f2_primobject__ptypehash.h"
#include "f2_primobject__frame.h"
#include "f2_primobject__environment.h"
#include "f2_reader.h"

#define default_print_recursion_depth 20

void f2__fwrite__raw_char  (f2ptr cause, f2ptr fptr, char ch, int return_size[2], boolean_t use_html);
void f2__fwrite__raw_string(f2ptr cause, f2ptr fptr, f2ptr str, f2ptr use_html);

f2ptr f2__fwrite_html     (f2ptr cause, f2ptr fiber, f2ptr fptr, f2ptr exp);
f2ptr f2__fwrite_depth    (f2ptr cause, f2ptr fiber, f2ptr fptr, f2ptr exp, int recursion_depth);
f2ptr f2__write_depth     (f2ptr cause, f2ptr fiber, f2ptr exp, int recursion_depth);
f2ptr f2__exp__print_depth(f2ptr cause, f2ptr fiber, f2ptr exp, int recursion_depth);
f2ptr f2__print_depth     (f2ptr cause, f2ptr fiber, f2ptr exp, int recursion_depth);

f2ptr f2__exp__print  (f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr f2__fiber__print(f2ptr cause, f2ptr fiber, f2ptr exp);
f2ptr f2__print       (f2ptr cause, f2ptr exp);
f2ptr f2__fwrite      (f2ptr cause, f2ptr fiber, f2ptr fptr, f2ptr exp);
f2ptr f2__write       (f2ptr cause, f2ptr fiber, f2ptr exp);

f2ptr f2__fprint_prompt      (f2ptr cause, f2ptr fiber, f2ptr stream, char* prompt, f2ptr exp);
f2ptr f2__fprint_prompt_debug(f2ptr cause, f2ptr fiber, f2ptr stream, char* prompt, f2ptr exp);

f2ptr f2__print_prompt      (f2ptr cause, f2ptr fiber, char* prompt, f2ptr exp);
f2ptr f2__print_prompt_debug(f2ptr cause, f2ptr fiber, char* prompt, f2ptr exp);

#endif // F2__PRINT__H

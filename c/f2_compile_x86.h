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

#ifndef F2__COMPILE_X86__H
#define F2__COMPILE_X86__H

#include "f2_bytecodes.h"
#include "f2_compile.h"
#include "f2_ptypes.h"

typedef enum x86_reg_e {
  x86_reg__eax,
  x86_reg__ecx,
  x86_reg__edx,
  x86_reg__ebx,
  x86_reg__esp,
  x86_reg__ebp,
  x86_reg__esi,
  x86_reg__edi
} x86_reg_t;

f2ptr f2chunk__new_compiled_from_funk(f2ptr cause, f2ptr funk);
f2ptr f2chunk__new_compiled_from_metro(f2ptr cause, f2ptr metro);

#endif // F2__COMPILE_X86__H

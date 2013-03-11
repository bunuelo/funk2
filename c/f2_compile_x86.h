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

#ifndef F2__COMPILE_X86__TYPES__H
#define F2__COMPILE_X86__TYPES__H

// machine_code_chunk

typedef struct funk2_object_type__machine_code_chunk__slot_s funk2_object_type__machine_code_chunk__slot_t;
declare_object_type_2_slot(machine_code_chunk, chunk, index_label_ptypehash,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

// x86_funk

typedef struct funk2_object_type__x86_funk__slot_s funk2_object_type__x86_funk__slot_t;
declare_object_type_5_slot(x86_funk,
			   name,
			   variables,
			   body,
			   demetropolized_body,
			   machine_code_chunk,
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );

#endif // F2__COMPILE_X86__TYPES__H


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


// machine_code_chunk

declare_primobject_2_slot(machine_code_chunk, chunk, index_label_ptypehash);

f2ptr raw__machine_code_chunk__new(f2ptr cause, f2ptr chunk, f2ptr index_label_ptypehash);
f2ptr  f2__machine_code_chunk__new(f2ptr cause);



f2ptr f2chunk__new_compiled_from_funk(f2ptr cause, f2ptr funk);
f2ptr f2chunk__new_compiled_from_metro(f2ptr cause, f2ptr metro);

f2ptr f2machine_code_chunk__primobject_type__new_aux(f2ptr cause);

f2ptr raw__expression__compile_x86(f2ptr cause, f2ptr expression);
f2ptr  f2__expression__compile_x86(f2ptr cause, f2ptr expression);


// x86_funk

declare_primobject_5_slot(x86_funk,
			  name,
			  variables,
			  body,
			  demetropolized_body,
			  machine_code_chunk);

f2ptr raw__x86_funk__new(f2ptr cause, f2ptr name, f2ptr variables, f2ptr body, f2ptr machine_code_chunk);
f2ptr  f2__x86_funk__new(f2ptr cause, f2ptr name, f2ptr variables, f2ptr body);

f2ptr f2x86_funk__primobject_type__new_aux(f2ptr cause);

// **

void f2__compile_x86__defragment__fix_pointers();
void f2__compile_x86__reinitialize_globalvars();
void f2__compile_x86__initialize();

#endif // F2__COMPILE_X86__H

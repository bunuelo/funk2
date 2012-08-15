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

#ifndef F2__CAUSE__TYPES__H
#define F2__CAUSE__TYPES__H

#include "f2_primobjects.h"

// cause_group

typedef struct funk2_object_type__cause_group__slot_s funk2_object_type__cause_group__slot_t;
declare_object_type_6_slot(cause_group,
			   bytecode_count_cmutex,
			   bytecode_count,
			   execution_nanoseconds_cmutex,
			   execution_nanoseconds_chunk,
			   bytes_allocated_count_cmutex,
			   bytes_allocated_count_chunk,
			   f2ptr increase_bytecode_count__symbol;
			   f2ptr increase_bytecode_count__funk;
			   f2ptr execution_nanoseconds__symbol;
			   f2ptr execution_nanoseconds__funk;
			   f2ptr execution_nanoseconds__set__symbol;
			   f2ptr execution_nanoseconds__set__funk;
			   f2ptr increase_execution_nanoseconds__symbol;
			   f2ptr increase_execution_nanoseconds__funk;
			   f2ptr bytes_allocated_count__symbol;
			   f2ptr bytes_allocated_count__funk;
			   f2ptr bytes_allocated_count__set__symbol;
			   f2ptr bytes_allocated_count__set__funk;
			   f2ptr increase_bytes_allocated_count__symbol;
			   f2ptr increase_bytes_allocated_count__funk;
			   f2ptr terminal_print_with_frame__symbol;
			   f2ptr terminal_print_with_frame__funk;
			   );


// cause

typedef struct funk2_object_type__cause__slot_s funk2_object_type__cause__slot_t;
declare_object_type_16_slot(cause,
			    fibers_cmutex,
			    fibers,
			    frame,
			    allocate_traced_arrays,
			    bytecode_tracing_on,
			    memory_tracing_on,
			    imagination_stack,
			    bytecode_branch_callbacks,
			    bytecode_funk_callbacks,
			    bytecode_tracer_callbacks,
			    bytecode_endfunk_callbacks,
			    complete_funk_callbacks,
			    read_other_memory_callbacks,
			    write_other_memory_callbacks,
			    critics,
			    cause_groups,
			    
			    f2ptr type_var_defined__symbol;
			    f2ptr type_var_defined__funk;
			    f2ptr var_defined__symbol;
			    f2ptr var_defined__funk;
			    f2ptr type_var_value__set__symbol;
			    f2ptr type_var_value__set__funk;
			    f2ptr var_value__set__symbol;
			    f2ptr var_value__set__funk;
			    f2ptr define__symbol;
			    f2ptr define__funk;
			    f2ptr define__funk__symbol;
			    f2ptr define__funk__funk;
			    f2ptr lookup__symbol;
			    f2ptr lookup__funk;
			    f2ptr lookup__funk__symbol;
			    f2ptr lookup__funk__funk;
			    f2ptr terminal_print_with_frame__symbol;
			    f2ptr terminal_print_with_frame__funk;
			    );

#endif // F2__CAUSE__TYPES__H


#ifndef F2__CAUSE__H
#define F2__CAUSE__H

#include "f2_primobjects.h"


// cause_group

declare_primobject_6_slot(cause_group,
			  bytecode_count_cmutex,
			  bytecode_count,
			  execution_nanoseconds_cmutex,
			  execution_nanoseconds_chunk,
			  bytes_allocated_count_cmutex,
			  bytes_allocated_count_chunk);

f2ptr  f2__cause_group__new                           (f2ptr cause);
void  raw__cause_group__increase_bytecode_count       (f2ptr cause, f2ptr this, u64 relative_bytecode_count);
f2ptr  f2__cause_group__increase_bytecode_count       (f2ptr cause, f2ptr this, f2ptr relative_bytecode_count);
u64   raw__cause_group__execution_nanoseconds         (f2ptr cause, f2ptr this);
f2ptr  f2__cause_group__execution_nanoseconds         (f2ptr cause, f2ptr this);
void  raw__cause_group__execution_nanoseconds__set    (f2ptr cause, f2ptr this, u64 execution_nanoseconds);
f2ptr  f2__cause_group__execution_nanoseconds__set    (f2ptr cause, f2ptr this, f2ptr execution_nanoseconds);
void  raw__cause_group__increase_execution_nanoseconds(f2ptr cause, f2ptr this, u64 relative_execution_nanoseconds);
f2ptr  f2__cause_group__increase_execution_nanoseconds(f2ptr cause, f2ptr this, f2ptr relative_execution_nanoseconds);
u64   raw__cause_group__bytes_allocated_count         (f2ptr cause, f2ptr this);
f2ptr  f2__cause_group__bytes_allocated_count         (f2ptr cause, f2ptr this);
void  raw__cause_group__bytes_allocated_count__set    (f2ptr cause, f2ptr this, u64 bytes_allocated_count);
f2ptr  f2__cause_group__bytes_allocated_count__set    (f2ptr cause, f2ptr this, f2ptr bytes_allocated_count);
void  raw__cause_group__increase_bytes_allocated_count(f2ptr cause, f2ptr this, u64 relative_bytes_allocated_count);
f2ptr  f2__cause_group__increase_bytes_allocated_count(f2ptr cause, f2ptr this, f2ptr relative_bytes_allocated_count);

f2ptr f2cause_group__primobject_type__new_aux(f2ptr cause);


// cause

#define cause__allocate_traced_arrays__default_value (nil)
//#define cause__allocate_traced_arrays__default_value (__funk2.globalenv.true__symbol)

declare_primobject_16_slot(cause,
			   fibers_cmutex,
			   fibers,
			   frame,
			   allocate_traced_arrays,
			   bytecode_tracing_on,
			   memory_tracing_on,
			   imagination_stack,
			   bytecode_branch_callbacks,
			   bytecode_funk_callbacks,
			   bytecode_tracer_callbacks,
			   bytecode_endfunk_callbacks,
			   complete_funk_callbacks,
			   read_other_memory_callbacks,
			   write_other_memory_callbacks,
			   critics,
			   cause_groups);

f2ptr      f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source);
f2ptr     raw__cause__add_fiber                    (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__cause__add_fiber                    (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr     raw__cause__remove_fiber                 (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__cause__remove_fiber                 (f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__cause__new_imaginary                (f2ptr cause, f2ptr imagination_name);
f2ptr      f2__cause                               (f2ptr cause);
f2ptr      f2__cause__bytecode_tracing_on          (f2ptr cause, f2ptr this);
f2ptr      f2__cause__lookup_type_var_value        (f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
boolean_t raw__cause__type_var_defined             (f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr      f2__cause__type_var_defined             (f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr     raw__cause__type_var_value__set          (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr      f2__cause__type_var_value__set          (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr     raw__cause__var_value__set               (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
f2ptr      f2__cause__var_value__set               (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
boolean_t raw__cause__var_defined                  (f2ptr cause, f2ptr this, f2ptr var);
f2ptr      f2__cause__var_defined                  (f2ptr cause, f2ptr this, f2ptr var);
boolean_t raw__cause__allocate_traced_arrays       (f2ptr cause, f2ptr this);
void      raw__cause__define_type_var              (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
f2ptr      f2__cause__define_type_var              (f2ptr cause, f2ptr this, f2ptr type, f2ptr var, f2ptr value);
void      raw__cause__define                       (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
f2ptr      f2__cause__define                       (f2ptr cause, f2ptr this, f2ptr var, f2ptr value);
void      raw__cause__define__funk                 (f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value);
f2ptr      f2__cause__define__funk                 (f2ptr cause, f2ptr this, f2ptr funkvar, f2ptr value);
f2ptr     raw__cause__lookup                       (f2ptr cause, f2ptr this, f2ptr var);
f2ptr      f2__cause__lookup                       (f2ptr cause, f2ptr this, f2ptr var);

f2ptr f2cause__primobject_type__new_aux(f2ptr cause);

// **

void f2__cause__preinitialize_globalvars();
void f2__cause__reinitialize_globalvars();
void f2__cause__initialize();

#endif // F2__CAUSE__H


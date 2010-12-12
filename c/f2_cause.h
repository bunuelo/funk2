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

#ifndef F2__CAUSE__TYPES__H
#define F2__CAUSE__TYPES__H

#include "f2_primobjects.h"

// cause

typedef struct funk2_object_type__cause__slot_s funk2_object_type__cause__slot_t;
declare_object_type_18_slot(cause,
			    fibers_mutex,
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
			    event_graph_mutex,
			    event_graph,
			    event_graph_last_event,
			    critics,
			    
			    f2ptr type_var_defined__symbol;
			    f2ptr type_var_defined__funk;
			    f2ptr var_defined__symbol;
			    f2ptr var_defined__funk;
			    f2ptr define__symbol;
			    f2ptr define__funk;
			    f2ptr define__funk__symbol;
			    f2ptr define__funk__funk;
			    f2ptr lookup__symbol;
			    f2ptr lookup__funk;
			    f2ptr lookup__funk__symbol;
			    f2ptr lookup__funk__funk;
			    f2ptr add_graph_event__funk__symbol;
			    f2ptr add_graph_event__funk__funk;
			    f2ptr add_graph_event__endfunk__symbol;
			    f2ptr add_graph_event__endfunk__funk;
			    f2ptr add_graph_event__branch__symbol;
			    f2ptr add_graph_event__branch__funk;
			    f2ptr add_graph_event__complete_funk__symbol;
			    f2ptr add_graph_event__complete_funk__funk;
			    f2ptr add_graph_event__read_other_memory__symbol;
			    f2ptr add_graph_event__read_other_memory__funk;
			    f2ptr add_graph_event__write_other_memory__symbol;
			    f2ptr add_graph_event__write_other_memory__funk;
			    f2ptr terminal_print_with_frame__symbol;
			    f2ptr terminal_print_with_frame__funk;
			    );

#endif // F2__CAUSE__TYPES__H


#ifndef F2__CAUSE__H
#define F2__CAUSE__H

#include "f2_primobjects.h"

// cause

//#define cause__allocate_traced_arrays__default_value (nil)
#define cause__allocate_traced_arrays__default_value (__funk2.globalenv.true__symbol)

declare_primobject_18_slot(cause,
			   fibers_mutex,
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
			   event_graph_mutex,
			   event_graph,
			   event_graph_last_event,
			   critics
			   );

f2ptr      f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source);
f2ptr      f2__cause__new_imaginary(                f2ptr cause, f2ptr imagination_name);
f2ptr      f2__cause__add_fiber(                    f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__cause__remove_fiber(                 f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr      f2__cause(                               f2ptr cause);
f2ptr      f2__cause__bytecode_tracing_on(          f2ptr cause, f2ptr this);
f2ptr      f2__cause__lookup_type_var_value(        f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
boolean_t raw__cause__type_var_defined(             f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
f2ptr      f2__cause__type_var_defined(             f2ptr cause, f2ptr this, f2ptr type, f2ptr var);
boolean_t raw__cause__var_defined(                  f2ptr cause, f2ptr this, f2ptr var);
f2ptr      f2__cause__var_defined(                  f2ptr cause, f2ptr this, f2ptr var);
f2ptr     raw__cause__lookup(                       f2ptr cause, f2ptr this, f2ptr var);
f2ptr      f2__cause__lookup(                       f2ptr cause, f2ptr this, f2ptr var);

f2ptr f2cause__primobject_type__new_aux(f2ptr cause);

// **

void f2__cause__reinitialize_globalvars();
void f2__cause__initialize();

#endif // F2__CAUSE__H


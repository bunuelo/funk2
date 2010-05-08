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
declare_object_type_13_slot(cause,
			    fibers_mutex,
			    fibers,
			    frame,
			    allocate_traced_arrays,
			    bytecode_tracing_on,
			    memory_tracing_on,
			    imagination_stack,
			    bytecode_branch_funks,
			    bytecode_funk_funks,
			    bytecode_tracer_funks,
			    bytecode_endfunk_funks,
			    event_graph_mutex,
			    event_graph,
			    
			    f2ptr define__symbol;
			    f2ptr define__funk;
			    f2ptr define__funk__symbol;
			    f2ptr define__funk__funk;
			    f2ptr add_graph_event__funk__symbol;
			    f2ptr add_graph_event__funk__funk;
			    f2ptr add_graph_event__endfunk__symbol;
			    f2ptr add_graph_event__endfunk__funk;
			    f2ptr add_graph_event__branch__symbol;
			    f2ptr add_graph_event__branch__funk;
			    );

#endif // F2__CAUSE__TYPES__H


#ifndef F2__CAUSE__H
#define F2__CAUSE__H

#include "f2_primobjects.h"

// cause

#define cause__allocate_traced_arrays__default_value (__funk2.globalenv.true__symbol)

declare_primobject_13_slot(cause,
			   fibers_mutex,
			   fibers,
			   frame,
			   allocate_traced_arrays,
			   bytecode_tracing_on,
			   memory_tracing_on,
			   imagination_stack,
			   bytecode_branch_funks,
			   bytecode_funk_funks,
			   bytecode_tracer_funks,
			   bytecode_endfunk_funks,
			   event_graph_mutex,
			   event_graph
			   );

f2ptr f2__cause__new_with_inherited_properties(f2ptr cause, f2ptr source);
f2ptr f2__cause__new_imaginary(f2ptr cause, f2ptr imagination_name);
f2ptr f2__cause__add_fiber(f2ptr cause, f2ptr this, f2ptr fiber);
f2ptr f2__cause__remove_fiber(f2ptr cause, f2ptr this, f2ptr fiber);

f2ptr  f2__cause(f2ptr cause);
f2ptr  f2__cause__bytecode_tracing_on(f2ptr cause, f2ptr this);
f2ptr  f2__cause__lookup_type_var_value(f2ptr cause, f2ptr this, f2ptr type, f2ptr var);

f2ptr f2cause__primobject_type__new_aux(f2ptr cause);

// **

void f2__cause__reinitialize_globalvars();
void f2__cause__initialize();

#endif // F2__CAUSE__H


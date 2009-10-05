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

#ifndef F2__GLOBALENV__H
#define F2__GLOBALENV__H

#include "f2_memory.h"
#include "f2_ptypes.h"
#include "f2_primfunks.h"
#include "f2_object.h"
#include "f2_blocks_world.h"

typedef struct funk2_globalenv_s {
  
  f2ptr              f2_globalenv_c__cause__symbol;
  f2ptr                   f2_ansi_c__cause__symbol;
  f2ptr              f2_bytecodes_c__cause__symbol;
  f2ptr                f2_compile_c__cause__symbol;
  f2ptr                f2_gmodule_c__cause__symbol;
  f2ptr                   f2_load_c__cause__symbol;
  f2ptr                 f2_memory_c__cause__symbol;
  f2ptr              f2_primfunks_c__cause__symbol;
  f2ptr f2_primobject_environment_c__cause__symbol;
  f2ptr       f2_primobject_frame_c__cause__symbol;
  f2ptr   f2_primobject_hashtable_c__cause__symbol;
  f2ptr            f2_primobjects_c__cause__symbol;
  f2ptr                  f2_print_c__cause__symbol;
  f2ptr                f2_pthread_c__cause__symbol;
  f2ptr                 f2_ptypes_c__cause__symbol;
  f2ptr                 f2_reader_c__cause__symbol;
  f2ptr           f2_redblacktree_c__cause__symbol;
  f2ptr                   f2_repl_c__cause__symbol;
  f2ptr              f2_scheduler_c__cause__symbol;
  f2ptr                 f2_signal_c__cause__symbol;
  f2ptr                 f2_socket_c__cause__symbol;
  f2ptr             f2_swapmemory_c__cause__symbol;
  f2ptr                  f2_fiber_c__cause__symbol;
  f2ptr                   f2_time_c__cause__symbol;
  f2ptr                  f2_trace_c__cause__symbol;
  f2ptr              f2_serialize_c__cause__symbol;
  f2ptr                     funk2_c__cause__symbol;
  
  f2ptr true__symbol;
  f2ptr quote__symbol;
  f2ptr backquote__list__symbol;
  f2ptr backquote__list_append__symbol;
  f2ptr comma__symbol;
  f2ptr cdr_comma__symbol;
  f2ptr funkvar__symbol;
  f2ptr stdin_stream__symbol;
  f2ptr stdin_stream;
  f2ptr stdout_stream__symbol;
  f2ptr stdout_stream;
  f2ptr stderr_stream__symbol;
  f2ptr stderr_stream;
  
  f2ptr type__symbol;
  
  f2ptr define_funk__symbol;
  f2ptr define__symbol;
  f2ptr mutatefunk__symbol;
  f2ptr mutate__symbol;
  f2ptr and_rest__symbol;
  f2ptr apply__symbol;
  f2ptr globalize__symbol;
  f2ptr globalize_funk__symbol;
  f2ptr yield__symbol;
  f2ptr if__symbol;
  f2ptr bytecode__symbol;
  f2ptr rawcode__symbol;
  f2ptr while__symbol;
  f2ptr return__symbol;
  
  f2ptr trace_all_compiles__symbol;
  
  f2ptr create_event__symbol;
  f2ptr read_event__symbol;
  f2ptr write_event__symbol;
  
  f2ptr ptype_integer__symbol;
  f2ptr ptype_double__symbol;
  f2ptr ptype_float__symbol;
  f2ptr ptype_pointer__symbol;
  f2ptr ptype_gfunkptr__symbol;
  f2ptr ptype_mutex__symbol;
  f2ptr ptype_char__symbol;
  f2ptr ptype_string__symbol;
  f2ptr ptype_symbol__symbol;
  f2ptr ptype_chunk__symbol;
  f2ptr ptype_simple_array__symbol;
  f2ptr ptype_traced_array__symbol;
  f2ptr ptype_larva__symbol;
  
  f2ptr get__symbol;
  f2ptr set__symbol;
  f2ptr execute__symbol;
  
  funk2_object_types_t            object_type;
  funk2_blocks_world_t            blocks_world;
  
} funk2_globalenv_t;

void funk2_globalenv__init(funk2_globalenv_t* this);
void funk2_globalenv__destroy(funk2_globalenv_t* this);

f2ptr              f2_globalenv_c__cause__new(f2ptr cause);
f2ptr                   f2_ansi_c__cause__new(f2ptr cause);
f2ptr              f2_bytecodes_c__cause__new(f2ptr cause);
f2ptr                f2_compile_c__cause__new(f2ptr cause);
f2ptr                f2_gmodule_c__cause__new(f2ptr cause);
f2ptr                   f2_load_c__cause__new(f2ptr cause);
f2ptr                 f2_memory_c__cause__new(f2ptr cause);
f2ptr              f2_primfunks_c__cause__new(f2ptr cause);
f2ptr f2_primobject_environment_c__cause__new(f2ptr cause);
f2ptr       f2_primobject_frame_c__cause__new(f2ptr cause);
f2ptr   f2_primobject_hashtable_c__cause__new(f2ptr cause);
f2ptr            f2_primobjects_c__cause__new(f2ptr cause);
f2ptr                  f2_print_c__cause__new(f2ptr cause);
f2ptr                f2_pthread_c__cause__new(f2ptr cause);
f2ptr                 f2_ptypes_c__cause__new(f2ptr cause);
f2ptr                 f2_reader_c__cause__new(f2ptr cause);
f2ptr           f2_redblacktree_c__cause__new(f2ptr cause);
f2ptr                   f2_repl_c__cause__new(f2ptr cause);
f2ptr              f2_scheduler_c__cause__new(f2ptr cause);
f2ptr                 f2_signal_c__cause__new(f2ptr cause);
f2ptr                 f2_socket_c__cause__new(f2ptr cause);
f2ptr             f2_swapmemory_c__cause__new(f2ptr cause);
f2ptr                  f2_fiber_c__cause__new(f2ptr cause);
f2ptr                   f2_time_c__cause__new(f2ptr cause);
f2ptr                  f2_trace_c__cause__new(f2ptr cause);
f2ptr              f2_serialize_c__cause__new(f2ptr cause);
f2ptr                     funk2_c__cause__new(f2ptr cause);

f2ptr f2bool__new(uint raw_value);

void f2__globalenv__initialize();

#endif // F2__GLOBALENV__H


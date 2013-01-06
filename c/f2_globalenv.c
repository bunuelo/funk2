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

void funk2_globalenv__reinit(funk2_globalenv_t* this) {
  char* symbol_str;
  
  symbol_str = "globalenv:f2_globalenv.c";              this->f2_globalenv_c__cause__symbol              = new__symbol(initial_cause(), symbol_str);
  
  f2ptr cause = f2_globalenv_c__cause__new(initial_cause());
  
  symbol_str = "globalenv:f2_bytecodes.c";              this->f2_bytecodes_c__cause__symbol              = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_ansi.c";                   this->f2_ansi_c__cause__symbol                   = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_compile.c";                this->f2_compile_c__cause__symbol                = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_gmodule.c";                this->f2_gmodule_c__cause__symbol                = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_load.c";                   this->f2_load_c__cause__symbol                   = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_memory.c";                 this->f2_memory_c__cause__symbol                 = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_primfunks.c";              this->f2_primfunks_c__cause__symbol              = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_primobject_environment.c"; this->f2_primobject_environment_c__cause__symbol = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_primobject_frame.c";       this->f2_primobject_frame_c__cause__symbol       = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_primobject_ptypehash.c";   this->f2_primobject_ptypehash_c__cause__symbol   = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_primobjects.c";            this->f2_primobjects_c__cause__symbol            = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_print.c";                  this->f2_print_c__cause__symbol                  = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_processor.c";              this->f2_processor_c__cause__symbol              = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_pthread.c";                this->f2_pthread_c__cause__symbol                = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_ptypes.c";                 this->f2_ptypes_c__cause__symbol                 = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_reader.c";                 this->f2_reader_c__cause__symbol                 = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_redblacktree.c";           this->f2_redblacktree_c__cause__symbol           = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_repl.c";                   this->f2_repl_c__cause__symbol                   = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_scheduler.c";              this->f2_scheduler_c__cause__symbol              = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_signal.c";                 this->f2_signal_c__cause__symbol                 = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_socket.c";                 this->f2_socket_c__cause__symbol                 = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_swapmemory.c";             this->f2_swapmemory_c__cause__symbol             = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_fiber.c";                  this->f2_fiber_c__cause__symbol                  = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_time.c";                   this->f2_time_c__cause__symbol                   = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_trace.c";                  this->f2_trace_c__cause__symbol                  = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:f2_serialize.c";              this->f2_serialize_c__cause__symbol              = new__symbol(cause, symbol_str);
  symbol_str = "globalenv:funk2.c";                     this->funk2_c__cause__symbol                     = new__symbol(cause, symbol_str);

  symbol_str = "t";                                     this->true__symbol                               = new__symbol(cause, symbol_str);
  symbol_str = "quote";                                 this->quote__symbol                              = new__symbol(cause, symbol_str);
  
  this->backquote__list__symbol        = new__symbol(cause, "backquote-list");
  this->backquote__list_append__symbol = new__symbol(cause, "backquote-list_append");
  this->comma__symbol                  = new__symbol(cause, "comma");
  this->cdr_comma__symbol              = new__symbol(cause, "cdr-comma");
  
  this->funkvar__symbol                = new__symbol(cause, "funkvar");
  this->define_funk__symbol            = new__symbol(cause, "define-funk");
  this->mutatefunk__symbol             = new__symbol(cause, "mutatefunk");
  this->define__symbol                 = new__symbol(cause, "define");
  this->mutate__symbol                 = new__symbol(cause, "mutate");
  this->and_rest__symbol               = new__symbol(cause, ":rest");
  this->apply__symbol                  = new__symbol(cause, "funk-apply");
  this->globalize__symbol              = new__symbol(cause, "globalize");
  this->globalize_funk__symbol         = new__symbol(cause, "globalize-funk");
  this->yield__symbol                  = new__symbol(cause, "yield");
  this->if__symbol                     = new__symbol(cause, "if");
  this->bytecode__symbol               = new__symbol(cause, "bytecode");
  this->rawcode__symbol                = new__symbol(cause, "rawcode");
  this->while__symbol                  = new__symbol(cause, "while");
  this->return__symbol                 = new__symbol(cause, "return");
  
  this->bytecode_eq__symbol                 = new__symbol(cause, "bytecode:eq");
  this->bytecode_not__symbol                = new__symbol(cause, "bytecode:not");
  this->bytecode_and__symbol                = new__symbol(cause, "bytecode:and");
  this->bytecode_or__symbol                 = new__symbol(cause, "bytecode:or");
  this->bytecode_add__symbol                = new__symbol(cause, "bytecode:add");
  this->bytecode_negative__symbol           = new__symbol(cause, "bytecode:negative");
  this->bytecode_subtract__symbol           = new__symbol(cause, "bytecode:subtract");
  this->bytecode_multiply__symbol           = new__symbol(cause, "bytecode:multiply");
  this->bytecode_inverse__symbol            = new__symbol(cause, "bytecode:inverse");
  this->bytecode_divide__symbol             = new__symbol(cause, "bytecode:divide");
  this->bytecode_modulo__symbol             = new__symbol(cause, "bytecode:modulo");
  this->bytecode_increment__symbol          = new__symbol(cause, "bytecode:increment");
  this->bytecode_decrement__symbol          = new__symbol(cause, "bytecode:decrement");
  this->bytecode_numerically_equals__symbol = new__symbol(cause, "bytecode:numerically_equals");
  this->bytecode_less_than__symbol          = new__symbol(cause, "bytecode:less_than");
  this->bytecode_greater_than__symbol       = new__symbol(cause, "bytecode:greater_than");
  
  f2__primobject__file_handle__reinitialize_globalvars();
  f2__primobject__stream__reinitialize_globalvars();
  
  {
    this->stdin_stream__symbol = new__symbol(cause, "stdin");
    f2ptr file_handle = f2__file_handle__new(cause, f2integer__new(cause, STDIN_FILENO));
    this->stdin_stream = f2__file_stream__new(cause, file_handle);
    environment__add_var_value(cause, global_environment(), this->stdin_stream__symbol,  this->stdin_stream);
  }

  {
    this->stdout_stream__symbol = new__symbol(cause, "stdout");
    f2ptr file_handle = f2__file_handle__new(cause, f2integer__new(cause, STDOUT_FILENO));
    this->stdout_stream = f2__file_stream__new(cause, file_handle);
    environment__add_var_value(cause, global_environment(), this->stdout_stream__symbol, this->stdout_stream);
  }
  
  {
    this->stderr_stream__symbol = new__symbol(cause, "stderr");
    f2ptr file_handle = f2__file_handle__new(cause, f2integer__new(cause, STDERR_FILENO));
    this->stderr_stream = f2__file_stream__new(cause, file_handle);
    environment__add_var_value(cause, global_environment(), this->stderr_stream__symbol, this->stderr_stream);
  }
  
  this->type__symbol = new__symbol(cause, "type");
  
  this->trace_all_compiles__symbol = new__symbol(cause, "-trace_all_compiles-");
  
  this->create_event__symbol = new__symbol(cause, "create_event");
  this->read_event__symbol   = new__symbol(cause, "read_event");
  this->write_event__symbol  = new__symbol(cause, "write_event");
  
  this->ptype_integer__symbol                  = new__symbol(cause, "ptype_integer");
  this->ptype_double__symbol                   = new__symbol(cause, "ptype_double");
  this->ptype_float__symbol                    = new__symbol(cause, "ptype_float");
  this->ptype_pointer__symbol                  = new__symbol(cause, "ptype_pointer");
  this->ptype_cmutex__symbol                   = new__symbol(cause, "ptype_cmutex");
  this->ptype_creadwritelock__symbol           = new__symbol(cause, "ptype_creadwritelock");
  this->ptype_char__symbol                     = new__symbol(cause, "ptype_char");
  this->ptype_string__symbol                   = new__symbol(cause, "ptype_string");
  this->ptype_symbol__symbol                   = new__symbol(cause, "ptype_symbol");
  this->ptype_chunk__symbol                    = new__symbol(cause, "ptype_chunk");
  this->ptype_cons__symbol                     = new__symbol(cause, "ptype_cons");
  this->ptype_simple_array__symbol             = new__symbol(cause, "ptype_simple_array");
  this->ptype_larva__symbol                    = new__symbol(cause, "ptype_larva");
  this->ptype_mutable_array_pointer__symbol    = new__symbol(cause, "ptype_mutable_array_pointer");
  
  this->get__symbol     = new__symbol(cause, "get");
  this->set__symbol     = new__symbol(cause, "set");
  this->execute__symbol = new__symbol(cause, "execute");
  
  this->eq__symbol                           = new__symbol(cause, "eq");
  this->eq_hash_value__symbol                = new__symbol(cause, "eq_hash_value");
  this->equals__symbol                       = new__symbol(cause, "equals");
  this->equals_hash_value__symbol            = new__symbol(cause, "equals_hash_value");
  this->equals_hash_value__loop_free__symbol = new__symbol(cause, "equals_hash_value-loop_free");
  
  this->asterisk__symbol = new__symbol(cause, "*");
  
  this->terminal_print_with_frame__symbol = new__symbol(cause, "terminal_print_with_frame");
}

void funk2_globalenv__defragment__fix_pointers(funk2_globalenv_t* this) {
  // -- reinitialize --
  
  defragment__fix_pointer(this->f2_globalenv_c__cause__symbol);
  
  defragment__fix_pointer(this->f2_bytecodes_c__cause__symbol);
  defragment__fix_pointer(this->f2_ansi_c__cause__symbol);
  defragment__fix_pointer(this->f2_compile_c__cause__symbol);
  defragment__fix_pointer(this->f2_gmodule_c__cause__symbol);
  defragment__fix_pointer(this->f2_load_c__cause__symbol);
  defragment__fix_pointer(this->f2_memory_c__cause__symbol);
  defragment__fix_pointer(this->f2_primfunks_c__cause__symbol);
  defragment__fix_pointer(this->f2_primobject_environment_c__cause__symbol);
  defragment__fix_pointer(this->f2_primobject_frame_c__cause__symbol);
  defragment__fix_pointer(this->f2_primobject_ptypehash_c__cause__symbol);
  defragment__fix_pointer(this->f2_primobjects_c__cause__symbol);
  defragment__fix_pointer(this->f2_print_c__cause__symbol);
  defragment__fix_pointer(this->f2_processor_c__cause__symbol);
  defragment__fix_pointer(this->f2_pthread_c__cause__symbol);
  defragment__fix_pointer(this->f2_ptypes_c__cause__symbol);
  defragment__fix_pointer(this->f2_reader_c__cause__symbol);
  defragment__fix_pointer(this->f2_redblacktree_c__cause__symbol);
  defragment__fix_pointer(this->f2_repl_c__cause__symbol);
  defragment__fix_pointer(this->f2_scheduler_c__cause__symbol);
  defragment__fix_pointer(this->f2_signal_c__cause__symbol);
  defragment__fix_pointer(this->f2_socket_c__cause__symbol);
  defragment__fix_pointer(this->f2_swapmemory_c__cause__symbol);
  defragment__fix_pointer(this->f2_fiber_c__cause__symbol);
  defragment__fix_pointer(this->f2_time_c__cause__symbol);
  defragment__fix_pointer(this->f2_trace_c__cause__symbol);
  defragment__fix_pointer(this->f2_serialize_c__cause__symbol);
  defragment__fix_pointer(this->funk2_c__cause__symbol);

  defragment__fix_pointer(this->true__symbol);
  defragment__fix_pointer(this->quote__symbol);
  
  defragment__fix_pointer(this->backquote__list__symbol);
  defragment__fix_pointer(this->backquote__list_append__symbol);
  defragment__fix_pointer(this->comma__symbol);
  defragment__fix_pointer(this->cdr_comma__symbol);
  
  defragment__fix_pointer(this->funkvar__symbol);
  defragment__fix_pointer(this->define_funk__symbol);
  defragment__fix_pointer(this->mutatefunk__symbol);
  defragment__fix_pointer(this->define__symbol);
  defragment__fix_pointer(this->mutate__symbol);
  defragment__fix_pointer(this->and_rest__symbol);
  defragment__fix_pointer(this->apply__symbol);
  defragment__fix_pointer(this->globalize__symbol);
  defragment__fix_pointer(this->globalize_funk__symbol);
  defragment__fix_pointer(this->yield__symbol);
  defragment__fix_pointer(this->if__symbol);
  defragment__fix_pointer(this->bytecode__symbol);
  defragment__fix_pointer(this->rawcode__symbol);
  defragment__fix_pointer(this->while__symbol);
  defragment__fix_pointer(this->return__symbol);
  
  defragment__fix_pointer(this->bytecode_eq__symbol);
  defragment__fix_pointer(this->bytecode_not__symbol);
  defragment__fix_pointer(this->bytecode_and__symbol);
  defragment__fix_pointer(this->bytecode_or__symbol);
  defragment__fix_pointer(this->bytecode_add__symbol);
  defragment__fix_pointer(this->bytecode_negative__symbol);
  defragment__fix_pointer(this->bytecode_subtract__symbol);
  defragment__fix_pointer(this->bytecode_multiply__symbol);
  defragment__fix_pointer(this->bytecode_inverse__symbol);
  defragment__fix_pointer(this->bytecode_divide__symbol);
  defragment__fix_pointer(this->bytecode_modulo__symbol);
  defragment__fix_pointer(this->bytecode_increment__symbol);
  defragment__fix_pointer(this->bytecode_decrement__symbol);
  defragment__fix_pointer(this->bytecode_numerically_equals__symbol);
  defragment__fix_pointer(this->bytecode_less_than__symbol);
  defragment__fix_pointer(this->bytecode_greater_than__symbol);
    
  defragment__fix_pointer(this->stdin_stream__symbol);
  defragment__fix_pointer(this->stdin_stream);
  
  defragment__fix_pointer(this->stdout_stream__symbol);
  defragment__fix_pointer(this->stdout_stream);
  
  defragment__fix_pointer(this->stderr_stream__symbol);
  defragment__fix_pointer(this->stderr_stream);
  
  defragment__fix_pointer(this->type__symbol);
  
  defragment__fix_pointer(this->trace_all_compiles__symbol);
  
  defragment__fix_pointer(this->create_event__symbol);
  defragment__fix_pointer(this->read_event__symbol);
  defragment__fix_pointer(this->write_event__symbol);
  
  defragment__fix_pointer(this->ptype_integer__symbol);
  defragment__fix_pointer(this->ptype_double__symbol);
  defragment__fix_pointer(this->ptype_float__symbol);
  defragment__fix_pointer(this->ptype_pointer__symbol);
  defragment__fix_pointer(this->ptype_cmutex__symbol);
  defragment__fix_pointer(this->ptype_creadwritelock__symbol);
  defragment__fix_pointer(this->ptype_char__symbol);
  defragment__fix_pointer(this->ptype_string__symbol);
  defragment__fix_pointer(this->ptype_symbol__symbol);
  defragment__fix_pointer(this->ptype_chunk__symbol);
  defragment__fix_pointer(this->ptype_cons__symbol);
  defragment__fix_pointer(this->ptype_simple_array__symbol);
  defragment__fix_pointer(this->ptype_larva__symbol);
  defragment__fix_pointer(this->ptype_mutable_array_pointer__symbol);
  
  defragment__fix_pointer(this->get__symbol);
  defragment__fix_pointer(this->set__symbol);
  defragment__fix_pointer(this->execute__symbol);
  
  defragment__fix_pointer(this->eq__symbol);
  defragment__fix_pointer(this->eq_hash_value__symbol);
  defragment__fix_pointer(this->equals__symbol);
  defragment__fix_pointer(this->equals_hash_value__symbol);
  defragment__fix_pointer(this->equals_hash_value__loop_free__symbol);
  
  defragment__fix_pointer(this->asterisk__symbol);
  
  defragment__fix_pointer(this->terminal_print_with_frame__symbol);
  
  
  // -- initialize --
  
  
}

void funk2_globalenv__init(funk2_globalenv_t* this) {
  funk2_globalenv__reinit(this);

  f2ptr cause = f2_globalenv_c__cause__new(initial_cause());
  
  environment__add_var_value(cause, global_environment(), this->true__symbol,               this->true__symbol);
  environment__add_var_value(cause, global_environment(), this->trace_all_compiles__symbol, nil);
}

void funk2_globalenv__destroy(funk2_globalenv_t* this) {
}

f2ptr raw__c_source_file__cause__new(f2ptr cause, char* filename) {
  // we should use filename in a source-file cause type...
  f2ptr this = f2__cause__new_with_inherited_properties(cause, cause);
  never_gc(this);
  return this;
}

f2ptr              f2_globalenv_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_globalenv.c");}
f2ptr                   f2_ansi_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_ansi.c");}
f2ptr              f2_bytecodes_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_bytecodes.c");}
f2ptr                f2_compile_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_compile.c");}
f2ptr                f2_gmodule_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_gmodule.c");}
f2ptr                   f2_load_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_load.c");}
f2ptr                 f2_memory_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_memory.c");}
f2ptr              f2_primfunks_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_primfunks.c");}
f2ptr f2_primobject_environment_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_primobject_environment.c");}
f2ptr       f2_primobject_frame_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_primobject_frame.c");}
f2ptr   f2_primobject_ptypehash_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_primobject_ptypehash.c");}
f2ptr            f2_primobjects_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_primobjects.c");}
f2ptr                  f2_print_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_print.c");}
f2ptr              f2_processor_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_processor.c");}
f2ptr                f2_pthread_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_pthread.c");}
f2ptr                 f2_ptypes_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_ptypes.c");}
f2ptr                 f2_reader_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_reader.c");}
f2ptr           f2_redblacktree_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_redblacktree.c");}
f2ptr                   f2_repl_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_repl.c");}
f2ptr              f2_scheduler_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_scheduler.c");}
f2ptr                 f2_signal_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_signal.c");}
f2ptr                 f2_socket_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_socket.c");}
f2ptr             f2_swapmemory_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_swapmemory.c");}
f2ptr                  f2_fiber_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_fiber.c");}
f2ptr                   f2_time_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_time.c");}
f2ptr                  f2_trace_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_trace.c");}
f2ptr              f2_serialize_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "f2_serialize.c");}
f2ptr                     funk2_c__cause__new(f2ptr cause) {return raw__c_source_file__cause__new(cause, "funk2.c");}

f2ptr f2bool__new(uint raw_value) {return raw_value ? __funk2.globalenv.true__symbol : nil;}

void f2__globalenv__reinitialize_globalvars() {
  funk2_globalenv__reinit(&(__funk2.globalenv));
}

void f2__globalenv__defragment__fix_pointers() {
  funk2_globalenv__defragment__fix_pointers(&(__funk2.globalenv));
}

void f2__globalenv__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "globalenv", "", &f2__globalenv__reinitialize_globalvars, &f2__globalenv__defragment__fix_pointers);
  
  funk2_globalenv__init(&(__funk2.globalenv));
}


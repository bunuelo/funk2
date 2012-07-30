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

// funk2

void f2__initialize() {
  f2__module_registration__initialize();
  f2__redblacktree__initialize();
  f2__heap__initialize();
  f2__memory__preinitialize();
  f2__ptypes__initialize();
  f2__system_processor__initialize();
  f2__system_file_handler__initialize();
  
  // **********************************************************************************************************************************************************************************
  // ** 
  // ** Global environment is created from global vars and then these global vars are added to the global environment.
  // ** This requires:
  // **   1. global vars to be "reinitialized"
  // **   2. global environment is "initialized"
  // **   3. all packages besides global environment are "initialized" (including global environment prerequisite components, such as ptypehash, frame, and environment primobjects)
  // ** 
  {
    {
      f2__primobjects__preinitialize_globalvars();
      f2__cause__preinitialize_globalvars();
      f2__primobject__ptypehash__preinitialize_globalvars(); 
      f2__primobject_frame__preinitialize_globalvars();
    }
    f2__primobject_environment__initialize();
    f2__globalenv__initialize();
    f2__primobject__ptypehash__initialize();
    f2__primobject_frame__initialize();
  }
  // ** 
  // **********************************************************************************************************************************************************************************
  
  f2__memory__initialize();
  f2__primobjects__initialize();
  f2__primobject_tensor__initialize();
  f2__primobject_object__initialize();
  f2__primobject_object_type__initialize();
  f2__primobject_circular_buffer__initialize();
  f2__primobject_set__initialize();
  f2__primobject_list__initialize();
  f2__primobject_doublelinklist__initialize();
  f2__primobject__stream__initialize();
  f2__primobject__traced_cmutex__initialize();
  f2__primobject__fiber_trigger__initialize();
  f2__primobject__file_handle__initialize();
  f2__primcfunks__initialize();
  f2__virtual_processor_handler__initialize();
  f2__array__initialize();
  f2__reader__initialize();
  f2__compile__initialize();
  f2__fiber__initialize();
  f2__bytecodes__initialize();
  f2__bug__initialize();
  f2__signal__initialize();
  f2__load__initialize();
  f2__socket__initialize();
  f2__trace__initialize();
  f2__primfunks__errno__initialize();
  f2__primfunks__fcntl__initialize();
  f2__primfunks__ioctl__initialize();
  f2__processor__initialize();
  f2__scheduler__initialize();
  f2__funk2_node__initialize();
  f2__peer_command_server__initialize();
  f2__primfunks__locale__initialize();
  f2__ansi__initialize();
  f2__termios__initialize();
  f2__ptypes_object_slots__initialize();
  f2__primobject__dynamic_library__initialize();
  f2__gmodule__initialize();
  f2__string__initialize();
  f2__chunk__initialize();
  f2__print__initialize();
  f2__apropos__initialize();
  f2__object__initialize();
  f2__primobject_type_handler__initialize();
  f2__primobject_type__initialize();
  f2__sort__initialize();
  f2__management_thread__initialize();
  f2__simple_repl__initialize();
  f2__garbage_collector__initialize();
  f2__defragmenter__initialize();
  f2__frame_objects__initialize();
  f2__primobject_hash__initialize();
  f2__dlfcn__initialize();
  f2__cause__initialize();
  f2__zlib__initialize();
  f2__cpu__initialize();
  f2__time__initialize();
  f2__primobject_largeinteger__initialize();
  f2__primes__initialize();
  f2__number__initialize();
  f2__surrogate_parent__initialize();
  f2__graphviz__initialize();
  f2__primobject__redblacktree__initialize();
  f2__xmlrpc__initialize();
  f2__package__initialize();
  f2__package_handler__initialize();
  f2__graph__initialize();
  f2__graph_cluster__initialize();
  f2__graph_match_error_correcting__initialize();
  f2__terminal_print__initialize();
  f2__nil__initialize();
  f2__natural_language__initialize();
  f2__partial_order__initialize();
  f2__core_extension_funk__initialize();
  f2__core_extension__initialize_module();
  f2__larva__initialize();
  f2__optimize__initialize();
  f2__primobject__matrix__initialize();
}

#define u64_large_prime ((u64)12764787846358441471ull)

void funk2__init(funk2_t* this, int argc, char** argv) {
  setenv("UBUNTU_MENUPROXY", "0", 0);
  
  f2__status__initialize();
  
  this->exit_now = boolean__false;
  this->node_id  = raw__nanoseconds_since_1970() * u64_large_prime;
  this->event_id = 0;
  funk2_processor_mutex__init(&(this->event_id_cmutex));
  
  funk2_system_processor__init(&(this->system_processor));
  funk2_system_file_handler__init(&(this->system_file_handler));
  funk2_surrogate_parent__init(&(this->surrogate_parent));
  
  status("");
  status("****************************************************************");
  status("**** booting up funk2 p2p node (node_id=#x%016" X64__fstr_without_percent ") ****", this->node_id);
  status("****************************************************************");
  status("");
  
  status("  sizeof(f2ptr_t)                    = " u64__fstr, (u64)(sizeof(f2ptr_t)));
  status("  sizeof(ptype_block_t)              = " u64__fstr, (u64)(sizeof(ptype_block_t)));
  status("  sizeof(ptype_simple_array_block_t) = " u64__fstr, (u64)(sizeof(ptype_simple_array_block_t)));
  status("");
  
  funk2_system_processor__print_status(&(__funk2.system_processor));
  funk2_command_line__init(&(this->command_line), argc, argv);
  
  {
    int buffer__byte_num = 32768;
    u8 ip_addr[4] = {127, 0, 0, 1};
    int port_num = this->command_line.peer_command_server__port_num;
    
    funk2_peer_command_server__init(&(this->peer_command_server), buffer__byte_num);
    funk2_peer_command_server_new_port_result_t result = funk2_peer_command_server__add_new_server_port(&(this->peer_command_server), "", ip_addr, port_num, buffer__byte_num, buffer__byte_num);
    if (result != funk2_peer_command_server_new_port_result__success) {
      status("error setting up peer command server port.");
      //exit(-1);
    }
    client_id_t client_id;
    client_id__init(&client_id, (u8*)"", ip_addr, port_num);
    funk2_node_handler__init(&(this->node_handler), buffer__byte_num, buffer__byte_num);
    funk2_node_handler__add_node(&(this->node_handler), __funk2.node_id, &client_id);
  }
  
  funk2_memory__init(&(this->memory));
  funk2_garbage_collector__init(&(this->garbage_collector));
  funk2_garbage_collector__init_sets_from_memory(&(this->garbage_collector), &(this->memory));
  funk2_defragmenter__init(&(this->defragmenter));
  funk2_bytecode__init(&(this->bytecode));
  funk2_operating_system__init(&(this->operating_system));
  funk2_locale__init(&(this->locale));
  funk2_processor_thread_handler__init(&(this->processor_thread_handler));
  funk2_virtual_processor_handler__init(&(this->virtual_processor_handler), memory_pool_num);
  funk2_primobject_type_handler__init(&(this->primobject_type_handler));
  funk2_scheduler_thread_controller__init(&(this->scheduler_thread_controller));
  funk2_management_thread__init(&(this->management_thread));
  funk2_user_thread_controller__init(&(this->user_thread_controller));
  funk2_opengl__init(&(this->opengl));
  funk2_openglu__init(&(this->openglu));
  funk2_xxf86vm__init(&(this->xxf86vm));
  funk2_xlib__init(&(this->xlib));
  funk2_cpu__init(&(this->cpu));
  funk2_xmlrpc__init(&(this->xmlrpc));
  
  f2ptr cause = initial_cause();
  
  char* install__bootstrap_img__filename      = F2__INSTALL__BOOTSTRAP_IMG__FILENAME;
  char* compile__bootstrap_img__filename      = F2__COMPILE__BOOTSTRAP_IMG__FILENAME;
  char* compile__bootstrap_repl_img__filename = F2__COMPILE__BOOTSTRAP_REPL_IMG__FILENAME;
  char* other__bootstrap_img__filename        = "/mit/6.868/funk2/img/bootstrap.img";
  
  f2__initialize();
  
  funk2_primobject_type_handler__add_nil_primobject(           &(this->primobject_type_handler), cause);
  funk2_primobject_type_handler__add_builtin_ptype_primobjects(&(this->primobject_type_handler), cause);
  funk2_primobject_type_handler__add_builtin_primobjects(      &(this->primobject_type_handler), cause);
  funk2_primobject_type_handler__add_builtin_frame_objects(    &(this->primobject_type_handler), cause);
  
  // try to load the user bootstrap image
  if ((__funk2.command_line.bootstrap_image_filename == NULL) ||
      funk2_memory__load_image_from_file(&(__funk2.memory), __funk2.command_line.bootstrap_image_filename)) {
    // try to load the local bootstrap image
    if (funk2_memory__load_image_from_file(&(__funk2.memory), compile__bootstrap_img__filename)) {
      // try to load the default system-wide bootstrap image
      if (funk2_memory__load_image_from_file(&(__funk2.memory), install__bootstrap_img__filename)) {
	// if we can't load the default system-wide bootstrap image or a local bootstrap image, then we are in the middle of compiling and depending on compiling progress we can load this intermediate image.
	if (funk2_memory__load_image_from_file(&(__funk2.memory), compile__bootstrap_repl_img__filename)) {
	  // try to load the other bootstrap image
	  if (funk2_memory__load_image_from_file(&(__funk2.memory), other__bootstrap_img__filename)) {
	    status("warning: couldn't load \"%s\" or \"%s\" or \"%s\".", install__bootstrap_img__filename, compile__bootstrap_repl_img__filename, other__bootstrap_img__filename);
	    status("warning: starting a very simple hardcoded read-evaluate-print loop because no compiled images can be found.");
	  } else {
	    status("warning: couldn't load \"%s\" or \"%s\".", install__bootstrap_img__filename, other__bootstrap_img__filename);
	    status("warning: starting a very simple hardcoded read-evaluate-print loop because no compiled images can be found.");
	  }
	} else {
	  status("warning: couldn't load system-wide installed bootstrap image, \"%s\", so reverted to loading local bootstrap image, \"%s\"", install__bootstrap_img__filename, compile__bootstrap_img__filename);
	}
      }
    } else {
      status("warning: loading \"%s\" instead of loading \"%s\" because we are in a compile directory.", compile__bootstrap_repl_img__filename, install__bootstrap_img__filename);
    }
  } else {
    status("funk2 note: loading user bootstrap image \'%s\'.", __funk2.command_line.bootstrap_image_filename);
  }
  
  cause = f2__cause__new_with_inherited_properties(cause, nil);
  never_gc(cause);
  
  // try to find a boot function
  f2ptr boot_funk = environment__lookup_funkvar_value(cause, global_environment(), new__symbol(cause, "boot"));
  if (! raw__funkable__is_type(cause, boot_funk)) {
    status("warning: no boot function defined.");
    
    // load file specified by user on command line
    if (this->command_line.load_source_filename != NULL) {
      status("load_source_filename = '%s'.", this->command_line.load_source_filename);
      
      // try to find a nice user-friendly load
      f2ptr load_funk = environment__lookup_funkvar_value(cause, global_environment(), new__symbol(cause, "load"));
      if (raw__larva__is_type(cause, load_funk)) {
	status("couldn't find user-friendly load function, so trying to find primfunk:load.");
	// if we can't find a user-friendly load, then use this basic hardcoded one for compiling the user-friendly one.
	load_funk = environment__lookup_funkvar_value(cause, global_environment(), new__symbol(cause, "primfunk:load"));
	if (raw__larva__is_type(cause, load_funk)) {
	  f2__fiber__print(cause, nil, global_environment());
	  error(nil, "could not find primfunk:load for compiling user-friendly load.");
	} else {
	  status("found primfunk:load.");
	}
      } else {
	status("found user-friendly load.");
      }
      
      f2ptr args = f2list1__new(cause, new__string(cause, this->command_line.load_source_filename));
      
      // start a fiber executing the load
      f2__fiber_serial(cause,
		       cause,
		       nil,
		       global_environment(),
		       load_funk,
		       args);
      
    } else {
      
      if (! this->command_line.no_repl) {
	// unless the user has explicitely specified the "--no-repl" command-line option, try to find a nice user-friendly repl
	f2ptr repl_funk = environment__lookup_funkvar_value(cause, global_environment(), new__symbol(cause, "repl"));
	if (raw__larva__is_type(cause, repl_funk)) {
	  // if we can't find a user-friendly repl, then use this basic hardcoded one for compiling the user-friendly one.
	  repl_funk = environment__lookup_funkvar_value(cause, global_environment(), new__symbol(cause, "primfunk:simple_repl"));
	  if (raw__larva__is_type(cause, repl_funk)) {
	    error(nil, "funk2 main (raw__funkable__is_type(repl_funk)) assertion failed.");
	  }
	}
	
	// start a fiber executing the user read-eval-print loop
	f2__fiber_serial(cause,
			 cause,
			 nil,
			 global_environment(),
			 repl_funk,
			 nil);
      } else {
	printf("\nfunk2: skipping repl function because of --no-repl option.");
      }
      
    }
    
  } else {
    
    if (! this->command_line.no_boot) {
      // unless the user has specifically used the "--no-boot" command-line option, start a fiber executing the boot function
      f2__fiber_serial(cause,
		       cause,
		       nil,
		       global_environment(),
		       boot_funk,
		       nil);
    } else {
      printf("\nfunk2: skipping boot function because of --no-boot option.");
    }
    
  }
  
  {
    f2ptr result = f2__global_core_extension_handler__reset_to_boot_state(cause);
    if (raw__larva__is_type(cause, result)) {
      error(nil, "funk2: error resetting global core extension handler to boot state.");
    }
  }
  
  pause_gc();
  funk2_virtual_processor_handler__start_virtual_processors(&(this->virtual_processor_handler));
  resume_gc();
  
  status("bootstrapping complete.");
  this->memory.bootstrapping_mode = boolean__false;
}

void f2__destroy() {
  funk2__destroy(&__funk2);
  
  status("funk2: destroying scheduler.");
  f2__scheduler__destroy();
  status("funk2: destroying processor.");
  f2__processor__destroy();
  status("funk2: destroying memory.");
  f2__memory__destroy();
  status("funk2: destroying peer command server.");
  f2__peer_command_server__destroy();
  status("funk2: destroying funk2 node handler.");
  f2__funk2_node__destroy();
  status("funk2: destroying primfunks-locale.");
  f2__primfunks__locale__destroy();
  status("funk2: destroying ptypes.");
  f2__ptypes__destroy();
  status("funk2: destroying module registration.");
  f2__module_registration__destroy();
  status("funk2: destroying status.");
  f2__status__destroy();
}

void funk2__destroy(funk2_t* this) {
  status("");
  status("******************************************************************");
  status("**** shutting down funk2 p2p node (node_id=#x%016" X64__fstr_without_percent ") ****", this->node_id);
  status("******************************************************************");
  status("");
  
  {
    status("funk2__main: telling all user threads to exit.");
    this->user_thread_controller.please_wait = boolean__true;
    funk2_user_thread_controller__exit(&(this->user_thread_controller));
    this->user_thread_controller.please_wait = boolean__false;
  }
  
  funk2_virtual_processor_handler__destroy(&(this->virtual_processor_handler));
  
  funk2_memory__print_gc_stats(&(this->memory));
  
  funk2_primobject_type_handler__destroy(&(this->primobject_type_handler));
  funk2_locale__destroy(&(this->locale));
  funk2_operating_system__destroy(&(this->operating_system));
  funk2_bytecode__destroy(&(this->bytecode));
  funk2_defragmenter__destroy(&(this->defragmenter));
  funk2_garbage_collector__destroy(&(this->garbage_collector));
  funk2_memory__destroy(&(this->memory));  
  funk2_command_line__destroy(&(this->command_line));
  funk2_node_handler__destroy(&(this->node_handler));
  funk2_peer_command_server__destroy(&(this->peer_command_server));
  funk2_processor_thread_handler__destroy(&(this->processor_thread_handler));
  funk2_scheduler_thread_controller__destroy(&(this->scheduler_thread_controller));
  funk2_management_thread__destroy(&(this->management_thread));
  funk2_user_thread_controller__destroy(&(this->user_thread_controller));
  funk2_opengl__destroy(&(this->opengl));
  funk2_openglu__destroy(&(this->openglu));
  funk2_xxf86vm__destroy(&(this->xxf86vm));
  funk2_xlib__destroy(&(this->xlib));
  funk2_processor_mutex__destroy(&(this->event_id_cmutex));
  funk2_cpu__destroy(&(this->cpu));
  funk2_surrogate_parent__destroy(&(this->surrogate_parent));
  funk2_xmlrpc__destroy(&(this->xmlrpc));
  funk2_system_file_handler__destroy(&(this->system_file_handler));
  funk2_system_processor__destroy(&(this->system_processor));
}

boolean_t funk2__handle(funk2_t* this) {
  funk2_peer_command_server__handle_clients(            &(this->peer_command_server));  
  funk2_peer_command_server__flush_command_input_buffer(&(this->peer_command_server), 1);
  funk2_node_handler__handle_nodes(                     &(this->node_handler));
  funk2_memory__handle(                                 &(this->memory));
  funk2_garbage_collector__handle(                      &(this->garbage_collector));
  funk2_defragmenter__handle(                           &(this->defragmenter));
  funk2_management_thread__handle_user_threads(         &(this->management_thread));
  funk2_cpu__handle(                                    &(this->cpu));
  funk2_surrogate_parent__handle(                       &(this->surrogate_parent));
  
  raw__fast_spin_sleep_yield();
  return boolean__false; // should return true if we did something.
}

pthread_t separate_thread__thread;
boolean_t separate_thread__done_booting;

// see funk2_main.c for actual main function.
int funk2__main(funk2_t* this, int argc, char** argv) {
  // our main code position is our reference for where the funk core has been loaded in memory.
  __funk2.funk2_main_code_position = to_ptr(&funk2__main);
  funk2__init(this, argc, argv);
  
  separate_thread__done_booting = boolean__true;
  
  while ((! (this->exit_now)) || (! funk2_management_thread__command_list__is_empty(&(this->management_thread)))) {
    boolean_t did_something = funk2__handle(this);
    if (! did_something) {
      raw__spin_sleep_yield();
    }
  }
  status("funk2__main: exited main loop.");
  
  f2__destroy();
  
  return 0;
}

void* funk2__separate_thread_bootup(void* param) {
  int   argc = 2;
  char* argv[3] = {"libfunk2.la", "--no-boot", (char*)NULL};
  int result = funk2__main(&__funk2, argc, argv);
  printf("funk2__separate_thread_bootup note: funk2__main exited with result=%d.", result);
  return NULL;
}

void funk2__start_main_in_separate_thread() {
  separate_thread__done_booting = boolean__false;
  printf("\nfunk2: booting up funk2 in a separate thread.");
  pthread_create(&separate_thread__thread, NULL, funk2__separate_thread_bootup, NULL);
  while (! separate_thread__done_booting) {
    usleep(1);
  }
  printf("\nfunk2: done booting up.\n");
}

// this should be the only global variable in funk2.
funk2_t __funk2;


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

#include "funk2.h"

void f2__initialize() {
  f2__redblacktree__initialize();
  f2__memory__initialize();
  f2__ptypes__initialize();
  
  // **********************************************************************************************************************************************************************************
  // ** 
  // ** Global environment is created from global vars and then these global vars are added to the global environment.
  // ** This requires:
  // **   1. global vars to be "reinitialized"
  // **   2. global environment is "initialized"
  // **   3. all packages besides global environment are "initialized" (including global environment prerequisite components, such as hashtable, frame, and environment primobjects)
  // ** 
  pause_gc(); {
    {
      f2__primobjects__reinitialize_globalvars();
      f2__primobject_hashtable__reinitialize_globalvars(); 
      f2__primobject_frame__reinitialize_globalvars();
    }
    f2__primobject_environment__initialize();
    f2__globalenv__initialize();
    pause_gc(); f2__primobject_hashtable__initialize(); resume_gc(); try_gc();
    pause_gc(); f2__primobject_frame__initialize();     resume_gc(); try_gc();
  } resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  // ** 
  // **********************************************************************************************************************************************************************************
  
  pause_gc(); f2__primobjects__initialize();                 resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject__action__initialize();          resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject_tensor__initialize();           resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject_object__initialize();           resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject_object_type__initialize();      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject_circular_buffer__initialize();  resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject__semantic_graph__initialize();  resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject__stream__initialize();          resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject__text_buffer__initialize();     resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primcfunks__initialize();                  resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__reader__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__compile__initialize();                     resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__thread__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__bytecodes__initialize();                   resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__signal__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__load__initialize();                        resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__socket__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__trace__initialize();                       resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__serialize__initialize();                   resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__thought_process__initialize();             resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primfunks__errno__initialize();            resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primfunks__fcntl__initialize();            resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primfunks__ioctl__initialize();            resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__scheduler__initialize();                   resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__funk2_node__initialize();                  resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__peer_command_server__initialize();         resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primfunks__ioctl__initialize();            resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primfunks__locale__initialize();           resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__ansi__initialize();                        resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__termios__initialize();                     resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__ptypes__initialize__object_slots();        resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__blocks_world__initialize();                resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject__dynamic_library__initialize(); resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__dlfcn__initialize();                       resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__gmodule__initialize();                     resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__string__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__child_handler__initialize();               resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__apropos__initialize();                     resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__object__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject_type_handler__initialize();     resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__primobject_type__initialize();             resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__sort__initialize();                        resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
  pause_gc(); f2__search__initialize();                      resume_gc(); try_gc(); release__assert(! gc__is_disabled(), nil, "garbage collection should be enabled at this point.");
}

#define u64_large_prime ((u64)12764787846358441471ull)

void funk2__init(funk2_t* this, int argc, char** argv) {
  f2__status__initialize();
  
  this->node_id  = raw__nanoseconds_since_1970() * u64_large_prime;
  this->event_id = 0;
  funk2_processor_mutex__init(&(this->event_id_mutex));
  
  status("booting up funk2 p2p node (node_id=#x" X64__fstr ")", this->node_id);
  
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
  funk2_thought_process__init(&(this->thought_process));
  funk2_bytecode__init(&(this->bytecode));
  
  funk2_operating_system__init(&(this->operating_system));
  funk2_locale__init(&(this->locale));
  
  int event_buffer__byte_num = 32768;
  funk2_event_router__init(&(this->event_router), event_buffer__byte_num);
  
  funk2_child_process_handler__init(&(this->child_process_handler));
  funk2_processor_thread_handler__init(&(this->processor_thread_handler));
  
  funk2_primobject_type_handler__init(&(this->primobject_type_handler));
  
  f2ptr cause = initial_cause();
  
  char* install__bootstrap_img__filename      = F2__INSTALL__BOOTSTRAP_IMG__FILENAME;
  char* compile__bootstrap_img__filename      = F2__COMPILE__BOOTSTRAP_IMG__FILENAME;
  char* compile__bootstrap_repl_img__filename = F2__COMPILE__BOOTSTRAP_REPL_IMG__FILENAME;
  char* other__bootstrap_img__filename        = "/mit/6.868/funk2/img/bootstrap.img";
  

  f2__initialize();
  
  pause_gc();

  funk2_primobject_type_handler__add_builtin_ptype_primobjects(&(this->primobject_type_handler), cause);
  funk2_primobject_type_handler__add_builtin_primobjects(&(this->primobject_type_handler), cause);
  
  // try to load the default system-wide bootstrap image
  if (raw__memory_image__load(install__bootstrap_img__filename)) {
    // try to load the local bootstrap image
    if (raw__memory_image__load(compile__bootstrap_img__filename)) {
      // if we can't load the default system-wide bootstrap image or a local bootstrap image, then we are in the middle of compiling and depending on compiling progress we can load this intermediate image.
      if (raw__memory_image__load(compile__bootstrap_repl_img__filename)) {
	// try to load the other bootstrap image
	if (raw__memory_image__load(other__bootstrap_img__filename)) {
	  status("warning: couldn't load \"%s\" or \"%s\" or \"%s\".", install__bootstrap_img__filename, compile__bootstrap_repl_img__filename, other__bootstrap_img__filename);
	  status("warning: starting a very simple hardcoded read-evaluate-print loop because no compiled images can be found.");
	} else {
	  status("warning: couldn't load \"%s\" or \"%s\".", install__bootstrap_img__filename, other__bootstrap_img__filename);
	  status("warning: starting a very simple hardcoded read-evaluate-print loop because no compiled images can be found.");
	}
      } else {
	status("warning: we must be in a compile process because couldn't load \"%s\" so reverted to loading \"%s\"", install__bootstrap_img__filename, compile__bootstrap_repl_img__filename);
      }
    } else {
      status("warning: couldn't load system-wide installed bootstrap image, \"%s\", so reverted to loading local bootstrap image, \"%s\"", install__bootstrap_img__filename, compile__bootstrap_img__filename);
    }
  }
  
  cause = f2__cause__new_with_default_properties(cause);
  //cause = f2__cause__new_default_with_memory_tracing_on(cause);
  
  // try to find a boot function
  f2ptr boot_funk = environment__lookup_funkvar_value(cause, global_environment(), f2symbol__new(cause, strlen("boot"), (u8*)"boot"));
  if (! raw__funkable__is_type(cause, boot_funk)) {
    status("warning: no boot function defined.");
    
    // load file specified by user on command line
    if (this->command_line.load_source_filename != NULL) {
      
      // try to find a nice user-friendly load
      f2ptr load_funk = environment__lookup_funkvar_value(cause, global_environment(), f2symbol__new(cause, strlen("load"), (u8*)"load"));
      if (! raw__funkable__is_type(cause, load_funk)) {
	// if we can't find a user-friendly load, then use this basic hardcoded one for compiling the user-friendly one.
	load_funk = environment__lookup_funkvar_value(cause, global_environment(), f2symbol__new(cause, strlen("primfunk:load"), (u8*)"primfunk:load"));
      }
      release__assert(raw__funkable__is_type(cause, load_funk), nil, "funk2 main (raw__funkable__is_type(load_funk)) assertion failed.");
      
      f2ptr args = f2cons__new(cause, f2string__new(cause, strlen(this->command_line.load_source_filename), (u8*)this->command_line.load_source_filename), nil);
      
      // start a thread executing the user read-eval-print loop
      f2__thread(cause,
		 cause,
		 nil,
		 global_environment(),
		 load_funk,
		 args);
      
    } else {
      
      // try to find a nice user-friendly repl
      f2ptr repl_funk = environment__lookup_funkvar_value(cause, global_environment(), f2symbol__new(cause, strlen("repl"), (u8*)"repl"));
      if (! raw__funkable__is_type(cause, repl_funk)) {
	// if we can't find a user-friendly repl, then use this basic hardcoded one for compiling the user-friendly one.
	repl_funk = environment__lookup_funkvar_value(cause, global_environment(), f2symbol__new(cause, strlen("primfunk:repl"), (u8*)"primfunk:repl"));
      }
      release__assert(raw__funkable__is_type(cause, repl_funk), nil, "funk2 main (raw__funkable__is_type(repl_funk)) assertion failed.");
      
      // start a thread executing the user read-eval-print loop
      f2__thread(cause,
		 cause,
		 nil,
		 global_environment(),
		 repl_funk,
		 nil);
    }
    
  } else {
    // start a thread executing the boot function
    f2__thread(cause,
	       cause,
	       nil,
	       global_environment(),
	       boot_funk,
	       nil);
  }
  
  //pthread_t posix_thread;
  //pause_gc();
  //raw__memory_server__start_new_server_thread(cause, &posix_thread, f2integer__new(cause, 2222));
  //resume_gc();
  
  // start pthreads for each processor (starts user repl once bootstrapping is done   this->memory.bootstrapping_mode = boolean__false;)
  f2__scheduler__start_processors();
  this->memory.bootstrapping_mode = boolean__false;
  
  resume_gc();
}

void f2__destroy() {
  status("funk2: destroying scheduler.");
  f2__scheduler__destroy();
  status("funk2: destroying memory.");
  f2__memory__destroy();
  status("funk2: destroying peer command server.");
  f2__peer_command_server__destroy();
  status("funk2: destroying funk2 node handler.");
  f2__funk2_node__destroy();
  status("funk2: destroying primfunks-locale.");
  f2__primfunks__locale__destroy();
  status("funk2: destroying status.");
  f2__status__destroy();
}

void funk2__destroy(funk2_t* this) {
  print_bytecode_stats(stdout);
  funk2_memory__print_gc_stats(&(this->memory));
  
  funk2_primobject_type_handler__destroy(&(this->primobject_type_handler));
  funk2_event_router__destroy(&(this->event_router));
  funk2_locale__destroy(&(this->locale));
  funk2_operating_system__destroy(&(this->operating_system));
  funk2_bytecode__destroy(&(this->bytecode));
  funk2_thought_process__destroy(&(this->thought_process));
  funk2_memory__destroy(&(this->memory));  
  funk2_command_line__destroy(&(this->command_line));
  funk2_node_handler__destroy(&(this->node_handler));
  funk2_peer_command_server__destroy(&(this->peer_command_server));
  funk2_child_process_handler__destroy(&(this->child_process_handler));
  funk2_processor_thread_handler__destroy(&(this->processor_thread_handler));
  
  funk2_processor_mutex__destroy(&(this->event_id_mutex));
}

boolean_t funk2__handle(funk2_t* this) {
  funk2_peer_command_server__handle_clients(&(this->peer_command_server));  
  funk2_peer_command_server__flush_command_input_buffer(&(__funk2.peer_command_server), 1);
  funk2_node_handler__handle_nodes(&(this->node_handler));
  funk2_child_process_handler__handle_child_processes(&(this->child_process_handler));
  funk2_memory__handle(&(this->memory));
  //funk2_event_router__handle_input_events(&(this->event_router));
  //printf("\nYour parent is here."); fflush(stdout);
  // very primitive global reflection might go here if necessary... (maybe handle global process signals?)
  f2__sleep(1);
  return boolean__true;
}

int funk2__main(funk2_t* this, int argc, char** argv) {
  funk2__init(this, argc, argv);
  
  while (1) {
    boolean_t did_something = funk2__handle(this);
    if (! did_something) {
      f2__sleep(1000000);
    }
  }
  //int repl_result = f2__repl(main_thread);
  
  funk2__destroy(this);
  f2__destroy();
  
  return 0;
}

// this is the only global variable in funk2.
funk2_t __funk2;

int main(int argc, char** argv) {
  return funk2__main(&__funk2, argc, argv);
}


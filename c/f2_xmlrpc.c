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

#include "funk2.h"

#if defined(F2__XMLRPC_SUPPORTED)


xmlrpc_value* xmlrpc__sample_add(xmlrpc_env* envP, xmlrpc_value* paramArrayP, void* userData) {
  xmlrpc_int x, y, z;
  
  // Parse our argument array.
  xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &x, &y);
  if (envP->fault_occurred) {
    return NULL;
  }
  
  // Add our two numbers.
  z = x + y;
  
  // Return our result.
  return xmlrpc_build_value(envP, "i", z);
}

xmlrpc_server_shutdown_fn xmlrpc__request_shutdown;
void                      xmlrpc__request_shutdown(xmlrpc_env* const envP, void* const context, const char* const comment) {
  // You make this run by executing the system method
  // 'system.shutdown'.  This function is registered in the method
  // registry as the thing to call for that.
  int* terminationRequestedP = context;
  
  xmlrpc_env_init(envP);
  
  status("Abyss XMLRPC server termination requested: %s\n", comment);
  
  *terminationRequestedP = 1;
}

boolean_t funk2_xmlrpc_server__init(funk2_xmlrpc_server_t* this, int port_num) {
  this->port_num         = port_num;
  this->processor_thread = NULL;
  
  xmlrpc_env_init(&(this->env));
  
  this->registryP = xmlrpc_registry_new(&(this->env));
  
  xmlrpc_registry_add_method(&(this->env), (this->registryP), NULL, "sample.add", &xmlrpc__sample_add, NULL);
  
  xmlrpc_registry_set_shutdown(this->registryP, &xmlrpc__request_shutdown, &(this->termination_requested));
  
  if (! ServerCreate(&(this->abyssServer), "XmlRpcServer", this->port_num, NULL, NULL)) {
    return boolean__true; // failure
  }
  
  xmlrpc_server_abyss_set_handlers(&(this->abyssServer), this->registryP);
  
  // DANGER: ServerInit calls exit(1) on failure to open a port.  This exits the entire process.  (We may need to include our own hacked abyss server if we want to avoid this behavior.)
  ServerInit(&(this->abyssServer));
  
  this->termination_requested = 0;
  
  return boolean__false; // success
}

void funk2_xmlrpc_server__destroy(funk2_xmlrpc_server_t* this) {
  ServerFree(&(this->abyssServer));
}

void funk2_xmlrpc_server__handle(funk2_xmlrpc_server_t* this) {
  // This waits for the next connection, accepts it, reads the
  // HTTP POST request, executes the indicated RPC, and closes
  // the connection.
  ServerRunOnce(&(this->abyssServer));
}

boolean_t funk2_xmlrpc_server__termination_requested(funk2_xmlrpc_server_t* this) {
  return (this->termination_requested != 0);
}

void funk2_xmlrpc_server__handler_loop(funk2_xmlrpc_server_t* this) {
  while (! funk2_xmlrpc_server__termination_requested(this)) {
    status("Waiting for next RPC...\n");
    funk2_xmlrpc_server__handle(this);
  }
}

void* funk2_xmlrpc_server__start_handler_thread__helper(void* ptr) {
  funk2_xmlrpc_server_t* this = (funk2_xmlrpc_server_t*)ptr;
  status("Calling XMLRPC server handler loop in new thread.");
  funk2_xmlrpc_server__handler_loop(this);
  status("Finished XMLRPC server handler loop thread.");
  this->processor_thread = NULL;
  return NULL;
}

void funk2_xmlrpc_server__start_handler_thread(funk2_xmlrpc_server_t* this) {
  this->processor_thread = funk2_processor_thread_handler__add_new_processor_thread(&(__funk2.processor_thread_handler), &funk2_xmlrpc_server__start_handler_thread__helper, (void*)this);
}

void xmlrpc_print_fault_status(xmlrpc_env* env) {
  status("xmlrpc error: %s (%d)", env->fault_string, env->fault_code);
}

boolean_t funk2_xmlrpc__call_test(char* url) {
  xmlrpc_env     env;
  xmlrpc_client* clientP;
  xmlrpc_value*  resultP;
  int            sum;
  boolean_t      success = boolean__false;
  
  // Initialize our error-handling environment.
  xmlrpc_env_init(&env);
  
  xmlrpc_client_setup_global_const(&env);
  
  xmlrpc_client_create(&env, XMLRPC_CLIENT_NO_FLAGS, "Funk2 XML-RPC Client", "2.11.0", NULL, 0,
		       &clientP);
  if (env.fault_occurred) {
    xmlrpc_print_fault_status(&env);
  } else {
    
    {
      xmlrpc_server_info* serverInfoP;
      xmlrpc_value*       paramArrayP;
      
      serverInfoP = xmlrpc_server_info_new(&env, url);
      
      paramArrayP = xmlrpc_array_new(&env);
      
      {
	xmlrpc_value* addend1P = xmlrpc_int_new(&env, 5);
	xmlrpc_value* addend2P = xmlrpc_int_new(&env, 7);
	
	xmlrpc_array_append_item(&env, paramArrayP, addend1P);
	xmlrpc_array_append_item(&env, paramArrayP, addend2P);
	
	xmlrpc_DECREF(addend1P);
	xmlrpc_DECREF(addend2P);
      }
      
      xmlrpc_client_call2(&env, clientP, serverInfoP, "sample.add",
			  paramArrayP, &resultP);
      
      xmlrpc_DECREF(paramArrayP);
      xmlrpc_server_info_free(serverInfoP);
    }
    
    // Get our sum and print it out.
    xmlrpc_read_int(&env, resultP, &sum);
    if (env.fault_occurred) {
      xmlrpc_print_fault_status(&env);
    } else {
      printf("The sum is %d\n", sum);
      success = boolean__true;
    }
    
    // Dispose of our result value.
    xmlrpc_DECREF(resultP);
    
    // Clean up our error-handling environment.
    xmlrpc_env_clean(&env);
    
    xmlrpc_client_destroy(clientP);
  }
  
  xmlrpc_client_teardown_global_const();
  return success;
}

#endif // F2__XMLRPC_SUPPORTED

void funk2_xmlrpc__init(funk2_xmlrpc_t* this) {
  this->servers = NULL;
}

void funk2_xmlrpc__destroy(funk2_xmlrpc_t* this) {
  funk2_xmlrpc_server_list_t* next;
  funk2_xmlrpc_server_list_t* iter = this->servers;
  while (iter) {
    next = iter->next;
    funk2_xmlrpc_server_t* server = &(iter->server);
    funk2_xmlrpc_server__destroy(server);
    f2__free(to_ptr(iter));
    iter = next;
  }
}

void funk2_xmlrpc__handle_destroying_dead_servers(funk2_xmlrpc_t* this) {
  funk2_xmlrpc_server_list_t* prev = NULL;
  funk2_xmlrpc_server_list_t* next;
  funk2_xmlrpc_server_list_t* iter = this->servers;
  while (iter) {
    next = iter->next;
    funk2_xmlrpc_server_t* server = &(iter->server);
    if (server->processor_thread == NULL) {
      status("Destroying dead XMLRPC server on port " u64__fstr ".", server->port_num);
      funk2_xmlrpc_server__destroy(server);
      f2__free(to_ptr(iter));
      if (prev) {
	prev->next    = next;
      } else {
	this->servers = next;
      }
    }
    prev = iter;
    iter = next;
  }
}

void funk2_xmlrpc__handle(funk2_xmlrpc_t* this) {
  funk2_xmlrpc__handle_destroying_dead_servers(this);
}

funk2_xmlrpc_server_t* funk2_xmlrpc__create_new_server(funk2_xmlrpc_t* this, int port_num) {
#if defined(F2__XMLRPC_SUPPORTED)
  funk2_xmlrpc_server_list_t* new_server_node = (funk2_xmlrpc_server_list_t*)from_ptr(f2__malloc(sizeof(funk2_xmlrpc_server_list_t)));
  boolean_t server_initialization_failure = funk2_xmlrpc_server__init(&(new_server_node->server), port_num);
  if (server_initialization_failure) {
    return NULL; // failure
  }
  funk2_xmlrpc_server__start_handler_thread(&(new_server_node->server));
  new_server_node->next = this->servers;
  this->servers = new_server_node;
  return &(new_server_node->server); // success
#else
  status(  "funk2 warning: XMLRPC support is not compiled in this install of funk2.");
  printf("\nfunk2 warning: XMLRPC support is not compiled in this install of funk2."); fflush(stdout);
  return NULL; // failure
#endif // F2__XMLRPC_SUPPORTED
}

boolean_t raw__xmlrpc__create_new_server(u64 port_num) {
  return (funk2_xmlrpc__create_new_server(&(__funk2.xmlrpc), port_num) != NULL);
}

f2ptr f2__xmlrpc__create_new_server(f2ptr cause, f2ptr port_num) {
  if (! raw__integer__is_type(cause, port_num)) {
    return f2larva__new(cause, 1, nil);
  }
  u64 port_num__i = f2integer__i(port_num, cause);
  return f2bool__new(raw__xmlrpc__create_new_server(port_num__i));
}
def_pcfunk1(xmlrpc__create_new_server, port_num, return f2__xmlrpc__create_new_server(this_cause, port_num));


boolean_t raw__xmlrpc__call_test(f2ptr cause, f2ptr url) {
#if defined(F2__XMLRPC_SUPPORTED)
  u64 url__length = raw__string__length(cause, url);
  u8* url__str    = (u8*)alloca(url__length + 1);
  raw__string__str_copy(cause, url, url__str);
  url__str[url__length] = 0;
  return funk2_xmlrpc__call_test((char*)url__str);
#else
  status(  "funk2 warning: XMLRPC support is not compiled in this install of funk2.");
  printf("\nfunk2 warning: XMLRPC support is not compiled in this install of funk2."); fflush(stdout);
  return boolean__false; // failure
#endif // F2__XMLRPC_SUPPORTED
}

f2ptr f2__xmlrpc__call_test(f2ptr cause, f2ptr url) {
  if (! raw__string__is_type(cause, url)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2bool__new(raw__xmlrpc__call_test(cause, url));
}
def_pcfunk1(xmlrpc__call_test, url, return f2__xmlrpc__call_test(cause, url));


// **

void f2__xmlrpc__reinitialize_globalvars() {
}

void f2__xmlrpc__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "xmlrpc", "", &f2__xmlrpc__reinitialize_globalvars);
  
  f2__xmlrpc__reinitialize_globalvars();
  
  f2__primcfunk__init__1(xmlrpc__create_new_server, port_num, "creates a test xmlrpc server with a sample.add RPC function that takes two integers as arguments.");
}


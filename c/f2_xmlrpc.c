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

void funk2_xmlrpc_server__init(funk2_xmlrpc_server_t* this, int port_num) {
  this->port_num = port_num;
  
  xmlrpc_env_init(&(this->env));
  
  this->registryP = xmlrpc_registry_new(&(this->env));
  
  xmlrpc_registry_add_method(&(this->env), (this->registryP), NULL, "sample.add", &xmlrpc__sample_add, NULL);
  
  xmlrpc_registry_set_shutdown(this->registryP, &xmlrpc__request_shutdown, &(this->termination_requested));
  
  ServerCreate(&(this->abyssServer), "XmlRpcServer", this->port_num, NULL, NULL);
  
  xmlrpc_server_abyss_set_handlers(&(this->abyssServer), this->registryP);
  
  ServerInit(&(this->abyssServer));
  
  //setupSignalHandlers();
  
  this->termination_requested = 0;
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

void funk2_xmlrpc_server__main() {
  int                   port_num = 4545;
  funk2_xmlrpc_server_t xmlrpc_server;
  funk2_xmlrpc_server__init(&xmlrpc_server, port_num);
  funk2_xmlrpc_server__handler_loop(&xmlrpc_server);
  funk2_xmlrpc_server__destroy(&xmlrpc_server);
}

void* funk2_xmlrpc_server__start_handler_thread__helper(void* ptr) {
  funk2_xmlrpc_server_t* this = (funk2_xmlrpc_server_t*)ptr;
  status("Calling XMLRPC server handler loop in new thread.");
  funk2_xmlrpc_server__handler_loop(this);
  status("Finished XMLRPC server handler loop thread.");
  return NULL;
}

void funk2_xmlrpc_server__start_handler_thread(funk2_xmlrpc_server_t* this) {
  funk2_processor_thread__init(&(this->processor_thread), funk2_xmlrpc_server__start_handler_thread__helper, this);
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

funk2_xmlrpc_server_t* funk2_xmlrpc__create_new_server(funk2_xmlrpc_t* this, int port_num) {
#if defined(F2__XMLRPC_SUPPORTED)
  funk2_xmlrpc_server_list_t* new_server_node = (funk2_xmlrpc_server_list_t*)from_ptr(f2__malloc(sizeof(funk2_xmlrpc_server_list_t)));
  funk2_xmlrpc_server__init(&(new_server_node->server), port_num);
  funk2_xmlrpc_server__start_handler_thread(&(new_server_node->server));
  new_server_node->next = this->servers;
  this->servers = new_server_node;
  return &(new_server_node->server);
#else
  status(  "funk2 warning: XMLRPC support is not compiled in this install of funk2.");
  printf("\nfunk2 warning: XMLRPC support is not compiled in this install of funk2."); fflush(stdout);
  return NULL;
#endif // F2__XMLRPC_SUPPORTED
}

// **

void f2__xmlrpc__reinitialize_globalvars() {
}

void f2__xmlrpc__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "xmlrpc", "", &f2__xmlrpc__reinitialize_globalvars);
  
  f2__xmlrpc__reinitialize_globalvars();
  
}


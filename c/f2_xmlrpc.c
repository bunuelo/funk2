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


static xmlrpc_value *
sample_add(xmlrpc_env *   const envP, 
           xmlrpc_value * const paramArrayP,
           void *         const userData) {
    
    xmlrpc_int x, y, z;

    /* Parse our argument array. */
    xmlrpc_decompose_value(envP, paramArrayP, "(ii)", &x, &y);
    if (envP->fault_occurred)
        return NULL;

    /* Add our two numbers. */
    z = x + y;

    /* Return our result. */
    return xmlrpc_build_value(envP, "i", z);
}



static xmlrpc_server_shutdown_fn requestShutdown;

static void
requestShutdown(xmlrpc_env * const envP,
                void *       const context,
                const char * const comment) {

    /* You make this run by executing the system method
       'system.shutdown'.  This function is registered in the method
       registry as the thing to call for that.
    */
    int * const terminationRequestedP = context;

    xmlrpc_env_init(envP);

    fprintf(stderr, "Termination requested: %s\n", comment);
    
    *terminationRequestedP = 1;
}



int 
main(int           const argc, 
     const char ** const argv) {

    TServer abyssServer;
    xmlrpc_registry * registryP;
    xmlrpc_env env;
    int terminationRequested;  /* A boolean value */

    if (argc-1 != 1) {
        fprintf(stderr, "You must specify 1 argument:  The TCP port number "
                "on which to listen for XML-RPC calls.  "
                "You specified %d.\n",  argc-1);
        exit(1);
    }
    
    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);

    xmlrpc_registry_add_method(
        &env, registryP, NULL, "sample.add", &sample_add, NULL);

    xmlrpc_registry_set_shutdown(registryP,
                                 &requestShutdown, &terminationRequested);

    ServerCreate(&abyssServer, "XmlRpcServer", atoi(argv[1]), NULL, NULL);
    
    xmlrpc_server_abyss_set_handlers(&abyssServer, registryP);

    ServerInit(&abyssServer);

    //setupSignalHandlers();

    terminationRequested = 0;

    while (!terminationRequested) {
        printf("Waiting for next RPC...\n");

        ServerRunOnce(&abyssServer);
            /* This waits for the next connection, accepts it, reads the
               HTTP POST request, executes the indicated RPC, and closes
               the connection.
            */
    }

    ServerFree(&abyssServer);
    
    return 0;
}


#endif // F2__XMLRPC_SUPPORTED

// **

void f2__xmlrpc__reinitialize_globalvars() {
}

void f2__xmlrpc__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "xmlrpc", "", &f2__xmlrpc__reinitialize_globalvars);
  
  f2__xmlrpc__reinitialize_globalvars();
  
}


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

static void
printPeerIpAddr(TSession * const abyssSessionP) {

    struct abyss_unix_chaninfo * channelInfoP;
    struct sockaddr_in * sockAddrInP;
    unsigned char * ipAddr;  /* 4 byte array */

    SessionGetChannelInfo(abyssSessionP, (void*)&channelInfoP);

    sockAddrInP = (struct sockaddr_in *) &channelInfoP->peerAddr;

    ipAddr = (unsigned char *)&sockAddrInP->sin_addr.s_addr;

    printf("RPC is from IP address %u.%u.%u.%u\n",
           ipAddr[0], ipAddr[1], ipAddr[2], ipAddr[3]);
}



static xmlrpc_value *
sample_add(xmlrpc_env *   const envP, 
           xmlrpc_value * const paramArrayP,
           void *         const serverInfo,
           void *         const channelInfo) {
    
    xmlrpc_int x, y, z;

    printPeerIpAddr(channelInfo);

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
requestShutdown(xmlrpc_env * const faultP,
                void *       const context,
                const char * const comment,
                void *       const callInfo) {

    /* You make this run by executing the system method
       'system.shutdown'.  This function is registered in the method
       registry as the thing to call for that.
    */
    int * const terminationRequestedP = context;
    TSession * const abyssSessionP = callInfo;

    xmlrpc_env_init(faultP);

    fprintf(stderr, "Termination requested: %s\n", comment);

    printPeerIpAddr(abyssSessionP);
    
    *terminationRequestedP = 1;
}



int 
xmlrpc__main(int           const argc, 
	     const char ** const argv) {
  
    struct xmlrpc_method_info3 const methodInfo = {
        .methodName     = "sample.add",
        .methodFunction = &sample_add,
        .serverInfo = NULL
    };
    TServer abyssServer;
    xmlrpc_registry * registryP;
    xmlrpc_env env;
    int terminationRequested;  /* A boolean value */
    const char * error;

    if (argc-1 != 1) {
        fprintf(stderr, "You must specify 1 argument:  The TCP port number "
                "on which to listen for XML-RPC calls.  "
                "You specified %d.\n",  argc-1);
        exit(1);
    }

    AbyssInit(&error);
    
    xmlrpc_env_init(&env);

    registryP = xmlrpc_registry_new(&env);

    xmlrpc_registry_add_method3(&env, registryP, &methodInfo);

    xmlrpc_registry_set_shutdown(registryP,
                                 &requestShutdown, &terminationRequested);

    ServerCreate(&abyssServer, "XmlRpcServer", atoi(argv[1]), NULL, NULL);
    
    xmlrpc_server_abyss_set_handlers2(&abyssServer, "/RPC2", registryP);

    ServerInit(&abyssServer);

    setupSignalHandlers();

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

    AbyssTerm();

    return 0;
}

#endif // F2__XMLRPC_SUPPORTED

// **

void f2__xmlrpc__reinitialize_globalvars() {
}

void f2__xmlrpc__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "xmlrpc", "", &f2__xmlrpc__reinitialize_globalvars);
  
  f2__xmlrpc__reinitialize_globalvars();
  
}


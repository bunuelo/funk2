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

#ifndef F2__XMLRPC__H
#define F2__XMLRPC__H

#include "f2_global.h"

// funk2_xmlrpc

typedef struct funk2_xmlrpc_s {
#if defined(F2__XMLRPC_SUPPORTED)
  xmlrpc_env xmlrpc_environment;
#endif // F2__XMLRPC_SUPPORTED
} funk2_xmlrpc_t;

void funk2_xmlrpc__init(   funk2_xmlrpc_t* this);
void funk2_xmlrpc__destroy(funk2_xmlrpc_t* this);

// **

void f2__xmlrpc__initialize();

#endif // F2__XMLRPC__H


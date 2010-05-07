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

xmlrpc_value* funk2_xmlrpc__create_xmlrpc_value_from_exp(xmlrpc_env* env, f2ptr cause, f2ptr exp) {
  if (exp == nil) {
    return xmlrpc_nil_new(env);
  } else if (raw__integer__is_type(cause, exp)) {
    s64 i = f2integer__i(exp, cause);
    if ((i <   0x100000000) &&
	(i >= -0x100000000)) {
      // can be represented in 32 bits.
      s32 i32 = (s32)i;
      return xmlrpc_int_new(env, i32);
    } else {
      // requires full 64 bits precision.
#if defined(XMLRPC_HAVE_I8)
      return xmlrpc_i8_new(env, i);
#else
      return NULL;
#endif // XMLRPC_HAVE_I8
    }
  } else if (raw__double__is_type(cause, exp)) {
    double d = f2double__d(exp, cause);
    return xmlrpc_double_new(env, d);
  } else if (raw__float__is_type(cause, exp)) {
    float  f = f2float__f(exp, cause);
    double d = (double)f;
    return xmlrpc_double_new(env, d);
  } else if (raw__symbol__is_type(cause, exp)) {
    u64 exp__length = f2symbol__length(exp, cause);
    u8* exp__str    = (u8*)alloca(exp__length + 1);
    raw__symbol__str_copy(cause, exp, exp__str);
    exp__str[exp__length] = 0;
    return xmlrpc_string_new_lp(env, exp__length, (char*)exp__str);
  } else if (raw__string__is_type(cause, exp)) {
    u64 exp__length = f2string__length(exp, cause);
    u8* exp__str    = (u8*)alloca(exp__length + 1);
    raw__string__str_copy(cause, exp, exp__str);
    exp__str[exp__length] = 0;
    return xmlrpc_string_new_lp(env, exp__length, (char*)exp__str);
  } else if (raw__time__is_type(cause, exp)) {
    f2ptr  nanoseconds_since_1970    = f2__time__nanoseconds_since_1970(cause, exp);
    u64    nanoseconds_since_1970__i = f2integer__i(nanoseconds_since_1970, cause);
    u64    seconds_since_1970        = nanoseconds_since_1970__i / nanoseconds_per_second;
    time_t seconds_since_1970__time  = (time_t)seconds_since_1970;
    return xmlrpc_datetime_new_sec(env, seconds_since_1970__time);
  } else if (raw__ptypehash__is_type(cause, exp)) {
    xmlrpc_value* new_struct = xmlrpc_struct_new(env);
    ptypehash__iteration(cause, exp, key, value,
			 xmlrpc_value* new_key   = funk2_xmlrpc__create_xmlrpc_value_from_exp(env, cause, key);
			 if (new_key == NULL) {
			   xmlrpc_DECREF(new_struct);
			   return NULL;
			 }
			 xmlrpc_value* new_value = funk2_xmlrpc__create_xmlrpc_value_from_exp(env, cause, value);
			 if (new_value == NULL) {
			   xmlrpc_DECREF(new_struct);
			   return NULL;
			 }
			 xmlrpc_struct_set_value_v(env, new_struct, new_key, new_value);
			 xmlrpc_DECREF(new_key);
			 xmlrpc_DECREF(new_value);
			 );
    return new_struct;
  } else if (raw__array__is_type(cause, exp)) {
    xmlrpc_value* new_array = xmlrpc_array_new(env);
    u64 exp__length = raw__array__length(cause, exp);
    {
      u64 index;
      for (index = 0; index < exp__length; index ++) {
	f2ptr         subexp     = raw__array__elt(cause, exp, index);
	xmlrpc_value* new_subexp = funk2_xmlrpc__create_xmlrpc_value_from_exp(env, cause, subexp);
	if (new_subexp == NULL) {
	  xmlrpc_DECREF(new_array);
	  return NULL;
	}
	xmlrpc_array_append_item(env, new_array, new_subexp);
	xmlrpc_DECREF(new_subexp);
      }
    }
    return new_array;
  } else {
    return NULL;
  }
}

f2ptr funk2_xmlrpc__new_exp_from_xmlrpc_value(xmlrpc_env* env, f2ptr cause, xmlrpc_value* value) {
  xmlrpc_type type = xmlrpc_value_type(value);
  switch(type) {
  case XMLRPC_TYPE_DEAD:    // not a value
    return f2larva__new(cause, 1, nil);
  case XMLRPC_TYPE_NIL:    // empty value, eg NULL
    return nil;
  case XMLRPC_TYPE_BASE64: { // base64 value, eg binary data
    size_t         value__length;
    unsigned char* value__str;
    xmlrpc_read_base64(env,
		       value,
		       &value__length,
		       (const unsigned char**)&value__str);
    f2ptr new_chunk = f2chunk__new(cause, value__length, value__str);
    free(value__str);
    return new_chunk;
  }
  case XMLRPC_TYPE_BOOL: {// boolean  [0 | 1]
    xmlrpc_bool bool_value;
    xmlrpc_read_bool(env, value, &bool_value);
    return f2bool__new(bool_value);
  }
  case XMLRPC_TYPE_DATETIME: { // datetime [ISO8601 | time_t]
    time_t seconds_since_1970;
    xmlrpc_read_datetime_sec(env, value, &seconds_since_1970);
    u64 nanoseconds_since_1970 = ((u64)seconds_since_1970) * nanoseconds_per_second;
    return f2time__new(cause, f2integer__new(cause, nanoseconds_since_1970));
  }
  case XMLRPC_TYPE_DOUBLE: { // double / floating point
    xmlrpc_double double_value;
    xmlrpc_read_double(env, value, &double_value);
    double d = (double)double_value;
    return f2double__new(cause, d);
  }
  case XMLRPC_TYPE_INT: {    // integer
    s64 i;
#if defined(XMLRPC_HAVE_I8)
    long long i8_value;
    xmlrpc_read_i8(env, value, &i8_value);
    i = (s64)i8_value;
#else
    int int_value;
    xmlrpc_read_int(env, value, &int_value);
    i = (s64)int_value;
#endif // XMLRPC_HAVE_I8
    return f2integer__new(cause, i);
  }
  case XMLRPC_TYPE_STRING: { // string
    size_t string__length;
    char*  string__str;
    xmlrpc_read_string_lp(env, value, &string__length, (const char**)&string__str);
    f2ptr new_string = f2string__new(cause, string__length, (u8*)string__str);
    free(string__str);
    return new_string;
  }
  case XMLRPC_TYPE_ARRAY: {  // vector array
    int array__size;
    array__size = xmlrpc_array_size(env, value);
    f2ptr new_array = raw__array__new(cause, array__size);
    {
      int index;
      for (index = 0; index < array__size; index ++) {
	xmlrpc_value* subexp;
	xmlrpc_array_read_item(env, value, index, &subexp);
	f2ptr new_subexp = funk2_xmlrpc__new_exp_from_xmlrpc_value(env, cause, subexp);
	if (raw__larva__is_type(cause, new_subexp)) {
	  return new_subexp;
	}
	raw__array__elt__set(cause, new_array, index, new_subexp);
      }
    }
    return new_array;
  }
  case XMLRPC_TYPE_STRUCT: { // vector struct
    int struct__size = xmlrpc_struct_size(env, value);
    f2ptr new_frame = f2__frame__new(cause);
    {
      int index;
      for (index = 0; index < struct__size; index ++) {
	xmlrpc_value* member_key;
	xmlrpc_value* member_value;
	xmlrpc_struct_read_member(env, value, index, &member_key, &member_value);
	f2ptr new_key = funk2_xmlrpc__new_exp_from_xmlrpc_value(env, cause, member_key);
	if (raw__larva__is_type(cause, new_key)) {
	  return new_key;
	}
	f2ptr new_value = funk2_xmlrpc__new_exp_from_xmlrpc_value(env, cause, member_value);
	if (raw__larva__is_type(cause, new_value)) {
	  return new_value;
	}
	f2__frame__add_var_value(cause, new_frame, new_key, new_value);
      }
    }
    return new_frame;
  }
  case XMLRPC_TYPE_C_PTR:
    return f2larva__new(cause, 12, nil);
  }
}

f2ptr f2__xmlrpc__apply(f2ptr cause, f2ptr url, f2ptr funkname, f2ptr arguments) {
  if ((! raw__string__is_type(cause, url)) ||
      ((! raw__string__is_type(cause, funkname)) && (! raw__symbol__is_type(cause, funkname)))) {
    return f2larva__new(cause, 1, nil);
  }
  
  u64 url__length = raw__string__length(cause, url);
  u8* url__str    = (u8*)alloca(url__length + 1);
  raw__string__str_copy(cause, url, url__str);
  url__str[url__length] = 0;
  
  u64 funkname__length;
  u8* funkname__str;
  if (raw__string__is_type(cause, funkname)) {
    funkname__length = raw__string__length(cause, funkname);
    funkname__str    = (u8*)alloca(funkname__length + 1);
    raw__string__str_copy(cause, funkname, funkname__str);
    funkname__str[funkname__length] = 0;
  } else if (raw__symbol__is_type(cause, funkname)) {
    funkname__length = raw__symbol__length(cause, funkname);
    funkname__str    = (u8*)alloca(funkname__length + 1);
    raw__symbol__str_copy(cause, funkname, funkname__str);
    funkname__str[funkname__length] = 0;
  } else {
    error(nil, "shouldn't get here because of type checking above.");
  }
  
  xmlrpc_env     env;
  xmlrpc_client* clientP;
  xmlrpc_value*  resultP;
  int            sum;
  boolean_t      success      = boolean__false;
  f2ptr          return_value = nil;
  
  // Initialize our error-handling environment.
  xmlrpc_env_init(&env);
  
  xmlrpc_client_setup_global_const(&env);
  
  xmlrpc_client_create(&env, XMLRPC_CLIENT_NO_FLAGS, "Funk2 XML-RPC Client", "2.11.0", NULL, 0,
		       &clientP);
  if (env.fault_occurred) {
    xmlrpc_print_fault_status(&env);
  } else {
    
    boolean_t call_successful_so_far = boolean__true;
    {
      xmlrpc_server_info* serverInfoP;
      xmlrpc_value*       argument_array;
      
      serverInfoP = xmlrpc_server_info_new(&env, (char*)url__str);
      
      argument_array = xmlrpc_array_new(&env);
      
      {
	f2ptr iter = arguments;
	while (iter && call_successful_so_far) {
	  f2ptr exp = f2__first(cause, iter);
	  {
	    xmlrpc_value* new_exp = funk2_xmlrpc__create_xmlrpc_value_from_exp(&env, cause, exp);
	    if (new_exp == NULL) {
	      call_successful_so_far = boolean__false;
	    } else {
	      xmlrpc_array_append_item(&env, argument_array, new_exp);
	      xmlrpc_DECREF(new_exp);
	    }
	  }
	  iter = f2__next(cause, iter);
	}
      }
      if (call_successful_so_far) {
	xmlrpc_client_call2(&env, clientP, serverInfoP, (char*)funkname__str,
			    argument_array, &resultP);
	
	if (env.fault_occurred) {
	  xmlrpc_print_fault_status(&env);
	  call_successful_so_far = boolean__false;
	}
      }
      xmlrpc_DECREF(argument_array);
      xmlrpc_server_info_free(serverInfoP);
    }
    
    if (call_successful_so_far) {
      return_value = funk2_xmlrpc__new_exp_from_xmlrpc_value(env, cause, resultP);
      
      // Dispose of our result value.
      xmlrpc_DECREF(resultP);
    }
    
    // Clean up our error-handling environment.
    xmlrpc_env_clean(&env);
    
    xmlrpc_client_destroy(clientP);
  }
  
  xmlrpc_client_teardown_global_const();
  
  if (! success) {
    return f2larva__new(cause, 5533, nil);
  }
  return return_value;
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


def_pcfunk3(xmlrpc__apply, url, funkname, arguments, return f2__xmlrpc__apply(this_cause, url, funkname, arguments));


// **

void f2__xmlrpc__reinitialize_globalvars() {
}

void f2__xmlrpc__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "xmlrpc", "", &f2__xmlrpc__reinitialize_globalvars);
  
  f2__xmlrpc__reinitialize_globalvars();
  
  f2__primcfunk__init__1(xmlrpc__create_new_server, port_num,                 "creates a test xmlrpc server with a sample.add RPC function that takes two integers as arguments.");
  f2__primcfunk__init__3(xmlrpc__apply,             url, funkname, arguments, "calls an xmlrpc server and returns the value.");
}


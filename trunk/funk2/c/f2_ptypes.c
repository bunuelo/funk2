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

#define F2__PTYPE__C__COMPILING

#include "funk2.h"

#ifdef DEBUG
#  define F2__PTYPE__TYPE_CHECK
#endif

funk2_processor_mutex_t __global_ptype_incr_mutex[memory_pool_num];

void print_mutex_error(int retval) {
  switch (retval) {
  case EINVAL: error(nil, "error unlocking ptype_mutex: mutex is not initialized.");              break;
  case EFAULT: error(nil, "error unlocking ptype_mutex: mutex is an invalid pointer.");           break;
  case EPERM:  error(nil, "error unlocking ptype_mutex: the calling thread does not own mutex."); break;
  default:     error(nil, "error unlocking ptype_mutex: unknown error.");                         break;
  }
}

void ptype_incr_mutex__lock(int pool_index)    {
#ifdef F2__PTHREAD
  assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range."); funk2_processor_mutex__lock(&__global_ptype_incr_mutex[pool_index]);/*while(funk2_processor_mutex__trylock(&__global_ptype_incr_mutex[pool_index])) {sched_yield();}*/
#endif // F2__PTHREAD
}

void ptype_incr_mutex__unlock(int pool_index)  {
#ifdef F2__PTHREAD
  assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range."); int retval = funk2_processor_mutex__unlock(&__global_ptype_incr_mutex[pool_index]); if (retval) {print_mutex_error(retval);}
#endif // F2__PTHREAD
}

int __global_ptype_access_num[memory_pool_num];

void ptype_access_num__incr(int pool_index) {
  debug__assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range.");
  ptype_incr_mutex__lock(pool_index);
  memory_mutex__lock(pool_index);
  __global_ptype_access_num[pool_index] ++;
  memory_mutex__unlock(pool_index);
  ptype_incr_mutex__unlock(pool_index);
}

void ptype_access_num__decr(int pool_index) {
  debug__assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range.");
  memory_mutex__lock(pool_index);
  debug__assert(__global_ptype_access_num[pool_index] > 0, nil, "access num is < 0.");
  __global_ptype_access_num[pool_index] --;
  memory_mutex__unlock(pool_index);
}

// these mutex polling loops are hacks that probably create a whole crapload of thread mutex collisions...
void ptype_access__lockout_access(int pool_index, int max_access) {
  debug__assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range.");
  ptype_incr_mutex__lock(pool_index);
  // these types of polling loops should be replaced by a pthread_cond!
  while (__global_ptype_access_num[pool_index] > max_access) {
    f2__sleep(1);
    sched_yield();
  }
}

int  ptype_access__try_lockout_access(int pool_index, int max_access) {
  debug__assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range."); 
  ptype_incr_mutex__lock(pool_index);
  int try_count = 1;
  while (__global_ptype_access_num[pool_index] > max_access && try_count > 0) {
    try_count --;
    sched_yield();
  }
  if (try_count == 0) {
    ptype_incr_mutex__unlock(pool_index);
    return 1; // failure
  } else {
    return 0; // success
  }
}

void ptype_access__unlockout_access(int pool_index) {
  debug__assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range.");
  ptype_incr_mutex__unlock(pool_index);
}

// used by global initialization for creation (and other) causes

f2ptr initial_cause() {
  return nil;
}

// this.system

f2ptr pfunk2__system__environment(f2ptr cause) {
  return __funk2.memory.global_environment_f2ptr;
}

// memblock

#ifdef MEMORY_OPTION__MEMBLOCK__RENDER_DATA
void memblock__set_render_position_relative_to(f2ptr this, f2ptr relative) {
  if (! relative) {return;}
  memblock_t* this_memblock     = (memblock_t*)raw__f2ptr_to_ptr(this);
  memblock_t* relative_memblock = (memblock_t*)raw__f2ptr_to_ptr(relative);

  float dx = (memblock__render_noise / 10000000.0) * (float)(rand() % 20001 - 10000);
  float dy = (memblock__render_noise / 10000000.0) * (float)(rand() % 20001 - 10000);
  float dz = (memblock__render_noise / 10000000.0) * (float)(rand() % 20001 - 10000);
  float memblock__last_x = relative_memblock->render_position[0] + dx;
  float memblock__last_y = relative_memblock->render_position[1] + dy;
  float memblock__last_z = relative_memblock->render_position[2] + dz;
  if (memblock__last_x < -1.0) {memblock__last_x = -1.0;}
  if (memblock__last_x >  1.0) {memblock__last_x =  1.0;}
  if (memblock__last_y < -1.0) {memblock__last_y = -1.0;}
  if (memblock__last_y >  1.0) {memblock__last_y =  1.0;}
  if (memblock__last_z < -1.0) {memblock__last_z = -1.0;}
  if (memblock__last_z >  1.0) {memblock__last_z =  1.0;}
  this_memblock->render_position[0] = memblock__last_x;
  this_memblock->render_position[1] = memblock__last_y;
  this_memblock->render_position[2] = memblock__last_z;
}
#else
#  define memblock__set_render_position_relative_to(this, relative)
#endif // MEMORY_OPTION__MEMBLOCK__RENDER_DATA

void ptype_trace_create(int pool_index, f2ptr cause, f2ptr this) {
  //pool__pause_gc(pool_index);
  
  //f2ptr create_event = f2event__new__trace_depth(cause, __funk2.globalenv.create_event__symbol, this, 0);
  //f2ptr cause__trace = f2cause__trace(cause, cause);
  //f2ptr new_trace    = f2doublelink__new__trace_depth(nil, cause__trace, nil, create_event, 0);
  //f2cause__trace__set__trace_depth(cause, nil, new_trace, 0);
  
  //pool__resume_gc(pool_index);
}

void ptype_trace_read(int pool_index, f2ptr cause, f2ptr location, f2ptr value) {
  //pool__pause_gc(pool_index);
  
  //f2ptr location_value_pair = f2cons__new__trace_depth(cause, location, value, 0);
  //f2ptr read_event          = f2event__new__trace_depth(cause, __funk2.globalenv.read_event__symbol, location_value_pair, 0);
  //f2ptr cause__trace        = f2cause__trace(cause, cause);
  //f2ptr new_trace           = f2doublelink__new__trace_depth(nil, cause__trace, nil, read_event, 0);
  //f2cause__trace__set__trace_depth(cause, nil, new_trace, 0);
  
  //pool__resume_gc(pool_index);
}

void ptype_trace_write(int pool_index, f2ptr cause, f2ptr location, f2ptr value) {
  //pool__pause_gc(pool_index);
  
  //f2ptr location_value_pair = f2cons__new__trace_depth(cause, location, value, 0);
  //f2ptr write_event         = f2event__new__trace_depth(cause, __funk2.globalenv.write_event__symbol, location_value_pair, 0);
  //f2ptr cause__trace        = f2cause__trace(cause, cause);
  //f2ptr new_trace           = f2doublelink__new__trace_depth(nil, cause__trace, nil, write_event, 0);
  //f2cause__trace__set__trace_depth(cause, nil, new_trace, 0);
  
  //pool__resume_gc(pool_index);
}

boolean_t raw__cause__is_traced__trace_depth(f2ptr cause, f2ptr this, int trace_depth) {
  if (! this) {
    return nil;
  }
#ifdef F2__PTYPE__TYPE_CHECK
  //if(! raw__cause__is_type(cause, this)) {
  //  status("raw__cause__is_traced !raw__cause__is_type(cause, this)");
  //  f2__print(nil, this); fflush(stdout);
  //  error(nil, "raw__cause__is_traced !raw__cause__is_type(cause, this)");
  //}
#endif
  return f2cause__memory_tracing_on__trace_depth(this, cause, trace_depth);
}

boolean_t raw__cause__is_traced(f2ptr cause, f2ptr this) {
  return raw__cause__is_traced__trace_depth(cause, this, 0);
}

void debug__cause__is_imaginary() {
  //printf("\ndebug__cause__is_imaginary here.");
}

boolean_t raw__cause__is_imaginary__trace_depth(f2ptr cause, f2ptr this, int trace_depth) {
  if (! this) {
    return nil;
  }
#ifdef F2__PTYPE__TYPE_CHECK
  //if(! raw__cause__is_type(cause, this)) {
  //  status("raw__cause__is_imaginary !raw__cause__is_type(cause, this)");
  //  f2__print(nil, this); fflush(stdout);
  //  error(nil, "raw__cause__is_imaginary !raw__cause__is_type(cause, this)");
  //}
#endif
  f2ptr the_cause_for_checking_whether_imaginary_or_not = nil; // avoids infinitely considering whether or not we are imagining by returning the "real" value of our cause's imagination stack... (see South Park, ImaginationLand Episode for elaboration)
  boolean_t return_value = (f2cause__imagination_stack(this, the_cause_for_checking_whether_imaginary_or_not) != nil);
  if (return_value) {
    debug__cause__is_imaginary();
  }
  return return_value;
}

boolean_t raw__cause__is_imaginary(f2ptr cause, f2ptr this) {
  return raw__cause__is_imaginary__trace_depth(cause, this, 0);
}

void ptype_error(f2ptr cause, f2ptr this, f2ptr expected_type) {
  error(nil, "ptype_error.");
}

// ptype

ptype_t pfunk2__f2ptype__raw(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  ptype_t retval = __pure__f2ptype__raw(this);
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2ptype__cause(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2ptype__cause(this);
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2ptype__cause__set(f2ptr this, f2ptr cause, f2ptr value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  __pure__f2ptype__cause(this) = value;
  ptype_access_num__decr(pool_index);
  return nil;
}


// integer

f2ptr ptype_integer__new(int pool_index, f2ptr cause, s64 i) {
  f2ptr integer_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_integer_block_t));
  ptype_integer_block_t* integer_block = (ptype_integer_block_t*)from_ptr(raw__f2ptr_to_ptr(integer_f2ptr));
  debug__assert(integer_block, nil, "block is nil.");
  integer_block->ptype.ptype = ptype_integer;
  integer_block->ptype.cause = cause;
  integer_block->i           = i;
  memblock__set_render_position_relative_to(integer_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, integer_f2ptr);}
  return integer_f2ptr;
}

f2ptr pfunk2__f2integer__new(f2ptr cause, s64 i) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2integer__new(pool_index, cause, i);
  ptype_access_num__decr(pool_index);
  return retval;
}

s64 pfunk2__f2integer__i(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_integer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_integer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  s64 i = __pure__f2integer__i(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return i;
}

boolean_t raw__integer__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_integer);
}
f2ptr f2__integer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__integer__is_type(cause, x));}
def_pcfunk1(integer__is_type,        x,    return f2__integer__is_type(this_cause, x));
def_pcfunk1(integer__new, this, return f2integer__new(this_cause, f2integer__i(this, this_cause)));
def_pcfunk1(integer__i,   this, return this);

f2ptr f2__integer__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_integer.i__funk;
  }
  return nil;
}

f2ptr f2__integer__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__integer__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_integer.new__funk;
  }
  return nil;
}

f2ptr f2integer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_integer.new__funk);}
  {char* slot_name = "i"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.i__funk, nil, nil);}
  return this;
}



// double

f2ptr ptype_double__new(int pool_index, f2ptr cause, double d) {
  f2ptr double_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_double_block_t));
  ptype_double_block_t* double_block = (ptype_double_block_t*)from_ptr(raw__f2ptr_to_ptr(double_f2ptr));
  debug__assert(double_block, nil, "block is nil.");
  double_block->ptype.ptype = ptype_double;
  double_block->ptype.cause = cause;
  double_block->d           = d;
  memblock__set_render_position_relative_to(double_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, double_f2ptr);}
  return double_f2ptr;
}

f2ptr pfunk2__f2double__new(f2ptr cause, double d) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2double__new(pool_index, cause, d);
  ptype_access_num__decr(pool_index);
  return retval;
}

double pfunk2__f2double__d(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_double) {
    ptype_error(cause, this, __funk2.globalenv.ptype_double__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  double d = __pure__f2double__d(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return d;
}

boolean_t raw__double__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_double);
}
f2ptr f2__double__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__double__is_type(cause, x));}
def_pcfunk1(double__is_type,        x,    return f2__double__is_type(this_cause, x));
def_pcfunk1(double__new, this, return f2double__new(this_cause, f2double__d(this, this_cause)));
def_pcfunk1(double__d,   this, return f2double__new(this_cause, f2double__d(this, this_cause)));

f2ptr f2__double__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.d__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.d__funk;
  }
  return nil;
}

f2ptr f2__double__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__double__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.new__funk;
  }
  return nil;
}

f2ptr f2double__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_double.new__funk);}
  {char* slot_name = "d"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_double.d__funk, nil, nil);}
  return this;
}

// deprecated
//boolean_t raw__doublep(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_double);}
//f2ptr f2__doublep(f2ptr cause, f2ptr x) {return f2bool__new(raw__doublep(x, cause));}
//def_pcfunk1(doublep, x, return f2__doublep(this_cause, x));


// float

f2ptr ptype_float__new(int pool_index, f2ptr cause, float f) {
  f2ptr float_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_float_block_t));
  ptype_float_block_t* float_block = (ptype_float_block_t*)from_ptr(raw__f2ptr_to_ptr(float_f2ptr));
  debug__assert(float_block, nil, "block is nil.");
  float_block->ptype.ptype = ptype_float;
  float_block->ptype.cause = cause;
  float_block->f           = f;
  memblock__set_render_position_relative_to(float_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, float_f2ptr);}
  return float_f2ptr;
}

f2ptr pfunk2__f2float__new(f2ptr cause, float f) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2float__new(pool_index, cause, f);
  ptype_access_num__decr(pool_index);
  return retval;
}

float pfunk2__f2float__f(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_float) {
    ptype_error(cause, this, __funk2.globalenv.ptype_float__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  float f = __pure__f2float__f(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return f;
}

boolean_t raw__float__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_float);
}
f2ptr f2__float__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__float__is_type(cause, x));}
def_pcfunk1(float__is_type,        x,    return f2__float__is_type(this_cause, x));
def_pcfunk1(float__new, this, return f2float__new(this_cause, f2float__f(this_cause, this)));
def_pcfunk1(float__f,   this, return this);

f2ptr f2__float__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_float.f__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_float.f__funk;
  }
  return nil;
}

f2ptr f2__float__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__float__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_float.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_float.new__funk;
  }
  return nil;
}

f2ptr f2float__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_float.new__funk);}
  {char* slot_name = "f"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_float.f__funk, nil, nil);}
  return this;
}

// deprecated
//boolean_t raw__floatp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_float);}
//f2ptr f2__floatp(f2ptr cause, f2ptr x) {return f2bool__new(raw__floatp(x, cause));}
//def_pcfunk1(floatp, x, return f2__floatp(this_cause, x));


// pointer

f2ptr ptype_pointer__new(int pool_index, f2ptr cause, ptr p) {
  f2ptr pointer_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_pointer_block_t));
  ptype_pointer_block_t* pointer_block = (ptype_pointer_block_t*)from_ptr(raw__f2ptr_to_ptr(pointer_f2ptr));
  debug__assert(pointer_block, nil, "block is nil.");
  pointer_block->ptype.ptype = ptype_pointer;
  pointer_block->ptype.cause = cause;
  pointer_block->p           = p;
  memblock__set_render_position_relative_to(pointer_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, pointer_f2ptr);}
  return pointer_f2ptr;
}

f2ptr pfunk2__f2pointer__new(f2ptr cause, ptr p) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2pointer__new(pool_index, cause, p);
  ptype_access_num__decr(pool_index);
  return retval;
}

ptr pfunk2__f2pointer__p(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  ptr p = __pure__f2pointer__p(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return p;
}

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_pointer);
}
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__pointer__is_type(cause, x));}
def_pcfunk1(pointer__is_type,        x,    return f2__pointer__is_type(this_cause, x));
def_pcfunk1(pointer__new, this, return f2pointer__new(this_cause, f2pointer__p(this_cause, this)));
def_pcfunk1(pointer__p,   this, return this);

f2ptr f2__pointer__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk;
  }
  return nil;
}

f2ptr f2__pointer__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__pointer__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk;
  }
  return nil;
}

f2ptr f2pointer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk);}
  {char* slot_name = "p"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk, nil, nil);}
  return this;
}

// deprecated
//boolean_t raw__pointerp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_pointer);}
//f2ptr f2__pointerp(f2ptr cause, f2ptr x) {return f2bool__new(raw__pointerp(x, cause));}
//def_pcfunk1(pointerp, x, return f2__pointerp(this_cause, x));


// gfunkptr

f2ptr ptype_gfunkptr__new(int pool_index, f2ptr cause, computer_id_t gf2_computer_id, pool_index_t gf2_pool_index, pool_address_t gf2_pool_address) {
  f2ptr gfunkptr_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_gfunkptr_block_t));
  ptype_gfunkptr_block_t* gfunkptr_block = (ptype_gfunkptr_block_t*)from_ptr(raw__f2ptr_to_ptr(gfunkptr_f2ptr));
  debug__assert(gfunkptr_block, nil, "block is nil.");
  gfunkptr_block->ptype.ptype = ptype_gfunkptr;
  gfunkptr_block->ptype.cause = cause;
  gfunkptr_block->gfunkptr    = f2ptr__new(gf2_computer_id, gf2_pool_index, gf2_pool_address);
  memblock__set_render_position_relative_to(gfunkptr_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, gfunkptr_f2ptr);}
  return gfunkptr_f2ptr;
}

f2ptr pfunk2__f2gfunkptr__new(f2ptr cause, computer_id_t gf2_computer_id, pool_index_t gf2_pool_index, pool_address_t gf2_pool_address) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2gfunkptr__new(pool_index, cause, gf2_computer_id, gf2_pool_index, gf2_pool_address);
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2gfunkptr__new_from_f2ptr(f2ptr cause, f2ptr f2p) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2gfunkptr__new(pool_index, cause, __f2ptr__computer_id(f2p), __f2ptr__pool_index(f2p), __f2ptr__pool_address(f2p));
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2gfunkptr__gfunkptr(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = __pure__f2gfunkptr__gfunkptr(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

computer_id_t pfunk2__f2gfunkptr__computer_id(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  computer_id_t rv = __pure__f2gfunkptr__computer_id(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

pool_index_t pfunk2__f2gfunkptr__pool_index(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  pool_index_t rv = __pure__f2gfunkptr__pool_index(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

pool_address_t pfunk2__f2gfunkptr__pool_address(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  pool_address_t rv = __pure__f2gfunkptr__pool_address(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

boolean_t raw__gfunkptr__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_gfunkptr);
}
f2ptr f2__gfunkptr__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__gfunkptr__is_type(cause, x));}
def_pcfunk1(gfunkptr__is_type, x, return f2__gfunkptr__is_type(this_cause, x));
def_pcfunk3(gfunkptr__new, computer_id, pool_index, pool_address, return f2gfunkptr__new(this_cause, f2integer__i(computer_id, this_cause), f2integer__i(pool_index, this_cause), f2integer__i(pool_address, this_cause)));
def_pcfunk1(gfunkptr__new_from_f2ptr, f2p, return f2gfunkptr__new_from_f2ptr(this_cause, f2p));
def_pcfunk1(gfunkptr__gfunkptr, this, return f2gfunkptr__gfunkptr(this, this_cause));
def_pcfunk1(gfunkptr__computer_id, this, return f2integer__new(this_cause, f2gfunkptr__computer_id(this, this_cause)));
def_pcfunk1(gfunkptr__pool_index, this, return f2integer__new(this_cause, f2gfunkptr__pool_index(this, this_cause)));
def_pcfunk1(gfunkptr__pool_address, this, return f2integer__new(this_cause, f2gfunkptr__pool_address(this, this_cause)));

f2ptr f2__gfunkptr__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__funk;
  }
  return nil;
}

f2ptr f2__gfunkptr__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__gfunkptr__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk;
  }
  return nil;
}

f2ptr f2gfunkptr__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk);}
  {char* slot_name = "new_from_f2ptr"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk);}
  {char* slot_name = "gfunkptr"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk, nil, nil);}
  {char* slot_name = "computer_id"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk, nil, nil);}
  {char* slot_name = "pool_index"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__funk, nil, nil);}
  {char* slot_name = "pool_address"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__funk, nil, nil);}
  return this;
}

// deprecated
//boolean_t raw__gfunkptrp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_gfunkptr);}
//f2ptr f2__gfunkptr(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {return f2gfunkptr__new(cause, f2integer__i(x, cause), f2integer__i(y, cause), f2integer__i(z, cause));}
//def_pcfunk3(gfunkptr, x, y, z, return f2__gfunkptr(this_cause, x, y, z));


// mutex

f2ptr ptype_mutex__new(int pool_index, f2ptr cause) {
  f2ptr mutex_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_mutex_block_t));
  ptype_mutex_block_t* mutex_block = (ptype_mutex_block_t*)from_ptr(raw__f2ptr_to_ptr(mutex_f2ptr));
  debug__assert(mutex_block, nil, "block is nil.");
  mutex_block->ptype.ptype = ptype_mutex;
  mutex_block->ptype.cause = cause;
  funk2_processor_mutex__init(mutex_block->m);
  memblock__set_render_position_relative_to(mutex_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, mutex_f2ptr);}
  return mutex_f2ptr;
}

funk2_processor_mutex_t* ptype_mutex__m(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  funk2_processor_mutex_t* m = __pure__f2mutex__m(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return m;
}

f2ptr pfunk2__f2mutex__new(f2ptr cause) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2mutex__new(pool_index, cause);
  ptype_access_num__decr(pool_index);
  return retval;
}

void pfunk2__f2mutex__lock(f2ptr this, f2ptr cause) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int lock_failed;
  do {
    int pool_index = __f2ptr__pool_index(this);
    ptype_access_num__incr(pool_index);
    lock_failed = funk2_processor_mutex__trylock(ptype_mutex__m(this, cause));
    ptype_access_num__decr(pool_index);
  } while (lock_failed);
}

void pfunk2__f2mutex__unlock(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_processor_mutex__unlock(ptype_mutex__m(this, cause));
  ptype_access_num__decr(pool_index);
}

int pfunk2__f2mutex__trylock(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_mutex__trylock(ptype_mutex__m(this, cause));
  ptype_access_num__decr(pool_index);
  return return_value;
}

boolean_t raw__mutex__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_mutex);
}
f2ptr f2__mutex__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__mutex__is_type(cause, x));}
def_pcfunk1(mutex__is_type, x, return f2__mutex__is_type(this_cause, x));

f2ptr f2__mutex__new(f2ptr cause) {return f2mutex__new(cause);}
def_pcfunk0(mutex__new, return f2__mutex__new(this_cause));

f2ptr f2__mutex__lock(f2ptr cause, f2ptr x) {f2mutex__lock(x, cause); return nil;}
def_pcfunk1(mutex__lock, this, return f2__mutex__lock(this_cause, this));

f2ptr f2__mutex__unlock(f2ptr cause, f2ptr x) {f2mutex__unlock(x, cause); return nil;}
def_pcfunk1(mutex__unlock, this, return f2__mutex__unlock(this_cause, this));

f2ptr f2__mutex__trylock(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2mutex__trylock(x, cause));}
def_pcfunk1(mutex__trylock, this, return f2__mutex__trylock(this_cause, this));


f2ptr f2__mutex__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__mutex__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__mutex__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_mutex.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_mutex.lock__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk;
  }
  return nil;
}

f2ptr f2mutex__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk);}
  {char* slot_name = "lock"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk);}
  {char* slot_name = "trylock"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk);}
  {char* slot_name = "unlock"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk);}
  return this;
}

// deprecated
boolean_t raw__mutexp(f2ptr x, f2ptr cause) {return (x && f2ptype__raw(x, cause) == ptype_mutex);}
f2ptr f2__mutexp(f2ptr cause, f2ptr x) {return f2bool__new(raw__mutexp(x, cause));}
//def_pcfunk1(mutexp, x, return f2__mutexp(this_cause, x));


// char

f2ptr ptype_char__new(int pool_index, f2ptr cause, u64 ch) {
  f2ptr char_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_char_block_t));
  ptype_char_block_t* char_block = (ptype_char_block_t*)from_ptr(raw__f2ptr_to_ptr(char_f2ptr));
  debug__assert(char_block, nil, "block is nil.");
  char_block->ptype.ptype = ptype_char;
  char_block->ptype.cause = cause;
  char_block->ch          = ch;
  memblock__set_render_position_relative_to(char_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, char_f2ptr);}
  return char_f2ptr;
}

f2ptr pfunk2__f2char__new(f2ptr cause, u64 ch) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2char__new(pool_index, cause, ch);
  ptype_access_num__decr(pool_index);
  return retval;
}

u64 pfunk2__f2char__ch(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_char) {
    ptype_error(cause, this, __funk2.globalenv.ptype_char__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 ch = __pure__f2char__ch(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return ch;
}

boolean_t raw__char__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_char);
}
f2ptr f2__char__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__char__is_type(cause, x));}
def_pcfunk1(char__is_type, x, return f2__char__is_type(this_cause, x));
def_pcfunk1(char__new, ch, return f2char__new(this_cause, f2char__ch(ch, this_cause)));
def_pcfunk1(char__ch, this, return this);

f2ptr f2__char__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_char.ch__funk;
  }
  return nil;
}

f2ptr f2__char__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__char__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_char.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_char.new__funk;
  }
  return nil;
}

f2ptr f2char__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_char.new__funk);}
  {char* slot_name = "ch"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_char.ch__funk, nil, nil);}
  return this;
}

// deprecated
//boolean_t raw__charp(f2ptr x, f2ptr cause) {return raw__char__is_type(cause, x);}

// string

f2ptr ptype_string__new(int pool_index, f2ptr cause, u64 length, u8* str) {
  f2ptr string_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_string_block_t) + length + 1);
  ptype_string_block_t* string_block = (ptype_string_block_t*)from_ptr(raw__f2ptr_to_ptr(string_f2ptr));
  debug__assert(string_block, nil, "block is nil.");
  string_block->ptype.ptype = ptype_string;
  string_block->ptype.cause = cause;
  string_block->length      = length;
  if (str) {memcpy(string_block->str, str, length);}
  else     {bzero(string_block->str, length);}
  string_block->str[length] = 0x00;
  memblock__set_render_position_relative_to(string_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, string_f2ptr);}
  return string_f2ptr;
}

f2ptr pfunk2__f2string__new(f2ptr cause, u64 length, u8* init) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2string__new(pool_index, cause, length, init);
  ptype_access_num__decr(pool_index);
  return retval;
}

u64 pfunk2__f2string__length(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  length = __pure__f2string__length(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return length;
}

u8 pfunk2__f2string__elt(f2ptr this, int index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  s8 ch = __pure__f2string__str(this)[index];
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return ch;
}

void pfunk2__f2string__str_copy(f2ptr this, f2ptr cause, u8* str) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2string__str(this), __pure__f2string__length(this));
  __pure__memblock__render_write_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
}

int pfunk2__f2string__hash_value(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 len = __pure__f2string__length(this);
  u8* str = __pure__f2string__str(this);
  int retval = (int)chararray__hash_value(len, str);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return retval;
}

boolean_t raw__string__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_string);
}
f2ptr f2__string__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__string__is_type(cause, x));}

f2ptr f2__string__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2string__length(x, cause));}

f2ptr f2__string__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, index))) {
    return f2larva__new(cause, 1);
  }
  u64 raw_index = f2integer__i(index, cause);
  return f2char__new(cause, f2string__elt(this, raw_index, cause));
}

f2ptr f2__string__hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, f2string__hash_value(this, cause));}

f2ptr f2__string__new(f2ptr cause, f2ptr str) {
  if (! raw__string__is_type(cause, str)) {
    return f2larva__new(cause, 1);
  }
  int str__length = f2string__length(str, cause);
  u8* str__bytes = (u8*)alloca(str__length);
  f2string__str_copy(str, cause, str__bytes);
  return f2string__new(cause, str__length, str__bytes);
}

def_pcfunk1(string__is_type, x, return f2__string__is_type(this_cause, x));
def_pcfunk1(string__new, str, return f2__string__new(this_cause, str));
def_pcfunk1(string__length, this, return f2__string__length(this_cause, this));
def_pcfunk2(string__elt, this, index, return f2__string__elt(this_cause, this, index));
def_pcfunk1(string__hash_value, this, return f2__string__hash_value(this_cause, this));

f2ptr f2__string__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.hash_value__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.hash_value__funk;
  }
  return nil;
}

f2ptr f2__string__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__string__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.new__funk;
  }
  return nil;
}

f2ptr f2string__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_string.new__funk);}
  {char* slot_name = "length"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_string.length__funk, nil, nil);}
  {char* slot_name = "elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_string.elt__funk, nil, nil);}
  {char* slot_name = "hash_value"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_string.hash_value__funk, nil, nil);}
  return this;
}



// symbol

funk2_processor_mutex_t symbol_hash_mutex; // must initialize

typedef struct symbol_hash_node_s {
  f2ptr                      symbol;
  struct symbol_hash_node_s* next;
} symbol_hash_node_t;

typedef struct symbol_hash_s {
  symbol_hash_node_t** array;
  u64                  hash_value_bit_mask;
  int                  total_symbol_num;
  int                  array_length;
} symbol_hash_t;
boolean_t     __symbol_hash__initialized = 0;
symbol_hash_t __symbol_hash;

void symbol_hash__initialize() {
  funk2_processor_mutex__init(&symbol_hash_mutex);
  __symbol_hash.array               = (symbol_hash_node_t**)from_ptr(f2__malloc(sizeof(symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH));
  bzero(__symbol_hash.array, sizeof(symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH);
  __symbol_hash.total_symbol_num    = 0;
  __symbol_hash.hash_value_bit_mask = SYMBOL_HASH__INITIAL_ARRAY_LENGTH - 1; // assumes SYMBOL_HASH__INITIAL_ARRAY_LENGTH is power of 2
  __symbol_hash.array_length        = SYMBOL_HASH__INITIAL_ARRAY_LENGTH;
  __symbol_hash__initialized        = 1;
}

void symbol_hash__reinitialize() {
  f2__free(to_ptr(__symbol_hash.array));
  symbol_hash__initialize();
}

void symbol_hash__add_symbol(f2ptr symbol_f2ptr) {
  ptype_symbol_block_t* symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(symbol_f2ptr));
  u64                   bin_index    = symbol_block->hash_value & __symbol_hash.hash_value_bit_mask;
  symbol_hash_node_t*   new_node     = (symbol_hash_node_t*)from_ptr(f2__malloc(sizeof(symbol_hash_node_t)));
  new_node->symbol = symbol_f2ptr;
  new_node->next = __symbol_hash.array[bin_index];
  __symbol_hash.array[bin_index] = new_node;
}

// 2^64 = 18, 446,744,073,709,551,616
//   or = 18  sextillion

f2ptr ptype_symbol__new(int pool_index, f2ptr cause, uint length, u8* str) {
  if (length == 0) {
    return nil;
  }
  funk2_processor_mutex__lock(&symbol_hash_mutex);
  if (! __symbol_hash__initialized) {symbol_hash__initialize();}
  ptype_symbol_block_t* symbol_block = NULL;
  
  // search for chararray in hashed symbols
  uint bin_index = (uint)((uint)chararray__hash_value(length, str) & (uint)__symbol_hash.hash_value_bit_mask);
  symbol_hash_node_t* node = __symbol_hash.array[bin_index];
  while (node) {
    symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(node->symbol));
    //if we find a symbol that matches chararray, return it.
    if (!symbol_block->ptype.block.used) {
      printf("\nfound unused symbol."); fflush(stdout);
    }
    if (symbol_block->length == length && (! memcmp(symbol_block->str, str, length))) {
      funk2_processor_mutex__unlock(&symbol_hash_mutex);
      return node->symbol;
    }
    node = node->next;
  }
  
  // otherwise, create a new symbol
  f2ptr symbol_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_symbol_block_t) + length + 1);
  symbol_block = (ptype_symbol_block_t*)from_ptr(raw__f2ptr_to_ptr(symbol_f2ptr));
  debug__assert(symbol_block, nil, "block is nil.");
  symbol_block->ptype.ptype = ptype_symbol;
  symbol_block->ptype.cause = cause;
  symbol_block->length      = length;
  if (str) {memcpy(symbol_block->str, str, length);}
  else     {bzero(symbol_block->str, length);}
  symbol_block->str[length] = 0x00;
  symbol_block->hash_value  = (u64)((uint)chararray__hash_value(length, str));
  
  // and add new symbol to hash table
  symbol_hash__add_symbol(symbol_f2ptr);
  
  funk2_processor_mutex__unlock(&symbol_hash_mutex);
  memblock__set_render_position_relative_to(symbol_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, symbol_f2ptr);}
  return symbol_f2ptr;
}

void gc_touch_all_symbols() {
  symbol_hash_node_t** array_iter = __symbol_hash.array;
  symbol_hash_node_t*  node_iter;
  int i;
  for (i = __symbol_hash.array_length; i > 0; i --) {
    for (node_iter = array_iter[0]; node_iter; node_iter = node_iter->next) {
      exp__gc_touch_all_referenced(__f2ptr_to_ptr(node_iter->symbol));
    }
    array_iter ++;
  }
}

f2ptr pfunk2__f2symbol__new(f2ptr cause, u64 length, u8* init) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2symbol__new(pool_index, cause, length, init);
  ptype_access_num__decr(pool_index);
  return retval;
}

u64 pfunk2__f2symbol__length(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  length     = __pure__f2symbol__length(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return length;
}

u64 pfunk2__f2symbol__hash_value(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  hash_value = __pure__f2symbol__hash_value(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return hash_value;
}

u8 pfunk2__f2symbol__elt(f2ptr this, int index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8 ch = __pure__f2symbol__str(this)[index];
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return ch;
}

void pfunk2__f2symbol__str_copy(f2ptr this, f2ptr cause, u8* str) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2symbol__str(this), __pure__f2symbol__length(this));
  __pure__memblock__render_write_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
}

boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_symbol);
}
f2ptr f2__symbol__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__symbol__is_type(cause, x));}
f2ptr f2__symbol__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2symbol__length(x, cause));}
f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2symbol__elt(x, f2integer__i(y, cause), cause));}
f2ptr f2__symbol__hash_value(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2symbol__hash_value(x, cause));}
f2ptr f2__symbol__new(f2ptr cause, f2ptr str) {
  if (! raw__string__is_type(cause, str)) {
    return f2larva__new(cause, 1);
  }
  int str__length = f2string__length(str, cause);
  u8* str__bytes = (u8*)alloca(str__length);
  f2string__str_copy(str, cause, str__bytes);
  return f2symbol__new(cause, str__length, str__bytes);
}
boolean_t raw__symbol__eq(f2ptr cause, f2ptr this, f2ptr that) {
  if ((! raw__symbol__is_type(cause, this)) || (! raw__symbol__is_type(cause, that))) {return boolean__false;}
  u64 this__length = f2symbol__length(this, cause);
  u64 that__length = f2symbol__length(that, cause);
  if (this__length != that__length) {
    return boolean__false;
  }
  char* this__str = (char*)alloca(this__length + 1);
  char* that__str = (char*)alloca(that__length + 1);
  f2symbol__str_copy(this, cause, (u8*)this__str);
  f2symbol__str_copy(that, cause, (u8*)that__str);
  if (memcmp(this__str, that__str, this__length) != 0) {
    return boolean__false;
  }
  return boolean__true;
}
f2ptr f2__symbol__eq(f2ptr cause, f2ptr x, f2ptr y) {return f2bool__new(raw__symbol__eq(cause, x, y));}

def_pcfunk1(symbol__is_type, x, return f2__symbol__is_type(this_cause, x));
def_pcfunk1(symbol__new, str, return f2__symbol__new(this_cause, str));
def_pcfunk1(symbol__length, this, return f2__symbol__length(this_cause, this));
def_pcfunk2(symbol__elt, this, index, return f2__symbol__elt(this_cause, this, index));
def_pcfunk1(symbol__hash_value, this, return f2__symbol__hash_value(this_cause, this));
def_pcfunk2(symbol__eq, x, y, return f2__symbol__eq(this_cause, x, y));

f2ptr f2__symbol__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__funk;
  }
  return nil;
}

f2ptr f2__symbol__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__symbol__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk;
  }
  return nil;
}

f2ptr f2symbol__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk);}
  {char* slot_name = "length";     f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk, nil, nil);}
  {char* slot_name = "elt";        f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk, nil, nil);}
  {char* slot_name = "hash_value"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__funk, nil, nil);}
  //{char* slot_name = "==";         f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__funk, nil, nil);}
  return this;
}

// deprecated
//f2ptr f2__symbolp(f2ptr cause, f2ptr x) {return f2__symbol__is_type(cause, x);}
//def_pcfunk1(symbolp, x, return f2__symbolp(this_cause, x));



// chunk

f2ptr ptype_chunk__new(int pool_index, f2ptr cause, u64 length, byte* bytes) {
  u64 data_byte_num = (sizeof(u8) * length);
  f2ptr chunk_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_chunk_block_t) + data_byte_num);
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  chunk_block->ptype.ptype = ptype_chunk;
  chunk_block->ptype.cause = cause;
  chunk_block->length      = length;
  if (bytes) {memcpy(chunk_block->bytes, bytes, data_byte_num);}
  else       {bzero(chunk_block->bytes, data_byte_num);}
  memblock__set_render_position_relative_to(chunk_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, chunk_f2ptr);}
  return chunk_f2ptr;
}

f2ptr ptype_chunk__new_copy(int pool_index, f2ptr cause, f2ptr init_chunk) {
  ptype_chunk_block_t* init_chunk_block = (ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(init_chunk)));
  u64 data_byte_num = (sizeof(u8) * init_chunk_block->length);
  f2ptr chunk_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_chunk_block_t));
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  chunk_block->ptype.ptype = ptype_chunk;
  chunk_block->ptype.cause = cause;
  chunk_block->length      = init_chunk_block->length;
  memcpy(chunk_block->bytes, init_chunk_block->bytes, data_byte_num);
  __pure__memblock__render_read_activated__set(init_chunk, 1);
  memblock__set_render_position_relative_to(chunk_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, chunk_f2ptr);}
  return chunk_f2ptr;
}

u8* ptype_chunk__bytes(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8* bytes = __pure__f2chunk__bytes(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return bytes;
}

f2ptr pfunk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2chunk__new(pool_index, cause, length, bytes);
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2chunk__new_copy(pool_index, cause, init_chunk);
  ptype_access_num__decr(pool_index);
  return retval;
}

u64 pfunk2__f2chunk__length(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2chunk__length(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return length;
}

u8 pfunk2__f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8 retval = __pure__f2chunk__bit8__elt(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return retval;
}

void  pfunk2__f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value)   {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
  __pure__f2chunk__bit8__elt__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
}

u16 pfunk2__f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u16 retval = __pure__f2chunk__bit16__elt(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return retval;
}

void pfunk2__f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit16__elt__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
}

u32 pfunk2__f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 retval = __pure__f2chunk__bit32__elt(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return retval;
}

void pfunk2__f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit32__elt__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
}

u64 pfunk2__f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 retval = __pure__f2chunk__bit64__elt(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return retval;
}

void pfunk2__f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit64__elt__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
}

f2ptr pfunk2__f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr thread, f2ptr env, f2ptr args) {
  int pool_index = __f2ptr__pool_index(this); 
  ptype_access_num__incr(pool_index); /*memblock__lock(this);*/
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__memblock__render_read_activated__set(this, 1); 
  cfunkptr_t jump = (cfunkptr_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  /*memblock__unlock(this);*/ ptype_access_num__decr(pool_index);
  printf("\nchunk-cfunk_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  return jump(cause, thread, env, args);
}

int pfunk2__f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr thread) {
  int pool_index = __f2ptr__pool_index(this); 
  ptype_access_num__incr(pool_index); /*memblock__lock(this);*/
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__memblock__render_read_activated__set(this, 1); 
  bytecode_jump_t jump = (bytecode_jump_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  /*memblock__unlock(this);*/ ptype_access_num__decr(pool_index);
  //printf("\nchunk-bytecode_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  f2ptr bytecode = nil;
  return jump(thread, bytecode);
}

f2ptr pfunk2__f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  int pool_index = __f2ptr__pool_index(this); 
  ptype_access_num__incr(pool_index); /*memblock__lock(this);*/
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__memblock__render_read_activated__set(this, 1);
  f2ptr rv = f2integer__new(cause, send(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  /*memblock__unlock(this);*/ ptype_access_num__decr(pool_index);
  return rv;
}

f2ptr pfunk2__f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  int pool_index = __f2ptr__pool_index(this); 
  ptype_access_num__incr(pool_index); /*memblock__lock(this);*/
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__memblock__render_write_activated__set(this, 1); 
  f2ptr rv = f2integer__new(cause, recv(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  /*memblock__unlock(this);*/ ptype_access_num__decr(pool_index);
  return rv;
}

boolean_t raw__chunk__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if ((!cause) || (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_chunk);
}
f2ptr f2__chunk__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__chunk__is_type(cause, x));}
f2ptr f2__chunk__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2chunk__length(x, cause));}

def_pcfunk1(chunk__is_type, x, return f2__chunk__is_type(this_cause, x));
def_pcfunk1(chunk__new, length, return f2chunk__new(this_cause, f2integer__i(length, this_cause), NULL));
def_pcfunk1(chunk__length, x, return f2__chunk__length(this_cause, x));
def_pcfunk2(chunk__bit8__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit8__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit8__elt__set, this, index, value, f2chunk__bit8__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit16__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit16__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit16__elt__set, this, index, value, f2chunk__bit16__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit32__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit32__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit32__elt__set, this, index, value, f2chunk__bit32__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit64__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit64__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit64__elt__set, this, index, value, f2chunk__bit64__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk4(chunk__cfunk_jump, this, thread, env, args, return f2chunk__cfunk_jump(this, this_cause, thread, env, args));
def_pcfunk2(chunk__bytecode_jump, this, thread, return f2integer__new(this_cause, f2chunk__bytecode_jump(this, this_cause, thread)));

f2ptr f2__chunk__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk;
  }
  return nil;
}

f2ptr f2__chunk__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk;
  }
  return nil;
}

f2ptr f2__chunk__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk;
  }
  return nil;
}

f2ptr f2chunk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk);}
  {char* slot_name = "new_copy"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_chunk.new_copy__funk);}
  {char* slot_name = "length"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk, nil, nil);}
  {char* slot_name = "bit8-elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk, nil);}
  {char* slot_name = "bit16-elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk, nil);}
  {char* slot_name = "bit32-elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk, nil);}
  {char* slot_name = "bit64-elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk, nil);}
  {char* slot_name = "cfunk_jump"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk);}
  {char* slot_name = "bytecode_jump"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk);}
  return this;
}


// struct dptr

void dptr__init(dptr_t* dptr, f2ptr p, f2ptr tracing_on, f2ptr trace, f2ptr imagination_frame) {
  dptr->p                 = p;
  dptr->tracing_on        = tracing_on;
  dptr->trace             = trace;
  dptr->imagination_frame = imagination_frame;
}


// simple_array

f2ptr ptype_simple_array__new(int pool_index, f2ptr cause, u64 length, ptr f2ptr_ptr) {
  u64 data_byte_num = (sizeof(f2ptr) * length);
  f2ptr simple_array_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_simple_array_block_t) + data_byte_num);
  ptype_simple_array_block_t* simple_array_block = (ptype_simple_array_block_t*)from_ptr(raw__f2ptr_to_ptr(simple_array_f2ptr));
  debug__assert(simple_array_block, nil, "block is nil.");
  //debug__assert(!cause || valid_memblock_ptr(f2ptr_to_ptr(cause)), nil, "valid_memblock_ptr(cause) failed");
  simple_array_block->ptype.ptype = ptype_simple_array;
  simple_array_block->ptype.cause = cause;
  simple_array_block->immutable   = 0;
  simple_array_block->length      = length;
  if (f2ptr_ptr) {memcpy(simple_array_block->f2ptr_data, from_ptr(f2ptr_ptr), data_byte_num);}
  else {
    int i;
    f2ptr* f2ptr_iter = (f2ptr*)(simple_array_block->f2ptr_data);
    for (i = length; i > 0; i --) {
      *f2ptr_iter = nil;
      f2ptr_iter  ++;
    }
  }
  memblock__set_render_position_relative_to(simple_array_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, simple_array_f2ptr);}
  return simple_array_f2ptr;
}

f2ptr pfunk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_ptr) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr this = __pure__f2simple_array__new(pool_index, cause, length, f2ptr_ptr);
  //if (cause) {ptype_trace_create(pool_index, cause, this);}
  ptype_access_num__decr(pool_index);
  return this;
}

f2ptr pfunk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(init_array) != ptype_simple_array) {
    ptype_error(cause, init_array, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return pfunk2__f2simple_array__new(cause, length, to_ptr(((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(init_array))))->f2ptr_data));
}

u8 pfunk2__f2simple_array__immutable(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  u8 retval = __pure__f2simple_array__immutable(this);
  ptype_access_num__decr(pool_index);
  return retval;
}

void pfunk2__f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  __pure__f2simple_array__immutable__set(this, value);
  ptype_access_num__decr(pool_index);
}

u64 pfunk2__f2simple_array__length(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2simple_array__length(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return length;
}

f2ptr pfunk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause) {
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int length = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2array__elt error: index out of range.");
  }
  f2ptr rv = __pure__f2simple_array__elt(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

f2ptr pfunk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  
  int pool_index = __f2ptr__pool_index(this);
  
  pool__pause_gc(pool_index);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__memblock__render_write_activated__set(this, 1);
  u64 length     = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2array__elt__set__trace_depth error: index out of range.");
  }
  __pure__f2simple_array__elt__set(this, index, value);
  ptype_access_num__decr(pool_index);
  pool__resume_gc(pool_index);
  return nil;
}

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_simple_array);
}
f2ptr f2__simple_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__simple_array__is_type(cause, x));}
f2ptr f2__simple_array__new(f2ptr cause, f2ptr length) {return f2simple_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));}
f2ptr f2__simple_array__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2simple_array__length(x, cause));}
f2ptr f2__simple_array__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2simple_array__elt(x, f2integer__i(y, cause), cause);}
f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2simple_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}

def_pcfunk1(simple_array__is_type, x, return f2__simple_array__is_type(this_cause, x));
def_pcfunk1(simple_array__new, length, return f2__simple_array__new(this_cause, length));
def_pcfunk1(simple_array__length, x, return f2__simple_array__length(this_cause, x));
def_pcfunk2(simple_array__elt, x, y, return f2__simple_array__elt(this_cause, x, y));
def_pcfunk3(simple_array__elt__set, x, y, z, return f2__simple_array__elt__set(this_cause, x, y, z));

f2ptr f2__simple_array__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk;
  }
  return nil;
}

f2ptr f2__simple_array__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk;
  }
  return nil;
}

f2ptr f2__simple_array__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk;
  }
  return nil;
}

f2ptr f2simple_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk);}
  {char* slot_name = "new_copy"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_simple_array.new_copy__funk);}
  {char* slot_name = "length"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk, nil, nil);}
  {char* slot_name = "elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk, nil);}
  return this;
}


// traced_array

f2ptr ptype_traced_array__new(int pool_index, f2ptr cause, u64 length, ptr dptr_ptr) {
  boolean_t tracing_on = raw__cause__is_traced(cause, cause);
  u64 data_byte_num = (sizeof(dptr_t) * length);
  f2ptr traced_array_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_traced_array_block_t) + data_byte_num);
  ptype_traced_array_block_t* traced_array_block = (ptype_traced_array_block_t*)from_ptr(raw__f2ptr_to_ptr(traced_array_f2ptr));
  debug__assert(traced_array_block, nil, "block is nil.");
  //debug__assert(!cause || valid_memblock_ptr(f2ptr_to_ptr(cause)), nil, "valid_memblock_ptr(cause) failed");
  traced_array_block->ptype.ptype = ptype_traced_array;
  traced_array_block->ptype.cause = cause;
  traced_array_block->length      = length;
  if (dptr_ptr) {memcpy(traced_array_block->dptr_data, from_ptr(dptr_ptr), data_byte_num);}
  else {
    int i;
    dptr_t* dptr_iter = (dptr_t*)(traced_array_block->dptr_data);
    for (i = length; i > 0; i --) {
      dptr__init((dptr_t*)dptr_iter, nil, tracing_on, nil, nil);
      dptr_iter  ++;
    }
  }
  memblock__set_render_position_relative_to(traced_array_f2ptr, cause);
  if (tracing_on) {ptype_trace_create(pool_index, cause, traced_array_f2ptr);}
  return traced_array_f2ptr;
}

f2ptr ptype_traced_array__new_from_f2ptrs(int pool_index, f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  boolean_t tracing_on = raw__cause__is_traced(cause, cause);
  u64 data_byte_num = (sizeof(dptr_t) * length);
  f2ptr traced_array_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_traced_array_block_t) + data_byte_num);
  ptype_traced_array_block_t* traced_array_block = (ptype_traced_array_block_t*)from_ptr(raw__f2ptr_to_ptr(traced_array_f2ptr));
  debug__assert(traced_array_block, nil, "block is nil.");
  traced_array_block->ptype.ptype = ptype_traced_array;
  traced_array_block->ptype.cause = cause;
  traced_array_block->length      = length;
  if (f2ptr_ptr) {
    int i;
    f2ptr*  f2ptr_iter = f2ptr_ptr;
    dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      dptr__init((dptr_t*)dptr_iter, *f2ptr_iter, tracing_on, nil, nil);
      f2ptr_iter ++;
      dptr_iter  ++;
    }
  } else {
    int i;
    dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      dptr__init((dptr_t*)dptr_iter, nil, tracing_on, nil, nil);
      dptr_iter  ++;
    }
  }
  memblock__set_render_position_relative_to(traced_array_f2ptr, cause);
  if (tracing_on) {ptype_trace_create(pool_index, cause, traced_array_f2ptr);}
  return traced_array_f2ptr;
}

f2ptr pfunk2__f2traced_array__new(f2ptr cause, u64 length, ptr dptr_ptr) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr this = __pure__f2traced_array__new(pool_index, cause, length, dptr_ptr);
  //if (cause) {ptype_trace_create(pool_index, cause, this);}
  ptype_access_num__decr(pool_index);
  return this;
}

f2ptr pfunk2__f2traced_array__new_from_f2ptrs(f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  int pool_index = this_processor_thread__pool_index(); ptype_access_num__incr(pool_index);
  f2ptr this = __pure__f2traced_array__new_from_f2ptrs(pool_index, cause, length, f2ptr_ptr);
  //if (cause) {ptype_trace_create(pool_index, cause, this);}
  ptype_access_num__decr(pool_index);
  return this;
}

f2ptr pfunk2__f2traced_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(init_array) != ptype_traced_array) {
    ptype_error(cause, init_array, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return f2traced_array__new(cause, length, to_ptr(((ptype_traced_array_block_t*)(from_ptr(f2ptr_to_ptr(init_array))))->dptr_data));
}

u8 pfunk2__f2traced_array__immutable(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  u8 retval = __pure__f2traced_array__immutable(this);
  ptype_access_num__decr(pool_index);
  return retval;
}

void pfunk2__f2traced_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  __pure__f2traced_array__immutable__set(this, value);
  ptype_access_num__decr(pool_index);
}

u64 pfunk2__f2traced_array__length(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return length;
}

f2ptr pfunk2__f2traced_array__elt__trace_depth(f2ptr this, u64 index, f2ptr cause, int trace_depth) {
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2traced_array_elt failed debug assertion: cause is non-null and not a cause.");
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2traced_array__elt error: index out of range.");
  }
  f2ptr return_value = nil;
  if (! raw__cause__is_imaginary__trace_depth(cause, cause, trace_depth - 1)) {
    return_value = __pure__f2traced_array__elt(this, index);
  } else {
    // this is an imaginary cause, so we need to retrieve the correct imaginary value, or the default (non-imaginary or "real") value is returned.
    f2ptr the_real_cause_for_really_thinking_imaginarily = nil;
    f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, the_real_cause_for_really_thinking_imaginarily);
    f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
    f2ptr real_value              = __pure__f2traced_array__elt(this, index);
    return_value = f2__imagination_frame__get_value_from_name_stack__trace_depth(the_real_cause_for_really_thinking_imaginarily, imagination_frame, imagination_name_stack, real_value, trace_depth - 1);
  }
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return return_value;
}

f2ptr pfunk2__f2traced_array__elt(f2ptr this, u64 index, f2ptr cause) {
  return pfunk2__f2traced_array__elt__trace_depth(this, index, cause, 1);
}

f2ptr pfunk2__f2traced_array__elt__set__trace_depth(f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth) {
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2traced_array_elt failed debug assertion: cause is non-null and not a cause.");
  
  int pool_index = __f2ptr__pool_index(this);
  
  pool__pause_gc(pool_index);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__memblock__render_write_activated__set(this, 1);
  u64 length     = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2traced_array__elt__set__trace_depth error: index out of range.");
  }
  if (! raw__cause__is_imaginary__trace_depth(cause, cause, trace_depth - 1)) {
    f2ptr old_elt    = __pure__f2traced_array__elt(this, index);
    f2ptr prev_elts  = __pure__f2traced_array__elt__trace(this, index);
    int   tracing_on = __pure__f2traced_array__elt__tracing_on(this, index);
    pool__resume_gc(pool_index);
    
    f2ptr new_tracing_doublelink = nil;
    f2ptr new_tracing_transframe = nil;
    if (tracing_on && (trace_depth > 0)) {
      f2ptr symbol_old_new = pfunk2__f2traced_array__new(cause, 3, to_ptr(NULL));
      f2traced_array__elt__set__trace_depth(symbol_old_new, 2, cause, value,   trace_depth - 1);
      f2traced_array__elt__set__trace_depth(symbol_old_new, 1, cause, old_elt, trace_depth - 1);
      new_tracing_transframe = f2transframe__new__trace_depth(cause, f2integer__new(cause, raw__system_microseconds_since_1970()), f2cons__new__trace_depth(cause, symbol_old_new, nil, trace_depth - 1), trace_depth - 1);
      new_tracing_doublelink = f2doublelink__new__trace_depth(cause, prev_elts, nil, new_tracing_transframe, trace_depth - 1);
    }
    
    pool__pause_gc(pool_index);
    if (new_tracing_doublelink) {
      if (prev_elts) {
	f2doublelink__next__set__trace_depth(prev_elts, nil, new_tracing_doublelink, trace_depth - 1);
      }
      __pure__f2traced_array__elt__trace__set(this, index, new_tracing_doublelink);
    }
    __pure__f2traced_array__elt__set(this, index, value);
  } else {
    // cause has imaginary effects
    // we first find imagination_link with the correct name if it exists or we allocate a new imagination_link with the cause's imagination's name.
    f2ptr the_real_cause_for_really_thinking_imaginarily = nil;
    f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, the_real_cause_for_really_thinking_imaginarily);
    f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
    f2ptr real_value              = __pure__f2traced_array__elt(this, index);
    f2ptr name = f2cons__car(imagination_name_stack, the_real_cause_for_really_thinking_imaginarily);
    f2ptr next = f2cons__cdr(imagination_name_stack, the_real_cause_for_really_thinking_imaginarily);
    f2ptr slot = f2__imagination_frame__get_slot(the_real_cause_for_really_thinking_imaginarily, imagination_frame, name);
    if (! slot) {
      imagination_frame = raw__imagination_frame__new_with_added_slot__trace_depth(the_real_cause_for_really_thinking_imaginarily, imagination_frame, name, next ? real_value : value, trace_depth - 1);
      __pure__f2traced_array__elt__imagination_frame__set(this, index, imagination_frame);
      if (next) {
	slot = f2__imagination_frame__get_slot(the_real_cause_for_really_thinking_imaginarily, imagination_frame, name);
	release__assert(slot != nil, cause, "pfunk2__f2traced_array__elt__set__trace_depth error 1: !(slot != nil)");
      }
    }
    if (next) {
      release__assert(slot != nil, cause, "pfunk2__f2traced_array__elt__set__trace_depth error 2: !(slot != nil)");
      f2__imagination_link__set_value_from_name_stack__trace_depth(the_real_cause_for_really_thinking_imaginarily, slot, next, value, trace_depth - 1);
    }
  }
  ptype_access_num__decr(pool_index);
  pool__resume_gc(pool_index);
  return nil;
}

f2ptr pfunk2__f2traced_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  return pfunk2__f2traced_array__elt__set__trace_depth(this, index, cause, value, 1);
}

f2ptr pfunk2__f2traced_array__elt__tracing_on(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__tracing_on(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__tracing_on__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__tracing_on__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return nil;
}

f2ptr pfunk2__f2traced_array__elt__trace(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__trace(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__trace__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__trace__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return nil;
}

f2ptr pfunk2__f2traced_array__elt__imagination_frame(f2ptr this, u64 index, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__imagination_frame(this, index);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__imagination_frame__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    ptype_access_num__decr(pool_index);
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__imagination_frame__set(this, index, value);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return nil;
}

boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_traced_array);
}
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__traced_array__is_type(cause, x));}
f2ptr f2__traced_array__new(f2ptr cause, f2ptr length) {return f2traced_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));}
f2ptr f2__traced_array__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2traced_array__length(x, cause));}
f2ptr f2__traced_array__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__tracing_on(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__tracing_on__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__trace(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__trace__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__imagination_frame(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__imagination_frame__set(x, f2integer__i(y, cause), cause, z); return nil;}

def_pcfunk1(traced_array__is_type, x, return f2__traced_array__is_type(this_cause, x));
def_pcfunk1(traced_array__new, length, return f2__traced_array__new(this_cause, length));
def_pcfunk1(traced_array__length, x, return f2__traced_array__length(this_cause, x));
def_pcfunk2(traced_array__elt, x, y, return f2__traced_array__elt(this_cause, x, y));
def_pcfunk3(traced_array__elt__set, x, y, z, return f2__traced_array__elt__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__tracing_on, x, y, return f2__traced_array__elt__tracing_on(this_cause, x, y));
def_pcfunk3(traced_array__elt__tracing_on__set, x, y, z, return f2__traced_array__elt__tracing_on__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__trace, x, y, return f2__traced_array__elt__trace(this_cause, x, y));
def_pcfunk3(traced_array__elt__trace__set, x, y, z, return f2__traced_array__elt__trace__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__imagination_frame, x, y, return f2__traced_array__elt__imagination_frame(this_cause, x, y));
def_pcfunk3(traced_array__elt__imagination_frame__set, x, y, z, return f2__traced_array__elt__imagination_frame__set(this_cause, x, y, z));

//def_pcfunk1(traced_array__length, this, return f2integer__new(this_cause, f2traced_array__length(this, this_cause)));
//def_pcfunk2(traced_array__elt, this, index, return f2traced_array__elt(this, f2integer__i(index, this_cause), this_cause));
//def_pcfunk3(traced_array__elt__set, this, index, value, f2traced_array__elt__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);
//def_pcfunk2(traced_array__elt__tracing_on, this, index, return f2traced_array__elt__tracing_on(this, f2integer__i(index, this_cause), this_cause));
//def_pcfunk3(traced_array__elt__tracing_on__set, this, index, value, f2traced_array__elt__tracing_on__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);
//def_pcfunk2(traced_array__elt__trace, this, index, return f2traced_array__elt__trace(this, f2integer__i(index, this_cause), this_cause));
//def_pcfunk3(traced_array__elt__trace__set, this, index, value, f2traced_array__elt__trace__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);
//def_pcfunk2(traced_array__elt__imagination_frame, this, index, return f2traced_array__elt__imagination_frame(this, f2integer__i(index, this_cause), this_cause));
//def_pcfunk3(traced_array__elt__imagination_frame__set, this, index, value, f2traced_array__elt__imagination_frame__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);

f2ptr f2__traced_array__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk;
  }
  return nil;
}

f2ptr f2__traced_array__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk;
  }
  return nil;
}

f2ptr f2__traced_array__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk;
  }
  return nil;
}

f2ptr f2traced_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk);}
  {char* slot_name = "length"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk, nil, nil);}
  {char* slot_name = "elt"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk, nil);}
  {char* slot_name = "elt-tracing_on"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk, nil);}
  {char* slot_name = "elt-trace"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk, nil);}
  {char* slot_name = "elt-imagination_frame"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name),
									    __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk, nil);}
  return this;
}


// larva

f2ptr ptype_larva__new(int pool_index, f2ptr cause, u32 type) {
  f2ptr larva_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_larva_block_t));
  ptype_larva_block_t* larva_block = (ptype_larva_block_t*)from_ptr(raw__f2ptr_to_ptr(larva_f2ptr));
  debug__assert(larva_block, nil, "block is nil.");
  larva_block->ptype.ptype = ptype_larva;
  larva_block->ptype.cause = cause;
  larva_block->type        = type;
  memblock__set_render_position_relative_to(larva_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, larva_f2ptr);}
  return larva_f2ptr;
}

f2ptr pfunk2__f2larva__new(f2ptr cause, u32 type) {
  int pool_index = this_processor_thread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2larva__new(pool_index, cause, type);
  ptype_access_num__decr(pool_index);
  return retval;
}

u32 pfunk2__f2larva__type(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_larva) {
    ptype_error(cause, this, __funk2.globalenv.ptype_larva__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 type = __pure__f2larva__type(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return type;
}

boolean_t raw__larva__is_type(f2ptr cause, f2ptr x) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_larva);
}
f2ptr f2__larva__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__larva__is_type(cause, x));}
def_pcfunk1(larva__is_type, x, return f2__larva__is_type(this_cause, x));
def_pcfunk1(larva__new, type, return f2larva__new(this_cause, f2integer__i(type, this_cause)));
def_pcfunk1(larva__type, this, return f2integer__new(this_cause, f2larva__type(this, this_cause)));

f2ptr f2__larva__slot__get_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_larva.type__funk;
  }
  return nil;
}

f2ptr f2__larva__slot__set_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  return nil;
}

f2ptr f2__larva__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_larva.new__funk;
  }
  return nil;
}

f2ptr f2larva__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause);
  {char* slot_name = "new"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), nil, nil, __funk2.globalenv.object_type.ptype.ptype_larva.new__funk);}
  {char* slot_name = "type"; f2__primobject_type__add_slot(cause, this, f2symbol__new(cause, strlen(slot_name), (u8*)slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.type__funk, nil, nil);}
  return this;
}


// **

void f2__ptypes__initialize__object_slots() {
  f2ptr cause = initial_cause();
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_integer.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.new__funk = cfunk;}
  {char* str = "i"; __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__i, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.i__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_double.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_double.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.new__funk = cfunk;}
  {char* str = "d"; __funk2.globalenv.object_type.ptype.ptype_double.d__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__d, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.d__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_float.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_float.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.new__funk = cfunk;}
  {char* str = "f"; __funk2.globalenv.object_type.ptype.ptype_float.f__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__f, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.f__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk = cfunk;}
  {char* str = "p"; __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk = cfunk;}
  {char* str = "new_from_f2ptr"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__new_from_f2ptr, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk = cfunk;}
  {char* str = "gfunkptr"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__gfunkptr, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk = cfunk;}
  {char* str = "computer_id"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__computer_id, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk = cfunk;}
  {char* str = "pool_index"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__pool_index, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_mutex.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_mutex.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk = cfunk;}
  {char* str = "lock"; __funk2.globalenv.object_type.ptype.ptype_mutex.lock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__lock, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk = cfunk;}
  {char* str = "unlock"; __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__unlock, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk = cfunk;}
  {char* str = "trylock"; __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__trylock, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_char.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_char.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.new__funk = cfunk;}
  {char* str = "ch"; __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__ch, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.ch__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_string.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_string.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_string.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__elt, this, index, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.elt__funk = cfunk;}
  {char* str = "hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.hash_value__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__elt, this, index, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk = cfunk;}
  {char* str = "hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk = cfunk;}
  {char* str = "bit8-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit8__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk = cfunk;}
  {char* str = "bit8-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit8__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk = cfunk;}
  {char* str = "bit16-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit16__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk = cfunk;}
  {char* str = "bit16-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit16__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk = cfunk;}
  {char* str = "bit32-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit32__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk = cfunk;}
  {char* str = "bit32-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit32__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk = cfunk;}
  {char* str = "bit64-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit64__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk = cfunk;}
  {char* str = "bit64-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit64__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk = cfunk;}
  {char* str = "cfunk_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(chunk__cfunk_jump, this, thread, env, args, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk = cfunk;}
  {char* str = "bytecode_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bytecode_jump, this, thread, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk = cfunk;}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(simple_array__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk = cfunk;}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk = cfunk;}
  {char* str = "elt-tracing_on"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__tracing_on, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk = cfunk;}
  {char* str = "elt-tracing_on-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__tracing_on__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk = cfunk;}
  {char* str = "elt-trace"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__trace, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk = cfunk;}
  {char* str = "elt-trace-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__trace__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk = cfunk;}
  {char* str = "elt-imagination_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__imagination_frame, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk = cfunk;}
  {char* str = "elt-imagination_frame-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__imagination_frame__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk = cfunk;}
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_larva.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk = cfunk;}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.new__funk = cfunk;}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.type__funk = cfunk;}
  
}

// initialize ptypes

void f2__ptypes__initialize() {
  symbol_hash__initialize();
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_processor_mutex__init(&__global_ptype_incr_mutex[pool_index]);
    __global_ptype_access_num[pool_index] = 0;
  }
}



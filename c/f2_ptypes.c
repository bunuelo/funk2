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

//#define F2__PTYPE__TYPE_CHECK

pthread_mutex_t __global_ptype_incr_mutex[memory_pool_num];

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
  assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range."); pthread_mutex_lock(&__global_ptype_incr_mutex[pool_index]);/*while(pthread_mutex_trylock(&__global_ptype_incr_mutex[pool_index])) {sched_yield();}*/
#endif // F2__PTHREAD
}

void ptype_incr_mutex__unlock(int pool_index)  {
#ifdef F2__PTHREAD
  assert(pool_index >= 0 && pool_index < memory_pool_num, nil, "pool_index out of range."); int retval = pthread_mutex_unlock(&__global_ptype_incr_mutex[pool_index]); if (retval) {print_mutex_error(retval);}
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

#ifdef MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP
u64 pfunk2__memblock__creation_microseconds_since_1970(f2ptr this, f2ptr cause) {int pool_index = __f2ptr__pool_index(this); ptype_access_num__incr(pool_index); u64 retval = __pure__memblock__creation_microseconds_since_1970(this); ptype_access_num__decr(pool_index); return retval;}
#endif // MEMORY_OPTION__MEMBLOCK__MICROSECOND_TIMESTAMP

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

bool raw__cause__is_traced(f2ptr cause, f2ptr this) {
  if (! this) {
    return nil;
  }
  debug__assert(raw__causep(this, cause), nil, "raw__cause__is_traced !raw__causep(this, cause)");
  return f2cause__memory_tracing_on(this, cause);
}

void debug__cause__is_imaginary() {
  printf("\ndebug__cause__is_imaginary here.");
}

bool raw__cause__is_imaginary(f2ptr cause, f2ptr this) {
  if (! this) {
    return nil;
  }
  debug__assert(raw__causep(this, cause), nil, "raw__cause__is_imaginary !raw__causep(this, cause)");
  bool return_value = (f2cause__imagination_stack(this, cause) != nil);
  if (return_value) {
    debug__cause__is_imaginary();
  }
  return return_value;
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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(integer__new__slot_funk, this, return f2integer__new(this_cause, f2integer__i(this, this_cause)));
def_pcfunk1(integer__i__slot_funk,   this, return this);

f2ptr f2__integer__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_integer.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_integer.i__funk;
  }
  return nil;
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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(double__new__slot_funk, this, return f2double__new(this_cause, f2double__d(this, this_cause)));
def_pcfunk1(double__d__slot_funk,   this, return f2double__new(this_cause, f2double__d(this, this_cause)));

f2ptr f2__double__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.d__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.d__funk;
  }
  return nil;
}


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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(float__new__slot_funk, this, return f2float__new(this_cause, f2float__f(this_cause, this)));
def_pcfunk1(float__f__slot_funk,   this, return this);

f2ptr f2__float__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_float.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_float.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_float.f__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_float.f__funk;
  }
  return nil;
}


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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(pointer__new__slot_funk, this, return f2pointer__new(this_cause, f2pointer__p(this_cause, this)));
def_pcfunk1(pointer__p__slot_funk,   this, return this);

f2ptr f2__pointer__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk;
  }
  return nil;
}


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
  int pool_index = this_pthread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2gfunkptr__new(pool_index, cause, gf2_computer_id, gf2_pool_index, gf2_pool_address);
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2gfunkptr__new_from_f2ptr(f2ptr cause, f2ptr f2p) {
  int pool_index = this_pthread__pool_index();
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

def_pcfunk3(gfunkptr__new__slot_funk, computer_id, pool_index, pool_address, return f2gfunkptr__new(this_cause, f2integer__i(computer_id, this_cause), f2integer__i(pool_index, this_cause), f2integer__i(pool_address, this_cause)));
def_pcfunk1(gfunkptr__new_from_f2ptr__slot_funk, f2p, return f2gfunkptr__new_from_f2ptr(this_cause, f2p));
def_pcfunk1(gfunkptr__gfunkptr__slot_funk, this, return f2gfunkptr__gfunkptr(this, this_cause));
def_pcfunk1(gfunkptr__computer_id__slot_funk, this, return f2integer__new(this_cause, f2gfunkptr__computer_id(this, this_cause)));
def_pcfunk1(gfunkptr__pool_index__slot_funk, this, return f2integer__new(this_cause, f2gfunkptr__pool_index(this, this_cause)));
def_pcfunk1(gfunkptr__pool_address__slot_funk, this, return f2integer__new(this_cause, f2gfunkptr__pool_address(this, this_cause)));

f2ptr f2__gfunkptr__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__symbol)) {
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


// mutex

f2ptr ptype_mutex__new(int pool_index, f2ptr cause) {
  f2ptr mutex_f2ptr = pool__memblock_f2ptr__new(pool_index, sizeof(ptype_mutex_block_t));
  ptype_mutex_block_t* mutex_block = (ptype_mutex_block_t*)from_ptr(raw__f2ptr_to_ptr(mutex_f2ptr));
  debug__assert(mutex_block, nil, "block is nil.");
  mutex_block->ptype.ptype = ptype_mutex;
  mutex_block->ptype.cause = cause;
  pthread_mutex_init(mutex_block->m, NULL);
  memblock__set_render_position_relative_to(mutex_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, mutex_f2ptr);}
  return mutex_f2ptr;
}

pthread_mutex_t* ptype_mutex__m(f2ptr this, f2ptr cause) {
  int pool_index = __f2ptr__pool_index(this);
  ptype_access_num__incr(pool_index);
  pthread_mutex_t* m = __pure__f2mutex__m(this);
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return m;
}

f2ptr pfunk2__f2mutex__new(f2ptr cause) {
  int pool_index = this_pthread__pool_index();
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
    lock_failed = pthread_mutex_trylock(ptype_mutex__m(this, cause));
  } while (lock_failed);
}

void pfunk2__f2mutex__unlock(f2ptr this, f2ptr cause) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  pthread_mutex_unlock(ptype_mutex__m(this, cause));
}

int pfunk2__f2mutex__trylock(f2ptr this, f2ptr cause) {
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return pthread_mutex_trylock(ptype_mutex__m(this, cause));
}

def_pcfunk0(mutex__new__slot_funk, return f2mutex__new(this_cause));
def_pcfunk1(mutex__lock__slot_funk, this, f2mutex__lock(this, this_cause); return nil);
def_pcfunk1(mutex__unlock__slot_funk, this, f2mutex__unlock(this, this_cause); return nil);
def_pcfunk1(mutex__trylock__slot_funk, this, return f2bool__new(f2mutex__trylock(this, this_cause) == 0));

f2ptr f2__mutex__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(char__new__slot_funk, ch, return f2char__new(this_cause, f2char__ch(ch, this_cause)));
def_pcfunk1(char__ch__slot_funk, this, return this);

f2ptr f2__char__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_char.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_char.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_char.ch__funk;
  }
  return nil;
}


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
  int pool_index = this_pthread__pool_index();
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
  int retval = chararray__hash_value(__pure__f2string__length(this), __pure__f2string__str(this));
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return retval;
}

def_pcfunk1(string__new__slot_funk, str,
	    int str__length = f2string__length(str, this_cause);
	    u8* str__bytes = (u8*)alloca(str__length);
	    f2string__str_copy(str, this_cause, str__bytes);
	    return f2string__new(this_cause, str__length, str__bytes));
def_pcfunk1(string__length__slot_funk, this, return f2integer__new(this_cause, f2string__length(this, this_cause)));
def_pcfunk2(string__elt__slot_funk, this, index, return f2char__new(this_cause, f2string__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk1(string__hash_value__slot_funk, this, return f2integer__new(this_cause, f2string__hash_value(this, this_cause)));

f2ptr f2__string__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_string.hash_value__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_string.hash_value__funk;
  }
  return nil;
}


// symbol

pthread_mutex_t symbol_hash_mutex = PTHREAD_MUTEX_INITIALIZER;

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
bool          __symbol_hash__initialized = 0;
symbol_hash_t __symbol_hash;

void symbol_hash__initialize() {
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
  pthread_mutex_lock(&symbol_hash_mutex);
  if (! __symbol_hash__initialized) {symbol_hash__initialize();}
  ptype_symbol_block_t* symbol_block = NULL;
  
  // search for chararray in hashed symbols
  uint bin_index = chararray__hash_value(length, str) & __symbol_hash.hash_value_bit_mask;
  symbol_hash_node_t* node = __symbol_hash.array[bin_index];
  while (node) {
    symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(node->symbol));
    //if we find a symbol that matches chararray, return it.
    if (!symbol_block->ptype.block.used) {
      printf("\nfound unused symbol."); fflush(stdout);
    }
    if (symbol_block->length == length && (! memcmp(symbol_block->str, str, length))) {
      pthread_mutex_unlock(&symbol_hash_mutex);
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
  symbol_block->hash_value  = chararray__hash_value(length, str);
  
  // and add new symbol to hash table
  symbol_hash__add_symbol(symbol_f2ptr);
  
  pthread_mutex_unlock(&symbol_hash_mutex);
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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(symbol__new__slot_funk, str,
	    int str__length = f2string__length(str, this_cause);
	    u8* str__bytes = (u8*)alloca(str__length);
	    f2string__str_copy(str, this_cause, str__bytes);
	    return f2symbol__new(this_cause, str__length, str__bytes));
def_pcfunk1(symbol__length__slot_funk, this, return f2integer__new(this_cause, f2symbol__length(this, this_cause)));
def_pcfunk2(symbol__elt__slot_funk, this, index, return f2char__new(this_cause, f2symbol__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk1(symbol__hash_value__slot_funk, this, return f2integer__new(this_cause, f2symbol__hash_value(this, this_cause)));

f2ptr f2__symbol__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__funk;
  }
  return nil;
}


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
  int pool_index = this_pthread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr retval = __pure__f2chunk__new(pool_index, cause, length, bytes);
  ptype_access_num__decr(pool_index);
  return retval;
}

f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk) {
  int pool_index = this_pthread__pool_index();
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
  return jump(thread);
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

def_pcfunk1(chunk__new__slot_funk, length, return f2chunk__new(this_cause, f2integer__i(length, this_cause), NULL));
def_pcfunk1(chunk__length__slot_funk, this, return f2integer__new(this_cause, f2chunk__length(this, this_cause)));
def_pcfunk2(chunk__bit8__elt__slot_funk, this, index, return f2pointer__new(this_cause, f2chunk__bit8__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit8__elt__set__slot_funk, this, index, value, f2chunk__bit8__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit16__elt__slot_funk, this, index, return f2pointer__new(this_cause, f2chunk__bit16__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit16__elt__set__slot_funk, this, index, value, f2chunk__bit16__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit32__elt__slot_funk, this, index, return f2pointer__new(this_cause, f2chunk__bit32__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit32__elt__set__slot_funk, this, index, value, f2chunk__bit32__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit64__elt__slot_funk, this, index, return f2pointer__new(this_cause, f2chunk__bit64__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit64__elt__set__slot_funk, this, index, value, f2chunk__bit64__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk4(chunk__cfunk_jump__slot_funk, this, thread, env, args, return f2chunk__cfunk_jump(this, this_cause, thread, env, args));
def_pcfunk2(chunk__bytecode_jump__slot_funk, this, thread, return f2integer__new(this_cause, f2chunk__bytecode_jump(this, this_cause, thread)));

f2ptr f2__chunk__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk;
  }
  return nil;
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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(simple_array__new__slot_funk, length, return f2simple_array__new(this_cause, f2integer__i(length, this_cause), to_ptr(NULL)));
def_pcfunk1(simple_array__length__slot_funk, this, return f2integer__new(this_cause, f2simple_array__length(this, this_cause)));
def_pcfunk2(simple_array__elt__slot_funk, this, index, return f2simple_array__elt(this, f2integer__i(index, this_cause), this_cause));
def_pcfunk3(simple_array__elt__set__slot_funk, this, index, value, f2simple_array__elt__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);

f2ptr f2__simple_array__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk;
  }
  return nil;
}


// traced_array

#ifdef F2__TRACE__ALL_POINTERS
#  define dptr__default__tracing_on __true__symbol
#else
#  define dptr__default__tracing_on nil
#endif // F2__TRACE__ALL_POINTERS

f2ptr ptype_traced_array__new(int pool_index, f2ptr cause, u64 length, ptr dptr_ptr) {
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
      dptr__init((dptr_t*)dptr_iter, nil, dptr__default__tracing_on, nil, nil);
      dptr_iter  ++;
    }
  }
  memblock__set_render_position_relative_to(traced_array_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, traced_array_f2ptr);}
  return traced_array_f2ptr;
}

f2ptr ptype_traced_array__new_from_f2ptrs(int pool_index, f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
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
      dptr__init((dptr_t*)dptr_iter, *f2ptr_iter, dptr__default__tracing_on, nil, nil);
      f2ptr_iter ++;
      dptr_iter  ++;
    }
  } else {
    int i;
    dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      dptr__init((dptr_t*)dptr_iter, nil, dptr__default__tracing_on, nil, nil);
      dptr_iter  ++;
    }
  }
  memblock__set_render_position_relative_to(traced_array_f2ptr, cause);
  if (raw__cause__is_traced(cause, cause)) {ptype_trace_create(pool_index, cause, traced_array_f2ptr);}
  return traced_array_f2ptr;
}

f2ptr pfunk2__f2traced_array__new(f2ptr cause, u64 length, ptr dptr_ptr) {
  int pool_index = this_pthread__pool_index();
  ptype_access_num__incr(pool_index);
  f2ptr this = __pure__f2traced_array__new(pool_index, cause, length, dptr_ptr);
  //if (cause) {ptype_trace_create(pool_index, cause, this);}
  ptype_access_num__decr(pool_index);
  return this;
}

f2ptr pfunk2__f2traced_array__new_from_f2ptrs(f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  int pool_index = this_pthread__pool_index(); ptype_access_num__incr(pool_index);
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

f2ptr pfunk2__f2traced_array__elt(f2ptr this, u64 index, f2ptr cause) {
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
  if (! raw__cause__is_imaginary(cause, cause)) {
    return_value = __pure__f2traced_array__elt(this, index);
  } else {
    // this is an imaginary cause, so we need to retrieve the correct imaginary value, or the default (non-imaginary or "real") value is returned.
    f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, cause);
    f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
    f2ptr real_value              = __pure__f2traced_array__elt(this, index);
    return_value = f2__imagination_frame__get_value_from_name_stack(cause, imagination_frame, imagination_name_stack, real_value);
  }
  __pure__memblock__render_read_activated__set(this, 1);
  ptype_access_num__decr(pool_index);
  return return_value;
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
  if (! raw__cause__is_imaginary(cause, cause)) {
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
      new_tracing_transframe = f2transframe__new__trace_depth(cause, f2cons__new__trace_depth(cause, symbol_old_new, nil, trace_depth - 1), trace_depth - 1);
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
    f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, cause);
    f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
    f2ptr real_value              = __pure__f2traced_array__elt(this, index);
    f2ptr name = f2cons__car(imagination_name_stack, cause);
    f2ptr next = f2cons__cdr(imagination_name_stack, cause);
    f2ptr slot = f2__imagination_frame__get_slot(cause, imagination_frame, name);
    if (! slot) {
      imagination_frame = raw__imagination_frame__new_with_added_slot__trace_depth(cause, imagination_frame, name, next ? real_value : value, trace_depth - 1);
      __pure__f2traced_array__elt__imagination_frame__set(this, index, imagination_frame);
      if (next) {
	slot = f2__imagination_frame__get_slot(cause, imagination_frame, name);
	release__assert(slot != nil, cause, "pfunk2__f2traced_array__elt__set__trace_depth error 1: !(slot != nil)");
      }
    }
    if (next) {
      release__assert(slot != nil, cause, "pfunk2__f2traced_array__elt__set__trace_depth error 2: !(slot != nil)");
      f2__imagination_link__set_value_from_name_stack__trace_depth(cause, slot, next, value, trace_depth - 1);
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

def_pcfunk1(traced_array__new__slot_funk, length, return f2traced_array__new(this_cause, f2integer__i(length, this_cause), to_ptr(NULL)));
def_pcfunk1(traced_array__length__slot_funk, this, return f2integer__new(this_cause, f2traced_array__length(this, this_cause)));
def_pcfunk2(traced_array__elt__slot_funk, this, index, return f2traced_array__elt(this, f2integer__i(index, this_cause), this_cause));
def_pcfunk3(traced_array__elt__set__slot_funk, this, index, value, f2traced_array__elt__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);
def_pcfunk2(traced_array__elt__tracing_on__slot_funk, this, index, return f2traced_array__elt__tracing_on(this, f2integer__i(index, this_cause), this_cause));
def_pcfunk3(traced_array__elt__tracing_on__set__slot_funk, this, index, value, f2traced_array__elt__tracing_on__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);
def_pcfunk2(traced_array__elt__trace__slot_funk, this, index, return f2traced_array__elt__trace(this, f2integer__i(index, this_cause), this_cause));
def_pcfunk3(traced_array__elt__trace__set__slot_funk, this, index, value, f2traced_array__elt__trace__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);
def_pcfunk2(traced_array__elt__imagination_frame__slot_funk, this, index, return f2traced_array__elt__imagination_frame(this, f2integer__i(index, this_cause), this_cause));
def_pcfunk3(traced_array__elt__imagination_frame__set__slot_funk, this, index, value, f2traced_array__elt__imagination_frame__set(this, f2integer__i(index, this_cause), this_cause, value); return nil);

f2ptr f2__traced_array__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk;
  }
  return nil;
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
  int pool_index = this_pthread__pool_index();
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

def_pcfunk1(larva__new__slot_funk, type, return f2larva__new(this_cause, f2integer__i(type, this_cause)));
def_pcfunk1(larva__type__slot_funk, this, return f2integer__new(this_cause, f2larva__type(this, this_cause)));

f2ptr f2__larva__slot_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_larva.new__funk;
  } else if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_larva.type__funk;
  }
  return nil;
}


void f2__ptypes__initialize__object_slots() {
  f2ptr cause = initial_cause();
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(integer__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_integer.new__funk = cfunk;}
  {char* str = "i"; __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(integer__i__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_integer.i__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_double.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(double__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_double.new__funk = cfunk;}
  {char* str = "d"; __funk2.globalenv.object_type.ptype.ptype_double.d__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(double__d__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_double.d__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_float.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(float__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_float.new__funk = cfunk;}
  {char* str = "f"; __funk2.globalenv.object_type.ptype.ptype_float.f__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(float__f__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_float.f__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(pointer__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk = cfunk;}
  {char* str = "p"; __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(pointer__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(gfunkptr__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk = cfunk;}
  {char* str = "new_from_f2ptr"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(gfunkptr__new_from_f2ptr__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk = cfunk;}
  {char* str = "gfunkptr"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(gfunkptr__gfunkptr__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk = cfunk;}
  {char* str = "computer_id"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(gfunkptr__computer_id__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk = cfunk;}
  {char* str = "pool_index"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(gfunkptr__pool_index__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_mutex.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(mutex__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk = cfunk;}
  {char* str = "lock"; __funk2.globalenv.object_type.ptype.ptype_mutex.lock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(mutex__lock__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk = cfunk;}
  {char* str = "unlock"; __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(mutex__unlock__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk = cfunk;}
  {char* str = "trylock"; __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(mutex__trylock__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_char.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(char__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_char.new__funk = cfunk;}
  {char* str = "ch"; __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(char__ch__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_char.ch__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_string.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(string__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_string.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_string.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(string__length__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_string.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(string__elt__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_string.elt__funk = cfunk;}
  {char* str = "hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(string__hash_value__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_string.hash_value__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(symbol__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(symbol__length__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(symbol__elt__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk = cfunk;}
  {char* str = "hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(symbol__hash_value__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_symbol.hash_value__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__length__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk = cfunk;}
  {char* str = "bit8-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit8__elt__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk = cfunk;}
  {char* str = "bit8-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit8__elt__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk = cfunk;}
  {char* str = "bit16-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit16__elt__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk = cfunk;}
  {char* str = "bit16-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit16__elt__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk = cfunk;}
  {char* str = "bit32-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit32__elt__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk = cfunk;}
  {char* str = "bit32-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit32__elt__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk = cfunk;}
  {char* str = "bit64-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit64__elt__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk = cfunk;}
  {char* str = "bit64-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bit64__elt__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk = cfunk;}
  {char* str = "cfunk_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__cfunk_jump__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk = cfunk;}
  {char* str = "bytecode_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(chunk__bytecode_jump__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(simple_array__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(simple_array__length__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(simple_array__elt__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk = cfunk;}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(simple_array__elt__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk = cfunk;}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__length__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk = cfunk;}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk = cfunk;}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk = cfunk;}
  {char* str = "elt-tracing_on"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__tracing_on__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk = cfunk;}
  {char* str = "elt-tracing_on-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__tracing_on__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk = cfunk;}
  {char* str = "elt-trace"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__trace__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk = cfunk;}
  {char* str = "elt-trace-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__trace__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk = cfunk;}
  {char* str = "elt-imagination_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__imagination_frame__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk = cfunk;}
  {char* str = "elt-imagination_frame-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(traced_array__elt__imagination_frame__set__slot_funk, cfunk, 0); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk = cfunk;}
  
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(larva__new__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_larva.new__funk = cfunk;}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var(larva__type__slot_funk, cfunk, 1); __funk2.globalenv.object_type.ptype.ptype_larva.type__funk = cfunk;}
  
}

// initialize ptypes

void f2__ptypes__initialize() {
  int pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    pthread_mutex_init(&__global_ptype_incr_mutex[pool_index], NULL);
    __global_ptype_access_num[pool_index] = 0;
  }
}



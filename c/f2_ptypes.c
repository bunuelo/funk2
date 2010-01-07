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

void print_mutex_error(int retval) {
  switch (retval) {
  case EINVAL: error(nil, "error unlocking ptype_mutex: mutex is not initialized.");              break;
  case EFAULT: error(nil, "error unlocking ptype_mutex: mutex is an invalid pointer.");           break;
  case EPERM:  error(nil, "error unlocking ptype_mutex: the calling thread does not own mutex."); break;
  default:     error(nil, "error unlocking ptype_mutex: unknown error.");                         break;
  }
}

void raw__exp__increment_reference_count(f2ptr this) {
  if (this) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this));
    atomic_inc(&(block->reference_count));
  }
}

boolean_t raw__exp__decrement_reference_count(f2ptr this) {
  boolean_t no_more_references = boolean__false;
  if (this) {
    funk2_memblock_t* block = (funk2_memblock_t*)from_ptr(__f2ptr_to_ptr(this));
    no_more_references      = atomic_dec_and_test(&(block->reference_count));
  }
  return no_more_references;
}

// notify garbage collector of changed references and mutated memory.
void funk2_garbage_collector__know_of_changed_references(funk2_garbage_collector_t* this, f2ptr exp, f2ptr old_value, f2ptr value) {
  if (old_value) {
    boolean_t no_more_references = raw__exp__decrement_reference_count(old_value);
    if (no_more_references) {
      // notify garbage collector to whiten old value if it is not already because it has no references (because of no references it doesn't upset the "no black references white" invariant).
      funk2_garbage_collector__know_of_no_more_references(this, exp);
    }
  }
  if (value) {
    raw__exp__increment_reference_count(value);
  }
  
  // notify garbage collector to grey this memory if it is black because it has been mutated.
  funk2_garbage_collector__know_of_used_exp_mutation(this, exp);
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

#define check_wait_politely() funk2_user_thread_controller__user_check_wait_politely(&(__funk2.user_thread_controller))

// ptype

boolean_t raw__ptype__is_type(f2ptr cause, f2ptr thing) {
  if (thing) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__ptype__is_type(f2ptr cause, f2ptr thing) {return f2bool__new(raw__ptype__is_type(cause, thing));}
def_pcfunk1(ptype__is_type, thing, return f2__ptype__is_type(this_cause, thing));

f2ptr f2__ptype__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("ptype"), (u8*)"ptype");}
def_pcfunk1(ptype__type, this, return f2__ptype__type(this_cause, this));

ptype_t pfunk2__f2ptype__raw(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  ptype_t retval = __pure__f2ptype__raw(this);
  return retval;
}

f2ptr f2__ptype__raw(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2ptype__raw(x, cause));}
def_pcfunk1(ptype__raw, x, return f2__ptype__raw(this_cause, x));

f2ptr pfunk2__f2ptype__cause(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  f2ptr value = __pure__f2ptype__cause(this);
  debug__assert((! value) || raw__cause__is_type(cause, value), nil, "debug error: value is not cause.");
  return value;
}

f2ptr f2__ptype__cause(f2ptr cause, f2ptr x) {
  if (! x) {
    return f2larva__new(cause, 1);
  }
  return f2ptype__cause(x, cause);
}
def_pcfunk1(ptype__cause, x, return f2__ptype__cause(this_cause, x));

f2ptr pfunk2__f2ptype__cause__set(f2ptr this, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  debug__assert((! value) || raw__cause__is_type(cause, value), nil, "debug error: value is not cause.");
  f2ptr old_value = __pure__f2ptype__cause(this);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  __pure__f2ptype__cause(this) = value;
  return nil;
}

f2ptr f2__ptype__cause__set(f2ptr cause, f2ptr x, f2ptr value) {
  if (! x) {
    return f2larva__new(cause, 1);
  }
  f2ptype__cause__set(x, cause, value);
  return nil;
}
def_pcfunk2(ptype__cause__set, x, value, return f2__ptype__cause__set(this_cause, x, value));

u64 pfunk2__f2ptype__creation_nanoseconds_since_1970(f2ptr this, f2ptr cause) {
  return __pure__f2ptype__creation_nanoseconds_since_1970(this);
}

u64 raw__ptype__creation_nanoseconds_since_1970(f2ptr cause, f2ptr this) {
  return pfunk2__f2ptype__creation_nanoseconds_since_1970(this, cause);
}
f2ptr f2__ptype__creation_nanoseconds_since_1970(f2ptr cause, f2ptr this) {
  return f2integer__new(cause, raw__ptype__creation_nanoseconds_since_1970(cause, this));
}
def_pcfunk1(ptype__creation_nanoseconds_since_1970, this, return f2__ptype__creation_nanoseconds_since_1970(this_cause, this));

f2ptr f2ptype__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, nil);
  {char* slot_name = "is_type";                         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.is_type__funk);}
  {char* slot_name = "type";                            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.type__funk);}
  {char* slot_name = "raw";                             f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.raw__funk);}
  {char* slot_name = "cause";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.cause__funk);}
  {char* slot_name = "cause";                           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.cause__set__funk);}
  {char* slot_name = "creation_nanoseconds_since_1970"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.creation_nanoseconds_since_1970__funk);}
  return this;
}

// integer

f2ptr ptype_integer__new(int pool_index, f2ptr cause, s64 i) {
  f2ptr integer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_integer_block_t));
  ptype_integer_block_t* integer_block = (ptype_integer_block_t*)from_ptr(raw__f2ptr_to_ptr(integer_f2ptr));
  debug__assert(integer_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  integer_block->ptype.ptype = ptype_integer;
  integer_block->ptype.cause = cause;
  integer_block->i           = i;
  return integer_f2ptr;
}

f2ptr pfunk2__f2integer__new(f2ptr cause, s64 i) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2integer__new(pool_index, cause, i);
  return retval;
}

s64 pfunk2__f2integer__i(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_integer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_integer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  s64 i = __pure__f2integer__i(this);
  return i;
}

boolean_t raw__integer__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_integer);
}
f2ptr f2__integer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__integer__is_type(cause, x));}
def_pcfunk1(integer__is_type, this, return f2__integer__is_type(this_cause, this));

f2ptr f2__integer__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("integer"), (u8*)"integer");}
def_pcfunk1(integer__type,    this, return f2__integer__type(this_cause, this));

def_pcfunk1(integer__new,     this, return f2integer__new(this_cause, f2integer__i(this, this_cause)));
def_pcfunk1(integer__i,       this, return this);

u64 raw__integer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__i(this, cause);}

f2ptr f2__integer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__integer__eq_hash_value(cause, this));}
def_pcfunk1(integer__eq_hash_value, this, return f2__integer__eq_hash_value(this_cause, this));

f2ptr f2__integer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.i__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_integer.new__funk;
    }
  }
  return nil;
}

f2ptr f2integer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_integer.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_integer.new__funk);}
  {char* slot_name = "i";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_integer.i__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk);}
  return this;
}



// double

f2ptr ptype_double__new(int pool_index, f2ptr cause, double d) {
  f2ptr double_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_double_block_t));
  ptype_double_block_t* double_block = (ptype_double_block_t*)from_ptr(raw__f2ptr_to_ptr(double_f2ptr));
  debug__assert(double_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  double_block->ptype.ptype = ptype_double;
  double_block->ptype.cause = cause;
  double_block->d           = d;
  return double_f2ptr;
}

f2ptr pfunk2__f2double__new(f2ptr cause, double d) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2double__new(pool_index, cause, d);
  return retval;
}

double pfunk2__f2double__d(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_double) {
    ptype_error(cause, this, __funk2.globalenv.ptype_double__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  double d = __pure__f2double__d(this);
  return d;
}

boolean_t raw__double__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_double);
}
f2ptr f2__double__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__double__is_type(cause, x));}
def_pcfunk1(double__is_type, x,    return f2__double__is_type(this_cause, x));

f2ptr f2__double__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("double"), (u8*)"double");}
def_pcfunk1(double__type,    this, return f2__double__type(this_cause, this));

def_pcfunk1(double__new,     this, return f2double__new(this_cause, f2double__d(this, this_cause)));
def_pcfunk1(double__d,       this, return f2double__new(this_cause, f2double__d(this, this_cause)));

u64 raw__double__eq_hash_value(f2ptr cause, f2ptr this) {
  union {
    struct {
      double d;
      u64    zero;
    } s;
    u64 u;
  } stack_memory;
  stack_memory.s.d    = f2double__d(this, cause);
  stack_memory.s.zero = 0;
  u64 eq_hash_value = stack_memory.u;
  return eq_hash_value;
}

f2ptr f2__double__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__double__eq_hash_value(cause, this));}
def_pcfunk1(double__eq_hash_value, this, return f2__double__eq_hash_value(this_cause, this));

f2ptr f2__double__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_double.d__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_double.d__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
  }
  return nil;
}

f2ptr f2__double__slot__execute_funk(f2ptr cause, f2ptr this, f2ptr slot) {
  if (f2__symbol__eq(cause, slot, __funk2.globalenv.object_type.ptype.ptype_double.new__symbol)) {
    return __funk2.globalenv.object_type.ptype.ptype_double.new__funk;
  }
  return nil;
}

f2ptr f2double__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_double.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_double.new__funk);}
  {char* slot_name = "d";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_double.d__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk);}
  return this;
}



// float

f2ptr ptype_float__new(int pool_index, f2ptr cause, float f) {
  f2ptr float_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_float_block_t));
  ptype_float_block_t* float_block = (ptype_float_block_t*)from_ptr(raw__f2ptr_to_ptr(float_f2ptr));
  debug__assert(float_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  float_block->ptype.ptype = ptype_float;
  float_block->ptype.cause = cause;
  float_block->f           = f;
  return float_f2ptr;
}

f2ptr pfunk2__f2float__new(f2ptr cause, float f) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2float__new(pool_index, cause, f);
  return retval;
}

float pfunk2__f2float__f(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_float) {
    ptype_error(cause, this, __funk2.globalenv.ptype_float__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  float f = __pure__f2float__f(this);
  return f;
}

boolean_t raw__float__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_float);
}
f2ptr f2__float__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__float__is_type(cause, x));}
def_pcfunk1(float__is_type, x,    return f2__float__is_type(this_cause, x));

f2ptr f2__float__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("float"), (u8*)"float");}
def_pcfunk1(float__type,    this, return f2__float__type(this_cause, this));

def_pcfunk1(float__new,     this, return f2float__new(this_cause, f2float__f(this_cause, this)));
def_pcfunk1(float__f,       this, return this);

u64 raw__float__eq_hash_value(f2ptr cause, f2ptr this) {
  union {
    u64 u;
    struct {
      float f;
      u64   zero;
    } s;
  } stack_memory;
  stack_memory.s.f    = f2float__f(this, cause);
  stack_memory.s.zero = 0;
  u64 eq_hash_value   = stack_memory.u;
  return eq_hash_value;
}

f2ptr f2__float__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__float__eq_hash_value(cause, this));}
def_pcfunk1(float__eq_hash_value, this, return f2__float__eq_hash_value(this_cause, this));

f2ptr f2__float__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.f__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.f__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_float.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_float.new__funk;
    }
  }
  return nil;
}

f2ptr f2float__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_float.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_float.new__funk);}
  {char* slot_name = "f";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_float.f__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk);}
  return this;
}



// pointer

f2ptr ptype_pointer__new(int pool_index, f2ptr cause, ptr p) {
  f2ptr pointer_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_pointer_block_t));
  ptype_pointer_block_t* pointer_block = (ptype_pointer_block_t*)from_ptr(raw__f2ptr_to_ptr(pointer_f2ptr));
  debug__assert(pointer_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  pointer_block->ptype.ptype = ptype_pointer;
  pointer_block->ptype.cause = cause;
  pointer_block->p           = p;
  return pointer_f2ptr;
}

f2ptr pfunk2__f2pointer__new(f2ptr cause, ptr p) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2pointer__new(pool_index, cause, p);
  return retval;
}

ptr pfunk2__f2pointer__p(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_pointer) {
    ptype_error(cause, this, __funk2.globalenv.ptype_pointer__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  ptr p = __pure__f2pointer__p(this);
  return p;
}

boolean_t raw__pointer__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_pointer);
}
f2ptr f2__pointer__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__pointer__is_type(cause, x));}
def_pcfunk1(pointer__is_type, x,    return f2__pointer__is_type(this_cause, x));

f2ptr f2__pointer__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("pointer"), (u8*)"pointer");}
def_pcfunk1(pointer__type,    this, return f2__pointer__type(this_cause, this));

def_pcfunk1(pointer__new,     this, return f2pointer__new(this_cause, f2pointer__p(this_cause, this)));
def_pcfunk1(pointer__p,       this, return this);

u64 raw__pointer__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2pointer__p(this, cause);}

f2ptr f2__pointer__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__pointer__eq_hash_value(cause, this));}
def_pcfunk1(pointer__eq_hash_value, this, return f2__pointer__eq_hash_value(this_cause, this));

f2ptr f2__pointer__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk;
    }
  }
  return nil;
}

f2ptr f2pointer__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_pointer.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk);}
  {char* slot_name = "p";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk);}
  return this;
}



// gfunkptr

f2ptr ptype_gfunkptr__new(int pool_index, f2ptr cause, computer_id_t gf2_computer_id, pool_index_t gf2_pool_index, pool_address_t gf2_pool_address) {
  f2ptr gfunkptr_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_gfunkptr_block_t));
  ptype_gfunkptr_block_t* gfunkptr_block = (ptype_gfunkptr_block_t*)from_ptr(raw__f2ptr_to_ptr(gfunkptr_f2ptr));
  debug__assert(gfunkptr_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  gfunkptr_block->ptype.ptype = ptype_gfunkptr;
  gfunkptr_block->ptype.cause = cause;
  gfunkptr_block->gfunkptr    = f2ptr__new(gf2_computer_id, gf2_pool_index, gf2_pool_address);
  return gfunkptr_f2ptr;
}

f2ptr pfunk2__f2gfunkptr__new(f2ptr cause, computer_id_t gf2_computer_id, pool_index_t gf2_pool_index, pool_address_t gf2_pool_address) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2gfunkptr__new(pool_index, cause, gf2_computer_id, gf2_pool_index, gf2_pool_address);
  return retval;
}

f2ptr pfunk2__f2gfunkptr__new_from_f2ptr(f2ptr cause, f2ptr f2p) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2gfunkptr__new(pool_index, cause, __f2ptr__computer_id(f2p), __f2ptr__pool_index(f2p), __f2ptr__pool_address(f2p));
  return retval;
}

f2ptr pfunk2__f2gfunkptr__gfunkptr(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = __pure__f2gfunkptr__gfunkptr(this);
  return rv;
}

computer_id_t pfunk2__f2gfunkptr__computer_id(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  computer_id_t rv = __pure__f2gfunkptr__computer_id(this);
  return rv;
}

pool_index_t pfunk2__f2gfunkptr__pool_index(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  pool_index_t rv = __pure__f2gfunkptr__pool_index(this);
  return rv;
}

pool_address_t pfunk2__f2gfunkptr__pool_address(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_gfunkptr) {
    ptype_error(cause, this, __funk2.globalenv.ptype_gfunkptr__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  pool_address_t rv = __pure__f2gfunkptr__pool_address(this);
  return rv;
}

boolean_t raw__gfunkptr__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_gfunkptr);
}
f2ptr f2__gfunkptr__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__gfunkptr__is_type(cause, x));}
def_pcfunk1(gfunkptr__is_type, x, return f2__gfunkptr__is_type(this_cause, x));

f2ptr f2__gfunkptr__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("gfunkptr"), (u8*)"gfunkptr");}
def_pcfunk1(gfunkptr__type, this, return f2__gfunkptr__type(this_cause, this));

def_pcfunk3(gfunkptr__new, computer_id, pool_index, pool_address, return f2gfunkptr__new(this_cause, f2integer__i(computer_id, this_cause), f2integer__i(pool_index, this_cause), f2integer__i(pool_address, this_cause)));
def_pcfunk1(gfunkptr__new_from_f2ptr, f2p, return f2gfunkptr__new_from_f2ptr(this_cause, f2p));
def_pcfunk1(gfunkptr__gfunkptr, this, return f2gfunkptr__gfunkptr(this, this_cause));
def_pcfunk1(gfunkptr__computer_id, this, return f2integer__new(this_cause, f2gfunkptr__computer_id(this, this_cause)));
def_pcfunk1(gfunkptr__pool_index, this, return f2integer__new(this_cause, f2gfunkptr__pool_index(this, this_cause)));
def_pcfunk1(gfunkptr__pool_address, this, return f2integer__new(this_cause, f2gfunkptr__pool_address(this, this_cause)));

u64 raw__gfunkptr__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2gfunkptr__gfunkptr(this, cause);}

f2ptr f2__gfunkptr__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__gfunkptr__eq_hash_value(cause, this));}
def_pcfunk1(gfunkptr__eq_hash_value, this, return f2__gfunkptr__eq_hash_value(this_cause, this));

f2ptr f2__gfunkptr__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk;
    }
  }
  return nil;
}

f2ptr f2gfunkptr__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.is_type__funk);}
  {char* slot_name = "type";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_gfunkptr.type__funk);}
  {char* slot_name = "new";            f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk);}
  {char* slot_name = "new_from_f2ptr"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk);}
  {char* slot_name = "gfunkptr";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk);}
  {char* slot_name = "computer_id";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk);}
  {char* slot_name = "pool_index";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__funk);}
  {char* slot_name = "pool_address";   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_address__funk);}
  {char* slot_name = "eq_hash_value";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_gfunkptr.eq_hash_value__funk);}
  return this;
}



// mutex

f2ptr ptype_mutex__new(int pool_index, f2ptr cause) {
  f2ptr mutex_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_mutex_block_t));
  ptype_mutex_block_t* mutex_block = (ptype_mutex_block_t*)from_ptr(raw__f2ptr_to_ptr(mutex_f2ptr));
  debug__assert(mutex_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  mutex_block->ptype.ptype = ptype_mutex;
  mutex_block->ptype.cause = cause;
  funk2_processor_mutex__init(mutex_block->m);
  return mutex_f2ptr;
}

f2ptr pfunk2__f2mutex__new(f2ptr cause) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2mutex__new(pool_index, cause);
  return retval;
}

funk2_processor_mutex_t* ptype_mutex__m(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  funk2_processor_mutex_t* m = __pure__f2mutex__m(this);
  return m;
}

boolean_t pfunk2__f2mutex__is_locked(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  //int pool_index = this_processor_thread__pool_index();
  boolean_t is_locked = funk2_processor_mutex__is_locked(ptype_mutex__m(this, cause));
  return is_locked;
}

void pfunk2__f2mutex__lock(f2ptr this, f2ptr cause) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_processor_mutex__user_lock(ptype_mutex__m(this, cause));
}

void pfunk2__f2mutex__unlock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  funk2_processor_mutex__unlock(ptype_mutex__m(this, cause));
}

int pfunk2__f2mutex__trylock(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_mutex) {
    ptype_error(cause, this, __funk2.globalenv.ptype_mutex__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int return_value = funk2_processor_mutex__trylock(ptype_mutex__m(this, cause));
  return return_value;
}

boolean_t raw__mutex__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_mutex);
}
f2ptr f2__mutex__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__mutex__is_type(cause, x));}
def_pcfunk1(mutex__is_type, x, return f2__mutex__is_type(this_cause, x));

f2ptr f2__mutex__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("mutex"), (u8*)"mutex");}
def_pcfunk1(mutex__type, x, return f2__mutex__type(this_cause, x));

f2ptr f2__mutex__new(f2ptr cause) {return f2mutex__new(cause);}
def_pcfunk0(mutex__new, return f2__mutex__new(this_cause));

f2ptr f2__mutex__is_locked(f2ptr cause, f2ptr x) {f2mutex__is_locked(x, cause); return nil;}
def_pcfunk1(mutex__is_locked, this, return f2__mutex__is_locked(this_cause, this));

f2ptr f2__mutex__lock(f2ptr cause, f2ptr x) {f2mutex__lock(x, cause); return nil;}
def_pcfunk1(mutex__lock, this, return f2__mutex__lock(this_cause, this));

f2ptr f2__mutex__unlock(f2ptr cause, f2ptr x) {f2mutex__unlock(x, cause); return nil;}
def_pcfunk1(mutex__unlock, this, return f2__mutex__unlock(this_cause, this));

f2ptr f2__mutex__trylock(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2mutex__trylock(x, cause));}
def_pcfunk1(mutex__trylock, this, return f2__mutex__trylock(this_cause, this));

u64 raw__mutex__eq_hash_value(f2ptr cause, f2ptr this) {
  funk2_processor_mutex_t* m = __pure__f2mutex__m(this);
  return funk2_processor_mutex__eq_hash_value(m);
}

f2ptr f2__mutex__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__mutex__eq_hash_value(cause, this));}
def_pcfunk1(mutex__eq_hash_value, this, return f2__mutex__eq_hash_value(this_cause, this));

f2ptr f2__mutex__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutex.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutex.lock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk;
    }
  }
  return nil;
}

f2ptr f2mutex__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutex.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_mutex.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk);}
  {char* slot_name = "lock";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk);}
  {char* slot_name = "trylock";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk);}
  {char* slot_name = "unlock";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk);}
  {char* slot_name = "is_locked";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_mutex.is_locked__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_mutex.eq_hash_value__funk);}
  return this;
}



// char

f2ptr ptype_char__new(int pool_index, f2ptr cause, u64 ch) {
  f2ptr char_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_char_block_t));
  ptype_char_block_t* char_block = (ptype_char_block_t*)from_ptr(raw__f2ptr_to_ptr(char_f2ptr));
  debug__assert(char_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  char_block->ptype.ptype = ptype_char;
  char_block->ptype.cause = cause;
  char_block->ch          = ch;
  return char_f2ptr;
}

f2ptr pfunk2__f2char__new(f2ptr cause, u64 ch) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2char__new(pool_index, cause, ch);
  return retval;
}

u64 pfunk2__f2char__ch(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_char) {
    ptype_error(cause, this, __funk2.globalenv.ptype_char__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 ch = __pure__f2char__ch(this);
  return ch;
}

boolean_t raw__char__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_char);
}
f2ptr f2__char__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__char__is_type(cause, x));}
def_pcfunk1(char__is_type, x, return f2__char__is_type(this_cause, x));

f2ptr f2__char__type(f2ptr cause, f2ptr this) {return f2symbol__new(cause, strlen("char"), (u8*)"char");}
def_pcfunk1(char__type, this, return f2__char__type(this_cause, this));

def_pcfunk1(char__new, ch, return f2char__new(this_cause, f2char__ch(ch, this_cause)));
def_pcfunk1(char__ch, this, return this);

u64 raw__char__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2char__ch(this, cause);}

f2ptr f2__char__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__char__eq_hash_value(cause, this));}
def_pcfunk1(char__eq_hash_value, this, return f2__char__eq_hash_value(this_cause, this));

f2ptr f2__char__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.ch__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_char.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_char.new__funk;
    }
  }
  return nil;
}

f2ptr f2char__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_char.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_char.new__funk);}
  {char* slot_name = "ch";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_char.ch__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk);}
  return this;
}


// string

f2ptr ptype_string__new(int pool_index, f2ptr cause, u64 length, u8* str) {
  f2ptr string_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_string_block_t) + length + 1);
  ptype_string_block_t* string_block = (ptype_string_block_t*)from_ptr(raw__f2ptr_to_ptr(string_f2ptr));
  debug__assert(string_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  string_block->ptype.ptype = ptype_string;
  string_block->ptype.cause = cause;
  string_block->length      = length;
  if (str) {memcpy(string_block->str, str, length);}
  else     {bzero(string_block->str, length);}
  string_block->str[length] = 0x00;
  return string_f2ptr;
}

f2ptr pfunk2__f2string__new(f2ptr cause, u64 length, u8* init) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2string__new(pool_index, cause, length, init);
  return retval;
}

u64 pfunk2__f2string__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  length = __pure__f2string__length(this);
  return length;
}

u8 pfunk2__f2string__elt(f2ptr this, int index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  s8 ch = __pure__f2string__str(this)[index];
  return ch;
}

void pfunk2__f2string__str_copy(f2ptr this, f2ptr cause, u8* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2string__str(this), __pure__f2string__length(this));
}

void raw__string__str_copy(f2ptr cause, f2ptr this, u8* str) {
  f2string__str_copy(this, cause, str);
}

int pfunk2__f2string__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_string) {
    ptype_error(cause, this, __funk2.globalenv.ptype_string__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 len = __pure__f2string__length(this);
  u8* str = __pure__f2string__str(this);
  int retval = (int)chararray__hash_value(len, str);
  return retval;
}

boolean_t raw__string__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_string);
}
f2ptr f2__string__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__string__is_type(cause, x));}
f2ptr f2__string__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("string"), (u8*)"string");}

u64   raw__string__length(f2ptr cause, f2ptr this) {return f2string__length(this, cause);}
f2ptr  f2__string__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__string__length(cause, this));}

f2ptr f2__string__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if ((! raw__string__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, index))) {
    return f2larva__new(cause, 1);
  }
  u64 raw_index = f2integer__i(index, cause);
  return f2char__new(cause, f2string__elt(this, raw_index, cause));
}

u64   raw__string__eq_hash_value(f2ptr cause, f2ptr this) {return f2string__eq_hash_value(this, cause);}
f2ptr  f2__string__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__string__eq_hash_value(cause, this));}

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
def_pcfunk1(string__type, x, return f2__string__type(this_cause, x));
def_pcfunk1(string__new, str, return f2__string__new(this_cause, str));
def_pcfunk1(string__length, this, return f2__string__length(this_cause, this));
def_pcfunk2(string__elt, this, index, return f2__string__elt(this_cause, this, index));
def_pcfunk1(string__eq_hash_value, this, return f2__string__eq_hash_value(this_cause, this));

f2ptr f2__string__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_string.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_string.new__funk;
    }
  }
  return nil;
}

f2ptr f2string__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_string.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_string.new__funk);}
  {char* slot_name = "length";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_string.length__funk);}
  {char* slot_name = "elt";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_string.elt__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk);}
  return this;
}



// symbol

f2ptr ptype_symbol__new(int pool_index, f2ptr cause, u64 length, u8* str) {
  if (length == 0) {
    return nil;
  }
  return funk2_symbol_hash__lookup_or_create_symbol(&(__funk2.ptypes.symbol_hash), pool_index, cause, length, str);
}

f2ptr pfunk2__f2symbol__new(f2ptr cause, u64 length, u8* init) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2symbol__new(pool_index, cause, length, init);
  return retval;
}

u64 pfunk2__f2symbol__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  length     = __pure__f2symbol__length(this);
  return length;
}

u64 pfunk2__f2symbol__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64  eq_hash_value = __pure__f2symbol__eq_hash_value(this);
  return eq_hash_value;
}

u8 pfunk2__f2symbol__elt(f2ptr this, int index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8 ch = __pure__f2symbol__str(this)[index];
  return ch;
}

void pfunk2__f2symbol__str_copy(f2ptr this, f2ptr cause, u8* str) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_symbol) {
    ptype_error(cause, this, __funk2.globalenv.ptype_symbol__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  memcpy(str, __pure__f2symbol__str(this), __pure__f2symbol__length(this));
}

void raw__symbol__str_copy(f2ptr cause, f2ptr this, u8* str) {
  f2symbol__str_copy(this, cause, str);
}

boolean_t raw__symbol__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_symbol);
}
f2ptr f2__symbol__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__symbol__is_type(cause, x));}
f2ptr f2__symbol__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("symbol"), (u8*)"symbol");}

u64   raw__symbol__length(f2ptr cause, f2ptr this) {return f2symbol__length(this, cause);}
f2ptr  f2__symbol__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__symbol__length(cause, this));}

f2ptr f2__symbol__elt(f2ptr cause, f2ptr x, f2ptr y) {return f2integer__new(cause, f2symbol__elt(x, f2integer__i(y, cause), cause));}

u64   raw__symbol__eq_hash_value(f2ptr cause, f2ptr this) {return f2symbol__eq_hash_value(this, cause);}
f2ptr  f2__symbol__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__symbol__eq_hash_value(cause, this));}

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
  if (raw__symbol__is_type(cause, this)) {
    if (this == that) {
      return boolean__true;
    }
  } else {
    return boolean__false;
  }
  if (! raw__symbol__is_type(cause, that)) {return boolean__false;}
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
def_pcfunk1(symbol__type, x, return f2__symbol__type(this_cause, x));
def_pcfunk1(symbol__new, str, return f2__symbol__new(this_cause, str));
def_pcfunk1(symbol__length, this, return f2__symbol__length(this_cause, this));
def_pcfunk2(symbol__elt, this, index, return f2__symbol__elt(this_cause, this, index));
def_pcfunk1(symbol__eq_hash_value, this, return f2__symbol__eq_hash_value(this_cause, this));
def_pcfunk2(symbol__eq, x, y, return f2__symbol__eq(this_cause, x, y));

f2ptr f2__symbol__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk;
    }
  }
  return nil;
}

f2ptr f2symbol__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_symbol.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk);}
  {char* slot_name = "length";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk);}
  {char* slot_name = "elt";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk);}
  return this;
}



// chunk

f2ptr ptype_chunk__new(int pool_index, f2ptr cause, u64 length, byte* bytes) {
  u64 data_byte_num = (sizeof(u8) * length);
  f2ptr chunk_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_chunk_block_t) + data_byte_num);
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  chunk_block->ptype.ptype = ptype_chunk;
  chunk_block->ptype.cause = cause;
  chunk_block->length      = length;
  if (bytes) {memcpy(chunk_block->bytes, bytes, data_byte_num);}
  else       {bzero(chunk_block->bytes, data_byte_num);}
  return chunk_f2ptr;
}

f2ptr ptype_chunk__new_copy(int pool_index, f2ptr cause, f2ptr init_chunk) {
  ptype_chunk_block_t* init_chunk_block = (ptype_chunk_block_t*)(from_ptr(f2ptr_to_ptr(init_chunk)));
  u64 data_byte_num = (sizeof(u8) * init_chunk_block->length);
  f2ptr chunk_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_chunk_block_t));
  ptype_chunk_block_t* chunk_block = (ptype_chunk_block_t*)from_ptr(raw__f2ptr_to_ptr(chunk_f2ptr));
  debug__assert(chunk_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  chunk_block->ptype.ptype = ptype_chunk;
  chunk_block->ptype.cause = cause;
  chunk_block->length      = init_chunk_block->length;
  memcpy(chunk_block->bytes, init_chunk_block->bytes, data_byte_num);
  return chunk_f2ptr;
}

u8* ptype_chunk__bytes(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8* bytes = __pure__f2chunk__bytes(this);
  return bytes;
}

f2ptr pfunk2__f2chunk__new(f2ptr cause, u64 length, byte* bytes) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2chunk__new(pool_index, cause, length, bytes);
  return retval;
}

f2ptr pfunk2__f2chunk__new_copy(f2ptr cause, f2ptr init_chunk) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2chunk__new_copy(pool_index, cause, init_chunk);
  return retval;
}

u64 pfunk2__f2chunk__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2chunk__length(this);
  return length;
}

u64 pfunk2__f2chunk__eq_hash_value(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 len   = __pure__f2chunk__length(this);
  u8* bytes = __pure__f2chunk__bytes(this);
  return (u64)chararray__hash_value(len, bytes);
}

u8 pfunk2__f2chunk__bit8__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u8 retval = __pure__f2chunk__bit8__elt(this, index);
  return retval;
}

void  pfunk2__f2chunk__bit8__elt__set(f2ptr this, u64 index, f2ptr cause, u8 value)   {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
  __pure__f2chunk__bit8__elt__set(this, index, value);
}

u16 pfunk2__f2chunk__bit16__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u16 retval = __pure__f2chunk__bit16__elt(this, index);
  return retval;
}

void pfunk2__f2chunk__bit16__elt__set(f2ptr this, u64 index, f2ptr cause, u16 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit16__elt__set(this, index, value);
}

u32 pfunk2__f2chunk__bit32__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 retval = __pure__f2chunk__bit32__elt(this, index);
  return retval;
}

void pfunk2__f2chunk__bit32__elt__set(f2ptr this, u64 index, f2ptr cause, u32 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit32__elt__set(this, index, value);
}

u64 pfunk2__f2chunk__bit64__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 retval = __pure__f2chunk__bit64__elt(this, index);
  return retval;
}

void pfunk2__f2chunk__bit64__elt__set(f2ptr this, u64 index, f2ptr cause, u64 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  __pure__f2chunk__bit64__elt__set(this, index, value);
}

f2ptr pfunk2__f2chunk__cfunk_jump(f2ptr this, f2ptr cause, f2ptr fiber, f2ptr env, f2ptr args) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  cfunkptr_t jump = (cfunkptr_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  printf("\nchunk-cfunk_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  return jump(cause, fiber, env, args);
}

int pfunk2__f2chunk__bytecode_jump(f2ptr this, f2ptr cause, f2ptr fiber) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  bytecode_jump_t jump = (bytecode_jump_t)(((ptype_chunk_block_t*)from_ptr(f2ptr_to_ptr(this)))->bytes);
  //printf("\nchunk-bytecode_jump: jumping to 0x%08lx", (long)jump); fflush(stdout);
  f2ptr bytecode = nil;
  return jump(fiber, bytecode);
}

f2ptr pfunk2__f2chunk__send(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = f2integer__new(cause, send(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  return rv;
}

f2ptr pfunk2__f2chunk__recv(f2ptr this, f2ptr cause, int start, int length, int fd, int flags) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this); 
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_chunk) {
    ptype_error(cause, this, __funk2.globalenv.ptype_chunk__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  f2ptr rv = f2integer__new(cause, recv(fd, ((u8*)(__pure__f2chunk__bytes(this))) + start, length, flags));
  return rv;
}

boolean_t raw__chunk__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if ((!cause) || (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_chunk);
}
f2ptr f2__chunk__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__chunk__is_type(cause, x));}
f2ptr f2__chunk__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("chunk"), (u8*)"chunk");}
f2ptr f2__chunk__length(f2ptr cause, f2ptr x) {return f2integer__new(cause, f2chunk__length(x, cause));}

u64   raw__chunk__eq_hash_value(f2ptr cause, f2ptr this) {return f2chunk__eq_hash_value(this, cause);}
f2ptr  f2__chunk__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__chunk__eq_hash_value(this, cause));}

def_pcfunk1(chunk__is_type, x, return f2__chunk__is_type(this_cause, x));
def_pcfunk1(chunk__type, x, return f2__chunk__type(this_cause, x));
def_pcfunk1(chunk__new, length, return f2chunk__new(this_cause, f2integer__i(length, this_cause), NULL));
def_pcfunk1(chunk__length, x, return f2__chunk__length(this_cause, x));
def_pcfunk1(chunk__eq_hash_value, x, return f2__chunk__eq_hash_value(this_cause, x));
def_pcfunk2(chunk__bit8__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit8__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit8__elt__set, this, index, value, f2chunk__bit8__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit16__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit16__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit16__elt__set, this, index, value, f2chunk__bit16__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit32__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit32__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit32__elt__set, this, index, value, f2chunk__bit32__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk2(chunk__bit64__elt, this, index, return f2pointer__new(this_cause, f2chunk__bit64__elt(this, this_cause, f2integer__i(index, this_cause))));
def_pcfunk3(chunk__bit64__elt__set, this, index, value, f2chunk__bit64__elt__set(this, this_cause, f2integer__i(index, this_cause), f2pointer__p(value, this_cause)); return nil);
def_pcfunk4(chunk__cfunk_jump, this, fiber, env, args, return f2chunk__cfunk_jump(this, this_cause, fiber, env, args));
def_pcfunk2(chunk__bytecode_jump, this, fiber, return f2integer__new(this_cause, f2chunk__bytecode_jump(this, this_cause, fiber)));

f2ptr f2__chunk__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk;
    }
  }
  return nil;
}

f2ptr f2chunk__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk);}
  {char* slot_name = "type";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.type__funk);}
  {char* slot_name = "new";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk);}
  {char* slot_name = "new_copy";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.new_copy__funk);}
  {char* slot_name = "length";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk);}
  {char* slot_name = "bit8-elt";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk);}
  {char* slot_name = "bit8-elt";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk);}
  {char* slot_name = "bit16-elt";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk);}
  {char* slot_name = "bit16-elt";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk);}
  {char* slot_name = "bit32-elt";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk);}
  {char* slot_name = "bit32-elt";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk);}
  {char* slot_name = "bit64-elt";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk);}
  {char* slot_name = "bit64-elt";     f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk);}
  {char* slot_name = "cfunk_jump";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk);}
  {char* slot_name = "bytecode_jump"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk);}
  return this;
}


// simple_array

f2ptr ptype_simple_array__new(int pool_index, f2ptr cause, u64 length, ptr f2ptr_ptr) {
  u64 data_byte_num = (sizeof(f2ptr) * length);
  f2ptr simple_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_simple_array_block_t) + data_byte_num);
  ptype_simple_array_block_t* simple_array_block = (ptype_simple_array_block_t*)from_ptr(raw__f2ptr_to_ptr(simple_array_f2ptr));
  debug__assert(simple_array_block, nil, "block is nil.");
  //debug__assert(!cause || valid_funk2_memblock_ptr(f2ptr_to_ptr(cause)), nil, "valid_funk2_memblock_ptr(cause) failed");
  if (cause) {raw__exp__increment_reference_count(cause);}
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
  return simple_array_f2ptr;
}

f2ptr pfunk2__f2simple_array__new(f2ptr cause, u64 length, ptr f2ptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2simple_array__new(pool_index, cause, length, f2ptr_ptr);
  return this;
}

f2ptr pfunk2__f2simple_array__new_copy(f2ptr cause, u64 length, f2ptr init_array) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(init_array) != ptype_simple_array) {
    ptype_error(cause, init_array, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  return pfunk2__f2simple_array__new(cause, length, to_ptr(((ptype_simple_array_block_t*)(from_ptr(f2ptr_to_ptr(init_array))))->f2ptr_data));
}

u8 pfunk2__f2simple_array__immutable(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  u8 retval = __pure__f2simple_array__immutable(this);
  return retval;
}

void pfunk2__f2simple_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  __pure__f2simple_array__immutable__set(this, value);
}

u64 pfunk2__f2simple_array__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2simple_array__length(this);
  return length;
}

f2ptr pfunk2__f2simple_array__elt(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int length = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2array__elt error: index out of range.");
  }
  f2ptr rv = __pure__f2simple_array__elt(this, index);
  return rv;
}

f2ptr pfunk2__f2simple_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2array_elt failed debug assertion: cause is non-null and not a cause.");
  
  //int pool_index = __f2ptr__pool_index(this);
  
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_simple_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_simple_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length     = __pure__f2simple_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2array__elt__set__trace_depth error: index out of range.");
  }
  
  f2ptr old_value = __pure__f2simple_array__elt(this, index);
  funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
  
  if (old_value) {
    // protect the old value
    funk2_garbage_collector__know_of_protected_f2ptr(&(__funk2.garbage_collector), old_value);
  }
  
  __pure__f2simple_array__elt__set(this, index, value);
  return nil;
}

boolean_t raw__simple_array__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_simple_array);
}
f2ptr f2__simple_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__simple_array__is_type(cause, x));}
f2ptr f2__simple_array__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("simple_array"), (u8*)"simple_array");}
f2ptr f2__simple_array__new(f2ptr cause, f2ptr length) {return f2simple_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));}

u64 raw__simple_array__length(f2ptr cause, f2ptr this) {return f2simple_array__length(this, cause);}
f2ptr f2__simple_array__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__simple_array__length(cause, this));}

f2ptr raw__simple_array__elt(f2ptr cause, f2ptr this, u64 index) {return f2simple_array__elt(this, index, cause);}
f2ptr f2__simple_array__elt(f2ptr cause, f2ptr this, f2ptr index) {return raw__simple_array__elt(cause, this, f2integer__i(index, cause));}

f2ptr f2__simple_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2simple_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}

u64   raw__simple_array__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)this;}
f2ptr  f2__simple_array__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__simple_array__eq_hash_value(cause, this));}

def_pcfunk1(simple_array__is_type, x, return f2__simple_array__is_type(this_cause, x));
def_pcfunk1(simple_array__type, x, return f2__simple_array__type(this_cause, x));
def_pcfunk1(simple_array__new, length, return f2__simple_array__new(this_cause, length));
def_pcfunk1(simple_array__length, x, return f2__simple_array__length(this_cause, x));
def_pcfunk1(simple_array__eq_hash_value, this, return f2__simple_array__eq_hash_value(this_cause, this));
def_pcfunk2(simple_array__elt, x, y, return f2__simple_array__elt(this_cause, x, y));
def_pcfunk3(simple_array__elt__set, x, y, z, return f2__simple_array__elt__set(this_cause, x, y, z));

f2ptr f2__simple_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk;
    }
  }
  return nil;
}

f2ptr f2simple_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk);}
  {char* slot_name = "type";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk);}
  {char* slot_name = "new";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk);}
  {char* slot_name = "new_copy";      f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_simple_array.new_copy__funk);}
  {char* slot_name = "length";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk);}
  {char* slot_name = "elt";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk);}
  {char* slot_name = "elt";           f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk);}
  return this;
}


// traced_array

f2ptr ptype_traced_array__new(int pool_index, f2ptr cause, u64 length, ptr dptr_ptr) {
  boolean_t tracing_on = raw__cause__is_traced(cause, cause);
  u64 data_byte_num = (sizeof(funk2_dptr_t) * length);
  f2ptr traced_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_traced_array_block_t) + data_byte_num);
  ptype_traced_array_block_t* traced_array_block = (ptype_traced_array_block_t*)from_ptr(raw__f2ptr_to_ptr(traced_array_f2ptr));
  debug__assert(traced_array_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  traced_array_block->ptype.ptype = ptype_traced_array;
  traced_array_block->ptype.cause = cause;
  traced_array_block->length      = length;
  if (dptr_ptr) {memcpy(traced_array_block->dptr_data, from_ptr(dptr_ptr), data_byte_num);}
  else {
    int i;
    funk2_dptr_t* dptr_iter = (funk2_dptr_t*)(traced_array_block->dptr_data);
    for (i = length; i > 0; i --) {
      funk2_dptr__init(dptr_iter, nil, tracing_on, nil, nil, nil, nil);
      dptr_iter  ++;
    }
  }
  return traced_array_f2ptr;
}

f2ptr ptype_traced_array__new_from_f2ptrs(int pool_index, f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  boolean_t tracing_on = raw__cause__is_traced(cause, cause);
  u64 data_byte_num = (sizeof(funk2_dptr_t) * length);
  f2ptr traced_array_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_traced_array_block_t) + data_byte_num);
  ptype_traced_array_block_t* traced_array_block = (ptype_traced_array_block_t*)from_ptr(raw__f2ptr_to_ptr(traced_array_f2ptr));
  debug__assert(traced_array_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  traced_array_block->ptype.ptype = ptype_traced_array;
  traced_array_block->ptype.cause = cause;
  traced_array_block->length      = length;
  if (f2ptr_ptr) {
    int i;
    f2ptr*  f2ptr_iter = f2ptr_ptr;
    funk2_dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      funk2_dptr__init(dptr_iter, *f2ptr_iter, tracing_on, nil, nil, nil, nil);
      f2ptr_iter ++;
      dptr_iter  ++;
    }
  } else {
    int i;
    funk2_dptr_t* dptr_iter  = traced_array_block->dptr_data;
    for (i = length; i > 0; i --) {
      funk2_dptr__init(dptr_iter, nil, tracing_on, nil, nil, nil, nil);
      dptr_iter  ++;
    }
  }
  return traced_array_f2ptr;
}

f2ptr pfunk2__f2traced_array__new(f2ptr cause, u64 length, ptr dptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2traced_array__new(pool_index, cause, length, dptr_ptr);
  return this;
}

f2ptr pfunk2__f2traced_array__new_from_f2ptrs(f2ptr cause, u64 length, f2ptr* f2ptr_ptr) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr this = __pure__f2traced_array__new_from_f2ptrs(pool_index, cause, length, f2ptr_ptr);
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
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  u8 retval = __pure__f2traced_array__immutable(this);
  return retval;
}

void pfunk2__f2traced_array__immutable__set(f2ptr this, f2ptr cause, u8 value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
  __pure__f2traced_array__immutable__set(this, value);
}

u64 pfunk2__f2traced_array__length(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  return length;
}

f2ptr pfunk2__f2traced_array__elt__trace_depth(f2ptr this, u64 index, f2ptr cause, int trace_depth) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2traced_array_elt failed debug assertion: cause is non-null and not a cause.");
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  int length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2traced_array__elt error: index out of range.");
  }
  f2ptr return_value = nil;
  f2ptr this__cause = __pure__f2ptype__cause(this);
  // only apply special memory access effects if we're not looking at our own memory.
  if (cause != this__cause) {
    if (raw__cause__is_imaginary__trace_depth(cause, cause, trace_depth - 1)) {
      // this is an imaginary cause, so we need to retrieve the correct imaginary value, or the default (non-imaginary or "real") value is returned.
      f2ptr the_real_cause_for_really_thinking_imaginarily = nil;
      f2ptr imagination_name_stack  = f2cause__imagination_stack(cause, the_real_cause_for_really_thinking_imaginarily);
      f2ptr imagination_frame       = __pure__f2traced_array__elt__imagination_frame(this, index);
      f2ptr real_value              = __pure__f2traced_array__elt(this, index);
      return_value = f2__imagination_frame__get_value_from_name_stack__trace_depth(the_real_cause_for_really_thinking_imaginarily, imagination_frame, imagination_name_stack, real_value, trace_depth - 1);
    } else {
      return_value = __pure__f2traced_array__elt(this, index);
    }
  } else {
    return_value = __pure__f2traced_array__elt(this, index);
  }
  return return_value;
}

f2ptr pfunk2__f2traced_array__elt(f2ptr this, u64 index, f2ptr cause) {
  return pfunk2__f2traced_array__elt__trace_depth(this, index, cause, 1);
}

f2ptr pfunk2__f2traced_array__elt__set__trace_depth(f2ptr this, u64 index, f2ptr cause, f2ptr value, int trace_depth) {
  check_wait_politely();
  //release__assert((! cause) || raw__causep(cause, nil), nil, "f2traced_array_elt failed debug assertion: cause is non-null and not a cause.");
  
  //int pool_index = __f2ptr__pool_index(this);
  
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length     = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
    //error(nil, "f2traced_array__elt__set__trace_depth error: index out of range.");
  }
  if (! raw__cause__is_imaginary__trace_depth(cause, cause, trace_depth - 1)) {
    f2ptr old_elt    = __pure__f2traced_array__elt(this, index);
    f2ptr prev_elts  = __pure__f2traced_array__elt__trace(this, index);
    int   tracing_on = __pure__f2traced_array__elt__tracing_on(this, index);
    
    f2ptr new_tracing_doublelink = nil;
    f2ptr new_tracing_transframe = nil;
    if (tracing_on && (trace_depth > 0)) {
      f2ptr symbol_old_new = pfunk2__f2traced_array__new(cause, 3, to_ptr(NULL));
      f2traced_array__elt__set__trace_depth(symbol_old_new, 2, cause, value,   trace_depth - 1);
      f2traced_array__elt__set__trace_depth(symbol_old_new, 1, cause, old_elt, trace_depth - 1);
      f2ptr symbol_old_news = f2cons__new__trace_depth(cause, symbol_old_new, nil, trace_depth - 1);
      new_tracing_transframe = f2transframe__new__trace_depth(cause, f2integer__new(cause, raw__nanoseconds_since_1970()), symbol_old_news, trace_depth - 1);
      new_tracing_doublelink = f2doublelink__new__trace_depth(cause, prev_elts, nil, new_tracing_transframe, trace_depth - 1);
    }
    
    if (new_tracing_doublelink) {
      if (prev_elts) {
	f2doublelink__next__set__trace_depth(prev_elts, nil, new_tracing_doublelink, trace_depth - 1);
      }
      __pure__f2traced_array__elt__trace__set(this, index, new_tracing_doublelink);
    }
    
    f2ptr old_value = __pure__f2traced_array__elt(this, index);
    
    funk2_garbage_collector__know_of_changed_references(&(__funk2.garbage_collector), this, old_value, value);
    
    if (old_value) {
      // protect the old value
      funk2_garbage_collector__know_of_protected_f2ptr(&(__funk2.garbage_collector), old_value);
    }
    
    __pure__f2traced_array__elt__set(this, index, value);
    
    // after setting value, execute mutate_funks
    {
      f2ptr mutate_funks = __pure__f2traced_array__elt__mutate_funks(this, index);
      if (funkable_iter) {
	f2ptr funkable_iter = mutate_funks;
	f2ptr fiber         = f2__scheduler__processor_thread_current_fiber(this_processor_thread__pool_index());
	f2ptr args          = f2cons__new__trace_depth(cause, value, f2cons__new__trace_depth(cause, old_value, trace_depth - 1), trace_depth - 1);
	while (funkable_iter) {
	  f2ptr funkable = f2cons__car__trace_depth(funkable_iter, cause, trace_depth - 1);
	  f2ptr mutate_funk_value = f2__force_funk_apply(cause, fiber, funkable, args);
	  if (raw__larva__is_type(cause, mutate_funk_value)) {
	    return mutate_funk_value;
	  }
	}
      }
    }
    
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
  return nil;
}

f2ptr pfunk2__f2traced_array__elt__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  return pfunk2__f2traced_array__elt__set__trace_depth(this, index, cause, value, 1);
}

f2ptr pfunk2__f2traced_array__elt__tracing_on(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__tracing_on(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__tracing_on__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__tracing_on__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__trace(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__trace(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__trace__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__trace__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__imagination_frame(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__imagination_frame(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__imagination_frame__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__imagination_frame__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__mutate_funks(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__mutate_funks(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__mutate_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__mutate_funks__set(this, index, value);
  return nil;
}


f2ptr pfunk2__f2traced_array__elt__read_funks(f2ptr this, u64 index, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  f2ptr rv = __pure__f2traced_array__elt__read_funks(this, index);
  return rv;
}

f2ptr pfunk2__f2traced_array__elt__read_funks__set(f2ptr this, u64 index, f2ptr cause, f2ptr value) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_traced_array) {
    ptype_error(cause, this, __funk2.globalenv.ptype_traced_array__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u64 length = __pure__f2traced_array__length(this);
  if (index < 0 || index >= length) {
    return pfunk2__f2larva__new(cause, larva_type__array_index_out_of_bounds);
  }
  __pure__f2traced_array__elt__read_funks__set(this, index, value);
  return nil;
}


boolean_t raw__traced_array__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_traced_array);
}
f2ptr f2__traced_array__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__traced_array__is_type(cause, x));}
f2ptr f2__traced_array__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("traced_array"), (u8*)"traced_array");}
f2ptr f2__traced_array__new(f2ptr cause, f2ptr length) {return f2traced_array__new(cause, f2integer__i(length, cause), to_ptr(NULL));}

u64   raw__traced_array__length(f2ptr cause, f2ptr this) {return f2traced_array__length(this, cause);}
f2ptr  f2__traced_array__length(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__traced_array__length(cause, this));}

f2ptr raw__traced_array__elt(f2ptr cause, f2ptr this, u64   index) {return f2traced_array__elt(this, index, cause);}
f2ptr  f2__traced_array__elt(f2ptr cause, f2ptr this, f2ptr index) {return raw__traced_array__elt(cause, this, f2integer__i(index, cause));}

f2ptr f2__traced_array__elt__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__tracing_on(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__tracing_on(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__tracing_on__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__tracing_on__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__trace(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__trace(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__trace__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__trace__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__imagination_frame(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__imagination_frame(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__imagination_frame__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__imagination_frame__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__mutate_funks(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__mutate_funks(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__mutate_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__mutate_funks__set(x, f2integer__i(y, cause), cause, z); return nil;}
f2ptr f2__traced_array__elt__read_funks(f2ptr cause, f2ptr x, f2ptr y) {return f2traced_array__elt__read_funks(x, f2integer__i(y, cause), cause);}
f2ptr f2__traced_array__elt__read_funks__set(f2ptr cause, f2ptr x, f2ptr y, f2ptr z) {f2traced_array__elt__read_funks__set(x, f2integer__i(y, cause), cause, z); return nil;}

def_pcfunk1(traced_array__is_type, x, return f2__traced_array__is_type(this_cause, x));
def_pcfunk1(traced_array__type, x, return f2__traced_array__type(this_cause, x));
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
def_pcfunk2(traced_array__elt__mutate_funks, x, y, return f2__traced_array__elt__mutate_funks(this_cause, x, y));
def_pcfunk3(traced_array__elt__mutate_funks__set, x, y, z, return f2__traced_array__elt__mutate_funks__set(this_cause, x, y, z));
def_pcfunk2(traced_array__elt__read_funks, x, y, return f2__traced_array__elt__read_funks(this_cause, x, y));
def_pcfunk3(traced_array__elt__read_funks__set, x, y, z, return f2__traced_array__elt__read_funks__set(this_cause, x, y, z));

u64   raw__traced_array__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)this;}
f2ptr  f2__traced_array__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__traced_array__eq_hash_value(cause, this));}
def_pcfunk1(traced_array__eq_hash_value, this, return f2__traced_array__eq_hash_value(this_cause, this));

f2ptr f2__traced_array__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk;
    } else if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk;
    }
  }
  return nil;
}

f2ptr f2traced_array__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";                f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk);}
  {char* slot_name = "type";                   f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk);}
  {char* slot_name = "new";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk);}
  {char* slot_name = "length";                 f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk);}
  {char* slot_name = "eq_hash_value";          f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk);}
  {char* slot_name = "elt";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk);}
  {char* slot_name = "elt";                    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk);}
  {char* slot_name = "elt-tracing_on";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk);}
  {char* slot_name = "elt-tracing_on";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk);}
  {char* slot_name = "elt-trace";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk);}
  {char* slot_name = "elt-trace";              f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk);}
  {char* slot_name = "elt-imagination_frame";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk);}
  {char* slot_name = "elt-imagination_frame";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk);}
  {char* slot_name = "elt-mutate_funks";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk);}
  {char* slot_name = "elt-mutate_funks_frame"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk);}
  {char* slot_name = "elt-read_funks";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk);}
  {char* slot_name = "elt-read_funks";         f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk);}
  return this;
}


// larva

f2ptr ptype_larva__new(int pool_index, f2ptr cause, u32 larva_type) {
  f2ptr larva_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_larva_block_t));
  ptype_larva_block_t* larva_block = (ptype_larva_block_t*)from_ptr(raw__f2ptr_to_ptr(larva_f2ptr));
  debug__assert(larva_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  larva_block->ptype.ptype = ptype_larva;
  larva_block->ptype.cause = cause;
  larva_block->larva_type  = larva_type;
  return larva_f2ptr;
}

f2ptr pfunk2__f2larva__new(f2ptr cause, u32 larva_type) {
  check_wait_politely();
  int pool_index = this_processor_thread__pool_index();
  f2ptr retval = __pure__f2larva__new(pool_index, cause, larva_type);
  return retval;
}

u32 pfunk2__f2larva__larva_type(f2ptr this, f2ptr cause) {
  check_wait_politely();
  //int pool_index = __f2ptr__pool_index(this);
#ifdef F2__PTYPE__TYPE_CHECK
  if (__pure__f2ptype__raw(this) != ptype_larva) {
    ptype_error(cause, this, __funk2.globalenv.ptype_larva__symbol);
  }
#endif // F2__PTYPE__TYPE_CHECK
  u32 type = __pure__f2larva__larva_type(this);
  return type;
}

boolean_t raw__larva__is_type(f2ptr cause, f2ptr x) {
  check_wait_politely();
#ifdef F2__PTYPE__TYPE_CHECK
  if (cause && (! raw__cause__is_type(nil, cause))) {error(nil, "cause is not cause.");}
#endif // F2__PTYPE__TYPE_CHECK
  return (x && f2ptype__raw(x, cause) == ptype_larva);
}
f2ptr f2__larva__is_type(f2ptr cause, f2ptr x) {return f2bool__new(raw__larva__is_type(cause, x));}
def_pcfunk1(larva__is_type, x, return f2__larva__is_type(this_cause, x));

f2ptr f2__larva__type(f2ptr cause, f2ptr x) {return f2symbol__new(cause, strlen("larva"), (u8*)"larva");}
def_pcfunk1(larva__type, x, return f2__larva__type(this_cause, x));

def_pcfunk1(larva__new, type, return f2larva__new(this_cause, f2integer__i(type, this_cause)));
def_pcfunk1(larva__larva_type, this, return f2integer__new(this_cause, f2larva__larva_type(this, this_cause)));

u64 raw__larva__eq_hash_value(f2ptr cause, f2ptr this) {return (u64)f2larva__larva_type(this, cause);}

f2ptr f2__larva__eq_hash_value(f2ptr cause, f2ptr this) {return f2integer__new(cause, raw__larva__eq_hash_value(cause, this));}
def_pcfunk1(larva__eq_hash_value, this, return f2__larva__eq_hash_value(this_cause, this));

f2ptr f2__larva__slot__type_funk(f2ptr cause, f2ptr this, f2ptr slot_type, f2ptr slot_name) {
  if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.get__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.type__funk;
    }
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.set__symbol)) {
  } else if (f2__symbol__eq(cause, slot_type, __funk2.globalenv.execute__symbol)) {
    if (f2__symbol__eq(cause, slot_name, __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol)) {
      return __funk2.globalenv.object_type.ptype.ptype_larva.new__funk;
    }
  }
  return nil;
}

f2ptr f2larva__primobject_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2cons__new(cause, f2symbol__new(cause, strlen("ptype"), (u8*)"ptype"), nil));
  {char* slot_name = "is_type";    f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk);}
  {char* slot_name = "type";       f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_larva.type__funk);}
  {char* slot_name = "new";        f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_larva.new__funk);}
  {char* slot_name = "larva_type"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk);}
  {char* slot_name = "eq_hash_value"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol, new__symbol(cause, slot_name),     __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk);}
  return this;
}



// symbol_hash

void funk2_symbol_hash__init(funk2_symbol_hash_t* this) {
  funk2_processor_mutex__init(&(this->mutex));
  this->array               = (funk2_symbol_hash_node_t**)from_ptr(f2__malloc(sizeof(funk2_symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH));
  bzero(this->array, sizeof(funk2_symbol_hash_node_t*) * SYMBOL_HASH__INITIAL_ARRAY_LENGTH);
  this->total_symbol_num    = 0;
  this->eq_hash_value_bit_mask = SYMBOL_HASH__INITIAL_ARRAY_LENGTH - 1; // assumes SYMBOL_HASH__INITIAL_ARRAY_LENGTH is power of 2
  this->array_length        = SYMBOL_HASH__INITIAL_ARRAY_LENGTH;
}

void funk2_symbol_hash__destroy(funk2_symbol_hash_t* this) {
  {
    funk2_symbol_hash_node_t** array_iter = this->array;
    funk2_symbol_hash_node_t*  node_iter;
    int i;
    for (i = this->array_length; i > 0; i --) {
      node_iter = *array_iter;
      while (node_iter) {
	funk2_symbol_hash_node_t* next = node_iter->next;
	f2__free(to_ptr(node_iter));
	node_iter = next;
      }
      array_iter ++;
    }
  }
  f2__free(to_ptr(this->array));
}

void funk2_symbol_hash__reinit(funk2_symbol_hash_t* this) {
  funk2_symbol_hash__destroy(this);
  funk2_symbol_hash__init(this);
}

void funk2_symbol_hash__add_symbol(funk2_symbol_hash_t* this, f2ptr symbol_f2ptr) {
  ptype_symbol_block_t*     symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(symbol_f2ptr));
  u64                       bin_index    = symbol_block->eq_hash_value & (this->eq_hash_value_bit_mask);
  funk2_symbol_hash_node_t* new_node     = (funk2_symbol_hash_node_t*)from_ptr(f2__malloc(sizeof(funk2_symbol_hash_node_t)));
  new_node->symbol = symbol_f2ptr;
  new_node->next = this->array[bin_index];
  this->array[bin_index] = new_node;
}

f2ptr funk2_symbol_hash__lookup_symbol__thread_unsafe(funk2_symbol_hash_t* this, u64 length, u8* str) {
  ptype_symbol_block_t* symbol_block = NULL;
  // search for chararray in hashed symbols
  u64 bin_index = (u64)((u64)chararray__hash_value(length, str) & (u64)(this->eq_hash_value_bit_mask));
  funk2_symbol_hash_node_t* node = (this->array[bin_index]);
  while (node) {
    symbol_block = (ptype_symbol_block_t*)from_ptr(f2ptr_to_ptr(node->symbol));
    //if we find a symbol that matches chararray, return it.
    debug__assert(symbol_block->ptype.block.used, nil, "funk2_symbol_hash__lookup_symbol error: found unused symbol.");
    if (symbol_block->length == length && (! memcmp(symbol_block->str, str, length))) {
      funk2_processor_mutex__unlock(&(this->mutex));
      return node->symbol;
    }
    node = node->next;
  }
  return nil;
}

f2ptr funk2_symbol_hash__lookup_symbol(funk2_symbol_hash_t* this, u64 length, u8* str) {
  funk2_processor_mutex__user_lock(&this->mutex);
  f2ptr result = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, length, str);
  funk2_processor_mutex__unlock(&(this->mutex));
  return result;
}

f2ptr funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, u8* str) {
  f2ptr symbol_f2ptr = funk2_symbol_hash__lookup_symbol__thread_unsafe(this, length, str);
  if (symbol_f2ptr) {
    return symbol_f2ptr;
  }
  
  // otherwise, create a new symbol
  symbol_f2ptr = funk2_memory__funk2_memblock_f2ptr__new_from_pool(&(__funk2.memory), pool_index, sizeof(ptype_symbol_block_t) + length + 1);
  ptype_symbol_block_t* symbol_block = (ptype_symbol_block_t*)from_ptr(raw__f2ptr_to_ptr(symbol_f2ptr));
  debug__assert(symbol_block, nil, "block is nil.");
  if (cause) {raw__exp__increment_reference_count(cause);}
  symbol_block->ptype.ptype = ptype_symbol;
  symbol_block->ptype.cause = cause;
  symbol_block->length      = length;
  if (str) {memcpy(symbol_block->str, str, length);}
  else     {bzero(symbol_block->str, length);}
  symbol_block->str[length] = 0x00;
  symbol_block->eq_hash_value  = (u64)((u64)chararray__hash_value(length, str));
  
  // and add new symbol to hash table
  funk2_symbol_hash__add_symbol(this, symbol_f2ptr);
  return symbol_f2ptr;
}

f2ptr funk2_symbol_hash__lookup_or_create_symbol(funk2_symbol_hash_t* this, int pool_index, f2ptr cause, u64 length, u8* str) {
  funk2_processor_mutex__user_lock(&this->mutex);
  f2ptr result = funk2_symbol_hash__lookup_or_create_symbol__thread_unsafe(this, pool_index, cause, length, str);
  funk2_processor_mutex__unlock(&(this->mutex));
  return result;
}

void funk2_symbol_hash__touch_all_symbols(funk2_symbol_hash_t* this, funk2_garbage_collector_t* garbage_collector) {
  status("funk2_garbage_collector: touch_all_symbols.");
  funk2_symbol_hash_node_t** array_iter = this->array;
  funk2_symbol_hash_node_t*  node_iter;
  int i;
  for (i = this->array_length; i > 0; i --) {
    for (node_iter = array_iter[0]; node_iter; node_iter = node_iter->next) {
      funk2_garbage_collector__touch_f2ptr(garbage_collector, node_iter->symbol);
    }
    array_iter ++;
  }
}

// 2^64 = 18, 446,744,073,709,551,616
//   or = 18  sextillion



// ptypes

void funk2_ptypes__init(funk2_ptypes_t* this) {
  funk2_symbol_hash__init(&(this->symbol_hash));
}

void funk2_ptypes__destroy(funk2_ptypes_t* this) {
  funk2_symbol_hash__destroy(&(this->symbol_hash));
}


// **

void f2__ptypes__initialize__object_slots() {
  f2ptr cause = initial_cause();
  
  // ptype
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.type__funk = never_gc(cfunk);}
  {char* str = "raw"; __funk2.globalenv.object_type.ptype.raw__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__raw, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.raw__funk = never_gc(cfunk);}
  {char* str = "cause"; __funk2.globalenv.object_type.ptype.cause__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__cause, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.cause__funk = never_gc(cfunk);}
  {char* str = "cause-set"; __funk2.globalenv.object_type.ptype.cause__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(ptype__cause__set, this, value, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.cause__set__funk = never_gc(cfunk);}
  {char* str = "creation_nanoseconds_since_1970"; __funk2.globalenv.object_type.ptype.creation_nanoseconds_since_1970__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(ptype__creation_nanoseconds_since_1970, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.creation_nanoseconds_since_1970__funk = never_gc(cfunk);}
  
  // integer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_integer.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_integer.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_integer.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.new__funk = never_gc(cfunk);}
  {char* str = "i"; __funk2.globalenv.object_type.ptype.ptype_integer.i__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__i, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.i__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(integer__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_integer.eq_hash_value__funk = never_gc(cfunk);}
  
  // double
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_double.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_double.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_double.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.new__funk = never_gc(cfunk);}
  {char* str = "d"; __funk2.globalenv.object_type.ptype.ptype_double.d__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__d, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.d__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(double__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_double.eq_hash_value__funk = never_gc(cfunk);}
  
  // float
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_float.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_float.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_float.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.new__funk = never_gc(cfunk);}
  {char* str = "f"; __funk2.globalenv.object_type.ptype.ptype_float.f__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__f, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.f__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(float__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_float.eq_hash_value__funk = never_gc(cfunk);}
  
  // pointer
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_pointer.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_pointer.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.new__funk = never_gc(cfunk);}
  {char* str = "p"; __funk2.globalenv.object_type.ptype.ptype_pointer.p__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__p, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.p__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(pointer__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_pointer.eq_hash_value__funk = never_gc(cfunk);}
  
  // gfunkptr
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new__funk = never_gc(cfunk);}
  {char* str = "new_from_f2ptr"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__new_from_f2ptr, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.new_from_f2ptr__funk = never_gc(cfunk);}
  {char* str = "gfunkptr"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__gfunkptr, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.gfunkptr__funk = never_gc(cfunk);}
  {char* str = "computer_id"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__computer_id, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.computer_id__funk = never_gc(cfunk);}
  {char* str = "pool_index"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__pool_index, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.pool_index__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_gfunkptr.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(gfunkptr__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_gfunkptr.eq_hash_value__funk = never_gc(cfunk);}
  
  // mutex
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_mutex.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_mutex.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_mutex.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.new__funk = never_gc(cfunk);}
  {char* str = "is_locked"; __funk2.globalenv.object_type.ptype.ptype_mutex.is_locked__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__is_locked, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.is_locked__funk = never_gc(cfunk);}
  {char* str = "lock"; __funk2.globalenv.object_type.ptype.ptype_mutex.lock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__lock, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.lock__funk = never_gc(cfunk);}
  {char* str = "unlock"; __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__unlock, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.unlock__funk = never_gc(cfunk);}
  {char* str = "trylock"; __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__trylock, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.trylock__funk = never_gc(cfunk);}
  {char* str = "is_locked"; __funk2.globalenv.object_type.ptype.ptype_mutex.is_locked__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__is_locked, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.is_locked__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_mutex.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(mutex__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_mutex.eq_hash_value__funk = never_gc(cfunk);}
  
  // char
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_char.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_char.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_char.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.new__funk = never_gc(cfunk);}
  {char* str = "ch"; __funk2.globalenv.object_type.ptype.ptype_char.ch__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__ch, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.ch__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(char__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_char.eq_hash_value__funk = never_gc(cfunk);}
  
  // string
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_string.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_string.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_string.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_string.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.length__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_string.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(string__elt, this, index, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.elt__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(string__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_string.eq_hash_value__funk = never_gc(cfunk);}
  
  // symbol
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_symbol.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_symbol.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_symbol.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.length__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_symbol.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(symbol__elt, this, index, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.elt__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(symbol__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_symbol.eq_hash_value__funk = never_gc(cfunk);}
  
  // chunk
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_chunk.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_chunk.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_chunk.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.length__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(chunk__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "bit8-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit8__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__funk = never_gc(cfunk);}
  {char* str = "bit8-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit8__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit8__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit16-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit16__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__funk = never_gc(cfunk);}
  {char* str = "bit16-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit16__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit16__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit32-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit32__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__funk = never_gc(cfunk);}
  {char* str = "bit32-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit32__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit32__elt__set__funk = never_gc(cfunk);}
  {char* str = "bit64-elt"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bit64__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__funk = never_gc(cfunk);}
  {char* str = "bit64-elt-set"; __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(chunk__bit64__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bit64__elt__set__funk = never_gc(cfunk);}
  {char* str = "cfunk_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__4_arg(chunk__cfunk_jump, this, fiber, env, args, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.cfunk_jump__funk = never_gc(cfunk);}
  {char* str = "bytecode_jump"; __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__bytecode_jump, this, fiber, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_chunk.bytecode_jump__funk = never_gc(cfunk);}
  
  // simple_array
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_simple_array.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_simple_array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_simple_array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.length__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(simple_array__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(simple_array__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(simple_array__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_simple_array.elt__set__funk = never_gc(cfunk);}
  
  // traced_array

  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_traced_array.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_traced_array.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.new__funk = never_gc(cfunk);}
  {char* str = "length"; __funk2.globalenv.object_type.ptype.ptype_traced_array.length__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__length, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.length__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(traced_array__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.eq_hash_value__funk = never_gc(cfunk);}
  {char* str = "elt"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__funk = never_gc(cfunk);}
  {char* str = "elt-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__set__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__tracing_on, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__funk = never_gc(cfunk);}
  {char* str = "elt-tracing_on-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__tracing_on__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__tracing_on__set__funk = never_gc(cfunk);}
  {char* str = "elt-trace"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__trace, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__funk = never_gc(cfunk);}
  {char* str = "elt-trace-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__trace__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__trace__set__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__imagination_frame, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__funk = never_gc(cfunk);}
  {char* str = "elt-imagination_frame-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__imagination_frame__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__imagination_frame__set__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__mutate_funks, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__funk = never_gc(cfunk);}
  {char* str = "elt-mutate_funks-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__mutate_funks__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__mutate_funks__set__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(traced_array__elt__read_funks, this, index, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__funk = never_gc(cfunk);}
  {char* str = "elt-read_funks-set"; __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__3_arg(traced_array__elt__read_funks__set, this, index, value, cfunk, 0, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_traced_array.elt__read_funks__set__funk = never_gc(cfunk);}
  
  // larva
  
  {char* str = "is_type"; __funk2.globalenv.object_type.ptype.ptype_larva.is_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__is_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.is_type__funk = never_gc(cfunk);}
  {char* str = "type"; __funk2.globalenv.object_type.ptype.ptype_larva.type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.type__funk = never_gc(cfunk);}
  {char* str = "new"; __funk2.globalenv.object_type.ptype.ptype_larva.new__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__new, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.new__funk = never_gc(cfunk);}
  {char* str = "larva_type"; __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__larva_type, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.larva_type__funk = never_gc(cfunk);}
  {char* str = "eq_hash_value"; __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__1_arg(larva__eq_hash_value, this, cfunk, 1, "primitive peer-to-peer memory layer access funktion"); __funk2.globalenv.object_type.ptype.ptype_larva.eq_hash_value__funk = never_gc(cfunk);}
  
}

// initialize ptypes

void f2__ptypes__initialize() {
  funk2_ptypes__init(&(__funk2.ptypes));
}

void f2__ptypes__destroy() {
  funk2_ptypes__destroy(&(__funk2.ptypes));
}


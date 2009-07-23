// 
// Copyright (c) 2007-2008 Bo Morgan.
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

#ifndef F2__MEMORY__H
#define F2__MEMORY__H

#include "f2_global.h"

#define nil ((f2ptr)0)

#define ptype__total_num 14
#define ptype__min_bits   4

#ifdef F2__PTYPE__C__COMPILING
u8 __ptype__str[][128] = {
  "free_memory",
  "newly_allocated",
  "integer",
  "double",
  "float",
  "pointer",
  "gfunkptr",
  "mutex",
  "char",
  "string",
  "symbol",
  "chunk",
  "simple_array",
  "traced_array",
  "larva",
};
#endif // F2__PTYPE__C__COMPILING

typedef enum ptype_e {
  ptype_free_memory     =  0,
  ptype_newly_allocated =  1,
  ptype_integer         =  2,
  ptype_double          =  3,
  ptype_float           =  4,
  ptype_pointer         =  5,
  ptype_gfunkptr        =  6,
  ptype_mutex           =  7,
  ptype_char            =  8,
  ptype_string          =  9,
  ptype_symbol          = 10,
  ptype_chunk           = 11,
  ptype_simple_array    = 12,
  ptype_traced_array    = 13,
  ptype_larva           = 14,
} ptype_t;

#include "f2_time.h"
//#include "f2_gfunkptr.h"

ptr  f2__malloc(f2size_t byte_num);
void f2__free(ptr this);
ptr  f2__new_alloc(ptr this, f2size_t old_byte_num, f2size_t new_byte_num);

void assert_failed(f2ptr thread, char* filename, int line_num, char* str);

void memblock__set_init_render_xyz(float x, float y, float z);
void memblock__set_init_render_on(u8 render_on);
void memblock__set_init_render_noise(float render_noise);

extern float memblock__render_noise;

void exp__gc_touch_all_referenced(ptr start_block_ptr);

void      pool__pause_gc(int pool_index);
int       pool__try_pause_gc(int pool_index);
void      pool__resume_gc(int pool_index);
boolean_t pool__try_gc(int pool_index);
boolean_t pool__should_run_gc(int pool_index);

void      pause_gc();
int       try_pause_gc();
void      resume_gc();
boolean_t try_gc();
boolean_t should_run_gc();
int       gc__is_disabled();

void  global_environment__set(f2ptr global_environment);
f2ptr global_environment();

void print_gc_stats();

void funk2_memory__handle(funk2_memory_t* memory);

int raw__memory_image__save(char* filename);
int raw__memory_image__load(char* filename);

void f2__memory__initialize();
void f2__memory__destroy();

#endif // F2__MEMORY__H

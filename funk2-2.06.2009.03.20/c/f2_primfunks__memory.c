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

#include "funk2.h"

// function prototypes in f2_memory.h
// 
// ptr   f2__malloc                  (f2size_t byte_num)
// void  f2__free                    (ptr this)
// ptr   f2__new_alloc               (ptr this, f2size_t old_byte_num, f2size_t new_byte_num)
// void  assert_failed               (f2ptr thread, char* filename, int line_num, char* str)
// void  exp__gc_touch_all_referenced(ptr start_block_ptr)
// void  pool__pause_gc              (int pool_index)
// void  pool__resume_gc             (int pool_index)
// boolean_t  pool__try_gc                (int pool_index)
// boolean_t  pool__should_run_gc         (int pool_index)
// void  pause_gc                    ()
// void  resume_gc                   ()
// boolean_t  try_gc                      ()
// boolean_t  should_run_gc               ()
// int   gc__is_disabled             ()
// void  global_environment__set     (f2ptr global_environment)
// f2ptr global_environment          ()
// void  print_gc_stats              ()
// void  f2__memory__initialize      ()
// int   f2__memory_image__save      (char* filename)
// int   f2__memory_image__load      (char* filename)


// ptr   f2__malloc                  (f2size_t byte_num)
def_pcfunk1(f2__malloc, byte_num, return f2pointer__new(this_cause, f2__malloc(f2integer__i(byte_num, this_cause))));

// void  f2__free                    (ptr this)
def_pcfunk1(f2__free, this, f2__free(f2pointer__p(this, this_cause)); return nil);

// ptr   f2__new_alloc               (ptr this, f2size_t old_byte_num, f2size_t new_byte_num)
def_pcfunk3(f2__new_alloc, this, old_byte_num, new_byte_num, return f2pointer__new(this_cause, f2__new_alloc(f2pointer__p(this, this_cause), f2integer__i(old_byte_num, this_cause), f2integer__i(new_byte_num, this_cause))));

// void  assert_failed               (f2ptr thread, char* filename, int line_num, char* str)
def_pcfunk4(assert_failed, thread, filename, line_num, str, assert_failed(thread, (char*)from_ptr(f2pointer__p(filename, this_cause)), f2integer__i(line_num, this_cause), (char*)from_ptr(f2pointer__p(str, this_cause))); return nil);

// void  exp__gc_touch_all_referenced(ptr start_block_ptr)
def_pcfunk1(exp__gc_touch_all_referenced, start_block_ptr, exp__gc_touch_all_referenced(f2pointer__p(start_block_ptr, this_cause)); return nil);

// void  pool__pause_gc              (int pool_index)
def_pcfunk1(pool__pause_gc, pool_index, pool__pause_gc(f2integer__i(pool_index, this_cause)); return nil);

// void  pool__resume_gc             (int pool_index)
def_pcfunk1(pool__resume_gc, pool_index, pool__resume_gc(f2integer__i(pool_index, this_cause)); return nil);

// boolean_t  pool__try_gc                (int pool_index)
def_pcfunk1(pool__try_gc, pool_index, return f2boolean__new(this_cause, pool__try_gc(f2integer__i(pool_index, this_cause))));

// boolean_t  pool__should_run_gc         (int pool_index)
def_pcfunk1(pool__should_run_gc, pool_index, return f2boolean__new(this_cause, f2integer__new(this_cause, pool__should_run_gc(f2integer__i(pool_index, this_cause)))));

// void  pause_gc                    ()
def_pcfunk0(pause_gc, pause_gc(); return nil);

// void  resume_gc                   ()
def_pcfunk0(resume_gc, resume_gc(); return nil);

// boolean_t  try_gc                      ()
def_pcfunk0(try_gc, return f2boolean__new(this_cause, f2integer__new(this_cause, try_gc())));

// boolean_t  should_run_gc               ()
def_pcfunk0(should_run_gc, return f2boolean__new(this_cause, f2integer__new(this_cause, should_run_gc())));

// int   gc__is_disabled             ()
def_pcfunk0(gc__is_disabled, return f2integer__new(this_cause, gc__is_disabled()));;

// void  global_environment__set     (f2ptr global_environment)
def_pcfunk1(global_environment__set, global_environment, global_environment__set(global_environment); return nil);

// f2ptr global_environment          ()
def_pcfunk0(global_environment, return global_environment());

// void  print_gc_stats              ()
def_pcfunk0(print_gc_stats, print_gc_stats(); return nil);

// void  f2__memory__initialize      ()
def_pcfunk0(f2__memory__initialize, f2__memory__initialize(); return nil);

// int   raw__memory_image__save      (char* filename)
def_pcfunk1(f2__memory_image__save, filename, return f2integer__new(this_cause, raw__memory_image__save((char*)from_ptr(f2pointer__p(f2char_pointer__pointer_value(filename, this_cause), this_cause)))));

// int   raw__memory_image__load      (char* filename)
def_pcfunk1(f2__memory_image__load, filename, return f2integer__new(this_cause, raw__memory_image__load((char*)from_ptr(f2pointer__p(f2char_pointer__pointer_value(filename, this_cause), this_cause)))));

void f2__primfunks__memory__initialize() {
  pause_gc();
  f2__primcfunk__init(f2__malloc);
  f2__primcfunk__init(f2__free);
  f2__primcfunk__init(f2__new_alloc);
  f2__primcfunk__init(assert_failed);
  f2__primcfunk__init(exp__gc_touch_all_referenced);
  f2__primcfunk__init(pool__pause_gc);
  f2__primcfunk__init(pool__resume_gc);
  f2__primcfunk__init(pool__try_gc);
  f2__primcfunk__init(pool__should_run_gc);
  f2__primcfunk__init(pause_gc);
  f2__primcfunk__init(resume_gc);
  f2__primcfunk__init(try_gc);
  f2__primcfunk__init(should_run_gc);
  f2__primcfunk__init(gc__is_disabled);
  f2__primcfunk__init(global_environment__set);
  f2__primcfunk__init(global_environment);
  f2__primcfunk__init(print_gc_stats);
  f2__primcfunk__init(f2__memory__initialize);
  f2__primcfunk__init(f2__memory_image__save);
  f2__primcfunk__init(f2__memory_image__load);
  resume_gc();
}


// 
// Copyright (c) 2007-2013 Bo Morgan.
// All rights reserved.
// 
// Authors:
//
//   Bo Morgan (2007-2013): Initial implementation.
// 
// This program is distributed under the terms of the GNU General
// Public License.  See the COPYING file that is distributed with this
// file.
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

#ifndef F2__GARBAGE_COLLECTOR_POOL__TYPES__H
#define F2__GARBAGE_COLLECTOR_POOL__TYPES__H

typedef enum   funk2_garbage_collector_tricolor_e                  funk2_garbage_collector_tricolor_t;
typedef struct funk2_garbage_collector_set_s                       funk2_garbage_collector_set_t;
typedef struct funk2_garbage_collector_mutation_buffer_s           funk2_garbage_collector_mutation_buffer_t;
typedef struct funk2_garbage_collector_no_more_references_buffer_s funk2_garbage_collector_no_more_references_buffer_t;
typedef struct funk2_garbage_collector_protected_f2ptr_buffer_s    funk2_garbage_collector_protected_f2ptr_buffer_t;
typedef struct funk2_garbage_collector_other_grey_buffer_s         funk2_garbage_collector_other_grey_buffer_t;
typedef struct funk2_garbage_collector_pool_s                      funk2_garbage_collector_pool_t;

#endif // F2__GARBAGE_COLLECTOR__TYPES__H

#ifndef F2__GARBAGE_COLLECTOR_POOL__H
#define F2__GARBAGE_COLLECTOR_POOL__H

#include "f2_archconfig.h"
#include "f2_tricolor_set.h"
#include "f2_memorypool.h"
#include "f2_protected_alloc_array.h"
#include "f2_defragmenter.h"
#include "f2_memblock.h"
#include "f2_garbage_collector_block_header.h"

// garbage_collector_mutation_buffer

struct funk2_garbage_collector_mutation_buffer_s {
  funk2_processor_mutex_t mutex;
  u64                     count;
  u64                     alloc_length;
  f2ptr_t*                data;
};

void funk2_garbage_collector_mutation_buffer__init                               (funk2_garbage_collector_mutation_buffer_t* this);
void funk2_garbage_collector_mutation_buffer__destroy                            (funk2_garbage_collector_mutation_buffer_t* this);
void funk2_garbage_collector_mutation_buffer__know_of_mutation                   (funk2_garbage_collector_mutation_buffer_t* this, f2ptr exp);
void funk2_garbage_collector_mutation_buffer__flush_mutation_knowledge_to_gc_pool(funk2_garbage_collector_mutation_buffer_t* this, funk2_garbage_collector_pool_t* pool);
s64  funk2_garbage_collector_mutation_buffer__calculate_save_size                (funk2_garbage_collector_mutation_buffer_t* this);
void funk2_garbage_collector_mutation_buffer__save_to_stream                     (funk2_garbage_collector_mutation_buffer_t* this, int fd);
u64  funk2_garbage_collector_mutation_buffer__save_to_buffer                     (funk2_garbage_collector_mutation_buffer_t* this, u8* initial_buffer);
void funk2_garbage_collector_mutation_buffer__load_from_stream                   (funk2_garbage_collector_mutation_buffer_t* this, int fd);
void funk2_garbage_collector_mutation_buffer__defragment__fix_pointers           (funk2_garbage_collector_mutation_buffer_t* this);

// garbage_collector_no_more_references_buffer

struct funk2_garbage_collector_no_more_references_buffer_s {
  funk2_processor_mutex_t mutex;
  u64                     count;
  u64                     alloc_length;
  f2ptr_t*                data;
};

void funk2_garbage_collector_no_more_references_buffer__init                                         (funk2_garbage_collector_no_more_references_buffer_t* this);
void funk2_garbage_collector_no_more_references_buffer__destroy                                      (funk2_garbage_collector_no_more_references_buffer_t* this);
void funk2_garbage_collector_no_more_references_buffer__know_of_no_more_references                   (funk2_garbage_collector_no_more_references_buffer_t* this, f2ptr exp);
void funk2_garbage_collector_no_more_references_buffer__flush_no_more_references_knowledge_to_gc_pool(funk2_garbage_collector_no_more_references_buffer_t* this, funk2_garbage_collector_pool_t* pool);
s64  funk2_garbage_collector_no_more_references_buffer__calculate_save_size                          (funk2_garbage_collector_no_more_references_buffer_t* this);
void funk2_garbage_collector_no_more_references_buffer__save_to_stream                               (funk2_garbage_collector_no_more_references_buffer_t* this, int fd);
u64  funk2_garbage_collector_no_more_references_buffer__save_to_buffer                               (funk2_garbage_collector_no_more_references_buffer_t* this, u8* initial_buffer);
void funk2_garbage_collector_no_more_references_buffer__load_from_stream                             (funk2_garbage_collector_no_more_references_buffer_t* this, int fd);
void funk2_garbage_collector_no_more_references_buffer__defragment__fix_pointers                     (funk2_garbage_collector_no_more_references_buffer_t* this);

// garbage_collector_protected_f2ptr_buffer

struct funk2_garbage_collector_protected_f2ptr_buffer_s {
  funk2_processor_mutex_t mutex;
  u64                     count;
  u64                     alloc_length;
  f2ptr_t*                data;
};

void funk2_garbage_collector_protected_f2ptr_buffer__init                                         (funk2_garbage_collector_protected_f2ptr_buffer_t* this);
void funk2_garbage_collector_protected_f2ptr_buffer__destroy                                      (funk2_garbage_collector_protected_f2ptr_buffer_t* this);
void funk2_garbage_collector_protected_f2ptr_buffer__know_of_no_more_references                   (funk2_garbage_collector_protected_f2ptr_buffer_t* this, f2ptr exp);
void funk2_garbage_collector_protected_f2ptr_buffer__flush_no_more_references_knowledge_to_gc_pool(funk2_garbage_collector_protected_f2ptr_buffer_t* this, funk2_garbage_collector_pool_t* pool);
void funk2_garbage_collector_protected_f2ptr_buffer__save_to_stream                               (funk2_garbage_collector_protected_f2ptr_buffer_t* this, int fd);
u64  funk2_garbage_collector_protected_f2ptr_buffer__save_to_buffer                               (funk2_garbage_collector_protected_f2ptr_buffer_t* this, u8* initial_buffer);
void funk2_garbage_collector_protected_f2ptr_buffer__load_from_stream                             (funk2_garbage_collector_protected_f2ptr_buffer_t* this, int fd);
void funk2_garbage_collector_protected_f2ptr_buffer__defragment__fix_pointers                     (funk2_garbage_collector_protected_f2ptr_buffer_t* this);

// garbage_collector_other_grey_buffer

struct funk2_garbage_collector_other_grey_buffer_s {
  u64      count;
  u64      alloc_length;
  f2ptr_t* data;
};

void funk2_garbage_collector_other_grey_buffer__init                    (funk2_garbage_collector_other_grey_buffer_t* this);
void funk2_garbage_collector_other_grey_buffer__destroy                 (funk2_garbage_collector_other_grey_buffer_t* this);
void funk2_garbage_collector_other_grey_buffer__know_of_other_grey      (funk2_garbage_collector_other_grey_buffer_t* this, f2ptr exp);
void funk2_garbage_collector_other_grey_buffer__flush_other_greys       (funk2_garbage_collector_other_grey_buffer_t* this, funk2_garbage_collector_pool_t* pool);
s64  funk2_garbage_collector_other_grey_buffer__calculate_save_size     (funk2_garbage_collector_other_grey_buffer_t* this);
void funk2_garbage_collector_other_grey_buffer__save_to_stream          (funk2_garbage_collector_other_grey_buffer_t* this, int fd);
u64  funk2_garbage_collector_other_grey_buffer__save_to_buffer          (funk2_garbage_collector_other_grey_buffer_t* this, u8* initial_buffer);
void funk2_garbage_collector_other_grey_buffer__load_from_stream        (funk2_garbage_collector_other_grey_buffer_t* this, int fd);
void funk2_garbage_collector_other_grey_buffer__defragment__fix_pointers(funk2_garbage_collector_other_grey_buffer_t* this);

// garbage_collector_pool

struct funk2_garbage_collector_pool_s {
  u64                                                 pool_index;
  funk2_tricolor_set_t                                tricolor_set;
  funk2_garbage_collector_mutation_buffer_t           other_mutations;
  funk2_garbage_collector_no_more_references_buffer_t other_no_more_references;
  funk2_garbage_collector_protected_f2ptr_buffer_t    other_protected_f2ptr;
  funk2_protected_alloc_array_fiber_hash_t            protected_alloc_array_fiber_hash;
  boolean_t                                           should_run_gc;
  funk2_garbage_collector_other_grey_buffer_t         other_grey_buffer[memory_pool_num];
  u8*                                                 temporary_load_buffer;
  s64                                                 temporary_load_buffer_offset;
  s64                                                 temporary_load_buffer_size;
  u8*                                                 temporary_save_buffer;
  s64                                                 temporary_save_buffer_size;
};

void      funk2_garbage_collector_pool__init                                     (funk2_garbage_collector_pool_t* this, u64 pool_index);
void      funk2_garbage_collector_pool__destroy                                  (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__add_used_exp                             (funk2_garbage_collector_pool_t* this, f2ptr exp);
void      funk2_garbage_collector_pool__remove_unused_exp                        (funk2_garbage_collector_pool_t* this, f2ptr exp);
void      funk2_garbage_collector_pool__change_used_exp_color                    (funk2_garbage_collector_pool_t* this, f2ptr exp, funk2_tricolor_t new_tricolor);
void      funk2_garbage_collector_pool__init_sets_from_memorypool                (funk2_garbage_collector_pool_t* this, funk2_memorypool_t* pool, u64 pool_index);
boolean_t funk2_garbage_collector_pool__still_have_grey_nodes                    (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__add_protected_alloc_f2ptr                (funk2_garbage_collector_pool_t* this, f2ptr exp);
void      funk2_garbage_collector_pool__signal_enter_protected_region            (funk2_garbage_collector_pool_t* this, char* source_filename, int source_line_num);
void      funk2_garbage_collector_pool__signal_exit_protected_region             (funk2_garbage_collector_pool_t* this, char* source_filename, int source_line_num);
boolean_t funk2_garbage_collector_pool__in_protected_region                      (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__touch_f2ptr                              (funk2_garbage_collector_pool_t* this, f2ptr exp);
void      funk2_garbage_collector_pool__touch_all_protected_alloc_arrays         (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__know_of_used_exp_self_mutation           (funk2_garbage_collector_pool_t* this, f2ptr exp); // assumes called by self  user processor thread
void      funk2_garbage_collector_pool__know_of_used_exp_other_mutation          (funk2_garbage_collector_pool_t* this, f2ptr exp); // assumes called by other user processor thread
void      funk2_garbage_collector_pool__know_of_used_exp_self_no_more_references (funk2_garbage_collector_pool_t* this, f2ptr exp); // assumes called by self  user processor thread
void      funk2_garbage_collector_pool__know_of_used_exp_other_no_more_references(funk2_garbage_collector_pool_t* this, f2ptr exp); // assumes called by other user processor thread
void      funk2_garbage_collector_pool__know_of_used_exp_self_protected_f2ptr    (funk2_garbage_collector_pool_t* this, f2ptr exp); // assumes called by self  user processor thread
void      funk2_garbage_collector_pool__know_of_used_exp_other_protected_f2ptr   (funk2_garbage_collector_pool_t* this, f2ptr exp); // assumes called by other user processor thread
void      funk2_garbage_collector_pool__flush_other_knowledge                    (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__grey_element                             (funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp);
void      funk2_garbage_collector_pool__grey_maybe_other_element                 (funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp);
void      funk2_garbage_collector_pool__grey_referenced_elements_from_dptr       (funk2_garbage_collector_pool_t* this, int pool_index, funk2_dptr_t* dptr);
void      funk2_garbage_collector_pool__grey_referenced_elements                 (funk2_garbage_collector_pool_t* this, int pool_index, f2ptr exp);
void      funk2_garbage_collector_pool__blacken_grey_nodes                       (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__grey_from_other_nodes                    (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__free_white_exps                          (funk2_garbage_collector_pool_t* this);
s64       funk2_garbage_collector_pool__calculate_save_size                      (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__save_to_stream                           (funk2_garbage_collector_pool_t* this, int fd);
void      funk2_garbage_collector_pool__create_save_buffer                       (funk2_garbage_collector_pool_t* this);
void      funk2_garbage_collector_pool__save_buffer_to_stream                    (funk2_garbage_collector_pool_t* this, int fd);
void      funk2_garbage_collector_pool__load_from_stream                         (funk2_garbage_collector_pool_t* this, int fd);
s64       funk2_garbage_collector_pool__load_from_buffer                         (funk2_garbage_collector_pool_t* this, u8* buffer);
void      funk2_garbage_collector_pool__defragment__fix_pointers                 (funk2_garbage_collector_pool_t* this);
boolean_t funk2_garbage_collector_pool__memblock_color_is_valid                  (funk2_garbage_collector_pool_t* this, funk2_memblock_t* memblock);

#endif // F2__GARBAGE_COLLECTOR_POOL__H


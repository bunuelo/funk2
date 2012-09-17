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

#include "funk2.h"

void funk2_defragmenter__init(funk2_defragmenter_t* this) {
  this->total_defragmentation_count = 0;
  this->need_defragmentation        = boolean__false;
  {
    s64 pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_hash__init(&(this->new_old_memory_position_hash[pool_index]), position_hash__bit_num);
    }
  }
}

void funk2_defragmenter__destroy(funk2_defragmenter_t* this) {
  {
    s64 pool_index;
    for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
      funk2_hash__destroy(&(this->new_old_memory_position_hash[pool_index]));
    }
  }
}

void funk2_defragmenter__memory_pool__destroy_memblocks(funk2_defragmenter_t* this, u64 pool_index) {
  funk2_memblock_t* iter          = funk2_memorypool__beginning_of_blocks(&(__funk2.memory.pool[pool_index]));
  funk2_memblock_t* end_of_blocks = funk2_memorypool__end_of_blocks(&(__funk2.memory.pool[pool_index]));
  while(iter < end_of_blocks) {
    if (iter->used) {
      ptype_block_t* block = (ptype_block_t*)iter;
      switch(block->block.ptype) {
      case ptype_scheduler_cmutex: {
	ptype_scheduler_cmutex_block_t* scheduler_cmutex_block = (ptype_scheduler_cmutex_block_t*)block;
	funk2_processor_spinlock__destroy(scheduler_cmutex_block->m);
      } break;
      case ptype_cmutex: {
	ptype_cmutex_block_t* cmutex_block = (ptype_cmutex_block_t*)block;
	funk2_processor_mutex__destroy(cmutex_block->m);
      } break;
      case ptype_scheduler_creadwritelock: {
	ptype_scheduler_creadwritelock_block_t* scheduler_creadwritelock_block = (ptype_scheduler_creadwritelock_block_t*)block;
	funk2_processor_readwritelock__destroy(scheduler_creadwritelock_block->rwlock);
      } break;
      case ptype_creadwritelock: {
	ptype_creadwritelock_block_t* creadwritelock_block = (ptype_creadwritelock_block_t*)block;
	funk2_processor_readwritelock__destroy(creadwritelock_block->rwlock);
      } break;
      default:
	break;
      }
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "funk2_defragmenter__memory_pool__destroy_memblocks test failure: (end_of_blocks != iter) failure.");
}

void funk2_defragmenter__memory_pool__initialize_memblocks(funk2_defragmenter_t* this, u64 pool_index) {
  funk2_memblock_t* iter          = funk2_memorypool__beginning_of_blocks(&(__funk2.memory.pool[pool_index]));
  funk2_memblock_t* end_of_blocks = funk2_memorypool__end_of_blocks(&(__funk2.memory.pool[pool_index]));
  while(iter < end_of_blocks) {
    if (iter->used) {
      ptype_block_t* block = (ptype_block_t*)iter;
      switch(block->block.ptype) {
      case ptype_scheduler_cmutex: {
	ptype_scheduler_cmutex_block_t* scheduler_cmutex_block = (ptype_scheduler_cmutex_block_t*)block;
	funk2_processor_spinlock__init(scheduler_cmutex_block->m);
	if (scheduler_cmutex_block->locked_state) {
	  funk2_processor_spinlock__lock(scheduler_cmutex_block->m);
	}
      } break;
      case ptype_cmutex: {
	ptype_cmutex_block_t* cmutex_block = (ptype_cmutex_block_t*)block;
	funk2_processor_mutex__init(cmutex_block->m);
	if (cmutex_block->locked_state) {
	  funk2_processor_mutex__lock(cmutex_block->m);
	}
      } break;
      case ptype_scheduler_creadwritelock: {
	ptype_scheduler_creadwritelock_block_t* scheduler_creadwritelock_block = (ptype_scheduler_creadwritelock_block_t*)block;
	funk2_processor_readwritelock__init(scheduler_creadwritelock_block->rwlock);
	// we don't current reinitialize readwritelocks to old states.
      } break;
      case ptype_creadwritelock: {
	ptype_creadwritelock_block_t* creadwritelock_block = (ptype_creadwritelock_block_t*)block;
	funk2_processor_readwritelock__init(creadwritelock_block->rwlock);
	// we don't current reinitialize readwritelocks to old states.
      } break;
      default:
	break;
      }
    }
    iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
  }
  release__assert(iter == end_of_blocks, nil, "funk2_defragmenter__memory_pool__destroy_memblocks test failure: (end_of_blocks != iter) failure.");
}

void funk2_defragmenter__memory_pool__move_memory(funk2_defragmenter_t* this, u64 pool_index) {
  status("funk2_defragmenter__memory_pool__move_memory: defragment moving memory.  pool_index=" u64__fstr, pool_index);
  
  funk2_memorypool_t* memorypool       = &(__funk2.memory.pool[pool_index]);
  funk2_memblock_t*   end_of_blocks    = funk2_memorypool__end_of_blocks(memorypool);
  funk2_heap_t*       free_memory_heap = &(memorypool->free_memory_heap);
  
  funk2_hash_t* new_old_memory_position_hash = &(this->new_old_memory_position_hash[pool_index]);
  funk2_hash__destroy(new_old_memory_position_hash);
  funk2_hash__init(new_old_memory_position_hash, position_hash__bit_num);
  
  {
    u64               previous_new_iter__byte_num = 0;
    funk2_memblock_t* iter                        = funk2_memorypool__beginning_of_blocks(memorypool);
    funk2_memblock_t* new_iter                    = iter;
    while (iter < end_of_blocks) {
      u64 iter__byte_num = funk2_memblock__byte_num(iter);
      {
	if (iter->used) {
	  funk2_hash__add(new_old_memory_position_hash, __ptr_to_f2ptr(pool_index, to_ptr(iter)), __ptr_to_f2ptr(pool_index, to_ptr(new_iter)));
	  memmove(new_iter, iter, iter__byte_num);
	  funk2_memblock__previous_byte_num(new_iter) = previous_new_iter__byte_num;
	  previous_new_iter__byte_num = iter__byte_num;
	  new_iter = (funk2_memblock_t*)(((u8*)new_iter) + iter__byte_num);
	} else {
	  funk2_heap__remove(free_memory_heap, (funk2_heap_node_t*)iter);
	}
      }
      iter = (funk2_memblock_t*)(((u8*)iter) + iter__byte_num);
    }
    u64 last_free_block__byte_num = (u64)(((u8*)end_of_blocks) - ((u8*)new_iter));
    memset(new_iter, 0, last_free_block__byte_num); // zero free block entirely before init.
    funk2_memblock__init(new_iter, last_free_block__byte_num, 0);
    funk2_memblock__previous_byte_num(new_iter) = previous_new_iter__byte_num;
    memorypool->last_block_byte_num = last_free_block__byte_num;
    funk2_heap__insert(free_memory_heap, (funk2_heap_node_t*)new_iter);
  }
  
  funk2_memorypool__shrink_last_free_block(memorypool, F2__INITIAL_MEMORY);
  
  status("funk2_defragmenter__memory_pool__move_memory: defragment moving memory.  pool_index=" u64__fstr " done.", pool_index);
}


f2ptr funk2_defragmenter__memory_pool__lookup_new_f2ptr(funk2_defragmenter_t* this, f2ptr exp) {
  if (exp == nil) {
    return nil;
  }
  s64 pool_index;
  for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
    funk2_hash_t* new_old_memory_position_hash = &(this->new_old_memory_position_hash[pool_index]);
    if (funk2_hash__contains(new_old_memory_position_hash, (u64)exp)) {
      return (f2ptr)funk2_hash__lookup(new_old_memory_position_hash, (u64)exp);
    }
  }
  status("funk2_defragmenter__memory_pool__lookup_new_f2ptr fatal error: could not find f2ptr in hash.  exp=" f2ptr__fstr, exp);
  error(nil, "funk2_defragmenter__memory_pool__lookup_new_f2ptr fatal error: could not find f2ptr in hash.");
}

void funk2_defragmenter__memory_pool__fix_pointers_in_dptr(funk2_defragmenter_t* this, funk2_dptr_t* dptr) {
  if (dptr->p)                 {dptr->p                 = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, dptr->p);}
#if defined(F2__USE_TRACED_DPTRS)
  if (dptr->tracing_on)        {dptr->tracing_on        = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, dptr->tracing_on);}
  if (dptr->trace)             {dptr->trace             = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, dptr->trace);}
  if (dptr->imagination_frame) {dptr->imagination_frame = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, dptr->imagination_frame);}
  if (dptr->mutate_funks)      {dptr->mutate_funks      = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, dptr->mutate_funks);}
  if (dptr->read_funks)        {dptr->read_funks        = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, dptr->read_funks);}
#endif // F2__USE_TRACED_DPTRS
}

void funk2_defragmenter__memory_pool__fix_pointers_in_memblock(funk2_defragmenter_t* this, funk2_memblock_t* memblock) {
  ptype_block_t* ptype_block = (ptype_block_t*)memblock;
  {
    f2ptr cause = ptype_block->cause;
    if (cause != nil) {
      ptype_block->cause = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, cause);
    }
  }
  {
    f2ptr creation_fiber = ptype_block->creation_fiber;
    if (creation_fiber != nil) {
      ptype_block->creation_fiber = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, creation_fiber);
    }
  }
  switch(ptype_block->block.ptype) {
  case ptype_free_memory: error(nil, "block of type free_memory in defragmenter.");
  case ptype_integer:                  return;
  case ptype_double:                   return;
  case ptype_float:                    return;
  case ptype_pointer:                  return;
  case ptype_scheduler_cmutex:         return;
  case ptype_cmutex:                   return;
  case ptype_scheduler_creadwritelock: return;
  case ptype_creadwritelock:           return;
  case ptype_char:                     return;
  case ptype_string:                   return;
  case ptype_symbol:                   return;
  case ptype_chunk:                    return;
  case ptype_simple_array: {
    s64 i;
    f2ptr_t* iter = ((ptype_simple_array_block_t*)ptype_block)->slot;
    for (i = ((ptype_simple_array_block_t*)ptype_block)->length; i > 0; i --) {
      if (iter->data) {
	iter->data = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, iter->data);
      }
      iter ++;
    }
  } return;
  case ptype_traced_array: {
    s64 i;
    funk2_dptr_t* iter = (funk2_dptr_t*)((ptype_traced_array_block_t*)ptype_block)->dptr_data;
    for (i = ((ptype_traced_array_block_t*)ptype_block)->length; i > 0; i --) {
      funk2_defragmenter__memory_pool__fix_pointers_in_dptr(this, iter);
      iter ++;
    }
  } return;
  case ptype_larva: {
    f2ptr bug = ((ptype_larva_block_t*)ptype_block)->bug;
    if (bug) {
      ((ptype_larva_block_t*)ptype_block)->bug = funk2_defragmenter__memory_pool__lookup_new_f2ptr(this, bug);
    }
  } return;
  default:
    {
      char str[1024];
      sprintf(str, "unknown type (" s64__fstr ") of block in garbage collector.", (s64)(ptype_block->block.ptype));
      error(nil, str);
    }
  }
}

void funk2_defragmenter__memory_pool__fix_pointers(funk2_defragmenter_t* this, u64 pool_index) {
  status("funk2_defragmenter__memory_pool__fix_pointers: defragment fixing memory pointers.  pool_index=" u64__fstr, pool_index);
  
  funk2_memorypool_t* memorypool    = &(__funk2.memory.pool[pool_index]);
  funk2_memblock_t*   end_of_blocks = funk2_memorypool__end_of_blocks(memorypool);
  
  {
    funk2_memblock_t* iter = funk2_memorypool__beginning_of_blocks(memorypool);
    while (iter < end_of_blocks) {
      if (iter->used) {
	funk2_defragmenter__memory_pool__fix_pointers_in_memblock(this, iter);
      }
      iter = (funk2_memblock_t*)(((u8*)iter) + funk2_memblock__byte_num(iter));
    }
  }
  
  status("funk2_defragmenter__memory_pool__fix_pointers: defragment fixing memory pointers.  pool_index=" u64__fstr " done.", pool_index);
}


void* funk2_defragmenter__defragment__parallel_phase_one(void* memorypool_pointer) {
  funk2_memorypool_t* memorypool = (funk2_memorypool_t*)memorypool_pointer;
  u64 pool_index = memorypool->pool_index;
  {
    funk2_defragmenter__memory_pool__destroy_memblocks(   &(__funk2.defragmenter), pool_index);
    funk2_defragmenter__memory_pool__move_memory(         &(__funk2.defragmenter), pool_index);
    funk2_defragmenter__memory_pool__initialize_memblocks(&(__funk2.defragmenter), pool_index);
    status("funk2_defragmenter__defragment: parallel phase one done.  pool_index=" u64__fstr, pool_index);
  }
  return NULL;
}

void* funk2_defragmenter__defragment__parallel_phase_two(void* memorypool_pointer) {
  funk2_memorypool_t* memorypool = (funk2_memorypool_t*)memorypool_pointer;
  u64 pool_index = memorypool->pool_index;
  {
    funk2_defragmenter__memory_pool__fix_pointers(&(__funk2.defragmenter), pool_index);
    status("funk2_defragmenter__defragment: parallel phase two done.  pool_index=" u64__fstr, pool_index);
  }
  return NULL;
}

void funk2_defragmenter__defragment(funk2_defragmenter_t* this) {
  
  status("funk2_defragmenter__defragment: parallel phase one.");
  {
    pthread_t pool_thread[memory_pool_num];
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	pthread_create(&(pool_thread[pool_index]), NULL, &funk2_defragmenter__defragment__parallel_phase_one, (void*)(&(__funk2.memory.pool[pool_index])));
      }
    }
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	pthread_join(pool_thread[pool_index], NULL);
      }
    }
  }
  
  status("funk2_defragmenter__defragment: parallel phase two.");
  {
    pthread_t pool_thread[memory_pool_num];
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	pthread_create(&(pool_thread[pool_index]), NULL, &funk2_defragmenter__defragment__parallel_phase_two, (void*)(&(__funk2.memory.pool[pool_index])));
      }
    }
    {
      s64 pool_index;
      for (pool_index = 0; pool_index < memory_pool_num; pool_index ++) {
	pthread_join(pool_thread[pool_index], NULL);
      }
    }
  }
  
  status("funk2_defragmenter__defragment: fixing all module pointers.");
  funk2_module_registration__defragment__fix_pointers(&(__funk2.module_registration));
}

void funk2_defragmenter__stop_everything_and_defragment(funk2_defragmenter_t* this) {
  status("funk2_defragmenter__handle asking all user processor threads to wait_politely so that we can begin defragmenting.");
  
  // stop and reinitialize system (but don't restart)
  funk2_virtual_processor_handler__destroy(&(__funk2.virtual_processor_handler));
  funk2_virtual_processor_handler__init(&(__funk2.virtual_processor_handler), memory_pool_num);
  __funk2.memory.bootstrapping_mode = boolean__true;
  
  status("");
  status("*******************************");
  status("**** DOING DEFRAGMENTATION ****");
  status("*******************************");
  status("");
  {
    int index;
    for (index = 0; index < memory_pool_num; index ++) {
      status ("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
    }
  }
  funk2_defragmenter__defragment(this);
  status("");
  status("***********************************");
  status("**** DONE WITH DEFRAGMENTATION ****");
  status("***********************************");
  status("");
  {
    int index;
    for (index = 0; index < memory_pool_num; index ++) {
      status ("__funk2.memory.pool[%d].total_global_memory = " f2size_t__fstr, index, (f2size_t)(__funk2.memory.pool[index].total_global_memory));
    }
  }
  this->need_defragmentation = boolean__false;
  this->total_defragmentation_count ++;
  
  funk2_virtual_processor_handler__start_virtual_processors(&(__funk2.virtual_processor_handler));
  __funk2.memory.bootstrapping_mode = boolean__false;
}

void funk2_defragmenter__handle(funk2_defragmenter_t* this) {
  if (this->need_defragmentation) {
    funk2_defragmenter__stop_everything_and_defragment(this);
  }
}

void funk2_defragmenter__signal_start(funk2_defragmenter_t* this) {
  this->need_defragmentation = boolean__true;
}

f2ptr f2__defragmenter__signal_start(f2ptr cause) {
  funk2_defragmenter__signal_start(&(__funk2.defragmenter));
  return nil;
}
def_pcfunk0(defragmenter__signal_start,
	    "Signals to the management thread to start a defragmentation of memory.",
	    return f2__defragmenter__signal_start(this_cause));


u64 funk2_defragmenter__total_defragmentation_count(funk2_defragmenter_t* this) {
  return this->total_defragmentation_count;
}

u64 raw__defragmenter__total_defragmentation_count(f2ptr cause) {
  return funk2_defragmenter__total_defragmentation_count(&(__funk2.defragmenter));
}

f2ptr f2__defragmenter__total_defragmentation_count(f2ptr cause) {
  return f2integer__new(cause, raw__defragmenter__total_defragmentation_count(cause));
}
def_pcfunk0(defragmenter__total_defragmentation_count,
	    "Signals to the management thread to start a defragmentation of memory.",
	    return f2__defragmenter__total_defragmentation_count(this_cause));




// **

void f2__defragmenter__defragment__fix_pointers() {
  // -- reinitialize --

  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(defragmenter__signal_start);
  f2__primcfunk__init__defragment__fix_pointers(defragmenter__total_defragmentation_count);
  
}

void f2__defragmenter__reinitialize_globalvars() {
  f2__primcfunk__init__0(defragmenter__signal_start);
  f2__primcfunk__init__0(defragmenter__total_defragmentation_count);
}

void f2__defragmenter__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "defragmenter", "", &f2__defragmenter__reinitialize_globalvars, &f2__defragmenter__defragment__fix_pointers);
  
  f2__defragmenter__reinitialize_globalvars();
}


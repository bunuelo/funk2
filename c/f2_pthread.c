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

#include "funk2.h"

int       __pthread_list__length = 0;
pthread_t __pthread_list[memory_pool_num + 1];

void pthread_list__reset() {
  __pthread_list__length = 0;
}

int this_pthread__pool_index() {
  pthread_t tid = pthread_self();
  int i = __pthread_list__length - 1;
  pthread_t* __pthread_iter = __pthread_list + i;
  while (i >= 0) {
    if (*__pthread_iter == tid) {
      if (i >= memory_pool_num) {
	return 0;
      }
      return i;
    }
    i --;
    __pthread_iter --;
  }
  __pthread_list[__pthread_list__length] = tid;
  __pthread_list__length ++;
  i = __pthread_list__length - 1;
  if (i >= memory_pool_num) {
    return 0;
  }
  return i;
}

void pthread_list__destroy_all_others() {
  pthread_t this__tid = pthread_self();
  status("pthread_list__destroy_all_others() note: this__tid=" u64__fstr ".", (u64)this__tid);
  int i;
  for (i = 0; i < __pthread_list__length; i ++) {
    pthread_t tid = __pthread_list[i];
    if (tid != this__tid) {
      status("pthread_list__destroy_all_others() note: pthread_cancel(tid=" u64__fstr ").", (u64)tid);
      pthread_cancel(tid);
    }
  }
}


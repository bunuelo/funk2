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

#include "funk2.h"

void funk2_system_processor__init(funk2_system_processor_t* this) {
  this->processor_affinity_index = NULL;
  this->processor_count          = 0;
  {
    funk2_proc_cpuinfo_t proc_cpuinfo;
    funk2_proc_cpuinfo__init(&proc_cpuinfo);
    if (proc_cpuinfo.supported) {
      this->processor_count = proc_cpuinfo.processor_count;
      status("proc_cpuinfo.processor_count = " s64__fstr, (s64)proc_cpuinfo.processor_count);
    }
  }
#if defined (HAVE_SCHED_GETAFFINITY)
  {
    status("using sched_getaffinity for processor count.");
    cpu_set_t initial_cpu_set;
    CPU_ZERO(&initial_cpu_set);
    {
      int result = sched_getaffinity(0, sizeof(cpu_set_t), &initial_cpu_set);
      if (result != 0) {
	error(nil, "funk2_system_processor__init error: sched_getaffinity error.");
      }
    }
    this->processor_count = 0;
    {
      s64 i;
      for (i = 0; i < CPU_SETSIZE; i ++) {
	if (CPU_ISSET(i, &initial_cpu_set) != 0) {
	  this->processor_count ++;
	}
      }
    }
    if (this->processor_count == 0) {
      this->processor_affinity_index = NULL;
    } else {
      this->processor_affinity_index = (u64*)from_ptr(f2__malloc(sizeof(u64) * this->processor_count));
      {
	s64 processor_index = 0;
	s64 i;
	for (i = 0; i < CPU_SETSIZE; i ++) {
	  if (CPU_ISSET(i, &initial_cpu_set) != 0) {
	    this->processor_affinity_index[processor_index] = i;
	    processor_index ++;
	  }
	}
      }
    }
  }
#else
#  if defined(HAVE_GETPROCESSAFFINITYMASK)
  {
    HANDLE current_process       = GetCurrentProcess();
    DWORD  process_affinity_mask = 0;
    DWORD  system_affinity_mask  = 0;
    if (GetProcessAffinityMask(current_process,
			       (PDWORD_PTR)&process_affinity_mask,
			       (PDWORD_PTR)&system_affinity_mask) == 0) {
      status("warning GetProcessAffinityMask failed.");
    } else {
      this->processor_count = 0;
      {
	s64 i;
	for (i = 0; i < 64; i ++) {
	  if ((process_affinity_mask & (((u64)1) << i)) != 0) {
	    this->processor_count ++;
	  }
	}
      }
      if (this->processor_count == 0) {
	this->processor_affinity_index = NULL;
      } else {
	this->processor_affinity_index = (u64*)from_ptr(f2__malloc(sizeof(u64) * this->processor_count));
	{
	  s64 processor_index = 0;
	  s64 i;
	  for (i = 0; i < 64; i ++) {
	    if ((process_affinity_mask & (((u64)1) << i)) != 0) {
	      this->processor_affinity_index[processor_index] = i;
	      processor_index ++;
	    }
	  }
	}
      }
    }
  }
#  else
  status("system_processor sched_getaffinity disabled.");
#  endif
#endif // HAVE_SCHED_GETAFFINITY
  if (__funk2.command_line.force_processor_count != 0) {
    status("command-line forcing processor count to " s64__fstr ".", __funk2.command_line.force_processor_count);
    this->processor_count = __funk2.command_line.force_processor_count;
  }
  if (this->processor_count == 0) {
    status("assuming 1 processor.");
    this->processor_count = 1;
  }
  status("__funk2.system_processor.processor_count = " s64__fstr, (s64)this->processor_count);
  if (this->processor_affinity_index == NULL) {
    status("system_processor warning affinities are disabled.");
  }
}

void funk2_system_processor__destroy(funk2_system_processor_t* this) {
}

void funk2_system_processor__print_status(funk2_system_processor_t* this) {
  status("* funk2.system_processor.processor_count = " u64__fstr, this->processor_count);
  if (this->processor_affinity_index != NULL) {
    s64 i;
    for (i = 0; i < this->processor_count; i ++) {
      status("* funk2.system_processor.processor_assignment_index[" s64__fstr "] = " u64__fstr, i, this->processor_affinity_index[i]);
    }
  }
}

// **

void f2__system_processor__reinitialize_globalvars() {
}

void f2__system_processor__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
}

void f2__system_processor__initialize() {
  //f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "system_processor", "", &f2__system_processor__reinitialize_globalvars, &f2__system_processor__defragment__fix_pointers);
  
  f2__system_processor__reinitialize_globalvars();
  
}


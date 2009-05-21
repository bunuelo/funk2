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

void child_process__init(child_process_t* this, char** argv, char** envp, pid_t pid) {
  char** new_argv;
  {
    int index;
    for (index = 0; argv[index] != NULL; index ++);
    int argv__length = index;
    new_argv = (char**)malloc(sizeof(char*) * (argv__length + 1));
    for (index = 0; index < argv__length; index ++) {
      int argv_index__length = strlen(argv[index]);
      new_argv[index] = (char*)malloc(argv_index__length + 1);
      strcpy(new_argv[index], argv[index]);
    }
    new_argv[index] = NULL;
  }
  char** new_envp;
  {
    int index;
    for (index = 0; envp[index] != NULL; index ++);
    int envp__length = index;
    new_envp = (char**)malloc(sizeof(char*) * (envp__length + 1));
    for (index = 0; index < envp__length; index ++) {
      int envp_index__length = strlen(envp[index]);
      new_envp[index] = (char*)malloc(envp_index__length + 1);
      strcpy(new_envp[index], envp[index]);
    }
    new_envp[index] = NULL;
  }
  this->argv    = new_argv;
  this->envp    = new_envp;
  this->pid     = pid;
  this->exited  = boolean__false;
  this->killed  = boolean__false;
  this->stopped = boolean__false;
}

child_process_t* child_process__new(char** argv, char** envp) {
  pid_t child_pid = fork();
  if (child_pid == -1) {
    printf("\nfork() error.\n"); fflush(stdout);
    return NULL;
  }
  if (child_pid == 0) {
    if (execve(argv[0], argv, envp) == -1) {
      printf("\nchild failed to execve (1)"); fflush(stdout);
      perror("child failed to execve");
      exit(-1);
    }
    printf("\nchild failed to execve (2)"); fflush(stdout);
    exit(-1);
  }
  child_process_t* child_process = (child_process_t*)malloc(sizeof(child_process_t));
  child_process__init(child_process, argv, envp, child_pid);
  return child_process;
}



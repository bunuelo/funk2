// 
// Copyright (c) 2007-2010 Bo Morgan.
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

funk2_child_process_init_t funk2_child_process__init(funk2_child_process_t* this, char** argv, char** envp) {
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
  this->argv             = new_argv;
  this->envp             = new_envp;
  this->exited           = boolean__false;
  this->killed           = boolean__false;
  this->stopped          = boolean__false;
  this->no_longer_exists = boolean__false;
  system("/bin/ls");
  //this->pid              = fork(); // FORK PROCESS HERE!!!
  this->pid = 1;
  if (this->pid == -1) {
    printf("\nfork() error.\n"); fflush(stdout);
    perror("fork");
    return funk2_child_process_init__fork_failed;
  }
  if (this->pid == 0) {
    if (execve(argv[0], argv, envp) == -1) {
      printf("\nchild failed to execve (1)"); fflush(stdout);
      perror("child failed to execve");
      exit(-1);
    }
    printf("\nchild failed to execve (2)"); fflush(stdout);
    exit(-1);
  }
  return funk2_child_process_init__success;
}

void funk2_child_process__destroy(funk2_child_process_t* this) {
  printf("\ndestroying child.  pid=%d\n", this->pid);
  if (! funk2_child_process__is_completed(this)) {
    printf("\nkilling child.  pid=%d\n", this->pid);
    int result = kill(this->pid, SIGKILL);
    if (result == -1) {
      printf("\nerror killing child.  pid=%d\n", this->pid);
    }
  }
  int index;
  for (index = 0; this->argv[index] != NULL; index ++) {
    free(this->argv[index]);
  }
  free(this->argv);
  for (index = 0; this->envp[index] != NULL; index ++) {
    free(this->envp[index]);
  }
  free(this->envp);
}

boolean_t funk2_child_process__is_completed(funk2_child_process_t* this) {
  return (this->exited || this->killed || this->no_longer_exists);
}

void funk2_child_process__handle(funk2_child_process_t* this) {
  if (! this->exited) {
    int pid_status;
    if (waitpid(this->pid, &pid_status, WNOHANG | WUNTRACED | WCONTINUED) == -1) {
      if (errno == ECHILD) {
	printf("\nchild_process__handle(): child process no longer exists, pid=%d.\n", this->pid);
	this->no_longer_exists = boolean__true;
      } else {
	char msg[1024];
	snprintf(msg, 1024, "\nchild_process__handle(): waitpid error, pid=%d.\n", this->pid);
	perror(msg);
      }
      return;
    }
    if (pid_status != 0) {
      if (WIFEXITED(pid_status)) {
	printf("\nchild_process__handle(): child process exited, pid=%d.\n", this->pid);
	this->exited = boolean__true;
      } else if (WIFSIGNALED(pid_status)) {
	printf("\nchild_process__handle(): child process killed, pid=%d.\n", this->pid);
	this->killed = boolean__true;
      } else if (WIFSTOPPED(pid_status)) {
	printf("child_process__handle(): child process stopped, pid=%d.\n", this->pid);
	this->stopped = boolean__true;
      } else if (WIFCONTINUED(pid_status)) {
	printf("child_process__handle(): child process continuing, pid=%d.\n", this->pid);
	this->stopped = boolean__false;
      }
    }
  }
}



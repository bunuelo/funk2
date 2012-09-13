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

#ifndef F2__STATUS__H
#define F2__STATUS__H

#include "f2_global.h"

typedef struct funk2_status_s {
  funk2_processor_spinlock_t trace_mutex;
} funk2_status_t;

void funk2_status(char* filename, int line_num, char* msg, ...);

// to disable status, there is a boolean global variable in f2_status.c
#define status(msg, rest...) funk2_status(__FILE__, __LINE__, msg, ## rest)

ssize_t raw__stream__write_character(f2ptr cause, f2ptr stream, funk2_character_t ch);
ssize_t raw__stream__writef(f2ptr cause, f2ptr stream, char* msg, ...);
ssize_t funk2_character_string__snprintf(funk2_character_t* string, s64 max_length, char* utf8_msg, ...);
ssize_t writef(int fd, char* msg, ...);

void f2__status__reinitialize_globalvars();
void f2__status__initialize();
void f2__status__destroy();

#endif // F2__STATUS__H


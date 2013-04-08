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

#if !defined(HAVE_GETLINE)
// This function is public domain -- Will Hartung 4/9/09
size_t getline(char** lineptr, size_t* n, FILE* stream) {
  char*  bufptr = NULL;
  char*  p      = bufptr;
  size_t size;
  int    c;
  
  if (lineptr == NULL) {
    return -1;
  }
  if (stream == NULL) {
    return -1;
  }
  if (n == NULL) {
    return -1;
  }
  bufptr = *lineptr;
  size = *n;
  
  c = fgetc(stream);
  if (c == EOF) {
    return -1;
  }
  if (bufptr == NULL) {
    bufptr = malloc(128);
    if (bufptr == NULL) {
      return -1;
    }
    size = 128;
  }
  p = bufptr;
  while(c != EOF) {
    if ((p - bufptr) > (size - 1)) {
      size = size + 128;
      bufptr = realloc(bufptr, size);
      if (bufptr == NULL) {
	return -1;
      }
    }
    *p++ = c;
    if (c == '\n') {
      break;
    }
    c = fgetc(stream);
  }
  
  *p++ = '\0';
  *lineptr = bufptr;
  *n = size;
  
  return p - bufptr - 1;
}
#endif // !HAVE_GETLINE

void funk2_proc_cpuinfo__init(funk2_proc_cpuinfo_t* this) {
  this->supported       = boolean__false;
  this->processor_count = 0;
  {
    FILE*   fptr;
    char*   line   = NULL;
    size_t  length = 0;
    ssize_t read_length;
    
    fptr = fopen("/proc/cpuinfo", "r");
    if (fptr == NULL) {
      status("funk2_proc_cpuinfo__init error opening /proc/cpuinfo.");
      this->supported = boolean__false;
      return;
    }
    
    status("funk2_proc_cpuinfo__init begin.");
    while ((read_length = getline(&line, &length, fptr)) != -1) {
      //status("funk2_proc_cpuinfo__init: Retrieved line of length %zu :\n", read_length);
      //status("funk2_proc_cpuinfo__init: \"%s\"", line);
      char* parameter_string = (char*)malloc(read_length + 1);
      char* value_string     = (char*)malloc(read_length + 1);
      sscanf(line, "%[^\t:] : %[^\t\n]", parameter_string, value_string);
      status("funk2_proc_cpuinfo__init: parsed \"%s\" = \"%s\"", parameter_string, value_string);
      if (strncmp(parameter_string, "processor", read_length) == 0) {
	status("funk2_proc_cpuinfo__init: found processor.");
	this->processor_count ++;
      }
      free(parameter_string);
      free(value_string);
    }
    status("funk2_proc_cpuinfo__init done.");
    free(line);
  }
  if (this->processor_count > 0) {
    this->supported = boolean__true;
  }
}


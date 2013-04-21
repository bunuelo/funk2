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

#ifndef F2__COMMAND_LINE__H
#define F2__COMMAND_LINE__H

typedef struct funk2_command_line_s {
  int       argc;
  char**    argv;
  boolean_t debug;
  char*     load_source_filename;
  char*     user_command;
  char*     bootstrap_image_filename;
  int       peer_command_server__port_num;
  s64       force_processor_count;
  boolean_t no_processor_affinity;
  boolean_t no_sigint_handler;
  boolean_t no_sigsegv_handler;
  boolean_t no_repl;
  boolean_t no_boot;
} funk2_command_line_t;

void f2__print_usage();
boolean_t string__parse_integer(char* this, int* return_value);
boolean_t string__parse_new_hostname_colon_portnum(char* this, char** hostname, int* port_num);
boolean_t string__filename_exists(char* this);
void funk2_command_line__init(funk2_command_line_t* this, int argc, char** argv);
void funk2_command_line__destroy(funk2_command_line_t* this);
void string__print_quote_protected(char* this);
void funk2_command_line__print(funk2_command_line_t* this);


// **

void f2__command_line__defragment__fix_pointers();
void f2__command_line__reinitialize_globalvars();
void f2__command_line__initialize();

#endif // F2__COMMAND_LINE__H




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

void f2__print_usage() {
  printf("\n\nfunk2: causally reflective programming language"
	 "\n"
	 "\n  funk2 [-x <command>] [-p <portnum>] [--swap-dir <swap-directory>] [<source.fu2>]"
	 "\n"
	 "\n    <source.fu2>"
	 "\n"
	 "\n        A user supplied filename of file from which to read and execute source"
	 "\n        code after booting and before exiting."
	 "\n"
	 "\n    -x <command>  [:default [repl]]"
	 "\n"
	 "\n        A user supplied command to execute after booting and before exiting."
	 "\n"
	 "\n    -p <portnum>  [:default 22222 :try anything from 22222 to 23221]"
	 "\n"
	 "\n        The localhost peer-command-server port number.  Each copy of funk2"
	 "\n        sharing a network interface must be able to allocate a unique"
	 "\n        peer-command-server port number."
	 "\n"
	 "\n    --swap-directory <swap-directory>  [:default ./f2swp/ :try /tmp/]"
	 "\n        "
	 "\n        local filesystem directory for storing swap files which should have an"
	 "\n        absolute minimum of 2 gigabytes of free space."
	 "\n\n");
}

bool string__parse_integer(char* this, int* return_value) {
  errno = 0;
  char* end_ptr = 0;
  int value = strtol(this, &end_ptr, 10);
  if (errno != 0 || (end_ptr && (end_ptr == this ||
				 (end_ptr[0] != 0 &&
				  end_ptr[0] != ' ' &&
				  end_ptr[0] != '(' &&
				  end_ptr[0] != ')' &&
				  end_ptr[0] != '<' &&
				  end_ptr[0] != '>' &&
				  end_ptr[0] != '{' &&
				  end_ptr[0] != '}' &&
				  end_ptr[0] != '[' &&
				  end_ptr[0] != ']' &&
				  end_ptr[0] != ':' &&
				  end_ptr[0] != '\t' &&
				  end_ptr[0] != '\r' &&
				  end_ptr[0] != '\n')))) {
    printf("\n  error parsing integer: \"%s\".", this);
    return true; // parse error
  }
  *return_value = value;
  return false;
}

bool string__parse_new_hostname_colon_portnum(char* this, char** hostname, int* port_num) {
  int first_colon_index;
  for (first_colon_index = 0; this[first_colon_index] != ':' && this[first_colon_index] != 0; first_colon_index++);
  if (this[first_colon_index] == 0) {
    printf("\n  error parsing <hostname>:<port_num>: couldn't find first colon, \"%s\".", this);
    return true; // parse error
  }
  char *new_hostname = (char*)malloc(first_colon_index + 1);
  memcpy(new_hostname, this, first_colon_index);
  new_hostname[first_colon_index] = 0;
  int user_port_num;
  if (string__parse_integer(this + first_colon_index + 1, &user_port_num)) {
    printf("\n  error parsing <hostname>:<port_num>: couldn't find port_num after first colon, \"%s\".", this + first_colon_index + 1);
    return true;
  }
  *hostname = new_hostname;
  *port_num = user_port_num;
  return false; // no parse error
}

bool string__filename_exists(char* this) {
  int fd = open(this, 0);
  if (fd == -1) {
    return false;
  }
  close(fd);
  return true;
}

void funk2_command_line__init(funk2_command_line_t* this, int argc, char** argv) {
  this->argc = argc;
  this->argv = argv;
  
  this->load_source_filename            = NULL;
  this->user_command                    = NULL;
  this->peer_command_server__port_num   = 22222;
  this->swap_directory                  = NULL;
  
  int index;
  bool parse_error = false;
  for (index = 1; index < argc; index ++) {
    if (strcmp(argv[index], "-x") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = true;
	break;
      }
      this->user_command = argv[index];
    } else if (strcmp(argv[index], "-p") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = true;
	break;
      }
      if (string__parse_integer(argv[index], &(this->peer_command_server__port_num))) {
	parse_error = true;
	break;
      }
    if (strcmp(argv[index], "--swap-directory") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = true;
	break;
      }
      this->swap_directory = argv[index];
    } else {
      if (! string__filename_exists(argv[index])) {
	printf("\n  error parsing <source.fu2>: filename does not exist, \"%s\".", argv[index]);
	parse_error = true;
	break;
      } else {
	this->load_source_filename = argv[index];
      }
    }
  }
  
  if (parse_error) {
    f2__print_usage();
    exit(-1);
  }
  
  funk2_command_line__print(this);
}

void funk2_command_line__destroy(funk2_command_line_t* this) {
}

void string__print_quote_protected(char* this) {
  if (this == NULL) {
    printf("nil");
    return;
  }
  printf("\"");
  int i;
  for (i = 0; this[i] != 0; i ++) {
    char ch = this[i];
    if (ch == '\"') {
      printf("\\\"");
    } else {
      printf("%c", ch);
    }
  }
  printf("\"");
}

void funk2_command_line__print(funk2_command_line_t* this) {
  int i;
  for (i = 0; i < this->argc; i ++) {
    status("command_line.argv[%d] = '%s'", i, this->argv[i]);
  }
  status("command_line.load_source_filename           = '%s'", this->load_source_filename);
  status("command_line.user_command                   = '%s'", this->user_command);
  status("command_line.peer_command_server.port_num   = %d", this->peer_command_server__port_num);
}


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

void f2__print_usage() {
  printf("\n\nfunk2: causally reflective parallel programming language"
	 "\n"
	 "\n  funk2"
	 "\n  funk2 -h"
	 "\n  funk2 <source.fu2>"
	 "\n  funk2 -x <command>"
	 "\n  funk2 -i <bootstrap-image>"
	 "\n"
	 "\n    -h"
	 "\n"
	 "\n        Print this help message."
	 "\n"
	 "\n    <source.fu2>"
	 "\n"
	 "\n        A user supplied filename of file from which to read and"
	 "\n        execute source code after booting and before exiting."
	 "\n"
	 "\n    -x <command>"
	 "\n"
	 "\n        A user supplied command to execute after booting and before"
	 "\n        exiting."
	 "\n"
	 "\n    -i <bootstrap-image>"
	 "\n"
	 "\n        The bootstrap image to load before parsing any other"
	 "\n        commands.  This option is useful for scripting Funk2 programs"
	 "\n        without needing to recompile."
	 "\n"
	 "\n    -p <portnum>"
	 "\n"
	 "\n        The localhost peer-command-server port number."
	 "\n"
	 "\n    --force-processor-count <force-processor-count>"
	 "\n"
	 "\n        Override low-level processor count detection.  Must be set to"
	 "\n        an integer, 1 or greater.  Note that this setting must be used"
	 "\n        consistently in compiling any bootstrap images and will result"
	 "\n        in undefined behavior if used with bootstrap images that"
	 "\n        assume a different number of processors."
	 "\n"
	 "\n    --no-sigint-handler"
	 "\n"
	 "\n        Disables SIGINT (CTRL-C) signal handler."
	 "\n"
	 "\n    --no-sigsegv-handler"
	 "\n"
	 "\n        Disables SIGSEGV (segmentation fault) signal handler."
	 "\n"
	 "\n\n");
}

boolean_t string__parse_integer(char* this, int* return_value) {
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
    return boolean__true; // parse error
  }
  *return_value = value;
  return boolean__false;
}

boolean_t string__parse_new_hostname_colon_portnum(char* this, char** hostname, int* port_num) {
  int first_colon_index;
  for (first_colon_index = 0; this[first_colon_index] != ':' && this[first_colon_index] != 0; first_colon_index++);
  if (this[first_colon_index] == 0) {
    printf("\n  error parsing <hostname>:<port_num>: couldn't find first colon, \"%s\".", this);
    return boolean__true; // parse error
  }
  char *new_hostname = (char*)from_ptr(f2__malloc(first_colon_index + 1));
  memcpy(new_hostname, this, first_colon_index);
  new_hostname[first_colon_index] = 0;
  int user_port_num;
  if (string__parse_integer(this + first_colon_index + 1, &user_port_num)) {
    printf("\n  error parsing <hostname>:<port_num>: couldn't find port_num after first colon, \"%s\".", this + first_colon_index + 1);
    return boolean__true;
  }
  *hostname = new_hostname;
  *port_num = user_port_num;
  return boolean__false; // no parse error
}

boolean_t string__filename_exists(char* this) {
  int fd = open(this, 0);
  if (fd == -1) {
    return boolean__false;
  }
  close(fd);
  return boolean__true;
}

void funk2_command_line__init(funk2_command_line_t* this, int argc, char** argv) {
  this->argc = argc;
  this->argv = argv;
  
  this->load_source_filename            = NULL;
  this->user_command                    = NULL;
  this->peer_command_server__port_num   = 22222;
  this->force_processor_count           = 0;
  this->bootstrap_image_filename        = NULL;
  this->no_sigint_handler               = boolean__false;
  this->no_repl                         = boolean__false;
  this->no_boot                         = boolean__false;
  
  int       index;
  boolean_t parse_error         = boolean__false;
  boolean_t print_help_and_exit = boolean__false;
  for (index = 1; index < argc; index ++) {
    if ((strcmp(argv[index], "-h")     == 0) ||
	(strcmp(argv[index], "--help") == 0)) {
      print_help_and_exit = boolean__true;
    } else if (strcmp(argv[index], "-x") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = boolean__true;
	break;
      }
      this->user_command = argv[index];
    } else if (strcmp(argv[index], "-p") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = boolean__true;
	break;
      }
      if (string__parse_integer(argv[index], &(this->peer_command_server__port_num))) {
	parse_error = boolean__true;
	break;
      }
    } else if (strcmp(argv[index], "-i") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = boolean__true;
	break;
      }
      this->bootstrap_image_filename = argv[index];
    } else if (strcmp(argv[index], "--force-processor-count") == 0) {
      index ++;
      if (index >= argc) {
	parse_error = boolean__true;
	break;
      }
      char* end_ptr = NULL;
      errno = 0;
      s64 force_processor_count = strtol(argv[index], &end_ptr, 10);
      if (errno != 0) {
	printf("\n  error parsing <processor-count>: \"%s\".", argv[index]);
	parse_error = boolean__true;
	break;
      }
      if (*end_ptr != '\0') {
	printf("\n  junk after argument <processor-count>: \"%s\".", argv[index]);
	parse_error = boolean__true;
	break;
      }
      if (force_processor_count < 1) {
	printf("\n  argument out of range <processor-count>: \"%s\".", argv[index]);
	parse_error = boolean__true;
	break;
      }
      this->force_processor_count = force_processor_count;
    } else if (strcmp(argv[index], "--no-sigint-handler") == 0) {
      this->no_sigint_handler = boolean__true;
    } else if (strcmp(argv[index], "--no-sigsegv-handler") == 0) {
      this->no_sigsegv_handler = boolean__true;
    } else if (strcmp(argv[index], "--no-repl") == 0) {
      this->no_repl = boolean__true;
    } else if (strcmp(argv[index], "--no-boot") == 0) {
      this->no_boot = boolean__true;
    } else {
      if (! string__filename_exists(argv[index])) {
	printf("\n  error parsing <source.fu2>: filename does not exist, \"%s\".", argv[index]);
	parse_error = boolean__true;
	break;
      } else {
	this->load_source_filename = argv[index];
      }
    }
  }
  
  funk2_command_line__print(this);
  
  if (parse_error) {
    f2__print_usage();
    exit(-1);
  }
  
  if (print_help_and_exit) {
    f2__print_usage();
    exit(0);
  }
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

// ^^




f2ptr raw__command_line__user_command_string(f2ptr cause) {
  char* user_command_string__str = __funk2.command_line.user_command;
  if (user_command_string__str == NULL) {
    return nil;
  } else {
    return new__string(cause, user_command_string__str);
  }
}

f2ptr f2__command_line__user_command_string(f2ptr cause) {
  return raw__command_line__user_command_string(cause);
}
def_pcfunk0(command_line__user_command_string,
	    "Returns the user command supplied on the command line.",
	    return f2__command_line__user_command_string(this_cause));


// **

void f2__command_line__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(command_line__user_command_string);
  
}

void f2__command_line__reinitialize_globalvars() {
  f2__primcfunk__init__0_and_rest(command_line__user_command_string, expressions);
}

void f2__command_line__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "command_line", "", &f2__command_line__reinitialize_globalvars, &f2__command_line__defragment__fix_pointers);
  
  f2__command_line__reinitialize_globalvars();
}


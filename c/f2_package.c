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

// source_expression

def_primobject_6_slot(source_expression,
		      body, first_line, last_line, first_column, last_column, subexpressions);

f2ptr f2__source_expression__new(f2ptr cause, f2ptr body, f2ptr first_line, f2ptr last_line, f2ptr first_column, f2ptr last_column, f2ptr subexpressions) {return f2source_expression__new(cause, body, first_line, last_line, first_column, last_column, subexpressions);}
def_pcfunk6(source_expression__new, body, first_line, last_line, first_column, last_column, subexpressions, return f2__source_expression__new(this_cause, body, first_line, last_line, first_column, last_column, subexpressions));

f2ptr f2source_expression__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2source_expression__primobject_type__new(cause);
  return this;
}


// source

def_primobject_1_slot(source,
		      code);

f2ptr f2__source__new(f2ptr cause, f2ptr code) {return f2source__new(cause, code);}
def_pcfunk1(source__new, code, return f2__source__new(this_cause, code));

f2ptr f2__source__load(f2ptr cause, f2ptr filename) {
  f2ptr code = f2__string__load(cause, filename);
  return f2__source__new(cause, code);
}
def_pcfunk1(source__load, filename, return f2__source__load(this_cause, filename));

f2ptr f2source__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2source__primobject_type__new(cause);
  return this;
}


// package

def_primobject_2_slot(package,
		      name,
		      dependencies);

f2ptr f2__package__new(f2ptr cause, f2ptr name, f2ptr dependencies) {return f2package__new(cause, name, dependencies);}
def_pcfunk2(package__new, name, dependencies, return f2__package__new(this_cause, name, dependencies));



f2ptr f2package__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2package__primobject_type__new(cause);
  return this;
}


f2ptr f2__pathname__scan_for_filenames_by_extension(f2ptr cause, f2ptr pathname, f2ptr extension) {
  if ((! raw__string__is_type(cause, pathname)) ||
      (! raw__string__is_type(cause, extension))) {
    return f2larva__new(cause, 1, nil);
  }
  u64   pathname__length = raw__string__length(cause, pathname);
  char* pathname__str    = (char*)alloca(pathname__length + 1);
  raw__string__str_copy(cause, pathname, pathname__str);
  pathname__str[pathname__length] = 0;
  
  u64   extension__length = raw__string__length(cause, extension);
  char* extension__str    = (char*)alloca(extension__length + 1);
  raw__string__str_copy(cause, extension, extension__str);
  extension__str[extension__length] = 0;
  
  f2ptr matching_filenames = nil;
  {
    DIR* dirp = opendir(pathname__str);
    if (dirp == NULL) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "pathname-scan_for_filenames_by_extension"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "could_not_open_directory"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "pathname"),  pathname);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "extension"), extension);
      char* errno_str = "unrecognized error number.";
      switch(errno) {
      case EACCES:  errno_str = "Permission denied.";                                    break;
      case EBADF:   errno_str = "fd is not a valid file descriptor opened for reading."; break;
      case EMFILE:  errno_str = "Too many file descriptors in use by process.";          break;
      case ENFILE:  errno_str = "Too many files are currently open in the system.";      break;
      case ENOENT:  errno_str = "Directory does not exist, or name is an empty string."; break;
      case ENOMEM:  errno_str = "Insufficient memory to complete the operation.";        break;
      case ENOTDIR: errno_str = "name is not a directory.";                              break;
      }
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "description"), new__string(cause, errno_str));
      return f2larva__new(cause, 67, f2__bug__new(cause, f2integer__new(cause, 67), bug_frame));
    }
    struct dirent* directory_entry;
    do {
      directory_entry = readdir(dirp);
      if (directory_entry) {
	char* d_name     = directory_entry->d_name;
	char* rindex_ptr = rindex(d_name, '.');
	if ((rindex_ptr != NULL) && (strcmp(extension__str, rindex_ptr + 1) == 0)) {
	  f2ptr matching_filename = new__string(cause, d_name);
	  matching_filenames = f2cons__new(cause, matching_filename, matching_filenames);
	}
      }
    } while (directory_entry);
    closedir(dirp);
    
  }
  return matching_filenames;
}
def_pcfunk2(pathname__scan_for_filenames_by_extension, pathname, extension, return f2__pathname__scan_for_filenames_by_extension(this_cause, pathname, extension));

// **

void f2__package__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  __source_expression__symbol = new__symbol(cause, "source_expression");
  __source__symbol            = new__symbol(cause, "source");
  __package__symbol           = new__symbol(cause, "package");
}

void f2__package__initialize() {
  f2__package__reinitialize_globalvars();
  funk2_module_registration__add_module(&(__funk2.module_registration), "package", "", &f2__cause__reinitialize_globalvars);
  f2ptr cause = initial_cause();
  
  //--
  
  // source_expression
  
  initialize_primobject_6_slot(source_expression,
			       body, first_line, last_line, first_column, last_column, subexpressions);
  
  // source
  
  initialize_primobject_1_slot(source,
			       code);
  
  f2__primcfunk__init__1(source__load, filename, "load source code from a file named by filename.");
  
  // package
  
  initialize_primobject_2_slot(package,
			       name,
			       dependencies);
  
  // pathname
  
  f2__primcfunk__init__2(pathname__scan_for_filenames_by_extension, pathname, extension, "Scans a directory name and returns all filenames that match the given extension.");
  
}


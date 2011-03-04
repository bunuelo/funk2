// 
// Copyright (c) 2007-2011 Bo Morgan.
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

f2ptr raw__source_expression__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  f2ptr print_as_frame_hash = raw__terminal_print_frame__print_as_frame_hash(cause, terminal_print_frame);
  f2ptr frame               = raw__ptypehash__lookup(cause, print_as_frame_hash, this);
  if (frame == nil) {
    frame = f2__frame__new(cause, f2list14__new(cause,
						new__symbol(cause, "print_object_type"), new__symbol(cause, "source_expression"),
						new__symbol(cause, "body"),           f2__source_expression__body(          cause, this),
						new__symbol(cause, "first_line"),     f2__source_expression__first_line(    cause, this),
						new__symbol(cause, "last_line"),      f2__source_expression__last_line(     cause, this),
						new__symbol(cause, "first_column"),   f2__source_expression__first_column(  cause, this),
						new__symbol(cause, "last_column"),    f2__source_expression__last_column(   cause, this),
						new__symbol(cause, "subexpressions"), f2__source_expression__subexpressions(cause, this)));
    f2__ptypehash__add(cause, print_as_frame_hash, this, frame);
  }
  return raw__frame__terminal_print_with_frame(cause, frame, terminal_print_frame);
}

f2ptr f2__source_expression__terminal_print_with_frame(f2ptr cause, f2ptr this, f2ptr terminal_print_frame) {
  assert_argument_type(source_expression,    this);
  assert_argument_type(terminal_print_frame, terminal_print_frame);
  return raw__source_expression__terminal_print_with_frame(cause, this, terminal_print_frame);
}
def_pcfunk2(source_expression__terminal_print_with_frame, this, terminal_print_frame, return f2__source_expression__terminal_print_with_frame(this_cause, this, terminal_print_frame));


f2ptr f2source_expression__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2source_expression__primobject_type__new(cause);
  {char* slot_name = "terminal_print_with_frame";  f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.primobject.primobject_type_source_expression.terminal_print_with_frame__funk);}
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


f2ptr raw__source__eval(f2ptr cause, f2ptr this) {
  return nil;
}

f2ptr f2__source__eval(f2ptr cause, f2ptr this) {
  assert_argument_type(source_expression, this);
  return raw__source__eval(cause, this);
}
def_pcfunk1(source__eval, this, return f2__source__eval(this_cause, this));


// package

def_primobject_8_slot(package,
		      pathname,
		      name,
		      package_dependencies,
		      source_dependencies,
		      object_types_defined_set,
		      loaded_all_dependencies_time,
		      documentation,
		      binary_dependencies);

f2ptr f2__package__new(f2ptr cause, f2ptr pathname, f2ptr name, f2ptr package_dependencies, f2ptr source_dependencies, f2ptr documentation, f2ptr binary_dependencies) {
  f2ptr object_types_defined_set     = f2__set__new(cause);
  f2ptr loaded_all_dependencies_time = nil;
  return f2package__new(cause, pathname, name, package_dependencies, source_dependencies, object_types_defined_set, loaded_all_dependencies_time, documentation, binary_dependencies);
}
def_pcfunk6(package__new, pathname, name, package_dependencies, source_dependencies, documentation, binary_dependencies, return f2__package__new(this_cause, pathname, name, package_dependencies, source_dependencies, documentation, binary_dependencies));



f2ptr f2package__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2package__primobject_type__new(cause);
  return this;
}



f2ptr f2__current_working_directory(f2ptr cause) {
  char* current_working_directory__str = getcwd(NULL, 0);
  f2ptr current_working_directory = new__string(cause, current_working_directory__str);
  free(current_working_directory__str);
  return current_working_directory;
}
def_pcfunk0(current_working_directory, return f2__current_working_directory(this_cause));

f2ptr raw__pathname__concat(f2ptr cause, f2ptr this, f2ptr that) {
  u64 this__length = raw__string__length(cause, this);
  u8* this__str    = (u8*)alloca(this__length + 1);
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;

  u64 that__length = raw__string__length(cause, that);
  u8* that__str    = (u8*)alloca(that__length + 1);
  raw__string__str_copy(cause, that, that__str);
  that__str[that__length] = 0;
  
  int separator_count = 0;
  if (this__str[this__length - 1] == '/') {
    separator_count ++;
  }
  if (that__str[0] == '/') {
    separator_count ++;
  }
  
  if (separator_count == 0) {
    return f2__stringlist__concat(cause, f2list3__new(cause, this, new__string(cause, "/"), that));
  } else if (separator_count == 1) {
    return f2__stringlist__concat(cause, f2list2__new(cause, this, that));
  } else { // separator_count == 2
    this__str[this__length - 1] = 0;
    return f2__stringlist__concat(cause, f2list2__new(cause, new__string(cause, (char*)this__str), that));
  }
}

f2ptr f2__pathname__concat(f2ptr cause, f2ptr this, f2ptr that) {
  assert_argument_type(string, this);
  assert_argument_type(string, that);
  return raw__pathname__concat(cause, this, that);
}
def_pcfunk2(pathname__concat, this, that, return f2__pathname__concat(this_cause, this, that));


boolean_t raw__pathnamelist__is_type(f2ptr cause, f2ptr object) {
  f2ptr iter = object;
  while (iter != nil) {
    if ((! raw__cons__is_type(cause, iter)) &&
	(! raw__list__is_type(cause, iter))) {
      return boolean__false;
    }
    f2ptr element = f2__first(cause, element);
    if (! raw__string__is_type(cause, element)) {
      return boolean__false;
    }
    iter = f2__next(cause, iter);
  }
  return boolean__false;
}

f2ptr raw__pathnamelist__concat(f2ptr cause, f2ptr this) {
  f2ptr result = nil;
  f2ptr iter = this;
  while (iter) {
    f2ptr pathname = f2__first(cause, iter);
    if (result == nil) {
      result = pathname;
    } else {
      result = f2__pathname__concat(cause, result, pathname);
    }
    iter = f2__next(cause, iter);
  }
  if (! result) {
    result = new__string(cause, "");
  }
  return result;
}

f2ptr f2__pathnamelist__concat(f2ptr cause, f2ptr this) {
  assert_argument_type(pathnamelist, this);
  return raw__pathnamelist__concat(cause, this);
}
def_pcfunk1(pathnamelist__concat, this, return f2__pathnamelist__concat(this_cause, this));

boolean_t raw__pathname__is_absolute(f2ptr cause, f2ptr this) {
  u64 this__length = raw__string__length(cause, this);
  u8* this__str    = (u8*)alloca(this__length);
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;
  
  return (this__str[0] == '/');
}

f2ptr f2__pathname__is_absolute(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return f2bool__new(raw__pathname__is_absolute(cause, this));
}
def_pcfunk1(pathname__is_absolute, this, return f2__pathname__is_absolute(this_cause, this));

f2ptr raw__pathname__as__absolute_pathname(f2ptr cause, f2ptr this) {
  if (raw__pathname__is_absolute(cause, this)) {
    return this;
  }
  return f2__pathname__concat(cause, f2__current_working_directory(cause), this);
}

f2ptr f2__pathname__as__absolute_pathname(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__pathname__as__absolute_pathname(cause, this);
}
def_pcfunk1(pathname__as__absolute_pathname, this, return f2__pathname__as__absolute_pathname(this_cause, this));

f2ptr raw__pathname__directory_pathname(f2ptr cause, f2ptr this) {
  u64 this__length = raw__string__length(cause, this);
  u8* this__str    = (u8*)alloca(this__length);
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;
  
  char* last_slash = rindex((char*)this__str, '/');
  if (last_slash) {
    last_slash[1] = 0;
  } else {
    this__str[0] = 0;
  }
  return new__string(cause, (char*)this__str);
}

f2ptr f2__pathname__directory_pathname(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__pathname__directory_pathname(cause, this);
}
def_pcfunk1(pathname__directory_pathname, this, return f2__pathname__directory_pathname(this_cause, this));

f2ptr f2__pathname__scan_for_filenames(f2ptr cause, f2ptr pathname) {
  assert_argument_type(string, pathname);
  u64 pathname__length = raw__string__length(cause, pathname);
  u8* pathname__str    = (u8*)alloca(pathname__length + 1);
  raw__string__str_copy(cause, pathname, pathname__str);
  pathname__str[pathname__length] = 0;
  
  f2ptr absolute_filenames = nil;
  {
    DIR* dirp = opendir((char*)pathname__str);
    if (dirp == NULL) {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),  new__symbol(cause, "pathname-scan_for_filenames_by_extension"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),  new__symbol(cause, "could_not_open_directory"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "pathname"),  pathname);
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
	f2ptr relative_filename = f2__pathname__concat(cause, pathname, new__string(cause, directory_entry->d_name));
	f2ptr absolute_filename = f2__pathname__as__absolute_pathname(cause, relative_filename);
	absolute_filenames = f2cons__new(cause, absolute_filename, absolute_filenames);
      }
    } while (directory_entry);
    closedir(dirp);
  }
  return absolute_filenames;
}
def_pcfunk1(pathname__scan_for_filenames, pathname, return f2__pathname__scan_for_filenames(this_cause, pathname));

f2ptr f2__pathname__scan_for_filenames_by_extension(f2ptr cause, f2ptr pathname, f2ptr extension) {
  assert_argument_type(string, this);
  f2ptr filenames = f2__pathname__scan_for_filenames(cause, pathname);
  if (raw__larva__is_type(cause, filenames)) {
    return filenames;
  }
  
  u64 extension__length = raw__string__length(cause, extension);
  u8* extension__str    = (u8*)alloca(extension__length + 1);
  raw__string__str_copy(cause, extension, extension__str);
  extension__str[extension__length] = 0;
  
  f2ptr matching_filenames = nil;
  {
    f2ptr iter = filenames;
    while (iter) {
      f2ptr filename = f2__cons__car(cause, iter);
      
      u64 filename__length = raw__string__length(cause, filename);
      u8* filename__str    = (u8*)alloca(filename__length + 1);
      raw__string__str_copy(cause, filename, filename__str);
      filename__str[filename__length] = 0;
      
      char* rindex_ptr = rindex((char*)filename__str, '.');
      if ((rindex_ptr != NULL) && (strcmp((char*)extension__str, rindex_ptr + 1) == 0)) {
	f2ptr matching_filename = filename;
	matching_filenames = f2cons__new(cause, matching_filename, matching_filenames);
      }
      iter = f2__cons__cdr(cause, iter);
    }
  }
  return matching_filenames;
}
def_pcfunk2(pathname__scan_for_filenames_by_extension, pathname, extension, return f2__pathname__scan_for_filenames_by_extension(this_cause, pathname, extension));

f2ptr raw__pathname__stat(f2ptr cause, f2ptr this) {
  u64 this__length = raw__string__length(cause, this);
  u8* this__str    = (u8*)alloca(this__length);
  raw__string__str_copy(cause, this, this__str);
  this__str[this__length] = 0;
  
  struct stat buf;
  if (stat((char*)this__str, &buf) != 0) {
    char* error_str = "unknown error occurred.";
    switch(errno) {
    case EACCES:       error_str = "Search permission is denied for one of the directories in the path prefix of path.  (See also path_resolution(7).)"; break;
    case EBADF:        error_str = "fd is bad."; break;
    case EFAULT:       error_str = "Bad address."; break;
    case ELOOP:        error_str = "Too many symbolic links encountered while traversing the path."; break;
    case ENAMETOOLONG: error_str = "File name too long."; break;
    case ENOENT:       error_str = "A component of the path path does not exist, or the path is an empty string."; break;
    case ENOMEM:       error_str = "Out of memory (i.e., kernel memory)."; break;
    case ENOTDIR:      error_str = "A component of the path is not a directory."; break;
    case EOVERFLOW:    error_str = "(stat()) path refers to a file whose size cannot be represented in the type off_t.  This can occur when an application compiled on a 32-bit platform without -D_FILE_OFFSET_BITS=64 calls stat() on a file whose size exceeds (2<<31)-1 bits."; break;
    }
    {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),    new__symbol(cause, "failed_to_stat_pathname"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),    new__symbol(cause, "pathname-stat"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "this"),        this);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "description"), new__string(cause, error_str));
      return f2larva__new(cause, 655, f2__bug__new(cause, f2integer__new(cause, 655), bug_frame));
    }
  }
  f2ptr stat_frame = f2__frame__new(cause, nil);
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "id_of_device_containing_file"),        f2integer__new(cause, (s64)buf.st_dev));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "inode_number"),                        f2integer__new(cause, (s64)buf.st_ino));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "protection_mode"),                     f2integer__new(cause, (s64)buf.st_mode));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "number_of_hard_links"),                f2integer__new(cause, (s64)buf.st_nlink));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "user_id_of_owner"),                    f2integer__new(cause, (s64)buf.st_uid));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "group_id_of_owner"),                   f2integer__new(cause, (s64)buf.st_gid));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "device_id"),                           f2integer__new(cause, (s64)buf.st_rdev));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "total_size_in_bytes"),                 f2integer__new(cause, (s64)buf.st_size));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "blocksize_for_file_system_io"),        f2integer__new(cause, (s64)buf.st_blksize));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "number_of_512_byte_blocks_allocated"), f2integer__new(cause, (s64)buf.st_blocks));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "time_of_last_access"),                 raw__time__new_from_unix_time(cause, buf.st_atime));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "time_of_last_modification"),           raw__time__new_from_unix_time(cause, buf.st_mtime));
  f2__frame__add_var_value(cause, stat_frame, new__symbol(cause, "time_of_last_status_change"),          raw__time__new_from_unix_time(cause, buf.st_ctime));
  return stat_frame;
}

f2ptr f2__pathname__stat(f2ptr cause, f2ptr this) {
  assert_argument_type(string, this);
  return raw__pathname__stat(cause, this);
}
def_pcfunk1(pathname__stat, this, return f2__pathname__stat(this_cause, this));


f2ptr raw__pathname__exists(f2ptr cause, u8* filename) {
  int result = access((char*)filename, F_OK);
  if (result == 0) {
    return f2bool__new(boolean__true);
  }
  char* error_string = NULL;
  switch (errno) {
  case ENOENT:
    return f2bool__new(boolean__false);
  case EROFS:        error_string = "Write permission was requested for a file on a read-only file system."; break;
  case ENOTDIR:      error_string = "A component used as a directory in pathname is not, in fact, a directory."; break;
  case ELOOP:        error_string = "Too many symbolic links were encountered in resolving pathname."; break;
  case EACCES:       error_string = "The requested access would be denied to the file, or search permission is denied for one of the directories in the path prefix of pathname.  (See also path_resolution(7).)"; break;
  case ENAMETOOLONG: error_string = "pathname is too long."; break;
  case EFAULT:       error_string = "pathname points outside your accessible address space."; break;
  case EINVAL:       error_string = "mode was incorrectly specified."; break;
  case EIO:          error_string = "An I/O error occurred."; break;
  case ENOMEM:       error_string = "Insufficient kernel memory was available."; break;
  case ETXTBSY:      error_string = "Write access was requested to an executable which is being executed."; break;
  default:           error_string = "undocumented access failure."; break;
  }
  return f2larva__new(cause, 1233, f2__bug__new(cause, f2integer__new(cause, 1233), f2__frame__new(cause, f2list8__new(cause,
														       new__symbol(cause, "bug_type"),     new__symbol(cause, "access_failure_while_checking_if_file_exists"),
														       new__symbol(cause, "funkname"),     new__symbol(cause, "pathname-exists"),
														       new__symbol(cause, "error_string"), new__string(cause, error_string),
														       new__symbol(cause, "filename"),     new__string(cause, (char*)filename)))));
}

f2ptr f2__pathname__exists(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  s64 filename__length = raw__string__length(cause, filename);
  u8* filename__string = (u8*)from_ptr(f2__malloc(filename__length + 1));
  raw__string__str_copy(cause, filename, filename__string);
  filename__string[filename__length] = 0;
  
  f2ptr result = raw__pathname__exists(cause, filename__string);
  
  f2__free(to_ptr(filename__string));
  return result;
}
def_pcfunk1(pathname__exists, filename, return f2__pathname__exists(this_cause, filename));


f2ptr raw__pathname__rename(f2ptr cause, u8* old_filename, u8* new_filename) {
  int result = rename((char*)old_filename, (char*)new_filename);
  if (result == 0) {
    return nil;
  }
  char* error_string = NULL;
  switch (errno) {
  case EACCES:       error_string = "A component of either path prefix denies search permission; or one of the directories containing old or new denies write permissions; or, write permission is required and is denied for a directory pointed to by the old or new arguments."; break;
  case EBUSY:        error_string = "The directory named by old or new is currently in use by the system or another process, and the implementation considers this an error."; break;
  case EEXIST:
  case ENOTEMPTY:    error_string = "The link named by new is a directory that is not an empty directory."; break;
  case EINVAL:       error_string = "The new directory pathname contains a path prefix that names the old directory."; break;
  case EIO:          error_string = "A physical I/O error has occurred."; break;
  case EISDIR:       error_string = "The new argument points to a directory and the old argument points to a file that is not a directory."; break;
  case ELOOP:        error_string = "A loop exists in symbolic links encountered during resolution of the path argument."; break;
  case EMLINK:       error_string = "The file named by old is a directory, and the link count of the parent directory of new would exceed {LINK_MAX}."; break;
  case ENAMETOOLONG: error_string = "The length of the old or new argument exceeds {PATH_MAX} or a pathname component is longer than {NAME_MAX}."; break;
  case ENOENT:       error_string = "The link named by old does not name an existing file, or either old or new points to an empty string."; break;
  case ENOSPC:       error_string = "The directory that would contain new cannot be extended."; break;
  case ENOTDIR:      error_string = "A component of either path prefix is not a directory; or the old argument names a directory and new argument names a non-directory file."; break;
  case EROFS:        error_string = "The requested operation requires writing in a directory on a read-only file system."; break;
  case EXDEV:        error_string = "The links named by new and old are on different file systems and the implementation does not support links between file systems."; break;
  case ETXTBSY:      error_string = "The file to be renamed is a pure procedure (shared text) file that is being executed."; break;
  default:           error_string = "undocumented rename failure."; break;
  }
  return f2larva__new(cause, 1235, f2__bug__new(cause, f2integer__new(cause, 1235), f2__frame__new(cause, f2list10__new(cause,
															new__symbol(cause, "bug_type"),     new__symbol(cause, "rename_failure"),
															new__symbol(cause, "funkname"),     new__symbol(cause, "pathname-rename"),
															new__symbol(cause, "error_string"), new__string(cause, error_string),
															new__symbol(cause, "old_filename"), new__string(cause, (char*)old_filename),
															new__symbol(cause, "new_filename"), new__string(cause, (char*)new_filename)))));
}

f2ptr f2__pathname__rename(f2ptr cause, f2ptr old_filename, f2ptr new_filename) {
  assert_argument_type(string, old_filename);
  assert_argument_type(string, new_filename);
  s64 old_filename__length = raw__string__length(cause, old_filename);
  u8* old_filename__string = (u8*)from_ptr(f2__malloc(old_filename__length + 1));
  raw__string__str_copy(cause, old_filename, old_filename__string);
  old_filename__string[old_filename__length] = 0;
  
  s64 new_filename__length = raw__string__length(cause, new_filename);
  u8* new_filename__string = (u8*)from_ptr(f2__malloc(new_filename__length + 1));
  raw__string__str_copy(cause, new_filename, new_filename__string);
  new_filename__string[new_filename__length] = 0;
  
  f2ptr result = raw__pathname__rename(cause, old_filename__string, new_filename__string);
  
  f2__free(to_ptr(old_filename__string));
  f2__free(to_ptr(new_filename__string));
  return result;
}
def_pcfunk2(pathname__rename, old_filename, new_filename, return f2__pathname__rename(this_cause, old_filename, new_filename));


f2ptr raw__getenv(f2ptr cause, f2ptr environment_variable) {
  u64 environment_variable__length = raw__string__length(cause, environment_variable);
  u8* environment_variable__str    = (u8*)alloca(environment_variable__length);
  raw__string__str_copy(cause, environment_variable, environment_variable__str);
  environment_variable__str[environment_variable__length] = 0;
  
  char* environment_value = getenv((char*)environment_variable__str);
  if (environment_value == NULL) {
    return nil;
  }
  return new__string(cause, environment_value);
}

f2ptr f2__getenv(f2ptr cause, f2ptr environment_variable) {
  assert_argument_type(string, environment_variable);
  return raw__getenv(cause, environment_variable);
}
def_pcfunk1(getenv, environment_variable, return f2__getenv(this_cause, environment_variable));



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
  
  {char* symbol_str = "terminal_print_with_frame"; __funk2.globalenv.object_type.primobject.primobject_type_source_expression.terminal_print_with_frame__symbol = f2symbol__new(cause, strlen(symbol_str), (u8*)symbol_str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(source_expression__terminal_print_with_frame, this, terminal_print_frame, cfunk, 0, "Prints a source_expression object using a terminal_print_frame.");
    __funk2.globalenv.object_type.primobject.primobject_type_source_expression.terminal_print_with_frame__funk = never_gc(cfunk);}
  
  // source
  
  initialize_primobject_1_slot(source,
			       code);
  
  f2__primcfunk__init__1(source__load, filename, "load source code from a file named by filename.");
  
  f2__primcfunk__init__1(source__eval, this, "");
  
  // package
  
  initialize_primobject_8_slot(package,
			       pathname,
			       name,
			       package_dependencies,
			       source_dependencies,
			       object_types_defined_set,
			       loaded_all_dependencies_time,
			       documentation,
			       binary_dependencies);
  
  // pathname
  
  f2__primcfunk__init__2(pathname__concat,                          this, that,                 "Concatenates two paths and returns the result in a new path string.");
  f2__primcfunk__init__1(pathnamelist__concat,                      this,                       "Concatenates a list of paths and returns the result in a new path string.");
  f2__primcfunk__init__1(pathname__is_absolute,                     this,                       "Returns true if pathname represents an absolute path.");
  f2__primcfunk__init__1(pathname__directory_pathname,              this,                       "Returns the directory part of a path.");
  f2__primcfunk__init__1(pathname__scan_for_filenames,              pathname,                   "Scans a directory name and returns all filenames.");
  f2__primcfunk__init__2(pathname__scan_for_filenames_by_extension, pathname, extension,        "Scans a directory name and returns all filenames that match the given extension.");
  f2__primcfunk__init__0(current_working_directory,                                             "Returns a string representing the current working directory name.");
  f2__primcfunk__init__1(pathname__as__absolute_pathname,           this,                       "Returns an absolute pathname for this pathname.");
  f2__primcfunk__init__1(pathname__stat,                            this,                       "Returns a frame with stat info about this pathname.");
  f2__primcfunk__init__1(pathname__exists,                          filename,                   "Returns a boolean value specifying whether or not the given pathname exists.");
  f2__primcfunk__init__2(pathname__rename,                          old_filename, new_filename, "Renames a pathname.");
  f2__primcfunk__init__1(getenv,                                    environment_variable,       "Returns the environment definition of the given string variable or returns nil if the variable is not defined.");
  
}


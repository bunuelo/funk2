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

#include "funk2.h"

f2ptr raw__chunk__save(f2ptr cause, f2ptr this, f2ptr filename) {
  int fd;
  {
    u64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    
    fd = open((char*)filename__utf8_str, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    f2__free(to_ptr(filename__utf8_str));
  }
  if (fd == -1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_file"), new__string(cause, __FILE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line"), f2integer__new(cause, __LINE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"), filename);
    return f2larva__new(cause, 89, f2__bug__new(cause, f2integer__new(cause, 89), bug_frame));
  }
  u64 write_bytes;
  u64 this__length = f2chunk__length(this, cause);
  {
    u8* this__str    = (u8*)from_ptr(f2__malloc(this__length));
    f2chunk__str_copy(this, cause, this__str);
    
    write_bytes = write(fd, this__str, this__length);
    
    f2__free(to_ptr(this__str));
  }
  f2ptr result = nil;
  if (write_bytes != this__length) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),    new__symbol(cause, "could_not_write_to_file"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_file"), new__string(cause, __FILE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "source_line"), f2integer__new(cause, __LINE__));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"),    filename);
    return f2larva__new(cause, 89, f2__bug__new(cause, f2integer__new(cause, 89), bug_frame));
  }
  close(fd);
  return result;
}

f2ptr f2__chunk__save(f2ptr cause, f2ptr this, f2ptr filename) {
  assert_argument_type(chunk,  this);
  assert_argument_type(string, filename);
  return raw__chunk__save(cause, this, filename);
}
def_pcfunk2(chunk__save, this, filename,
	    "Save this chunk to a file of filename.",
	    return f2__chunk__save(this_cause, this, filename));


f2ptr f2__chunk__load(f2ptr cause, f2ptr filename) {
  assert_argument_type(string, filename);
  int fd;
  {
    u64 filename__utf8_length = raw__string__utf8_length(cause, filename);
    u8* filename__utf8_str    = (u8*)from_ptr(f2__malloc(filename__utf8_length + 1));
    raw__string__utf8_str_copy(cause, filename, filename__utf8_str);
    filename__utf8_str[filename__utf8_length] = 0;
    
    fd = open((char*)filename__utf8_str, O_RDONLY);
    
    f2__free(to_ptr(filename__utf8_str));
  }
  if (fd == -1) {
    f2ptr bug_frame = f2__frame__new(cause, nil);
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"), new__symbol(cause, "could_not_open_file_for_reading"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"), new__symbol(cause, "chunk-load"));
    f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"), filename);
    return f2larva__new(cause, 90, f2__bug__new(cause, f2integer__new(cause, 90), bug_frame));
  }
  u64 file__length = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  u8* file__str = (u8*)malloc(file__length);
  u64 read_length = read(fd, file__str, file__length);
  if (read_length != file__length) {
    printf("\nread_length=" u64__fstr ", file__length=" u64__fstr "\n", read_length, file__length);
    free(file__str);
    {
      f2ptr bug_frame = f2__frame__new(cause, nil);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "bug_type"),    new__symbol(cause, "could_not_read_complete_file"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "funkname"),    new__symbol(cause, "chunk-load"));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "filename"),    filename);
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "read_length"), f2integer__new(cause, read_length));
      f2__frame__add_var_value(cause, bug_frame, new__symbol(cause, "file_length"), f2integer__new(cause, file__length));
      return f2larva__new(cause, 91, f2__bug__new(cause, f2integer__new(cause, 91), bug_frame));
    }
  }
  f2ptr new_chunk = f2chunk__new(cause, file__length, file__str);
  free(file__str);
  close(fd);
  return new_chunk;
}
def_pcfunk1(chunk__load, filename,
	    "Load a chunk from a filename.",
	    return f2__chunk__load(this_cause, filename));



f2ptr f2chunk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2chunk__primobject_type__new(cause);
  {char* slot_name = "save"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.save__funk);}
  return this;
}

// **

void f2__chunk__defragment__fix_pointers() {
  // -- reinitialize --
  
  
  
  // -- initialize --
  
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.save__symbol);
  f2__primcfunk__init__defragment__fix_pointers(chunk__save);
  defragment__fix_pointer(__funk2.globalenv.object_type.ptype.ptype_chunk.save__funk);
  
  f2__primcfunk__init__defragment__fix_pointers(chunk__load);
  
}

void f2__chunk__reinitialize_globalvars() {
  f2ptr cause = initial_cause();
  
  {char* str = "save"; __funk2.globalenv.object_type.ptype.ptype_chunk.save__symbol = new__symbol(cause, str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__save, this, filename, cfunk); __funk2.globalenv.object_type.ptype.ptype_chunk.save__funk = never_gc(cfunk);}
  
  f2__primcfunk__init__1(chunk__load, filename);
}

void f2__chunk__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "chunk", "", &f2__chunk__reinitialize_globalvars, &f2__chunk__defragment__fix_pointers);
  
  f2__chunk__reinitialize_globalvars();
}


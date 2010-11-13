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

f2ptr raw__chunk__save(f2ptr cause, f2ptr this, f2ptr filename) {
  int fd;
  {
    u64 filename__length = f2chunk__length(filename, cause);
    u8* filename__str = (u8*)from_ptr(f2__malloc(filename__length + 1));
    f2chunk__str_copy(filename, cause, filename__str);
    filename__str[filename__length] = 0;
    
    fd = open((char*)filename__str, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    
    f2__free(to_ptr(filename__str));
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
  if ((! raw__chunk__is_type(cause, this)) ||
      (! raw__string__is_type(cause, filename))) {
    return f2larva__new(cause, 1, nil);
  }
  raw__chunk__save(cause, this, filename);
}
def_pcfunk2(chunk__save, this, filename, return f2__chunk__save(this_cause, this, filename));


f2ptr f2chunk__primobject_type__new_aux(f2ptr cause) {
  f2ptr this = f2chunk__primobject_type__new(cause);
  {char* slot_name = "save"; f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, slot_name), __funk2.globalenv.object_type.ptype.ptype_chunk.save__funk);}
  return this;
}

// **

void f2__chunk__reinitialize_globalvars() {
}

void f2__chunk__initialize() {
  f2ptr cause = initial_cause();
  
  funk2_module_registration__add_module(&(__funk2.module_registration), "chunk", "", &f2__chunk__reinitialize_globalvars);
  
  f2__chunk__reinitialize_globalvars();
  
  {char* str = "save"; __funk2.globalenv.object_type.ptype.ptype_chunk.save__symbol = f2symbol__new(cause, strlen(str), (u8*)str);}
  {f2__primcfunk__init__with_c_cfunk_var__2_arg(chunk__save, this, filename, cfunk, 1, "save this chunk to a file of filename."); __funk2.globalenv.object_type.ptype.ptype_chunk.save__funk = never_gc(cfunk);}
}


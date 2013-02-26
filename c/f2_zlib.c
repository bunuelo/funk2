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

#define ZLIB_CHUNK             ((s64)(1024ull * 1024ull))
#define ZLIB_COMPRESSION_LEVEL 2









// *dest_length returns length of src_data after compression.
// dest_data can be NULL.
boolean_t zlib__deflate(u8* dest_data, u64* dest_length, u8* src_data, u64 src_length) {
  s64      zlib_result;
  s64      zlib_flush_command;
  u64      byte_num;
  z_stream zlib_stream;
  u8*      out_buffer;
  u64      available_input = src_length;
  u64      src_index       = 0;
  u64      dest_index      = 0;
  
  // allocate deflate state
  zlib_stream.zalloc = Z_NULL;
  zlib_stream.zfree  = Z_NULL;
  zlib_stream.opaque = Z_NULL;
  zlib_result = deflateInit(&zlib_stream, ZLIB_COMPRESSION_LEVEL);
  if (zlib_result != Z_OK) {
    return boolean__true;
  }
  
  out_buffer = (u8*)from_ptr(f2__malloc(ZLIB_CHUNK));
  
  while (available_input > 0) {
    
    if (available_input > ZLIB_CHUNK) {
      zlib_stream.avail_in = ZLIB_CHUNK;
      zlib_flush_command = Z_NO_FLUSH;
    } else {
      zlib_stream.avail_in = available_input;
      zlib_flush_command = Z_FINISH;
    }
    
    //status("available_input = " u64__fstr, available_input);
    //status("src_index       = " u64__fstr, src_index);
    //status("dest_index      = " u64__fstr, dest_index);
    
    zlib_stream.next_in = src_data + src_index;
    
    do {
      zlib_stream.avail_out = ZLIB_CHUNK;
      zlib_stream.next_out  = out_buffer;
      zlib_result = deflate(&zlib_stream, zlib_flush_command);
      assert(zlib_result != Z_STREAM_ERROR);
      byte_num = ZLIB_CHUNK - zlib_stream.avail_out;
      if (dest_data) {
	memcpy(dest_data + dest_index, out_buffer, byte_num);
      }
      dest_index += byte_num;
    } while (zlib_stream.avail_out == 0);
    
    //status("zlib_stream.avail_in = " u64__fstr, (u64)(zlib_stream.avail_in));
    
    assert(zlib_stream.avail_in == 0); // all input used
    
    
    if (available_input > ZLIB_CHUNK) {
      available_input -= ZLIB_CHUNK;
      src_index       += ZLIB_CHUNK;
    } else {
      available_input = 0;
    }
  }
  
  // clean up and return
  deflateEnd(&zlib_stream);
  
  f2__free(to_ptr(out_buffer));
  
  *dest_length = dest_index;
  return boolean__false;
}

boolean_t zlib__deflate_length(u8* src_data, u64 src_length, u64* dest_length) {
  return zlib__deflate(NULL, dest_length, src_data, src_length);
}

f2ptr raw__chunk__deflate(f2ptr cause, f2ptr this) {
  u64 src_length = raw__chunk__length(cause, this);
  u8* src_data   = (u8*)from_ptr(f2__malloc(src_length));
  raw__chunk__str_copy(cause, this, src_data);
  
  u64 dest_length = 0;
  if (zlib__deflate_length(src_data, src_length, &dest_length)) {
    f2__free(to_ptr(src_data));
    return nil;
  }
  
  u8* temp_data = (u8*)from_ptr(f2__malloc(dest_length));
  if (zlib__deflate(temp_data, &dest_length, src_data, src_length)) {
    f2__free(to_ptr(src_data));
    f2__free(to_ptr(temp_data));
    return nil;
  }
  f2__free(to_ptr(src_data));
  
  f2ptr new_chunk = f2chunk__new(cause, dest_length, temp_data);
  f2__free(to_ptr(temp_data));
  return new_chunk;
}

f2ptr f2__chunk__deflate(f2ptr cause, f2ptr this) {
  assert_argument_type(chunk, this);
  return raw__chunk__deflate(cause, this);
}
def_pcfunk1(chunk__deflate, this,
	    "",
	    return f2__chunk__deflate(this_cause, this));


boolean_t zlib__inflate(u8* dest_data, u64* dest_length, u8* src_data, u64 src_length) {
  s64      zlib_result;
  s64      zlib_flush_command;
  u64      byte_num;
  z_stream zlib_stream;
  u8*      out_buffer;
  u64      available_input = src_length;
  u64      src_index       = 0;
  u64      dest_index      = 0;
  
  // allocate inflate state
  zlib_stream.zalloc   = Z_NULL;
  zlib_stream.zfree    = Z_NULL;
  zlib_stream.opaque   = Z_NULL;
  zlib_stream.avail_in = 0;
  zlib_stream.next_in  = Z_NULL;
  zlib_result = inflateInit(&zlib_stream);
  if (zlib_result != Z_OK) {
    return boolean__true;
  }
  
  if (available_input != 0) {
    
    out_buffer = (u8*)from_ptr(f2__malloc(ZLIB_CHUNK));
    
    while (available_input > 0) {
      
      if (available_input > ZLIB_CHUNK) {
	zlib_stream.avail_in = ZLIB_CHUNK;
	zlib_flush_command   = Z_NO_FLUSH;
      } else {
	zlib_stream.avail_in = available_input;
	zlib_flush_command   = Z_FINISH;
      }
      
      zlib_stream.next_in = src_data + src_index;
      
      do {
	zlib_stream.avail_out = ZLIB_CHUNK;
	zlib_stream.next_out = out_buffer;
	zlib_result = inflate(&zlib_stream, zlib_flush_command);
	assert(zlib_result != Z_STREAM_ERROR);
	switch (zlib_result) {
	case Z_NEED_DICT:
	case Z_DATA_ERROR:
	case Z_MEM_ERROR:
	  f2__free(to_ptr(out_buffer));
	  inflateEnd(&zlib_stream);
	  return boolean__true;
	}
	byte_num = ZLIB_CHUNK - zlib_stream.avail_out;
	if (dest_data) {
	  memcpy(dest_data + dest_index, out_buffer, byte_num);
	}
	dest_index += byte_num;
      } while (zlib_stream.avail_out == 0);
      
      assert(zlib_stream.avail_in == 0); // all input used
      
      if (available_input > ZLIB_CHUNK) {
	available_input -= ZLIB_CHUNK;
	src_index       += ZLIB_CHUNK;
      } else {
	available_input = 0;
      }
    }
    
    f2__free(to_ptr(out_buffer));
    
  }
  
  inflateEnd(&zlib_stream);
  *dest_length = dest_index;
  if (zlib_result == Z_STREAM_END) {
    return boolean__false; // success
  } else {
    return boolean__true; // failure
  }
}

boolean_t zlib__inflate_length(u8* src_data, u64 src_length, u64* dest_length) {
  return zlib__inflate(NULL, dest_length, src_data, src_length);
}


f2ptr raw__chunk__inflate(f2ptr cause, f2ptr this) {
  u64 src_length = raw__chunk__length(cause, this);
  u8* src_data   = (u8*)from_ptr(f2__malloc(src_length));
  raw__chunk__str_copy(cause, this, src_data);
  
  u64 dest_length = 0;
  if (zlib__inflate_length(src_data, src_length, &dest_length)) {
    f2__free(to_ptr(src_data));
    return nil;
  }
  
  u8* temp_data = (u8*)from_ptr(f2__malloc(dest_length));
  if (zlib__inflate(temp_data, &dest_length, src_data, src_length)) {
    f2__free(to_ptr(src_data));
    f2__free(to_ptr(temp_data));
    return nil;
  }
  f2__free(to_ptr(src_data));
  
  f2ptr new_chunk = f2chunk__new(cause, dest_length, temp_data);
  f2__free(to_ptr(temp_data));
  return new_chunk;
}

f2ptr f2__chunk__inflate(f2ptr cause, f2ptr this) {
  assert_argument_type(chunk, this);
  return raw__chunk__inflate(cause, this);
}
def_pcfunk1(chunk__inflate, this,
	    "",
	    return f2__chunk__inflate(this_cause, this));


// **

void f2__zlib__defragment__fix_pointers() {
  // -- reinitialize --
  // -- initialize --
  
  f2__primcfunk__init__defragment__fix_pointers(chunk__deflate);
  f2__primcfunk__init__defragment__fix_pointers(chunk__inflate);
}

void f2__zlib__reinitialize_globalvars() {
  f2__primcfunk__init__1(chunk__deflate, this);
  f2__primcfunk__init__1(chunk__inflate, this);
}

void f2__zlib__initialize() {
  funk2_module_registration__add_module(&(__funk2.module_registration), "zlib", "", &f2__zlib__reinitialize_globalvars, &f2__zlib__defragment__fix_pointers);
  
  f2__zlib__reinitialize_globalvars();
}


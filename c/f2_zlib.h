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

#ifndef F2__ZLIB__H
#define F2__ZLIB__H

#include "f2_primfunks.h"

boolean_t zlib__deflate(u8* dest_data, u64* dest_length, u8* src_data, u64 src_length);
boolean_t zlib__deflate_length(u8* src_data, u64 src_length, u64* dest_length);
f2ptr f2__string__deflate(f2ptr cause, f2ptr this);
boolean_t zlib__inflate(u8* dest_data, u64* dest_length, u8* src_data, u64 src_length);
boolean_t zlib__inflate_length(u8* src_data, u64 src_length, u64* dest_length);
f2ptr f2__string__inflate(f2ptr cause, f2ptr this);

// **

void f2__zlib__initialize();

#endif // F2__ZLIB__H


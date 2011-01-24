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

#ifndef F2__SERIALIZE__H
#define F2__SERIALIZE__H

#include "f2_primobjects.h"

void    raw__serialize_ptype_to_chunk_index(f2ptr cause, f2ptr chunk, int index, int* new_index, ptype_t ptype);
ptype_t raw__deserialize_ptype_from_chunk_index(f2ptr cause, f2ptr chunk, int index, int* new_index);
void    raw__serialize_to_chunk_index(f2ptr cause, f2ptr chunk, int index, int *new_index, f2ptr exp);
f2ptr   f2__serialize(f2ptr cause, f2ptr exp);
f2ptr   raw__deserialize_from_chunk_index(f2ptr cause, f2ptr chunk, int index, int* new_index);
f2ptr   f2__deserialize(f2ptr cause, f2ptr chunk, f2ptr index, f2ptr new_index_place);

void f2__serialize__reinitialize_globalvars();
void f2__serialize__initialize();

#endif // F2__SERIALIZE__H

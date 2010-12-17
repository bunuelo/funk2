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

#include "../../c/funk2.h"
#include "semantic_object_type.h"
#include "../semantic_knowledge_base/semantic_knowledge_base.h"
#include "../meta_semantic_knowledge_base/meta_semantic_knowledge_base.h"





// **

f2ptr f2__semantic_object_type__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(semantic_object_type__core_extension_ping, 0, "");

f2ptr f2__semantic_object_type__core_extension_initialize(f2ptr cause) {
  status("semantic_object_type initialized.");
  return nil;
}
export_cefunk0(semantic_object_type__core_extension_initialize, 0, "");

f2ptr f2__semantic_object_type__core_extension_destroy(f2ptr cause) {
  status("semantic_object_type destroyed.");
  return nil;
}
export_cefunk0(semantic_object_type__core_extension_destroy, 0, "");



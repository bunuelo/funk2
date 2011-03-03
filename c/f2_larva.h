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

#ifndef F2__LARVA__H
#define F2__LARVA__H

#define assert_argument_type(correct_type, argument_value) {		\
    f2ptr temporary_argument_value = argument_value;			\
    if (! raw__##correct_type##__is_type(cause, temporary_argument_value)) { \
      return f2__larva__invalid_argument_type__new(cause, new__string(cause, (char*)__FILE__), f2integer__new(cause, __LINE__), new__symbol(cause, (char*)__FUNCTION__), \
						   new__symbol(cause, #correct_type), new__symbol(cause, #argument_value), temporary_argument_value); \
    }									\
  }

f2ptr f2__larva__invalid_argument_type__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr current_funktion_name,
					    f2ptr correct_type, f2ptr argument_name, f2ptr argument_value);

// **

void f2__larva__initialize();

#endif // F2__LARVA__H

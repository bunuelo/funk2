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

#ifndef F2__LARVA__H
#define F2__LARVA__H

#define assert_argument_type(correct_type, argument_value) {		\
    f2ptr temporary_argument_value = argument_value;			\
    if (! raw__##correct_type##__is_type(cause, temporary_argument_value)) { \
      return f2__larva__invalid_argument_type__new(cause, new__string(cause, (char*)__FILE__), f2integer__new(cause, __LINE__), new__symbol(cause, (char*)__FUNCTION__), \
						   new__symbol(cause, #correct_type), f2__object__type(cause, temporary_argument_value), new__symbol(cause, #argument_value), temporary_argument_value); \
    }									\
  }

#define assert_argument_type_or_nil(correct_type, argument_value) {	\
    f2ptr temporary_argument_value = argument_value;			\
    if ((temporary_argument_value != nil) && (! raw__##correct_type##__is_type(cause, temporary_argument_value))) { \
      return f2__larva__invalid_argument_type__new(cause, new__string(cause, (char*)__FILE__), f2integer__new(cause, __LINE__), new__symbol(cause, (char*)__FUNCTION__), \
						   f2list2__new(cause, nil, new__symbol(cause, #correct_type)), f2__object__type(cause, temporary_argument_value), new__symbol(cause, #argument_value), temporary_argument_value); \
    }									\
  }

#define assert_value(value) ({						\
      f2ptr assert_value_temp = value;					\
      if (raw__larva__is_type(cause, assert_value_temp)) {		\
	f2ptr assert_value_temp__bug = f2larva__bug(assert_value_temp, cause); \
	if (assert_value_temp__bug == nil) {				\
	  assert_value_temp__bug = f2__bug__new_from_larva(cause, assert_value_temp); \
	}								\
	return f2__larva__invalid_value__new(cause,			\
					     new__string(cause, (char*)__FILE__), \
					     f2integer__new(cause, __LINE__), \
					     new__symbol(cause, (char*)__FUNCTION__), \
					     new__symbol(cause, #value), \
					     assert_value_temp__bug);	\
      }									\
      assert_value_temp;						\
    })

#define catch_value(value, additional_frame_args) ({			\
      f2ptr assert_value_temp = value;					\
      if (raw__larva__is_type(cause, assert_value_temp)) {		\
	f2ptr assert_value_temp__bug = f2larva__bug(assert_value_temp, cause); \
	if (assert_value_temp__bug == nil) {				\
	  assert_value_temp__bug = f2__bug__new_from_larva(cause, assert_value_temp); \
	}								\
	return f2__larva__caught_invalid_value__new(cause,		\
						    new__string(cause, (char*)__FILE__), \
						    f2integer__new(cause, __LINE__), \
						    new__symbol(cause, (char*)__FUNCTION__), \
						    new__symbol(cause, #value),	\
						    assert_value_temp__bug, \
						    additional_frame_args); \
      }									\
      assert_value_temp;						\
    })



#define new__error(frame_args)						\
  f2__larva__error__new(cause,						\
			new__string(cause, (char*)__FILE__),		\
			f2integer__new(cause, __LINE__),		\
			new__symbol(cause, (char*)__FUNCTION__),	\
			frame_args);

f2ptr f2__larva__invalid_argument_type__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr current_funktion_name,
					    f2ptr correct_type, f2ptr actual_type, f2ptr argument_name, f2ptr argument_value);

f2ptr f2__larva__invalid_value__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr current_funktion_name,
				    f2ptr value_name, f2ptr value);

f2ptr f2__larva__caught_invalid_value__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name,
					   f2ptr value_name, f2ptr value,
					   f2ptr additional_args);

f2ptr f2__larva__error__new(f2ptr cause, f2ptr source_filename, f2ptr source_line_number, f2ptr funktion_name, f2ptr frame_args);

// **

void f2__larva__initialize();

#endif // F2__LARVA__H

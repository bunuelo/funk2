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

#ifndef F2__SET__TYPES__H
#define F2__SET__TYPES__H

typedef struct funk2_set_s      funk2_set_t;
typedef struct funk2_set_node_s funk2_set_node_t;
typedef u64                     funk2_set_element_t;

#define funk2_set_prime_number__16_bit (65521ull)
#define funk2_set_prime_number__32_bit (3267000013ull)

#endif // F2__SET__TYPES__H

#ifndef F2__SET__H
#define F2__SET__H

struct funk2_set_node_s {
  funk2_set_element_t element;
  funk2_set_node_t*   next;
};

struct funk2_set_s {
  u64                element_count;
  u64                bin_power;
  funk2_set_node_t** bin;
};

void      funk2_set__init               (funk2_set_t* this);
void      funk2_set__destroy            (funk2_set_t* this);
void      funk2_set__remove_all         (funk2_set_t* this);
u64       funk2_set__element_count      (funk2_set_t* this);
u64       funk2_set__element_bin_index  (funk2_set_t* this, funk2_set_element_t element);
void      funk2_set__double_size        (funk2_set_t* this);
void      funk2_set__add                (funk2_set_t* this, funk2_set_element_t element);
boolean_t funk2_set__contains           (funk2_set_t* this, funk2_set_element_t element);
void      funk2_set__remove             (funk2_set_t* this, funk2_set_element_t element);
void      funk2_set__remove_and_add_to  (funk2_set_t* this, funk2_set_element_t element, funk2_set_t* to_set);
void*     funk2_set__mapc               (funk2_set_t* this, void(* mapc_funk)(funk2_set_element_t element, void** user_data, boolean_t* stop, void** return_value), void** user_data);
s64       funk2_set__calculate_save_size(funk2_set_t* this);
void      funk2_set__save_to_stream     (funk2_set_t* this, int fd);
u64       funk2_set__save_to_buffer     (funk2_set_t* this, u8* initial_buffer);
void      funk2_set__load_from_stream   (funk2_set_t* this, int fd);
s64       funk2_set__load_from_buffer   (funk2_set_t* this, u8* buffer);
void      funk2_set__print              (funk2_set_t* this);

void funk2_set__test();

#define funk2_set__iteration(this, funk2_set__iteration__element, body) {			\
    funk2_set_t*       funk2_set__iteration__this            = this;	\
    u64                funk2_set__iteration__index;			\
    u64                funk2_set__iteration__this__bin_count = 1ull << funk2_set__iteration__this->bin_power; \
    funk2_set_node_t** funk2_set__iteration__this__bin       = funk2_set__iteration__this->bin; \
    for (funk2_set__iteration__index = 0; funk2_set__iteration__index < funk2_set__iteration__this__bin_count; funk2_set__iteration__index ++) { \
      funk2_set_node_t* funk2_set__iteration__index__iter = funk2_set__iteration__this__bin[funk2_set__iteration__index]; \
      while (funk2_set__iteration__index__iter != NULL) {		\
	funk2_set_element_t funk2_set__iteration__element = funk2_set__iteration__index__iter->element; \
	{								\
	  body;								\
	}								\
	funk2_set__iteration__index__iter = funk2_set__iteration__index__iter->next; \
      }									\
    }									\
  }


#endif // F2__SET__H


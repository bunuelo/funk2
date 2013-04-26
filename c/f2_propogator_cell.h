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

#ifndef F2__PROPOGATOR_CELL__TYPES__H
#define F2__PROPOGATOR_CELL__TYPES__H

typedef u64 (*funk2_propogator_cell_recalculate_funktion_t)(void* user_data);

typedef struct funk2_propogator_cell_cons_s funk2_propogator_cell_cons_t;
typedef struct funk2_propogator_cell_s      funk2_propogator_cell_t;

#endif // F2__PROPOGATOR_CELL__TYPES__H

#ifndef F2__PROPOGATOR_CELL__H
#define F2__PROPOGATOR_CELL__H

#include "f2_atomic_u64.h"

struct funk2_propogator_cell_cons_s {
  funk2_propogator_cell_t* propogator_cell;
  funk2_atomic_u64_t       next; // (funk2_propogator_cell_cons_t*)
};

struct funk2_propogator_cell_s {
  pthread_mutex_t                              atomic_value_mutex;
  pthread_cond_t                               atomic_value_cond;
  funk2_atomic_u64_t                           atomic_value;
  funk2_propogator_cell_recalculate_funktion_t recalculate_funktion;
  void*                                        user_data;
  funk2_atomic_u64_t                           dependents; // (funk2_propogator_cell_cons_t*)
};

void      funk2_propogator_cell__init                  (funk2_propogator_cell_t* this, u64 initial_value, funk2_propogator_cell_recalculate_funktion_t recalculate_funktion, void* user_data);
void      funk2_propogator_cell__init_input            (funk2_propogator_cell_t* this, u64 initial_value);
void      funk2_propogator_cell__init_hidden           (funk2_propogator_cell_t* this, funk2_propogator_cell_recalculate_funktion_t recalculate_funktion, void* user_data);
void      funk2_propogator_cell__destroy               (funk2_propogator_cell_t* this);
u64       funk2_propogator_cell__value                 (funk2_propogator_cell_t* this);
u64       funk2_propogator_cell__value__set            (funk2_propogator_cell_t* this, u64 new_value);                // only used for input cells
u64       funk2_propogator_cell__increment             (funk2_propogator_cell_t* this);                               // only used for input cells
u64       funk2_propogator_cell__decrement             (funk2_propogator_cell_t* this);                               // only used for input cells
boolean_t funk2_propogator_cell__compare_and_swap      (funk2_propogator_cell_t* this, u64 old_value, u64 new_value); // only used for input cells
void      funk2_propogator_cell__add_dependent         (funk2_propogator_cell_t* this, funk2_propogator_cell_t* propogator_cell);
void      funk2_propogator_cell__remove_dependent      (funk2_propogator_cell_t* this, funk2_propogator_cell_t* propogator_cell);
void      funk2_propogator_cell__recalculate_dependents(funk2_propogator_cell_t* this);
void      funk2_propogator_cell__recalculate           (funk2_propogator_cell_t* this); // only used for hidden cells
void      funk2_propogator_cell__lock                  (funk2_propogator_cell_t* this);
void      funk2_propogator_cell__wait                  (funk2_propogator_cell_t* this);
void      funk2_propogator_cell__unlock                (funk2_propogator_cell_t* this);

#endif // F2__PROPOGATOR_CELL__H


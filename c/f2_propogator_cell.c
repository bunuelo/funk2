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

void funk2_propogator_cell__init(funk2_propogator_cell_t* this, u64 initial_value, funk2_propogator_cell_recalculate_funktion_t recalculate_funktion, void* user_data) {
  pthread_mutex_init(&(this->atomic_value_mutex), NULL);
  pthread_cond_init(&(this->atomic_value_cond), NULL);
  funk2_atomic_u64__init(&(this->atomic_value), initial_value);
  this->recalculate_funktion = recalculate_funktion;
  this->user_data            = user_data;
  funk2_atomic_u64__init(&(this->dependents), (u64)to_ptr(NULL));
}

void funk2_propogator_cell__init_input_cell(funk2_propogator_cell_t* this, u64 initial_value) {
  funk2_propogator_cell__init(this, initial_value, NULL, NULL);
}

void funk2_propogator_cell__init_hidden_cell(funk2_propogator_cell_t* this, funk2_propogator_cell_recalculate_funktion_t recalculate_funktion, void* user_data) {
  funk2_propogator_cell__init(this, 0, recalculate_funktion, user_data);
}

void funk2_propogator_cell__destroy(funk2_propogator_cell_t* this) {
  pthread_mutex_destroy(&(this->atomic_value_mutex));
  pthread_cond_destroy(&(this->atomic_value_cond));
  funk2_atomic_u64__destroy(&(this->atomic_value));
}

u64 funk2_propogator_cell__value(funk2_propogator_cell_t* this) {
  return funk2_atomic_u64__value(&(this->atomic_value));
}

u64 funk2_propogator_cell__value__set(funk2_propogator_cell_t* this, u64 new_value) {
  if (this->recalculate_funktion != NULL) {
    error(nil, "funk2_propogator_cell__value__set recalculate_funktion != NULL: (we tried to mistakenly set the value of a hidden cell)");
  }
  pthread_mutex_lock(&(this->atomic_value_mutex));
  u64 old_value = funk2_atomic_u64__set_value(&(this->atomic_value), new_value);
  if (new_value != old_value) {
    pthread_cond_broadcast(&(this->atomic_value_cond));
    pthread_mutex_unlock(&(this->atomic_value_mutex));
    funk2_propogator_cell__recalculate_dependents(this);
  } else {
    pthread_mutex_unlock(&(this->atomic_value_mutex));
  }
  return old_value;
}

void funk2_propogator_cell__add_dependent(funk2_propogator_cell_t* this, funk2_propogator_cell_t* propogator_cell) {
  funk2_propogator_cell_cons_t* cons = (funk2_propogator_cell_cons_t*)from_ptr(f2__malloc(sizeof(funk2_propogator_cell_cons_t)));
  cons->propogator_cell = propogator_cell;
  funk2_atomic_u64__init(&(cons->next), (u64)to_ptr(NULL));
  {
    boolean_t success = boolean__false;
    while (! success) {
      u64 old_value = funk2_atomic_u64__value(&(this->dependents));
      funk2_atomic_u64__set_value(&(cons->next), old_value);
      success = funk2_atomic_u64__compare_and_swap(&(this->dependents), old_value, (u64)to_ptr(cons));
    }
  }
}

void funk2_propogator_cell__remove_dependent(funk2_propogator_cell_t* this, funk2_propogator_cell_t* propogator_cell) {
  boolean_t dependent_exists     = boolean__true;
  boolean_t successfully_removed = boolean__false;
  while (dependent_exists && (! successfully_removed)) {
    dependent_exists = boolean__false;
    funk2_propogator_cell_cons_t* prev = NULL;
    funk2_propogator_cell_cons_t* iter = (funk2_propogator_cell_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->dependents)));
    while ((iter != NULL) && (! successfully_removed)) {
      if (iter->propogator_cell == propogator_cell) {
	dependent_exists = boolean__true;
	if (prev != NULL) {
	  u64       old_value = funk2_atomic_u64__value(&(prev->next));
	  boolean_t success   = funk2_atomic_u64__compare_and_swap(&(prev->next), old_value, funk2_atomic_u64__value(&(iter->next)));
	  if (success) {
	    successfully_removed = boolean__true;
	  }
	} else {
	  u64       old_value = funk2_atomic_u64__value(&(this->dependents));
	  boolean_t success   = funk2_atomic_u64__compare_and_swap(&(this->dependents), old_value, funk2_atomic_u64__value(&(iter->next)));
	  if (success) {
	    successfully_removed = boolean__true;
	  }
	}
	if (successfully_removed) {
	  funk2_atomic_u64__destroy(&(iter->next));
	  f2__free(to_ptr(iter));
	}
      }
      iter = (funk2_propogator_cell_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
    }
    if (iter == NULL) {
      dependent_exists = boolean__false;
    }
  }
  if (! successfully_removed) {
    error(nil, "funk2_propogator_cell__remove_dependent dependent does not exist in cell.");
  }
}

void funk2_propogator_cell__recalculate_dependents(funk2_propogator_cell_t* this) {
  funk2_propogator_cell_cons_t* iter = (funk2_propogator_cell_cons_t*)from_ptr(funk2_atomic_u64__value(&(this->dependents)));
  while (iter != NULL) {
    funk2_propogator_cell_t* propogator_cell = iter->propogator_cell;
    funk2_propogator_cell__recalculate(propogator_cell);
    iter = (funk2_propogator_cell_cons_t*)from_ptr(funk2_atomic_u64__value(&(iter->next)));
  }
}

void funk2_propogator_cell__recalculate(funk2_propogator_cell_t* this) {
  if (this->recalculate_funktion == NULL) {
    error(nil, "funk2_propogator_cell recalculate_funktion is NULL.  (we tried to mistakenly recalculate input cell)");
  }
  u64 new_value = (*(this->recalculate_funktion))(this->user_data);
  pthread_mutex_lock(&(this->atomic_value_mutex));
  u64 old_value = funk2_atomic_u64__set_value(&(this->atomic_value), new_value);
  if (new_value != old_value) {
    pthread_cond_broadcast(&(this->atomic_value_cond));
    pthread_mutex_unlock(&(this->atomic_value_mutex));
    funk2_propogator_cell__recalculate_dependents(this);
  } else {
    pthread_mutex_unlock(&(this->atomic_value_mutex));
  }
}

void funk2_propogator_cell__lock(funk2_propogator_cell_t* this) {
  pthread_mutex_lock(&(this->atomic_value_mutex));
}

void funk2_propogator_cell__wait(funk2_propogator_cell_t* this) {
  pthread_cond_wait(&(this->atomic_value_cond), &(this->atomic_value_mutex));
}

void funk2_propogator_cell__unlock(funk2_propogator_cell_t* this) {
  pthread_mutex_unlock(&(this->atomic_value_mutex));
}


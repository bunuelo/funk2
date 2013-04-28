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

void funk2_processor_thread_event__init(funk2_processor_thread_event_t* this, u64 start_time__nanoseconds_since_1970, char* message) {
  this->start_time__nanoseconds_since_1970 = start_time__nanoseconds_since_1970;
  u64 message__length;
  for (message__length = 0; message[message__length] != 0; message__length ++);
  {
    this->message = (char*)from_ptr(f2__malloc(sizeof(char) * message__length));
    {
      s64 index;
      for (index = 0; index < message__length; index ++) {
	this->message[index] = message[index];
      }
    }
    this->message[message__length] = 0;
  }
}

void funk2_processor_thread_event__destroy(funk2_processor_thread_event_t* this) {
  f2__free(to_ptr(this->message));
}

void funk2_processor_thread_event__print_status(funk2_processor_thread_event_t* this) {
  status("    event=\"%s\"", this->message);
}

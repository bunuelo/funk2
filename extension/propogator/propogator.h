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

#ifndef F2__PROPOGATOR__H
#define F2__PROPOGATOR__H

#include "../../c/funk2.h"

// propogator

def_header_ceframe1(propogator, cell_set);

f2ptr raw__propogator__new        (f2ptr cause);
f2ptr  f2__propogator__new        (f2ptr cause);
void  raw__propogator__add_cell   (f2ptr cause, f2ptr this, f2ptr cell);
f2ptr  f2__propogator__add_cell   (f2ptr cause, f2ptr this, f2ptr cell);
void  raw__propogator__remove_cell(f2ptr cause, f2ptr this, f2ptr cell);
f2ptr  f2__propogator__remove_cell(f2ptr cause, f2ptr this, f2ptr cell);


// propogator_cell

def_header_ceframe2(propogator_cell, propogator, value);

f2ptr raw__propogator_cell__new(f2ptr cause, f2ptr propogator);
f2ptr  f2__propogator_cell__new(f2ptr cause, f2ptr propogator);


// propogator_process

def_header_ceframe1(propogator_process, input_ports, output_ports, execute_funk);

f2ptr raw__propogator_process__new(f2ptr cause, f2ptr execute_funk);
f2ptr  f2__propogator_process__new(f2ptr cause, f2ptr execute_funk);


// propogator_relation

def_header_ceframe1(propogator_relation, cell_port_frame);

f2ptr raw__propogator_relation__new(f2ptr cause);
f2ptr  f2__propogator_relation__new(f2ptr cause);



// **

f2ptr f2__propogator__core_extension__ping      (f2ptr cause);
f2ptr f2__propogator__core_extension__initialize(f2ptr cause);
f2ptr f2__propogator__core_extension__destroy   (f2ptr cause);


#endif // F2__PROPOGATOR__H


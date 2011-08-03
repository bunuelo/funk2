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

#include "blocks_world.h"

/*
  `[prog [have cairo_context set_source_rgba 1.0 1.0 1.0 1.0]
	 [have cairo_context paint]
	 
	 [have cairo_context save]
	 [have cairo_context translate 16.0 16.0]
	 [have cairo_context scale
	       [/ [- [get image_width as-double] [* 2 16.0]] width]
	       [/ [- [get image_width as-double] [* 2 16.0]] width]]
	 
	 [mapc [funk [gripper]
		     [have gripper render_to_cairo cairo_context]]
	       grippers]
	 
	 [mapc [funk [block]
		     [have block render_to_cairo cairo_context]]
	       blocks]
	 
	 [have cairo_context restore]
	 ]
*/

// blocks_world_gripper

boolean_t raw__blocks_world_gripper__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_gripper"));
}

f2ptr f2__blocks_world_gripper__render_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  return nil;
}


// blocks_world_block

boolean_t raw__blocks_world_block__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_block"));
}

f2ptr f2__blocks_world_block__render_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  return nil;
}

// blocks_world_physics

boolean_t raw__blocks_world_physics__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_physics"));
}

f2ptr f2__blocks_world_physics__render_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context, f2ptr image_width, f2ptr image_height) {
  assert_argument_type(blocks_world_physics, this);
  assert_argument_type(cairo_context,        cairo_context);
  assert_argument_type(double,               image_width);
  assert_argument_type(double,               image_height);
  
  f2ptr this__width = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width")));
  assert_argument_type(double, this__width);
  f2ptr this__grippers = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "grippers")));
  f2ptr this__blocks   = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks")));
  
  double this__width__d  = f2double__d(this__width, cause);
  double image_width__d  = f2double__d(image_width, cause);
  double image_height__d = f2double__d(image_height, cause);
  
  raw__cairo_context__paint(cause, cairo_context);
  raw__cairo_context__save(cause, cairo_context);
  raw__cairo_context__translate(cause, cairo_context, 16.0, 16.0);
  raw__cairo_context__scale(cause, cairo_context,
			    ((image_width__d  - (2 * 16.0)) / this__width__d)
			    ((image_height__d - (2 * 16.0)) / this__width__d));
  
  {
    f2ptr iter = this__grippers;
    while (iter != nil) {
      f2ptr gripper = assert_value(f2__cons__car(cause, iter));
      assert_value(f2__blocks_world_gripper__render_to_cairo(cause, gripper, cairo_context));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  {
    f2ptr iter = this__blocks;
    while (iter != nil) {
      f2ptr gripper = assert_value(f2__cons__car(cause, iter));
      assert_value(f2__blocks_world_block__render_to_cairo(cause, gripper, cairo_context));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  return nil;
}
export_cefunk1(blocks_world_physics__render_to_cairo, this, 0, "Renders blocks_world_physics object to cairo_context.");



// **

f2ptr f2__blocks_world__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(blocks_world__core_extension__ping, 0, "");

f2ptr f2__blocks_world__core_extension__initialize(f2ptr cause) {
  status("blocks_world initialized.");
  return nil;
}
export_cefunk0(blocks_world__core_extension__initialize, 0, "");

f2ptr f2__blocks_world__core_extension__define_types(f2ptr cause) {
  status("blocks_world types defined.");
  return nil;
}
export_cefunk0(blocks_world__core_extension__define_types, 0, "");

f2ptr f2__blocks_world__core_extension__destroy(f2ptr cause) {
  status("blocks_world destroyed.");
  return nil;
}
export_cefunk0(blocks_world__core_extension__destroy, 0, "");



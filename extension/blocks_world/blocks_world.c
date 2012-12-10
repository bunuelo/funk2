// 
// Copyright (c) 2007-2012 Bo Morgan.
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

// blocks_world_sprite

boolean_t raw__blocks_world_sprite__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_sprite"));
}

f2ptr f2__blocks_world_sprite__render_shape_path_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  assert_argument_type(blocks_world_sprite, this);
  assert_argument_type(cairo_context,       cairo_context);
  
  f2ptr this__shape  = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "shape"),  nil));
  f2ptr this__x      = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"),      nil));
  f2ptr this__y      = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y"),      nil));
  f2ptr this__width  = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"),  nil));
  f2ptr this__height = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil));
  
  assert_argument_type(double, this__x);
  assert_argument_type(double, this__y);
  assert_argument_type(double, this__width);
  assert_argument_type(double, this__height);
  
  double this__x__d      = f2double__d(this__x,      cause);
  double this__y__d      = f2double__d(this__y,      cause);
  double this__width__d  = f2double__d(this__width,  cause);
  double this__height__d = f2double__d(this__height, cause);
  
  if (raw__eq(cause, new__symbol(cause, "pyramid"), this__shape)) {
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d + (this__width__d / 2.0), this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d / 2.0, this__height__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, -this__width__d, 0.0);
    raw__cairo_context__close_path( cause, cairo_context);
  } else if (raw__eq(cause, new__symbol(cause, "gripper"), this__shape)) {
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d + (this__width__d / 2.0), 0.0);
    raw__cairo_context__rel_line_to(cause, cairo_context, 0.0,                                 this__y__d);
    raw__cairo_context__close_path( cause, cairo_context);
    
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d + (this__width__d / 2.0), this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, -(this__width__d / 2.0),             ((this__height__d * 2.0) / 3.0));
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d / 3.0,                this__height__d / 3.0);
    raw__cairo_context__rel_line_to(cause, cairo_context, -(this__width__d / 3.0),             -(this__height__d / 3.0));
    raw__cairo_context__close_path( cause, cairo_context);
    
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d + (this__width__d / 2.0), this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d / 2.0,                ((this__height__d * 2.0) / 3.0));
    raw__cairo_context__rel_line_to(cause, cairo_context, -(this__width__d / 3.0),             this__height__d / 3.0);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d / 3.0,                -(this__height__d / 3.0));
    raw__cairo_context__close_path( cause, cairo_context);
    
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d + (this__width__d / 2.0), this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d / 3.0,                (this__height__d * 4.0) / 9.0);
    raw__cairo_context__rel_line_to(cause, cairo_context, -((this__width__d * 4.0) / 6.0),     0.0);
    raw__cairo_context__close_path( cause, cairo_context);
  } else { // by default draw a rectangle
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d,      this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d,  0.0);
    raw__cairo_context__rel_line_to(cause, cairo_context, 0.0,             this__height__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, -this__width__d, 0.0);
    raw__cairo_context__close_path( cause, cairo_context);
  }
  return nil;
}

double raw__blocks_world_sprite__render_shape_text_height(f2ptr cause, f2ptr this) {
  f2ptr this__shape = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "shape"), nil));
  if (raw__eq(cause, new__symbol(cause, "pyramid"), this__shape)) {
    return 0.05;
  } else if (raw__eq(cause, new__symbol(cause, "gripper"), this__shape)) {
    f2ptr this__height = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil));
    assert_argument_type(double, this__height);
    double this__height__d  = f2double__d(this__height, cause);
    return ((this__height__d / 3.0) - 0.05);
  } else {
    return 0.05;
  }
}

f2ptr f2__blocks_world_sprite__render_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  assert_argument_type(blocks_world_sprite, this);
  assert_argument_type(cairo_context,       cairo_context);
  
  f2ptr this__color  = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "color"),  nil));
  f2ptr this__name   = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "name"),   nil));
  f2ptr this__x      = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"),      nil));
  f2ptr this__y      = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y"),      nil));
  f2ptr this__width  = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"),  nil));
  f2ptr this__height = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil));
  
  assert_argument_type(double, this__x);
  assert_argument_type(double, this__y);
  assert_argument_type(double, this__width);
  assert_argument_type(double, this__height);
  
  double this__x__d      = f2double__d(this__x,      cause);
  double this__y__d      = f2double__d(this__y,      cause);
  double this__width__d  = f2double__d(this__width,  cause);
  double this__height__d = f2double__d(this__height, cause);
  
  f2ptr this__name__as__string = assert_value(f2__exp__as__string(cause, this__name));
  
  double render_shape_text_height = raw__blocks_world_sprite__render_shape_text_height(cause, this);
  
  raw__cairo_context__save(cause, cairo_context);
  if      (raw__eq(cause, new__symbol(cause, "red"),   this__color)) {raw__cairo_context__set_source_rgba(cause, cairo_context, 1.0,  0.75, 0.75, 1.0);}
  else if (raw__eq(cause, new__symbol(cause, "brown"), this__color)) {raw__cairo_context__set_source_rgba(cause, cairo_context, 1.0,  0.75, 0.5,  1.0);}
  else if (raw__eq(cause, new__symbol(cause, "green"), this__color)) {raw__cairo_context__set_source_rgba(cause, cairo_context, 0.5,  1.0,  0.75, 1.0);}
  else if (raw__eq(cause, new__symbol(cause, "blue"),  this__color)) {raw__cairo_context__set_source_rgba(cause, cairo_context, 0.5,  0.75, 1.0,  1.0);}
  else if (raw__eq(cause, new__symbol(cause, "black"), this__color)) {raw__cairo_context__set_source_rgba(cause, cairo_context, 0.75, 0.75, 0.75, 1.0);}
  else if (raw__eq(cause, new__symbol(cause, "white"), this__color)) {raw__cairo_context__set_source_rgba(cause, cairo_context, 0.9,  0.9,  0.9,  1.0);}
  raw__cairo_context__set_line_width(cause, cairo_context, 0.0);
  assert_value(f2__blocks_world_sprite__render_shape_path_to_cairo(cause, this, cairo_context));
  raw__cairo_context__fill(cause, cairo_context);
  raw__cairo_context__restore(cause, cairo_context);
  
  raw__cairo_context__save(cause, cairo_context);
  raw__cairo_context__set_source_rgba(cause, cairo_context, 0.0, 0.0, 0.0, 1.0);
  raw__cairo_context__set_line_cap(cause, cairo_context, new__symbol(cause, "square"));
  raw__cairo_context__set_line_width(cause, cairo_context, 0.02);
  assert_value(f2__blocks_world_sprite__render_shape_path_to_cairo(cause, this, cairo_context));
  raw__cairo_context__stroke(cause, cairo_context);
  raw__cairo_context__restore(cause, cairo_context);
  
  raw__cairo_context__save(cause, cairo_context);
  raw__cairo_context__set_source_rgba(cause, cairo_context, 0.0, 0.0, 0.0, 1.0);
  raw__cairo_context__select_font_face(cause, cairo_context, "Times New Roman", new__symbol(cause, "normal"), new__symbol(cause, "normal"));
  raw__cairo_context__set_font_size(cause, cairo_context, 0.2);
  f2ptr text_extents = assert_value(f2__cairo_context__text_extents(cause, cairo_context, this__name__as__string));
  
  f2ptr text_extents__width = assert_value(f2__frame__lookup_var_value(cause, text_extents, new__symbol(cause, "width"), nil));
  assert_argument_type(double, text_extents__width);
  double text_extents__width__d = f2double__d(text_extents__width, cause);
  
  raw__cairo_context__move_to(cause, cairo_context, 
			      this__x__d + ((this__width__d - text_extents__width__d) / 2.0),
			      (this__y__d + this__height__d) - render_shape_text_height);
  
  assert_value(f2__cairo_context__text_path(cause, cairo_context, this__name__as__string));
  raw__cairo_context__fill(     cause, cairo_context);
  raw__cairo_context__restore(  cause, cairo_context);
  return nil;
}


// blocks_world_gripper

boolean_t raw__blocks_world_gripper__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_gripper"));
}

f2ptr f2__blocks_world_gripper__render_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  assert_argument_type(blocks_world_gripper, this);
  assert_argument_type(cairo_context,        cairo_context);
  return f2__blocks_world_sprite__render_to_cairo(cause, this, cairo_context);
}

f2ptr raw__blocks_world_gripper__step(f2ptr cause, f2ptr this, double step_size) {
  assert_argument_type(blocks_world_gripper, this);
  
  f2ptr this__x = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"), nil));
  assert_argument_type(double, this__x);
  double this__x__d = f2double__d(this__x, cause);
  
  f2ptr this__y = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y"), nil));
  assert_argument_type(double, this__y);
  double this__y__d = f2double__d(this__y, cause);
  
  f2ptr this__height = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil));
  assert_argument_type(double, this__height);
  double this__height__d = f2double__d(this__height, cause);
  
  f2ptr this__x_velocity = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x_velocity"), nil));
  assert_argument_type(double, this__x_velocity);
  double this__x_velocity__d = f2double__d(this__x_velocity, cause);
  
  f2ptr this__y_velocity = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y_velocity"), nil));
  assert_argument_type(double, this__y_velocity);
  double this__y_velocity__d = f2double__d(this__y_velocity, cause);
  
  f2ptr this__movement_command = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "movement_command"), nil));
  
  double next_x = this__x__d + (step_size * this__x_velocity__d);
  double next_y = this__y__d + (step_size * this__y_velocity__d);
  
  f2ptr this__blocks_world_physics = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks_world_physics"), nil));
  assert_argument_type(blocks_world_physics, this__blocks_world_physics);
  
  f2ptr this__blocks_world_physics__width = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "width"), nil));
  assert_argument_type(double, this__blocks_world_physics__width);
  double this__blocks_world_physics__width__d = f2double__d(this__blocks_world_physics__width, cause);
  
  f2ptr this__blocks_world_physics__blocks = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "blocks"),   nil));
  
  if (next_x < 0.0) {
    next_x = 0.0;
  }
  if (next_x > (this__blocks_world_physics__width__d - 1.0)) {
    next_x = this__blocks_world_physics__width__d - 1.0;
  }
  
  double obstacle_below_y = 0.0;
  f2ptr  obstacle_block   = nil;
  
  {
    f2ptr iter = this__blocks_world_physics__blocks;
    while (iter != nil) {
      f2ptr block = assert_value(f2__cons__car(cause, iter));
      {
	if (! raw__eq(cause, this, block)) {
	  if (raw__blocks_world_block__overlaps_horizontally(cause, this, block)) {
	    f2ptr block__y = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "y"), nil));
	    assert_argument_type(double, block__y);
	    double block__y__d = f2double__d(block__y, cause);
	    if (this__y__d < block__y__d) {
	      if ((obstacle_block == nil) ||
		  (block__y__d < obstacle_below_y)) {
		obstacle_block   = block;
		obstacle_below_y = block__y__d;
	      }
	    }
	  }
	}
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "on_block"), nil));
  
  if (obstacle_block != nil) {
    
    double maximum_block_y = obstacle_below_y - this__height__d;
    double next_block_y    = this__y__d + (step_size * this__y_velocity__d);
    if (maximum_block_y < next_block_y) {
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "on_block"), obstacle_block));
      next_y = maximum_block_y;
      {
	this__y_velocity__d = 0.0;
	this__y_velocity    = f2double__new(cause, this__y_velocity__d);
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), this__y_velocity));
      }
      if (raw__eq(cause, new__symbol(cause, "grab"), this__movement_command)) {
	f2ptr obstacle_block__x = assert_value(f2__frame__lookup_var_value(cause, obstacle_block, new__symbol(cause, "x"), nil));
	assert_argument_type(double, obstacle_block__x);
	double obstacle_block__x__d = f2double__d(obstacle_block__x, cause);
	
	{
	  this__movement_command = new__symbol(cause, "recoil");
	  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "movement_command"), this__movement_command));
	}
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "is_holding"),            obstacle_block));
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "is_holding_relative_x"), f2double__new(cause, obstacle_block__x__d - this__x__d)));
	
      }
    }
    
  }
  
  if (next_y < 0.5) {
    next_y = 0.5;
    if (raw__eq(cause, new__symbol(cause, "recoil"), this__movement_command)) {
      {
	this__movement_command = new__symbol(cause, "stop");
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "movement_command"), this__movement_command));
      }
    }
  }
  
  if (raw__eq(cause, new__symbol(cause, "drop"), this__movement_command)) {
    {
      this__movement_command = new__symbol(cause, "stop");
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "movement_command"), this__movement_command));
    }
    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "is_holding"),            nil));
    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "is_holding_relative_x"), nil));
  }
  
  {
    this__x__d = next_x;
    this__x    = f2double__new(cause, this__x__d);
    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x"), this__x));
  }
  {
    this__y__d = next_y;
    this__y    = f2double__new(cause, this__y__d);
    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y"), this__y));
  }
  
  return nil;
}


f2ptr raw__blocks_world_gripper__handle_movement(f2ptr cause, f2ptr this, double step_size) {
  assert_argument_type(blocks_world_gripper, this);
  
  f2ptr this__x_velocity = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x_velocity"), nil));
  assert_argument_type(double, this__x_velocity);
  double this__x_velocity__d = f2double__d(this__x_velocity, cause);
  
  f2ptr this__y_velocity = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y_velocity"), nil));
  assert_argument_type(double, this__y_velocity);
  double this__y_velocity__d = f2double__d(this__y_velocity, cause);
  
  f2ptr this__gripper_movement_speed = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "gripper_movement_speed"), nil));
  assert_argument_type(double, this__gripper_movement_speed);
  double this__gripper_movement_speed__d = f2double__d(this__gripper_movement_speed, cause);
  
  f2ptr this__gripper_grab_speed = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "gripper_grab_speed"), nil));
  assert_argument_type(double, this__gripper_grab_speed);
  double this__gripper_grab_speed__d = f2double__d(this__gripper_grab_speed, cause);
  
  f2ptr this__movement_command = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "movement_command"), nil));
  
  if (raw__eq(cause, new__symbol(cause, "stop"), this__movement_command)) {
    {
      this__x_velocity__d = 0.0;
      this__x_velocity    = f2double__new(cause, this__x_velocity__d);
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x_velocity"), this__x_velocity));
    }
    {
      this__y_velocity__d = 0.0;
      this__y_velocity    = f2double__new(cause, this__y_velocity__d);
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), this__y_velocity));
    }
  } else if (raw__eq(cause, new__symbol(cause, "left"),   this__movement_command)) {
    {
      this__x_velocity__d = -this__gripper_movement_speed__d;
      this__x_velocity    = f2double__new(cause, this__x_velocity__d);
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x_velocity"), this__x_velocity));
    }
  } else if (raw__eq(cause, new__symbol(cause, "right"),  this__movement_command)) {
    {
      this__x_velocity__d = this__gripper_movement_speed__d;
      this__x_velocity    = f2double__new(cause, this__x_velocity__d);
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x_velocity"), this__x_velocity));
    }
  } else if (raw__eq(cause, new__symbol(cause, "grab"),   this__movement_command)) {
    {
      this__y_velocity__d = this__gripper_grab_speed__d;
      this__y_velocity    = f2double__new(cause, this__y_velocity__d);
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), this__y_velocity));
    }
  } else if (raw__eq(cause, new__symbol(cause, "recoil"), this__movement_command)) {
    {
      this__y_velocity__d = -this__gripper_grab_speed__d;
      this__y_velocity    = f2double__new(cause, this__y_velocity__d);
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), this__y_velocity));
    }
  } else if (raw__eq(cause, new__symbol(cause, "drop"),   this__movement_command)) {
  }
  
  return nil;
}

f2ptr raw__blocks_world_gripper__add_perception(f2ptr cause, f2ptr this, f2ptr perception) {
  f2ptr perception_list = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "perception_list"), nil));
  perception_list = raw__cons__new(cause, perception, perception_list);
  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "perception_list"), perception_list));
  return nil;
}

f2ptr f2__blocks_world_gripper__calculate_perceptions(f2ptr cause, f2ptr this) {
  assert_argument_type(blocks_world_gripper, this);
  
  f2ptr this__blocks_world_physics = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks_world_physics"), nil));
  assert_argument_type(blocks_world_physics, this__blocks_world_physics);
  
  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "perception_list"), nil));
  
  f2ptr this__name = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "name"), nil));
  
  f2ptr this__x = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"), nil));
  assert_argument_type(double, this__x);
  double this__x__d = f2double__d(this__x, cause);
  
  f2ptr this__blocks_world_physics__grippers = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "grippers"), nil));
  f2ptr this__blocks_world_physics__blocks   = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "blocks"),   nil));
  
  f2ptr gripper__is_holding__name = nil;
  {
    f2ptr iter = this__blocks_world_physics__grippers;
    while (iter != nil) {
      f2ptr gripper = assert_value(f2__cons__car(cause, iter));
      {
	f2ptr gripper__name = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "name"), nil));
	if (raw__eq(cause, this, gripper)) {
	  f2ptr gripper__movement_command = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "movement_command"), nil));
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "is"),               new__symbol(cause, "me")));
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "movement_command"), gripper__movement_command));
	}
	f2ptr gripper__color            = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "color"),      nil));
	f2ptr gripper__is_holding       = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "is_holding"), nil));
	if (gripper__is_holding != nil) {
	  gripper__is_holding__name = assert_value(f2__frame__lookup_var_value(cause, gripper__is_holding, new__symbol(cause, "name"), nil));
	}
	raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "is-a"),       new__symbol(cause, "gripper")));
	raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "color"),      gripper__color));
	raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "is-holding"), gripper__is_holding__name));
	
	f2ptr gripper__x = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "x"), nil));
	assert_argument_type(double, gripper__x);
	double gripper__x__d = f2double__d(gripper__x, cause);
	
	if (gripper__x__d > this__x__d) {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "right-of"), this__name));
	}
	if (gripper__x__d < this__x__d) {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, gripper__name, new__symbol(cause, "left-of"), this__name));
	}
	
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }

  {
    f2ptr iter = this__blocks_world_physics__blocks;
    while (iter != nil) {
      f2ptr block = assert_value(f2__cons__car(cause, iter));
      {
	f2ptr block__name     = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "name"),     nil));
	f2ptr block__color    = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "color"),    nil));
	f2ptr block__shape    = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "shape"),    nil));
	f2ptr block__on_block = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "on_block"), nil));
	
	f2ptr block__on_block__name = nil;
	if (block__on_block != nil) {
	  block__on_block__name = assert_value(f2__frame__lookup_var_value(cause, block__on_block, new__symbol(cause, "name"), nil));
	}
	
	f2ptr block__x = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "x"), nil));
	assert_argument_type(double, block__x);
	double block__x__d = f2double__d(block__x, cause);
	
	f2ptr block__width = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "width"), nil));
	assert_argument_type(double, block__width);
	double block__width__d = f2double__d(block__width, cause);
	
	if (raw__eq(cause, new__symbol(cause, "blocks_world_table"), f2__object__type(cause, block))) {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "is-a"),  new__symbol(cause, "table")));
	} else {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "is-a"),  new__symbol(cause, "block")));
	}
	raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "color"), block__color));
	raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "shape"), block__shape));
	if (block__on_block) {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "on"), block__on_block__name));
	}
	
	if (block__x__d > this__x__d) {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "right-of"), this__name));
	}
	if (block__x__d < this__x__d) {
	  raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "left-of"), this__name));
	}
	if (! raw__eq(cause, block__name, gripper__is_holding__name)) {
	  if ((this__x__d >  (block__x__d - (block__width__d * 1.00))) &&
	      (this__x__d <= (block__x__d - (block__width__d * 0.25)))) {
	    raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "below-right"), this__name));
	  } else if ((this__x__d > (block__x__d - (block__width__d * 0.25))) &&
		     (this__x__d < (block__x__d + (block__width__d * 0.25)))) {
	    raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "below"),       this__name));
	  } else if ((this__x__d >= (block__x__d + (block__width__d * 0.25))) &&
		     (this__x__d <  (block__x__d + (block__width__d * 1.00)))) {
	    raw__blocks_world_gripper__add_perception(cause, this, f2list3__new(cause, block__name, new__symbol(cause, "below-left"),  this__name));
	  }
	}
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  return nil;
}
export_cefunk1(blocks_world_gripper__calculate_perceptions, this, 0, "Calculates perceptions for this blocks_world_gripper.");


// blocks_world_block

boolean_t raw__blocks_world_block__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_block"));
}

f2ptr f2__blocks_world_block__render_to_cairo(f2ptr cause, f2ptr this, f2ptr cairo_context) {
  assert_argument_type(blocks_world_block, this);
  assert_argument_type(cairo_context,      cairo_context);
  return f2__blocks_world_sprite__render_to_cairo(cause, this, cairo_context);
}

boolean_t raw__blocks_world_block__overlaps_horizontally(f2ptr cause, f2ptr this, f2ptr block) {
  f2ptr this__x      = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"),      nil));
  f2ptr this__width  = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"),  nil));
  f2ptr block__x     = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "x"),      nil));
  f2ptr block__width = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "width"),  nil));
  
  assert_argument_type(double, this__x);
  assert_argument_type(double, this__width);
  assert_argument_type(double, block__x);
  assert_argument_type(double, block__width);
  
  double this__x__d      = f2double__d(this__x,      cause);
  double this__width__d  = f2double__d(this__width,  cause);
  double block__x__d     = f2double__d(block__x,      cause);
  double block__width__d = f2double__d(block__width,  cause);
  
  return (! (((this__x__d + this__width__d) <= block__x__d)                       ||
	     (this__x__d                    >= (block__x__d + block__width__d))));
}

f2ptr raw__blocks_world_block__step(f2ptr cause, f2ptr this, double step_size) {
  assert_argument_type(blocks_world_block, this);
  
  double obstacle_below_y = 0.0;
  f2ptr  obstacle_block   = nil;
  
  f2ptr this__blocks_world_physics = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks_world_physics"), nil));
  assert_argument_type(blocks_world_physics, this__blocks_world_physics);
  
  f2ptr this__x = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"), nil));
  assert_argument_type(double, this__x);
  double this__x__d = f2double__d(this__x, cause);
  
  f2ptr this__y = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y"), nil));
  assert_argument_type(double, this__y);
  double this__y__d = f2double__d(this__y, cause);
  
  f2ptr this__y_velocity = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y_velocity"), nil));
  assert_argument_type(double, this__y_velocity);
  double this__y_velocity__d = f2double__d(this__y_velocity, cause);
  
  f2ptr this__height = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil));
  assert_argument_type(double, this__height);
  double this__height__d = f2double__d(this__height, cause);
  
  
  f2ptr this__blocks_world_physics__grippers = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "grippers"), nil));
  f2ptr this__blocks_world_physics__blocks   = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "blocks"),   nil));
  
  {
    f2ptr iter = this__blocks_world_physics__blocks;
    while (iter != nil) {
      f2ptr block = assert_value(f2__cons__car(cause, iter));
      {
	if (! raw__eq(cause, this, block)) {
	  if (raw__blocks_world_block__overlaps_horizontally(cause, this, block)) {
	    f2ptr block__y = assert_value(f2__frame__lookup_var_value(cause, block, new__symbol(cause, "y"), nil));
	    assert_argument_type(double, block__y);
	    double block__y__d = f2double__d(block__y, cause);
	    if (this__y__d < block__y__d) {
	      if ((obstacle_block == nil) ||
		  (block__y__d < obstacle_below_y)) {
		obstacle_block   = block;
		obstacle_below_y = block__y__d;
	      }
	    }
	  }
	}
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "on_block"), nil));
  
  if (obstacle_block != nil) {
    
    f2ptr obstacle_block__shape = assert_value(f2__frame__lookup_var_value(cause, obstacle_block, new__symbol(cause, "shape"), nil));
    assert_argument_type(symbol, obstacle_block__shape);
    
    f2ptr obstacle_block__x = assert_value(f2__frame__lookup_var_value(cause, obstacle_block, new__symbol(cause, "x"), nil));
    assert_argument_type(double, obstacle_block__x);
    double obstacle_block__x__d = f2double__d(obstacle_block__x, cause);
    
    double maximum_block_y = obstacle_below_y - this__height__d;
    double next_block_y    = this__y__d + (step_size * this__y_velocity__d);
    if (maximum_block_y < next_block_y) {
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "on_block"), obstacle_block));
      {
	this__y__d = maximum_block_y;
	this__y    = f2double__new(cause, this__y__d);
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y"), this__y));
      }
      {
	this__y_velocity__d = 0.0;
	this__y_velocity    = f2double__new(cause, this__y_velocity__d);
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), this__y_velocity));
      }
      if (raw__eq(cause, obstacle_block__shape, new__symbol(cause, "pyramid"))) {
	double slide_horizontal_speed = (this__x__d < obstacle_block__x__d) ? -1.0 : 1.0;
	{
	  this__x__d = this__x__d + (step_size * slide_horizontal_speed);
	  this__x    = f2double__new(cause, this__x__d);
	  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x"), this__x));
	}
      }
    } else {
      {
	this__y__d = next_block_y;
	this__y    = f2double__new(cause, this__y__d);
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y"), this__y));
      }
    }
    
  }
  
  {
    f2ptr iter = this__blocks_world_physics__grippers;
    while (iter != nil) {
      f2ptr gripper = assert_value(f2__cons__car(cause, iter));
      {
	f2ptr gripper__is_holding = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "is_holding"), nil));
	if (raw__eq(cause, this, gripper__is_holding)) {
	  f2ptr gripper__x = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "x"), nil));
	  assert_argument_type(double, gripper__x);
	  double gripper__x__d = f2double__d(gripper__x, cause);

	  f2ptr gripper__y = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "y"), nil));
	  assert_argument_type(double, gripper__y);
	  double gripper__y__d = f2double__d(gripper__y, cause);
	  
	  f2ptr gripper__is_holding_relative_x = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "is_holding_relative_x"), nil));
	  assert_argument_type(double, gripper__is_holding_relative_x);
	  double gripper__is_holding_relative_x__d = f2double__d(gripper__is_holding_relative_x, cause);
	  
	  f2ptr gripper__height = assert_value(f2__frame__lookup_var_value(cause, gripper, new__symbol(cause, "height"), nil));
	  assert_argument_type(double, gripper__height);
	  double gripper__height__d = f2double__d(gripper__height, cause);
	  
	  {
	    this__x__d = gripper__x__d + gripper__is_holding_relative_x__d;
	    this__x    = f2double__new(cause, this__x__d);
	    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x"), this__x));
	  }
	  
	  {
	    this__y__d = gripper__y__d + gripper__height__d;
	    this__y    = f2double__new(cause, this__y__d);
	    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y"), this__y));
	  }
	  
	  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "x_velocity"), f2double__new(cause, 0.0)));
	  assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), f2double__new(cause, 0.0)));
	}
      }
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  return nil;
}


f2ptr raw__blocks_world_block__handle_movement(f2ptr cause, f2ptr this, double step_size) {
  assert_argument_type(blocks_world_block, this);
  
  f2ptr this__y_velocity = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y_velocity"), nil));
  assert_argument_type(double, this__y_velocity);
  double this__y_velocity__d = f2double__d(this__y_velocity, cause);
  
  {
    this__y_velocity__d = this__y_velocity__d + (step_size * 9.8);
    this__y_velocity    = f2double__new(cause, this__y_velocity__d);
    assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "y_velocity"), this__y_velocity));
  }
  
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
  
  f2ptr this__width = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil));
  assert_argument_type(double, this__width);
  f2ptr this__grippers = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "grippers"), nil));
  f2ptr this__blocks   = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks"),   nil));
  
  double this__width__d  = f2double__d(this__width, cause);
  double image_width__d  = f2double__d(image_width, cause);
  //double image_height__d = f2double__d(image_height, cause);
  
  raw__cairo_context__set_source_rgba(cause, cairo_context, 1.0, 1.0, 1.0, 1.0);
  raw__cairo_context__paint(cause, cairo_context);
  raw__cairo_context__save(cause, cairo_context);
  raw__cairo_context__translate(cause, cairo_context, 16.0, 16.0);
  raw__cairo_context__scale(cause, cairo_context,
			    ((image_width__d - (2 * 16.0)) / this__width__d),
			    ((image_width__d - (2 * 16.0)) / this__width__d));
  
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
      f2ptr block = assert_value(f2__cons__car(cause, iter));
      assert_value(f2__blocks_world_block__render_to_cairo(cause, block, cairo_context));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  return nil;
}
export_cefunk4(blocks_world_physics__render_to_cairo, this, cairo_context, image_width, image_height, 0, "Renders blocks_world_physics object to cairo_context.");



f2ptr f2__blocks_world_physics__step(f2ptr cause, f2ptr this, f2ptr step_size) {
  assert_argument_type(blocks_world_physics, this);
  assert_argument_type(double,               step_size);
  double step_size__d = f2double__d(step_size, cause);
  
  f2ptr this__grippers = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "grippers"), nil));
  f2ptr this__blocks   = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks"),   nil));
  
  {
    f2ptr iter = this__grippers;
    while (iter != nil) {
      f2ptr gripper = assert_value(f2__cons__car(cause, iter));
      assert_value(raw__blocks_world_gripper__step(cause, gripper, step_size__d));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  {
    f2ptr iter = this__blocks;
    while (iter != nil) {
      f2ptr block = assert_value(f2__cons__car(cause, iter));
      assert_value(raw__blocks_world_block__step(cause, block, step_size__d));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  return nil;
}
export_cefunk2(blocks_world_physics__step, this, step_size, 0, "Steps blocks_world_physics object.");


f2ptr f2__blocks_world_physics__handle_movement(f2ptr cause, f2ptr this, f2ptr step_size) {
  assert_argument_type(blocks_world_physics, this);
  assert_argument_type(double,               step_size);
  double step_size__d = f2double__d(step_size, cause);
  
  f2ptr this__grippers = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "grippers"), nil));
  f2ptr this__blocks   = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks"),   nil));
  
  {
    f2ptr iter = this__grippers;
    while (iter != nil) {
      f2ptr gripper = assert_value(f2__cons__car(cause, iter));
      assert_value(raw__blocks_world_gripper__handle_movement(cause, gripper, step_size__d));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  {
    f2ptr iter = this__blocks;
    while (iter != nil) {
      f2ptr block = assert_value(f2__cons__car(cause, iter));
      assert_value(raw__blocks_world_block__handle_movement(cause, block, step_size__d));
      iter = assert_value(f2__cons__cdr(cause, iter));
    }
  }
  
  return nil;
}
export_cefunk2(blocks_world_physics__handle_movement, this, step_size, 0, "Handles movement for blocks_world_physics object.");



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



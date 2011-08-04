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

// blocks_world_sprite

boolean_t raw__blocks_world_sprite__is_type(f2ptr cause, f2ptr object) {
  return raw__object__inherits_from(cause, object, new__symbol(cause, "blocks_world_sprite"));
}

/*
  [cond [[eq `cube shape]
	 
	 [have cairo_context move_to     x         y]
	 [have cairo_context rel_line_to width     0.0]
	 [have cairo_context rel_line_to 0.0       height]
	 [have cairo_context rel_line_to [- width] 0.0]
	 [have cairo_context close_path]]
	
	[[eq `pyramid shape]
	 
	 [have cairo_context move_to     [+ x [/ width 2]] y]
	 [have cairo_context rel_line_to [/ width 2]       height]
	 [have cairo_context rel_line_to [- width] 0.0]
	 [have cairo_context close_path]]
	
	[[eq `gripper shape]
	 
	 [have cairo_context move_to     [+ x [/ width 2]] 0.0]
	 [have cairo_context rel_line_to 0.0               y]
	 [have cairo_context close_path]
	 
	 [have cairo_context move_to     [+ x [/ width 2]] y]
	 [have cairo_context rel_line_to [- [/ width 2]]   [/ [* height 2] 3]]
	 [have cairo_context rel_line_to    [/ width 3]    [/    height    3]]
	 [have cairo_context rel_line_to [- [/ width 3]]   [- [/ height    3]]]
	 [have cairo_context close_path]
	 
	 [have cairo_context move_to     [+ x [/ width 2]] y]
	 [have cairo_context rel_line_to [/ width 2]       [/ [* height 2] 3]]
	 [have cairo_context rel_line_to [- [/ width 3]]   [/    height    3]]
	 [have cairo_context rel_line_to [/    width 3]    [- [/ height    3]]]
	 [have cairo_context close_path]
	 
	 [have cairo_context move_to     [+ x [/ width 2]]     y]
	 [have cairo_context rel_line_to [/ width 3]           [/ [* height 4] 9]]
	 [have cairo_context rel_line_to [- [/ [* width 4] 6]] 0.0]
	 [have cairo_context close_path]
	 
	 ]
	
*/

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
  
  if (raw__eq(cause, new__symbol(cause, "cube"), this__shape)) {
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d,      this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d,  0.0);
    raw__cairo_context__rel_line_to(cause, cairo_context, 0.0,             this__height__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, -this__width__d, 0.0);
    raw__cairo_context__close_path( cause, cairo_context);
  } else if (raw__eq(cause, new__symbol(cause, "pyramid"), this__shape)) {
    raw__cairo_context__move_to(    cause, cairo_context, this__x__d + (this__width__d / 2.0), this__y__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, this__width__d / 2.0, this__height__d);
    raw__cairo_context__rel_line_to(cause, cairo_context, -this__width__d, 0.0);
    raw__cairo_context__close_path( cause, cairo_context);
  } else if (raw__eq(cause, new__symbol(cause, "gripper"), this__shape)) {
    /*
	 [have cairo_context move_to     [+ x [/ width 2]] 0.0]
	 [have cairo_context rel_line_to 0.0               y]
	 [have cairo_context close_path]
	 
	 [have cairo_context move_to     [+ x [/ width 2]] y]
	 [have cairo_context rel_line_to [- [/ width 2]]   [/ [* height 2] 3]]
	 [have cairo_context rel_line_to    [/ width 3]    [/    height    3]]
	 [have cairo_context rel_line_to [- [/ width 3]]   [- [/ height    3]]]
	 [have cairo_context close_path]
	 
	 [have cairo_context move_to     [+ x [/ width 2]] y]
	 [have cairo_context rel_line_to [/ width 2]       [/ [* height 2] 3]]
	 [have cairo_context rel_line_to [- [/ width 3]]   [/    height    3]]
	 [have cairo_context rel_line_to [/    width 3]    [- [/ height    3]]]
	 [have cairo_context close_path]
	 
	 [have cairo_context move_to     [+ x [/ width 2]]     y]
	 [have cairo_context rel_line_to [/ width 3]           [/ [* height 4] 9]]
	 [have cairo_context rel_line_to [- [/ [* width 4] 6]] 0.0]
	 [have cairo_context close_path]
    */
    
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
  }
  return nil;
}

double raw__blocks_world_sprite__render_shape_text_height(f2ptr cause, f2ptr this) {
  f2ptr this__shape = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "shape"), nil));
  if (raw__eq(cause, new__symbol(cause, "cube"), this__shape)) {
    return 0.05;
  } else if (raw__eq(cause, new__symbol(cause, "pyramid"), this__shape)) {
    return 0.05;
  } else if (raw__eq(cause, new__symbol(cause, "gripper"), this__shape)) {
    f2ptr this__height = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil));
    assert_argument_type(double, this__height);
    double this__height__d  = f2double__d(this__height, cause);
    return ((this__height__d / 3.0) - 0.05);
  }
  return 0.0;
}

/*
  [have cairo_context save]
  [cond [[eq `red   color] [have cairo_context set_source_rgba 1.0  0.75 0.75 1.0]]
	[[eq `brown color] [have cairo_context set_source_rgba 1.0  0.75 0.5  1.0]]
	[[eq `green color] [have cairo_context set_source_rgba 0.5  1.0  0.75 1.0]]
	[[eq `blue  color] [have cairo_context set_source_rgba 0.5  0.75 1.0  1.0]]
	[[eq `black color] [have cairo_context set_source_rgba 0.75 0.75 0.75 1.0]]
	[[eq `white color] [have cairo_context set_source_rgba 0.9  0.9  0.9  1.0]]]
  [have cairo_context set_line_width 0.0]
  [have this render_shape_path_to_cairo cairo_context]
  [have cairo_context fill]
  [have cairo_context restore]
  
  [have cairo_context save]
  [have cairo_context set_source_rgba 0.0 0.0 0.0 1.0]
  [have cairo_context set_line_cap `square]
  [have cairo_context set_line_width 0.02]
  [have this render_shape_path_to_cairo cairo_context]
  [have cairo_context stroke]
  [have cairo_context restore]
  
  [have cairo_context save]
  [have cairo_context set_source_rgba 0.0 0.0 0.0 1.0]
  [have cairo_context select_font_face 'Times New Roman' `normal `normal]
  [have cairo_context set_font_size 0.2]
  [let [[text_extents [have cairo_context text_extents [get name as-string]]]]
    [have cairo_context move_to
	  [+ x [/ [- width [get text_extents width]] 2]]
	  [- [+ y height] [get this render_shape_text_height]]]]
  [have cairo_context text_path [get name as-string]]
  [have cairo_context fill]
  [have cairo_context restore]
*/

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

/*
  [let [[next_x [+ x [* step_size x_velocity]]]
	[next_y [+ y [* step_size y_velocity]]]]
    [if [< next_x 0.0]
	[= next_x 0.0]]
    [if [> next_x [- [get blocks_world_physics width] 1]]
	[= next_x [- [get blocks_world_physics width] 1]]]
    
    [let [[obstacle_below_y nil]
	  [obstacle_block   nil]]
      [mapc [funk [block]
		  [if [not [eq this block]]
		      [if [and [get this overlaps_horizontally block]
			       [< y [get block y]]
			       [or [null obstacle_below_y]
				   [< [get block y] obstacle_below_y]]]
			  [prog [= obstacle_below_y [get block y]]
				[= obstacle_block   block]]]]]
	    [get blocks_world_physics blocks]]
      [= on_block nil]
      [if [not [null obstacle_below_y]]
	  [prog `[terminal_format standard-terminal '\n' `[,name on ,[get block name]]]
		[let [[maximum_block_y [- obstacle_below_y height]]]
		  [if [< maximum_block_y next_y]
		      [prog [= on_block   obstacle_block]
			    [= next_y     maximum_block_y]
			    [= y_velocity 0.0]
			    [if [eq `grab movement_command]
				[prog [= movement_command      `recoil]
				      [= is_holding            obstacle_block]
				      [= is_holding_relative_x [- [get obstacle_block x] x]]
				      ]]]]]]]
      ]
    
    [if [< next_y 0.5]
	[prog [= next_y 0.5]
	      [if [eq `recoil movement_command]
		  [= movement_command nil]]]]
    
    [if [eq `drop movement_command]
	[prog [= movement_command      nil]
	      [= is_holding            nil]
	      [= is_holding_relative_x nil]]]
    
    [= x next_x]
    [= y next_y]]]
*/

f2ptr raw__blocks_world_gripper__step(f2ptr cause, f2ptr this, double step_size) {
  assert_argument_type(blocks_world_gripper, this);
  
  f2ptr this__x = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "x"), nil));
  assert_argument_type(double, this__x);
  double this__x__d = f2double__d(this__x, cause);
  
  f2ptr this__y = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "y"), nil));
  assert_argument_type(double, this__y);
  double this__y__d = f2double__d(this__y, cause);
  
  f2ptr this__width = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil));
  assert_argument_type(double, this__width);
  double this__width__d = f2double__d(this__width, cause);
  
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
  
  f2ptr this__movement_command = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "movement_command"), nil));
  
  f2ptr this__blocks_world_physics = assert_value(f2__frame__lookup_var_value(cause, this, new__symbol(cause, "blocks_world_physics"), nil));
  assert_argument_type(blocks_world_physics, this__blocks_world_physics);
  
  f2ptr this__blocks_world_physics__width = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "width"), nil));
  assert_argument_type(double, this__blocks_world_physics__width);
  double this__blocks_world_physics__width__d = f2double__d(this__blocks_world_physics__width, cause);
  
  f2ptr this__blocks_world_physics__grippers = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "grippers"), nil));
  f2ptr this__blocks_world_physics__blocks   = assert_value(f2__frame__lookup_var_value(cause, this__blocks_world_physics, new__symbol(cause, "blocks"),   nil));
  
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
      /*      
		      [prog [= on_block   obstacle_block]
			    [= next_y     maximum_block_y]
			    [= y_velocity 0.0]
			    [if [eq `grab movement_command]
				[prog [= movement_command      `recoil]
				      [= is_holding            obstacle_block]
				      [= is_holding_relative_x [- [get obstacle_block x] x]]
				      ]]]]]]]
      */
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
  
  /*
    [if [< next_y 0.5]
	[prog [= next_y 0.5]
	      [if [eq `recoil movement_command]
		  [= movement_command nil]]]]
    
    [if [eq `drop movement_command]
	[prog [= movement_command      nil]
	      [= is_holding            nil]
	      [= is_holding_relative_x nil]]]
    
    [= x next_x]
    [= y next_y]]]
  */
  
  if (next_y < 0.5) {
    next_y = 0.5;
    if (raw__eq(cause, new__symbol(cause, "recoil"), this__movement_command)) {
      {
	this__movement_command = nil;
	assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "movement_command"), this__movement_command));
      }
    }
  }
  
  if (raw__eq(cause, new__symbol(cause, "drop"), this__movement_command)) {
    {
      this__movement_command = nil;
      assert_value(f2__frame__add_var_value(cause, this, new__symbol(cause, "movement_command"), this__movement_command));
    }
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
  
  /*
    [not [or [<= [+ this__x__d this__width__d] [get block x]]
             [>= this__x__d                    [+ [get block x] [get block width]]]]]]
  */
  
  return (! (((this__x__d + this__width__d) <= block__x__d)                       ||
	     (this__x__d                    >= (block__x__d + block__width__d))));
}

/*
  [let [[obstacle_below_y nil]
	[obstacle_block   nil]]
    [mapc [funk [block]
		[if [not [eq this block]]
		    [if [and [get this overlaps_horizontally block]
			     [< y [get block y]]
			     [or [null obstacle_below_y]
				 [< [get block y] obstacle_below_y]]]
			[prog [= obstacle_below_y [get block y]]
			      [= obstacle_block   block]]]]]
	  [get blocks_world_physics blocks]]
    [= on_block nil]
    [if [not [null obstacle_below_y]]
	[prog `[terminal_format standard-terminal '\n' `[,name on ,[get block name]]]
	      [let [[maximum_block_y [- obstacle_below_y height]]]
		[let [[next_block_y [+ y [* step_size y_velocity]]]]
		  [if [< maximum_block_y next_block_y]
		      [prog [= on_block   obstacle_block]
			    [= y          maximum_block_y]
			    [= y_velocity 0.0]]
		    [= y next_block_y]]]]]]
    ]
  [mapc [funk [gripper]
	      [if [eq this [get gripper is_holding]]
		  [prog [= x [+ [get gripper x] [get gripper is_holding_relative_x]]]
			[= y [+ [get gripper y] [get gripper height]]]
			[= x_velocity 0.0]
			[= y_velocity 0.0]]]]
	[get blocks_world_physics grippers]]
*/

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
	  /*
		  [prog [= x [+ [get gripper x] [get gripper is_holding_relative_x]]]
			[= y [+ [get gripper y] [get gripper height]]]
			[= x_velocity 0.0]
			[= y_velocity 0.0]]]]
	  */ 
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



/*
  `[prog [mapc [funk [gripper]
		     [have gripper step step_size]]
	       grippers]
	 [mapc [funk [block]
		     [have block step step_size]]
	       blocks]]]
*/

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



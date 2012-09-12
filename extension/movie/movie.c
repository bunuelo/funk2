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

#include "movie.h"
#include "../image/image.h"
#include "../image_sequence/image_sequence.h"

#ifdef F2__LIBAVCODEC_SUPPORTED

void libavcodec__initialize() {
  avcodec_init();
  avcodec_register_all();
}

void libavcodec__video_encode_example(const char *filename) {
  
  AVCodec *codec;
  AVCodecContext *c= NULL;
  int i, out_size, size, x, y, outbuf_size;
  FILE *f;
  AVFrame *picture;
  uint8_t *outbuf, *picture_buf;
  
  // find the mpeg1 video encoder
  codec = avcodec_find_encoder(CODEC_ID_MPEG1VIDEO);
  if (!codec) {
    printf("codec not found\n");
    return;
  }
  
  c= avcodec_alloc_context();
  picture= avcodec_alloc_frame();
  
  // put sample parameters
  c->bit_rate = 400000;
  // resolution must be a multiple of two
  c->width = 352;
  c->height = 288;
  // frames per second
  c->time_base= (AVRational){1,25};
  c->gop_size = 10; // emit one intra frame every ten frames
  c->max_b_frames=1;
  c->pix_fmt = PIX_FMT_YUV420P;
  
  // open it
  if (avcodec_open(c, codec) < 0) {
    printf("could not open codec\n");
    return;
  }
  
  f = fopen(filename, "wb");
  if (!f) {
    printf("could not open %s\n", filename);
    return;
  }
  
  // alloc image and output buffer
  outbuf_size = 100000;
  outbuf = malloc(outbuf_size);
  size = c->width * c->height;
  picture_buf = malloc((size * 3) / 2); // size for YUV 420
  
  picture->data[0] = picture_buf;
  picture->data[1] = picture->data[0] + size;
  picture->data[2] = picture->data[1] + size / 4;
  picture->linesize[0] = c->width;
  picture->linesize[1] = c->width / 2;
  picture->linesize[2] = c->width / 2;
  
  // encode 1 second of video
  for(i=0;i<25;i++) {
    // prepare a dummy image
    // Y
    for(y=0;y<c->height;y++) {
      for(x=0;x<c->width;x++) {
	picture->data[0][y * picture->linesize[0] + x] = x + y + i * 3;
      }
    }
    
    // Cb and Cr
    for(y=0;y<c->height/2;y++) {
      for(x=0;x<c->width/2;x++) {
	picture->data[1][y * picture->linesize[1] + x] = 128 + y + i * 2;
	picture->data[2][y * picture->linesize[2] + x] = 64 + x + i * 5;
      }
    }
    
    // encode the image
    out_size = avcodec_encode_video(c, outbuf, outbuf_size, picture);
    //printf("encoding frame %3d (size=%5d)\n", i, out_size);
    fwrite(outbuf, 1, out_size, f);
  }
  
  // get the delayed frames
  for(; out_size; i++) {
    out_size = avcodec_encode_video(c, outbuf, outbuf_size, NULL);
    //printf("write frame %3d (size=%5d)\n", i, out_size);
    fwrite(outbuf, 1, out_size, f);
  }
  
  /* add sequence end code to have a real mpeg file */
  outbuf[0] = 0x00;
  outbuf[1] = 0x00;
  outbuf[2] = 0x01;
  outbuf[3] = 0xb7;
  fwrite(outbuf, 1, 4, f);
  fclose(f);
  free(picture_buf);
  free(outbuf);
  
  avcodec_close(c);
  av_free(c);
  av_free(picture);
}


// funk2_movie_context

boolean_t funk2_movie_context__init(funk2_movie_context_t* this, s64 width, s64 height, s64 bit_rate, s64 frames_per_second) {
  if (((width  & 1) != 0) ||
      ((height & 1) != 0)) {
    printf("\nwidth and height must both be a power of two.");
    return boolean__false;
  }
  // valid frames per second for MPEG-1: 23.976, 24, 25, 29.97, 30, 50, 59.94, and 60
  if ((frames_per_second != 24) &&
      (frames_per_second != 25) &&
      (frames_per_second != 30) &&
      (frames_per_second != 50) &&
      (frames_per_second != 60)) {
    printf("\nframes_per_second for MPEG-1 must be one of 24, 25, 30, 50, or 60.");
    return boolean__false;
  }
  
  this->width            = width;
  this->height           = height;
  this->av_codec_context = NULL;
  
  // find the mpeg1 video encoder
  this->av_codec = avcodec_find_encoder(CODEC_ID_MPEG1VIDEO);
  if (this->av_codec == NULL) {
    printf("codec not found\n");
    return boolean__false;
  }
  
  // put sample parameters
  this->av_codec_context                = avcodec_alloc_context();
  this->av_codec_context->bit_rate      = bit_rate;
  this->av_codec_context->width         = width;
  this->av_codec_context->height        = height;
  this->av_codec_context->time_base.num = 1;
  this->av_codec_context->time_base.den = frames_per_second;
  this->av_codec_context->gop_size      = 10; // emit one intra frame every ten frames
  this->av_codec_context->max_b_frames  = 1;
  this->av_codec_context->pix_fmt       = PIX_FMT_YUV420P;
  this->av_codec_context->qmin          = 3;
  
  if (avcodec_open(this->av_codec_context, this->av_codec) < 0) {
    printf("could not open codec\n");
    return boolean__false;
  }
  
  {    
    this->rgb_picture_frame = avcodec_alloc_frame();
    if (this->rgb_picture_frame == NULL) {
      printf("\ncouldn't allocate rgb_picture_frame.");
      return boolean__false;
    }
    
    this->rgb_picture_frame__size   = avpicture_get_size(PIX_FMT_RGB32, width, height);
    this->rgb_picture_frame__buffer = (u8*)from_ptr(f2__malloc(this->rgb_picture_frame__size));
    
    avpicture_fill((AVPicture*)this->rgb_picture_frame, this->rgb_picture_frame__buffer, PIX_FMT_RGB32, width, height);
  }
  
  {    
    this->yuv_picture_frame = avcodec_alloc_frame();
    if (this->yuv_picture_frame == NULL) {
      printf("\ncouldn't allocate yuv_picture_frame.");
      return boolean__false;
    }
    
    this->yuv_picture_frame__size   = avpicture_get_size(PIX_FMT_YUV420P, width, height);
    this->yuv_picture_frame__buffer = (u8*)from_ptr(f2__malloc(this->yuv_picture_frame__size));
    
    avpicture_fill((AVPicture*)this->yuv_picture_frame, this->yuv_picture_frame__buffer, PIX_FMT_YUV420P, width, height);
  }
  
  this->image_convert_context = sws_getContext(width, height, PIX_FMT_RGB32, width, height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
  
  this->out_buffer_size = bit_rate;
  this->out_buffer      = (u8*)from_ptr(f2__malloc(this->out_buffer_size));
  return boolean__true;
}

void funk2_movie_context__destroy(funk2_movie_context_t* this) {
  sws_freeContext(this->image_convert_context);
  
  f2__free(to_ptr(this->rgb_picture_frame__buffer));
  av_free(this->rgb_picture_frame);
  f2__free(to_ptr(this->yuv_picture_frame__buffer));
  av_free(this->yuv_picture_frame);
  f2__free(to_ptr(this->out_buffer));
  
  avcodec_close(this->av_codec_context);
  av_free(this->av_codec_context);
}


#endif // F2__LIBAVCODEC_SUPPORTED


// movie_context

f2ptr raw__movie_context__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr bit_rate, f2ptr frames_per_second, f2ptr pointer) {
#ifdef F2__LIBAVCODEC_SUPPORTED
  return f2__frame__new(cause, f2list12__new(cause,
					     new__symbol(cause, "type"),              new__symbol(cause, "movie_context"),
					     new__symbol(cause, "width"),             width,
					     new__symbol(cause, "height"),            height,
					     new__symbol(cause, "bit_rate"),          bit_rate,
					     new__symbol(cause, "frames_per_second"), frames_per_second,
					     new__symbol(cause, "pointer"),           pointer));
#else
  return f2larva__new(cause, 511161, nil);
#endif // F2__LIBAVCODEC_SUPPORTED
}

f2ptr f2__movie_context__new(f2ptr cause, f2ptr width, f2ptr height, f2ptr bit_rate, f2ptr frames_per_second) {
  if ((! raw__integer__is_type(cause, width)) ||
      (! raw__integer__is_type(cause, height)) ||
      (! raw__integer__is_type(cause, bit_rate)) ||
      (! raw__integer__is_type(cause, frames_per_second))) {
    return f2larva__new(cause, 1, nil);
  }
#ifdef F2__LIBAVCODEC_SUPPORTED
  s64                    width__i             = f2integer__i(width,             cause);
  s64                    height__i            = f2integer__i(height,            cause);
  s64                    bit_rate__i          = f2integer__i(bit_rate,          cause);
  s64                    frames_per_second__i = f2integer__i(frames_per_second, cause);
  funk2_movie_context_t* movie_context        = (funk2_movie_context_t*)from_ptr(f2__malloc(sizeof(funk2_movie_context_t)));
  if (! funk2_movie_context__init(movie_context, width__i, height__i, bit_rate__i, frames_per_second__i)) {
    return f2larva__new(cause, 12335, nil);
  }
  f2ptr pointer = f2pointer__new(cause, to_ptr(movie_context));
  return raw__movie_context__new(cause, width, height, bit_rate, frames_per_second, pointer);
#else
  return f2larva__new(cause, 511161, nil);
#endif // F2__LIBAVCODEC_SUPPORTED
}
export_cefunk4(movie_context__new, width, height, bit_rate, frames_per_second, 0, "Returns a new movie_context object.");


boolean_t raw__movie_context__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "movie_context");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__movie_context__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__movie_context__is_type(cause, thing));
}
export_cefunk1(movie_context__is_type, thing, 0, "Returns whether or not thing is of type movie_context.");


f2ptr raw__movie_context__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__movie_context__type(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__type(cause, this);
}
export_cefunk1(movie_context__type, thing, 0, "Returns the specific type of object that this movie_context is.");


f2ptr raw__movie_context__width(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "width"), nil);
}

f2ptr f2__movie_context__width(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__width(cause, this);
}
export_cefunk1(movie_context__width, thing, 0, "Returns the width of the movie_context.");


f2ptr raw__movie_context__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "width"), value);
}

f2ptr f2__movie_context__width__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__width__set(cause, this, value);
}
export_cefunk2(movie_context__width__set, thing, value, 0, "Sets the width of the movie_context.");


f2ptr raw__movie_context__height(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "height"), nil);
}

f2ptr f2__movie_context__height(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__height(cause, this);
}
export_cefunk1(movie_context__height, thing, 0, "Returns the height of the movie_context.");


f2ptr raw__movie_context__height__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "height"), value);
}

f2ptr f2__movie_context__height__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__height__set(cause, this, value);
}
export_cefunk2(movie_context__height__set, thing, value, 0, "Sets the height of the movie_context.");


f2ptr raw__movie_context__bit_rate(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "bit_rate"), nil);
}

f2ptr f2__movie_context__bit_rate(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__bit_rate(cause, this);
}
export_cefunk1(movie_context__bit_rate, thing, 0, "Returns the bit_rate of the movie_context.");


f2ptr raw__movie_context__bit_rate__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "bit_rate"), value);
}

f2ptr f2__movie_context__bit_rate__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__bit_rate__set(cause, this, value);
}
export_cefunk2(movie_context__bit_rate__set, thing, value, 0, "Sets the bit_rate of the movie_context.");


f2ptr raw__movie_context__frames_per_second(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "frames_per_second"), nil);
}

f2ptr f2__movie_context__frames_per_second(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__frames_per_second(cause, this);
}
export_cefunk1(movie_context__frames_per_second, thing, 0, "Returns the frames_per_second of the movie_context.");


f2ptr raw__movie_context__frames_per_second__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "frames_per_second"), value);
}

f2ptr f2__movie_context__frames_per_second__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__frames_per_second__set(cause, this, value);
}
export_cefunk2(movie_context__frames_per_second__set, thing, value, 0, "Sets the frames_per_second of the movie_context.");


f2ptr raw__movie_context__pointer(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "pointer"), nil);
}

f2ptr f2__movie_context__pointer(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__pointer(cause, this);
}
export_cefunk1(movie_context__pointer, thing, 0, "Returns the pointer of the movie_context.");


f2ptr raw__movie_context__pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "pointer"), value);
}

f2ptr f2__movie_context__pointer__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__pointer__set(cause, this, value);
}
export_cefunk2(movie_context__pointer__set, thing, value, 0, "Sets the pointer of the movie_context.");


f2ptr raw__movie_context__destroy(f2ptr cause, f2ptr this) {
#ifdef F2__LIBAVCODEC_SUPPORTED
  f2ptr pointer = raw__movie_context__pointer(cause, this);
  if (pointer == nil) {
    return f2larva__new(cause, 123, nil);
  }
  funk2_movie_context_t* movie_context = (funk2_movie_context_t*)from_ptr(f2pointer__p(pointer, cause)); 
  funk2_movie_context__destroy(movie_context);
  f2__free(to_ptr(movie_context));
  raw__movie_context__pointer__set(cause, this, nil);
  return nil;
#else
  return f2larva__new(cause, 511161, nil);
#endif // F2__LIBAVCODEC_SUPPORTED
}

f2ptr f2__movie_context__destroy(f2ptr cause, f2ptr this) {
  if (! raw__movie_context__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie_context__destroy(cause, this);
}
export_cefunk1(movie_context__destroy, this, 0, "Frees all of the resources associated with this movie_context.");



f2ptr f2__movie_context_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),               f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),              f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),             f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "width"),             f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__width__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "height"),            f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__height")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "height"),            f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__height__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "bit_rate"),          f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__bit_rate")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "bit_rate"),          f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__bit_rate__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "frames_per_second"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__frames_per_second")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "frames_per_second"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__frames_per_second__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "pointer"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__pointer")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "pointer"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__pointer__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "destroy"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie_context__destroy")));}
  return this;
}




f2ptr raw__libavcodec__video_chunk__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence) {
#ifdef F2__LIBAVCODEC_SUPPORTED
  s64 width__i                  = f2integer__i(raw__movie_context__width(  cause, movie_context),  cause);
  s64 height__i                 = f2integer__i(raw__movie_context__height( cause, movie_context),  cause);
  s64 image_sequence__width__i  = f2integer__i(raw__image_sequence__width( cause, image_sequence), cause);
  s64 image_sequence__height__i = f2integer__i(raw__image_sequence__height(cause, image_sequence), cause);
  if ((width__i  != image_sequence__width__i) ||
      (height__i != image_sequence__height__i)) {
    return f2larva__new(cause, 15316, nil);
  }
  f2ptr movie_context__pointer = raw__movie_context__pointer(cause, movie_context);
  if (movie_context__pointer == nil) {
    return f2larva__new(cause, 2461, nil);
  }
  funk2_movie_context_t* funk2_movie_context = (funk2_movie_context_t*)from_ptr(f2pointer__p(movie_context__pointer, cause));
  
  f2ptr video_chunk_list = nil;
  {
    
    {
      
      s64 out_size = 0;
      {
	f2ptr iter = f2__image_sequence__first_image_link(cause, image_sequence);
	while (iter != nil) {
	  f2ptr image     = f2__doublelink__value(cause, iter);
	  f2ptr rgba_data = f2__image__rgba_data(cause, image);
	  
	  s64 chunk__length = f2chunk__length(rgba_data, cause);
	  if (chunk__length != funk2_movie_context->rgb_picture_frame__size) {
	    printf("\nmovie.c error: chunk__length != rgb_picture_frame__size");
	    return f2larva__new(cause, 453, nil);
	  }
	  raw__chunk__str_copy(cause, rgba_data, funk2_movie_context->rgb_picture_frame__buffer);
	  
	  { // swap red and blue
	    s64 y;
	    for (y = 0; y < height__i; y ++) {
	      s64 x;
	      for (x = 0; x < width__i; x ++) {
		s64 pixel_index = ((y * width__i) + x) << 2;
		u8 red                                                    = funk2_movie_context->rgb_picture_frame__buffer[pixel_index + 0];
		funk2_movie_context->rgb_picture_frame__buffer[pixel_index + 0] = funk2_movie_context->rgb_picture_frame__buffer[pixel_index + 2];
		funk2_movie_context->rgb_picture_frame__buffer[pixel_index + 2] = red;
	      }
	    }
	  }
	  
	  sws_scale(funk2_movie_context->image_convert_context,
		    (const uint8_t* const*)(((AVPicture*)funk2_movie_context->rgb_picture_frame)->data),
		    ((AVPicture*)funk2_movie_context->rgb_picture_frame)->linesize,
		    0,
		    height__i,
		    ((AVPicture*)funk2_movie_context->yuv_picture_frame)->data,
		    ((AVPicture*)funk2_movie_context->yuv_picture_frame)->linesize);	
	  
	  // encode the image
	  out_size = avcodec_encode_video(funk2_movie_context->av_codec_context, funk2_movie_context->out_buffer, funk2_movie_context->out_buffer_size, funk2_movie_context->yuv_picture_frame);
	  f2ptr chunk      = f2chunk__new(cause, out_size, funk2_movie_context->out_buffer);
	  video_chunk_list = raw__cons__new(cause, chunk, video_chunk_list);
	  
	  iter = f2__doublelink__next(cause, iter);
	}
      }
      
      // get the delayed frames
      while (out_size != 0) {
	out_size = avcodec_encode_video(funk2_movie_context->av_codec_context, funk2_movie_context->out_buffer, funk2_movie_context->out_buffer_size, NULL);
	f2ptr chunk      = f2chunk__new(cause, out_size, funk2_movie_context->out_buffer);
	video_chunk_list = raw__cons__new(cause, chunk, video_chunk_list);
      }
      
      /* add sequence end code to have a real mpeg file */
      {
	funk2_movie_context->out_buffer[0] = 0x00;
	funk2_movie_context->out_buffer[1] = 0x00;
	funk2_movie_context->out_buffer[2] = 0x01;
	funk2_movie_context->out_buffer[3] = 0xb7;
	out_size = 4;
	f2ptr chunk      = f2chunk__new(cause, out_size, funk2_movie_context->out_buffer);
	video_chunk_list = raw__cons__new(cause, chunk, video_chunk_list);
      }
    }
  }
  video_chunk_list = f2__reverse(cause, video_chunk_list);
  s64 total_length = 0;
  {
    f2ptr iter = video_chunk_list;
    while (iter) {
      f2ptr chunk = f2cons__car(iter, cause);
      total_length += f2chunk__length(chunk, cause);
      iter = f2cons__cdr(iter, cause);
    }
  }
  f2ptr video_chunk = f2chunk__new(cause, total_length, NULL);
  {
    s64 index = 0;
    f2ptr iter = video_chunk_list;
    while (iter) {
      f2ptr chunk = f2cons__car(iter, cause);
      s64 chunk_length = f2chunk__length(chunk, cause);
      {
	s64 chunk_index;
	for (chunk_index = 0; chunk_index < chunk_length; chunk_index ++) {
	  raw__chunk__bit8__elt__set(cause, video_chunk, index + chunk_index, raw__chunk__bit8__elt(cause, chunk, chunk_index));
	}
      }
      index += chunk_length;
      iter = f2cons__cdr(iter, cause);
    }
  }
  return video_chunk;
#else
  return f2larva__new(cause, 3290, nil);
#endif // F2__LIBAVCODEC_SUPPORTED
}

f2ptr f2__libavcodec__video_chunk__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence) {
  if ((! raw__movie_context__is_type(cause, movie_context)) ||
      (! raw__image_sequence__is_type(cause, image_sequence))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__libavcodec__video_chunk__new_from_image_sequence(cause, movie_context, image_sequence);
}
export_cefunk2(libavcodec__video_chunk__new_from_image_sequence, movie_context, image_sequence, 0, "");



// movie

f2ptr raw__movie__new(f2ptr cause, f2ptr video_chunk) {
  return f2__frame__new(cause, f2list4__new(cause,
					    new__symbol(cause, "type"),        new__symbol(cause, "movie"),
					    new__symbol(cause, "video_chunk"), video_chunk));
}

f2ptr f2__movie__new(f2ptr cause, f2ptr video_chunk) {
  if (! raw__chunk__is_type(cause, video_chunk)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__new(cause, video_chunk);
}
export_cefunk1(movie__new, images, 0, "Returns a new movie object.");


boolean_t raw__movie__is_type(f2ptr cause, f2ptr thing) {
  if (! raw__frame__is_type(cause, thing)) {
    return boolean__false;
  }
  f2ptr this_type_name_symbol = new__symbol(cause, "movie");
  f2ptr thing_type_name       = f2__frame__lookup_var_value(cause, thing, new__symbol(cause, "type"), nil);
  if (raw__eq(cause, this_type_name_symbol, thing_type_name)) {
    return boolean__true;
  }
  f2ptr thing_type = f2__lookup_type(cause, thing_type_name);
  if (raw__primobject_type__has_parent_type(cause, thing_type, this_type_name_symbol)) {
    return boolean__true;
  }
  return boolean__false;
}

f2ptr f2__movie__is_type(f2ptr cause, f2ptr thing) {
  return f2bool__new(raw__movie__is_type(cause, thing));
}
export_cefunk1(movie__is_type, thing, 0, "Returns whether or not thing is of type movie.");


f2ptr raw__movie__type(f2ptr cause, f2ptr this) {
  return f2__object__type(cause, this);
}

f2ptr f2__movie__type(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__type(cause, this);
}
export_cefunk1(movie__type, thing, 0, "Returns the specific type of object that this movie is.");


f2ptr raw__movie__video_chunk(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "video_chunk"), nil);
}

f2ptr f2__movie__video_chunk(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__video_chunk(cause, this);
}
export_cefunk1(movie__video_chunk, thing, 0, "Returns the video_chunk of the movie.");


f2ptr raw__movie__video_chunk__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "video_chunk"), value);
}

f2ptr f2__movie__video_chunk__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__video_chunk__set(cause, this, value);
}
export_cefunk2(movie__video_chunk__set, thing, value, 0, "Sets the video_chunk of the movie.");


f2ptr raw__movie__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence) {
  f2ptr video_chunk = raw__libavcodec__video_chunk__new_from_image_sequence(cause, movie_context, image_sequence);
  if (raw__larva__is_type(cause, video_chunk)) {
    return video_chunk;
  }
  return f2__movie__new(cause, video_chunk);
}

f2ptr f2__movie__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence) {
  if ((! raw__movie_context__is_type(cause, movie_context)) ||
      (! raw__image_sequence__is_type(cause, image_sequence))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__new_from_image_sequence(cause, movie_context, image_sequence);
}
export_cefunk2(movie__new_from_image_sequence, movie_context, image_sequence, 0, "Creates a new movie from an image sequence.");


f2ptr raw__movie__save(f2ptr cause, f2ptr this, f2ptr filename) {
  f2ptr video_chunk = raw__movie__video_chunk(cause, this);
  return f2__chunk__save(cause, video_chunk, filename);
}

f2ptr f2__movie__save(f2ptr cause, f2ptr this, f2ptr filename) {
  if ((! raw__movie__is_type(cause, this)) ||
      (! raw__string__is_type(cause, filename))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__save(cause, this, filename);
}
export_cefunk2(movie__save, this, filename, 0, "Saves a movie to an mpeg file.");


f2ptr f2__movie_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),         f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),     f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),        f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "video_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__video_chunk")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "video_chunk"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__video_chunk__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "save"),        f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__save")));}
  return this;
}



// **

f2ptr f2__movie__core_extension__ping(f2ptr cause) {
  return nil;
}
export_cefunk0(movie__core_extension__ping, 0, "");

f2ptr f2__movie__core_extension__initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "movie_context"), f2__movie_context_type__new(cause));
  f2__add_type(cause, new__symbol(cause, "movie"),         f2__movie_type__new(cause));
  f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "image_sequence"), new__symbol(cause, "image_sequence__core_extension__ping")), nil);
#ifdef F2__LIBAVCODEC_SUPPORTED
  libavcodec__initialize();
  status("movie initialized.");
#else
  status("movie initialized, but libavcodec was not compiled into this version of Funk2.");
#endif // F2__LIBAVCODEC_SUPPORTED
  return nil;
}
export_cefunk0(movie__core_extension__initialize, 0, "");

f2ptr f2__movie__core_extension__destroy(f2ptr cause) {
  status("movie destroyed.");
  return nil;
}
export_cefunk0(movie__core_extension__destroy, 0, "");



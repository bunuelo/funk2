// 
// Copyright (c) 2007-2010 Bo Morgan.
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

#include "../../c/funk2.h"
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

#endif // F2__LIBAVCODEC_SUPPORTED



f2ptr raw__libavcodec__video_chunk__new_from_image_sequence(f2ptr cause, f2ptr image_sequence, f2ptr bit_rate, f2ptr frames_per_second) {
#ifdef F2__LIBAVCODEC_SUPPORTED
  s64 bit_rate__i          = f2integer__i(bit_rate,                                           cause);
  s64 frames_per_second__i = f2integer__i(frames_per_second,                                  cause);
  s64 width__i             = f2integer__i(raw__image_sequence__width( cause, image_sequence), cause);
  s64 height__i            = f2integer__i(raw__image_sequence__height(cause, image_sequence), cause);
  f2ptr video_chunk_list = nil;
  {
    AVCodec *codec;
    AVCodecContext *c= NULL;
    int out_size, size, x, y, outbuf_size;
    AVFrame *picture;
    uint8_t *outbuf, *picture_buf;
    
    // find the mpeg1 video encoder
    codec = avcodec_find_encoder(CODEC_ID_MPEG1VIDEO);
    if (!codec) {
      printf("codec not found\n");
      return f2larva__new(cause, 43111, nil);
    }
    
    c= avcodec_alloc_context();
    picture= avcodec_alloc_frame();
    
    // put sample parameters
    c->bit_rate = bit_rate__i;
    // resolution must be a multiple of two
    c->width  = width__i;
    c->height = height__i;
    // frames per second
    c->time_base.num = 1;
    c->time_base.den = frames_per_second__i;
    c->gop_size = 10; // emit one intra frame every ten frames
    c->max_b_frames=1;
    c->pix_fmt = PIX_FMT_YUV420P;
    
    // open it
    if (avcodec_open(c, codec) < 0) {
      printf("could not open codec\n");
      return f2larva__new(cause, 43111, nil);
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
    
    out_size = 0;
    {
      f2ptr iter = f2__image_sequence__first_image_link(cause, image_sequence);
      while (iter != nil) {
	f2ptr image     = f2__doublelink__value(cause, iter);
	f2ptr rgba_data = f2__image__rgba_data(cause, image);
	
	// prepare a dummy image
	// Y
	for(y = 0; y < c->height; y ++) {
	  for(x = 0; x < c->width; x ++) {
	    double red   = ((double)raw__chunk__bit8__elt(cause, rgba_data, ((y * c->width) + x) << 2) + 0) / 255.0;
	    double green = ((double)raw__chunk__bit8__elt(cause, rgba_data, ((y * c->width) + x) << 2) + 0) / 255.0;
	    double blue  = ((double)raw__chunk__bit8__elt(cause, rgba_data, ((y * c->width) + x) << 2) + 0) / 255.0;
	    picture->data[0][y * picture->linesize[0] + x] = x + y;
	  }
	}
	
	// Cb and Cr
	for(iy = 0; iy < c->height/2; iy ++) {
	  for(ix = 0; ix < c->width/2; ix ++) {
	    int x = x * 2;
	    int y = y * 2;
	    double red_0_0   = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 0) * c->width) + (x + 0)) << 2) + 0) / 255.0;
	    double green_0_0 = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 0) * c->width) + (x + 0)) << 2) + 0) / 255.0;
	    double blue_0_0  = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 0) * c->width) + (x + 0)) << 2) + 0) / 255.0;
	    double red_1_0   = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 1) * c->width) + (x + 0)) << 2) + 0) / 255.0;
	    double green_1_0 = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 1) * c->width) + (x + 0)) << 2) + 0) / 255.0;
	    double blue_1_0  = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 1) * c->width) + (x + 0)) << 2) + 0) / 255.0;
	    double red_0_1   = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 0) * c->width) + (x + 1)) << 2) + 0) / 255.0;
	    double green_0_1 = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 0) * c->width) + (x + 1)) << 2) + 0) / 255.0;
	    double blue_0_1  = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 0) * c->width) + (x + 1)) << 2) + 0) / 255.0;
	    double red_1_1   = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 1) * c->width) + (x + 1)) << 2) + 0) / 255.0;
	    double green_1_1 = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 1) * c->width) + (x + 1)) << 2) + 0) / 255.0;
	    double blue_1_1  = ((double)raw__chunk__bit8__elt(cause, rgba_data, (((y + 1) * c->width) + (x + 1)) << 2) + 0) / 255.0;
	    double red   = (red_0_0   + red_0_1   + red_1_0   + red_1_1)   / 4;
	    double green = (green_0_0 + green_0_1 + green_1_0 + green_1_1) / 4;
	    double blue  = (blue_0_0  + blue_0_1  + blue_1_0  + blue_1_1)  / 4;
	    picture->data[1][iy * picture->linesize[1] + ix] = 128 + iy;
	    picture->data[2][iy * picture->linesize[2] + ix] = 64 + ix;
	  }
	}
	
	// encode the image
	out_size = avcodec_encode_video(c, outbuf, outbuf_size, picture);
	f2ptr chunk      = f2chunk__new(cause, out_size, outbuf);
	video_chunk_list = f2cons__new(cause, chunk, video_chunk_list);
	
	iter = f2__doublelink__next(cause, iter);
      }
    }
    
    // get the delayed frames
    while (out_size != 0) {
      out_size = avcodec_encode_video(c, outbuf, outbuf_size, NULL);
      f2ptr chunk      = f2chunk__new(cause, out_size, outbuf);
      video_chunk_list = f2cons__new(cause, chunk, video_chunk_list);
    }
    
    /* add sequence end code to have a real mpeg file */
    {
      outbuf[0] = 0x00;
      outbuf[1] = 0x00;
      outbuf[2] = 0x01;
      outbuf[3] = 0xb7;
      out_size = 4;
      f2ptr chunk      = f2chunk__new(cause, out_size, outbuf);
      video_chunk_list = f2cons__new(cause, chunk, video_chunk_list);
    }
    free(picture_buf);
    free(outbuf);
    
    avcodec_close(c);
    av_free(c);
    av_free(picture);
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

f2ptr f2__libavcodec__video_chunk__new_from_image_sequence(f2ptr cause, f2ptr image_sequence, f2ptr bit_rate, f2ptr frames_per_second) {
  if ((! raw__image_sequence__is_type(cause, image_sequence)) ||
      (! raw__integer__is_type(cause, bit_rate)) ||
      (! raw__integer__is_type(cause, frames_per_second))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__libavcodec__video_chunk__new_from_image_sequence(cause, image_sequence, bit_rate, frames_per_second);
}
export_cefunk3(libavcodec__video_chunk__new_from_image_sequence, image_sequence, bit_rate, frames_per_second, 0, "");



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


f2ptr raw__movie__new_from_image_sequence(f2ptr cause, f2ptr image_sequence, f2ptr bit_rate, f2ptr frames_per_second) {
  f2ptr video_chunk = raw__libavcodec__video_chunk__new_from_image_sequence(cause, image_sequence, bit_rate, frames_per_second);
  if (raw__larva__is_type(cause, video_chunk)) {
    return video_chunk;
  }
  return f2__movie__new(cause, video_chunk);
}

f2ptr f2__movie__new_from_image_sequence(f2ptr cause, f2ptr image_sequence, f2ptr bit_rate, f2ptr frames_per_second) {
  if ((! raw__image_sequence__is_type(cause, image_sequence)) ||
      (! raw__integer__is_type(cause, bit_rate)) ||
      (! raw__integer__is_type(cause, frames_per_second))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__new_from_image_sequence(cause, image_sequence, bit_rate, frames_per_second);
}
export_cefunk3(movie__new_from_image_sequence, image_sequence, bit_rate, frames_per_second, 0, "Creates a new movie from an image sequence.");


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

f2ptr f2__movie__core_extension_ping(f2ptr cause) {
  return nil;
}
export_cefunk0(movie__core_extension_ping, 0, "");

f2ptr f2__movie__core_extension_initialize(f2ptr cause) {
  f2__add_type(cause, new__symbol(cause, "movie"), f2__movie_type__new(cause));
  f2__force_funk_apply(cause, f2__this__fiber(cause), f2__core_extension_funk__new(cause, new__symbol(cause, "image"), new__symbol(cause, "image_sequence__core_extension_ping")), nil);
#ifdef F2__LIBAVCODEC_SUPPORTED
  libavcodec__initialize();
  libavcodec__video_encode_example("example.mpeg");
  printf("\nmovie initialized."); fflush(stdout);
#else
  printf("\nmovie initialized, but libavcodec was not compiled into this version of Funk2."); fflush(stdout);
#endif // F2__LIBAVCODEC_SUPPORTED
  return nil;
}
export_cefunk0(movie__core_extension_initialize, 0, "");

f2ptr f2__movie__core_extension_destroy(f2ptr cause) {
  printf("\nmovie destroyed."); fflush(stdout);
  return nil;
}
export_cefunk0(movie__core_extension_destroy, 0, "");



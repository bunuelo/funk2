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



f2ptr raw__libavcodec__video_chunk_list__new_from_image_sequence(f2ptr cause, f2ptr image_sequence, f2ptr bit_rate, f2ptr frames_per_second) {
#ifdef F2__LIBAVCODEC_SUPPORTED
  s64 bit_rate__i          = f2integer__i(bit_rate,                                           cause);
  s64 frames_per_second__i = f2integer__i(frames_per_second,                                  cause);
  s64 width__i             = f2integer__i(raw__image_sequence__width( cause, image_sequence), cause);
  s64 height__i            = f2integer__i(raw__image_sequence__height(cause, image_sequence), cause);
  f2ptr video_chunk_list = nil;
  {
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
      f2ptr chunk      = f2chunk__new(cause, out_size, outbuf);
      video_chunk_list = f2cons__new(cause, chunk, video_chunk_list);
    }
    
    // get the delayed frames
    for(; out_size; i++) {
      out_size = avcodec_encode_video(c, outbuf, outbuf_size, NULL);
      f2ptr chunk      = f2chunk__new(cause, out_size, outbuf);
      video_chunk_list = f2cons__new(cause, chunk, video_chunk_list);
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
  return video_chunk_list;
#else
  return f2larva__new(cause, 3290, nil);
#endif // F2__LIBAVCODEC_SUPPORTED
}

f2ptr f2__libavcodec__video_chunk_list__new_from_image_sequence(f2ptr cause, f2ptr image_sequence, f2ptr bit_rate, f2ptr frames_per_second) {
  if ((! raw__image_sequence__is_type(cause, image_sequence)) ||
      (! raw__integer__is_type(cause, bit_rate)) ||
      (! raw__integer__is_type(cause, frames_per_second))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__libavcodec__video_chunk_list__new_from_image_sequence(cause, image_sequence, bit_rate, frames_per_second);
}
export_cefunk3(libavcodec__video_chunk_list__new_from_image_sequence, this, image_sequence, bit_rate, frames_per_second, 0, "");



f2ptr raw__movie__new(f2ptr cause, f2ptr images) {
  f2ptr first_image_link;
  {
    f2ptr next = nil;
    f2ptr iter = images;
    while (iter != nil) {
      next = iter;
      iter = f2__doublelink__prev(cause, iter);
    }
    first_image_link = next;
  }
  f2ptr last_image_link;
  {
    f2ptr prev = nil;
    f2ptr iter = images;
    while (iter != nil) {
      prev = iter;
      iter = f2__doublelink__next(cause, iter);
    }
    last_image_link = prev;
  }
  s64 width  = -1;
  s64 height = -1;
  {
    f2ptr iter = first_image_link;
    while (iter != nil) {
      f2ptr image = f2__doublelink__value(cause, iter);
      if (! raw__image__is_type(cause, image)) {
	return f2larva__new(cause, 1, nil);
      }
      s64 image__width  = raw__image__width( cause, image);
      s64 image__height = raw__image__height(cause, image);
      if (width == -1) {
	width  = image__width;
	height = image__height;
      } else if ((width  != image__width) ||
		 (height != image__height)) {
	return f2larva__new(cause, 13, nil);
      }
      iter = f2__doublelink__next(cause, iter);
    }
  }
  return f2__frame__new(cause, f2list8__new(cause,
					    new__symbol(cause, "type"),             new__symbol(cause, "movie"),
					    new__symbol(cause, "first_image_link"), first_image_link,
					    new__symbol(cause, "last_image_link"),  last_image_link,
					    new__symbol(cause, "images"),           images));
}

f2ptr f2__movie__new(f2ptr cause, f2ptr images) {
  if ((images != nil) && (! raw__doublelink__is_type(cause, images))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__new(cause, images);
}
export_cefunk1(movie__new, images, 0, "Returns a new movie object.  images can be nil or a doublelink list.");


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


f2ptr raw__movie__first_image_link(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "first_image_link"), nil);
}

f2ptr f2__movie__first_image_link(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__first_image_link(cause, this);
}
export_cefunk1(movie__first_image_link, thing, 0, "Returns the first_image_link of the movie.");


f2ptr raw__movie__first_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "first_image_link"), value);
}

f2ptr f2__movie__first_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__first_image_link__set(cause, this, value);
}
export_cefunk2(movie__first_image_link__set, thing, value, 0, "Sets the first_image_link of the movie.");


f2ptr raw__movie__last_image_link(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "last_image_link"), nil);
}

f2ptr f2__movie__last_image_link(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__last_image_link(cause, this);
}
export_cefunk1(movie__last_image_link, thing, 0, "Returns the last_image_link of the movie.");


f2ptr raw__movie__last_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "last_image_link"), value);
}

f2ptr f2__movie__last_image_link__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__last_image_link__set(cause, this, value);
}
export_cefunk2(movie__last_image_link__set, thing, value, 0, "Sets the last_image_link of the movie.");


f2ptr raw__movie__images(f2ptr cause, f2ptr this) {
  return f2__frame__lookup_var_value(cause, this, new__symbol(cause, "images"), nil);
}

f2ptr f2__movie__images(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__images(cause, this);
}
export_cefunk1(movie__images, thing, 0, "Returns the images of the movie.");


f2ptr raw__movie__images__set(f2ptr cause, f2ptr this, f2ptr value) {
  return f2__frame__add_var_value(cause, this, new__symbol(cause, "images"), value);
}

f2ptr f2__movie__images__set(f2ptr cause, f2ptr this, f2ptr value) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__images__set(cause, this, value);
}
export_cefunk2(movie__images__set, thing, value, 0, "Sets the images of the movie.");


s64 raw__movie__length(f2ptr cause, f2ptr this) {
  s64 length = 0;
  f2ptr iter = raw__movie__first_image_link(cause, this);
  while (iter != nil) {
    length ++;
    iter = f2__doublelink__next(cause, iter);
  }
  return length;
}

f2ptr f2__movie__length(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return f2integer__new(cause, raw__movie__length(cause, this));
}
export_cefunk1(movie__length, this, 0, "Returns the number of images in the image sequence.");


f2ptr raw__movie__width(f2ptr cause, f2ptr this) {
  f2ptr width = nil;
  f2ptr iter = raw__movie__first_image_link(cause, this);
  if (iter != nil) {
    f2ptr image = f2__doublelink__value(cause, iter);
    width = raw__image__width(cause, image);
  }
  return width;
}

f2ptr f2__movie__width(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__width(cause, this);
}
export_cefunk1(movie__width, this, 0, "Returns the width of all of the images in the sequence, or nil if sequence is empty.");


f2ptr raw__movie__height(f2ptr cause, f2ptr this) {
  f2ptr height = nil;
  f2ptr iter = raw__movie__first_image_link(cause, this);
  if (iter != nil) {
    f2ptr image = f2__doublelink__value(cause, iter);
    height = raw__image__height(cause, image);
  }
  return height;
}

f2ptr f2__movie__height(f2ptr cause, f2ptr this) {
  if (! raw__movie__is_type(cause, this)) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__height(cause, this);
}
export_cefunk1(movie__height, this, 0, "Returns the height of all of the images in the sequence, or nil if sequence is empty.");


f2ptr raw__movie__add_image_to_end(f2ptr cause, f2ptr this, f2ptr image) {
  f2ptr width  = raw__movie__width(cause, this);
  f2ptr height = raw__movie__height(cause, this);
  s64   width__i;
  s64   height__i;
  if (width != nil) {
    width__i  = f2integer__i(width,  cause);
    height__i = f2integer__i(height, cause);
    f2ptr image__width     = raw__image__width( cause, image);
    f2ptr image__height    = raw__image__height(cause, image);
    s64   image__width__i  = f2integer__i(image__width,  cause);
    s64   image__height__i = f2integer__i(image__height, cause);
    if ((width__i  != image__width__i) ||
	(height__i != image__height__i)) {
      return f2larva__new(cause, 3, nil);
    }
  }
  f2ptr last_image_link = raw__movie__last_image_link(cause, this);
  f2ptr link = f2__doublelink__new(cause, last_image_link, nil, image);
  if (last_image_link == nil) {
    f2__movie__images__set(          cause, this, link);
    f2__movie__first_image_link__set(cause, this, link);
  } else {
    f2__doublelink__next__set(cause, last_image_link, link);
  }
  f2__movie__last_image_link__set(cause, this, link);
  return nil;
}

f2ptr f2__movie__add_image_to_end(f2ptr cause, f2ptr this, f2ptr image) {
  if ((! raw__movie__is_type(cause, this)) ||
      (! raw__image__is_type(cause, image))) {
    return f2larva__new(cause, 1, nil);
  }
  return raw__movie__add_image_to_end(cause, this, image);
}
export_cefunk2(movie__add_image_to_end, this, image, 0, "Adds an image to the end of the image sequence.  The image must be the same dimensions as the other images in the sequence.");


f2ptr raw__movie__elt(f2ptr cause, f2ptr this, s64 index) {
  if (index < 0) {
    return f2larva__new(cause, 2, nil);
  }
  s64   count = 0;
  f2ptr iter  = f2__movie__first_image_link(cause, this);
  while (iter != nil) {
    f2ptr image = f2__doublelink__value(cause, iter);
    if (count == index) {
      return image;
    }
    count ++;
    iter = f2__doublelink__next(cause, iter);
  }
  return f2larva__new(cause, 2, nil);
}

f2ptr f2__movie__elt(f2ptr cause, f2ptr this, f2ptr index) {
  if ((! raw__movie__is_type(cause, this)) ||
      (! raw__integer__is_type(cause, index))) {
    return f2larva__new(cause, 1, nil);
  }
  s64 index__i = f2integer__i(index, cause);
  return raw__movie__elt(cause, this, index__i);
}
export_cefunk2(movie__elt, this, index, 0, "Returns an image from the sequence.  Indices start at zero.");


f2ptr f2__movie_type__new(f2ptr cause) {
  f2ptr this = f2__primobject_type__new(cause, f2list1__new(cause, new__symbol(cause, "frame")));
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "new"),              f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__new")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "is_type"),          f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__is_type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "type"),             f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__type")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "first_image_link"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__first_image_link")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "first_image_link"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__first_image_link__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "last_image_link"),  f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__last_image_link")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "last_image_link"),  f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__last_image_link__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "images"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__images")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.set__symbol,     new__symbol(cause, "images"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__images__set")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "length"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__length")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "width"),            f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__width")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "height"),           f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__height")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.execute__symbol, new__symbol(cause, "add_image_to_end"), f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__add_image_to_end")));}
  {f2__primobject_type__add_slot_type(cause, this, __funk2.globalenv.get__symbol,     new__symbol(cause, "elt"),              f2__core_extension_funk__new(cause, new__symbol(cause, "movie"), new__symbol(cause, "movie__elt")));}
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



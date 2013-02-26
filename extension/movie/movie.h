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

#ifndef F2__EXTENSION__MOVIE__H
#define F2__EXTENSION__MOVIE__H

#include "../../c/funk2.h"

typedef struct funk2_movie_context_s funk2_movie_context_t;
struct funk2_movie_context_s {
#ifdef F2__LIBAVCODEC_SUPPORTED
  s64                width;
  s64                height;
  AVCodec*           av_codec;
  AVCodecContext*    av_codec_context;
  AVFrame*           rgb_picture_frame;
  s64                rgb_picture_frame__size;
  u8*                rgb_picture_frame__buffer;
  AVFrame*           yuv_picture_frame;
  s64                yuv_picture_frame__size;
  u8*                yuv_picture_frame__buffer;
  struct SwsContext* image_convert_context;
  s64                out_buffer_size;
  u8*                out_buffer;
#endif // F2__LIBAVCODEC_SUPPORTED
};

f2ptr raw__libavcodec__video_chunk__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence);
f2ptr  f2__libavcodec__video_chunk__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence);

f2ptr     raw__movie__new                    (f2ptr cause, f2ptr video_chunk);
f2ptr      f2__movie__new                    (f2ptr cause, f2ptr video_chunk);
boolean_t raw__movie__is_type                (f2ptr cause, f2ptr thing);
f2ptr      f2__movie__is_type                (f2ptr cause, f2ptr thing);
f2ptr     raw__movie__type                   (f2ptr cause, f2ptr this);
f2ptr      f2__movie__type                   (f2ptr cause, f2ptr this);
f2ptr     raw__movie__video_chunk            (f2ptr cause, f2ptr this);
f2ptr      f2__movie__video_chunk            (f2ptr cause, f2ptr this);
f2ptr     raw__movie__video_chunk__set       (f2ptr cause, f2ptr this, f2ptr value);
f2ptr      f2__movie__video_chunk__set       (f2ptr cause, f2ptr this, f2ptr value);
f2ptr     raw__movie__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence);
f2ptr      f2__movie__new_from_image_sequence(f2ptr cause, f2ptr movie_context, f2ptr image_sequence);
f2ptr     raw__movie__save                   (f2ptr cause, f2ptr this, f2ptr filename);
f2ptr      f2__movie__save                   (f2ptr cause, f2ptr this, f2ptr filename);

f2ptr f2__movie_type__new(f2ptr cause);

// **

f2ptr f2__movie__core_extension__ping      (f2ptr cause);
f2ptr f2__movie__core_extension__initialize(f2ptr cause);
f2ptr f2__movie__core_extension__destroy   (f2ptr cause);


#endif // F2__EXTENSION__MOVIE__H


// 
// Copyright (c) 2007-2009 Bo Morgan.
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

#include "funk2.h"

#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#  include <fcntl.h>
#  include <io.h>
#  define SET_BINARY_MODE(file) setmode(fileno(file), O_BINARY)
#else
#  define SET_BINARY_MODE(file)
#endif

#define CHUNK 16384

// Compress from file source to file dest until EOF on source.
// def() returns Z_OK on success, Z_MEM_ERROR if memory could not be
// allocated for processing, Z_STREAM_ERROR if an invalid compression
// level is supplied, Z_VERSION_ERROR if the version of zlib.h and the
// version of the library linked do not match, or Z_ERRNO if there is
// an error reading or writing the files.
int zlib__deflate__stream_to_stream(int source_fd, int dest_fd, int level) {
  int ret, flush;
  f2size_t have;
  z_stream strm;
  unsigned char in[CHUNK];
  unsigned char out[CHUNK];
  
  // allocate deflate state
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  ret = deflateInit(&strm, level);
  if (ret != Z_OK) {
    return ret;
  }
  
  // compress until end of file
  do {
    strm.avail_in = raw_read(source_fd, in, CHUNK);
    if (strm.avail_in == -1) {
      (void)deflateEnd(&strm);
      return Z_ERRNO;
    }
    if (strm.avail_in == 0) {
      flush = Z_FINISH;
    } else {
      flush = Z_NO_FLUSH;
    }
    strm.next_in = in;
    
    // run deflate() on input until output buffer not full, finish
    // compression if all of source has been read in
    do {
      strm.avail_out = CHUNK;
      strm.next_out = out;
      ret = deflate(&strm, flush);    // no bad return value
      assert(ret != Z_STREAM_ERROR);  // state not clobbered
      have = CHUNK - strm.avail_out;
      if (raw_write(dest_fd, out, have) != have) {
	(void)deflateEnd(&strm);
	return Z_ERRNO;
      }
    } while (strm.avail_out == 0);
    assert(strm.avail_in == 0);     // all input will be used
    
    // done when last data in file processed
  } while (flush != Z_FINISH);
  assert(ret == Z_STREAM_END);        // stream will be complete
  
  // clean up and return
  (void)deflateEnd(&strm);
  return Z_OK;
}

int zlib__deflate__stream_to_memory(FILE *source, FILE *dest, int level) {
  int ret, flush;
  unsigned have;
  z_stream strm;
  unsigned char in[CHUNK];
  unsigned char out[CHUNK];
  
  // allocate deflate state
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  ret = deflateInit(&strm, level);
  if (ret != Z_OK) {
    return ret;
  }
  
  // compress until end of file
  do {
    strm.avail_in = fread(in, 1, CHUNK, source);
    if (ferror(source)) {
      (void)deflateEnd(&strm);
      return Z_ERRNO;
    }
    flush = feof(source) ? Z_FINISH : Z_NO_FLUSH;
    strm.next_in = in;
    
    // run deflate() on input until output buffer not full, finish
    // compression if all of source has been read in
    do {
      strm.avail_out = CHUNK;
      strm.next_out = out;
      ret = deflate(&strm, flush);    // no bad return value
      assert(ret != Z_STREAM_ERROR);  // state not clobbered
      have = CHUNK - strm.avail_out;
      if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
	(void)deflateEnd(&strm);
	return Z_ERRNO;
      }
    } while (strm.avail_out == 0);
    assert(strm.avail_in == 0);     // all input will be used
    
    // done when last data in file processed
  } while (flush != Z_FINISH);
  assert(ret == Z_STREAM_END);        // stream will be complete
  
  // clean up and return
  (void)deflateEnd(&strm);
  return Z_OK;
}

// Decompress from file source to file dest until stream ends or EOF.
// inf() returns Z_OK on success, Z_MEM_ERROR if memory could not be
// allocated for processing, Z_DATA_ERROR if the deflate data is
// invalid or incomplete, Z_VERSION_ERROR if the version of zlib.h and
// the version of the library linked do not match, or Z_ERRNO if there
// is an error reading or writing the files.
int zlib__inflate__stream_to_stream(FILE *source, FILE *dest) {
  int ret;
  unsigned have;
  z_stream strm;
  unsigned char in[CHUNK];
  unsigned char out[CHUNK];
  
  // allocate inflate state
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  strm.avail_in = 0;
  strm.next_in = Z_NULL;
  ret = inflateInit(&strm);
  if (ret != Z_OK) {
    return ret;
  }
  
  // decompress until deflate stream ends or end of file
  do {
    strm.avail_in = fread(in, 1, CHUNK, source);
    if (ferror(source)) {
      (void)inflateEnd(&strm);
      return Z_ERRNO;
    }
    if (strm.avail_in == 0) {
      break;
    }
    strm.next_in = in;
    
    // run inflate() on input until output buffer not full
    do {
      strm.avail_out = CHUNK;
      strm.next_out = out;
      ret = inflate(&strm, Z_NO_FLUSH);
      assert(ret != Z_STREAM_ERROR);  // state not clobbered
      switch (ret) {
      case Z_NEED_DICT:
	ret = Z_DATA_ERROR;     // and fall through
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
	(void)inflateEnd(&strm);
	return ret;
      }
      have = CHUNK - strm.avail_out;
      if (fwrite(out, 1, have, dest) != have || ferror(dest)) {
	(void)inflateEnd(&strm);
	return Z_ERRNO;
      }
    } while (strm.avail_out == 0);
    
    // done when inflate() says it's done
  } while (ret != Z_STREAM_END);
  
  // clean up and return
  (void)inflateEnd(&strm);
  return (ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR);
}

// report a zlib or i/o error
void zlib__report_error(int ret) {
  fputs("zpipe: ", stderr);
  switch (ret) {
  case Z_ERRNO:
    if (ferror(stdin)) {
      fputs("error reading stdin\n", stderr);
    }
    if (ferror(stdout)) {
      fputs("error writing stdout\n", stderr);
    }
    break;
  case Z_STREAM_ERROR:
    fputs("invalid compression level\n", stderr);
    break;
  case Z_DATA_ERROR:
    fputs("invalid or incomplete deflate data\n", stderr);
    break;
  case Z_MEM_ERROR:
    fputs("out of memory\n", stderr);
    break;
  case Z_VERSION_ERROR:
    fputs("zlib version mismatch!\n", stderr);
    break;
  }
}


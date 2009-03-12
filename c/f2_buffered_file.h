#ifndef F2__BUFFERED_FILE__H
#define F2__BUFFERED_FILE__H

#include "f2_circular_buffer.h"

typedef struct buffered_file_s {
  int               fd;
  boolean_t         end_of_file;
  circular_buffer_t read_buffer;
  circular_buffer_t write_buffer;
} buffered_file_t;

void                            buffered_file__init(buffered_file_t* this, int fd, u32 read_buffer__byte_num, u32 write_buffer__byte_num);
void                            buffered_file__destroy(buffered_file_t* this);
void                            buffered_file__flush(buffered_file_t* this);
circular_buffer__write_result_t buffered_file__write(buffered_file_t* this, void* data, u32 byte_num);
void                            buffered_file__seek_ahead(buffered_file_t* this, u32 byte_num);
circular_buffer__read_result_t  buffered_file__peek_read(buffered_file_t* this, void* data, u32 byte_num);
circular_buffer__read_result_t  buffered_file__read(buffered_file_t* this, void* data, u32 byte_num);
u32                             buffered_file__read_bytes_buffered(buffered_file_t* this);
u32                             buffered_file__read_bytes_free(buffered_file_t* this);
u32                             buffered_file__write_bytes_buffered(buffered_file_t* this);
u32                             buffered_file__write_bytes_free(buffered_file_t* this);

#endif // F2__BUFFERED_FILE__H

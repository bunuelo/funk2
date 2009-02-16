#include "funk2.h"

void buffered_file__init(buffered_file_t* this, int fd, u32 read_buffer__byte_num, u32 write_buffer__byte_num) {
  this->fd          = fd;
  this->end_of_file = false;
  circular_buffer__init(&(this->read_buffer),  read_buffer__byte_num);
  circular_buffer__init(&(this->write_buffer), write_buffer__byte_num);
}

void buffered_file__destroy(buffered_file_t* this) {
  circular_buffer__destroy(&(this->read_buffer));
  circular_buffer__destroy(&(this->write_buffer));
}

void buffered_file__flush(buffered_file_t* this) {
  if (! this->end_of_file) {
    circular_buffer__file_read_result_t read_result = circular_buffer__file_read(&(this->read_buffer), this->fd);
    switch(read_result) {
    case circular_buffer__file_read_result__end_of_file: this->end_of_file = true; break;
    case circular_buffer__file_read_result__success:                               break;
    }
    if (! this->end_of_file) {
      circular_buffer__file_write_result_t write_result = circular_buffer__file_write(&(this->write_buffer), this->fd);
      switch(write_result) {
      case circular_buffer__file_write_result__end_of_file: this->end_of_file = true; break;
      case circular_buffer__file_write_result__success:                               break;
      }
    }
  }
}

circular_buffer__write_result_t buffered_file__write(buffered_file_t* this, void* data, u32 byte_num) {
  return circular_buffer__write(&(this->write_buffer), data, byte_num);
}

void buffered_file__seek_ahead(buffered_file_t* this, u32 byte_num) {
  circular_buffer__seek_ahead(&(this->read_buffer), byte_num, NULL);
}

circular_buffer__read_result_t buffered_file__peek_read(buffered_file_t* this, void* data, u32 byte_num) {
  return circular_buffer__peek_read(&(this->read_buffer), data, byte_num, NULL);
}

circular_buffer__read_result_t buffered_file__read(buffered_file_t* this, void* data, u32 byte_num) {
  return circular_buffer__read(&(this->read_buffer), data, byte_num);
}

u32 buffered_file__read_bytes_free(buffered_file_t* this) {
  return circular_buffer__get_free_byte_num(&(this->read_buffer));
}

u32 buffered_file__read_bytes_buffered(buffered_file_t* this) {
  return circular_buffer__get_used_byte_num(&(this->read_buffer));
}

u32 buffered_file__write_bytes_free(buffered_file_t* this) {
  return circular_buffer__get_free_byte_num(&(this->write_buffer));
}

u32 buffered_file__write_bytes_buffered(buffered_file_t* this) {
  return circular_buffer__get_used_byte_num(&(this->write_buffer));
}


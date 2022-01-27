#include "ring_buffer.h"

uint8_t ring_buffer_length(struct ring_buffer* r) {
  return ((r->lead_ptr >= r->follow_ptr) ? (r->lead_ptr - r->follow_ptr) :  (0x100 - r->follow_ptr + r->lead_ptr));
}

void ring_buffer_save_point(struct ring_buffer* r) {
  r->save_ptr = r->follow_ptr;
}

void ring_buffer_revert_save_point(struct ring_buffer* r) {
  r->follow_ptr = r->save_ptr;
}

int ring_buffer_index(struct ring_buffer* r, uint8_t idx) {
  return (idx < ring_buffer_length(r)) ? (int)r->buffer[(r->follow_ptr+idx)&0xFF] : (int)OUT_OF_RANGE;
}

void ring_buffer_reset(struct ring_buffer* r) {
  r->lead_ptr   = 0;
  r->follow_ptr = 0;
}

int ring_buffer_push(struct ring_buffer* r, uint8_t const data) {
  if ((uint8_t)(r->follow_ptr - r->lead_ptr) == 1) {
    return (int)NO_SPACE;
  } else {
    r->buffer[r->lead_ptr++] = data;
    return (int)OK;
  }
}

uint8_t ring_buffer_index_with_offset(struct ring_buffer const* r, uint8_t idx, uint8_t offset)
{
    return r->buffer[(offset+idx) & 0xFF];
}


int ring_buffer_pop(struct ring_buffer* r) {
  return (r->lead_ptr == r->follow_ptr) ? (int)NOT_FOUND : (int)r->buffer[r->follow_ptr++];
}

uint8_t ring_accessor_get(ring_accessor_t* r , uint8_t idx) {
  return r->buffer[(r->ptr + idx)&0xFF];
}



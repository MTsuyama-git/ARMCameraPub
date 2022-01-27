#include "ring_buffer.h"
#include <stdlib.h>
#include <string.h>

void ring_buffer_init(ring_buffer* rb) {
    rb->buffer = (uint8_t*)malloc(sizeof(uint8_t) * BUFFER_LENGTH);
    rb->save_ptr = rb-> lead_ptr = rb->follow_ptr = 0;
}

void ring_buffer_push(ring_buffer* rb, uint8_t x) {
    rb->buffer[rb->lead_ptr++] = x;
    rb->lead_ptr %= BUFFER_LENGTH;
}

void ring_buffer_bulk_push(ring_buffer* rb, const uint8_t* buffer, uint8_t len) {
    if(rb->lead_ptr + len < BUFFER_LENGTH) {
        memcpy(&(rb->buffer[rb->lead_ptr]), buffer, len);
        rb->lead_ptr += len;
    }
    else {
        uint8_t remain = (rb->lead_ptr + len - BUFFER_LENGTH);
        memcpy(&(rb->buffer[rb->lead_ptr]), buffer, len - remain);
        memcpy(rb->buffer, buffer, remain);
        rb->lead_ptr = remain;
        
    }
}

int ring_buffer_pop(ring_buffer* rb) {
    if(rb->lead_ptr == rb->follow_ptr)
        return NOT_FOUND;
    uint8_t result = rb->buffer[rb->follow_ptr++];
    rb->follow_ptr %= BUFFER_LENGTH;
    return (int)result;
}

void ring_buffer_revert(ring_buffer* rb) {
    rb->follow_ptr = rb->save_ptr;
}

void ring_buffer_save_ptr(ring_buffer* rb) {
    rb->save_ptr = rb->follow_ptr;
}




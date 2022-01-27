#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

#include "main.h"

#define BUFFER_LENGTH 255

#define NOT_FOUND -1

typedef struct ring_buffer ring_buffer;

struct ring_buffer {
    uint8_t* buffer;
    uint8_t save_ptr;
    uint8_t lead_ptr;
    uint8_t follow_ptr;
};

void ring_buffer_init(ring_buffer*);
void ring_buffer_push(ring_buffer*, uint8_t);
void ring_buffer_bulk_push(ring_buffer*, const uint8_t*, uint8_t);
int  ring_buffer_pop(ring_buffer*);
void ring_buffer_revert(ring_buffer*);
void ring_buffer_save_ptr(ring_buffer*);


#endif

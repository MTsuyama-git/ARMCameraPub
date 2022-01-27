#ifndef __RING_BUFFER_H
#define __RING_BUFFER_H

#include <string.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"
typedef enum ring_buffer_result {
    RING_BUFFER_NOT_FOUND    = -1,
    RING_BUFFER_OK           = 0,
    RING_BUFFER_NO_SPACE     = 1,
    RING_BUFFER_OUT_OF_RANGE = 2,
} ring_buffer_result_t;

struct ring_buffer {
  uint8_t *buffer;
  uint8_t lead_ptr;
  uint8_t follow_ptr;
  uint8_t save_ptr;
};

typedef struct  ring_accessor {
  uint8_t * buffer;
  uint8_t ptr;
}ring_accessor_t;

enum parser_state {
  PREAMBLE_1     = 0x00,
  PREAMBLE_2     = 0x01,
  TYPE           = 0x02,
  SENDER_ID      = 0x03,
  DESTINATION_ID = 0x04,
  PACKET_ID      = 0x05,
  OPERATOR       = 0x06,
  LENGTH         = 0x07,
  DATA           = 0x08,
  CRC_1          = 0x09,
  CRC_2          = 0x0A,
  CRC_3          = 0x0B,
  CRC_4          = 0x0C,
};

enum result {
  OK           =  0,
  NOT_FOUND    = -1,
  OUT_OF_RANGE = -2,
  NO_SPACE     = -3,
    };



 uint8_t ring_buffer_length(struct ring_buffer* );
 void ring_buffer_save_point(struct ring_buffer* );
 void ring_buffer_revert_save_point(struct ring_buffer* );
 int ring_buffer_index(struct ring_buffer*, uint8_t );
uint8_t ring_buffer_index_with_offset(struct ring_buffer const*, uint8_t, uint8_t);
 void ring_buffer_reset(struct ring_buffer* );
 int ring_buffer_push(struct ring_buffer* , uint8_t const );
 int ring_buffer_pop(struct ring_buffer*);

void ring_accessor_set_buffer(ring_accessor_t* , uint8_t* );
uint8_t* ring_accessor_get_buffer(ring_accessor_t* );
void ring_accessor_set_ptr(ring_accessor_t* , uint8_t );
 uint8_t ring_accessor_get(ring_accessor_t* , uint8_t );

#endif

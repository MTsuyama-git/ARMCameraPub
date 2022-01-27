#ifndef __PACKET_H
#define __PACKET_H
#include "ring_buffer.h"

void parse_packet(ring_buffer*);
void packet_parser_bulk_push(ring_buffer*, uint8_t const*, uint32_t*);

#endif

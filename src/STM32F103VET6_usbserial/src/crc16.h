#ifndef _CRC16_H
#define _CRC16_H

#include "ring_buffer.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_tim.h"

uint16_t calc_crc16(uint8_t const *ptr, uint32_t len);
uint16_t calc_crc16_simple(uint8_t const *ptr, uint32_t len);
uint16_t calc_crc16_ring_accessor(ring_accessor_t* r, uint32_t len);
#endif

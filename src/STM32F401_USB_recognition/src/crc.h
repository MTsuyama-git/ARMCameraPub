#ifndef __CRC_H

#define __CRC_H
#include "stm32f4xx_hal.h"

void CRC_Init(void);
void CRC_DeInit(void);
uint32_t calc_crc32(uint32_t* address, uint32_t size_in_byte);

#endif

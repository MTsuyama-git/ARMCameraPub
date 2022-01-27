/* https://crccalc.com/?crc=0xAA 0x55 0x00 0x00 0x01 0x00 0x01 0x00&method=crc32&datatype=hex&outtype=hex */
/* https://crccalc.com/?crc=0x00001111 0x00002222 0x00003333 0x00004444&method=crc32&datatype=hex&outtype=hex */

#include "crc.h"

CRC_HandleTypeDef hcrc;


void CRC_Init(void)
{
    __HAL_RCC_CRC_CLK_ENABLE();
  hcrc.Instance = CRC;
  HAL_CRC_Init(&hcrc);
  CRC->CR |= CRC_CR_RESET;
  /* if (HAL_CRC_Init(&hcrc) != HAL_OK) */
  /* { */
  /*   Error_Handler(); */
  /* } */

}


void CRC_DeInit(void) {
    __HAL_RCC_CRC_CLK_DISABLE();
    hcrc.Instance = CRC;
    HAL_CRC_DeInit(&hcrc);
}

uint32_t calc_crc32(uint32_t* address, uint32_t size_in_byte)
{
    return ~HAL_CRC_Calculate(&hcrc, address, size_in_byte);
}

/* uint32_t calc_crc32(uint32_t* address, uint32_t size_in_byte) */
/* { */
/*     int i; */
/*     CRC->CR |= CRC_CR_RESET; */
/*     for (i = 0; i < size_in_byte; ++i) { */
/*         CRC->DR = __REV(~address[i]); */
/*     } */
/*     return (__REV(CRC->DR) ^ 0xFFFFFFFF); */
/*     return ~(HAL_CRC_Calculate(&hcrc, address, size_in_byte)); */
/* } */

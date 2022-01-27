#ifndef __UART_H
#define __UART_H


#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32f4xx_hal.h"

void UART_Init(uint8_t**buf);
void USART2_IRQHandler(void);
void uart_interrupted(USART_TypeDef *, uint8_t);
size_t uart_send_downstream(uint8_t const* , size_t const);
#ifdef __cplusplus
}
#endif

#endif

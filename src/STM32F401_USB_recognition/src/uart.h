#ifndef __UART_H
#define __UART_H
#include "stm32f4xx_hal.h"
#include "stm32f4xx_it.h"
#include "main.h"
#include "ring_buffer.h"

#define RX_BUFFER_LEN 255

void UART_Init(uint8_t*, void(*_uart_handler)(void));
void uart_interrupted(USART_TypeDef *, uint8_t);
void puts0(USART_TypeDef*, uint8_t);
void biputs0(USART_TypeDef*, uint16_t);
#endif

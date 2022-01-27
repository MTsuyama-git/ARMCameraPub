#ifndef __UART_H
#define __UART_H

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "stm32f1xx_hal.h"

void UART4_IRQHandler(void);
void uart_interrupted(USART_TypeDef *, uint8_t);


#ifdef __cplusplus
}
#endif

#endif

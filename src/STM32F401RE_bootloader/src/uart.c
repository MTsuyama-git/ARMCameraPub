#include "uart.h"

static void USART2_Init(void);

extern uint8_t uart_rx_buffer_ptr;

uint8_t** uart_rx_buffer;

void UART_Init(uint8_t**buf) {
    uart_rx_buffer = buf;
    USART2_Init();
}

static void USART2_Init(void)
{
    IRQn_Type irq;
    UART_HandleTypeDef huart;
  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart.Instance = USART2;
  huart.Init.BaudRate = 115200;
  huart.Init.WordLength = UART_WORDLENGTH_8B;
  huart.Init.StopBits = UART_STOPBITS_1;
  huart.Init.Parity = UART_PARITY_NONE;
  huart.Init.Mode = UART_MODE_TX_RX;
  huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  USART2->CR1 |= USART_CR1_RXNEIE;
  USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
  USART2->CR3 = 0;
  USART2->CR2 = 0;
  /* USART2->CR1|= USART_CR1_IDLEIE | USART_CR1_TCIE | USART_CR1_RXNEIE | USART_CR1_TXEIE | USART_CR1_PEIE; */
  /* USART2->CR2|= USART_CR2_CLKEN; */
  irq = USART2_IRQn;
  HAL_NVIC_SetPriority(irq, 31,3);
  NVIC_EnableIRQ(irq);
  /* USER CODE END USART2_Init 2 */

}

void USART2_IRQHandler(void) {
    uart_interrupted(USART2, 2);
}

void uart_interrupted(USART_TypeDef * uart, uint8_t uartIndex)
{
    if (uart->SR & USART_SR_RXNE) {
        // data received
        while(uart->SR & USART_SR_RXNE) {
            uint8_t data =uart->DR;
            uart_rx_buffer[uart_rx_buffer_ptr++] = (data);
        }
        /* for(int i = 0; i < uart_rx_buffer_ptr; ++i) { */
        /*     while((uart->SR & USART_SR_TXE)==0); */
        /*     uart->DR = uart_rx_buffer[i]; */
        /* } */
        /* uart_rx_buffer_ptr = 0; */
        /* while((uart->SR & USART_SR_TXE)==0); */
        /* uart->DR = data; */
        /* USART2->CR1 |= USART_CR1_TCIE; */
    } else if (uart->SR & USART_SR_ORE) {
        // over run error
        uart->SR |= USART_SR_ORE;
    } else if (uart->SR & USART_SR_TC) {
        // transmission complete
        uart->CR1 |= USART_CR1_TCIE;
        // Router_didTransmitToUSARTOneByteComplete();
    } else if (uart->SR & USART_SR_PE){
        // parity error
        // but this is never called because CR1.PEIE is always 0;
        uart->CR1 |= USART_CR1_PCE;
    } else if (uart->SR & USART_SR_IDLE){
        // should be tihs never called
        uart->CR1 |= USART_CR1_IDLEIE;
    } /* else if (uart->SR & USART_SR_EOBF){ */
    /*     // should be tihs never called */
    /*     uart->ICR |= USART_CR1_EOBCF; */
    /* } else if (uart->SR & USART_SR_CMF){ */
    /*     // should be tihs never called */
    /*     uart->ICR |= USART_ICR_CMCF; */
    /* }  */else {

        /* unsigned int i,ii; */
    	/* char text[60]; */
    	/* const char *t = "unknown uart interrupt"; */
    	/* for (i=0;i<23;i++) { */
    	/* 	text[i] = t[i]; */
    	/* } */
    	/* text[i++] = '['; */
    	/* text[i++] = '0' + uartIndex; */
    	/* text[i++] = ']'; */
    	/* for (ii=0;ii<32;ii++) { */
		/* 	text[i+ii] = ((uart->SR & (1 << ii)) != 0) ? '1' : '0'; */
		/* } */
    	/* i+=32; */
    	/* text[i] = '\0'; */
        /* PANIC("%s", text); */

        return;
    }
    return;
}

size_t uart_send_downstream(uint8_t const* data, size_t const len) {
    for (size_t i = 0; i < len; i++) {
        while ((USART2->SR & USART_SR_TXE) == 0);
        USART2->DR = data[i];
    }
    return len;
}

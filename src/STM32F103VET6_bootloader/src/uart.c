#include "uart.h"

extern uint8_t uart_rx_buffer_ptr;
uint8_t** uart_rx_buffer;

void UART_Init(uint8_t**buf) {
    uart_rx_buffer = buf;
    UART4_Init();
}

static void UART4_Init(void)
{
    IRQn_Type irq;
    UART_HandleTypeDef huart4;

    huart4.Instance = UART4; // PC10: TX, PC11: RX
    huart4.Init.BaudRate = 115200;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart4) != HAL_OK)
    {
        Error_Handler();
    }

    UART4->CR1 |= USART_CR1_TCIE;  // clear interrupt flag
    UART4->CR1 |=USART_CR1_RE | USART_CR1_TE;
    NVIC_SetPriority(irq, 0x00); // highest priority
    NVIC_EnableIRQ(irq);

}

void UART4_IRQHandler(void) {
    uart_interrupted(UART4, 4);
}

void uart_interrupted(USART_TypeDef * uart, uint8_t uartIndex)
{
    if (uart->SR & USART_SR_RXNE) {
        // data received
        uint8_t data =uart->DR;
        uart_rx_buffer[uart_rx_buffer_ptr++] = data;
        /* while((uart->ISR & USART_ISR_TXE)==0); */
        /* uart->TDR = data; */
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

        unsigned int i,ii;
    	char text[60];
    	const char *t = "unknown uart interrupt";
    	for (i=0;i<23;i++) {
    		text[i] = t[i];
    	}
    	text[i++] = '[';
    	text[i++] = '0' + uartIndex;
    	text[i++] = ']';
    	for (ii=0;ii<32;ii++) {
			text[i+ii] = ((uart->SR & (1 << ii)) != 0) ? '1' : '0';
		}
    	i+=32;
    	text[i] = '\0';
        /* PANIC("%s", text); */

        return;
    }
    return;
}

size_t uart_send_downstream(uint8_t const* data, size_t const len) {
    for (size_t i = 0; i < len; i++) {
        while ((UART4->SR & USART_SR_TXE) == 0);
        UART4->DR = data[i];
    }
    return len;
}

#include "uart.h"
extern uint8_t led;

void UART4_IRQHandler(void) {
    uart_interrupted(UART4, 4);
}

void uart_interrupted(USART_TypeDef * uart, uint8_t uartIndex)
{
    if (uart->SR & USART_SR_RXNE) {
        // data received
        uint8_t data =uart->DR;
        /* uart_rx_buffer[uartIndex-1][uart_rx_buffer_ptr[uartIndex-1]++] = data; */
        /* while((uart->SR & USART_SR_TXE)==0); */
        while ((uart->SR & USART_SR_RXNE));
        uart->CR1|=USART_CR1_TE;
        while (!(uart->SR & USART_SR_TXE));
        uart->DR = data;
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

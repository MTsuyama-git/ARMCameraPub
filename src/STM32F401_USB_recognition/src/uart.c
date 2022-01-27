#include "uart.h"

static void USART2_Init(void);
static void USART6_Init(void);
static void USART1_Init(void);

static void(*uart_handler)(void);

extern uint8_t led;
extern uint8_t uart_rx_buffer_ptr;
uint8_t* uart_rx_buffer;


void UART_Init(uint8_t* _uart_rx_buffer, void(*_uart_handler)(void)) {
    uart_handler = _uart_handler;
    uart_rx_buffer = _uart_rx_buffer;
    uart_rx_buffer_ptr = 0;
    USART2_Init();
    /* USART6_Init(); */
    /* USART1_Init(); */
}


/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void USART2_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
    IRQn_Type irq;
    UART_HandleTypeDef huart;
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
  USART2->CR1 |= USART_CR1_RXNEIE;
  USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
  USART2->CR3 = 0;
  USART2->CR2 = 0;
  /* USER CODE BEGIN USART2_Init 2 */
  irq = USART2_IRQn;
  HAL_NVIC_SetPriority(irq, 31,3);
  NVIC_EnableIRQ(irq);
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void USART6_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
    IRQn_Type irq;
    UART_HandleTypeDef huart;
  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart.Instance = USART6;
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
  USART6->CR1 |= USART_CR1_RXNEIE;
  USART6->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
  USART6->CR3 = 0;
  USART6->CR2 = 0;
  /* USER CODE BEGIN USART2_Init 2 */
  irq = USART6_IRQn;
  HAL_NVIC_SetPriority(irq, 31,3);
  NVIC_EnableIRQ(irq);
  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void USART1_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */
    IRQn_Type irq;
    UART_HandleTypeDef huart;
  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart.Instance = USART1;
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
  USART1->CR1 |= USART_CR1_RXNEIE;
  USART1->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
  USART1->CR3 = 0;
  USART1->CR2 = 0;
  /* USER CODE BEGIN USART2_Init 2 */
  irq = USART1_IRQn;
  HAL_NVIC_SetPriority(irq, 31,3);
  NVIC_EnableIRQ(irq);
  /* USER CODE END USART2_Init 2 */

}

void USART1_IRQHandler(void) {
    uart_interrupted(USART1, 2);
}

void USART2_IRQHandler(void) {
    uart_interrupted(USART2, 2);
}

void USART6_IRQHandler(void) {
    led = 1;
    uart_interrupted(USART6, 2);
}


void uart_interrupted(USART_TypeDef * uart, uint8_t uartIndex)
{
    if (uart->SR & USART_SR_RXNE) {
        // data received
        while(uart->SR & USART_SR_RXNE) {
            uint8_t data =uart->DR;
            uart_rx_buffer[uart_rx_buffer_ptr++] = data;
            uart_handler();
        }
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
    } else {
        return;
    }
    return;
}


void puts0(USART_TypeDef *uart, uint8_t ch) {
  while((uart->SR & USART_SR_TXE) ==0);
  uart->DR=ch;
}

void biputs0(USART_TypeDef *uart, uint16_t ch) {
    puts0(uart, ch>>8);
    puts0(uart, ch&0xFF);
}

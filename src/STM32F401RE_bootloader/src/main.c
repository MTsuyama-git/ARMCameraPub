/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
******************************************************************************
* @attention
*
* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
* All rights reserved.</center></h2>
*
* This software component is licensed by ST under Ultimate Liberty license
* SLA0044, the "License"; You may not use this file except in compliance with
* the License. You may obtain a copy of the License at:
*                             www.st.com/SLA0044
*
******************************************************************************
*/
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"
#include "crc.h"
#include "gpio.h"
#include "uart.h"
#include "packet.h"
#include "ring_buffer.h"
#include "partition.h"
#include "dispatcher.h"
#include "nvs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
const char* buf="Hello\r\n";
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t USB_rx_buffer[0x200];
static uint8_t uart_tx_buffer[0x100];
static int8_t uart_rx_buffer[0x100];
volatile uint8_t uart_tx_buffer_ptr = 0;
volatile uint8_t uart_rx_buffer_ptr = 0;
volatile uint8_t USB_rx_buffer_lead_ptr;
volatile uint8_t gSystemInitialized = 0;
uint8_t led = 0;
extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE END PV */
#define ENABLE_BOOTLOADER_PROTECTION 0
#define PAGES_TO_PROTECT (OB_WRP_PAGES0TO1 | OB_WRP_PAGES2TO3 | OB_WRP_PAGES4TO5)

void __attribute__ ((noreturn,weak)) _start(void);
void CHECK_AND_SET_FLASH_PROTECTION(void);
int main(void);

typedef void (*pFunction)();

uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *) SRAM_END, // initial stack pointer
    (uint32_t *) _start,   // _start is the Reset_Handler
    (uint32_t *) NMI_Handler,
    (uint32_t *) HardFault_Handler,
    (uint32_t *) MemManage_Handler,
    (uint32_t *) BusFault_Handler,
    (uint32_t *) UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t *) SVC_Handler,
    (uint32_t *) DebugMon_Handler,
    0,
    (uint32_t *) PendSV_Handler,
    (uint32_t *) SysTick_Handler,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,              				  /* Reserved                      */                         
    0,             					  /* Reserved                     */                          
    0,                                /* Reserved                     */                          
    0,                                /* Reserved                     */                          
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    (uint32_t *) USART2_IRQHandler,                /* USART2                       */                   
    0,              				  /* Reserved                       */                   
    0,
    0,
    0,
    0,                                /* Reserved     				  */         
    0,                                /* Reserved       			  */         
    0,                                /* Reserved 					  */
    0,                                /* Reserved                     */                          
    0,
    0,                                /* Reserved                     */                   
    0,
    0,
    0,
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */
    0,
    0,
    0,
    0,
    0,
    0,                   			  /* Reserved                     */                   
    0,             					  /* Reserved                     */                     
    0,             					  /* Reserved                     */                          
    0,            					  /* Reserved                     */                          
    0,             					  /* Reserved                     */                          
    0,             					  /* Reserved                     */                          
    (uint32_t *) OTG_FS_IRQHandler,                /* USB OTG FS                   */                   
    0,
    0,
    0,
    0,
    0,
    0,
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */                         
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */
    0,
    0,                                /* Reserved                     */                   
    0,                                /* Reserved                     */
    0,
};

uint32_t const * const __nvs_flash[NVS_SIZE / 4] __attribute__((section(".nvs_flash"))) = { 0 };

// Begin address for the initialization values of the .data section.
// defined in linker script
extern uint32_t _sidata;
// Begin address for the .data section; defined in linker script
extern uint32_t _sdata;
// End address for the .data section; defined in linker script
extern uint32_t _edata;
// Begin address for the .bss section; defined in linker script
extern uint32_t _sbss;
// End address for the .bss section; defined in linker script
extern uint32_t _ebss;

inline void
__attribute__((always_inline))
__initialize_data(uint32_t* from, uint32_t* region_begin, uint32_t* region_end) {
  // Iterate and copy word by word.
  // It is assumed that the pointers are word aligned.
  uint32_t *p = region_begin;
  while (p < region_end)
    *p++ = *from++;
}

inline void
__attribute__((always_inline))
__initialize_bss(uint32_t* region_begin, uint32_t* region_end) {
  // Iterate and copy word by word.
  // It is assumed that the pointers are word aligned.
  uint32_t *p = region_begin;
  while (p < region_end)
    *p++ = 0;
}

void __attribute__ ((noreturn,weak))
_start(void) {
    __initialize_data(&_sidata, &_sdata, &_edata);
    __initialize_bss(&_sbss, &_ebss);
    main();
    for (;;);
}

void shift_buffer(uint8_t* buffer, uint8_t buffer_len, uint8_t shift_count)
{
    for (uint8_t i = 0; i < buffer_len - shift_count; i++) {
        buffer[i] = buffer[shift_count+i];
    }
}

static flasher_state_t flasher_state = NOT_IN;

int main(void);

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void main_tick_1ms()  {
}
void main_tick_5ms()  {}
void main_tick_10ms() {}
void main_tick_50ms() {
    led = 1 - led;
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, led);
    /* HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1,led); */
}
void main_tick_100ms() {}
void main_tick_500ms() {}
void main_tick_1s()   {
    /* led = 1 - led; */
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, led);
    /* while (!(UART4->SR & USART_SR_TXE)); */
    /* UART4->DR = 'a'; */
}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    GPIO_Init();
    USB_DEVICE_Init();
    CRC_Init();
    /* nvs_init(); */
    packet_parser_init();

    UART_Init(&uart_rx_buffer);
    gSystemInitialized = 1;

    char pcb_version[VERSION_MAX_LEN]   = { 0 };
    char firm_version[VERSION_MAX_LEN] = { 0 };
    uint8_t run_mode = APP_MODE;

    uint16_t size = 0;
    if (nvs_get("PCB_VER", (uint8_t*)pcb_version, &size, VERSION_MAX_LEN) == KEY_NOT_FOUND  ||
        nvs_get("FW_VER",  (uint8_t*)firm_version, &size, VERSION_MAX_LEN) == KEY_NOT_FOUND ||
        nvs_get("RUN_MODE", &run_mode, &size, 1) == KEY_NOT_FOUND)
    {
        run_mode = FLASHER_MODE;
        memcpy(pcb_version, PCB_VERSION, strlen(PCB_VERSION)+1);
        memcpy(firm_version, "__EMPTY__", 10);
        nvs_clear();
        // create
        nvs_put("PCB_VER", (uint8_t*)pcb_version, strlen(pcb_version)+1, VERSION_MAX_LEN);
        nvs_put("FW_VER",  (uint8_t*)firm_version, 10, VERSION_MAX_LEN);
        nvs_put("RUN_MODE", &run_mode, 1, 1);
        // done
        if (nvs_commit() != NVS_OK) {
            /* PANIC("flash commit failed"); */
        }
    }

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        packet_t p = { 0 };
        for(;;) {
            if (uart_rx_buffer_ptr > 0) {
                packet_parser_bulk_push(uart_rx_buffer, uart_rx_buffer_ptr);
                while (packet_parse(&p)) {
                    dispatch_packet(&p);
                }
                uart_rx_buffer_ptr = 0;
            }
            /* uart_send_downstream(uart_tx_buffer, uart_tx_buffer_ptr); */
            /* uart_tx_buffer_ptr = 0; */
            /* USB_rx_buffer_lead_ptr = 0; */
            /* USBD_CDC_ReceivePacket(&hUsbDeviceFS); */
        }
        /* if (uart_rx_buffer_ptr > 0) { */
        /*     packet_parser_bulk_push(uart_rx_buffer, uart_rx_buffer_ptr); */
        /*     while (packet_parse16(&p)) { */
        /*         p.sender_id += 1; */
        /*         USB_SendQueuePacket(&p); */
        /*     } */
        /*     uart_rx_buffer_ptr = 0; */
        /* } */
   
        /* USER CODE END WHILE */
        /* HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1); */
        /* HAL_Delay(50); */
        /* HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0); */
        /* HAL_Delay(50); */
        /* HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1); */
        /* HAL_Delay(50); */
        /* HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0); */
        /* CDC_Transmit_FS(buf, strlen(buf)); */
        /* HAL_Delay(1000); */
        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage 
     */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 72;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 3;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
}



/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */

    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{ 
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
       tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

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
#include "main.h"
#include "gpio.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "partition.h"
#include "nvs.h"
#include "uart.h"
#include "packet.h"
#include "dispatcher.h"

#define ENABLE_BOOTLOADER_PROTECTION 0
#define PAGES_TO_PROTECT (OB_WRP_PAGES0TO1 | OB_WRP_PAGES2TO3 | OB_WRP_PAGES4TO5)

typedef void (*pFunction)();

void SystemClock_Config(void);
int main(void);
void __attribute__ ((noreturn,weak)) _start(void);

uint8_t led = 0;
uint8_t USB_rx_buffer[0x200];
static uint8_t uart_tx_buffer[0x100];
static uint8_t uart_rx_buffer[0x100];
volatile uint8_t uart_tx_buffer_ptr = 0;
volatile uint8_t uart_rx_buffer_ptr = 0;
volatile uint8_t USB_rx_buffer_lead_ptr;
volatile uint8_t gSystemInitialized = 0;
extern USBD_HandleTypeDef hUsbDeviceFS;

uint32_t *vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t *)SRAM_END,
    (uint32_t *)_start,
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
    0,
    (uint32_t *) USB_LP_CAN1_RX0_IRQHandler,
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
    (uint32_t *)UART4_IRQHandler,
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

static void __attribute__ ((noreturn)) flasher_main()
{

    packet_parser_init();
#if ENABLE_BOOTLOADER_PROTECTION
    /* Ensures that the first sector of flash is write-protected preventing that the
       bootloader is overwritten */
    CHECK_AND_SET_FLASH_PROTECTION();
#endif

    flasher_state = WAITING;

    packet_t p = { 0 };

    for(;;) {
        if (USB_rx_buffer_lead_ptr > 0) {
            packet_parser_bulk_push(USB_rx_buffer, USB_rx_buffer_lead_ptr);
            while (packet_parse(&p)) {
                dispatch_packet(&p);
            }
        }
	    uart_send_downstream(uart_tx_buffer, uart_tx_buffer_ptr);
	    uart_tx_buffer_ptr = 0;
        USB_rx_buffer_lead_ptr = 0;
        USBD_CDC_ReceivePacket(&hUsbDeviceFS);
    }
	if (uart_rx_buffer_ptr > 0) {
        packet_parser_bulk_push(uart_rx_buffer, uart_rx_buffer_ptr);
        while (packet_parse16(&p)) {
            p.sender_id += 1;
            USB_SendQueuePacket(&p);
        }
        uart_rx_buffer_ptr = 0;
	}
}


static __attribute__ ((noreturn))
void jump_to_firmware()
{
    __IO uint32_t* start_address = (__IO uint32_t*)(FIRM_START_ADDRESS);
    uint32_t  jump_address = *(start_address+1);
    pFunction jump = (pFunction)(jump_address);

    CRC_DeInit();
    USB_DeInit();
    /* GPIO_DeInit(); */
    HAL_RCC_DeInit();
    HAL_DeInit();

    SysTick->CTRL = 0;
    SysTick->LOAD = 0;
    SysTick->VAL  = 0;

    __DMB(); // ARM says to use a DMB instruction before relocating VTOR
    SCB->VTOR = (uint32_t)(start_address); // relocate vector table.
    __DSB(); // ARM says to use a DSB instruction just after relocating VTOR

    __set_MSP(*start_address);
    jump();

    for (;;);
}


int main(void)
{
    HAL_Init();
    SystemClock_Config();

    GPIO_Init();
    USB_Init();
    CRC_Init();
    nvs_init();

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
    }

    if (run_mode == FLASHER_MODE) {
        flasher_main();
    } else {
        uint32_t crc      = *(((uint32_t*)FIRM_CRC_ADDRESS));
        uint32_t calc_crc = calc_crc32((uint32_t*)(FIRM_START_ADDRESS), FIRM_SIZE);
        if ((strcmp(firm_version, "__EMPTY__") != 0) && crc == calc_crc) {
            // verified
            jump_to_firmware();
        } else {
            run_mode = FLASHER_MODE;
            nvs_put("RUN_MODE", &run_mode, 1, 1);
            nvs_commit();
            NVIC_SystemReset();
        }
    }


    while (1)
    {

    }
}

void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
    PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

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
#endif 



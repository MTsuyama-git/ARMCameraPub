/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usb_device.c
  * @version        : v1.0_Cube
  * @brief          : This file implements the USB Device
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

#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"
#include "main.h"
#include "packet.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USB Device Core handle declaration. */
USBD_HandleTypeDef hUsbDeviceFS;

#define FORCE_DISCONNECT_WAIT_TIME_IN_MS 300
#define USB_BUSY_BREAK_THRESHOLD 0x07FFFF

static uint8_t USB_tx_buffer[0x200] = { 0 };
static volatile uint8_t USB_tx_buffer_lead_ptr = 0;

/*
 * -- Insert your variables declaration here --
 */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*
 * -- Insert your external function declaration here --
 */
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * Init USB device Library, add supported class and start the library
  * @retval None
  */
void USB_DEVICE_Init(void)
{
  /* USER CODE BEGIN USB_DEVICE_Init_PreTreatment */
  
  /* USER CODE END USB_DEVICE_Init_PreTreatment */
  
  /* Init Device Library, add supported class and start the library. */
  if (USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS) != USBD_OK)
  {
    Error_Handler();
  }
  if (USBD_Start(&hUsbDeviceFS) != USBD_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_DEVICE_Init_PostTreatment */
  
  /* USER CODE END USB_DEVICE_Init_PostTreatment */
}

void USB_DeInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    USBD_Stop(&hUsbDeviceFS);
    USBD_DeInit(&hUsbDeviceFS);

    GPIO_InitStruct.Pin = USB_DP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, USB_DP_Pin, 0);

    HAL_Delay(FORCE_DISCONNECT_WAIT_TIME_IN_MS);
}

uint32_t USB_SendQueuePacket(packet_t const* p)
{
    __disable_irq();
    uint32_t w = packet_serialize(p, USB_tx_buffer+USB_tx_buffer_lead_ptr, 0x200-USB_tx_buffer_lead_ptr);
    USB_tx_buffer_lead_ptr += w;
    __enable_irq();
    return w;
}

uint32_t USB_SendQueue(uint8_t const* buffer, uint32_t size)
{
    __disable_irq();
    uint32_t i;
    for (i = 0; i < size; i++) {
        USB_tx_buffer[USB_tx_buffer_lead_ptr++] = buffer[i];
        if (USB_tx_buffer_lead_ptr >= 0xFF) {
            __enable_irq();
            return i+1;
        }
    }
    __enable_irq();
    return i;
}

void USB_SendTick(void)
{
    if (USB_tx_buffer_lead_ptr > 0) {
        USB_Send(USB_tx_buffer, USB_tx_buffer_lead_ptr);
        USB_tx_buffer_lead_ptr = 0;
    }
}

void USB_Send(uint8_t* buffer, uint32_t size)
{
    USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
    if (hcdc == NULL || size == 0) return;
    volatile uint32_t busy_times = 0;
    while (1) {
        hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
        if (hcdc->TxState != 0) { // USBD_BUSY
            if (++busy_times > USB_BUSY_BREAK_THRESHOLD) {
            }
            else continue;
        } else {
            break;
        }
    }
    USBD_CDC_SetTxBuffer(&hUsbDeviceFS, buffer, size);
    USBD_CDC_TransmitPacket(&hUsbDeviceFS);
    while (1) {
        hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
        if (hcdc->TxState == 0) break;
    }
}


/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

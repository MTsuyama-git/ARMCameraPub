#ifndef __USB_DEVICE__H__
#define __USB_DEVICE__H__

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"
#include "usbd_def.h"
#include "packet.h"

#define USB_CONNECTED_Pin GPIO_PIN_12 // PB12
#define USB_DP_Pin        GPIO_PIN_12 // PA12

void USB_Init(void);
void USB_DeInit(void);
uint32_t USB_SendQueuePacket(packet_t const* p);
uint32_t USB_SendQueue(uint8_t const*, uint32_t);
void USB_SendTick(void);
void USB_Send(uint8_t* , uint32_t);
#endif /* __USB_DEVICE__H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

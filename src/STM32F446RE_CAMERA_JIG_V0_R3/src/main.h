/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define CLK_Pin GPIO_PIN_14
#define CLK_GPIO_Port GPIOC
#define DI_Pin GPIO_PIN_15
#define DI_GPIO_Port GPIOC
#define SUPPLY_Pin GPIO_PIN_0
#define SUPPLY_GPIO_Port GPIOC
#define CAMERA_PWDN_Pin GPIO_PIN_3
#define CAMERA_PWDN_GPIO_Port GPIOC
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define LCD_RESET_Pin GPIO_PIN_4
#define LCD_RESET_GPIO_Port GPIOC
#define LCD_A0_Pin GPIO_PIN_5
#define LCD_A0_GPIO_Port GPIOC
#define LCD_NSS_Pin GPIO_PIN_0
#define LCD_NSS_GPIO_Port GPIOB
#define MTA_PHASE_Pin GPIO_PIN_1
#define MTA_PHASE_GPIO_Port GPIOB
#define MTA_EN_Pin GPIO_PIN_2
#define MTA_EN_GPIO_Port GPIOB
#define SD_NSS_Pin GPIO_PIN_12
#define SD_NSS_GPIO_Port GPIOB
#define MTB_PHASE_Pin GPIO_PIN_14
#define MTB_PHASE_GPIO_Port GPIOB
#define MTB_EN_Pin GPIO_PIN_15
#define MTB_EN_GPIO_Port GPIOB
#define STB1_Pin GPIO_PIN_9
#define STB1_GPIO_Port GPIOA
#define STB2_Pin GPIO_PIN_10
#define STB2_GPIO_Port GPIOA
#define STB3_Pin GPIO_PIN_11
#define STB3_GPIO_Port GPIOA
#define STB4_Pin GPIO_PIN_12
#define STB4_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define STB5_Pin GPIO_PIN_15
#define STB5_GPIO_Port GPIOA
#define STB6_Pin GPIO_PIN_10
#define STB6_GPIO_Port GPIOC
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define LAT_Pin GPIO_PIN_4
#define LAT_GPIO_Port GPIOB
    
#define SUPPLY_OFF GPIO_PIN_SET
#define SUPPLY_ON GPIO_PIN_RESET
/* USER CODE BEGIN Private defines */
#define DATA_NUM 384
#define STB_CNT 3
#define BUFFER_NUM 2
#define PATTER_NUM 4
#define STATE_CHANGE_CNT (3)
#define DATA_SECTION_NUM 6

typedef struct  {
    char name[255];
    uint8_t status;
    uint8_t remain;
  GPIO_TypeDef* port;
  uint16_t pin;
}gpioPin;



/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

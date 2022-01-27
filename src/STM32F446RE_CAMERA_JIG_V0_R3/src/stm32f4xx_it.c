/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_it.h"
#include "printer_stepping_defs.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

extern state_e printState;

extern uint8_t led;
extern uint8_t clk;
extern uint8_t dat;

extern uint8_t data_remain; // number of data in buffer
extern int8_t lat_cnt;
extern uint64_t buffer[2][6]; // data of 324 dot * 2
extern uint8_t buffer_id;
extern uint8_t buffer_stat[2];

extern uint16_t dat_cnt;
extern uint8_t lat;
extern uint8_t lat_en;
extern uint8_t supply_cnt;

// stb
extern int8_t stb1_pre;
extern uint8_t stb1;
extern int8_t stb2_pre;
extern uint8_t stb2;
extern int8_t stb3_pre;
extern uint8_t stb3;
extern int8_t stb4_pre;
extern uint8_t stb4;
extern int8_t stb5_pre;
extern uint8_t stb5;
extern int8_t stb6_pre;
extern uint8_t stb6;

extern uint8_t mta;
extern uint8_t mta_;
extern uint8_t mtb;
extern uint8_t mtb_;

extern uint8_t mt_drive_pattern[2][4];
extern uint8_t mt_pattern_count;
extern int8_t mt_state_change_count;

extern uint8_t reading_buffer;
extern uint8_t next_read_buffer;
extern uint8_t mt_reading_pattern;

extern uint8_t ena_pattern[];
extern uint8_t pha_pattern[];
extern uint8_t enb_pattern[];
extern uint8_t phb_pattern[];


/**
  * @brief This function handles TIM3 global interrupt.
  */
void TIM3_IRQHandler(void)
{
    /* // ltica */
    /* HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, led); */
    /* led = 1 - led; */

    /* /\* USER CODE BEGIN TIM3_IRQn 0 *\/ */
    /* if(printState == WAITING) { */
    /*     // for debug */
    /*     for(uint8_t _section_id = 0; _section_id < DATA_SECTION_NUM; _section_id++) { */
    /*         buffer[reading_buffer][_section_id] = 0xFFFFFFFFFFFFFFFF; */
    /*         /\* next_read_buffer = reading_buffer+1; *\/ */
    /*         /\* next_read_buffer %= BUFFER_NUM; *\/ */
    /*     } */
    /*     printState = SENDING_DATA;  */
    /*     clk = 1; */
    /*     dat_cnt = 0; */
    /*     // end for debug */

    /*     /\* if(buffer_stat[reading_buffer] == PREPARED) { *\/ */
    /*     /\*     buffer_stat[reading_buffer] = READING; *\/ */
    /*     /\*     printState = SENDING_DATA; *\/ */
    /*     /\*     dat_cnt = 0; *\/ */
    /*     /\*     clk = 1; *\/ */
    /*     /\* } *\/ */
    /* } */
    /* else if(printState == SENDING_DATA) { */
    /*     clk = 1 - clk; */
    /*     if(clk) { */
    /*         if(dat_cnt == DATA_NUM) { */
    /*             printState = LAT_DATA; */
    /*             buffer_stat[reading_buffer] = NOT_PREPARED; */
    /*             lat_cnt = 100; // 1ns * 100 */
    /*             lat = 0; */
    /*             /\* HAL_GPIO_WritePin(LAT_PORT, LAT_Pin, lat);   *\/ */
    /*         } */
    /*     } */
    /*     else { */
    /*         dat = buffer[reading_buffer][dat_cnt/64] & 0x01; */
    /*         buffer[reading_buffer][dat_cnt/64] >>= 1;                 */
    /*         dat_cnt++; */
    /*         /\* HAL_GPIO_WritePin(DATA_PORT, DATA_IN_Pin, dat); *\/ */
    /*     } */
    /*     /\* HAL_GPIO_WritePin(CLK_PORT, CLK_Pin, clk);  *\/ */
    /* } */
    /* else if(printState == LAT_DATA) { */
    /*     lat_cnt--; */
    /*     if(lat_cnt == 0) { */
    /*         lat = 1; */
    /*         /\* HAL_GPIO_WritePin(LAT_PORT, LAT_Pin, lat);   *\/ */
    /*         printState = PRINTING; */
    /*         /\* stb_cnt = 62; *\/ */
    /*         mt_state_change_count = 0; */
    /*         mt_pattern_count = 0; */
    /*         /\* 8v_logic = 1; *\/ */
    /*         stb1 = 1; */
    /*         stb2 = 1; */
    /*         stb3 = 1; */
    /*         stb4 = 1; */
    /*         stb5 = 1; */
    /*         stb6 = 1; */
    /*         /\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_0_Pin, stb1); *\/ */
    /*         /\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_1_Pin, stb2); *\/ */
    /*         /\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_2_Pin, stb3); *\/ */
    /*         /\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_3_Pin, stb4); *\/ */
    /*         /\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_4_Pin, stb5); *\/ */
    /*         /\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_5_Pin, stb6); *\/ */
    /*         /\* HAL_GPIO_WritePin(POWER_ENABLER_PORT, SUPPLY_8_5_ENABLE_Pin, SUPPLY_ON); *\/ */
    /*     } */
    /* } */
    /* else if(printState == PRINTING) { */
    /*     if(mt_state_change_count == 0 && mt_pattern_count < PATTERN_NUM) { */
    /*         mta  = (mt_drive_pattern[reading_buffer%2][mt_pattern_count] >> 3) & 1; */
    /*         mtb  = (mt_drive_pattern[reading_buffer%2][mt_pattern_count] >> 2) & 1; */
    /*         mta_ = (mt_drive_pattern[reading_buffer%2][mt_pattern_count] >> 1) & 1; */
    /*         mtb_ = (mt_drive_pattern[reading_buffer%2][mt_pattern_count] >> 0) & 1; */
    /*         mt_pattern_count++; */
    /*         mt_pattern_count %= (PATTERN_NUM); */
    /*         mt_state_change_count++; */
    /*         HAL_GPIO_WritePin(MTA_EN_GPIO_Port, MTA_EN_Pin, mta); */
    /*         HAL_GPIO_WritePin(MTB_EN_GPIO_Port, MTB_EN_Pin, mtb); */
    /*         HAL_GPIO_WritePin(MTA_PHASE_GPIO_Port, MTA_PHASE_Pin, mta_); */
    /*         HAL_GPIO_WritePin(MTB_PHASE_GPIO_Port, MTB_PHASE_Pin, mtb_); */
    /*     } */
    /*     else if(mt_state_change_count == 0) { */
    /*         /\* reading_buffer = next_read_buffer; *\/ */
    /*         reading_buffer++; */
    /*         reading_buffer%= BUFFER_NUM; */
    /*         printState = WAITING; */
    /*         /\* HAL_GPIO_WritePin(POWER_ENABLER_PORT, SUPPLY_8_5_ENABLE_Pin, SUPPLY_OFF); *\/ */
    /*     } */
    /*     /\* if(stb_cnt == 0) { *\/ */
    /*     /\*     stb1 = 0; *\/ */
    /*     /\*     stb2 = 0; *\/ */
    /*     /\*     stb3 = 0; *\/ */
    /*     /\*     stb4 = 0; *\/ */
    /*     /\*     stb5 = 0; *\/ */
    /*     /\*     stb6 = 0; *\/ */
    /*     /\*     /\\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_0_Pin, stb1); *\\/ *\/ */
    /*     /\*     /\\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_1_Pin, stb2); *\\/ *\/ */
    /*     /\*     /\\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_2_Pin, stb3); *\\/ *\/ */
    /*     /\*     /\\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_3_Pin, stb4); *\\/ *\/ */
    /*     /\*     /\\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_4_Pin, stb5); *\\/ *\/ */
    /*     /\*     /\\* HAL_GPIO_WritePin(STROBE_PORT, STROBE_5_Pin, stb6); *\\/ *\/ */
    /*     /\* } *\/ */
    /*     mt_state_change_count++; */
    /*     mt_state_change_count %= MT_STATE_CHANGE_COUNT; */
    /*     /\* stb_cnt--; *\/ */
    /* } */
    /* USER CODE END TIM3_IRQn 0 */
    HAL_GPIO_WritePin(MTA_EN_GPIO_Port, MTA_EN_Pin, ena_pattern[mt_pattern_count]);
    HAL_GPIO_WritePin(MTB_EN_GPIO_Port, MTB_EN_Pin, enb_pattern[mt_pattern_count]);
    HAL_GPIO_WritePin(MTA_PHASE_GPIO_Port, MTA_PHASE_Pin, pha_pattern[mt_pattern_count]);
    HAL_GPIO_WritePin(MTB_PHASE_GPIO_Port, MTB_PHASE_Pin, phb_pattern[mt_pattern_count]);
    mt_pattern_count++;
    mt_pattern_count %= 8;

    HAL_TIM_IRQHandler(&htim3);
    /* USER CODE BEGIN TIM3_IRQn 1 */

    /* USER CODE END TIM3_IRQn 1 */
    /* HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, led); */
    /* led = 1-led; */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

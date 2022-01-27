/* USER CODE BEGIN Header */
/**
******************************************************************************
* @file           : main.c
* @brief          : Main program body
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
#include "printer_stepping_defs.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TFT_DC_C  HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, 0) 
#define TFT_DC_D  HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, 1) 
#define TFT_CS_L  HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_GPIO_Port, 0) 
#define TFT_CS_H  HAL_GPIO_WritePin(LCD_NSS_GPIO_Port, LCD_NSS_GPIO_Port, 1) 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;
ADC_HandleTypeDef hadc2;

DCMI_HandleTypeDef hdcmi;

I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile uint8_t led = 1;
volatile uint8_t clk = 0;
volatile uint8_t dat = 0;

volatile uint8_t data_remain = 0; // number of data in buffer
volatile int lat_cnt = -1;
volatile uint64_t buffer[2][6] = {{0},{0}};
volatile uint8_t buffer_id = 0;
volatile uint8_t buffer_stat[2] = {NOT_PREPARED, NOT_PREPARED};

volatile uint16_t dat_cnt = 0;
volatile uint8_t lat = 1;
volatile uint8_t lat_en = 0;

volatile uint8_t supply_cnt = 0;

// stb
volatile int8_t stb1_pre = -1;
volatile uint8_t stb1 = 0;
volatile int8_t stb2_pre = -1;
volatile uint8_t stb2 = 0;
volatile int8_t stb3_pre = -1;
volatile uint8_t stb3 = 0;
volatile int8_t stb4_pre = -1;
volatile uint8_t stb4 = 0;
volatile int8_t stb5_pre = -1;
volatile uint8_t stb5 = 0;
volatile int8_t stb6_pre = -1;
volatile uint8_t stb6 = 0;


// motor
volatile uint8_t mta  = 0;
volatile uint8_t mta_ = 0;
volatile uint8_t mtb  = 0;
volatile uint8_t mtb_ = 0;

volatile state_e printState = WAITING;
const uint8_t mt_drive_pattern[2][4] = {{13,7,15,11},{14,6,12,9}};

const uint8_t ena_pattern[] = {0,1,1,1,0,1,1,1};
const uint8_t pha_pattern[] = {0,1,1,1,0,0,0,0};
const uint8_t enb_pattern[] = {1,1,0,1,1,1,0,1};
const uint8_t phb_pattern[] = {1,1,0,0,0,0,0,1};

uint8_t lcdTxBuffer[] = {0, 0, 0, 0, 0, 0, 0, 0};
uint8_t lcdRxBuffer[] = {0,0,0,0,0,0,0,0,0,0};

volatile uint8_t mt_pattern_count = 0;
volatile int8_t mt_state_change_count = -1;
volatile uint8_t reading_buffer = 0;
volatile uint8_t next_read_buffer = 0;
volatile uint8_t mt_reading_pattern = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_ADC2_Init(void);
static void MX_DCMI_Init(void);
static void MX_I2C2_Init(void);
static void MX_SPI2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM3_Init(void);
/* USER CODE BEGIN PFP */
gpioPin a, _a, b, _b;
gpioPin* pinArray[] = {&a, &_a, &b, &_b};
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
inline static void setup_lat(void) {
    HAL_GPIO_WritePin(LAT_GPIO_Port, LAT_Pin, GPIO_PIN_SET); 
}

inline static void setup_clk(void) {
    HAL_GPIO_WritePin(CLK_GPIO_Port, CLK_Pin, GPIO_PIN_RESET); 
}

inline static void setup_data_port(void) {
    /* HAL_GPIO_WritePin(DATA_PORT, DATA_OUT_Pin, GPIO_PIN_RESET);  */
    HAL_GPIO_WritePin(DI_Pin, DI_GPIO_Port, GPIO_PIN_RESET);
}

inline static void setup_stb(void) {
    /* HAL_GPIO_WritePin(STROBE_PORT, STROBE_0_Pin, GPIO_PIN_RESET);  */
    /* HAL_GPIO_WritePin(STROBE_PORT, STROBE_1_Pin, GPIO_PIN_RESET);  */
    /* HAL_GPIO_WritePin(STROBE_PORT, STROBE_2_Pin, GPIO_PIN_RESET);  */
    /* HAL_GPIO_WritePin(STROBE_PORT, STROBE_3_Pin, GPIO_PIN_RESET);  */
    /* HAL_GPIO_WritePin(STROBE_PORT, STROBE_4_Pin, GPIO_PIN_RESET);  */
    /* HAL_GPIO_WritePin(STROBE_PORT, STROBE_5_Pin, GPIO_PIN_RESET);  */
    HAL_GPIO_WritePin(STB1_GPIO_Port, STB1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STB2_GPIO_Port, STB2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STB3_GPIO_Port, STB3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STB4_GPIO_Port, STB4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STB5_GPIO_Port, STB5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(STB6_GPIO_Port, STB6_Pin, GPIO_PIN_RESET);
}

inline static void setup_supply(void) {
    HAL_GPIO_WritePin(SUPPLY_GPIO_Port, SUPPLY_Pin, SUPPLY_OFF); // supply off
}

inline static void setup_motor(void) {
    a.port = MTA_EN_GPIO_Port;
    a.pin  = MTA_EN_Pin;
    b.port = MTB_EN_GPIO_Port;
    b.pin  = MTB_EN_Pin;
    HAL_GPIO_WritePin(a.port, a.pin, 1);
    HAL_GPIO_WritePin(b.port, b.pin, 1);
}

inline static void setup_motor0(void) {
    a.port = MTA_EN_GPIO_Port;
    a.pin  = MTA_EN_Pin;
    b.port = MTB_EN_GPIO_Port;
    b.pin  = MTB_EN_Pin;
    _a.port = MTA_PHASE_GPIO_Port;
    _a.pin = MTA_PHASE_Pin;
    _b.port = MTB_PHASE_GPIO_Port;
    _b.pin = MTB_PHASE_Pin;
    a.status = 1;
    a.remain = 1;
    HAL_GPIO_WritePin(a.port, a.pin, a.status);
    b.status = 0;
    b.remain=4;
    HAL_GPIO_WritePin(b.port, b.pin, b.status);
    _a.status = 0;
    _a.remain = 2;
    _b.status = 0;
    _b.remain = 0;
    HAL_GPIO_WritePin(MTA_PHASE_GPIO_Port, MTA_PHASE_Pin, _a.status);
    HAL_GPIO_WritePin(MTB_PHASE_GPIO_Port, MTB_PHASE_Pin, _a.status);
}

void writeCommand(uint8_t cmd)
{
    lcdTxBuffer[0] = cmd;
    TFT_DC_C;
    TFT_CS_L;
    HAL_SPI_Transmit(&hspi2,(uint8_t*)lcdTxBuffer,1,2000);
    TFT_CS_H;
}

void writeData(uint8_t dat)
{
    lcdTxBuffer[0] = dat;
    TFT_DC_D;
    TFT_CS_L;
    HAL_SPI_Transmit(&hspi2,(uint8_t*)lcdTxBuffer,1,2000);
    TFT_CS_H;
}


void setup(void) {
    /* setup for supply */
    setup_supply();
    /* setup for motor */
    setup_motor();
    /* strobe */
    setup_stb();
    /* data */
    setup_data_port();
    /* clk */
    setup_clk();
    /* lat */
    setup_lat();
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
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_ADC2_Init();
    MX_DCMI_Init();
    MX_I2C2_Init();
    MX_SPI2_Init();
    MX_USART2_UART_Init();
    MX_TIM3_Init();
    /* USER CODE BEGIN 2 */
    // for motor
    // HAL_TIM_Base_Start_IT(&htim3); // Begin timer(TMR3) interrupt
    /* USER CODE END 2 */
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */

    /* hspi2 */
    // reset LCD
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, 1);
    HAL_Delay(5);
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, 0);
    HAL_Delay(20);
    HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, 1);
    HAL_Delay(150);

    // command initialize
    writeCommand(0x01);  // soft reset

    writeCommand(0x11);  // exit sleep

    writeCommand(0x3A);writeData(0x05); // set pix format

    writeCommand(0x26);writeData(0x04); // set gamma curve

    writeCommand(0xF2);writeData(0x01); // enable gamma adjustment

    writeCommand(0xE0);writeData(0x3F);writeData(0x25);writeData(0x1C);writeData(0x1E);writeData(0x20);
    writeData(0x12);writeData(0x2A);writeData(0x90);writeData(0x24);writeData(0x11);writeData(0x00);
    writeData(0x00);writeData(0x00);writeData(0x00);writeData(0x00); // positive gamma

    writeCommand(0xE1);writeData(0x20);writeData(0x20);writeData(0x20);writeData(0x20);writeData(0x05);
    writeData(0x00);writeData(0x15);writeData(0xA7);writeData(0x3D);writeData(0x18);writeData(0x25);
    writeData(0x2A);writeData(0x2B);writeData(0x2B);writeData(0x3A); // negative gamma
    
    writeCommand(0xB1);writeData(0x08);writeData(0x08); // Frame rate ctrl 1

    writeCommand(0xB4);writeData(0x07);                 // display inversion

    writeCommand(0xC0);writeData(0x0A);writeData(0x02); // power ctrl 1

    writeCommand(0xC1);writeData(0x02); // power ctrl 2

    writeCommand(0xC5);writeData(0x50);writeData(0x5B); // vcom control 1

    writeCommand(0xC7);writeData(0x40); // vcom offset

    writeCommand(0x2A);writeData(0x00);writeData(0x00);writeData(0x00);writeData(0x7F); // set column address

    HAL_Delay(250);
    
    writeCommand(0x2B);writeData(0x00);writeData(0x00);writeData(0x00);writeData(0x9F); // set page address

    writeCommand(0x36);writeData(0xC8); // set address mode

 
    /* writeCommand(0x29); // display on */

    writeCommand(0x28); // display off
    
    while (1)
    {
        /* USER CODE END WHILE */

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
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB busses clocks 
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
        |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
    {
        Error_Handler();
    }
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSI, RCC_MCODIV_1);
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

    /* USER CODE BEGIN ADC1_Init 0 */

    /* USER CODE END ADC1_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC1_Init 1 */

    /* USER CODE END ADC1_Init 1 */
    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
     */
    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
     */
    sConfig.Channel = ADC_CHANNEL_1;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC1_Init 2 */

    /* USER CODE END ADC1_Init 2 */

}

/**
 * @brief ADC2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC2_Init(void)
{

    /* USER CODE BEGIN ADC2_Init 0 */

    /* USER CODE END ADC2_Init 0 */

    ADC_ChannelConfTypeDef sConfig = {0};

    /* USER CODE BEGIN ADC2_Init 1 */

    /* USER CODE END ADC2_Init 1 */
    /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
     */
    hadc2.Instance = ADC2;
    hadc2.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
    hadc2.Init.Resolution = ADC_RESOLUTION_12B;
    hadc2.Init.ScanConvMode = DISABLE;
    hadc2.Init.ContinuousConvMode = DISABLE;
    hadc2.Init.DiscontinuousConvMode = DISABLE;
    hadc2.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc2.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc2.Init.NbrOfConversion = 1;
    hadc2.Init.DMAContinuousRequests = DISABLE;
    hadc2.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
    if (HAL_ADC_Init(&hadc2) != HAL_OK)
    {
        Error_Handler();
    }
    /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
     */
    sConfig.Channel = ADC_CHANNEL_7;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN ADC2_Init 2 */

    /* USER CODE END ADC2_Init 2 */

}

/**
 * @brief DCMI Initialization Function
 * @param None
 * @retval None
 */
static void MX_DCMI_Init(void)
{

    /* USER CODE BEGIN DCMI_Init 0 */

    /* USER CODE END DCMI_Init 0 */

    /* USER CODE BEGIN DCMI_Init 1 */

    /* USER CODE END DCMI_Init 1 */
    hdcmi.Instance = DCMI;
    hdcmi.Init.SynchroMode = DCMI_SYNCHRO_HARDWARE;
    hdcmi.Init.PCKPolarity = DCMI_PCKPOLARITY_FALLING;
    hdcmi.Init.VSPolarity = DCMI_VSPOLARITY_LOW;
    hdcmi.Init.HSPolarity = DCMI_HSPOLARITY_LOW;
    hdcmi.Init.CaptureRate = DCMI_CR_ALL_FRAME;
    hdcmi.Init.ExtendedDataMode = DCMI_EXTEND_DATA_8B;
    hdcmi.Init.JPEGMode = DCMI_JPEG_DISABLE;
    hdcmi.Init.ByteSelectMode = DCMI_BSM_ALL;
    hdcmi.Init.ByteSelectStart = DCMI_OEBS_ODD;
    hdcmi.Init.LineSelectMode = DCMI_LSM_ALL;
    hdcmi.Init.LineSelectStart = DCMI_OELS_ODD;
    if (HAL_DCMI_Init(&hdcmi) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN DCMI_Init 2 */

    /* USER CODE END DCMI_Init 2 */

}

/**
 * @brief I2C2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C2_Init(void)
{

    /* USER CODE BEGIN I2C2_Init 0 */

    /* USER CODE END I2C2_Init 0 */

    /* USER CODE BEGIN I2C2_Init 1 */

    /* USER CODE END I2C2_Init 1 */
    hi2c2.Instance = I2C2;
    hi2c2.Init.ClockSpeed = 100000;
    hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c2.Init.OwnAddress1 = 0;
    hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c2.Init.OwnAddress2 = 0;
    hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN I2C2_Init 2 */

    /* USER CODE END I2C2_Init 2 */

}

/**
 * @brief SPI2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI2_Init(void)
{

    /* USER CODE BEGIN SPI2_Init 0 */

    /* USER CODE END SPI2_Init 0 */

    /* USER CODE BEGIN SPI2_Init 1 */

    /* USER CODE END SPI2_Init 1 */
    /* SPI2 parameter configuration*/
    hspi2.Instance = SPI2;
    hspi2.Init.Mode = SPI_MODE_MASTER;
    hspi2.Init.Direction = SPI_DIRECTION_2LINES;
    hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
    hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
    hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
    hspi2.Init.NSS = SPI_NSS_SOFT;
    hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
    hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
    hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
    hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    hspi2.Init.CRCPolynomial = 10;
    if (HAL_SPI_Init(&hspi2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN SPI2_Init 2 */

    /* USER CODE END SPI2_Init 2 */

}

/**
 * @brief TIM3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM3_Init(void)
{

    /* USER CODE BEGIN TIM3_Init 0 */

    /* USER CODE END TIM3_Init 0 */

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    /* USER CODE BEGIN TIM3_Init 1 */

    /* USER CODE END TIM3_Init 1 */
    htim3.Instance = TIM3;
    htim3.Init.Prescaler = 119;
    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.Period = 199;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
    {
        Error_Handler();
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN TIM3_Init 2 */

    /* USER CODE END TIM3_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

    /* USER CODE BEGIN USART2_Init 0 */

    /* USER CODE END USART2_Init 0 */

    /* USER CODE BEGIN USART2_Init 1 */

    /* USER CODE END USART2_Init 1 */
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
    /* USER CODE BEGIN USART2_Init 2 */

    /* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, CLK_Pin|DI_Pin|SUPPLY_Pin|CAMERA_PWDN_Pin 
                      |LCD_RESET_Pin|LCD_A0_Pin|STB6_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, LD2_Pin|STB1_Pin|STB2_Pin|STB3_Pin 
                      |STB4_Pin|STB5_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, LCD_NSS_Pin|MTA_PHASE_Pin|MTA_EN_Pin|SD_NSS_Pin 
                      |MTB_PHASE_Pin|MTB_EN_Pin|LAT_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin : B1_Pin */
    GPIO_InitStruct.Pin = B1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : CLK_Pin DI_Pin SUPPLY_Pin CAMERA_PWDN_Pin 
      LCD_RESET_Pin LCD_A0_Pin STB6_Pin */
    GPIO_InitStruct.Pin = CLK_Pin|DI_Pin|SUPPLY_Pin|CAMERA_PWDN_Pin 
        |LCD_RESET_Pin|LCD_A0_Pin|STB6_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : LD2_Pin STB1_Pin STB2_Pin STB3_Pin 
      STB4_Pin STB5_Pin */
    GPIO_InitStruct.Pin = LD2_Pin|STB1_Pin|STB2_Pin|STB3_Pin 
        |STB4_Pin|STB5_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pins : LCD_NSS_Pin MTA_PHASE_Pin MTA_EN_Pin SD_NSS_Pin 
      MTB_PHASE_Pin MTB_EN_Pin LAT_Pin */
    GPIO_InitStruct.Pin = LCD_NSS_Pin|MTA_PHASE_Pin|MTA_EN_Pin|SD_NSS_Pin 
        |MTB_PHASE_Pin|MTB_EN_Pin|LAT_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : PA8 */
    GPIO_InitStruct.Pin = GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF0_MCO;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*Configure GPIO pin : PB5 */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

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

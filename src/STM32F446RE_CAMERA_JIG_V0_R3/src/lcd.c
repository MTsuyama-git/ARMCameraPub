#include <lcd.h>

SPI_HandleTypeDef *_hspi = NULL;
GPIO_TypeDef *_cs_port = NULL, *_reset_port = NULL, *_a0_port = NULL;
uint16_t _cs_pin, _reset_pin, _a0_pin;

uint8_t data_buffer[256];

static void transmitData(uint8_t* tx_buffer, uint16_t size, uint32_t timeout);
static void lcd_begin(void);
static void chipInit(void);

void LCD_Init(SPI_HandleTypeDef* hspi, uint8_t, GPIO_TypeDef* cs_port, uint16_t cs_pin, GPIO_TypeDef* reset_port, uint16_t reset_pin, GPIO_TypeDef* a0_port, uint16_t a0_pin) {
    _hspi = hspi;
    _cs_port = cs_port;
    _reset_port = reset_port;
    _a0_port = a0_port;
    _cs_pin = cs_pin;
    _reset_pin = reset_pin;
    _a0_pin = a0_pin;
    lcd_begin();

}

static void lcd_begin(void) {
    HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_SET);
}

static void chipInit(void) {
    uint8_t i;
    data_buffer[0] = CMD_SWRESET;
    transmitData(data_buffer, 1, 3000);
    HAL_Delay(500); // wait until the lcd complets reset

    data_buffer[0] = CMD_SLPOUT;
    transmitData(data_buffer, 1, 3000); // when the lecd complete reset, it starts sleep.
    HAL_Delay(5);
    
    // set color format 16 bit
    data_buffer[0] = CMD_PIXFMT;
    data_buffer[1] = 0x05;
    transmitData(data_buffer, 2, 3000); 
    HAL_Delay(5);

    // 
    data_buffer[0] = CMD_GAMMASET;
    data_buffer[1] = 0x08;
    transmitData(data_buffer, 2, 3000);  // default gamma curve 3
    HAL_Delay(1);

    //
    data_buffer[0] = CMD_GAMMASEL;
    data_buffer[1] = 0x01;
    transmitData(data_buffer, 2, 3000);  // enable gamma adj
    HAL_Delay(1);
    

    
}

static void transmitData(uint8_t* tx_buffer, uint16_t size, uint32_t timeout) {
    HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(_hspi, tx_buffer, size, timeout);
    HAL_GPIO_WritePin(_cs_port, _cs_pin, GPIO_PIN_SET);
}

/* static void transmitReceiveData(uint8_t* tx_buffer, uint16_t size, uint32_t timeout) { */
/*     HAL_SPI_TransmitReceive(_hspi, tx_buffer, rx_buffer, size, timeout); */
/* } */

/* static void receiveData(uint8_t* rx_buffer, uint16_t size, uint32_t timeout) { */
/*     HAL_SPI_Receive(_hspi, rx_buffer, size, timeout); */
/* } */

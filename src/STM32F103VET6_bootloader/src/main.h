#ifndef __MAIN_H
#define __MAIN_H
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"

#ifndef PCB_VERSION
#error Required PCB_VERSION. ex $ make PCB_VERSION=1.0.0
#endif

typedef enum run_mode {
    APP_MODE     = 0x00,
    FLASHER_MODE = 0x01,
} run_mode_t;

typedef enum flasher_state {
    NOT_IN       = 0x00,
    WAITING      = 0x01,
    ERASING      = 0x02,
    WRITING      = 0x03,
} flasher_state_t;

#define VERSION_MAX_LEN 64

void Error_Handler(void);

#endif


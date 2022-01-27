#ifndef __COLOR_BAR_H
#define __COLOR_BAR_H
#include "stm32f3xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct PixInfo {
    uint8_t length;
    const uint16_t pixinfo;
} PixInfo_t;

typedef struct LineInfo {
    const uint8_t length;
    const uint8_t num_pixInfo;
    const PixInfo_t* pixinfos;
} LineInfo_t;

PixInfo_t getPixInfo(uint8_t, const uint16_t);

#ifdef __cplusplus
}
#endif

#endif

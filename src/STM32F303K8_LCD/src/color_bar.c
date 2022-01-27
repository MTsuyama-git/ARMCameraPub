#include "color_bar.h"

PixInfo_t getPixInfo(uint8_t length, const uint16_t pixinfo) {
    PixInfo_t result = {length, pixinfo};
    return result;
}

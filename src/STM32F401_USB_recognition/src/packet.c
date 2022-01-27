#include "packet.h"
#include "uart.h"
#include "main.h"
#include "ring_buffer.h"

extern uint8_t led;
extern uint8_t len;
extern uint16_t nptr;
extern uint16_t err_code;
extern uint16_t frameNum;
extern uint16_t* sizeinfo;
extern uint8_t sizeinfo_ptr;
extern uint8_t* cfgdesc_raw;
extern uint16_t cfgdesc_len;

typedef enum parse_state parse_state;

enum parse_state {
    PREAMBLE_1,
    PREAMBLE_2,
    TYPE,
    LEN,
    CMD,
    ARGS,
};

void parse_packet(ring_buffer* rb) {
    int x;
    parse_state ps = PREAMBLE_1;
    int remain = 0;
    uint8_t argptr = 0;
    uint8_t args[0xFF];
    uint8_t cmd = 0xFF;
    while(1) {
        x = ring_buffer_pop(rb);
        if(x == NOT_FOUND) {
            goto end;
        }
        switch(ps) {
        case PREAMBLE_1:
            if((uint8_t)x != 0xAA) {
                goto except;
            }
            else {
                ps = PREAMBLE_2;
            }
            break;
        case PREAMBLE_2:
            if((uint8_t)x != 0x55) {
                goto except;
            }
            else {
                ps = TYPE;
            }
            break;
        case TYPE:
            ps = LEN;
            break;
        case LEN:
            if((uint8_t) x == 0) {
                goto next;
            }
            else {
                remain = x;
                ps = CMD;
            }
            break;
        case CMD:
            cmd = (uint8_t)x;
            ps = ARGS;
            remain--;
            break;
        case ARGS:
            args[argptr++] = (uint8_t) x;
            if(remain == 0) {
                int i;
                uint8_t message[] = {0xAA, 0x55, (err_code >> 8) & 0xFF, err_code & 0xFF, (frameNum >> 8) & 0xFF, frameNum & 0xFF};
                for(i = 0; i < 6; ++i) {
                    puts0(USART2, message[i]);
                }
                for(i = 0; i < cfgdesc_len; ++i) {
                    puts0(USART2, cfgdesc_raw[i]);
                }
                for(i = 0; i < sizeinfo_ptr; ++i) {
                    biputs0(USART2, sizeinfo[i]);
                }
                goto next;
            }
            remain--;
            break;
        }
    }
end:
    // 正常終了
    ring_buffer_revert(rb);
    return;
next:
except:
    // 異常終了
    ring_buffer_save_ptr(rb);
    return;
    
}

void packet_parser_bulk_push(ring_buffer* rb, uint8_t const* src, uint32_t* size)
{
    __set_PRIMASK(1);
    ring_buffer_bulk_push(rb, src, *size);
    *size = 0;
    __set_PRIMASK(0);
}

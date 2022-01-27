#include "packet.h"
#include "gpio.h"
#include "usb_device.h"
#include "main.h"
#include "partition.h"
#include "nvs.h"
#include "crc.h"

typedef enum flasher_op {
    OP_NOP         = 0x00,
    OP_GET_PROFILE = 0x01,
    OP_ERASE       = 0x02,
    OP_WRITE_START = 0x03,
    OP_WRITE_DATA  = 0x04,
    OP_WRITE_END   = 0x05,
    OP_RESET       = 0x06,
} flasher_op_t;

typedef enum flasher_result {
    ACK  = 0x79,
    NACK = 0x1F
} flasher_result_t;

typedef struct write_state {
    uint8_t started;
    uint32_t written_bytes;
    char firmware_version[32];
} write_state_t;

static void get_profile(packet_t const* p)
{
    packet_t sp = { 0 };
    sp.type = Response;
    sp.sender_id = p->destination_id;
    sp.packet_id = p->packet_id;
    sp.op        = p->op;
    uint16_t id = (uint16_t)(DBGMCU->IDCODE & 0xFFF); //Retrieves MCU ID from DEBUG interface
    uint16_t size = 0;
    uint8_t current_run_mode = APP_MODE;

    char pcb_version[VERSION_MAX_LEN]   = { 0 };
    uint16_t pcb_version_len = 0;
    char firm_version[VERSION_MAX_LEN] = { 0 };
    uint16_t firm_version_len = 0;

    if (nvs_get("PCB_VER", (uint8_t*)pcb_version, &pcb_version_len, VERSION_MAX_LEN) != NVS_OK ||
        nvs_get("FW_VER",  (uint8_t*)firm_version, &firm_version_len, VERSION_MAX_LEN) != NVS_OK ||
        nvs_get("RUN_MODE", &current_run_mode, &size, 1) != NVS_OK)
    {
        sp.len     = 3;
        sp.data[0] = NACK;
        sp.data[1] = (id)      & 0xFF;
        sp.data[2] = (id >> 8) & 0xFF;
    } else {
        sp.len = 4 + pcb_version_len + firm_version_len;
        sp.data[0] = ACK;
        sp.data[1] = (id)      & 0xFF;
        sp.data[2] = (id >> 8) & 0xFF;
        sp.data[3] = current_run_mode;
        memcpy(sp.data + 4, pcb_version, pcb_version_len);
        memcpy(sp.data + 4 + pcb_version_len, firm_version, firm_version_len);
    }
    USB_SendQueuePacket(&sp);
}

static uint32_t erase_firm()
{
    FLASH_EraseInitTypeDef erase_info;
    uint32_t error_page = 0;
    erase_info.PageAddress = FIRM_START_ADDRESS;
    erase_info.NbPages     = (FIRM_SIZE + 4) / (2 * 0x400);
    erase_info.TypeErase   = FLASH_TYPEERASE_PAGES;
    HAL_FLASH_Unlock();
    if (HAL_FLASHEx_Erase(&erase_info, &error_page) != HAL_OK) {
        HAL_FLASH_Lock();
        return error_page;
    }
    HAL_FLASH_Lock();
    return 0;
}

static void erase(packet_t const* p)
{
    nvs_put("FW_VER", (uint8_t const*)"__EMPTY__", 10, VERSION_MAX_LEN);
    uint32_t error_page = erase_firm();
    nvs_result_t nvs_res = nvs_commit();
    packet_t sp = { 0 };
    sp.type = Response;
    sp.sender_id = p->destination_id;
    sp.packet_id = p->packet_id;
    sp.op        = p->op;
    sp.len       = 2;
    sp.data[0]   = (error_page == 0) && (nvs_res == NVS_OK) ? ACK : NACK;
    sp.data[1]   = error_page & 0xFF;
    USB_SendQueuePacket(&sp);
}

static write_state_t write_state = {
    .started          = 0,
    .written_bytes    = 0,
    .firmware_version  = { 0 },
};

static void write_start(packet_t const* p)
{
    write_state.started = 1;
    write_state.written_bytes = 0;
    memcpy(write_state.firmware_version, p->data, p->len);
    packet_t sp = { 0 };
    sp.type      = Response;
    sp.sender_id = p->destination_id;
    sp.packet_id = p->packet_id;
    sp.op        = p->op;
    sp.len       = 1;
    sp.data[0]   = ACK;
    USB_SendQueuePacket(&sp);
}

static void write_data(packet_t const* p)
{
    uint32_t const base_address = FIRM_START_ADDRESS;
    packet_t sp = { 0 };
    sp.type      = Response;
    sp.sender_id = p->destination_id;
    sp.packet_id = p->packet_id;
    sp.op        = p->op;
    sp.len       = 1;

    if (!write_state.started) {
        goto send_nak;
    }

    if ((p->len % 4) != 0) {
        goto send_nak;
    }

    HAL_FLASH_Unlock(); //Unlocks the flash memory

    /* Decode the sent bytes using AES-128 ECB */
    // aes_enc_dec((uint8_t*) pucData, AES_KEY, 1);

    uint32_t d = 0;
    for (uint32_t i = 0; i < p->len; i+=4) {
        memcpy(&d, p->data+i, sizeof(uint32_t));
        if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, base_address + write_state.written_bytes, d) != HAL_OK)
        {
            HAL_FLASH_Lock();
            goto send_nak;
        }
        write_state.written_bytes += 4;
    }

    HAL_FLASH_Lock(); //Locks again the flash memory

    sp.data[0] = ACK;
    USB_SendQueuePacket(&sp);
    return;

send_nak:
    sp.data[0] = NACK;
    USB_SendQueuePacket(&sp);

}

static void write_end(packet_t const* p)
{
    uint32_t const firm_address = FIRM_START_ADDRESS;
    uint32_t const firm_size    = FIRM_SIZE;
    uint32_t const crc_address  = FIRM_CRC_ADDRESS;
    uint32_t calc_crc = 0;
    packet_t sp = { 0 };
    sp.type      = Response;
    sp.sender_id = p->destination_id;
    sp.packet_id = p->packet_id;
    sp.op        = p->op;
    sp.len       = 1;

    if (!write_state.started) {
        goto send_nak;
    }

    calc_crc = calc_crc32((uint32_t*)(firm_address), firm_size);

    HAL_FLASH_Unlock(); //Unlocks the flash memory

    if (HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, crc_address, calc_crc) != HAL_OK)
    {
        HAL_FLASH_Lock();
        goto send_nak;
    }

    HAL_FLASH_Lock();

    uint8_t next_run_mode = APP_MODE;
    if (nvs_put("RUN_MODE", &next_run_mode, 1, 1) != NVS_OK ||
        nvs_put("FW_VER", (uint8_t const*)write_state.firmware_version,
                strlen(write_state.firmware_version)+1,
                VERSION_MAX_LEN)                  != NVS_OK ||
        nvs_commit()                              != NVS_OK)
    {
        goto send_nak;
    }

    sp.data[0] = ACK;
    USB_SendQueuePacket(&sp);
    return;

send_nak:
    sp.data[0] = NACK;
    USB_SendQueuePacket(&sp);

}

static void reset(packet_t const* p)
{
    packet_t sp = { 0 };
    sp.type      = Response;
    sp.sender_id = p->destination_id;
    sp.packet_id = p->packet_id;
    sp.op        = p->op;
    sp.len       = 1;
    if (p->len != 1) {
        sp.data[0] = NACK;
        USB_SendQueuePacket(&sp);
    } else {
        uint8_t next_run_mode = (run_mode_t)(p->data[0]);
        if (nvs_put("RUN_MODE", &next_run_mode, 1, 1) == NVS_OK &&
            nvs_commit()                              == NVS_OK)
        {
            sp.data[0] = ACK;
            USB_SendQueuePacket(&sp);
            HAL_Delay(100);
            USB_DeInit();
            NVIC_SystemReset();
            HAL_Delay(500);
        } else {
            sp.data[0] = NACK;
            USB_SendQueuePacket(&sp);
        }
    }
}

void dispatch_packet(packet_t const* p)
{
    switch (p->op) {
    case OP_GET_PROFILE:
        get_profile(p);
        break;
    case OP_ERASE:
        erase(p);
        break;
    case OP_WRITE_START:
        write_start(p);
        break;
    case OP_WRITE_DATA:
        write_data(p);
        break;
    case OP_WRITE_END:
        write_end(p);
        break;
    case OP_RESET:
        reset(p);
        break;
    default:
        break;
    }
}

#ifndef __PARTITION_H
#define __PARTITION_H

#ifdef STM32F103xE

#define SRAM_SIZE 64*1024
#define SRAM_END  (SRAM_BASE + SRAM_SIZE)

#define BOOTLOADER_SIZE           (30  * 0x400)       // 30k
#define NVS_SIZE                  (2   * 0x400)       // 2k
#define FIRM_SIZE                 ((480 * 0x400) - 4) // 480k

#define BASE_ADDRESS              (0x08000000)  // start address of flash
#define BOOTLOADER_START_ADDRESS  (BASE_ADDRESS)
#define NVS_START_ADDRESS         (BOOTLOADER_START_ADDRESS + BOOTLOADER_SIZE)
#define NVS_END_ADDRESS           ((NVS_START_ADDRESS + NVS_SIZE) - 1)
#define FIRM_START_ADDRESS        (NVS_START_ADDRESS + NVS_SIZE)
#define FIRM_END_ADDRESS          ((FIRM_START_ADDRESS + FIRM_SIZE) - 1)
#define FIRM_CRC_ADDRESS          (FIRM_START_ADDRESS + FIRM_SIZE)

#endif

#endif

#ifndef __PRINTER_STEPPING_DEFS_H
#define __PRINTER_STEPPING_DEFS_H

#define DATA_NUM 384
#define STB_CNT 3
#define BUFFER_NUM 2
#define PATTERN_NUM 4
/* #define STATE_CHANGE_CNT (3) */
#define DATA_SECTION_NUM 6

#define PSC_PRINTER 0
#define PERIOD_PRINTER 7

#define __PSC_PRINTER (PSC_PRINTER+1)
#define __PERIOD_PRINTER (PERIOD_PRINTER+1)

#define PSC_STEPPING 39
#define PERIOD_STEPPING 99

#define __PSC_STEPPING (PSC_STEPPING+1)
#define __PERIOD_STEPPING (PERIOD_STEPPING+1)

#define MIN_PSC_STEPPING 19
#define MIN_PERIOD_STEPPING 99

#define MAX_PSC_STEPPING 639 // 2559，5200*200とかもいけるけど遅い
#define MAX_PERIOD_STEPPING 99

#define MT_STATE_CHANGE_COUNT ((__PSC_STEPPING*__PERIOD_STEPPING)/(__PSC_PRINTER*__PERIOD_PRINTER))

typedef enum bufState {
    NOT_PREPARED = 1, // buffer is empty or preparing
    PREPARED = 2, // buffer is completely prepared
    READING = 4, // buffer is now reading
} bufState_e;

typedef enum state{
    WAITING,       // waiting
    SENDING_DATA,  // send data by 1bit to head
    LAT_DATA,      // lat
    PRINTING,      // change stb and running motor
    FEEDING,       // when feed button is pushed(not implemented)
}state_e;


#endif

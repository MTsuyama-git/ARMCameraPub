// USBHostでUVCを扱うためのソース
#include "usb_uvc.h"

static const CamInfo CamInfoList[] = {
// Logitech C270
C270_INFO(160x120),
C270_INFO(176x144),
C270_INFO(320x176),
C270_INFO(320x240),
C270_INFO(352x288),
C270_INFO(432x240),
C270_INFO(640x480),
C270_INFO(544x288),
C270_INFO(640x360),
C270_INFO(752x416),
C270_INFO(800x448),
C270_INFO(800x600),

// Logitech C210
C210_INFO(160x120),
C210_INFO(176x144),
C210_INFO(320x176),
C210_INFO(320x240),
C210_INFO(352x288),
C210_INFO(432x240),
C210_INFO(640x480),
C210_INFO(544x288),
C210_INFO(640x360),
C210_INFO(752x416),
C210_INFO(800x448),
C210_INFO(800x600),

// Logitech Qcam Orbit AF QCAM-200R
Q200R_INFO(160x120),
Q200R_INFO(176x144),
Q200R_INFO(320x240),
Q200R_INFO(352x288),
Q200R_INFO(640x480),
Q200R_INFO(800x600),

// LifeCam VX700
VX700_INFO(160x120),
VX700_INFO(176x144),
VX700_INFO(320x240),
VX700_INFO(352x288),
VX700_INFO(640x480),

// Sonix USB 2.0 Camera
SONIX_INFO(160x120),
SONIX_INFO(176x144),
SONIX_INFO(320x240),
SONIX_INFO(352x288),
SONIX_INFO(640x480),

// Not found
{0,0,0,0},
};


typedef enum {
  NOT_CONNECTED,
  CONNECTED,
} devState_t;

typedef enum {
  NOT_FOUND,
  FOUND,
} foundState_t;

// private states
static uint8_t _cominfo_size;
static uint8_t _option;
static CamInfo* _caminfo_list=NULL;
static devState_t _dev_connected = NOT_CONNECTED; // state of connected
static USBDeviceConnected* _dev = NULL; // connected device
static USBEndpoint _ep_iso_in = NULL; // end point of usb
static int _cam_intf = -1;
static foundState_t _device_found = NOT_FOUND;
static foundState_t _cominfo_found = NOT_FOUND;

// callback
static void (*m_pCb)(uint16_t, uint8_t, int);
// static CDummy* m_pCbItem;
static void (*m_pCbMeth)(uint16_t, uint8_t*, int);

void init(uint8_t size, uint8_t option, CamInfo* user_caminfo) {
  _size = size;
  _option = option;
  if (_user_caminfo) {
    _caminfo_list = _user_caminfo;    
  }
  else {
    _caminfo_list = CamInfoList;
  }
}

static void _init()
{
#ifdef DEBUG
  USART2_Printf("USB UVC class initialize start\r\n");
#endif
  
  
}


// clear callbacks
static void clearOnResult() {
  m_pCb = NULL;
  m_pCbMeth = NULL;
}

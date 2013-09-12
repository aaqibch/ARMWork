
#include "armcmx.h"

// Strawberry Linux original lpclcd port maps

#if defined(LPCLCD)
#include "lpclcd.h"

#define SD_SPI  SPI0
#define SD_SCK  PIO1_29
#define SD_MISO PIO0_8
#define SD_MOSI PIO0_9
#define SD_CS   PIO0_2
#define SD_DETECT   PIO1_4 

#define NFC_IRQ     PIO1_5
#define NFC_RSTPD   PIN_NOT_DEFINED

#define SRAM_CS PIO1_23

#elif defined (CAPPUCCINO)
#include "cappuccino.h"

#define SD_SPI  SPI0
#define SD_SCK  PIO1_29
#define SD_MISO PIO0_8
#define SD_MOSI PIO0_9
#define SD_CS   PIO0_2
#define SD_DETECT   PIO1_16 

#define NFC_IRQ     PIO0_17
#define NFC_RSTPD   PIN_NOT_DEFINED
#define LED_USER    LED_SDBUSY

#define SRAM_CS PIO1_23
#endif


uint8 readIDInfo(ISO14443 & card, IDData & data);
uint8 writeIDInfo(ISO14443 & card, IDData & data);
void displayIDData(char *, uint8 cardtype, IDData &);

uint8 get_MifareBlock(ISO14443 & card, IDData & data, const uint8_t * key);
uint8 get_FCFBlock(ISO14443 & card, IDData & data);

const static byte IizukaKey_b[] = {
  0xBB, 0x63, 0x45, 0x74, 0x55, 0x79, 0x4B };
const static byte factory_a[] = {
  0xaa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };


#define ACCESSBITS(x)     ( ((x)[8])<<4 & 0xff0L | ((x)[7])>>4 & 0x000fL )
#define TRAILERBITS(x)    ((((x)&1L)<<3)<<8 | (((x)>>1&1L)<<3)<<4 | (((x)>>2&1L)<<3))
#define DATABLOCKBITS(x, b)    ((((x)&1L)<<(b&3))<<8 | (((x)>>1&1L)<<(b&3))<<4 | (((x)>>2&1L)<<(b&3)))

#define formattimedate(s, t, d)  (sprintf((char*)(s), " [%02x:%02x:%02x %02x/%02x/20%02x]", \
                  t>>16&0x3f, t>>8&0x7f, t&0x7f, d>>8&0x1f, d&0x3f, d>>16&0xff) )


void parse_do_command(StringStream & stream) ;

struct Tasks {
  uint32 timer_master; 
  uint32 timer_serial;
  uint32 timer_rtc;
  uint32 timer_nfc; 
  uint32 timer_lcdlight;
  
  boolean update() {
    if ( timer_master != millis() ) {
      timer_master = millis();
      if ( timer_serial )
        timer_serial--;
      if ( timer_rtc ) 
        timer_rtc--;
      if ( timer_nfc )
        timer_nfc--;
      if ( timer_lcdlight )
        timer_lcdlight--;
      return true;
    }
    return false;
  }
  
  boolean serial() {
    if ( timer_serial > 0 )
      return false;
    timer_serial = 3;
    return true;
  }
  
  boolean rtc() {
    if ( timer_rtc > 0 )
      return false;
    timer_rtc = 73;
    return true;
  }
  
  boolean nfc() {
    if ( timer_nfc > 0 )
      return false;
    timer_nfc = 667;
    return true;
  }
  
  boolean lcdlight() {
    if ( timer_lcdlight > 0 )
      return false;
    timer_lcdlight = 1000;
    return true;
  }
  
} task;



struct KeyID {
  uint8 raw[16];
  
static const uint32 BASE_OFFSET_ADDR = 0x000010;

KeyID() {
    memset(raw, 0x20, 10);
    setExpdate(0);
    raw[14] = 0;
    raw[15] = 0;
  }
  
  void setExpdate(uint32 date) {
    raw[10] = date>>24 & 0xff;
    raw[11] = date>>16 & 0xff;
    raw[12] = date>>8 & 0xff;
    raw[13] = date & 0xff;
  }

  uint32 getExpdate() {
    uint32 d;
    d = raw[10];
    d = (d<<8) | raw[11];
    d = (d<<8) | raw[12];
    d = (d<<8) | raw[13];
    return d;
  }
  
  uint8 setChecksum() {
    int i;
    uint8 xsum = 0;
    for (i = 0; i < 15; i++) {
      xsum ^= raw[i];
    }
    raw[15] = xsum;
    return raw[15];
  }
  
  uint8 check() {
    int i;
    uint8 chksum = 0;
    for (i = 0; i < 16; i++) {
      chksum ^= raw[i];
    }
    return chksum == 0;
  }

  uint32 storeAddress(uint16 num){
    return (num<<4) + BASE_OFFSET_ADDR;
  }
};
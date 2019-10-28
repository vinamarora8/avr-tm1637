#include <inttypes.h>
#include "tm1637.h"
#include "tm1637_display.h"

uint8_t TM1637_init() {
  uint8_t ret;
  TM1637_sendStart();
  ret = TM1637_sendByte(0b01000000);
  TM1637_sendStop();

  return ret;
}

uint8_t TM1637_displaySetting(uint8_t on, uint8_t brightness) {

  uint8_t ret;
  
  if (on != 0)
    on = 0x08;

  brightness &= 0x7;
  
  TM1637_sendStart();
  ret = TM1637_sendByte(0b10000000 | on | brightness);
  TM1637_sendStop();

  return ret;
}

uint8_t TM1637_writeNumber(uint16_t num, uint8_t dp) {

  uint8_t ret, curr_ret;
  
  if (dp != 0)
    dp = 0x80;

  TM1637_sendStart();
  ret = TM1637_sendByte(0b11000000);  
  

  uint8_t curr_dig;
  for (uint8_t i = 0; i<4; i++) {    
    curr_dig = num/1000;
    curr_ret = TM1637_sendByte(TM1637_digitToSegment[curr_dig] | dp);
    if (!curr_ret)
      ret = 0;
    num = (num - curr_dig*1000)*10;
  }
  
  TM1637_sendStop();

  return ret;
}


const uint8_t TM1637_digitToSegment[] = {
 // XGFEDCBA
  0b00111111,    // 0
  0b00000110,    // 1
  0b01011011,    // 2
  0b01001111,    // 3
  0b01100110,    // 4
  0b01101101,    // 5
  0b01111101,    // 6
  0b00000111,    // 7
  0b01111111,    // 8
  0b01101111,    // 9
  0b01110111,    // A
  0b01111100,    // b
  0b00111001,    // C
  0b01011110,    // d
  0b01111001,    // E
  0b01110001     // F
  };

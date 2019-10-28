#include <avr/io.h>                     /* Defines pins, ports, etc */
#include <util/delay.h>                 /* Functions to waste time */
#include "tm1637.h"
#include "tm1637_display.h"


int main(void) {
  
  DDRD |= _BV(PD7);
  PORTD |= _BV(7);

  TM1637_init();
  TM1637_displaySetting(1, 7);

  for (int i = 0; i<100000; i++) {
    TM1637_writeNumber(i, 0);
    i = i%10000;
    _delay_ms(1);
  }

  
  return 0;
}

#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */
#include "tm1637.h"


// sendByte(const uint8_t);
uint8_t TM1637_sendByte(const uint8_t b) {

  uint8_t data = b;

  // Set DIO as outputs (CLK is assumed to be output, and low)
  TM1637_DIO_DDR |= (1 << TM1637_DIO);
  TM1637_CLK_DDR |= (1 << TM1637_CLK);

  // Write DIO, wait, pull clock up, wait, pull clock down      
  for (uint8_t i = 0; i < 8; i++) {

    if (data & 0x01)
      TM1637_DIO_PORT |= (1 << TM1637_DIO);
    else
      TM1637_DIO_PORT &= ~(1 << TM1637_DIO);

    _delay_us(TM1637_CLK_PERIOD/2);
    TM1637_CLK_PORT |= (1 << TM1637_CLK);
    _delay_us(TM1637_CLK_PERIOD/2);
    TM1637_CLK_PORT &= ~(1 << TM1637_CLK);

    data = data >> 1;
  }

  // Check ACK
  // DIO as input, wait, read DIO
  TM1637_DIO_DDR &= ~(1 << TM1637_DIO);
  _delay_us(TM1637_CLK_PERIOD);
  uint8_t ack = (bit_is_clear(TM1637_DIO_PIN, TM1637_DIO) != 0);

  // Pulse clock once, and pull DIO low
  // (tm1637 will leave DIO after this clock's negedge)
  TM1637_CLK_PORT |= (1 << TM1637_CLK);
  _delay_us(TM1637_CLK_PERIOD/2);
  TM1637_CLK_PORT &= ~(1 << TM1637_CLK);
  
  TM1637_DIO_PORT &= ~(1 << TM1637_DIO);
  TM1637_DIO_DDR |= (1 << TM1637_DIO);
  
  _delay_us(TM1637_CLK_PERIOD/2);

  
  return ack;

}


void TM1637_sendStart() {
  // CLK and DIO are set to outputs
  TM1637_DIO_DDR |= (1 << TM1637_DIO);
  TM1637_DIO_PORT &= ~(1 << TM1637_DIO);
  _delay_us(TM1637_CLK_PERIOD); 
  TM1637_CLK_DDR |= (1 << TM1637_CLK);
  TM1637_CLK_PORT &= ~(1 << TM1637_CLK);
  _delay_us(TM1637_CLK_PERIOD);  
 
}

void TM1637_sendStop() {
  // CLK and DIO are set to outputs
  TM1637_CLK_DDR |= (1 << TM1637_CLK);
  TM1637_DIO_DDR |= (1 << TM1637_DIO);

  // clk is assumed to be low
  TM1637_CLK_PORT |= (1 << TM1637_CLK);
  _delay_us(TM1637_CLK_PERIOD);
  TM1637_DIO_PORT |= (1 << TM1637_DIO);
  _delay_us(TM1637_CLK_PERIOD);
  
  TM1637_CLK_DDR &= ~(1 << TM1637_CLK);    
  TM1637_DIO_DDR &= ~(1 << TM1637_DIO);
}

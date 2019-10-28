#include <avr/io.h>                        /* Defines pins, ports, etc */
#include <util/delay.h>                     /* Functions to waste time */

#ifndef TM1637_CLK
#    define TM1637_CLK PC5
#endif

#ifndef TM1637_DIO
#    define TM1637_DIO PC4
#endif

#ifndef TM1637_CLK_DDR
#    define TM1637_CLK_DDR DDRC
#endif

#ifndef TM1637_DIO_DDR
#    define TM1637_DIO_DDR DDRC
#endif

#ifndef TM1637_DIO_PORT
#    define TM1637_DIO_PORT PORTC
#endif

#ifndef TM1637_CLK_PORT
#    define TM1637_CLK_PORT PORTC
#endif

#ifndef TM1637_DIO_PIN
#    define TM1637_DIO_PIN PINC
#endif

#ifndef TM1637_CLK_PERIOD
#    define TM1637_CLK_PERIOD 2 /* microseconds */
#endif

uint8_t TM1637_sendByte(const uint8_t);
void TM1637_sendStart(void);
void TM1637_sendStop(void);
  


const uint8_t TM1637_digitToSegment[16];

uint8_t TM1637_init(void);
uint8_t TM1637_displaySetting(uint8_t, uint8_t);
uint8_t TM1637_writeNumber(uint16_t, uint8_t);

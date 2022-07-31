#ifndef SCD4X_HPP
#define SCD4X_HPP

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <stdio.h>

/* SCD4x default i2c address */
const uint8_t SCD4X_DEFAULT_ADDR = 0x62;

class SCD4x {
public:
  SCD4x(i2c_inst_t *_i2c_num);
  SCD4x(i2c_inst_t *_i2c_num, uint8_t _i2c_address);
  uint8_t generate_crc(const uint8_t *data, uint16_t count);

private:
  /* SCD4x user settings */
  const i2c_inst_t *i2c_num;
  const uint8_t i2c_address;

  /* SCD4x commands */
  const uint16_t SCD4X_REINIT = 0x3646;
  const uint16_t SCD4X_FACTORYRESET = 0x3632;
  const uint16_t SCD4X_FORCEDRECAL = 0x362F;
  const uint16_t SCD4X_SELFTEST = 0x3639;
  const uint16_t SCD4X_DATAREADY = 0xE4B8;
  const uint16_t SCD4X_STOPPERIODICMEASUREMENT = 0x3F86;
  const uint16_t SCD4X_STARTPERIODICMEASUREMENT = 0x21B1;
  const uint16_t SCD4X_STARTLOWPOWERPERIODICMEASUREMENT = 0x21AC;
  const uint16_t SCD4X_READMEASUREMENT = 0xEC05;
  const uint16_t SCD4X_SERIALNUMBER = 0x3682;
  const uint16_t SCD4X_GETTEMPOFFSET = 0x2318;
  const uint16_t SCD4X_SETTEMPOFFSET = 0x241D;
  const uint16_t SCD4X_GETALTITUDE = 0x2322;
  const uint16_t SCD4X_SETALTITUDE = 0x2427;
  const uint16_t SCD4X_SETPRESSURE = 0xE000;
  const uint16_t SCD4X_PERSISTSETTINGS = 0x3615;
  const uint16_t SCD4X_GETASCE = 0x2313;
  const uint16_t SCD4X_SETASCE = 0x2416;

  /* SCD4x checksum parameters */
  const uint8_t CRC8_POLYNOMIAL = 0x31;
  const uint8_t CRC8_INIT = 0xFF;
};
#endif

#ifndef SCD4X_HPP
#define SCD4X_HPP

#include "hardware/i2c.h"
#include "pico/stdlib.h"
#include <stdio.h>

/* SCD4x default i2c address */
const uint8_t SCD4X_DEFAULT_ADDR = 0x62;

class SCD4x {
 public:
  SCD4x(i2c_inst_t* _i2c_num);
  SCD4x(i2c_inst_t* _i2c_num, uint8_t _i2c_address);
  int co2();
  float temperature();
  float relative_humidity();
  bool data_ready();

 private:
  /* SCD4x user settings */
  i2c_inst_t* i2c_num;
  const uint8_t i2c_address;

  /* SCD4x commands */
  const uint8_t SCD4X_REINIT[2] = { 0x36, 0x46 };                           /* 0x3646 */
  const uint8_t SCD4X_FACTORYRESET[2] = { 0x36, 0x32 };                     /* 0x3632 */
  const uint8_t SCD4X_FORCEDRECAL[2] = { 0x36, 0x2F };                      /* 0x362F */
  const uint8_t SCD4X_SELFTEST[2] = { 0x36, 0x39 };                         /* 0x3639 */
  const uint8_t SCD4X_DATAREADY[2] = { 0xE4, 0xB8 };                        /* 0xE4B8 */
  const uint8_t SCD4X_STOPPERIODICMEASUREMENT[2] = { 0x3F, 0x86 };          /* 0x3F86 */
  const uint8_t SCD4X_STARTPERIODICMEASUREMENT[2] = { 0x21, 0xB1 };         /* 0x21B1 */
  const uint8_t SCD4X_STARTLOWPOWERPERIODICMEASUREMENT[2] = { 0x21, 0xAC }; /* 0x21AC */
  const uint8_t SCD4X_READMEASUREMENT[2] = { 0xEC, 0x05 };                  /* 0xEC05 */
  const uint8_t SCD4X_SERIALNUMBER[2] = { 0x36, 0x82 };                     /* 0x3682 */
  const uint8_t SCD4X_GETTEMPOFFSET[2] = { 0x23, 0x18 };                    /* 0x2318 */
  const uint8_t SCD4X_SETTEMPOFFSET[2] = { 0x24, 0x1D };                    /* 0x241D */
  const uint8_t SCD4X_GETALTITUDE[2] = { 0x23, 0x22 };                      /* 0x2322 */
  const uint8_t SCD4X_SETALTITUDE[2] = { 0x24, 0x27 };                      /* 0x2427 */
  const uint8_t SCD4X_SETPRESSURE[2] = { 0xE0, 0x00 };                      /* 0xE000 */
  const uint8_t SCD4X_PERSISTSETTINGS[2] = { 0x36, 0x15 };                  /* 0x3615 */
  const uint8_t SCD4X_GETASCE[2] = { 0x23, 0x13 };                          /* 0x2313 */
  const uint8_t SCD4X_SETASCE[2] = { 0x24, 0x16 };                          /* 0x2416 */

  /* SCD4x checksum parameters */
  const uint8_t CRC8_POLYNOMIAL = 0x31;
  const uint8_t CRC8_INIT = 0xFF;

  /* Member variables */
  // uint8_t recv_buf[2] = {0, 0};
  const uint I2C_DEFAULT_TIMEOUT_US = 600;
  int _co2 = -1;
  float _temperature = 9999;
  float _relative_humidity = -1;

  /* Member functions */
  int _send_command(const uint8_t* cmd);
  int _send_command(const uint8_t* cmd, uint64_t cmd_delay_us);
  int _send_command(const uint8_t* cmd, uint timeout_us, uint64_t cmd_delay_us);
  int _read_reply(uint8_t* buf, int byte_num, uint timeout_us);
  int _read_reply(uint8_t* buf, int byte_num);
  void _read_data();
  bool _check_crc(uint8_t* buf);
  uint8_t _generate_crc(const uint8_t* data, uint16_t count);
};
#endif

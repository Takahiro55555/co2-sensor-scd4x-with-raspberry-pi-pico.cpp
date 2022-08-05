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
  bool update();

 private:
  /* SCD4x user settings */
  i2c_inst_t* i2c_num;
  const uint8_t i2c_address;

  /* SCD4x commands */
  const static int COMMAND_BYTES = 2;
  const uint8_t SCD4X_REINIT[COMMAND_BYTES] = { 0x36, 0x46 };                           /* 0x3646 */
  const uint8_t SCD4X_FACTORYRESET[COMMAND_BYTES] = { 0x36, 0x32 };                     /* 0x3632 */
  const uint8_t SCD4X_FORCEDRECAL[COMMAND_BYTES] = { 0x36, 0x2F };                      /* 0x362F */
  const uint8_t SCD4X_SELFTEST[COMMAND_BYTES] = { 0x36, 0x39 };                         /* 0x3639 */
  const uint8_t SCD4X_DATAREADY[COMMAND_BYTES] = { 0xE4, 0xB8 };                        /* 0xE4B8 */
  const uint8_t SCD4X_STOPPERIODICMEASUREMENT[COMMAND_BYTES] = { 0x3F, 0x86 };          /* 0x3F86 */
  const uint8_t SCD4X_STARTPERIODICMEASUREMENT[COMMAND_BYTES] = { 0x21, 0xB1 };         /* 0x21B1 */
  const uint8_t SCD4X_STARTLOWPOWERPERIODICMEASUREMENT[COMMAND_BYTES] = { 0x21, 0xAC }; /* 0x21AC */
  const uint8_t SCD4X_READMEASUREMENT[COMMAND_BYTES] = { 0xEC, 0x05 };                  /* 0xEC05 */
  const uint8_t SCD4X_SERIALNUMBER[COMMAND_BYTES] = { 0x36, 0x82 };                     /* 0x3682 */
  const uint8_t SCD4X_GETTEMPOFFSET[COMMAND_BYTES] = { 0x23, 0x18 };                    /* 0x2318 */
  const uint8_t SCD4X_SETTEMPOFFSET[COMMAND_BYTES] = { 0x24, 0x1D };                    /* 0x241D */
  const uint8_t SCD4X_GETALTITUDE[COMMAND_BYTES] = { 0x23, 0x22 };                      /* 0x2322 */
  const uint8_t SCD4X_SETALTITUDE[COMMAND_BYTES] = { 0x24, 0x27 };                      /* 0x2427 */
  const uint8_t SCD4X_SETPRESSURE[COMMAND_BYTES] = { 0xE0, 0x00 };                      /* 0xE000 */
  const uint8_t SCD4X_PERSISTSETTINGS[COMMAND_BYTES] = { 0x36, 0x15 };                  /* 0x3615 */
  const uint8_t SCD4X_GETASCE[COMMAND_BYTES] = { 0x23, 0x13 };                          /* 0x2313 */
  const uint8_t SCD4X_SETASCE[COMMAND_BYTES] = { 0x24, 0x16 };                          /* 0x2416 */

  /* SCD4x checksum parameters */
  const uint8_t CRC8_POLYNOMIAL = 0x31;
  const uint8_t CRC8_INIT = 0xFF;

  /* Member variables */
  // uint8_t recv_buf[2] = {0, 0};
  const uint I2C_DEFAULT_TIMEOUT_US = 6000;
  int _co2 = -1;
  float _temperature = 9999;
  float _relative_humidity = -1;

  /* Member functions */
  int _snprint_buf(char *str, uint16_t str_size, uint8_t *buf, uint16_t buf_size);
  int _send_command(const uint8_t* cmd);
  int _send_command(const uint8_t* cmd, uint64_t cmd_delay_us);
  int _send_command(const uint8_t* cmd, uint timeout_us, uint64_t cmd_delay_us);
  int _read_reply(uint8_t* buf, int byte_num, uint timeout_us);
  int _read_reply(uint8_t* buf, int byte_num);
  void _read_data();
  uint8_t _generate_crc(const uint8_t* data, uint16_t count);
};
#endif

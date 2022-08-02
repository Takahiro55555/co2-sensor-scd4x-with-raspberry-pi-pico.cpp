#include "scd4x.hpp"

SCD4x::SCD4x(i2c_inst_t* _i2c_num) : i2c_num(_i2c_num), i2c_address(SCD4X_DEFAULT_ADDR) {}

SCD4x::SCD4x(i2c_inst_t* _i2c_num, uint8_t _i2c_address)
  : i2c_num(_i2c_num), i2c_address(_i2c_address)
{
}

uint8_t SCD4x::generate_crc(const uint8_t* data, uint16_t count)
{
  uint16_t current_byte;
  uint8_t crc = CRC8_INIT;
  uint8_t crc_bit;
  /* calculates 8-Bit checksum with given polynomial */
  for(current_byte = 0; current_byte < count; ++current_byte) {
    crc ^= (data[current_byte]);
    for(crc_bit = 8; crc_bit > 0; --crc_bit) {
      if(crc & 0x80)
        crc = (crc << 1) ^ CRC8_POLYNOMIAL;
      else
        crc = (crc << 1);
    }
  }
  return crc;
}

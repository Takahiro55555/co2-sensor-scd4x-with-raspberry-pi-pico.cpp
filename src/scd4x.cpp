#include "scd4x.hpp"

SCD4x::SCD4x(i2c_inst_t* _i2c_num) : i2c_num(_i2c_num), i2c_address(SCD4X_DEFAULT_ADDR) {}

SCD4x::SCD4x(i2c_inst_t* _i2c_num, uint8_t _i2c_address)
  : i2c_num(_i2c_num), i2c_address(_i2c_address)
{
}

int SCD4x::co2()
{
  if(data_ready()) {
    _read_data();
  }
  return _co2;
}

float SCD4x::temperature()
{
  if(data_ready()) {
    _read_data();
  }
  return _temperature;
}
float SCD4x::relative_humidity()
{
  if(data_ready()) {
    _read_data();
  }
  return _relative_humidity;
}

int SCD4x::_send_command(const uint8_t* cmd)
{
  return _send_command(cmd, I2C_DEFAULT_TIMEOUT_US, 0);
}

int SCD4x::_send_command(const uint8_t* cmd, uint64_t cmd_delay_us)
{
  return _send_command(cmd, I2C_DEFAULT_TIMEOUT_US, cmd_delay_us);
}

int SCD4x::_send_command(const uint8_t* cmd, uint timeout_us, uint64_t cmd_delay_us)
{
  int byte_num = 2;
  int i2c_result = i2c_write_timeout_us(i2c_num, i2c_address, cmd, byte_num, false, timeout_us);
  sleep_us(cmd_delay_us);
  return i2c_result;
}

int SCD4x::_read_reply(uint8_t* buf, int byte_num)
{
  return _read_reply(buf, byte_num, I2C_DEFAULT_TIMEOUT_US);
}

int SCD4x::_read_reply(uint8_t* buf, int byte_num, uint timeout_us)
{
  int i2c_result = i2c_read_timeout_us(i2c_num, i2c_address, buf, byte_num, false, timeout_us);
  return i2c_result;
}

bool SCD4x::data_ready()
{
  _send_command(SCD4X_DATAREADY);
  uint8_t buf[2] = { 0 };
  _read_reply(buf, 2, 1000);
  return !((buf[0] & 0x07 == 0) and (buf[1] == 0));
}

void SCD4x::_read_data()
{
  uint8_t buf[9] = { 0 };
  _send_command(SCD4X_READMEASUREMENT, 1000);
  _read_reply(buf, 9);
  printf("_read_data(), %x %x %x %x %x %x\n", buf[0], buf[1], buf[3], buf[4], buf[6], buf[7]);
  _co2 = ((int)buf[0] << 8) | (int)buf[1];
  int temp = ((int)buf[3] << 9) | buf[4];
  _temperature = -45 + 175 * ((float)temp / 0x10000);
  int humi = ((int)buf[6] << 8) | (int)buf[7];
  _relative_humidity = 100 * ((float)humi / 0x10000);
}

bool SCD4x::_check_crc(uint8_t* buf)
{
  /* ToDo: 未実装 */
  return true;
}

uint8_t SCD4x::_generate_crc(const uint8_t* data, uint16_t count)
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

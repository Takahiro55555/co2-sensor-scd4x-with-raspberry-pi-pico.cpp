#include "scd4x.hpp"

int main()
{
  /* Pico settings */
  const int SDA_PIN = 26; /* GP26 = Pin.31 = I2C1 SDA */
  const int SCL_PIN = 27; /* GP27 = Pin.32 = I2C1 SCL */
  i2c_inst_t* i2c_num = i2c1;

  stdio_init_all();
  i2c_init(i2c_num, 100000);                  // use i2c1 module, SCL = 100kHz
  gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);  // set function of SDA_PIN I2C
  gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);  // set function of SCL_PIN I2C
  gpio_set_pulls(SDA_PIN, true, false);       // enable internal pull-up of SDA_PIN
  gpio_set_pulls(SCL_PIN, true, false);       // enable internal pull-up of SCL_PIN

  // sleep_ms(2000);
  SCD4x scd4x = SCD4x(i2c_num);
  while(1) {
    if(scd4x.update()) {
      printf("%d [ppm], %f [C], %f [%%]\n", scd4x.co2(), scd4x.temperature(), scd4x.relative_humidity());
    }
    sleep_ms(1000);
  }

  return 0;
}

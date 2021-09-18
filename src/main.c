/**
 * Make sure to include "pico_multicore" in the "target_link_libraries" in
 * CMakeLists.txt You may need to re-run "cmake .." from the build folder
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "lcd.h"

const uint LED_PIN25 = 25;
const uint LED_PIN14 = 14;

// void
// core1_entry()
// {
//   gpio_init(LED_PIN14);
//   gpio_set_dir(LED_PIN14, GPIO_OUT);
//   while (true) {
//     gpio_put(LED_PIN14, 1);
//     sleep_ms(250);
//     gpio_put(LED_PIN14, 0);
//     sleep_ms(250);
//   }
// }

void
core1_entry()
{
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || \
    !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
  // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
  i2c_init(i2c_default, 100 * 1000);
  gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
  gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
  gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
  gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

  // Make the I2C pins available to picotool
  bi_decl(bi_2pins_with_func(
      PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

  lcd_init();

  static char *message[] = { "Running", "this loop", "on", "Core 1" };

  while (1) {
    for (int m = 0; m < sizeof(message) / sizeof(message[0]); m += MAX_LINES) {
      for (int line = 0; line < MAX_LINES; line++) {
        lcd_set_cursor(line, (MAX_CHARS / 2) - strlen(message[m + line]) / 2);
        lcd_string(message[m + line]);
      }
      sleep_ms(2000);
      lcd_clear();
    }
  }
#endif
}

int
main()
{
  stdio_init_all();

  multicore_launch_core1(core1_entry);

  gpio_init(LED_PIN25);
  gpio_set_dir(LED_PIN25, GPIO_OUT);

  while (true) {
    gpio_put(LED_PIN25, 1);
    sleep_ms(1000);
    gpio_put(LED_PIN25, 0);
    sleep_ms(1000);
  }
  return 0;
}

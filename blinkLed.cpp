#include <iostream>
#include <chrono>
#include <thread>
#include <gpiod.h>

int main() {
  // Name of GPIO chip
  const char* chipname = "gpiochip0";

  // Use GPIO18 as pin
  constexpr unsigned int led_line_offset = 18;

  // Open GPIO chip
  gpiod_chip* chip = gpiod_chip_open_by_name(chipname);
  if (!chip) {
    std::cerr << "Error: could not open chip " << chipname << std::endl;
    return 1;
  }

  // Get the line (pin) corresponding to our LED
  gpiod_line* led_line = gpiod_chip_get_line(chip, led_line_offset);
  if (!led_line) {
    std::cerr << "Error: could not request line as output." << std::endl;
    gpiod_chip_close(chip);
    return 1;
  }
  
  // Set line as output
  int ret = gpiod_line_request_output(led_line, "blink-led", 0);
  if (ret != 0) {
    std::cerr << "Error: could not request line as output." << std::endl;
    gpiod_chip_close(chip);
    return 1;
  }

  // Blink the LED 10 times
  for (int i = 0; i < 20; i++) {
    // Turn LED on
    gpiod_line_set_value(led_line, 1);
    std::cout << "LED ON" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // Turn LED off
    gpiod_line_set_value(led_line, 0);
    std::cout << "LED OFF" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  // Release the line and close the chip
  gpiod_line_release(led_line);
  gpiod_chip_close(chip);

  return 0;
}

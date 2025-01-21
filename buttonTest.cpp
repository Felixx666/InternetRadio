#include <iostream>
#include <chrono>
#include <thread>
#include <gpiod.h>

int main() {
  // Name of the GPIO chip.
  const char* chipname = "gpiochip0";

  // GPIO line offset for GPIO17.
  constexpr unsigned int line_offset = 17;

  // Open the chip
  gpiod_chip *chip = gpiod_chip_open_by_name(chipname);
  if (!chip) {
    std::cerr << "Failed to open" << chipname << std::endl;
  }

  // Get the line (pin) object
  gpiod_line* line = gpiod_chip_get_line(chip, line_offset);
  if (!line) {
    std::cerr << "Error: could not get line" << line_offset << std::endl;
    gpiod_chip_close(chip);
    return 1;
  }

  int flags = GPIOD_LINE_REQUEST_FLAG_BIAS_PULL_UP;

  int ret = gpiod_line_request_input_flags(line, "my-button-reader", flags);
  if (ret < 0) {
    std::cerr << "Error: could not request line as input (pull-up)." <<
      std::endl;
    gpiod_chip_close(chip);
    return 1;
  }
  
  std::cout << "Reading GPIO" << line_offset << " whith internal pullup. " 
    << "Press the button (connected to GND) to see changes.\n";

  // Read in a loop
  for (int i = 0; i < 20; ++i) {
    // Gett the current vlaue of the line: 1 == High, 0 = LOW
    int value = gpiod_line_get_value(line);
    if (value < 0) {
      std::cerr << "Error: could not read line value." << std::endl;
      break;
    }

    std::cout << "GPIO" << line_offset << " value: " << value << std::endl;

    // Wait half a secod
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  gpiod_line_release(line);
  gpiod_chip_close(chip);

  return 0;
}

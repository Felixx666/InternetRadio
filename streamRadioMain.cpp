#include <limits>
#include <iostream>

#include "streamRadio.h"

int main() {
  StreamRadio radio;

  radio.startStream("swr3");

  std::cout << "Playing" << std::endl;
  std::cout << "Press Enter to stop." << std::endl;

  // Wait for user input befor stopping playback.
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  radio.stopStream();
}


#include <wiringPi.h>
#include <iostream>

#define LED_PIN 17 // GPIO 17

int main() {
  // Initialize pigpio
  if (wiringPiSetupGpio() == -1) {
    std::cerr << "Failed to initialize wiringPi!" << std::endl;
    return 1;
  }

  // Set the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Blink the LED
  for (int i = 0; i < 15; ++i) {
    digitalWrite(LED_PIN, HIGH); // Turn on
    delay(1000);                 // Wait one second 
    digitalWrite(LED_PIN, LOW);  // Turn off
    delay(1000);                 // Wait one second
  }

  return 0;
}

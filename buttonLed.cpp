#include <wiringPi.h>
#include <iostream>
#include <signal.h>
#include <atomic>

// Atomic flag to indicate if the program should keep running
std::atomic<bool> running(true);

// Signal handler function
void signalHandler(int signal) {
  if (signal == SIGINT) {
    running = false; // Set the flag to false to stop the loop
  }
}

#define BUTTON_PIN 17   // GPIO 17
#define LED_PIN 18   // GPIO 18

int main() {
  // initialize wiringPi
  if (wiringPiSetupGpio() == -1) {
    std::cerr << "Failed to initialize wiringPi!" << std::endl;
    return 1;
  }

  // Set up the LED pin as output
  pinMode(BUTTON_PIN, INPUT);
  pullUpDnControl(BUTTON_PIN, PUD_UP); // Enable internal pull-up resistor.

  // Set up the LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // Register the signal handler for SIGINT (Ctrl+C)
  signal(SIGINT, signalHandler);

  std::cout << "Press the button to turn the LED. Press Ctrl+C exit."
    << std::endl;

  while (running) {
    // Read the button state
    if (digitalRead(BUTTON_PIN) == LOW) { // Button is pressed active low)
      digitalWrite(LED_PIN, HIGH);        // Turn on the LED
    } else {
      digitalWrite(LED_PIN, LOW);         // Turn off the LED
    }
    delay(10); // Small delay to debounce the button
    std::cout << digitalRead(BUTTON_PIN) << std::endl;
  }

  // Clean up GPIO
  digitalWrite(LED_PIN, LOW); // Turn off the LED
  pinMode(LED_PIN, INPUT);    // Set LED pin back to input mode
  std::cout << "\nProgramm stopped. GPIO cleaned up." << std::endl;

  return 0;
}

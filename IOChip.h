#ifndef IOCHIP_H
#define IOCHIP_H

#include <string>
#include <vector>

class IOChip() {
 public:
  // Constructor
  IOChip(const char* chipname);

  // Destructor
  ~IOChip()

  // Add a button connected to given pin as given name
  void addButton(int pin, std::string name);

  // Add a LED connected to given pin as given name
  void addLED(int pin, std::string name);

  // Read Button state of given button
  bool readButton(std::string name);
  
  // Turn given LED on
  void LEDOn(std::string name);

  // Turn given LED off
  void LEDOff(std::string name);

 private:
  // Vector of buttons
  std::vector<string> _buttons;

  // Vector of LEDs
  std::vector<string> _LEDs;
}

#endif // IOCHIP_H

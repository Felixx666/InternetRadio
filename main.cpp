#include <unistd.h>
#include <iostream>
#include <wiringPi.h>
#include <signal.h>
#include <atomic>
#include <string>
#include <map>
#include <thread>
#include <chrono>
#include "streamRadio.h"

#define BUTTON1_PIN 17
#define LED_PIN 18

void initSetup() {
  if (wiringPiSetupGpio() == -1) {
    std::cerr << "WiringPi setup failed." << std::endl;
  }
  pinMode(BUTTON1_PIN, INPUT);
  pullUpDnControl(BUTTON1_PIN, PUD_UP);
}

// Atomic flag to indicate if the program should keep running
std::atomic<bool> running(true);

// Signal handler function
void signalHandler(int signal) {
  if (signal == SIGINT) {
    running = false; // Set the flag to false to stop the loop
  }
}

// Init radio channels
std::map<int, std::string> initChannels() {
  // Radio channels:
  std::map<int, std::string> channels;
  channels[0] = "swr3";
  channels[1] = "swr2";
  channels[2] = "swr4";
  channels[3] = "Radio Regenbogen";
  channels[4] = "badenfm";
  return channels;
}

std::map<int, std::string> channels = initChannels();
int nbChannels = channels.size();
std::atomic<int> channel{0};

StreamRadio radio;

// Init a worker to run stream in a seperate thread.
std::atomic<bool> runningStream{true};
void streamWorker() {
  while (true) {
    int currentChannel = channel.load(); 
    radio.startStream(channels[currentChannel]);
  }
  std::cout << "Worker thread exiting." << std::endl;
}




int main() {
  initSetup();
  signal(SIGINT, signalHandler);
  std::cout << "Press Ctrl+C exit." << std::endl;
  radio.startStream(channels[channel]);
  while (running) {
    // Read the button state
    if (digitalRead(BUTTON1_PIN) == LOW) {
      channel = (channel + 1) % nbChannels;
      radio.stopStream();
      delay(1000);
      radio.startStream(channels[channel]);
    }
    std::cout << channels[channel] << std::endl;
    delay(100);
  }
  return 0;
}

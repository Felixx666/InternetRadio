#ifndef DISPLAY_H
#define DISPLAY_H

#include <cstdint>
#include <string>

#include <linux/i2c-dev.h>

class Display {
 public:
  void init();

  void printStringScaled(const std::string &str, int x, int y, int scale);

  void clear();

 private:
  const char *i2cDevice = "/dev/i2c-1";
  int fd;
};


#endif // DISPLAY_H

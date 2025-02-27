#include "display.h"
#include <unistd.h>

int main() {
  Display display;
  display.init();
  display.printStringScaled("Huhu", 0, 0, 2);
  usleep(2'000'000);
  display.clear();
}

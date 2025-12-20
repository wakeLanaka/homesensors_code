#include "./include/GpioController.h"
#include <chrono>
#include <gpiod.hpp>
#include <thread>

#define CHIPNAME "/dev/gpiochip0"
#define PIN 16

int main(int, char **) {
  gpiod::chip chip{CHIPNAME};
  GpioController gpio16{chip};

  gpio16.setup(PIN, false);

  while (1) {
    gpio16.toggle_value();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

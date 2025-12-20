#include "../include/GpioController.h"
#include <cstdint>
#include <gpiod.hpp>

GpioController::GpioController(gpiod::chip const &chip) : chip{chip} {}

int GpioController::setup(int8_t pin, bool isInput) {
  line = chip.get_line(pin);
  if (!line || line.is_requested() || line.is_used()) {
    return -1;
  }

  isInput ? line.set_direction_input() : line.set_direction_output();
  return 0;
}

int GpioController::get_value() const { return line.get_value(); }
void GpioController::set_value(int value) const { line.set_value(value); }
void GpioController::toggle_value() const { line.set_value(!line.get_value()); }

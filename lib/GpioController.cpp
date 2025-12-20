#include "../include/GpioController.h"
#include <cstdint>
#include <gpiod.hpp>

GpioController::GpioController(gpiod::chip const &chip) : chip{chip} {}

int GpioController::setup(int8_t pin, bool isInput) {
  line = chip.get_line(pin);
  if (!line) {
    return -1;
  } else if (line.is_used()) {
    return -2;
  }

  gpiod::line_request request;
  request.consumer = "homesensors-app";

  if (isInput) {
    request.request_type = gpiod::line_request::DIRECTION_INPUT;
  } else {
    request.request_type = gpiod::line_request::DIRECTION_OUTPUT;
  }
  line.request(request);

  return 0;
}

int GpioController::get_value() const { return line.get_value(); }
void GpioController::set_value(int value) const { line.set_value(value); }
void GpioController::toggle_value() const { line.set_value(!line.get_value()); }

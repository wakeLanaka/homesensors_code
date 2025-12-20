#ifndef __GPIOCONTROLLER_H_
#define __GPIOCONTROLLER_H_

#include <gpiod.hpp>

struct GpioController {

  GpioController(gpiod::chip const &chip);
  int setup(int8_t const pin, bool const isInput = true);
  int get_value() const;
  void set_value(int const value) const;
  void toggle_value() const;

private:
  gpiod::chip chip;
  gpiod::line line;
};

#endif

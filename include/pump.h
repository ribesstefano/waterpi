#ifndef WATERPI_PUMP_H_
#define WATERPI_PUMP_H_

#include <vector>
#include "wiringPi.h"
#include "gpio.h"
#include <chrono>

namespace waterpi {

/**
 * @brief      This class describes a pump. Flowrate: 1.2 - 1.6 L/min.
 */
class Pump {
public:
  Pump(const int start_gpio_id);
  ~Pump();
  void Start(const int timeout = -1);
  void Stop();
  bool is_active();
  float get_pumped_liters();

  static const float kFlowRate; // L/s
private:
  GPIO_Map pins_;
  bool is_active_;
  float pumped_liters_;
  std::chrono::steady_clock::time_point start_;
  std::chrono::steady_clock::time_point end_;
};

} // waterpi

#endif // end WATERPI_PUMP_H_
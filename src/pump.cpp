#include "pump.h"

namespace waterpi {

const float Pump::kFlowRate = 1.2 / 60; // L/s

Pump::Pump(const int start_gpio_id) {
  pins_["start"] = start_gpio_id;
  pinMode(pins_["start"], OUTPUT);
  is_active_ = false;
  pumped_liters_ = 0;
}

Pump::~Pump() {
  Stop();
}

void Pump::Start(const int timeout_s = -1) {
  digitalWrite(pins_["start"], HIGH_GPIO);
  is_active_ = true;
  if (timeout_s > 0) {
    delayMicroseconds(timeout_s * 10e6);
    digitalWrite(pins_["start"], LOW_GPIO);
    is_active_ = false;
    float pumped_liters_ += kFlowRate * timeout_s;
  } else {
     start_ = std::chrono::steady_clock::now();
  }
}

void Pump::Stop() {
  if (is_active_) {
    digitalWrite(pins_["start"], LOW_GPIO);
    stop_ = std::chrono::steady_clock::now();
    auto running_seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    float pumped_liters_ += kFlowRate * running_seconds;
    is_active_ = false;
  }
}

bool Pump::is_active() {
  return is_active_;
}

float Pump::get_pumped_liters() {
  return pumped_liters_;
}

} // waterpi
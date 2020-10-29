#include "pump.h"

namespace waterpi {

const float Pump::kFlowRate = 1.2 / 60; // L/s

Pump::Pump(const int start_gpio_id) {
  this->pins_["start"] = start_gpio_id;
  pinMode(pins_["start"], OUTPUT);
  this->is_active_ = false;
  this->pumped_liters_ = 0;
}

Pump::~Pump() {
  Stop();
}

void Pump::Start(const int timeout_s = -1) {
  digitalWrite(pins_["start"], HIGH_GPIO);
  this->is_active_ = true;
  if (timeout_s > 0) {
    delayMicroseconds(timeout_s * 10e6);
    digitalWrite(pins_["start"], LOW_GPIO);
    this->is_active_ = false;
    this->pumped_liters_ += kFlowRate * timeout_s;
  } else {
     this->start_ = std::chrono::steady_clock::now();
  }
}

void Pump::Stop() {
  if (this->is_active_) {
    digitalWrite(this->pins_["start"], LOW_GPIO);
    this->end_ = std::chrono::steady_clock::now();
    auto running_seconds = std::chrono::duration_cast<std::chrono::seconds>(this->end_ - this->start_).count();
    this->pumped_liters_ += kFlowRate * running_seconds;
    this->is_active_ = false;
  }
}

bool Pump::is_active() {
  return this->is_active_;
}

float Pump::get_pumped_liters() {
  return this->pumped_liters_;
}

} // waterpi
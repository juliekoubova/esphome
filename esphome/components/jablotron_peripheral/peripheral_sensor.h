#pragma once
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "../jablotron/jablotron_device.h"

namespace esphome {
namespace jablotron_peripheral {

class PeripheralSensor : public binary_sensor::BinarySensor, public jablotron::PeripheralDevice {
 public:
  void set_parent_jablotron(jablotron::JablotronComponent *parent) override;
  void set_state(bool value) override;

 private:
  int last_value_ = -1;
};

}  // namespace jablotron_peripheral
}  // namespace esphome

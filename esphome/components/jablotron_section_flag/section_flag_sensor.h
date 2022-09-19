#pragma once
#include <string_view>
#include "esphome/components/binary_sensor/binary_sensor.h"
#include "../jablotron/jablotron_device.h"

namespace esphome {
namespace jablotron {

class SectionFlagSensor : public binary_sensor::BinarySensor, public SectionFlagDevice {
 public:
  void set_parent_jablotron(JablotronComponent *) override;
  void set_state(bool) override;

 private:
  int last_value_ = -1;
};

}  // namespace jablotron
}  // namespace esphome

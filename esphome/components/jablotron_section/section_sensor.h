#pragma once
#include <string_view>
#include "esphome/components/text_sensor/text_sensor.h"
#include "../jablotron/jablotron_device.h"

namespace esphome {
namespace jablotron {

class SectionSensor : public text_sensor::TextSensor, public SectionDevice {
 public:
  void set_state(std::string_view) override;
  void set_parent_jablotron(JablotronComponent *) override;

 private:
  std::string last_value_;
};

}  // namespace jablotron
}  // namespace esphome

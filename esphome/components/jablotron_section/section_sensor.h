#pragma once
#include "esphome/components/text_sensor/text_sensor.h"
#include "../jablotron/jablotron_device.h"
#include "../jablotron/string_view.h"

namespace esphome {
namespace jablotron_section {

class SectionSensor : public text_sensor::TextSensor, public jablotron::SectionDevice {
 public:
  void set_state(jablotron::StringView) override;
  void set_parent_jablotron(jablotron::JablotronComponent *) override;

 private:
  std::string last_value_;
};

}  // namespace jablotron_section
}  // namespace esphome

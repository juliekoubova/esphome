#pragma once
#include "esphome/components/text_sensor/text_sensor.h"
#include "../jablotron/jablotron_device.h"

namespace esphome {
namespace jablotron_info {

class InfoSensor : public text_sensor::TextSensor, public jablotron::InfoDevice {
 public:
  void set_state(jablotron::StringView) override;
  void set_parent_jablotron(jablotron::JablotronComponent *) override;
};

}  // namespace jablotron_info
}  // namespace esphome

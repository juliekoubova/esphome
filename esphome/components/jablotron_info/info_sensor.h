#pragma once
#include "esphome/components/text_sensor/text_sensor.h"
#include "../jablotron/jablotron_device.h"

namespace esphome {
namespace jablotron {

class InfoSensor : public text_sensor::TextSensor, public InfoDevice {
 public:
  void set_state(StringView) override;
  void set_parent_jablotron(JablotronComponent *) override;
};

}  // namespace jablotron
}  // namespace esphome

#include "info_sensor.h"
#include "../jablotron/jablotron_component.h"

namespace esphome {
namespace jablotron {

void InfoSensor::set_parent_jablotron(JablotronComponent *parent) { parent->register_info(this); }

void InfoSensor::set_state(std::string_view response) {
  this->publish_state(std::string{response.begin(), response.end()});
}

}  // namespace jablotron
}  // namespace esphome

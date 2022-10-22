#include "info_sensor.h"
#include "../jablotron/jablotron_component.h"
#include "../jablotron/string_view.h"

namespace esphome {
namespace jablotron {

void InfoSensor::set_parent_jablotron(JablotronComponent *parent) { parent->register_info(this); }

void InfoSensor::set_state(StringView response) { this->publish_state(response); }

}  // namespace jablotron
}  // namespace esphome

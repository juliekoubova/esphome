#include "section_sensor.h"
#include "esphome/core/log.h"
#include "../jablotron/string_view.h"
#include "../jablotron/jablotron_component.h"

namespace esphome {
namespace jablotron {

static const char *const TAG = "jablotron_section";

void SectionSensor::set_state(StringView response) {
  if (response != this->last_value_) {
    this->last_value_ = std::string{response};
    this->publish_state(this->last_value_);
  }
}

void SectionSensor::set_parent_jablotron(JablotronComponent *parent) { parent->register_section(this); }

}  // namespace jablotron
}  // namespace esphome

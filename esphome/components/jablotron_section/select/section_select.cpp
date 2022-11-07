#include "section_select.h"
#include "esphome/components/jablotron/jablotron_component.h"

namespace esphome::jablotron_section {

constexpr const char ARMED[] = "ARMED";
constexpr const char ARMED_PART[] = "ARMED_PART";
constexpr const char READY[] = "READY";

constexpr const char TAG[] = "jablotron_section";

void SectionSelect::control(std::string const &value) {
  if (value == ARMED) {
    this->get_parent_jablotron()->queue_request_access_code("SET " + this->get_index_string());
  } else if (value == ARMED_PART) {
    this->get_parent_jablotron()->queue_request_access_code("SETP " + this->get_index_string());
  } else if (value == READY) {
    this->get_parent_jablotron()->queue_request_access_code("UNSET " + this->get_index_string());
  }
}

void SectionSelect::register_parent(jablotron::JablotronComponent &parent) { parent.register_section(this); }

void SectionSelect::set_state(jablotron::StringView value) {
  if (this->last_value_ != value) {
    this->last_value_ = std::string{value};
    this->publish_state(this->last_value_);
  }
}

}  // namespace esphome::jablotron_section

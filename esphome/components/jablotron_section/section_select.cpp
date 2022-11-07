#include "section_select.h"
#include "esphome/components/jablotron/jablotron_component.h"

namespace esphome::jablotron_section {

constexpr const char ARMED[] = "ARMED";
constexpr const char ARMED_PART[] = "ARMED_PART";
constexpr const char READY[] = "READY";

constexpr const char TAG[] = "jablotron_section";

void SectionSelect::control(std::string const &value) {
  if (this->index_string_.empty()) {
    ESP_LOGE(TAG, "Section index not set");
    return;
  }
  if (value == ARMED) {
    this->parent_->queue_request_access_code("SET " + this->index_string_);
  } else if (value == ARMED_PART) {
    this->parent_->queue_request_access_code("SETP " + this->index_string_);
  } else if (value == READY) {
    this->parent_->queue_request_access_code("UNSET " + this->index_string_);
  }
}

void SectionSelect::set_parent_jablotron(jablotron::JablotronComponent *parent) {
  this->parent_ = parent;
  this->parent_->register_section(this);
}

void SectionSelect::set_index(int32_t index) {
  IndexedDevice::set_index(index);
  this->index_string_ = std::to_string(index);
}

void SectionSelect::set_state(jablotron::StringView value) {
  if (this->last_value_ != value) {
    this->last_value_ = std::string{value};
    this->publish_state(this->last_value_);
  }
}

}  // namespace esphome::jablotron_section

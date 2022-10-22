#include "jablotron_component.h"
#include "response_handler.h"
#include <sstream>

namespace esphome {
namespace jablotron {

static const char *const TAG = "jablotron";

JablotronComponent::JablotronComponent()
    : PollingComponent(2500),
      prfstate_handler_{peripherals_},
      state_handler_{sections_},
      ver_handler_{infos_},
      section_flag_handler_{section_flags_} {}

void JablotronComponent::setup() {
  UARTLineDevice::setup();
  this->queue_request_("VER");
}

void JablotronComponent::update() { this->pending_update_ = true; }

void JablotronComponent::loop() {
  auto *line = this->read_line();
  if (line != nullptr) {
    ESP_LOGD(TAG, "Received line: '%s'", line);
    auto *handler = this->handle_response_(line);
    if (handler == nullptr) {
      ESP_LOGE(TAG, "Unknown message: '%s'", line);
    } else if (handler->is_last_response()) {
      this->response_awaiter_.response_received();
    }
  }

  if (!this->available() && this->line_buffer_empty() && !this->response_awaiter_.is_waiting_for_response()) {
    this->send_queued_request_();
  }
}

void JablotronComponent::queue_peripheral_request_() {
  if (!this->peripherals_.empty()) {
    this->queue_request_("PRFSTATE");
  }
}

void JablotronComponent::queue_section_request_() {
  if (!this->sections_.empty()) {
    std::stringstream indices;
    for (auto *const section : sections_) {
      indices << ' ';
      indices << section->get_index();
    }
    this->queue_request_("STATE" + indices.str());
    this->queue_request_("FLAGS" + indices.str());
  }
}

void JablotronComponent::send_queued_request_() {
  if (this->request_queue_.empty() && this->pending_update_) {
    this->queue_peripheral_request_();
    this->queue_section_request_();
    this->pending_update_ = false;
  }
  if (!this->request_queue_.empty()) {
    auto request = std::move(this->request_queue_.front());
    this->request_queue_.pop_front();
    this->send_request_(std::move(request));
    this->response_awaiter_.request_sent();
  }
}

void JablotronComponent::queue_request_(std::string request) {
  ESP_LOGD(TAG, "Queueing request '%s'", request.c_str());
  this->request_queue_.emplace_back(std::move(request));
}

void JablotronComponent::send_request_(const std::string &request) {
  ESP_LOGD(TAG, "Sending request '%s'", request.c_str());
  this->write_line(request);
}

void JablotronComponent::register_section(SectionDevice *device) {
  ESP_LOGI(TAG, "Registering section index=%u", device->get_index());
  this->sections_.push_back(device);
}

void JablotronComponent::register_section_flag(SectionFlagDevice *device) {
  ESP_LOGI(TAG, "Registering section flag flag=%u index=%u", device->get_flag(), device->get_index());
  this->section_flags_.push_back(device);
}

void JablotronComponent::register_peripheral(PeripheralDevice *device) {
  ESP_LOGI(TAG, "Registering peripheral index=%u", device->get_index());
  this->peripherals_.push_back(device);
}

void JablotronComponent::register_info(InfoDevice *device) {
  ESP_LOGI(TAG, "Registering info");
  this->infos_.push_back(device);
}

ResponseHandler *JablotronComponent::handle_response_(StringView response) {
  if (prfstate_handler_.invoke(response)) {
    return &prfstate_handler_;
  } else if (state_handler_.invoke(response)) {
    return &state_handler_;
  } else if (ok_handler_.invoke(response)) {
    return &ok_handler_;
  } else if (ver_handler_.invoke(response)) {
    return &ver_handler_;
  } else if (error_handler_.invoke(response)) {
    return &error_handler_;
  } else if (section_flag_handler_.invoke(response)) {
    return &section_flag_handler_;
  } else {
    return nullptr;
  }
}

}  // namespace jablotron
}  // namespace esphome

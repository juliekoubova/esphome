#include "uart_line_device.h"

namespace esphome {
namespace jablotron {

static const char *const TAG = "uart_line";

bool UARTLineDevice::line_buffer_empty() const { return this->read_buffer_.empty(); }

void UARTLineDevice::setup() {
  if (this->flow_control_pin_ != nullptr) {
    this->flow_control_pin_->setup();
  }
}

void UARTLineDevice::set_flow_control_pin(GPIOPin *flow_control_pin) { this->flow_control_pin_ = flow_control_pin; }

std::vector<std::string> UARTLineDevice::read_lines() {
  auto available = this->available();
  auto size = this->read_buffer_.size();

  if (available) {
    ESP_LOGD(TAG, "read_lines available=%u size=%u", available, size);
    this->read_buffer_.resize(size + available);
    this->read_array(reinterpret_cast<uint8_t *>(this->read_buffer_.data()) + size, available);
  }

  std::vector<std::string> lines;
  std::string::const_iterator line_begin = this->read_buffer_.cbegin();
  ESP_LOGD(TAG, "read_lines read_buffer=\"%s\"", this->read_buffer_.c_str());

  for (auto it = this->read_buffer_.cbegin(); it != this->read_buffer_.cend(); ++it) {
    if (*it == '\n') {
      continue;
    }
    if (*it == '\r') {
      auto &line = lines.emplace_back(line_begin, it);
      ESP_LOGD(TAG, "read_lines line=\"%s\"", line.c_str());
      line_begin = it + 1;
    }
  }

  this->read_buffer_.erase(this->read_buffer_.begin(), line_begin);
  ESP_LOGD(TAG, "read_lines read_buffer=\"%s\"", this->read_buffer_.c_str());
  return lines;
}

void UARTLineDevice::write_line(std::string str) {
  str += "\r\n";

  if (this->flow_control_pin_ != nullptr) {
    this->flow_control_pin_->digital_write(true);
  }

  this->write_array(reinterpret_cast<const uint8_t *>(str.data()), str.size());
  this->flush();

  if (this->flow_control_pin_ != nullptr) {
    this->flow_control_pin_->digital_write(false);
  }
}

}  // namespace jablotron
}  // namespace esphome

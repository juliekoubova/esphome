#pragma once
#include "esphome/components/uart/uart.h"

namespace esphome {
namespace jablotron {

template<uint16_t BufferSize> class UARTLineDevice : public uart::UARTDevice {
  static_assert(BufferSize > 1, "BufferSize must be greater than 1");

 public:
  void setup() {
    if (this->flow_control_pin_ != nullptr) {
      this->flow_control_pin_->setup();
    }
  }

  void set_flow_control_pin(GPIOPin *flow_control_pin) { this->flow_control_pin_ = flow_control_pin; }

  bool line_buffer_empty() const { return this->read_size_ == 0; }

  char *read_line() {
    if (!this->available()) {
      return nullptr;
    }

    uint8_t byte;
    if (!this->read_byte(&byte)) {
      return nullptr;
    }

    if (byte == '\n') {
      return nullptr;
    }

    if (byte == '\r' || this->read_size_ == BufferSize - 1) {
      if (this->read_size_ == 0) {
        return nullptr;
      }
      this->read_size_ = 0;
      return this->read_buffer_.data();
    }

    this->read_buffer_[this->read_size_++] = static_cast<char>(byte);
    this->read_buffer_[this->read_size_] = '\0';
    return nullptr;
  }

  void write_line(std::string str) {
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

 private:
  std::array<char, BufferSize> read_buffer_;
  uint16_t read_size_;
  GPIOPin *flow_control_pin_ = nullptr;
};

}  // namespace jablotron
}  // namespace esphome

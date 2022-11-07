#pragma once
#include "esphome/components/select/select.h"
#include "esphome/components/jablotron/jablotron_device.h"
#include "esphome/components/jablotron/string_view.h"

namespace esphome {
namespace jablotron_section {

class SectionSelect : public select::Select, public jablotron::SectionDevice {
 public:
  void control(const std::string &value) override;
  void set_parent_jablotron(jablotron::JablotronComponent *parent) override;
  void set_index(int32_t index) override;
  void set_state(jablotron::StringView state) override;

 private:
  jablotron::JablotronComponent *parent_ = nullptr;
  std::string last_value_;
  std::string index_string_;
};

}  // namespace jablotron_section
}  // namespace esphome

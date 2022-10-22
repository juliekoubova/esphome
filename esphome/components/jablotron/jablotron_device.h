#pragma once
#include <string>
#include <vector>
#include "string_view.h"

namespace esphome {
namespace jablotron {

class JablotronComponent;

template<typename T = StringView> class JablotronDevice {
 public:
  virtual ~JablotronDevice() = default;
  virtual void set_parent_jablotron(JablotronComponent *parent) = 0;
  virtual void set_state(T) = 0;
};

template<typename T = StringView> class IndexedDevice : public JablotronDevice<T> {
 public:
  int get_index() const { return this->index_; }
  void set_index(int value) { this->index_ = value; }

 private:
  int index_ = -1;
};

enum class SectionFlag {
  NONE = 0,
  INTERNAL_WARNING = 1,
  EXTERNAL_WARNING = 2,
  FIRE_ALARM = 3,
  INTRUDER_ALARM = 4,
  PANIC_ALARM = 5,
  ENTRY = 6,
  EXIT = 7
};

class SectionFlagDevice : public IndexedDevice<bool> {
 public:
  SectionFlag get_flag() const;
  void set_flag(SectionFlag flag);
  void set_flag(int flag);

 private:
  SectionFlag flag_ = SectionFlag::NONE;
};

using PeripheralDevice = IndexedDevice<bool>;
using PeripheralDeviceVector = std::vector<PeripheralDevice *>;

using SectionDevice = IndexedDevice<StringView>;
using SectionDeviceVector = std::vector<SectionDevice *>;

using InfoDevice = JablotronDevice<StringView>;
using InfoDeviceVector = std::vector<InfoDevice *>;

using SectionFlagDeviceVector = std::vector<SectionFlagDevice *>;

}  // namespace jablotron
}  // namespace esphome

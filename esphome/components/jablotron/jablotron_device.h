#pragma once
#include <string>
#include <string_view>
#include <vector>

namespace esphome {
namespace jablotron {

class JablotronComponent;

template<typename T = std::string_view> class JablotronDevice {
 public:
  virtual ~JablotronDevice() = default;
  virtual void set_parent_jablotron(JablotronComponent *parent) = 0;
  virtual void set_state(T) = 0;
};

template<typename T = std::string_view> class IndexedDevice : public JablotronDevice<T> {
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
  void set_flag(SectionFlag);
  void set_flag(int);

 private:
  SectionFlag flag_ = SectionFlag::NONE;
};

using PeripheralDevice = IndexedDevice<bool>;
using PeripheralDeviceVector = std::vector<PeripheralDevice *>;

using SectionDevice = IndexedDevice<>;
using SectionDeviceVector = std::vector<SectionDevice *>;

using InfoDevice = JablotronDevice<>;
using InfoDeviceVector = std::vector<InfoDevice *>;

using SectionFlagDeviceVector = std::vector<SectionFlagDevice *>;

}  // namespace jablotron
}  // namespace esphome

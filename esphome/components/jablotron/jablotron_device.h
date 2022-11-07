#pragma once
#include <string>
#include <vector>
#include "string_view.h"

namespace esphome {
namespace jablotron {

class JablotronComponent;

class JablotronDevice {
 public:
  virtual ~JablotronDevice() = default;
  virtual void set_parent_jablotron(JablotronComponent *parent) = 0;
};

class IndexedDevice {
 public:
  virtual ~IndexedDevice() = default;

  int get_index() const { return this->index_; }
  virtual void set_index(int value) { this->index_ = value; }

 private:
  int index_ = -1;
};

template<typename T = StringView> class SensorDevice {
 public:
  virtual ~SensorDevice() = default;
  virtual void set_state(T value) = 0;
};

template<typename T = StringView>
class IndexedSensorDevice : public JablotronDevice, public IndexedDevice, public SensorDevice<T> {};

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

class SectionFlagDevice : public IndexedSensorDevice<bool> {
 public:
  SectionFlag get_flag() const;
  void set_flag(SectionFlag value);
  void set_flag(int value);

 private:
  SectionFlag flag_ = SectionFlag::NONE;
};

class InfoDevice : public JablotronDevice, public SensorDevice<StringView> {};

using PeripheralDevice = IndexedSensorDevice<bool>;
using PeripheralDeviceVector = std::vector<PeripheralDevice *>;

using SectionDevice = IndexedSensorDevice<StringView>;
using SectionDeviceVector = std::vector<SectionDevice *>;

using InfoDeviceVector = std::vector<InfoDevice *>;
using SectionFlagDeviceVector = std::vector<SectionFlagDevice *>;

}  // namespace jablotron
}  // namespace esphome

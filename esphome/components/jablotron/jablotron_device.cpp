#include "jablotron_device.h"
#include "jablotron_component.h"

namespace esphome {
namespace jablotron {

SectionFlag SectionFlagDevice::get_flag() const { return this->flag_; }

void SectionFlagDevice::set_flag(SectionFlag value) { this->flag_ = value; }

void SectionFlagDevice::set_flag(int value) { this->set_flag(static_cast<SectionFlag>(value)); }

}  // namespace jablotron
}  // namespace esphome

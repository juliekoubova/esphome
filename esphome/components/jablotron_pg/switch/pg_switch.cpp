#include "pg_switch.h"
#include "esphome/components/jablotron/jablotron_component.h"

namespace esphome::jablotron_pg {

void PGSwitch::register_parent(jablotron::JablotronComponent &parent) { parent.register_pg(this); }

void PGSwitch::write_state(bool state) { this->publish_state(state); }

void PGSwitch::set_state(bool state) { this->publish_state(state); }

}  // namespace esphome::jablotron_pg

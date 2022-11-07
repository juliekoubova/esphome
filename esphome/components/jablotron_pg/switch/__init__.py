import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import switch
from esphome.components.jablotron import (
    CONF_ID,
    CONF_INDEX,
    INDEX_SCHEMA,
    JABLOTRON_DEVICE_SCHEMA,
    register_jablotron_device,
)

jablotron_pg_ns = cg.esphome_ns.namespace("jablotron_pg")
PGSwitch = jablotron_pg_ns.class_("PGSwitch", switch.Switch)

DEPENDENCIES = ["jablotron", "switch"]
CONFIG_SCHEMA = (
    switch.SWITCH_SCHEMA.extend(JABLOTRON_DEVICE_SCHEMA)
    .extend(INDEX_SCHEMA)
    .extend(
        {
            cv.GenerateID(): cv.declare_id(PGSwitch),
        }
    )
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await switch.register_switch(var, config)
    cg.add(var.set_index(config[CONF_INDEX]))
    await register_jablotron_device(var, config)

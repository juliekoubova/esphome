import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import select
from esphome.components.jablotron import (
    CONF_INDEX,
    INDEX_SCHEMA,
    JABLOTRON_DEVICE_SCHEMA,
    register_jablotron_device,
)
from . import jablotron_section_ns

SectionSelect = jablotron_section_ns.class_("SectionSelect", select.Select)

DEPENDENCIES = ["jablotron"]
CONFIG_SCHEMA = (
    select.SELECT_SCHEMA.extend(JABLOTRON_DEVICE_SCHEMA)
    .extend(INDEX_SCHEMA)
    .extend(
        {
            cv.GenerateID(): cv.declare_id(SectionSelect),
        }
    )
)


async def to_code(config):
    sel = await select.new_select(config, options=["READY", "ARMED_PART", "ARMED"])
    cg.add(sel.set_index(config[CONF_INDEX]))
    await register_jablotron_device(sel, config)

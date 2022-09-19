import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from ..jablotron import (
    CONF_INDEX,
    INDEX_SCHEMA,
    JABLOTRON_DEVICE_SCHEMA,
    jablotron_ns,
    register_jablotron_device,
)

SectionFlagSensor = jablotron_ns.class_("SectionFlagSensor", binary_sensor.BinarySensor)

CONF_FLAG = "flag"
SECTION_FLAGS = {
    "INTERNAL_WARNING": 1,
    "EXTERNAL_WARNING": 2,
    "FIRE_ALARM": 3,
    "INTRUDER_ALARM": 4,
    "PANIC_ALARM": 5,
    "ENTRY": 6,
    "EXIT": 7,
}

DEPENDENCIES = ["jablotron"]
CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(SectionFlagSensor)
    .extend(JABLOTRON_DEVICE_SCHEMA)
    .extend(INDEX_SCHEMA)
    .extend(cv.Schema({cv.Required(CONF_FLAG): cv.enum(SECTION_FLAGS, upper=True)}))
)


async def to_code(config):
    sensor = await binary_sensor.new_binary_sensor(config)
    cg.add(sensor.set_index(config[CONF_INDEX]))
    cg.add(sensor.set_flag(config[CONF_FLAG]))
    await register_jablotron_device(sensor, config)

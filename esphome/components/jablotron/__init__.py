import esphome.codegen as cg
import esphome.config_validation as cv
from esphome import pins
from esphome.components import uart
from esphome.const import CONF_FLOW_CONTROL_PIN, CONF_ID, CONF_INDEX

CODEOWNERS = ["@juliekoubova"]
DEPENDENCIES = ["uart"]

CONF_JABLOTRON_ID = "jablotron_id"
jablotron_ns = cg.esphome_ns.namespace("jablotron")
JablotronComponent = jablotron_ns.class_(
    "JablotronComponent", cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(JablotronComponent),
            cv.Optional(CONF_FLOW_CONTROL_PIN): pins.gpio_output_pin_schema,
        }
    )
    .extend(cv.polling_component_schema("1s"))
    .extend(uart.UART_DEVICE_SCHEMA)
)

JABLOTRON_DEVICE_SCHEMA = cv.Schema(
    {cv.GenerateID(CONF_JABLOTRON_ID): cv.use_id(JablotronComponent)}
)

INDEX_SCHEMA = cv.Schema({cv.Required(CONF_INDEX): cv.int_range(min=0)})


async def register_jablotron_device(var, config):
    parent = await cg.get_variable(config[CONF_JABLOTRON_ID])
    cg.add(var.set_parent_jablotron(parent))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    if CONF_FLOW_CONTROL_PIN in config:
        flow_control_pin = await cg.gpio_pin_expression(config[CONF_FLOW_CONTROL_PIN])
        cg.add(var.set_flow_control_pin(flow_control_pin))
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)

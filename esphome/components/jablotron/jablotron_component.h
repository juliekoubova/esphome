#pragma once
#include <deque>
#include <string_view>
#include <unordered_set>
#include <vector>
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "jablotron_device.h"
#include "response_awaiter.h"
#include "response_handler.h"
#include "uart_line_device.h"

namespace esphome {
namespace jablotron {

class JablotronComponent : public UARTLineDevice<260>, public PollingComponent {
 public:
  JablotronComponent();

  void setup() override;
  void loop() override;
  void update() override;

  void register_info(InfoDevice *);
  void register_peripheral(PeripheralDevice *);
  void register_section(SectionDevice *);
  void register_section_flag(SectionFlagDevice *);

 private:
  ResponseHandler *handle_response(std::string_view response);

  void queue_peripheral_request();
  void queue_section_request();
  void queue_request(std::string request);
  void send_queued_request();
  void send_request(std::string request);

 private:
  InfoDeviceVector infos_;
  PeripheralDeviceVector peripherals_;
  SectionDeviceVector sections_;
  SectionFlagDeviceVector section_flags_;
  std::deque<std::string> request_queue_;

  ResponseAwaiter response_awaiter_;
  bool pending_update_ = 0;

  ResponseHandlerError error_handler_;
  ResponseHandlerOK ok_handler_;
  ResponseHandlerPrfState prfstate_handler_;
  ResponseHandlerState state_handler_;
  ResponseHandlerVer ver_handler_;
  ResponseHandlerSectionFlag section_flag_handler_;
};

}  // namespace jablotron
}  // namespace esphome

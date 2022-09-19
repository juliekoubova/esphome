#pragma once
#include <string_view>
#include "jablotron_device.h"

namespace esphome {
namespace jablotron {

class ResponseHandler {
 public:
  virtual ~ResponseHandler() = default;
  virtual bool invoke(std::string_view) const = 0;

 public:
  bool is_last_response() const;

 protected:
  void set_is_last_response(bool);

 private:
  bool is_last_response_ = false;
};

class ResponseHandlerError : public ResponseHandler {
 public:
  ResponseHandlerError();
  bool invoke(std::string_view) const final;
};

class ResponseHandlerOK : public ResponseHandler {
 public:
  ResponseHandlerOK();
  bool invoke(std::string_view) const final;
};

class ResponseHandlerPrfState final : public ResponseHandler {
 public:
  ResponseHandlerPrfState(const PeripheralDeviceVector &);
  bool invoke(std::string_view) const final;

 private:
  const PeripheralDeviceVector &devices_;
};

class ResponseHandlerState final : public ResponseHandler {
 public:
  ResponseHandlerState(const SectionDeviceVector &);
  bool invoke(std::string_view) const final;

 private:
  const SectionDeviceVector &devices_;
};

class ResponseHandlerVer final : public ResponseHandler {
 public:
  ResponseHandlerVer(const InfoDeviceVector &);
  bool invoke(std::string_view) const final;

 private:
  const InfoDeviceVector &devices_;
};

class ResponseHandlerSectionFlag final : public ResponseHandler {
 public:
  ResponseHandlerSectionFlag(const SectionFlagDeviceVector &);
  bool invoke(std::string_view) const final;

 private:
  const SectionFlagDeviceVector &devices_;
};

}  // namespace jablotron
}  // namespace esphome

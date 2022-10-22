#include "string_view.h"
#include "esphome/core/log.h"
#include <cstring>
#include <cstdlib>

namespace esphome {
namespace jablotron {

namespace {

static const char *const TAG = "jablotron";

uint8_t parse_hex_nibble(char hex) {
  if (hex >= '0' && hex <= '9') {
    return hex - '0';
  } else if (hex >= 'A' && hex <= 'F') {
    return hex - 'A' + 10;
  } else {
    ESP_LOGE(TAG, "parse_hex_nibble: char=%c not 0-9A-F", hex);
    return 0;
  }
}

uint8_t parse_hex_byte(char high, char low) { return (parse_hex_nibble(high) << 4) | (parse_hex_nibble(low)); }

}  // namespace

StringView::StringView() : data_{nullptr}, size_{0} {}
StringView::StringView(const char *begin) : data_{begin}, size_{std::strlen(begin)} {}

StringView::StringView(const char *begin, size_t size) : data_{begin}, size_{size} {}

StringView::StringView(const std::string &str) : data_{str.data()}, size_{str.size()} {}

bool get_bit_in_hex_string(StringView str, size_t index) {
  if (index >= str.size()) {
    ESP_LOGE(TAG, "get_bit_in_hex_string: index=%zu out of string bounds", index);
    return false;
  }

  auto div = std::div(index, 8);
  size_t high_nibble_index = 2 * div.quot;
  size_t low_nibble_index = 2 * div.quot + 1;
  size_t bit_index = div.rem;

  if (low_nibble_index >= str.size()) {
    ESP_LOGE(TAG, "get_bit_in_hex_string: string length not even");
    return false;
  }

  uint8_t byte = parse_hex_byte(str[high_nibble_index], str[low_nibble_index]);
  uint8_t bit_mask = 1 << bit_index;
  return byte & bit_mask;
}

bool starts_with(StringView str, StringView prefix) {
  if (prefix.empty()) {
    return false;
  }
  return str.substr(0, prefix.size()) == prefix;
}

bool try_remove_prefix(StringView &str, StringView prefix) {
  if (starts_with(str, prefix)) {
    str.remove_prefix(prefix.size());
    return true;
  }
  return false;
}

bool try_remove_prefix(StringView &str, const std::string &prefix) {
  return try_remove_prefix(str, StringView{prefix});
}

bool try_remove_prefix(StringView &str, const char *prefix) { return try_remove_prefix(str, StringView{prefix}); }

bool try_remove_prefix_and_space(StringView &str, StringView prefix) {
  if (starts_with(str, prefix) && str[prefix.size()] == ' ') {
    str.remove_prefix(prefix.size() + 1);
    return true;
  }
  return false;
}

bool try_remove_prefix_and_space(StringView &str, const std::string &prefix) {
  return try_remove_prefix_and_space(str, StringView{prefix});
}

bool try_remove_prefix_and_space(StringView &str, const char *prefix) {
  return try_remove_prefix_and_space(str, StringView{prefix});
}

bool try_remove_integer_and_space(StringView &str, int &result) {
  const char *begin = str.data();
  char *integer_end = nullptr;
  result = static_cast<int>(std::strtol(begin, &integer_end, 10));
  if (integer_end == begin || *integer_end != ' ') {
    return false;
  }
  str = StringView{integer_end + 1};
  return true;
}

}  // namespace jablotron
}  // namespace esphome

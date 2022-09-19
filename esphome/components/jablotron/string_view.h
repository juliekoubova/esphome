#pragma once
#include <string_view>
#include <string>

namespace esphome {
namespace jablotron {
bool get_bit_in_hex_string(std::string_view str, size_t index);
bool starts_with(std::string_view str, std::string_view prefix);

bool try_remove_prefix(std::string_view &str, std::string_view prefix);
bool try_remove_prefix(std::string_view &str, std::string prefix);
bool try_remove_prefix(std::string_view &str, const char *prefix);

bool try_remove_prefix_and_space(std::string_view &str, std::string_view prefix);
bool try_remove_prefix_and_space(std::string_view &str, std::string prefix);
bool try_remove_prefix_and_space(std::string_view &str, const char *prefix);

bool try_remove_integer_and_space(std::string_view &str, int &result);
}  // namespace jablotron
}  // namespace esphome

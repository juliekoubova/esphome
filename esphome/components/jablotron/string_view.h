#pragma once
#include <stdexcept>
#include <cstring>
#include <string>
#include <limits>

namespace esphome {
namespace jablotron {

class StringView {
 public:
  using size_type = std::size_t;

  constexpr StringView();
  constexpr StringView(const char *begin);
  constexpr StringView(const char *begin, size_type size);
  constexpr StringView(const std::string &str);

  constexpr const char *data() const noexcept { return this->data_; }
  constexpr bool empty() const noexcept { return this->size_ == 0; }
  constexpr size_type size() const noexcept { return this->size_; }
  operator std::string() const { return std::string{this->data_, this->size_}; }

  constexpr bool starts_with(StringView s) const { return this->substr(0, s.size()) == s; }

  void remove_prefix(size_type n) {
    if (n > this->size_) {
      this->data_ = nullptr;
      this->size_ = 0;
    } else {
      this->data_ += n;
      this->size_ -= n;
    }
  }

  constexpr StringView substr(size_type pos = 0, size_type count = NPOS) const {
    if (pos > this->size_) {
      return StringView{};
    }
    auto rcount = std::min(this->size_ - pos, count);
    return StringView{this->data_ + pos, rcount};
  }

  const char &operator[](size_type index) const { return this->data_[index]; }

  constexpr bool operator==(const StringView &other) const noexcept {
    return this->size_ == other.size_ && (this->size_ == 0 || std::strncmp(this->data_, other.data_, this->size_) == 0);
  }

  constexpr bool operator!=(const StringView &other) const noexcept { return !(*this == other); }

  constexpr bool operator==(const std::string &other) const noexcept { return *this == StringView{other}; }
  constexpr bool operator!=(const std::string &other) const noexcept { return *this != StringView{other}; }

  constexpr bool operator==(const char *other) const noexcept { return *this == StringView{other}; }
  constexpr bool operator!=(const char *other) const noexcept { return *this != StringView{other}; }

  static constexpr size_type NPOS = std::numeric_limits<size_t>::max();

 private:
  const char *data_;
  size_type size_;
};

constexpr bool operator==(const std::string &string, const StringView &view) noexcept { return view == string; }
constexpr bool operator!=(const std::string &string, const StringView &view) noexcept { return view != string; }

bool get_bit_in_hex_string(StringView str, size_t index);
bool starts_with(StringView str, StringView prefix);

bool try_remove_prefix(StringView &str, StringView prefix);
bool try_remove_prefix(StringView &str, const std::string &prefix);
bool try_remove_prefix(StringView &str, const char *prefix);

bool try_remove_prefix_and_space(StringView &str, StringView prefix);
bool try_remove_prefix_and_space(StringView &str, const std::string &prefix);
bool try_remove_prefix_and_space(StringView &str, const char *prefix);

bool try_remove_integer_and_space(StringView &str, int &result);
}  // namespace jablotron
}  // namespace esphome

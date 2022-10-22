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

  StringView();
  StringView(const char *begin);
  StringView(const char *begin, size_type size);
  StringView(const std::string &str);

  const char *data() const noexcept { return this->data_; }
  bool empty() const noexcept { return this->size_ == 0; }
  size_type size() const noexcept { return this->size_; }
  operator std::string() const { return std::string{this->data_, this->size_}; }

  size_type starts_with(StringView s) const { return this->substr(0, s.size()) == s; }

  void remove_prefix(size_type n) {
    if (n > this->size_) {
      this->data_ = nullptr;
      this->size_ = 0;
    } else {
      this->data_ += n;
      this->size_ -= n;
    }
  }

  StringView substr(size_type pos = 0, size_type count = npos) const {
    if (pos > this->size_) {
      throw std::out_of_range("pos out of range");
    }
    auto rcount = std::min(this->size_ - pos, count);
    return StringView{this->data_ + pos, rcount};
  }

  const char &operator[](size_type index) const { return this->data_[index]; }

  bool operator==(const StringView &other) const noexcept {
    return this->size_ == other.size_ && (this->size_ == 0 || std::strncmp(this->data_, other.data_, this->size_) == 0);
  }

  bool operator!=(const StringView &other) const noexcept { return !(*this == other); }

  static constexpr size_type npos = std::numeric_limits<size_t>::max();

 private:
  const char *data_;
  size_type size_;
};

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

#ifndef M_STRING_H
#define M_STRING_H

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <memory>

namespace klb {

class String {
 public:
  String() : data(nullptr), size(0), capacity(0) {}

  String(const char *ptr) {
    size = std::strlen(ptr);
    expand_capacity(size);
    std::memcpy(data, ptr, size);
  }

  String(const String &other) {
    size = other.size;
    expand_capacity(size);
    std::memcpy(data, other.data, size);
  }

  String &operator=(const char *ptr) {
    size = std::strlen(ptr);
    expand_capacity(size);
    std::memcpy(data, ptr, size);

    return *this;
  }

  String &operator=(const String &other) {
    if (this->data == other.data) {
      return *this;
    }

    size = other.size;
    expand_capacity(size);
    std::memcpy(data, other.data, size);

    return *this;
  }

  ~String() {
    std::free(data);
    size = 0;
    capacity = 0;
  }

 public:
  const char *c_str() const { return data; }

  char *getData() const { return data; }

  bool empty() const { return 0 != size; }

  std::size_t length() const { return size; }

 public:
  std::size_t find(char c, std::size_t pos = 0) const {
    if (pos >= size) {
      return std::string::npos;
    }
    for (std::size_t i = pos; i < size; ++i) {
      if (data[i] == c) {
        return i;
      }
    }
    return std::string::npos;
  }

  String substr(std::size_t pos = 0,
                 std::size_t len = std::string::npos) const {
    String result;
    if (pos >= size) {
      return result;
    }

    if (len == std::string::npos || pos + len > size) {
      len = size - pos;
    }

    result.expand_capacity(len);
    std::memcpy(result.data, data + pos, len);

    return result;
  }

 private:
  void expand_capacity(std::size_t new_size) {
    if (new_size <= capacity) {
      return;
    }

    capacity = new_size + 1;
    char *new_data = (char *)std::realloc(data, capacity);
    if (nullptr == new_data) {
      throw std::bad_alloc();
    }

    data = new_data;
    data[size] = '\0';
  }

 private:
  char *data;
  std::size_t size;
  std::size_t capacity;
};

}  // namespace klb

#endif

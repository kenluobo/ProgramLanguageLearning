#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <cstddef>

template <typename T>
class DynamicArray {
 public:
  DynamicArray() : size(0), capacity(0), data(nullptr) {}

  explicit DynamicArray(std::size_t size)
      : size(size), capacity(size), data(new T[size]) {}

  DynamicArray(const DynamicArray& other)
      : size(other.size), capacity(other.capacity), data(new T[capacity]) {}

  DynamicArray(DynamicArray&& other) noexcept
      : size(other.size), capacity(other.capacity), data(other.data) {
    other.size = 0;
    other.capacity = 0;
    other.data = nullptr;
  }

  DynamicArray& operator=(const DynamicArray& other) {
    if (this != &other) {
      size = other.size;
      capacity = other.capacity;

      delete[] data;
      data = other.data;

      other.size = 0;
      other.capacity = 0;
      other.data = nullptr;
    }

    return *this;
  }

  DynamicArray& operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
      size = other.size;
      capacity = other.capacity;

      delete[] data;
      data = other.data;

      other.size = 0;
      other.capacity = 0;
      other.data = nullptr;
    }

    return *this;
  }

  ~DynamicArray() {
    delete[] data;
    size = 0;
    capacity = 0;
  }

 public:
  bool empty() const { return size == 0; }

  std::size_t get_size() const { return size; }

  std::size_t get_capacity() const { return capacity; }

  T& operator[](std::size_t index) { return data[index]; }

  const T& operator[](std::size_t index) const { return data[index]; }

  T& at(std::size_t index) {
    if (index >= size) {
      throw std::out_of_range("Index out of range");
    }
    return data[index];
  }

 public:
  void expand_capacity(std::size_t new_capacity) {
    if (new_capacity <= capacity) {
      return;
    }

    T* new_data = new T[new_capacity];
    std::memcpy(new_data, data, size * sizeof(T));
    delete[] data;

    capacity = new_capacity;
  }

  void push_back(const T& val) {
    if (size == capacity) {
      expand_capacity(capacity == 0 ? 1 : capacity * 2);
    }

    data[size++] = val;
  }

 public:
  bool operator==(const DynamicArray& other) const {
    if (size != other.size) {
      return false;
    }

    for (std::size_t i = 0; i < size; ++i) {
      if (data[i] != other.data[i]) {
        return false;
      }
    }

    return true;
  }

  bool operator!=(const DynamicArray& other) const { return !(*this == other); }

 private:
  std::size_t size;
  std::size_t capacity{};

  T* data;
};

#endif

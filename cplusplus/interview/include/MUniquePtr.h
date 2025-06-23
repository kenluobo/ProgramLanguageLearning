#ifndef M_UNIQUE_PTR_H
#define M_UNIQUE_PTR_H

namespace klb {

template <typename T>
class MUniquePtr {
 public:
  MUniquePtr(T *p = nullptr) : ptr(p) {}

  MUniquePtr(const MUniquePtr<T> &other) = delete;

  MUniquePtr(MUniquePtr<T> &&other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  }

  MUniquePtr &operator=(const MUniquePtr<T> &other) = delete;

  MUniquePtr &operator=(MUniquePtr<T> &&other) noexcept {
    if (*this != other) {
      ptr = other.ptr;
      other.ptr = nullptr;
    }

    return *this;
  }

  ~MUniquePtr() { delete ptr; }

 public:
  T *get() const { return ptr; }

  T *operator->() const { return ptr; }
  T &operator*() const { return *ptr; }

  explicit operator bool() const { return nullptr != ptr; }

  void reset(T *p = nullptr) {
    delete ptr;
    ptr = p;
  }

  T *release() {
    T *temp = ptr;
    ptr = nullptr;
    return temp;
  }

 private:
  T *ptr;
};

}  // namespace klb

#endif
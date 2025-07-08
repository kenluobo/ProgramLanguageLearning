#ifndef M_UNIQUE_PTR_H
#define M_UNIQUE_PTR_H

namespace klb {

template <typename T>
class UniquePtr {
 public:
  UniquePtr(T *p = nullptr) : ptr(p) {}

  UniquePtr(const UniquePtr<T> &other) = delete;

  UniquePtr(UniquePtr<T> &&other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  }

  UniquePtr &operator=(const UniquePtr<T> &other) = delete;

  UniquePtr &operator=(UniquePtr<T> &&other) noexcept {
    if (*this != other) {
      ptr = other.ptr;
      other.ptr = nullptr;
    }

    return *this;
  }

  ~UniquePtr() { delete ptr; }

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

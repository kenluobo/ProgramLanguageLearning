#ifndef M_SHARED_PTR_H
#define M_SHARED_PTR_H

#include <cstddef>

namespace klb {

template <typename T>
class SharedPtr {
 public:
  SharedPtr() : ptr(nullptr), ref_cnt(nullptr) {}

  SharedPtr(T* t_ptr) : ptr(t_ptr ? t_ptr : new T), ref_cnt(new int{1}) {}

  SharedPtr(const SharedPtr<T>& other) {
    if (nullptr != other) {
      ptr = other.ptr;
      ref_cnt = other.ref_cnt;

      if (nullptr != ref_cnt) {
        ++(*ref_cnt);
      }
    }
  }

  SharedPtr& operator=(const SharedPtr<T>& other) {
    release();
    if (nullptr != other) {
      ptr = other.ptr;
      ref_cnt = other.ref_cnt;

      if (nullptr != ref_cnt) {
        ++(*ref_cnt);
      }
    }

    return *this;
  }

  ~SharedPtr() { release(); }

 public:
  T* operator->() { return ptr; }

  T& operator*() { return *this; }

 public:
  void reset(T* p = nullptr) {
    release();

    if (nullptr != p) {
      ptr = p;
      ref_cnt = new int{1};
    } else {
      ptr = nullptr;
      ref_cnt = nullptr;
    }
  }

  int use_count() const { return ref_cnt ? *ref_cnt : 0; }

  T* get() const { return ptr; }

 private:
  void release() {
    if (nullptr != ref_cnt) {
      --(*ref_cnt);
      if (0 == (*ref_cnt)) {
        delete ptr;
        delete ref_cnt;
      }
    }
  }

 private:
  T* ptr;
  int* ref_cnt;
};

}  // namespace klb

#endif

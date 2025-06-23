#ifndef M_SHARED_PTR_H
#define M_SHARED_PTR_H

#include <cstddef>

template <typename T>
class MSharedPtr {
 public:
  MSharedPtr() : ptr(nullptr), ref_cnt(nullptr) {}

  MSharedPtr(T* t_ptr)
      : ptr(t_ptr ? t_ptr : new T), ref_cnt(new std::size_t{1}) {}

  MSharedPtr(const MySahredPtr<T>& msptr) {
    if (nullptr != msptr) {
      ptr = msptr.ptr;
      ref_cnt = msptr.ref_cnt;
    }
  }

  T* get() { return ptr; }

  T* operator->() { return ptr; }

  T operator*() { return *ptr; }

 private:
  T* ptr;
  std::size_t* ref_cnt;
};

#endif

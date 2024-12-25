#ifndef CLASS_DEMO_H
#define CLASS_DEMO_H

#include "stl.h"
#include "test.h"

class Base;
class Derived;

//====================================================
class Base {
public:
  Base() { OUT_FUNC_INFO(); }

  Base(const Base &b) { OUT_FUNC_INFO(); }
  Base &operator=(const Base &b) {
    OUT_FUNC_INFO();
    return *this;
  }

  Base(Base &&b) noexcept { OUT_FUNC_INFO(); }
  Base &operator=(Base &&b) noexcept {
    OUT_FUNC_INFO();
    return *this;
  }

  virtual ~Base() { OUT_FUNC_INFO(); }

public:
  virtual void out_msg() { out("call ", 1); }
};

//====================================================
class Derived final : public Base {
public:
  Derived() { OUT_FUNC_INFO(); }

  Derived(const Derived &b) { OUT_FUNC_INFO(); }
  Derived &operator=(const Derived &b) {
    OUT_FUNC_INFO();
    return *this;
  }

  Derived(Derived &&b) noexcept { OUT_FUNC_INFO(); }
  Derived &operator=(Derived &&b) noexcept {
    OUT_FUNC_INFO();
    return *this;
  }

  ~Derived() override { OUT_FUNC_INFO(); }

public:
  void out_msg() override { out("call ", 2); }
};

#endif

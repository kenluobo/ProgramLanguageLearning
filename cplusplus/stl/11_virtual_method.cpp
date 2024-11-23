#include "utils/test.hpp"
#include <cstdint>
#include <string>

//==================================================================
enum class AnimalCategory : std::uint8_t {
  LandAnimal = 0,
  WaterAnimal,
  Amphibian
};

static std::string convertAnimalCategoryToString(AnimalCategory AC) {
  switch (AC) {
  case AnimalCategory::LandAnimal:
    return "LandAnimal";
  case AnimalCategory::WaterAnimal:
    return "WaterAnimal";
  case AnimalCategory::Amphibian:
    return "Amphibian";
  }
}

//==================================================================
class Animal {
public:
  virtual AnimalCategory getCategory() = 0;
  virtual std::string getCategoryAsString() = 0;

private:
  AnimalCategory AC;
};

//==================================================================
class Human : public Animal {
public:
  virtual AnimalCategory getCategory() { return AC; }
  virtual std::string getCategoryAsString() {
    return convertAnimalCategoryToString(AC);
  }
  virtual ~Human() = default;

private:
  AnimalCategory AC = AnimalCategory::LandAnimal;
};

class Employee : public Human {
public:
  virtual ~Employee() = default;
};

//==================================================================
class Fish : public Animal {
public:
  virtual AnimalCategory getCategory() { return AC; }
  virtual std::string getCategoryAsString() {
    return convertAnimalCategoryToString(AC);
  }

private:
  AnimalCategory AC = AnimalCategory::WaterAnimal;
};

//==================================================================
void test_virtual_method() {
  // todo
  Human h;
  out("Human ", h.getCategoryAsString());

  Employee e;
  out("Employee ", e.getCategoryAsString());

  Fish f;
  out("Fish ", f.getCategoryAsString());

  Employee *p_e = &e;
  out("Employee Pointer ", p_e->getCategoryAsString());
  out("Human Pointer ", static_cast<Human *>(p_e)->getCategoryAsString());
}

//==================================================================
void test() { TEST(test_virtual_method); }

//==================================================================
int main() { test(); }

#ifndef FAKER_HPP
#define FAKER_HPP

#include <faker-cxx/faker.h>
#include <faker-cxx/lorem.h>

#include <string>

class Faker {
  public:
    static std::string GetLorem() {
        return faker::lorem::paragraph();
    }

    static std::string GetHacker() {
        auto name = faker::person::firstName();
        auto lastName = faker::person::lastName();
        auto phrase = faker::hacker::phrase();
        return std::string(name) + " " + std::string(lastName) + " : " + std::string(phrase);
    }
};

#endif  // FAKER_HPP
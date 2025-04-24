#ifndef FAKER_HPP
#define FAKER_HPP

#include <faker-cxx/faker.h>
#include <faker-cxx/lorem.h>

#include <mutex>
#include <string>

class Faker {
  public:
    Faker() {
        auto seed = static_cast<unsigned int>(time(nullptr)) + m_Seed++;
        srand(seed);
    }

    std::string GetLorem() {
        std::lock_guard<std::mutex> lock(m_Mutex);
        auto seed = static_cast<unsigned int>(time(nullptr)) + m_Seed++;
        srand(seed);
        return faker::lorem::paragraph();
    }

    std::string GetHacker() {
        std::lock_guard<std::mutex> lock(m_Mutex);
        auto name = faker::person::firstName();
        auto lastName = faker::person::lastName();
        auto phrase = faker::hacker::phrase();
        auto seed = static_cast<unsigned int>(time(nullptr)) + m_Seed++;
        srand(seed);
        return std::string(name) + " " + std::string(lastName) + " : " + std::string(phrase);
    }

  private:
    inline static unsigned int m_Seed = 0;
    static std::mutex m_Mutex;
};

#endif  // FAKER_HPP
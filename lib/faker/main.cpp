#include <iostream>

#include "faker-cxx/faker.h"
#include "faker-cxx/hacker.h"
#include "faker-cxx/person.h"

int main(int argc, char *argv[]) {
    std::cout << faker::hacker::phrase() << std::endl;
    std::cout << faker::hacker::abbreviation() << std::endl;
    std::cout << faker::hacker::adjective() << std::endl;
    std::cout << faker::hacker::ingverb() << std::endl;
    std::cout << faker::hacker::noun() << std::endl;
    std::cout << faker::hacker::verb() << std::endl;
    std::cout << faker::person::firstName() << std::endl;
    return 0;
}
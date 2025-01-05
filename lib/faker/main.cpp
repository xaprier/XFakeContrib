#include <iostream>
#include <thread>

#include "Faker.hpp"

void TestFaker() {
    Faker faker;
    for (int i = 0; i < 3; i++) {
        auto lorem = faker.GetLorem();
        auto hacker = faker.GetHacker();
        std::cout << "Thread: " << std::this_thread::get_id() << '\t' << "Lorem(" << i << "): " << lorem << '\t' << "Hacker(" << i << "): " << hacker << std::endl;
    }
}

void TestThread() {
    std::thread t1(TestFaker);
    std::thread t2(TestFaker);
    t1.join();
    t2.join();
}

int main(int argc, char *argv[]) {
    TestThread();
    return 0;
}
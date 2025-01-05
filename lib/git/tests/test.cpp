#include "test.hpp"

#include <QString>
#include <fstream>
#include <iostream>

#include "GitChangeHandler.hpp"

namespace git::tests {
std::string filePath = "/mnt/Shared/Projects/git/priv/deneme.txt";
void RunTests() {
    TestGitChange();
    std::cout << "All tests passed" << std::endl;
}

void TestGitChange() {
    TestGitChangeCreate();
    TestGitChangeEdit();
    TestGitChangeDelete();
}

void TestGitChangeCreate() {
    // get content of deneme.txt
    std::ifstream file(filePath);
    // read content of deneme.txt
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    // close file
    file.close();

    // create a change
    GitChangeHandler handler("/mnt/Shared/Projects/git/priv");
    handler.CreateChange(QString::fromStdString(filePath), "deneme");  // should append "deneme" to deneme
    handler.ApplyChanges();

    // get content of deneme.txt
    std::ifstream file2(filePath);
    // read content of deneme.txt
    std::string content2((std::istreambuf_iterator<char>(file2)),
                         (std::istreambuf_iterator<char>()));
    // close file
    file2.close();

    content += "deneme\n";

    // check if content is changed
    if (content != content2) {
        throw std::runtime_error("TestGitChangeCreate failed");
    }
}

void TestGitChangeEdit() {
    // get content of deneme.txt
    std::ifstream file(filePath);
    // read content of deneme.txt
    std::string content((std::istreambuf_iterator<char>(file)),
                        (std::istreambuf_iterator<char>()));
    // close file
    file.close();

    // create a change
    GitChangeHandler handler("/mnt/Shared/Projects/git/priv");
    handler.EditChange(QString::fromStdString(filePath), "deneme");  // should set content of deneme to "deneme"
    handler.ApplyChanges();

    // get content of deneme.txt
    std::ifstream file2(filePath);
    // read content of deneme.txt
    std::string content2((std::istreambuf_iterator<char>(file2)),
                         (std::istreambuf_iterator<char>()));
    // close file
    file2.close();

    // check if content is changed
    if (content2 != "deneme\n") {
        throw std::runtime_error("TestGitChangeEdit failed");
    }
}

void TestGitChangeDelete() {
}
}  // namespace git::tests

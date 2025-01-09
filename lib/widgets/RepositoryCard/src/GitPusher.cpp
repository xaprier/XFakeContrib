#include "GitPusher.hpp"

#include <stdexcept>

void GitPusher::run() {
    if (m_Repository.isNull()) {
        throw std::runtime_error("Repository not initialized");
    }

    if (m_RepoPath.isEmpty()) {
        throw std::runtime_error("Repository path is empty");
    }

    auto origin = m_Repository->Remote().split('\n').first().trimmed();
    auto branch = m_Repository->Branch({"--show-current"}).trimmed();

    m_Repository->Push({"-u", origin, branch});
}
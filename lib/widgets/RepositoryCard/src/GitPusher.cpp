#include "GitPusher.hpp"

#include <stdexcept>

#include "Logger.hpp"

void GitPusher::run() {
    if (m_Repository.isNull()) {
        Logger::log_static(QObject::tr("Repository not initialized").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        throw std::runtime_error(QObject::tr("Repository not initialized").toStdString());
    }

    if (m_RepoPath.isEmpty()) {
        Logger::log_static(QObject::tr("Repository path is empty").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        throw std::runtime_error(QObject::tr("Repository path is empty").toStdString());
    }

    auto origin = m_Repository->Remote().split('\n').first().trimmed();
    auto branch = m_Repository->Branch({"--show-current"}).trimmed();

    m_Repository->Push({"-u", origin, branch});
}
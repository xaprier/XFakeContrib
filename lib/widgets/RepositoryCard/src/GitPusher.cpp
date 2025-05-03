#include "GitPusher.hpp"

#include <stdexcept>

#include "Logger.hpp"

void GitPusher::run() {
    try {
        if (m_Repository.isNull()) {
            Logger::log_static(QObject::tr("Repository not initialized").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
            throw std::runtime_error(QObject::tr("Repository not initialized").toStdString());
        }

        if (m_RepoPath.isEmpty()) {
            Logger::log_static(QObject::tr("Repository path is empty").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
            throw std::runtime_error(QObject::tr("Repository path is empty").toStdString());
        }

        QString output;
        auto success = m_Repository->Remote(output);

        if (!success) {
            Logger::log_static(QObject::tr("Failed to get remote repository: \n%1").arg(output).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
            throw std::runtime_error(QObject::tr("Failed to get remote repository: \n%1").arg(output).toStdString());
        }

        auto origin = output.split('\n').first().trimmed();

        success = m_Repository->Branch(output, {"--show-current"});
        if (!success) {
            Logger::log_static(QObject::tr("Failed to get current branch: \n%1").arg(output).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
            throw std::runtime_error(QObject::tr("Failed to get current branch: \n%1").arg(output).toStdString());
        }

        auto branch = output.split('\n').first().trimmed();

        success = m_Repository->Push(output, {"-u", origin, branch});
        if (!success) {
            Logger::log_static(QObject::tr("Failed to push to remote repository: \n%1").arg(output).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
            throw std::runtime_error(QObject::tr("Failed to push to remote repository: \n%1").arg(output).toStdString());
        }
    } catch (const std::exception &e) {
        Logger::log_static(QObject::tr("Exception: %1").arg(e.what()).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        emit si_ErrorOccurred(QString::fromStdString(e.what()));
        return;
    } catch (...) {
        Logger::log_static(QObject::tr("Unknown error occurred in GitPusher").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        emit si_ErrorOccurred("Unknown error occurred in GitPusher");
        return;
    }

    emit this->si_PusherFinished();
}
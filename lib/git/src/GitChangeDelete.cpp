#include "GitChangeDelete.hpp"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

#include "Logger.hpp"

void GitChangeDelete::ApplyChange() {
    QMutexLocker locker(&m_Mutex);

    if (m_ReposPath.isEmpty()) {
        Logger::log_static(QObject::tr("Repository path is empty: %1").arg(m_ReposPath).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        throw std::runtime_error(QObject::tr("Repository path is empty: %1").arg(m_ReposPath).toStdString());
    }

    if (m_FileName.isEmpty()) {
        Logger::log_static(QObject::tr("File name is empty: %1").arg(m_FileName).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        throw std::runtime_error(QObject::tr("File name is empty: %1").arg(m_FileName).toStdString());
    }

    QDir dir(m_ReposPath);

    if (!dir.exists()) {
        Logger::log_static(QObject::tr("Repository path does not exist: %1").arg(dir.absolutePath()).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        throw std::runtime_error(QObject::tr("Repository path does not exist: %1").arg(dir.absolutePath()).toStdString());
    }

    QString filePath = m_FileName;
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        Logger::log_static(QObject::tr("Failed to open file for writing: %1").arg(filePath).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        throw std::runtime_error(QObject::tr("Failed to open file for writing: %1").arg(filePath).toStdString());
    }

    // close file before deleting
    file.close();

    // delete file if it exists and has permissions
    if (!file.remove()) {
        throw std::runtime_error(QObject::tr("Failed to delete file").toLatin1());
    }
}
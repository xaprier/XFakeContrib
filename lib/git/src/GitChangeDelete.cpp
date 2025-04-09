#include "GitChangeDelete.hpp"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void GitChangeDelete::ApplyChange() {
    QMutexLocker locker(&m_Mutex);

    if (m_ReposPath.isEmpty()) {
        throw std::runtime_error(QObject::tr("Repository path is empty: %1").arg(m_ReposPath).toStdString());
    }

    if (m_FileName.isEmpty()) {
        throw std::runtime_error(QObject::tr("File name is empty: %1").arg(m_FileName).toStdString());
    }

    QDir dir(m_ReposPath);

    if (!dir.exists()) {
        throw std::runtime_error(QObject::tr("Repository path does not exist: %1").arg(dir.absolutePath()).toStdString());
    }

    QString filePath = m_FileName;
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        throw std::runtime_error(QObject::tr("Failed to open file for writing: %1").arg(filePath).toStdString());
    }

    // close file before deleting
    file.close();

    // delete file if it exists and has permissions
    if (!file.remove()) {
        throw std::runtime_error("Failed to delete file");  // todo: translation
    }
}
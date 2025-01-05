#include "GitChangeCreate.hpp"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void GitChangeCreate::ApplyChange() {
    QMutexLocker locker(&m_Mutex);
    QDir dir(m_ReposPath);
    if (!dir.exists()) {
        throw std::runtime_error("Repository path does not exist");  // todo: translation
    }

    QString filePath = m_FileName;
    QFile file(filePath);
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file for writing");  // todo: translation
    }

    QTextStream out(&file);
    out << m_Change << '\n';  // append the change to the file
    file.close();
}
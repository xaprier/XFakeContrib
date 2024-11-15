#include "GitChangeDelete.hpp"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void GitChangeDelete::ApplyChange() {
    QDir dir(m_ReposPath);
    if (!dir.exists()) {
        throw std::runtime_error("Repository path does not exist");
    }

    QString filePath = QDir::toNativeSeparators(m_ReposPath + "/" + m_FileName);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file for writing");
    }

    // close file before deleting
    file.close();

    // delete file if it exists and has permissions
    if (!file.remove()) {
        throw std::runtime_error("Failed to delete file");
    }
}
#include "GitChangeDelete.hpp"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void GitChangeDelete::ApplyChange() {
    QDir dir(m_ReposPath);
    if (!dir.exists()) {
        throw std::runtime_error("Repository path does not exist");  // todo: translation
    }

    QString filePath = m_FileName;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file for writing");  // todo: translation
    }

    // close file before deleting
    file.close();

    // delete file if it exists and has permissions
    if (!file.remove()) {
        throw std::runtime_error("Failed to delete file");  // todo: translation
    }
}
#include "GitChangeCreate.hpp"

#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void GitChangeCreate::ApplyChange() {
    QDir dir(m_ReposPath);
    if (!dir.exists()) {
        throw std::runtime_error("Repository path does not exist");
    }

    QString filePath = QDir::toNativeSeparators(m_ReposPath + "/" + m_FileName);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file for writing");
    }

    QTextStream out(&file);
    out << m_Change;  // append the change to the file
    file.close();
}
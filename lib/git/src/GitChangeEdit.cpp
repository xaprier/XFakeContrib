#include "GitChangeEdit.hpp"

#include <qglobal.h>
#include <qmutex.h>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QIODevice>
#include <QTextStream>

void GitChangeEdit::ApplyChange() {
    QMutexLocker locker(&m_Mutex);
    QDir dir(m_ReposPath);
    if (!dir.exists()) {
        throw std::runtime_error("Repository path does not exist");  // todo: translation
    }

    QString filePath = m_FileName;
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file for writing");  // todo: translation
    }

    // clear file before writing
    file.resize(0);

    // write new changes to file
    QTextStream out(&file);
    out << m_Change << '\n';
    file.close();
}
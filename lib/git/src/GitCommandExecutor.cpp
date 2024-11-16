#include "GitCommandExecutor.hpp"

#include <qprocess.h>

#include "GitCommand.hpp"

void GitCommandExecutor::SetPath(const QString& path) {
    this->m_Path = path;
}

void GitCommandExecutor::Execute(const GitCommand::Command& command, const QStringList& arguments, QString& output, QString& error) {
    QString commandString = GitCommand::GitCommandToString(command);
    if (commandString.isEmpty()) {
        error = "Invalid Git command";
        qDebug() << error;
        return;
    }

    QProcess process;
    QString program = "git";
    QStringList fullArguments;
    fullArguments << commandString << arguments;

    process.setWorkingDirectory(m_Path);
    process.setInputChannelMode(QProcess::ForwardedInputChannel);
    process.start(program, fullArguments);
    if (!process.waitForStarted()) {
        error = "Failed to start Git process";
        qDebug() << error;
        return;
    }

    process.waitForFinished();
    if (process.exitStatus() == QProcess::CrashExit) {
        error = "Git Process crashed";
        qDebug() << error;
        return;
    }

    output = process.readAllStandardOutput();
    error = process.readAllStandardError();

    if (process.exitCode() == 0) error.clear();

    if (!error.isEmpty()) {
        qDebug() << "Git command error:" << error;
    }
}
#include "GitCommandExecutor.hpp"

#include "GitCommand.hpp"
#include "Logger.hpp"

void GitCommandExecutor::SetPath(const QString& path) {
    this->m_Path = path;
}

void GitCommandExecutor::Execute(const GitCommand::Command& command, const QStringList& arguments, QString& output, QString& error) {
    QString commandString = GitCommand::GitCommandToString(command);
    if (commandString.isEmpty()) {
        error = QObject::tr("Invalid Git command");
        Logger::log_static(error.toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
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
        error = QObject::tr("Failed to start Git process");
        Logger::log_static(error.toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    process.waitForFinished();
    if (process.exitStatus() == QProcess::CrashExit) {
        error = QObject::tr("Git Process crashed");
        Logger::log_static(error.toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    output = process.readAllStandardOutput();
    error = process.readAllStandardError();

    if (process.exitCode() == 0) error.clear();
}
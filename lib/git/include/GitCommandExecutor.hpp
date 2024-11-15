#ifndef GITCOMMANDEXECUTOR_HPP
#define GITCOMMANDEXECUTOR_HPP

#include <QDebug>
#include <QInputDialog>
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>

#include "GitCommand.hpp"

class GitCommandExecutor : public QObject {
    Q_OBJECT

  public:
    explicit GitCommandExecutor(const QString& path = "", QObject* parent = nullptr) : QObject(parent) {
        this->SetPath(path);
    }

    void SetPath(const QString& path);

    /**
     * Executes a Git command with the specified arguments.
     * @param command The Git subcommand to execute (e.g., "status", "commit").
     * @param arguments The list of arguments to pass to the command.
     * @param output The output of the execution
     * @param error The error output of the execution if exists
     */
    void Execute(const GitCommand::Command& command, const QStringList& arguments, QString& output, QString& error);

  private:
    QString m_Path;
};

#endif  // GITCOMMANDEXECUTOR_HPP

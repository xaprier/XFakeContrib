#ifndef GITPUSHMANAGER_HPP
#define GITPUSHMANAGER_HPP

#include "GitCommand.hpp"
#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitPushManager : public GitManager {
    Q_OBJECT
  public:
    GitPushManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        return m_Executor.Execute(GitCommand::Push, arguments, output, error);
    }

    bool HasPushRights(const QString& remote = "origin");

    QString GetCommandType() const override {
        return "Git Push Command";
    }

  private:
    GitCommandExecutor& m_Executor;
};

#endif  // GITPUSHMANAGER_HPP
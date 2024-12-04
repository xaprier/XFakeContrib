#ifndef GITREMOTEMANAGER_HPP
#define GITREMOTEMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitRemoteManager : public GitManager {
  public:
    GitRemoteManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        m_Executor.Execute(GitCommand::Remote, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Remote Command";
    }

  private:
    GitCommandExecutor& m_Executor;
};

#endif  // GITREMOTEMANAGER_HPP
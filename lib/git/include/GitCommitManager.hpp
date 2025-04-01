#ifndef GITCOMMITMANAGER_HPP
#define GITCOMMITMANAGER_HPP

#include "GitCommand.hpp"
#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitCommitManager : public GitManager {
    Q_OBJECT
  public:
    GitCommitManager(GitCommandExecutor &executor) : m_Executor(executor) {}
    void Execute(const QStringList &arguments, QString &output, QString &error) override {
        return m_Executor.Execute(GitCommand::Commit, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Commit Command";
    }

  private:
    GitCommandExecutor &m_Executor;
};

#endif  // GITCOMMITMANAGER_HPP

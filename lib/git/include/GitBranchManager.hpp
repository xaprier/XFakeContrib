#ifndef GITBRANCHMANAGER_HPP
#define GITBRANCHMANAGER_HPP

#include "GitCommand.hpp"
#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitBranchManager : public GitManager {
    Q_OBJECT
  public:
    GitBranchManager(GitCommandExecutor &executor) : m_Executor(executor) {}
    void Execute(const QStringList &arguments, QString &output, QString &error) override {
        return m_Executor.Execute(GitCommand::Branch, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Branch Command";
    }

  private:
    GitCommandExecutor &m_Executor;
};

#endif  // GITBRANCHMANAGER_HPP

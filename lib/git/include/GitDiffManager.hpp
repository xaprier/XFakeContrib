#ifndef GITDIFFMANAGER_HPP
#define GITDIFFMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitDiffManager : public GitManager {
  public:
    GitDiffManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        m_Executor.Execute(GitCommand::Diff, arguments, output, error);
        m_HasChangesToCommit = !output.isEmpty();
    }

    bool HasChangesToCommit() const {
        return m_HasChangesToCommit;
    }

    QString GetCommandType() const override {
        return "Git Diff Command";
    }

  private:
    bool m_HasChangesToCommit = false;
    GitCommandExecutor& m_Executor;
};

#endif  // GITDIFFMANAGER_HPP
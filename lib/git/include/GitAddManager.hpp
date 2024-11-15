#ifndef GITADDMANAGER_HPP
#define GITADDMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitAddManager : public GitManager {
  public:
    GitAddManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        return m_Executor.Execute(GitCommand::Add, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Add Command";
    }

  private:
    GitCommandExecutor& m_Executor;
};

#endif  // GITADDMANAGER_HPP
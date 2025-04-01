#ifndef GITLOGMANAGER_HPP
#define GITLOGMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitLogManager : public GitManager {
    Q_OBJECT
  public:
    GitLogManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        return m_Executor.Execute(GitCommand::Log, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Log Command";
    }

  private:
    GitCommandExecutor& m_Executor;
};

#endif  // GITLOGMANAGER_HPP
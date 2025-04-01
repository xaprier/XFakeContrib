#ifndef GITCHECKIGNOREMANAGER_HPP
#define GITCHECKIGNOREMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitCheckIgnoreManager : public GitManager {
    Q_OBJECT
  public:
    GitCheckIgnoreManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        m_Executor.Execute(GitCommand::CheckIgnore, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Check-Ignore Command";
    }

  private:
    GitCommandExecutor& m_Executor;
};

#endif  // GITCHECKIGNOREMANAGER_HPP
#ifndef GITCHECKOUTMANAGER_HPP
#define GITCHECKOUTMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

class GitCheckoutManager : public GitManager {
  public:
    GitCheckoutManager(GitCommandExecutor& executor) : m_Executor(executor) {}
    void Execute(const QStringList& arguments, QString& output, QString& error) override {
        m_Executor.Execute(GitCommand::Checkout, arguments, output, error);
    }

    QString GetCommandType() const override {
        return "Git Checkout Command";
    }

  private:
    GitCommandExecutor& m_Executor;
};

#endif  // GITCHECKOUTMANAGER_HPP
#ifndef GITCHANGEMANAGER_HPP
#define GITCHANGEMANAGER_HPP

#include "GitCommandExecutor.hpp"
#include "GitManager.hpp"

// class GitChangeManager : public GitManager {
//   public:
//     GitChangeManager(GitCommandExecutor& executor) : m_Executor(executor) {}
//     void Execute(const QStringList& arguments, QString& output, QString& error) override {
//         return m_Executor.Execute(GitCommand::Change, arguments, output, error);
//     }

//     bool HasPushRights(const QString& remote = "origin");

//     QString GetCommandType() const override {
//         return "Git Push Command";
//     }

//   private:
//     GitCommandExecutor& m_Executor;
// };

#endif  // GITCHANGEMANAGER_HPP
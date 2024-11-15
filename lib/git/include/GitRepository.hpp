#ifndef GITREPOSITORY_HPP
#define GITREPOSITORY_HPP

#include <qchar.h>

#include <QObject>

#include "GitAddManager.hpp"
#include "GitBranchManager.hpp"
#include "GitCommandExecutor.hpp"
#include "GitCommitManager.hpp"
#include "GitPushManager.hpp"

class GitRepository : public QObject {
  public:
    GitRepository(const QString &localRepositoryPath = "", QObject *parent = nullptr);
    void Push(const QString &remote = "", const QString &branch = "");
    void Commit(const QStringList &arguments = {"-m", "Default Commit Message"});
    void Branch(const QStringList &arguments = {});
    void Add(const QStringList &arguments = {});

    void SetRepositoryPath(const QString &localRepositoryPath = "");
    const QString &GetRepositoryPath() const { return m_RepositoryPath; }

  private:
    bool _IsValidGitRepository(const QString &path);
    void _HandleCommandResult(const QString &output, const QString &error, const QString &commandType);

  private:
    QString m_RepositoryPath;
    bool m_IsValidRepository = false;

  private:
    GitCommandExecutor m_Executor;
    GitCommitManager m_CommitManager;
    GitBranchManager m_BranchManager;
    GitPushManager m_PushManager;
    GitAddManager m_AddManager;
};

#endif  // GITREPOSITORY_HPP
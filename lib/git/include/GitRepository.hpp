#ifndef GITREPOSITORY_HPP
#define GITREPOSITORY_HPP

#include <qchar.h>

#include <QObject>

#include "GitAddManager.hpp"
#include "GitBranchManager.hpp"
#include "GitCheckIgnoreManager.hpp"
#include "GitCheckoutManager.hpp"
#include "GitCommandExecutor.hpp"
#include "GitCommitManager.hpp"
#include "GitDiffManager.hpp"
#include "GitLogManager.hpp"
#include "GitPushManager.hpp"
#include "GitRemoteManager.hpp"

class GitRepository : public QObject {
  public:
    GitRepository(const QString &localRepositoryPath = "", QObject *parent = nullptr);
    QString Push(const QStringList &arguments);
    QString Commit(const QStringList &arguments = {"-m", "Default Commit Message"});
    QString Branch(const QStringList &arguments = {});
    QString Add(const QStringList &arguments = {});
    QString Diff(const QStringList &arguments = {"--name-only"});
    QString Checkout(const QStringList &arguments = {});
    QString Log(const QStringList &arguments = {});
    QString Remote(const QStringList &arguments = {});
    QString CheckIgnore(const QStringList &arguments = {});

    void SetRepositoryPath(const QString &localRepositoryPath = "");
    QString GetRepositoryPath() const { return m_RepositoryPath; }
    bool IsValidRepository() const { return m_IsValidRepository; }

  private:
    bool _IsValidGitRepository(const QString &path);
    void _HandleCommandResult(const QString &output, const QString &error, const QString &commandType);

  private:
    QString m_RepositoryPath = "";
    bool m_IsValidRepository = false;

  private:
    GitCommandExecutor m_Executor;
    GitCommitManager m_CommitManager;
    GitBranchManager m_BranchManager;
    GitPushManager m_PushManager;
    GitAddManager m_AddManager;
    GitDiffManager m_DiffManager;
    GitCheckoutManager m_CheckoutManager;
    GitLogManager m_LogManager;
    GitRemoteManager m_RemoteManager;
    GitCheckIgnoreManager m_CheckIgnoreManager;
};

#endif  // GITREPOSITORY_HPP
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

#include "Git_Global.hpp"

class GIT_EXPORT GitRepository : public QObject {
    Q_OBJECT
  public:
    GitRepository(const QString &localRepositoryPath = "", QObject *parent = nullptr);
    bool Push(QString &output, const QStringList &arguments);
    bool Commit(QString &output, const QStringList &arguments = {"-m", "Default Commit Message"});
    bool Branch(QString &output, const QStringList &arguments = {});
    bool Add(QString &output, const QStringList &arguments = {});
    bool Diff(QString &output, const QStringList &arguments = {"--name-only"});
    bool Checkout(QString &output, const QStringList &arguments = {});
    bool Log(QString &output, const QStringList &arguments = {});
    bool Remote(QString &output, const QStringList &arguments = {});
    bool CheckIgnore(QString &output, const QStringList &arguments = {});

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
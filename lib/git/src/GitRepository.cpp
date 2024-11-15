#include "GitRepository.hpp"

#include <QDebug>
#include <QDir>

GitRepository::GitRepository(const QString &localRepositoryPath, QObject *parent)
    : QObject(parent), m_Executor(localRepositoryPath), m_CommitManager(m_Executor), m_BranchManager(m_Executor), m_PushManager(m_Executor), m_AddManager(m_Executor) {
    this->SetRepositoryPath(localRepositoryPath);
}

void GitRepository::Push(const QString &remote, const QString &branch) {
    if (!m_IsValidRepository) {
        qDebug() << "Push command aborted: Invalid Git repository path.";
        return;
    }
    qDebug() << "Executing push command...";
    QString output, error;
    QStringList arguments = {remote, branch};
    m_PushManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_PushManager.GetCommandType());
}

void GitRepository::Commit(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        qDebug() << "Commit command aborted: Invalid Git repository path.";
        return;
    }
    qDebug() << "Executing commit command...";
    QString output, error;
    m_CommitManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_CommitManager.GetCommandType());
}

void GitRepository::Branch(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        qDebug() << "Branch command aborted: Invalid Git repository path.";
        return;
    }
    qDebug() << "Executing branch command...";
    QString output, error;
    m_BranchManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_BranchManager.GetCommandType());
}

void GitRepository::Add(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        qDebug() << "Add command aborted: Invalid Git repository path.";
        return;
    }
    qDebug() << "Executing add command...";
    QString output, error;
    m_AddManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_AddManager.GetCommandType());
}

void GitRepository::SetRepositoryPath(const QString &localRepositoryPath) {
    this->m_RepositoryPath = localRepositoryPath;
    this->m_IsValidRepository = _IsValidGitRepository(localRepositoryPath);
    if (!m_IsValidRepository) {
        qDebug() << "Invalid Git repository path:" << m_RepositoryPath;
        return;
    }
    this->m_Executor.SetPath(localRepositoryPath);
}

bool GitRepository::_IsValidGitRepository(const QString &path) {
    QDir dir(path);
    return dir.exists() && dir.exists(".git");
}

void GitRepository::_HandleCommandResult(const QString &output, const QString &error, const QString &commandType) {
    if (!output.isEmpty() && error.isEmpty()) {
        qDebug() << commandType << "result:" << output;
    } else {
        if (!error.isEmpty()) {
            qDebug() << commandType << "error:" << error;
        } else {
            qDebug() << commandType << "no output and no error.";
        }
    }
}

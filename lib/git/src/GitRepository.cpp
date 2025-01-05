#include "GitRepository.hpp"

#include <QDebug>
#include <QDir>

GitRepository::GitRepository(const QString &localRepositoryPath, QObject *parent)
    : QObject(parent), m_Executor(localRepositoryPath), m_CommitManager(m_Executor), m_BranchManager(m_Executor), m_PushManager(m_Executor), m_AddManager(m_Executor), m_DiffManager(m_Executor), m_CheckoutManager(m_Executor), m_LogManager(m_Executor), m_RemoteManager(m_Executor), m_CheckIgnoreManager(m_Executor) {
    this->SetRepositoryPath(localRepositoryPath);
}

QString GitRepository::Push(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing push command...";
    QString output, error;
    m_PushManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_PushManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Commit(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing commit command...";
    QString output, error;
    m_CommitManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_CommitManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Branch(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing branch command...";
    QString output, error;
    m_BranchManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_BranchManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Add(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing add command...";
    QString output, error;
    m_AddManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_AddManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Diff(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing diff command...";
    QString output, error;
    m_DiffManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_DiffManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Checkout(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing checkout command...";
    QString output, error;
    m_CheckoutManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_CheckoutManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Log(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing log command...";
    QString output, error;
    m_LogManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_LogManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::Remote(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }
    qDebug() << "Executing remote command...";
    QString output, error;
    m_RemoteManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_RemoteManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

QString GitRepository::CheckIgnore(const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + m_RepositoryPath.toStdString());
    }

    qDebug() << "Executing check-ignore command...";
    QString output, error;
    m_CheckIgnoreManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_RemoteManager.GetCommandType());
    if (!error.isEmpty()) return error;
    return output;
}

void GitRepository::SetRepositoryPath(const QString &localRepositoryPath) {
    this->m_RepositoryPath = localRepositoryPath;
    this->m_IsValidRepository = _IsValidGitRepository(localRepositoryPath);
    if (!m_IsValidRepository) {
        throw std::invalid_argument("Invalid Git repository path: " + localRepositoryPath.toStdString());
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

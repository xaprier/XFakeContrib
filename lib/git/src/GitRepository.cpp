#include "GitRepository.hpp"

#include <QDir>
#include <QString>

#include "Logger.hpp"

GitRepository::GitRepository(const QString &localRepositoryPath, QObject *parent)
    : QObject(parent), m_Executor(localRepositoryPath), m_CommitManager(m_Executor), m_BranchManager(m_Executor), m_PushManager(m_Executor), m_AddManager(m_Executor), m_DiffManager(m_Executor), m_CheckoutManager(m_Executor), m_LogManager(m_Executor), m_RemoteManager(m_Executor), m_CheckIgnoreManager(m_Executor) {
    this->SetRepositoryPath(localRepositoryPath);
}

bool GitRepository::Push(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing push command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_PushManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_PushManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Commit(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing commit command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_CommitManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_CommitManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Branch(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing branch command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_BranchManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_BranchManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Add(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing add command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_AddManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_AddManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Diff(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing diff command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_DiffManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_DiffManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Checkout(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing checkout command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_CheckoutManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_CheckoutManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Log(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing log command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_LogManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_LogManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::Remote(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing remote command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_RemoteManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_RemoteManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

bool GitRepository::CheckIgnore(QString &message, const QStringList &arguments) {
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(m_RepositoryPath).toLatin1());
    }
    Logger::log_static(QObject::tr("Executing check-ignore command...").toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);

    QString output, error;
    m_CheckIgnoreManager.Execute(arguments, output, error);
    _HandleCommandResult(output, error, m_RemoteManager.GetCommandType());
    if (!error.isEmpty()) {
        message = error;
        return 0;
    }
    message = output;
    return 1;
}

void GitRepository::SetRepositoryPath(const QString &localRepositoryPath) {
    this->m_RepositoryPath = localRepositoryPath;
    this->m_IsValidRepository = _IsValidGitRepository(localRepositoryPath);
    if (!m_IsValidRepository) {
        throw std::invalid_argument(QObject::tr("Invalid Git repository path: %1").arg(localRepositoryPath).toLatin1());
    }
    this->m_Executor.SetPath(localRepositoryPath);
}

bool GitRepository::_IsValidGitRepository(const QString &path) {
    QDir dir(path);
    return dir.exists() && dir.exists(".git");
}

void GitRepository::_HandleCommandResult(const QString &output, const QString &error, const QString &commandType) {
    QString message;
    if (!output.isEmpty() && error.isEmpty()) {
        message = QObject::tr("%1 executed successfully: %2").arg(commandType, output);
    } else {
        if (!error.isEmpty()) {
            message = QObject::tr("%1 executed with error: %2").arg(commandType, error);
        } else {
            message = QObject::tr("%1 executed with no output.").arg(commandType);
        }
    }
    Logger::log_static(message.toStdString(), LoggingLevel::DEBUG, __LINE__, __PRETTY_FUNCTION__);
}

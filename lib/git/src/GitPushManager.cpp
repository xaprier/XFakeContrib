#include "GitPushManager.hpp"

bool GitPushManager::HasPushRights(const QString& remote) {
    QString output, error;
    QStringList arguments = {"push", "--dry-run", remote};
    m_Executor.Execute(GitCommand::Push, arguments, output, error);

    if (output.contains("Everything up-to-date") || !error.contains("permission denied")) {
        qDebug() << "User has push rights.";
        return true;
    } else {
        qDebug() << "User does not have push rights. Error:" << error;
        return false;
    }
}
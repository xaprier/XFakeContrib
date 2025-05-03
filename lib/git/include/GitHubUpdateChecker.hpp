#ifndef GITHUBUPDATECHECKER_HPP
#define GITHUBUPDATECHECKER_HPP

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

#include "Git_Global.hpp"

class GIT_EXPORT GitHubUpdateChecker : public QObject {
    Q_OBJECT

  public:
    explicit GitHubUpdateChecker(QObject* parent = nullptr);

    void Check();

  signals:
    void si_UpdateAvailable(QString currentVersion, QString latestVersion, QString downloadUrl);

  private slots:
    void sl_OnReplyFinished(QNetworkReply* reply);

  private:
    QNetworkAccessManager* m_Manager;
    QString m_CurrentVersion;
    QString m_Owner;
    QString m_Repo;
};

#endif  // GITHUBUPDATECHECKER_HPP
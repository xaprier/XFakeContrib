#ifndef GITHUBUPDATECHECKER_HPP
#define GITHUBUPDATECHECKER_HPP

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class GitHubUpdateChecker : public QObject {
    Q_OBJECT

  public:
    explicit GitHubUpdateChecker(QObject* parent = nullptr);

    void Check();

  signals:
    void si_UpdateAvailable(const QString& currentVersion, const QString& latestVersion, const QString& downloadUrl);

  private slots:
    void sl_OnReplyFinished(QNetworkReply* reply);

  private:
    QNetworkAccessManager* m_Manager;
    QString m_CurrentVersion;
    QString m_Owner;
    QString m_Repo;
};

#endif  // GITHUBUPDATECHECKER_HPP
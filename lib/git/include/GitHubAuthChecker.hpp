#ifndef GITHUBAUTHCHECKER_HPP
#define GITHUBAUTHCHECKER_HPP

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

#include "Git_Global.hpp"

class GIT_EXPORT GitHubAuthChecker : public QObject {
    Q_OBJECT

  public:
    explicit GitHubAuthChecker(QObject* parent = nullptr);

    void CheckAuthKey(const QString& authToken);

    bool IsChecking() const { return m_ProcessingValidation; }

  signals:
    void si_AuthCheckResult(bool isValid, QString message);

  private slots:
    void sl_AuthCheckFinished(QNetworkReply* reply);
    void sl_Check(QString authToken);

  private:
    std::atomic<bool> m_ProcessingValidation;
    QSharedPointer<QNetworkAccessManager> m_Manager;
};

#endif  // GITHUBAUTHCHECKER_HPP
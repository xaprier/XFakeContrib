#ifndef GITHUBAUTHCHECKER_HPP
#define GITHUBAUTHCHECKER_HPP

#include <qnetworkaccessmanager.h>
#include <qvariant.h>

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>

class GitHubAuthChecker : public QObject {
    Q_OBJECT

  public:
    explicit GitHubAuthChecker(QObject* parent = nullptr) : QObject(parent), m_ProcessingValidation(false) {
        m_Manager = QSharedPointer<QNetworkAccessManager>::create(this);
        connect(m_Manager.get(), &QNetworkAccessManager::finished, this, &GitHubAuthChecker::onAuthCheckFinished);
    }

    void checkAuthKey(const QString& authToken) {
        QUrl url("https://api.github.com/graphql");
        QNetworkRequest request(url);
        request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
        request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

        // Basit bir sorgu (örneğin, kendi kullanıcı adını sorgulama)
        QString query = "{\"query\": \"{ viewer { login } }\"}";
        QByteArray data = query.toUtf8();

        m_Manager->post(request, data);
        m_ProcessingValidation = true;
    }

    bool isChecking() const { return m_ProcessingValidation; }

  signals:
    void authCheckResult(bool isValid, const QString& message);

  private slots:
    void onAuthCheckFinished(QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            QJsonObject jsonObj = jsonDoc.object();

            if (jsonObj.contains("data")) {
                emit authCheckResult(true, "Authentication successful.");
            } else {
                emit authCheckResult(false, "Invalid authentication key.");
            }
        } else {
            emit authCheckResult(false, "Network error: " + reply->errorString());
        }
        reply->deleteLater();
        m_ProcessingValidation = false;
    }

  private:
    bool m_ProcessingValidation;
    QSharedPointer<QNetworkAccessManager> m_Manager;
};

#endif  // GITHUBAUTHCHECKER_HPP
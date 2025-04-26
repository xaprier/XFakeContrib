#include "GitHubAuthChecker.hpp"

GitHubAuthChecker::GitHubAuthChecker(QObject* parent) : QObject(parent), m_ProcessingValidation(false) {
    m_Manager = QSharedPointer<QNetworkAccessManager>::create(this);
    connect(m_Manager.get(), &QNetworkAccessManager::finished, this, &GitHubAuthChecker::sl_AuthCheckFinished);
}

void GitHubAuthChecker::CheckAuthKey(const QString& authToken) {
    QMetaObject::invokeMethod(this, "sl_Check", Qt::QueuedConnection, Q_ARG(const QString&, authToken));
}

void GitHubAuthChecker::sl_AuthCheckFinished(QNetworkReply* reply) {
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
        QJsonObject jsonObj = jsonDoc.object();

        if (jsonObj.contains("data")) {
            emit si_AuthCheckResult(true, QObject::tr("Authentication successful."));
        } else {
            emit si_AuthCheckResult(false, QObject::tr("Invalid authentication key."));
        }
    } else {
        emit si_AuthCheckResult(false, QObject::tr("Network error: %1").arg(reply->errorString()));
    }
    reply->deleteLater();
    m_ProcessingValidation = false;
}

void GitHubAuthChecker::sl_Check(const QString& authToken) {
    QUrl url("https://api.github.com/graphql");
    QNetworkRequest request(url);
    request.setRawHeader("Authorization", "Bearer " + authToken.toUtf8());
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // simple query for testing
    QString query = "{\"query\": \"{ viewer { login } }\"}";
    QByteArray data = query.toUtf8();

    m_Manager->post(request, data);
    m_ProcessingValidation = true;
}
#include "GitHubUpdateChecker.hpp"

#include "Config.hpp"
#include "Logger.hpp"
#include "LoggingLevel.hpp"

GitHubUpdateChecker::GitHubUpdateChecker(QObject* parent) : QObject(parent) {
    m_Manager = new QNetworkAccessManager(this);
    connect(m_Manager, &QNetworkAccessManager::finished, this, &GitHubUpdateChecker::sl_OnReplyFinished);

    m_CurrentVersion = QString("v%1").arg(PROJECT_VERSION);
    m_Owner = QString(PROJECT_ORGANIZATION);
    m_Repo = QString(PROJECT_NAME);
}

void GitHubUpdateChecker::Check() {
    const QString url = QString("https://api.github.com/repos/%1/%2/releases/latest").arg(m_Owner, m_Repo);
    m_Manager->get(QNetworkRequest(QUrl(url)));
}

void GitHubUpdateChecker::sl_OnReplyFinished(QNetworkReply* reply) {
    if (reply->error()) {
        Logger::log_static("Update check failed: " + reply->errorString().toStdString(), LoggingLevel::ERROR);
        reply->deleteLater();
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(reply->readAll());
    QJsonObject jsonObj = jsonDoc.object();

    QString latestVersion = jsonObj["tag_name"].toString();

    if (latestVersion.isEmpty()) {
        Logger::log_static("Invalid response on update check.", LoggingLevel::WARNING);
    } else if (latestVersion != m_CurrentVersion) {
        QString downloadUrl = jsonObj["html_url"].toString();
        emit si_UpdateAvailable(m_CurrentVersion, latestVersion, downloadUrl);
    } else {
        Logger::log_static("No update available. Current version: " + m_CurrentVersion.toStdString(), LoggingLevel::INFO);
    }

    reply->deleteLater();
}
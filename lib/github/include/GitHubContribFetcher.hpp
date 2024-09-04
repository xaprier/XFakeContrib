#ifndef GITHUBCONTRIBFETCHER_HPP
#define GITHUBCONTRIBFETCHER_HPP

#include <QDate>
#include <QEventLoop>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonParseError>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QObject>
#include <QSharedPointer>
#include <QUrl>

#include "Contrib.hpp"
#include "ContribTotal.hpp"

class GitHubContribFetcher : public QObject {
    Q_OBJECT

  public:
    GitHubContribFetcher(const QString& username, QObject* parent = nullptr)
        : QObject(parent), m_Username(username) {
        m_Manager = QSharedPointer<QNetworkAccessManager>::create(this);
    }

    const std::vector<ContribTotal>& GetTotalContribs() const {
        return m_TotalContributions;
    }

    const std::vector<Contrib>& GetContribs() const {
        return m_Contributions;
    }

    void fetchUserContributions();
    void saveFormattedJsonToFile(const QString& filename);

  private:
    void processResponse(const QByteArray& response);

  private:
    QString m_Username;
    QSharedPointer<QNetworkAccessManager> m_Manager;
    std::vector<Contrib> m_Contributions;
    std::vector<ContribTotal> m_TotalContributions;
};

#endif  // GITHUBCONTRIBFETCHER_HPP

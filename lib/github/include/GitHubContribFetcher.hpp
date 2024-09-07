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
#include <map>
#include <stdexcept>

#include "Contrib.hpp"
#include "ContribTotal.hpp"
#include "GithubAuthChecker.hpp"
#include "GithubContribLevels.hpp"

class GitHubContribFetcher : public QObject {
    Q_OBJECT

  public:
    GitHubContribFetcher(const QString& username, const QString& token, QObject* parent = nullptr)
        : QObject(parent), m_Username(username), m_Token(token), m_AuthChecker(QSharedPointer<GitHubAuthChecker>::create()), m_LastTokenValidation(false) {
        m_Manager = QSharedPointer<QNetworkAccessManager>::create(this);
        connect(m_AuthChecker.get(), &GitHubAuthChecker::authCheckResult, this, &GitHubContribFetcher::onAuthCheckResult);
        // start processing of validation token
        m_AuthChecker->checkAuthKey(token);
    }

    const std::map<int, ContribTotal>& GetTotalContribs() const {
        return m_TotalContributions;
    }

    const std::map<QDate, Contrib>& GetContribs() const {
        return m_Contributions;
    }

    void fetchUserContributions();
    void saveFormattedJsonToFile(const QString& filename);

  private slots:
    void onNetworkReplyFinished(QNetworkReply* reply);
    void onAuthCheckResult(bool isValid, const QString& message);

  signals:
    void allRepliesFinished();

  private:
    void processResponse(const QByteArray& response);
    QDate fetchFirstContributionDate();

  private:
    QString m_Username;
    QString m_Token;
    QSharedPointer<QNetworkAccessManager> m_Manager;
    QSharedPointer<GitHubAuthChecker> m_AuthChecker;
    QList<QNetworkReply*> m_ActiveReplies;
    std::map<QDate, Contrib> m_Contributions;
    std::map<int, ContribTotal> m_TotalContributions;  // year, total
    bool m_LastTokenValidation;
};

#endif  // GITHUBCONTRIBFETCHER_HPP

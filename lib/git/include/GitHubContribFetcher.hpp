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

#include "Contrib.hpp"
#include "ContribTotal.hpp"
#include "GitHubAuthChecker.hpp"

#include "Git_Global.hpp"

class GIT_EXPORT GitHubContribFetcher : public QObject {
    Q_OBJECT

  public:
    explicit GitHubContribFetcher(const QString& username, const QString& token, QObject* parent = nullptr);

    const std::map<int, ContribTotal>& GetTotalContribs() const {
        return m_TotalContributions;
    }

    const std::map<QDate, Contrib>& GetContribs() const {
        return m_Contributions;
    }

    void FetchUserContributions();
    void SaveFormattedJsonToFile(const QString& filename);

  private slots:
    void sl_NetworkReplyFinished(QNetworkReply* reply);
    void sl_AuthCheckResult(bool isValid, QString message);
    void sl_FetchUserContribs();

  signals:
    void si_AllRepliesFinished();

  private:
    void ProcessResponse(const QByteArray& response);
    QDate FetchFirstContributionDate();

  private:
    QString m_Username;
    QString m_Token;
    QSharedPointer<QNetworkAccessManager> m_Manager;
    QSharedPointer<GitHubAuthChecker> m_AuthChecker;
    QList<QNetworkReply*> m_ActiveReplies;
    std::map<QDate, Contrib> m_Contributions;
    std::map<int, ContribTotal> m_TotalContributions;  // year, total
    std::atomic<bool> m_LastTokenValidation;
};

#endif  // GITHUBCONTRIBFETCHER_HPP

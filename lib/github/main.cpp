#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QObject>
#include <QProcess>

#include "ContribTotal.hpp"
#include "GitHubAuthChecker.hpp"
#include "GitHubContribFetcher.hpp"

void TestFetcher(const QString& username, const QString& token);

void TestAuth(const QString& token);

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // username
    QString username = "xaprier";
    QString token = "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";  // will reset later
    TestFetcher(username, token);
    TestAuth(token);

    return app.exec();
}

void TestAuth(const QString& token) {
    // create fetcher
    GitHubAuthChecker* auth = new GitHubAuthChecker();

    QObject::connect(auth, &GitHubAuthChecker::si_AuthCheckResult, [&](bool isValid, const QString& message) {
        qDebug() << "Auth key is valid: " << isValid;
        qDebug() << "Message: " << message;
    });

    auth->CheckAuthKey(token);
}

void TestFetcher(const QString& username, const QString& token) {
    // create fetcher
    GitHubContribFetcher* fetcher = new GitHubContribFetcher(username, token);

    std::vector<Contrib> contribs;
    std::vector<ContribTotal> totals;

    // fetch contributions
    QObject::connect(fetcher, &GitHubContribFetcher::si_AllRepliesFinished, [&]() {
        qDebug() << "All replies finished";

        fetcher->SaveFormattedJsonToFile("data.json");
    });

    fetcher->FetchUserContributions();
}

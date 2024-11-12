#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QProcess>

#include "ContribTotal.hpp"
#include "GitHubContribFetcher.hpp"

void testFetcher(const QString& username, const QString& token) {
    // create fetcher
    GitHubContribFetcher fetcher(username, token);

    std::vector<Contrib> contribs;
    std::vector<ContribTotal> totals;

    // fetch contributions
    fetcher.FetchUserContributions();

    fetcher.SaveFormattedJsonToFile("data.json");
}

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // username
    QString username = "xaprier";
    QString token = "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";  // will reset later
    testFetcher(username, token);

    return app.exec();
}

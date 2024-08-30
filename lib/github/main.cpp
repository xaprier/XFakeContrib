#include <QCoreApplication>
#include <QDebug>

#include "GitHubContribFetcher.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // username
    QString username = "xaprier";

    // create fetcher
    GitHubContribFetcher fetcher(username);

    // fetch contributions
    fetcher.fetchUserContributions();

    fetcher.saveFormattedJsonToFile("data.json");

    return app.exec();
}

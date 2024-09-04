#include <QCoreApplication>
#include <QDebug>

#include "ContribTotal.hpp"
#include "GitHubContribFetcher.hpp"

int main(int argc, char* argv[]) {
    QCoreApplication app(argc, argv);

    // username
    QString username = "xaprier";

    // create fetcher
    GitHubContribFetcher fetcher(username);

    std::vector<Contrib> contribs;
    std::vector<ContribTotal> totals;

    // fetch contributions
    fetcher.fetchUserContributions();

    fetcher.saveFormattedJsonToFile("data.json");

    return app.exec();
}

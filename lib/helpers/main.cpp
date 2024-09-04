#include <QApplication>
#include <iostream>

#include "ContribCard.hpp"
#include "GitHubContribAdapter.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QDate firstContribDate;

    GitHubContribFetcher fetcher("xaprier");
    fetcher.fetchUserContributions();
    fetcher.saveFormattedJsonToFile("data.json");
    GitHubContribAdapter adapter(fetcher);
    auto card = adapter.adapt();

    // ContribCard contribCard(allContribs, allLevels, firstContribDate);
    card->show();

    return app.exec();
}
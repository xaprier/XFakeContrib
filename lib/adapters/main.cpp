#include <QApplication>

#include "ContribCard.hpp"
#include "GitHubContribAdapter.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QDate firstContribDate;

    GitHubContribFetcher fetcher("xaprier", "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");
    fetcher.FetchUserContributions();
    fetcher.SaveFormattedJsonToFile("data.json");
    GitHubContribAdapter adapter(fetcher);
    auto card = adapter.adapt();

    // ContribCard contribCard(allContribs, allLevels, firstContribDate);
    card->show();

    return app.exec();
}
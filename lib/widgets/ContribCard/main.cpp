#include <qapplication.h>
#include <qdatetime.h>

#include <QApplication>

#include "Contrib.hpp"
#include "ContribCard.hpp"
#include "ContribTotal.hpp"
#include "ContributionPeriod.hpp"
#include "DayContrib.hpp"
#include "LevelColorIndicator.hpp"
#include "MonthContrib.hpp"
#include "YearContrib.hpp"

// Function to generate random contributions for a given number of weeks and days per week
std::map<QDate, Contrib> generateRandomContributions(QDate startDate = QDate::currentDate().addYears(-1)) {
    QDate current = startDate;
    std::map<QDate, Contrib> contributions;

    while (current != QDate::currentDate()) {
        int contrib = std::rand() % 20;
        int level = contrib / 4;
        contributions[current] = Contrib(level, contrib);
        current = current.addDays(1);
    }

    return contributions;
}

std::map<int, ContribTotal> generateRandomTotalContributions(std::map<QDate, Contrib> contribs) {
    std::map<int, ContribTotal> total;
    ContribTotal lastYear(0, 0);
    for (const auto& [date, contrib] : contribs) {
        int currentCount = contrib.GetCount();
        int currentLevel = contrib.GetLevel();
        QDate currentDAte = contrib.GetDate();
        total[date.year()] = ContribTotal(total[date.year()].GetCount() + contrib.GetCount(), date.year());
        if (QDate::currentDate().addYears(-1) < date && QDate::currentDate() >= date)
            lastYear.SetCount(lastYear.GetCount() + currentCount);
    }
    total[0] = lastYear;
    return total;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int weeks = 55;            // Number of weeks to generate
    int maxContribution = 20;  // Maximum value for random contribution

    // Generate random contributions
    auto contributions = generateRandomContributions(QDate(2021, 10, 12));
    auto totalContributions = generateRandomTotalContributions(contributions);

    // DayContrib contrib(8, 24);
    // contrib.show();

    // WeekContrib contrib(QDate(2015, 9, 13), std::vector<int>{3, 0, 5, 2, 9, 7}, 9);
    // contrib.show();

    // QDate startDate(2023, 8, 26);
    // auto* monthContrib = new MonthContrib(startDate, contributions, levels);
    // monthContrib->show();

    // YearContrib yearContrib("Last 12 Months", contributions, levels);
    // yearContrib.show();

    // LevelColorIndicator indic;
    // indic.show();

    // ContributionPeriod period(QDate(2021, 5, 13));
    // period.show();

    ContribCard card;
    card.Update(contributions);
    card.show();
    return app.exec();
}
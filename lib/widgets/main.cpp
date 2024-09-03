#include <qapplication.h>

#include <QApplication>

#include "ContribCard.hpp"
#include "ContributionPeriod.hpp"
#include "DayContrib.hpp"
#include "LevelColorIndicator.hpp"
#include "MonthContrib.hpp"
#include "YearContrib.hpp"

// Function to generate random contributions for a given number of weeks and days per week
std::vector<int> generateRandomContributions(int weeks, int maxContribution) {
    std::vector<int> contributions(7 * weeks);

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < weeks * 7; ++i) {
        contributions[i] = std::rand() % (maxContribution + 1);  // Random contribution between 0 and maxContribution
    }

    return contributions;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int weeks = 55;            // Number of weeks to generate
    int maxContribution = 20;  // Maximum value for random contribution

    // Generate random contributions
    std::vector<int> contributions = generateRandomContributions(weeks, maxContribution);
    std::vector<int> levels = generateRandomContributions(weeks, 4);

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

    ContribCard card(contributions, levels, QDate(2021, 5, 23));
    card.show();

    return app.exec();
}
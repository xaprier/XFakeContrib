#include <qapplication.h>

#include <QApplication>

#include "DayContrib.hpp"
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

    // DayContrib contrib(8, 24);
    // contrib.show();

    // WeekContrib contrib(QDate(2015, 9, 13), std::vector<int>{3, 0, 5, 2, 9, 7}, 9);
    // contrib.show();

    // QDate startDate = QDate::currentDate().addDays(-QDate::currentDate().daysInMonth() + 1);  // Ayın başı
    // auto* monthContrib = new MonthContrib(startDate, contributions, maxContribution);
    // monthContrib->show();

    YearContrib yearContrib(contributions, maxContribution);
    yearContrib.show();

    return app.exec();
}
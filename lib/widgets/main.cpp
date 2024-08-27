#include <qapplication.h>

#include <QApplication>

#include "DayContrib.hpp"
#include "MonthContrib.hpp"
#include "WeekContrib.hpp"

// Function to generate random contributions for a given number of weeks and days per week
std::vector<std::vector<int>> generateRandomContributions(int weeks, int daysPerWeek, int maxContribution) {
    std::vector<std::vector<int>> contributions(weeks, std::vector<int>(daysPerWeek));

    // Seed the random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < weeks; ++i) {
        for (int j = 0; j < daysPerWeek; ++j) {
            contributions[i][j] = std::rand() % (maxContribution + 1);  // Random contribution between 0 and maxContribution
        }
    }

    return contributions;
}

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    int weeks = 6;             // Number of weeks in the month
    int daysPerWeek = 7;       // Number of days in a week
    int maxContribution = 20;  // Maximum value for random contribution

    // Generate random contributions
    std::vector<std::vector<int>> contributions = generateRandomContributions(weeks, daysPerWeek, maxContribution);

    // DayContrib contrib(8, 24);
    // contrib.show();

    // WeekContrib contrib(QDate(2015, 9, 13), std::vector<int>{3, 0, 5, 2, 9, 7}, 9);
    // contrib.show();

    int totalContrib = 20;                                                                    // Maksimum katkı sayısı
    QDate startDate = QDate::currentDate().addDays(-QDate::currentDate().daysInMonth() + 1);  // Ayın başı

    MonthContrib* monthContrib = new MonthContrib(startDate, contributions, totalContrib);
    monthContrib->show();

    return app.exec();
}
#ifndef MONTHCONTRIB_HPP
#define MONTHCONTRIB_HPP

#include <qlabel.h>
#include <qnamespace.h>

#include <QDate>
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>
#include <memory>
#include <vector>

#include "WeekContrib.hpp"

class MonthContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a start date and contributions for the month
    MonthContrib(const QDate& startDate, const std::vector<std::vector<int>>& contribCounts, int totalContrib, QWidget* parent = nullptr)
        : QWidget(parent), m_StartDate(startDate) {
        QGridLayout* mainLayout = new QGridLayout(this);

        // Add the month label at the top
        QLabel* monthLabel = new QLabel(m_StartDate.toString("MMMM"), this);  // E.g., "August 2024"
        monthLabel->setAlignment(Qt::AlignCenter);                            // Center align the month name
        mainLayout->addWidget(monthLabel, 0, 0, 1, 1);

        // get first monday in month
        auto firstMonday = this->getFirstMondayOfMonth(startDate);
        // get week count until end of the month
        auto lastSunday = this->getLastSundayAfterMonth(startDate);
        int weekCount = std::ceil(firstMonday.daysTo(lastSunday) / 7.0);

        // Create and add WeekContrib widgets
        QDate currentMonday = firstMonday;
        for (int i = 0; i < weekCount; ++i) {
            std::vector<int> weeklyContribCounts;
            if (i < contribCounts.size()) {
                weeklyContribCounts = contribCounts[i];
            }
            m_WeekContribs.push_back(std::make_shared<WeekContrib>(currentMonday, weeklyContribCounts, totalContrib, this));

            // Add the WeekContrib widget to the layout in the correct position
            mainLayout->addWidget(m_WeekContribs.back().get(), 1, i, 7, 1);  // Adding to row (1 + i), spanning all columns (7)

            // Move to the next Monday
            currentMonday = currentMonday.addDays(7);
        }

        setLayout(mainLayout);  // Set the layout for the widget
    }

    // Function to get the start date of the month
    QDate getStartDate() const {
        return m_StartDate;
    }

    // Function to get the list of WeekContrib widgets as weak pointers
    std::vector<std::weak_ptr<WeekContrib>> getWeekContribs() const {
        std::vector<std::weak_ptr<WeekContrib>> weakPtrs;
        weakPtrs.reserve(m_WeekContribs.size());

        // Convert each shared_ptr to a weak_ptr and add it to the result vector
        for (const auto& sharedPtr : m_WeekContribs) {
            weakPtrs.push_back(sharedPtr);
        }

        return weakPtrs;
    }

  private:
    QDate getFirstMondayOfMonth(const QDate& date) {
        QDate firstMondayOfMonth = QDate(date.year(), date.month(), 1);
        while (firstMondayOfMonth.dayOfWeek() != Qt::Monday) {
            firstMondayOfMonth = firstMondayOfMonth.addDays(1);
        }
        return firstMondayOfMonth;
    }

    QDate getLastSundayAfterMonth(const QDate& startDate) {
        QDate lastDayOfMonth(startDate.year(), startDate.month(), startDate.daysInMonth());
        while (lastDayOfMonth.dayOfWeek() != Qt::Sunday) {
            lastDayOfMonth = lastDayOfMonth.addDays(1);
        }
        return lastDayOfMonth;
    }

  private:
    QDate m_StartDate;                                         // Start date of the month
    std::vector<std::shared_ptr<WeekContrib>> m_WeekContribs;  // List of WeekContrib widgets for each week of the month
    std::shared_ptr<QLabel> m_Label;
};

#endif  // MONTHCONTRIB_HPP

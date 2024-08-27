#ifndef MONTHCONTRIB_HPP
#define MONTHCONTRIB_HPP

#include <qlabel.h>
#include <qlayout.h>
#include <qnamespace.h>

#include <QDate>
#include <QDebug>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

#include "WeekContrib.hpp"

class MonthContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a start date and contributions for the month
    MonthContrib(const QDate& startDate, const std::vector<int>& contribCounts, int maxContrib, QWidget* parent = nullptr)
        : QWidget(parent), m_StartDate(startDate) {
        QGridLayout* mainLayout = new QGridLayout(this);

        // Set spacing to reduce gaps between weeks
        mainLayout->setSpacing(0);
        mainLayout->setContentsMargins(5, 5, 5, 5);

        // Add the month label at the top
        QLabel* monthLabel = new QLabel(m_StartDate.toString("MMMM"), this);  // E.g., "August 2024"
        monthLabel->setAlignment(Qt::AlignCenter);                            // Center align the month name
        // monthLabel->setFixedHeight(20);

        // get first monday in month
        auto firstMonday = this->getFirstMondayOfMonth(startDate);
        // get week count until end of the month
        auto lastSunday = this->getLastSundayAfterMonth(startDate);
        int weekCount = std::ceil(firstMonday.daysTo(lastSunday) / 7.0);
        mainLayout->addWidget(monthLabel, 0, 0, 1, weekCount);

        // Calculate the number of days from today to the first Monday of the month
        auto today = QDate::currentDate();
        int daysFromTodayToFirstMonday = firstMonday.daysTo(today);

        // Calculate the total number of days for the current month
        int dayCount = weekCount * 7;

        // Initialize a vector of contributions for the current month
        std::vector<int> contribs(dayCount, 0);

        // Check bounds before performing the copy operation
        if (daysFromTodayToFirstMonday >= 0 && daysFromTodayToFirstMonday + dayCount <= contribCounts.size()) {
            std::copy(contribCounts.end() - daysFromTodayToFirstMonday - dayCount, contribCounts.end() - daysFromTodayToFirstMonday, contribs.begin());
        }

        // Create and add WeekContrib widgets
        QDate currentMonday = firstMonday;
        for (int i = 0; i < weekCount; ++i) {
            std::vector<int> weeklyContribCounts(contribs.begin() + 7 * i, contribs.begin() + 7 * (i + 1));
            auto weekContrib = std::make_shared<WeekContrib>(currentMonday, weeklyContribCounts, maxContrib, this);
            // Add the WeekContrib widget to the layout in the correct position
            mainLayout->addWidget(weekContrib.get(), 1, i);

            // Move to the next Monday
            currentMonday = currentMonday.addDays(7);
            m_WeekContribs.push_back(weekContrib);
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

#ifndef MONTHCONTRIB_HPP
#define MONTHCONTRIB_HPP

#include <qdatetime.h>
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
#include <memory>
#include <vector>

#include "DayContrib.hpp"

class MonthContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a start date and contributions for the month
    MonthContrib(const QDate& monthDate, const std::vector<int>& contribCounts, int maxContrib, QWidget* parent = nullptr)
        : QWidget(parent), m_MonthDate(monthDate) {
        QGridLayout* mainLayout = new QGridLayout(this);

        // Set spacing to reduce gaps between weeks
        mainLayout->setSpacing(2);
        mainLayout->setContentsMargins(5, 5, 5, 5);

        // Add the month label at the top
        QLabel* monthLabel = new QLabel(m_MonthDate.toString("MMMM"), this);  // E.g., "August"
        monthLabel->setAlignment(Qt::AlignCenter);                            // Center align the month name

        QDate startDate(monthDate.year(), monthDate.month(), 1);

        auto weekCount = this->getWeekCountInMonth(monthDate);
        mainLayout->addWidget(monthLabel, 0, 0, 1, weekCount);

        // Initialize a vector of contributions for the current month
        std::vector<int> contribs(startDate.daysInMonth(), 0);
        int dayDiff = startDate.daysTo(QDate::currentDate());

        // Check bounds before performing the copy operation
        if (dayDiff + startDate.daysInMonth() < contribCounts.size() && dayDiff >= 0) {
            std::copy(contribCounts.begin() + dayDiff, contribCounts.begin() + dayDiff + startDate.daysInMonth(), contribs.begin());
        }

        // Create and add DayContrib widgets
        auto day = startDate;
        for (int i = 0, week = 0; i < startDate.daysInMonth() && day <= QDate::currentDate(); ++i) {
            auto dayContrib = std::make_shared<DayContrib>(contribs[i], maxContrib, day);
            int dayInWeek = day.dayOfWeek();
            mainLayout->addWidget(dayContrib.get(), dayInWeek, week, 1, 1);
            this->m_DayContribs.push_back(dayContrib);
            if (day.dayOfWeek() == Qt::Sunday) week++;
            day = day.addDays(1);
        }

        setLayout(mainLayout);  // Set the layout for the widget
    }

    // Function to get the start date of the month
    QDate getStartDate() const {
        return QDate(m_MonthDate.year(), m_MonthDate.month(), 1);
    }

    // Function to get the list of WeekContrib widgets as weak pointers
    std::vector<std::weak_ptr<DayContrib>> getDayContribs() const {
        std::vector<std::weak_ptr<DayContrib>> weakPtrs;
        weakPtrs.reserve(m_DayContribs.size());

        // Convert each shared_ptr to a weak_ptr and add it to the result vector
        for (const auto& sharedPtr : m_DayContribs) {
            weakPtrs.push_back(sharedPtr);
        }

        return weakPtrs;
    }

  private:
    int getWeekCountInMonth(const QDate& date) {
        // first day of month
        QDate firstDayOfMonth(date.year(), date.month(), 1);
        // last day of month
        QDate lastDayOfMonth = firstDayOfMonth.addMonths(1).addDays(-1);

        // first monday offset
        int firstWeekMondayOffset = (firstDayOfMonth.dayOfWeek() - Qt::Monday + 7) % 7;
        QDate firstMonday = firstDayOfMonth.addDays(-firstWeekMondayOffset);

        // last sundy offset
        int lastWeekSundayOffset = (Qt::Sunday - lastDayOfMonth.dayOfWeek() + 7) % 7;
        QDate lastSunday = lastDayOfMonth.addDays(lastWeekSundayOffset);

        // day count between firstMonday and lastSunday
        int totalDays = firstMonday.daysTo(lastSunday) + 1;

        // get total weeks with integer
        int weekCount = totalDays / 7;

        // add missing part of week
        if (totalDays % 7 != 0) {
            ++weekCount;
        }

        return weekCount;
    }

  private:
    QDate m_MonthDate;                                       // Month date of the month
    std::vector<std::shared_ptr<DayContrib>> m_DayContribs;  // List of DayContrib widgets for each week of the month
    std::shared_ptr<QLabel> m_Label;
};

#endif  // MONTHCONTRIB_HPP

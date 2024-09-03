#include "MonthContrib.hpp"

#include <qwidget.h>

#include <memory>

MonthContrib::MonthContrib(const QDate& endDate, const std::vector<int>& contribCounts, const std::vector<int>& contribLevels, QWidget* parent)
    : QWidget(parent), m_EndDate(endDate) {
    QGridLayout* mainLayout = new QGridLayout(this);

    // Set spacing to reduce gaps between weeks
    mainLayout->setSpacing(2);
    mainLayout->setContentsMargins(5, 5, 5, 5);

    // Add the month label at the top
    m_Label = std::make_shared<QLabel>(endDate.toString("MMMM"), this);  // E.g., "August"
    m_Label->setAlignment(Qt::AlignCenter);                              // Center align the month name

    QDate startDate(endDate.year(), endDate.month(), 1);

    auto weekCount = this->getWeekCountInMonth(endDate);
    mainLayout->addWidget(m_Label.get(), 0, 0, 1, weekCount);

    // Initialize a vector of contributions for the current month
    int dayDiff = startDate.daysTo(QDate::currentDate());
    int daysInMonth = endDate.day();
    std::vector<int> contribs(daysInMonth, 0);
    std::vector<int> levels(daysInMonth, 0);

    // Check bounds before performing the copy operation
    if (dayDiff + daysInMonth < contribCounts.size() && dayDiff >= 0) {
        std::copy(contribCounts.begin() + dayDiff, contribCounts.begin() + dayDiff + daysInMonth, contribs.begin());
        std::copy(contribLevels.begin() + dayDiff, contribLevels.begin() + dayDiff + daysInMonth, levels.begin());
    }

    // Create and add DayContrib widgets
    auto day = startDate;
    int week = 0;
    for (int i = 0; i < daysInMonth; ++i) {
        auto dayContrib = std::make_shared<DayContrib>(contribs[i], levels[i], day);
        int dayInWeek = day.dayOfWeek();
        mainLayout->addWidget(dayContrib.get(), dayInWeek, week, 1, 1);
        this->m_DayContribs.push_back(dayContrib);
        if (day.dayOfWeek() == Qt::Sunday) week++;
        day = day.addDays(1);
    }

    for (int col = 0; col < week + 1; ++col) {
        mainLayout->setColumnStretch(col, 1);  // Ensure the column stretches
    }

    for (int row = 0; row < 8; ++row) {
        mainLayout->setRowStretch(row, 1);  // Ensure the row stretches
    }

    setLayout(mainLayout);  // Set the layout for the widget
    setMinimumSize(115, 150);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

std::vector<std::weak_ptr<DayContrib>> MonthContrib::getDayContribs() const {
    std::vector<std::weak_ptr<DayContrib>> weakPtrs;
    weakPtrs.reserve(m_DayContribs.size());

    // Convert each shared_ptr to a weak_ptr and add it to the result vector
    for (const auto& sharedPtr : m_DayContribs) {
        weakPtrs.push_back(sharedPtr);
    }

    return weakPtrs;
}

int MonthContrib::getWeekCountInMonth(const QDate& date) const {
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
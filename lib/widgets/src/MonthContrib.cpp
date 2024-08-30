#include "MonthContrib.hpp"

MonthContrib::MonthContrib(const QDate& monthDate, const std::vector<int>& contribCounts, const std::vector<int>& contribLevels, QWidget* parent)
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
    std::vector<int> levels(startDate.daysInMonth(), 0);
    int dayDiff = startDate.daysTo(QDate::currentDate());

    // Check bounds before performing the copy operation
    if (dayDiff + startDate.daysInMonth() < contribCounts.size() && dayDiff >= 0) {
        std::copy(contribCounts.begin() + dayDiff, contribCounts.begin() + dayDiff + startDate.daysInMonth(), contribs.begin());
        std::copy(contribLevels.begin() + dayDiff, contribLevels.begin() + dayDiff + startDate.daysInMonth(), levels.begin());
    }

    // Create and add DayContrib widgets
    auto day = startDate;
    for (int i = 0, week = 0; i < startDate.daysInMonth() && day <= QDate::currentDate(); ++i) {
        auto dayContrib = std::make_shared<DayContrib>(contribs[i], levels[i], day);
        int dayInWeek = day.dayOfWeek();
        mainLayout->addWidget(dayContrib.get(), dayInWeek, week, 1, 1);
        this->m_DayContribs.push_back(dayContrib);
        if (day.dayOfWeek() == Qt::Sunday) week++;
        day = day.addDays(1);
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
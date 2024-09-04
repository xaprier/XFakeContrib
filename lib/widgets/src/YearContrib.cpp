#include "YearContrib.hpp"

#include <qdebug.h>

#include <algorithm>
#include <memory>

YearContrib::YearContrib(const QString& title, const std::vector<Contrib>& allContribs, const QDate& end_date, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(5, 5, 5, 5);

    // Calculate the start date: 1 year ago from today
    QDate oneYearAgo = end_date.addYears(-1);

    // Adjust to the nearest Monday
    QDate startDate = oneYearAgo;

    // Add the year label at the top
    m_Label = new QLabel(title, this);  // E.g., "2023 - 2024"
    m_Label->setAlignment(Qt::AlignCenter);
    m_Label->setFixedHeight(16);
    mainLayout->addWidget(m_Label);

    // Create a horizontal layout for the months
    QHBoxLayout* monthsLayout = new QHBoxLayout();

    // Create MonthContrib widgets starting from `startDate`
    QDate currentMonthStartDate = QDate(startDate.year(), startDate.month(), 1);
    int monthIndex = 0;

    while (currentMonthStartDate <= end_date) {
        // Determine the end date of the current month
        QDate monthEndDate = currentMonthStartDate.addMonths(1).addDays(-1);

        // If the current month is the last month, adjust the end date
        if (currentMonthStartDate.month() == end_date.month() && currentMonthStartDate.year() == end_date.year()) {
            monthEndDate = end_date;
        }

        int days = monthEndDate.day();

        auto monthContrib = new MonthContrib(monthEndDate, allContribs, this);

        // Add the MonthContrib widget to the horizontal layout
        monthsLayout->addWidget(monthContrib);

        // Create and add MonthContrib widgets for each month
        m_MonthContribs.push_back(monthContrib);

        // Move to the next month
        currentMonthStartDate = currentMonthStartDate.addMonths(1);
    }

    // Add the months layout to the main layout
    mainLayout->addLayout(monthsLayout);

    setLayout(mainLayout);  // Set the layout for the widget
}

const std::vector<MonthContrib*> YearContrib::getMonthContribs() const {
    return this->m_MonthContribs;
}
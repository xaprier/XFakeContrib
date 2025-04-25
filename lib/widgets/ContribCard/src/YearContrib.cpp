#include "YearContrib.hpp"

#include <set>

#include "MonthContrib.hpp"

YearContrib::YearContrib(QWidget* parent, const QString& title, const std::map<QDate, Contrib>& allContribs, const QDate& endDate)
    : QWidget(parent), m_EndDate(endDate), m_Title(title), m_AllContribs(allContribs) {
    this->_SetupUI();
    this->Update(title, allContribs, endDate);
}

void YearContrib::Update(const QString& title, const std::map<QDate, Contrib>& allContribs, const QDate& endDate) {
    this->_UpdateTitle(title);
    this->_UpdateEndDate(endDate);
    this->_UpdateContrib(allContribs);
}

const std::vector<QWeakPointer<MonthContrib>> YearContrib::GetMonthContribs() const {
    std::vector<QWeakPointer<MonthContrib>> weakPtrs;
    weakPtrs.reserve(m_MonthContribs.size());  // Optimize allocation

    // Iterate over the QSharedPointer vector
    for (const auto& sharedPtr : m_MonthContribs) {
        weakPtrs.push_back(sharedPtr);
    }

    return weakPtrs;
}

void YearContrib::_SetupUI() {
    // Layout for the main widget, this should raw data and will be deleted by Qt parent
    m_Layout = new QVBoxLayout(this);
    m_Layout->setContentsMargins(5, 5, 5, 5);

    // Add the year label at the top
    m_Label = QSharedPointer<QLabel>::create(this);  // E.g., "2023 - 2024"
    m_Label->setAlignment(Qt::AlignCenter);
    m_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    m_Layout->addWidget(m_Label.get());

    // Create a horizontal layout for the months
    m_MonthsLayout = new QHBoxLayout(this);

    m_Layout->addLayout(m_MonthsLayout);

    setLayout(m_Layout);  // Set the layout for the widget
}

void YearContrib::_UpdateTitle(const QString& title) {
    this->m_Title = title;
    this->m_Label->setText(m_Title);
}

void YearContrib::_UpdateEndDate(const QDate& endDate) {
    this->m_EndDate = endDate;
}

void YearContrib::_UpdateContrib(const std::map<QDate, Contrib>& allContribs) {
    this->m_AllContribs = allContribs;

    QDate oneYearAgo = m_EndDate.addYears(-1);
    QDate startDate = oneYearAgo;
    QDate currentMonthStartDate = QDate(startDate.year(), startDate.month(), 1);

    // Set to keep track of active months (only year and month)
    std::set<QDate> activeMonths;

    // Vector to store all the months and their corresponding data
    std::vector<QDate> monthsInOrder;

    // Loop through the months in the year range
    while (currentMonthStartDate <= m_EndDate) {
        QDate monthEndDate = currentMonthStartDate.addMonths(1).addDays(-1);

        // If the current month is the last month, adjust the end date
        if (currentMonthStartDate.month() == m_EndDate.month() && currentMonthStartDate.year() == m_EndDate.year()) {
            monthEndDate = m_EndDate;
        }

        // Mark this month as active (only year and month)
        activeMonths.insert(monthEndDate);

        // Save the month in the monthsInOrder vector for later sorting
        monthsInOrder.push_back(monthEndDate);
        currentMonthStartDate = currentMonthStartDate.addMonths(1);
    }

    // Sort months in ascending order
    std::sort(monthsInOrder.begin(), monthsInOrder.end());

    // Now process the months in sorted order
    for (const QDate& monthEndDate : monthsInOrder) {
        int days = monthEndDate.day();

        // Find the existing MonthContrib widget for this month if it exists
        auto it = std::find_if(m_MonthContribs.begin(), m_MonthContribs.end(), [&](const QSharedPointer<MonthContrib>& mc) {
            QDate currentDate = mc->GetEndDate();
            return currentDate == monthEndDate;
        });

        if (it != m_MonthContribs.end()) {
            // Update existing widget
            (*it)->SetMonth(monthEndDate);
            (*it)->SetContribs(allContribs);
        } else {
            // Create a new MonthContrib widget if it doesn't exist
            auto monthContrib = QSharedPointer<MonthContrib>::create(monthEndDate, allContribs, this);
            m_MonthContribs.push_back(monthContrib);
            m_MonthsLayout->addWidget(monthContrib.get());
        }
    }

    // Remove unused MonthContribs based on month and year
    m_MonthContribs.erase(std::remove_if(m_MonthContribs.begin(), m_MonthContribs.end(), [&](const QSharedPointer<MonthContrib>& mc) {
                              QDate startDate = mc->GetEndDate();
                              if (activeMonths.find(startDate) == activeMonths.end()) {
                                  m_MonthsLayout->removeWidget(mc.get());
                                  mc->deleteLater();
                                  return true;  // Mark for removal
                              }
                              return false;
                          }),
                          m_MonthContribs.end());
}
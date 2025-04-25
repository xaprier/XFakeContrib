#include "MonthContrib.hpp"

#include <set>

#include "DayContrib.hpp"

MonthContrib::MonthContrib(const QDate& endDate, const std::map<QDate, Contrib>& allContribs, QWidget* parent)
    : QWidget(parent), m_EndDate(endDate), m_Label(QSharedPointer<QLabel>::create("", this)), m_AllContribs(allContribs) {
    this->_SetupUI();
    this->_Update();
}

void MonthContrib::SetMonth(const QDate& monthDate) {
    m_EndDate = monthDate;
    this->_Update();
}

void MonthContrib::SetContribs(const std::map<QDate, Contrib>& allContribs) {
    m_AllContribs = allContribs;
    this->_Update();
}

std::vector<QWeakPointer<DayContrib>> MonthContrib::GetDayContribs() const {
    std::vector<QWeakPointer<DayContrib>> weakPtrs;
    weakPtrs.reserve(m_DayContribs.size());  // Optimize allocation

    // Iterate over the QSharedPointer vector
    for (const auto& sharedPtr : m_DayContribs) {
        weakPtrs.push_back(sharedPtr);
    }

    return weakPtrs;
}

int MonthContrib::_GetWeekCountInMonth(const QDate& date) const {
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

void MonthContrib::_SetupUI() {
    // Layout for the main widget, this should raw data and will be deleted by Qt parent
    m_MainLayout = new QGridLayout(this);

    m_Label->setAlignment(Qt::AlignCenter);  // Center align the month name
    m_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    const int spacing = 1;
    const int margin = 2;

    // Set spacing to reduce gaps between weeks
    m_MainLayout->setSpacing(spacing);
    m_MainLayout->setContentsMargins(margin, margin, margin, margin);

    QDate startDate(m_EndDate.year(), m_EndDate.month(), 1);
    auto weekCount = this->_GetWeekCountInMonth(m_EndDate);

    const int minHeight = 160;  // Size of each square
    const int minWidth = 100;
    const int daysInWeek = 7;
    const int verticalSpacingCount = daysInWeek - 1;
    const int horizontalSpacingCount = weekCount - 1;
    const int height = minHeight + (verticalSpacingCount * spacing);
    const int width = minWidth + (horizontalSpacingCount * spacing);

    setLayout(m_MainLayout);      // Set the layout for the widget
    setFixedSize(width, height);  // Set a fixed size for the widget
}

void MonthContrib::_Update() {
    // Add the month label at the top
    m_Label->setText(m_EndDate.toString("MMMM"));  // E.g., "August"
    QDate startDate(m_EndDate.year(), m_EndDate.month(), 1);
    auto weekCount = this->_GetWeekCountInMonth(m_EndDate);
    m_MainLayout->removeWidget(m_Label.get());
    m_MainLayout->addWidget(m_Label.get(), 0, 0, 1, weekCount);

    int daysInMonth = m_EndDate.day();
    auto day = startDate;
    int week = 0;

    // Set of active days in the current month
    std::set<QDate> activeDays;

    for (int i = 0; i < daysInMonth; ++i) {
        activeDays.insert(day);
        // Find the existing DayContrib widget for this day if it exists
        auto it = std::find_if(m_DayContribs.begin(), m_DayContribs.end(), [&](const QSharedPointer<DayContrib>& dc) {
            return dc->GetDate() == day;
        });

        int count = 0;
        int level = 0;
        auto contribIt = m_AllContribs.find(day);
        if (contribIt != m_AllContribs.end()) {
            count = contribIt->second.GetCount();
            level = contribIt->second.GetLevel();
        }

        if (it != m_DayContribs.end()) {
            // Update existing widget
            (*it)->SetContribCount(count, level);
            (*it)->SetDate(day);
        } else {
            // Create a new DayContrib widget if it doesn't exist
            auto dayContrib = QSharedPointer<DayContrib>::create(count, level, day, this);
            m_DayContribs.push_back(dayContrib);
            int dayInWeek = day.dayOfWeek();
            m_MainLayout->addWidget(m_DayContribs.back().get(), dayInWeek, week, 1, 1);
        }

        if (day.dayOfWeek() == Qt::Sunday) week++;
        day = day.addDays(1);
    }

    // Remove unused DayContribs that are not part of the current month
    m_DayContribs.erase(std::remove_if(m_DayContribs.begin(), m_DayContribs.end(), [&](const QSharedPointer<DayContrib>& dc) {
                            if (activeDays.find(dc->GetDate()) == activeDays.end()) {
                                m_MainLayout->removeWidget(dc.get());
                                dc->deleteLater();
                                return true;  // Mark for removal
                            }
                            return false;
                        }),
                        m_DayContribs.end());

    for (int col = 0; col < week + 1; ++col) {
        m_MainLayout->setColumnStretch(col, 1);
    }

    for (int row = 0; row < 8; ++row) {
        m_MainLayout->setRowStretch(row, 1);
    }
}
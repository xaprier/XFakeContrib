#ifndef WEEKCONTRIB_HPP
#define WEEKCONTRIB_HPP

#include <QDate>
#include <QGridLayout>
#include <QWidget>
#include <memory>

#include "DayContrib.hpp"

class WeekContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a start date and contributions for the week
    WeekContrib(const QDate& startDate, const std::vector<int>& contribCounts, int maxContrib, QWidget* parent = nullptr)
        : QWidget(parent), m_StartDate(startDate) {
        // Create a layout to arrange the days of the week vertically
        QGridLayout* layout = new QGridLayout(this);
        layout->setSpacing(2);  // Set spacing between widgets
        layout->setContentsMargins(2, 4, 2, 4);

        // Initialize DayContrib widgets for each day of the week
        for (int i = 0; i < 7; ++i) {
            QDate day = m_StartDate.addDays(i);
            int contribCount = i < contribCounts.size() ? contribCounts[i] : 0;
            auto dayContrib = std::make_shared<DayContrib>(contribCount, maxContrib, day, this);
            layout->addWidget(dayContrib.get(), i, 0);  // Add the widget to the layout
            m_DayContribs.push_back(dayContrib);        // Store in the list
        }

        setLayout(layout);  // Set the layout for the widget
    }

    // Function to get the start date of the week
    QDate getStartDate() const {
        return m_StartDate;
    }

    std::vector<std::weak_ptr<DayContrib>> getDayContribs() const {
        std::vector<std::weak_ptr<DayContrib>> weakPtrs;
        weakPtrs.reserve(m_DayContribs.size());  // Reserve space for efficiency

        // Convert each shared_ptr to a weak_ptr and add it to the result vector
        for (const auto& sharedPtr : m_DayContribs) {
            weakPtrs.push_back(sharedPtr);
        }

        return weakPtrs;
    }

  private:
    QDate m_StartDate;                                       // Start date of the week
    std::vector<std::shared_ptr<DayContrib>> m_DayContribs;  // List of DayContrib widgets for each day of the week
};

#endif  // WEEKCONTRIB_HPP

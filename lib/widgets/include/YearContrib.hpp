#ifndef YEARCONTRIB_HPP
#define YEARCONTRIB_HPP

#include <QDate>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <vector>

#include "MonthContrib.hpp"

class YearContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize the year with the contributions
    YearContrib(const std::vector<int>& allContribs, const std::vector<int>& allContribLevels, const QDate& end_date = QDate::currentDate(), QWidget* parent = nullptr);

    // Function to get the start date of the year
    QDate getStartDate() const {
        return m_StartDate;
    }

    // Function to get the list of MonthContrib widgets as weak pointers
    std::vector<std::weak_ptr<MonthContrib>> getMonthContribs() const;

  private:
    QDate m_StartDate;                                           // Start date of the year
    std::vector<std::shared_ptr<MonthContrib>> m_MonthContribs;  // List of MonthContrib widgets for each month of the year
};

#endif  // YEARCONTRIB_HPP
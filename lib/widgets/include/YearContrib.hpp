#ifndef YEARCONTRIB_HPP
#define YEARCONTRIB_HPP

#include <QDate>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <memory>
#include <vector>

#include "Contrib.hpp"
#include "MonthContrib.hpp"

class YearContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize the year with the contributions
    YearContrib(const QString& title, const std::vector<Contrib>& allContribs, const QDate& end_date = QDate::currentDate(), QWidget* parent = nullptr);

    // Function to get the start date of the year
    QDate getStartDate() const {
        return m_StartDate;
    }

    // Function to get the list of MonthContrib widgets as weak pointers
    const std::vector<MonthContrib*> getMonthContribs() const;

  private:
    QDate m_StartDate;  // Start date of the year
    QLabel* m_Label;
    std::vector<MonthContrib*> m_MonthContribs;  // List of MonthContrib widgets for each month of the year
};

#endif  // YEARCONTRIB_HPP
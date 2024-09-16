#ifndef YEARCONTRIB_HPP
#define YEARCONTRIB_HPP

#include <qvariant.h>

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
    YearContrib(const QString& title, const std::map<QDate, Contrib>& allContribs, const QDate& end_date = QDate::currentDate(), QWidget* parent = nullptr);

    // Function to get the start date of the year
    QDate getStartDate() const {
        return m_StartDate;
    }

    // Function to get the list of MonthContrib widgets as weak pointers
    const std::vector<QWeakPointer<MonthContrib>> getMonthContribs() const;

  private:
    QDate m_StartDate;  // Start date of the year
    QSharedPointer<QLabel> m_Label;
    std::vector<QSharedPointer<MonthContrib>> m_MonthContribs;  // List of MonthContrib widgets for each month of the year
};

#endif  // YEARCONTRIB_HPP
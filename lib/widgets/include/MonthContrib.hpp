#ifndef MONTHCONTRIB_HPP
#define MONTHCONTRIB_HPP

#include <qdatetime.h>
#include <qevent.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qnamespace.h>
#include <qsizepolicy.h>

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
    MonthContrib(const QDate& monthDate, const std::vector<int>& contribCounts, const std::vector<int>& contribLevels, QWidget* parent = nullptr);

    // Function to get the start date of the month
    QDate getStartDate() const {
        return QDate(m_MonthDate.year(), m_MonthDate.month(), 1);
    }

    // Function to get the list of WeekContrib widgets as weak pointers
    std::vector<std::weak_ptr<DayContrib>> getDayContribs() const;

  private:
    int getWeekCountInMonth(const QDate& date) const;

  private:
    QDate m_MonthDate;                                       // Month date of the month
    std::vector<std::shared_ptr<DayContrib>> m_DayContribs;  // List of DayContrib widgets for each week of the month
    std::shared_ptr<QLabel> m_Label;
};

#endif  // MONTHCONTRIB_HPP

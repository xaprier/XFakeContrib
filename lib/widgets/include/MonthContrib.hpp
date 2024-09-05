#ifndef MONTHCONTRIB_HPP
#define MONTHCONTRIB_HPP

#include <qdatetime.h>
#include <qevent.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qnamespace.h>
#include <qsizepolicy.h>
#include <qvariant.h>

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

#include "Contrib.hpp"
#include "DayContrib.hpp"

class MonthContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a start date and contributions for the month
    MonthContrib(const QDate& monthDate, const std::map<QDate, Contrib>& allContribs, QWidget* parent = nullptr);

    // Function to get the start date of the month
    QDate getStartDate() const {
        return QDate(m_EndDate.year(), m_EndDate.month(), 1);
    }

    // Function to get the list of WeekContrib widgets as weak pointers
    std::vector<QWeakPointer<DayContrib>> getDayContribs() const;

  private:
    int getWeekCountInMonth(const QDate& date) const;

  private:
    QDate m_EndDate;                                        // end date of month
    std::vector<QSharedPointer<DayContrib>> m_DayContribs;  // List of DayContrib widgets for each week of the month
    QSharedPointer<QLabel> m_Label;
};

#endif  // MONTHCONTRIB_HPP

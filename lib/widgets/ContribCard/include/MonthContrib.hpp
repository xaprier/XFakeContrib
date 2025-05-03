#ifndef MONTHCONTRIB_HPP
#define MONTHCONTRIB_HPP

#include <QDate>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <cmath>
#include <vector>

#include "Contrib.hpp"
#include "DayContrib.hpp"

class MonthContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a start date and contributions for the month
    MonthContrib(const QDate& monthDate, const std::map<QDate, Contrib>& allContribs, QWidget* parent = nullptr);

    void SetMonth(const QDate& monthDate = QDate::currentDate());
    void SetContribs(const std::map<QDate, Contrib>& allContribs = {});

    // Function to get the start date of the month
    QDate GetStartDate() const {
        return QDate(m_EndDate.year(), m_EndDate.month(), 1);
    }

    QDate GetEndDate() const {
        return m_EndDate;
    }

    // Function to get the list of WeekContrib widgets as weak pointers
    std::vector<QWeakPointer<DayContrib>> GetDayContribs() const;

  private:
    int _GetWeekCountInMonth(const QDate& date) const;
    void _SetupUI();
    void _Update();

  private:
    QGridLayout* m_MainLayout;
    std::map<QDate, Contrib> m_AllContribs;
    QDate m_EndDate;                                        // end date of month
    std::vector<QSharedPointer<DayContrib>> m_DayContribs;  // List of DayContrib widgets for each week of the month
    QSharedPointer<QLabel> m_Label;
};

#endif  // MONTHCONTRIB_HPP

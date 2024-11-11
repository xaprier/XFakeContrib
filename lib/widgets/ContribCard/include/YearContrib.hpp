#ifndef YEARCONTRIB_HPP
#define YEARCONTRIB_HPP

#include <QDate>
#include <QHBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QWidget>
#include <set>
#include <vector>

#include "Contrib.hpp"
#include "MonthContrib.hpp"

// todo: refactor to update
class YearContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize the year with the contributions
    YearContrib(QWidget* parent = nullptr, const QString& title = "", const std::map<QDate, Contrib>& allContribs = {}, const QDate& end_date = QDate::currentDate());

    // Function to get the start date of the year
    QDate GetEndDate() const {
        return m_EndDate;
    }

    void Update(const QString& title = "", const std::map<QDate, Contrib>& allContribs = {}, const QDate& endDate = QDate::currentDate());

    // Function to get the list of MonthContrib widgets as weak pointers
    const std::vector<QWeakPointer<MonthContrib>> GetMonthContribs() const;

  private:
    void _SetupUI();
    void _UpdateTitle(const QString& title);
    void _UpdateEndDate(const QDate& endDate);
    void _UpdateContrib(const std::map<QDate, Contrib>& allContribs);

  private:
    QDate m_EndDate;  // Start date of the year
    QString m_Title;
    std::map<QDate, Contrib> m_AllContribs;
    QVBoxLayout* m_Layout;
    QHBoxLayout* m_MonthsLayout;
    QSharedPointer<QLabel> m_Label;
    std::vector<QSharedPointer<MonthContrib>> m_MonthContribs;  // List of MonthContrib widgets for each month of the year
};

#endif  // YEARCONTRIB_HPP
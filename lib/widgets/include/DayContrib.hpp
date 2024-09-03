#ifndef DAYCONTRIB_HPP
#define DAYCONTRIB_HPP

#include <QDate>
#include <QEnterEvent>
#include <QEvent>
#include <QPainter>
#include <QResizeEvent>
#include <QSizePolicy>
#include <QToolTip>
#include <QWidget>

#include "ContribColor.hpp"

class DayContrib : public QWidget {
    Q_OBJECT

  public:
    // Constructor to initialize with a contribution count and total contributions
    DayContrib(int contribCount = 0, int contribLevel = 0, const QDate& date = QDate::currentDate(), QWidget* parent = nullptr);

    // Function to set contribution count and update color
    void setContribCount(int contribCount, int contribLevel);

    // Function to set the date
    void setDate(const QDate& date) {
        m_Date = date;
    }

    // Function to get the date
    QDate getDate() const {
        return m_Date;
    }

  protected:
    // Override the paintEvent to draw the widget with the corresponding color
    void paintEvent(QPaintEvent* event) override;

    // Override the enterEvent to show the date as a tooltip
    void enterEvent(QEnterEvent* event) override;

    // Override the leaveEvent to hide the tooltip when the cursor leaves the widget
    void leaveEvent(QEvent* event) override;

  private:
    int m_ContribCount;    // Contribution count for the day
    ContribColor m_Color;  // Color based on contribution count
    QDate m_Date;          // Date associated with the contribution
};

#endif  // DAYCONTRIB_HPP

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
    void SetContribCount(int contribCount, int contribLevel);

    // Function to set the date
    void SetDate(const QDate& date) {
        m_Date = date;
    }

    // Function to get the date
    QDate GetDate() const {
        return m_Date;
    }

    void UpdateColor();

  signals:
    void si_LeftClicked(const QDate& date);
    void si_RightClicked(const QDate& date);
    void si_MiddleClicked(const QDate& date);

  protected:
    // Override the paintEvent to draw the widget with the corresponding color
    void paintEvent(QPaintEvent* event) override;

// Override the enterEvent to show the date as a tooltip
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
    void enterEvent(QEnterEvent* event) override;
#else
    void enterEvent(QEvent* event) override;
#endif

    // Override the leaveEvent to hide the tooltip when the cursor leaves the widget
    void leaveEvent(QEvent* event) override;

    // Override the mousePressEvent to emit signals when the widget is clicked
    void mousePressEvent(QMouseEvent* event) override;

  private:
    int m_ContribCount;    // Contribution count for the day
    int m_ContribLevel;    // Contribution level for the day
    ContribColor m_Color;  // Color based on contribution count
    QDate m_Date;          // Date associated with the contribution
};

#endif  // DAYCONTRIB_HPP

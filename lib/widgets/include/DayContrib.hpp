#ifndef DAYCONTRIB_HPP
#define DAYCONTRIB_HPP

#include <qevent.h>

#include <QDate>
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
    DayContrib(int contribCount = 0, int totalContrib = 0, const QDate& date = QDate::currentDate(), QWidget* parent = nullptr)
        : QWidget(parent), m_ContribCount(contribCount), m_Date(date) {
        m_Color = ContribColor(m_ContribCount, totalContrib);
        setMinimumSize(16, 16);  // Set a minimum size for the widget
        setContentsMargins(2, 2, 2, 2);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    // Function to set contribution count and update color
    void setContribCount(int contribCount, int totalContrib) {
        m_ContribCount = contribCount;
        m_Color = ContribColor(m_ContribCount, totalContrib);
        update();  // Repaint the widget
    }

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
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setBrush(m_Color);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());  // Fill the widget with the color
    }

    // Override the enterEvent to show the date as a tooltip
    void enterEvent(QEnterEvent* event) override {
        QWidget::enterEvent(event);  // Call base class implementation
        QToolTip::showText(mapToGlobal(QPoint(width() / 2, height() / 2)), m_Date.toString("dd MMM yyyy"));
    }

    // Override the leaveEvent to hide the tooltip when the cursor leaves the widget
    void leaveEvent(QEvent* event) override {
        QWidget::leaveEvent(event);  // Call base class implementation
        QToolTip::hideText();
    }

  private:
    int m_ContribCount;    // Contribution count for the day
    ContribColor m_Color;  // Color based on contribution count
    QDate m_Date;          // Date associated with the contribution
};

#endif  // DAYCONTRIB_HPP

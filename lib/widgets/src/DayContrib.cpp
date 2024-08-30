#include "DayContrib.hpp"

DayContrib::DayContrib(int contribCount, int totalContrib, const QDate& date, QWidget* parent)
    : QWidget(parent), m_ContribCount(contribCount), m_Date(date) {
    m_Color = ContribColor(m_ContribCount, totalContrib);
    setMinimumSize(16, 16);  // Set a minimum size for the widget
    setContentsMargins(2, 2, 2, 2);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void DayContrib::setContribCount(int contribCount, int totalContrib) {
    m_ContribCount = contribCount;
    m_Color = ContribColor(m_ContribCount, totalContrib);
    update();  // Repaint the widget
}

void DayContrib::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(m_Color);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());  // Fill the widget with the color
}

void DayContrib::enterEvent(QEnterEvent* event) {
    QWidget::enterEvent(event);  // Call base class implementation
    QToolTip::showText(mapToGlobal(QPoint(width() / 2, height() / 2)), m_Date.toString("dd MMM yyyy"));
}

void DayContrib::leaveEvent(QEvent* event) {
    QWidget::leaveEvent(event);  // Call base class implementation
    QToolTip::hideText();
}
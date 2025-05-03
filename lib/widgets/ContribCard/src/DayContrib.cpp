#include "DayContrib.hpp"

#include <QLocale>

DayContrib::DayContrib(int contribCount, int contribLevel, const QDate& date, QWidget* parent)
    : QWidget(parent), m_ContribCount(contribCount), m_Date(date), m_ContribLevel(contribLevel) {
    this->SetContribCount(contribCount, contribLevel);
    setMinimumSize(16, 16);  // Set a minimum size for the widget
    setMaximumSize(24, 24);  // Set a maximum size for the widget
    setContentsMargins(2, 2, 2, 2);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

void DayContrib::SetContribCount(int contribCount, int contribLevel) {
    m_ContribCount = contribCount;
    m_ContribLevel = contribLevel;
    this->UpdateColor();
}

void DayContrib::UpdateColor() {
    m_Color = ContribColor(m_ContribLevel);
    update();  // Repaint the widget
}

void DayContrib::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setBrush(m_Color);
    painter.setPen(Qt::NoPen);
    painter.drawRect(rect());  // Fill the widget with the color
}
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
void DayContrib::enterEvent(QEnterEvent* event) {
#else
void DayContrib::enterEvent(QEvent* event) {
#endif
    QWidget::enterEvent(event);  // Call base class implementation
    QString text = QObject::tr("Count %1\nDate %2").arg(m_ContribCount).arg(QLocale().toString(m_Date, "ddd, dd MMM yyyy"));
    QToolTip::showText(mapToGlobal(QPoint(width() / 2, height() / 2)), text);
}

void DayContrib::leaveEvent(QEvent* event) {
    QWidget::leaveEvent(event);  // Call base class implementation
    QToolTip::hideText();
}

void DayContrib::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        emit si_LeftClicked(m_Date);
    } else if (event->button() == Qt::RightButton) {
        emit si_RightClicked(m_Date);
    } else if (event->button() == Qt::MiddleButton) {
        emit si_MiddleClicked(m_Date);
    }

    QWidget::mousePressEvent(event);  // Call base class implementation
}
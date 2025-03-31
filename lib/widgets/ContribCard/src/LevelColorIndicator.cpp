#include "LevelColorIndicator.hpp"

LevelColorIndicator::LevelColorIndicator(QWidget* parent) : QWidget(parent) {
    // Layout for the main widget, this should raw data and will be deleted by Qt parent
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_LessLabel = std::make_shared<QLabel>(QObject::tr("Less"), this);
    m_MoreLabel = std::make_shared<QLabel>(QObject::tr("More"), this);

    m_LessLabel->setAlignment(Qt::AlignRight);

    layout->addWidget(m_LessLabel.get());

    m_DayContribs = std::make_shared<std::array<_DayContribWithoutToolTip, 5>>();
    for (std::size_t i = 0; i < m_DayContribs->size(); i++) {
        m_DayContribs->at(i).SetContribCount(0, i);
        m_DayContribs->at(i).setToolTip("");
        layout->addWidget(&m_DayContribs->at(i));
    }

    layout->addWidget(m_MoreLabel.get());

    setLayout(layout);
}

void LevelColorIndicator::UpdateColors() {
    for (std::size_t i = 0; i < m_DayContribs->size(); i++) {
        m_DayContribs->at(i).UpdateColor();
    }
}

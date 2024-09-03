#include "LevelColorIndicator.hpp"

LevelColorIndicator::LevelColorIndicator(QWidget* parent) : QWidget(parent) {
    m_Layout = std::make_shared<QHBoxLayout>(this);
    m_LessLabel = std::make_shared<QLabel>(QObject::tr("Less"), this);
    m_MoreLabel = std::make_shared<QLabel>(QObject::tr("More"), this);

    m_LessLabel->setAlignment(Qt::AlignRight);

    m_Layout->addWidget(m_LessLabel.get());

    m_DayContribs = std::make_shared<std::array<_DayContribWithoutToolTip, 5>>();
    for (std::size_t i = 0; i < m_DayContribs->size(); i++) {
        m_DayContribs->at(i).setContribCount(0, i);
        m_DayContribs->at(i).setToolTip("");
        m_Layout->addWidget(&m_DayContribs->at(i));
    }

    m_Layout->addWidget(m_MoreLabel.get());

    setLayout(m_Layout.get());
}
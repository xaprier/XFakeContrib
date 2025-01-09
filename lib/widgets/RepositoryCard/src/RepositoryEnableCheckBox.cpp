#include "RepositoryEnableCheckBox.hpp"

#include <QHBoxLayout>
#include <QMouseEvent>

RepositoryEnableCheckBox::RepositoryEnableCheckBox(QWidget *parent) : QWidget(parent) {
    m_CheckBox = new QCheckBox(this);  // NOLINT
    m_CheckBox->setCheckState(Qt::CheckState::Unchecked);
    m_CheckBox->setToolTip(QObject::tr("Enable/Disable Repository"));

    // set align center
    QHBoxLayout *layout = new QHBoxLayout(this);  // NOLINT
    layout->addWidget(m_CheckBox);
    layout->setAlignment(Qt::AlignCenter);
    this->setLayout(layout);

    connect(this->m_CheckBox, &QCheckBox::stateChanged, [this](int state) {
        emit this->stateChanged(state);
    });
}

void RepositoryEnableCheckBox::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton && event->type() == QEvent::MouseButtonDblClick)
        m_CheckBox->setChecked(!m_CheckBox->isChecked());
    QWidget::mousePressEvent(event);
}
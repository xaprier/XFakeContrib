#include "ThemeSelectionCard.hpp"

#include <qboxlayout.h>
#include <qscopedpointer.h>

ThemeSelectionCard::ThemeSelectionCard(QWidget *parent)
    : QWidget(parent),
      m_Layout(new QHBoxLayout(this)),
      m_ThemeSelectionComboBox(new ThemeSelectionComboBox(this)),
      m_ApplyButton(new QPushButton(Icon(":/icons/checked.svg"), QObject::tr("Apply"), this)) {
    m_Layout->addWidget(m_ThemeSelectionComboBox.data());
    m_Layout->addWidget(m_ApplyButton.data());

    connect(m_ApplyButton.data(), &QPushButton::clicked, m_ThemeSelectionComboBox.data(), &ThemeSelectionComboBox::sl_OnApplyButtonClicked);
}

ThemeSelectionCard::~ThemeSelectionCard() {
    qDebug() << "ThemeSelectionCard destructor";
}

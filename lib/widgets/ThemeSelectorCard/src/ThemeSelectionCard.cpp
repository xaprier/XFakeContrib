#include "ThemeSelectionCard.hpp"

ThemeSelectionCard::ThemeSelectionCard(QWidget *parent)
    : Card(parent),
      m_Layout(new QHBoxLayout(this)),
      m_ThemeSelectionComboBox(new ThemeSelectionComboBox(this)),
      m_ApplyButton(new QPushButton(Icon(":/icons/checked.svg"), QObject::tr("Apply"), this)) {
    m_Layout->addWidget(m_ThemeSelectionComboBox.data());
    m_Layout->addWidget(m_ApplyButton.data());

    connect(m_ApplyButton.data(), &QPushButton::clicked, [this]() {
        this->m_ThemeSelectionComboBox->sl_OnApplyButtonClicked();
        emit si_ThemeUpdated();
    });
}

ThemeSelectionCard::~ThemeSelectionCard() {
}

void ThemeSelectionCard::UpdateIcons() {
    m_ApplyButton->setIcon(Icon(":/icons/checked.svg"));
}

#include "ThemeSelectionCard.hpp"

#include <qnamespace.h>

#include "StyleManager.hpp"

ThemeSelectionCard::ThemeSelectionCard(QWidget *parent)
    : Card(parent),
      m_Layout(new QHBoxLayout(this)),
      m_ThemeSelectionComboBox(new QComboBox(this)),
      m_ApplyButton(new QPushButton(Icon(":/icons/checked.svg"), QObject::tr("Apply"), this)) {
    m_Layout->addWidget(m_ThemeSelectionComboBox);
    m_Layout->addWidget(m_ApplyButton);

    this->_LoadThemes();

    connect(m_ApplyButton, &QPushButton::clicked, [this]() {
        // this->m_ThemeSelectionComboBox->sl_OnApplyButtonClicked();
        this->sl_OnApplyButtonClicked();
        emit si_ThemeUpdated();
    });

    setLayout(m_Layout);
}

ThemeSelectionCard::~ThemeSelectionCard() {
}

void ThemeSelectionCard::UpdateIcons() {
    m_ApplyButton->setIcon(Icon(":/icons/checked.svg"));
}

void ThemeSelectionCard::sl_OnApplyButtonClicked() {
    auto selected = this->m_ThemeSelectionComboBox->currentText();
    StyleManager::SetTheme(selected);
}

void ThemeSelectionCard::_LoadThemes() noexcept {
    m_Themes = StyleManager::GetThemes();
    auto current = StyleManager::GetTheme();

    // adding items to the combo box with showing the current theme
    for (const auto &theme : m_Themes) {
        this->m_ThemeSelectionComboBox->addItem(theme);
        if (theme == current) {
            this->m_ThemeSelectionComboBox->setCurrentText(theme);
        }
    }
}

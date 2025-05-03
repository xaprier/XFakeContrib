#include "ThemeSelectionComboBox.hpp"

#include "StyleManager.hpp"
#include "Logger.hpp"

ThemeSelectionComboBox::ThemeSelectionComboBox(QWidget *parent) : QComboBox(parent) {
    _LoadThemes();
}

void ThemeSelectionComboBox::_LoadThemes() noexcept {
    m_Themes = StyleManager::GetThemes();
    auto current = StyleManager::GetTheme();

    // adding items to the combo box with showing the current theme
    for (const auto &theme : m_Themes) {
        addItem(theme);
        if (theme == current) {
            setCurrentText(theme);
        }
    }
}

void ThemeSelectionComboBox::sl_OnApplyButtonClicked() {
    auto selected = this->currentText();
    Logger::log_static(QObject::tr("Applied theme %1").arg(selected).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
    StyleManager::SetTheme(selected);
}
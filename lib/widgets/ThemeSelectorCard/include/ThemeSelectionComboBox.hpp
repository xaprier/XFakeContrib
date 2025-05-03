#ifndef THEMESELECTIONCOMBOBOX_HPP
#define THEMESELECTIONCOMBOBOX_HPP

#include <QComboBox>
#include <QString>
#include <QStringList>

class ThemeSelectionComboBox : public QComboBox {
    Q_OBJECT
  public:
    explicit ThemeSelectionComboBox(QWidget *parent = nullptr);
    ~ThemeSelectionComboBox() = default;

  public slots:
    void sl_OnApplyButtonClicked();

  private:
    void _LoadThemes() noexcept;

  private:
    QStringList m_Themes;
};

#endif  // THEMESELECTIONCOMBOBOX_HPP
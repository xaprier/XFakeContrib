#ifndef THEMESELECTIONCARD_HPP
#define THEMESELECTIONCARD_HPP

#include <QBoxLayout>
#include <QPushButton>
#include <QScopedPointer>
#include <QWidget>

#include "Icon.hpp"
#include "ThemeSelectionComboBox.hpp"

class ThemeSelectionCard : public QWidget {
    Q_OBJECT
  public:
    explicit ThemeSelectionCard(QWidget *parent = nullptr);
    ~ThemeSelectionCard() override;

    Icon GetIcon() const { return Icon(":/icons/theme.svg"); }
    QString GetName() const { return QObject::tr("Theme Manager"); }

  private:
    QScopedPointer<QPushButton> m_ApplyButton;
    QScopedPointer<ThemeSelectionComboBox> m_ThemeSelectionComboBox;
    QScopedPointer<QHBoxLayout> m_Layout;
};

#endif  // THEMESELECTIONCARD_HPP
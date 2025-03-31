#ifndef THEMESELECTIONCARD_HPP
#define THEMESELECTIONCARD_HPP

#include <QBoxLayout>
#include <QPushButton>
#include <QScopedPointer>
#include <QWidget>

#include "Card.hpp"
#include "Icon.hpp"
#include "ThemeSelectionComboBox.hpp"

class ThemeSelectionCard : public Card {
    Q_OBJECT
  public:
    explicit ThemeSelectionCard(QWidget* parent = nullptr);
    ~ThemeSelectionCard() override;

    virtual Icon GetIcon() const override { return Icon(":/icons/theme.svg"); }
    virtual QString GetName() const override { return QObject::tr("Theme Manager"); }

    virtual void UpdateIcons() override;
    virtual void Update() override {}

  signals:
    void si_ThemeUpdated();

  private:
    QScopedPointer<QPushButton> m_ApplyButton;
    QScopedPointer<ThemeSelectionComboBox> m_ThemeSelectionComboBox;
    QScopedPointer<QHBoxLayout> m_Layout;
};

#endif  // THEMESELECTIONCARD_HPP
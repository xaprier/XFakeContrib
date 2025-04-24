#ifndef THEMESELECTIONCARD_HPP
#define THEMESELECTIONCARD_HPP

#include <qcombobox.h>

#include <QBoxLayout>
#include <QListWidget>
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

  private slots:
    void sl_OnApplyButtonClicked();

  signals:
    void si_ThemeUpdated();

  private:
    void _LoadThemes() noexcept;

    QPushButton* m_ApplyButton;
    // QSharedPointer<ThemeSelectionComboBox> m_ThemeSelectionComboBox;
    QStringList m_Themes;
    QComboBox* m_ThemeSelectionComboBox;
    QHBoxLayout* m_Layout;
};

#endif  // THEMESELECTIONCARD_HPP
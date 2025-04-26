#ifndef CARD_HPP
#define CARD_HPP

#include <QString>
#include <QWidget>

#include "Icon.hpp"

class Card : public QWidget {
    Q_OBJECT
  public:
    using QWidget::QWidget;

    virtual Icon GetIcon() const = 0;
    virtual QString GetName() const = 0;

    virtual void Update() = 0;
    virtual void UpdateIcons() = 0;
};

#endif  // CARD_HPP

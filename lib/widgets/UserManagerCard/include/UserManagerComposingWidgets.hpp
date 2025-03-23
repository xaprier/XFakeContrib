#ifndef USERMANAGERCOMPOSINGWIDGETS_HPP
#define USERMANAGERCOMPOSINGWIDGETS_HPP

#include "XQWidgetComposer.hpp"

class UserManagerComposingWidgets : public xaprier::Qt::Widgets::XQWidgetComposer {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UserManagerComposingWidgets)
  public:
    explicit UserManagerComposingWidgets(QList<QWidget *> list = {}, QWidget *parent = nullptr);
    ~UserManagerComposingWidgets() override;

    void SetWidgets(QList<QWidget *> list = {});

    [[nodiscard]] virtual QWidget *Item(int index = 0) const;

  public slots:
    virtual void Set(int index = 0);

  private:
    QList<QWidget *> m_List;
};

#endif  // USERMANAGERCOMPOSINGWIDGETS_HPP
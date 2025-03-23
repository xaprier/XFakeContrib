#ifndef REPOSITORYMANAGERCOMPOSINGWIDGETS_HPP
#define REPOSITORYMANAGERCOMPOSINGWIDGETS_HPP

#include "XQWidgetComposer.hpp"

class RepositoryManagerComposingWidgets : public xaprier::Qt::Widgets::XQWidgetComposer {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryManagerComposingWidgets)
  public:
    explicit RepositoryManagerComposingWidgets(QList<QWidget *> list = {}, QWidget *parent = nullptr);
    ~RepositoryManagerComposingWidgets() override;

    void SetWidgets(QList<QWidget *> list = {});

    [[nodiscard]] virtual QWidget *Item(int index = 0) const;

  public slots:
    virtual void Set(int index = 0);

  private:
    QList<QWidget *> m_List;
};

#endif  // REPOSITORYMANAGERCOMPOSINGWIDGETS_HPP
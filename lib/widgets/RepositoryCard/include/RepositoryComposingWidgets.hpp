#ifndef REPOSITORYCOMPOSINGWIDGETS_HPP
#define REPOSITORYCOMPOSINGWIDGETS_HPP

#include "XQWidgetComposer.hpp"

class RepositoryComposingWidgets : public xaprier::Qt::Widgets::XQWidgetComposer {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryComposingWidgets)
  public:
    explicit RepositoryComposingWidgets(QList<QWidget *> list = {}, QWidget *parent = nullptr);
    ~RepositoryComposingWidgets() override;

    void SetWidgets(QList<QWidget *> list = {});

    [[nodiscard]] virtual QWidget *Item(int index = 0) const;

  public slots:
    virtual void Set(int index = 0);

  private:
    QList<QWidget *> m_List;
};

#endif  // REPOSITORYCOMPOSINGWIDGETS_HPP
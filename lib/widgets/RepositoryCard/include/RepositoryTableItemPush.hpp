#ifndef REPOSITORYTABLEITEMPUSH_HPP
#define REPOSITORYTABLEITEMPUSH_HPP

#include <QPointer>
#include <QToolButton>

#include "RepositoryComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryTableItemPush final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemPush)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit RepositoryTableItemPush(QWidget *parent = nullptr);
    ~RepositoryTableItemPush() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

  public slots:
    void SetLoading();
    void SetButton();
    void Set(Status status);

  private:
    QPointer<xaprier::Qt::Widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<QToolButton> m_Button;
};

#endif  // REPOSITORYTABLEITEMPUSH_HPP
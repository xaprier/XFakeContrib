#ifndef REPOSITORYCARDPUSH_HPP
#define REPOSITORYCARDPUSH_HPP

#include <QPointer>
#include <QPushButton>

#include "RepositoryComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryCardPush final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCardPush)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit RepositoryCardPush(QWidget *parent = nullptr);
    ~RepositoryCardPush() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

  public slots:
    void SetLoading();
    void SetButton();
    void Set(Status status);

  private:
    QPointer<xaprier::qt::widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<QPushButton> m_Button;
};

#endif  // REPOSITORYCARDPUSH_HPP
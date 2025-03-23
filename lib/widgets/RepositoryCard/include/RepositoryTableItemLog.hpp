#ifndef REPOSITORYTABLEITEMLOG_HPP
#define REPOSITORYTABLEITEMLOG_HPP

#include <QPointer>
#include <QToolButton>

#include "RepositoryComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryTableItemLog final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItemLog)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit RepositoryTableItemLog(QWidget *parent = nullptr);
    ~RepositoryTableItemLog() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

  public slots:
    void SetButton();
    void SetLoading();
    void Set(Status status);

  private:
    QPointer<QToolButton> m_Button;
    QPointer<xaprier::Qt::Widgets::XQCircularLoadingIndicator> m_Indicator;
};

#endif  // REPOSITORYTABLEITEMLOG_HPP
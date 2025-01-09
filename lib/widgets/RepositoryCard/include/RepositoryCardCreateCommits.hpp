#ifndef REPOSITORYCARDCREATECOMMITS_HPP
#define REPOSITORYCARDCREATECOMMITS_HPP

#include <QPointer>
#include <QPushButton>

#include "RepositoryComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryCardCreateCommits final : public RepositoryComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCardCreateCommits)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit RepositoryCardCreateCommits(QWidget *parent = nullptr);
    ~RepositoryCardCreateCommits() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryComposingWidgets::Item(static_cast<int>(status)); }

  public slots:
    void SetLoading();
    void SetButton();
    void Set(Status status);

  private:
    QPointer<xaprier::qt::widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<QPushButton> m_Button;
};

#endif  // REPOSITORYCARDCREATECOMMITS_HPP
#ifndef REPOSITORYMANAGERCOMPOSEDBUTTON_HPP
#define REPOSITORYMANAGERCOMPOSEDBUTTON_HPP

#include <QPointer>
#include <QToolButton>

#include "RepositoryManagerComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryManagerComposedButton final : public RepositoryManagerComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryManagerComposedButton)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit RepositoryManagerComposedButton(QWidget *parent = nullptr);
    ~RepositoryManagerComposedButton() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryManagerComposingWidgets::Item(static_cast<int>(status)); }

    void SetToolTip(Status type, const QString &message = "");
    void SetDisabled(Status type, bool disable = false);

  signals:
    void si_ButtonClicked(bool checked = false);

  public slots:
    void SetLoading();
    void SetButton();
    void Set(Status status);

  private:
    QPointer<xaprier::qt::widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<QToolButton> m_Button;
};

#endif  // REPOSITORYMANAGERCOMPOSEDBUTTON_HPP
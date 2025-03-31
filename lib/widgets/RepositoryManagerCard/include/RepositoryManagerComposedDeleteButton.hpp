#ifndef REPOSITORYMANAGERCOMPOSEDDELETEBUTTON_HPP
#define REPOSITORYMANAGERCOMPOSEDDELETEBUTTON_HPP

#include <QPointer>
#include <QPushButton>

#include "Icon.hpp"
#include "RepositoryManagerComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class RepositoryManagerComposedDeleteButton final : public RepositoryManagerComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryManagerComposedDeleteButton)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit RepositoryManagerComposedDeleteButton(QWidget *parent = nullptr);
    ~RepositoryManagerComposedDeleteButton() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return RepositoryManagerComposingWidgets::Item(static_cast<int>(status)); }

    void UpdateColors() override;

    void SetToolTip(Status type, const QString &message = "");
    void SetDisabled(Status type, bool disable = false);
    void SetButtonIcon(const Icon &icon);
    void SetButtonText(const QString &text);

  signals:
    void si_ButtonClicked(bool checked = false);

  public slots:
    void SetLoading();
    void SetButton();
    void Set(Status status);

  private:
    QPointer<xaprier::Qt::Widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<QPushButton> m_Button;
};

#endif  // REPOSITORYMANAGERCOMPOSEDDELETEBUTTON_HPP
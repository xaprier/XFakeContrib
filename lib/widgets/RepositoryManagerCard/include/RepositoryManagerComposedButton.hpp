#ifndef REPOSITORYMANAGERCOMPOSEDBUTTON_HPP
#define REPOSITORYMANAGERCOMPOSEDBUTTON_HPP

#include <qpushbutton.h>

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
    void SetButtonIcon(const QIcon &icon);
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

#endif  // REPOSITORYMANAGERCOMPOSEDBUTTON_HPP
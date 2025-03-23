#ifndef USERMANAGERCOMPOSEDVALIDATEBUTTON_HPP
#define USERMANAGERCOMPOSEDVALIDATEBUTTON_HPP

#include <QPointer>
#include <QToolButton>

#include "UserManagerComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class UserManagerComposedValidateButton final : public UserManagerComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UserManagerComposedValidateButton)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit UserManagerComposedValidateButton(QWidget *parent = nullptr);
    ~UserManagerComposedValidateButton() final = default;

    [[nodiscard]] inline QWidget *Item(Status status) const noexcept { return UserManagerComposingWidgets::Item(static_cast<int>(status)); }

    void SetDisabled(Status type, bool disable = false);

  signals:
    void si_ButtonClicked(bool checked = false);

  public slots:
    void SetLoading();
    void SetButton();
    void Set(Status status);

  private:
    QPointer<xaprier::Qt::Widgets::XQCircularLoadingIndicator> m_Indicator;
    QPointer<QToolButton> m_Button;
};

#endif  // USERMANAGERCOMPOSEDVALIDATEBUTTON_HPP
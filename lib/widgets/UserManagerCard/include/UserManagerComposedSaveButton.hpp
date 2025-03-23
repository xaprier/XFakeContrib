#ifndef USERMANAGERCARDCOMPOSEDSAVEBUTTON_HPP
#define USERMANAGERCARDCOMPOSEDSAVEBUTTON_HPP

#include <QPointer>
#include <QPushButton>

#include "UserManagerComposingWidgets.hpp"
#include "XQCircularLoadingIndicator.hpp"

class UserManagerComposedSaveButton final : public UserManagerComposingWidgets {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(UserManagerComposedSaveButton)
  public:
    enum class Status {
        BUTTON = 0,
        LOADING
    };

    explicit UserManagerComposedSaveButton(QWidget *parent = nullptr);
    ~UserManagerComposedSaveButton() final = default;

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
    QPointer<QPushButton> m_Button;
};

#endif  // USERMANAGERCARDCOMPOSEDSAVEBUTTON_HPP
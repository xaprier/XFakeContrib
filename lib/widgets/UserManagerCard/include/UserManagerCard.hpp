#ifndef USERMANAGERCARD_HPP
#define USERMANAGERCARD_HPP

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

#include "Icon.hpp"

class UserManager;
class UserManagerComposedSaveButton;
class UserManagerComposedValidateButton;
class GitHubAuthChecker;

namespace xaprier::Qt::Widgets {
class PasswordLineEdit;
}

class UserManagerCard : public QWidget {
    Q_OBJECT
  public:
    explicit UserManagerCard(QWidget* parent = nullptr);
    ~UserManagerCard() override;

    Icon GetIcon() const { return Icon(":/icons/user_manager.svg"); }
    QString GetName() const { return QObject::tr("User Manager"); }

    UserManager& GetManager() const { return m_UserManager; }

  signals:
    void si_UserUpdated();

  protected slots:
    void sl_ValidateUser(bool checked);
    void sl_AuthCheckCompleted(bool isValid, const QString& message);

  protected:
    void _SetupUI();
    void _LoadUser();

  private:
    UserManager& m_UserManager;
    xaprier::Qt::Widgets::PasswordLineEdit* m_TokenLineEdit;
    QLineEdit* m_UsernameLineEdit;
    UserManagerComposedValidateButton* m_ValidateButton;
    GitHubAuthChecker* m_AuthChecker;
};

#endif  // USERMANAGERCARD_HPP
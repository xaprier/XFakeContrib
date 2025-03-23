#include "UserManagerCard.hpp"

#include <qboxlayout.h>
#include <qmessagebox.h>

#include "GitHubAuthChecker.hpp"
#include "PasswordLineEdit.hpp"
#include "UserManager.hpp"
#include "UserManagerComposedSaveButton.hpp"
#include "UserManagerComposedValidateButton.hpp"

UserManagerCard::UserManagerCard(QWidget* parent) : m_UserManager(UserManager::Instance()), m_AuthChecker(new GitHubAuthChecker(this)), QWidget(parent) {
    this->_SetupUI();
    this->_LoadUser();

    connect(m_SaveButton, &UserManagerComposedSaveButton::si_ButtonClicked, this, &UserManagerCard::sl_ValidateUser);
    connect(m_ValidateButton, &UserManagerComposedValidateButton::si_ButtonClicked, this, &UserManagerCard::sl_ValidateUser);
    connect(m_AuthChecker, &GitHubAuthChecker::si_AuthCheckResult, this, &UserManagerCard::sl_AuthCheckCompleted);
}

UserManagerCard::~UserManagerCard() {
    delete m_TokenLineEdit;
    delete m_UsernameLineEdit;
    delete m_ValidateButton;
    delete m_SaveButton;
}

void UserManagerCard::_SetupUI() {
    QIcon showIcon = QIcon(":/icons/icons/show.png");
    QIcon hideIcon = QIcon(":/icons/icons/hide.png");
    QIcon checkIcon = QIcon(":/icons/icons/checked.png");

    // todo: show warning if icons not loaded

    m_TokenLineEdit = new xaprier::Qt::Widgets::PasswordLineEdit(false, xaprier::Qt::Widgets::PasswordLineEdit::SwitchType::Toggle, hideIcon, showIcon, this);
    m_UsernameLineEdit = new QLineEdit(this);
    m_ValidateButton = new UserManagerComposedValidateButton(this);
    m_SaveButton = new UserManagerComposedSaveButton(this);

    m_UsernameLineEdit->setPlaceholderText(QObject::tr("Username"));
    m_TokenLineEdit->setPlaceholderText(QObject::tr("Token"));

    m_TokenLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_UsernameLineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(m_UsernameLineEdit, 0, 0, 1, 3);
    gridLayout->addWidget(m_TokenLineEdit, 1, 0, 1, 3);
    gridLayout->addWidget(m_ValidateButton, 0, 3, 2, 1);
    gridLayout->addWidget(m_SaveButton, 2, 3, 1, 1);

    this->setLayout(gridLayout);
}

void UserManagerCard::_LoadUser() {
    this->m_UsernameLineEdit->setText(this->m_UserManager.GetUsername());
    this->m_TokenLineEdit->setText(this->m_UserManager.GetToken());
}

void UserManagerCard::sl_ValidateUser(bool checked) {
    this->m_UserManager.SetUsername(this->m_UsernameLineEdit->text());
    this->m_UserManager.SetToken(this->m_TokenLineEdit->text());

    this->m_ValidateButton->SetLoading();
    this->m_SaveButton->SetLoading();

    this->m_AuthChecker->CheckAuthKey(this->m_UserManager.GetToken());

    this->_LoadUser();
}

void UserManagerCard::sl_AuthCheckCompleted(bool isValid, const QString& message) {
    if (isValid) {
        QString validMsg = QObject::tr("Credentials are valid. Do you want to save them?");
        auto msg = QMessageBox(QMessageBox::Icon::Information, QObject::tr("Validation"), validMsg, QMessageBox::StandardButton::Yes | QMessageBox::StandardButton::No);
        auto result = msg.exec();

        if (result == QMessageBox::StandardButton::Yes) {
            this->m_UserManager.SaveCredentials();
        }
    } else {
        QString invalidMsg = QObject::tr("Credentials are invalid. Please check your username and token\n\n%1").arg(message);
        auto msg = QMessageBox(QMessageBox::Icon::Critical, QObject::tr("Validation"), invalidMsg, QMessageBox::StandardButton::Ok);
        msg.exec();
    }

    this->m_ValidateButton->SetButton();
    this->m_SaveButton->SetButton();
}
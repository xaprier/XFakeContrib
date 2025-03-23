#include "UserManagerComposedSaveButton.hpp"

#include <QPushButton>

using namespace xaprier::Qt::Widgets;

UserManagerComposedSaveButton::UserManagerComposedSaveButton(QWidget *parent) : UserManagerComposingWidgets({}, parent), m_Button(new QPushButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    m_Button->setText(QObject::tr("Save"));
    m_Button->setToolTip(QObject::tr("Save changes"));
    m_Button->setIcon(QIcon(":/icons/icons/push.png"));

    m_Indicator->setToolTip(QObject::tr("Saving changes... Please wait."));
    m_Indicator->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});

    connect(m_Button, &QPushButton::clicked, this, &UserManagerComposedSaveButton::si_ButtonClicked);
}

void UserManagerComposedSaveButton::SetDisabled(Status type, bool disable) {
    switch (type) {
        case Status::BUTTON:
            this->m_Button->setDisabled(disable);
            break;
        case Status::LOADING:
            this->m_Indicator->setDisabled(disable);
            break;
        default:
            break;
    }
}

void UserManagerComposedSaveButton::SetLoading() {
    this->Set(Status::LOADING);
}

void UserManagerComposedSaveButton::SetButton() {
    this->Set(Status::BUTTON);
}

void UserManagerComposedSaveButton::Set(Status status) {
    UserManagerComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

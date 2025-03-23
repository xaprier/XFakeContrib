#include "UserManagerComposedValidateButton.hpp"

#include <qsizepolicy.h>

using namespace xaprier::Qt::Widgets;

UserManagerComposedValidateButton::UserManagerComposedValidateButton(QWidget *parent) : UserManagerComposingWidgets({}, parent), m_Button(new QToolButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    m_Button->setToolTip(QObject::tr("Validate Token"));
    m_Button->setIcon(QIcon(":/icons/icons/checked.png"));
    m_Button->setMinimumSize(50, 50);

    m_Indicator->setToolTip(QObject::tr("Validating changes... Please wait."));
    m_Indicator->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    m_Indicator->setMaximumSize(m_Button->width(), m_Button->height());

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});

    connect(m_Button, &QToolButton::clicked, this, &UserManagerComposedValidateButton::si_ButtonClicked);
}

void UserManagerComposedValidateButton::SetDisabled(Status type, bool disable) {
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

void UserManagerComposedValidateButton::SetLoading() {
    this->Set(Status::LOADING);
}

void UserManagerComposedValidateButton::SetButton() {
    this->Set(Status::BUTTON);
}

void UserManagerComposedValidateButton::Set(Status status) {
    UserManagerComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

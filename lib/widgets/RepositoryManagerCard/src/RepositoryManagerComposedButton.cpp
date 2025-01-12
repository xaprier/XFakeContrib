#include "RepositoryManagerComposedButton.hpp"

using namespace xaprier::qt::widgets;

RepositoryManagerComposedButton::RepositoryManagerComposedButton(QWidget *parent) : RepositoryManagerComposingWidgets({}, parent), m_Button(new QToolButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});

    connect(m_Button, &QToolButton::clicked, this, &RepositoryManagerComposedButton::si_ButtonClicked);
}

void RepositoryManagerComposedButton::SetToolTip(Status type, const QString &message) {
    switch (type) {
        case Status::BUTTON:
            this->m_Button->setToolTip(message);
            break;
        case Status::LOADING:
            this->m_Indicator->setToolTip(message);
            break;
        default:
            break;
    }
}

void RepositoryManagerComposedButton::SetDisabled(Status type, bool disable) {
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

void RepositoryManagerComposedButton::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryManagerComposedButton::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryManagerComposedButton::Set(Status status) {
    RepositoryManagerComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

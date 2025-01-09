#include "RepositoryCardPush.hpp"

using namespace xaprier::qt::widgets;

RepositoryCardPush::RepositoryCardPush(QWidget* parent) : RepositoryComposingWidgets({}, parent), m_Button(new QPushButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);
    m_Button->setToolTip(QObject::tr("Push all latest changes to remote"));
    m_Button->setText(QObject::tr("Push All"));

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});
}

void RepositoryCardPush::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryCardPush::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryCardPush::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

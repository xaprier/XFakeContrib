#include "RepositoryTableItemLog.hpp"

#include "XQCircularLoadingIndicator.hpp"

using namespace xaprier::qt::widgets;

RepositoryTableItemLog::RepositoryTableItemLog(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_Button(new QToolButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});
}

void RepositoryTableItemLog::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryTableItemLog::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryTableItemLog::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        m_Indicator->Start();
    else
        m_Indicator->Stop();
}

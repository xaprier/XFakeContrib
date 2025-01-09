#include "RepositoryTableItemStatus.hpp"

using namespace xaprier::qt::widgets;

RepositoryTableItemStatus::RepositoryTableItemStatus(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_CheckBox(new RepositoryEnableCheckBox), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    // Setting-Up Layout
    this->SetWidgets({m_CheckBox, m_Indicator});
}

void RepositoryTableItemStatus::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryTableItemStatus::SetCheckBox() {
    this->Set(Status::CHECKBOX);
}

void RepositoryTableItemStatus::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

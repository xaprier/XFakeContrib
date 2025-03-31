#include "RepositoryTableItemStatus.hpp"

#include "StyleManager.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryTableItemStatus::RepositoryTableItemStatus(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_CheckBox(new RepositoryEnableCheckBox), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    this->UpdateColors();

    // Setting-Up Layout
    this->SetWidgets({m_CheckBox, m_Indicator});
}

void RepositoryTableItemStatus::UpdateColors() {
    QString colorHex = StyleManager::GetCurrentThemeColors()["icon"];
    m_Indicator->SetProgressColor(colorHex);
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

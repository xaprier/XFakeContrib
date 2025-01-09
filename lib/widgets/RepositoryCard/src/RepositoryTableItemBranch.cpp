#include "RepositoryTableItemBranch.hpp"

RepositoryTableItemBranch::RepositoryTableItemBranch(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_ComboBox(new QComboBox) {
    // Setting-Up Layout
    this->SetWidgets({m_ComboBox});
}

void RepositoryTableItemBranch::SetComboBox() {
    this->Set(Status::COMBOBOX);
}

void RepositoryTableItemBranch::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));
}

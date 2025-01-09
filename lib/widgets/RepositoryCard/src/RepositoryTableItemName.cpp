#include "RepositoryTableItemName.hpp"

RepositoryTableItemName::RepositoryTableItemName(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_Label(new QLabel) {
    // Setting-Up Layout
    this->SetWidgets({m_Label});
}

void RepositoryTableItemName::SetLabel() {
    this->Set(Status::LABEL);
}

void RepositoryTableItemName::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));
}

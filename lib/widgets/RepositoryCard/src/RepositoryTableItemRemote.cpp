#include "RepositoryTableItemRemote.hpp"

RepositoryTableItemRemote::RepositoryTableItemRemote(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_Label(new QLabel) {
    // Setting-Up Layout
    this->SetWidgets({m_Label});
}

void RepositoryTableItemRemote::SetLabel() {
    this->Set(Status::LABEL);
}

void RepositoryTableItemRemote::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));
}

#include "RepositoryTableItemCommitFile.hpp"

RepositoryTableItemCommitFile::RepositoryTableItemCommitFile(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_Button(new QToolButton()) {
    // Setting-Up Layout
    this->SetWidgets({m_Button});
}

void RepositoryTableItemCommitFile::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryTableItemCommitFile::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));
}

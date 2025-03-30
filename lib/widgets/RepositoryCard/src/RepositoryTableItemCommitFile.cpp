#include "RepositoryTableItemCommitFile.hpp"

#include "Icon.hpp"

RepositoryTableItemCommitFile::RepositoryTableItemCommitFile(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_Button(new QToolButton()) {
    m_Button->setIcon(Icon(":/icons/file.svg"));
    m_Button->setToolTip(QObject::tr("Select commit file"));

    m_Button->setStyleSheet(R"(
        QToolButton {
            border: 1px solid red;
        }
        QToolButton:hover {
            border: 1px solid darkred;
        }
    )");

    // Setting-Up Layout
    this->SetWidgets({m_Button});
}

void RepositoryTableItemCommitFile::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryTableItemCommitFile::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));
}

void RepositoryTableItemCommitFile::SetValidFileSelected(bool selected) {
    if (selected) {
        m_Button->setStyleSheet(R"(
            QToolButton {
                border: 1px solid green;
            }
            QToolButton:hover {
                border: 1px solid darkgreen;
            }
        )");
    } else {
        m_Button->setStyleSheet(R"(
            QToolButton {
                border: 1px solid red;
            }
            QToolButton:hover {
                border: 1px solid darkred;
            }
        )");
    }
}

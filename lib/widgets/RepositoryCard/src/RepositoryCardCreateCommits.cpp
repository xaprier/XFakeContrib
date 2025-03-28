#include "RepositoryCardCreateCommits.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryCardCreateCommits::RepositoryCardCreateCommits(QWidget* parent) : RepositoryComposingWidgets({}, parent), m_Button(new QPushButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);
    m_Indicator->SetProgressColor("#e67300");

    m_Button->setToolTip(QObject::tr("Create commits in selected repositories"));
    m_Button->setText(QObject::tr("Create Commits"));

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});
}

void RepositoryCardCreateCommits::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryCardCreateCommits::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryCardCreateCommits::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

#include "RepositoryCardCreateCommits.hpp"

#include "Icon.hpp"
#include "StyleManager.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryCardCreateCommits::RepositoryCardCreateCommits(QWidget* parent) : RepositoryComposingWidgets({}, parent), m_Button(new QPushButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    m_Button->setToolTip(QObject::tr("Create commits in selected repositories"));
    m_Button->setText(QObject::tr("Create Commits"));

    this->UpdateColors();

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});
}

void RepositoryCardCreateCommits::UpdateColors() {
    QString colorHex = StyleManager::GetCurrentThemeColors()["icon"];
    m_Indicator->SetProgressColor(colorHex);
    m_Button->setIcon(Icon(":/icons/createcommit.svg"));  // this will reload the icon with color
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

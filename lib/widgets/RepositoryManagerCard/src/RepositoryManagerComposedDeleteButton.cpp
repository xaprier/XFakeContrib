#include "RepositoryManagerComposedDeleteButton.hpp"

#include "Icon.hpp"
#include "StyleManager.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryManagerComposedDeleteButton::RepositoryManagerComposedDeleteButton(QWidget *parent) : RepositoryManagerComposingWidgets({}, parent), m_Button(new QPushButton()), m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_Button->setText(QObject::tr("Delete"));

    this->UpdateColors();

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});

    connect(m_Button, &QPushButton::clicked, this, &RepositoryManagerComposedDeleteButton::si_ButtonClicked);
}

void RepositoryManagerComposedDeleteButton::UpdateColors() {
    QString colorHex = StyleManager::GetCurrentThemeColors()["icon"];
    m_Indicator->SetProgressColor(colorHex);
    m_Button->setIcon(Icon(":/icons/delete.svg"));
}

void RepositoryManagerComposedDeleteButton::SetToolTip(Status type, const QString &message) {
    switch (type) {
        case Status::BUTTON:
            this->m_Button->setToolTip(message);
            break;
        case Status::LOADING:
            this->m_Indicator->setToolTip(message);
            break;
        default:
            break;
    }
}

void RepositoryManagerComposedDeleteButton::SetDisabled(Status type, bool disable) {
    switch (type) {
        case Status::BUTTON:
            this->m_Button->setDisabled(disable);
            break;
        case Status::LOADING:
            this->m_Indicator->setDisabled(disable);
            break;
        default:
            break;
    }
}

void RepositoryManagerComposedDeleteButton::SetButtonIcon(const Icon &icon) {
    this->m_Button->setIcon(icon);
}

void RepositoryManagerComposedDeleteButton::SetButtonText(const QString &text) {
    this->m_Button->setText(text);
}

void RepositoryManagerComposedDeleteButton::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryManagerComposedDeleteButton::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryManagerComposedDeleteButton::Set(Status status) {
    RepositoryManagerComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

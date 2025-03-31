#include "RepositoryTableItemPush.hpp"

#include "Icon.hpp"
#include "StyleManager.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryTableItemPush::RepositoryTableItemPush(QWidget *parent) : RepositoryComposingWidgets({}, parent),
                                                                    m_Button(new QToolButton()),
                                                                    m_Indicator(new XQCircularLoadingIndicator) {
    // Setting-Up Widgets
    m_Indicator->SetSquare(true);

    m_Button->setToolTip(QObject::tr("Push latest changes to remote"));
    m_Button->setText(QObject::tr("Push"));

    this->UpdateColors();

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});
}

void RepositoryTableItemPush::UpdateColors() {
    QString colorHex = StyleManager::GetCurrentThemeColors()["icon"];
    m_Indicator->SetProgressColor(colorHex);
    m_Button->setIcon(Icon(":/icons/push.svg"));  // this will reload the icon with color
}

void RepositoryTableItemPush::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryTableItemPush::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryTableItemPush::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        this->m_Indicator->Start();
    else
        this->m_Indicator->Stop();
}

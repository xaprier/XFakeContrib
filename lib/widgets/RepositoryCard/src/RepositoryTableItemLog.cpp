#include "RepositoryTableItemLog.hpp"

#include "Icon.hpp"
#include "StyleManager.hpp"
#include "XQCircularLoadingIndicator.hpp"

using namespace xaprier::Qt::Widgets;

RepositoryTableItemLog::RepositoryTableItemLog(QWidget *parent) : RepositoryComposingWidgets({}, parent), m_Button(new QToolButton()), m_Indicator(new XQCircularLoadingIndicator) {
    QString colorHex = StyleManager::GetCurrentThemeColors()["icon"];

    // Setting-Up Widgets
    m_Indicator->SetSquare(true);
    m_Indicator->SetProgressColor(colorHex);

    m_Button->setIcon(Icon(":/icons/log.svg"));
    m_Button->setToolTip(QObject::tr("Show logs"));
    m_Button->setText(QObject::tr("Logs"));

    // Setting-Up Layout
    this->SetWidgets({m_Button, m_Indicator});
}

void RepositoryTableItemLog::SetButton() {
    this->Set(Status::BUTTON);
}

void RepositoryTableItemLog::SetLoading() {
    this->Set(Status::LOADING);
}

void RepositoryTableItemLog::Set(Status status) {
    RepositoryComposingWidgets::Set(static_cast<int>(status));

    if (status == Status::LOADING)
        m_Indicator->Start();
    else
        m_Indicator->Stop();
}

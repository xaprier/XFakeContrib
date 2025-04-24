#include "RepositoryCard.hpp"

#include <qmessagebox.h>

#include <QGridLayout>

#include "../design/ui_RepositoryCardUI.h"
#include "RepositoryTableView.hpp"

RepositoryCard::RepositoryCard(QWidget *parent) : Card(parent), m_Ui(new Ui::RepositoryCardUI), m_Settings(Settings::Instance()) {
    m_Ui->setupUi(this);

    QGridLayout *groupBoxLayout = new QGridLayout(this->m_Ui->groupBoxRepoTable);  // parent is set, no need to delete it. // NOLINT
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    groupBoxLayout->setContentsMargins(0, 0, 0, 0);
#else
    groupBoxLayout->setMargin(0);
#endif
    m_Repositories = new RepositoryTableView(this);  // parent is set, no need to delete it. // NOLINT
    groupBoxLayout->addWidget(m_Repositories);
    this->m_Ui->groupBoxRepoTable->setLayout(groupBoxLayout);

    m_Connections = new RepositoryCardConnections(m_Repositories->GetItems(), m_Ui, m_Repositories, this);  // NOLINT
}

RepositoryCard::~RepositoryCard() {
    delete m_Connections;
    delete m_Ui;
}

void RepositoryCard::UpdateIcons() {
    for (auto *item : m_Repositories->GetItems()) {
        item->UpdateColors();
    }

    m_Ui->pushPB->UpdateColors();
    m_Ui->createCommitsPB->UpdateColors();
}

void RepositoryCard::SetEndDate(const QDate &date) {
    QDate today = QDate::currentDate();
    QDate startDate = this->m_Ui->startDateDE->date();

    if (date < startDate) {
        QMessageBox::warning(this, tr("Invalid Date"), tr("End date cannot be before start date."), QMessageBox::Ok);
        return;
    }

    if (date.isValid() && date != this->m_Ui->endDateDE->date() && date <= today) {
        this->m_Ui->endDateDE->setDate(date);
    }
}

void RepositoryCard::SetStartDate(const QDate &date) {
    QDate today = QDate::currentDate();
    QDate endDate = this->m_Ui->endDateDE->date();

    if (date > endDate) {
        QMessageBox::warning(this, tr("Invalid Date"), tr("Start date cannot be after end date."), QMessageBox::Ok);
        return;
    }

    if (date.isValid() && date != this->m_Ui->startDateDE->date() && date <= today) {
        this->m_Ui->startDateDE->setDate(date);
    }
}

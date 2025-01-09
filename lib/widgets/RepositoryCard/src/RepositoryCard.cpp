#include "RepositoryCard.hpp"

#include <QGridLayout>

#include "../design/ui_RepositoryCardUI.h"
#include "RepositoryTableView.hpp"

RepositoryCard::RepositoryCard(QWidget *parent) : QWidget(parent), m_Ui(new Ui::RepositoryCardUI), m_Settings(Settings::Instance()) {
    m_Ui->setupUi(this);

    QGridLayout *groupBoxLayout = new QGridLayout(this->m_Ui->groupBoxRepoTable);  // parent is set, no need to delete it. // NOLINT
    groupBoxLayout->setMargin(0);
    m_Repositories = new RepositoryTableView(this->m_Ui->groupBoxRepoTable);  // parent is set, no need to delete it. // NOLINT
    groupBoxLayout->addWidget(m_Repositories);
    this->m_Ui->groupBoxRepoTable->setLayout(groupBoxLayout);
    // todo: update items in repositorycardconnection when new items added.
    m_Connections = new RepositoryCardConnections(m_Repositories->GetItems(), m_Settings, m_Ui, this);  // NOLINT
}

RepositoryCard::~RepositoryCard() {
    delete m_Ui;
    delete m_Connections;
}

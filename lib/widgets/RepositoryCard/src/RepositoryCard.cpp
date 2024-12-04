#include "RepositoryCard.hpp"

#include <algorithm>

#include "../design/ui_RepositoryCardUI.h"
#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"

RepositoryCard::RepositoryCard(QWidget *parent) : QWidget(parent), m_Ui(new Ui::RepositoryCardUI), m_Repository(new GitRepository), m_Handler(new GitChangeHandler), m_Settings(Settings::Instance()) {
    m_Ui->setupUi(this);
    m_Connections = new RepositoryCardConnections(m_Settings, m_Handler, m_Repository, m_Ui);
    this->_LoadRepositories();
}

RepositoryCard::~RepositoryCard() {
    delete m_Ui;
    delete m_Connections;
}

void RepositoryCard::_LoadRepositories() {  // todo: when new repositories added to config, we should call this function again.
    auto repositories = m_Settings->GetRepositories();

    // if no repositories found, disable all buttons and comboBoxes with giving information to user
    if (repositories.isEmpty()) {
        m_Ui->repositoriesCombo->addItem(QObject::tr("No Repositories Found"));
        m_Ui->repositoriesCombo->setDisabled(true);
        m_Ui->branchCombo->addItem(QObject::tr("Please Add Repository from Repository Manager"));
        m_Ui->branchCombo->setDisabled(true);
        m_Ui->logPB->setDisabled(true);
        m_Ui->pushPB->setDisabled(true);
        m_Ui->createCommitsPB->setDisabled(true);
        m_Ui->commitFilePB->setDisabled(true);
        return;
    }

    m_Ui->repositoriesCombo->blockSignals(true);
    m_Ui->repositoriesCombo->clear();
    for (const auto &absolutePath : repositories) {
        // last path separator
        auto index = absolutePath.lastIndexOf('/');
        auto directoryName = absolutePath.mid(index + 1);
        // add directoryName to comboBox with setting toolTip to absolutePath
        m_Ui->repositoriesCombo->addItem(directoryName);
        m_Ui->repositoriesCombo->setItemData(m_Ui->repositoriesCombo->count() - 1, absolutePath, Qt::ToolTipRole);
    }
    m_Ui->repositoriesCombo->blockSignals(false);

    m_Repository->SetRepositoryPath(m_Ui->repositoriesCombo->currentData(Qt::ToolTipRole).toString());

    // emit signal to load branches and other updates
    emit m_Ui->repositoriesCombo->currentIndexChanged(m_Ui->repositoriesCombo->currentIndex());

    // update remote url
    auto remote = m_Repository->Remote({"get-url", m_Repository->Remote({}).split('\n').first()}).trimmed();
    m_Ui->remoteUrlLE->setText(remote);
}

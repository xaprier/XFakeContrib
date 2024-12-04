#include "RepositoryCardConnections.hpp"

#include <QFileDialog>

#include "../design/ui_RepositoryCardUI.h"
#include "LogDialog.hpp"

RepositoryCardConnections::RepositoryCardConnections(Settings *settings, GitChangeHandler *changeHandler, GitRepository *repository, Ui::RepositoryCardUI *ui, QObject *base) : QObject(base), m_Ui(ui), m_Handler(changeHandler), m_Repository(repository), m_Settings(settings) {
    this->_SetupConnections();
}

void RepositoryCardConnections::_SetupConnections() {
    connect(m_Ui->logPB, &QPushButton::clicked, this, &RepositoryCardConnections::sl_LogButtonClicked);
    connect(m_Ui->createCommitsPB, &QPushButton::clicked, this, &RepositoryCardConnections::sl_CreateCommitsButtonClicked);
    connect(m_Ui->pushPB, &QPushButton::clicked, this, &RepositoryCardConnections::sl_PushButtonClicked);
    connect(m_Ui->commitFilePB, &QPushButton::clicked, this, &RepositoryCardConnections::sl_SelectCommitFileClicked);
    connect(m_Ui->repositoriesCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RepositoryCardConnections::sl_RepositoryIndexChanged);
    connect(m_Ui->branchCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RepositoryCardConnections::sl_BranchIndexChanged);
    connect(m_Ui->commitCountCB, &QCheckBox::stateChanged, this, &RepositoryCardConnections::sl_CommitCountCBStateChanged);
    connect(m_Ui->dateCB, &QCheckBox::stateChanged, this, &RepositoryCardConnections::sl_DateCBStateChanged);
    connect(m_Ui->commitMessageCB, &QCheckBox::stateChanged, this, &RepositoryCardConnections::sl_CommitMessageCBStateChanged);
    connect(m_Ui->commitContentCB, &QCheckBox::stateChanged, this, &RepositoryCardConnections::sl_CommitContentCBStateChanged);
}

void RepositoryCardConnections::sl_LogButtonClicked(bool checked) {
    auto log = m_Repository->Log();
    auto directory = m_Ui->repositoriesCombo->currentText();
    LogDialog dialog(directory + " Log", log, m_Ui->logPB);
    dialog.exec();
}

void RepositoryCardConnections::sl_CreateCommitsButtonClicked(bool checked) {
}

void RepositoryCardConnections::sl_PushButtonClicked(bool checked) {
}

void RepositoryCardConnections::sl_SelectCommitFileClicked(bool checked) {
    auto dir = m_Ui->repositoriesCombo->currentData(Qt::ToolTipRole).toString();
    auto file = QFileDialog::getOpenFileName(m_Ui->commitFilePB, QObject::tr("Select Commit File"), dir, QObject::tr("Text Files (*.txt);All Files (*)"));
    if (file.isEmpty())
        return;

    // check file is writeable
    if (!QFile::exists(file) || !QFile::permissions(file).testFlag(QFileDevice::WriteUser)) {
        m_Ui->commitFilePB->setText(QObject::tr("Selected File: ") + QObject::tr("File is not writeable"));
        return;
    }

    // get file name only
    auto fileName = file.split('/').last();
    m_Ui->commitFilePB->setText(QObject::tr("Selected File: ") + fileName);
    this->m_CommitFile = file;

    // enable create commit button for file selected
    m_Ui->createCommitsPB->setDisabled(false);
    m_Ui->createCommitsPB->setToolTip("");
}

void RepositoryCardConnections::sl_RepositoryIndexChanged(int index) {
    // set repository path...
    m_Repository->SetRepositoryPath(m_Ui->repositoriesCombo->currentData(Qt::ToolTipRole).toString());
    // ...and load branches again because of repository change
    this->_LoadBranches();
    // update remote url
    auto remote = m_Repository->Remote({"get-url", m_Repository->Remote({}).split('\n').first()}).trimmed();
    m_Ui->remoteUrlLE->setText(remote);

    // reset commit file
    m_Ui->commitFilePB->setText(QObject::tr("Select Commit File(Not Selected)"));
    this->m_CommitFile.clear();

    // disable create commit button for no file selected
    m_Ui->createCommitsPB->setDisabled(true);
    m_Ui->createCommitsPB->setToolTip(QObject::tr("Select a commit file first"));
}

void RepositoryCardConnections::sl_BranchIndexChanged(int index) {
    // set branch
    auto branch = m_Ui->branchCombo->currentText();
    if (branch.isEmpty()) return;

    if (branch.startsWith("* ")) return;  // current branch

    m_Repository->Checkout({"-f", m_Ui->branchCombo->currentText()});
    m_Ui->branchCombo->blockSignals(true);
    this->_LoadBranches();  // load branches because of branch change
    m_Ui->branchCombo->blockSignals(false);
}

void RepositoryCardConnections::sl_CommitCountCBStateChanged(int state) {
    // disable commit count if checked
    m_Ui->commitCountSP->setDisabled(state == Qt::Checked);
}

void RepositoryCardConnections::sl_DateCBStateChanged(int state) {
    // disable dateedits if today is checked
    bool disable = state == Qt::Checked;
    m_Ui->startDateDE->setDisabled(disable);
    m_Ui->endDateDE->setDisabled(disable);
}

void RepositoryCardConnections::sl_CommitMessageCBStateChanged(int state) {
    // disable static commit message if checked
    bool disable = state == Qt::Checked;
    m_Ui->commitMessageLE->setDisabled(disable);
}

void RepositoryCardConnections::sl_CommitContentCBStateChanged(int state) {
    // disable static commit content if checked
    bool disable = state == Qt::Checked;
    m_Ui->commitContentLE->setDisabled(disable);
}

void RepositoryCardConnections::_LoadBranches() {
    auto branches = m_Repository->Branch({"-a"}).split('\n');
    // we should delete first two characters if they are whitespaces because of indentation
    for (auto &branch : branches)
        if (branch.startsWith("  "))
            branch.remove(0, 2);

    // remove empty branches and branches that start with "remote"
    branches.erase(std::remove_if(branches.begin(), branches.end(), [](const QString &branch) { return branch.isEmpty() || branch.startsWith("remote"); }), branches.end());
    m_Ui->branchCombo->clear();
    for (const auto &branch : branches) {
        m_Ui->branchCombo->addItem(branch);
    }

    // set current branch in comboBox
    this->m_Ui->branchCombo->blockSignals(true);
    auto currentBranch = this->m_Ui->branchCombo->findText("* " + m_Repository->Branch({"--show-current"}).trimmed());
    if (currentBranch != -1)
        this->m_Ui->branchCombo->setCurrentIndex(currentBranch);
    this->m_Ui->branchCombo->blockSignals(false);
}
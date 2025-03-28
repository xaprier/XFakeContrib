#include "RepositoryTableItemConnections.hpp"

#include <qnamespace.h>

#include <QFileDialog>
#include <QFuture>
#include <QFutureWatcher>
#include <QMessageBox>
#include <QtConcurrent/QtConcurrent>

#include "GitPusher.hpp"
#include "GitRepository.hpp"
#include "LogDialog.hpp"
#include "RepositoryEnableCheckBox.hpp"
#include "RepositoryTableItem.hpp"
#include "RepositoryTableItemBranch.hpp"
#include "RepositoryTableItemCommitFile.hpp"
#include "RepositoryTableItemLog.hpp"
#include "RepositoryTableItemName.hpp"
#include "RepositoryTableItemPush.hpp"
#include "RepositoryTableItemRemote.hpp"
#include "RepositoryTableItemStatus.hpp"

RepositoryTableItemConnections::RepositoryTableItemConnections(RepositoryTableItem *item, QObject *parent) : QObject(parent), m_Item(item) {
    this->_SetupConnections();
    this->_LoadBranches();
}

void RepositoryTableItemConnections::_SetupConnections() {
    {
        auto checkBox = qobject_cast<RepositoryEnableCheckBox *>(m_Item->m_StatusItem->Item(RepositoryTableItemStatus::Status::CHECKBOX));
        if (!checkBox)
            qWarning() << "Failed to cast from RepositoryTableItemStatus to RepositoryEnableCheckBox.";
        else
            connect(checkBox, &RepositoryEnableCheckBox::stateChanged, this, &RepositoryTableItemConnections::sl_RepositoryStateChanged);
    }
    {
        auto logButton = qobject_cast<QToolButton *>(m_Item->m_LogItem->Item(RepositoryTableItemLog::Status::BUTTON));
        if (!logButton)
            qWarning() << "Failed to cast from RepositoryTableItemLog to QToolButton.";
        else
            connect(logButton, &QToolButton::clicked, this, &RepositoryTableItemConnections::sl_LogButtonClicked);
    }
    {
        auto pushButton = qobject_cast<QToolButton *>(m_Item->m_PushItem->Item(RepositoryTableItemPush::Status::BUTTON));
        if (!pushButton)
            qWarning() << "Failed to cast from RepositoryTableItemPush to QToolButton.";
        else
            connect(pushButton, &QToolButton::clicked, this, &RepositoryTableItemConnections::sl_PushButtonClicked);
    }

    {
        auto commitFileButton = qobject_cast<QToolButton *>(m_Item->m_CommitFileButton->Item(RepositoryTableItemCommitFile::Status::BUTTON));
        if (!commitFileButton)
            qWarning() << "Failed to cast from RepositoryTableItemCommitFile to QToolButton.";
        else
            connect(commitFileButton, &QToolButton::clicked, this, &RepositoryTableItemConnections::sl_SelectCommitFileClicked);
    }

    {
        auto branchCombo = qobject_cast<QComboBox *>(m_Item->m_BranchItem->Item(RepositoryTableItemBranch::Status::COMBOBOX));
        if (!branchCombo)
            qWarning() << "Failed to cast from RepositoryTableItemBranch to QComboBox.";
        else
            connect(branchCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RepositoryTableItemConnections::sl_BranchIndexChanged);
    }

    connect(m_Item->GetConnections(), &RepositoryTableItemConnections::si_CreateCommitter, this, &RepositoryTableItemConnections::sl_CreateCommitter);
}

void RepositoryTableItemConnections::_LoadBranches() {
    auto branches = m_Item->m_GitRepository->Branch({"-a"}).split('\n');
    // we should delete first two characters if they are whitespaces because of indentation
    for (auto &branch : branches)
        if (branch.startsWith("  "))
            branch.remove(0, 2);

    // remove empty branches and branches that start with "remote"
    branches.erase(std::remove_if(branches.begin(), branches.end(), [](const QString &branch) { return branch.isEmpty() || branch.startsWith("remote"); }), branches.end());

    auto comboBox = qobject_cast<QComboBox *>(m_Item->m_BranchItem->Item(RepositoryTableItemBranch::Status::COMBOBOX));

    // if guard protection for invalid cast
    if (!comboBox) {
        qWarning() << "Failed to cast from RepositoryTableItemBranch to QComboBox.";
        return;
    }

    comboBox->blockSignals(true);  // Block Signals to prevent sl_BranchIndexChanged to be called when loading branches
    comboBox->clear();
    for (const auto &branch : branches)
        comboBox->addItem(branch);

    // set current branch in comboBox
    auto currentBranch = comboBox->findText("* " + m_Item->m_GitRepository->Branch({"--show-current"}).trimmed());

    if (currentBranch != -1)
        comboBox->setCurrentIndex(currentBranch);

    comboBox->blockSignals(false);  // Unblock Signals
}

void RepositoryTableItemConnections::sl_RepositoryStateChanged(int state) {
    // if (state == Qt::Checked)
    //     emit this->si_ItemSelected(true);
    // else if (state == Qt::Unchecked)
    //     emit this->si_ItemSelected(false);
    //! maybe this is not correct
    emit this->m_Item->GetConnections()->si_StatusChanged(state == Qt::Checked);
}

void RepositoryTableItemConnections::sl_LogButtonClicked(bool checked) {
    m_Item->m_LogItem->SetLoading();

    QFuture<QString> futureForLogFetch = QtConcurrent::run(m_Item->m_GitRepository, &GitRepository::Log, QStringList{});

    if (!m_Watcher.isNull()) delete m_Watcher;
    // Create a QFutureWatcher to monitor the operation
    m_Watcher = new QFutureWatcher<QString>(this);  // NOLINT

    // Connect the finished signal to your slot
    connect(m_Watcher, &QFutureWatcher<QString>::finished, this, &RepositoryTableItemConnections::sl_FetchLogFinished);

    // Set the QFuture to the watcher
    m_Watcher->setFuture(futureForLogFetch);
}

void RepositoryTableItemConnections::sl_PushButtonClicked(bool checked) {
    GitPusher *pusher = new GitPusher(m_Item->GetAbsolutePath());  // NOLINT
    qDebug() << "Pushing " << m_Item->GetAbsolutePath();
    // start loading animation
    auto item = qobject_cast<QLabel *>(m_Item->m_RemoteItem->Item(RepositoryTableItemRemote::Status::LABEL));

    // if guard protection for invalid cast
    if (!item) {
        qWarning() << "Failed to cast from RepositoryTableItemRemote to QLabel.";
        return;
    }

    auto remote = item->text();
    this->m_Item->m_PushItem->Set(RepositoryTableItemPush::Status::LOADING);
    this->m_Item->m_PushItem->setToolTip("Pushing Repository to " + remote);
    m_Pushing = true;
    emit this->si_PushStarted();
    pusher->start();

    // finish loading animation
    connect(pusher, &GitPusher::finished, [pusher, this]() {
        this->m_Item->m_PushItem->Set(RepositoryTableItemPush::Status::BUTTON);
        this->m_Item->m_PushItem->setToolTip("");  // clear tooltip
        m_Pushing = false;
        emit this->si_PushFinished();
        pusher->deleteLater();
    });
}

void RepositoryTableItemConnections::sl_SelectCommitFileClicked(bool checked) {
    auto item = qobject_cast<QLabel *>(m_Item->m_RepoNameItem->Item(RepositoryTableItemName::Status::LABEL));

    // if guard protection for invalid cast
    if (!item) {
        qWarning() << "Failed to cast from RepositoryTableItemName to QLabel.";
        return;
    }

    auto dir = item->toolTip();  // toolTip will include repository path

    if (dir.isEmpty())  // if no repository path found, return
        return;

    // dir validation
    QDir directory(dir);
    if (!directory.exists()) {
        qWarning() << "The directory does not exist:" << dir;
        return;
    }

    auto commitFileButton = qobject_cast<QToolButton *>(m_Item->m_CommitFileButton->Item(RepositoryTableItemCommitFile::Status::BUTTON));

    // if guard protection for invalid cast
    if (!commitFileButton) {
        qWarning() << "Failed to cast from RepositoryTableItemCommitFile to QToolButton.";
        return;
    }

    auto file = QFileDialog::getOpenFileName(commitFileButton, QObject::tr("Select Commit File"), dir, QObject::tr("Text Files (*.txt);All Files (*)"));
    if (file.isEmpty())
        return;

    if (!file.startsWith(dir)) {
        QMessageBox::critical(m_Item->m_CommitFileButton, QObject::tr("Error"), QObject::tr("Selected file is not in the repository directory: %1").arg(file));
        return;
    }

    if (!QFile::permissions(file).testFlag(QFileDevice::WriteUser)) {
        QMessageBox::critical(m_Item->m_CommitFileButton, QObject::tr("Error"), QObject::tr("Cannot write to selected file: %1").arg(file));
        return;
    }

    // if output is not empty, means it is ignored file.
    if (!m_Item->m_GitRepository->CheckIgnore({file}).isEmpty()) {
        QMessageBox::critical(m_Item->m_CommitFileButton, QObject::tr("Error"), QObject::tr("Selected file is ignored file in repository: %1").arg(file));
        return;
    }

    m_Item->m_SelectedFile = file;
    // update button
    commitFileButton->setToolTip("Selected File: " + m_Item->m_SelectedFile.split('/').last());
    m_Item->m_CommitFileButton->SetValidFileSelected(true);
    emit m_Item->GetConnections()->si_FileSelected();
}

void RepositoryTableItemConnections::sl_BranchIndexChanged(int index) {
    auto combo = qobject_cast<QComboBox *>(m_Item->m_BranchItem->Item(RepositoryTableItemBranch::Status::COMBOBOX));

    // if guard protection for invalid cast
    if (!combo) {
        qWarning() << "Failed to cast from RepositoryTableItemBranch to QComboBox.";
        return;
    }

    auto branch = combo->currentText();
    if (branch.isEmpty()) return;

    if (branch.startsWith("* ")) return;  // current branch

    m_Item->m_GitRepository->Checkout({"-f", combo->currentText()});
    this->_LoadBranches();  // load branches because of branch change
}

void RepositoryTableItemConnections::sl_CreateCommitter(const quint32 &commitCount, const QDate &date, const QString &commitMessage, const QString &commitContent) {
    auto repoPath = m_Item->GetAbsolutePath();
    auto file = m_Item->m_SelectedFile;
    auto *committer = new GitCommitter(repoPath, file, commitMessage, commitContent, commitCount, date);
    m_Committers.append(committer);  // todo: this should be invalid, we must use queue for this.
    connect(committer, &GitCommitter::finished, this, &RepositoryTableItemConnections::sl_CommitterFinished);

    // update status
    m_Item->m_StatusItem->Set(RepositoryTableItemStatus::Status::LOADING);
    m_Item->m_StatusItem->setToolTip(QObject::tr("Creating commits for %1 days").arg(m_Committers.size()));

    // start committer
    committer->start();
}

void RepositoryTableItemConnections::sl_CommitterFinished() {
    auto committer = qobject_cast<GitCommitter *>(sender());

    // if guard protection for invalid cast
    if (!committer) {
        qWarning() << "Failed to cast from sender() to GitCommitter.";
        return;
    }

    m_Committers.removeOne(committer);

    // Update status
    if (m_Committers.isEmpty()) {
        m_Item->m_StatusItem->Set(RepositoryTableItemStatus::Status::CHECKBOX);
        m_Item->m_StatusItem->setToolTip("");                             // Clear tool tip
        emit this->m_Item->GetConnections()->si_AllCommittersFinished();  // send signal for giving info to repositorycard
    } else {
        m_Item->m_StatusItem->setToolTip(QObject::tr("Creating commits for %1 days").arg(m_Committers.size()));
        emit this->m_Item->GetConnections()->si_CommitterFinished();  // send signal for giving info to repositorycard
    }

    committer->deleteLater();
}

void RepositoryTableItemConnections::sl_FetchLogFinished() {
    if (m_Watcher.isNull()) {
        qWarning() << "QFutureWatcher is null";
        m_Watcher->deleteLater();
        return;
    }

    QString result = m_Watcher->future().result();

    auto label = qobject_cast<QLabel *>(m_Item->m_RepoNameItem->Item(RepositoryTableItemName::Status::LABEL));

    // if guard protection for invalid cast
    if (!label) {
        qWarning() << "Failed to cast from RepositoryTableItemName to QLabel.";
        m_Watcher->deleteLater();
        return;
    }

    auto logButton = qobject_cast<QToolButton *>(m_Item->m_LogItem->Item(RepositoryTableItemLog::Status::BUTTON));

    // if guard protection for invalid cast
    if (!logButton) {
        qWarning() << "Failed to cast from RepositoryTableItemLog to QToolButton.";
        m_Watcher->deleteLater();
        return;
    }

    m_Item->m_LogItem->SetButton();  // Loaded log, dont show loading indicator

    auto directory = label->text();
    LogDialog dialog(directory + " Log", result, logButton);
    dialog.exec();

    m_Watcher->deleteLater();
}

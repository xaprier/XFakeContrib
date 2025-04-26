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
#include "Logger.hpp"
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
            Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemStatus to RepositoryEnableCheckBox.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        else
            connect(checkBox, &RepositoryEnableCheckBox::stateChanged, this, &RepositoryTableItemConnections::sl_RepositoryStateChanged);
    }
    {
        auto logButton = qobject_cast<QToolButton *>(m_Item->m_LogItem->Item(RepositoryTableItemLog::Status::BUTTON));
        if (!logButton)
            Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemLog to QToolButton.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        else
            connect(logButton, &QToolButton::clicked, this, &RepositoryTableItemConnections::sl_LogButtonClicked);
    }
    {
        auto pushButton = qobject_cast<QToolButton *>(m_Item->m_PushItem->Item(RepositoryTableItemPush::Status::BUTTON));
        if (!pushButton)
            Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemPush to QToolButton.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        else
            connect(pushButton, &QToolButton::clicked, this, &RepositoryTableItemConnections::sl_PushButtonClicked);
    }

    {
        auto commitFileButton = qobject_cast<QToolButton *>(m_Item->m_CommitFileButton->Item(RepositoryTableItemCommitFile::Status::BUTTON));
        if (!commitFileButton)
            Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemCommitFile to QToolButton.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        else
            connect(commitFileButton, &QToolButton::clicked, this, &RepositoryTableItemConnections::sl_SelectCommitFileClicked);
    }

    {
        auto branchCombo = qobject_cast<QComboBox *>(m_Item->m_BranchItem->Item(RepositoryTableItemBranch::Status::COMBOBOX));
        if (!branchCombo)
            Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemBranch to QComboBox.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        else
            connect(branchCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &RepositoryTableItemConnections::sl_BranchIndexChanged);
    }

    connect(this, &RepositoryTableItemConnections::si_CreateCommitter, this, &RepositoryTableItemConnections::sl_CreateCommitter);
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
        Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemBranch to QComboBox.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
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

    Logger::log_static(QObject::tr("Fetching logs for %1").arg(m_Item->GetAbsolutePath()).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    QFuture<QString> futureForLogFetch = QtConcurrent::run(&GitRepository::Log, m_Item->m_GitRepository, QStringList{});
#else
    QFuture<QString> futureForLogFetch = QtConcurrent::run(m_Item->m_GitRepository, &GitRepository::Log, QStringList{});
#endif

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
    Logger::log_static(QObject::tr("Pushing to %1").arg(m_Item->GetAbsolutePath()).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);

    this->m_Item->m_PushItem->Set(RepositoryTableItemPush::Status::LOADING);
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

    // start loading animation
    auto item = qobject_cast<QLabel *>(m_Item->m_RemoteItem->Item(RepositoryTableItemRemote::Status::LABEL));

    // if guard protection for invalid cast
    if (!item) {
        Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemRemote to QLabel.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    auto remote = item->text();
    this->m_Item->m_PushItem->setToolTip("Pushing Repository to " + remote);
}

void RepositoryTableItemConnections::sl_SelectCommitFileClicked(bool checked) {
    auto item = qobject_cast<QLabel *>(m_Item->m_RepoNameItem->Item(RepositoryTableItemName::Status::LABEL));

    // if guard protection for invalid cast
    if (!item) {
        Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemName to QLabel.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    auto dir = item->toolTip();  // toolTip will include repository path

    if (dir.isEmpty())  // if no repository path found, return
        return;

    // dir validation
    QDir directory(dir);
    if (!directory.exists()) {
        Logger::log_static(QObject::tr("The directory does not exist: %1").arg(dir).toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    auto commitFileButton = qobject_cast<QToolButton *>(m_Item->m_CommitFileButton->Item(RepositoryTableItemCommitFile::Status::BUTTON));

    // if guard protection for invalid cast
    if (!commitFileButton) {
        Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemCommitFile to QToolButton.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
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
    Logger::log_static(QObject::tr("Selected file: %1").arg(m_Item->m_SelectedFile).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
    m_Item->m_CommitFileButton->SetValidFileSelected(true);
    emit m_Item->GetConnections()->si_FileSelected();
}

void RepositoryTableItemConnections::sl_BranchIndexChanged(int index) {
    auto combo = qobject_cast<QComboBox *>(m_Item->m_BranchItem->Item(RepositoryTableItemBranch::Status::COMBOBOX));

    // if guard protection for invalid cast
    if (!combo) {
        Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemBranch to QComboBox.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
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
    m_Committers.append(committer);
    connect(committer, &GitCommitter::finished, this, &RepositoryTableItemConnections::sl_CommitterFinished);

    // update status
    m_Item->m_StatusItem->Set(RepositoryTableItemStatus::Status::LOADING);
    m_Item->m_StatusItem->setToolTip(QObject::tr("Creating commits for %1 days").arg(m_Committers.size()));

    Logger::log_static(QObject::tr("Creating commits(%1) for %2 days with file: %3").arg(commitCount).arg(m_Committers.size()).arg(file).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);

    // start committer
    committer->start();
}

void RepositoryTableItemConnections::sl_CommitterFinished() {
    auto committer = qobject_cast<GitCommitter *>(sender());

    // if guard protection for invalid cast
    if (!committer) {
        Logger::log_static(QObject::tr("Failed to cast from sender() to GitCommitter.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        return;
    }

    m_Committers.removeOne(committer);

    // Update status
    if (m_Committers.isEmpty()) {
        m_Item->m_StatusItem->Set(RepositoryTableItemStatus::Status::CHECKBOX);
        m_Item->m_StatusItem->setToolTip("");                             // Clear tool tip
        emit this->m_Item->GetConnections()->si_AllCommittersFinished();  // send signal for giving info to repositorycard
        Logger::log_static(QObject::tr("All Committers are finished with file: %1").arg(committer->CommitFile()).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
    } else {
        m_Item->m_StatusItem->setToolTip(QObject::tr("Creating commits for %1 days").arg(m_Committers.size()));
        emit this->m_Item->GetConnections()->si_CommitterFinished();  // send signal for giving info to repositorycard
        Logger::log_static(QObject::tr("Committer finished with file: %1, remained %2").arg(committer->CommitFile()).arg(m_Committers.size()).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);
    }

    committer->deleteLater();
}

void RepositoryTableItemConnections::sl_FetchLogFinished() {
    if (m_Watcher.isNull()) {
        Logger::log_static(QObject::tr("QFutureWatcher is null").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
        m_Watcher->deleteLater();
        return;
    }

    QString result = m_Watcher->future().result();
    QString repoDirectory = "";

    auto label = qobject_cast<QLabel *>(m_Item->m_RepoNameItem->Item(RepositoryTableItemName::Status::LABEL));

    // if guard protection for invalid cast
    if (!label) {
        Logger::log_static(QObject::tr("Failed to cast from RepositoryTableItemName to QLabel.").toStdString(), LoggingLevel::ERROR, __LINE__, __PRETTY_FUNCTION__);
    } else {
        repoDirectory = label->text();  // toolTip will include repository path
    }

    Logger::log_static(QObject::tr("Log fetching finished for: %1").arg(repoDirectory).toStdString(), LoggingLevel::INFO, __LINE__, __PRETTY_FUNCTION__);

    m_Item->m_LogItem->SetButton();  // Loaded log, dont show loading indicator

    LogDialog dialog(repoDirectory + " Log", result, m_Item->m_RepoNameItem);
    dialog.exec();

    m_Watcher->deleteLater();
}

#include "RepositoryTableItem.hpp"

#include <qobject.h>

#include "RepositoryTableItemCommitFile.hpp"
#include "RepositoryTableItemConnections.hpp"
#include "RepositoryTableItemPush.hpp"
#include "RepositoryTableType.hpp"

RepositoryTableItem::RepositoryTableItem(const QString& absolutePath, QObject* parent)
    : QObject(parent),
      m_AbsolutePath(absolutePath),
      m_StatusItem(new RepositoryTableItemStatus()),
      m_RepoNameItem(new RepositoryTableItemName()),
      m_BranchItem(new RepositoryTableItemBranch()),
      m_RemoteItem(new RepositoryTableItemRemote()),
      m_CommitFileButton(new RepositoryTableItemCommitFile()),
      m_LogItem(new RepositoryTableItemLog()),
      m_PushItem(new RepositoryTableItemPush()) {
    // GitRepository and GitChangeHandler objects
    m_GitRepository = new GitRepository(absolutePath, this);        // NOLINT
    m_GitChangeHandler = new GitChangeHandler(absolutePath, this);  // NOLINT

    // Repo name
    {
        int index = absolutePath.lastIndexOf('/');
        QString repoName = absolutePath.mid(index + 1);
        auto label = qobject_cast<QLabel*>(m_RepoNameItem->Item(RepositoryTableItemName::Status::LABEL));

        // if guard protection for invalid cast
        if (!label) {
            qWarning() << "Failed to cast from RepositoryTableItemName to QLabel.";
            return;
        }

        label->setText(repoName);
        label->setToolTip(absolutePath);
    }

    // Remote item
    {
        QString remote = m_GitRepository->Remote({"get-url", m_GitRepository->Remote({}).split('\n').first()}).trimmed();
        auto label = qobject_cast<QLabel*>(m_RemoteItem->Item(RepositoryTableItemRemote::Status::LABEL));

        // if guard protection for invalid cast
        if (!label) {
            qWarning() << "Failed to cast from RepositoryTableItemRemote to QLabel.";
            return;
        }

        label->setText(remote);
    }

    // Commit File Button
    {
        auto toolButton = qobject_cast<QToolButton*>(m_CommitFileButton->Item(RepositoryTableItemCommitFile::Status::BUTTON));

        // if guard protection for invalid cast
        if (!toolButton) {
            qWarning() << "Failed to cast from RepositoryTableItemCommitFile to QToolButton.";
            return;
        }

        toolButton->setToolTip(QObject::tr("Select Commit File(No File Selected)"));
        // todo: set icons for these buttons
    }

    // Log Button
    {
        auto toolButton = qobject_cast<QToolButton*>(m_LogItem->Item(RepositoryTableItemLog::Status::BUTTON));

        // if guard protection for invalid cast
        if (!toolButton) {
            qWarning() << "Failed to cast from RepositoryTableItemLog to QToolButton.";
            return;
        }

        QString remote = m_GitRepository->Remote({"get-url", m_GitRepository->Remote({}).split('\n').first()}).trimmed();
        toolButton->setToolTip(QObject::tr("Get latest logs for: %1").arg(remote));
        // todo: set icons for these buttons
    }

    // Setup Connections
    m_Connections = new RepositoryTableItemConnections(this);  // NOLINT
}

RepositoryTableItem::~RepositoryTableItem() {
    delete m_StatusItem;
    delete m_RepoNameItem;
    delete m_BranchItem;
    delete m_RemoteItem;
    delete m_CommitFileButton;
    delete m_LogItem;
    delete m_PushItem;
}

QObject* RepositoryTableItem::GetItem(RepositoryTableType itemType) const {
    switch (itemType) {
        case RepositoryTableType::REPO_STATUS:
            return m_StatusItem;
            break;
        case RepositoryTableType::REPO_NAME:
            return m_RepoNameItem;
            break;
        case RepositoryTableType::REPO_BRANCH:
            return m_BranchItem;
            break;
        case RepositoryTableType::REPO_REMOTE:
            return m_RemoteItem;
            break;
        case RepositoryTableType::REPO_COMMIT_FILE:
            return m_CommitFileButton;
            break;
        case RepositoryTableType::REPO_LOG:
            return m_LogItem;
            break;
        case RepositoryTableType::REPO_PUSH:
            return m_PushItem;
            break;
        default:
            return nullptr;
            break;
    }
}

bool RepositoryTableItem::IsFileWritable() const {
    if (m_SelectedFile.isEmpty()) {
        return false;  // File path is empty or invalid
    }

    QFileInfo info(QDir::cleanPath(m_SelectedFile));  // Normalize the path

    if (!info.exists()) {
        return false;
    }

    return info.isWritable();
}

int RepositoryTableItem::GetCommitterCount() const {
    return m_Connections->GetCommitterCount();
}

void RepositoryTableItem::Push() {
    auto button = qobject_cast<QToolButton*>(this->m_PushItem->Item(RepositoryTableItemPush::Status::BUTTON));

    if (!button) {
        qWarning() << "Failed to cast from RepositoryTableItemPush to QToolButton.";
        return;
    }

    emit button->clicked();

    // Create an event loop to wait for the operation to complete
    QEventLoop loop;

    // Connect the completion signal to quit the event loop
    connect(m_Connections, &RepositoryTableItemConnections::si_PushFinished, &loop, &QEventLoop::quit);

    // Start the event loop and block until pushCompleted is emitted
    loop.exec();
}

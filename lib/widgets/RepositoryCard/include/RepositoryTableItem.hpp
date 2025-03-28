#ifndef REPOSITORYTABLEITEM_HPP
#define REPOSITORYTABLEITEM_HPP

#include <qglobal.h>

#include <QPointer>
#include <QStandardItem>
#include <QString>

#include "GitChangeHandler.hpp"
#include "GitRepository.hpp"
#include "RepositoryTableItemBranch.hpp"
#include "RepositoryTableItemCommitFile.hpp"
#include "RepositoryTableItemLog.hpp"
#include "RepositoryTableItemName.hpp"
#include "RepositoryTableItemPush.hpp"
#include "RepositoryTableItemRemote.hpp"
#include "RepositoryTableItemStatus.hpp"
#include "RepositoryTableType.hpp"

// forward declaration for connections
class RepositoryTableItemConnections;

class RepositoryTableItem final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryTableItem)
  public:
    explicit RepositoryTableItem(const QString& absolutePath, QObject* parent = nullptr);
    ~RepositoryTableItem() final;

    [[nodiscard]] QObject* GetItem(RepositoryTableType itemType) const;
    [[nodiscard]] const QString& GetAbsolutePath() const { return m_AbsolutePath; }
    [[nodiscard]] bool IsEnabled() const { return dynamic_cast<RepositoryEnableCheckBox*>(m_StatusItem->Item(RepositoryTableItemStatus::Status::CHECKBOX))->IsChecked(); }
    [[nodiscard]] bool IsFileSelected() const { return !m_SelectedFile.isEmpty(); }
    [[nodiscard]] bool IsFileWritable() const;
    [[nodiscard]] int GetCommitterCount() const;

    QPointer<RepositoryTableItemConnections> GetConnections() const { return m_Connections; }

    void Push();

    friend class RepositoryTableItemConnections;

  private:
    GitChangeHandler* m_GitChangeHandler;
    GitRepository* m_GitRepository;
    QString m_AbsolutePath, m_SelectedFile;
    mutable QPointer<RepositoryTableItemConnections> m_Connections;
    QPointer<RepositoryTableItemStatus> m_StatusItem;
    QPointer<RepositoryTableItemPush> m_PushItem;
    QPointer<RepositoryTableItemName> m_RepoNameItem;
    QPointer<RepositoryTableItemRemote> m_RemoteItem;
    QPointer<RepositoryTableItemBranch> m_BranchItem;
    QPointer<RepositoryTableItemCommitFile> m_CommitFileButton;
    QPointer<RepositoryTableItemLog> m_LogItem;
};

#endif  // REPOSITORYTABLEITEM_HPP
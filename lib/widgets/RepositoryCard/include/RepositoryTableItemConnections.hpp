#ifndef REPOTABLEITEMCONNECTIONS_HPP
#define REPOTABLEITEMCONNECTIONS_HPP

#include <QList>
#include <QObject>
#include <QString>

#include "GitCommitter.hpp"
#include "RepositoryTableItem.hpp"

class RepositoryTableItem;

class RepositoryTableItemConnections : public QObject {
    Q_OBJECT
  public:
    explicit RepositoryTableItemConnections(RepositoryTableItem *item, QObject *parent = nullptr);
    [[nodiscard]] int GetCommitterCount() const { return m_Committers.count(); }
    [[nodiscard]] bool IsPushing() const { return m_Pushing; }

  protected slots:
    void sl_RepositoryStateChanged(int state);
    void sl_LogButtonClicked(bool checked);
    void sl_PushButtonClicked(bool checked);
    void sl_SelectCommitFileClicked(bool checked);
    void sl_BranchIndexChanged(int index);
    void sl_CreateCommitter(quint32 commitCount, QDate date, QString commitMessage, QString commitContent);
    void sl_CommitterFinished(QDate date);
    void sl_FetchLogFinished();

  signals:
    void si_PushFinished(bool success = true);
    void si_PushStarted();
    void si_CreateCommitter(quint32 commitCount, QDate date, QString commitMessage, QString commitContent);
    void si_StatusChanged(bool checked);
    void si_CommitterFinished(bool success = true);
    void si_AllCommittersFinished(bool success = true);
    void si_FileSelected();

  private:
    void _SetupConnections();
    void _LoadBranches();

  private:
    bool m_Pushing = false;
    QPointer<QFutureWatcher<bool>> m_Watcher;
    QString m_Output;
    RepositoryTableItem *m_Item;
    QString m_CommitFile;
    QList<GitCommitter *> m_Committers;
};

#endif  // REPOTABLEITEMCONNECTIONS_HPP
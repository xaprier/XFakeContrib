#ifndef REPOSITORYCARDCONNECTIONS_HPP
#define REPOSITORYCARDCONNECTIONS_HPP

#include <QFuture>
#include <QFutureWatcher>
#include <QList>
#include <QObject>

#include "Settings.hpp"

namespace Ui {
class RepositoryCardUI;
}

// Forward declaration for item
class RepositoryTableItem;

class RepositoryCardConnections final : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(RepositoryCardConnections)
  public:
    explicit RepositoryCardConnections(QList<RepositoryTableItem *> items, Settings *settings, Ui::RepositoryCardUI *ui, QObject *base = nullptr);
    ~RepositoryCardConnections() final;

  protected slots:
    void sl_CreateCommitsButtonClicked(bool checked);
    void sl_PushButtonClicked(bool checked);
    void sl_CommitCountCBStateChanged(int state);
    void sl_DateCBStateChanged(int state);
    void sl_CommitMessageCBStateChanged(int state);
    void sl_CommitContentCBStateChanged(int state);

    void sl_StartDateChanged(const QDate &date);
    void sl_EndDateChanged(const QDate &date);

    void sl_CommitterFinished();
    void sl_AllCommittersFinished();

    void sl_ItemPushCompleted(QFutureWatcher<void> *watcher);

  private:
    void _SetupConnections();
    void _SetupDates();
    void _WidgetsSetEnabled(bool enabled);
    void _UpdateButtonsStatus();

    [[nodiscard]] quint32 _GetCommitCount() const;
    [[nodiscard]] QString _GetCommitMessage() const;
    [[nodiscard]] QString _GetCommitContent() const;

    void _CreateCommits(const QDate &startDate, const QDate &endDate);

  private:
    QList<QFutureWatcher<void> *> m_PushWatchers;
    QList<RepositoryTableItem *> m_Items;
    Ui::RepositoryCardUI *m_Ui;
    Settings *m_Settings;
};

#endif  // REPOSITORYCARDCONNECTIONS_HPP